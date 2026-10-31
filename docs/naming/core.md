# CORE agent notes (CPlayer and the shared vocabulary)

Method: every use of each member in src/ (HEAD 0bf6ea5), the 4.02 `.pat` files parsed
with LoadPatterns' layout scratch `coretools/pat.py` -> `pats.json`: every pattern's
level/cancelLevel and every frame's values and flags, all 24 characters), sprites rendered
from the `.dat` files with the character and `system\object.dat` palettes
(`coretools/spr.py`), the 24 ReadCommand state machines decoded by script
(`coretools/cmds.py`, `cmdsum.py`), and the shared UpdatePattern cases compared across
classes (`coretools/cases.py`). EFZ's own terms (Recoil Guard, guard gauge, RF/Reinforce
gauge, Instant Charge) are from the Mizuumi wiki's EFZ pages (wiki.gbl.gg) and match what
the code does.

Units: a *tick* is one simulation step. CScene3::Update runs `unk578` (3) ticks per drawn
frame, at about 64 drawn frames a second; .pat durations are multiplied by 3 at load. So
60 ticks = 20 frames. The comments in efz.h that say "frames" for these timers mean ticks.

## How the systems work (what the names stand for)

- **Hit resolution** (CScene3::Unk767f60, `ResolvePlayerAttack`), in order: attacker's
  result still 0 and hits left; defender's frame not invulnerable (flagsB0 0x20), not
  throw-protected against a throw, not in `CanAirRecover`, no `m_invulTime`. Then: parry
  frames (flagsB0 0x1000/0x800) -> both results 6; recoil guard (`m_recoilGuardWindow`
  >= 30, or `m_canRecoilCounter` from any state) -> 0xa8/0xa9/0xaa, attacker frozen 60
  ticks; guard point (flagsB0 0x200) -> chip only, no reaction; guard (`CanGuard`) ->
  0x96-0x9c with chip damage and guard gauge; else the hit: reaction by
  groundHitPattern/airHitPattern or by posture (flagsB0 1/2) and strength (flagsAA
  0x10/0x20/8), or armor (flagsB0 4 / m_armorTime) -> damage without reaction.
- **Juggles**: a hit sets `m_untechTime` = untechTime * proration * 0.8. In air hitstun it
  counts down (only once the guard gauge is empty); at 0 the player may air-recover
  (button + direction) *and can no longer be hit* (`CanAirRecover` blocks every check).
  flagsAA 0x400 (`m_noAirRecovery`) removes both until the next hit.
- **Guard gauge** (`m_guardGauge`, max 360): damage/30 per guarded hit; delays the untech
  countdown. An attacker who has some pays a guarded hit's cost from it first
  (scene3.cpp:1301-1306).
- **Recoil Guard**: pressing back *from neutral* sets the window to 60; a guard during
  its first 30 ticks is a recoil guard. A new press only counts once the window has run
  out, so mashing back does nothing. Air recoil guard works even against attacks that
  can't be air-guarded (player.cpp:534 waives flagsAA 4 inside the window). The CPU never
  recoil-guards: every CpuInput zeroes the window (akane.cpp:832).
- **RF gauge** (`m_rfGauge`, `m_rfBlue`): see comments.txt. Blue = full, then draining.
- **Instant Charge** (22C, 0xa7/0xab): level 500, so it cancels anything that connected
  (m_attackResult 2, 3, 5, 7; with blue RF even after a parry, 6).
- **Cancels**: a move starts when the current frame has flagsB0 8 and
  `m_patterns[pattern].cancelLevel <= m_patterns[move].level`; the extra
  `(pattern >= 0xc8 && m_attackResult >= 2 && != 6 || pattern < 0xc8)` in every
  StartCommand means a move can only be cancelled after it connected.
