# The native game

The recovered sources build two ways. The Makefile compiles them with Visual C++ .NET
2003 into the original `efz.exe`, byte for byte. CMake (`CMakeLists.txt`) compiles the
same sources with a current compiler into a 64-bit game for Windows, macOS and Linux,
with SDL3 in place of Win32, DirectDraw, DirectInput and DirectSound. No wine or emulator
is involved.

The native game must play the same game as the original. The test is the one in
[compat.md](compat.md): a replay played in both gives the same status for both players
on every tick. This document describes what the native build changes, and why each
change keeps that true.

## Building and playing

On each system one script builds the game, as far as anything changed, and starts it:

```sh
tools/run.sh --data "$EFZ_DIR"     # Linux, macOS: build/run/efz (in efz.app on macOS)
tools\run.cmd --data C:\EFZ        # Windows: build\run\RelWithDebInfo\efz.exe
```

They build with CMake in `build/run`, of the build type the replay test checks
(RelWithDebInfo, CMakeLists.txt's default). They find CMake where the usual installers
put it (on Windows, Visual Studio's own as well), and when the machine lacks something
they say what and how to install it. On Linux without the compiler and the libraries'
development files, `tools/run.sh` builds in docker with `tools/native.sh` instead
(`EFZ_BUILD=host` or `docker` chooses). `--build-only` only builds; other options go to
the game. CI builds with these scripts and checks that they start the game.

```sh
tools/native.sh                    # build/native/efz for Linux, in the efz-native image
tools/native.sh windows            # build/windows/efz.exe for 64-bit Windows (MinGW-w64)
build/native/efz --data "$EFZ_DIR"
```

`tools/native.sh` builds in docker (`toolchain/native.Dockerfile`) and runs the tests.
With CMake and a compiler on the machine, plain CMake works on all three systems:

```sh
cmake -B build/native
cmake --build build/native --config RelWithDebInfo
ctest --test-dir build/native -C RelWithDebInfo
```

CMake downloads SDL3 3.4.18, pinned by SHA-256, and links it statically.
`-DEFZ_SYSTEM_SDL3=ON` uses an installed SDL3 instead. On Linux, SDL3's build needs the
development files of the desktop's libraries (X11, Wayland, ALSA, PulseAudio; see
`.github/workflows/native.yml`); it loads the libraries themselves at run time, so the
binary runs on any desktop. CI builds and tests Linux (x64, arm64), Windows (MSVC) and
macOS (arm64, x64).

- **The game's files.** `--data DIR` is a folder with the original game's data (its
  `system` folder and the rest); without it the game looks in `$EFZ_DATA`, the current
  folder, its own folder and, for a macOS app, the folder holding the app. Names are
  matched regardless of case, so a copy from a Windows disk works on Linux.
- **What it writes.** `key.ini`, the per-character records, replays and screenshots go
  to `--save DIR`: by default the data folder, or the user's preferences folder
  (`SDL_GetPrefPath`) if that can't be written. Files there are read first.
- **The window.** 640×480, resizable; the game's 320×240 or 640×480 picture is scaled
  to fit with its aspect kept, pixels sharp. Alt+Enter or F11 toggles full screen.
- **Controls.** `key.ini`'s bindings, as before: keys by position (DirectInput codes,
  with a Japanese layout's own), and up to two game controllers, plugged in at any
  time, as DirectInput's two joysticks (left stick or d-pad, buttons in XInput order).
- **Sound.** Mixed in software on SDL's audio thread. The music loops at its loop
  points exactly, where the original checked once per frame.

For tests the game runs without a display (`SDL_VIDEO_DRIVER=offscreen
SDL_AUDIO_DRIVER=dummy`) and takes `--frames N`, `--fast`, `--keys SCRIPT` and
`--dump DIR` (see `port/main.cpp`).

## One source

The native build compiles every file of `src/` except the four Windows-only ones
(`main.cpp`, `graphics.cpp`, `input.cpp`, `sound.cpp`), which `port/` replaces. Where
the two builds need different code, `src/efz.h` has macros that expand to exactly the
original's casts under the old compiler (so `make check` still gives the original's
bytes) and to something else under `EFZ_NATIVE`. `#ifdef EFZ_NATIVE` appears in two
places only (below).

## Memory: the original's layout, 32-bit pointers

The game's structures hold pointers in 4 bytes, and its code keeps pointers in `int`s
too: it adds offsets to them (`x8 = (int)p1->m_patterns[i].frames + frame * 0xc8`),
casts them back, and copies whole structures. A 64-bit build cannot store its pointers
in 4 bytes. It keeps the layout and stores **handles** instead (`port/guest.h`):

- Everything the game allocates comes from one arena (`port/arena.cpp`): 2 GB of address
  space reserved at startup and used from the bottom up. A handle is an offset into it;
  handle 0 is NULL. The allocator is deterministic and zeroes what it hands out.
