# efz-decomp

A matching decompilation of **Eternal Fighter ZERO 4.02** (`efz.exe`, Twilight Frontier, 2005):
C++ source that the original compiler, Visual C++ .NET 2003, builds back into a byte-identical
`efz.exe` (SHA-256 `3a1616d6…6dd66481`). The recovered source is then the base for a maintained,
modernised version of the game.

**Status: `make check` rebuilds a byte-identical `efz.exe`.** All 630 game functions
(`0x401000`–`0x77697e`) are recovered: the platform layer, the `CPlayer` base class,
all 24 character classes, the animated stage backgrounds and the eight scenes. Linked
with the static CRT, the original's import libraries and its icon, they give a file
whose SHA-256 is the original's. Only the timestamp, the PDB's GUID and one count in the
Rich header are set after linking (`tools/postlink.py`). `tools/progress.py` prints the
per-function numbers.

The source reads fields through named members rather than the lifter's raw offsets
(`unk2af8[4] = -0x1d` for `*(short*)((char*)this + 0x2b00) = -0x1d`, `(*m_opponent)->x`),
and still builds the identical exe. [docs/readability.md](docs/readability.md) records
how, and which readability changes keep the compiled code: renaming members and methods
does; renaming locals doesn't, since this compiler orders stack slots by their names.

| Source | What it is |
|---|---|
| `src/main.cpp` | `WinMain`, the window procedure, the 64 FPS frame timer |
| `src/effect.cpp` | `CGame::UpdateEffect`, the per-frame update of the 640 effect slots |
| `src/file.cpp` | `CFile`, the file wrapper the loaders use |
| `src/config.cpp` | `key.ini`, per-character `.rec` records, the replay stream |
| `src/game.cpp` | `CGame`: effects, sound effects and music, screen shake, palette flashes |
| `src/graphics.cpp` | `CGraphics`: DirectDraw setup, `.dat`/`.bmp` sprite loaders, software blitters (inline assembly), palettes, screenshots |
| `src/input.cpp` | `CInput`: DirectInput keyboard and joysticks, key bindings |
| `src/sound.cpp` | `CSound`: DirectSound buffers, `.wav` loading, music loop points |
| `src/player.cpp` | `CPlayer`, the base of the character classes: movement, guard and damage, the `.pal`/`.dat`/`.pat`/`.wav` loaders, round reset |
| `src/playerobj.cpp` | `CPlayer`'s table of 64 spawned objects (projectiles and the like) |
| `src/<character>.cpp` | One character class each (`shiori.cpp`, `sayuri.cpp`, ...) |
| `src/<character>_vf6.cpp` | Each character's per-state update, `UpdatePattern`, a file of its own as in the original |
| `src/bg01.cpp` | `CAnimBg`, the animated stage backgrounds' base, and stage 01's background |
| `src/bg10.cpp`, `bg12.cpp`, `bg16.cpp` | The other three animated backgrounds |
| `src/scene0.cpp` ... `scene8.cpp` | The scenes `WinMain` runs: 0 title, 1 character select, 2 match setup, 3 the fight, 5 results, 6 config, 7 staff roll, 8 replays |
| `src/scene3_draw.cpp` | The drawing helpers of scene 3, the fight |
| `src/efz.rc` | The icon resource (the icon itself is taken from the original at build time) |

## Game files

This repository contains no original game files: no executables, sprites, sounds or music.
EFZ's readme prohibits redistributing its data and decompiling it. Everything here works
against a legitimately obtained EFZ 4.02 install, which `EFZ_DIR` points at.

## Setup

You need Docker, Python 3 with `pefile`, GNU `objdump`, `iconv`, `curl` and `sha1sum`.

```sh
toolchain/setup.sh                 # ~1 GB download, once; builds the efz-msvc71 image
export EFZ_DIR=/path/to/EFZ        # folder containing the original efz.exe
tools/peinfo.py                    # check it is the 4.02 build
make diff                          # compile src/ and compare with the original
make check                         # link build/efz.exe and compare it with the original
```

`make check` ends with `cmp` finding no difference and the original's SHA-256. The
build takes the icon from `$EFZ_DIR/efz.exe` and sets three things after linking that
no build can reproduce: the link timestamp, the GUID the linker gives the PDB, and the
Rich header's count of objects from the Standard Edition compiler (the original's 152
against the source's 71; the other 81 left nothing in the file).

