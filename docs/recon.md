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
| `Utc1310_CPP_Std` | 13.10.3077 | 152 | **The game.** C++ compiled by Visual C++ .NET 2003 *Standard Edition*. Everything in the image comes from 71 of them (see *Matched objects*); the other 81 left nothing in it |
| `Utc1310_C` | 13.10.3077 | 112 | Static CRT (Microsoft's prebuilt, optimised) |
| `Utc1310_CPP` | 13.10.3077 | 4 | Static CRT C++ support |
| `Masm710` | 7.10.3077 | 31 | CRT assembly helpers |
| `Utc1310_C` | 13.10.4035 | 2 | `dinput.lib`'s `c_dfDIKeyboard`/`c_dfDIJoystick` data-format objects. **Observed:** the DirectX SDK's `dilib*.obj` carry this stamp, and the two tables sit in `.text` at `0x776a70` and `0x777a80` |
| `Utc1310_CPP` | 13.10.4035 | 1 | `dxguid.lib`'s `dxguid.obj`, for the DirectInput GUIDs. **Observed:** it carries this stamp |
| `Implib710` | 4035 | 6 | `ddraw`, `dinput` and `dsound` import objects (2 per DLL). **Observed:** the DirectX SDK (Aug 2005) libs carry 4035, as do all its libs from late 2004 on |
| `Implib710` | 2179 | 7 | `winmm`, `kernel32` and `gdi32`, plus the null import descriptor from `winmm.lib`, the first library. **Observed:** the February 2003 Platform SDK's `winmm.lib` and `gdi32.lib` and the toolkit's `kernel32.lib` carry 2179, and their hints match the original's |
| `Implib710` | 2067 | 2 | `user32`. **Observed:** the original's `user32` hints equal the February 2003 Platform SDK's up to `PostQuitMessage` and are one higher from `RegisterClassA` on; the 2005 SDK's differ elsewhere (`LoadCursorA` to `PostQuitMessage`, `UpdateWindow`). **Inferred:** VS .NET 2003's own `user32.lib`, which isn't freely available; `toolchain/user32lib.py` derives a stand-in |
| `Cvtres710` | 7.10.3052 | 1 | The icon resource. **Observed:** the .NET Framework 1.1 ships `cvtres.exe` 7.10.3052 |
| `Linker710` | 7.10.3077 | 1 | VS .NET 2003 linker |

Consequences for a byte-identical rebuild:

- **Compiler: `cl.exe` 13.10.3077 (Visual C++ .NET 2003 RTM).** The Standard Edition had no
  optimiser, so all game code is unoptimised. **Observed:** every game function has a
  `push ebp; mov ebp,esp` frame, `this` is spilled to the stack, and expressions are
  evaluated statement by statement. This is the easiest kind of MSVC output to match.
- **The free Visual C++ Toolkit 2003 1.01 reproduces it.** It ships `cl` 13.10.3077, and with
  `/Od` it generates identical code. **Observed:** `WinMain` matches byte for byte. The
  Toolkit 1.0 release is `cl` 13.10.3052; don't use it. The Standard Edition stamps
  `Utc1310_CPP_Std` into each object and the toolkit stamps `Utc1310_CPP`;
  `tools/stdstamp.py` rewrites the stamp after compiling.
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

  More cases, **observed** while matching `CPlayer`:
  - `p->arr[i]` adds the member offset to `p` first, which makes `p` the heavier operand,
    so `p` is loaded before `i`. The raw form `(char*)p + i*4 + off` loads `i` first. With
    `this` as the base the two forms compile the same.
  - In `a + b` and `a * b` on doubles, a memory operand is kept as the instruction's
    operand. If its address is worked out before the other side is loaded, it was the
    left operand: `fild t; fmul [X]` with `X`'s address ready first is `X * t`. A constant
    doesn't count: `0.0 * x` computes `x`'s address first and still loads `0.0` first.
  - `x += e` works out `x`'s address first and loads `x` last. `x = e + x` doesn't.
  - `==` and `!=` on doubles compile to `fucompp` with the *right* operand loaded first.
    The relational operators load the left one first and use `fcomp`/`fcompp`.
  More, **observed** while matching Shiori:
  - `lea r, [x + y + K]` folds a constant into the addition that follows it in the
    source: `x + K + y`. If `y` is computed first, the source is `x + y + K`, since
    `(x + K) + y` always computes `x + K` first. A plain load next to a call has the call
    evaluated first; anything heavier is evaluated in source order.
  - `imul r, [m]` with `r` copied from another register just before (or the product moved
    to `eax` for a division afterwards) is `m * x`, not `x * m`.
  - `float + int` compiles to `fiadd`, `double + int` to `fild` and `faddp`. So
    `25.0f * f + i * f + n` stays `float` and keeps `fiadd`, and an explicit
    `(double)` on an `int` operand changes later instructions. Write int-to-float
    conversions implicitly.
  - Comparing doubles, `a > b - c` against `m` in memory: the side that is a plain load
    can have its address worked out first just because it is heavier. Against an
    arithmetic expression, a memory operand whose address comes first was the left
    operand.
  - A `short` or `char` incremented at its own width (`mov cx,[m]; add cx,1`) is `x++`.
    After `movsx`/`movzx` it is `x = x + 1`.
  - A `char` constant argument of 0x80 or more pushed as `0xb0` (not `0xffffffb0`) means
    an unsigned `BYTE` parameter.
- **Register choice rotates through `eax`, `ecx`, `edx`** across statements, calls and
  labels alike, and dead code still takes its turn. **Observed:** a statement the
  compiler drops (one after a `break`, or `if (0) {}`) emits nothing but moves the
  rotation on, so the next statement starts one or two registers later. The original
  has such dead code in places (Shiori's `Vf6` has nine, Kanna's `Vf6` one).
  `tools/regfix.py` finds them by comparing builds and records them in
  `tools/regpads.json`; the lifter then writes that many `if (0) {}` there.
- **More forms, observed in the character code:**
  - A comparison stored to a `char` is worked out at 8 bits (`sbb cl,cl`, or `setl dl`
    alone) when written `c = a < b`, and as an int (`sbb ecx,ecx`, or `xor edx,edx`
    before `setl dl`) when written `c = a < b ? 1 : 0`.
  - `x * 2` on a `float` is `fadd st(0),st`, and an `int` 2 keeps the result `float`.
  - Of two scaled terms in a sum, the compiler folds the left one's scaling into the
    `lea` and shifts the right one itself: `lea [x*4 + y*2 + 1]` with `x` shifted first
    is `y * 2 + x * 4 + 1`.
  - `int` against `double`: the `int` is always loaded with `fild`, so which side's
    address is worked out first shows the source order. With two plain `double`
    loads, the heavier address comes first whatever the order.
  - A base-class method called from a derived class adjusts `this` by the base's offset
    without the null check an explicit cast adds (`ObjBase` methods from `CPlayer`).
- **More forms, observed in the scenes:**
  - A `switch` with few cases compiles to compares on its temporary (`cmp [t], 1; je`
    ... `jmp default`), not a jump table. Consecutive cases sharing one body become a
    range check: `cmp [t], 0; jl default; cmp [t], 1; jle body`.
  - `/GS` protects `char` and `short` arrays, also inside a struct, but not `int`
    arrays or arrays of `RECT`. A 0xc8-byte frame record declared as `BYTE[0xc8]`
    brought in a cookie the original doesn't have; as `RECT`s and scalars it doesn't.
  - A comparison whose value is dropped, `(int)(a <= b);`, still computes 0 or 1 into a
    temporary that nothing reads. Assigned to a variable, the value is copied out of
    that temporary instead.
  - An `unsigned` converted to `double` is stored as a 64-bit value with a zero high
    dword and loaded with `fild qword`.
  - A struct returned by value goes to a hidden temporary. `r = f()` copies it once into
    `r`; `this->r = f()` copies it into a second temporary first; `g(f())` pushes it
    straight from the first.
  - `delete` of a pointer to a type without a destructor (`delete (char*)p`) stores the
    pointer in a temporary and calls `operator delete`; the temporaries of a function's
    `delete`s are laid out in source order.
  - `new T[n]` keeps `n` in a temporary of its own.
  - A two-dimensional member array is indexed row first: `lea r, [this + i*R + K]` and
    then `[r + j*s]`. The flat form `*((char*)this + i*R + K + j*s)` puts `K` in the last
    addressing mode instead.
  - Folded memory operands: for `M + a` with `a` a plain load the compiler loads `M` and
    folds `a`. So a folded `M` whose address was worked out before `a` was loaded is the
    right operand, `a + M`, unless the result is stored back to `M` (`M += a`).
  - A `short` or `char` `x += y` evaluates `y` before loading `x`; `x = x + y` loads `x`
    first. In both, `x`'s address can be worked out before `y`.
  - An `(expression) * m / k` keeps the expression's register as the product's:
    `imul edi, [m]; mov eax, edi; cdq`.
- **Some expressions always go through unnamed temporaries.** **Observed:**
  - A boolean used as a value (`return a && b;`, `x * (y > 0)`) is materialised as 0 or 1
    in a temporary by an `if`/`else` diamond. The diamond is hoisted in front of the
    expression that uses it.
  - An `int` expression converted to `double` is stored to a temporary for `fild`.
  - `(float)e` is an `fst dword` into a temporary that is never read. The rest of the
    expression keeps using the unrounded value.

  These temporaries go below all named locals and below `this`. `this` itself is placed
  by the same name hash as the locals, so named locals can sit on either side of it, but
  a slot below every name is always a temporary.
- **More idioms.** **Observed:** `x * 2.0` compiles to `fadd st(0),st`. A `char` function's
  `return -1` is `or al,0xff`. A struct assignment of up to 16 bytes is a run of `mov`
  pairs, one per dword.
- **Classes.** **Observed** in `CPlayer`:
  - A class with a vtable whose base has none puts the vtable pointer at 0 and the base
    after it, aligned to the base's alignment: `ObjBase` holds doubles, so it starts at 8.
  - Converting a pointer to a base at a nonzero offset is null-checked
    (`p ? (char*)p + 8 : 0`).
  - Stores that run before a member object is constructed come from the constructor's
    initializer list. They are fields declared before that member.
  - The compiler sets the vtable pointer at the start of constructors and destructors.
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
  - In a constructor, the inline functions the body uses come before the constructors of
    member objects. `CPlayer`'s constructor emits `PatternData`'s constructor (used by
    `new PatternData[505]` in the body) before `Afterimages`'s (a member).
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
- **Matched objects.** All game code from `0x401000` to `0x77697e` matches, object by
  object: the platform layer, `CPlayer`, the 24 character classes, four animated stage
  backgrounds and the eight scenes. Run `tools/progress.py` for current numbers.

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
  | `player.cpp` | `0x40e630`–`0x412b0f` | 49 | `CPlayer`, the base of the character classes; inline `PatternData` and `Afterimages` methods |
  | `playerobj.cpp` | `0x412b10`–`0x4136cf` | 6 | `CPlayer`'s table of 64 spawned objects and drawing them |
  | `shiori_vf6.cpp` | `0x4136d0`–`0x422d6f` | all | `Vf6`, the per-state update |
  | `shiori.cpp` | `0x422d70`–`0x43405f` | all | `CShiori` and the inline `ObjBase::SetVelocity` |
  | `sayuri_vf6.cpp` | `0x434060`–`0x4463df` | all | `Vf6`, the per-state update |
  | `sayuri.cpp` | `0x4463e0`–`0x45184f` | all | `CSayuri` |
  | `nayuki_vf6.cpp` | `0x451850`–`0x46108f` | all | `Vf6`, the per-state update |
  | `nayuki.cpp` | `0x461090`–`0x46d96f` | all | `CNayuki` |
  | `nanase_vf6.cpp` | `0x46d970`–`0x48a71f` | all | `Vf6`, the per-state update (and the second one it hands over to) |
  | `nanase.cpp` | `0x48a720`–`0x49d60f` | all | `CNanase`; an unused destructor |
  | `nagamori_vf6.cpp` | `0x49d610`–`0x4add8f` | all | `Vf6`, the per-state update |
  | `nagamori.cpp` | `0x4add90`–`0x4c04af` | all | `CNagamori` and the inline `ObjBase::AngleTo` |
  | `mizukab_vf6.cpp` | `0x4c04b0`–`0x4d284f` | all | `Vf6`, the per-state update |
  | `mizukab.cpp` | `0x4d2850`–`0x4e7ebf` | all | `CMizukaB` |
  | `mizuka_vf6.cpp` | `0x4e7ec0`–`0x4f82ff` | all | `Vf6`, the per-state update |
  | `mizuka.cpp` | `0x4f8300`–`0x50c4af` | all | `CMizuka` |
  | `misuzu_vf6.cpp` | `0x50c4b0`–`0x519dff` | all | `Vf6`, the per-state update |
  | `misuzu.cpp` | `0x519e00`–`0x530bbf` | all | `CMisuzu` |
  | `mishio_vf6.cpp` | `0x530bc0`–`0x54647f` | all | `Vf6`, the per-state update |
  | `mishio.cpp` | `0x546480`–`0x5571ef` | all | `CMishio` |
  | `misaki_vf6.cpp` | `0x5571f0`–`0x5678ff` | all | `Vf6`, the per-state update |
  | `misaki.cpp` | `0x567900`–`0x5736cf` | all | `CMisaki` |
  | `mio_vf6.cpp` | `0x5736d0`–`0x58830f` | all | `Vf6`, the per-state update |
  | `mio.cpp` | `0x588310`–`0x59c49f` | all | `CMio` |
  | `minagi_vf6.cpp` | `0x59c4a0`–`0x5a9f9f` | all | `Vf6`, the per-state update |
  | `minagi.cpp` | `0x5a9fa0`–`0x5c857f` | all | `CMinagi` |
  | `mayu_vf6.cpp` | `0x5c8580`–`0x5dddef` | all | `Vf6`, the per-state update |
  | `mayu.cpp` | `0x5dddf0`–`0x5e85ef` | all | `CMayu` |
  | `makoto_vf6.cpp` | `0x5e85f0`–`0x5f6d8f` | all | `Vf6`, the per-state update |
  | `makoto.cpp` | `0x5f6d90`–`0x60792f` | all | `CMakoto` |
  | `mai_vf6.cpp` | `0x607930`–`0x6163af` | all | `Vf6`, the per-state update |
  | `mai.cpp` | `0x6163b0`–`0x62a5df` | all | `CMai` |
  | `kaori_vf6.cpp` | `0x62a5e0`–`0x638d8f` | all | `Vf6`, the per-state update |
  | `kaori.cpp` | `0x638d90`–`0x6429bf` | all | `CKaori` |
  | `kano_vf6.cpp` | `0x6429c0`–`0x653a1f` | all | `Vf6`, the per-state update |
  | `kano.cpp` | `0x653a20`–`0x66756f` | all | `CKano` |
  | `kanna_vf6.cpp` | `0x667570`–`0x675c7f` | all | `Vf6`, the per-state update |
  | `kanna.cpp` | `0x675c80`–`0x68354f` | all | `CKanna` |
  | `ikumi_vf6.cpp` | `0x683550`–`0x6a59bf` | all | `Vf6`, the per-state update (and the second one it hands over to) |
  | `ikumi.cpp` | `0x6a59c0`–`0x6be9bf` | all | `CIkumi`; an unused destructor |
  | `exnanase_vf6.cpp` | `0x6be9c0`–`0x6cfbaf` | all | `Vf6`, the per-state update |
  | `exnanase.cpp` | `0x6cfbb0`–`0x6d93ef` | all | `CEXNanase` |
  | `ayu_vf6.cpp` | `0x6d93f0`–`0x6e812f` | all | `Vf6`, the per-state update |
  | `ayu.cpp` | `0x6e8130`–`0x6f2f1f` | all | `CAyu` |
  | `akane_vf6.cpp` | `0x6f2f20`–`0x7039cf` | all | `Vf6`, the per-state update |
  | `akane.cpp` | `0x7039d0`–`0x7124ff` | all | `CAkane` |
  | `akiko_vf6.cpp` | `0x712500`–`0x72199f` | all | `Vf6`, the per-state update |
  | `akiko.cpp` | `0x7219a0`–`0x73070f` | all | `CAkiko` |
  | `nayukib_vf6.cpp` | `0x730710`–`0x73e78f` | all | `Vf6`, the per-state update |
  | `nayukib.cpp` | `0x73e790`–`0x750d2f` | all | `CNayukiB` |
  | `bg01.cpp` | `0x750d30`–`0x751a3f` | all | `CAnimBg`, the animated backgrounds' base (frames and `.pat` animations), and `CBg01`; inline `CAnimBg` constructor |
  | `bg10.cpp`, `bg12.cpp`, `bg16.cpp` | `0x751a40`–`0x75325f` | all | `CBg10`, `CBg12`, `CBg16` |
  | `scene1.cpp` | `0x753260`–`0x759f2f` | all | Scene 1, character and stage select; inline `CScene` constructor and palette fades |
  | `scene6.cpp` | `0x759f30`–`0x75db6f` | all | Scene 6, the config menu |
  | `scene3_draw.cpp` | `0x75db70`–`0x76339f` | all | The drawing helpers scene 3's `Draw` calls: digits, gauges, the fight's overlay |
  | `scene3.cpp` | `0x7633a0`–`0x76c6ef` | all | Scene 3, the fight: collisions, camera, gauges, replay recording and playback |
  | `scene2.cpp` | `0x76c6f0`–`0x76e47f` | all | Scene 2, setting up a match: random picks, backgrounds, loading |
  | `scene8.cpp` | `0x76e480`–`0x7712ef` | all | Scene 8, the replay browser; two uncalled functions |
  | `scene5.cpp` | `0x7712f0`–`0x7758af` | all | Scene 5, the result screen; `pow(int, int)` from `<math.h>` |
  | `scene7.cpp` | `0x7758b0`–`0x775d5f` | all | Scene 7, the staff roll |
  | `scene0.cpp` | `0x775d60`–`0x77697d` | all | Scene 0, the title screen; two uncalled functions |

  The boundaries come from where inline functions are emitted and from `.rdata`, where
  each object's contributions follow one another: first its string literals (one
  section, made before any code), then its floating-point constants and vtables in the
  order its functions first use them, minus those an earlier object already supplied.
  Each character class is two objects: the constructor copies the character's folder
  name (`"shiori"`, `"sayuri"`, ...) into `CPlayer`'s name field, and that string comes
  *after* `Vf6`'s constants, so `Vf6` (which precedes the constructor) was compiled
  separately. `CScene3`'s drawing helpers before its constructor are split off the same
  way. The characters run in reverse alphabetical order.
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
- **The link.** **Observed:** `make check` rebuilds a byte-identical `efz.exe`. What
  it took:
  - **`/debug /incremental:no`, objects in address order.** `/debug` makes `/opt:noref`
    the default, which keeps the CRT functions nothing calls; with `/opt:ref` the CRT
    part was 0x5780 bytes short. `/opt:icf` would fold identical functions. `/MT`
    (asking for `libcmt`) doesn't change the game code.
  - **`winmm.lib` first.** The import directory lists the DLLs in the order their
    libraries are searched, and the thunks within a DLL follow from that too.
  - **The PDB at `D:\nonotaro\works\EFZ\EFZ.pdb`**, made afresh so its age is 1. The
    path is in the RSDS record and its length shifts the rest of `.rdata`.
  - **The import libraries** listed under *Toolchain*: their hints are in the hint/name
    table.
  - **The icon**, `efz.exe`'s only resource: RT_ICON 1 (32×32, 256 colours) and
    RT_GROUP_ICON 101, language 0x411, compiled by the February 2003 Platform SDK's
    `rc.exe` and `cvtres.exe` 7.10.3052. `tools/icon.py` takes it from the original.
  - **`.bss` order.** Globals without an initialiser are laid out in a fixed order of
    their names (a hash, like stack locals; `tools/stackorder.py --globals`), then the
    zero-initialised ones in declaration order, then objects with constructors, again
    by name. `main.cpp`'s scalars are zero-initialised, and `CInput`'s global is
    `g_inputDev` because `g_input` would come before `g_graphics`. `input.cpp` has 16
    bytes after `g_enumInput` that no code uses, and `0x7b1290` is `scene3.cpp`'s
    `g_fkeyHeld`.
  - **The Rich header** lists each tool in reverse order of first use, the linker last.
    Its key is the stub's length plus each stub byte rotated left by its offset (with
    `e_lfanew` taken as 0) plus each entry's ID rotated left by its count. `link.exe`
    reserves `0x20 + 8 × (entries + (key >> 5) % 3)` bytes for it, so the counts decide
    where the PE header starts.
  - **What the build can't reproduce** is set by `tools/postlink.py`: the timestamp,
    the PDB's GUID, and the Rich header's count of 152 Standard Edition objects (the
    source has 71), which also moves the PE header from `0x108` to `0x100`.

