# EfzRevival's features in the native game

EfzRevival 1.02h ([revival.md](revival.md)) adds to `efz.exe` netplay, practice tools, a
tournament mode, custom music and window settings. The native game has them built in,
from the recovered source in `revival/` (each section below names the files), and reads
Revival's own settings file. Netplay itself is [netplay.md](netplay.md); this is the
rest, and the netplay settings that file controls.

What isn't here: **spectating**, either way (a native host still turns spectators away,
and the native game can't watch a match).

## EfzRevival.ini

`port/revival/config.cpp` reads `EfzRevival.ini` from the save folder, else the game's
folder, as Revival reads it (`revival/EfzRevival/Config.cpp`): UTF-16, as Revival ships
it, or UTF-8; `[Section]` and `Key = value` lines, `;` comments. Keys are DirectInput's
names (`DIK_SPACE`, `DIK_NUMPAD0`; the list is in Revival's own ini) or a button of the
controller P1's A is on (`BUTTON_1` to `BUTTON_32`), `None` for none. A key the file
doesn't name has the value Revival ships, so the game without the file behaves as
Revival as installed. A Revival player's file can be copied over as it is. OPTIONS' second
page sets the most used of these in the game, and has switches of the native game's own
for EfzRevival's features offline, each tool, and the input display ([native.md](native.md),
"OPTIONS").

| Section | Keys | Used for |
|---|---|---|
| `[Network]` | `Name`, `Port` | NET PLAY's NAME and PORT until its own screen has set them (`netplay.ini`) |
| | `MaxRollback` | The most frames rolled back (0-9, default 4) |
| | `HolePunchingServer` | The hole-punching server, `HOST:PORT` or `None` (below) |
| | `AllowPracticeKeys` | F4 and F5 work in a match when both sides set 1 |
| | `IncreaseInputDelay`, `DecreaseInputDelay` | The input delay in a fight (keypad + and -; F10 and F9 work too); in a replay, seeking |
| | `ToggleRemotePalettes` | Show the other player's custom palette or the colour's own |
| | `DisplayScore` | Wins on screen |
| | `SaveAllReplays`, `ReplayFolder`, `SavePreviousReplay` | Every match's replay saved to the folder, or (0) only when the key is pressed on character select or the results |
| | `SaveBattleLog`, `BattleLogFile` | The battle log (below). `LogScore` is read and, as in Revival, not used |
| `[Practice]` | every key | The practice and replay tools (below) |
| `[Tournament]` | `P1_Name`, `P2_Name`, `TournamentFolder` | The tournament (below) |
| `[Global]` | `WindowX`, `WindowY`, `WindowWidth`, `WindowHeight` | The window's place and size at start |
| | `SoftwareRendering` | SDL's software renderer |
| | `BGMFolder`, `MuteBGM`, `ToggleBGM` | The music (below) |
| | `BackBufferWidth`, `BackBufferHeight`, `Debug` | Not used: Revival's Direct3D back buffer (SDL scales the picture here), and its logs (the game's log is [logging.md](logging.md)) |

## Netplay

`port/netplay/session.cpp`, `palettes.cpp`, `protocol.cpp`, from Revival's
`OnlineSession.cpp`, `EfzPalettes.cpp` and the launcher's `ProtocolState*.cpp`:

- **Custom palettes.** A player who picked an EDIT COLOR palette (`<character>\<character>N.pal`)
  sends it to the other side every 30 frames of character select and match setup
  (MessagePalette); the other side shows it in the fight. `ToggleRemotePalettes` (Space)
  in a fight shows the colour's own instead, or back, on the next frame both players'
  inputs are known (a rollback never undoes it).
- **Replays.** As Revival saves them, in `ReplayFolder` (default `replay/netplay/`, made if
  missing). With `SaveAllReplays = 0` each match's replay is kept until the next match
  starts; `SavePreviousReplay` (S) on character select or the results saves it, and the
  screen says "Saved replay to disk" or "Failed to save replay".
- **The battle log** (`BattleLog.txt` in the save folder): a line when a session starts,
  `<date time> <P1> VS <P2>`, then one a game, in Revival's columns: when it began, the
  characters, the rounds each won, how long it took and the score.
- **Practice keys.** `AllowPracticeKeys = 1` on both sides lets F4 and F5 through in a
  fight (refill, and the meter); the delay screen says whether they are on.
