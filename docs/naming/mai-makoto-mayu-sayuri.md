# chars6: CMai, CMakoto, CMayu, CSayuri

Files: `renames.txt` (37 lines: 36 members + the `Vf8` slot), `patterns.txt` (367 lines:
247 actions, 120 object actions), `comments.txt`. No `commands.txt`: every command
these four parse is shared with other characters (list at the end, for the core agent).

## Conventions I used (please keep consistent with the other agents if possible)

- **`unk3138`, `unk313c`, `unk3140` exist in every character** and are zeroed by the
  character's `StartPattern`. They are scratch for the current pattern; what they hold
  changes per pattern (loop counts, "began in the air", hold-frame counts, saved
  `vx*100`/`vy*100` in the shared 0xaa/0xab, and so on). Named `m_patternVar1/2/3`.
- **The three `[0x40]` int arrays** are per-object scratch, zeroed by `RemoveObject`:
  `m_objectVar1/2/3`. The third one is never used by Mayu or Sayuri; Mai uses it only
  for object 0x198 (unreached), Makoto only for 0x1a3.
- **Objects 0x1f0-0x1f2 are shared** (same code in all four): the shared knock-back hit
  states 0x53-0x56 spawn 0x1f0 once (flag member, named `m_bounceDebrisOut` in all
  four: Mai `unk3154`, others `unk3144`); it bursts when the player hits the ground
  (leaves 0x53-0x56, or reaches frame 2 of 0x53/0x54) into six 0x1f1 and four 0x1f2
  with plain `rand()` (visual only, as docs/compat.md says). Named kObjBounceDebris,
  kObjDebrisHeavy (gravity 0.05, lifetime 80-140), kObjDebrisLight (gravity 0.03,
  lifetime 120-220) in each class.
- **`Vf8`** (a pure virtual slot, so it needs one name in all 25 classes): called for
  both players every tick, after `Unk40f230` and before `UpdatePattern`
  (scene3.cpp:150). Mai uses it for her familiar gauge, Sayuri to flag the guard
  counter, Makoto and Mayu leave it empty. I proposed `PreUpdate` under `CPlayer::Vf8`;
  the core agent should settle the name.
