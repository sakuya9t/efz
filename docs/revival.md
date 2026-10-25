# EfzRevival 1.02h reconnaissance

EfzRevival is the community add-on that every online and most offline EFZ play runs
through: rollback netplay, spectating, replays and the training tools (pause and frame
step, save and load state, record and replay, hit/hurt/collision box display). It hooks
the 4.02 `efz.exe` this repository rebuilds. This document covers its 1.02h release,
the target of a matching decompilation alongside `efz.exe`'s.

Statements are marked **observed** (read from the binaries) or **inferred**.

## The binaries

1.02h (27 May 2022, by Fireseal) ships three binaries, built from one solution in
`C:\Git\efz_2022`. None of it is in this repository; `REVIVAL_DIR` points at a copy
(default `~/.local/share/efz-decomp/revival/1.02h`).

| File | Bytes | SHA-256 | PE timestamp | PDB record |
|---|---|---|---|---|
| `EfzRevival.exe` | 1,007,104 | `e2c8b136a36f829f4178daf96655ee952ffa465776ae204219cafc24b74b488f` | `0x6292935e` | `C:\Git\efz_2022\Release\EfzRevivalLauncher.pdb`, age 12 |
| `EfzRevival.dll` | 707,584 | `0687e74bb40a8aadc91b591284bc962a320078394bdf7d23b9741d54e937f8aa` | `0x62929371` | `C:\Git\efz_2022\Release\EfzRevival.pdb`, age 128 |
| `DDRAW.dll` | 814,080 | `4d83369bd40fca915ba8bbe8b46afabdcd626a0e97c4a1135f97a292db0ca72c` | `0x625c3202` | `C:\Git\efz_2022\Release\DDRAW.pdb`, age 4 |

