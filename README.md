# efz-decomp

A matching decompilation of **Eternal Fighter ZERO 4.02** (`efz.exe`, Twilight Frontier, 2005):
C++ source that the original compiler, Visual C++ .NET 2003, builds back into a byte-identical
`efz.exe` (SHA-256 `3a1616d6…6dd66481`). The recovered source is then the base for a maintained,
modernised version of the game.

**Status:** 19 of ~622 game functions match, covering the first two object files
(`0x401000`–`0x4054af`, plus their init stubs at the end of `.text`):
- `src/main.cpp`: `WinMain`, the window procedure, the frame-timer thread
- `src/effect.cpp`: `CGame::UpdateEffect`, the 14 KB per-frame update for all 640 effect
  slots

## Game files

This repository contains no original game files: no executables, sprites, sounds or music.
EFZ's readme prohibits redistributing its data and decompiling it. Everything here works
against a legitimately obtained EFZ 4.02 install, which `EFZ_DIR` points at.

## Setup

You need Docker, Python 3 with `pefile`, GNU `objdump`, `curl` and `sha1sum`.

```sh
toolchain/setup.sh                 # ~650 MB download, once; builds the efz-msvc71 image
export EFZ_DIR=/path/to/EFZ        # folder containing the original efz.exe
tools/peinfo.py                    # check it is the 4.02 build
make diff                          # compile src/ and compare with the original
```

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
4. **Fix stack-layout differences by renaming.** This compiler orders stack variables by a
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
| `tools/msvc` | Run `cl`, `link` or `lib` in the container |

## Findings so far

See [docs/recon.md](docs/recon.md). In short:

- **Toolchain:** VS .NET 2003 (`cl` 13.10.3077), Standard Edition. It has no optimiser,
  so `/Od /GS` reproduces the code.
- **Size:** about 3.6 MB of game code in 152 translation units.
- **Libraries:** the static CRT plus DirectDraw, DirectInput and DirectSound, using
  DirectX 7-era interfaces through the DirectX 9 SDK.
- **Structure:**
  - about 622 game functions, mostly virtual methods of 23 character classes (13-slot
    vtables)
  - 8 top-level scene objects, driven from `WinMain`

## Roadmap

1. **Reconnaissance:** toolchain, layout and inventory. *Done.*
2. **Toolchain:** VS .NET 2003 under wine in Docker, plus a per-function compare loop.
   *Done:* `src/main.cpp` matches its original object byte for byte.
3. **Function matching**, in this order:
   1. platform layer and file loaders
   2. shared base classes
   3. effects and projectiles
   4. the 23 character classes
4. **Byte-identical exe.** Link with the original CRT and libraries, set the post-link header
   fields (timestamp, RSDS record, Rich header), and check the SHA-256 in CI.
5. **Modern fork.** Starting from the matched source:
   - separate the deterministic 64 FPS simulation from the platform layer
   - replace DirectDraw, DirectInput and DirectSound with SDL3
   - reach parity with EfzRevival: rollback netplay, spectating, replays, training tools
   - add widescreen and HD output, in-game input binding and controller hot-plug
   - add mod support for characters, stages and palettes
6. **UE5.** Host the simulation core as a UE5 C++ module and render it with new assets.
