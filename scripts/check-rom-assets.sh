#!/usr/bin/env bash
set -euo pipefail

rom="${1:-dscraft.nds}"

if [ ! -s "$rom" ]; then
	echo "ROM not found: $rom" >&2
	exit 1
fi

required_paths=(
	"/dscraft/worlds/small.map"
	"/dscraft/loading.pcx"
	"/dscraft/cursor.pcx"
	"/dscraft/inventory.pcx"
	"/dscraft/menu/button.pcx"
	"/dscraft/menu/control1.pcx"
	"/dscraft/font/HUD.pcx"
	"/dscraft/textures/logo.pcx"
	"/dscraft/textures/crosshair.pcx"
	"/dscraft/packs/eldpack/terrain.png"
)

list_file="$(mktemp)"
trap 'rm -f "$list_file"' EXIT

if command -v ndstool >/dev/null 2>&1; then
	ndstool -l "$rom" > "$list_file"
else
	if ! command -v docker >/dev/null 2>&1; then
		echo "ndstool is not installed and docker is not available." >&2
		exit 1
	fi

	tmpcfg="$(mktemp -d)"
	trap 'rm -f "$list_file"; rm -rf "$tmpcfg"' EXIT
	DOCKER_CONFIG="$tmpcfg" docker run --rm \
		-v "$PWD":/dscraft \
		-w /dscraft \
		devkitpro/devkitarm:latest \
		bash -lc "source /opt/devkitpro/ndsvars.sh && ndstool -l '$rom'" > "$list_file"
fi

missing=0
for path in "${required_paths[@]}"; do
	if ! grep -Fq "$path" "$list_file"; then
		echo "Missing NitroFS asset: $path" >&2
		missing=1
	fi
done

if [ "$missing" -ne 0 ]; then
	exit 1
fi

echo "ROM assets OK: ${#required_paths[@]} required paths present in $rom"
