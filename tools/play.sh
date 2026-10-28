#!/bin/bash
# Play efz.exe under wine on an X display, such as the desktop you are logged into.
#   tools/play.sh                 run build/efz.exe (built with make link if missing)
#   tools/play.sh --original      run $EFZ_DIR/efz.exe instead
#   tools/play.sh --revival [DIR] run EfzRevival with build/efz.exe: the rebuilt
#                                 EfzRevival.exe, EfzRevival.dll and DDRAW.dll (made if
#                                 missing), or those in DIR ($REVIVAL_DIR: the originals)
#
# The game runs in a folder of its own, $EFZ_PLAY/game (default
# ~/.local/share/efz-decomp/game). It links to the data in $EFZ_DIR and holds real
# copies of everything the game writes: key.ini, the per-character .rec records,
# replays and screenshots. The original install is never written to. $EFZ_PLAY/wine is
# the wine prefix.
#
# With --revival the folder is $EFZ_PLAY/revival-game and the prefix
# $EFZ_PLAY/revival-wine. The launcher's console opens in the wine desktop: its menu's 5
# is Local Play (the game with EfzRevival.dll's practice mode). Its settings start as
# $REVIVAL_DIR's EfzRevival.ini and are kept from then on. DDRAW.dll draws with
# Direct3D 9, which needs OpenGL, so wine's Direct3D keeps its default renderer and the
# docker image is efz-revival-test (toolchain/revival-test.Dockerfile, with Mesa).
#
# Environment:
#   EFZ_DIR       the folder with the original game (required)
#   DISPLAY       the X display to show the game on. A terminal in the desktop session
#                 has it set already; from ssh, pass it, e.g. DISPLAY=:10.
#   EFZ_DESKTOP   size of the wine desktop window the game runs in (default 640x480,
#                 800x600 with --revival). The game switches the screen to 640x480 or
#                 320x240; inside a wine desktop that only resizes this window. "off"
#                 lets it change the real screen mode.
#   EFZ_NETWORK   the container's network (default none; host for Revival's netplay)
#   REVIVAL_DIR   the 1.02h files (default ~/.local/share/efz-decomp/revival/1.02h)
#   WINEDEBUG     wine's log channels (default -all, quiet)
#
# Wine comes from the host if it is installed, else from the efz-play docker image
# (toolchain/play.Dockerfile, built on first use from the toolchain's efz-msvc71).
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
play=${EFZ_PLAY:-$HOME/.local/share/efz-decomp}
game=$play/game
desktop=${EFZ_DESKTOP:-640x480}

die() { echo "tools/play.sh: $*" >&2; exit 1; }
[ -n "${EFZ_DIR:-}" ] || die 'set EFZ_DIR to the folder containing the original efz.exe'
[ -d "$EFZ_DIR" ] || die "no folder $EFZ_DIR"
EFZ_DIR=$(cd "$EFZ_DIR" && pwd)
[ -f "$EFZ_DIR/efz.exe" ] || die "no efz.exe in $EFZ_DIR"
[ -n "${DISPLAY:-}" ] || die 'set DISPLAY to the X display to play on (e.g. DISPLAY=:10)'

exe=$repo/build/efz.exe
revival=
case ${1:-} in
    --original) exe=$EFZ_DIR/efz.exe ;;
    --revival) revival=${2:-built} ;;
    '') ;;
    *) die "unknown option $1" ;;
esac
[ "$exe" != "$repo/build/efz.exe" ] || [ -f "$exe" ] || make -C "$repo" link EFZ_DIR="$EFZ_DIR"

prefix=$play/wine
image=efz-play
if [ -n "$revival" ]; then
    game=$play/revival-game
    prefix=$play/revival-wine
    image=efz-revival-test
    desktop=${EFZ_DESKTOP:-800x600}
    revival_dir=${REVIVAL_DIR:-$HOME/.local/share/efz-decomp/revival/1.02h}
    if [ "$revival" = built ]; then
        make -C "$repo" revival-launcher build/revival/dll/EfzRevival.final.dll \
            build/revival/ddraw/DDRAW.final.dll
        bins=("$repo/build/revival/launcher/EfzRevival.exe"
              "$repo/build/revival/dll/EfzRevival.final.dll"
              "$repo/build/revival/ddraw/DDRAW.final.dll")
    else
        bins=("$revival/EfzRevival.exe" "$revival/EfzRevival.dll" "$revival/DDRAW.dll")
    fi
    for f in "${bins[@]}" "$revival_dir/EfzRevival.ini"; do [ -f "$f" ] || die "no $f"; done
fi