- **Hole punching.** A host behind a router, with no port forwarded, can be joined through
  a hole-punching server, as Revival's launcher does it: the host pings the server once
  as it starts hosting, so the server learns its address as the internet sees it; a
  joiner the host hasn't answered yet asks the server (MessagePunch, every half second)
  to introduce it; the server tells the host where the joiner is and the joiner where the
  host is, and each sends there (that port and the nine after it, one a punch), which
  opens both routers to the other. The default server is Revival's own
  (`128.199.38.97:10800`), which this game then contacts when it hosts or joins; set
  `HolePunchingServer = None` to never use one. Revival's server program isn't among its
  files: `tools/punchserver.py` is one, made from what the launcher sends and expects,
  for anyone who wants their own.

## Music

`port/revival/music.cpp`, from Revival's `Music.cpp` and `MusicList.cpp`. The `.wav`,
`.mp3`, `.ogg` and `.flac` files of `BGMFolder` (a full path; a yen sign is taken for a
backslash) play in random order instead of the game's music on match setup and in a
fight, a new one each match, the same one again when it ends in a long fight. Revival
also plays `.wma`, through Windows' DirectShow; this game skips them, with a line in the
log. `MuteBGM = 1` starts with the music off, and `ToggleBGM` (F12) turns it off and on
anywhere. The decoders are dr_mp3 0.7.4, dr_flac 0.13.4 and stb_vorbis 1.25, one file
each, fetched by CMake (`tools/native.sh` keeps them in `~/.cache/efz-native`).

## Practice: VS PLAYER and PRACTICE

`port/revival/practice.cpp`, from Revival's `PracticeSession.cpp` and `Recorder.cpp`. In
a fight of VS PLAYER or PRACTICE (the game's own F-keys work as ever):

| Key (default) | |
|---|---|
| `Pause` (Space) | Pause and go on; Esc while paused goes on too |
| `StepFrame` (P) | One frame, paused (the overlay counts them) |
| `Save` (G), `Load` (B) | Save the fight's state, and go back to it |
| `ToggleDisplay` (Enter) | The text overlay |
| `ToggleHitBoxes` (Page Up), `ToggleHurtBoxes` (Page Down), `ToggleCollisionBoxes` (Home) | Red hit boxes (dashed once the attack can't hit any more), blue hurt boxes, yellow collision boxes with the crossup line through the player's x; the players' objects' too |
| `IncreaseFPS` (Insert), `DecreaseFPS` (Delete), `ResetFPS` (End) | The game's speed, 16 frames a second at a time |
| `IncreaseInputDelay`, `DecreaseInputDelay` (keypad + and -) | Delay the player's own inputs |

VS PLAYER only (the dummy is P2, or P1 when P2 started the mode):

| Key (default) | |
|---|---|
| `ToggleRecord` (H) | Record the dummy: the player's controls drive it until pressed again |
| `ToggleReplay` (N) | The dummy plays the recording back |
| `SwitchStartCondition` (Left Ctrl) | When the recording or replay starts: Now, Wake-Up, Tech, Guard, Recoil Guard, Random RG |
| `SetBuffer1`-`5` (1-5) | Which of the five recordings |
| `ToggleReplayRandom` (0) | Replay a random non-empty one |
| `SwitchPlayers` (keypad 0) | Control the other side |
| `MirrorPlayers` (keypad 3) | Swap both players' positions around the stage's middle |

The overlay shows who plays, what the dummy does (What), when it starts (When), the
buffers, the delay and the frames stepped, and the input display: the player's last 15
inputs, newest first, each with how long it was held, the direction as the keypad's
digit (8 up, 2 down, 4 left, 6 right, 7 up-left and so on, 5 none) then A, B, C, D (Revival
draws arrows; SDL's font here has none). As in Revival:
Tech with Record gives control at the first frame a tech is possible, without teching;
Guard holds back and down (up against a jump); Recoil Guard makes every guard a recoil
guard, Random RG half of them.

Otherwise than Revival: the dummy's recorder acts only in these fights (Revival's runs in
every fight, the same unless a start condition was left on); its random draws are its
own, not the game's rand; Esc while paused goes on. A fight a load, a mirror or the
recoil-guard dummy changed from outside the game's own rules has no fight record
([logging.md](logging.md)) from then on: its record ends there, with that as the reason.

## Replays

`port/revival/replay.cpp`, from Revival's `ReplaySession.cpp`. A replay played from the
REPLAY menu can be paused, stepped, sped up and slowed down, saved and loaded, and the
boxes shown, with the practice keys; `IncreaseInputDelay` and `DecreaseInputDelay` seek
forward and back by the states kept every 64 frames. An EfzRevival replay (a netplay
replay, Revival's or this game's: the game's part, then its random state and both
players' inputs) is played from that copy of the inputs, with Revival's random generator
from its state and netplay's settings (normal effects, every frame drawn, 100% damage, 2
rounds), as Revival plays it, with both players' input displays; pressing a direction or
a button takes over P1 (`SwitchPlayers`: P2), the other side going on with the replay,
until `Load`. A replay without that part shows "Not an extended .rep". The fight record
([logging.md](logging.md)) of a replay played from Revival's inputs, or where a state was
loaded, stops there. While the REPLAY
menu records a replay, pause, step, speed and the boxes work too; the replays this game
records are the game's own, without Revival's extended part. The REPLAY menu's other
mode (Tab: the fight records) plays as before ([logging.md](logging.md)).

## The tournament

`port/revival/tournament.cpp`, from Revival's `TournamentSession.cpp`:

```sh
efz --data DIR --tournament
```

The game walks its title to VS PLAYER by itself. The players are `P1_Name` and
`P2_Name`, read again on character select: new names start a new set, its score from 0.
The score and the names are on screen. Each match's replay is saved in
`TournamentFolder` (default `Tournament/`) as `<date-time> <P1> (<character>) vs <P2>
(<character>).rep`, and each set's results go to its `tournament_results.txt` (with
`SaveBattleLog = 1`), in the battle log's columns. In a fight the function keys do
nothing and Esc leaves only once held 80 frames (a second and a quarter); B on character
select doesn't go back to the title, and the colours stay from one character select to
the next. Back on the title the game quits: Esc on character select goes there, as ever,
so an Esc held on past the fight's end ends the tournament (Revival's too). There is no custom music in a tournament
(`MuteBGM` still holds). Otherwise than Revival, the replays are saved whatever
`SaveAllReplays` says.

