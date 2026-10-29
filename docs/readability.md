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
  typed (`CPlayer::Unk410050(PatternFrame* p1, PatternFrame* p2)`, the character
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

So the remaining unreadable parts are deliberate: locals keep the lifter's names (`l4`,
`x8`, `v2c`: a letter for where the slot is and its offset), because naming them means
choosing names whose hashes keep the frame.

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
v1.0.0 (and the same 9 functions it can't lift), and four new failures: CScene3's collision functions `Unk7679b0`, `Unk767f60`,
`Unk7697d0` and `Unk76bd40`, whose frames the lifter no longer recovers now that their
parameters and callees are typed. Their source matches; only relifting them fails.

## What is left

- About 60 casts of a member's address remain where the code really reads it as
  another type (`*(RECT*)&unk46e[8] = MakeRect(...)` in a char array of Scene8,
  `*(int*)&unk134 = 0` on a float), and a few `(i << 4) + (char*)p` where the index is
  computed first: `&p->boxes[i]` would load `p` first.
- Most members are still `unk<offset>`, most methods `Unk<address>`, and the pattern
  numbers (`pattern = 0xd`) are bare: naming them is reverse engineering, one at a
  time.
