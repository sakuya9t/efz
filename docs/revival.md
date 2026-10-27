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
  - A precompiled header, `stdafx.h` with `<boost/asio.hpp>`: every source, the
    generated `EfzPackets.pb.cc` included, is compiled with it (`/Yu`, forced in with
    `/FI` here), `stdafx.cpp` makes it (`/Yc`) and `stdafx.obj` is linked after the
    other objects. **Observed** in the static initializers: only the last object
    (`0x495c40`-`0x495cc0`) has asio's error categories, `winsock_init` and
    placeholders, and the others only the header statics their code uses (see "The
    launcher, byte for byte").
  - Debug information (the original was linked `/DEBUG`): `/Z7` and `/Zi` give the same
    image, and both change which copy of identical functions the link keeps.
- `EfzRevival.dll`, linked with `/LTCG`: `/O2 /Ob0 /Oy- /GS- /GL /Gy- /GF- /GR- /MT /EHsc
  /arch:SSE /D _USING_V110_SDK71_` (as the Makefile has them), with the template's
  precompiled header (`/Yu"stdafx.h"`). **Observed** (test links compared with `tools/revltcg.py`):
  - `/Gy-` (no function-level linking): the developer's functions are not COMDATs, so
    the linker places them after everything else, just after the import thunks the
    CRT pulls in (`RtlUnwind`, `IsProcessorFeaturePresent`), as in the original
    (`0x10065580`-`0x1007a250`). Functions defined in headers (templates, members
    defined in class bodies) are COMDATs and come first (`0x10001000`-`0x1002dca9`).
  - `/Ob0`: `init` calls `std::wstring`'s constructor and destructor out of line.
  - `/GF-`: identical literals are separate (46 duplicates, "wtf" twice in a row).
  - x87 floating point (`/arch:SSE`: `cmov`, no SSE2); `DDRAW.dll` uses SSE2.
  - Link-time code generation keeps `this`-call member functions' stack arguments
    (`ret N`) but passes a free function's in registers, and it knows which registers
    a non-COMDAT callee preserves, which it can't assume for a COMDAT. So whether a
    function is a member, and whether it is defined in a header, shows in its callers.
  - Precompiled header: every source includes the Visual Studio template's `stdafx.h`
    (`targetver.h`, `WIN32_LEAN_AND_MEAN`, `windows.h`) first and is compiled with it
    (`/Yu`; `stdafx.cpp` makes it, `/Yc`, and `stdafx.obj` is linked last). It decides
    where link-time code generation puts the functions of another object (see "How
    link-time code generation orders functions" below).
  - `EfzRender` (DDRAW.dll's renderer) is declared `class __declspec(dllexport)` in a
    header both DLLs include: `EfzRevival.dll` calls DDRAW.dll through its import
    table (link-time code generation turns the thunk calls into `call [IAT]`) and
    also emits and exports the implicit `EfzRender::operator=`.
  - Exports: `DirectDrawCreate=_DirectDrawCreate@12` in both `.def` files (in
    EfzRevival.dll it names DDRAW.dll's import thunk), so DDRAW.dll exports both
    spellings and its import library imports `_DirectDrawCreate@12` by name.
- `DDRAW.dll`, linked with `/LTCG`: `/O2 /Ob0 /Oy- /GS- /GL /Gy /GF /MT /EHsc`, SSE2 (the
  default), and linked without `/OPT:REF` or `/OPT:ICF` (unreferenced functions and
  identical copies are all in it) and with `DxErr.lib`. **Observed:** a test build reproduces `EfzRender::isFullscreen`,
  `isActiveWindow`, `setBoxRender`, `setRenderText`, `getEfzRender` and `CDDRAW`'s
  constructor (the Visual Studio DLL template's sample class). Unlike EfzRevival.dll it
  links function by function (`/Gy`), so its own code is among the COMDATs at the
  start (`0x10001000`-`0x10020080`), not after the CRT. It also compiles `Config.cpp`
  (the ini and key tables) and the hook trampolines that EfzRevival.dll has.
  `make revival-ddraw-diff` builds `revival/DDRAW/*.cpp` and compares.
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
2. **Of identical functions one copy survives** (`/OPT:ICF`), in its own place.
   Accessors such as `has_x()` that read the same bit of different messages fold into
   one. Which copy is not a rule of names or order: read from `link.exe` (its public
   symbols are on Microsoft's symbol server; `IMAGE::ICFAnalysis`, `ICFComparePcon`),
   the candidates of each section are sorted with the CRT's `qsort` by checksum, size,
   relocation count and a few flags, and the first of each run of identical ones is
   kept. Identical functions compare equal, and `qsort` isn't stable, so the
   survivor depends on every candidate in the link, dead code included (a dead object
   linked after the others changed 33 of 60 test pairs) and on `/Z7`. Only with
   `/VERBOSE` (which fills in the names the sort compares last) is the alphabetically
   first kept. The launcher's link pins the original's choices with an order file
   (see "The launcher, byte for byte").
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

## The launcher, byte for byte

`make revival-launcher-check` links, post-processes (`tools/revpostlink.py`) and compares
`EfzRevival.exe` with the original; it doesn't pass yet. Where it stands:
- Same size, sections, header and resources. `.data` is the original's size and its
  initialized part is laid out the same; the 172 static initializers (`.CRT$XCU`) are
  the original's, object for object; `.rdata` is the original's size.
- `.text` is the original's size. Every launcher function compiles to the original's
  instructions (`make revival-diff`; the few DIFFs left are template copies the checker
  maps to another identical copy). Of the original's 3,708 functions in
  `0x401000`-`0x44eb47`, 3,633 pair with one of the build's and 3,407 sit at their
  address with their instructions; the rest are the `0x30` bytes of `time.inl`'s static
  `gmtime`/`localtime_s`/`time` (below), and call targets and data addresses that follow
  from what is still out of place. The CRT after it (`0x44eae5` on) is loaded in the
  original's order but for three ConcRT objects, and is not in place: of identical CRT
  functions the link keeps other copies (below).

What the image showed about the sources (**observed**, each confirmed by a test build):
- **The precompiled header.** A header static of `stdafx.h` (asio's categories,
  `winsock_init`, placeholders) is in `stdafx.obj` and in an object compiled with the
  header only when that object's code uses it, before the object's own statics.
  Template statics a precompiled header instantiated (`_Error_objects::_Iostream_object`,
  locale ids, `call_stack<>::top_`, service ids) come first too. So the order of an
  object's static initializers says which header statics its code uses and in which
  order it includes `Version.h` (`REVIVAL_SUFFIX`) and `boost/bind.hpp` (`_1`-`_9`):
  `ProtocolContext.h` includes bind before `Version.h`, `EfzRevivalLauncher.cpp`
  includes `Version.h` and then `ProtocolContext.h` (its inline `Timer` and `Log` code
  defines the deadline timer service's id and `codecvt`'s).
- **Unused code.** An unused (static or inline) function isn't compiled, but the
  statics and literals it uses are created where it stands. `Config.obj` defines
  `iostream_category`'s object and four locale ids and has `L"None"` and `L"Name"` as its
  first literals though nothing in it prints a number: `Config.cpp` had such code before
  its functions (a stand-in is in the source).
- **`g_characterSizes`**, a table of the characters' `CPlayer` sizes, is in the
  initialized data of every object that includes `Version.h` (twelve copies; the DLLs
  have it too). `Characters.h` defines it.
- **String literals** (`/GF`: a COMDAT each) are numbered as the compiler first meets
  them, so an object's literals come in the order of its source text: the headers', then
  the functions' in the order of their definitions, then the templates'. That gives the
  order of the definitions of every function that uses a literal (the protocol states,
  `ProtocolContext`, `Network`, `GameProcess`; `SharedData.h` before `Log.h`).
- **Exception data** (`.xdata$x`) comes in the order the compiler generated the
  functions: the order their symbols were created (a class's members in declaration
  order, a template when first instantiated), not their definitions. It constrains the
  headers' declarations and include order (to do).
- **Static locals** in `.bss` come in the order of their functions' definitions
  (`ProtocolContext::send`'s before `checkSync`'s).
- **Names kept by address.** The compiler keeps a scope's names in a table keyed by where
  they lie in its memory, so names declared one after the other come out in their order
  but starting anywhere: `EfzPackets.pb.obj` lays out the ten `default_instance_`
  pointers in message order from `MessageRedirect` with `stdafx.h` holding asio alone,
  from `MessagePalette` (the original's) with `stdio.h` and `tchar.h` (the console
  template's lines) after it. Before asio they would change the order in which every
  object refers to the CRT.
- **Libraries.** The link resolves a library's members in the order of its list of
  undefined symbols (`LIB::Search`): the objects' symbols in link order, each object's in
  the order the compiler created them (declaration order, so include order), then the
  entry point, then each loaded member's at the end. So `ProtocolContext.h` includes
  `<thread>` before `Log.h` (whose boost.iostreams brings `<fstream>`): the thread
  objects come before `fiopen.obj`, and `abort.obj` before `fopen.obj`. `tolower.obj`
  comes right after `stdafx.obj`'s `signal` and before the entry point, so an object
  linked after `stdafx.obj` referred to `tolower` (`Unused.cpp`, a stand-in: nothing of
  it is in the image); `_wctype.obj` follows from it. Three ConcRT objects
  (`ScheduleGroupBase`, `VirtualProcessor`, `VirtualProcessorRoot`) are still loaded
  later than in the original: what loads them are other CRT objects' references, the
  same in both, so the difference lies in what the original's unused code pulled in
  (the Rich header counts one CRT object more). The original also has 4 bytes more
  `.bss` after `generated_message_util`'s (not `stringprintf.obj`, whose `vsnprintf`
  would load `vsnprint.obj` earlier) and Network.obj 4 bytes after `REVIVAL_SUFFIX`
  that nothing reads (a file static of the source lands after asio's placeholders).

Fixed after the link (`tools/revpostlink.py`), as nothing in the sources can give them:
the timestamp, the PDB's GUID and age (12), the Rich header's counts (30 objects from the
launcher's compiler, 134 C++ objects of the CRT, 202 imported functions: what the
unused code pulled in), boost.system's anonymous-namespace name (as for the DLL), and
the size reserved for `.reloc`. `link.exe` reserves
`2 x DIR32 relocations + 10 x pages` before it drops unreferenced code
(`IMAGE::CalculatePtrs`, counted by `CountRelocsInSection`), and pads the rest with
zeros: the original's inputs had 65,626 such relocations, about 43,000 more than the
build's, all in code no longer in the image.

**The order file.** Which of several identical functions the link keeps depends on
every function in it (rule 2 of "How the code is laid out"), so the original's unused
code decided it. `revival/EfzRevivalLauncher/EfzRevival.order` (`/ORDER`) lists the
build's functions in the original's order, every function of a group of identical ones
at the group's place; `make revival-launcher-order` remakes it with `tools/revorder.py`,
which pairs the original's functions with a link without it (instruction text with
addresses masked: an alignment, unique text, then the targets of address operands
through the pairs found). Static functions can't be ordered (an order file names only
public symbols), and unnamed functions go after all named ones: `time.inl`'s `gmtime`,
`localtime_s` and `time`, which `ProtocolContext.obj` has out of line after its own
functions (`0x444520`), so the order covers only the launcher's objects, protobuf
(`0x44a710` on, whose `gzip_stream.cc` has a static function too) keeps the link's
order, which is the original's, and the three end up before protobuf, `0x30` bytes
from their place. Exception funclets (`.text$x`) can't be ordered either (they are
local symbols), and identical read-only data is folded the same way and can't be
ordered either (`/ORDER` takes functions only): of the identical virtual base tables
`e0 ff ff ff 08 00 00 00` of the boost exception wrappers, the original keeps
`Config.obj`'s (`0x497898`), the build `ProtocolContext.obj`'s. Nor can the CRT be
ordered: some of its objects aren't COMDATs (`memchr.obj` and the other assembler ones;
`/ORDER` warns LNK4065), and those would go after every ordered function. So of
identical CRT functions, too, the link's choice stands, and it is another than the
original's from the CRT's third object on: the original keeps `xthrow.obj`'s deleting
destructor of `bad_function_call`, `length_error` and `invalid_argument` (`0x44ec39`),
the build `Exceptions.obj`'s, and everything after it moves. Where folded functions,
funclets and data go is the link's choice; matching it needs the original's link
inputs, unused code included (the comparison sorts every candidate with the CRT's
unstable `qsort` and keeps the first of each run).

Making the order file again after the sources change (`make revival-launcher-order`)
takes two links: one without it, and one with the order that link suggests, because
naming identical functions changes which of them the link folds.

## Recovering EfzRevival.dll

The DLL's code is generated at link time (`/GL`), so it is checked after linking. Its
sources are `revival/EfzRevival/*.cpp`, annotated like the launcher's (`// FUNCTION:
0xADDR`; no `// OBJECT:` line, see below). DDRAW.dll's interface (`EfzRender`) is in
`revival/DDRAW/EfzRender.h`; until DDRAW.dll is rebuilt, its import library comes from
`revival/DDRAW/stub/`.

```sh
make revival-dll-diff                          # link build/revival/dll/EfzRevival.dll, compare all
make revival-dll-check S=a.cpp,b.cpp OUT=dir   # compile a.cpp and b.cpp, link every object
                                               # there is into dir, report their functions
```

`V=-v` adds instruction diffs, `F=name` filters. `tools/revltcg.py` compares each
annotated function with the original instruction by instruction, mapping address
operands through the link map; missing functions are left unresolved
(`/FORCE:UNRESOLVED`), so a function can only match once what it calls exists. A
`static` function with copies in several objects (`Utility.h`'s `to_utf8`, `time.h`'s
`_time`) has one name for all of them: an annotation names the first copy, and calls to
the others are matched by address, learned like an unannotated function's.

What differs from the launcher (all observed in test links):
- **Layout.** The developer's functions follow the CRT (`0x10065580`-`0x1007a250`), one
  object after another in link order (alphabetical file names: `Config.cpp`,
  `dllmain.cpp`, ..., `EfzRevival.cpp` with `init`, ...). Within an object they come in
  the reverse of the order in which their symbols were created, which is mostly the
  reverse of their definitions (next section). Functions defined in headers (class
  bodies, templates) are COMDATs at the start (`0x10001000`-`0x1002dca9`), shared by
  all objects.
- **Calling conventions.** Link-time code generation passes a free function's first
  two arguments in `ecx`/`edx` when it sees every caller; member functions keep
  `thiscall` with their stack arguments (`ret N`), even when they don't use `this`
  (the caller then doesn't load `ecx`). A function whose address is taken (hook
  targets, vtable slots) keeps the standard convention. So the shape of a call shows
  whether the callee is a member, and `ret N` with an unused `ecx` means a member that
  doesn't touch its object.
- **Register knowledge.** A caller knows which registers a non-COMDAT callee
  preserves and keeps values in them across the call; it can't assume that for a
  COMDAT (a function defined in a header). `Palettes::makePalette` (`0x1006d820`) only
  matches with `PaletteId`'s constructor defined in its class body.
- **Branches.** `return palette <= 5;` compiles to `sbb`; the original's `setbe`
  comes from `if (palette > 5) return false; return true;`.
- **Strings.** Not pooled (`/GF-`): each use of a literal is its own copy. **Observed**
  in the link maps: the literals get their names at link time (`$SG` and a counter
  that counts down across the whole link), object after object, and come out in that
  order; within an object mostly in the order of the source, headers included
  (`atlbase.h`'s where `Music.h` is included; unused functions' too). MSVC evaluates a
  call's arguments right to left, so `stream << "a" << x << "b"` with the standard
  library's `operator<<` (not a member) uses `"b"` first; `Log`'s `operator<<` is a
  member and goes left to right. Not understood: in the original, `MusicPlayer::play`'s
  literal comes before `Playlist::load`'s, though `play` is defined after it (its
  address says so: defined first, `play` moves above all of `Music.cpp`'s functions);
  the rebuild has them in source order. The literals' `$SG` numbers are `c2.dll`'s
  "function assigned IDs" (`namestring2`), and `CompareSymOrderInternal` sorts a
  literal that has an owning function by its owner and then that ID. In some objects neighbouring
  literals come out pairwise swapped (the original's ATL strings in
  `PracticeSession.cpp` and `ReplaySession.cpp`, the rebuilt tournament session's first
  ones); the pattern changes with the counts before them (**inferred**: the order of a
  hash table walk), so it can only match once every literal before it exists. One- and
  two-byte literals (`""`, `"\n"`) are placed in the gaps the others' alignment leaves,
  anywhere in the section. One-byte objects in `.bss` (`std::ignore`, boost.bind's
  `_1`-`_9`) are placed the same way: in the original the first object's nine
  placeholders are scattered over `0x100a063a`-`0x100a0642`, the next object's partly
  in gaps; the rebuild has them in order (not reproduced).
- **Unused code.** The linker drops functions nothing calls, but not their literals: an
  object's strings show code the original had and never called. **Observed** in the
  original, with no reference to them: `"Save too large"` (between `Config.cpp`'s and
  `EfzGame.cpp`'s strings), `"Error, stream wrong size"` first and `"Size: "`, `" id "`,
  `" custom "` last in `EfzPalettes.cpp`'s, `"Time "` last in `EfzRevival.cpp`'s,
  `"Comparing "`, `" with "`, `"0x"`, `" Old "`, `" New "` (all of `GameState.cpp`'s),
  three more `"Trampoline malloc failed"` between `Hook.cpp`'s three, and
  `L"None"`, `L"Name"`, `L"Parameters"` with four `":"` at the start of `Config.cpp`'s,
  `OnlineSession.cpp`'s and `TournamentSession.cpp`'s. The sources have unused
  functions that give these strings (marked "Unused"); what the code was is a guess.
- **Game addresses.** The DLL patches and reads `efz.exe` at fixed addresses; `src/`
  (the game's own decompilation) names them: `0x40d131` is inside `CInput::GetInput`,
  `0x7b1290` is `g_fkeyHeld`, `0x7b0960` is inside `g_graphics`, and so on
  (`grep -rn '0x7b0960' src/` or the annotations in `src/efz.h`).

### The whole image

`make revival-dll-check-image` links the DLL, sets what no build reproduces
(`tools/revdllpostlink.py`: the timestamp, the PDB's GUID and age 128, the Rich
header's count of imported functions, the reserved size of `.reloc`, and the names of
boost's anonymous namespaces in the type descriptors, `?A0x0812ae90` and
`?A0x71bbbf5e`, which the compiler drew when the developer's boost libraries were
built) and compares the result with the original byte for byte (`tools/pecmp.py`). What the image showed about
the build (**observed** unless marked):
- **Link:** `/DEBUG` with the PDB at `C:\Git\efz_2022\Release\EfzRevival.pdb` (the
  debug directory has a CodeView and a VC feature record), the manifest embedded (the
  `.rsrc` section, identical), `/OPT:REF /OPT:ICF` (`/OPT:NOREF` would keep all of
  boost.filesystem), and `v110_xp`'s subsystem version 5.01 (the OS and subsystem
  versions in the optional header). The libraries are the project's (`winmm`, `psapi`, `DDRAW`,
  `quartz`, `strmiids`) then Visual Studio's defaults, with `ws2_32` from asio's
  `#pragma comment`: that gives the import directory's order (WINMM, PSAPI, DDRAW,
  QUARTZ, KERNEL32, USER32, ole32, WS2_32) and the Rich header's.
- **No RTTI** (`/GR-`): the only type descriptors are those exceptions need.
- **Objects:** 22 compiled with `/GL` (Rich header), one more C++ object than the 21
  recovered in the VC feature record. The static initializers (`.CRT$XCU`) show which
  headers each object includes: fifteen copies of `Version.h`'s `REVIVAL_SUFFIX` (every
  object that includes `EfzGame.h`, so it includes `Version.h` first), boost.bind's
  `_1`-`_9` with `std::ignore` in fourteen (`Log.h`, through
  `boost/iostreams/copy.hpp`), asio's error categories and `winsock_init` in eight
  (`Config.h`, which includes only `boost/asio/ip/udp.hpp`: none of asio's own
  placeholders) and boost.system's in `Music.cpp` (boost.filesystem). Two objects have
  only `Log.h`'s, one between `Hook.cpp` and `Music.cpp` and one between
  `PracticeSession.cpp` and `Recorder.cpp`; their names are guesses (`Log.cpp`,
  `Process.cpp`), as is the 22nd object's (`RingBuffer.cpp`), which left nothing.
- **Includes:** the first COMDATs are `wchar.h`'s, placement `new` and `delete`, then
  `char_traits`: the order a standard header like `<map>` gives before any boost header
  (which brings `<utility>`, and `char_traits`, first). So `Config.h` includes the
  standard headers before asio.
- **ATL:** `atlbase.h` defines its registrar's strings (`L"S"`, `L"M"`, ...,
  `L"ForceRemove"`, ..., `L"TypeLib"`) in every object that includes it: five objects
  have them, `Music.cpp` and the four sessions with music, and not `EfzRevival.cpp`,
  which includes the session headers, nor the tournament session. So the sessions'
  headers see only `Playlist` (`Playlist.h`, held by value) and declare `MusicPlayer`;
  `Music.h` (with `CComPtr`s, so `atlbase.h`) is included by the sessions' sources. ATL
  is Visual Studio 2012's (`vc_libraryextended`, set up by
  `toolchain/setup-vs2012.sh` in `vs2012/atlmfc`); a `v110_xp` build defines
  `_USING_V110_SDK71_`, which `atlcore.h` needs with the 7.1A SDK.
