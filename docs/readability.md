# Readable source

The lifter (`tools/lift.py`) recovered every function as code that compiles to the
original's bytes, but it wrote every field access as a cast of a pointer plus an offset:

```cpp
*(short*)((char*)this + 0x2b00) = -0x1d;
l4 = *(short*)(*(char**)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc);
if (*(double*)((char*)this + 0x20) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
```

The source now reads them through the members `src/efz.h` declares at those offsets:

```cpp
m_pointY[4] = -0x1d;    // Akane's constructor: the fifth point on her body
l4 = (short)anims[pattern].frames[frame].duration;
if (x < (*m_opponent)->x) {
```

and `make check` still builds a byte-identical `efz.exe`. This document records how
that was done, which readability changes keep the bytes and which don't (all measured
with this compiler), and what is left.

**Since 31 October 2026 the bytes no longer bind the source.** The tag
`compat-reference` keeps the last source that builds the identical exe; the
compatibility suite ([compat.md](compat.md)) checks every later change against it,
comparing the whole game state tick by tick. The second round of names below was made
that way. "What keeps the bytes" and "What changes them" now describe the tag.

## Names, 31 October 2026

Eight analyses read every use of what was still unknown (their notes:
[naming/](naming/README.md)), and the names went in with `tools/members.py rename` and
`tools/constants.py`:

| | Before | After |
|---|---|---|
| `unk<offset>` member references | 30,752 | 413 (members only ever zeroed, never read, or padding) |
| `Unk<address>` method references | 1,055 | 2 (an empty method nothing calls) |
| Action numbers compared with or assigned to a `pattern` | 11,073 | 449 (mostly another character's action, or a range of a character's own) |
| Action numbers indexing `m_patterns`/`anims`, and `case`s of the action switches | 4,439 | 137 |
| Command numbers compared with or assigned to `m_command` | 1,950 | 55 (commands no ReadCommand produces) |
| Flag masks on `flagsAA`/`flagsB0` | 1,128 | 2 |

So Akane's StartCommand went from

```cpp
if (m_command == 0x34 && (unk118 >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || unk120 > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & 8) > 0 && m_patterns[pattern].unk2 <= m_patterns[0xa7].unk0) {
    StartPattern();
    ClearBufferedPress();
    pattern = 0xa7;
    if (y < 0.0) {
        pattern = 0xab;
```

to

```cpp
if (m_command == kCmd22C && (m_rfGauge >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || m_rfBlue > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kInstantCharge].level) {
    StartPattern();
    ClearBufferedPress();
    pattern = kInstantCharge;
    if (y < 0.0) {
        pattern = kAirInstantCharge;
```

- **Members and methods**: 651 renames, 31,782 references: CPlayer's (`m_rfGauge`,
  `m_guardGauge`, `m_recoilGuardWindow`, `m_hitstop`, `m_freezeTime`...), the frame data
  (`PatternFrame::damage`, `chipDamage`, `proration`, `attackerHitstop`, `pushBox`...),
  every character's own (`m_helperState`, `m_poisonLevel`, `m_warmUp`...), the game's
  and the scenes' (`m_gameMode`, `m_roundsToWin`...), the effects', and the virtual slots
  left (`PreUpdate`, `HandleKeys`). `efz.h` comments each with what the code does with it.
- **Constants** (`tools/constants.txt`, declared in `efz.h` by `tools/constants.py
  declare`; 21,374 numbers in the code are now one of them):
  - 109 shared actions (`kStand`, `kHitAirLaunch`, `kGuardCrouchHeavy`, `kRecoilGuardAir`,
    `kInstantCharge`, the five objects every character has) and range bounds
    (`kFirstHitReaction`, `kFirstGuard`, `kFirstCharacterAction`), at namespace scope;
  - 2,405 characters' own actions, in each class, named in numpad notation where the
    move has an input (`k5A`, `kJump2C`, `k236B`, `kAir214C`, `k641236C`, `kLv4`), by
    what it is otherwise (`kThrowHit`, `kObjCrow`), `kUnused...` where no code can
    reach it (143);
  - the commands (`m_command`), decoded from each class's ReadCommand: shared where every
    character reads a number the same way (`kCmd236A`, `kCmd22C`, `kCmdDashLeft`),
    the class's own where not (`kCmd214214A` is 0x64 for Sayuri, 0x6e for the others;
    LV4 inputs such as `kCmdA5A6BC`);
  - the bits of `PatternFrame::flagsAA` (`kAttackGuardCrouch`, `kAttackThrow`,
    `kAttackUnblockable`...) and `flagsB0` (`kStateCancellable`, `kStateInvulnerable`,
    `kStateGuardPoint`...), and the 74 effect types (`kEffectGuardSpark`, `kEffectHitBurst`...).

