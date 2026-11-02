# chars2: CKano, CIkumi, CMishio, CShiori

Per-character working copies are in the subfolders kano/, ikumi/, mishio/ and shiori/; helper scripts (digest.py, squeeze.sh, patinfo.py) are in work/.
The top-level patterns.txt, renames.txt and comments.txt join them in that order.

| Class | Members named / left | Methods named | Actions named |
|---|---|---|---|
| CKano | 16 / 2 (unk3148 and unk314c, only zeroed) | - | 118 (61 actions, 57 objects) |
| CIkumi | 18 / 0 | 4 / 0 | 116 (69 actions, 47 kObj objects) |
| CMishio | 15 / 3 (unk316c, unk3170 and unk3374, only zeroed) | - | 124 (78 actions, 46 objects) |
| CShiori | 11 / 0 | - | 110 (59 actions, 51 kObj objects) |

- **Left in every class.** The shared objects 0x1ef and 0x1f0-0x1f3: each class has
  its own copy of the same code (see "Shared" below). Shiori's dead object 0x19b is
  also left.
- **Vf8 and DrawGauge.** These are virtual slots, so they are only described per
  character. Vf8 is the per-frame hook CScene3 calls between Unk40f230 and
  UpdatePattern (scene3.cpp:150). A name such as `UpdateCharacter` or `PreUpdate`
  would fit. The four classes use it for:
  - Kano: power-gauge regeneration, an idle bonus and 236236C's meteor.
  - Ikumi: her stock and mode system, and orb bursts on hits.
  - Mishio: the power-up timer, particles and tint.
  - Shiori: nothing (empty).

## Conventions used in all four (so the names line up)

- **Per-action scratch.** unk3138/unk313c/unk3140 are zeroed by StartPattern in all
  four, and used as once-flags, loop counts and vx/vy * 100 saved over a freeze. They
  are named m_patternVar1/2/3.
- **Per-object scratch.** The three per-object int[0x40] arrays are zeroed by
  RemoveObject. They are named m_objectVar1/2/3.
- **The 0x1f0 flag.** unk3144 in all four is set when shared actions 0x53-0x56 spawn
  object 0x1f0, and cleared when it bursts. It is named m_burstObjectOut. Other classes
  have the same flag at other offsets: Akane's is unk3148.
- **Actions.**
  - Normals: k5A, k5BClose/k5BFar, k6B, k2A, kJumpA, kJump2A.
  - Dash attacks: kDashA, kDash2A.
  - Throws: kThrow -> kThrowConnected, kAirThrow -> kAirThrowConnected.
  - Specials: k236A/B/C, air versions kAir236A.
  - Supers: k236236A/B/C, k214214A/B/C, k641236A/B/C, k21436A/B/C, with A/B/C =
    LV1/2/3.
  - LV4: kLv4 -> kLv4Connected.
  - Never started: kUnused....
  - Objects: kObj<What> or kObj<Move><Role>.

## Facts across the four

- **The CPU.** CpuInput is byte-identical in kano, ikumi, mishio and shiori: Shiori's
  routine. It writes commands for Shiori's moves only (623, 412 and Shiori's LV4 0x5f),
  plus 0x82-0x84, which only Mizuka, MizukaB and Misuzu read. Everything else it writes
  goes to branches the other three don't have. It never starts:
  - Kano's 421, 236236, 214214, 21436, 22B, 5D, 236D or LV4.
  - Ikumi's supers, LV4 or 41236C.
  - Mishio's 236236, 214214, 22A/22B or LV4. It never checks her power-up either, so
    most of her specials do nothing.
  - Shiori's 214214 or 21436.
  - The double jump, for any of them.
  - Details: shiori/notes.md.
- **Gauge level selection differs.**
  - Kano matches the exact button for 641236, 236236 and 214214: C with 2000 gauge
    does nothing. Only her 21436 falls back.
  - Shiori and Mishio fall back from C to B to A for every super.
  - Ikumi's 214214A/B/C all cost 1000.
- **21436 has a same-frame bug in Kano, Ikumi and Shiori.** A button on the same frame
  as the final 6 gives command 0xa0 + button, which none of them handles, so the super
  fails. Mishio parses 21436 too but has no move on it. Kano's 421 has the same bug: the button on the final 1 gives 0x14 +
  button, the 623 command. These change human input, so a fix is not replay-safe.
- **Random draws in visuals and voices.** All four use CPlayer::Random in purely
  visual or voice code (Kano's explosion voices and spark offsets, Mishio's particles,
  Shiori's LV4 jitter, Ikumi's orb angles). The draws are recorded in replays and use
  up words, so the fork has to keep every such call.
- **Dead code.**
  - Kano: actions 0xd3 and 0x107-0x10e, objects 0x192, 0x194 and 0x1a1.
  - Mishio: 0xd4-0xd6 and 0x118, object 0x1bb.
  - Shiori: 0x12c, 0x136 and 0x137, objects 0x195 and 0x19b.
  - Ikumi: see ikumi/notes.md.

## Commands seen only in these files (suggestions for the core agent)

None of these is Kano-, Ikumi-, Mishio- or Shiori-only: each number is also read by
other characters, so they are listed here and not in a commands.txt.

- **0x5e: Ikumi's LV4, 236236236 + C within 110 frames (ikumi.cpp:1003-1041).** Mio
  and Mizuka use the same number for a button sequence (mio.cpp:791).
- **0x5f: Shiori's LV4, 236236 B C with exactly 3000 gauge (shiori.cpp ReadCommand).**
  The CPU writes it for all four.
- **0x62: Mishio's LV4, B, neutral, B, down, neutral, C, A over the 180-frame history
  (mishio.cpp:682-716).** It is also the LV4 command of Mayu, Sayuri and Mizuka, each
  with its own sequence.
- **Suggested names for the LV4 commands.** Every LV4 command means "this character's
  LV4 input", so kLv4 can't be used for all three. Names such as `kLv4Input` /
  `kLv4Input2` / `kLv4Input3` for 0x5e/0x5f/0x62, or a name per motion (k236236236C,
  k236236BC), are the core agent's call.
- **0x96-0x98: 41236 41236 + A/B/C (Ikumi's grab super, ikumi.cpp:1043-1078).**
  Nanase has the same code (nanase.cpp:611); Mizuka's 0x96 differs.
- **0x28-0x2b are 4 1 2 + button (back, down-back, down).** They are not 421. Kano's
  421 is 0x3c-0x3f, and her parser also yields 0x14 on a same-frame button.
- **0x65 with exactly 3000 gauge.** Shiori reads 236236B as 0x65 and ignores it.

## Shared members and actions (observations for the core agent)

Collected from the four; details in each character's section.

- **PlayerObject.** unk84 is the object's hits left. It is set to 1, 3, 5, 7 or 0x63
  as the object starts, and some objects end at 0. unk80 is the frame's hit result:
  - 2/3: hit or guarded.
  - 4: clashed with an object.
  - 5: struck.
  - 6: excluded by some objects.
  - It is reset when the animation frame advances.
- **unk118/unk120.** The EX resource:
  - C specials, Kano's 236D and 22C need unk118 >= 500 or unk120 > 0, and take 500
    (250 with unk120). The C versions show effect 0x21.
  - 0xa7/0xab (22C) empty it into m_proration when unk120 == 1.
  - Shared 0x51 and 0x53-0x56 drain it while unk120 != 0.
- **unk14c.** The super freeze. Every super sets 0x78 at its flash, 0xa7 sets 0x5a,
  0xaa sets 0x3c. The opponent's UpdatePattern and UpdateObjects return while it is > 0.
  unk14a is a per-player hit stop / hold (LV4s set 9999).
- **unk15c.** Specials need < 2, jump-cancels < 3, dashes < 1. unk158 is set by the
  forward dash and keeps its speed. unk159/unk15a count air dashes and air jumps.
- **The LV4 condition.** Every class's LV4 needs the player in 0xa8 or 0xa9 (one test
  per character file), HP < 3333 (0xd05) and 3000 gauge.
