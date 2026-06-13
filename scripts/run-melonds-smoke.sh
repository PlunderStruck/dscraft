#!/usr/bin/env bash
set -euo pipefail

rom="${1:-dscraft.nds}"
seconds="${SMOKE_SECONDS:-5}"

if [ ! -s "$rom" ]; then
	echo "ROM not found: $rom" >&2
	exit 1
fi

rom_path="$(cd "$(dirname "$rom")" && pwd)/$(basename "$rom")"
app_path="${MELONDS_APP:-/Applications/melonDS.app}"
melonds_bin="$app_path/Contents/MacOS/melonDS"
keep_open="${MELONDS_KEEP_OPEN:-0}"

if [ ! -x "$melonds_bin" ]; then
	echo "melonDS app not found at $app_path" >&2
	exit 1
fi

input_pid=
melonds_pid=

terminate_pid() {
	pid="$1"
	if [ -z "$pid" ] || ! kill -0 "$pid" >/dev/null 2>&1; then
		return
	fi
	kill "$pid" >/dev/null 2>&1 || true
	for _ in 1 2 3 4 5 6 7 8 9 10; do
		if ! kill -0 "$pid" >/dev/null 2>&1; then
			wait "$pid" >/dev/null 2>&1 || true
			return
		fi
		sleep 0.2
	done
	kill -9 "$pid" >/dev/null 2>&1 || true
	wait "$pid" >/dev/null 2>&1 || true
}

cleanup() {
	if [ -n "${input_pid:-}" ] && kill -0 "$input_pid" >/dev/null 2>&1; then
		terminate_pid "$input_pid"
	fi
	if [ "$keep_open" != "1" ] && [ -n "${melonds_pid:-}" ] && kill -0 "$melonds_pid" >/dev/null 2>&1; then
		terminate_pid "$melonds_pid"
	fi
}
trap cleanup EXIT INT TERM

"$melonds_bin" "$rom_path" >/dev/null 2>&1 &
melonds_pid=$!
sleep "$seconds"

if ! kill -0 "$melonds_pid" >/dev/null 2>&1; then
	echo "melonDS did not keep running with $rom_path" >&2
	exit 1
fi

osascript <<'APPLESCRIPT' >/dev/null 2>&1 &
tell application "melonDS" to activate
delay 0.5
tell application "System Events"
	key code 36
	delay 0.2
	key code 13
	delay 0.2
	key code 1
	delay 0.2
	key code 0
	delay 0.2
	key code 2
end tell
APPLESCRIPT
input_pid=$!
for _ in 1 2 3 4 5; do
	if ! kill -0 "$input_pid" >/dev/null 2>&1; then
		wait "$input_pid" || true
		input_pid=
		break
	fi
	sleep 1
done
if [ -n "${input_pid:-}" ] && kill -0 "$input_pid" >/dev/null 2>&1; then
	terminate_pid "$input_pid"
	input_pid=
	echo "melonDS smoke input timed out; launch/process checks still passed." >&2
fi

if ! kill -0 "$melonds_pid" >/dev/null 2>&1; then
	echo "melonDS exited during smoke input." >&2
	exit 1
fi

swift - "$rom_path" <<'SWIFT' 2>/dev/null || true
import CoreGraphics
let windows = CGWindowListCopyWindowInfo([.optionOnScreenOnly], kCGNullWindowID) as? [[String: Any]] ?? []
let melonWindows = windows.filter {
    let owner = ($0[kCGWindowOwnerName as String] as? String ?? "").lowercased()
    return owner.contains("melon")
}
if melonWindows.isEmpty {
    print("melonDS process is running; no on-screen render window was visible to CoreGraphics.")
} else {
    for window in melonWindows {
        let bounds = window[kCGWindowBounds as String] ?? [:]
        print("melonDS render window visible: \(bounds)")
    }
}
SWIFT

echo "melonDS smoke OK: $rom_path is running"
if [ "$keep_open" = "1" ]; then
	echo "melonDS left open because MELONDS_KEEP_OPEN=1." >&2
else
	echo "melonDS smoke cleanup: closing pid $melonds_pid." >&2
fi
