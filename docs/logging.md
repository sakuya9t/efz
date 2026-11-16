# Logging, crash reports and fight records

The native game ([native.md](native.md)) keeps a record of each run: what happened, by
level; a report when it crashes or hangs; checks of the game's state after every tick of a
fight; and a record of every fight complete enough to replay it, tick for tick, and to
learn from. This document describes what is written, where, in what format, and how to
use it. The code is in `port/log.cpp`, `port/crash.cpp` and `port/record.cpp`.

## Where it goes

Each run of the game is a **session** with a folder of its own under the logs folder,
named for when it started:

```
<save folder>/logs/20261103-182001-4f2a/
  efz.log               what happened, a line each
  session.json          the run's facts and how it ended
  fight-001.jsonl       the first fight's record
  fight-001.state       the game's state at its first tick
  fight-001.rep         the replay file it played, if it played one
  fight-001-t004321.state   the state at a tick where a check failed
  crash.txt, crash.dmp  after a crash (the .dmp on Windows)
  hang.txt, hang.dmp    after a hang
```

| Option | |
|---|---|
| `--log-dir DIR` | the logs folder (also `$EFZ_LOG_DIR`); default the save folder's `logs`; `none`: no files |
| `--log-level L` | what `efz.log` gets: `debug`, `info` (the default), `warn`, `error` (also `$EFZ_LOG_LEVEL`) |
| `--log-keep N` | the sessions kept, the newest (default 20); `0` keeps any number |
| `--log-max-mb N` | and no more than N MB of them, the newest (default 2048); `0` any size. For collecting data, `--log-keep 0 --log-max-mb 0` keeps everything |
| `--verbose` | stderr gets every line; otherwise warnings and errors |
| `--record`, `--no-record` | fight records: on, except under the compatibility test's harness (`EFZ_TRACE`), which runs hundreds of fights |
| `--seed N` | `rand()`'s seed for the run; by default the clock, as the original. Logged either way |

Every file is written straight through, a line at a time, without a buffer of the
program's: what was logged before a crash is on disk after it. Nothing in the log or the
records allocates from the game's arena once the session has started.

## efz.log

```
2026-11-03 18:59:09.524 +2.489 f=1 s=3 INFO  fight: fight 1: ayu (P1, cpu) vs nayuki (P2, cpu), stage 1, vs cpu
```

The local time, seconds since the start, the main loop's frame and scene (0 title, 1
character select, 2 match setup, 3 fight, 5 results, 6 config, 7 staff roll, 8 replays;
-1 before the loop), the level, a category, the message. The categories:

| Category | |
|---|---|
| `log` | the session itself; a previous session that crashed or never recorded its end |
| `main` | options, folders, SDL and its drivers, the seed, `key.ini`'s settings; each change of scene with how long the scene's frames took; a fight frame that took over 1/4 s without waiting in a fade; why the game quit |
| `video`, `input`, `sdl` | the renderer; controllers plugged and unplugged; SDL's own messages |
| `file` | a file the game couldn't open (debug level: the game tries files that needn't exist) |
| `game` | the game's own error messages (its message boxes) |
| `arena` | the arena out of room, a pointer outside it (both fatal) |
| `fight`, `record` | each fight's start and end, with the result and its record |
| `check` | a check of the state that failed (below) |
| `replay` | a replayed fight's progress and verdict |
| `crash`, `watchdog` | a crash; a main loop that stopped |

The last 256 lines of every level, debug included, are kept in memory too: a crash report
ends with them, so it shows the files the game failed to open just before, even when
`efz.log` doesn't.

## session.json

```json
{
  "format": "efz-session", "version": 1,
  "id": "20261103-185907-7461",
  "status": "exited",
  "started": "2026-11-03T18:59:07.034-08:00", "ended": "...", "exit_code": 0, "seconds": 5.8,
  "build": {"revision": "28d9caa6d4ad", "dirty": true, "compiler": "msvc 194435229",
            "config": "RelWithDebInfo", "os": "windows", "arch": "x64"},
  "args": [...], "data": "...", "save": "...", "sdl": "3.4.18", "video": "...",
  "audio": "...", "seed": 1793761147, "renderer": "...",
  "counts": {"fights": 1, "anomalies": 0, "warnings": 0, "errors": 0}
}
```