- The game also passes the addresses of locals around as integers (the fight's
  collision checks do), so the main thread's stack has handles too, from `0xf0000000`.
- A pointer member in `src/efz.h` is a `PTR32(T)`: 4 bytes holding a handle, used like a
  `T*` (`m_opponent`, `(*m_opponent)->x`, `m_game->m_music`). It casts as a pointer
  does: to another pointer type (to a base class with the adjustment) and to an
  integer, which gives the handle.
- Each cast between an integer and a pointer in the code is a macro, `TOPTR(T*, v)` or
  `TOINT(T, p)`, and the one load of a pointer from raw memory is `PTRAT(addr)`.
  `tools/portify.py` writes them: it compiles each file for 64 bits with g++, reads the
  diagnostics, and runs again on new code from `tools/lift.py`.
- `port/layout.cpp` checks the sizes and offsets of the structures on every compiler.
  The scenes and the animated backgrounds, whose members follow a vtable pointer
  directly, are 4 bytes further on (8-byte vtable pointer); their code only reaches
  them by name.

Handles cost an add and a compare per access, which a 2005 game at 64 frames a second
doesn't notice.

## Floating point: the original's x87

The original computes on the x87 with the precision control at 53 bits (the CRT's
default), and its compiler without optimisation keeps each expression on the x87
stack. That gives the same results as SSE2 or ARM doubles with three exceptions, all
measured against the original's code:

| The original | The native build |
|---|---|
| A float is loaded onto the x87 stack: arithmetic on floats is done in double and rounded to float only when stored (`25.0f * f + 3 * f`) | `F32` (`port/x87.h`): stored as a float, computes as a double. `*(F32*)` in place of `*(float*)` in `src/` |
| A cast to float inside an expression is dropped: the compiler stores a rounded copy it never reads (`fst` to an unused temporary) | `F32CAST(x)`: a double |
| `sin`, `cos`, `atan2` run `fsin`, `fcos`, `fpatan` and leave a 64-bit-significand result on the stack; `cos(a) * speed` rounds the product of that to 53 bits | `X87Value`: the result as an x87 register; `*`, `+`, `-`, `/` and comparisons with a double are exact on integers, rounded once (`port/x87.cpp`) |

`port/x87.cpp` computes sine, cosine and arctangent in double-double arithmetic and
rounds them to 64 bits. Measured on this machine:

- the emulated results are correctly rounded on all of 105,762 inputs (against mpmath
  at 200 bits);
- the exact operations match a real x87 at 53-bit precision on 2 million random cases
  of multiply, add, subtract, divide (both ways), round and compare;
- `tests/x87_test.cpp` checks 525 of these values on every platform (`ctest`, CI).

The original's own results are not that consistent. This AMD Ryzen 9 7945HX's `fsin`
and `fcos` are off by a few units in the 64th bit on 34% of those inputs (and by up
to 10⁵ next to multiples of π), which changes the double result of `cos(a) * speed`
0.11% of the time. Intel's microcode differs again. So the original's fights already
differ between CPUs in rare cases (a velocity one unit in the last place apart), and
no single implementation matches every original. The native build gives the correctly
rounded result everywhere, so it agrees with itself on every platform.
`-DEFZ_HOST_X87=ON` (GCC or Clang on x86) takes the three functions from the machine's
own x87 instead: the original's results on this machine exactly, for the replay test.

The build also turns off what a current compiler would do differently: no fused
multiply-add (`-ffp-contract=off`, `/fp:contract-`), no fast math.

## The rest of the original's behaviour

- **Evaluation order.** The original evaluates a call's arguments right to left. Two
  calls take two random draws as arguments (`ObjBase::SetVelocity` in `CShiori` and
  `CNayukiB`); `#ifdef EFZ_NATIVE` there draws them in the original's
  order. No other call or operator has two arguments whose order matters (checked by
  scanning for calls with side effects in two arguments).
- **`rand`.** The static CRT's (`port/x87.cpp`): the same sequence from the same seed.
- **Integers and characters.** Signed overflow wraps (`-fwrapv`) and `char` is signed
  (`-fsigned-char`), as with the original's compiler. The code still reads some
  members through casts of other types (`*(int*)&unk134 = 0` on a float), so
  `-fno-strict-aliasing`.
- **Uninitialised memory.** GCC finds no local read before it is written. Fields of
  heap objects can be: the arena zeroes every block, where the original's heap leaves
  what was there, different on every run. The replay test sees two: the combo damage
  (`m_comboDamage`) until a combo starts, which nothing reads, and the hits an attack
  can still land (`m_hitsLeft`), which decides whether some attacks connect before the
  player's first attack sets it. The original goes either way on those from run to
  run; the native game, with zero there, always the same one
  ([compat.md](compat.md)).

