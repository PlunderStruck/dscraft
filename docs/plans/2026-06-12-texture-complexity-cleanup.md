# Texture Complexity Cleanup

Date: 2026-06-12

## Goal

Reduce real complexity in texture creation without changing the game-visible contract: asset-backed texture creators still fail when the file cannot be opened, return a previously loaded texture for a duplicate filename when a free slot exists, otherwise load into the first free `Texture` slot.

## Current State

- `source/game/textures.Os.c:91-179` repeats the same file-open, free-slot scan, duplicate-name scan, load, and return flow across five asset-backed texture creators. Source: `scip-query code 'source/game/textures.Os.c:91-179'`.
- Buffer-backed creators at `source/game/textures.Os.c:181-207` repeat the free-slot scan without the asset-file or duplicate-name policy. Source: `scip-query code 'source/game/textures.Os.c:181-207'`.
- `source/game/textures.Os.c` has 53 external consumers, so this is a medium-risk internal refactor that must preserve public function signatures. Source: `scip-query change-surface source/game/textures.Os.c`.

## Reuse Audit

- The same-signature scan identified `Game_CreateTexture`, `Game_CreateAlphaMask`, and `Game_CreateMaskedTexture` as same-shape functions returning `MTL_img*` from `char* filename, char* directory`. Source: `scip-query similar-signatures --min-loc 5 -n 20`.
- `Game_CreateTexture` and `Game_CreateAlphaMask` have 100% tracked callee overlap; `Game_CreateTexture` and `Game_CreateMaskedTexture` share the file/slot/duplicate policy but diverge at the final loader. Source: `scip-query convergence Game_CreateTexture Game_CreateAlphaMask` and `scip-query convergence Game_CreateTexture Game_CreateMaskedTexture`.

## Plan

- [x] Add `Game_FindFreeTexture`, `Game_FindLoadedTexture`, `Game_TextureFileExists`, and `Game_RequestTextureSlot` as static helpers in `source/game/textures.Os.c`.
- [x] Replace duplicated asset-backed creator control flow with calls to `Game_RequestTextureSlot`, leaving each public function responsible for its own loader call.
- [x] Replace duplicated buffer-backed free-slot loops with `Game_FindFreeTexture`.
- [x] Reindex, run `scip-query diff-gate`, and build with the devkitARM Docker image.

## Stress Test

- The refactor is reversible and internal: no header signatures changed. Source: `scip-query code 'include/game/textures.h:1-80'`.
- The essential edge case is duplicate texture lookup. The helper intentionally checks for a free slot before returning a duplicate to match the original loop ordering. Source: `scip-query code 'source/game/textures.Os.c:91-179'`.

## Verification

- `scip-query reindex` completed successfully after the edit.
- `scip-query incomplete-migration` reported no incomplete migrations.
- `scip-query diff-gate` reported two `new-dead` findings for `Game_RequestTextureSlot` and `Game_TextureFileExists`; accepted as analyzer false positives because `scip-query code 'source/game/textures.Os.c:80-195'` shows the public texture creators calling `Game_RequestTextureSlot`, and `Game_RequestTextureSlot` calls `Game_TextureFileExists`.
- Docker/devkitARM build passed and produced `dscraft.nds`: `source /opt/devkitpro/ndsvars.sh && make clean >/dev/null && make -j2`.
