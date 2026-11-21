# efz

**Eternal Fighter ZERO 4.02**, recovered as source and carried on: a native 64-bit game
for Windows, macOS and Linux that plays the original's game tick for tick, with
EfzRevival's rollback netplay built in, and agents trained to play it, which play inside
the game.

It began as a matching decompilation of `efz.exe` (Twilight Frontier, 2005) and of
EfzRevival 1.02h, the community's add-on for netplay and practice. That part is done:
the tag `compat-reference` builds a byte-identical `efz.exe` with the original's
compiler, Visual C++ .NET 2003 ([docs/decomp.md](docs/decomp.md)). Since 31 October
2026 the source is free to change, and what holds it to the original is the game, not
the bytes: the compatibility suite plays 254 fights in every build and compares the
whole game state with the original's after every tick.

- **The native game** ([docs/native.md](docs/native.md)). The same sources on SDL3
  instead of Win32, DirectDraw, DirectInput and DirectSound, without wine. It keeps the
  original's memory layout and floating point, so it computes the same game on every
  machine. Every run keeps a log, crash reports and a record of every fight, which plays
  back from the REPLAY menu, converts to and from the game's `.rep` and to video
  ([docs/logging.md](docs/logging.md)).
- **Netplay** ([docs/netplay.md](docs/netplay.md)). NET PLAY on the title hosts or joins
  a match over the network, with rollback. It is EfzRevival 1.02h's own protocol and
  rules, recovered from its binaries and made native: no launcher, no injected DLL.
- **Agents in the game** ([docs/agents.md](docs/agents.md)). A trained agent, one
  `.efzagent` file, plays a side of VS HUMAN or this computer's side of a network match.
  The game runs it on its own, no Python needed: its network, and its combos, okizeme and
  pressure planned on copies of the fight.
- **The headless game** ([docs/headless.md](docs/headless.md)). `efz_env`, a library
  (C API, and a Python package) that runs batches of matches without a window or sound
  on every core, thousands of times real time, with save states, the game's CPU as an
  opponent and rewards. The same game: the compatibility suite runs in it too.
- **Training** ([runs/human-ayu/](runs/human-ayu/README.md),
  [docs/training-v2.md](docs/training-v2.md)). Agents that start as clones of people
  from the community's replays, then train on against a league of opponents trained to
  beat them, with scripted habits on top. The goal is an agent that beats the best
  players within a person's limits: it sees the game a reaction time late, presses at
  people's speed and doesn't confirm a hit instantly.

## Game files

This repository contains no original game files: no executables, sprites, sounds or music.
EFZ's readme prohibits redistributing its data and decompiling it. Everything here works
against a legitimately obtained EFZ 4.02 install, which `--data` or `EFZ_DIR` points at.

One file is made from the game's data: `tests/compat/pack.tar.gz.enc`, encrypted. It
holds what the compatibility test reads (the frame data, palettes and the pictures'
sizes; no pictures or sounds), so that CI can run the test, and the repository holds no
key to it: CI gets that from a secret ([docs/compat.md](docs/compat.md), "In CI").

## Playing

One command builds the game from this checkout, as far as anything changed, and starts
it:

```sh
tools/run.sh --data /path/to/EFZ           # Linux, macOS
tools\run.cmd --data C:\path\to\EFZ        # Windows
```

It needs CMake 3.16 or later and a C++17 compiler: on Windows, Visual Studio 2019 or
later (its Build Tools are enough, and bring CMake) or MinGW-w64; on macOS, the Xcode
command line tools and CMake; on Linux, also the development files of X11 and of ALSA
or PulseAudio, which SDL3 builds its back ends from. A Linux machine without them builds
in docker instead, if it has docker. The script says what is missing and how to install
it. The first build downloads SDL3 and takes a few minutes; `--build-only` only builds.

