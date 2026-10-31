# CKaori, CNanase, CEXNanase, CNagamori: notes

Statements are **observed** in the source unless marked *inferred*. Motions are in numpad
notation for a character facing right. `ReadCommand` scans the input history oldest to
newest (`m_inputPos` is the next slot to write, `src/player.cpp:1084-1096`); history bit 1
is right and 2 left on screen (`m_inputX` is absolute, `player.cpp:1042-1052`), so
`(facing == -1) + 1` is "forward". A command's button is its base + 0 (A), 1 (B), 2 (C),
3 (D). Supers pick their level from the button and cap it by the gauge (C tested first at
>= 3000, then B|C at >= 2000, then any at >= 1000); I named those `Lv1/Lv2/Lv3`.
`tools4/motions.py` in the scratch decodes every `ReadCommand` loop mechanically.

Names chosen to be the same in all four classes where the code is the same:
`m_patternVar1-3` (unk3138/313c/3140: zeroed by every class's `StartPattern`; Ayu's
agent picked the same name), `m_particleBurstOut` (the flag guarding object 0x1f0),
`m_objectState`/`m_objectTimer` (the first two per-object int arrays), and the shared
objects `kObjLv4VictimOverlay` 0x1ef, `kObjParticleBurst` 0x1f0, `kObjParticle` 0x1f1,
`kObjParticleSlow` 0x1f2, `kObjLaunchFx` 0x1f3 (every character has them; the core agent
may want one name for all 24).

## Kaori (CKaori)

Her CpuInput is Akane's table (memory note); her StartCommand is Akane's shape too.

| Input | Action | What it does |
|---|---|---|
| A, B (close < 50 px / far), C | 0xc8, 0xc9/0xca, 0xcb | normals |
| 2A, 2B, 2C | 0xcc-0xce | |
| j.A, j.B, j.C | 0xcf-0xd1 | land into 0xd |
| C + direction, < 30 px, opponent standing | 0xdc -> 0xdd | throw, 1200 |
| j.C + forward, < 100 px, opponent airborne | 0xf8 -> 0xf9 | air throw, 1400; whiff continues as j.C |
| 66 | 0xfa | her forward dash is a step (vx 2.5); A/B/C/2C on frames 5-6: 0x103/0x107/0x104/0x105 |
| 44 then 66 on landing | 0xa4 -> 0xfb | longer step (vx 4.0), same follow-ups |
| 214A / B / C(unk118) | 0xfd / 0xfe / 0xff | 2-hit attack; B moves forward; C costs unk118 |
| 623A / B / C(unk118) | 0x100 / 0x101 / 0x102 | stays in place, hitting object 0x19a / 0x190 / 0x19b at x+40, frame 8 held 6 / 10 / 7 loops |
| 236236 + button | 0x12c/0x12e/0x130 -> +1 on hit | strike, then she is put left of the opponent (facing forced to 1) for a 3-object sequence 0x192-0x194 (Lv3: 0x195-0x197 burst into sparks) |
| 214214 + button | 0x132/0x134/0x136 -> +1 | rush (vx 4.0/4.3/4.6), on hit holds the opponent (0x48): 6/15/15 hits |
| 6413 + button | 0x138-0x13a | jumping super, hits at frames 12 and 16 |
| 666 + D, gauge 3000, HP < 3333 | 0x13b -> 0x13c | LV4; connects when m_attackResult is 6 at frame 6; 5000 damage, opponent dropped from y -640 |

