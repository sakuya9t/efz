# chars5: CMisuzu, CMinagi, CMisaki, CMio

These files merge the four per-character folders (misuzu/, minagi/, misaki/, mio/), which
hold the same files for each class.

## For whoever applies these names

- **Command numbers are per character, not one motion each.** commands.txt has three
  numbers twice, each with a different meaning:

  | Number | Character | Meaning |
  |---|---|---|
  | 0x46 | CMisuzu | 41236 (read as 4, 1, 3) |
  | 0x46 | CMinagi | 421 |
  | 0xa0 | CMinagi | 21436, button on the frame of the final 6 |
  | 0xa0 | CMisaki | 6321463214 |
  | 0x5c | CMinagi, CMisaki | the same motion (222D); Mizuka's ends in C |

  Each line's comment names its class. The LV4 inputs are named by motion: 0x5c k222D
  (Minagi, Misaki), 0x5d kA5A2BC (Misuzu), 0x5e kB5A2AB (Mio). Either make command
  constants per class, or keep one name per number with per-character comments.
- **Shared scratch members have one name in all four classes:**
  - the per-action ints StartPattern zeroes: `m_patternVar1-3`;
  - the per-object arrays RemoveObject zeroes: `m_objectVar1-3`;
  - "object 0x1f0 spawned": `m_burstObjectAlive`;
  - objects 0x1f0/0x1f1/0x1f2: kObjBurst/kObjBurstPiece/kObjBurstPiece2.

  Most other characters have the same members, so the same names should fit them too.
  0x1ef and 0x1f3 (also in every character) are left to the core agent.