- **`Utility.h`** (name made up): `Config.cpp`, `OnlineSession.cpp` and
  `TournamentSession.cpp` start their strings the same way (the unused `L"None"`,
  `L"Name"`, `L"Parameters"`, then the address parser's four `":"`) and each has its
  own pair of `to_utf8` functions in the same order: one header of `static` functions
  that the three include. Only `Config.cpp` uses the address parser.
- **How far:** `make revival-dll-check-image` shows the headers (but for the sizes that
  follow from the sections), `.rsrc` and the size of `.data` identical, `.text`
  `0x100` bytes short and `.rdata` `0x10` short. 404 of the 416 annotated functions
  match; 353 of the 368 developer functions and 2419 of the 2695 COMDATs are in their
  original order (`tools/revalign.py`); the static initializers are the same 271 in the
  same order. The string literals are the original's set but for ordering in a few
  objects; what's left in `.rdata` is mostly the exception tables, which follow the
  COMDATs' order, and the order of three imports within their DLLs.
- **Source forms the code shows** (**observed**: each changed one function from
  differing to matching, the rest of the source alike):
  - `if (c) x = a; else x = b;` stores in each branch, where `x = c ? a : b` becomes a
    `cmov` or `neg`/`sbb` before a call (`Recorder::setRecoilGuard`, `inputString`'s
    button letters, the five function keys in each session's `fightUpdate`); a value
    chosen for a call (`text << (c ? "a" : "b")`) is a call in each branch, which the
    compiler merges (`SpectatorSession::drawInfo`, `ReplaySession::drawInfo`,
    `setEfzReplay`).
  - The other way round, `fps_ = fps_ < 1.0 ? 1.0 : fps_;` keeps the value in registers
    for the following call, where an `if` stores and reloads it.
  - A zero in `eax` comes from `ZeroMemory`/`memset` (the original clears `FILETIME`s,
    `int` pairs and runs of members that way); plain `= 0` stores are immediates, and
    a statement order puts the `memset` last (`Game::Game`), the members it doesn't
    cover after it (`SpectatorSession::start`), or two of them side by side
    (`OnlineSession::start`).
  - `/fp:strict` copies a `double` into a local through two integer moves before
    comparing it (`Recorder::guardInput`), and computes `64.0 / 2` at run time
    (`ReplaySession::keyPressed`).
  - `if (a) {...} else {...}` lays out the `a` branch first: `ReplaySession`'s
    `update` and `sceneChanged` test `isControlling()` and handle it first.
  - Named temporaries (`SyncBlock block = makeSyncBlock(...); queue.push(block);`) pass
    the local's address; `return endpoint = ...;` passes the assignment's result
    (`parseEndpoint`); a member read in each test (`Recorder::checkStart`'s `start_`)
    keeps the cases from being proven exclusive.
  - Container element types: the practice recorder's and the replay's input bytes are
    `char` (`std::deque<char>`, `std::vector<char>`): `unsigned char` instantiates
    `std::_Allocate<unsigned char>`, which link-time code generation gives a register
    calling convention, so it can't fold with `char`'s.
  - `Game`'s replay name is a `std::wstring` in a struct of its own (its implicit
    constructor and destructor are folded with `boost::filesystem::path`'s); `rand`'s
    seed string is read with `str().data()`.
- **Not reproduced:** `SyncBlock`'s constructor matches with its members zeroed in the
  body (`frame`, `fpuCW`, then `stateP1`, `stateP2`, `state`, the doubles and `rng`),
  only the inputs in the initializer list, a change to the launcher's `SharedData.h`
  that is still to be made. Register allocation without a source change found yet in
  `Game::getCollisionInfo`, `collectRects`, `drawBoxRequest`, `readExtendedReplay` and
  `LiveInput`'s constructor (which the original compiles knowing its base
  constructor returns `this`); `Palettes::readColors`, whose `index` the original keeps
  though both callers pass 0 (local variables, `unsigned`, a dead caller didn't change
  that); `PracticeSession::keyPressed`'s `(x - middle) * -1.0 + middle`, which the
  original multiplies and this build turns into a subtraction (eight spellings
  tried); `MusicPlayer::play`'s merged `control_->Run()` tail;
  `OnlineSession::menuFramesToRun`'s `last + 1 - frame_`.

### How link-time code generation orders functions

Read from `c2.dll`'s code with its public symbols (Microsoft's symbol server has
`c2.pdb` and `c1xx.pdb` for these builds) and confirmed by test links
(`tools/ltcgprobe.py`):

- **Keys.** When the linker hands the objects' intermediate language to `c2.dll`, each
  object is read in link order, and every global symbol it defines or refers to gets a
  key the first time it is seen (`ModPutL2Ssr`: the keys count down from a large
  number; a definition read later keeps the key of the reference that created the
  symbol). The order of the symbols within an object is the order of its records:
  first the functions it defines, in the order of their definitions (a call before the
  definition doesn't create the symbol; a declaration doesn't either), then the
  symbols it only refers to.
- **The symbols an object refers to** come in one of two orders, depending on how the
  front end (`c1xx.dll`) wrote the object. With a precompiled header (`/Yu`) it keeps a
  work list (`WorkList_t`): each symbol is pushed when first referred to and the list
  is emptied last-in first-out, so the referenced symbols are created in the reverse of
  their first references (an inline function's references follow when it comes off
  the list). Without one (`m_usingWorkList` is set only for `/Yu`) it walks its symbol
  table instead (`BlockScope_t::DumpSymbols_impl`): a hash table of the identifiers,
  then each class's members in declaration order, which is why renaming swapped
  functions and call order didn't matter in test links without a precompiled header.
- **Emission.** Each object's non-COMDAT functions are sorted by key, ascending
  (`SymbolEmission::CompareSymOrderInternal`, a merge sort per object): so they come
  out in the reverse of their creation. COMDATs (header functions) come out roughly in
  creation order across the whole link, an identical-code fold taking the place of its
  earliest member.

Consequences for the sources:
- An object's own functions are defined in the reverse of their original address
  order (`tools/revreorder.py` rewrites a file that way); `static` helpers then need a
  declaration before their first use, which creates nothing.
- A function an earlier object refers to (a session's constructor, called from
  `EfzRevival.cpp`'s `init`; `hook`, `patchCode`, ... from its `setup`; `Session`'s
  virtual functions, from the derived sessions' vtables and destructors) is created
  there, so it comes after all of its own object's functions, in the order of the
  first references (with the precompiled header). Where it is defined doesn't matter.
- Object boundaries show where such functions sit: `PracticeSession`'s constructor
  comes before `Recorder`'s functions, so `Recorder` is a separate object
  (`Recorder.cpp`) after `PracticeSession.cpp`, whose functions it calls first; and
  `makeSyncBlock` (called first from `OnlineSession.cpp`) comes after the spectator
  session's constructor (called from `init`), so it is in an object of its own after
  the spectator's (`OnlineSync.cpp`).
- Names don't matter for the developer's functions; they still do for COMDATs folded
  with others and for anything sorted by the linker.

The modules, by address (chunk B), as far as known:

| Range | What |
|---|---|
| `0x10065620`-`0x1006abb0` | `Config.cpp`: the same source as the launcher's first object (ini keys, `DIK_`/`BUTTON_` names), plus `Utility.h`'s address parser and UTF-8 conversions |
| `0x1006abc0` | `dllmain.cpp`: the template `DllMain` |
| `0x1006abd0`-`0x1006de..` | Game state and input (`key.ini`, devices), the extended replay buffer, the hit/hurt/collision box display (`0x1006c1d0`, `0x1006cf90` call `EfzRender::addRectRender`), characters and palettes |
| `0x1006de..`-`0x1006f260` | `EfzRevival.cpp`: `init` (`0x1006f0b0`), the first-frame setup that installs the hooks (`0x1006ee10`), the hook targets (`0x1006dfa0`-`0x1006e070` replace `CReplayFile`'s methods; `0x1006eb10`-`0x1006ebc0` forward to the session), keyboard and joystick edges, the crash handler (`0x1006e1c0`), switching to practice/replay sessions (`0x1006e090`) |
| `0x1006f260`-`0x1006f7a0` | Save states: copies of the game's memory (`0x1006f390`) |
| `0x1006f7a0`-`0x1006fae2` | Hooks: patching bytes and three kinds of trampoline |
| `0x1006faf0`-`0x10070600` | Music (DirectShow: custom BGM folder), replay file names |
| `0x10070600`-`0x10074210` | `OnlineSession.cpp`: rollback, input exchange with the launcher, sync, replay saving |
| `0x10074210`-`0x10075680` | `OnlineSpectatorSession.cpp`: the spectator session |
| `0x10075680`-`0x100757e0` | `OnlineSync.cpp` (name unknown): `makeSyncBlock`, and an empty constructor and destructor nothing calls |
| `0x100757e0`-`0x10076b70` | `PracticeSession.cpp`: pause, frame step, save/load state, record/replay |
| `0x10076b70`-`0x10077650` | `Recorder.cpp`: recording and replaying a player's inputs |
| `0x10077650`-`0x10078900` | `ReplaySession.cpp`: the replay session |
| `0x10078900`-`0x10078960` | `Session.cpp`: `Session`'s default handlers (`revival/EfzRevival/Session.h`) |
| `0x10078960`-`0x1007a250` | The tournament session |

## Checking the injection

`tools/revival-test.sh` runs EfzRevival with `efz.exe` on a virtual X server (docker image
`efz-revival-test`, `toolchain/revival-test.Dockerfile`): it answers the launcher's menu
with 5 (Local Play), then reports whether `efz.exe` runs with `EfzRevival.dll` and
`DDRAW.dll` mapped and what the game window's title is (the DLL sets it on the first
frame), and keeps screenshots. Two things wine needs: a wine desktop window (the game
switches to 640x480, which a virtual X server can't), and `WINEDLLOVERRIDES=ddraw=n,b`,
so that the game loads the `DDRAW.dll` beside it, as Windows does, instead of wine's.

**Observed** with the original 1.02h files and the rebuilt `efz.exe`: the launcher
starts the game, both DLLs are mapped, and the title becomes
"Eternal Fighter Zero -Revival- 1.02h!!!". The `L"h!!!"` that a header defines as a
static `std::wstring` in most of the launcher's objects is the version suffix.

**Observed** with the rebuilt binaries too (`make revival-launcher`, the two DLL links,
copied into one folder): the recovered launcher starts the rebuilt `efz.exe`, the
recovered `EfzRevival.dll` and `DDRAW.dll` are mapped in it, the DLL's first-frame setup
sets the title "Eternal Fighter Zero -Revival- 1.02h!!!" and the title screen renders
through the recovered `DDRAW.dll`, as with the originals.

```sh
EFZ_DIR=/path/to/EFZ tools/revival-test.sh                        # the originals
EFZ_DIR=/path/to/EFZ tools/revival-test.sh --revival DIR --name x # rebuilt binaries in DIR
```

## The launcher and the DLL: shared memory

**Observed** (`revival/EfzRevivalLauncher/SharedQueue.h`, `SharedData.h`). The two processes
talk through named shared-memory queues: a header of two counters (records read and
written) and a ring of records, created and zeroed by whichever side comes first, each
with an auto-reset event `<name>Write`.

| Queue | Records | Written by |
|---|---|---|
| `Init` | 1 `GameInfo`: local side, delay, rollback, seed, practice keys, both names, the launcher's process id | launcher |
| `InputP1`, `InputP2` | 600 two-byte inputs | DLL (local), launcher (remote) |
| `PaletteP1`, `PaletteP2` | 10 palettes of `0xa4` bytes | DLL |
| `Net` | 100 ping statistics | launcher |
| `Sync` | 200 per-frame states: frame, state, FPU control word, both players' states, inputs and positions (doubles), RNG | DLL |
| `Quit` | 1 bool | launcher (on close; if the queue is full it kills `efz.exe`) |
| `LoadMatch` | 100 entries | launcher |

The launcher waits on the input queue's event to forward local inputs to the network.
`ProtocolContext`'s constructor (`0x432600`) reads `EfzRevival.ini` through `Config`:
`Debug` turns on the logs, `MaxRollback` is clamped to 9, `Player` 1 or 2 (anything else
picks a side at random), `HolePunchingServer` becomes a peer.

Logs: `logNet.txt` (per checked frame, the two queue sizes and `HH:MM:SS Checked <frame>`,
or on a desync `ERROR:` with both sides' states; ping summaries) and `logPing.csv`
(`<timeGetTime>,<round trip>`). The first desync prints "Desync detected", flashes the
console and plays the asterisk sound. Outgoing protobuf messages are compressed with
protobuf's `GzipOutputStream` (zlib format, level 9) before sending.

## Rollback (EfzRevival.dll's online session)

**Observed** in `revival/EfzRevival/OnlineSession.cpp` (`0x10070600`-`0x10074210`):
- **Input delay.** From the launcher's `Init` record, clamped to 0-20. In the menus it is
  re-derived as ceil(max ping / (2 x ms per frame)); a fight starts with the last delay
  set. In a fight the IncreaseInputDelay/DecreaseInputDelay keys change it, but not
  below ceil(ping in frames) - max rollback.
- **Each update.** Reads one local input and runs the frames from the current one up to
  the newest local input minus the delay. It pauses when local inputs lead the remote
  ones by more than delay + max rollback, and repeats the last local input when the
  delay has run out or the remote side is ahead by more than the lowest ping in frames.
  There is no rollback in the first 20 frames of a fight, from 120 frames after the
  match is decided, or outside fights (there it waits for remote inputs).
- **Save and restore.** A frame without the remote input runs on the last one repeated.
  A frame with both inputs is saved before it runs (the game's memory through the save
  states, plus the session's frame counters registered with `addInt`), its inputs go
  into the replay and its sync record is sent. After a run, the state of the last
  confirmed frame (not before the fight's start) is loaded, so the next update re-runs
  the unconfirmed frames; the ring holds 60 states. Rendering is off except on a run's
  last frame. Sounds are counted per frame so that a re-run doesn't play them twice,
  and sounds started on mispredicted inputs that won't recur are stopped.
- **Desyncs.** For every confirmed frame, in order, the DLL pushes a sync record (frame,
  scene, FPU control word, both players' actions, both inputs, the random seed, both
  positions) to the `Sync` queue; the launcher compares it with the remote side's.
- **Start.** P1 sends 22 scripted inputs to get through the title menu; P2 sends zeros.
  `Quit` is set on Esc in the menus or on going back to the title.
- **Replays and the battle log.** At character select the replay is named
  `<ReplayFolder>\<YYYYmmdd-HHMMSS> <P1> (<char>) vs <P2> (<char>).rep` and writing is
  switched on; only confirmed frames are written, and the fight's start sets the
  replay's random seed. SavePreviousReplay flushes it ("Saved replay to disk",
  "Failed to save replay", "All replays get autosaved"). The game's end-of-match replay
  handling (`0x763f04`, `0x763e50`) is hooked. The battle log (UTF-8) gets
  `<time> P1 VS P2` per session and
  `<fight start> <char> VS <char> Rounds: a b Duration: mmm:ss Score: x y` per game.
- **Music.** `MusicPlayer` plays the custom BGM folder through DirectShow (ATL `CComPtr`s;
  `Music.h` includes `atlbase.h`, whose registrar strings lead the strings of each
  object that includes it, see "The whole image") and remembers files that failed to
  play.

## Practice, replays, spectating, tournaments (EfzRevival.dll's other sessions)

**Observed** in `revival/EfzRevival/PracticeSession.cpp`, `ReplaySession.cpp`,
`OnlineSpectatorSession.cpp` and `TournamentSession.cpp` (`0x10074210`-`0x1007a250`):
- **Pause and frame step.** Pausing patches 10 places in `efz.exe` and sets
  `CScene3`'s speed (`+0x578`) to 0; the scene still runs every frame, so drawing and the
  overlay go on. A step clears the boxes, adds one to the "Frame Step" counter, runs one
  frame at speed 3 and pauses again. The counter resets on pausing, unpausing and
  leaving the fight. Loading a state while paused stays paused; otherwise it restores
  speed 3. Replays step the same way, stopping the game's reading of the replay file
  around the step.
- **Record and replay.** Each player's inputs go through a `Recorder` (3 bytes a frame:
  the game reads input 3 times a frame). Recording swaps the players' key bindings so
  that you drive the dummy, and appends to the selected buffer (SetBuffer1-5); Random
  picks a non-empty buffer at random each time playback starts. Start conditions: Now,
  Wake-Up (action 99 past its frame 2), Tech, Guard (actions `0x97`/`0x99`/`0x9c`),
  Recoil Guard (sets `CPlayer+0x14e` to 60 every frame) and Random RG (that, half the
  time, starting on actions `0xa8`-`0xaa`); Record Wait and Replay Wait hold until the
  condition is met. Under the guard conditions an idle dummy holds back (and down,
  unless the opponent is in the air). Saving or loading a state restarts recording or
  playback from there. Input delay applies to the human player: 3 zero bytes per frame.
- **Switching and mirroring players.** Switching swaps which player is the dummy and the
  two 16-byte key-binding blocks (saved at the start, restored on leaving the fight).
  Mirroring sets x to (x - 319.5) * -1 + 319.5.
- **Game speed.** Steps of 16 FPS (at least 1) through DDRAW.dll's timer (`setFps`); the
  reset key and leaving the fight go back to 64.
- **Spectating.** Each update runs min(frames received - 1 - frame, speed) frames,
  drawing only the last (and the versus screen), stopping early on a scene change; speed
  is 1-9 ("Game Speed: Nx"). It exits when the launcher dies, `Quit` fills or Esc is
  pressed.
- **Tournament.** P1 gets 22 menu inputs (down, down, A) to reach VS PLAYER. At character
  select the ini is re-read every 64 frames, and new player names start a new set. The
  versus screen sets the names and the replay's file name and starts recording;
  `tournament_results.txt` gets a header per set and one line per game (time, both
  characters, rounds, duration, set score). F1-F10 are cleared in fights and Esc must be
  held for 80 frames.
- **Replays.** Extended replays keep 300 save states, one every 64 frames
  (`RingBuffer<ReplayState>`), for seeking and for taking control of a character.

## DDRAW.dll: rendering, the overlay and the boxes

**Observed** in `revival/DDRAW/` (every developer function written; 214 of 217 match):
- **DirectDraw on Direct3D 9.** `DirectDrawCreate` returns `myIDirectDraw`; its
  `SetCooperativeLevel` creates the device (windowed, `D3DSWAPEFFECT_FLIP`, a lockable back
  buffer of the ini's BackBufferWidth/Height, software vertex processing with
  `FPU_PRESERVE`). The game's 8-bit surfaces are D3D surfaces in system memory in the first
  of P8, L8, A8, R3G3B2 or A4L4 the card supports, or `SoftwareSurface`s (an
  `IDirect3DSurface9` over `malloc`ed memory) with SoftwareRendering. `Flip` converts the
  8-bit back buffer through the palette into a 32-bit frame, stretches it onto a 640x480
  render target, draws the text and boxes there, and stretches that onto the back buffer
  (pillar- or letterboxed to 4:3 in fullscreen, which is borderless over the monitor and
  toggled with Alt+Enter). A failed `Present` rebuilds the default-pool surfaces and font.
- **`EfzRender`** (`0xb0` bytes, one instance at `0x100b6bc8`) holds that Direct3D state
  and the overlay: a `std::list` of text lines and a `std::unordered_set` of boxes (hashed
  and compared by rectangle only, so the first box added for a rectangle wins).
- **Text.** "ＭＳゴシック" 14 px before Vista, Consolas 15 px from Vista on; each line is drawn
  white over four black copies one pixel off (an outline). `addTextRender`'s last argument
  is `DT_` format flags.
- **Boxes.** Each box is a closed `ID3DXLine` polyline two pixels wide, created per box every
  frame and drawn with `SetPattern(flags)`. EfzRevival.dll draws hitboxes red, hurtboxes blue
  and collision boxes yellow; a hitbox that has already hit gets the pattern `0xf0f0f0f0`
  (four pixels on, four off).
- **Standalone fixes** (also under Revival, whenever the process is efz.exe 4.02): DDRAW's
  own window from the ini, a frame timer replacing `FrameTimerThread`'s loop at `0x40187f`
  (63.9 FPS by default, error carried between frames; `getEfzTimer` returns it, and
  EfzRevival.dll's game speed sets its FPS), DirectInput 7's `DirectInputCreateW` with
  joystick hats as directions, and a few sound and scene patches.
- **`getEfzInput(bool player2)`** runs a copy of `CInput::GetInput` (made at startup, with the
  hat hook) on the game's input object and returns the controls, so EfzRevival.dll can read
  real local input around its own patch of `CInput::GetInput`.

## EfzRevival.dll: hooks, boxes, save states

**Observed** in `revival/EfzRevival/EfzRevival.cpp`, `EfzGame.cpp`, `GameState.cpp`, `Hook.cpp`
(`0x1006a850`-`0x1006fae2`; 175 of 183 functions match):
- **Hooks.** `init` hooks `0x401582` (`WinMain`'s loop) to `setup`, which runs once: it sets
  the window title, makes `0x776053` an unconditional jump and installs the rest:
  - `0x40d131`, the end of `CInput::GetInput` -> `inputHook` (left+right becomes left, then
    the session's `input`);
  - `0x7656a7` in `CScene3::Vf2` -> the session's `fightUpdate`;
  - the call at `0x401642` -> `frameHook`: switch sessions if the game's mode changed,
    `keepAwake` (a zero mouse move through `SendInput`), key and button edges to the
    session, then the session's `update`;
  - the call at `0x76479c` in `CScene3::Draw` -> `drawBoxesHook`;
  - the CRT's `rand` at `0x777d61` -> `std::minstd_rand` with a uniform 0-`0x7fff`
    distribution (a random state the rollback can save);
  - `CReplayFile`'s five methods (`0x405e90`-`0x406020`) -> `ReplayFile`;
  - `CSound::Play` (`0x40de80`), `Stop` (`0x40de40`) and `SetVolume` (`0x40e5d0`) -> the
    session's sound slots.
  `setRendering(false)` makes 7 blit and fill functions return at once (rollback re-runs
  frames without drawing); `true` restores them. In practice mode, leaving the title
  switches to the replay session (scene 8) or the practice session (scene 1).
- **Boxes.** A session's `showBoxes(player, kind)` queues requests; `drawBoxesHook` draws
  them during the fight scene's `Draw`. `drawBoxRequest` reads the player's current pattern
  frame (patterns at `CPlayer+0x164`), puts each box through the game's own box function,
  the camera (with the shake offset while hit) and x2, and hands it to DDRAW.dll's
  `EfzRender::addRectRender(rect, colour, stipple)`:
  - hit boxes red `0xffff0000`, stippled `0xf0f0f0f0` while the hit is inactive;
  - hurt boxes blue `0xff0000ff`, only while the player is vulnerable;
  - the collision box yellow `0xffffff00`, plus the crossup midline: a zero-width rectangle
    at the player's x, twice the box's height, starting half a box higher;
  - projectiles (the 64-entry object ring) the same way, offset by 420 in y.
- **Save states.** A 500,000-byte buffer of copied regions: the x87 state, the F-key word,
  the fight scene (`0x598` bytes, or all but `0x434`-`0x440` when not full), `CGame`
  (`0x142f0`), each player (by its character's size), the 1 KB palette, the back buffer,
  the stage animation frames (`0x1c0` or `0xe0`), plus the random generator's state and
  the box list. Loading restores everything but the x87 state.
- **Crash handler.** Writes "!!!Crash!!!", the DLL's base, the exception's address and code,
  the registers and 150 stack words following the `ebp` chain to `logEfz.txt`.

## The launcher's protocol

**Observed** in `revival/EfzRevivalLauncher/Network.cpp`, `ProtocolContext.cpp` and the
`ProtocolState*.cpp` files. Each UDP datagram is a 2-byte header and one protobuf message:
byte 0 is 1 when the message is zlib-compressed (level 9; Init, Input, Sync and Palette
are), byte 1 the type; payloads are at most `0x3fe` bytes. Every packet refreshes its
sender's entry in the peer table.

| Type | Message | Fields |
|---|---|---|
| 0 | Init | f1: 0 confirm (host to client), 1 request; f2 game (0); f3 version (`0x66`); f4 role (1 player, 2 spectator); f5 side (the client's, in a confirm); f6 seed (the host's `timeGetTime`, 0 in a request); f7/f8 names as UTF-16 bytes, at most 20 characters, "None" if absent; f9 practice keys (both sides' ANDed) |
| 1 | Input | f1: 0 inputs, 1 ack; f2 last remote frame received (-1 in the spectator stream); f3 first frame; f4 count (60 per ack); f5 the 2-byte inputs (spectators get P1 and P2 alternating); f6 match index (a change loads the next match) |
| 2 / 3 | Ping / Pong | f3 `timeGetTime()`, echoed back; RTT = now - f3; a NAT-traversal ping has f3 = 0 |
| 4 | Sync | f1: 0 data (f4: 0x40-byte sync blocks), 1 request (f2 first frame, f3 count 10) |
| 5 | Quit | f1 0 |
| 6 | Palette | f1 player, f2 the 0xa4-byte palette |
| 7 | Redirect | f1 the endpoint to use instead (raw `sockaddr_in6`) |
| 8 | ChangeRole | f1: 1 host not playing yet, 2 host already playing ("join as a spectator?") |
| 9 | Done | f1: 0 delay chosen and ready, 1 refused (spectating disabled) |
| 10 | Punch | f1 the target endpoint |

Peers carry flags: 1 receives inputs, 2 connected player or host, 3 opponent, 4 the
hole-punching server.
- **Hosting** (`ProtocolStateHostConnect`) pings the punch server. A player's request gets a
  confirm and moves both sides to TestDelay; a spectator's gets ChangeRole(1), or Done(1)
  when spectating is off. A wrong version gets a confirm and, if a newer version exists,
  End.
- **Joining** (`ProtocolStateClientConnect`) resends the request every 500 ms; until
  connected it also sends Punch to the server, which relays it to the host. Punch replies
  make the client retry at the target port +0..9 in rotation. A confirm sets side, seed and
  names; 5000 ms of silence ends it.
- **TestDelay** measures the round trip with pings and suggests a delay of
  ceil(ping / (2 x 15.625 ms)) - rollback (rollback capped at 3); the user types the delay
  and Done(0) says ready (inputs arriving early count as Done).
- **Play** sends inputs and acks with resends, checks sync blocks frame by frame (a desync
  raises the alert), relays palettes, and sweeps NAT-traversal pings over port..port+50
  (players) or +10 (spectators). From 3 spectators on, the host redirects new spectators
  to existing ones, so that spectators feed one another.
- **Spectating** (`SpecConnect`, `SpecPlay`) connects with role 2 and follows the alternating
  input stream, its speed adjustable.
- **Timeouts.** A peer silent for 8000 ms is dropped; checked every 5000 ms while
  connecting and every 1000 ms in play.

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
