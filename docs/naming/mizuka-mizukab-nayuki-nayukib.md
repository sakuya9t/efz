# chars3 notes: CMizuka, CMizukaB, CNayuki, CNayukiB

Files: `patterns.txt` (every case label >= 0xc8 of the four UpdatePatterns and
UpdateObjects), `renames.txt` (48 members), `comments.txt`. No `commands.txt`: none of
the commands these four use is theirs alone, and the numbers 0x5a-0x62 mean different
inputs in different classes (see "Commands"), so the core agent should name them.

Method: StartCommand (input -> pattern), the UpdatePattern switch, UpdateObjects, CpuInput;
reachability by a script (StartCommand/CpuInput/UpdateObjects/shared states as roots,
then every `pattern = N` inside each case); the .pat files of the unpacked game
(`.../7673b13e-.../efz-unpacked/tasogare/EFZ/<name>/<name>.pat`) for which objects have
attack boxes. Object names are mechanical (what the code does); I did not look at sprites.

"EX" below = the C version that needs `unk118 >= 500 || unk120 > 0` and takes 500 (250
with unk120) of unk118. Levels = gauge 1000/2000/3000.

## Move lists

### CMizuka (mizuka\, the boss "Mizuka" of the eternal world)
- Normals: 5A 0xc8, 5B 0xc9 (within 70 px) / 0xca, 5C 0xcb, 2A 0xcc, 2B 0xcd, 2C 0xce
  (slide), j.A 0xcf, j.B 0xd0, j.C 0xd1, j.6C 0xd2, dash A/B/C 0xe6-0xe8 (button during the
  ground forward dash 0xa3), throw 0xdc -> 0xdd (C + 4/6 within 40 px).
- D: flight (shared numbers 0xb3 hover, 0xb4 forward, 0xb5 back), 1000 frames in
  m_flightTime; D again or the time out ends it. Air moves end back in 0xb3 while flying.
- 236A/B/C 0xfa/0xfb/0xfc(EX): capture orbs 0x1a1 (slow), 0x1a2 (rising), 4 homing 0x1a3.
  An orb that hits holds the opponent (their 0x79) and, when it ends, drops them from
  y -480 above Mizuka (0x3b). Air: 0x106/0x107 (0x1a4 descending)/0x108(EX).
- 214A/B/C 0xfd/0xfe/0xff(EX): ground object 0x196 at 60/160 px; C: a chain 0x198 ->
  0x199 -> 0x19a every 60 px to the screen edge. Air 214 (any) 0x109: wide 0x1cb, 99 hits.
- 41236A/B/C 0x100-0x102 (C needs no EX): two volleys of three thrown objects at 3.6,
  level (0x1bc-0x1bf) or rising at -35/-60/-85 degrees (0x1c0-0x1c3).
- 623 0x103 (A, B, C without EX), 623C 0x105 (EX): her own hit frames 4-6, effect 0x1b5.
- 236236A/B/C 0x12c-0x12e (1/2/3 levels): 7/17/35 walkers (0x19b-0x1a0, Random speed)
  from 340 px behind her.
- 641236A/B/C 0x12f-0x131 (1/2/3): kObjCatcher (0x1b8) falls on the opponent; if it
  catches, 0x132/0x133/0x134: a cinematic at fixed x (230 / 420) where Mizuka throws 1, 2
  or 3 items (0x1c6, 0x1c7, 0x1c5) at the caught opponent; each arrival rolls
  `Random(0,9) < 5` (5/9) = fail (opponent dropped), else 1800 / 3500 / 6500 damage.
- 214214C 0x13a (3 levels): leap; on a hit 0x13b, a long cinematic at x 320: six risers
  (one every 80 frames), a black flash, then kObjGrabber (5900 damage) with five sweepers.
