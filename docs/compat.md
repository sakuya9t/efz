# Backward compatibility

The modern fork has to play the same game as the original 4.02 `efz.exe`. This document
records how that is tested (decided 28 October 2026; the whole game state and a fixed
reference since 31 October 2026), what the original's replays can and cannot reproduce,
and the rules a change has to follow so the test keeps working.

Statements about the game are **observed** (read from the matched source) or **inferred**.

## Decisions

- **The test is a suite of fights** (`tests/compat/suite.txt`): replays, and fights of
  the game's CPU (which never plays in a replay). Each must play in the fork exactly as
  it plays in the original, tick by tick. If P1 takes a heavy attack at frame 144 and
  loses 432 HP, and P2 takes a full combo at frame 3400 and loses 5529 HP in all, the
  fork shows the same frames and the same numbers.
- **The original is fixed: the git tag `compat-reference`.** Since 31 October 2026 the
  source no longer has to build `efz.exe` byte for byte: names, types and structure may
  change. The reference is the last source that did (`make check` there), built with
  the test's harness and run under wine; `tests/compat/reference.txt` holds the digest
  of its log for every case. A change passes when every case's log is the reference's,
  byte for byte.
- **Compare the whole game state.** After every tick the harness hashes both players
  (all of CPlayer and the character class, the 64 objects of each), the fight scene, the
  game object and the effects, pointers left out. Visual effects are compared too: they
  follow the same code and the same `rand()`, and a change to them is a change.
- **The status is the report.** The log also prints each player's action, frame,
  position, velocity, HP, combo and gauge. The first tick on which a block's hash
  differs is where the bug is; `tools/compat.py explain` names the members that differ.
- A change that touches the simulation sits behind a negotiated ruleset, as netplay with
  EfzRevival 1.02h already requires. With the ruleset off, the suite must pass
  unchanged.

## Running it

```sh
tools/native.sh                      # build/native/efz
tools/compat.py check                # every case in the native game (about 2 minutes, -j 16)
tools/compat.py check fuzz5- cpu-03  # some: by name, or a prefix ending in -
tools/compat.py --windows check      # build/windows/efz.exe, under 64-bit wine
tools/compat.py check --exe build/trace/efz.exe   # any 32-bit build with the harness, under wine
tools/compat.py explain cpu-03       # where and how a failing case parts from the reference
tools/compat.py coverage             # what the suite runs: lines of src/, actions per character
```

`EFZ_DIR` names the original game's folder (its data; the suite has none of it). Work
folders, wine prefixes and the reference's logs are in `$EFZ_COMPAT` (default
`~/.local/share/efz-decomp/compat2`). A check needs only the data and the build to test;
`explain` also runs the reference (below), so it needs the toolchain's docker images.

## The suite

`tests/compat/suite.txt`, one case per line:

| Kind | Cases | What |
|---|---|---|
| `NAME replay` | 204 | `tests/compat/replays/NAME.rep` played back, both players human. 154 random fights from before the readable source (114 the original recorded, 40 the native game), 3,000 to 6,000 ticks; 50 the reference recorded with the harness's newer scripted input (more motions: supers, dashes, double motions), 4,000 ticks |
| `NAME cpu SPEC TICKS` | 50 | A fight nothing records: characters, stage, palettes and seed (`P1:P2:STAGE:PAL1:PAL2:SEED:C1:C2`), each side the game's CPU (`1`) or the harness's scripted input (`0`). `cpu-NN`: character NN's CPU against another CPU; `bot-NN`: against scripted input |

In all 254 cases, 1,223,436 ticks (about 5.3 hours of fighting). Adding cases:

```sh
tools/compat.py add-fuzz 20 fuzz6- --seed 6 --ticks 4000   # the reference records 20 replays
tools/compat.py add-cpu cpu-ayu-mai 1:2:5:0:0:77:1:1 6000   # a CPU fight
tools/compat.py reference --update fuzz6- cpu-ayu-mai        # their digests
```

then commit the new replays, `suite.txt` and `reference.txt`.

## The reference

