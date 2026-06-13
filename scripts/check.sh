#!/usr/bin/env bash
set -euo pipefail

with_emulator=0

for arg in "$@"; do
	case "$arg" in
		--with-emulator) with_emulator=1 ;;
		*) echo "usage: $0 [--with-emulator]" >&2; exit 2 ;;
	esac
done

scripts_dir="$(cd "$(dirname "$0")" && pwd)"
repo_root="$(cd "$scripts_dir/.." && pwd)"
cd "$repo_root"

"$scripts_dir/build-rom.sh"
"$scripts_dir/check-rom-assets.sh" dscraft.nds

if command -v scip-query >/dev/null 2>&1; then
	scip-query reindex
	scip-query health
	scip-query incomplete-migration
else
	echo "scip-query not found; skipped code-health checks." >&2
fi

if [ "$with_emulator" -eq 1 ]; then
	"$scripts_dir/run-melonds-smoke.sh" dscraft.nds
fi

echo "DSCraft check complete"
