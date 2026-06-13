# dscraft
minecraft adaptation for nintendo DS


all written in summer 2011


feel free to use this (terrible) code for non-commercial purposes as long as you give credit to original authors; this repo includes some libraries i didn't write myself like lodepng, iniparser and pcx loader

## Local build and smoke checks

The repository now has a small preservation harness for working on the old DS
code without relying on memory:

```sh
scripts/build-rom.sh
scripts/check-rom-assets.sh dscraft.nds
scripts/check.sh
scripts/check.sh --with-emulator
```

`scripts/build-rom.sh` uses a local devkitARM environment when `DEVKITARM` is
set, otherwise it builds through the `devkitpro/devkitarm` Docker image.
`scripts/check-rom-assets.sh` verifies that required NitroFS data, including
`/dscraft/worlds/small.map`, is packaged into the ROM. The emulator smoke check
launches `dscraft.nds` in melonDS and confirms the process stays alive after
basic input, then closes the melonDS process it started. Set
`MELONDS_KEEP_OPEN=1` when you intentionally want to keep the emulator open
after the smoke check.

See `docs/architecture/runtime-entrypoints.md` before deleting code that looks
dead to static analysis.