`tools/compat.py build-reference` extracts the tag `compat-reference` and runs
`make trace check` in it: `make check` proves its `efz.exe` is the original byte for
byte, and `build/reference/efz.exe` is that code with the harness (`src/trace.cpp`,
hooked into `WinMain`, `CScene3::Update` and `CInput::GetInput`; every other function
is the original's code). `tools/compat.py reference` plays every case in it under wine
(16 at a time, about 4 minutes) and checks each log's digest against `reference.txt`.

To make two runs of the original comparable on every byte, the harness changes four
things in the reference, and the native game does the same:

| | The original | The reference and the native game | Why it is the same game |
|---|---|---|---|
| Memory from `new` | The heap's garbage | Zeroed (the native game's arena always was) | Initialised members are the same; an uninitialised one, `CPlayer::m_hitsLeft`, decided a few hits by the garbage (see "Answered"): zero is one of the original's outcomes |
| `sin`, `cos`, `atan2` | The CPU's `fsin`, `fcos`, `fpatan`, whose last bits differ between CPUs | Correctly rounded to the x87's 64 bits: `port/x87.cpp`, which MinGW builds into the reference (`tools/x87ref.cpp`) | One of the CPUs' results; the same on every machine |
| `rand()` | Seeded from the clock | Seeded with the case's seed (replays: 1) | Only effects and the CPU use it (see below) |
| The rectangle a throw's hit spark is placed at (`CScene3::Unk7679b0`, `Unk767f60`, `Unk7697d0`) | Read from stack memory the code never set | Zeroed | Only the spark's position |

While a replay plays, the harness also has the controls read as untouched, so what the
menus and `CGame`'s polling see is the same everywhere.

## What is compared

The log (`src/trace.cpp`) starts with a line naming its format; then each line is one
tick: the tick, the replay's read position, each player's status (below), and an
FNV-1a hash of each block of state:

| Block | What |
|---|---|
| `p1`, `p2` | The player's `CPlayer` (`0x3138` bytes), without its object table |
| `p1obj`, `p2obj` | Its 64 objects (`PlayerObject`, `0x98` bytes each) |
| `p1char`, `p2char` | The character class's own members (from `CPlayer`'s end to its size) |
| `scene` | The fight scene's (`CScene3`) members |
| `game` | `CGame`, without the effects |
| `fx` | The effects' ring buffer: 640 `Effect`s and their bookkeeping |

Left out: pointers (the vtable, `m_game`, sprite tables..., Nanase's and Ikumi's second
pattern tables), which differ between builds; `CScene3`'s frames-per-second count and
`lastMessage`, which follow the clock and the window system. Everything else is
compared bit for bit, padding included. The hashes rely on the original's layout,
which the native build keeps (`port/layout.cpp`): a change of layout needs the harness
to hash the members it moved by name.

With `EFZ_TRACE_DUMP` the harness writes every block's bytes, which `explain` diffs
between the reference and the build and maps to members through `tools/members.py
fields` (needs the libclang Python package):

```
cpu-01: FAILED
  tick 2015: first difference
    tick 2015: state differs in fx
  tick 2015, block fx: 2 bytes differ
    effect 258: reference active 1 type 0x38 frame 0 timer 0 x 41.0 y -63.0 ...
    effect 258: build     active 1 type 0x38 frame 0 timer 0 x 57.0 y -61.0 ...
```

## Coverage

`tools/compat.py coverage` builds the native game with gcov (`tools/native.sh
coverage`), plays every case in it, and prints for each source file the share of its
lines the suite runs and how many of its functions it never runs, then the actions each
character reached. `build/coverage/gcov/*.gcov` has each line with its count. A change
to code the suite never runs is not tested by it: add a case that runs it.

## The replay format

**Observed.** `replay\dataN-M.rep` (N, M = 1-9, 81 slots, `src/scene8.cpp`) is a stream
of 16-bit words. It has no frame markers, checksum, random seed or settings: the game
reads the words back strictly in the order it wrote them.

| Part | Words | Where |
|---|---|---|
| Header | P1 character, P2 character, `0x68`, stage, P1 palette, P2 palette | written `src/scene3.cpp:680-686`, read `src/scene2.cpp:126-137` |
| Each fight frame, not while paused | Two values the F4/F5 keys set; the second is the HP the players are reset to (`src/player.cpp:326`) | `CScene3::Vf2`, `src/scene3.cpp:595-611` |
| Each player's input | One word: bits `1` right, `2` left, `4` down, `8` up, `0x10`-`0x80` A-D | `src/player.cpp:1027-1029`, decoded at `:1037-1084` |
| Each random draw through `CPlayer::Random` (`0x4108a0`) | The `rand()` value when recording; on playback the word replaces it | `src/player.cpp:667-680` |

