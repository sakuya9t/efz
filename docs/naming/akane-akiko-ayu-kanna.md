# CAkane, CAkiko, CAyu, CKanna: notes

Line numbers are in the sources as of git 185f706 (the character files are unchanged at
HEAD). "Ticks": CScene3 runs 3 simulation ticks per displayed frame (`unk578 = 3`,
scene3.cpp:30), and LoadPatterns multiplies the .pat frame durations by 3, so every timer
in these files counts ticks (1000 ticks = 5.6 s).

I also parsed the `.pat` files (format from `CPlayer::LoadPatterns`, 240 bytes a frame;
parser scratch/tools/pat.py,
with summ.py and scan.py there; data in /home/sakuya/.local/share/efz-decomp/game). That tells
which actions have frame data and their damage (`PatternFrame::unka0`), and which attacks
send the defender into which hit reaction (`unkac` air / `unkae` ground). Used below as
"in .pat".

## The common shape (all four)

- **StartCommand** tries, in order: 22C (0xa7/0xab), then (unless `unk15c >= 2`) LV4,
  supers from 3 levels down, specials C before B before A, then the dashes (unless
  `unk15c >= 1`) and the air jump (unless `unk15c >= 3`), then normals A, B, C. Every branch needs
  `m_patterns[pattern].frames[frame].flagsB0 & 8` (the current frame is cancellable),
  `m_patterns[pattern].unk2 <= m_patterns[target].unk0`, and for a current pattern >= 0xc8
  `m_attackResult >= 2 && != 6` (it hit or was guarded). In .pat, unk0 is 10 for A
  normals, 20-25 B, 30 C, 50 specials and supers; unk2 is what the current move needs to
  be cancelled, e.g. supers 71.
- Super cost: the button picks the level for 236236/641236 (A 1000, B 2000, C 3000) and the
  pattern subtracts it (`m_gauge - 0x3e8...`). Akane's 214214 A/B/C cost 1000 each; Kanna
  has only 3-level supers.
- **C specials** need `unk118 >= 500 || unk120 > 0` and subtract 500 (250 when `unk120`) of
  unk118, with effect 0x21 (e.g. akane_vf6.cpp:3606).
- Normals: most can jump-cancel on hit or guard (`m_inputY == -1`, pattern 4/5/6, or
  0xe/0xf/0x10 in the air); some only on hit (Akane's 5B far and 2C, Akiko's 5B far and 2B).
- The three ints `unk3138/313c/3140` (StartPattern zeroes them) and the three per-object
  arrays (RemoveObject zeroes the slot) have the same role in all 24 classes. I named
  them `m_patternVar0..2` and `m_objectVar0..2`; worth using the same names everywhere.
  Each class also has a flag set when hit reactions 0x53-0x56 spawn object 0x1f0 and
  cleared when it bursts: Akane's `unk3148`, the others' `unk3144` -> `m_burstPending`.

## CAkane (Satomura Akane; summons a helper)