- Supers are named by level where the gauge picks the version (`k236236Lv1/2/3`), by
  button where each button is its own 1-level super (Makoto's `k236236A/B/C`).
- "Unreached" = no code path sets the pattern / spawns the object (checked by script
  over the character's two files; the shared code never sets 0xc8+). Named
  `kUnused...` where the mechanics are clear.
- Motions are as the parser checks them, which is laxer than the canonical motion:
  "41236" is parsed 4,1,3; "641236" 6,4,1,3; "63214" 6,3,1,4. Command 0x28 is parsed
  4,1,2 (back, down-back, down) + button in every character that has it; I called the
  moves `k412A` etc.

## CMai (Mai): a summoned familiar

Her gimmick is a familiar object (probably her mamono / child self in the story; I
called it "familiar"). `m_familiarState` (unk3144): 0 none, 1 out and idle (object
0x191), 2 acting, 3 recharging, 4 awakened (after the LV4). `m_familiarGauge`
(unk3148) is the extra gauge `DrawGauge` draws: time left of 10000 while out or
awakened, a 1200 countdown while recharging. `Vf8` drains it 1 a frame (2 while
recharging) adjusted by `m_familiarRate` (unk3150: 1 = 4 faster, 2 = 1 slower,
3/4 = 1 faster), ends recharge (back to 0) and the awakened mode (to a slow recharge),
and while awakened forces `m_gauge` to 0 every frame.

| Input | Action | What |
|---|---|---|
| 5A 5B(close/far) 5C 2A 2B 2C j.A j.B j.C | 0xc8-0xd1 | normals |
| 6A 6B 6C | 0xd2-0xd4 | strikes with objects 0x19f-0x1a1; awakened 0xd5-0xd7 (cost 1000 of the familiar gauge) |
| 4C (3C fallback) | 0xd8 | sliding kick |
| C+dir close / air 6C | 0xdc/0xdd, 0xf0/0xf1 | throws |
| C in the dash hop | 0xe8 | (A/B versions 0xe6/0xe7 unreached) |
| air 623A/B/C | 0xfa-0xfc, landing 0xfd | falling attack; C is EX and spawns 0x1a2 |
| 412A/B/C | 0xfe-0x100 | sink and reappear 60/180 px in front of the opponent; holding A/B 30+ frames gives 0x105/0x106; C is an EX underground dash |
| 214A/B/C (no familiar) | 0x101-0x103 | familiar 0x19c strikes 40/120/200 px ahead; awakened: burst 0x1a8 at 80/160/240 |
| D / 6D / 4D (no familiar) | 0x104 | summon 0x191 (gauge 10000) at her / 60 px ahead / behind |
| D (familiar out) | 0x10d | recall (0x194, fast recharge) |
| 236A/B/C (no familiar) | 0x107-0x109 | familiar dash 0x1ac/0x1ad/0x1ae; B and C leave it out |
| 623A/B/C (no familiar) | 0x10a-0x10c | familiar 0x1b0 appears 80/160/240 px ahead, strikes (0x1c5), stays out |
| 236D / 214D / 412D / 22D (familiar out) | Mai does nothing | the idle familiar reads `m_command` itself: 0x1af / 0x1c3 / 0x1b4 / 0x19e |
| 236236 (1/2/3 levels) | 0x12f-0x131 | dash slash; hit -> flurry 0x132-0x134 (2400/3200/4500) |
| 214214 (1/2/3 levels) | 0x13e/0x140/0x142, familiar out 0x13f/0x141/0x143 | projectile super, fired by a summoned familiar or by the one out |
| 236236D, 3 levels, HP < 3333, no familiar | 0x135 | LV4: object 0x1ab sets the awakened mode (state 4, gauge 10000) |
| 236236D while awakened, HP < 3333 | 0x144 -> 0x145 | finisher: 3500 + 0.15 x remaining familiar gauge |

- C versions of the specials need `unk118 >= 500 || unk120 > 0` and cost 500 of unk118
  (250 with unk120), or 1000 of the familiar gauge when awakened.
- The familiar is lost (0x192) whenever Mai enters a hit state (0x32-0x95) or the
  familiar is struck (`unk80` 4 = lost a clash, 5 = hit by an attack).
- With the familiar out, 214214 (0x13f/0x141/0x143) spends no gauge itself: the
  familiar pays at Mai's frame 3. If the familiar is lost before that, the super whiffs
  for free.
- Unreached: actions 0xe6, 0xe7, 0xf9, 0x138, 0x13b-0x13d; objects 0x196, 0x197 (and its
  0x198), 0x199 (and its 0x19a, 0x19b, 0x1a7, 0x1a9, 0x1aa), 0x19d, 0x1a5, 0x1a6, 0x1b1,
  0x1b2, 0x1b3, 0x1b5, 0x1bd, 0x1c1. 0x13b-0x13d with 0x199 look like an older 214214
  that rained 3/5/10 falling objects.
- ReadCommand checks 236 twice (mai.cpp:701 and :767, identical; the second never fires).
- CPU (CpuInput) never starts 236X (her familiar dashes), 623B, 214214C, the LV4 or the
  D-motion familiar commands; it presses D to summon/recall. It writes `m_command =
  0x48` (mai.cpp:1109), which Mai doesn't have. `m_pressD` is assigned twice in a row
  (mai.cpp:969-970; the first value is lost, its Random draw still happens).

## CMakoto (Makoto)

| Input | Action | What |
|---|---|---|
| normals | 0xc8-0xd3 | 5C (0xcb) repeats with C up to twice, j.2C (0xd1) likewise; 6B (0xd2) a hop |
| A/B/C, 2A/2B/2C during the run 0xa3 | 0xe6-0xeb | run attacks |
| throws | 0xdc/0xdd, 0xf8/0xf9 | |
| 236A/B/C | 0xfa-0xfc | hoppers 0x193-0x195: hop out, pace, strike when the opponent is within 25 px or 236 is pressed again |
| 214A/B/C | 0xfd-0xff | firecrackers 0x196-0x198: land, sputter sparks 0x199, burst; another 214 detonates them |
| 623A/B/C | 0x100-0x102 | leaping attacks (C leaps twice) |
| 412A/B/C, no bouncer out | 0x103-0x105 | bouncers 0x19a-0x19c bounce off the screen edges (`m_bouncerOut`) |
| 236236A/B/C (1 level each) | 0x12c-0x12e | slow 5-hit floating objects 0x1a2-0x1a4 |
| 214214 Lv1-3 | 0x12f-0x131 | jump and float down over a ground hit object 0x19f-0x1a1 |
| 641236 Lv1-3 | 0x132-0x134 | charging rush with 0x1a7 in front |
| 2,6,3+D, gauge exactly 3000, HP < 3333 | 0x135 | LV4: throws 0x1a6 up, catches it and heals; if struck, 0x136 |

- Oddities: 236C spawns its hopper on every tick of frame 3 plus once more (missing
  `timer == 0`, makoto_vf6.cpp:3606); the LV4 heal caps HP at 10000, one more than full
  (makoto_vf6.cpp:4917); firecracker B decrements its spark timer twice a tick
  (makoto.cpp:2165, 2190); `kAir214A` 0x106 is unreachable (makoto.cpp:237: `y < 0.0`
  inside a `y == 0.0` branch); 6B tests `m_inputY == 0 || (m_bufferedPress & 4) != 0`
  (a buffered down still allows it, makoto.cpp:370).
- Unreached: 0xd4 (and 0xd5, 0xd6 behind it).
- Normals keep sliding at the run speed while `unk158 == 1` (set by the run 0xa3).
- CPU: never 236236A (it draws 0x65 + Random(0, 3), so 0x65-0x67; 0x67 is nothing) or the
  LV4. Its CpuInput tests `pattern == 0x108` and `0xee` (makoto.cpp:855, 993), actions
  Makoto doesn't have: copied from Mai's routine (mai.cpp has the same 0x108 line).

## CMayu (Mayu)

No extra members besides the shared scratch; almost no objects (only her LV4 uses
any).

| Input | Action | What |
|---|---|---|
| normals | 0xc8-0xd3 | 6B hop 0xd2, 1B 0xd3 |
| A/B/C in the dash hop | 0xe6-0xe8, landing 0xe9 | |
| throws | 0xdc/0xdd, 0xf8/0xf9 | |
| 41236A/B/C | 0xfa-0xfc -> 0xfd/0xfe | running command grab |
| 41236D | 0x11b -> 0x11c | grab, stands on the opponent |
| 236A | 0x103 | dash; hold A -> rising 0x106, hold B -> jump 0x107 (A to dive 0x100) |
| 236B | 0x104 | jump; A to dive 0x100, 236 again -> rising 0x122 |
| 236C (EX) | 0x105 | flying tackle |
| air 236A/B/C | 0x118-0x11a | dives; hit -> 0x123 |
| 623A/B/C | 0x10a-0x10c | leaps |
| 214A / 214C | 0x110 / 0x112 | leap back / forward to the screen edge, cling, jump off; then A/B/C dives 0x10d/0x10e/0x10f |
| 214B | 0x121 | the same, then an automatic dive by distance 0x11d/0x11e/0x11f |
| 214D | 0x111 -> 0x113 | wall jump into a grab |
| 214214 Lv1-3 | 0x13a-0x13c | steerable spin |
| 641236 Lv1-3 (A-C only) | 0x134-0x136 -> 0x137-0x139 | anti-air grab |
| 21436 Lv1-3 | 0x13d/0x13f/0x141 -> 0x13e/0x140/0x142 | dash strike into a rush |
| 2,3,6,9,3+D, gauge exactly 3000, HP < 3333 | 0x12f (0x130 within 60 px) | LV4: grab, slam, then ~830 frames of stomps with two helpers 0x191/0x192 (never below 1 HP from them) |

- Bug: the air throw 0xf9 clamps the right wall at `x > 6100.0` (mayu_vf6.cpp:3204),
  surely 610.0; the left one is 30.0.
- 0xfd/0xfe take a hit back off the combo count (`m_comboHits--`, `m_shownHits--`).
- Unreached: 0xff, 0x12c-0x12e (three supers no command maps to); objects 0x190,
  0x196, 0x197, 0x198 (and 0x199, 0x19a).
- CPU: picks 236236 commands (0x64 + Random, mayu.cpp:914, 1179) Mayu doesn't have;
  `Random(0, 2) * 0x64` (mayu.cpp:979) gives 0 (a dash left) or 0x64 (nothing): `+` was
  meant; 623 as `Random(0, 3) + 0x14` (mayu.cpp:1529) is sometimes 0x17 (nothing); `m_command = facing`
  (mayu.cpp:1489) sits behind an impossible condition (`< 0x190 && > 0x1a4`). Never
  starts 214214, 214D, 41236D or the LV4.

## CSayuri (Sayuri)

| Input | Action | What |
|---|---|---|
| normals | 0xc8-0xd1 | no command normals |
| throws | 0xdc/0xdd, 0xf8/0xf9 | |
| 236A/B/C, no shot out | 0xfa-0xfc | ground shot 0x191 (C fires two); `m_shotsOut` |
| air 236A/B/C | 0x109-0x10b | shots 0x192/0x1a3/0x1a4 and a hop back; air C costs nothing |
| 41236A/B/C | 0xfd-0xff | running grab, carries the opponent to the screen edge and slams |
| 214A/B/C | 0x100 | parry stance; a clash -> counter 0x12b and `m_parriedPattern` = the opponent's pattern |
| A/B/C while guarding the parried pattern | 0x102 | guard counter (her guard flashes, `Tint`, when it is allowed) |
| air 412A/B/C | 0x103-0x105 | dive (B guarded -> 0x10c rebound) |
| 623A/B/C | 0x106-0x108 | dash / hop / both |
| 21436 Lv1-3 | 0x12c-0x12e | super carry; Lv2/3 carry back and forth |
| 236236 Lv1-3 | 0x132-0x134 | 2/4/6 shooters 0x198-0x19d fire 0x197 |
| 63214 63214 Lv1-3 | 0x135/0x137/0x139 -> holds 0x136/0x138/0x13a | grab, strikes 0x1a0 fall around |
| 2, A, 2, D, gauge exactly 3000, HP < 3333 | 0x13b -> 0x13c | LV4: drop from above, sit and stomp |

- Her guard states spawn a guard object 0x190 (`m_guardEffectOut`) that follows her
  stand/crouch/air guard height.
- ReadCommand parses 214214 (`0x64` + button, sayuri.cpp:543) but StartCommand has no
  move for it. Note her numbering is the reverse of Mai's/Makoto's: Sayuri 0x64 =
  214214 and 0x6e = 236236; Mai/Makoto 0x64 = 236236 and 0x6e = 214214.
- `kUnusedDashC` 0xe8 lands into 0x10d, which has no case (default: stands still,
  loops its animation); unreachable anyway. Unreached: 0xd2, 0xd5, 0xd6, 0xe6-0xe8, 0x101.
- CPU: `Random(0, 2) * 0xaa` (sayuri.cpp:1017) gives 0 (dash left) or 0xaa: `+` meant;
  `m_cpuRoll < 0x10 && m_cpuRoll > 0x12` (sayuri.cpp:1020) can never hold, and its
  command 0x5d doesn't exist; `m_command = facing` (sayuri.cpp:1428) is behind
  `< 0x2a && > 0x2f`. It does start the LV4 (0x62) but only at m_cpuRoll == 0x36 and far
  away (sayuri.cpp:1423). Never starts 41236X or 63214 63214X.

## Not determined

- CMai 0xf9: unreached; freezes the opponent 60 frames with effect 0x28, one hit. Every
  character has a case 0xf9; for Makoto/Mayu/Sayuri (and Kano...) it is the air throw
  hold, Mai's isn't. Left unnamed.
- CMai objects 0x1b1 (one hit, played once) and 0x1b2 (played once): never spawned, no
  clue what they were. Left unnamed.
- Objects 0x1ef and 0x1f3, in all four: 0x1f3 is spawned by the shared state 0x51 and
  follows the player until its animation ends; 0x1ef by the shared 0x57, a screen
  object at (60, 40) removed when 0x57 ends. 0x51 and 0x57 are set only by Kaori's code
  (kaori_vf6.cpp:3134, 4934), so these are each character's "struck by Kaori's X"
  graphics. Left for whoever names 0x51/0x57.
- CSayuri 0x10d: no case (see above).

## Observations on CPlayer members and shared actions (for the core agent)

- `unk118` / `unk120`: C specials need `unk118 >= 500 || unk120 > 0` and subtract 500
  (250 when `unk120 != 0`). 22C (`m_command 0x34`) with the same condition while the
  current attack hit or was guarded goes to 0xa7 (ground) / 0xab (air): afterimages,
  `unk118` reset to 0 (added x5 to `m_proration` when `unk120 == 1`), the opponent frozen
  90 frames. While `unk120 != 0`, the hit states drain `unk118` (0.8 a frame in 0x51/0x52,
  30 at the start of 0x53-0x56).
- `unk14c` freezes the opponent (their UpdatePattern/UpdateObjects return while it is
  > 0); supers set 0x78. Objects with `unk88 != 0` keep moving during one's own freeze.
- `PlayerObject::unk80`: the object's hit result; 4 = lost an object clash
  (scene3.cpp:1934), 5 = struck by an attack (scene3.cpp:1836); characters' objects die
  or flee on 4/5. `unk84` = hits the object has left.
- `Unk40ff70()`: 1 / -1 when at the left / right screen edge (Mayu's wall jumps).
- 0xa3 forward dash: Mai, Mayu and Sayuri hop; Makoto runs (vx 2.2, sets `unk158 = 1`,
  which keeps the normals sliding).
- 0x96-0x9b / 0x9c and 0xa8-0xaa are guard states (Sayuri's guard object places itself
  standing for 0x96-0x98/0xa8, crouching 0x99-0x9b/0xa9, air 0x9c/0xaa).
- Makoto, Mayu and Sayuri only parse 22D (0x35) while `pattern == 0x60`, and none of them
  uses 0x35; only Mai's familiar does.
- LV4s: Mai 236236D, Makoto 2,6,3+D, Mayu 2,3,6,9,3+D, Sayuri 2,A,2,D; all need HP < 3333
  (0xd05); Makoto/Mayu/Sayuri need the gauge exactly 3000 in ReadCommand, Mai >= 3000.

## Command motions as these four parse them

| Command | Motion (window) | Who |
|---|---|---|
| 0x0a-0x0d | 236 + A/B/C/D (45) | all |
| 0x14-0x17 | 623 (60) | all (Mayu, Sayuri: ground only) |
| 0x1e-0x21 | 214 (45) | all |
| 0x28-0x2b | 4,1,2 (45) | Mai, Makoto, Sayuri (Sayuri: air only) |
| 0x32-0x35 | 5,2,5,2 + A/B/C/D (45 for A/B, 90 for C/D) | all |
| 0x46-0x49 | 4,1,3 = 41236 (60, ground) | Mayu, Sayuri |
| 0x60 | 2,6,3 + D, gauge == 3000 (60) | Makoto LV4 |
| 0x62 | Mayu 2,3,6,9,3 + D; Sayuri 2,5,A,2,5,D; gauge == 3000, ground (90) | Mayu, Sayuri LV4 |
| 0x64-0x67 | Mai/Makoto 236236; Sayuri 214214 (90) | |
| 0x6e-0x71 | Mai/Makoto/Mayu 214214; Sayuri 236236 (90; Mayu 80) | |
| 0x78-0x7a | 6,4,1,3 = 641236 (75), gauge >= 1000; Mayu A-C only | Makoto, Mayu |
| 0xa0-0xa3 | 6,3,1,4,6,3,1,4 (135, ground) | Sayuri |
| 0xaa-0xad | 2,1,4,3,6 = 21436 (90), gauge >= 1000, ground | Mayu, Sayuri |
| 6 | up pressed after not-up (5) | all |
| 0 / 1 | L,5,L / R,5,R (45): absolute directions | all |
