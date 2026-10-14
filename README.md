# efz-decomp

A matching decompilation of **Eternal Fighter ZERO 4.02** (`efz.exe`, Twilight Frontier, 2005):
C++ source that the original compiler, Visual C++ .NET 2003, builds back into a byte-identical
`efz.exe` (SHA-256 `3a1616d6…6dd66481`). The recovered source is then the base for a maintained,
modernised version of the game.

**Status: all game code matches.** Every game function from `0x401000` to `0x77697e`
builds byte for byte: the platform layer, the `CPlayer` base class, all 24 character
classes, the animated stage backgrounds and the eight scenes. That is all 630 game
functions; the only bytes in between are the compiler's `int3` padding. Next is linking
them, with the static CRT and the DirectX import libraries, into a byte-identical
`efz.exe`. `tools/progress.py` prints the current numbers.

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
| `src/bg01.cpp` | `CAnimBg`, the animated stage backgrounds' base, and stage 01's background |
| `src/bg10.cpp`, `bg12.cpp`, `bg16.cpp` | The other three animated backgrounds |
| `src/scene0.cpp` ... `scene8.cpp` | The scenes `WinMain` runs: 0 title, 1 character select, 2 match setup, 3 the fight, 5 results, 6 config, 7 staff roll, 8 replays |

## Game files

This repository contains no original game files: no executables, sprites, sounds or music.
EFZ's readme prohibits redistributing its data and decompiling it. Everything here works
against a legitimately obtained EFZ 4.02 install, which `EFZ_DIR` points at.

## Setup

You need Docker, Python 3 with `pefile`, GNU `objdump`, `iconv`, `curl` and `sha1sum`.

```sh
toolchain/setup.sh                 # ~650 MB download, once; builds the efz-msvc71 image
export EFZ_DIR=/path/to/EFZ        # folder containing the original efz.exe
tools/peinfo.py                    # check it is the 4.02 build
make diff                          # compile src/ and compare with the original
make link                          # link build/efz.exe from the recovered code
```

`make link` puts every game function at its original address. The rest of the file is
not byte-identical yet: the statically linked CRT, the data sections, the resources and
the header still differ.

`toolchain/setup.sh` fetches Microsoft's own installers from archive.org, pinned by SHA-1:
- **Visual C++ Toolkit 2003 1.01**, the free release of the exact compiler build
- **Windows Server 2003 SP1 Platform SDK**
- **DirectX SDK (August 2005)**

It unpacks them in the container into `~/tools/efz-toolchain`. `cl.exe` runs under wine in
that container; `tools/msvc <tool> <args>` runs any of the tools.

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
   `tools/objcheck.sh <obj>`: it regenerates `src/<obj>.cpp` (keeping its leading comment
   and `#include`s), updates the declarations in `src/efz.h`, compiles and diffs.
   Whatever still differs points at a lifter rule to add. `tools/lifttest.py` relifts
   every matched function to check that the lifter doesn't regress.
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
| `tools/stackorder.py` | Picks local names that reproduce the original stack layout |
| `tools/progress.py` | Matched functions and bytes, and where the matched prefix of `.text` ends |
| `tools/lift.py` | Lifts a function (`body 0xADDR`) or an object (`write <obj>`) to C++ |
| `tools/objdefs.py` | Object ranges, class names and signatures for the lifter |
| `tools/objcheck.sh` | Regenerate, compile and diff objects |
| `tools/batch.sh` | `objcheck.sh` over many objects, one summary line each |
| `tools/regfix.py` | Find dead code the compiler dropped from where register choice diverges |
| `tools/undefined.py` | C++ symbols some object uses and none defines (would break the link) |
| `tools/lifttest.py` | Relift the matched functions and check they still match |
| `tools/objorder.py` | Function order in `.obj` files as the linker will lay them out |
| `tools/msvc` | Run `cl`, `link` or `lib` in the container |

## Findings so far

See [docs/recon.md](docs/recon.md). In short:

- **Toolchain:** VS .NET 2003 (`cl` 13.10.3077), Standard Edition. It has no optimiser,
  so `/Od /GS` reproduces the code.
- **Size:** about 3.6 MB of game code in 46 objects. The Rich header counts 152 objects
  built by this compiler; what the other 106 hold isn't known yet.
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
4. **Byte-identical exe.** Link with the original CRT and libraries, set the post-link header
   fields (timestamp, RSDS record, Rich header), and check the SHA-256 in CI.
5. **Modern fork.** Starting from the matched source:
   - separate the deterministic 64 FPS simulation from the platform layer
   - replace DirectDraw, DirectInput and DirectSound with SDL3
   - reach parity with EfzRevival: rollback netplay, spectating, replays, training tools
   - add widescreen and HD output, in-game input binding and controller hot-plug
   - add mod support for characters, stages and palettes
6. **UE5.** Host the simulation core as a UE5 C++ module and render it with new assets.
