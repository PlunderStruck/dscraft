# Map Header Split

Date: 2026-06-13

## Result

- Split the old aggregate `include/game/map.h` into focused headers:
  - `map_types.h` for constants, map structs, and shared map state declarations.
  - `map_access.h` for inline block, light, collision, and surface helpers.
  - `map_api.h` for world lifecycle and block mutation calls.
  - `map_io.h` for map file, sector, and cluster streaming calls.
  - `map_render.h` for map texture, fog, light-map, and draw calls.
- Kept `map.h` as a compatibility aggregate for future external callers.
- Migrated in-repo callers away from `map.h`; no source/header currently includes the aggregate.
- Moved quad-cache inline helpers out of the public access header and into `source/game/map.c`, because only map internals use them.

## Verification

- `scripts/build-rom.sh`: passed.
- `scip-query reindex`: passed.
- `scip-query health`: 81/100, 14 circular dependencies.
- `SMOKE_SECONDS=2 scripts/check.sh --with-emulator`: passed; melonDS launched the ROM and the smoke script closed its process.
- `scip-query diff-gate`: reported accepted C-index false positives after header moves. The findings are mostly moved inline helpers, anonymous C structs, runtime entrypoint `main`, and callback-style functions that build and smoke verification prove are still wired.

## Notes

The split is mostly an architecture cleanup, not a score chase. `scip-query cycles` still reports C header/source declaration pairs for other modules, but the map aggregate is no longer part of the in-repo include graph.