Oddities:
- Kaori never enters the shared forward dash 0xa3 (66 gives 0xfa), so her dash attacks
  0xe6-0xeb (`kaori.cpp:271-346`) are unreachable, and so are CPU actions 6-0x11
  (`kaori.cpp:1006-1090`), which wait for pattern 0xa3. *Inferred:* a CPU in action 6 keeps
  stepping (0xfa is above 0x9e, so the reset at `kaori.cpp:976` doesn't fire).
- Unreachable cases: 0xd2 (dive), 0xd3 (air attack, only after the unused 0xf0), 0xd5,
  0xd6 (no 0xd4 exists), 0xf0/0xf1 (a second air throw), 0x106.
- `unk3144` is never written but by the constructor and Reset (0); 6413 needs it 0
  (`kaori.cpp:118-130`). In Akane the same slot is set by her objects; here it is a
  leftover. Left unnamed.
- `unk334c[]` is only ever zeroed. Left unnamed.
- 236236 (0x12d): if the opponent is at x < 40 it is pushed 40 to the right first
  (`kaori_vf6.cpp:4094-4097`).

## Nanase (CNanase)

She fights with a sword (*inferred* from the code: it is thrown, lands, lies on the floor
and is picked up). While she holds it the game uses `nanase.pat`; once thrown,
`UsePatterns2(1)` swaps `anims` (hers and every object's) and `m_patterns` for the tables
`LoadPatterns2` read from `nanase\nanase2.pat`, and `UpdatePattern`/`UpdateObjects` hand
over to `UpdatePattern2` (Unk47c130) / `UpdateObjects2` (Unk497540). The pattern numbers
mean the same moves in both tables; only some moves exist in one (armed: 214, 236, 623,
214214, 41364136, LV4, grab follow-ups; unarmed: 236236). `m_swordThrown` (unk344c) and
`m_usingPatterns2` (unk3458) are always set together. Picking up: stand or walk (pattern
< 3) within 30 px of the sword (object 0x194) and press D: pattern 0x12b, back to
`nanase.pat` (`nanase.cpp:2742-2748`).

| Input | Action | What it does |
|---|---|---|
| A, B (< 70 px close), C, 2A-2C, j.A-j.C | 0xc8-0xd1 | normals (armed 2C moves her 50 px) |
| C + direction / air C + forward | 0xdc/0xdd, 0xf8/0xf9 | throws 1200 / 1400 |
| 66 then A/B/C (2A/2B/2C) | 0xe6-0xe8 (0xe9-0xeb) | dash attacks during 0xa3 |
| 41236A (any button unarmed) | 0xfa -> 0xfb | command grab; armed follow-ups during 0xfb: 236A -> 0x106, 236B -> 0xfc (4500 x height factor), 236C with gauge 3000 and HP <= 3333 -> 0x132 (a second LV4, 6500 x height) |
| 41236B / C, armed | 0x107 / 0x108 -> 0xfb | the same grab |
| 236A / B / C(unk118), armed | 0xfd / 0xfe / 0xff | dashing 2-hit attack, follow-up on hit |
| 623A / B / C(unk118), armed, also in the air | 0x100 / 0x101 / 0x102 | rising slash that throws the sword (0x190, C: 0x19d) at frame 13 |
| 214A / B / C(unk118), armed | 0x103 / 0x104 / 0x105 | ground strike with pebbles; C sends the shockwave 0x1ad (rocks 0x195-0x198) |
| 214214 + button, armed | 0x12c-0x12e | one big hit; Lv3 freezes the opponent 360 frames |
| 236236 + button, unarmed | 0x12f-0x131 | dash vx 6.0 |
| 41364136 + A/B/C, armed | 0x134-0x136 | throws the super sword 0x1a3/0x1a4/0x1ac (unarmed after) |
| 41364136 + D, gauge 3000, HP < 3333, armed | 0x133 | LV4 power-up: object 0x1af for `m_lv4Time` = 3000 frames: half damage taken (`m_defense` 0.5), unk138/unk13a = 2, afterimages; DrawGauge shows the time left |
| D next to the sword | 0x12b | pick it up |

Oddities:
- The 41364136 parser (`nanase.cpp:613-645`) has a slip: at state 5 a forward input
  either completes the command (with a button) or sets state 8, which nothing continues.
  Effective motion: 4 1 3 6 4 1 3 + button.
- `Random(0, 1)` is always 0 (`player.cpp`: p1 + (p2 - p1) * rand() / 0x8000), so every
  `Random(0, 1) + 0x199` spawns 0x199 and the pebble 0x19a is never spawned in practice.
  Each such call still reads a replay word.
- Unreachable: 0xd2-0xd6; nanase2's 0x109/0x10a (the same code as Nagamori's 0x109/0x10a)
  and nanase2's versions of 0xfc, 0xfd-0xff, 0x103-0x106, 0x12c, 0x132 (gated by
  `m_swordThrown == 0`). Note 0x106 means different code in the two tables; only table 1's
  (the grab follow-up) is reachable.
