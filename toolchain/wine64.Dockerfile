# Runs the native game's Windows build (build/windows/efz.exe, 64-bit) under wine for
# tools/compat.py --windows: efz-revival-test's wine with its 64-bit half.
FROM efz-revival-test

USER root
RUN apt-get update \
 && apt-get install -y --no-install-recommends wine64 \
 && rm -rf /var/lib/apt/lists/*
USER build