## Not changed

Revival forces normal effects and makes left and right together left in every mode it
runs. The native game does that only in a network match: offline it stays the original,
whose replays and the compatibility suite ([compat.md](compat.md)) are kept to it. None
of the above runs under the compatibility suite's harness, nor while a fight record is
played from the REPLAY menu.

## Checked

- The compatibility suite, unchanged (`tools/compat.py check`).
- `tools/nettest.py native` and `revival` (netplay, [netplay.md](netplay.md)), and
  `tools/nettest.py internet`: a match over the internet with another machine, the
  other hosting, then this one hosting behind its router with nothing forwarded and the
  other joining through `tools/punchserver.py`, and without the server, which must not
  connect. First run, 21 November 2026, a home connection to a server in Miami (ping 78
  ms): all three as they must be, the sync records the same on every frame compared and
  each fight's replays the same on both ends.
- The music: a `.wav`, an `.mp3`, an `.ogg` and a `.flac` of a 440 Hz tone, each played
  through a fight with SDL's disk audio driver: the tone in the output, each file played
  to its end (132,300 frames, 3 s) and again.
- The practice tools: VS PLAYER driven by scripted keys (`--keys`), the window saved
  (`EFZ_DUMP_WINDOW`): the overlay, the boxes, the speed, pause, step, save and load
  (the fight's record ends at the load); the dummy recorded (P2 walking and pressing A
  with P1's keys) and replayed: the fight record has the same inputs at the same offsets
  from each start; the start conditions, buffers, random and switching in the log.
- The replays: a netplay replay of two native games in a REPLAY slot, watched to its
  end from its own inputs (1,242 frames) and compared with the same file converted by
  `--rep-to-record`, which plays the game's words: the same inputs on all 3,723 ticks
  both have, and the same players, objects and effects throughout (the replay mode and
  the random state differ, as they must); pause, step, save, seeking back, a takeover of
  P1 and Load back to the replay.
- The tournament: the walk to VS PLAYER, Esc pressed briefly (nothing) and held (the
  fight left after 80 frames), the replay in `Tournament/`, the set's line in
  `tournament_results.txt`. Esc held on into character select goes back to the title, as
  the game's character select does, which ends the tournament.
- The palettes: two native games, the joiner's EDIT COLOR palette (a file only it has)
  shown on the host as the one sent.
