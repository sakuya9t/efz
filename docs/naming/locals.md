# Naming notes, 3 November 2026: locals and parameters

The locals and parameters got their names on 3 November 2026 (see
[../readability.md](../readability.md)). These notes hold the conventions the names
follow, and what reading every function for them turned up. Line numbers are those of
that day's source.

## Conventions

The 24 character classes repeat a few functions shape for shape, and those shapes hold
nine in ten of the lifter's names. The same thing has the same name everywhere:

| Where | Names |
|---|---|
| `UpdatePattern`, `UpdateObjects` | `duration` (ticks the current frame lasts), `frameCount` (frames in the animation), `effect` (the `EffectDesc` given to `CreateEffect` or `SpawnObject`), `slot` (the object being updated, an index into `m_objects`) |
| `ReadCommand` | `pos` (the entry of `m_inputHistory` read, oldest first), `input` (its `kInput` bits), `step` (how much of the motion has been read) |
| `CpuInput` | `dx` (how far the opponent is in front), `dy` (how far above or below) |
| Drawing | `sprite` (an `EffectFrame`), `src` and `dst` (the rectangles of a `Blit`) |
| Constructors | a player's `opponent, game, graphics, input, sound, side`; a scene's `hwnd, player1Ref, player2Ref, game, graphics, input, sound`: the members they fill |
| The fight's collisions | `attacker`, `defender`, `attackerFrame`, `defenderFrame`, `attackRects`, `hurtRects`, `overlaps`, `contact` (where the touching boxes overlap: the hit spark goes at its centre) |
| Fades | `frameStart`, and `shortFrame`: 1 every other frame, which waits 15 ms instead of 16, so the fades run at about 64.5 frames a second |
| Loops | `i`, `j` for counters; `side` for the two players |

`efz.h`'s declarations take the parameter names of their definitions. A few names in
`graphics.cpp`'s `BuildBlendTables` (`jb`, `sr3`, `row08`) were picked for the
original's stack layout and kept.

## Bugs and oddities of the original

- `CPlayer::DealDamage` (player.cpp:628-630): when the proration goes above 10000, it is
  multiplied by the move's factor a second time instead of being clamped. A factor that
  raises it (above 1000) applies twice.
- `CPlayer::LoadSprites` (player.cpp:836-841): a sprite that fails to load shows its
  number in a message box, and the offset doesn't move past it, so every later sprite is
  read from the same bytes.
- `CScene3::ResolveObjectHitsObject` (scene3.cpp:1838): when the struck object's frame is
  counter-hittable, `*targetFrame = ...` copies the owner's current frame over the
  object's frame in the owner's pattern table, for the rest of the match.
  `ResolvePlayerHitsObject` does the same to a copy on the stack.
- `CScene3::ResolvePlayerAttack` (scene3.cpp:1117-1118): a parry stores
  `m_attackResult = 2` and at once `= 6`; the first store does nothing.
- `CScene3::DrawComboCount` (scene3_draw.cpp:428-432): `if (hits > 9)` has two identical
  branches; two-digit counts were perhaps meant to sit elsewhere.
- The character select's stage roulette (scene1.cpp:353-375) runs inside the loop over
  both players, and both are in that state, so its timer and the stage step twice a
  frame.
- `CScene5::Enter` (scene5.cpp:425-427): the loop over the winner's `m_rivals` has no
  `break`, so the last matching entry picks the win picture.
- The animated backgrounds' destructors never run: scenes 3 and 5 free the background as
  a `char*` (scene3.cpp:98, :132, scene5.cpp:62), and `~CGame` through a `CAnimBg*`
  without a virtual destructor (game.cpp:88). Each stage with one leaks its surfaces,
  objects and animations.
- `CBg12::Update` (bg12.cpp:65-74): pattern 0 has no `break` and falls into pattern 1, so
  that layer moves 0.75 pixels a frame, not 0.5.
- `CBg16::Update` (bg16.cpp:84-85): pattern 3 clamps `x` at 947 where the others wrap
  around, so that layer stops after about 7 seconds.
- The backgrounds' object patterns (0-3) had been named as players' actions (`case
  kStand:`); they are plain numbers again, and `tools/constants.py` leaves the
  background classes alone.
