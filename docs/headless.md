# The headless game, for training agents

The recovered sources also build without a window, sound or keyboard, many games to a
process, stepped in parallel on every core: `efz_env`, a library with a C API
(`port/headless/efz_env.h`) and a Python package over it (`python/efz_env`). It is
the same game as the original's, tick for tick, only run as fast as the CPU allows.
What it is for: reinforcement learning (self-play, or an agent against the game's own
CPU), search over save states, and any other program that plays the game.

```python
from efz_env import EfzVecEnv, ActionTable

env = EfzVecEnv('/path/to/EFZ', num_envs=256, max_frames=64 * 120)
env.set_matches(chars=('ayu', None), char_pool=['mai', 'akane'], cpu=(False, True))
table = ActionTable()                       # 45 discrete actions
obs = env.reset()                           # (256, 2, 168): each player's view
obs, reward, terminated, truncated, info = env.step(table.to_bytes(indices))
```

## Building

```sh
cmake -B build/headless -DEFZ_GAME=OFF      # no SDL3 needed
cmake --build build/headless --config Release
build/headless/efz-bench --data "$EFZ_DIR"  # build/headless/Release/... with Visual Studio
pip install -e python                       # or put python/ on PYTHONPATH
```

`EFZ_GAME=OFF` skips the game and SDL3; the default builds both. The targets:

| Target | What |
|---|---|
| `efz_env` | The library (`efz_env.dll`, `libefz_env.so`, `libefz_env.dylib`) |
| `efz-headless` | The game on the headless platform, as the SDL3 game runs it, for the compatibility test |
| `efz-bench` | Speed, and a check that the library runs the same game every time (`--check`) |

The Python package finds the library at `$EFZ_ENV_LIBRARY`, next to the package, or in
the checkout's `build/*/` folders. It needs numpy; `efz_env.gym` needs gymnasium.

Without drawing, the library needs only what the game's state depends on: a
compatibility pack (`tools/compatpack.py`, [compat.md](compat.md)) does as `data_dir`,
about 1 MB to copy to each training machine instead of the install. **Measured:** the
same observations and rewards from the pack as from the install (8 environments, 800
steps). Drawn frames from a pack are flat colours: draw with the install.

## The same game

The headless platform (`port/headless/platform.cpp`) stands in for SDL3's
(`port/main.cpp`, `video.cpp`, `input.cpp`, `sound.cpp`) and changes nothing the game
does:

- **Pictures.** By default nothing is drawn: sprites keep their sizes and the first
  pixel (the colour key, which the game reads into its state) but aren't decoded, the
  blend tables aren't built and the blitters return at once. The game still calls
  everything it called; nothing it computes reads a picture. `drawing=True` draws the
  frames as the SDL3 game does, for `render()`.
- **The clock.** `timeGetTime` advances 16 ms each time it is read, so the waits of
  the fades end at once and every run is the same. Only the frames-per-second count on
  screen reads it otherwise.
- **The controls.** `CInput::GetInput` returns the program's byte for each player; the
  keyboard is never pressed.
- **Sound.** The 150 sound slots are taken and released as on SDL3, from the `.wav`
  headers, so the sound IDs the game keeps are the same; nothing is loaded or played.

**Measured** (3 November 2026, Windows 11, MSVC 17.14): `efz-headless` plays 40 cases of
the compatibility suite ([compat.md](compat.md): CPU fights, the harness's scripted
input, and replays) into logs identical byte for byte to the SDL3 game's, built from
the commit before this one, with and without `--draw` (5 of the cases drawn). The
whole game state is hashed after every tick, so that is every byte of it. On 4 November
the whole suite, with `--hop 97` (below): the same logs in all 254 cases.

