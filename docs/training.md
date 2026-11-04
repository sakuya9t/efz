# Training agents: the frameworks, other games' AIs, and what follows

Research of 3 November 2026, before any training: how far `efz_env`
([headless.md](headless.md)) is from the mainstream reinforcement-learning frameworks;
how the AIs of Touhou 12.3 Hisoutensoku (東方非想天則, "th123", Tasogare Frontier's
other fighting game) are built; how EFZ's own CPU plays; what to take from all three;
and a design, under discussion, for agents that play like people, with ideas from
Street Fighter and other fighting games.

In short:

- The frameworks need thin adapters (50-100 lines each), and `efz_env` had four gaps
  (its only autoreset was one RLlib's runner and Gymnasium's wrappers don't expect).
  Both are done: the gaps are closed and the adapters are in `python/efz_env`.
- Every Hisoutensoku AI that plays well is hand-written rules. The learning attempts
  (2021-2026) were held back by slow environments, and none beats a person.
- EFZ's CPU is hand-written rules too. At level 4 it blocks every attack it is able to
  block, so it is a poor yardstick of strength.

## The frameworks

Tested on Windows 11 (Ryzen 7 6800U, no CUDA) with Python 3.12 in a scratch
environment, against the `efz_env` of commit 30daf00. The adapters were throwaway
scripts; none is in the repository.

| Framework (version) | Result | Effort |
|---|---|---|
| Gymnasium 1.4.0 | `gym.register(..., vector_entry_point=...)` and `gym.make_vec(..., vectorization_mode="vector_entry_point")` return `EfzVsCpu` itself. `check_env` passes on a one-environment adapter. Its vector `NormalizeObservation` refuses `EfzVsCpu` ("Expected autoreset_mode to be NEXT_STEP or DISABLED"), and `RecordEpisodeStatistics` raises on the `episode` info key | Small |
| Stable-Baselines3 2.9.2 | A `VecEnv` over `EfzVecEnv` (~70 lines, mapping onto `step_async`/`step_wait`) trained PPO against the CPU (1,600 agent-steps a second including training) and in self-play with both players as agents of one policy (7,200 a second). CPU torch was the bottleneck, not the game | Small |
| TorchRL 0.14.1 | `GymWrapper(EfzVsCpu(...))` fails: it reads the vector env's `autoreset_mode` attribute. With that attribute, `check_env_specs` passes and the observation at a match's end is its last, not the next match's first | Small |
| PettingZoo 1.27.0 | A `ParallelEnv` over a one-match batch passes `parallel_api_test` and `parallel_seed_test`. PettingZoo has no batched form, so this gives up the batch | Small |
| RLlib 2.60.0 (on Windows) | Single-agent PPO runs on the batch with `gym_env_vectorize_mode="vector_entry_point"`. `SingleAgentEnvRunner` assumes next-step autoreset (an episode with no data takes the step's observation as its reset and drops that step), so with same-step autoreset it would take the next match's first view for the last one's end. Its `episode_len_mean` reads 302 for 300-step matches in either mode: RLlib's own count, not a sign of that (an earlier version of this page took it for one). Multi-agent self-play works with one `MultiAgentEnv` per match; `num_envs_per_env_runner` > 1 goes through RLlib's own `SyncVectorMultiAgentEnv` (next-step only), so not through our batch | Medium |
| Minari 0.5.4 | `DataCollector` over the one-environment adapter wrote a dataset (it needs `minari[create]`, which installs JAX) | Small |

Read, not run:

| Framework | What it would take |
|---|---|
| CleanRL | Pinned to gymnasium 0.29.1: its scripts are copied and edited (the env's creation, the episode statistics), ~10 lines |
| Tianshou 2.0 | Its collectors reset finished environments themselves: needs autoreset off |
| skrl 2.1, SheepRL 1.0 | Gymnasium vector environments, so the Gymnasium fixes cover them |
| PufferLib | 3.0.0 (the PyPI release) refuses to install on Windows ("Unsupported system: Windows"). The 5.0 branch on GitHub has environments in C inside its own tree (`ocean/<env>/<env>.h`, `puf_init`/`puf_step`) and trains on NVIDIA GPUs only. Its design (in-place buffers, a match's two players as two agents) is the closest to ours: worth it on Linux with an NVIDIA GPU |
| EnvPool 1.2.7 | Maintained again in 2026, but a new environment means forking it and building it with Bazel (C++ `Env` with `Reset`/`Step`, per-match stepping we don't export). It would duplicate `efz_env` |
| Sample Factory 2.1.1, DIAMBRA Arena 2.2.7 | No release since 2023 and 2024. DIAMBRA can't take new games; its conventions (a move and an attack as two discrete actions, P1/P2 roles) are worth copying |
| stable-retro 1.0.1, FightLadder | Emulator cores; EFZ isn't one. FightLadder's league training and Elo/exploitability evaluation are built on SB3, so they would work through the SB3 adapter |
| Gymnax, Brax, PureJaxRL and the like | The environment must be written in JAX: not possible for this game |
| OpenSpiel 2.0 | A simultaneous-move game in Python, with save states for its game copies; its algorithms suit small games |

### Gaps in efz_env (closed)

Found on 3 November 2026 and closed the same day (efz_env version 2; the adapters are
in `python/efz_env`, [headless.md](headless.md), "Training frameworks"):

| Gap | What it broke | Now |
|---|---|---|
| Only same-step autoreset (a match that ends starts again within the step) | Gymnasium's vector observation and reward wrappers refuse it; RLlib's runner assumes next-step; TorchRL refuses next-step and prefers none; Tianshou resets ended environments itself | `EfzEnvConfig.autoreset`: same step, next step (`EfzVsCpu`'s default) or off. TorchRL runs `EfzVsCpu` with `'disabled'` or `'same_step'` |
| `reset(seed=...)` did nothing: the seed was read when the batch was made | The same seed and actions diverged at step 58; Gymnasium's seeding contract | `efz_env_seed(env, i, seed)`; `reset(seed=s)` seeds environment i with s + i. `check_env` passes |
| `EfzVsCpu`'s info key `episode` (a match counter) | Gymnasium's `RecordEpisodeStatistics`, SB3 and CleanRL use `episode` for return and length | `match_index` (none in the single environment, whose info must not depend on how many matches came before) |
| `EfzVsCpu` had no `autoreset_mode` attribute | TorchRL's `GymWrapper` | It has |

There is no standard for batched two-player games. The working convention (PufferLib's,
and the SB3 adapter's) treats a batch of N matches as 2N agents: one shared policy with
`relative_actions`, and a hook for frozen opponents when training against past
versions.

## Hisoutensoku's AIs

Eleven projects were read (code, not their claims), with the community wiki and the 34
AIs bundled in the 2026 repack of the AI tool.

### How they reach the game

| | External tool | Mod inside the game |
|---|---|---|
| Who | click3's `th123_ai` and its scripts; zhaiwuz5, dticpw, mozhu62's live play | PinkySmile's SokuAI training mod (on SokuLib/SWRSToys), which ldw079 uses |
| State | `ReadProcessMemory` from fixed addresses of version 1.10 (frame counter `0x008985D8`, scene `0x008A0044`), walking the game's object lists for bullets | The mod sends the state of both characters and their projectiles every frame over TCP |
| Controls | Fake key presses (`keybd_event`, `SendInput`); the game must have focus. Giuroll (the rollback mod) and Wine's DirectInput ignore synthetic keys | The mod hooks the game's input read (the call at `0x40A45D`) and writes the controls as frames held, as the game counts them |
| Timing | Real time, 60 frames a second, polling the frame counter | Lockstep: the game waits for each frame's controls |
| Speed | 1x | A speed setting: 436 frames a second per instance, rendering off; three instances on one PC gave ~1,300 |
| Save states | None | None: resets replay a match's start |

`efz_env` has neither problem: the game runs in the program, ~200,000 frames a second
across a laptop's cores, deterministic, with save states.

### The scripts: hand-written rules

`th123_ai` (click3, 2009-2013) runs Lua 5.1 scripts. `main()` and the threads made
with `create_thread` are coroutines that all advance one frame per `yield()`. Scripts
read globals refreshed each frame: positions, speeds, both players' move numbers
(`my_act`, `enemy_act`) and frames into them, HP, spirit, cards, combo state, weather,
objects, hit and hurt boxes. They press keys with `key_on`/`key_off`/`key_event` and
`command("236B")`. The tool has fairness settings (`set_key_delay`, `set_data_delay`):
1 of the 34 bundled AIs uses one.

The AIs are per-character if/elseif chains run every frame, on distance, the opponent's
move number and its frame, with `math.random` rolls. Community tables of move numbers
(the repository's `motion.txt`, `skill.txt`, `spell.txt`) are the keys. Two exceptions
learn: "アリス３" (2009) stores snapshots of the state before moves that hit or were
blocked, and replays the nearest stored one (nearest-neighbour imitation of whoever
trained it by playing against it); and a Suika AI measures each opposing move's reach
and active frames in the game and saves them for its guard.

**The super-reaction Reimu AI** (超反応霊夢AI; Chinese players' 「神AI」, "God AI", with
a "2012 version" and a "2018 version") is the best-known. The original is from
2010-09-12; しなうす modified it on 2011-10-01, 2012-11-03 and 2018-01-11. The 2018
version is about 8,200 lines of Lua (`reimu_main.ai`) and a 1,000-line library
(`def_clc.lua`):

- Rules on the opponent's move numbers for each of the 20 characters. For example, the
  generic low-attack reaction lists, per character, the moves that hit low; on the
  attack's first frame (`enemy_allframe==1`), on a 1-in-6 roll, it high-jumps.
- Combos as fixed timings: from Fantasy Seal at frame 142+ with the opponent in hit
  reaction 71, A, 10 frames, A, 12, A, 15, forward and B.
- "Caution" counters: after blocking it stays defensive for a random 2-25 frames; after
  blocking certain heavy attacks it may stop guarding to hit back.
- **Its strength is the stage.** On the Hakurei Shrine (or with Reimu's music against
  Remilia) `guard_rank` is 0: it blocks the right height from an attack's first frame.
  Its readme says this mode is not for practising against people, because reactions
  no person has force specific lines to win. Otherwise 20% of the time it plays a
  "semi-super" mode (the same guard, but pressure gets through), and the rest of the
  time `guard_rank` and `graze_rank` are drawn from 1-30.
- **The guard is a model of reaction time.** When an enemy attack starts, `guard_rate`
  is 0; each frame of the attack it moves by `random(9) - 4` (+1 a frame on average).
  Until it reaches `guard_rank` the AI holds a guessed height (redrawn every 600
  frames); from then on it blocks correctly. Grazing has a per-frame `graze_rank/1000`
  chance of being impossible. So `guard_rank` is roughly a reaction time in frames,
  varying from attack to attack.

Their reported limits: people who learn a script's patterns beat it; combos fail; every
script is tied to version 1.10 and to real time; bugs shipped because nothing tested
them.

### The learning attempts

| Project | Approach | What came of it |
|---|---|---|
| ldw079/th123_rl (2026) | Its own PPO choosing among ~90 hand-written move sequences per character (with hit-confirm branches), a behaviour-cloning term from 61,572 expert replays, a CPU ladder, self-play snapshots, a league and exploiters; ~360-390 features including a projectile threat grid; 7-9 million decisions per character | Its logs: people won 40-0 over 11 sessions. It beats the Normal CPU 17-0, which people beat every time. 38% of its decisions are jumps, 83-88% of its attacks miss. 15-25 games an hour per worker at 4.3% uptime |
| PinkySmile/SokuAI (2021-2025) | A genetic algorithm over small networks (62 move outputs, cut to 4), later a TorchRL rewrite | Unfinished; the reward counts damage only when HP goes up |
| mozhu62/SOKU_AI, SOKU_AI_IQL (2026) | Offline RL (CQL, IQL) from replays played back to dump states | Never trained |
| Ubuntufanboy/SokuBot (2026) | A world model learned from 200 hours of replay video, a policy trained in it | Its own notes: it has never pressed a button in the game (Wine ignores synthetic keys); predictions of an action's effect hold for ~0.27 s |
| zhaiwuz5, dticpw, reofficial (2024-2025) | TD3 and replay-derived data; PPO with a heavily shaped reward; a genetic algorithm on screenshots | Stubs, no results |

Much of the 2025-2026 code was written by LLM agents, and the READMEs claim more than
the code does. One repository that searches turn up, ackerlinkinc/th105-fighting-engine-reverser,
is no AI at all: its page decodes and runs a hidden script, and a workflow makes fake
commits every hour. Don't open it.

What went wrong, from their code and notes:

- **Reward hacking.** ldw079's agent farmed graze rewards (+419 a round against ±20 for a
  KO); return rose while winning fell. Fixed with potential-based shaping and taking the
  small rewards back on lost rounds. Other projects shipped sign and scale errors.
- **Imitation.** Replays hold only inputs; states come from playing them back, and
  ldw079's labels drifted 70-240 frames from their states. Frame-by-frame cloning learns
  "do nothing": mozhu62 weighted the frames where the input changes 24-32 times.
- **Actions that don't work.** A button on the same frame as a new direction is
  swallowed, so every scripted move needed a direction held 6 frames first; some moves
  never came out, or came out facing the wrong way.
- **The CPU as a measure.** Beating it said nothing about beating a person.

## EFZ's CPU

From the recovered source:

- Each character has its own `CpuInput()` (`src/akane.cpp:814`, and 23 more): ~22,000
  lines in all, ~900 a character. Each frame it sets the controls or a special move
  (`m_command = kCmd623A`) from rules on the distance in front (`dx`) and above
  (`dy`), its own and the opponent's pattern numbers, the gauges, and rolls of
  `Random(0, 100) < m_cpuSkill * k`. `m_cpuAction` holds short sequences (dash, then
  attack) across frames.
- `m_cpuSkill` is the CPU level, 1-4 (`src/scene2.cpp:344`), or in arcade mode the
  match number / 1.5 (`src/scene2.cpp:341`), so later arcade matches go past 4.
- **The guard reads the attack.** When an attack can be blocked and the CPU is able to
  block, `CPlayer::HoldsGuard` (`src/player.cpp:543`) blocks unless
  `rand() > m_cpuSkill * 10000` (`src/player.cpp:551`; `rand()` is 0-32767), and takes
  the height from the attack's own flags. So it blocks 30.5% of such attacks at level 1,
  61% at 2, 91.6% at 3 and all of them at 4, always at the right height. Recoil guard
  has rolls of its own in each `CpuInput()`.

An agent trained only against level 4 learns what beats a perfect blocker: throws,
attacks during its moves, guard crush; mixups never pay.

## What follows for EFZ

1. **Speed is what held them back, and we have it.** ldw079's scaffolding (90 scripted
   moves a character, hand-built threat features, the cloning term) makes up for ~1,300
   frames a second. With ~200,000, plain self-play PPO with a league is the first thing
   to try.
2. **Measure strength with ratings, not the CPU.** Use the CPU as the first rung of a
   curriculum; rate agents against frozen snapshots and exploiters, and against people
   through netplay with EfzRevival ([compat.md](compat.md), "The network layer").
   `efz_env.pbt` does the first part: a league of PPO agents rated by Elo (the CPU at
   1000), the weakest replaced by perturbed copies of the strongest
   ([headless.md](headless.md), "Population-based training").
3. **Keep the reward sparse.** `efz_env`'s (damage, rounds, match) already is. Any shaping
   potential-based; watch behaviour (attacks that miss, the share of jumps, time-outs),
   not only return; unit-test reward code.
4. **Test the actions.** Our 45 actions press directions and buttons only, so a special
   move like 236A takes several steps. A test should check that each action, and each
   character's special moves as sequences of them, come out from the states that matter
   at the default `frame_skip`.
5. **Imitation from replays is possible here exactly.** Deterministic playback rebuilds
   every state of a replay (the compatibility suite does it); fight records
   ([logging.md](logging.md)) and Minari datasets hold the result. Weight the frames
   where the input changes, or label moves rather than frames.
6. **Scripted opponents are cheap.** EFZ's `CpuInput()` routines, with the Reimu AI's
   reaction model on top (a random walk to a threshold), give a ladder of opponents from
   human-like to inhuman, outside the game's code so the game stays the original's.
7. **We can search; none of them could.** Save states allow tree search over the real
   game. In the FightingICE competition the winners went from tuned rules (2015) to
   Monte Carlo tree search over a simulator (2016-2018) to minimax with rules per
   character (2019).
8. **Smaller things:** scenario controls for curricula (SokuAI sets HP and positions and
   bans moves; save states do the first two), a memory of recent frames in the agent
   (several used a GRU or a temporal convolution over the history), and masking hidden
   information in the trainer (Hisoutensoku has cards; EFZ has little).

### Combos: learnt, or started for it

Damage pays for each hit at once, so a policy is drawn from one hit to two to three:
lenient chains can be found by reinforcement learning alone. Specials, supers and tight
links are rare finds from per-frame controls. A special needs its motion's directions,
in order, within the last 60 ticks (20 frames) of the input history (Akane's 623,
`src/akane.cpp:592`; lenient: the directions needn't be on consecutive frames), and
then, to cancel into it, the button while the current frame is cancellable and the
attack has hit or been blocked (`src/akane.cpp:208`). Nearly every project started its
agent off: special moves or whole combos as actions (FightLadder, SokuAI, ldw079's ~90
combos with hit-confirm branches), skills as actions (Blade & Soul), or cloning replays
first (slippi-ai).

For EFZ, in order:

1. **Command actions.** Each character's special and super motions as actions, played out
   by the environment as the frames of directions and the button: through the human path
   (`ReadInput`), so execution noise applies, not by setting `m_command` as the CPU does.
   A motion is 3-6 frames, so little reaction is lost.
2. **Starting from hits.** Matches started from save states taken just after a hit lands
   (from CPU fights or the agent's own), so continuing a combo is practised often. Only a
   game with save states can do this.
3. **Cloning.** Human replays teach combos and style together. The CPU does combos too,
   but chooses its specials by setting `m_command` (`src/akane.cpp:897`): its recorded
   inputs carry the buttons, not the motions, so cloning it teaches which move and when
   (with command actions), not how to enter it.

Not: whole combos as actions (brittle, and they take away trait 2, choosing the combo
one can land), or rewards per combo hit (farmed).

### Collecting replays

The community has many replays, from basic combos to advanced; there is no public
archive of them. They are shared as `.rep` files in its channels (the English, Japanese
and South American Discord servers the Mizuumi wiki lists), and players keep their own:

- **Netplay.** EfzRevival saves every netplay match by default (`SaveAllReplays = 1`,
  `ReplayFolder = replay/netplay/`, if that folder exists) as
  `<YYYYmmdd-HHMMSS> <P1> (<char>) vs <P2> (<char>).rep` ([revival.md](revival.md)):
  years of matches in many players' folders, with who played whom.
- **Tournaments.** Tournament mode saves every game, with `tournament_results.txt` (the
  players, characters, rounds and score of each).
- **Combos.** Local replays and the practice recorder's; the Mizuumi wiki's combo lists
  per character (its notation can be turned into inputs and checked in the game). The
  wiki turns away automated reading, so its pages come by hand or by permission.

An EfzRevival replay is the game's own replay with a block after it: the random seed,
then both players' inputs, then the block's offset and `-1` ending the file
(`Game::readExtendedReplay`, `revival/EfzRevival/EfzGame.cpp:1020`). A seed of 0 is an
early version's bug. The game's own part holds the inputs and every random draw
([compat.md](compat.md), "The replay format"), which this game already plays back
exactly; whether a netplay replay's own part is complete is to be checked on real
files. `key.ini`'s fight settings are in neither.

From replays to data:

1. **Play them back** headless with the fight recorder ([logging.md](logging.md)): every
   tick's inputs and state, the observations, save states.
2. **Check them.** Each must end as it was played: the rounds and score of the battle log
   or `tournament_results.txt`, a KO where the inputs end.
3. **Find the combos** (the combo counter and damage, from the first hit to the drop) and
   rate how hard each is by playing it again from the save state before it with each
   input a frame early or late: the share that still lands. That measures trait 2 from
   the game itself.
4. **Use them**: cloning; matches started from their hits; each player's habits,
   reaction times and adapting (traits 1, 4, 5) by player and level.

Players' names are in the file names: ask before collecting, say it is for training
agents, let people opt out, and replace names with stable pseudonyms in the data. Before training, the action test of
item 4 above, at the `frame_skip` used: with 4, a three-direction motion takes 12 frames,
within the 20, but links get coarser.

## Human-like agents

A design under discussion (3 November 2026); nothing of it is built. The aim is agents
that play like people, and like weaker people when asked, not only agents that win.

### Limits a person has

An agent trained without these builds its play on them (AlphaStar's final version was
retrained under camera and actions-per-minute limits), so they apply from the first
training run, in a layer between the agent and the game. The game stays the original's.

- **Reaction delay.** The agent sees the state of *d* frames ago, *d* varying from moment
  to moment (as the Reimu AI's random walk does). A common rule of thumb is 15-20
  frames at 60 a second to react to one move among several; EFZ runs 64.
- **Inputs.** A shortest hold and a most changes a second (`frame_skip` only roughly
  does it).
- **Execution.** Inputs now and then a frame early or late, directions now and then the
  neighbouring one.
- **What can be seen.** The observations include what a person can't read off the screen
  (invulnerability, armor, proration, exact frames): drop or blur them, or use pictures
  (drawn, ~43,000 frames a second against ~250,000).

### What makes a weaker player

The four traits below (the user's) are what self-play removes. It reads well, takes the
best combo, plays to win whatever the score, and becomes hard to predict, so each trait
is put in on purpose. Limitations go in the environment, so the agent learns to play
around them as people do; preferences go in the objective.

| Trait | Kind | Mechanism | Measured by |
|---|---|---|---|
| 1. More wrong predictions, worse under pressure | Limitation | Reaction delay and commitment (frames a defensive choice stays locked) grow with a pressure signal; more fallback to habits (4) | Guard success and right guesses under pressure against neutral |
| 2. Safer combos, because hard ones drop | Limitation | The execution noise above; the agent is told its skill, so it picks what it can land. The game's own timing windows decide what is hard (tight links fail, lenient cancels hold): no list of combos | Combos tried and dropped, by difficulty, against the noise |
| 3. Conservative under pressure, needless risks when ahead | Preference | Reward weights: damage taken counts more under pressure, damage dealt more when ahead. Or a critic of the spread of returns, choosing cautiously or boldly by the situation | Unsafe moves when ahead against behind |
| 4. Easier to read | Limitation | A habit table per persona over decision points (wake-up, after blocking a string, round start, at a range), e.g. backdash on wake-up 70%. At those points the environment sometimes puts the habit in place of the agent's choice, more often under pressure; an option that just worked becomes more habitual (win-stay) | A predictor of its next choice from its past ones; exploiters' win rate |
| 5. No adapting to the opponent within a match | Limitation | Adapting needs a memory of this match: the policy gets the opponent's choices so far (counts at the decision points of 4, or a recurrent state over the history), and the persona sets how fast that memory updates, not at all for the weakest. Weak personas also keep an option the opponent keeps punishing (no lose-shift). Opponents whose habits differ from match to match make adapting pay for the strong | A probe opponent with one fixed habit (a reversal on every wake-up), switched halfway: how fast the agent's punishes of it rise, and recover after the switch |

Signals: **pressure** from the game state (in block or hit stun, near the wall, low HP,
the opponent able to act first, just combo'd); **lead** from the HP and rounds.

The 2012 Reimu AI already did a version of 3: ahead by more than 1,000 HP it waits up to
`(lead + 1000) / 500` random frames before reacting (`00_reimuEXAM_main.ai:9282`).

Trait 5 is the other side of 4: the weak player is read and doesn't read. Today's
`efz_env` observation is the present state alone, with nothing of the match's history,
so a policy without memory already can't adapt; the strong personas are the ones that
need memory. Scripted AIs that adapt exist: Hisoutensoku's Remilia AI counts the
opponent's habits to punish repeats; Killer Instinct's Shadows and Street Fighter 6's
CPU change their approach once punished.

**One policy, many players.** A persona drawn for each match is given to the policy as
input: skill (jitter, slips), reaction (mean, spread), pressure sensitivity, risk (fear
behind, greed ahead), habit strength and table, adaptation (how fast its memory of the
opponent updates), knowledge (the moves and mechanics it uses at all). At play time the
persona chooses the player. With human replays, persona ranges can be fitted per skill band to
the measures above; style can come from them too (behaviour cloning, then RL kept near
it by a KL penalty, or a discriminator's reward).

**Cautions.** A crude pressure signal is gamed (avoiding corners absurdly if "near the
wall" dominates it): keep it to stun, frame disadvantage and HP, and watch the measures.
Trait 3 makes the agent worse at winning on purpose, so strength is rated on wins alone.

**First steps.** Close the autoreset and seeding gaps; then a prototype layer
(`python/efz_env/human.py`: the delay line, the noise, the signals, the persona in the
observation, the reward weights) with the measures, and short PPO runs to check that
each setting moves its measure the expected way. Habits come second: decision points
need moves found from pattern numbers.

### From Street Fighter and other fighting games

EFZ plays much like Street Fighter, and that community and its developers have worked
on the same question.

**Street Fighter 6's CPU** (Capcom, Naohiro Yasuhara, CEDEC 2024) is rules, not
learning, built to play "like a person" at every level:

- Each action is a card (its startup shown as its cost, its damage); a situation has a
  deck of them (a tactic, 戦術); tactics make a strategy (作戦) for each level. Each
  character has key cards that define its style; higher levels combine more cards.
- **Level is two axes:** the tactics it knows and its execution (実行能力). Level 1 has no
  special moves; level 6 has modest tactics and high execution; level 7 advanced tactics
  and unsteady execution, so it misjudges and misinputs.
- **It enters commands as a player does, so it can fail them:** a Zangief whose punch
  came late after the stick's rotation jumped instead of throwing.
- **A pressure coefficient (プレッシャー係数) sets whether inputs succeed;** lower levels
  feel it more. This is traits 1 and 2 above, shipped.
- **How finely it knows the frames (分解能) depends on its level:** a low level knows only
  that it is ahead (有利); a high level knows by how many frames.
- It decides on rounds, HP, gauges, position and distance, the difference in recovery
  (硬直差), posture and counters.
- **It teaches:** it repeats a pattern so the player can learn to punish it, changes when
  punished, and shows mechanics (Drive Parry into Drive Rush).

What to take: a persona has a **knowledge** axis besides execution (the moves and
mechanics it uses at all, e.g. no recoil guard or guard cancel for a beginner, as an
action mask), and **coarse perception** for weaker personas (only who acts first, not by
how much). Execution noise grows with pressure, more for weaker personas. A teaching
persona is predictable on purpose and shifts when punished.

**Killer Instinct's Shadows** (Iron Galaxy, 2015) imitate one player from their matches,
by case-based reasoning. Everything a player does is recorded with the state (400-700
patterns a match, up to 40 matches for an opponent). At run time the nearest cases are
found over 40+ measures, relative to the opponent (distance, HP difference) so they
carry over between situations, and with the preceding actions so set-ups are recognised.
Combos are timed to the frame. Candidates are ranked by how well they worked, a lower one
picked now and then to deceive; a shadow shifts when punished and falls back when a
planned sequence breaks. Tekken 8's Super Ghosts learn from a player's offline and online
matches likewise (no technical detail published). Here: deterministic replays and fight
records make "your own ghost" possible, by cloning one player's matches.

**The community's reaction numbers** (forums and guides, not research):

- About 265 ms (16 frames at 60 a second) to react to one expected, easily seen
  stimulus; moves of 16 or more frames of startup are reactable as the only threat.
  Choosing among several takes longer (one estimate: 200 ms simple, 384 ms complex).
- The response matters: switching stance (crouch to stand block, a jump) is fastest, a
  button slower, a special move's motion slowest.
- A tell matters: a move whose first 20 frames show little motion is unreactable even at
  30 frames of startup.
- **Mental stack:** the more a player tracks, the slower they react, and under time
  pressure reactions become guesses. A **read** narrows the threats to one, reacting fast
  to it and falling for the rest.

Here: the reaction delay can be a base of about 17 frames (265 ms at EFZ's 64 a
second), plus a load that grows with the threats and the pressure, plus the response's
own cost (which the action space already charges for motions). Reads could be made
explicit: the agent picks the option it expects and reacts fast to that one alone.
Hit-confirming follows from the delay: an agent whose delay exceeds the confirm window
can't confirm and must commit blind, as weaker players do.

**EFZ is fast.** Its fastest moves start in 4 frames (62 ms) against about 10 in Tekken
and Dead or Alive, so the numbers of 3D games don't carry over, and Street Fighter's
only partly. Close up, nearly everything is far below any reaction: a person blocks by
default and guesses, and the reaction delay matters mostly in neutral (jumps, dashes,
slow moves, whiffs). So close-range play is about traits 1 and 4 (predictions and
habits), and the delay alone won't make it human.

**Measures.** Street Fighter 6 shows each player's battle stats (Drive Rush, Parry,
throws, throw escapes) on Buckler's Boot Camp. Rank-level averages weren't found
published, but the stats are the kind of thing a persona's measures should be and could
be calibrated against if EFZ data stay scarce. FightLadder (Street Fighter II and others)
rates agents by Elo and by exploiters trained against frozen agents.

### Reinforcement learning in fighting games

Little of it comes from players; studios, researchers and hobbyists did it. Two are close
to what we want:

- **Blade & Soul** (NCSOFT, 2019; a 3D action fighting game). An LSTM policy decides every
  0.1 s from what a person can see (HP, distance, the wall, cooldowns, status), with
  reward +10/-10 for the match and the HP margin, and γ 0.995. A self-play curriculum
  pits three styles against each other, made by reward shaping on three axes: a penalty
  per time step (finish sooner), how much its own HP counts against the opponent's, and a
  penalty for distance. Move decisions are held for 1 s (10 steps), which explored best.
  **For fairness each decision reached the game 230 ms late, the average reaction time
  of its professionals.** In the 2018 World Championship Blind Match it won 3 of 7
  against professionals (62% across five), the aggressive agent beating all of them.
  Partly, the players said, because it never let them pause between exchanges, as
  people do: a human trait nobody had modelled.
- **Super Smash Bros. Melee.** Phillip (Firoiu et al., 2017) was pure deep RL and beat
  top players. Its successor, slippi-ai ("Phillip II"), clones human Slippi replays first
  ("which makes it play a lot more like a human"), then refines that policy by self-play
  RL, and plays with an input delay of 18 frames or more (it "should feel like playing
  locally at up to 300ms ping"). It has played top players (Zain, aMSa, Cody, Moky, Aklo)
  on stream. Its README asks that it not be run on the ranked ladders.

The others:

| | What | What came of it |
|---|---|---|
| FightLadder (2024) | Street Fighter II and III, Fatal Fury 2, Mortal Kombat, KOF '97 on emulators; IPPO, FSP, PSRO and a league on PPO | Every agent exploitable: PPO exploiters won 88-100%; people beat them "rather consistently" by blocking and low kicks at the right time. League and PSRO a little less exploitable. A sparse win/loss reward didn't learn; they shaped it |
| linyiLYi/street-fighter-ai | Street Fighter II, PPO (SB3) on pixels against the final boss in one saved state | 100% in that state at 7M steps, and no use elsewhere: the longer it trained, the less it generalised. Fixed the agent avoiding the fight ("cowardice") with a decaying penalty |
| For Honor (Ubisoft La Forge) | Competitive self-play ("DeepBot") | Described as hard to beat and more human than hand-written bots; no paper |
| FootsiesGym (2026) | Footsies (a minimal 2D fighting game on neutral), a vectorised simulator, RLlib | A benchmark for the guessing games of neutral |
| DIAMBRA Arena, DareFightingICE | Platforms and competitions (above) | PPO on pixels; MCTS and rules won FightingICE |

What follows: train against many opponents and styles, never against one CPU (the
Street Fighter II agent); measure exploitability, since even leagues stay exploitable
and people find the holes fast (FightLadder); a delay of human reaction time is what
professionals accepted as fair (230 ms in Blade & Soul, 300 ms in Melee); start from
human play where there is data (slippi-ai); and Blade & Soul's three reward axes are a
ready form of the persona's risk settings. People pause between exchanges; an agent
that never does reads as a machine.

## Sources

Frameworks: [Gymnasium autoreset modes](https://gymnasium.farama.org/main/api/vector/autoreset/),
[Gymnasium releases](https://github.com/Farama-Foundation/Gymnasium/releases),
[SB3 vector environments](https://stable-baselines3.readthedocs.io/en/master/guide/vec_envs.html),
[RLlib single-agent env runner](https://docs.ray.io/en/latest/_modules/ray/rllib/env/single_agent_env_runner.html),
[RLlib multi-agent env runner](https://docs.ray.io/en/latest/_modules/ray/rllib/env/multi_agent_env_runner.html),
[RLlib multi-agent environments](https://docs.ray.io/en/latest/rllib/multi-agent-envs.html),
[TorchRL VecGymEnvTransform](https://docs.pytorch.org/rl/stable/reference/generated/torchrl.envs.transforms.VecGymEnvTransform.html),
[PufferLib](https://github.com/PufferAI/PufferLib), [PufferLib docs](https://puffer.ai/docs.html),
[EnvPool](https://github.com/sail-sg/envpool), [EnvPool: a new environment](https://envpool.readthedocs.io/en/latest/content/new_env.html),
[PettingZoo releases](https://github.com/Farama-Foundation/PettingZoo/releases),
[CleanRL](https://github.com/vwxyzjn/cleanrl), [DIAMBRA Arena](https://arxiv.org/abs/2210.10595),
[FightLadder](https://arxiv.org/abs/2406.02081). Versions and dates from PyPI.

Hisoutensoku: [th123ai wiki](https://wikiwiki.jp/th123ai/), its
[published AIs](https://wikiwiki.jp/th123ai/%E5%85%AC%E9%96%8B%E4%B8%AD%E3%81%AEAI/AImanager/%E3%82%AD%E3%83%A3%E3%83%A9%E5%88%A5AI),
[th123_ai repack with the scripts](https://coolier.net/th_up4/index.php?id=6752),
[click3/th123_ai](https://github.com/click3/th123_ai),
[click3/AIManager](https://github.com/click3/AIManager),
[PinkySmile/SokuAI](https://github.com/Gegel85/SokuAI),
[ldw079/th123_rl](https://github.com/ldw079/th123_rl),
[mozhu62/SOKU_AI](https://github.com/mozhu62/SOKU_AI),
[mozhu62/SOKU_AI_IQL](https://github.com/mozhu62/SOKU_AI_IQL),
[Ubuntufanboy/SokuBot](https://github.com/Ubuntufanboy/SokuBot),
[zhaiwuz5/TH123_AIDev_Python](https://github.com/zhaiwuz5/TH123_AIDev_Python),
[dticpw/th123_AI_project](https://github.com/dticpw/th123_AI_project),
[reofficial/SokuAI-Evolutionary-Algorithm-Proof-of-Concept](https://github.com/reofficial/SokuAI-Evolutionary-Algorithm-Proof-of-Concept),
[lzusa/th123-replay-recorder](https://github.com/lzusa/th123-replay-recorder),
[SokuDev/SokuMods](https://github.com/SokuDev/SokuMods),
[a 2018 test of the God AI](https://www.bilibili.com/video/BV1aW411A7hk/).

FightingICE: [the competition](https://ice.ci.ritsumei.ac.jp/~ftgaic/index-R23.html),
[2019 results](https://www.slideshare.net/ftgaic/2019-fighting-game-ai-competition),
[2020 results](https://www.slideshare.net/ftgaic/2020-fighting-game-ai-competition),
[rolling horizon evolution for it](https://arxiv.org/abs/2003.13949).

Human-like agents: [Maia](https://arxiv.org/abs/2006.01855),
[piKL](https://arxiv.org/abs/2112.07544),
[human-regularised search and learning](https://arxiv.org/abs/2210.05125),
[GAIL](https://arxiv.org/abs/1606.03476), [AMP](https://arxiv.org/abs/2104.02180),
[AlphaStar's limits (secondhand)](https://alexirpan.com/2019/11/17/alphastar-update.html).

Street Fighter and others: Street Fighter 6's CPU at CEDEC 2024 in
[Famitsu](https://www.famitsu.com/article/202408/15462),
[GameBusiness.jp](https://www.gamebusiness.jp/article/2024/09/06/23466.html) and
[AUTOMATON](https://automaton-media.com/en/news/street-fighter-6s-cpu-is-designed-to-feel-pressured-just-like-a-human-and-make-input-mistakes/);
[Killer Instinct's Shadow AI](https://gamedeveloper.com/programming/the-killer-groove-the-shadow-ai-of-killer-instinct);
[Tekken 8's Super Ghosts](https://www.ggrecon.com/guides/tekken-8-super-ghost-battle);
[On Reaction Times (Infil)](https://ki.infil.net/reaction.html);
[mental stack (Red Bull)](https://www.redbull.com/ca-en/mental-stack-fighting-games),
[and under time pressure (Event Hubs)](https://eventhubs.com/news/2024/jun/23/advice-improve-wins-sf6);
[reaction time analysis (Dustloop)](https://www.forums.dustloop.com/forums/topic/6399-reaction-time-analysis/);
[FightLadder](https://sites.google.com/view/fightladder/home).

Reinforcement learning in fighting games:
[Blade & Soul (NCSOFT)](https://arxiv.org/abs/1904.03821),
[Phillip, Melee](https://arxiv.org/abs/1702.06230),
[slippi-ai](https://github.com/vladfi1/slippi-ai),
[FightLadder's results](https://arxiv.org/abs/2406.02081),
[linyiLYi/street-fighter-ai](https://github.com/linyiLYi/street-fighter-ai),
[For Honor's DeepBot](https://80.lv/articles/ubisoft-on-building-efficient-player-bots-using-deep-reinforcement-learning/),
[FootsiesGym](https://pypi.org/project/footsies-gym/).