- **Shared objects (identical code in every class).**
  - 0x1ef: from shared 0x57, at screen (60, 40), removed when the player leaves 0x57.
  - 0x1f0: from 0x53-0x56. It bursts into 0x1f1 x6 and 0x1f2 x4 with plain rand(),
    sound 0x22.
  - 0x1f3: from shared 0x51, follows the player.
  - Suggested names: kObjBurst / kObjBurstPiece / kObjBurstPieceBig for 0x1f0-0x1f2.
- **ReadInput.** m_inputX is absolute (1 right, -1 left): both branches of the facing
  test in CPlayer::ReadInput give the same result (player.cpp:1042-1052). The efz.h
  comment "relative to facing" is wrong. m_inputHistory's bits are absolute too.
- **Kano's DrawGauge uses anims 0x2a-0x2c as HUD sprites.** So do Mishio's 0x27-0x2c
  and Shiori's 0x2b/0x2c. These pattern numbers are gauge graphics, not actions.


# CKano (src/kano.cpp, src/kano_vf6.cpp)

Named: 16 members (all but unk3148 and unk314c, which are only zeroed in the constructor
and Reset), 118 action numbers (61 of her own actions 0xc8-0x13c, 57 objects
0x190-0x1c8). Left: the shared objects 0x1ef and 0x1f0-0x1f3 (same code in every class),
and Vf8 and DrawGauge, which are virtual slots. No commands.txt: every command Kano reads is
a shared ID.

## The charge gauge (m_chargeGauge, unk3150)

Kano's own mechanic. It is a second gauge, 0-10000, drawn by DrawGauge at the power
gauge's top (0x31, 0x1f) from anims 0x2a (full), 0x2b (frame) and 0x2c (fill, width *
gauge / 10000).

- **Filling it.**
  - D on the ground (0xfa) is a chant: frames 3-6 loop, adding 0x4b a frame.
  - Every special and super has the same loop in its startup (+0x4b for specials,
    +0x64/0x96/0xc8 for supers). It exits when the gauge reaches 10000.
  - D chants until the gauge is full or D is pressed again.
- **Spending it.**
  - A special fires only on a full gauge, then sets it to 7500/5000/2500 (A/B/C), so the
    stronger button costs more.
  - A super empties it.
  - 21436 refills it to 10000 during its frames 3-12, then empties it as each shot
    fires.
  - If the gauge is already full when a move starts, StartCommand skips the startup
    (frame 7) and takes the cost there (kano.cpp:143...).
- **236D (0xfb).**
  - Needs 500 of CPlayer::unk118 (or unk120 > 0), the same resource as 22C. It costs
    500 (250 with unk120) and sets the gauge to 10000.
  - It also cancels a special's recovery, once that special's object is out (frame
    > 0xf / 0x10 / 0xb).

## Vf8 (kano.cpp:629; the per-frame hook CScene3 calls before UpdatePattern)

- **Power gauge regeneration.**
  - m_gaugeRegenTimer counts while the opponent's unk14c is 0 (no super freeze) and
    Kano isn't in a super (pattern < 0x12c).
  - Past 2 + 4 * level frames (level = m_gauge / 1000), m_gauge gains 1. That is +1
    every 3 / 7 / 11 frames at levels 0 / 1 / 2.
  - A second test, the same comparison times 0.5 and pattern 3 (kano.cpp:640), can
    never be true: the first test has just zeroed the timer. It is dead code.
- **Idle bonus.**
  - m_idleTimer counts while vx == 0 outside actions 0x32-0xc8 and supers, and resets
    otherwise.
  - At 0x276 = 630 frames the gauge gains 300 and object 0x19b floats up 50 px above
    her.
- **236236C's meteor.**
  - m_meteorTimer counts down every frame.
  - When it reaches 0 while m_meteorsPending > 0, object 0x1c3 falls from y -480 at
    x + 120 - Random(0, 240) - 192 * m_meteorFacing.
  - That Random goes through CPlayer::Random, so replays record it.
  - The next meteor would come 180 frames later. 236236C adds only one, 600 frames
    after the super.

Other characters' Vf8 is different: Shiori's is empty; Mishio's runs her power-up timer.

## Move list (motion -> command -> action)

Kano needs the exact button for 641236, 236236 and 214214. 641236C with 2000 gauge
does nothing (kano.cpp:198-259). Only 21436 falls back: C gives the B version with 2000
gauge, the A version with 1000 (kano.cpp:197-220). This differs from Shiori and Mishio.
Specials (236/214/421) also need their objects gone: m_eruptionsOut, m_shotsOut and
m_orbsOut must be 0.

| Input | Cmd | Needs | Action | What it does |
|---|---|---|---|---|
| 5A / 2A / jA | - | | 0xc8 / 0xcc / 0xcf | |
| 5B close (< 70 px) / far | - | | 0xc9 / 0xca | |
| 6B / 2B / jB | - | | 0xd9 / 0xcd / 0xd0 | |
| 5C / 2C / 3C / jC | - | | 0xcb / 0xce / 0xd4 / 0xd1 | 3C slides at 2.6, 3 hits; jC 5 hits, loops once |
| 6C | - | ground | 0xd2 | remote hit 0x199 150 px ahead at y -40; costs 20 gauge |
| j2A / j2B / j2C | - | above y -25 (B: -30) | 0xd5 / 0xd6 / 0xd7 | dive at 30 degrees, speed 2.2, until landing |
| A/B/C, 2A/2B/2C in the forward dash | - | in 0xa3 | 0xe6-0xe8, 0xe9-0xeb | dash attacks; dash 2C 6 hits |
| C + direction, within 30 px | - | grounded opponent, not being hit | 0xdc -> 0xdd | throw, DealDamage(1000, 750) |
| 6C in the air, within 100 px | - | airborne opponent, not being hit | 0xf8 -> 0xf9 | air throw, DealDamage(1200, 500); a miss continues as jC from frame 2 |
| D | - | ground, charge < 10000 | 0xfa | chant: fills the charge gauge |
| 236D | 0xd | unk118 >= 500 or unk120, charge < 10000 | 0xfb | fills the charge gauge at once |
| 236A/B/C | 0xa-0xc | ground, no eruption out | 0xfe / 0xff / 0x100 | eruption on the ground 150 px ahead, +-70 px with left/right held: 1 / 2 / 5 bursts (0x1bb / 0x1bc / 0x1bd -> hits 0x190); B and C also cost 20 / 50 gauge |
| 214A/B/C | 0x1e-0x20 | ground, no shot out | 0x101 / 0x102 / 0x103 | 1 / 3 / 5 shots 0x191 forward at different heights (vx 3 slowing to 1.5); B and C cost 7 / 10 gauge per shot |
| 421A/B/C (4, 2, 1 + button) | 0x3c-0x3e | ground, no orb out | 0x104 / 0x105 / 0x106 | orb 0x1b8 / 0x1b9 / 0x1ba rises over her and fires 1 / 2 / 3 shots aimed at the opponent (0x1b3-0x1b7, 70 to 10 degrees); B and C cost 20 / 50 gauge |
| 22C | 0x34 | shared | 0xa7 / air 0xab | shared |
| 22B | 0x33 | 2000 gauge | 0x135 | LV2: summons 0x1ae, which leaves the floor trap 0x1af: it attacks while Kano stands within 30 px of it, up to 10 hits or 2400 frames |
| 641236A | 0x78 | 1000 | 0x12c | LV1: 0x1c7 creeps forward while A is held; letting go erupts it 3 times (0x19a) |
| 641236B | 0x79 | 2000 | 0x12d | LV2: 0x1a3 speeds up into the rush 0x1a4 (vx 4, up to 99 hits) |
| 641236C | 0x7a | 3000 | 0x12e | LV3: a pillar on Kano herself (0x1c1 -> 0x1be) with debris 0x1c0 -> 0x1c6 |
| 236236A | 0x64 | 1000 | 0x12f | LV1: bomb 0x19c thrown down-forward; on contact a chain of 7 explosions (0x19d -> 0x1a5) |
| 236236B | 0x65 | 2000 | 0x130 | LV2: three lingering blasts 0x1ad (5 hits each) and a rising chain blast 0x19d |
| 236236C | 0x66 | 3000 | 0x131 | LV3: 0x1c2 flies off; 600 frames later the meteor 0x1c3 falls (Vf8) and explodes (0x1c5) |
| 214214A | 0x6e | 1000 | 0x138 | LV1: big shot 0x1a7; on a hit it pops up and bursts 8 times |
| 214214B | 0x6f | 2000 | 0x139 | LV2: shot 0x1ac (7 hits); it stops on a hit and bursts every 2 frames |
| 214214C | 0x70 | 3000 | 0x13a | LV3: shot 0x1b2 rises, then flies level with 99 hits and hitting sparks 0x1b0 |
| 21436A/B/C | 0xaa-0xac | 1000 / 2000 / 3000 (falls back) | 0x132 / 0x133 / 0x134 | LV1-3: 3 / 4 / 5 homing shots 0x19e / 0x19f / 0x1a0, 30 frames apart |
| 21436D | 0xad | in 0xa8/0xa9, HP < 3333, 3000 gauge | 0x13b -> 0x13c | LV4: a grab at frame 7; on a hit she carries the opponent up, and object 0x1c8 deals DealDamage(5000, 850) |