- 463214C 0x13c (3 levels): kObj463214C, a large ground hit that repeats and advances.
- Never entered: 0xd3-0xd6, 0xf9, 0x104, 0x135-0x139 (0x135-0x137 are hold-and-hit
  sequences with frames in mizuka.pat; 0x139 is a counter-like stance whose 3000 cost is in
  a dead branch: `if (frame == 1 && timer == 0)` inside `if (frame == 0 && timer == 0)`,
  mizuka_vf6.cpp:5275-5277).

### CMizukaB (mizukab\): the same code base with a reworked move list
- Same normals/throw plus dash 2A/2B/2C 0xe9-0xeb and an air throw 0xf8 -> 0xf9 (6C near
  an airborne opponent). 5C and 2C are jump-cancellable on hit; 2C slides at 2.5.
- D flight: m_flying is 1 (no frame count); Vf8 takes 1 of unk118 a frame instead, and
  ends the flight when unk118 is gone. Capped at y -360 (shared 0xb3-0xb5 differ).
- 236A/B 0xfa/0xfb: the orb stops in place (5 hits); 236 again on frame 10 (air: 8)
  launches it as 0x1a4 (3.0/3.5, decelerating). 236C 0xfc (EX): one slow capture orb.
- 421A/B/C 0x10a-0x10c: teleports forward / back / above the opponent (y -130); air
  0x10d-0x10f (once a jump; C lands 60 px before the opponent). unk58 is 2 meanwhile.
- 623A 0x103, 623B 0x104 (or C without EX), 623C 0x105 (EX); 214 and 41236 as CMizuka.
  No air 214: that StartCommand line became 0x14 -> 0x103.
