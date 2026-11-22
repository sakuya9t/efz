# Code of others in the native game

The native game and its replay tool (`efz`, `efz-convert`; [native.md](native.md)) are
built with six libraries that CMake downloads, pinned by SHA-256, and links into the
programs. Anyone handing the programs on hands this file on with them.

| Library | What for | Licence |
|---|---|---|
| [SDL3](https://libsdl.org) 3.4.18 | The window, input, sound, file dialogs | zlib |
| [libopus](https://opus-codec.org) 1.5.2 | The sound of the videos of fights (`port/mp4.cpp`) | BSD (below) |
| [minih264](https://github.com/lieff/minih264) (`minih264e.h`, commit b0baea7) | The pictures of the videos of fights (`port/minih264.c`) | CC0 1.0: public domain |
| [dr_mp3](https://github.com/mackron/dr_libs) 0.7.4 (`dr_mp3.h`, commit aec2dd2) | EfzRevival's custom music, MP3 (`port/revival/music.cpp`) | Public domain (Unlicense) or MIT-0 |
| [dr_flac](https://github.com/mackron/dr_libs) 0.13.4 (`dr_flac.h`, commit 806ee9a) | The same, FLAC | Public domain (Unlicense) or MIT-0 |
| [stb_vorbis](https://github.com/nothings/stb) 1.25 (`stb_vorbis.c`, commit 033efa1) | The same, Ogg Vorbis | Public domain or MIT |

## libopus

```
Copyright 2001-2023 Xiph.Org, Skype Limited, Octasic,
                    Jean-Marc Valin, Timothy B. Terriberry,
                    CSIRO, Gregory Maxwell, Mark Borgerding,
                    Erik de Castro Lopo, Mozilla, Amazon

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:

- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

- Neither the name of Internet Society, IETF or IETF Trust, nor the
names of specific contributors, may be used to endorse or promote
products derived from this software without specific prior written
permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Opus is subject to the royalty-free patent licenses which are
specified at:

Xiph.Org Foundation:
https://datatracker.ietf.org/ipr/1524/

Microsoft Corporation:
https://datatracker.ietf.org/ipr/1914/

Broadcom Corporation:
https://datatracker.ietf.org/ipr/1526/
```

## SDL3

```
Copyright (C) 1997-2026 Sam Lantinga <slouken@libsdl.org>

This software is provided 'as-is', without any express or implied
warranty.  In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgment in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
```

## minih264

To the extent possible under law, the authors have dedicated all copyright and related
and neighboring rights to this software to the public domain worldwide
([CC0 1.0](http://creativecommons.org/publicdomain/zero/1.0/)).
