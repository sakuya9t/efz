#!/bin/bash
# Check that EfzRevival starts efz.exe and injects itself into it, as the original does.
#   tools/revival-test.sh [--revival DIR] [--game EXE] [--name NAME]
#     DIR   EfzRevival.exe, EfzRevival.dll and DDRAW.dll to test (default $REVIVAL_DIR,
#           the original 1.02h files; EfzRevival.ini always comes from $REVIVAL_DIR)
#     EXE   the efz.exe to start (default build/efz.exe, the rebuilt game)
#     NAME  names the run's folder, $EFZ_PLAY/revival-test/NAME (default "run")
#
# In the efz-revival-test docker image (toolchain/revival-test.Dockerfile): a virtual X
# server, wine, the launcher in a wine console. It answers the launcher's menu with
# 5 (Local Play: efz.exe with EfzRevival.dll in practice mode), waits for the game, and
# reports what shows that the DLL is in and running:
#   - efz.exe runs and has EfzRevival.dll and DDRAW.dll mapped
#   - the game window's title, which the DLL sets on the game's first frame
#     ("Eternal Fighter Zero -Revival- 1.02...")
# and leaves the folder with screenshots (launcher.png, game.png) and wine's output.
# EFZ_DIR is the game's data, as for tools/play.sh.
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
play=${EFZ_PLAY:-$HOME/.local/share/efz-decomp}
originals=${REVIVAL_DIR:-$HOME/.local/share/efz-decomp/revival/1.02h}
revival=$originals
exe=$repo/build/efz.exe
name=run
while [ $# -gt 0 ]; do
    case $1 in
        --revival) revival=$2; shift 2 ;;
        --game) exe=$2; shift 2 ;;
        --name) name=$2; shift 2 ;;
        *) echo "tools/revival-test.sh: unknown option $1" >&2; exit 1 ;;
    esac
done
die() { echo "tools/revival-test.sh: $*" >&2; exit 1; }
[ -n "${EFZ_DIR:-}" ] && [ -f "$EFZ_DIR/efz.exe" ] || die 'set EFZ_DIR to the game folder'
EFZ_DIR=$(cd "$EFZ_DIR" && pwd)
for f in EfzRevival.exe EfzRevival.dll DDRAW.dll; do
    [ -f "$revival/$f" ] || die "no $f in $revival"
done
[ -f "$exe" ] || die "no $exe"

# The run's folder: links to the game's data, copies of what is tested.
run=$play/revival-test/$name
rm -rf "$run"
mkdir -p "$run/game"
for entry in "$EFZ_DIR"/*; do
    ln -s "$entry" "$run/game/$(basename "$entry")"
done
# The links to what is copied go first: cp would write through them into $EFZ_DIR (a
# game folder with Revival installed has its own EfzRevival.* and DDRAW.dll).
rm -f "$run/game/efz.exe" "$run/game/key.ini" "$run/game/EfzRevival.exe" \
    "$run/game/EfzRevival.dll" "$run/game/DDRAW.dll" "$run/game/EfzRevival.ini"
cp "$exe" "$run/game/efz.exe"
[ ! -e "$EFZ_DIR/key.ini" ] || cp "$EFZ_DIR/key.ini" "$run/game/key.ini"
cp "$revival/EfzRevival.exe" "$revival/EfzRevival.dll" "$revival/DDRAW.dll" "$run/game/"
cp "$originals/EfzRevival.ini" "$run/game/"
mkdir -p "$play/revival-test/wine"

docker image inspect efz-revival-test >/dev/null 2>&1 ||
    docker build -q -t efz-revival-test -f "$repo/toolchain/revival-test.Dockerfile" \
        "$repo/toolchain" >/dev/null

docker run --rm --init --network none --ipc host \
    -v "$EFZ_DIR:$EFZ_DIR:ro" -v "$run:/run" -v "$play/revival-test/wine:/wine" \
    -e WINEPREFIX=/wine -e WINEDEBUG=-all -e DISPLAY=:99 -e WINEDLLOVERRIDES=ddraw=n,b \
    -w /run/game \
    efz-revival-test bash -c '
set -u
Xvfb :99 -screen 0 1024x768x24 >/dev/null 2>&1 &
sleep 2
[ -e /wine/.revival-setup ] || { wineboot -i >/dev/null 2>&1; wineserver -w; touch /wine/.revival-setup; }
# A wine desktop window, as for tools/play.sh: the game switches to 640x480, which
# only resizes it. The DLL override lets the game load the DDRAW.dll beside it, as
# Windows does, instead of wine'"'"'s own.
wine explorer /desktop=EFZ,800x600 wineconsole EfzRevival.exe > /run/wine.log 2>&1 &
for i in $(seq 60); do
    w=$(xdotool search --name "EfzRevival" 2>/dev/null | head -1)
    [ -n "$w" ] && break; sleep 1
done
sleep 3
import -window root /run/launcher.png 2>/dev/null
if [ -z "${w:-}" ]; then echo "launcher: no console window"; exit 1; fi
echo "launcher: console window \"$(xdotool getwindowname "$w")\""
xdotool windowactivate --sync "$w" 2>/dev/null || xdotool windowfocus "$w"
xdotool type --delay 100 5; xdotool key Return
# the game: a process whose command starts with its path (wine shows Z:\...\efz.exe)
findgame() {
    for p in /proc/[0-9]*; do
        c=$(tr "\0" " " < $p/cmdline 2>/dev/null) || continue
        case ${c%% *} in *efz.exe|*EFZ.EXE) echo ${p#/proc/}; return ;; esac
    done
}
for i in $(seq 60); do
    pid=$(findgame)
    [ -n "$pid" ] && break; sleep 1
done
[ -n "${pid:-}" ] || { echo "efz.exe: not started"; exit 1; }
echo "efz.exe: running (pid $pid)"
title=
for i in $(seq 60); do
    g=$(xdotool search --name "Eternal Fighter" 2>/dev/null | head -1)
    if [ -n "$g" ]; then
        title=$(xdotool getwindowname "$g")
        case $title in *Revival*) break ;; esac
    fi
    sleep 1
done
sleep 3
for dll in EfzRevival.dll DDRAW.dll; do
    if grep -qi "/$dll\$" /proc/$pid/maps; then echo "efz.exe: $dll mapped"; else echo "efz.exe: $dll NOT mapped"; fi
done
echo "game window: \"$title\""
import -window root /run/game.png 2>/dev/null
wineserver -k
'
echo "screenshots and wine.log in $run"