- 236236A 0x12c / B 0x12d (both 1 level): walkers from the screen edge in front / behind
  (emitters 0x1cd/0x1ce); air 236236A/B/C 0x13d (1), 0x13e (2, B or C), 0x13f (3): a big
  object held, thrown down, impact on landing (C's impact chains every 120 px).
- 463214A/B/C 0x12f-0x131: CMizuka's 641236 catch super, unchanged.
- LV4 0x13a -> 0x13b: CMizuka's 214214C, on input 0x5a = C, 5, B, 6, A, 5, A with HP <= 3333
  and a full gauge.
- Never entered: 0xd3-0xd6, 0x109, 0x12e (236236C on the ground starts nothing), 0x135-0x139
  (0x139 here: a 3000 self-heal, +10 HP a frame until full), 0x13c.

### CNayuki (nayuki\, awake)
- m_warmUp 0-9 (3 at the round's start): 5D 0x103 (and the stance's D 0x10f) +1; getting
  up from a knockdown (shared 0x60) -1. DrawGauge draws anims[0x2c] and the digit
  anims[0x22 + m_warmUp] (the `PTRAT(&anims[n].frameCount + 0x114)` is anims[n + 0x22].frames).
  It raises walk speed (0.6 + 0.02 per level), skips frames of many moves, adds hits
  (j.B level/2 + 2, more 623C hops), air dashes (1 + (lvl > 2) + (lvl > 7)), the forward /
  back air dash hits at > 7 / > 4, and unlocks moves: 41236 >= 1, 623 >= 2, 6B >= 2, 5B->j.C >= 5.
- Normals: 5A, 5B (80 px) 0xc9 / 0xca (a forward hop), 5C, 2A, 2B, 2C, j.A/B/C, 6B 0xd2,
  5B far -> C 0xd6, dash j.A/B/C 0xe6-0xe8 (her forward dash 0xa3 is a hop), throw 0xdc,
  air throw 0xf8.
- 236A/B/C 0xfa/0xfb/0xfc(EX): tosses an object (0x191-0x193) and kicks it on frame 6 if
  within 60 px; only the kicked frame has an attack box. 236D 0x117 tosses 0x191 without
  the kick (the kick is tested on `pattern == 0xfa`).
- 623A/B/C 0x104/0x105/0x106(EX): rising hits, faster/higher with warm-up.
- 41236A/B/C 0x108 (rush forward) / 0x109 (rush backward; B or C without EX) / 0x10a (EX).
- 214 0x10c: a stance; on its frame 7: 44/66 dash, 236A/B, 623A, A (0x113, or 0x10d at
  warm-up >= 5), B (0x112: throws 0x1ab/0x1ac/0x1ad by 4/5/6), C 0x114, 2C 0x119, 6D/4D
  steps 0x115/0x116 (they loop back to the stance), D 0x10f (+1 warm-up), 2D 0x118.
- 2D 0x118: a pose without the warm-up gain (also from the stance).
- 236236A/B/C 0x12c-0x12e (1/2/3): a tossed bomb, 1/2/3 explosions (0x199-0x19b) that shed
  Random sparks.
- 214214A/B/C 0x12f-0x131: she floats, steerable at 0.5/0.65/0.8, 15/21/21 loops; two
  emitters (head 0x19d, feet 0x19e) fire 320-px-wide hits every 3/2/1 loops.
- LV4 0x132: input 0x61 = C, then 236236 within 90 frames, HP < 3333, full gauge: charges
  10 loops, rushes (99 hits); touching the opponent at speed > 4 bounces off (0x101) with
  two explosions.
- Never entered: 0xd3-0xd5, 0xfd, 0xfe, 0x100, 0x102, 0x107, 0x10b, 0x10e, 0x110, 0x111
  (0x110/0x111 are byte-identical copies of the used 0x115/0x116, 0x10e of 0x114).

### CNayukiB (nayukiB\, asleep)
- Normals: 5A, 5B (70 px), 5C, 2A, 2B, 2C, j.A/B/C, dash A/B/C 0xe6-0xe8 and dash 2A/2B/2C
  0xe9-0xeb, throw 0xdc, air throw 0xf8. No D move.
- 623A/B/C 0xfa/0xfb/0xfc(EX): jumping hits. 236A/B/C 0xfd-0xff: two hits in place (C is
  not EX; the three cases are identical code). 412A/B/C 0x100-0x102(EX): hop and dive,
  in the air too (from frame 2). 214A/B/C 0x103-0x105(EX), air 0x106-0x108: spinning hops.
- 236236A/B/C 0x12f-0x131 (1/2/3): a rising projectile, 3/6/15 hits, shedding sparks.
- Air 214214A/B/C 0x12c-0x12e (1/2/3): a dive (4, 2), 3/6/10 hits.
- 641236A/B/C 0x132-0x134 (1/2/3), only while no orbit runs: two satellites orbit her
  (50 px, the y squashed to 1/4) for m_orbitTime 3000 frames (-2 a frame); each satellite
  hit costs 1000 - 350*level (level 3 gains 50); hit or KO ends it; DrawGauge's bar.
- LV4 0x135: input 0x67 = 236236D, HP < 3333, full gauge: leaps and releases ten
  summons (0x19c-0x1a9) that bounce out, land, show five popups (0x1b1-0x1b5) and attack;
  they have hurtboxes (unk80 5 = the summon was struck: it is knocked about).
- Never entered: 0xd2-0xd6, 0x136.

## Commands these classes use (decoded from their ReadCommands, for the core agent)
History bits are raw: 1 right, 2 left, so forward is `(facing == -1) + 1`, back
`2 - (facing == -1)`, down-forward `(facing == -1) + 5`, down-back `6 - (facing == -1)`.
Scans run oldest to newest (m_inputPos is the next slot to write).
- 0 / 1: left-left / right-right (raw); StartCommand makes them dashes by the opponent's side.
- 6: up after not-up (air jump). 0x0a-0x0d 236+A-D. 0x14-0x17 623. 0x1e-0x21 214.
  0x28-0x2b 412 (4,1,2). 0x32-0x35 2,5,2 + button (0x34 = 22C guard cancel; 0x35 = 22D is
  only read while in 0x60). 0x3c-0x3f 6,5,6 + button. 0x46-0x49 41236 (4,1,3).
  0x50-0x53 421 (CMizukaB) / 631 or 421 (CMizuka). 0x64-0x67 236236. 0x6e-0x71 214214.
  0x78-0x7b 641236 (6,4,1,3). 0x82-0x85 463214 (4,6,3,1). 0x8c-0x8f 2,3,6,1,4.
  0x96-0x99 41236 41236. 0xa0-0xa3 63214 63214. 0xaa-0xad 2,1,4,3,6 then a button.
- Per class (the same numbers are other inputs elsewhere): 0x5a CMizuka A,5,A,6,B,C (unused),
  CMizukaB C,5,B,6,A,5,A (its LV4); 0x5b-0x5f, 0x62 in CMizuka only (unused there: 6BA65A,
  222C, A5A4BC, B5A2AB, 236236 B C, B5A4BA); 0x60 2,6,3 + C (CMizuka; CNayukiB with a full
  gauge, unused by both); 0x61 C then 236236 (CMizuka unused; CNayuki's LV4, full gauge).
- Nayuki's/NayukiB's 236236 and 214214 scans start only with gauge >= 1000.

## Bugs and oddities (all in the original; replay-relevant ones marked)
- **Replay-relevant:** CMizukaB's 421: a button on the same frame as the 1 gives 0x14+btn
  (623) instead of 0x50+btn (mizukab.cpp:631-651, the `(1 && x6 == 2)` branch). Changing it
  changes human input handling, so it is not compat-safe.
- CMizuka/B ReadCommand 0x8c block: a button with the final 4 gives 0xa0+btn; 0xaa block: a
  button with the 6 gives 0xa0+btn (copy slips; also in other classes' ReadCommands?).
- CMizuka StartCommand 236236C tests `m_patterns[0x12c].unk0` (mizuka.cpp:128); CNayukiB's
  412C tests 0x103's (nayukib.cpp:201). Harmless if the .pat priorities match.
- CMizukaB Vf8 ends the flight on `pattern < 0x31 && pattern < 0x96` (mizukab.cpp:494):
  probably meant `> 0x31` (being hit); as written being hit doesn't end it, landing does.
- CMizukaB 0x1d0/0x1d2/0x1d5: `if (frame > 0x31 && frame < 0x96)` tests the player's frame
  where pattern was meant, and the landing test adds the player's vy to the object's y
  (mizukab.cpp:3662, :3742; also :3786/:3866, :3921/:4001).
- CNayuki 0x107/0x10d/0x113 test `y + vx > 0.0` where vy was meant (nayuki_vf6.cpp:3930,
  :4295, :4579).
- CNayuki CpuInput: `m_command = (WORD)Random(0, 2) * 0x6e` (nayuki.cpp:927: 0 = a dash, or
  214214A, never B/C), and two impossible ranges (`m_cpuRoll < 0x10 && m_cpuRoll > 0x12`
  :930 for the LV4, `< 0x2a && > 0x2f` :1420). The CPU sends 0x61 without the HP check.
- CMizuka and CMizukaB share one CpuInput (identical text). For CMizukaB it sends inputs its
  StartCommand ignores: 0x70 (214214C), 0x78-0x7a (641236), 0x28/0x29, 0x5f, air 214;
  0x66 on the ground; it never sends 421, the LV4 0x5a or air 236236. CMizuka also ignores
  0x28/0x29/0x5f. CNayuki's CPU never uses 236D or 236236C; in the stance only neutral
  buttons. CNayukiB's CpuInput tests `pattern == 0xee`, which it has no case for.
- Random use: CMizuka/B walkers' speed, 623C's x and the catch roll; CNayuki's explosion
  sparks; CNayukiB's 236236 sparks and every LV4 summon all draw through CPlayer::Random,
  so they are recorded in replays even where they are only visual (sparks). Debris
  0x1f1/0x1f2 use rand() (docs/compat.md).

## Shared numbers (< 0xc8, and 0x1ef-0x1f3) seen in these classes, for the core agent
- 0xa3 forward dash: CMizuka runs (vx 1.5, unk58 1/3 on frames 5/6), stops (0xb2) after
  42 frames held or 24 released; CNayuki hops (1.4, -0.75); CNayuki's air dashes
  0xa5/0xa6 wait for the kObjAirDashStep object (m_patternVar1) and land in 0xb3 (a
  landing state for her).
- 0xb3-0xb5 are CMizuka/B's flight (D); CMizukaB also has 0xa1 (unused) and 0xa2 (22D
  while getting up, 1000 gauge: jumps out), 0xb6 (unused). 0x60 is getting up (0x61/0x62
  land -> 0x63 lying -> 0x60); CNayuki loses a warm-up level there.
- 0x53-0x56 spawn kObjBurst once (m_burstObjectOut); 0x51 spawns 0x1f3; 0x57 spawns
  0x1ef in screen space (60,40). Every class has these objects (docs/compat.md calls
  0x1f0-0x1f2 the burst); names as the other agents chose them.
- CPlayer members as these classes use them (not named here): unk118 the EX resource (C
  specials cost 500, 22C needs >= 500 and zeroes it, CMizukaB's flight drains it); unk120 an
  "EX mode" that halves the cost and drains unk118 0.8 a frame in 0x46/0x52; unk14c the
  super-flash freeze (0x78 at every super, the opponent's UpdatePattern returns while > 0);
  unk14a hitstop of the player; unk158 "keep sliding" after a dash; unk159/unk15a air-dash
  and air-action counts; unk58 1/3 on dash frames, 2 on CMizukaB's teleport (invulnerable?).
  PlayerObject: unk84 = hits the object can still land (0x63 for multi-hit), unk80 = its
  attack result (3 hit, 5 = it was struck), unk86 its hitstop.
- **efz.h's comments on m_inputX and m_inputHistory say "relative to facing (1 forward)"
  and "bits 1 forward, 2 back"; the code says raw: ReadInput (player.cpp:1042-1052) gives
  m_inputX 1 for right whatever the facing, StartCommand tests `m_inputX == facing` for
  forward, and ReadCommand tests `(facing == -1) + 1` for a forward history entry.**

## Vf8 (CPlayer's slot, called once a frame for both players by CScene3, scene3.cpp:150)
CMizuka, CNayuki: empty. CMizukaB: the flight's unk118 drain and end. CNayukiB: the
641236 orbit's angle and timer. A per-frame "tick" outside UpdatePattern (it runs even
during hitstop, which returns early from UpdatePattern).

## Not determined / doubts
- What the objects look like: names say what they do (walker, riser, sweeper, catcher,
  satellite, summon...). kObj214 (107x133, hits once on frame 8) is probably a pillar;
  0x1a5-0x1b6 are figure-sized (79x127): perhaps characters in the cinematic.
- kObjCatchProp (0x1b7): a 37x46 object beside Mizuka in the B/C catch cinematics; its role
  (a counter? the tally?) is unclear.
- m_patternVar1-3 / m_objectVar1-3 are honest but generic: each pattern or object type uses
  them its own way. The scheme (three ints zeroed by StartPattern, three 64-int arrays
  zeroed by RemoveObject) is the same in every character; I matched the names most other
  agents chose (m_patternVar1-3, m_objectVar1-3, m_burstObjectOut, kObjBurst,
  kObjBurstPiece/2, kObjLaunchFx, kObjLv4VictimOverlay: another agent found 0x57 is
  the state of being hit by a LV4).
- The unused patterns are named kUnusedNN (what they would do is in patterns.txt); some
  have frames in the .pat (0xd8 and 0xe9 in mizuka.pat even have no code at all).
- CMizuka 0xf9's purpose (unkdc 4, unkde -20, unk14c 60, effect 0x28): not determined.