Never started (no StartCommand, CPU or other path):
- **Actions.**
  - 0xd3: a fall at (1.2, 1.2).
  - 0x107/0x108: a chant at +300 a frame, then two remote hits 0x199 110 px ahead.
  - 0x109-0x10b: three 0x1a2 dropped from 480 px up.
  - 0x10c-0x10e: an air chant with velocity halved and +45 gauge; 0x10e also spends
    unk118.
  - These look like an older move set. 0x10c-0x10e set m_patternVar1 = 3 on frame 0,
    so their own "loop 3 times" test never runs.
- **Objects.** 0x192, 0x194 and 0x1a1 are never spawned. 0x1a2 is spawned only by
  0x109-0x10b.

## Motions (ReadCommand, kano.cpp:681-1023)

Checked in this order; the first match returns:
- 0xaa-0xad: 21436 + A-D. Gauge >= 1000 at the first 2. Window 90 frames.
- 0x78-0x7b: 641236. The 2 and the last 6 are optional. Window 75 frames.
- 0x6e-0x71: 214214, and 0x64-0x67: 236236. Window 90 frames.
- 0x3c-0x3f: 421. Window 60 frames.
- 0xa-0xd: 236, 0x28-0x2b: 412, and 0x1e-0x21: 214. Window 45 frames.
- 6: double jump.
- 0x35: 22D, starting in action 0x60. 0x34 / 0x33 / 0x32: 22C / 22B / 22A.
- 1 / 0: dashes.

Quirks (they change human input, so they are not replay-safe to fix):
- 421 with the button on the same frame as the final 1 gives 0x14 + button (kano.cpp:813).
  That is the 623 command, which Kano's StartCommand ignores, so the special fails.
  The parser looks copied from a 623 one.
- 21436 with the button on the same frame as the final 6 gives 0xa0 + button
  (kano.cpp:698), which Kano ignores.
- 0x28 (412) is parsed but Kano has no 412 move.
- 0x35 (22D) is parsed but Kano has no 22D move.

## CPU (CpuInput, kano.cpp:1025-1892)

Shiori's routine, byte for byte; see shiori/notes.md. For Kano:
- **What works.**
  - 236 (0xa-0xc; a special charges itself, so it fires) and 214 (0x1e-0x20).
  - 641236 (0x78-0x7a, picked at random once the gauge is >= 1000). Kano needs the
    exact gauge, so 0x79/0x7a with too little gauge does nothing.
  - 22C (0x34), dashes, normals and throws.
- **What does nothing.** 0x14-0x16 (623), 0x28-0x2a (412), 0x5f (Shiori's LV4) and
  0x82-0x84 all go to StartCommand branches Kano doesn't have.
- **Never used.** 421, 236236, 214214, 21436, 22B, 5D, 236D and Kano's LV4. The CPU
  presses D only while she is being hit.
- **Tests on Shiori's numbers.** The routine tests patterns 0xfa-0xfc and
  0x10e-0x110. For Kano 0xfa is 5D, 0xfb is 236D, 0x10e is unused, and 0xfc, 0x10f and
  0x110 don't exist.
- **A wasted draw.** At kano.cpp:1072-1073, m_pressD is drawn twice in a row and the
  first draw is lost. Both draws still use up replay words, which is harmless only
  because there is no CPU in a recorded fight.

## Oddities and possible bugs

- **0x1b8's aimed shot (kano.cpp:3118-3146, the tests at :3120 and :3134).** When the orb faces left, both branches
  test `m_objects[i].x > (*m_opponent)->x`. The second should probably be `<`, so a
  left-facing orb with the opponent to its right always fires 0x1b3 (70 degrees).
  0x1b9 and 0x1ba repeat the same code.
- **Moves that cost power gauge.**
  - 6C costs 20 gauge.
  - The B/C versions of 236 and 421 cost 20/50, and 214B/C cost 7/10 per shot.
  - These are `m_gauge = m_gauge - n`, with no check that the gauge is high enough.
- **Count leaks.**
  - The object counters (m_shotsOut, m_orbsOut, m_eruptionsOut) are only decremented
    in the objects' own end code.
  - If an object is overwritten when the 64-slot ring wraps (SpawnObject removes
    m_objectHead), its count never comes back down. The matching special is then
    blocked until Reset.
  - **Inferred.** This is rare.
- **0x1b2 (214214C) after leaving the screen.** It is removed when it leaves the
  screen, but the code goes on to spawn a 0x1b0 from the freed slot that same frame.
- **0x19d's rise.** 0x19d tests Kano's current action (`pattern == 0x130`) to decide
  whether to rise. It stops rising once she leaves 236236B.
- **0x1bf follows Kano.** It sets its x to Kano's every frame, including the one
  spawned where the meteor lands.
- **Random in visual or voice code.** Voice picks (0x19d: Random(0, 3) per explosion)
  and spark offsets (0x1a7, 0x1ac, 0x1b0, 0x1b2, 0x1be) use CPlayer::Random, so they
  are recorded in replays and use up words.
- **Specials end in the air.** 214/236/421 test `y == 0.0` only in StartCommand. Their
  startup loop keeps Kano still (StopMoving at frames 0 and 7).
- **Animations as gauge sprites.** anims 0x2a-0x2c are gauge sprites, not actions.

## Shared members and actions seen (for the core agent)

- **The super freeze.** Supers set unk14c = 0x78 at their flash. LV3 supers call
  FillBackground(0xb0, 0xa4) (0x12e, 0x13a), the others FillBackground(0xb0, 3). The
  flash effect is CGame 0x44/0x45/0x46 for LV1/2/3, plus 0x47 for the LV4.
- **unk118/unk120.**
  - 236D and 22C need unk118 >= 500 or unk120 > 0.
  - 0xa7/0xab (22C) empty unk118 into m_proration (unk118 * 5, when unk120 == 1) and
    freeze for 90 frames (unk14c = 0x5a).
  - Shared 0x51 and 0x53-0x56 drain unk118 while unk120 != 0.
- **The LV4's opponent.** It needs the player in 0xa8 or 0xa9, as in every class (one
  test per character file).
  - The grab sets the opponent to 0x6b at frame 0, then to 0x64 on frames 4-8 at points
    in front of Kano.
  - At the end it becomes 0x3b with ay 0.035.
  - 0x1c8 sets the opponent to 0x65 with unk14a = 9999.