| Input | Action | What it does |
|---|---|---|
| A / 2A / jA | 0xc8 / 0xcc / 0xcf | |
| B (<70 px) / B / 2B / jB | 0xc9 / 0xca / 0xcd / 0xd0 | 2B slides forward |
| C / 2C / jC / j6C | 0xcb / 0xce / 0xd1 / 0xd3 | 5C 9 hits |
| A/B/C, 2A/2B/2C during forward dash 0xa3 | 0xe6-0xe8, 0xe9-0xeb | dash attacks; dash 2C hops |
| C + direction, close | 0xdc -> 0xdd | throw |
| air 6C, close, opponent airborne | 0xf0 -> 0xf1 | air throw, 1200 |
| 236 A/B/C (ground, no helper out) | 0xfa / 0xfb / 0xfc | helper flies in (0x19e) / runs in along the ground and attacks (0x19f -> 0x1a0) / enters from the far side (0x199) |
| air 236 A/B/C | 0x10f / 0x110 / 0x111 | dive down-forward, one bounce |
| 623 A/B/C (ground) | 0xfd / 0xfe / 0xff | rising multi-hit / dash + jump, 12 ticks invulnerable |
| 214 A/B/C | 0x100 / 0x101 / 0x102 | leap up / back / forward |
| 412 A/B/C | 0x103 / 0x104 / 0x105 | long forward hop |
| during a leap, after 52 ticks: 236 A/B/C | 0x106 / 0x107 / 0x108 | throws three shots 0x190 / 0x191 / 0x192 |
| leap: C / C+2 (412 only) / C+4 (214 only) | 0x109 / 0x10a / 0x10b -> 0x10c | dive / drop / air grab, 1000 |
| leap landing | 0x10d, 0x10e | 0x10e (after 214A/C) has one hit |
| 236236 A/B/C | 0x12c / 0x12d / 0x12e | shots go up (0x195) and rain on the opponent (0x196-0x198, Random positions) |
| 214214 A/B/C (1 level each) | 0x12f / 0x130 / 0x131 | object 0x19c at Akane / 100 px ahead / 150 px up; a hit freezes the opponent 90 ticks |
| 641236 A/B/C (no helper out) | 0x132 / 0x133 / 0x134 | helper super 0x1a1 / 0x1a2 / 0x1a3 drops in from behind; Akane poses until it lets her go |
| A,N,A,6,B,C (full gauge, HP < 3333) | 0x135 | LV4: dashing grab, 4500, KO picture 0x1ac |

Helper life: any helper hit by the opponent (`PlayerObject::unk80 == 4 || 5`) becomes
0x19a (thrown up), then 0x19d (jumps away); leaving the screen clears `m_helperState`.

Unused: 0xd2 (air dive, has data), 0xd5/0xd6 (no data), 0xf9, 0x137/0x138 (3-level grab
super whose 0x138 sends 0x1a5-0x1ab at the held opponent), 0x13b (no data). .pat also has
0xd7, 0xec, 0xf8, 0x136, 0x1ee with frames but no code (default case).

## CAkiko (Minase Akiko)

| Input | Action | What it does |
|---|---|---|
| normals | 0xc8-0xd1 | no dash attacks; jB 5 hits, jC loops |
| C + direction / air 6C | 0xdc -> 0xdd / 0xf0 -> 0xf1 | throw: 0x1a7 pushes the opponent into the wall (1200); air throw: 0x1a8 carries them down (1200) |
| 236 A / B | 0xfa / 0xfb | volleys in rotation (`m_nextShot`): A 5x 0x193, 3x 0x194, 3x 0x192; B 1x 0x196, 3x 0x197, 1x 0x198 (lob -> 0x199) |
| 236 C | 0xfc | two random volleys of the B kind |
| 623 A / B | 0xfd / 0x100 | lunge; on hit + 623A/B again -> 0xff, again -> 0x103 |
| 623 C | 0x101 | lunge (9, -3.6); on hit + 623C -> 0x102 up to 3 more times, then 0xfe |
| 214 A / B / C | 0x104 / 0x105 / 0x106 | a field (0x1a0 / 0x1a3 / 0x1a5) that drains the opponent's unk118 1 per 2 ticks within 50 px; C's moves and hits |
| 41236 A / B / C | 0x107 / 0x109 / 0x10b | command grab pulling the opponent in (unkb8); hit -> 0x108 / 0x10a / 0x10c, 1500 / 1500 / 1750 |
| 236236 A/B/C | 0x12c / 0x12d / 0x12e | run-in from behind (0x1a6/0x1ab/0x1ac) and a debris explosion ahead (0x1ad-0x1b2) |
| 214214 A/B/C | 0x12f / 0x131 / 0x133 | strike; on hit 0x130 / 0x132 / 0x134: 1000 damage and a 1000-tick **seal**: opponent's `unk15c` = 1 (no dashes), 2 (no specials/supers either), 3 (no jumps either) |
| 641236 A/B/C | 0x135 / 0x136 / 0x137 | the **slow-down**: `unk160` = level; Vf8 freezes the opponent every other tick while a counter climbs to 999 at 4 - level per tick (333 / 500 / 1000 ticks), music faded, voice every 36 ticks; ends early when Akiko is hit |
| 2,N,A,2,N,B,C (full, HP < 3333) | 0x13e -> 0x13f | LV4: appears behind the opponent, 5500 |

