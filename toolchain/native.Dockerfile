# Builds the native (SDL3) game for tools/native.sh: CMake, Ninja, GCC and Clang for
# Linux, MinGW-w64 for Windows, and the development files SDL3 needs to build its X11,
# Wayland, PulseAudio, PipeWire and ALSA back ends (it loads their libraries at run
# time, so the binary runs on any desktop). Bookworm, as the host, so what it builds
# runs on the host.
FROM debian:bookworm

RUN apt-get update \
 && apt-get install -y --no-install-recommends \
        build-essential cmake ninja-build clang lld git ca-certificates curl pkg-config \
        python3 mingw-w64 gdb xvfb xauth \
        libx11-dev libxext-dev libxrandr-dev libxcursor-dev libxi-dev libxss-dev \
        libxfixes-dev libxtst-dev libxkbcommon-dev libwayland-dev wayland-protocols \
        libdecor-0-dev libegl-dev libgl-dev libgles-dev libdrm-dev libgbm-dev \
        libasound2-dev libpulse-dev libpipewire-0.3-dev libudev-dev libdbus-1-dev \
        libibus-1.0-dev \
 && rm -rf /var/lib/apt/lists/*

ARG UID=1000
ARG GID=1000
RUN groupadd -g $GID build && useradd -m -u $UID -g $GID build
USER build