- **Throw victims.** 0x6b for the ground throw, then 0x3f. 0x64/0x65 for the air
  throw.
- **unk158.** The forward dash 0xa3 sets it to 1 and 4/5 read it. Kano's normals clear
  it.
- **PlayerObject.** unk84 is the object's hits left (1, 5, 7, 0x63), and unk80 is the
  frame's hit result (a nonzero value is a hit; 6 is excluded by 0x19c/0x19e). Kano's
  0x1ad removes itself when unk84 reaches 0.
- **Shared objects.**
  - 0x1ef: from shared 0x57, at screen position (60, 40), removed when the player
    leaves 0x57.
  - 0x1f0: from 0x53-0x56. It bursts into six 0x1f1 and four 0x1f2 with plain rand()
    speeds and lifetimes. Kano's m_burstObjectOut guards it.
  - 0x1f3: from shared 0x51, follows the player.
  - Shiori's notes suggest kObjBurst / kObjBurstPiece / kObjBurstPieceBig for
    0x1f0-0x1f2. Kano's names avoid them (her 0x195 is kObjShotBurst).
- **Command 0x34.** For Kano, 0x34 (22C) leads to 0xa7 on the ground and 0xab in the
  air (kano.cpp:122-129).

## Doubts

- **The trap's meaning.** kObjFloorTrap (0x1af) is active only while Kano herself
  stands over it (`y == 0 && |obj.x - x| < 30`, kano.cpp:2796). What it looks like in
  the game, and whether it is meant to hit the opponent standing near her, isn't
  visible from the code.
- **The "charge" names.** The code shows only that the voice cue 0 starts every move
  and that the loop fills the bar. The names assume nothing more.
- **The object names.** Names such as kObjPillar, kObjBomb and kObjMeteor are guesses
  from motion (where it is spawned and how it moves), not from the sprites.

# CIkumi notes

Sources: src/ikumi.cpp, src/ikumi_vf6.cpp. Frame/box facts from the game's own
ikumi.pat / ikumi2.pat (parsed with work/patinfo.py; data in
/home/sakuya/.local/share/asm/worktrees/7673b13e-.../efz-unpacked/tasogare/EFZ/ikumi).

## Her system: orbs, stocks, the powered mode

- **Orbs.** When certain attacks hit, Vf8 (ikumi.cpp:909-958) spawns, once per action
  (`m_orbBurstSpawned`), an orb burst at the opponent: B normals 0x1d6 (3 orbs), dash B
  0x1de (5), 236A/B + 623A/B 0x1d7 (6), C/stock-3 specials 0x1df (9), stock-6 specials
  0x1e0 (10). 214 pillars, 41236C and the grab supers drop bursts themselves. Orbs fly
  up at a random angle (Random, so replay-recorded) and fall; Ikumi catches one by
  touching it (within 15 px, 0-50 px above her feet): small +10, medium +30, large +50
  to `m_stockCharge`; one that lands lies on the ground (0x1dc) and gives +8 if she is
  on it at its frame 4.
- **Stocks.** 100 charge = 1 stock, at most 8 (`m_stocks`, DrawGauge's 8 pips, coloured by
  tier: anims 0x27 for 0-2, 0x28 for 3-5, 0x29 for 6-8). Specials (236B/C, 623B/C, 214)
  have three versions: base at 0-2 stocks, `Stock3` at 3-5, `Stock6` at 6-8; the
  stronger two take one stock. 236A and 623A have only the base version.
- **Powered mode.** At 8 stocks, in a neutral ground state (pattern < 8), Vf8 starts
  0x12c by itself (ikumi.cpp:838). When 0x12c ends: `m_modeTimer` = 1260, `m_stocks` =
  0xa, `UseAltPatterns(1)`. For 1260 frames (orbs now add 10/30/50/5 frames instead):
  ikumi2.pat's faster frame data (same sprites, shorter durations on most normals and
  specials), UpdatePatternAlt/UpdateObjectsAlt, every special in its Stock6 version for
  free, 21436 strikes at once (0x13e-0x140), more damage (air throw 1200->1400, 41236C
  250/600 -> 500/700, grab supers 2000/3000/4100 -> 2800/3800/5500), tint cycling
  (`m_modeTintTimer`), afterimages, CPlayer unk138/unk13a = 2 every frame. No LV4,
  214214 or 21436 store during it. At 0: stocks and charge back to 0, base tables.

## Move list (motion -> command -> action)

| Motion | Command | Action | What it does |
|---|---|---|---|
| A / 2A / jA | - | 0xc8 / 0xcc / 0xcf | normals |
| B near (70 px) / far / 2B / jB | - | 0xc9 / 0xca / 0xcd / 0xd0 | normals, drop 3 orbs on hit |
| C / 2C / jC | - | 0xcb / 0xce / 0xd1 | normals (2C replays its active frames twice; jC 3 hits) |
| dash + A/2A/B/2B/C/2C | - | 0xe6/0xe9/0xe7/0xea/0xe8/0xeb | dash attacks; dash 2C is a hop |
| C + dir near grounded opp. | - | 0xdc -> 0xdd | throw, 900 |
| air 6C near airborne opp. | - | 0xf8 -> 0xf9 | air throw, 1200 |
| 236A | 0xa | 0xfd | rush (vx 2.5), strikes at 150 px |
| 236B | 0xb | 0xfe / 0x10a / 0x10d | as above; 1 / 2 / 3 hits |
| 236C (unk118 >= 500 or unk120) | 0xc | 0xff / 0x10b / 0x10e | spends 500 unk118 (250 under unk120) |
| 623A | 0x14 | 0x100 -> 0x103 | forward leap with effect 0x190, lands in 0x103 |
| 623B | 0x15 | 0x101 / 0x110 / 0x114 | leap, landings 0x103 / 0x112 / 0x116 |
| 623C (unk118) | 0x16 | 0x102 / 0x111 / 0x115 | as B, spends unk118 |
| 214A/B/C | 0x1e-0x20 | 0xfa-0xfc / 0x117-0x119 / 0x11a-0x11c | ground pillar 60/120/180 px ahead; 1 hit / 2 cycles / 4 cycles of 2 hits |
| 41236C | 0x48 | 0x107 -> 0x108 | command grab (grounded), 250+250, 2 big orb bursts |
| 41236 41236 + A/B/C | 0x96-0x98 | 0x12f/0x131/0x133 -> 0x130/0x132/0x134 | grab supers, LV1/2/3 |
| 214214 + A/B/C (1000 each, not in mode) | 0x6e-0x70 | 0x135/0x136/0x137 | summon a double: 236-rush / leap / pillar |
| 21436 + A/B/C | 0xaa-0xac | 0x138/0x139/0x13a | LV1/2/3: store a strike (m_storedSuperLevel) |
| 21436 any, strike stored | 0xaa-0xac | 0x13b/0x13c/0x13d | release it under the opponent, free |
| 21436 + A/B/C in the mode | 0xaa-0xac | 0x13e/0x13f/0x140 | LV1/2/3 strike at once |
| 236236236C, full gauge, HP < 3333 | 0x5e | 0x141 -> 0x142 | LV4 |
| (8 stocks, automatic) | - | 0x12c | powered mode start |
| 22C (shared) | 0x34 | 0xa7 / 0xab | shared |

Supers by button: C tries LV3, B LV2, A LV1, each falling back a level when the gauge is
short (0x131 accepts B or C, 0x12f any button; 21436 the same).

Priority in StartCommand: LV4, 214214, mode 21436, release, store, grab supers, 41236C,
623C, 623B, 623A, 214C/B/A, 236C, 236B, 236A, then dash, double jump, normals. No D move
(StartCommand never reads m_pressD; 22D = 0x35 is read but unused).