`toolchain/setup.sh` fetches Microsoft's own installers from archive.org, pinned by SHA-1:
- **Visual C++ Toolkit 2003 1.01**, the free release of the exact compiler build
- **Windows Server 2003 SP1 Platform SDK**, for headers
- **Platform SDK, February 2003**: the `gdi32`, `winmm` and `user32` import libraries
  and `rc.exe` of the release Visual Studio .NET 2003 shipped. Its `user32.lib` differs
  from the one efz.exe was linked with, so `toolchain/user32lib.py` derives a stand-in
  with the original's import hints.
- **DirectX SDK (August 2005)**
- **.NET Framework 1.1**, for `cvtres.exe` 7.10.3052, which converted the original's
  resources

It unpacks them in the container into `~/tools/efz-toolchain`. `cl.exe` runs under wine in
that container; `tools/msvc <tool> <args>` runs any of the tools.

## Playing

`make play` (or `tools/play.sh`) runs `build/efz.exe` under wine in a window on the X
display in `$DISPLAY`. From a terminal in your desktop session that is already set; over
ssh, name the session's display, e.g. `DISPLAY=:10 make play` for an xrdp desktop.
`tools/play.sh --original` runs `$EFZ_DIR/efz.exe` instead.

- **Where it runs.** Wine from the host if it is installed, otherwise the `efz-play`
  docker image (`toolchain/play.Dockerfile`, built on first use from the toolchain's
  image), which gets the display's socket and cookie, and the session's PulseAudio or
  PipeWire socket for sound.
- **What it writes.** The game runs in `~/.local/share/efz-decomp/game` (`EFZ_PLAY`
  moves it), which links to the data in `$EFZ_DIR` and holds real copies of what the game
  writes: `key.ini`, the `.rec` records, replays and screenshots; the container also
  mounts `$EFZ_DIR` read-only. The wine prefix is in `~/.local/share/efz-decomp/wine`.
- **The window.** The game switches the screen to 640×480 (or 320×240) fullscreen; it
  runs inside a 640×480 wine desktop window, so only that window changes.
  `EFZ_DESKTOP=off` lets it change the real screen mode instead.
- **Sound.** The game can't run without a DirectSound device: it shows "DirectSound
  オブジェクトが生成できません" and crashes after it. Without a sound server, the image's
  ALSA device discards the sound so the game still runs.
- **Controls.** The keyboard, as bound in `key.ini`. Joysticks aren't passed into the
  container.

## Matching workflow

1. **Annotate.** Put `// FUNCTION: 0xADDR` above the function or its declaration, and
   `// GLOBAL: 0xADDR` above globals. Method declarations inside a class body are picked up
   too.
2. **Write the C++** in `src/`. Pseudocode from Ghidra or REA is a starting point.
3. **Compare.** Run `make diff` (or `make diff F=Name` for one function).
   `tools/funcdiff.py` lays the compiled function over the original and checks every byte
   and every relocation:
   - calls and globals must hit the annotated addresses
   - imports must hit the right IAT slot
   - string literals must have identical contents

   It prints an instruction diff of whatever differs, plus the addresses of symbols that
   aren't annotated yet (`learned:`).
4. **Or lift a whole object.** `tools/lift.py` turns this compiler's unoptimised x86
   back into C++ that compiles to the same bytes. Describe the object in
   `tools/objdefs.py` (address range, class, names), then run
   `tools/objcheck.sh <obj>`: it regenerates `src/<obj>.cpp` (keeping its leading comment,
   `#include`s and the globals right after them), updates the declarations in
   `src/efz.h`, compiles and diffs.
   Whatever still differs points at a lifter rule to add. `tools/lifttest.py` relifts
   every matched function to check that the lifter doesn't regress. The lifter writes
   fields as raw offsets and predates the names in `src/`: after regenerating an
   object, `tools/members.py rewrite src/<obj>.cpp` turns its accesses into members
   again, and its methods need renaming back.
5. **Fix stack-layout differences by renaming.** This compiler orders stack variables by a
   hash of their names, not by declaration order. If only `[ebp-N]` offsets differ:
   - list each local's slot in the original, top of the frame first
   - run `tools/stackorder.py solve` with a few candidate names per local; one probe
     compile ranks all candidates
   - use the names and declaration order it prints

## Tools