DrawGauge draws the seal bar (anims 0x2b/0x2c) and the counter (digits anims[0x28].frames,
anims 0x29/0x2a) from Akiko's own pattern table at shared numbers. Her Vf8 checks the
opponent's `unk160 == 0 || 4`, so in a mirror only one slow-down acts at a time.

Unused: 0xd2-0xd6, 0xe6-0xe8 (code and frame data identical to Ayu's 6B, 6C, j.2C, 0xe6-0xe8:
Akiko's .pat was evidently made from Ayu's), 0xf9; object 0x19a.

## CAyu (Tsukimiya Ayu)

| Input | Action | What it does |
|---|---|---|
| normals, 6B 0xd2, 6C 0xd3, j2C 0xd4 (-> 0xd5 rebound / 0xd6 landing) | | |
| air D | 0x28 (shared number) | glide: 50 of unk118 to start, 1 per tick; down cancels |
| throws | 0xdc -> 0xdd (1200), 0xf0 -> 0xf1 (1100) | |
| 623 A / B | 0xfa / 0xfc | jump throwing 0x190 up-forward (identical code) |
| 623 C ground / air | 0xfb / 0x10b | 0x198 up-forward / 0x199 down-forward -> 0x19a |
| 214 A / B / C | 0x100 / 0x101 / 0x102 | hop and stomp; contact -> 0x103 rebound; C 99 hits |
| 236 A / B / C | 0x104 / 0x105 / 0x106 -> 0x107 | dash tackle; C loops once more, 27 ticks invulnerable |
| 214214 A/B/C ground / air | 0x12c-0x12e / 0x12f-0x131 | shots 0x195 / 0x1a3 / three 0x1a4 (`m_shotSpeed`) |
| 641236 A/B/C | 0x132 / 0x133 / 0x134 | bursts on both sides: 0x1a5 / 0x196 / all three |
| 236236 A/B/C | 0x13b / 0x13c / 0x13d | rush with 0x1a2 in front |
| A,N,A,4,B,C (full, HP < 3333) | 0x13e | LV4 feathers (docs/compat.md) |

Unused: 0xe6-0xe8, 0xf9, 0xfd/0xfe/0xff (a chargeable dash with a D cancel; 0xfe has no
data), objects 0x193/0x194, 0x19b/0x19c/0x19d (and 0x1a6/0x1a7 they turn into, which have
no case). `CAyu::unk3148` is set to 1 by 0x19b/0x19c and to 0 by 0x19d and read nowhere:
a dead flag, left unnamed.

## CKanna (Kannabi no Mikoto)

Kanna flies: her jump states (shared 4-6, 9, 0xa, 0xe-0x14, 0xa5, 0xa6) allow up to two
air moves (`unk15a < 2`), each only after `m_airMoveDelay` (60) ticks in the current one:
up = another jump, forward/back = 0x11/0x13, down+forward/back = 0x12/0x14, down = fall.
Her StartCommand has no throw, no air jump (command 6) and dashes on the ground only;
her air normals cancel into the air dashes 0xa5/0xa6 on hit or guard. Her Move is
CPlayer::Unk40e740 except that walking/standing (0, 1, 2) don't restart each other.

