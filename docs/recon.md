# efz.exe reconnaissance

Target: Eternal Fighter ZERO MEMORIAL patched to **4.02**, the build EfzRevival requires.

| | |
|---|---|
| File | `efz.exe`, 3,743,744 bytes |
| SHA-256 | `3a1616d6c76d2eea08a95bb198d853e96cb6b9b3266e277ca1d167426dd66481` |
| PE timestamp | `0x4386998f` (2005-11-25 04:56:47 UTC) |
| Image base / entry | `0x400000` / `0x778a4a` (CRT `WinMainCRTStartup`) |
| PDB record | `D:\nonotaro\works\EFZ\EFZ.pdb`, RSDS GUID `1c282773e2de5c49bb17c3b43b19b436`, age 1 (PDB not shipped) |
| Checksum / file alignment | `0` / `0x1000` |

Reproduce with `tools/peinfo.py` and `tools/inventory.py`. Statements below are
marked **observed** (read directly from the binary) or **inferred**.

## Toolchain

Rich header, decoded by `tools/peinfo.py` (**observed**):

| Tool | Build | Objects | Reading |
|---|---|---|---|
| `Utc1310_CPP_Std` | 13.10.3077 | 152 | **The game.** C++ compiled by Visual C++ .NET 2003 *Standard Edition* |
| `Utc1310_C` | 13.10.3077 | 112 | Static CRT (Microsoft's prebuilt, optimised) |
| `Utc1310_CPP` | 13.10.3077 | 4 | Static CRT C++ support |
| `Masm710` | 7.10.3077 | 31 | CRT assembly helpers |
| `Utc1310_C` | 13.10.4035 | 2 | `dinput.lib`'s `c_dfDIKeyboard`/`c_dfDIJoystick` data-format objects. **Observed:** the DirectX SDK's `dilib*.obj` carry this stamp, and the two tables sit in `.text` at `0x776a70` and `0x777a80` |
| `Utc1310_CPP` | 13.10.4035 | 1 | Unidentified DirectX SDK library object |
| `Implib710` | 4035 | 6 | `ddraw`, `dinput` and `dsound` import objects (2 per DLL). **Observed:** the DirectX SDK (Aug 2005) libs carry 4035, as do all its libs from late 2004 on |
| `Implib710` | 2179 | 7 | 3 DLLs plus the shared null import descriptor. **Inferred:** the Platform SDK subset bundled with VS .NET 2003; the toolkit's own `kernel32.lib` carries 2179 |
| `Implib710` | 2067 | 2 | 1 DLL, source not identified |
| `Cvtres710` | 7.10.3052 | 1 | Resources |
| `Linker710` | 7.10.3077 | 1 | VS .NET 2003 linker |

Consequences for a byte-identical rebuild:

- **Compiler: `cl.exe` 13.10.3077 (Visual C++ .NET 2003 RTM).** The Standard Edition had no
  optimiser, so all game code is unoptimised. **Observed:** every game function has a
  `push ebp; mov ebp,esp` frame, `this` is spilled to the stack, and expressions are
  evaluated statement by statement. This is the easiest kind of MSVC output to match.
- **The free Visual C++ Toolkit 2003 1.01 reproduces it.** It ships `cl` 13.10.3077, and with
  `/Od` it generates identical code. **Observed:** `WinMain` matches byte for byte. The
  Toolkit 1.0 release is `cl` 13.10.3052; don't use it. The Standard Edition stamps
  `Utc1310_CPP_Std` into the Rich header and the toolkit stamps `Utc1310_CPP`, so the
  final header has to be fixed up after linking.
- **The build flags are `/Od /GS`, without `/EHsc`.** **Observed:** this is what matches.
  With `/EHsc`, every `new T(...)` would get an exception frame, and the original has none.
- **Stack layout follows a hash of local-variable names, not declaration order.**
  **Observed:** reordering `WinMain`'s locals changed nothing, but renaming `hWnd` to
  `hwnd` moved it to the original slot. Probe compiles show how it works:
  - Locals go into a **16-bucket hash table**.
  - The table is laid out bucket by bucket from the top of the frame.
  - Within a bucket, the later declaration sits higher.
  - Nothing outside the function matters, and neither does declaration order across
    buckets.
  - **The hash function itself is unknown.** CRC-32, FNV, djb2 and linear and shift-xor
    hashes all fail to fit.

  `tools/stackorder.py` works around the unknown hash by measuring ranks directly. Several
  names usually fit, so a match doesn't prove the developer's spelling.
- **`/GS` doesn't reorder locals.** **Observed:** the cookie goes directly above the first
  *protected* buffer in hash order. Protected buffers are `char`/`BYTE` arrays over 4 bytes
  and structs that contain one: `DSBUFFERDESC` counts, through its `GUID`'s `Data4[8]`.
  `DWORD`/`int` arrays, `PALETTEENTRY[256]` and `BYTE[2]` don't get a cookie.
- **Large arrays and structs are 8-byte aligned, and their size is rounded up to 8.**
  **Observed:**
  - 100-, 256- and 1000-byte `char` arrays, `DDSURFACEDESC` (`0x6c` → `0x70`) and
    `PALETTEENTRY[256]` start 8-aligned with padding above them.
  - Arrays of 36 bytes or less (`char[8]`, `char[10]`, `char[30]`, `char[32]`,
    `DWORD[9]`) are packed at 4-byte alignment.
  - The exact threshold lies in between. This pins down buffer sizes: `CFile::Printf`'s
    buffer is `char[256]`, not `char[260]`.
- **`char` locals share slots.** **Observed:** `BYTE`/`char` locals that are adjacent in
  hash order are packed into one 4-byte slot, from its top byte down.
- **Block-scope locals get their own slots.** **Observed:**
  - In `UpdateEffect`, each `case` block's `double`s get fresh slots below the
    function-scope locals, one block after another in code order.
  - `for (int y = ...)` inside an `if`/`else` branch counts as that branch's block
    (`CGraphics::LoadSurface`, `DrawLine`).
- **Compiler temporaries go below the named locals.** **Observed:** this covers the
  pointer copies for `new`/`delete`, struct return values and `switch` operands.
- **Evaluation is left to right, unless the right operand is heavier.** **Observed:**
  - In floating-point expressions, the left operand is evaluated first. It is spilled to
    a temporary when the right one contains a call.
  - A heavier right operand is evaluated first: `*ra + *(rb += 4)` loads `rb` first
    (`BuildBlendTables`).
  - `data[A + B + k]` computes `A`, then `B`, adds `data` to `B` and indexes with `A`
    (`CInput::LoadPreset`).

  Operand order in the original source can therefore be read off the binary, and folding
  an increment into an expression shows up as a change in evaluation order.
- **Inline functions are COMDATs placed after the object that first uses them, in
  emission order.** **Observed:**
  - Emission follows the referencing functions in source order.
  - Within one function, the inline functions it uses are emitted in the order they are
    *defined*.
  - `effect.obj` emits `fabs(float)`, `fabsf`, `sin(float)`, `sinf` and
    `EffectDesc::EffectDesc` in the original's address order.
  - In `game.obj`, the original order (`EffectAnim::Alloc`, its constructor, then
    `CFile`'s) only came out after `EffectAnim`'s definition, with `Alloc` first, moved
    above `CFile`'s.
  - Compiler-generated helpers (`??_E` vector deleting destructors, the `??_H`/`??_I`
    vector constructor/destructor iterators) are emitted the same way.
- **Inline assembly is used for the pixel loops.** **Observed:** the blitters,
  `FillRect` and `Upscale` in `CGraphics` contain `__asm` blocks that save `esi`/`edi`
  themselves. Functions with `__asm` also save `ebx`/`esi`/`edi` in the prologue.
- **Shift-JIS string literals need code page 932.** **Observed:** under wine's default code
  page, `cl` reads a `0x5c` trail byte (in `表`, `ソ`, …) as a backslash escape.
  `tools/msvc` sets `LC_ALL=ja_JP.SJIS`. The Makefile converts the UTF-8 sources to CP932
  before compiling.
- **Watch for `windows.h` macros.** A method named `PlaySound` or `LoadBitmap` silently
  becomes `PlaySoundA`/`LoadBitmapA`.
- **The compiler pads functions to 16 bytes with `int3` inside one `.text` section;
  `/Gy` is not involved.** **Observed:** in the recompiled `main.obj`, `WndProc` sits at
  `+0x670` and `FrameTimerThread` at `+0x850`. Compiler-generated functions (scalar
  deleting destructors) go in COMDAT sections, which the linker places right after the
  object's code.
- **Matched objects.** All game code from `0x401000` to `0x40e62f` matches, object by
  object. Run `tools/progress.py` for current numbers.

  | Source | Range | Functions | Contents |
  |---|---|---|---|
  | `main.cpp` | `0x401000`–`0x4019af` | 12 | `WinMain`, window procedure, frame timer; inline `CGraphics` constructor; init stubs at `0x786420`–`0x7864af` |
  | `effect.cpp` | `0x4019b0`–`0x4054af` | 7 | `CGame::UpdateEffect`, a dead `.bmp`→`.dat` converter, inline helpers |
  | `file.cpp` | `0x4054b0`–`0x405a1f` | 18 | `CFile`, the Win32 file wrapper |
  | `config.cpp` | `0x405a20`–`0x40606f` | 11 | `key.ini` access, per-character `.rec` records, `CReplayFile` |
  | `game.cpp` | `0x406070`–`0x4083af` | 35 | `CGame`: effects, sounds and music, screen shake, palette flashes; inline helpers |
  | `graphics.cpp` | `0x4083b0`–`0x40c5df` | 36 | `CGraphics`: DirectDraw, sprite loaders, blitters, palettes, screenshots |
  | `input.cpp` | `0x40c5e0`–`0x40d80f` | 9 | `CInput`: DirectInput keyboard and joysticks, bindings |
  | `sound.cpp` | `0x40d810`–`0x40e62f` | 15 | `CSound`: DirectSound, `.wav` loading, music loop points |

  The boundaries come from each object's string literals, which are contiguous in
  `.rdata`. The next object starts at `0x40e630` with two `CPlayer` methods, followed by
  `CPlayer`'s constructor (`0x40e740`).
- **String literals are not pooled.** **Observed:** `/GF` is off, and `WinMain`'s four
  identical `"ETENAL FIGHTER ZERO"` literals each get their own copy. (The typo is the
  original's.)
- **`/GS` is on in game code.** **Observed:** 30 game functions copy the security cookie at
  `0x78f050` into `[ebp-4]`.
- **No C++ exception frames in game code.** **Observed:** all `fs:0` uses are in the CRT.
- **Functions are padded to 16 bytes with `int3`.** **Observed.**
- **The CRT is linked statically.** **Observed:** there's no `msvcr71.dll` import. The imports
  include `CreateThread` and `Tls*`, so it is probably the multithreaded `libcmt.lib`
  (**inferred**). The CRT should be linked from VS .NET 2003's own libraries, not decompiled.
- **Header fields** must be set after linking: the timestamp, the RSDS GUID/age/path, and
  the Rich header (its count of 152 also confirms the number of game translation units).

## Imports

DirectX 7-era APIs: `DirectDrawCreate`, `DirectInputCreateEx`, `DirectSoundCreate`
(by ordinal 1), plus WINMM (`timeBeginPeriod`/`timeGetTime`, `mmio*` for WAV), USER32
window/message functions, and one GDI32 call. 115 imported functions in total.

## Code layout (`tools/inventory.py`)

| Region | Range | Functions | Bytes |
|---|---|---|---|
| Game | `0x401000`–`0x77697e` | ~622 | 3,627,390 |
| Import thunks and DirectInput data formats | `0x77697e`–`0x777d46` | — | 5,064 |
| Static CRT | `0x777d46`–`0x7864af` | ~342 | ~59,000 |

**Observed:** the last game function returns at `0x77697c`, and 39 `jmp [IAT]` thunks follow
it. Then come DirectInput's keyboard and joystick data-format tables. The CRT begins with
`operator new` at `0x777d46`. Other CRT addresses learned from `WinMain` relocations:
`srand` `0x777d54`, `time` `0x777d83`, `operator delete` `0x777e20`, `memset` `0x777dc0`,
and `_purecall` `0x77893d` (from `CPlayer`'s vtable).

- **The first game function is `WinMain` at `0x401000`.** **Observed:** `RegisterClassA`,
  `LoadIcon(0, IDI_APPLICATION)`, and `memset` (CRT, `0x777dc0`).
- **Game functions are mostly C++ virtual methods** (**observed**). There are 36 vtables
  in `.rdata`:
  - **23 vtables have 13 slots each.** These are the character classes (24 character
    folders; variants such as `nayukib` may share a class, **inferred**). Slot 12 is
    usually the shared base method `0x410b70`.
  - **13 smaller vtables (2–6 slots)** are probably projectile, effect and system objects (**inferred**).
- **Functions are very large:** median ~320 bytes, but the biggest are 70–118 KB each.
  These are per-character virtual methods. Each is probably a large state machine over
  move states (**inferred**). Two of them, `0x5b2d10` and `0x5c8580`, are exactly 88,176
  bytes, which suggests copy-and-paste or a shared macro between related characters.
- **There are 97 switch jump tables** in total.
- **Character objects have a large layout** (**observed** field offsets): `+0x14c`,
  `+0x2ca`, `+0x2cc`, an array at `+0x3d0`, and an array of 0x98-byte records near `+0x556`.

## Program structure (from `WinMain`, matched)

Each line below is **observed**, read from the matched `WinMain` in `src/main.cpp`:

- **Window:** a borderless `WS_POPUP` window, sized to the full screen and registered as
  `"ETENAL FIGHTER ZERO"`.
- **Frame timer:** `timeBeginPeriod(1)` is followed by a time-critical thread
  (`FrameTimerThread`, `0x401850`). The thread waits `g_frameWait` ms (initially 10) on
  an event that is never signalled, then signals `g_frameEvent`, which the main loop waits
  on once per frame. Once a second, if more than 64 frames ran, it adds 1 ms to
  `g_frameWait`. That's the 64 FPS cap. It only ever slows down; it never speeds back up.
- **Shutdown:** on `WM_DESTROY`, `WndProc` deletes the scenes, the game object and both
  `CPlayer` objects, shuts down sound, input and graphics, and kills the timer thread.
  `CPlayer` is deleted through a base with a non-virtual destructor, so derived
  destructors never run. That's a bug in the original.
- **Subsystems** are globals, each initialised with the window handle:
  - graphics (DirectDraw) at `0x790150`, which also gets config byte `0x20`
  - input (DirectInput) at `0x7b0968`
  - sound (DirectSound) at `0x7b0b60`

  `ReadConfigByte` (`0x405a20`) re-reads the config file on every call.
- **Game state:** a `0x142f0`-byte object at `0x79010c` is created next. Its `+0x1368`
  flag toggles every frame, and its `+0xf26` value is passed to the sound system each frame.
- **Scenes:** eight objects in `g_scenes[9]` at `0x790110` (slot 4 is unused); slots 6–8
  sit behind an `if (1)`. Each frame calls `g_scenes[g_scene]->Update()` (vtable slot 1),
  and its return value is the next scene index (`BYTE` at `0x790148`). Constructors and
  sizes are listed in `src/efz.h`.

## Effect system (from `CGame::UpdateEffect`, matched)

**Observed:**
- **Ring buffer.** `CGame` holds 640 effects in a ring buffer: head `+0x1380`, tail
  `+0x1382`, active flags `+0x1384`, and `0x70`-byte records at `+0x2a08`.
- **Creating and removing.** `CreateEffect` (`0x407100`) copies an `EffectDesc` built on
  the caller's stack into the next slot; `RemoveEffect` (`0x4072a0`) frees a slot. Many
  game functions call `CreateEffect` (1268 call sites).
- **Animation table.** Each effect has a type, frame and timer. The table at `+0x14208`
  gives each type's frame count and per-frame durations. An effect is removed after its
  last frame.
- **Behaviours by type:**
  - particle bursts, spawned on the first frame
  - straight-line motion at a random angle and speed
  - debris that bounces on `y = 0`: gravity `0.2`, damping `0.6`–`0.9`
  - orbiting points on a rotated ellipse, slowed by `0.94` each frame
  - screen-centre (160, 120) follow-ups when an animation ends
- **All randomness is `rand()`.** A rollback-netplay port must keep the CRT's `rand()`
  sequence and call order identical.

## Engine facts worth preserving

- **The game runs at 64 FPS, not 60.** Source: the EfzRevival changelog.
- **`efz.exe` loads data files by name.** Each `X.dat` can be swapped for an `X.bmp`
  fallback. Examples: `system\title.dat`/`.bmp`, `system\stage\all.dat`, and
  `nanase\nanase2.pat`, `ikumi\ikumi2.pat` (second-form characters).
- **EfzRevival** (DDRAW.dll proxy + `EfzRevival.dll`) hooks this exact build. It adds
  rollback netplay, spectating, replays and training features, and its feature list
  is the parity target for the modernised fork.

## Platform layer (matched)

**Observed** in the matched code:

- **Graphics** (`CGraphics`, DirectDraw 1 interfaces):
  - The screen is 320x240 or 640x480 in 8-bit colour. The primary surface and its one
    back buffer are in *system* memory.
  - Sprites are system-memory surfaces. Everything is drawn in software into the
    320x240 corner of the back buffer by `__asm` loops: colour-keyed copy, mirrored
    copy, two 64 KB blend tables (average and saturated sum), tint, shadow and smear.
  - In 640x480 mode, `Flip` doubles the image in place.
  - The blend tables are rebuilt from the palette with squared distances from a
    quarter-squares table.
- **Input** (`CInput`, DirectInput 7):
  - Each player has 8 bindings: 4 directions and 4 buttons.
  - A binding is a keyboard key or a joystick button or axis direction (dead zone ±500
    of ±1000).
  - The keyboard is acquired exclusively.
- **Sound** (`CSound`, DirectSound):
  - There are 150 static buffers, each filled from a `.wav` kept in memory.
  - The music loops by moving the play cursor back once it passes a loop end read from
    the file's `cue `/`adtl` chunks.
- **Shared game state** (`CGame`):
  - edge-triggered button presses
  - 920 effect sprites and 65 sound effects
  - music with volume fades
  - screen shake: a decaying amplitude on two rotating phases
  - palette flashes to white or black

## Data formats

**Observed**, from the matched loaders, except where marked:

- **`.dat` images** (e.g. `system\effect\effect.dat`, `system\object.dat`):
  - Byte 0 is a palette entry count `n`, followed by `n` 3-byte entries in B, G, R
    order.
  - Then come sprites back to back. Each is a little-endian `u16` width and height,
    then pixels, which are either:
    - **raw:** bottom-up rows, each byte plus a palette base
    - **run-length:** top-down; a byte above the threshold `rle` repeats the previous
      colour `byte - rle` times
  - `effect.dat` holds 920 sprites (`rle` `0x51`, base `0xaf`).
  - **Inferred:** character `.dat` files are the same container. The flag bytes
    `0xf0`/`0xfe` seen before are palette counts.
- **`system\effect\effect.pat`:**
  - A `u32` animation count.
  - Per animation: 3 unknown `u32`s and a frame count.
  - Per frame: 6 `u32`s (duration, sprite, width, height, hotspot x, y), 14 unused
    `u32`s and 10 unused 16-byte records.
  - **Inferred:** character `.pat` files share at least the frame record.
- **`key.ini`** (at least 32 bytes):
  - Bytes `0x00`–`0x1f`: the bindings, per player and in order up, down, left, right,
    A–D. Each binding is two bytes, a device and a code; a device byte `n > 0` gives the
    binding `(n << 8) + code - 1`.
  - Further presets of 39 bytes sit at `n * 39`; byte `0x9c` selects one.
  - Byte `0x20`: the display mode (1 = 640x480).
  - Bytes `0x21`–`0x26`: game settings read by `CGame`.
- **`system\<name>\<name>.rec`:** 36 bytes: 8 `u32` per-character counters and a zero.
- **Replays** (`CReplayFile`): a stream of `u16` input words. (EfzRevival's `.rep`
  format extends the game's.)
- **`snap\snNNNN.bmp`** screenshots: a 320x240 8-bit BMP of the back buffer.
- **`*.wav`:** PCM only. Music loop points come from the `cue ` and `adtl` chunks in
  the file's last 320 bytes (`u32` at chunk + `0x10`, times 4).
- **`*.pat` character files** (31) start with a `u32` count (`akane.pat`: 223)
  (**inferred** layout beyond that).

## Not yet established

- **The stack-order hash function.** It's measured empirically for now; recovering it
  from `c1xx.dll` would let tools predict layouts without compiling.

- **The function list is approximate.** It comes from objdump with heuristics; it needs
  a Ghidra or IDA database and a reconciled function list.
- **Most translation-unit boundaries are unknown.** There are 152 objects; the first 8 are
  established (see *Matched objects*). The rest follow the same method.
- **Some compiler flags are unconfirmed.** `/Od /GS` without `/EHsc` is settled by
  `WinMain`. `/Zp`, `/J` and `/GR` still need a function that depends on them.
- **Import hints are unchecked.** Byte-identical `.idata` needs import libraries whose
  hints match the original; the SDK libraries' hints haven't been compared yet.
- **The character `.pat` record layout** beyond the effect frames is not decoded yet.
