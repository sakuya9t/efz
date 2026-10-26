# Runs EfzRevival (launcher, injected DLL, DDRAW.dll) with efz.exe on a virtual X
# server, for tools/revival-test.sh: efz-play's wine plus Xvfb, xdotool to answer the
# launcher's console, Mesa for wine's Direct3D 9 (DDRAW.dll renders with it) and
# ImageMagick for screenshots.
FROM efz-play

USER root
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
        xvfb xdotool x11-utils imagemagick procps \
        libgl1:i386 libgl1-mesa-dri:i386 libglx-mesa0:i386 libegl1:i386 \
 && rm -rf /var/lib/apt/lists/*
USER build
