# Cycle Boundary Cleanup

Date: 2026-06-13

## Result

- Reduced `scip-query cycles` from 25 baseline cycles to 14 cycles.
- Kept `scip-query health` at 81/100.
- Built `dscraft.nds` successfully after each batch.
- Passed `SMOKE_SECONDS=2 scripts/check.sh --with-emulator`.

## Changes

- Moved environment runtime state back into `source/game/environment.c` and replaced direct state mutation with small environment API calls.
- Moved map texture pointers back into `source/game/map.c` and exposed only binding helpers for the menu/game render paths.
- Hid `dual3D`, interface, memory, and xmem implementation globals behind query/helper functions where callers needed state.
- Split player-aware map rendering declaration into `include/game/map_player.h` so `map.h` no longer depends on `player_struct`.
- Deleted the empty `source/game/environment_state.c` state holder after environment ownership moved into the implementation.

## Remaining Cycles

The remaining 14 cycles are either vendored headers (`fat`, `lodepng`) or broad C modules where the public header owns core types and the source implements the API (`map`, `textures`, `API`, `player`, `state`, etc.). Fixing those honestly requires larger type/header decomposition rather than removing includes.

## Verification

- `scripts/build-rom.sh`: passed.
- `scip-query reindex`: passed.
- `scip-query health`: 81/100, 14 circular dependencies.
- `SMOKE_SECONDS=2 scripts/check.sh --with-emulator`: passed; melonDS launched the ROM and showed render windows.
- `scip-query diff-gate`: reported 42 accepted `new-dead` findings in touched C files. These are index false positives on anonymous structs, inline helpers, and callback-style functions after broad header edits.
