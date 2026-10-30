#!/bin/bash
# Build the native game from this checkout and start it, on Linux or macOS (on Windows,
# tools\run.cmd):
#   tools/run.sh --data /path/to/EFZ   the game, built first if anything changed
#   tools/run.sh --build-only          only build
# Every other option goes to the game (port/main.cpp): --save DIR, --fullscreen...
# --data is the folder of an EFZ 4.02 install, the one with the system folder. Without
# it the game's data is $EFZ_DATA, $EFZ_DIR or the current folder.
#
# The build is CMakeLists.txt's in build/run, of the build type the replay test checks
# (RelWithDebInfo); the first one downloads SDL3 and takes a few minutes. It needs CMake
# 3.16 or later and a C++17 compiler. On macOS: the Xcode command line tools
# (xcode-select --install) and CMake (brew install cmake, or CMake.app). On Linux also
# the development files SDL3 builds its X11 and sound back ends from (the apt-get line
# below). A Linux machine without them builds in docker if it has docker
# (tools/native.sh, into build/native), to run on the machine itself. EFZ_BUILD=host or
# EFZ_BUILD=docker chooses.
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
die() { echo "tools/run.sh: $*" >&2; exit 1; }

os=$(uname -s)
case $os in
    Linux|Darwin) ;;
    *) die "for Linux and macOS; on Windows, run tools\\run.cmd" ;;
esac

# As in .github/workflows/native.yml and toolchain/native.Dockerfile.
apt_packages='cmake ninja-build g++ libx11-dev libxext-dev libxrandr-dev libxcursor-dev
    libxi-dev libxss-dev libxfixes-dev libxtst-dev libxkbcommon-dev libwayland-dev
    wayland-protocols libdecor-0-dev libegl-dev libgl-dev libgles-dev libdrm-dev
    libgbm-dev libasound2-dev libpulse-dev libpipewire-0.3-dev libudev-dev libdbus-1-dev
    libibus-1.0-dev'

build_only=
data=
args=()
for a in "$@"; do
    case $a in
        --build-only) build_only=1 ;;
        *) [ "$a" != --data ] || data=1; args+=("$a") ;;
    esac
done
# Checked before building, which can take minutes. The game checks the folder itself.
if [ -z "$build_only" ] && [ -z "$data" ] && [ -z "${EFZ_DATA:-}" ]; then
    if [ -n "${EFZ_DIR:-}" ]; then
        args+=(--data "$EFZ_DIR")
    elif [ ! -d system ]; then
        die 'where is the game? Pass --data DIR, the folder of an EFZ 4.02 install
(with its system folder), or set EFZ_DIR to it'
    fi
fi

cmake_ok() {
    local v
    v=$("$1" --version 2>/dev/null |
        sed -n 's/^cmake version \([0-9][0-9]*\)\.\([0-9][0-9]*\).*/\1 \2/p')
    [ -n "$v" ] || return 1
    set -- $v
    [ "$1" -gt 3 ] || { [ "$1" -eq 3 ] && [ "$2" -ge 16 ]; }
}
# Also where macOS installs it without putting it on the PATH.
cmake=
for c in "$(command -v cmake || true)" /Applications/CMake.app/Contents/bin/cmake \
         /opt/homebrew/bin/cmake /usr/local/bin/cmake; do
    if [ -n "$c" ] && [ -x "$c" ] && cmake_ok "$c"; then
        cmake=$c
        break
    fi
done
cxx=
for c in "${CXX:-}" c++ g++ clang++; do
    if [ -n "$c" ] && command -v "$c" >/dev/null; then
        cxx=$c
        break
    fi
done
has_header() { printf '#include <%s>\n' "$1" | "$cxx" -x c++ -E - >/dev/null 2>&1; }

# What this machine lacks to build the game itself.
missing=
[ -n "$cmake" ] || missing="$missing, CMake 3.16 or later"
if [ "$os" = Darwin ]; then
    # Without them, c++ is only a stub that offers to install them.
    xcode-select -p >/dev/null 2>&1 || missing="$missing, the Xcode command line tools"
elif [ -z "$cxx" ]; then
    missing="$missing, a C++ compiler"
else
    { has_header X11/Xlib.h && has_header X11/extensions/Xext.h; } || has_header wayland-client.h ||
        missing="$missing, X11's development files"
    has_header alsa/asoundlib.h || has_header pulse/pulseaudio.h ||
        missing="$missing, ALSA's or PulseAudio's development files"
fi
missing=${missing#, }

how=${EFZ_BUILD:-}
case $how in
    '') how=host
        if [ -n "$missing" ] && [ "$os" = Linux ] && command -v docker >/dev/null; then
            echo "tools/run.sh: building in docker, as this machine has no $missing" >&2
            how=docker
        fi ;;
    host) ;;
    docker) [ "$os" = Linux ] || die 'docker builds the Linux game only' ;;
    *) die "EFZ_BUILD is host or docker, not $how" ;;
esac

if [ "$how" = docker ]; then
    "$repo/tools/native.sh" linux
    exe=$repo/build/native/efz
else
    if [ -n "$missing" ]; then
        if [ "$os" = Darwin ]; then
            hint='xcode-select --install; brew install cmake'
        else
            hint="sudo apt-get install $(echo $apt_packages)
(Debian and Ubuntu; elsewhere, the same libraries' development packages)"
        fi
        die "to build the game, this machine needs $missing:
$hint"
    fi
    build=$repo/build/run
    if [ ! -f "$build/CMakeCache.txt" ] || { [ ! -f "$build/build.ninja" ] && [ ! -f "$build/Makefile" ]; }; then
        gen=()
        ! command -v ninja >/dev/null || gen=(-G Ninja)
        "$cmake" -S "$repo" -B "$build" ${gen[@]+"${gen[@]}"} -Wno-dev
    fi
    "$cmake" --build "$build" --config RelWithDebInfo --parallel "$(getconf _NPROCESSORS_ONLN 2>/dev/null || echo 4)"
    exe=$build/efz
    [ ! -x "$build/efz.app/Contents/MacOS/efz" ] || exe=$build/efz.app/Contents/MacOS/efz
fi

[ -x "$exe" ] || die "the build made no $exe"
if [ -n "$build_only" ]; then
    echo "built ${exe#"$repo"/}"
    exit 0
fi
exec "$exe" ${args[@]+"${args[@]}"}
