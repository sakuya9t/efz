#!/bin/bash
# The network test's match against EfzRevival 1.02h (tools/nettest.py revival, docs/
# compat.md "The network layer"), inside the efz-revival-test docker image with no
# network but its own loopback: EfzRevival.exe under wine on a virtual X server with the
# original efz.exe, and the native game (/native/efz) on the other end of the loopback.
#
# The run's folder is /run: game/ the game's folder for Revival (made by nettest.py),
# native/ the native game's save and log folders. What it is told, in the environment:
#   HOST      revival or native: which end hosts (the other joins 127.0.0.1:PORT)
#   PORT      the host's UDP port
#   SEED      the random keys' seed (Revival's end: bash's RANDOM)
#   KEYS      the native game's --keys: random presses of P1's controls
#   FRAMES    the native game's --frames: the most it runs
#   FIGHT     seconds of each fight: the first ends with Esc on Revival's end (both
#             games back at character select, both write the fight's replay), the
#             second, once it starts, is stopped after half as long
#   LAG       EFZ_NET_LAG for the native game ("MS[:JITTER]"), or empty
#   EFZ_DIR   the game's data, mounted at its own path
# It writes driver.log (what happened when), native.out, wine.log and screenshots
# (hosting.png, fight.png, end.png).
set -u

log() { echo "$(date +%T) $*" | tee -a /run/driver.log; }
fail() { log "FAILED: $*"; shot /run/failed.png; wineserver -k 2>/dev/null; exit 1; }
shot() { import -window root "$1" 2>/dev/null; }
nativelog() { cat /run/native/logs/*/efz.log 2>/dev/null; }
# Waits up to $1 seconds for the native game's log to have a line matching $2.
waitlog() {
    for _ in $(seq "$1"); do
        nativelog | grep -q -- "$2" && return 0
        kill -0 "$native" 2>/dev/null || return 1
        sleep 1
    done
    return 1
}
focus() { xdotool windowactivate --sync "$1" 2>/dev/null || xdotool windowfocus "$1"; }
# The game: a process whose command starts with its path (wine shows Z:\...\efz.exe).
findgame() {
    for p in /proc/[0-9]*; do
        c=$(tr "\0" " " < "$p/cmdline" 2>/dev/null) || continue
        case ${c%% *} in *efz.exe|*EFZ.EXE) echo "${p#/proc/}"; return ;; esac
    done
}

: > /run/driver.log
RANDOM=$SEED
Xvfb :99 -screen 0 1024x768x24 >/dev/null 2>&1 &
sleep 2
[ -e /wine/.revival-setup ] || { wineboot -i >/dev/null 2>&1; wineserver -w; touch /wine/.revival-setup; }
cd /run/game
# As tools/revival-test.sh: a wine desktop window (the game switches to 640x480), and
# the DDRAW.dll beside the game rather than wine's.
wine explorer /desktop=EFZ,800x600 wineconsole EfzRevival.exe > /run/wine.log 2>&1 &
for _ in $(seq 60); do
    console=$(xdotool search --name "EfzRevival" 2>/dev/null | head -1)
    [ -n "$console" ] && break
    sleep 1
done
[ -n "${console:-}" ] || fail "no launcher console"
sleep 2
log "launcher console up"

native=
start_native() {
    EFZ_NET_LAG=$LAG SDL_VIDEO_DRIVER=offscreen SDL_AUDIO_DRIVER=dummy \
        /native/efz --data "$EFZ_DIR" --save /run/native/save --log-dir /run/native/logs \
        "$@" --name Native --frames "$FRAMES" --keys "$KEYS" > /run/native.out 2>&1 &
    native=$!
}
# The menu reads a key, not a line (readMenu): the digit alone; an Enter after it would
# answer the next question.
if [ "$HOST" = revival ]; then
    focus "$console"
    xdotool type --delay 100 1
    sleep 2
    log "Revival hosts on UDP $PORT"
    start_native --join "127.0.0.1:$PORT"
else
    start_native --host --port "$PORT"
    waitlog 20 "hosting on UDP port" || fail "the native game doesn't host"
    log "the native game hosts on UDP $PORT"
    focus "$console"
    xdotool type --delay 100 2
    sleep 1
    xdotool type --delay 50 "127.0.0.1:$PORT"; xdotool key Return
    log "Revival joins 127.0.0.1:$PORT"
fi
shot /run/hosting.png
waitlog 60 "ping average" || fail "no connection (the native game never measured the ping)"
log "connected: $(nativelog | grep -o 'playing as P[12]\|joined .* as P[12]\|ping average.*' | head -1)"
# Revival asks for the delay once its own measuring is done: Enter takes the one it
# recommends. Asked again until it starts the game (an early Enter waits in the console).
pid=
for _ in $(seq 20); do
    focus "$console"
    xdotool key Return
    sleep 2
    pid=$(findgame)
    [ -n "$pid" ] && break
done
[ -n "$pid" ] || fail "Revival didn't start efz.exe"
for _ in $(seq 30); do
    game=$(xdotool search --name "Eternal Fighter" 2>/dev/null | head -1)
    [ -n "$game" ] && break
    sleep 1
done
[ -n "${game:-}" ] || fail "no game window"
log "efz.exe runs (pid $pid): \"$(xdotool getwindowname "$game")\""
sleep 1
focus "$game"

# Random presses of P1's controls (key.ini: the arrows, X, V, Z; not C, B, which backs
# out of character select), and the match's course from the native game's log.
keys=(Up Down Left Right x v z)
stage=0
start=$SECONDS
while kill -0 "$native" 2>/dev/null; do
    k=${keys[$((RANDOM % ${#keys[@]}))]}
    xdotool keydown "$k"; sleep "0.0$((RANDOM % 9 + 1))"; xdotool keyup "$k"
    sleep "0.0$((RANDOM % 9 + 1))"
    fights=$(nativelog | grep -c "fight at frame")
    case $stage in
    0) if [ "$fights" -ge 1 ]; then stage=1; t=$SECONDS; log "fight 1 starts"; fi ;;
    1) if [ $((SECONDS - t)) -ge "$FIGHT" ]; then
           shot /run/fight.png
           focus "$game"
           xdotool keydown Escape; sleep 0.2; xdotool keyup Escape
           stage=2; log "Esc on Revival's end: both back to character select"
       fi ;;
    2) if [ "$fights" -ge 2 ]; then stage=3; t=$SECONDS; log "fight 2 starts"; fi ;;
    3) if [ $((SECONDS - t)) -ge $((FIGHT / 2)) ]; then
           log "stopping the native game"
           kill -TERM "$native"
           break
       fi ;;
    esac
    if [ $((SECONDS - start)) -ge 600 ]; then
        log "ten minutes: stopping the native game"
        kill -TERM "$native"
        break
    fi
done
for _ in $(seq 20); do kill -0 "$native" 2>/dev/null || break; sleep 1; done
kill -0 "$native" 2>/dev/null && { log "the native game didn't stop: killed"; kill -KILL "$native"; }
wait "$native" 2>/dev/null
log "the native game ended ($?), at stage $stage"
# Revival sees the quit, closes the game and goes back to its menu.
sleep 5
shot /run/end.png
wineserver -k 2>/dev/null
log "done"