- *Inferred:* if 64 objects push the lying sword (0x194) out of the table
  (`AdvanceObjectHead`), she stays unarmed for the round: nothing else resets the tables
  but Reset.
- `unk334c[]` only zeroed. Left unnamed.

## EX Nanase (CEXNanase)

No sword and no second table. A grappler whose holds let the opponent guess.

| Input | Action | What it does |
|---|---|---|
| normals, throws, dash attacks | as Nanase | 5B close is < 50 px |
| 6C | 0xd2 | hop forward attack |
| 41236A / B / C | 0xfc / 0xfd / 0xfa | striking grab / anti-air grab / grab; all lead to the hold 0xfe |
| in 0xfe, at its end | 236A or 214A -> 0xff, 236B or 214B -> 0xfb, nothing -> 0x101 | slam 1500 / toss / release hit |
| in 0xff at frame 10 (1000 gauge) | 236A|214A -> 0x12c, 236B|214B -> 0x132 | 5-hit chain / 1800 hit (facing flips) |
| in 0x12c (1000) | 236236A|214214A -> 0x12e, B -> 0x133 | throw 4200 / jump slam 4500 |
| in 0x132 (1000) | 236236A|214214A -> 0x13e, B -> 0x13f | drag to the wall 3000 / ground hit |
| 214A / B / C(unk118) | 0x10f-0x111 | hit objects 0x191-0x193 at body height, 3/2/3 loops (cancellable: m_attackResult forced to 3) |
| 623A / B / C(unk118) | 0x112-0x114 | rush vx 2.5/2.8 with an attached object 0x194-0x196; C has 15 hits |
| 236236 + button | 0x135/0x137/0x139 -> +1 | running grab super: 2300/3300/4900 |
| 214214 + button | 0x13b-0x13d | ground hit 60 px ahead (0x19c-0x19e) |
| automatic | 0x140 | awakening (Vf8, `exnanase.cpp:405-410`) |

The escape guess: during 0xfe (frame 2), 0xff (frames < 10), 0x12c (< 10) and 0x132 (< 10)
the opponent's first A/B/C press goes to `m_patternVar1` (1/2/3). If Nanase then picks the
A branch and they pressed C, or the B branch and they pressed B, they escape (0x9e) and she
recovers in 0x102. These read the opponent's `m_pressA-C`, i.e. recorded input: replay-safe.

Awakening: when `m_awakened` is 0, the gauge is exactly 3000, HP < 1666 (and > 0), the
opponent is alive, both players' `unkac` + 1 equals `m_roundsToWin` (*inferred:* both at
match point, `scene3.cpp:405-411` counts rounds there), she is on the ground in pattern < 8.
0x140 sets `m_awakened` for the rest of the match (Reset clears it): +1 gauge a frame,
animation frames 2 game frames shorter (`timer >= l4 - 2`), faster walk and dashes, higher
jumps, afterimages, a tint cycle (`m_tintCycle`) and sparks (`m_sparkTimer`).