- **Never-started actions** with code are named `kUnused...` (0xd2, 0xd4-0xd6...) or
  after their slot where another input reaches it elsewhere (Misuzu's kDashA-C).
  Per-character notes list them.
- **Vf8** is proposed as `CPlayer::Vf8 PreUpdate` (renames.txt, last line of the CMisuzu
  block). It is a virtual slot: CScene3 calls it for both players every tick, before
  UpdatePattern. Misuzu's runs her poison; Minagi's, Misaki's and Mio's are empty.
- **Two efz.h comments are wrong (checked in player.cpp:1042-1052 and every ReadCommand):**
  - `m_inputX` is absolute: 1 is right, -1 is left, not forward/back.
  - `m_inputHistory`'s direction bits are absolute too: 1 right, 2 left. Code gets
    forward from facing (`(facing == -1) + 1`).
- **The CPU routine Minagi, Misaki and Misuzu share** fits none of them well:
  - It writes 0x5c (Minagi/Misaki's LV4, nothing for Misuzu).
  - It writes 214214 (nothing for Misaki).
  - It expects dash attacks 0xe6-0xe8, which Misuzu lacks.
  - It never starts Minagi's 421/41236/21436, Misaki's counters or 6321463214, or
    Misuzu's 421, crow 41236, 46321 or LV4.

## CMisuzu

Files: src/misuzu.cpp (StartCommand :136, DrawGauge :493, Vf8 :551, ReadCommand :583,
CpuInput :954, UpdateObjects :1949), src/misuzu_vf6.cpp (UpdatePattern).

Two mechanics run through most of her moves:

- **The crow.** `Reset` spawns object 0x190, which follows her for the whole round,
  hovering 45 px behind her and 100 px up (misuzu.cpp:1966-2037). It writes its
  position to `m_crowX`/`m_crowY`. Her 41236 needs the crow idle (`m_crowBusy == 0`) and
  within 50 px of her x. At frame 5 of the move the crow itself becomes the attack
  (0x199-0x19b), then turns back into 0x190.
- **Poison.** Her 421 floaters and 214214's counter objects poison the opponent when they
  hit: `m_poisonLevel` +1 (up to 5) and `m_poisonTime` = 3000 frames (+1000 if already
  poisoned, at most 3000).
  - Every frame `Vf8` (proposed `PreUpdate`) tints the opponent (colour 0xcb).
  - Every 45 - 7*level frames the opponent loses 10 HP, straight from `m_hp`, never
    below 1 (misuzu.cpp:551-575). It is not DealDamage, so it adds no combo, score or
    proration, and it can't KO.
  - The poison ends when the time runs out, the opponent is KO, or **Misuzu herself is
    hit** (her pattern 0x32-0x95).
  - DrawGauge draws a frame and a bar for it (anims 0x2a-0x2c, at y 31 on her side of
    the screen), and up to 3 crow-stock icons at y 218.

### Move list

The C version of 236, 214, 623, 421 and 41236 needs `unk118 >= 500` or `unk120 > 0`. It
takes 500 from unk118 (250 with unk120). Without that, the C input falls through to the
B version.

**Normals**

| Input | Action | What it does |
|---|---|---|
| 5A | 0xc8 | |
| 5B | 0xc9 | within 70 px |
| 5B | 0xca | farther than 70 px |
| 5C | 0xcb | |
| 6C | 0xd3 | small hop at frame 7 |
| 2A, 2B, 2C | 0xcc, 0xcd, 0xce | |
| j.A, j.B, j.C | 0xcf, 0xd0, 0xd1 | j.C repeats frames 4-6 once |

**Throws**

| Input | Action | What it does |
|---|---|---|
| C + a direction | 0xdc -> 0xdd | Within 30 px; both players on the ground; the opponent not in hit or guard states 0x32-0x9c. Damage 1200 (DealDamage(0x4b0, 750)). |
| Air 6C | 0xf8 -> 0xf9 | Within 100 px of an airborne opponent. Damage 1200 at frame 4. If it misses, it becomes j.C at frame 2. |

**Specials**

| Input | Command | Action | What it does |
|---|---|---|---|
| 214A/B/C | 0x1e-0x20 | 0xfa-0xfc | At frame 3 spawns an air trap 0x193-0x195, 80 px above her. During its frame 1, if an airborne opponent comes within 50 px (measured 40 px above the opponent's feet), the trap closes. Its hit freezes the opponent for 60 frames (C: 90) through the opponent's `unk14a`, and the trap freezes too (`unk86`). One trap per strength (`m_airTrapA-C`). Recasting 214C removes A and B traps still in their frame 1. |
| 236A/B/C | 0xa-0xc | 0xfd-0xff | Winds up (frames 3-4 three times), then on the first loop spawns a ground trap 0x196-0x198, 30 px ahead. After 20 frames it springs when the opponent is within 50 px horizontally (C: 70 px). If its frame 0 runs out, it disappears. A and B traps also vanish (with puff effect 0) when she is hit, or when she recasts the same strength or 236C. One per strength (`m_groundTrapA-C`). |
| 41236A/B/C | 0x46-0x48 | 0x100-0x102 | Needs the crow idle and near. At frame 5 the crow becomes 0x199/0x19a: it sinks, then swoops forward (vx 4, slowing). 0x19b dives: 5 hits, vx 3.4 vy 1, with effect 0x19c on it. The C version doesn't need unk118 when she has a crow stock. |
| 41236 + stock | 0x46-0x48 | 0x139-0x13b | Taken instead of 0x100-0x102 when `m_crowStock > 0`. Uses a stock. Freezes the opponent 180 frames (`unk14c = 0xb4`). The crow becomes 0x1bb, 0x1bc or 0x1bd, objects that keep running through the freeze (`unk88`). 0x1bb attacks on the ground with a long multi-hit loop. 0x1bc lands and kicks out a shot, 0x1be: it floats until `m_crowShotRelease`, then flies off at vx 3.5. 0x1bd: 10 hits, jumps forward at frame 7. |
| 623A/B/C | 0x14-0x16 | 0x103-0x105 | A jumping attack (vx 1.2/1.4/1.8, vy -1.6/-1.5/-1.6, from frame 8). Lands at frame 17. Zeroes the dash count `unk158`. |
| j.623A/B/C | 0x14-0x16 | 0x106-0x108 | The same from the air, from frame 0. |
| 421A/B/C | 0x3c-0x3e | 0x109-0x10b | The poison launcher, a chain of objects (below). Any of it is cancelled when she is hit or starts 421 again. |

The 421 chain:
1. At frame 12, 0x19d/0x1a0/0x1a3 appears on her.
2. At its frame 11 it spawns 0x19e/0x1a1/0x1a4, 55 px above her head.
3. At its frame 10 that fires 0x1c8/0x1c9/0x1ca:
   - A goes up and forward (vx 4, vy -2.5) and bursts over the opponent (within 5 px) or at the end of its animation.
   - B goes straight and stops once past the opponent.
   - C goes like A.
4. It becomes the burst 0x1cb/0x1cc/0x1cd.
5. At frame 10 the burst releases the poison floater: 0x1c5 (A, sways down), 0x1c6 (B, drifts back), or two 0x1c7 (C, random drift). Each floater has 1 hit. It pops (0x1a8) near the ground (y >= -75), on any contact, after 20 cycles (6 for B) or after 1200 frames.

**Supers** (A/B/C = 1, 2 or 3 levels, as far as the gauge allows)

| Input | Command | Action | What it does |
|---|---|---|---|
| 214214 | 0x6e-0x70 | 0x12c-0x12e | Counter stance. If an attack clashes with frame 7 (`m_attackResult == 6`), she freezes the opponent (`unk14c = 0x9f`) and goes to 0x12f. There she throws the poison object 0x1a9/0x1aa/0x1ab, worth +1, +3 or +5 levels: it pops into 6 random drops 0x1ac-0x1ae, which splash into 0x1af-0x1b2. Then she jumps away (vy -2.9) with effects 0x1b3 and 0x1c0. Without a clash, the counter frame passes and the move recovers. |
| 236236 | 0x64-0x66 | 0x133-0x135 | Summons an object 60 px ahead of her that sprays shots while she holds the pose: lv1 0x1b4 fires 0x1b5 21 times; lv2 0x1b6 fires 0x1b7 21 times; lv3 0x1b8 rises from 200 px below the ground and fires 0x1b9 fanned at 45 - 2n degrees, 32 shots (2 per loop, 16 loops). Leaving the pose ends it (0x1ba, or 0x1b8 sinks). |
| 46321 (4, 6, 3, 1 + any button) | 0x82-0x84 | 0x136 | Always 1 level. Adds a crow stock (max 3) at frame 9. 0x137/0x138 (2 and 3 levels, +2/+3 stocks) have code but StartCommand never picks them. |
| LV4: A, 5, A, 2, B, C | 0x5d | 0x13c | Needs a gauge of exactly 3000 at the first A, HP < 3333, on the ground. Objects 0x1c2 -> 0x1c3 (+0x1c4) appear at her hand. The opponent is frozen (`unk14c = 2`) from frame 7 to 41. There is a white flash and the music fades at the 5th of 10 loops of frame 12, and `m_game->unk1420c/unk1420e = 30000`. The attack frame is 37 (the opponent must be standing and not in hit states). On a hit the opponent goes to 0x6b, and at frame 38 tick 120 the screen object 0x1c1 spawns. At its frame 16 it takes 5000 HP straight from `m_hp` and puts the opponent in 0x63. If the KO doesn't end the match, Misuzu goes to 0x13d (a pose with the music fading). Otherwise 0x1c1 holds the final frame. The move ends in 0x60. |

### Commands

ReadCommand's priority order is 0x5d, 0x82, 0x6e, 0x64, 0x46, 0x3c, 0x14, 0xa, 0x1e,
then the shared 6, 0x35-0x32, 1, 0 (see commands.txt for each reader). Two consequences:
- 421 is read before 214, so walking back into a 214 (4, 2, 1, 4) gives 421.
- 41236 is read as only 4, 1, 3 + button, so a 236 started from back (4, 1, 2, 3, 6)
  gives 41236.

**The numbers are per character**: Misuzu's 0x46 is 41236 while Minagi's 0x46 is 421.
Either name commands per class, or keep one name per number with the motion in a
comment per character.

### What the CPU does (CpuInput, misuzu.cpp:954-1948)

The routine is shared with Minagi and Misaki. It writes:
- 236 (0xa-0xc), 623 (0x14-0x16), 214 (0x1e-0x20);
- 236236 (`Random(0,3)+0x64`), 214214 (`Random(0,3)+0x6e`, misuzu.cpp: one site);
- 22C (0x34);
- 0x5c with a full gauge. That is not a Misuzu command (her LV4 is 0x5d), so it does nothing.

It never starts:
- 421 (her poison);
- 41236 (the crow);
- 46321 (the crow stock);
- her LV4.

Its dash-attack plans (`m_cpuAction` 6-0x11, misuzu.cpp:1180-1262) dash, then press
A/B/C during 0xa3, expecting dash attacks 0xe6-0xe8 that Misuzu doesn't have. Her
forward dash is a hop, so the press gives 5A/2A on its first frames and air normals after
that. The tests `if (pattern == 0xe6) m_cpuAction = 0;` sit inside `pattern == 0xa3`
branches, so they can never be true (the same in all three characters). It also tests the
dash 2A-2C actions 0xe9-0xeb (misuzu.cpp:1146), which Misuzu has no case for.

### Never reached, or never spawned

- **Actions with code that nothing starts:**
  - 0xd2 (hop attack; 6B slot elsewhere);
  - 0xd4-0xd6 (air dive and its follow-ups; j.2C slot elsewhere);
  - 0xe6-0xe8 (dash A/B/C);
  - 0x130 (air 214214: StartCommand tests `y == 0` before it, misuzu.cpp:184-188; 0x131/0x132 have no case at all);
  - 0x137, 0x138.

  Named after their slots, following what the Minagi and Misaki agents did (kUnused* for 0xd2/0xd4-0xd6).
- **Objects with code that nothing spawns (left unnamed):**
  - 0x191, 0x192 (play once and are removed);
  - 0x19f, 0x1a2, 0x1a5, 0x1a6, 0x1a7: poison floaters like 0x1c5. They rise first, then bob, and their hits poison too. 0x1a7's hit sets the time to 3000 without the +1000 rule. Probably an earlier version of the 421 floaters.

### Left unnamed

- 0x191, 0x192, 0x19f, 0x1a2, 0x1a5, 0x1a6, 0x1a7 (never spawned, above).
- 0x1ef: spawned at screen (60, 40) in shared state 0x57, removed when she leaves 0x57, `unk8c = 30000`.
- 0x1f3: spawned at her position in shared state 0x51 and follows her.

  Every character has the same 0x1ef and 0x1f3 code, so the core agent should name them
  together with 0x51 and 0x57.
- 0x1f0-0x1f2 are named kObjBurst/kObjBurstPiece/kObjBurstPiece2 in all four of these
  classes, the same in every character. 0x1f1/0x1f2 use plain `rand()`, so replays don't
  reproduce them; they are visual.

### Oddities and bugs

- **41236's range test is redundant.** Both halves of the facing test are the same
  (`m_crowX - 0x32 < x && m_crowX + 0x32 > x` for facing 1 and -1, misuzu.cpp:228, 237,
  246).
- **The 623 actions use vx where vy was meant.** They apply gravity only
  `if (y + vx < 0.0)` (vf6:3542, :3589, :3652, :3691, :3730, :3785). So on the ground
  versions gravity starts a frame late, once she is higher than vx px. Misaki has the same slip in her air supers.
- **0x1bb can start early.** The stocked crow 0x1bb starts its attack early when
  Misuzu's own `m_patternVar1 > 0` (misuzu.cpp:3494). 0x139 never sets it, so this only
  happens if she starts an action that counts.
- **0x196's repeat count is off by one.** It uses `m_objectVar2` both as its "hits set"
  once-flag and as its repeat count, so its frames 10-11 repeat twice, not three times
  (misuzu.cpp:2178-2181, :2211).
- **The 214214 counter compares frame 7, not a hitbox.** `m_attackResult == 6` (clash)
  on frame 7 is the catch.

### Observations on shared CPlayer members and actions (for the core agent)

**Input**
- `m_inputHistory` directions are absolute (1 right, 2 left). ReadCommand builds forward
  as `(facing == -1) + 1`, not the forward/back bits efz.h describes.
- `m_inputX` is compared with `facing` for forward (misuzu.cpp:388-394, :479). Minagi's
  agent found it absolute as well.

**Resources and freezes**
- **unk118/unk120:** the resource the C specials and 22C (0xa7/0xab) need: `>= 500`, or
  unk120 set.
  - Each C special takes 500 (250 with unk120).
  - Hit states take 30 or 0.8 per frame while unk120 is set.
  - 0xab moves `unk118 * 5` into `m_proration` when unk120 == 1, then zeroes unk118
    (vf6:2391-2394).
- **unk14a:** a freeze of that player. UpdatePattern returns while it is > 0 (vf6:13).
  Misuzu's air traps set the opponent's to 60/90.
- **unk14c:** the super freeze. Supers set 0x78, a counter 0x9f, a stock crow 0xb4, LV4 2
  per frame. While ours is > 0, the opponent's UpdatePattern and UpdateObjects return;
  our objects keep running only with `PlayerObject::unk88`. CScene3 counts it down
  (scene3.cpp:162-171).

**Objects (PlayerObject)**
- unk80: the object's attack result. 3 is a hit; 4 and 5 make her traps vanish (a clash).
  It is zeroed every animation frame.
- unk84: hits left. 0x63 is used for "many".
- unk86: a freeze of the object; the object is skipped while it is nonzero.
- unk88: the object runs during our unk14c.

**Counters**
- unk158: ground dash count; 623 and the supers zero it.
- unk159/unk15a: air dash and air jump counts. The double jump needs `unk15a < 1`.
- unk15c: specials need it < 2, dashes < 1, the double jump and jump cancels < 3.

**Throws and hit states**
- unkc0/unkc8 are the vx/vy the hit states 0x51/0x55/0x56 start with; throws set them on
  the opponent.
- Hit states are 0x32-0x95 (Misuzu's objects test that range to vanish when she is hit).
  States 0x53-0x56 add 30 gauge and spawn 0x1f0.

**LV4**
- 0x63: the opponent's state after the 5000 damage.
- 0x6b: the opponent while held.
- 0x60: Misuzu's state after the LV4.
- `m_game->unk1420c/unk1420e` are set to 30000 during it.

**CPU**
- unka8 scales every probability in CpuInput (difficulty).
- unk14e is set to 0x3c or 0x1e, probably the CPU's guard time.

**Vf8**
Proposed name `PreUpdate`, in renames.txt as `CPlayer::Vf8`. It is a virtual slot, so
renaming it renames all 25 overrides. CScene3 calls it before UpdatePattern
(scene3.cpp:150-151). Of these four characters, only Misuzu's does anything. Kano's
regenerates gauge, Nagamori's counts a timer down.

### Doubts

- **"Trap", "floater", "summon" and "launcher" describe behaviour, not sprites.** I
  haven't seen the graphics. The 421 floaters drift, sway and pop like bubbles, but the
  names don't say so.
- **The motion name `k46321` is shortest-true, not canonical.** It is what the reader
  needs: 4, 6, 3, 1 + button, with the 2 between 3 and 1 natural but not required. The
  game's manual may call it something else (463214?).

## CMinagi

Minagi fights through Michiru, a partner object (0x190) spawned by `Reset` 40 px behind her
(minagi.cpp:81-92) that never dies. Minagi's own special "attacks" are only poses
(minagi_vf6.cpp:3426-4048: they stop her, set `m_attackResult = 3` every frame so they stay
cancelable, and end); Michiru's object sees Minagi's pattern reach a trigger frame (2 on the
ground, 3 in the air, 1 for air supers) and turns into the attack object (minagi.cpp:1951-2111).
`m_michiruState` (unk3148) is Michiru reporting back; every Michiru special needs it != 4.
Minagi's own moves: normals, throws, the 41236 shot and the 21436 super.

### Move list (motion -> m_command -> action -> what it does)

Directions in numpad notation, facing right. A/B/C variants are at consecutive numbers.

| Motion | Command | Action | What |
|---|---|---|---|
| A / B / C | - | 0xc8 / 0xc9 (B within 50 px) or 0xca / 0xcb | 5A, close 5B, far 5B, 5C |
| 2A / 2B / 2C | - | 0xcc / 0xcd / 0xce | crouching normals |
| j.A / j.B / j.C | - | 0xcf / 0xd0 / 0xd1 | air normals |
| A/B/C in forward dash 0xa3 (+2) | - | 0xe6-0xe8 (0xe9-0xeb) | dash attacks, slide vx 2.0 |
| 4/6 + C close, opponent grounded | - | 0xdc -> 0xdd | throw, 1250 damage |
| 6 + C in the air near an airborne opponent | - | 0xf8 -> 0xf9 + obj 0x1c5 | air throw: carried down, 1200 on landing |
| D | - | 0xfa | Michiru to the ready stance 0x191, or out of it |
| D + right / D + left (absolute) | - | 0xfb / 0xfc | Michiru walks right / left (0x192) |
| 236 + A/B/C (air ok) | 0xa-0xc | 0xfd-0xff (air 0x109-0x10b) | Michiru hop attack 0x194-0x196 (ready: 0x1a6-0x1a8) |
| 421 + A/B/C (air ok) | 0x46-0x48 | 0x100-0x102 (air 0x10d-0x10f) | Michiru anti-air jump 0x197-0x199 |
| 214 + A/B/C (air ok) | 0x1e-0x20 | 0x103-0x105 (air 0x110-0x112) | Michiru vertical multi-hit 0x19a-0x19c (ready: 0x1aa-0x1ac) |
| 623 + A/B/C (ground) | 0x14-0x16 | 0x113-0x115 | Michiru rising 99-hit attack 0x1d2-0x1d4 |
| 41236 + A/B/C (ground, one at a time) | 0x50-0x52 | 0x106-0x108 | Minagi's slow shot 0x1ad / 0x1ae / 0x1af+0x1b0 |
| 236236 + A/B/C (1/2/3 levels, air ok) | 0x64-0x66 | 0x12c-0x12e (air 0x132-0x134) | Michiru rising multi-hit 0x1c6-0x1c8 with spray 0x1cf-0x1d1 |
| 214214 + A/B/C (1/2/3 levels, air ok) | 0x6e-0x70 | 0x12f-0x131 (air 0x135-0x137) | Michiru strike that freezes the opponent 45/75/100 frames (from ready: dash, 90/150/200) |
| 21436 + A/B/C (1/2/3 levels, ground) | 0xaa-0xac | 0x138-0x13a | Minagi fires rising shots 0x1b8-0x1ba, Michiru 0x1b5 fires 0x1bb |
| gauge 3000: 5, 2, 5, 2, 5, 2, D; HP < 3333 | 0x5c | 0x13b | LV4: Michiru 0x1be rains 0x1bf from the sky (trails 0x1c0-0x1c4) |

C versions of the specials need `unk118 >= 500 || unk120 > 0` and take 500 off unk118 (250
with unk120) at their first frame (e.g. minagi_vf6.cpp:3511-3528). The supers' level check is
the usual one: C needs 3000, B or C 2000, any 1000 (minagi.cpp:143-209).

### Michiru's states (m_michiruState, written by her object)

- 0 idle 0x190: faces the opponent; walks back (0x1b4) if more than 300 px from Minagi.
- 1 starting 5D (0x191 frames 0-7). 3 ready: 0x191 frames 8-0x10 loop until D again. From
  ready, 236/214 use the "Ready" objects (no windup; 214 drifts back to Minagi; 236 no rebound),
  421/623 start their object at frame 8/9, 214214 uses the dash versions 0x1a1/0x1a3/0x1a5.
- 2 walking (0x192 after D+direction, 0x1b4 walking back).
- 4 busy: any attack, knocked back (0x193, entered when her object's `unk80` is 4 or 5), held
  (0x1d5, while Minagi is in shared action 0x7b).

### Oddities

- LV4 check reads `m_patterns[0x139].unk0` (the 21436B's) but starts 0x13b (minagi.cpp:137).
- 21436 with the button on the same frame as the final 6 reads as 0xa0-0xa2, which
  StartCommand ignores (minagi.cpp:585-590): the button must come a frame later.
- 236236's spray (0x1cf-0x1d1) and the 21436 shots' speeds and the LV4 drop x use `Random`, so
  they are in the replay (minagi.cpp:4765, 4927, 5093, 5163, 5233).
- Never started by anything in minagi*.cpp: actions 0xd2, 0xd3, 0xd4 (and 0xd5/0xd6, reached
  only from 0xd4), 0x10c, 0x13c-0x141; objects 0x19d-0x19f, 0x1cc-0x1ce (no code sets them),
  0x1c9-0x1cb (only from 0x13c-0x141). 0x13c-0x141 are byte copies of the 236236 actions; their
  ready-stance Michiru objects 0x1c9-0x1cb are a hop (vx 1.5, vy -1.4, 5 hits) instead of the
  rising spray. 0x19d-0x19f and 0x1cc-0x1ce are identical pairs: key on 0x12c/0x132 (0x12d/0x133,
  0x12e/0x134), 99 hits at frame 0xa, then a jump vx 0.5 vy -2.2, `(*m_opponent)->Unk410a80`
  while frame < 0x14: an older 236236 Michiru, left unnamed.
- Not determined (left out): 0xd3 (a ground C-like attack, one hit at frame 3, jump-cancelable on
  hit or guard: minagi_vf6.cpp:2988; Misuzu's 0xd3 differs), 0x10c (an air pose that falls to
  the ground and loops, minagi_vf6.cpp:3828). Both unreachable.
- `DrawGauge` and `Vf8` are empty for Minagi (minagi.cpp:530-536).
- Effect types passed to `m_game->CreateEffect` (0, 1, 3, 4, 8, 9, 0x1f, 0x21, 0x44-0x47) are
  CGame effects, not object patterns.

### CPU (CpuInput, minagi.cpp:915-1908; identical to CMisaki's, shared with CMisuzu)

It writes commands 0xa-0xc (236), 0x14/0x16 (623A/C), 0x1e-0x20 (214), 0x34, 0x5c (LV4),
0x64-0x66 (236236), 0x6e-0x70 (214214), and dashes. It never writes 0x46 (421), 0x50 (41236),
0xaa (21436), and presses D only in the hitstun branch (minagi.cpp:962-965), so the CPU Minagi
never moves Michiru with D, never uses the shot, 421 or the 21436 super. Dead code in it:
`m_pressD` is assigned twice and the first value lost (minagi.cpp:962-963); `m_cpuRoll < 0x12 &&
m_cpuRoll > 0x14` (minagi.cpp:1087) and `y - opp.y > -50 && y - opp.y < -50` (minagi.cpp:1050)
can never be true.

### Observations on shared CPlayer members and actions (for the core agent)

- `m_inputX` is absolute (1 right, -1 left), not facing-relative: player.cpp:1044-1051 sets it
  from the keys, :1084 stores bit 1 for `m_inputX == 1`; StartCommand compares it with `facing`
  for forward. efz.h's comments on m_inputX and m_inputHistory ("1 forward, 2 back") should say
  right/left. Minagi's D+right/D+left (0xfb/0xfc) depend on it.
- PlayerObject: `unk80` is the object's hit result (3 hit, 4 lost a clash with another object
  scene3.cpp:1934-1939, 5 struck scene3.cpp:1834-1836/2023), cleared on each new animation frame;
  `unk84` the hits it can still land (like m_hitsLeft; 0x63 = unlimited); `unk86` frames the
  object is frozen (UpdateObjects skips it, minagi.cpp:1922); `unk88` 1 = keeps updating during
  the super freeze (`unk14c`), minagi.cpp:1922, set by Michiru's super objects.
- `unk14a`: freeze timer, UpdatePattern returns while > 0 (minagi_vf6.cpp:13); Michiru's 214214
  sets the opponent's. `unk14c`: 0x78 at every super flash (minagi_vf6.cpp:4054).
- Shared objects every character has: 0x1ef (lives only during action 0x57, vx -0.02,
  minagi.cpp:5879), 0x1f0 (spawned in 0x53-0x56 once per `m_burstObjectAlive`; when Minagi
  leaves those actions it bursts into six 0x1f1 and four 0x1f2 and plays sound 0x22,
  minagi.cpp:5895-5970), 0x1f1/0x1f2 (the pieces, minagi.cpp:5982/6011), 0x1f3 (spawned in 0x51,
  minagi_vf6.cpp:1362; plays once). 0x1f0-0x1f2 are named kObjBurst/kObjBurstPiece/kObjBurstPiece2
  (the agreed names); 0x1ef and 0x1f3 are left for the core agent.
- Shared action 0x7b is the hold Akiko's 0x13f puts the opponent in (akiko_vf6.cpp:5129).
- The per-action scratch triple (unk3138/313c/3140, cleared by StartPattern) and the per-object
  triple of arrays (cleared by RemoveObject) exist in most characters at similar offsets; the
  agreed names are m_patternVar1-3 and m_objectVar1-3.

Counts: 10 of 10 members named (no Unk methods); 133 action numbers named; left out 0xd3,
0x10c, objects 0x19d-0x19f and 0x1cc-0x1ce (unreachable), and the shared objects 0x1ef, 0x1f3.

## CMisaki

Files: src/misaki.cpp (StartCommand 92, ReadCommand 439, CpuInput 741, UpdateObjects 1736),
src/misaki_vf6.cpp (UpdatePattern). DrawGauge and Vf8 are empty: she has no gauge or
per-frame status of her own. Only 4 int members plus the three per-object arrays.

"C condition" below = `unk118 >= 500.0 || unk120 > 0`; the move then takes 500 from
unk118, or 250 when unk120 != 0 (0xfc, 0x100, 0x102). Without it, the C motion falls back
to the B version.

### Move list (motion -> command -> action)

Normals (StartCommand, misaki.cpp:305-422)
- 5A 0xc8, 5B 0xc9 within 70 px / 0xca farther, 5C 0xcb, 2A 0xcc, 2B 0xcd, 2C 0xce (slide),
  jA 0xcf, jB 0xd0, jC 0xd1. Ground normals jump-cancel on hit or guard (5C on hit only),
  air normals air-jump-cancel (0xe/0xf/0x10).
- Dash attacks: A/B/C during the forward dash 0xa3 (not holding back) -> 0xe6/0xe7/0xe8;
  with down held -> 0xe9/0xea/0xeb. 0xe8 lunges (vx 3), 0xeb hops.
- Throw: C + forward or back within 30 px, opponent grounded and not in hit/guard states
  (pattern < 0x32 or > 0x9c) -> 0xdc, connects -> 0xdd (1250).
- Air throw: forward + C in the air within 100 px of an airborne opponent -> 0xf8,
  connects -> 0xf9 (1300, throws behind, lands via 0xfd); a miss turns into jC (0xd1 frame 2).

Specials
- 236A/B/C (0xa/0xb/0xc, ground) -> 0xfe / 0xff / 0x100 (C condition). A and B throw a
  slowing projectile (0x196 vx 1.5, 0x197 vx 2.2); C sends 0x1a1, which walks forward
  1 px/frame planting 5 ground bursts 0x198.
- 623A/B/C (0x14/0x15/0x16, ground) -> 0x101 / 0x104 / 0x102 (C condition). 0x101/0x104
  jump (vy -3 / -4) and catch an airborne opponent at frames 5-6, carry them over and throw
  them behind (850 / 650), turn round, land via 0xfd. 0x102 stays on the ground and catches
  an airborne opponent at frame 4 -> 0x103: 3 slams of 350, then a launch.
- 214A/B/C (0x1e/0x1f/0x20) -> ground 0xfa / 0xfb / 0xfc, air 0x107 / 0x108 / 0xfc (the C
  version has no y test). A hop that strikes on the way down (once vy passes 0.2 / 0.8);
  0xfc hops higher, gives 60 frames of unk13c (projectile immunity, see below) and bounces
  again at frame 0x12 (visual 0x199). Air versions stop in the air, then hop again.
- 22A (0x32) -> 0x105, 22B (0x33) -> 0x109: counter stances (identical code; any difference
  is in misaki.pat). An attack meeting the stance at frame 3 (m_attackResult 6) freezes
  the opponent for 90 frames (Misaki's unk14c) and starts 0x106, the counter strike.
  These are the shared 22A/22B command numbers; 22C (0x34) stays the shared 0xa7/0xab.

Supers (gauge 1000 / 2000 / 3000 = levels 1-3; A/B/C pick the level, capped by the gauge)
- 236236 in the air (0x64-0x66) -> 0x12c / 0x12d / 0x12e: freeze, rise, drop a column
  (0x1a3 / 0x193 / 0x1a7) that chains segments 40 px apart down to the ground, where a
  ground part (0x1a5 / 0x194 / 0x1a9) spawns the hitting blast (0x1a6 / 0x195 / 0x1aa,
  9 / 16 / 29 hits' worth of frame-0 repeats).
- 236236 on the ground -> 0x12f / 0x130 / 0x131: tosses 15 / 21 / 30 items, each one of
  0x19b (50%), 0x19d, 0x19f (25% each) through CPlayer::Random, so replay-safe; speeds are
  also Random. Each bounces once on landing or contact, leaving a piece (0x19c/0x19e/0x1a0)
  and playing voice 1. Levels 2/3 set unk13c to 135/153.
- 6321463214 (two half circles back, 0xa0-0xa2, ground start) -> 0x132 / 0x133 / 0x134:
  a vacuum grab. For 16 passes of frames 5-7 it pulls the opponent in (opponent unkd0 = 1,
  unkb8 = growing speed toward her, capped 1.5 / 2.0 / 2.0) with visual 0x1a2; levels 1-2
  only grab a grounded opponent, level 3 anything. Caught -> 0x135 / 0x136 / 0x137:
  0x135 4 slams of 300, a jump (vy -7) and a landing on the opponent (1400);
  0x136 7 slams, launch, jump, column 0x193, land via 0xfd;
  0x137 holds them overhead while 10 columns 0x193 fall from 250 px above, then 1000.
- LV4: 222D with the gauge exactly 3000 and HP < 3333 (0x5c) -> 0x139, a counter stance
  (takes the 3000 at frame 0). An attack meeting it at frame 2 -> 0x138, the strike
  (visuals 0x192, 0x191; on hit the opponent's unk14a = 500).

Never started (code present, no assignment anywhere, nor in player.cpp/scene3.cpp):
0xd2 (hop attack), 0xd3 (standing attack), 0xd4 (falling attack) with its 0xd5 rebound
and 0xd6 landing, and 0xec (a copy of 0xeb). By the numbering 0xd3 would be a 6C as in
Misuzu, but nothing in Misaki says so; the names are kUnused*.

### Objects

Hitting: 0x193/0x1a3/0x1a7 (re-armed every frame), 0x195/0x1a6/0x1aa, 0x196, 0x197,
0x198, 0x19b/0x19d/0x19f. Visual only (PlayerObject::unk84 stays 0, which scene3.cpp:1403
requires): 0x190, 0x191, 0x192, 0x194, 0x199, 0x19a, 0x19c/0x19e/0x1a0, 0x1a1, 0x1a2,
0x1a5, 0x1a9. 0x1a4 and 0x1a8 are not used.

Shared objects (same code in every character): 0x1ef (spawned in screen space at (60, 40)
when shared pattern 0x57 starts, removed when the pattern changes), 0x1f0-0x1f2 (the
burst docs/compat.md describes; named kObjBurst*), 0x1f3 (follows the player for one
animation, spawned when shared pattern 0x51 starts). 0x1ef and 0x1f3 left unnamed: what
0x57 and 0x51 are is the core agent's call.

### CpuInput (shared with Minagi and Misuzu)

The CPU picks for Misaki: all normals, dash attacks (m_cpuAction 6/8/0xa -> 0xe6-0xe8,
0xc/0xe/0x10 -> 0xe9-0xeb), 2A (action 0x14), the ground throw (back + C within 40 px),
236A/B/C, 623A/B (after 5B close), 623C as anti-air against a falling opponent, 214A/B/C,
22C (0x34, from 0xfb/0xfa/0xe8/0xeb while the opponent guards), 236236 (0x64-0x66, ground
or air), LV4 (0x5c).

It never starts: the 22A/22B counters (0x32/0x33 never written), the 6321463214 supers
0x132-0x134 (0xa0-0xa2 never written) and the air throw 0xf8 (it never presses C with
forward in the air). Its 214214 pick (`Random(0, 3) + 0x6e`, misaki.cpp:1651, in the air) and
the 0x67 of `Random(0, 3) + 0x65` do nothing for her.

Dead conditions in the routine (shared copies): `m_cpuRoll < 0x12 && m_cpuRoll > 0x14`
(misaki.cpp:913), `y - opp.y > -50 && < -50` (:889), `v10 > 800 && v10 < 120` (backdash,
:1675). The follow-ups of m_cpuAction 7/9/0xb/0xd/0xf/0x11 test `pattern == 0xe6` etc.
inside `pattern == 0xa3`, so they never reset m_cpuAction themselves.

### Oddities

- 0x12c-0x12e end on `vx + y >= 0.0` (misaki_vf6.cpp:4459, 4520, 4585), vy meant; vx is 0, so it is
  `y >= 0`.
- 0x139: `if (frame == 1 && timer == 0)` nested in `frame == 0 && timer == 0` (dead).
- 0x132-0x134 store 0xf in m_patternVar3 (unk3140) at frame 1 and never read it.
- 0xfe-0x100 decrement unk3138 at frame 0xc to repeat two frames, but nothing sets it, so
  the repeat never runs.
- 0x101/0x104 have an air start (`y < 0 -> frame 5`) but 623 requires y == 0.
- The C versions of 236 and 623 fall back to B (0xff, 0x104) when the condition fails;
  0x104 is therefore both 623B and "623C without resource".
- unk3348 (per object) is only zeroed (constructor, Reset, RemoveObject): never used.

### Shared CPlayer members/actions seen here (for the core agent)

- unk118 / unk120: the resource the C specials and 22C (0xa7/0xab) need; specials cost
  500 (250 with unk120 != 0); 0xab with unk120 == 1 adds unk118 * 5 to m_proration and
  zeroes unk118; hit states 0x46/0x51/0x52 drain 0.8 per frame while unk120 != 0.
- unk13c: while > 0 the player can't be hit by the opponent's objects (scene3.cpp:1403
  tests `p2->unk13c == 0`); 214C and 236236 B/C set it.
- unk14c: set to 0x78 by supers, 0x5a by counters; while > 0 the opponent's
  UpdatePattern returns (freeze). unk14a: the player's own freeze (opponent's set by
  0x135/0x138).
- unk158: 1 after a dash; normals keep and decay vx while it is 1 (dash momentum).
- m_attackResult 6 at a counter stance's active frame = an attack met it.
- PlayerObject::unk84 = the object's hits left (0 at spawn, scene3 decrements),
  unk80 = its attack result (2 after contact; 0x196/0x197 vanish at >= 2).
- 0xa3 (dash) counts its frames in unk3138 and goes to 0xb2 (dash brake) after 120 frames
  holding forward or 60 not; 0xaa/0xab save vx/vy * 100 in unk3138/unk313c across the
  freeze.
- Vf8 is called once a frame before UpdatePattern (scene3.cpp:150); Misaki's is empty.

### Not determined
- unk3348 (unused, see above): left unnamed.
- 0x1ef, 0x1f3 (shared objects).
- What the column objects and tossed items are on screen (names are by behaviour).

## CMio

Mio has two stances in `m_stance` (unk3150), toggled by D on the ground (0x10e, at its
frame 4), reset to 0 each round, shown by the gauge icon (anims 0x2b/0x2c, DrawGauge).
Each stance has its own normals, specials, supers and LV4 (StartCommand mio.cpp:116 and
:405). Stance 1 is called "Float" in the names because of what it does: walk 0.5 instead
of 0.7 (mio_vf6.cpp:38), jumps at vy -2 / gravity 0.02 instead of -3 / 0.045 (same height,
slower; :95, :267), two air dashes instead of one (mio.cpp:524), and air D (y < -30) is a
hover, shared action 0x11, which cuts the velocity to a quarter, drops gravity and drains
unk118 by 1 a frame (mio_vf6.cpp:346). What the stances are on screen is not known.

### Move list (motion -> command -> action)

Stance 0 (ground):
- A/B/C normals: 5A 0xc8, 5B 0xc9 (within 70 px) / 0xca, 5C 0xcb, 6C 0xe1, 2A 0xcc,
  2B 0xcd (multi-hit), 2C 0xce (slide), jA 0xcf, jB 0xd0, jC 0xd1, j2C 0xdf (dive) -> 0xe0.
- During the forward dash 0xa3 (not holding back): A/B/C 0xe6-0xe8, 2A/2B/2C 0xe9-0xeb.
- Throw: C + direction within 30 px of a grounded opponent -> 0xdc -> 0xdd (a hold of
  repeated 100-damage hits, up to 600 frames, then 400). Air throw: air 6C near an
  airborne opponent -> 0xf8 -> 0xf9 (1000 damage).
- 623A/B/C (0x14-0x16) -> 0xfa/0xfb/0xfc: spinning rise and fall, 8/12/20 hits; C costs
  500 of unk118 (250 with unk120) like every C special here.
- 214A/B/C (0x1e-0x20) -> 0x102/0x103/0x104: hop, then a sliding multi-hit.
- 236A (0xa) -> 0xfe, 236B (0xb) -> 0x10f: one hit each; at their frame 6, 236A again
  after contact -> 0x100 / 0x110 (four strike objects 0x197 from far to near, plus 0x198
  in 0x110); 236B at frame 6 -> 0x111 (shot 0x1c8). 236C (0xc) -> 0xff: a column of
  seven 0x1c0/0x1c1.
- 236236A/B/C (0x64-0x66, 1/2/3 levels) -> 0x12f/0x130/0x131: a close hit that freezes
  the opponent 120 frames, then 0x19b/0x19c/0x19d drop from y -480 around her for
  100/145/200 frames (drawn through Random).
- 214214A/B/C (0x6e-0x70) -> 0x135/0x136/0x137: strike object 0x1be in front, 8 hits,
  15 hits, or one that freezes the opponent 180 frames and marks it with 0x1bf.
- LV4: 641236C (0x7a, gauge 3000, HP < 3333) -> 0x13b, a rush; if it connects, the
  player must press A, B, C, A, B, C, D in turn on hit (0x13c-0x142), then 623C -> 0x143
  (leaping finish) or 236C -> 0x144 (object 0x1ba, 15 loops). A miss ends in shared 0x60.

Stance 1 (Float):
- Normals: 5A 0xd2 / 0xf2 (within 60 px), 5B 0xd3, 4B 0xe4, 5C 0xd5, 2A 0xd6 / 0xf3
  (within 60 px), 2B 0xd7, 2C 0xd8 (7 hits), jA 0xd9, jB 0xda, j2B 0xe3, jC 0xdb,
  j2C 0xe5. Dash attacks 0xec-0xf1. Throw 0xdc (same as stance 0), air throw 0xf7 -> 0xf9.
- 412A/B/C (0x28-0x2a), ground or air -> 0x105/0x106/0x107: rises and throws up to
  7/12 objects 0x194, or 16 x 0x1bc for C, aimed by a value swung 0..2.5 (m_patternVar3).
- 236A/B/C -> 0x108/0x109/0x10a: shot 0x195 (vx 6) once / twice; C turns away and
  throws 0x196, which wraps around the stage (x = -x past -960/1640) to come back.
- 214A/B/C -> 0x10b/0x10c/0x10d: marker 0x1c5 on the ground 0x58/0x80/0xbc px ahead;
  it spawns three 0x1a6, each calls a column 0x19a from y -560 that steps down 160 px
  at a time and ends in 0x199 on the floor. No unk118 cost for C.
- 236236A/B/C -> 0x132/0x133/0x134 (also in the air, from frame 3): rising shot
  0x1a2 / 0x1a8 (with trail 0x1a3) / 0x1a9 (trail, sparks, ground dust).
- 214214A/B/C -> 0x138/0x139/0x13a: volleys of three 0x1aa, once, twice, four times.
- LV4: B, neutral, A, 2, A, B (0x5e, gauge exactly 3000, HP < 3333) -> 0x14a; on hit at
  frame 3 -> 0x14b: the opponent is held while objects 0x1ab-0x1b9 gather on both sides;
  when 0x1b7 ends it sets m_patternVar2 = 1 and 0x14b deals 5000 and launches the
  opponent (0x47, vy -15); Mio herself goes to 0x47 at y -640 (off the top) at the end.
- D on the ground in either stance (not from 0xe0) -> 0x10e, stance change.

### Unreachable code

- 0xd4 (stance 1 far 5B): StartCommand's two B branches (mio.cpp:665-674) both start
  0xd3; the second was surely meant to be 0xd4 (stance 0's pair is 0xc9/0xca, and 0xd4's
  body matches 0xca's). CpuInput even has a branch for `pattern == 0xd4` (mio.cpp:2015).
- 0xfd and 0x101: cases in UpdatePattern (mio_vf6.cpp:4529, :4723) that nothing enters.
  0xfd falls (vy += 0.025) and lands into a recovery; 0x101 spawns 0x198 and has one hit
  (the tail of 0x110). Left unnamed.
- 0x12c/0x12d: one-level super flashes that set the stance to 1 / 0 (mio_vf6.cpp:5481,
  :5510); nothing starts them. Named kUnusedSuperToFloat/kUnusedSuperToGround.
- Objects nothing spawns: 0x190 (with its pieces 0x191-0x193, plain rand()), 0x1a4,
  0x1a5, 0x1a7 (straight shots). Named kObjUnused...
- Vf8 is empty in Mio (mio.cpp:773); it is the per-frame slot CScene3 calls for both
  players (scene3.cpp:150), Misuzu's poison tick. Its name is for the core agent.

### CpuInput (mio.cpp:1132-2670), Mio's own

- Never writes 0x7a, so the CPU never uses the stance-0 LV4; it can use the stance-1 one
  (0x5e, mio.cpp:1222, :2453) only below 3333 HP like a player.
- Writes commands Mio's StartCommand doesn't handle: 0x48 (mio.cpp:1300, stance 1) and
  0x46 (:2025, :2162, :2263, :2318). Those picks do nothing (a table copied from another
  character). The 0x46 sites sit in the follow-ups for 0xd4 (unreachable), 0xd7, 0xee,
  0xf1.
- mio.cpp:1246 `v10 < 80.0 && v10 > 160.0` can never be true (dead block).
- mio.cpp:1213 sets `m_pressA = 3`; StartCommand tests `m_pressA == 1`, so it does nothing.
- mio.cpp:2398 `m_command = facing;` (1 or -1) where every other site writes
  `facing == 1` or `facing == -1` (0/1, the dash commands).
- It does use D (m_pressD = 1 at mio.cpp:1520 and others) to change stance in combos.

### Commands

0xa-0xc 236, 0x14-0x16 623 (stance 0 only), 0x1e-0x20 214, 0x28-0x2a 412 (4, 1, 2 + button;
stance 1 only, mio.cpp:955), 0x64-0x66 236236, 0x6e-0x70 214214, 0x78-0x7a 641236 (gauge
3000 and stance 0 in the reader; only 0x7a used), 0x5e B,5,A,2,A,B (stance 1). The
stance tests are in ReadCommand itself (mio.cpp:819, :844, :928, :972), so a motion of the
other stance doesn't even produce its command.

### Observations on shared members and actions

- unk118 is the meter C specials need (>= 500 or unk120 > 0) and pay (500, or 250 with
  unk120 set; e.g. mio_vf6.cpp:4463); hovering in 0x11 drains it by 1 a frame, 0x51 by
  0.8 a frame and 0x53 by 30 while unk120 is set. 0xab (22C, command 0x34) zeroes it and,
  with unk120 == 1, adds unk118 * 5 to m_proration.
- unk14a > 0 freezes a player (UpdatePattern returns at once, mio_vf6.cpp:14); Mio's
  moves add to the opponent's (0x3c for 0x195, 0x78 for supers, 0x1e per throw-hold hit).
  unk14c (0x78 in every super) is the super-flash freeze of the other player.
- 0xa3 (forward dash) runs into 0xb2 after 100 frames held forward or 60 not held
  (mio_vf6.cpp:2235-2242), counted in m_patternVar1/m_patternVar2.
- PlayerObject::unk84 looks like the object's hits left (1 for most, 7 for the float
  236236 shots, 2 for 0x1ba, set 0 when 0x19c/0x19d land); unk80 its attack result
  (3 hit, > 1 hit or guarded: 0x195 stops on 3, bounces on 2; cleared to re-hit).
- In stance 1 the air throw tests 0xf8's priority but starts 0xf7 (mio.cpp:690-693).
- 0x1ef (spawned in 0x57 at screen 60,40, mio_vf6.cpp:1702) and 0x1f3 (follows the
  player during 0x51, :1422) are shared objects every character has; left for the core
  agent with 0x51/0x57.

### Not determined

- 0xfd, 0x101 (unreachable, see above).
- 0x1ef, 0x1f3 (shared).
- What the stances, the figures of the float LV4 and most objects look like: names are
  from behaviour only.
