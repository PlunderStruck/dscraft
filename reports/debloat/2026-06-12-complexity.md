# De-Bloat Report: Complexity Cleanup

**Date:** 2026-06-12
**Health Score:** 79/100
**Scope:** texture creation, API widget drawing, header-owned storage, and PCX dead-code cleanup

## Summary

- Starting findings: 22 dead symbols, 47 isolated symbols, 24 cycles, 50 similar pairs, 3 wrappers, 9 passthroughs, 7 stale abstractions, 3 drifted files. Source: `scip-query health`.
- Current findings: 21 dead symbols, 33 isolated symbols, 26 cycles, 50 similar pairs, 3 wrappers, 9 passthroughs, 8 stale abstractions, 2 drifted files. Source: `scip-query health`.
- Health score rose to 79/100. Remaining score drag is dominated by capped cycle and similarity penalties; many of those findings are normal C header/source declaration relationships or header/global false positives after manual inspection.
- Chosen actions: extract duplicated texture slot policy, extract repeated API textured-quad drawing, move selected header-owned global storage into source files, delete a genuinely unused PCX 1-bit loader, and move single-use BMP screenshot types out of the public include tree.

## Priority 3: Consolidation Opportunities

- `Game_CreateTexture`, `Game_CreateTextureAlpha`, `Game_CreateAlphaMask`, `Game_CreateTextureAlphaMask`, and `Game_CreateMaskedTexture` repeated the same asset-backed slot-request policy with only the loader call changing. Source: `scip-query code 'source/game/textures.Os.c:91-179'`.
- `Game_CreateTextureBuffer` and `Game_CreateTextureBuffer16` repeated the free-slot scan. Source: `scip-query code 'source/game/textures.Os.c:181-207'`.
- `API_DrawWindow`, `API_UpdateButton`, `API_UpdateCheckBox`, `API_UpdateSlider`, and `API_UpdateVSlider` repeated background binding and textured-quad rendering. Source: `scip-query code 'source/API/API.Os.c:86-383'`.
- `API_CreateSlider` and `API_CreateVSlider` repeated entity allocation and slider initialization, differing only by draw function and x/y dimensions. Source: `scip-query code 'source/API/API.Os.c:611-707'`.

## Priority 1: Safe Deletions

- Removed `ReadPCX1bit` from `source/game/pcx.Os.c`; the only 1-bit dispatch path was already commented out, and no live code referenced the helper.
- Deleted `include/common/bmp.h` after verifying `source/screenshot.Os.c` was its only consumer, then moved `HEADER` and `INFOHEADER` into that source file.

## Priority 2: Structural Fixes

- Converted selected header-owned globals to `extern` declarations and added their storage definitions in source files: textures, map test buffer, dual3D sprite state, font state, interface inventory state, and survival mob list.
- Reduced real global-storage duplication, though scip-query still reports normal C header/source declaration loops as cycles.

## Structural Metrics

- Circular dependencies: 26 after the current reindex. Source: `scip-query health`.
- Similar pairs: 50, though many broad `API` pairs were rejected as analyzer noise because they reported shared header/global references rather than matching behavior. Source: `scip-query similar --min-similarity 0.5 --min-callees 3 -n 20`.
- Top complexity hotspots remain `Game_Frame`, `Game_Init`, `Game_Kill`, `Game_VBlank`, and `RenderScene`. Source: `scip-query health`.

## Verification

- Reindexed successfully with `scip-query reindex`.
- `scip-query incomplete-migration` reported no incomplete migrations.
- `scip-query diff-gate` reported echo/new-dead findings for C globals, inline/static helpers, and header types; accepted as false positives where the compiler and source references prove they are wired.
- Docker/devkitARM build passed and produced `dscraft.nds`.
- melonDS launched `/Users/aydansalois/Documents/GitHub/dscraft/dscraft.nds`; the File menu reported `DS slot: dscraft.nds`, the System menu exposed `Pause` rather than `Resume`, and the process stayed running after start/movement key input.
- `ndstool -l dscraft.nds` inside the devkitARM container confirmed `/dscraft/worlds/small.map` is packaged in the ROM.
- `scip-query cleanup-plan --verify` still reports FAT layout fields, `TABLE_SIN`, and `source/template.c main()` as dead, but project checker verification is unavailable and manual inspection rejects them as unsafe deletions.