- **Freeze vs hitstop**: `m_hitstop` stops one player; `m_freezeTime` stops the *other*
  player (and this player's own objects unless movesInFreeze).
- **m_attackResult** values (existing comment says 0/2/3/6): also 5 = hit one of the
  opponent's objects (scene3.cpp:2021), 7 = absorbed by armor (:1341); 6 is set on both
  players by a parry or a projectile reflect.

## Shared move list (all characters)

| Input | Command | Action |
|---|---|---|
| double tap toward / away (ground) | 0x0/0x1 | 0xa3 run / 0xa4 back hop |
| double tap toward / away (air, above y -30 forward) | 0x0/0x1 | 0xa5 / 0xa6 |
| up again in the air | 0x6 | 0xe/0xf/0x10 |
| 22C after a connected attack, RF >= 500 or blue | 0x34 | 0xa7 / air 0xab |
| back within 30 ticks before a guard | (m_recoilGuardWindow) | 0xa8/0xa9/0xaa |
| button + direction in air hitstun, untech run out | (TryAirRecovery) | 0x9d/0x9e |
| 22D during wake-up, 1 level | 0x35 | 0xa2 (Mizuka B only) |

## Left unnamed (not determined, or unused)

- CPlayer::unkdc, unkde (akane_vf6.cpp:3457-3458 and 5 more characters set 4 and -0x14
  in the same move), unke8 (akane.cpp:2111 sets 1.5), unkf2 (set 0xa or 3 in 14 moves):
  written, never read anywhere.
- CPlayer::unk15b, unk25f: no uses (padding bytes).
- PatternFrame::unka2, unkc6: not loaded from the .pat file, never used.
- PlayerObject::unk70, unk78: zeroed by SpawnObject; unk70 is only read multiplied by 0.0
  (player.cpp:389). Dead.
- EffectDesc: the game agent named keep/shadow/sound/movesInFreeze (agreed; not repeated
  here); unk6, unk19, unk1a, unk22, unk2d, unk2e, unk44 are unused.
- CScene3 box helpers (Unk766480, Unk766b50, Unk767600, Unk7677a0, Unk767930): the game
  agent's renames cover them.
- Patterns below 0xc8 not named:
  - 0x11-0x14 (Kanna, Mio, Mizuka), 0x28 (Akiko, Ayu: ayu.cpp:423), 0xb3-0xb6
    (Mizuka, Mizuka B, Nayuki): character states with no shared meaning; for the
    character agents. 0x14-0x2c are also per-character gauge sprites (DrawGauge,
    ikumi.cpp:647-760, mio.cpp:752).
  - Kanna and Mayu reuse 0xa (kSuperJump) for a state of their own; the applier should
    keep the number or a class constant there.
  - Akiko, Ayu, Misuzu have their own cases for 0x67/0x6b/0x71 (throw poses they move).
  - 0x2e: a second copy of the name plate, never drawn.
  - 0x91-0x95: data only (guard-like, flagsB0 4|0x60), no code enters them.
  - 0x9f, 0xa0: empty patterns.
  - 0xa1: an attack like 0xa2 (effect 9, invulnerable) that no code starts.
  - 0xac-0xb1: data only, no case in any UpdatePattern (0xae/0xaf level-50 attacks with
    armor frames, 0xb0/0xb1 level-30 attacks): leftovers of an older system.
- Commands not named (per character, for the character agents): 0x2 (never produced),
  0x50-0x53 (Minagi 4136, Mizuka 631, Mizuka B 421), 0x5a-0x62 (each character's LV4
  input with a full gauge), 0x8c (Mizuka 23614), 0x96-0x99 (Ikumi, Nanase, Mizuka),
  0xa0-0xa3 (Misaki and Sayuri: 6314 6314; the same-tick 21436 elsewhere), 0xc1 (Akiko's
  CpuInput, read by nothing). Note the applier already prefixes command constants with
  `kCmd` (as for the character agents' commands.txt), so `k236A` becomes `kCmd236A`.

## Naming choices worth knowing

- Vf8: other agents proposed `UpdateTimers` and `PreUpdate`. I propose `PreUpdate` (the
  hook does regeneration, poison, timers...) and named Unk40f980
  `UpdateGaugesAndTimers`, which collides with neither choice. If Vf8 becomes
  `UpdateTimers`, keep Unk40f980's name as given.
- CPlayer 0x3118-0x3137 is a whole CharRecord (the code passes `(CharRecord*)&unk3118`):
  declaring it `CharRecord m_record;` would remove the casts and give the fields the game
  agent's names (uses, vsWins, vsLosses, bestScore, bestScoreHigh, unk14, maxCombo,
  maxDamage). Not measured for byte-identity; the renames given are the safe fallback.
- `m_hitsLanded` (existing name) is not a hit count: +1 per hit, it decays in open play
  (m_hitsDecayTimer/Step), multiplies the score (DealDamage, ScoreHit), and mode 2's
  result screen adds its bonuses to it and shows it (scene5.cpp:352, 461-469). Something
  like `m_scoreMultiplier` would be truer.
- The shared objects 0x1ef-0x1f3 are identical in all 24 classes; the character agents
  gave them different names per class (kObjBurst, kObjParticleBurst, kObjDebrisBurst,
  kObjBounceDebris, kObjLaunchFx, kObjState51Effect...). One set at CPlayer level (mine:
  kObjFallInDarkness, kObjEncasedBreak, kObjShardSmall/Large, kObjBurnFlames) would be
  consistent; the per-class copies could then be dropped.
- 0x53-0x56 "encased": the sprite is a jagged block drawn entirely in the shared palette
  (cream/beige with `system\object.dat`'s colours), breaking into shards; ice, stone or
  something else can't be told for sure from the pixels, hence the neutral name. Attackers:
  Kano's 421 shots and big shots, Shiori's 236 lasers, Nayuki (B), Mio.
- The thrown poses 0x64-0x79 are named from their sprites (Akane, Nagamori, Kano agree):
  three sets of the same seven poses: 0x64-0x6a (0x67 alone invulnerable), 0x6b-0x71 (all
  hittable), 0x72-0x78 the same sprites upside down (invulnerable, throw-protected).

## Oddities and bugs noticed

- Super jump (0xa-0xc) is unreachable: MoveOnGround needs m_command 3-5, which no
  ReadCommand or CpuInput produces.
- efz.h's comment on m_inputX is wrong: it is the *screen* direction (1 right, -1 left),
  player.cpp:1041-1052; `m_inputX == facing` is what means forward. With both left and
  right held, the one away from facing wins. m_inputHistory bits 1/2 are right/left too;
  ReadCommand converts with facing.
- HoldsGuard (player.cpp:564): once in a guard, holding *any* direction (even forward)
  keeps guarding; only neutral drops it.
- ProcessInput (player.cpp:310) resets the opponent's combo when `pattern > 0x96`, so the
  light standing guard 0x96 counts as hitstun there (0x97-0x9c don't): off by one.
- IsGuarding's range 0xa8-0xab includes 0xab (air Instant Charge).
- Kano and Mizuka B: a 421 with the button on the same tick as the 1 gives 0x14 (the 623
  number). Ikumi, Kano, Minagi, Mishio, Shiori: a 21436 with the button on the same tick
  as the 6 gives 0xa0, which they ignore.
- Sayuri's ReadCommand swaps 0x64 and 0x6e (214214 is 0x64, 236236 is 0x6e).
- 22D (0x35) is read by all 24 ReadCommands; only Mizuka B's wake-up uses it (0xa2), so
  0xa2's code in the other 23 classes is dead.
- m_counterHit (unk144) and m_guardedObject (unk154) are written and never read; flagsAA
  0x200 and 0x1000 and flagsB0 0x80 are set in the data but never tested; flagsB0 0x400
  is tested but set on no frame. PlayerObject::sound is copied but never played.
- An object's counter hit doubles the untech time (scene3.cpp:1723); a player's doesn't
  (it uses * 0.8 instead).