| Tool | Purpose |
|---|---|
| `tools/peinfo.py` | Build identity, Rich header (toolchain), PDB record, sections, imports |
| `tools/inventory.py` | Function, vtable and region inventory, used to size and split the work |
| `tools/compid.py` | `@comp.id` build stamps in `.lib`/`.obj` files, to match the SDKs |
| `tools/funcdiff.py` | Per-function byte and relocation comparison |
| `tools/stackorder.py` | Picks local names that reproduce the original stack layout (`--globals`: `.bss` layout) |
| `tools/progress.py` | Matched functions and bytes, and where the matched prefix of `.text` ends |
| `tools/lift.py` | Lifts a function (`body 0xADDR`) or an object (`write <obj>`) to C++ |
| `tools/members.py` | Rewrites raw offset accesses into `efz.h`'s members, renames members and methods, checks `efz.h`'s layout ([docs/readability.md](docs/readability.md)) |
| `tools/objdefs.py` | Object ranges, class names and signatures for the lifter |
| `tools/objcheck.sh` | Regenerate, compile and diff objects |
| `tools/batch.sh` | `objcheck.sh` over many objects, one summary line each |
| `tools/regfix.py` | Find dead code the compiler dropped from where register choice diverges |
| `tools/undefined.py` | C++ symbols some object uses and none defines (would break the link) |
| `tools/lifttest.py` | Relift the matched functions and check they still match |
| `tools/objorder.py` | Function order in `.obj` files as the linker will lay them out |
| `tools/msvc` | Run `cl`, `link`, `lib` or `rc` in the container |
| `tools/stdstamp.py` | Stamps objects as the Standard Edition compiler's, as in the original's Rich header |
| `tools/icon.py` | Writes the original's icon as an `.ico` for `src/efz.rc` |
| `tools/postlink.py` | Sets the timestamp, PDB GUID and Rich header count after linking |
| `tools/play.sh` | Plays the built (or original) `efz.exe` under wine on an X display |
| `tools/msvc11` | Run Visual C++ 2012 tools (EfzRevival's toolchain) in the container |
| `tools/libmatch.py` | Finds the functions of prebuilt `.lib`/`.obj` files in a binary, relocations masked |
| `tools/rtti.py` | Lists an MSVC binary's vtables, with their classes, through its RTTI |
| `tools/revdiff.py` | Per-function comparison for EfzRevival, addresses from annotations or unique byte matches |
| `tools/revlayout.py` | Predicts where an object's functions land (name order, identical-function folding) |
| `tools/revorder.py` | Pairs a rebuilt launcher's functions with the original's and writes the link order file |
| `tools/revpostlink.py` | Sets the launcher's timestamp, PDB GUID and age, Rich counts and `.reloc` size after linking |
| `tools/ghidra/ExportFunctions.java` | Ghidra headless script: every function's entry, extent, name source and callees as JSON |

## EfzRevival

The second target is EfzRevival 1.02h, the add-on that provides EFZ's rollback netplay,
spectating, replays and training tools (frame step, save states, hit/hurt/collision
boxes): `EfzRevival.exe` (the launcher and network side), `EfzRevival.dll` (injected
into `efz.exe`: rollback, practice features, replays) and its `DDRAW.dll` (a Direct3D 9
renderer). It is being decompiled the same way, to source that rebuilds its binaries
byte for byte. Its binaries aren't in the repository either; `REVIVAL_DIR` points at a
copy of the 1.02h files (default `~/.local/share/efz-decomp/revival/1.02h`).

```sh
toolchain/setup-vs2012.sh          # ~3.5 GB download, once; after toolchain/setup.sh
```

lays out Visual C++ 2012 with Update 5's compiler, the Windows SDK 7.1A, the DirectX SDK
(June 2010), boost 1.56, protobuf 2.6.1 and zlib 1.2.8, which is what the binaries'
Rich headers and code show; `tools/msvc11` runs it.

```sh
make revival-diff                  # compare the launcher's functions with $REVIVAL_DIR's
make revival-dll-diff              # link EfzRevival.dll (/LTCG) and compare its functions
make revival-ddraw-diff            # the same for DDRAW.dll
make revival-launcher              # link EfzRevival.exe
EFZ_DIR=... tools/revival-test.sh --revival DIR   # run binaries from DIR with efz.exe
EFZ_DIR=... tools/play.sh --revival  # play the rebuilt Revival on your X display
```

The comparisons use a Ghidra export of the originals for function boundaries
(`GHIDRA_HOME`, made once). **All three binaries' code is recovered** and links:

| Binary | Source | Functions matching |
|---|---|---|
| `EfzRevival.exe` | `revival/EfzRevivalLauncher/`: config, console menu, game launch and injection, UDP network, the protocol state machine, shared memory with the DLL, the network messages (`EfzPackets.proto`) | 3342 of 3365 |
| `EfzRevival.dll` | `revival/EfzRevival/`: hooks into `efz.exe`, the box display, save states, rollback (`OnlineSession`), practice (pause, frame step, record/replay), spectating, replays, tournaments, music | 413 of 416 |
| `DDRAW.dll` | `revival/DDRAW/`: DirectDraw on Direct3D 9, the text overlay and box renderer | 221 of 221 |

The rebuilt binaries inject into the rebuilt `efz.exe` and run like the originals
(`tools/revival-test.sh`). `DDRAW.dll` rebuilds byte for byte (`make revival-ddraw-check`).
The other two can't be made identical: which of several identical functions and data
the linker keeps is decided by an unstable sort over everything it loaded, including the
original's unused code that the link dropped, and the outcome behaves like a hash of all
of it. `EfzRevival.exe` has the original's size, sections, data and static initializers;
`EfzRevival.dll` its imports, static initializers and string order, with 413 of 416
functions matching. Apart from those three functions and a few orderings, what differs is
the copies the linker keeps and what follows from where they sit. See [docs/revival.md](docs/revival.md) for the binaries, the toolchain, the
rules that decide the code layout, the protocol, rollback and the practice tools.

## Findings so far

See [docs/recon.md](docs/recon.md). In short:

- **Toolchain:** VS .NET 2003 (`cl` 13.10.3077), Standard Edition. It has no optimiser,
  so `/Od /GS` reproduces the code.
- **Size:** about 3.6 MB of game code in 71 objects. The Rich header counts 152 objects
  built by this compiler; the other 81 left nothing in the file.
- **Libraries:** the static CRT plus DirectDraw, DirectInput and DirectSound, using
  DirectX 7-era interfaces through the DirectX 9 SDK.
- **Structure:**
  - 630 game functions, mostly virtual methods of 24 character classes that derive from
    `CPlayer` (13-slot vtables)
  - 8 top-level scene objects, driven from `WinMain`

## Roadmap

1. **Reconnaissance:** toolchain, layout and inventory. *Done.*
2. **Toolchain:** VS .NET 2003 under wine in Docker, plus a per-function compare loop.
   *Done:* `src/main.cpp` matches its original object byte for byte.
3. **Function matching**, in this order:
   1. platform layer and file loaders. *Done:* `0x401000`–`0x40e62f`, 8 objects.
   2. shared base classes. *Done:* `CPlayer`, `0x40e630`–`0x4136cf`, 2 objects.
   3. effects and projectiles. *Done:* `CGame::UpdateEffect` and `CPlayer`'s object table.
   4. the 24 character classes. *Done.*
   5. the scenes and menus (`0x750d30`–`0x77697e`). *Done.*
4. **Byte-identical exe.** *Done:* `make check`. Still to do: run it in CI (that needs
   a legitimately obtained `efz.exe` on the runner).
5. **Modern fork.** Starting from the matched source:
   - separate the deterministic 64 FPS simulation from the platform layer
   - replace DirectDraw, DirectInput and DirectSound with SDL3
   - reach parity with EfzRevival: rollback netplay, spectating, replays, training tools
   - add widescreen and HD output, in-game input binding and controller hot-plug
   - add mod support for characters, stages and palettes
6. **UE5.** Host the simulation core as a UE5 C++ module and render it with new assets.

EfzRevival 1.02h, alongside:

1. **Reconnaissance:** binaries, toolchain, libraries, layout. *Done:*
   [docs/revival.md](docs/revival.md).
2. **Toolchain:** Visual C++ 2012 Update 5 for `v110_xp`, boost 1.56. *Done:* a test
   link reproduces the Rich header's products and builds.
3. **Function matching:** the launcher first (no `/GL`, so objects compare one by one),
   then `EfzRevival.dll` and `DDRAW.dll` (`/GL`: compared after linking). *Done:* all
   code recovered; 3342/3365, 413/416 and 221/221 functions match; the rebuilt binaries
   inject and run like the originals.
4. **Byte-identical binaries.** *Done* for `DDRAW.dll`. `EfzRevival.exe`: as far as
   its sources go (see "The launcher, byte for byte" in [docs/revival.md](docs/revival.md)).
   `EfzRevival.dll`: as far as its sources go, with three functions whose compiled form
   wasn't reproduced (see "The whole image").