**From now on the compatibility suite checks it on every run** ([compat.md](compat.md)):
`tools/compat.py check` plays each case in the SDL3 game and in `efz-headless`, and
each log must be the reference's and the two the same. `efz-headless` runs with
`--hop 97`: every 97 frames its game is copied into another arena and goes on on a new
thread, as the library's restarts (copies of saved games) and its workers (any thread
takes any game) do, so the check covers what training relies on and not only the
platform. What needs no game data runs in CI on every platform: `ctest -L headless`
(`tests/headless_test.cpp`: arena copies give the same heap; arenas on different
threads stay apart; a sprite loaded without drawing takes the same bytes and keeps the
same colour key as one decoded whole, on 4,000 random images; the API's structures)
and `python/tests` (the Python package against the library).

```sh
tools/compat.py check                     # both, every case
tools/compat.py check --mode headless     # the headless runner only
ctest --test-dir build/native -L headless # without the game's data
```

**Found on the way, and fixed** (4 November 2026): the SDL3 game built with MSVC gave
the reference's log in only 146 of the 254 cases, the same in `efz-headless`. Not
`key.ini`: GCC builds give it in all 254 with the same one. Visual C++ 2022 draws the
two `rand()`s of one expression in `src/effect.cpp` in the other order from the
original's compiler (and GCC), which C++ allows ([native.md](native.md), "Evaluation
order"); with the draws in statements of their own, both MSVC builds give the
reference's log in all 254.

## How it runs many games at once

- **An arena per game.** Everything a game allocates lives in its arena (port/guest.h),
  and pointers inside the game are offsets into it. A build with `EFZ_MULTI_INSTANCE`
  makes the arena's base (and the stack window) thread-local: a thread runs a game by
  binding its arena. The rest of a game's state outside its objects (`rand`'s seed, the
  clock, the controls, what `WinMain` kept in globals) is in the arena's first 64 KB
  (`Globals`), and so is the allocator's, with offsets for links. So the bytes of an
  arena up to its highest block are the whole game: copying them into another arena
  makes it the same game. Outside a game (no arena bound), `operator new` takes from the
  C library's heap.
- **Matches start from copies.** The first time a match (characters, stage, palettes,
  CPU sides) is asked for, a game is set up as the menus would (VS on the replay menu's
  footing: mode 5, nothing recorded, no records written), played through the loading
  (scene 2) and the intro, and saved; it is 5.5 MB (61 MB drawing). Starting that match
  again is copying it back. A batch keeps `cache_size` such matches (least recently used
  dropped). After the copy each match gets a `rand` seed of its own, so the CPU and the
  effects differ from match to match.
- **One pool of threads.** Each step is a job of one item per environment on a pool
  shared by every batch of the process; the calling thread helps. Its workers spin
  briefly between jobs, so steps coming back to back find them awake.

The game's sources are compiled twice in a build: once for the SDL3 game and once
for the library, which needs `EFZ_MULTI_INSTANCE`. The SDL3 game is unchanged by it
(its arena base stays a plain global).

## Speed

Measured on an AMD Ryzen 7 6800U laptop (8 cores, 16 threads), Windows 11, MSVC,
random controls, Ayu against Ayu unless said otherwise. A frame is what the game runs
64 times a second: three ticks of the simulation. The laptop's clock boost moves the
same build's numbers by up to a third from run to run: the ranges are what repeated
runs gave.

| What | Frames a second | Times real time |
|---|---|---|
| 1 thread, 1 environment | 24,000-49,000 | 380-770 |
| 16 threads, 64 environments | 200,000-280,000 | 3,100-4,400 |
| 16 threads, 256 environments | 190,000-300,000 | 3,000-4,700 |
| 16 threads, 64 environments, random characters and stages | 236,000 | 3,700 |
| 16 threads, 16 environments, drawn | 43,000 | 670 |
| From Python, 256 environments, random controls (`examples/bench.py --policy none`) | 265,000 | 4,100 |