## Second tables (unk3464/unk3468 = m_altAnims/m_altPatterns)

- Loaded from ikumi\ikumi2.pat by LoadAltPatterns (Unk6a5eb0) from Load; ikumi.pat's
  tables are saved as ints in m_baseAnims/m_basePatterns (unk346c/unk3470) after
  CPlayer::Load. UseAltPatterns (Unk6ab6a0) swaps anims, all 64 objects' anims and
  m_patterns; m_altPatternsIn (unk3460) says which.
- **Pattern numbers mean the same moves in both tables.** ikumi2.pat has the same
  patterns minus 0x141/0x142 (LV4) and the same sprite sizes; only durations (shorter)
  and a few boxes differ (0x130/0x132/0x134 have no attack boxes there; their damage is
  DealDamage anyway). UpdatePatternAlt's switch is UpdatePattern's minus 0x141/0x142; the
  only code differences (cmpcases): 0xc8/0xeb jump-cancel conditions, 0xf9/0x108/0x130/
  0x132/0x134 damage, 0x134's orb facing at random, 0x100's cancel window (frame 7
  m_attackResult = 2 in base, removed in alt), 0x135-0x137 loop 5 times instead of 2,
  0x138-0x13a no longer set m_attackResult = 3 during their loop. 0x12c, 0x135-0x13a
  can't start during the mode, so their alt copies are dead code.
- UpdateObjectsAlt differs in: orbs (timer instead of charge), 0x1a4 (different loop
  frames; base has `unk3160 < 0` tests that are never true), 0x1ad 2 hits instead of 4,
  0x1b7 doesn't set m_patternVar2.

## Objects (all spawned by SpawnObject; sizes from ikumi.pat)

See patterns.txt. Groups: 0x190-0x19d move effects and 214 pillars; 0x19e mode aura;
0x19f-0x1a3 grab-super effects; 0x1a4-0x1a6 + 0x1ac-0x1ae the 214214 doubles; 0x1a7-0x1ab
21436 strikes; 0x1af-0x1b7 LV4; 0x1d6-0x1e0 orbs and bursts.

Shared objects every character has (not named here, left to the core agent): 0x1ef
(screen-space, 60,40, removed when pattern != 0x57, spawned by shared 0x57), 0x1f0 (by
0x53-0x56, bursts into 0x1f1/0x1f2 with plain rand() lifetimes; m_burstObjectOut), 0x1f3
(by shared 0x51, follows the player).

## CPU (CpuInput, identical to CShiori's byte for byte in source)

Writes commands 0xa-0xd, 0x14-0x16, 0x1e-0x20, 0x28-0x2a, 0x34, 0x5f, 0x78-0x7a,
0x82-0x84, 0/1 (dashes) and presses A-C. Ikumi has no 0x28-0x2a, 0x5f, 0x78-0x7a or
0x82-0x84, so those picks do nothing. **The CPU Ikumi never starts any super, the LV4,
41236C, 214214 or 21436**; it uses only normals, dashes, 22C, 236, 623, 214 (their
stock versions follow from her stocks, and it can still reach the mode by collecting
8 stocks).

## Bugs and oddities

- ReadCommand 0x96 (ikumi.cpp:1043-1078, same in nanase.cpp): state 5 checks "forward"
  (x6 == 5, sets 8, a dead state) before "down-back" (x6 == 5 -> 6). Effective motion:
  4 1 3 6 4 1 3 then any button; pressing 6 right after the second 4 kills it. The
  final 6 is never needed.
- ReadCommand 21436 (ikumi.cpp:1080-1106): a button on the same frame as the final 6
  gives 0xa0 + button, which StartCommand ignores; the button must come on a later frame.
- Ikumi's 0x14-0x16 is 623 (6, 2, 3 + button, 55 frames). Kano's ReadCommand writes 0x14
  from its 421 loop on a same-frame button: there it is a stray number.
- The constructor calls UseAltPatterns(0) before `unk3460 = 0` (ikumi.cpp:14-15): it
  reads the byte uninitialised (harmless unless the heap byte is exactly 1).
- LoadAltPatterns runs on every Load (new match, replay restart) and allocates new frame
  arrays each time without freeing the old ones; CPlayer::Load loads ikumi.pat once
  (unk30e8). A leak, no effect on play.
- ikumi.pat has two records for pattern 0xf8 (7 frames, then 2 frames); the second
  overwrites the first (and leaks it). Patterns 0xd2, 0xd6, 0xd8, 0xed, 0x109, 0x10c are
  in ikumi.pat but no code starts them.
- 214A/B/C's `frame == 7 && unk3138 > 0` replay never runs: m_patternVar1 is 0 there.
- Mode end mid-action: Vf8 swaps the tables back whatever action is running.

## Observations on shared members/actions (for the core agent)

- `unk14c`: a freeze timer; every super sets its own to 0x78 and the opponent's
  UpdatePattern/UpdateObjects skip while it is > 0 (the super flash). CScene3 counts it down.
- `unk14a`: set on the opponent during holds (0x3c throws, 0x5dc in 0x108, 0x1e per hit in
  0x130) and cleared at the end: hit-stop / held.
- `unk118`/`unk120`: C-version specials and 0x34 (22C -> 0xa7/0xab) need unk118 >= 500 or
  unk120 > 0; they spend 500 (250 while unk120 != 0). Shared 0x51 drains 0.8/frame and
  0x53 30 while unk120 != 0.
- `unk13e`/`unk140`: LV4 0x142 sets its own unk13e = 3 and the opponent's unk140 = 3.
- `unk138`/`unk13a`: set to 2 every frame of the powered mode (Vf8).
- `m_attackResult = 2` written by a move itself (0x100 frame 7) opens a cancel window
  (StartCommand cancels from pattern >= 0xc8 only if m_attackResult >= 2).
- PlayerObject: `unk84` = hits the object can still land (objects end early when 0);
  `unk80` = the object's contact result (3 = hit, > 0 any); `unk88` = still updated
  during its owner's unk14c; `unk86` = skip update; `unk8c` = 0x7530 on 0x1ef.
- EffectDesc: `unk28 = 1` on the LV4 figures 0x1b3-0x1b6 (unknown).
- Vf8 (virtual slot): per-frame hook before UpdatePattern. Ikumi's: auto mode start at
  8 stocks, mode timer and tint, orb bursts on hit. DrawGauge: stock pips and charge bar,
  or the mode's timer bar.
- Ikumi has no case 0xa1/0xa2 in her switches (Kano has).

## Not determined

- What the doubles, figures and strikes look like beyond sprite sizes (no sprites
  decoded): the names describe behaviour. "Orb" is a descriptive word for the small
  collectible sprites (7x8, 26x25, 26x40).
- 0x1a9 has attack boxes in ikumi.pat but its code sets unk84 = 0, so it never hits.

# CMishio (src/mishio.cpp, src/mishio_vf6.cpp)

## The power-up (m_powerUp, unk3158)

Mishio's specials are locked behind a two-bit power-up:

- **0**: none. 623 + A/B/C (0xfa-0xfc) is her only special. If it connects (hit or
  guard, `m_attackResult > 0`), at its end she gets power-up 1 or 2, 50/50 through
  `Random(0, 1000) < 500` (vf6:3536), so it is recorded in replays.
- **1** (bit 0): opens 236, 214 (and its follow-ups), 6C, 623's power-1 version, ground
  236236 and 214214.
- **2** (bit 1): opens 412, 22A/22B, 6B, 623's power-2 version, 641236 and air 236236.
- **3** (both): set by the LV4 for `m_powerUpTime` = 4500 frames (vf6:7317); Vf8 counts
  it down (not during the LV4 itself) and drops to 0 at the end. Moves don't use it up.

