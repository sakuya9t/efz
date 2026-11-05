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

## The fine-tuned agent

`finetune.py --start bc-d14.zip --prior bc-d14.zip --delay 14 --level 2 --team
team/player*.zip --chunk 2e6 --budget 3e7 --eval 32` into `agent/`, 4 November 2026,
19:49 to 21:12: about 14 minutes a chunk of 2 million steps (2,400 a second). Its
evaluations after each chunk (32 matches against the CPU at the chunk's level, any
character, and 32 against the curriculum agent in the mirror):

| Steps | CPU level | Wins vs CPU | Wins vs curriculum agent | KL to the clone | Presses/s | Guards/min (vs CPU) |
|---|---|---|---|---|---|---|
| 0 (the clone) | 2 | 12% | 0% | - | 1.28 | 11.4 |
| 2M | 2 | 81% (promoted) | 25% | 0.025 | 2.14 | 5.6 |
| 4M | 3 | 34% | 47% | 0.028 | 1.83 | 9.6 |
| 6M | 3 | 47% | 59% | 0.030 | 1.92 | 9.7 |
| 8M | 3 | 59% | 81% | 0.034 | 1.77 | 10.7 |
| 10M | 3 | 75% (promoted) | 91% | 0.034 | 1.86 | 9.4 |

Stopped at 10M (`finetune.json` continues it, at level 4) for what its combos lack, next.

## Combos, and the combo master

Its combos (the user's observation: little Instant Charge, cancels, damage), against
the CPU after 10M steps, with people's from their matches:

| | People | Curriculum agent (CPU 3) | Agent, 10M (CPU 3) | Agent, 10M (CPU 4) |
|---|---|---|---|---|
| Wins | - | 81% | 69% | 44% |
| Combo damage: average / 90th percentile / most | 970 / 2,357 / 7,421 | 737 / 1,433 / 3,578 | 718 / 1,486 / 4,112 | 694 / 1,477 / 4,407 |
| Combo hits: 90th percentile / most | 10 / 44 | 5 / 21 | 5 / 21 | 5 / 19 |
| Combos (2+ hits) with a special / an Instant Charge | 44% / 16% | 22% / 0% | 59% / 0.7% | 57% / 2% |
| Damage a minute in combos | 6,796 | 8,521 | 8,051 | 6,917 |

It deals as much a minute as people from more, shorter combos: the reward pays a poke at
once and a long combo only when every input of it is right, so learning from whole
matches settles there. The long ones (the 90th percentile and the most, at half of
people's) need cancels buffered while the character can't move and Instant Charge.

`combo_starts.py` keeps 706 places where people's combos started (the first hit, from
330 replays; 82 from replays bc.py holds out), and `combo.py` trains the combo master on
trials from them: the agent has the attacker, the defender guards once it can, the
reward is the combo's damage. A save state holds the library's addresses, so the starts
are kept as a replay and a step and made again by playing back (706 of 706 at the view
kept, in 36 s). On held-out starts, the damage after the first hit, people's from the
same starts (the clone and 2M on 64 of the 82, people 468 / 1,452 / 2,926 there):

| | The clone (64) | Combo master, 2M (64) | 4M (82) | People (82) |
|---|---|---|---|---|
| Damage: average / 90th percentile / most | 264 / 934 / 2,330 | 504 / 1,429 / 2,235 | 602 / 1,581 / 2,662 | 502 / 1,534 / 2,926 |
| Hits, most | 10 | 9.5 | 10 | 20 |
| Better than the player from the same start | 11% | 35% | 35% | - |
| With an Instant Charge | 0% | 3% | 1% | - |

It overtook people on average within 2 million steps (6-8 minutes a million), not yet
on the longest combos; from 3M half its trials start where people made the most (the
corner, the meter) and run up to 1,200 steps.

Its role (the user's): a red-team opponent, landing the most damaging combo whenever it
can. It needn't convert at people's rate, so it is trained on without the KL pull toward
people or the reaction time, and plays the agent seeing the game as it is (the agent and
its other opponents seeing it 14 frames late), so that taking a hit costs the agent what
it can cost: pokes stop paying. (`finetune.py --combo` can also make it the target of the
agent's KL pull during its own combos; not used, as it would pull the agent's combos
toward a superhuman's.)

## The models

On Hugging Face, https://huggingface.co/sakuya9t/efz, under the same paths:
`python runs/hub.py download human-ayu` (the clones, the team, the agent's checkpoints,
the combo master). The repository keeps the clones and the team too; the agent's and
the combo master's checkpoints are only there.

## The scripts

| Script | What |
|---|---|
| `dataset.py` | replays to data: per Ayu side, the views, inputs and rewards of each step |
| `bc.py` | the clone: the 45 actions people's inputs come to each frame, and the critic from their matches' returns; `--delay` for a reaction time, `--players` for one player's clone (from the clone of everyone, `--init`) |
| `finetune.py` | PPO from the clone, every frame, KL to it; half the matches against the level-4 CPU with any character, half Ayu's mirror against a frozen copy, the clone, the curriculum agent and the `--team` of players' clones |
| `evaluate.py` | matches to the end, with how each side played (`Events`: presses, jumps, guards, recoil guards and counters, punishes after an RG, the 623 guesses, combos with their 90th percentile and most, Instant Charge, inputs while unable to move) |
| `people.py` | the same measures of people, overall, by opponent and by player |
| `compare.py` | people and agents side by side, as the tables here |
| `team_check.py` | whether players' clones predict their players better than the clone of everyone |
| `combo_starts.py` | where people's combos started, kept as a replay and a step |
| `combo.py` | the combo master: trials from those starts, rewarded for the combo's damage |