The suite passed on every step, in the native build and in the original compiler's
build of the same source under wine (`tools/compat.py check --exe`).

### Naming now

Find what the code does with the thing, then:

```sh
# a member or method: lines "Class::old new"; virtual slots need every override
tools/members.py rename renames.txt
# a number: add a line to tools/constants.txt ("action CAyu 0x13e kLv4  # comment")
tools/constants.py declare tools/constants.txt   # efz.h's enums
tools/constants.py apply tools/constants.txt     # the numbers in src/*.cpp
tools/native.sh && tools/compat.py check         # the game is unchanged
```

`rename` follows clang's references, macro arguments included, and the harness's code
(`src/trace.cpp`); `port/` isn't parsed with the game's flags, so its few references
(`port/layout.cpp`'s offset checks) are edited by hand. `constants.py` replaces a
number only where clang shows what it is (see its docstring).

## Locals, numbers and file names, 3 November 2026

| | Before | After |
|---|---|---|
| References to the lifter's local and parameter names (`l4`, `x8`, `v2c`, `p1`) | 77,201 | none; `graphics.cpp` keeps a few names picked for the original's stack layout (`jb`, `sr3`, `row08`) |
| Hex literals in `src/*.cpp` | 32,425 | 4,153: the codes below |

So Akiko's ReadCommand went from

```cpp
x6 = 0;
v4 = m_inputPos + 0x5a;
for (; v4 < m_inputPos + 0xb4; v4++) {
    v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
    if ((v5 & 0x40) != 0 && x6 == 6) {
```

to

```cpp
step = 0;
pos = m_inputPos + (kInputHistoryLength - 90);
for (; pos < m_inputPos + kInputHistoryLength; pos++) {
    input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
    if ((input & kInputC) != 0 && step == 6) {
```

- **Locals and parameters** are named for what they hold. The functions the 24
  characters repeat shape for shape (UpdatePattern, UpdateObjects, ReadCommand,
  CpuInput, DrawGauge, the constructors) held nine in ten of the lifter's names and get
  the same names in every class; the rest were read function by function.
  [naming/locals.md](naming/locals.md) has the conventions, and the original's bugs
  found on the way. `efz.h`'s declarations take their definitions' parameter names.
  Each rename was scoped to its function and refused where the new name was already
  used there, so no local hides a member or a global.
- **Numbers that are quantities are decimal**: ticks, frames, positions, gauge, damage,
  odds (`Random(0, 100) < 20`), rectangles, and the sound, voice, music, stage, palette
  and character numbers, which the game turns into file names in decimal. **Codes stay
  hex**, as the docs and `tools/constants.txt` give them: actions (and object and
  effect types, which are actions), commands, the CPU's actions, key codes, sizes,
  config offsets, palette entries, bit operations, `case` labels, and values from
  0x10000 up; so do the platform files (`main`, `graphics`, `input`, `sound`, `file`,
  `config`, `trace`).
- **The input** has constants in `efz.h`: the bits of a tick (`kInputRight`...
  `kInputUp`, `kInputA`...`kInputD`, the masks `kInputDirections` and `kInputButtons`)
  and `kInputHistoryLength`. `m_inputPos` is where the next tick goes, so the oldest.
- **`<character>_vf6.cpp` is `<character>_states.cpp`**: the per-state update, named
  for what it holds rather than for its virtual slot.

None of it changes the code: the native game's Release build (MSVC 19.44) compiled to
the same `.text`, `.rdata` and `.data` after every step. With the original's compiler
the renamed locals do reorder stack frames (see below), which can only matter where
code reads a local before writing it; `tools/compat.py check --exe` checks that build.

## What was done

- **Members for every offset.** `efz.h` declares a member at each offset the code
  reaches: about 600 new ones in `CPlayer`, its 0x98-byte `PlayerObject` table, the 24
  character classes, the scenes, `CAnimBg` and its `BgObject`s, `CGame` and
  `Afterimages`. Where the meaning is known the member has a name (`m_hp`, `m_gauge`,
  `m_comboHits`, `m_opponent`, `ax`, `ay`, `m_inputHistory`, `m_view`...); elsewhere it
  is `unk<offset>`, its type the one the code reads it as.
- **Accesses rewritten.** `tools/members.py rewrite` parsed the sources with clang,
  followed each address through the declared classes (bases, nested structs, arrays,
  pointer members, pointer arithmetic on ints) and replaced about 186,000 accesses. No
  `*(T*)((char*)p + offset)` is left.
- **Pointers typed.** Parameters and locals that held pointers as `int` or `char*` are
  typed (`CPlayer::CanGuard(PatternFrame* p1, PatternFrame* p2)`, the character
  constructors' `CPlayer**`, `CGame*`..., `EffectFrame* v18`), so their accesses resolve
  too, and their callers lost their `(int)` casts.
- **Names.** `tools/members.py rename` renamed 54,000 references: CPlayer's members
  (`m_hp`, `m_gauge`, `m_attackResult`, `m_cpuAction`, `m_pointX`...) and helpers
  (`DealDamage`, `Random`, `ReadInput`, `LoadPatterns`, `FillBackground`...), the
  virtual slots `Vf0`-`Vf12` in all 25 classes (`StartPattern`, `UpdatePattern`,
  `SpawnObject`...), and members of CGame, CAnimBg, EffectDesc and the objects. Each
  name comes from what the code does with it; `efz.h` comments the evidence. Calls
  of CPlayer's non-virtual helpers lost the lifter's `CPlayer::` qualifier.

## What keeps the bytes

Measured by compiling both forms with `cl` 13.10 `/Od` and comparing, then by
`make check` on the whole game.

| Change | Code |
|---|---|
| `*(T*)((char*)p + off)` → `p->member`, for loads, stores, `++`, `+=`, address-of | same |
| `*(T*)((char*)this + i * 0x98 + off)` → `m_objects[i].field`; `(p4 << 4)` → `rects[p4]` | same |
| `*(int*)(p + 0x14) + i * 4` (a pointer read as an int) → `&surfaces[i]` | same |
| `*(short*)p` where the member is a `WORD` → `(short)member`, in a value | same |
| `((ObjBase*)((char*)this + 8))->AngleTo(...)` → `AngleTo(...)` (an inherited method) | same |
| `(&m_afterimages)->F()` → `m_afterimages.F()`; `&objs[i].pattern` → `&objs[i]` (first member) | same |
| A parameter's type, `int` → `PatternFrame*` (callers pass the pointer instead of `(int)`) | same |
| A local's type, `char*` → `EffectFrame*`, keeping its name: its slot stays | same |
| `*p1 = (CPlayer*)(int)new CAkane(...)` → `*p1 = new CAkane(...)` (an upcast to a base at offset 0) | same |
| `CPlayer::Random(...)` → `Random(...)` for a non-virtual method (a virtual one needs it) | same |
| Renaming a member, a method or a virtual slot (with all its overrides) | same: names are only in the PDB |
| Renaming an initialised global | same |
| A constant as an `enum` or `#define` instead of a literal | same |
| Comments, whitespace, line breaks | same (line numbers are only in the PDB) |

## What changes them

| Change | Why |
|---|---|
| Renaming a local variable | The compiler orders stack slots by a hash of their names. Renaming `l4` to `duration` in `CAkane::UpdatePattern` rewrote the whole function. `tools/stackorder.py` finds names that keep a layout |
| Renaming an uninitialised global | `.bss` is ordered by the names too (`stackorder.py --globals`); renaming `g_sound` moved it |
| `m += x` on a member of the other signedness than the original access | The old value is widened before the add: `movsx` becomes `movzx`, though the stored result is the same. Plain `=` and `++` don't care |
| `x = x + 1` → `x++` on a 16-bit member | `++` adds in 16 bits; `x + 1` widens to 32 |
| `x = x - y` → `x -= y` | The operands are evaluated in the other order. With a constant (`x = x + 0xa` → `x += 0xa`) they compiled alike |
| An upcast, `(ObjBase*)p`, even `(ObjBase*)this` | It tests the pointer for null first. A member access or an inherited method call doesn't |
| An inline helper function instead of repeated code | `/Od` doesn't inline: it becomes a call |
| `bool` instead of `BYTE` | It compiles differently: `b = k != 0` gained an instruction |
| A member's type (`char` for `BYTE`) where some use depends on it | Compares, widening and function arguments follow the type. Where every use stores it or has its own cast, retyping is free |
| A `double` in a class that had none, or a member that isn't naturally aligned | The class's alignment changes: a class that starts the vtable pointer then pads to 8 (why `ObjBase` sits at `CPlayer+8`), and `sizeof`, which `new` passes, rounds up |
| A byte array in a struct some function has as a local | `/GS` then guards that function with a cookie (see `PatternFrame` in `efz.h`) |
| Moving a function, or reordering a file's functions | The code is laid out in definition order |

So, as long as the bytes bound the source, locals kept the lifter's names (`l4`, `x8`,
`v2c`: a letter for where the slot is and its offset), because naming them meant
choosing names whose hashes keep the frame. They have names since 3 November 2026.

## The conventions in efz.h

- `unk<offset>` is a member whose meaning isn't known; the offset is in its class.
- A byte array named `unk<offset>` (or `data`, `unk`) is padding, unless it has a
  comment: then it is a real array whose purpose isn't known yet.
- `// +0x..` on a member is its offset, and `// SIZE: 0x..` above a class its size.
  `tools/members.py layout` checks both, and every `unk<offset>`, against clang's
  layout of the classes (the MSVC one).

## The tools

`tools/members.py` needs the `libclang` Python package (`pip install libclang`) and
the toolchain's headers. It parses the sources the way `cl` sees them (MSVC mode, the
PSDK and DirectX SDK headers through a case-insensitive copy of their folders in
`build/clang-include`).