# The game folder: links to the original's files, except for what the game writes.
mkdir -p "$game/system" "$game/replay" "$game/snap"
for entry in "$EFZ_DIR"/*/; do
    name=$(basename "$entry")
    case $name in
        system|replay) ;;
        *) ln -sfn "$EFZ_DIR/$name" "$game/$name" ;;
    esac
done
for entry in "$EFZ_DIR"/system/*; do
    name=$(basename "$entry")
    if [ -d "$entry" ]; then
        # system\<character>\ gets the character's .rec record written into it
        mkdir -p "$game/system/$name"
        for file in "$entry"/*; do
            [ -e "$file" ] || continue
            case $file in
                *.rec) [ -e "$game/system/$name/$(basename "$file")" ] ||
                       cp "$file" "$game/system/$name/" ;;
                *) ln -sfn "$file" "$game/system/$name/$(basename "$file")" ;;
            esac
        done
    else
        ln -sfn "$entry" "$game/system/$name"
    fi
done
[ -e "$game/key.ini" ] || [ ! -e "$EFZ_DIR/key.ini" ] || cp "$EFZ_DIR/key.ini" "$game/key.ini"
cp "$exe" "$game/efz.exe"
run=(efz.exe)
if [ -n "$revival" ]; then
    rm -f "$game/EfzRevival.exe" "$game/EfzRevival.dll" "$game/DDRAW.dll"
    cp "${bins[0]}" "$game/EfzRevival.exe"
    cp "${bins[1]}" "$game/EfzRevival.dll"
    cp "${bins[2]}" "$game/DDRAW.dll"
    [ -e "$game/EfzRevival.ini" ] || cp "$revival_dir/EfzRevival.ini" "$game/EfzRevival.ini"
    run=(wineconsole EfzRevival.exe)
    # The game loads the DDRAW.dll beside it, as Windows does, instead of wine's own.
    export WINEDLLOVERRIDES=ddraw=n,b
fi

mkdir -p "$prefix"
export WINEDEBUG=${WINEDEBUG:--all}
if [ "$desktop" = off ]; then
    cmd=(wine "${run[@]}")
else
    cmd=(wine explorer "/desktop=EFZ,$desktop" "${run[@]}")
fi
# A new prefix is set up completely before the first game (wineboot, then waiting for
# wineserver), with DirectDraw on wine's GDI renderer: the game only blits 2D surfaces,
# and this needs no OpenGL from the X server (xrdp sessions and Xvfb often have none).
# Revival's DDRAW.dll needs Direct3D 9, so its prefix keeps the default renderer.
setup=(sh -c "wineboot -i && wine reg add 'HKCU\\Software\\Wine\\Direct3D' /v renderer /d gdi /f && wineserver -w")
[ -z "$revival" ] || setup=(sh -c "wineboot -i && wineserver -w")

if command -v wine >/dev/null; then
    cd "$game"
    export WINEPREFIX=$prefix WINEARCH=win32 LANG=ja_JP.UTF-8
    [ -e "$prefix/.efz-setup" ] || { "${setup[@]}" >/dev/null 2>&1 && touch "$prefix/.efz-setup"; }
    exec "${cmd[@]}"
fi

command -v docker >/dev/null || die 'needs wine or docker'
if ! docker image inspect efz-play >/dev/null 2>&1; then
    echo 'building the efz-play image'
    docker build -q -t efz-play -f "$repo/toolchain/play.Dockerfile" "$repo/toolchain" >/dev/null
fi
if ! docker image inspect "$image" >/dev/null 2>&1; then
    echo "building the $image image"
    docker build -q -t "$image" -f "$repo/toolchain/revival-test.Dockerfile" "$repo/toolchain" >/dev/null
fi

# X access from the container: the display's socket, and its cookie for any host name.
display=${DISPLAY#*:}; display=${display%%.*}
xauth=$play/xauthority
install -m 600 /dev/null "$xauth"
xauth nlist "$DISPLAY" 2>/dev/null | sed -e 's/^..../ffff/' | xauth -f "$xauth" nmerge - 2>/dev/null || true
args=(--rm --init --network "${EFZ_NETWORK:-none}" --ipc host
      -v "/tmp/.X11-unix/X$display:/tmp/.X11-unix/X$display" -e "DISPLAY=:$display"
      -v "$xauth:/tmp/xauthority:ro" -e XAUTHORITY=/tmp/xauthority
      -v "$EFZ_DIR:$EFZ_DIR:ro" -v "$game:/game" -v "$prefix:/wine"
      -e WINEPREFIX=/wine -e WINEDEBUG -w /game)
[ -z "$revival" ] || args+=(-e WINEDLLOVERRIDES)
# Sound through the session's PulseAudio (or PipeWire's) server, if there is one.
pulse=${XDG_RUNTIME_DIR:-/run/user/$(id -u)}/pulse/native
[ -S "$pulse" ] && args+=(-v "$pulse:/run/pulse/native" -e PULSE_SERVER=unix:/run/pulse/native)
[ -e "$prefix/.efz-setup" ] || {
    docker run "${args[@]}" "$image" "${setup[@]}" >/dev/null 2>&1 && touch "$prefix/.efz-setup"; }
exec docker run "${args[@]}" "$image" "${cmd[@]}"
