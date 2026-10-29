# Backward compatibility

The modern fork has to play the same game as the original 4.02 `efz.exe`. This document
records how that is tested (decided 28 October 2026), what the original's replays can and
cannot reproduce, and the rules a change has to follow so the test keeps working.

Statements about the game are **observed** (read from the matched source) or **inferred**.

## Decisions

- **The test is a replay.** A replay played back in the fork must give the same
  character status, frame by frame, as the same replay played back in the original. If
  P1 takes a heavy attack at frame 144 and loses 432 HP, and P2 takes a full combo at
  frame 3400 and loses 5529 HP in all, the fork shows the same frames and the same
  numbers.
- **Compare the characters' status, not visual effects.** What is compared is each
  player's state on every frame (see "Status" below). Particles, feathers and other
  effects are left out.
- **The per-frame status is the comparison; the events are the report.** A position
  that drifts by 0.001 changes no hit until one whiffs many frames later, so the first
  frame whose status differs is where the bug is. The event list (hits, damage, combo
  totals) is printed around that frame for reading.
- A change that touches the simulation sits behind a negotiated ruleset, as netplay with
  EfzRevival 1.02h already requires. With the ruleset off, the replay test must pass
  unchanged.

## The replay format

**Observed.** `replay\dataN-M.rep` (N, M = 1-9, 81 slots, `src/scene8.cpp`) is a stream
of 16-bit words. It has no frame markers, checksum, random seed or settings: the game
reads the words back strictly in the order it wrote them.

| Part | Words | Where |
|---|---|---|
| Header | P1 character, P2 character, `0x68`, stage, P1 palette, P2 palette | written `src/scene3.cpp:677-683`, read `src/scene2.cpp:126-137` |
| Each fight frame, not while paused | Two values the F4/F5 keys set; the second is the HP the players are reset to (`src/player.cpp:326`) | `CScene3::Vf2`, `src/scene3.cpp:592-608` |
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
| Ayu's dash feathers (`0x191`, `0x192`) on 66, 44 and their air versions (states `0xa3`-`0xa6`) | Plain `rand()` (`src/ayu_vf6.cpp:2157-2373`, `src/ayu.cpp:1562-1605`) | Visual only; left out |
| The burst of objects `0x1f1`/`0x1f2` every character spawns from its object `0x1f0` (e.g. `src/kano.cpp:3784`) | Plain `rand()` for their lifetimes and speeds (e.g. `src/nayuki.cpp:2425-2460`) | **Inferred** visual; left out |
| The game's effects | Plain `rand()` (`src/effect.cpp`) | Visual; left out |
| The CPU's random guard (`src/player.cpp:551`) | Plain `rand()` | Never runs in a recorded fight: replays are recorded from the title menu's replay item, which makes both players human (`src/scene0.cpp:132-133`) |
| `key.ini` bytes `0x21`-`0x26` (read into `CGame`, `src/game.cpp:37-43`) | Not stored in the replay | Tests run with one fixed `key.ini` |
| Uninitialised variables | Whatever memory held | See the open questions |
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
  x87, or another FPU precision can flip the truncation and change the HP by one.
- **A change that isn't meant to change the game passes the replay test unchanged.**
  This covers SDL3, widescreen, input rebinding and the like.

## Status

What the test compares for each player on each frame. Offsets are in `CPlayer`.

| Field | Member and offset | Notes |
|---|---|---|
| HP | `m_hp`, `+0x108` | 9999 full (`src/player.cpp:216`) |
| HP when the current combo began | `m_comboStartHp`, `+0x10c` | `src/player.cpp:624` |
| The combo's damage so far | `m_comboDamage`, `+0x100` | `src/player.cpp:635` |
| Hits in the current combo | `m_comboHits`, `+0x174` | `src/player.cpp:632` |
| Position | `x`, `y`, `+0x20`, `+0x28` | Doubles; y is negative in the air. Compared bit for bit |
| Action | `pattern`, `+0x8` | e.g. Ayu's forward dash is `0xa3` |
| Gauge | `m_gauge`, `+0x148` | A level per 1000, 3000 full: moves test `>= 0x3e8`, `0x7d0` and `0xbb8` |

The list grows as more fields are identified. The replay word offset is logged with
each frame too: if the fork and the original read different words first, the bug is in
what the fork consumes; if the words agree and the status differs, it is game logic.

## Open questions

- Does the original play each replay the same way every time? Uninitialised variables
  (EfzRevival fixes some) could make it vary. Playing every test replay several times on
  the original answers it, and has to come before trusting any comparison.
- Feathers share the 64-slot object table with projectiles. When it is full the oldest
  object stops being updated (`CPlayer::Unk412f10`, `src/playerobj.cpp:53`), so a
  random number of feathers could drop a projectile in one playback only. Whether Ayu
  can reach 64 objects depends on feather lifetimes in `ayu.pat`.
- Which of `key.ini` bytes `0x21`-`0x26` change the fight.
- EfzRevival's replays are a format of their own (it replaces `CReplayFile`'s methods;
  see [revival.md](revival.md)). Playing them is later work.
