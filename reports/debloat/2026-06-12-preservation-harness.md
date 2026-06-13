# Preservation Harness and Cleanup Report

**Date:** 2026-06-12
**Health Score:** 81/100
**Scope:** Build, ROM asset, emulator smoke, warning, and low-risk structural cleanup.

## Summary

- Added repeatable local/Docker build, ROM asset, full-check, and melonDS smoke scripts.
- Documented runtime entry points, NitroFS asset assumptions, and known scip-query false positives.
- Removed all compiler warnings other than none: the latest full check reports 0 deprecated warnings and 0 non-deprecated warnings.
- Reduced public header surface by moving private environment, texture-bank, PCX-header, font, and interface inventory details into their owning source files.
- Fixed the recursive Makefile rule so parallel builds propagate jobserver tokens, then added the missing generated soundbank dependency exposed by parallel builds.

## Verification

Latest command:

```sh
SMOKE_SECONDS=2 scripts/check.sh --with-emulator
```

Result:

- `dscraft.nds` builds successfully.
- ROM assets OK: 10 required NitroFS paths present.
- `scip-query reindex` completes.
- `scip-query health`: 81/100.
- `scip-query incomplete-migration`: no incomplete migrations.
- melonDS launch/process/window smoke passes; AppleScript input times out on this machine, but the ROM remains running and render windows are visible.

Warning check:

```sh
rg "warning:" /tmp/dscraft-full-check-final.log | rg -v "deprecated"
rg "deprecated" /tmp/dscraft-full-check-final.log | wc -l
```

Result:

- Non-deprecated warnings: 0.
- Deprecated warnings: 0.

## Remaining Health Signals

- Dead code: still dominated by analyzer-visible external/runtime entries and vendored FAT/header fields.
- Cycles: still mostly C header/source implementation cycles and vendored library cycles.
- Similar pairs: noisy because scip-query treats many header globals and source definitions as equivalent callee sets in this C codebase.
- Stale abstractions: remaining findings are `mutex_t` in FAT locking support and `settings_struct`, which is genuinely shared by player/menu settings.

## Diff Gate Notes

Command:

```sh
scip-query diff-gate
```

Result:

- The command reports 107 findings against the large working-tree diff.
- Accepted echo findings: C `extern` declarations in headers compared with their source definitions, especially API and filesystem globals.
- Accepted new-dead findings: runtime entry points (`main`), static inline map helpers used through same-file/header expansion, private C helper functions, and local structs whose fields are accessed in ways the current index does not model.
- Actionable follow-up is to add a committed `.scipquery-baseline.json` only after this preservation cleanup lands, so future runs detect new findings instead of replaying this legacy baseline.

## Next Safe Targets

- Continue reducing header dependencies where a source file can own implementation state.
- Consider a careful state-module split for engine/game entry points, but only in small build-and-smoke-checked batches.
- Leave vendored FAT and LodePNG internals alone unless replacing the dependency wholesale.