Oddities:
- No LV4 command (her ReadCommand has no 0x96 loop); 41364136 doesn't exist for her.
- 236 (0xa-0xc) starts nothing on its own; it is only read inside the holds.
- Unreachable: 0xd3-0xd6, 0x100, 0x103, 0x12d, 0x12f-0x131 (Nanase's unarmed 236236 copied).
- `unk3354[]` only zeroed; `unk3460` (char) only zeroed by the constructor;
  `Unk6d2410(int)` is empty and never called. Left unnamed.
- `StartCommand` tests `(flagsB0 & 8) > 1` for 0x13b and 0x135 (`exnanase.cpp:133, 151`),
  the same as `> 0` for that bit.

## Nagamori (CNagamori)

She places floating bombs and detonates them with her attacks: `TriggerObjectsNear(x, y,
w, h)` (Unk4ae1d0) flags every object in the box (`m_objectTriggered`); a floating bomb
that is flagged and whose 120-frame cooldown (`m_objectTimer`) is over spawns an
explosion 0x195, which hits at its frame 14, triggers objects within 90 px (chains) and,
when it hits, sets the opponent's velocity toward itself (`SetVelocity(angle, 2.2)`,
`nagamori.cpp:2001-2005`; x87 sin/cos, see docs/compat.md). The bomb is removed unless
`m_keepBombs`. Bombs bob (ay +-0.015) and expire after 16 (some 10/12) animation loops.

| Input | Action | What it does |
|---|---|---|
| normals, throws, dash attacks | 0xc8-0xd1, 0xdc/0xdd, 0xf8/0xf9, 0xe6-0xeb | 2C: 6 hits, triggers bombs near the floor |
| 6B | 0xd8 | step kick; StartCommand omits the hit/guard test other moves have (`nagamori.cpp:445`) |
| 2C while the shot is out | 0xd7 | hop kick |
| 623A / B / C(unk118), also in the air | 0xfa / 0xfb / 0xfc | 1 / 2 / 3 hops, each triggers bombs ahead |
| 214A / B / C (gauge > 50, costs 50) | 0xff / 0x100 / 0x101 (air: 0x113-0x115) | place bomb 0x190 / 0x196 (drifts forward) / 0x197 (rises forward); air C: 0x198 |
| air 236A / B / C (gauge > 50, costs 50) | 0x104-0x106 -> 0x107 | place 0x190 / 0x196 / 0x198 |
| 236A / B / C(unk118) | 0x10b / 0x10c / 0x10d | throw the shot 0x19b/0x19c/0x19d: flies out, slows, comes back to her hand (`m_shotState` 1, 2, 0); it triggers bombs it passes; C's drops bombs on the way back |
| 236A / B / C while it is out | 0x116 / 0x117 / 0x118 | `m_shotOrder`: the shot rises / dives / flies out again |
| 412A / B / C(unk118) | 0x10e-0x110 | hop, triggers behind and on landing; B/C place a bomb on landing |
| 236236 + button | 0x12c-0x12e -> 0x12f-0x131 | grab, pins the opponent (0x71), hits, 2000/2000/2500 finisher |
| 214214A / B / C (each 1 level, also in the air) | 0x133 / 0x132 / 0x134 (air 0x136/0x135/0x137) | super bomb 0x192 (survives its explosions) / 0x193 (big explosion 0x1c6) / the bouncer 0x191 (one at a time: `m_bouncerOut`) that drops bomb clusters |
| 6413 + button, shot in hand | 0x139-0x13b | blast 0x1c2-0x1c4 on her, triggers every object on screen with `m_keepBombs` set (bombs explode but stay) |
| 6, B, A, 6, neutral, A; gauge 3000, HP < 3333, on the ground | 0x138 | LV4 |

The LV4: 0x138 spawns 0x1bf at 45 frames (it flashes, triggers objects within 320 px and
writes the player's `m_patternVar1` to release 0x138's frame loops), then 0x1a1, and sets
`m_lv4Time` = 1200 when it ends. 0x1a1 counts it down: the opponent stays frozen (her
unk14c = 1200 every frame), her gauge is 0, opponent's unk13a = 1 and unk140 = 2, her
unk13c = 1; at set values it spawns 29 screen-space pieces 0x1a2-0x1be that slide in and
out. At 0 the opponent is knocked down (0x3b) and an opponent left at 1 HP is set to 0.

