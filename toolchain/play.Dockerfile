# Runs efz.exe for tools/play.sh: the build image's 32-bit wine, plus what a game window
# needs that the compiler doesn't: the X11 extensions wine's display driver loads, sound
# through PulseAudio (or PipeWire's PulseAudio server), a Japanese font for the game's
# message boxes and a Japanese locale, which makes Shift-JIS the ANSI code page.
# Without a sound server, ALSA's default device discards the sound: the game can't run
# without a DirectSound device (it dereferences the missing one).
FROM efz-msvc71

USER root
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
        libxrender1:i386 libxrandr2:i386 libxi6:i386 libxcursor1:i386 libxinerama1:i386 \
        libxcomposite1:i386 libxfixes3:i386 libxxf86vm1:i386 libpulse0:i386 \
        fonts-ipafont-gothic locales \
 && sed -i 's/^# *\(ja_JP.UTF-8\)/\1/' /etc/locale.gen && locale-gen \
 && printf 'pcm.!default { type null }\nctl.!default { type null }\n' > /etc/asound.conf \
 && rm -rf /var/lib/apt/lists/*
USER build
ENV LANG=ja_JP.UTF-8