| Input | Action | What it does |
|---|---|---|
| normals | 0xc8-0xd1 | 5B/5C/2B/jB/jC draw overlay objects 0x1a4-0x1a9 |
| 236 A/B/C ground / air | 0xfa / 0xfd | one hit, effect 0x194 |
| 236 C ground | 0xfb | 0x1ab, then a screen-wide 0x1ac |
| 623 A/B/C / 623 C | 0x100 / 0x101 -> 0x103 | rise with 0x1b9; C loops 5 more times, slow |
| 214 A / B / C | 0x107 / 0x108 / 0x109 | 0x190-0x192 rise, then an impact 0x193 50/125/200 px ahead |
| 41236 A/B / C | 0x10a / 0x10b | slow 99-hit 0x196 / six homing 0x1ae |
| 236236 A (ground or air) | 0x12c | feathers from behind (like Ayu's LV4) |
| 236236 B ground / air | 0x12f / 0x132 | bursts both sides 0x1a2 / attached 0x1aa (4500) |
| 236236 C (full, HP < 3333, ground) | 0x135 (0x136 on a miss) | LV4 |

All supers need the full gauge. Unused: 0xd2-0xd6, 0xdc/0xdd (a throw with data),
0xe6-0xeb (dash attacks with data), 0xf9; objects 0x197, 0x198, 0x19a-0x19e (the last
five have no frames), 0x1a3.

## The CPU (CpuInput)

Moves are written as `m_command` or presses; a move a table never writes can't be
started by the CPU. `Random` there doesn't matter to replays (both players are human).

- **Akane** (the routine Kaori shares): normals, dash attacks (`m_cpuAction` 6-0x11),
  623 A/B/C, 236 A/B/C, 412 A/B/C, 214 A/B/C, 22C, 236236 A/B/C,
  214214 A/B/C after 2C, 641236B only at exactly 2000 gauge, LV4 only at exactly 3000.
  Never 641236 A/C. Bugs: `m_cpuRoll < 0x12 && m_cpuRoll > 0x14` (akane.cpp:1003) can't
  be true; `m_pressA = 2` (:937) presses nothing (StartCommand tests `== 1`);
  `Random(0, 3) + 0x65` (:1626) yields 0x67 a third of the time, no move.
- **Akiko**: 623 A/B/C, 214 A/B/C, 22C, 41236 A/B/C, 236 A/B/C, 641236 A/B, 236236 A/B/C,
  214214 A/B/C. Never LV4, 641236C. Bugs: `Random(0, 3) * 0x6e` (akiko.cpp:1072: 0 = dash
  left, 0x6e, 0xdc); `m_command = facing` (:1469: 1 or -1); `0xc1` (:1482, no move);
  `Random(0, 1) + 0x79` (:1499) is always 0x79.
- **Ayu**: 623 A/C, 214 A/B/C, 22C, LV4, 236 A/C, 236236 A/B, 214214 A/B, 641236 A/B.
  Never 623B, 236B, the C supers. Bugs: `Random(0, 2) * 0x78` (ayu.cpp:925, 0 = dash
  left); `m_command = facing` under the impossible `m_cpuRoll < 0x2a && > 0x2f` (:1372);
  `Random(0, 1) + 0x65/0x79` constant; `m_pressA = 2` (:848).
- **Kanna**: 623 A/C, 214 A/B/C, 22C, 41236 A/B/C, 236 A/B/C, 236236 A/B. Writes 0x5c
  (kanna.cpp:771, :1530) for her LV4, which is 0x66 for her: the CPU never does it.
  `Random(0, 5) + 0x46` (:1297, :1350) gives 0x49/0x4a (nothing) 40% of the time; the
  impossible roll test at :847 and `m_pressA = 2` (:785) as Akane's. `m_cpuHitCooldown`
  and `m_cpuAirPause` are never initialised (heap garbage until the first CPU tick clamps
  a negative to 0; a large positive value would idle those branches for a while).

## Bugs and oddities in the move code (none affects replays unless noted)

- Akane StartCommand: j6C (0xd3) doesn't `return`, so the jC test runs next with pattern
  already 0xd3; it fails only because StartPattern reset `m_attackResult` (akane.cpp:420).
- Akane 0x12e spawns while `m_patternVar0 < 4` but loops while `< 3`; 0x12d spawns `< 3`,
  loops `< 3` (4 passes, 3 with shots). Probably meant, but uneven.
- Akane 0x1a2/0x1a3: `frame == 7 && frame == 0xc` can't be true, so a sound never plays
  (akane.cpp:2428, :2501).
- Akane leap follow-ups wait for `m_patternVar0 > 0x34` (52 ticks) after the leap starts.
- Akiko StartCommand: 641236B tests `m_patterns[0x137].unk0` instead of 0x136's
  (akiko.cpp:144); harmless, both are 50 in akiko.pat.
- Ayu StartCommand: a second `m_command == 0x78 && m_gauge >= 0xbb8 -> 0x132`
  (ayu.cpp:190) can never be reached. Ayu's LV4 subtracts 4000 gauge (ayu_vf6.cpp:4974); the clamp at
  player.cpp:493 makes it 0.
- Ayu 0x107 ends with `m_inputY = 1; if (1) pattern = 3;` (ayu_vf6.cpp:4179): it writes the
  input.
- Ayu 0x134 is placed before 0x133 in the switch (no effect).
- Kanna 236236C at HP >= 3333 matches no branch: nothing happens.
- Pattern code reads `m_command` (Akiko's 623 chain, Akane's leap follow-ups), so human
  and CPU input go through ReadCommand's motion windows mid-move.

## Shared members and actions (observations for the core agent)

- `unk118`: a meter refilled per tick (player.cpp:453), at 1000 sets `unk120 = 1`; C
  specials and 22C need >= 500 and spend 500 (250 when `unk120`); Ayu's glide burns it;
  Akiko's 214 fields drain the opponent's. `unk120`: "meter full" mode, C specials half
  price; while it is on, the hit reactions drain unk118 (0.8 a tick, or 30 on entering
  some, e.g. akane_vf6.cpp:1367).
- `unk15c`: **seal level**, set only by Akiko's 214214 hits (akiko_vf6.cpp:4736, :4813,
  :4897) and cleared by her Vf8: >= 1 no dashes, >= 2 no specials/supers, >= 3 no jumps,
  air jumps or jump cancels (also player.cpp:51).
