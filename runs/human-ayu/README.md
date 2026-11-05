# Ayu from people's replays

Agents that play Ayu the way people do, made from the community's replay collection
(4 November 2026, on the same Ryzen 7 6800U laptop as the other runs, PyTorch on the
CPU). Unlike the agents of [`../curriculum/`](../curriculum/), which know only Ayu's
mirror and decide every 4 frames, these:

- **act every frame** (64 a second), as people do, seeing their own last 16 inputs
  (`efz_env.history`), which they need to carry a motion through (236, 623, 641236);
- **start as a clone of people** (behavioural cloning on 1,908 matches of people's Ayu
  against every character), and learn on from there by reinforcement, **pulled toward
  people's play** by a KL penalty to the clone (`efz_env.policy.EfzPolicy.set_prior`);
- optionally **see the game late**, by a reaction time (`--delay`, in frames), as people
  do; their own inputs they know at once;
- are measured on **how** they play, not only how often they win: presses, jumps,
  guards, recoil guards and recoil counters, punishes after an RG, the 623A/623B
  guesses (`evaluate.py`, `Events`), against the same measures of people (`people.py`).

## The data

`dataset.py` plays back every replay of the collection in which Ayu plays
(`EfzVecEnv.play`, at frame_skip 1) and keeps Ayu's view and inputs at each step: 1,949
sides of 1,915 replays, 1,908 of them checked in sync (EfzRevival's own frame count
matched, 459 frames apart for all, or the match ended in a KO). The replays, the data
and the players' pseudonyms are outside the repository (`D:\tasogare\efz-replays`):
the file names carry the players' names.

## The clones

`bc.zip` (sees the game as it is) and `bc-d14.zip` (14 frames late, about 220 ms): 4
epochs on 4.9 million steps, the best kept. On the held-out tenth of the replays they
predict people's inputs at 0.344 and 0.349 nats a frame: the reaction time costs
little, people anticipate more than they react. Against the level-4 CPU with any
character, 48 matches each, people's measures from all 1,908 matches (`people.py`):

| | People | Curriculum agent | `bc.zip` | `bc-d14.zip` |
|---|---|---|---|---|
| Wins / losses / cut | - | 58% / 42% / 0% | 19% / 71% / 10% | 0% / 96% / 4% |
| Presses a second | 1.46 | 9.31 | 1.31 | 1.24 |
| Jumps a minute | 19.0 | 19.0 | 20.5 | 19.9 |
| Guards a minute (ground) | 11.7 | 0.8 | 14.0 | 16.6 |
| Hits taken a minute, ground + air | 5.2 + 2.6 | 11.2 + 2.2 | 9.2 + 3.0 | 10.0 + 3.2 |
| Recoil guard, ground / air | 14% / 14% | 1% / 0.4% | 8% / 7% | 7% / 9% |
| Recoil counter | 27% | 5% | 10% | 8% |
| After its RG: a move / it hit | 40% / 14% | 89% / 28% | 43% / 13% | 32% / 11% |
| 623A / 623B a minute | 0.25 / 0.35 | 0.36 / 0.65 | 0.26 / 0.21 | 0.17 / 0.14 |

They play like people: the presses, jumps, guards, the moves after a recoil guard and
the 623s at people's rates, none of it written as a rule. They recoil-guard and
recoil-counter about half as often as people. And they lose to the level-4 CPU, which
guards nearly everything; with a reaction time they win 88% at level 1, 22% at level 2.
A first clone, trained on the thinned steps without weighting them, pressed three times
as often as people and used 623 five times as often (and beat the CPU 60%): thinning
the steps where nothing changes inflates the odds of a change; `bc.py` weighs them back.

## The team

`team/player<N>.zip`: six players' clones (N: their pseudonyms, in `players.csv` beside
the replays), each `bc-d14.zip` trained two more epochs on one player's matches (41 to
487 of them), chosen for how they differ (`people.json`, `by_player`). Each predicts its
player's held-out matches better than `bc-d14.zip` does (by 1-3.5%, `team/check.json`)
and they differ in strength (8% to 38% wins against the level-2 CPU), but they keep
little of their players' habits: most measures fall back to everyone's (docs/training.md,
"A team of players"). They are among the opponents of the fine-tuning.

## The fine-tuned agent (training)

`finetune.py --start bc-d14.zip --prior bc-d14.zip --delay 14 --level 2 --team
team/player*.zip --chunk 2e6 --budget 3e7 --eval 32` into `agent/`, started 4 November
2026, 19:49: about 14 minutes a chunk of 2 million steps (2,400 a second). Its
evaluations after each chunk (32 matches against the CPU at the chunk's level, any
character, and 32 against the curriculum agent in the mirror):

| Steps | CPU level | Wins vs CPU | Wins vs curriculum agent | KL to the clone | Presses/s | Guards/min (vs CPU) |
|---|---|---|---|---|---|---|
| 0 (the clone) | 2 | 12% | 0% | - | 1.28 | 11.4 |
| 2M | 2 | 81% (promoted) | 25% | 0.025 | 2.14 | 5.6 |
| 4M | 3 | 34% | 47% | 0.028 | 1.83 | 9.6 |
| 6M | 3 | 47% | 59% | 0.030 | 1.92 | 9.7 |

`agent/` (its model and checkpoints) comes with the run's end.

## The scripts

| Script | What |
|---|---|
| `dataset.py` | replays to data: per Ayu side, the views, inputs and rewards of each step |
| `bc.py` | the clone: the 45 actions people's inputs come to each frame, and the critic from their matches' returns; `--delay` for a reaction time, `--players` for one player's clone (from the clone of everyone, `--init`) |
| `finetune.py` | PPO from the clone, every frame, KL to it; half the matches against the level-4 CPU with any character, half Ayu's mirror against a frozen copy, the clone, the curriculum agent and the `--team` of players' clones |
| `evaluate.py` | matches to the end, with how each side played (`Events`) |
| `people.py` | the same measures of people, overall, by opponent and by player |