Resetting 64 environments to matches already loaded takes 10 ms; loading a match the
first time takes 20-30 ms (on one thread; files in the OS's cache). With random
characters and stages most matches are new: a larger `cache_size`, or fewer stages
(`stage_pool`), keeps that down. Per environment the library commits about 8 MB, plus
5.5 MB per cached match.

## The GPU

The simulation runs on the CPU: 250,000 lines of branching integer and double C++
(virtual calls into 24 characters' state machines, pointer chasing through pattern
tables, the x87's arithmetic emulated exactly) are what GPUs do worst, and a port to
one would be a rewrite that could no longer be checked against the original tick for
tick. What the library does for a GPU is keep it fed:

- **Page-locked observations.** `env.pin_memory(torch)` has the library write each
  step's observations straight into pinned tensors, so `obs.to('cuda',
  non_blocking=True)` is a DMA that overlaps what comes next. (`set_obs_buffers` takes
  any memory of the program's.)
- **Stepping while the network runs.** `step_async` starts a step on the worker
  threads and returns; `step_wait` finishes it. With two batches double-buffered, one
  steps while the policy runs on the other's observations:

  ```python
  a.step_async(act(a.obs))
  while training:
      actions_b = policy(b.obs)   # on the GPU, while A steps
      a.step_wait()
      b.step_async(actions_b)
      actions_a = policy(a.obs)   # while B steps
      b.step_wait()
      a.step_async(actions_a)
  ```

  Measured with a stand-in policy that takes the CPU's attention for 1 ms per 256
  environments' observations (`examples/bench.py --policy sleep:1`): 142,000 frames a
  second stepping and then running the policy, 230,000 double-buffered, the
  simulation's time entirely hidden.

## The API

`port/headless/efz_env.h` is the C API, `python/efz_env/vec.py` the Python class over
it; both are documented where they are declared. In short:

| | |
|---|---|
| A batch | `num_envs` matches, each two players, a stage, best of `rounds_to_win` rounds |
| A step | `frame_skip` frames with each player's control byte held. With `skip_noninteractive` (default) the step runs on through frames where the controls do nothing: the intros and the time after a KO |
| A side | the program's, or the game's CPU (`cpu=(False, True)`, at `cpu_level` 1-4) |
| Controls | one byte per player: `0x01` right (forward with `relative_actions`, the default), `0x02` left (back), `0x04` down, `0x08` up, `0x10`-`0x80` A-D. A button counts when it goes down: hold it across steps and it is one press. `ActionTable` maps discrete actions (default 9 directions × none/A/B/C/D) to bytes |
| Rewards | per player: `reward_damage` per full HP bar dealt minus taken (default 1), `reward_round` per round won minus lost (0), `reward_match` for winning the match minus for losing (1). Zero-sum |
| Ends | `terminated` when a player wins the match, `truncated` at `max_frames`. The environment starts its next match in the same step: `obs` is the new match's, `final_obs` the last of the old one, and `info` describes the old one (`ended`, `winner`, `episode_return`...) |
| Matches | `set_matches(chars, stage, cpu, palettes, char_pool, stage_pool)`: fixed, or drawn for each match from pools (default every playable character, 0-21 and 23, and every stage) |
| Save states | `save_state(i)` and `load_state(i, state)`: the whole game, a few MB. A state loads into any environment of any batch of the same process (the game's objects hold the addresses of their C++ classes' tables) |
| Pictures | `drawing=True`, then `render(i)`: the last frame, 320×240 RGB |
| Gymnasium | `efz_env.gym.EfzVsCpu`: the vector API for one agent (player 1) against the CPU, discrete actions |

### Observations

Each player's view, 168 floats: 8 about the match, 32 about the viewer, 32 about the
opponent, then the 8 objects (projectiles and the like) of each that are nearest the
viewer, 6 floats each. `env.observation_names` names them (`self_hp`, `opp_x`,
`opp_obj0_vx`...).

| Block | Features |
|---|---|
| Match | frames into the match / `max_frames` (or / 10000), round, intro running, a KO waiting for the next round, the opponent's x and y relative to the viewer's, the viewer's side, rounds to win |
| Each player | HP / 9999, power gauge / 3000, RF gauge / 1000, RF gauge blue, guard gauge / 360, x ((x − 320) / 320), y / 240 (negative in the air), velocity / 20, facing, the action (pattern) number and its frame, in hitstun, guarding, dashing, hitstop, a super's freeze, invulnerable, unable to guard, armor, throw-protected, air-recovery wait, combo hits, proration, rounds won, air actions used, character number, the action is a move of the character's own, played by the CPU, Akiko's seal, the combo's damage, airborne |
| Each object | active, x relative to the viewer, y, velocity, can still hit |

The action and character numbers are categorical, as numbers: a network does better
with an embedding of them than with the numbers themselves.

## Limits

- One data folder per process (`SetDataDir` is the process's).
- Save states hold the addresses of the game's C++ class tables: they load only into
  the process that saved them.
- No logs, crash reports or fight records: those are the SDL3 game's
  ([logging.md](logging.md)); the game's own errors go to stderr. A fight record's state
  file, unlike a save state, holds no addresses and loads in any process, build or
  system (`TraceLoadState`), but efz_env doesn't load one yet.
- Each environment reserves 2 GB of address space (committing what it uses); 64-bit
  address spaces have room for tens of thousands.
- Linux and macOS: the library builds there in CI (`.github/workflows/native.yml`), and
  keeps its `operator new` to itself (a version script on Linux, an export list on
  macOS); its speed and the compatibility suite have been measured on Windows only.