A third header word of 100 or less is the stage and means the replay has no per-frame
F4/F5 words (the game then uses 1000 and 9999). **Inferred:** these are replays from
earlier versions.

## What a replay reproduces

- **Randomness that matters to play.** It goes through `CPlayer::Random`, so it is
  recorded. Ayu's LV4 (A, neutral, A, 4, B, C with the gauge full and HP below 3333;
  state `0x13e`, `src/ayu.cpp:124` and `:449-479`) is the clearest case. During the
  move, whether each attacking feather spawns, its type (fast `0x1a0` or slow `0x1a1`),
  its height, speed, rise and starting animation frame are all drawn through the helper
  (`src/ayu_vf6.cpp:5021-5033`, `src/ayu.cpp:1868-1915`).
- **Guarding.** A human player's guard comes from input: holding away from the opponent,
  standing or crouching, against the attack's high/low flags (`src/player.cpp:563-570`).

## What it does not reproduce

| What | Why | How the test handles it |
|---|---|---|
| Ayu's dash feathers (`0x191`, `0x192`) on 66, 44 and their air versions (states `0xa3`-`0xa6`) | Plain `rand()` (`src/ayu_vf6.cpp:2157-2373`, `src/ayu.cpp:1562-1605`) | Visual only; compared, with `rand()` seeded the same in both games |
| The burst of objects `0x1f1`/`0x1f2` every character spawns from its object `0x1f0` (e.g. `src/kano.cpp:3784`) | Plain `rand()` for their lifetimes and speeds (e.g. `src/nayuki.cpp:2425-2460`) | **Inferred** visual; compared, as above |
| The game's effects | Plain `rand()` (`src/effect.cpp`) | Visual; compared, as above |
| The CPU (`CpuInput`, and its random guard, `src/player.cpp:551`) | Plain `rand()` and `CPlayer::Random`, which records nothing a CPU's input could be replayed from | Never runs in a recorded fight: replays are recorded from the title menu's replay item, which makes both players human (`src/scene0.cpp:132-133`). The suite's `cpu` cases play it from a seed instead |
| `key.ini` bytes `0x21`-`0x26` (read into `CGame`, `src/game.cpp:37-43`) | Not stored in the replay | Tests run with one fixed `key.ini` |
| Uninitialised variables | Whatever memory held | Zeroed in the reference and the native game ("The reference"); see "Answered": `CPlayer::m_hitsLeft` decides some hits |
| Menus, character select, results | Only the fight is recorded | Out of scope |

## Rules for changes in the fork

- **Keep every helper call.** The same number of calls to `CPlayer::Random`, in the
  same order, at the same points. One call more or less shifts every later word, and the
  replay goes off the rails from that frame.
- **Random numbers that can affect a hit go through the helper.** Plain `rand()` is only
  for visuals. The original already works this way: Ayu's attacking feathers use the
  helper and her dash feathers use `rand()`.
- **Keep the floating point.** Damage is `(int)(base × three double factors)`
  (`src/player.cpp:626`) and positions are doubles. A different compiler, SSE instead of
  x87, or another FPU precision can flip the truncation and change the HP by one. In
  the shared sources that means: floats through `F32` (computed in double, rounded when
  stored), `F32CAST` for a cast to float inside an expression (the original drops it),
  and `sin`, `cos` and `atan2` only through `x87.h`'s versions in the native build
  ([native.md](native.md)).
- **Keep the order of side effects.** The original evaluates a call's arguments right
  to left; a call with two random draws as arguments needs them drawn in that order
  natively (two do, `#ifdef EFZ_NATIVE`).
- **A change that isn't meant to change the game passes the suite unchanged**
  (`tools/compat.py check`). This covers renames and other readability work, SDL3,
  widescreen, input rebinding and the like. Code the suite doesn't run (`coverage`)
  isn't tested by it: add a case that does before changing it.

## The status line

What the log prints for each player on each tick, besides the hashes. Offsets are in
`CPlayer`.