`status` is `running` while the game runs, then `exited` or `crashed`. A session that
still says `running` when the next one starts ended without saying how (killed, hung, or
a crash the handler couldn't report): the next session's log says so. The revision is
git's when the game was built (`tools/buildinfo.cmake`); `dirty` means it had changes.

## Crashes and hangs

`port/crash.cpp` catches access violations, illegal instructions, arithmetic faults,
`abort()` (which `Fatal`, the arena's checks and failed assertions end in), an uncaught
exception, and on Windows the C library's invalid parameters and pure virtual calls. It
writes `crash.txt`:

```
efz crash report

what:    access violation (0xc0000005) writing 0x0 at 00007FF7672D93A7 (efz.exe+0x3593a7)
session: 20261103-185547-f2ab
build:   28d9caa6d4ad+ (msvc 194435229, RelWithDebInfo, windows x64)
time:    2026-11-03T18:55:47.719-08:00, 0.0 s after the start

stack, innermost first:
   0 efz.exe!efz::CrashTest+0x67 (crash.cpp:589)
   1 efz.exe!EfzMain+0x2814 (main.cpp:282)
   ...

game:
  scene 3 (fight), frame 12345 of the session
  fight 3: tick 4567, frame 1530 of the fight, during the tick
  P1 ayu (human), at the last tick's end: action 163 frame 2, x 312.50 y 0.00, hp 7200, ...
  its record: .../fight-003.jsonl
  to replay it: efz --data DIR --replay-fight ".../fight-003.jsonl"

log, the last lines (debug included), oldest first:
  ...
```

then sets `session.json`'s status to `crashed`, ends the fight's record with an `end` line
whose reason is `crash`, and lets the system end the game (a core dump on Linux and
macOS). On Windows it also writes `crash.dmp`, a minidump that Visual Studio or WinDbg
opens with `efz.pdb`, and shows a message box saying where the report is (not without a
display). The stack trace names functions and lines on Windows (from `efz.pdb`); on Linux
and macOS it gives each frame as `efz+0xOFFSET`, which `addr2line -f -C -e efz 0xOFFSET`
names.

**A crash in a fight can be replayed.** The fight's record holds every tick up to the
crash, so `--replay-fight` plays it again to the same point, in a debugger if need be.

The **watchdog**, a thread of its own, reports a main loop that hasn't advanced for 15
seconds (message boxes excepted): an error in the log and `hang.txt` with the game's
state; on Windows also the main thread's stack and `hang.dmp`. It says so again if the
loop goes on.

`ctest` checks the report on every platform CI builds: `efz --crash-test segv` (or
`abort`, or `fatal`) crashes on purpose, without game data, and `tests/crash_test.cmake`
checks the report it leaves.

## The checks

After every tick of a fight, the recorder checks what the game's state should never be.
Each kind is logged the first tick it shows in a fight, with the state at that tick in
`fight-NNN-tTTTTTT.state` (four at most a fight), and an `anomaly` line in the record;
after that it is only counted, and the fight's end gives the counts.

| Check | Level | When |
|---|---|---|
| `nonfinite` | error | a player's position, velocity or acceleration is NaN or infinite |
| `position` | warn | a player is far outside the stage: x below -100 or above 740 (the walls are at 20 and 619), y below -2000 or above 100 (0 is the ground) |
| `facing` | error | facing is neither 1 nor -1 |
| `action` | error | the action (pattern) is beyond the 505 a character has, or has no frames |
| `frame` | error | the frame is beyond its action's animation |
| `hp`, `gauge`, `guard_gauge`, `rf_gauge` | warn | outside -9999 to 9999, 0 to 3000, 0 to 360, 0 to 1000 |
| `combo`, `timers` | warn | negative hits or damage in a combo; negative hitstop or freeze |
| `object_nonfinite`, `object_action`, `object_frame` | error | the same, for the 64 objects a player spawns |
| `stuck` | warn | the round is on, nothing stops the player (no hitstop, no freeze from the opponent's super), and its action, frame and the ticks spent on the frame haven't changed for 1920 ticks (10 seconds) |
| `effects` | error | the effects' ring outside its 640 slots |
| `speed` | warn | not 1 to 3 ticks a frame |

None of them fires on the compatibility test's 254 fights (1.2 million ticks). They read
the state and change nothing; they run under the harness too, so the logs of
`tools/compat.py check`'s runs have them.

## Fight records

A fight is one visit of the fight scene: from its first tick to leaving it, all its
rounds. Each is `fight-NNN.jsonl` in the session folder, one JSON object a line, about 340
bytes a tick. The fight runs three ticks a frame (`CScene3::m_speed`), 192 a second, so a
record grows by about 4 MB a minute of fighting:

```
{"type":"fight","format":"efz-fight","version":1,"session":"...","fight":1,"mode":3,"mode_name":"vs cpu",...}
{"type":"tick","t":0,"f":0,"rng":216758024,"in":[0,0],"g":[1,99,0],"p":[[0,0,240,0,0,0,1,9999,0,0,0.3,0,0,0,0,99,0,0],[...]],"h":"a2ec6e85..."}
{"type":"event","t":777,"f":259,"event":"round_start","round":1}
{"type":"keys","f":299,"down":[66]}
...
{"type":"end","t":4002,"f":1393,"reason":"match_end","winner":0,"rounds_won":[2,1],"hp":[3120,-412],"anomalies":{}}
```

None are made during a network match ([netplay.md](netplay.md)): its rollback runs frames
again, which a record can't follow, and the match keeps a replay of its own.

**The header** (`"type":"fight"`): the session and the fight's number, the build, the
game mode (`mode`: 0 arcade, 1 practice, 3 vs cpu, 4 vs human, 5 replay, 6 demo) and
`replay_mode` (1 playing a replay, with `replay_copy` and `replay_offset`; 2 recording
one), the stage, the round and rounds to win, the CPU level, each player's character
number and name, palette, whether the CPU plays it and its skill; `rng`, `rand()`'s
state, and `fkey_held`, at the first tick; `state`, the state file, and `state_hashes`,
its blocks' hashes; and the names of the tick lines' fields.

**A tick** (`"type":"tick"`), after the tick:

| Key | |
|---|---|
| `t` | the tick, from 0 |
| `f` | the frame of the fight it ran in (a frame runs three ticks; fewer in the fade after a match's last KO and in some of Shiori's moves; none while paused) |
| `rng` | `rand()`'s state as the tick began |
| `in` | each player's input this tick, as a replay's input word: bits 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D. For a human the directions and buttons held, as `CPlayer::ReadInput` read them (from the controls or the replay); for the CPU what it chose, the buttons it pressed |
| `g` | `game_fields`: the round, `m_intro` (nonzero: the round's opening; input is ignored) and whether the round is over (a KO) |
| `p` | each player's `player_fields`: action and frame, x, y, vx, vy (doubles, exactly: they read back as the same bits), facing, HP (9999 full), power gauge (0-3000), guard gauge (0-360), RF gauge (0-1000), the current combo's hits and damage, hitstop, freeze (the opponent's super flash), the command recognized (0x63 none), rounds won, objects active |
| `h` | the FNV-1a hash of each block of the state, 9 × 8 hex digits in `blocks` order: the compatibility test's (`p1 p1obj p1char p2 p2obj p2char scene game fx`, [compat.md](compat.md)), so a record's hashes compare with the test's logs |

**Events**: `event` lines for `round_start`, `round_end` (the round's winner, -1 for a
draw, rounds won and HP), `match_end` (the winner), `pause` and `resume`; `keys` for the
keys the fight scene reads itself changing (Esc, F1-F12 as DIK codes: F4 and F5 refill
the gauges in practice, F6 restarts a replay's recording or changes the dummy's stance,
F7 its guard, F8 pauses); `pad` for the controls read outside a tick (the demo's "press
a button"); `anomaly` for the checks. **The end**: why (`match_end`, `escape`,
`replay_end`, `left`, `exit` when the game quit, `crash`), the winner, rounds won, HP and
the anomalies' counts.

**The state file** (`fight-NNN.state`) has the game's state at the first tick, before any
input is read: the blocks the hashes are of, pointers zeroed, each as the harness's
`EFZ_TRACE_DUMP` writes them (`[tick, block, size]` as 32-bit little-endian, then the
bytes), so `tools/compat.py`'s tools read it.

## Replaying a fight

```sh
efz --data "$EFZ_DIR" --replay-fight logs/20261103-182001-4f2a/fight-003.jsonl          # watch it
efz --data "$EFZ_DIR" --replay-fight .../fight-003.jsonl --fast                         # check it
SDL_VIDEO_DRIVER=offscreen SDL_AUDIO_DRIVER=dummy efz --data ... --replay-fight ... --fast   # headless
```

The replay sets the recorded characters, stage and palettes up, as the harness does,
without the menus. At the first tick it loads the state file (the masked pointers keep
their own values), `rand()`'s state and `g_fkeyHeld`, the one global of the fight's
outside the state; it gives the game the record's copy of a replay file the fight was
playing, or a scratch file for one it was recording. Then on each tick it gives each
human player the recorded input, gives the fight scene's own keyboard reads the recorded
F-keys frame by frame, and lets the CPU decide again: the CPU's decisions follow from the
state and `rand()`. After each tick it compares the state's hashes, `rand()`, the frame
and both inputs with the record's.

It quits at the record's last tick. Exit code 0: every tick as recorded; 3: a difference
(the log names the first tick and what differs, and writes the replay's state there to
`desync-tTTTTTT.state`, to compare with `tools/compat.py`'s tools); 4: it couldn't replay
(no such file, another character set, a state of another layout). The replay writes no
file of the player's: its game saves to `scratch` in its own session folder. It records
the fight again, with `replay_of` in the header, so the two records compare
(`tools/efzlog.py diff`).

All 254 fights of the compatibility suite were recorded and replayed this way (CPU
against CPU, CPU against scripted input, replays played back), and fights with F4, F5, F6
and F8 pressed mid-fight; each replayed exactly, every tick. A record with one input
changed replays as recorded up to that tick, and the replay reports that tick. A replay also checks a change to the game: a build that plays the
fight differently fails it at the first tick that differs, as `tools/compat.py` would.

What a record doesn't replay: the menus (only the fight is recorded); a fight whose
replay copy is missing; and a build whose state blocks have another layout (the layout
is the original's, `port/layout.cpp`, so records move between Windows, Linux and macOS).

## Data for training

The records are the game's whole fight in a form a learner can read: per tick, the
inputs (the actions) and the players' status (the observations), events for rewards
(rounds, KOs, damage from the HP), and the state's hashes. With the state file and the
replay, any tick can be reproduced to read more of the state than the record has.

```python
import sys; sys.path.insert(0, 'tools')
from efzlog import read_fight, ticks_table, iter_fights, decode_input

for path in iter_fights('/path/to/save/logs'):
    fight = read_fight(path)
    cols = ticks_table(fight)           # {'t': [...], 'in_p1': [...], 'p1_hp': [...], ...}
    actions = [decode_input(b) for b in cols['in_p1']]
```

```sh
tools/efzlog.py sessions ~/EFZ/logs          # every session: status, fights, anomalies
tools/efzlog.py show 20261103-182001-4f2a    # one: warnings, errors, crash, fights
tools/efzlog.py fight .../fight-003.jsonl    # its events and anomalies
tools/efzlog.py export .../fight-003.jsonl fight-003.npz   # a column per field, a row per tick
tools/efzlog.py diff a.jsonl b.jsonl         # where two records of a fight part
```

To collect fights without a person at the controls, run the harness's CPU or scripted
fights with records on and keep every session:

```sh
SDL_VIDEO_DRIVER=offscreen SDL_AUDIO_DRIVER=dummy EFZ_TRACE=/dev/null EFZ_TRACE_FAST=1 \
EFZ_TRACE_RECORD=1-1:1:10:1:0:1:7:1:1 EFZ_TRACE_TICKS=6000 \
  efz --data "$EFZ_DIR" --save /tmp/game --record --log-dir data/logs --log-keep 0 --log-max-mb 0
```

(`EFZ_TRACE_RECORD`'s fields are in `src/trace.cpp`: slot, characters, stage, palettes,
seed, then 1 for each side the CPU plays.)

## What it costs

Each tick hashes the state's blocks (about 200 KB) and writes a line; the checks read a
few hundred bytes. Next to the game's tick that is little: on a Ryzen 7 6800U, 10 at a
time, the compatibility suite took 4:23 with records and 4:57 without (its time is
mostly loading; the difference is noise). Its 254 records, 1.2 million ticks, take 412
MB. The session folders kept are the newest 20, and at most 2 GB of them, unless
`--log-keep` and `--log-max-mb` say otherwise.

## How it hooks into the game

The recorder needs three points in a tick, which `src/trace.cpp`, the compatibility test's
harness, provides: `TraceTickStart` before the players read their input,
`TraceInputsRead` once they have (`CScene3::Update`), and `TraceTick` after the tick.
`g_traceHooks` connects them to `port/record.cpp`; in `make trace`'s build of the original
nothing is connected. `TraceSaveState` and `TraceLoadState` gather the same blocks the
hashes are of and hand them out, or put saved bytes back with the pointers left as they
are. The input layer (`port/input.cpp`) passes the keyboard the game reads through the
recorder, which records or replaces the keys the fight scene reads, and tells it what
`GetInput` returned.

The checks and the records read the game's state and change nothing: the compatibility
suite's logs are the same, byte for byte, with records on and off.

The headless library ([headless.md](headless.md)) compiles the same harness without
the recorder: it writes no session folder, record or crash report (a library leaves
those to the program that loads it), and the log lines of the parts every build shares
(`arena.cpp`, `win32.cpp`) go to stderr there, warnings and worse. Its save states are
the whole arena, quick to take but only for the process that took them; a record's state
file is the hashed blocks with the pointers left out, which load in any build on any
system.
