#!/usr/bin/env bash
set -euo pipefail

clean=1
jobs="${JOBS:-2}"

for arg in "$@"; do
	case "$arg" in
		--no-clean) clean=0 ;;
		-j*) jobs="${arg#-j}" ;;
		*) echo "usage: $0 [--no-clean] [-jN]" >&2; exit 2 ;;
	esac
done

run_make() {
	if [ "$clean" -eq 1 ]; then
		make clean
	fi
	make -j"$jobs"
}

if [ -n "${DEVKITARM:-}" ]; then
	run_make
else
	if ! command -v docker >/dev/null 2>&1; then
		echo "DEVKITARM is not set and docker is not available." >&2
		exit 1
	fi

	tmpcfg="$(mktemp -d)"
	trap 'rm -rf "$tmpcfg"' EXIT

	DOCKER_CONFIG="$tmpcfg" docker run --rm \
		-v "$PWD":/dscraft \
		-w /dscraft \
		devkitpro/devkitarm:latest \
		bash -lc "source /opt/devkitpro/ndsvars.sh && if [ $clean -eq 1 ]; then make clean; fi && make -j$jobs"
fi

if [ ! -s dscraft.nds ]; then
	echo "Build completed but dscraft.nds was not produced." >&2
	exit 1
fi

echo "Built dscraft.nds"
