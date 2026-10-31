# GAME agent notes

Method: read every use in src/ (game, effect, scene0-8, scene3_draw, bg*, main, config,
input, graphics, sound, trace), and checked what the game shows by decoding the 4.02 data
in ~/.local/share/efz-decomp/game/system (title_ob, chr_sel_ob, config_ob, score, result,
replay, bgNN/bgNNb, effect.pat + effect.dat, every character's .pat) to PNG. Scratch
renders: scratch /gamework/img/ (fx_*.png = every effect's frames).

## The scenes (g_scenes[], WinMain)

| # | Class | What | Leaves to |
|---|---|---|---|
| 0 | CScene0 | title menu: ARCADE, VS CPU, VS HUMAN, PRACTICE, REPLAY, OPTION, EXIT (title_ob.dat); idle 1800 frames starts the demo | 1, 2 (demo), 6, 8 |
| 1 | CScene1 | character select (3x8 grid), colour (6, EDIT COLOR with down/D), stage select (VS/practice/replay); F1-F4 reload key bindings | 2, 0, 8 |
| 2 | CScene2 | "now loading" (random nl/nlNNN.dat): picks demo/arcade opponents and stages, reads or writes the replay header, loads stage + negative + animated bg, loads players | 3 |
| 3 | CScene3 | the fight | 5, 1, 0, 8 |
| 4 | none | g_scenes[4] is NULL | |
| 5 | CScene5 | result screen: winner's portrait and win picture, loser's animation, arcade continue prompt, mode 2 stage result; saves the records | 1, 2, 7, 0 |
| 6 | CScene6 | OPTION: the config menu, the loading-screen gallery, character records | 0 |
| 7 | CScene7 | staff roll (stfr.dat), after clearing arcade | 0 |
| 8 | CScene8 | replay browser: REPLAY 1-9 pages x DATA 1-9, play / record / back, overwrite prompt | 2 (play), 1 (record), 0 |

## CGame::m_gameMode (unk1364) values; suggested constants

kModeArcade 0, kModePractice 1, kModeArcadeScore 2 (never set: no title item; plays like
arcade with no continue, CPU level rising with the match number (scene2.cpp:340), damage
always 100%, a "stage N result" bonus screen and best-score records), kModeVsCpu 3,
kModeVsHuman 4, kModeReplay 5, kModeDemo 6. Title rows map 0->0, 1->3, 2->4, 3->1, 4->5.
F4/F5 refill works in modes 1, 3, 4, 5; F6/F7 dummy controls only in 1; F6 restarts a
recording in 5.

## key.ini

0x00-0x1f bindings (2 players x 8 x 2 bytes, CInput::LoadBindings); 0x20 graphics mode
(0 320x240, 1 640x480, main.cpp:94); 0x21 CPU level 1-4 (also "settings present" when
> 0); 0x22 draw rate + 1 (0 30FPS, 1 60FPS); 0x23 effects + 1; 0x24 damage 1-3; 0x25 not
read by efz.exe; 0x26 rounds 1-3; 0x98 > 0 enables F2-F4 presets on character select;
0x9c preset loaded at startup; presets at set * 39.

## The fight's keys (CScene3::HandleKeys, scene3.cpp:486-613)

Esc quit; F4 held: refill meter +5/frame (wraps 2000 -> off); F5: refill on (1000) ->
HP 3332 -> off; F6: practice dummy stance, or restart a replay recording; F7: practice
dummy guard; F8 pause. Compiled out (`if (1) {} else`): F1-F3 speed 1-3, F9/F10 screenshot
capture on/off, F11 reset its counter, F12 both HP to 1. g_fkeyHeld makes F5-F8 act once.

## Round flow

CGame::Reset: round 1, m_intro 1. StartIntro: m_intro 1 -> effect 0x1b (the motto "the
true eternal does exists here.", sic) whose frame 26 makes 0x05; m_intro 2 -> 0x05
directly (sound 0xb + round). 0x05 frame 10 -> "ROUND" 0x15 + digit 0x38+round, frame 15
-> swoosh 0x1a; 0x15 end -> 0x06 + 0x16 "GET READY?"; 0x16 -> 0x17; 0x17 end -> 0x07 +
0x18 "ATTACK!!"; 0x18 -> 0x19; 0x19 end -> wipe 0x12 and m_intro = 0. Input is dropped
while m_intro or m_roundOver. CheckKo: a KO that does not end the match shows 0x13 DOWN on
the loser's side and freezes both players 180 ticks; when both players are neutral again HP resets to
9999 and m_intro = 2. The match's last KO sets m_leave 2, m_speed 1 (slow motion) and
the end fade (200 frames).

## Arcade flow

Character select: m_arcadeMatch 1, m_beatenChars 0. CScene2 picks a random opponent not
yet beaten and not 0x12, 0x13, 0x16 (locked ones too) and its home stage; match 8 is Kanna
(0x13) if the player never continued, else Mizuka (0x18, also when the extra characters
are missing). A loss offers コンティニュー？ YES/NO; YES rematches the same opponent and
remembers the match in m_continuedAt. Winning match 8 goes to the staff roll (scene 7).

## Left unnamed (not determined, or never used)

- CGame: unk1345 (set 0 in the constructor, never read), unk1347, unk1351, unk1367 (no
  uses), unk1352 (set to 300 / 270 when an intro starts, scene3.cpp:647,661, never read),
  m_effectUnk2784 (cleared per slot by CreateEffect, never read); byte padding unk1335,
  unk1359, unk1371, unk137a, unk2a04, unk142a8.
- Effect: every member but type/frame/timer/x/y/vx/vy/side/scale/layer/screen and the two
  named (unk6, unk8-unk14, unk38-unk44, unk49, unk4a, unk52, unk58-unk68, unk6d, unk6e) are
  never touched. Its layout copies PlayerObject's (x at 0x18, facing at 0x48, side 0x4c,
  scale 0x50, layer 0x51, screen 0x54, sound at 0x6c like PlayerObject::unk6c).
- EffectDesc: unk6, unk19, unk1a, unk22, unk2d, unk2e, unk44 never set or read.
- EffectAnim: unk1, unk2 (padding; the .pat's per-animation header ints are discarded).
- CharRecord::unk14: saved and loaded, never changed or shown.
- CFile::unk8, CGraphics::unk20405, CInput::unk100 / unk1f4, CScene::unk42f: no uses.
- CScene0::unk43e (cleared when the cursor moves, never read).
- CScene1::unk555: the stage-hidden byte for stage 17 (inside the 0x17-byte memset),
  never set; declared as padding.
- CScene6::unk44a, unk748 (set 0, never read).
- CScene8: unk43c, unk440, unk446, unk448, unk44a, unk44c (set to CScene1's portrait
  slide start values, never read); unk462-unk467 (the tail of the unused table in
  unk44e[2..]).
- Global g_unused7b127c (input.cpp:16): 16 bytes nothing uses; it is the only global still
  named by its address. Left as is.

## Observations for the core agent (CPlayer, PatternFrame, PlayerObject)

- PatternFrame::unkc0 = the hit's effect type and unkc1 = its sound (scene3.cpp:1366-1373):
  0 blue burst, 0xb/0xc/0xd light/medium/heavy orange sparks, 0xe/0xf/0x10 slash sparks
  (sound 4), 0x34 explosion, 0x38 none (sound only), 0x43, 0x48 (see effects.txt).
- PlayerObject: unk58 = has a shadow (EffectDesc::shadow; scene3_draw.cpp:504), unk6c =
  sound (EffectDesc::sound), unk88 = moves during its owner's freeze (EffectDesc::movesInFreeze),
  unk8c = still drawn while CGame::m_hideObjectsTime runs. CPlayer::unk2d0[] = per-object
  keep flags (EffectDesc::keep), AdvanceObjectHead skips them.
- CPlayer::unk3118-unk3134 are a CharRecord: uses, vsWins, vsLosses, bestScore,
  bestScoreHigh, (unk312c = record unk14), maxCombo, maxDamage.
- CPlayer::unk30ec / unk30ee: copies of CScene3::m_refillMeter / m_refillHp
  (player.cpp:324-336). unk30dc: sum of the winner's remaining HP over rounds (mode 2's
  life bonus). m_hitsLanded is used as the mode 2 score accumulator (scene5.cpp:461-469).
- CPlayer::unk14c freezes the opponent (super flash; +180 on a KO), unk14a is hitstop
  (camera focus timers and fills stop while either is set). unk14e = 60 when back is
  pressed; >= 30 makes a guard a recoil guard (actions 0xa8 stand, 0xa9 crouch, 0xaa
  air, effect 0x11; EfzRevival calls it Recoil Guard). unk118/unk120: the meter under the
  gauge (0-1000, unk120 = full/active); C specials spend 500 of it; F4/F5 set it.
- CPlayer::Unk410a40 / Unk410a80 set the camera focus (CGame::m_cameraFocusX/Y).
- Actions seen from the scenes: 0x2f the loser's animation on the result screen
  (scene5.cpp:505-537: placed at 480,-240 facing left); 0x3b both players on a double KO
  (scene3.cpp:413-416); 0x46 wall bounce; 0x61/0x62 hitting the ground (effect 3, shake);
  0x96-0x9c guard (0x9c in the air); 0x9d/0x9e air recovery forward/back
  (player.cpp:345-364); 0xa3-0xa6 dashes; 0xa7/0xab the meter cancel (command 0x34,
  effects 1 and 4); 0xa8-0xaa recoil guard; 0xa1/0xa2 create effect 9 and attack.

## Oddities and bugs

- CScene3::UpdateCamera: both branches of the vertical focus step add m_focusYStep
  (scene3.cpp:278-288), and m_focusY is overwritten on the next line anyway: dead code.
- A double KO counts a round for both players but caps it at m_roundsToWin - 1
  (scene3.cpp:404-421): a double KO never ends a match.
- Mode 2 is unreachable, so CharRecord's best score is never written in 4.02.
- Records keep max combo/damage only at damage 100%; VS wins/losses only in VS HUMAN.
- The FPS counter (CScene3::m_fps) is drawn at the top centre of the HUD.
- Character ID 0x16 creates a second CNayuki (like 0xa); 0x18 is Mizuka (boss), not on the
  grid. CScene6::m_names has its own order (folder names), with 24 slots for 23 entries.
- CScene8's constructor fills a 24-entry character table (unk44e[2..], unk462-unk467)
  and 19 RECTs inside unk46e (+0xf6..) that nothing reads; Unk771170/Unk771230 and
  CScene0's Unk776820/Unk7768d0 are never called.
- EfzRevival's revival/EfzRevival/Efz.h comments disagree with the game here: its
  `hasPalette` (0x1338) is the EDIT COLOR flag; its `unk1343 "the side a human plays"` is
  m_isCpu[0] (the human side is 0x1342); `CScene::unk2d "1 round over"` is "quit"; its
  `CScene0::menuChoice "2 VS COM, 3 VS PLAYER"` does not match title_ob.dat's order
  (1 VS CPU, 2 VS HUMAN, 3 PRACTICE). Worth checking against Revival's menu patch.

## Suggestions beyond renames (layout, for whoever edits efz.h)

- CScene1::unk544[0xd] + unk551..unk554 + unk555 + unk556..unk55a are one 0x17-byte
  array (stage-hidden flags; the memset at scene1.cpp:958 clears all). Declaring it as
  `char m_stageHidden[0x17]` and writing m_stageHidden[0xd] = 1 should compile the same
  (constant indices), but needs make check.
- CScene8::unk46e[0x2da] is three things: char exists[9][9] (+0x46e), char chars[9][18]
  (+0x4bf), padding, RECT rects[...] (+0x564). The 2-D index casts in scene8.cpp would
  disappear; the index arithmetic may compile differently, so measure.
- Effect types and modes as enums (effects.txt, the list above): free per readability.md.

## For the renaming process

- tools/members.py rename does not see into macros: about 150 `TOPTR(T, unkNNN)` uses of
  the scenes' surface members (scene0 6, scene1 46, scene2 3, scene5 34, scene6 40,
  scene7 3, scene8 17) need the same names by hand. scene7.cpp already shows it: lines
  25, 60, 62 still say unk434 after m_staffSurface was applied.
- trace.cpp (TraceStart, TraceHashScene, TraceHashGame) and docs/compat.md,
  docs/readability.md, docs/revival.md name some of these members/methods
  (unk1364, unk14281, CScene2::Unk76da20, CScene3::Vf2, CScene3+0x578...).