| Field | Member and offset | Notes |
|---|---|---|
| HP | `m_hp`, `+0x108` | 9999 full (`src/player.cpp:216`) |
| HP when the current combo began | `m_comboStartHp`, `+0x10c` | `src/player.cpp:624` |
| The combo's damage so far | `m_comboDamage`, `+0x100` | `src/player.cpp:635`. **Observed:** uninitialised until a combo starts: garbage, different on every run of the original. Compared while the hit count is above 0 |
| Hits in the current combo | `m_comboHits`, `+0x174` | `src/player.cpp:632` |
| Position | `x`, `y`, `+0x20`, `+0x28` | Doubles; y is negative in the air. Compared bit for bit |
| Velocity | `vx`, `vy`, `+0x30`, `+0x38` | Doubles, compared bit for bit |
| Frame of the action | `frame`, `+0xa` | |
| Facing | `facing`, `+0x50` | 1 or -1 |
| Action | `pattern`, `+0x8` | e.g. Ayu's forward dash is `0xa3` |
| Gauge | `m_gauge`, `+0x148` | A level per 1000, 3000 full: moves test `>= 0x3e8`, `0x7d0` and `0xbb8` |

The replay word offset is logged with each tick too: if the fork and the original read
different words first, the bug is in what the fork consumes; if the words agree and
the state differs, it is game logic.

## Answered

- **Does the original play each replay the same way every time?** Nearly always, not
  always. **Observed:** of 154 replays (114 it recorded, 40 the native game recorded;
  [native.md](native.md)), it played 5 differently from run to run: an attack that
  hits in some runs misses in others, the rest of the match then parting. The cause is
  `CPlayer::m_hitsLeft` (`+0x16c`), the hits the current attack can still land: each
  attack's code sets it during the attack and each hit takes one off, but nothing sets
  it before a player's first attack, and the hit test (`CScene3::Unk767f60`,
  `src/scene3.cpp:1052`) requires it above 0. The frame an attack's box first appears
  is tested once before its code sets the field (Mizuka's state `0xc8` sets it on
  frame 2, at the update after the one that starts that frame; Kaori's `0xcd` on frame
  3). So a player's first attack hits there when the heap's garbage is positive as a
  short. Memory dumps of a run that hits and one that misses show it on all five: the
  attacker's field holds 27022, 20255, 19239, 19272 and 7196 in the one and -23847,
  -27669, -6235, -17603 and -13365 in the other. The native game's memory starts
  zeroed, so such an attack never hits there, which is one of the original's two
  outcomes; on all 5 the native game plays exactly as one of the original's runs.
  EfzRevival 1.02h doesn't initialise the field either (it only reads it to draw
  hitboxes), so two players on it could part the same way. The reference zeroes the
  heap as the native game does, so the suite has one outcome.
- **Is the original the same on every CPU?** No, though rarely does it show. `sin`,
  `cos` and `atan2` are the x87's `fsin`, `fcos` and `fpatan`, whose last bits are
  each CPU's own: this AMD Zen 4's differ from the correctly rounded value on a third
  of inputs, which changes a velocity set from an angle (`ObjBase::SetVelocity`) by one
  unit in the last place about once in a thousand calls. Intel's microcode differs again. The native game uses the
  correctly rounded value on every machine; `EFZ_HOST_X87` builds it with the
  machine's own instead ([native.md](native.md)). Effects show it often: with them in
  the comparison, 3 of the first 3 cases parted on this machine until the reference
  took the correctly rounded values too.
- **Does `<math.h>`'s float `sin` round to float?** No. Visual C++ .NET 2003 drops the
  cast in its inline `sinf`, so `sin((float)rand()) * 6.0f` (effect `0x2e`) is the
  64-bit result times 6, rounded to double. `fabs` of a float expression does round: its
  argument is passed as a float (effect `0x2f`, `FABSF` in `src/efz.h`).

## Open questions

- Feathers share the 64-slot object table with projectiles. When it is full the oldest
  object stops being updated (`CPlayer::Unk412f10`, `src/playerobj.cpp:53`), so a
  random number of feathers could drop a projectile in one playback only. Whether Ayu
  can reach 64 objects depends on feather lifetimes in `ayu.pat`.
- Which of `key.ini` bytes `0x21`-`0x26` change the fight.
- EfzRevival's replays are a format of their own (it replaces `CReplayFile`'s methods;
  see [revival.md](revival.md)). Playing them is later work.