**Observed:** the launcher and DLL hashes equal the 1.02h identity that the open-source
InGameNetplay mod checks before it attaches to a Revival session
(`include/netplay/bridge/revival_addresses.h` in
[Aquat1c/InGameNetplay](https://github.com/Aquat1c/InGameNetplay)). `DDRAW.dll` is a
month older than the other two (17 April 2022, the first 1.02h build in the changelog)
and was not rebuilt for 1.02h's two follow-up fixes.

## How the pieces fit

- **`EfzRevival.exe`**, the launcher (console). It asks host / join / spectate /
  tournament / local on the console, runs the network side, starts `efz.exe` and
  injects `EfzRevival.dll` (**observed** imports: `CreateProcessA`, `VirtualAllocEx`,
  `WriteProcessMemory`, `CreateRemoteThread`, `ws2_32` UDP sockets, shared memory and
  events). Networking is boost.asio on Winsock (`win_iocp_io_service`,
  `datagram_socket_service<udp>`); packets are protobuf-lite messages
  (`EfzPackets::MessageInit`, `MessageInput`, `MessageSync`, `MessagePing`,
  `MessagePunch`, `MessagePalette`, `MessageChangeRole`, `MessageRedirect`,
  `MessageDone`, `MessageQuit`) driven by a `ProtocolState` state machine
  (`ProtocolStateHostConnect`, `ClientConnect`, `SpecConnect`, `TestDelay`, `Play`,
  `SpecPlay`, `End`) - all from RTTI.
- **`EfzRevival.dll`**, injected into `efz.exe`. Its export `init(int *args)` reads
  `EfzRevival.ini`, checks that the launcher passed version `0x66`, and creates one of
  four session objects by mode (`args[0]`): 0 online (`0x690` bytes), 1 spectator
  (`0x500`), 2 practice (`0x2b0`), 3 tournament (`0x310`). It then patches `efz.exe`
  at `0x401582`, inside `WinMain`'s frame loop, with a 10-byte jump to its frame hook
  (**observed** in `init` at `0x1006f0b0`). Rollback (save/load of the game state),
  input exchange with the launcher, the practice features and replays live here.
- **`DDRAW.dll`**, a DirectDraw proxy that `efz.exe` loads by name instead of the
  system one. It draws the game's 8-bit surfaces with Direct3D 9 (`d3d9`, `d3dx9_43`),
  adds windowed mode and back-buffer scaling, and exports an `EfzRender` class that
  `EfzRevival.dll` uses for its text overlay and its boxes (`addTextRender`,
  `addRectRender`, `renderBox`, `setBoxRender`), plus `getEfzInput`/`getEfzTimer`.
  It also works alone: started without the launcher, `efz.exe` runs as "vanilla" EFZ
  that works on modern Windows.

## Toolchain

**Observed** in the Rich headers (`tools/peinfo.py`), and reproduced by
`toolchain/setup-vs2012.sh` + `tools/msvc11`: Visual C++ 2012 **Update 5**, targeting
`v110_xp`. Update 5 replaced only the C/C++ back and front ends (`c2.dll`, `c1xx.dll`
17.00.**61219**, in `VS11-KB2707250vc.msp`) and kept Update 4's `cl.exe`, `c1.dll` and
`link.exe` (61030); objects take `c2.dll`'s build in their `@comp.id`.

| Tool | Build | DLL | DDRAW | EXE | Reading |
|---|---|---|---|---|---|
| `Utc1700_LTCG_CPP` | 61219 | 22 | 13 | | **The developer's C++, built with `/GL`** (whole-program optimisation, code generated at link time) |
| `Utc1700_CPP` | 61219 | | | 30 | **The launcher's C++, no `/GL`**: its own sources and protobuf-lite compiled from source |
| `Utc1700_CPP` | 61030 | 7 | 1 | 2 | Prebuilt boost 1.56 libraries (filesystem, system, iostreams), built with Update 4 |
| `Utc1700_C` | 61030 | 8 | | 8 | zlib 1.2.8 from the same boost build (boost_zlib; its objects are `adler32`, `crc32`, `deflate`, `inffast`, `inflate`, `inftrees`, `trees`, `zutil` and a few unused ones); the banners `deflate 1.2.8` / `inflate 1.2.8` are in the image |
| `Utc1700_C` / `_CPP` / `Masm1100` | 50929 | 216 / 73 / 32 | 206 / 65 / 27 | 239 / 134 / 37 | Static CRT (`libcmt.lib`, `libcpmt.lib`; all of their objects carry 50929). The launcher's also has the Concurrency Runtime |
| `Implib900` | 30729 | 15 | 11 | 9 | Windows SDK 7.1A import libraries |
| `Implib1100` | 61030 | 2 | | | **Inferred:** `DDRAW.lib`, the import library from building `DDRAW.dll`, whose exports the DLL imports |
| prodid `0x0083` | 30729 | 1 | | | A VS2008 SP1 object from an SDK static library; **inferred**: `strmiids.lib` (the DLL plays custom BGM through DirectShow: `CoCreateInstance`, `AMGetErrorTextW`) |
| `0x00ab` / `0x009c` / `0x007b` | 30319 / 21202 / 50727 | | 1 / 2 / 2 | | DirectX SDK (June 2010) libraries (`d3dx9.lib`, `d3d9.lib`) |
| `Export1100`, `Cvtres1100`, `Linker1100` | 61030 | 1 each | 1 each | (no exports) | Exports, the resources (manifest; the launcher's icon), the link |
| prodid `0x0097` | 0 | | | 1 | Not identified |

A test DLL linked with `/LTCG` by this toolchain gives the same products and builds:
`Utc1700_LTCG_CPP 61219`, `Implib900 30729`, `Export1100`/`Linker1100 61030`.

Build options **observed** so far:
- `/MT`: the CRT is static in all three (1.02a's `DDRAW.dll` still used `MSVCR110.dll`).
- `/GS` (load config has a security cookie) and `/SAFESEH` (SEH handler tables of
  403, 312 and 485 entries).
- C++ exceptions (`/EHsc`): `__CxxFrameHandler3`, catch funclets.
- The launcher's own sources: `/O2 /Ob0 /Oy- /GS /sdl /Gy /EHsc /arch:IA32 /fp:strict
  /MT`. **Observed**:
  - `/Ob0` (`EfzPackets.pb.cc`): nothing is inlined, not even protobuf's accessors or
    `std::string`'s constructor, yet the code is optimised (leaf functions without
    frames, values in registers).
  - `/sdl`: before constructing an object whose class has pointer members, a
    compiler-made `__autoclassinit` zeroes them (with `/Ob0` it is a call).
  - `/arch:IA32`: members are zeroed with integer stores; VS2012's default `/arch:SSE2`
    uses `xorps`/`movq`.
  - `/Oy-`: functions that need a frame build it on `ebp`.
  - `/fp:strict` (`Console::printChar`): with `/fp:precise` the compiler takes
    `(x + step) % width` from the `idiv` that computed `(x + step) / width` before the
    call to `floor`; the original divides again after it. Intrinsics stay on (`/O2`):
    `std::char_traits<char>::length` inlines `strlen`, the messages' `Clear` inlines
    `memset`. **Inferred:** strict floating point for deterministic rollback.
- protobuf, a separate static library: its own project's Release options
  (`/O2 /Oi /Oy- /GS /Gy /EHsc /fp:precise`), changed to `/MT`, with `HAVE_ZLIB`, built
  from its `vsprojects` directory (its `__FILE__` strings are `..\src\google\protobuf\...`).
  **Observed:** this reproduces every protobuf function that can be placed.
- Include paths: the launcher saw protobuf at `C:\Programming\protobuf-2.6.1\src` (the
  `__FILE__` of `repeated_field.h` in a template instantiated in `EfzPackets.pb.cc`);
  `EfzPackets.pb.cc` itself was compiled as a bare file name.
- The link folds identical functions (`/OPT:ICF`): `ArrayInputStream::Next` and
  `ArrayOutputStream::Next` are one function at `0x44dd00`.
- RTTI: the launcher's own classes have type descriptors; `EfzRevival.dll`'s and
  `DDRAW.dll`'s don't (`/GR-` there, **inferred**; the library classes' descriptors come
  from the prebuilt objects).
- Unicode: the ini and file APIs are the `W` ones (`GetPrivateProfileStringW`,
  `CreateFileW`).

## Libraries

- **boost 1.56.0**: static msvc-11.0 libraries (`-mt-s`): system, filesystem,
  iostreams with zlib, date_time (launcher). Header-only parts: asio, function, bind,
  algorithm/string, exception. **Observed** with `tools/libmatch.py`: the official
  `boost_1_56_0-msvc-11.0-32` libraries (built with Update 4, 61030) reproduce 94 of the
  101 functions in the DLL's boost range byte for byte (1.57: 86, 1.55: 64, and 1.55 was
  built with VS2012 RTM). The 7 others are 5-22 byte stubs and one 299-byte function.
  The developer's copies were a separate build all the same: the anonymous-namespace
  names in their RTTI strings differ (`?A0x0812ae90` for boost.system's categories
  against the official `?A0x92439a12`), and MSVC draws those names afresh on every
  compile (**observed**: the same file compiled twice gets two names). All three
  binaries share the developer's `error_code.obj` (same name in each).
- **protobuf 2.6.1**, lite runtime plus `io/gzip_stream.cc` built with `HAVE_ZLIB`;
  launcher only, compiled from source with the launcher's flags. **Observed:** compiled
  with the flags below, its functions reproduce the launcher's byte for byte at their
  addresses (`0x44d7e0`-`0x44eb47` holds the stream classes); 2.6.1 alone reproduces
  `internal::VerifyVersion`, which embeds the version, and 2.5.0 reproduces fewer
  functions (125 against 147).
- **zlib 1.2.8**, through boost_zlib: gzip for replays and logs.
- Direct3D 9 + D3DX 9 (June 2010, `d3dx9_43.dll`) in `DDRAW.dll`; DirectShow in the DLL.

## Code layout

From `tools/ghidra/ExportFunctions.java` over a Ghidra 12.1.4 auto-analysis (which
labels the static CRT with its VS2012 FunctionID database):

```sh
analyzeHeadless ~/tools/efz-ghidra revival-1.02h -import $REVIVAL_DIR/EfzRevival.dll \
    -scriptPath tools/ghidra -postScript ExportFunctions.java build/revival/EfzRevival.dll.functions.json
```

(Ghidra refuses project paths with a component starting with `.`, hence not under
`~/.local`.)

| | Functions | of which FunctionID-named |
|---|---|---|
| `EfzRevival.exe` | 6,740 | 1,384 |
| `EfzRevival.dll` | 5,345 | 865 |
| `DDRAW.dll` | 4,469 | 1,214 |

`EfzRevival.dll`'s `.text` (**observed**):

| Range | What |
|---|---|
| `0x10001000`-`0x1002dca9` | Header code the developer's sources instantiated: STL and boost templates (`std::wstring`, streams, `boost::exception` clones), 16-byte aligned like all compiled-here code |
| `0x1002dca9`-`0x1005ed30` | Static C++ library and CRT, unaligned (FunctionID names nearly all of it), with a few aligned runs among it |
| `0x1005ed30`-`0x10065460` | Aligned, unnamed: **inferred** the prebuilt boost objects |
| `0x10065460`-`0x10065580` | Import thunks (`RtlUnwind`, `IsProcessorFeaturePresent`) and the CRT's `__stricmp` |
| `0x10065580`-`0x1007a250` | The developer's own functions: `DirectDrawCreate` (`0x10065580`), `init` (`0x1006f0b0`), the session classes; then the CRT's `__aullrem` |
| `0x1007a2ec`-`0x10080e3b` | About 1,150 exception-handling funclets (`.text$x`) |

A map from an `/LTCG` link still names each generated function's object, so the
link-time code can be compared function by function after linking.

## How the code is laid out

Three rules decide where a function ends up. Each was tested by linking small test
objects with the toolchain and reading the map, and each holds in the launcher:

1. **The compiler emits an object's functions sorted by decorated name.** With `/Gy`
   every function is a COMDAT section, and Visual C++ 2012 numbers them in name order
   whatever the source order (`aa_free`, `alpha`, `mid`, `zeta`, `zz_free`, `_entry` from a
   file that defines them in another order). The linker keeps an object's section order.
   In the launcher, `MergeFrom` and `MergePartialFromCodedStream` of the ten messages run
   `ChangeRole, Done, Init, Input, Palette, Ping, Punch, Quit, Redirect, Sync`, and
   `gzip_stream.obj`'s functions run `??0GzipInputStream` ... `?Skip@...`.
2. **Of identical functions only the last copy survives** (`/OPT:ICF`), in its own
   place: of `aaa`, `qqq` and `zzz` with the same body, `zzz` is kept, whichever is
   referenced first. Accessors such as `has_x()` that read the same bit of different
   messages fold into one.
3. **An inline function used by several objects is taken from the first object in link
   order** (COMDAT "any" selection); the other copies are discarded.

So a function's position depends on its name, on which other functions share its
body, and on which earlier objects use it. Names that are lost (all of EfzPackets' field
names, for one) are therefore constrained to windows by the original's layout, and an
object's layout can only be checked in full once every object before it in link order
exists. Until then each function is compared on its own (`tools/revdiff.py`), and
`tools/revlayout.py` predicts an object's layout from rules 1 and 2.

## Recovering a launcher object

The launcher is matched object by object, in link order (its objects are linked in
the alphabetical order of their source files, so a recovered file's name has to sort
between its neighbours'). Setup, once the toolchain is in place:

```sh
make revival-names      # probes + recovered objects -> names for the original's code
make revival-decomp     # Ghidra decompilation with those names (needs GHIDRA_HOME)
```

They write `build/revival/EfzRevival.exe.names.json` (decorated name -> address),
`.labels.json` (address -> readable name) and `.c` (the decompilation). To read the
original:

| Command | Shows |
|---|---|
| `tools/revmap.py LO HI` | Every function start with its placed names (or `?`) and string literals |
| `tools/revdc.py LO HI` | Ghidra's decompilation of the functions there |
| `tools/revdis.py LO HI` | Disassembly with call targets, imports and strings labelled |

A source file in `revival/EfzRevivalLauncher/` names the range its object occupies
with `// OBJECT: 0xLO 0xHI` and its functions with `// FUNCTION: 0xADDR` (as in `src/`).
`make revival-check N=<file stem>` compiles it, compares every function in the range
(`V=-v` prints instruction diffs) and lists the original's functions in the range that
neither it nor a probe produces yet; the object is done when that list is empty and
every function matches. The functions that aren't the developer's (template and inline
library code) need no annotation: they are found by their bytes, and they come out
right once the code that uses them does.

What decides the code, from the objects matched so far:
- Each function is compiled on its own (`/Ob0`), so a function's bytes depend only on
  its source, its object's other declarations aside.
- Statement order is kept closely: moving an assignment across a call changes which
  register holds it (`Console::printChar`). Local variable names don't matter.
- A function returning `int`/`BOOL` sets `eax`; one returning `bool` sets `al`.
- An object's functions are laid out sorted by decorated name (case-sensitive), its
  template and inline functions among them, so the developer's lost names are
  constrained by their neighbours'. An inline or template function used by several
  objects is emitted in the first; identical functions are folded into the last copy.
- C inline functions from the CRT headers (`_wmemmove`, `_ldexpf`, `_gmtime`) sort
  after every C++ name, so they close the object that first used them.
- The static initializers are grouped near the end of `.text` (`0x495230`-`0x49604b`,
  listed by the `.CRT$XCU` table at `0x497314`), one run per object in link order:
  boost.bind's placeholders `_1`-`_9`, error-category references and a header's static
  `std::wstring` (`L"h!!!"`) show which objects include which headers.

## The network messages

`revival/EfzRevivalLauncher/EfzPackets.proto` is reconstructed from the launcher (every
generated function compiles to the original's bytes). Package `EfzPackets`, protobuf
2.6.1, `optimize_for = LITE_RUNTIME`; ten messages, declared in this order:

| Message | Fields (number: type, `req`uired / `opt`ional / `rep`eated) | What is known |
|---|---|---|
| `MessageInit` | 1: enum (2 values) req; 2: uint32 req; 3: uint32 req; 4: enum (3 values) req; 5: enum (2) req; 6: uint32 req; 7, 8: bytes opt; 9: bool opt | Connection handshake. Field 3 is the protocol version, sent as `0x66` (the check `init` repeats in the DLL); field 1 selects the full form (all fields, two names) or a short one; 7 and 8 are names (0x80-byte buffers, "None" when absent) |
| `MessageInput` | 1: enum (2) req; 2: int32 opt; 3: uint32 req; 4: uint32 opt; 5: bytes rep; 6: int32 opt | Inputs, several frames per message (field 5) |
| `MessagePing` | 3: uint32 req | A `timeGetTime()` timestamp (fields 1 and 2 were removed at some point) |
| `MessageSync` | 1: enum (2) req; 2: uint32 opt; 3: uint32 opt; 4: bytes rep | Either a data block (field 1 = 0) or a request with two numbers (field 1 = 1) |
| `MessagePalette` | 1: enum (2) req; 2: bytes req | A player's palette |
| `MessageQuit`, `MessageDone` | 1: enum (2) req | |
| `MessageRedirect`, `MessagePunch` | 1: bytes req | A 28-byte socket address (`sockaddr_in6`); **inferred:** redirecting a connection elsewhere, and UDP hole punching |
| `MessageChangeRole` | 1: enum (3 values) req | |

There are six enums: five with values 0-1 and one with values 0-2. Which 2-value enum
each field uses can't be told from the code (their `IsValid` functions are identical).
The launcher sends each message with a type number of its own (Ping 2, Sync 4,
Redirect 7, Punch 10, ...) through one send routine (`0x4407c0`).

## Features (1.02h `EfzRevival.ini`, readme and changelog)

- **Netplay**: rollback (`MaxRollback`, default 4) with adjustable input delay, IPv4
  and IPv6, UDP port 10800, UDP hole punching through a server
  (`HolePunchingServer = 128.199.38.97:10800`), recommended delay from 90% worst ping,
  desync detection, remote palettes, score display, battle log, automatic replay saving.
- **Spectating**: from the start of the match series, with catch-up speed control.
- **Practice** (in VS PLAYER): pause, frame step with a counter, save/load state,
  record/replay with a start condition (now / wakeup / tech) and 5 buffers (random
  playback), switch and mirror players, game speed in 16 FPS steps, input display.
- **Box display**: hitboxes (PageUp), hurtboxes (PageDown), collision boxes (Home);
  hitboxes that already hit are stippled, and collision boxes show the crossup midline.
- **Replays**: an extended `.rep` format; save/load, pause, frame step and speed in any
  replay, and taking control of a character from an extended replay.
- **Tournament mode**: offline, player names and scores, automatic replays, hold Esc to
  quit.
- **Global** (also without the launcher): window position and size, back-buffer size,
  software rendering, BGM mute and a custom music folder.

## Reference material

Open-source mods that hook Revival document its internals across versions (addresses,
session layouts, the practice controller): InGameNetplay, EfzExtendedPractice
(`include/game/efzrevival_addrs.h`, `include/game/practice_offsets.h`),
EfzDisplayManager and Concerto (`efz.py`, which drives the launcher's console). They
give names and offsets to check against, not code to copy: the decomp's source is
written from the binaries.
