#!/bin/bash
# Build the native game (CMakeLists.txt, docs/native.md) in the efz-native docker image,
# which has CMake, the compilers and what SDL3 needs (toolchain/native.Dockerfile).
#   tools/native.sh                 build/native/efz for Linux; runs on the host
#   tools/native.sh windows         build/windows/efz.exe for 64-bit Windows (MinGW-w64)
#   tools/native.sh linux -DEFZ_HOST_X87=ON ...   with CMake options
# then run the tests (ctest) for the Linux build.
#
# With CMake and SDL3's build dependencies on the machine, plain CMake works as well:
#   cmake -B build/native && cmake --build build/native
# SDL3's release tarball is downloaded once into ~/.cache/efz-native.
set -euo pipefail

repo=$(cd "$(dirname "$0")/.." && pwd)
target=${1:-linux}
[ $# -eq 0 ] || shift
case $target in
    linux) dir=build/native; toolchain= ;;
    windows) dir=build/windows; toolchain=-DCMAKE_TOOLCHAIN_FILE=toolchain/mingw-w64.cmake ;;
    *) echo "tools/native.sh: unknown target $target (linux or windows)" >&2; exit 1 ;;
esac

cache=$HOME/.cache/efz-native
sdl=SDL3-3.4.18.tar.gz
mkdir -p "$cache"
[ -f "$cache/$sdl" ] ||
    curl -sSL -o "$cache/$sdl" "https://github.com/libsdl-org/SDL/releases/download/release-3.4.18/$sdl"

docker image inspect efz-native >/dev/null 2>&1 ||
    docker build -q -t efz-native --build-arg UID="$(id -u)" --build-arg GID="$(id -g)" \
        -f "$repo/toolchain/native.Dockerfile" "$repo/toolchain" >/dev/null

docker run --rm -u "$(id -u):$(id -g)" -v "$repo:/work" -v "$cache:/cache" -w /work efz-native \
    bash -c "cmake -S . -B $dir -G Ninja -Wno-dev -DEFZ_SDL3_ARCHIVE=/cache/$sdl $toolchain $* >/dev/null &&
             cmake --build $dir &&
             if [ $target = linux ]; then ctest --test-dir $dir --output-on-failure; fi"
echo "built $dir"