The game reads its data from `--data` (a folder with an EFZ 4.02 install, or
`EFZ_DIR`) and writes `key.ini`, records, replays and screenshots to `--save` (default:
the data folder, or the user's preferences folder if that is read-only). Alt+Enter
toggles full screen (`--fullscreen` starts in it); controllers work as DirectInput
joysticks did and can be plugged in at any time.

Other ways to build it:

```sh
cmake -B build/native && cmake --build build/native   # any of the three systems
tools/native.sh                    # build/native/efz for Linux, in docker; runs the tests
tools/native.sh windows            # build/windows/efz.exe for 64-bit Windows, from Linux
```

### Fight records

Each run keeps a log folder (`logs/` in the save folder): `efz.log`, a report with a
stack trace when it crashes or hangs, checks of the game's state on every tick of a
fight, and a record of every fight, which replays it tick for tick (in the game, from the
REPLAY menu's RECORDS page) and is data to learn from
([docs/logging.md](docs/logging.md)):

```sh
efz --data DIR --replay-fight logs/<session>/fight-003.jsonl --fast   # replay a fight, check every tick
efz --data DIR --record-to-rep logs/<session>/fight-*.jsonl --out reps  # records to the game's .rep
efz --data DIR --rep-to-record replay/data1-1.rep                     # a .rep to a record
efz --data DIR --export-mp4 logs/<session>/fight-003.jsonl            # a video of a fight
efz-convert                                                           # the same, in a window
tools/efzlog.py show logs/<session>  # what happened: warnings, errors, crash, fights
tools/efzlog.py export logs/<session>/fight-003.jsonl fight.npz       # a row a tick
```

### Netplay

NET PLAY, on the title menu after VS HUMAN: one side hosts, the other joins its address,
and both play from character select on, with rollback.

```sh
efz --data DIR --host                       # or from the command line: host on UDP 10800
efz --data DIR --join 192.168.1.5          # join it
```

Two native games are checked against each other frame by frame. Against `efz.exe` with
EfzRevival 1.02h, which it is built to play, it hasn't been tried yet
([docs/netplay.md](docs/netplay.md), "Against EfzRevival 1.02h").

### Playing against an agent

Put an `.efzagent` file in the game's `agents` folder. On VS HUMAN's character select,
F5 has it play P1 and F6 P2 (pressed again, the next agent; Shift+F5 and Shift+F6 go
back); it picks its own character and you pick the stage. On NET PLAY, PLAYED BY has it
play your side of a network match. `--agent-p1 FILE` and `--agent-p2 FILE` do the same
from the command line. An agent file is made from a trained model or a pack:

```sh
python python/examples/export_agent.py PACK.zip     # the model, its routes, its chooser: one file
python python/examples/export_agent.py --show FILE.efzagent
python python/examples/unpack_agent.py FILE.efzagent  # back to a model, to train it further
```

[docs/agents.md](docs/agents.md) has what goes in the file, how the game plays it, and
what keeps an agent's side of a network match compatible.

## Training agents

The headless game is for reinforcement learning and other programs that play: many
matches to a process, stepped in parallel in C++ and handed to Python as numpy arrays
(or straight into pinned memory for a GPU).

```sh
cmake -B build/headless -DEFZ_GAME=OFF && cmake --build build/headless --config Release
build/headless/efz-bench --data "$EFZ_DIR"          # speed; --check: determinism
pip install -e "python[all]"
```

```python
from efz_env import EfzVecEnv, ActionTable
env = EfzVecEnv(efz_dir, num_envs=256)              # both sides yours: self-play
env.set_matches(cpu=(False, True))                  # or player 2 the game's CPU
obs = env.reset()                                   # (256, 2, 168)
obs, reward, terminated, truncated, info = env.step(ActionTable().to_bytes(actions))
```

There are adapters for Gymnasium (`efz/VsCpu-v0`), Stable-Baselines3 and PettingZoo, a
PPO training script, and a window to play an agent yourself, which records every match:

```sh
python python/examples/train.py --data "$EFZ_DIR" --opponent self --steps 2e6 --out runs/self
python python/examples/play.py --data "$EFZ_DIR" --agent runs/self/model.zip
```

So far the agent plays Ayu, other characters only as its opponents
([runs/](runs/README.md)). The current line,
[runs/human-ayu/](runs/human-ayu/README.md), starts from a clone of people (1,908 of
the community's in-sync Ayu matches) and is trained in rounds: a league of exploiters of
each character trained against it, scripted habits on top of them, its combos from
people's routes planned on copies of the fight. Each round is judged by a benchmark
suite of drills with error bars, beside the strongest Ayu player of the replays, and by
people's games against it in the native game. [docs/training-v2.md](docs/training-v2.md) is the
plan and the record of every round; [docs/training.md](docs/training.md) the research
before it (the training frameworks, how other fighting games' AIs and EFZ's own CPU are
built). The models are on Hugging Face (https://huggingface.co/sakuya9t/efz):
`python runs/hub.py download` fetches them into `runs/`.

## Checking a change

Every change has to play the original's game. `tools/compat.py` plays the suite
(`tests/compat/`: 204 replays, and 50 fights of the game's CPU against itself and
against scripted input; 1.2 million ticks) in the native game and headless, and
compares the whole game state, hashed after every tick, with the reference's: the
original source at `compat-reference`, built with the test's harness and run under wine
([docs/compat.md](docs/compat.md)).

```sh
tools/compat.py check               # the 254 cases in the native game and headless (about 4 minutes)
tools/compat.py explain cpu-03      # where a failing case parts from the original, by member
tools/compat.py coverage            # which lines of src/ the suite runs
```

CI builds the game on Linux (x64, arm64), Windows and macOS (arm64, x64), runs the tests
that need no game data, and runs the suite from the encrypted compatibility pack.

## The repository

| Path | What it is |
|---|---|
| `src/` | The game, recovered: `CPlayer` and the 24 character classes, effects, the scenes, the loaders; Win32 and DirectX in four files of its own ([docs/decomp.md](docs/decomp.md) has a table of them) |
| `port/` | The native game's platform layer on SDL3, in place of those four files: 32-bit handles for the game's pointers, the original's floating point, the log, crash reports and fight records |
| `port/netplay/` | Netplay: EfzRevival 1.02h's launcher protocol and online session (rollback) in the game's process, its UDP messages, the NET PLAY screens |
| `port/agent/` | Agents in the game: their view of a fight (shared with `efz_env`), their network read from an agent file, their combos, okizeme and pressure planned on copies of the fight |
| `port/headless/` | The headless platform and the training library `efz_env` (`efz_env.h`), `efz-headless`, `efz-bench` |
| `python/` | The Python package over `efz_env`: `EfzVecEnv`, action tables, the framework adapters, agent files; examples to train, play, export and unpack |
| `runs/` | The trained agents and the scripts that made them: cloning, fine-tuning, leagues of exploiters, the planners, evaluation and the benchmark suite |
| `revival/` | EfzRevival 1.02h, recovered: the launcher, `EfzRevival.dll` and `DDRAW.dll` |
| `tests/` | The compatibility suite and the native game's own tests |
| `tools/` | Building and running the game, the compatibility test, the logs; the decompilation's tools |
| `toolchain/` | The original compilers in docker (Visual C++ .NET 2003, Visual C++ 2012), and the native build's image |
| `docs/` | Below |

## Documentation

| Document | |
|---|---|
| [native.md](docs/native.md) | The native game: building it, how it keeps the original's memory layout and floating point, known differences |
| [compat.md](docs/compat.md) | The compatibility suite: what it compares, the reference, the rules a change follows, the recorded and network layers |
| [logging.md](docs/logging.md) | Logs, crash reports and fight records: what is written, the formats, the tools |
| [netplay.md](docs/netplay.md) | Netplay: playing, the protocol and the session, Revival's rules, how it was checked |
| [agents.md](docs/agents.md) | Agents in the game: the agent file, how the game plays it, its planners, over the network |
| [headless.md](docs/headless.md) | `efz_env`: observations, actions, rewards, save states, speed, the GPU, the API |
| [training.md](docs/training.md) | Research before training: the frameworks, Hisoutensoku's AIs, EFZ's CPU, human-like agents |
| [training-v2.md](docs/training-v2.md) | The training plan since 11 November 2026 and the record of every round |
| [progress.md](docs/progress.md) | Where the agent work stood on 7 November 2026, what lives outside the repository |
| [decomp.md](docs/decomp.md) | The decompilation: rebuilding the original `efz.exe` and EfzRevival, the matching workflow and its tools |
| [readability.md](docs/readability.md), [naming/](docs/naming/README.md) | How the source got its names, and the research behind them: each character's moves and mechanics |
| [recon.md](docs/recon.md), [revival.md](docs/revival.md) | What the original binaries are: `efz.exe`, and EfzRevival 1.02h |
| [third-party.md](docs/third-party.md) | The libraries the native game links, and their licences |

## Roadmap

1. **The source.** *Done:* `efz.exe` byte for byte (`v1.0.0`), EfzRevival 1.02h
   (`v2.0.0`), names for nearly everything, the compatibility suite in place of the
   bytes (`compat-reference`).
2. **The native game** on Windows, macOS and Linux, 64-bit, on SDL3. *Done*, checked
   against the original by the suite in CI.
3. **Revival's features, native.** *Begun:* rollback netplay is built in; native against
   native is checked frame by frame. Still to do: a match against `efz.exe` with
   EfzRevival 1.02h over the network (the network layer of
   [docs/compat.md](docs/compat.md)), spectating, and the training tools (frame step,
   save states, hit and hurt boxes).
4. **Agents.** *Done:* the headless library, and agents that play in the game, offline
   and over the network. *Under way:* an Ayu that beats the best players within a
   person's limits; then other characters.
5. **The game itself:** widescreen and HD output, in-game input binding, mod support for
   characters, stages and palettes; the simulation hosted as a UE5 C++ module, drawn
   with new assets.