## The platform layer (`port/`)

| File | What it does |
|---|---|
| `efz_native.h` | What `efz.h` includes instead of `<windows.h>` and DirectX: Win32 types at their Win32 sizes (handles are 32-bit numbers), the few Win32 functions the game code calls, the DirectX interfaces it touches |
| `guest.h`, `arena.cpp` | Handles, the arena, `operator new` |
| `x87.h`, `x87.cpp` | `F32`, `X87Value`, the emulated `sin`, `cos`, `atan2`, `rand` |
| `graphics.cpp` | `CGraphics`: 8-bit surfaces, the loaders and blitters of `src/graphics.cpp` (its assembly loops as C++, DirectDraw's checks on lock rectangles kept), the palette, presenting through an SDL texture |
| `input.cpp` | `CInput`: the keyboard state by DirectInput code, controllers as joysticks; `GetInput` and the `key.ini` loaders as the original |
| `sound.cpp` | `CSound`: the 150 sound slots, a mixer on SDL's audio thread, `.wav` parsing, the music's loop points |
| `win32.cpp` | `CreateFile` and the rest over the C library (case-insensitive names, the save folder), `MessageBox`, `timeGetTime` |
| `main.cpp`, `sdlmain.cpp` | What `WinMain` did, in the same order, then the scenes at 64 frames a second |
| `layout.cpp` | The structure checks |

## The compatibility test

`src/trace.cpp` is a harness built into both games: `make trace` builds
`build/trace/efz.exe`, efz.exe's code with the harness's hooks (in `CScene3::Update`,
`CInput::GetInput` and the main loop; every other function is the original's), and the
native game always has it. Environment variables make it record a replay with scripted
random input, play one without going through the menus, or play a fight of the game's
CPU from a seed, and log the whole game state, hashed, after every tick of the fight.
`tools/compat.py` plays the suite of [compat.md](compat.md) in a build and compares
each log with the original's (the `compat-reference` tag's build, under wine):

```sh
tools/native.sh && tools/compat.py check   # the native game
tools/compat.py check --windows            # the Windows build, under 64-bit wine
tools/compat.py check --native build/native-x87/efz   # another native build
```

Results (31 October 2026; the suite compares every byte of the state since then):

| The native game | Cases | Ticks | Play as the original does |
|---|---|---|---|
| Linux x64, GCC (the default: emulated `sin`, `cos`, `atan2`) | 254 | 1,223,436 | all |

Before 31 October the test compared only the players' status (action, frame, position,
velocity, HP, combo, gauge) on 154 replays:

| The native game | Replays | Ticks | Play as the original does |
|---|---|---|---|
| Linux x64, GCC | 154 | 816,930 | all |
| Linux x64, `-DEFZ_HOST_X87=ON` | 154 | 816,930 | all |
| Windows x64, MinGW-w64, under wine64 | 154 | 816,930 | all |

The replays are matches of random characters, stages and input, about three and a half
hours of fighting: 94 the original recorded (seeds 7 and 100, 5000 and 6000 ticks; two
by hand), 20 more it recorded after the port moved to the readable source (seed 500,
3000 ticks), and 40 the native game recorded (seeds 300 and 600), which the original
plays back. Comparing the whole state found two differences the status had hidden, both
in effects: `fabs` of a float rounds its argument (effect `0x2f`; the native game now
does too, `FABSF`), and a throw's hit spark is placed from stack memory the original
never set (zeroed in both now, [compat.md](compat.md)).

"As the original does" needs a qualification: on 5 of the 154 the original itself
plays differently from run to run, an attack connecting in some runs and not in others
(uninitialised memory, below). On those 5 the native game plays exactly as one of the
original's runs, tick for tick, every time. On the other 149 every run of the original,
its recording and the native game agree on every tick. The three builds write the same
trace for every replay, byte for byte (the Windows build's lines end in CR LF). Since
31 October the reference zeroes memory from `new` as the native game does, so each case
has one outcome, and every build writes its log with `\n` line ends.

Before the source was readable, the port was made on the lifter's raw offsets, and
measured the same way (92 of the replays). Two steps of that work show what the
replay test catches:

| That earlier port | Replays | Ticks | Agree |
|---|---|---|---|
| With the C library's `sin` and `cos` | 80 | 480,480 | 77: in the other 3, Kano's velocity in moves that set it from an angle (actions `0xd5`-`0xd7`) parts by one unit in the last place |
| Without `F32` | 12 | 60,084 | 2: the others part where float arithmetic rounded to float |

## Known differences

- **Trig on other CPUs**, above.
- **Throws' hit sparks** are placed from stack memory the original never set; the
  native game zeroes it ([compat.md](compat.md)).
- **Palette fades** show on the next frame drawn; DirectDraw changed the screen's
  palette at once.
- **No display mode changes.** The game picture is scaled into the window instead.