Most moves of a set put the power-up back to 0 at their end (`if (m_powerUp == 1)
m_powerUp = 0`); exceptions, which keep it: 236A/B/C (0xfd-0xff), 214 without a
follow-up (0x11a/0x11b don't reset; 0x10b after a follow-up does), 412A (0x10c, while
412B/C reset it), 6B and 6C. Whether those are meant is not known.

DrawGauge draws the icon (anims 0x27 none, 0x28 power 1, 0x29 power 2, 0x2a both,
5 frames at m_powerUpIconTimer / 6) at (0xb, 0xc4) from the side, and, while
m_powerUpTime > 0, a bar (anims 0x2b frame + 0x2c fill, width * time / 4500) at the
power gauge's top (0x31, 0x1f). The icon timer advances in DrawGauge, i.e. per drawn
frame, not per tick.

Vf8 (the per-frame hook CScene3 calls before UpdatePattern): the power-up timer, and
while powered up a particle effect (CGame effect 0x22 for power 1, 0x24 for power 2,
either at random for 3) near her every 2 frames outside actions 0x32-0x95; in mode 3
it also cycles Tint every 0x12 frames. Mishio's Vf8 has no gauge regeneration or idle
bonus (Kano's does). Its particle positions use `CPlayer::Random`, 2 draws (3 in mode
3) every 2 frames while powered up: visual-only, but they consume replay words.

## Move list (motion -> command -> action)

Commands come from Mishio's ReadCommand (mishio.cpp:674-1052); the motions are the same
parser as Kano's except where noted. Gauge cost for supers: the button picks the
highest version the gauge allows, falling back: 236236C with 2000 gauge gives the B
version, with 1000 the A version (mishio.cpp:141-210). Kano's StartCommand matches the
exact button instead.

| Motion | Command | Needs | Action | What it does |
|---|---|---|---|---|
| 5A / 2A / jA | - | | 0xc8 / 0xcc / 0xcf | |
| 5B close (<90 px) / far | - | | 0xc9 / 0xca | |
| 2B / jB | - | | 0xcd / 0xd0 | |
| 6B | - | power 2 | 0xd2 | hop kick (vx 1.0, vy -1.3) |
| 5C / 2C / jC | - | | 0xcb / 0xce / 0xd1 | |
| 6C | - | power 1 | 0xd3 | |
| dash A/B/C, dash 2A/2B/2C | - | in 0xa3 | 0xe6-0xe8, 0xe9-0xeb | B/C jump-cancel on hit |
| C + direction, close | - | grounded opponent | 0xdc -> 0xdd | throw: swaps sides, no DealDamage call |
| 6C in the air, close | - | airborne opponent | 0xf8 -> 0xf9 | air throw, DealDamage(0x47e) |
| 623 A/B/C | 0x14-0x16 | none | 0xfa / 0xfb / 0xfc | grants power 1 or 2 on contact; C costs unk118 |
| 623 A/B/C | 0x14-0x16 | power 1 | 0x111-0x113 | sweeping arc 0x1b5 (C: 0x1bc then 0x1b5) |
| 623 A/B/C | 0x14-0x16 | power 2 | 0x114-0x116 | arc 0x1b6; B adds slow orb 0x1ba; C two arcs |
| 623 A/B/C | 0x14-0x16 | power 3 | 0x117 / 0x117 / 0x119 | plain hit; 623B starts 0x117, so 0x118 is unreachable |
| 236A | 0xa | power 1 | 0xfe | 4 hits in place |
| 236B (236C without unk118) | 0xb, 0xc | power 1 | 0xfd | rush vx 3.0, 6 hits |
| 236C | 0xc + unk118 >= 500 | power 1 | 0xff | rush vx 3.2, 99 hits, costs 500 (250) unk118 |
| 214A / B / C | 0x1e-0x20 | power 1 | ground 0x101 / 0x102 / 0x100, air 0x103 / 0x104 / 0x105 | flight: ground up-forward / up / turn round + up-forward; air forward / down-forward / down. A button + direction while flying: follow-up 0x106 (8), 0x107 (9, 7 turns), 0x108 (6, 4 turns), 0x109 (3, 1 turns), 0x10a (2), one only; then 0x10b. Without: 0x11a / 0x11b |
| 412 A/B/C (back, down-back, down) | 0x28-0x2a | power 2, no shot out | 0x10c / 0x10d / 0x10e | shot 0x190 fast 1 hit / 0x191 slow 3 hits / 0x192 accelerating 99 hits (C costs unk118) |
| 22A / 22B | 0x32 / 0x33 | power 2, no field out | 0x10f / 0x110 | object 0x198 at the opponent (A: at most 150 px away; B: at least 150 px) that keeps spawning hits 0x199 |
| 22C | 0x34 | shared | 0xa7 / air 0xab | shared action (needs unk118 >= 500 or unk120, on a guarded/hit attack) |
| 236236 A/B/C, ground | 0x64-0x66 | power 1 | 0x12c-0x12e | rush vx 3.5, 99 hits, first hit freezes the opponent 0xb4 frames |
| 236236 A/B/C, air | 0x64-0x66 | power 2 | 0x13b-0x13d | 1 / 3 / 5 orbs down at 40-60 deg that land and keep hitting |
| 214214 A/B/C | 0x6e-0x70 | power 1 | 0x12f-0x131 | super flight, follow-ups 0x132 (8), 0x133 (9), 0x134 (6), 0x135 (3), 0x136 (2), up to level + 1; recovery 0x137 |
| 641236 A/B/C | 0x78-0x7a | power 2 | 0x138-0x13a | orb 0x1a1 overhead; holding the same button charges (up to 9 loops); three shots 0x1a2-0x1a4, charged 0x1ae-0x1b0 |
| B 5 B 2 5 C A | 0x62 | HP < 3333, 3000 gauge | 0x13e | LV4: burst 0x1b3, then power-up 3 for 4500 frames |

D: Mishio's StartCommand has no D branch at all (no D normal, no D special).

Shared commands seen in her parser (core agent's): 0xa-0xd 236+button, 0x14-0x17
623+button (forward, down, down-forward; the button may come on the down-forward
frame), 0x1e-0x21 214+button, 0x28-0x2b back, down-back, down + button ("412"),
0x32-0x35 22+A/B/C/D (0x35 only from action 0x60), 0x64-0x67 236236, 0x6e-0x71 214214,
0x78-0x7b 641236 (forward, back, down-back, down-forward + button; the down between
isn't required), 0xaa-0xad 21436+button and 0xa0-0xa3 (button on its last forward
frame): parsed but unused by Mishio's StartCommand; 6 double jump, 0/1 dashes
(left-left/right-right).

## CPU (CpuInput, mishio.cpp:1054-1921)

Identical to Shiori's (diff of the two functions with the class names stripped is
empty). For Mishio it writes 0x14/0x15 (623A/B: `Random(0, 2) + 0x14`, never 623C),
0xa-0xc, 0x1e-0x20, 0x28-0x2a, 0x78-0x7a, 0x34, plus 0x5f and 0x82-0x84, which
Mishio's StartCommand ignores. It never checks m_powerUp, so 236/214/412/641236 do
nothing unless the 623 has granted the matching power. It never writes 236236,
214214, 22A/22B or the LV4.

## Oddities