Oddities:
- `unk3158` is never written (always 0); bombs read it as `unk3158 + 10` for
  `m_objectPhase` (`nagamori.cpp:1807, 1933`). `unk315c` is never set; Vf8 only counts it
  down (`nagamori.cpp:544`). Both left unnamed. `m_bombsPlaced` and `m_bouncerDrops` are
  written but never read.
- 0xd4 sets 0xd6, which has no case in Nagamori (it would loop in `default`); 0xd4 itself
  is unreachable, as are 0xd2, 0xfd, 0xfe, 0x109, 0x10a and object 0x1a0.
- Commands: her LV4 is 0x5b (Mizuka's too); 412 (0x28-0x2a) is hers.

## Shared objects (every character)

- 0x1f0: spawned once (flag `m_particleBurstOut`) as she enters 0x53-0x56; when she leaves
  them, or 0x53/0x54 pass frame 1, it bursts into many 0x1f1/0x1f2 around her body, sound
  0x22. 0x1f1/0x1f2 use plain `rand()` (docs/compat.md lists them as visual).
- 0x1f3: one animation glued to her as 0x51 starts (0x51: launched with velocity
  `unkc0`/`unkc8` that the attacker set, e.g. Kaori's throw `kaori_vf6.cpp:3136-3137`).
- 0x1ef: screen-space at (60, 40), spawned as she enters 0x57 (what LV4s put the victim
  in, `kaori_vf6.cpp:4934`), removed when she leaves it.

## CPlayer members and shared actions seen (not named here)

- `unk118`: the resource C-version specials need (>= 500, or `unk120` > 0); they cost 500,
  250 when `unk120` != 0, with effect 0x21 (unk2c 0xb); the 22C guard cancel (command
  0x34 -> 0xa7, air 0xab) needs it too. 0x53-0x56 take 30 and 0x51 0.8 a frame when
  `unk120` != 0.
- `unk14c`: the attacker's freeze of the opponent (super flash 0x78, LV4 0xa0/0x4b0):
  `UpdatePattern` returns while `(*m_opponent)->unk14c > 0`, and UpdateObjects runs only
  objects with unk88 set. `unk14a`: a player's own freeze (hitstop); supers set the
  opponent's to 0xb4.
- `m_attackResult`: 7 appears beside 2 as "guarded" (`nanase_vf6.cpp:3627`); Kaori's LV4
  connects on 6 (`kaori_vf6.cpp:4892`), so 6 is not only "clashed".
- `unkf2` = 10 during Nanase's 214214 Lv1/Lv2 and unarmed 236236 Lv1/Lv2
  (`nanase_vf6.cpp:4436, 4476, 9231, 9277`); `unk138`/`unk13a` = 2 during Nanase's LV4;
  Nagamori's LV4 sets unk13c and the opponent's unk13a/unk140; EXNanase's 0x12c/0x12e set
  `unk140` = 3 (`exnanase_vf6.cpp:4270, 4390`).
- `unk128` = 1 is set on the opponent by every grab.
- DrawGauge uses `anims[0x2b]` (frame) and `anims[0x2c]` (bar) of the character's own
  animation table (Nanase, Nagamori).
- Shared actions used as victim states: 0x6b grabbed, 0x48 held by Kaori's rush, 0x47
  Nanase's smash, 0x63 pushed by EXNanase 0x13e, 0x67/0x64/0x65/0x68 held poses in throws,
  0x3f launched, 0x45 air-thrown, 0x51 thrown, 0x57 hit by a LV4, 0x62/0x61 knocked down,
  0x9e escaped EXNanase's hold, 0x71 pinned (Nagamori 236236), 0x3b knockdown.
- Vf8 is the per-character hook CScene3 calls every tick before UpdatePattern
  (`scene3.cpp:150`); Kaori's and Nanase's are empty, EXNanase's runs the awakening,
  Nagamori's counts unk315c down. *Suggestion for the core agent:* `PreUpdate`.

## Commands (for the core agent)

| Command | Motion | Seen in |
|---|---|---|
| 0, 1 | 44 / 66 in screen direction (left-left, right-right), neutral between | all |
| 6 | up after not-up within 5 frames (air jump) | all |
| 0xa-0xc | 236 | all |
| 0x14-0x16 | 623 | all |
| 0x1e-0x20 | 214 | all |
| 0x28-0x2a | 412 (back, down-back, down) | all parse it; only Nagamori uses it |
| 0x32/0x33/0x34 | 2 2 + A/B/C (neutral between); 0x34 is the guard cancel | all |
| 0x35 | 2 2 + D from pattern 0x60 | all |
| 0x46-0x48 | 413 + button (41236) | Nanase, EXNanase |
| 0x5b | 6, B, A, 6, neutral, A; gauge 3000, on the ground | Nagamori |
| 0x5d | neutral 6 neutral 6 neutral 6 + D; gauge 3000 | Kaori |
| 0x64-0x66 | 236236 | all |
| 0x6e-0x70 | 214214 | all |
| 0x78-0x7a | 6 4 1 3 (forward, back, down-back, down-forward) + button | Kaori, Nagamori |
| 0x96-0x99 | 4 1 3 6 4 1 3 + button (0x99 = D) | Nanase |

Several loops also require a gauge level or (Nanase) `m_swordThrown`.

## CPU (CpuInput)

- Kaori (Akane's table): issues 236 (0xa-0xc), 412 (0x28-0x2a) and 0x5a, which Kaori
  doesn't have; never 6413A/C or her LV4 (0x5d). `kaori.cpp:932` tests
  `m_cpuRoll < 0x12 && m_cpuRoll > 0x14` (never true).
- Nanase and EXNanase share one routine (EXNanase's has the `unk344c` tests removed):
  never 41236B/C, never the 41364136 supers. For EXNanase 236 and 0x99 do nothing, and the
  CPU never chooses her hold follow-ups. `nanase.cpp:1139` / `exnanase.cpp:960` test
  `m_cpuRoll < 0x12 && m_cpuRoll > 0x16` (never true: the 236236 pick).
  `((WORD)Random(0, 1) == 1) + 0x1f` is always 0x1f (`nanase.cpp:1074`).
- Tests of actions the character doesn't have (left as bare numbers: no name fits):
  Kaori `pattern == 0x108` (`kaori.cpp:800`), 0x109 and 0x10f-0x111 (`kaori.cpp:952,
  1451`); EXNanase 0x108 (`exnanase.cpp:831`); Nagamori 0x108 (`nagamori.cpp:961`).
  None of these patterns exists for them, so the tests are never true.
- Nagamori (a routine of its own): issues 41236 (0x46-0x48), which she doesn't have;
  never 412, 6413 or her LV4. `Random(0, 1) + 0x65` is always 0x65 (`nagamori.cpp:1069,
  1665`) and `((WORD)Random(0, 1) == 1) * 2 + 0x14` always 0x14 (`nagamori.cpp:1002`).

## Counts

Members/methods named: CKaori 6, CNanase 19 (15 members, 4 methods), CEXNanase 10,
CNagamori 16 (15 members, 1 method): 51. Left unnamed (above): CKaori::unk3144,
CKaori::unk334c, CNanase::unk334c, CEXNanase::unk3354, CEXNanase::unk3460,
CEXNanase::Unk6d2410, CNagamori::unk3158, CNagamori::unk315c, and CPlayer's Vf8 slot.
Actions/objects named: CKaori 73, CNanase 86, CEXNanase 85, CNagamori 128 (372; the
unreachable ones carry "Unused" or say so in their comment). Every case label of the
four UpdatePattern(2)/UpdateObjects(2) switches from 0xc8 up has a line in patterns.txt.
