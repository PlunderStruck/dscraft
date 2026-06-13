# Runtime Entrypoints And Preservation Notes

This project is an old Nintendo DS homebrew game. A runtime entry point is code that the platform or toolchain calls directly instead of through an ordinary C reference from another source file. In this repository, `source/template.c:main` is the ARM9 program entry point for the ROM, so graph tools can report it as dead even though deleting it would remove the game. `source/template.c` includes `include/game/map_types.h` for shared startup state such as `packPath`; it should not include the aggregate `include/game/map.h` unless startup needs the full map API again.

The FAT headers under `include/fat/` describe on-disk filesystem data. An on-disk layout is a C representation of bytes stored by a filesystem or file format, where field order and size matter because external data is read into that shape. Fields in `DIR_ENTRY` and filesystem-type constants can appear unused to source-indexing tools, but they preserve compatibility with FAT directory records and partition metadata.

`include/common/math_lookup.h:TABLE_SIN` is a lookup table: a precomputed array used to trade storage for fast numeric access on constrained hardware. The table is reached through math macros and inline code, so it can look disconnected in a symbol graph even when it is part of the intended math API.

NitroFS assets are files packaged into the Nintendo DS ROM and read at runtime through libnds filesystem APIs. The game needs `/dscraft/worlds/small.map` plus menu, font, texture, and pack assets in the ROM; a build that compiles but omits those files can boot to an unusable game.

## Required Local Gates

- Build the ROM with `scripts/build-rom.sh`.
- Verify packaged game data with `scripts/check-rom-assets.sh dscraft.nds`.
- Run the full local check with `scripts/check.sh`.
- For gameplay smoke testing, run `scripts/check.sh --with-emulator` with melonDS installed.

## Known Analyzer False Positives

- `source/template.c:main` is an entry point, not dead code.
- FAT directory fields and partition constants are data-layout declarations, not ordinary unused variables.
- Header/source declaration pairs can appear as circular dependencies in `scip-query cycles`; inspect whether the cycle is a real ownership problem before refactoring.
- C struct fields and header globals can appear in wrapper, passthrough, and similarity reports as if they were functions. Treat those reports as leads, not proof.