- 623B with power 3 starts 0x117 (623A's) instead of 0x118 (mishio.cpp:273); 0x118's
  code (a vx 2.5 lunge) is unreachable.
- 0xd4-0xd6 (a falling attack that bounces off or lands with a shake) are never
  started: no StartCommand branch (Kano's j2C equivalents are started by down+button
  in the air).
- Object 0x1bb (a 10-hit version of 0x1ba) is never spawned.
- 0xfa, 0xfb, 0x111, 0x112, 0x114, 0x115, 0x117, 0x118 set m_patternVar1 = 5 and never
  read it (their C versions use it as a hit flag).
- 0x10d, 0x10f, 0x110 and 0x13b-0x13d set `m_attackResult = 3` on every animation frame, so they
  count as "hit" for the cancel rules (StartCommand's `m_attackResult >= 2`) even when
  nothing hit.
- 214's follow-up limit works through StartPattern zeroing m_patternVar2 before the
  `++`: the follow-up action ends with `pattern = 0x10b` without StartPattern and a
  second `++`, so 0x10b sees 2 and allows no more.
- 0xdd (the ground throw) has no DealDamage call: it moves the opponent behind her and
  sets them to 0x34; any damage must come from the frame data.
- Objects 0x1b5/0x1b6/0x1bc/0x1bd (the 623 arcs) draw `Random(0, 30)` every frame they
  live, 0x198 and 0x19c-0x1a0 draw two per sparkle, 236236B/C one per game frame in frames
  0x16-0x1e (three when it spawns a sparkle): visual, but replay words.

## Shared members/actions (observations only)

- `PlayerObject::unk84` is set to the object's hit count when it starts (1, 3, 0x63,
  2-4 for the air orbs, 5 for 0x1ba) and `unk80 > 0` means it hit this frame: likely
  "hits left" and "hit this frame".
- unk118/unk120: C versions of 623, 236, 412 need `unk118 >= 500 || unk120 > 0` and
  take 500 (250 when unk120 != 0) off unk118, with effect 0x21; shared 0x53 takes 30 if
  unk120. Also the condition for 22C -> 0xa7.
- Supers set `unk14c = 0x78` (the super freeze: the opponent's UpdatePattern and
  UpdateObjects return while it is above 0) and the first hit of 236236 sets the opponent's `unk14a = 0xb4` and her
  own `0x5a`.
- `CGame::Unk4080c0(0xf)` is called every frame in the level-3 supers (0x13a, 214214C's
  follow-ups): a screen effect.
- Shared objects 0x1ef (from 0x57), 0x1f0-0x1f2 (from 0x53-0x56), 0x1f3 (from 0x51) are
  in Mishio's UpdateObjects as in everyone's; left to the core agent.

## Not determined / left out

- unk316c, unk3170, unk3374: only zeroed (constructor, Reset, RemoveObject); unused.
- Vf8 and DrawGauge are virtual slots: described above, not renamed.
- What the two powers are in the game's terms (their effects 0x22/0x24 differ only in
  particle speed); named by number.
- 0x11a vs 0x11b: identical code, different animations; which looks like what isn't
  visible from the code (named k214Recovery / k214Recovery2).

# CShiori (src/shiori.cpp, src/shiori_vf6.cpp)

Named: 11 members (all of 0x3138-0x3358), 110 action numbers (63 player actions >= 0xc8,
47 objects). Left: object 0x19b (dead copy, below), the shared objects 0x1ef/0x1f0-0x1f3
(suggestions below), Vf8 and DrawGauge (virtual slots). No commands.txt: every command
Shiori reads is a shared ID (0x5f is read only by Shiori, but kano/ikumi/mishio/mizuka/
mizukab write it too).

Naming used: strengths A/B/C at consecutive numbers -> `k236A/B/C`; air versions
`kAir236A`; supers `k641236A/B/C`, `k214214A/B/C`, `k21436A/B/C` (A = LV1, B = LV2,
C = LV3); `kLv4`, `kLv4Connected`; normals `k5A`, `k5BClose`/`k5BFar` (0xc9 within 70 px),
`k2A`, `kJumpA`; dash attacks `kDashA`, `kDash2A`; throws `kThrow`/`kThrowConnected`,
`kAirThrow`/`kAirThrowConnected`; never-started code `kUnused...`; objects `kObj<move><role>`.

## Commands (ReadCommand, shiori.cpp:515-891)

Input history bits are absolute (1 right, 2 left, 4 down, 8 up); `(facing == -1) + 1` is
forward, `2 - (facing == -1)` back, `+ 5` down-forward, `6 - ...` down-back. Checked in
this order; the first match returns:

| cmd | motion | window | note |
|---|---|---|---|
| 0x5f | 2 3 6 2 3 6 B C, gauge exactly 3000 at the first 2 | 90 | LV4 |
| 0xaa-0xad | 2 1 4 3 6 + A-D (gauge >= 1000) | 90 | a button on the same frame as the 6 gives 0xa0-0xa3 instead (shiori.cpp:566), which StartCommand ignores: the super fails |
| 0x78-0x7b | 6 4 1 3 + A-D (641236; 2 and the last 6 optional), gauge >= 1000 | 75 | |
| 0x65 | 2 3 6 2 3 6 B, gauge exactly 3000 | 90 | nothing handles it in Shiori: with a full gauge 236236B does nothing (it would otherwise read as 236B) |
| 0x6e-0x71 | 214214 + A-D, gauge >= 1000 | 90 | |
| 0x14-0x17 | 6 2 3 + A-D | 60 | |
| 0xa-0xd | 2 3 6 + A-D | 45 | |
| 0x28-0x2b | 4 1 2 + A-D (back, down-back, down) | 45 | not 421 (Kano's 0x3c is 4 2 1) |
| 0x1e-0x21 | 2 1 4 + A-D | 45 | |
| 6 | up after not-up, within 5 frames | 5 | double jump |
| 0x35 | 5 2 5 2 D, starting while pattern 0x60 | 90 | |
| 0x34 / 0x33 / 0x32 | 5 2 5 2 + C / B / A | 90 / 45 / 45 | |
| 1 / 0 | right, neutral, right / left, neutral, left | 45 | dashes |

## Move list (StartCommand, shiori.cpp:103-475)

"EX" = needs unk118 >= 500 or unk120 > 0 and spends 500 of unk118 (250 if unk120), with
effect 0x21; without it the C command falls back to the B version.

| input | cmd | action | what it does |
|---|---|---|---|
| 5A / 2A / jA | - | 0xc8 / 0xcc / 0xcf | |
| 5B | - | 0xc9 within 70 px, else 0xca | |
| 2B / jB | - | 0xcd / 0xd0 | jB loops once |
| 5C / 2C / jC | - | 0xcb / 0xce / 0xd1 | 5C: 5 loops, hits on 3, effect 0x190; jC 3 hits |
| 4C/6C close | - | 0xdc -> 0xdd | ground throw, 1000 damage |
| j6C close | - | 0xf8 -> 0xf9 | air throw, 1100; a miss continues as jC |
| A/B/C, 2A/2B/2C in forward dash | - | 0xe6-0xe8, 0xe9-0xeb | dash attacks; dash C hops |
| 236A/B/C | 0xa-0xc | 0xfa-0xfc; air 0x106-0x108 | attack object in front of her (0x191; air 0x198 kept at her front); C (EX): three 0x1ab / 0x1ac at three heights over 40 frames. A holds longer (5 loops) than B (3) |
| 623A/B/C | 0x14-0x16 | 0xfd-0xff (ground only) | standing multi-hit: 5 / 9 / 18 hits; C is EX, effect 0x1a1 |
| 412A/B/C | 0x28-0x2a | ground 0x109-0x10b; air 0x100-0x102 | ground: three 0x1a2 fall from the sky, 80-130 / 160-210 / 240-290 px ahead (the button is the distance; C needs and spends no EX). Air: she floats, two 0x192 fall diagonally to the ground; air C (EX) 0x194 with 4 hits |
| 214A/B/C | 0x1e-0x20 | ground 0x103-0x105; air 0x10c-0x10e | calls a creature behind her (one at a time, m_summonOut): A 0x1b1 hovers by her then charges; B 0x1b2 hovers and shoots 0x199 three times (air B: 0x1c3 stays put and shoots); C (EX) 0x1c6 drifts forward, then 0x1c5 stays and hits 2 per cycle for 4 cycles. A creature breaks into debris 0x19c-0x1a0 when Shiori is hit (pattern 0x32-0x95) or it is struck (object unk80 4 or 5) |
| 641236A/B/C | 0x78-0x7a | 0x12f-0x131 | LV1-3, ground. Her own body hits 5 / 15 / 30 times; each frame the hit is re-armed with a 50% Random (recorded); visual column 0x1ad/0x1ae(/0x1af) |
| 214214A/B/C | 0x6e-0x70 | 0x132-0x134 | LV1-3, ground. A mover 0x1b5/0x1b6/0x1b7 travels along the ground dropping hitting objects 0x1a4/0x1a5/0x1a6: 3 / 6 / 15 of them |
| 21436A/B/C | 0xaa-0xac | ground 0x13b-0x13d, air 0x138-0x13a | LV1-3. A spray of 0x1b3 shots, one per 6 frames at angle Random(0,90)-45 and speed 2.6-3.0: 15 / 27 / 50 |
| D | - | 0x135 | ground, only while m_dObjectTime == 0: object 0x1a7 on her body for 900 frames, re-armed with a hit every frame; drawn as a bar under the gauge |
| 236236BC, HP < 3333, gauge 3000 | 0x5f | 0x13e -> 0x13f | LV4. Object 0x1b8/0x1b9 in front of her; if it hits during 0x13e it holds the opponent (0x1bc, 0x1ba, Random jitter around m_lv4HoldX/Y) and she goes to 0x13f: leaps to the opponent, her hit spawns 0x1bd on them, 360 frames rising, then 0x1bd deals DealDamage(5000, 700) and knocks down (opponent 0x3f) |

Level selection differs from a strict "button = level": 641236C with 2000 gauge gives
LV2, with 1000 LV1 (StartCommand tests `0x7a && >= 3000`, then `0x79||0x7a && >= 2000`,
then any of the three `>= 1000`). Same for 214214 and 21436. A is always LV1.

Never started (no StartCommand or CPU path): 0x12c (3000-gauge super that calls the
214B creature), 0x136/0x137 (5D as 2000/3000 supers, objects 0x1a8/0x1a9, m_dObjectTime
4800, which DrawGauge would draw 4/3 the bar's width). Objects never spawned: 0x195 (a
hovering creature that turns into 0x199 after 520 frames) and 0x19b (bounces, fades
via CGame::Unk407ce0 over 160 frames: the object Kano's Vf8 spawns as its idle reward,
copied here unused).

## Vf8 and DrawGauge

- Vf8 (shiori.cpp:505) is empty: Shiori has no per-frame gauge regeneration or timers.
- DrawGauge (shiori.cpp:477) draws anims 0x2b (frame) and 0x2c (fill, width *
  m_dObjectTime / 3600) under the power gauge while m_dObjectTime > 0.

## CPU (CpuInput, shiori.cpp:893-1760; byte-identical in kano/ikumi/mishio)

Commands it writes: 0x16 (623C) and 0xc (236C) when unk118 > 500; 0xa-0xc (Random);
0x14/0x15; 0x1e-0x20 (Random); 0x28, 0x29, 0x2a, 0x28-0x2a; 0x78-0x7a (Random,
gauge >= 1000); 0x5f (gauge == 3000); 0x34 (22C); dashes as `m_command = facing == 1`
(forward, also air) and `-((facing == 1) - 1)` (back). Also 0x82-0x84 (shiori.cpp:1595,
opponent > 200 px away): no command of these four characters; Mizuka, MizukaB and
Misuzu read 0x82, so the routine looks copied from one of theirs.

So the CPU never starts: 214214 (0x132-0x134), 21436 (0x138-0x13d), the double jump (6),
22A/22B/22D, and D only by mashing it in hitstun (`m_pressD` random at :940-941, cleared at :943 against an attack starting near her).
When does it pick what:
- In 0xa8/0xa9 (shiori.cpp:979-1018), by distance: 623C, 236C, 641236, LV4 near; 236C,
  LV4 mid; 236A-C, LV4 far.
- When the opponent is in 0xa8-0xaa (15% x unka8): 623C, 236C, 641236, else
  m_cpuAction 2.
- After its own attack connects (m_attackResult > 1, 25% x unka8), by its pattern
  (0xc8-0xd1, 0xe7, 0xe8): chains into normals, 623A/B, 641236, 236A, 214, 22C, LV4, 412.
- Otherwise by distance and heights (shiori.cpp:1534-1694).
- 22C (0x34) from 0xfa-0xfc and 0x10e-0x110 when the opponent is in 0x96-0x9c
  (shiori.cpp:1077); 0x10f/0x110 aren't Shiori actions.

m_cpuAction states (shared routine): 1 after a normal (cleared below 0xc8), 2 wait while
unk170 == 1 (unk14e = 0x1e), 3 defensive (no air attacks; much higher chance to set the
guard timer unk14e = 0x3c, :912), 4 jump then air dash, 5 forward dash, 6->7 dash then A,
8->9 dash then B, 0xa->0xb dash then C, 0xc 2A.

Bugs: `m_pressA = 3` (shiori.cpp:974) never equals the 1 StartCommand tests, so that
branch only crouches; `Random(0, 1) == 0` (e.g. :1236) is always true. CpuInput uses
CPlayer::Random, which is harmless only because a recorded fight has no CPU.

## Shared CPlayer members and actions seen (for the core agent)

- unk118 / unk120: the EX resource; C specials and 22C need unk118 >= 500 or
  unk120 > 0 and take 500 (250 with unk120) off unk118; shared 0x53 takes 30 when
  unk120 != 0 (shiori_vf6.cpp:1475).
- unk14c: set to 0x78 at every super's flash; the opponent's UpdatePattern and
  UpdateObjects stop while it is > 0 (super freeze).
- unk15c: specials need < 2 (D too), jump-cancels < 3, dashes == 0.
- unk158: 1 after a forward dash 0xa3, keeps the dash's vx into a normal; cleared by most
  actions. unk159/unk15a: air dashes / air jumps used (StartCommand :301-351).
- unk13e = 3 in 0x13f and 0x1ba; Unk410a80(0x32, 3) every frame of the LV4.
- unk1a0 / unk1a4: the CPU's hold-right / hold-left timers. unka8: the CPU's
  difficulty factor. unk14e: the CPU's guard timer.
- PlayerObject::unk84 is the object's hits left (set 1, 3, 4, 0x63); unk80 the result of
  the frame (scene3.cpp: 2/3 hit or guarded, 4 clashed with an object, 5 struck), reset
  when the animation frame advances.
- Opponent actions set by Shiori: 0x6b ground throw victim, 0x67 air throw victim,
  0x56 thrown down, 0x79 LV4 victim, 0x3f LV4 knockdown.
- Shared objects in Shiori's switch: 0x1ef (shared 0x57 spawns it, removed when the
  player leaves 0x57: suggest kObjDownDust or similar after the core agent's 0x57), 0x1f0
  (shared 0x53-0x56, bursts into 0x1f1 x6 / 0x1f2 x4 when the player leaves those
  actions or passes their frame 1: suggest kObjBurst, kObjBurstPiece, kObjBurstPieceBig),
  0x1f3 (shared 0x51, follows the player).

## Oddities

- Constructor: `m_rivals[1] = 7;` then `m_rivals[1] = 0xb;` (shiori.cpp:38-39); the 7
  is lost, probably meant for another slot.
- 0x108 (air 236C) adds 0x2d gauge twice on its first frame (shiori_vf6.cpp:3900, 3905).
- Debris 0x19c-0x1a0 and 0x1f1/0x1f2 take lifetimes and speeds from plain rand();
  they only matter through the 64-slot object table.
- 0x1b3's speed is Random(0x1e, 0x19) * 0.1, p1 > p2: 3.0 down to 2.6.