```sh
tools/members.py scan --json scan.json   # accesses that still hit padding, by class and offset
tools/members.py rewrite [files]         # rewrite raw accesses into members, in place
tools/members.py check [files]           # the same as a diff
tools/members.py layout                  # check efz.h's offsets and sizes
tools/members.py rename renames.txt      # lines "Class::member newName" (members, methods)
make check                               # then: the exe must still be identical
```

To name something: find what the code does with it, add the evidence as a comment in
`efz.h`, rename it with `tools/members.py rename` (not a textual replace: `unk20` is a
different member in each class), and run `make check`. `rename` doesn't see into macro
bodies; `effect.cpp`'s are edited by hand.

The lifter still writes raw offsets. Lifting a function again (`tools/lift.py`,
`tools/objcheck.sh`) overwrites its readable source; run `tools/members.py rewrite`
on the file afterwards. `tools/lifttest.py` (relift every matched function and compare)
gives 503 matches, the same 44 failures in the hand-written platform files as at
v1.0.0 (and the same 9 functions it can't lift), and four new failures: CScene3's collision functions `WillRecoilCounter`, `ResolvePlayerAttack`,
`ResolveObjectAttack` and `ResolvePlayerHitsObject`, whose frames the lifter no longer recovers now that their
parameters and callees are typed. Their source matches; only relifting them fails.

## What is left

- Some numbers are codes without a name yet: other characters' actions, object and
  effect types the constants don't cover, palette entries.
- About 60 casts of a member's address remain where the code really reads it as
  another type (`*(RECT*)&...[8] = MakeRect(...)` in a char array of Scene8,
  `*(int*)&m_guardGauge = 0` on a float), and a few `(i << 4) + (char*)p` where the
  index is computed first. These can now become plain code.
- Some members are still `unk<offset>`: those the code only zeroes or never reads, and
  padding. Some actions too: another character's (the opponent's pattern compared with
  a number) and a few in the data no code enters.
- Arrays the original declared as runs of single members (`CScene1`'s hidden-stage
  flags, `CScene8::unk46e`, three arrays in one) can be declared as what they are.
