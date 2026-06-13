# Map Header Split Plan

## Goal

Split the overloaded map public header into focused headers without changing game behavior. Done means `map.h` remains a compatibility include, narrower headers own the map type/access/API groups, the ROM builds, and the melonDS smoke check still launches and cleans up.

## Evidence

- `scip-query plan-context include/game/map.h`: `map.h` has 151 external consumers and usually co-changes with `source/game/map.c`, `source/menu/menu_main.Os.c`, and interface/API headers.
- `scip-query code 'include/game/map.h:1-520'`: current `map.h` mixes constants, map structs, extern state, public map functions, file callbacks, and static inline access helpers.
- `scip-query rdeps include/game/map.h`: consumers include API, player, map, controls, environment, menu, and template entrypoint files.
- `scip-query change-surface include/game/map.h`: this is high risk, so the first cut keeps `map.h` as an aggregate compatibility header.

## Steps

- [x] Create `include/game/map_types.h` for constants, core map structs, and map-global extern declarations from `map.h:4-242`.
- [x] Create `include/game/map_api.h` for public map lifecycle and block declarations from `map.h:247-265` and `map.h:472-473`.
- [x] Create `include/game/map_io.h` for map sector and cluster read/write/open declarations from `map.h:244-286` plus map save/streaming declarations.
- [x] Create `include/game/map_render.h` for texture, fog, light-map, and map draw declarations from `map.h:250-268`.
- [x] Create `include/game/map_access.h` for static inline map access, collision, and lighting helpers from `map.h:288-441`.
- [x] Replace `include/game/map.h` with a compatibility aggregate that includes the focused headers.
- [x] Update `include/game/map_player.h` to depend on the narrow map type header plus player types.
- [x] Move source consumers off `map.h`; no source or header includes the aggregate after the migration.
- [x] Build after the split, then reindex and inspect cycles before changing broader consumers.
- [ ] Run `SMOKE_SECONDS=2 scripts/check.sh --with-emulator` and `scip-query diff-gate`; accept known C index false positives only with explicit notes.