- `unk160`: Akiko's slow-down level (1-3, 4 while ending); only Akiko and CPlayer::Reset
  touch it.
- `unk14c`: freeze of the **opponent** (and of one's own objects without `unk88`) while > 0:
  supers set 0x78, 22C 0x5a, Akiko's slow-down 1; CScene3 decrements it (scene3.cpp:163).
- `unk14a`: hitstop/freeze of oneself (UpdatePattern returns while > 0; Kanna's overlay
  objects hold their timer during it); Akane's 0x19c/0x1a3 and Akiko's 214214 set it on
  the opponent (90, 120, 450 ticks).
- `unk13c`: invulnerability ticks (the hit tests need it 0, scene3.cpp:973).
- `unk158`: dash momentum flag (normals keep sliding while 1); `unk159`/`unk15a`: air
  dashes / air actions used this jump.
- `PatternData::unk0`/`unk2`: cancel levels (see the common shape).
- `PlayerObject::unk80`: the object's attack result like `m_attackResult` (3 hit, 2
  guarded; 4/5 the object was hit, which knocks Akane's helper away); `unk84`: hits the
  object can still land (99 = unlimited); `unk88`: keeps updating during `unk14c`
  (EffectDesc::unk30).
- `CPlayer::Unk40ff70`: nonzero when the player is at a wall (x <= 20, >= 619, or 280 px
  from the opponent); Akiko's throw object uses it on the opponent.
- `CPlayer::Vf8` -> `UpdateTimers` proposed in renames.txt (slot 8; empty for these three,
  Akiko's real).
- Hit reactions: the attacker's frame data picks the defender's pattern (`unkae` grounded,
  `unkac` airborne, scene3.cpp:1308-1319). From the .pat files: 0x53-0x56 are inflicted
  only by Kano, Shiori, Nayuki B and Mio objects, 0x51/0x52 by objects of several
  characters, 0x57 by nothing (so object 0x1ef, spawned only in pattern 0x57, never
  appears). The efz.h comment on `m_inputHistory` says "1 forward, 2 back": the bits are
  absolute (1 right, 2 left); `m_inputPos` is the next slot (the oldest entry), not the
  newest.

## Not determined

- Objects 0x1ef (screen-space mark of the unreachable reaction 0x57) and 0x1f3 (follows
  the player for its animation when reaction 0x51 starts): shared by every character,
  left to the core agent.
- What the objects look like (the helper's identity, Akiko's shots...): names describe
  behaviour only. The sprites are in `<name>.dat`; no extractor exists yet.
- `CAyu::unk3148` (dead flag, above).
- Akane's .pat-only actions 0xd7, 0xec, 0xf8, 0x136 and object 0x1ee have no code.
