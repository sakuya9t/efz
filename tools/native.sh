#!/bin/bash
# Build the native game (CMakeLists.txt, docs/native.md) in the efz-native docker image,
# which has CMake, the compilers and what SDL3 needs (toolchain/native.Dockerfile).
#   tools/native.sh                 build/native/efz for Linux; runs on the host
#   tools/native.sh windows         build/windows/efz.exe for 64-bit Windows (MinGW-w64)
#   tools/native.sh coverage        build/coverage/efz, instrumented for gcov
#   tools/native.sh linux -DEFZ_HOST_X87=ON ...   with CMake options
# then run the tests (ctest) for the Linux build.
#
# DOCKER is the docker command (default docker; "sudo docker" where the user isn't in the
# docker group), EFZ_CTEST_ARGS more arguments for ctest ("--label-exclude headless": not
# the headless library's, whose Python tests need numpy, which the image hasn't).
#
# With CMake and SDL3's build dependencies on the machine, plain CMake works as well:
#   cmake -B build/native && cmake --build build/native
# SDL3's release tarball, libopus's and minih264's encoder header (the videos, port/mp4.cpp)
# and the music's decoders (port/revival/music.cpp) are downloaded once into
# ~/.cache/efz-native.
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
target=${1:-linux}
[ $# -eq 0 ] || shift
case $target in
    linux) dir=build/native; toolchain= ;;
    windows) dir=build/windows; toolchain=-DCMAKE_TOOLCHAIN_FILE=toolchain/mingw-w64.cmake ;;
    coverage) dir=build/coverage; toolchain=-DEFZ_COVERAGE=ON ;;
    *) echo "tools/native.sh: unknown target $target (linux, windows or coverage)" >&2; exit 1 ;;
esac

cache=$HOME/.cache/efz-native
sdl=SDL3-3.4.18.tar.gz
mkdir -p "$cache"
[ -f "$cache/$sdl" ] ||
    curl -sSL -o "$cache/$sdl" "https://github.com/libsdl-org/SDL/releases/download/release-3.4.18/$sdl"
opus=opus-1.5.2.tar.gz
[ -f "$cache/$opus" ] || curl -sSL -o "$cache/$opus" "https://downloads.xiph.org/releases/opus/$opus"
minih264=minih264e-b0baea7a.h
[ -f "$cache/$minih264" ] ||
    curl -sSL -o "$cache/$minih264" \
        "https://raw.githubusercontent.com/lieff/minih264/b0baea7a80ef9d12da97301dd1099b8791b5ba43/minih264e.h"

# The custom music's decoders (CMakeLists.txt's EFZ_DRMP3_HEADER and the others).
drmp3=dr_mp3-aec2dd20.h
[ -f "$cache/$drmp3" ] ||
    curl -sSL -o "$cache/$drmp3" \
        "https://raw.githubusercontent.com/mackron/dr_libs/aec2dd20667f54acfdb66031217df6d240f56c52/dr_mp3.h"
drflac=dr_flac-806ee9ad.h
[ -f "$cache/$drflac" ] ||
    curl -sSL -o "$cache/$drflac" \
        "https://raw.githubusercontent.com/mackron/dr_libs/806ee9ada8ca9827b22f76827f739c290f37ba48/dr_flac.h"
stbvorbis=stb_vorbis-033efa1b.c
[ -f "$cache/$stbvorbis" ] ||
    curl -sSL -o "$cache/$stbvorbis" \
        "https://raw.githubusercontent.com/nothings/stb/033efa1bcb750136ac98e997d53833b758e0089b/stb_vorbis.c"

docker=${DOCKER:-docker}
$docker image inspect efz-native >/dev/null 2>&1 ||
    $docker build -q -t efz-native --build-arg UID="$(id -u)" --build-arg GID="$(id -g)" \
        -f "$repo/toolchain/native.Dockerfile" "$repo/toolchain" >/dev/null

$docker run --rm -u "$(id -u):$(id -g)" -v "$repo:/work" -v "$cache:/cache" -w /work efz-native \
    bash -c "cmake -S . -B $dir -G Ninja -Wno-dev -DEFZ_SDL3_ARCHIVE=/cache/$sdl \
                   -DEFZ_OPUS_ARCHIVE=/cache/$opus -DEFZ_MINIH264_HEADER=/cache/$minih264 \
                   -DEFZ_DRMP3_HEADER=/cache/$drmp3 -DEFZ_DRFLAC_HEADER=/cache/$drflac \
                   -DEFZ_STBVORBIS_SOURCE=/cache/$stbvorbis \
                   $toolchain $* >/dev/null &&
             cmake --build $dir &&
             if [ $target = linux ]; then ctest --test-dir $dir --output-on-failure ${EFZ_CTEST_ARGS:-}; fi"
echo "built $dir"