## Imports

DirectX 7-era APIs: `DirectDrawCreate`, `DirectInputCreateEx`, `DirectSoundCreate`
(by ordinal 1), plus WINMM (`timeBeginPeriod`/`timeGetTime`, `mmio*` for WAV), USER32
window/message functions, and one GDI32 call. 115 imported functions in total.

## Code layout (`tools/inventory.py`)

| Region | Range | Functions | Bytes |
|---|---|---|---|
| Game | `0x401000`–`0x77697e` | 630 | 3,627,390 |
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
  - **23 vtables have 13 slots each:** `CPlayer`'s at `0x787bcc` (slots 1–8 pure) and
    22 character classes (24 character folders; variants such as `nayukib` may share a
    class, **inferred**). Characters keep `CPlayer`'s slot 11 (`0x410b70`) and override
    the others.
  - **13 smaller vtables (2–6 slots)** are probably projectile, effect and system objects (**inferred**).
- **Functions are very large:** median ~320 bytes, but the biggest are 70–118 KB each.
  These are per-character virtual methods. Each is probably a large state machine over
  move states (**inferred**). Two of them, `0x5b2d10` and `0x5c8580`, are exactly 88,176
  bytes, which suggests copy-and-paste or a shared macro between related characters.
- **There are 97 switch jump tables** in total. **Observed:** the tables sit inside their
  functions, after the code, and can throw a linear disassembly out of step so that the
  next function's prologue is missed. `tools/inventory.py` also scans the raw bytes for
  16-aligned `push ebp; mov ebp,esp`, which found 8 functions hidden that way (among
  them Shiori's constructor at `0x422d70`).
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
  sizes are listed in `src/efz.h`. The scenes are 0 title, 1 character and stage select,
  2 match setup, 3 the fight, 5 results, 6 config, 7 staff roll and 8 replays.
- **Stage backgrounds:** stages 01, 10, 12 and 16 have an animated background object
  (`CAnimBg`), which scene 2 creates and keeps at `CGame+0x137c`. The fight draws it
  behind and in front of the players through its second virtual method.

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
  (**inferred** layout beyond that). In memory each pattern frame is 0xc8 bytes:
  five `RECT`s at `+0x00` and four at `+0x50` (probably hurt and attack boxes, going by
  how the fight's collision checks use them), one more at `+0x90`, then flags
  (`+0xaa`, `+0xb0`) and other shorts, floats and chars up to `+0xc6` (`PatternFrame` in
  `src/efz.h`).
- **Animated backgrounds:** `system\bg\bgNN\MMM.dat` frames (or `.bmp`) and a
  `bgNN.pat` animation table in the effect `.pat` format.

## Not yet established

- **The stack-order hash function.** It's measured empirically for now; recovering it
  from `c1xx.dll` would let tools predict layouts without compiling.

- **81 of the 152 game objects left no trace.** Everything in the image is accounted
  for by 71 objects (see *Matched objects*). The others contributed no code, data or
  constants, so nothing shows what they were: empty files, files whose code was
  `#if`'d out, or splits of the 71 along lines the layout can't show (a file without
  strings of its own leaves no seam in `.rdata`). `Vf6` and `Unk47c130` in
  `nanase_vf6.cpp` (likewise Ikumi's) may have been two files, for one.
- **Some compiler flags are unconfirmed.** `/Od /GS` without `/EHsc` is settled by
  `WinMain`. `/Zp`, `/J` and `/GR` still need a function that depends on them.
- **The character `.pat` record layout** is decoded only as far as the frame boxes.
