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

### The red team

`combo-red/`: the combo master (4M) trained on to 12M without the reaction time or the
KL pull. On the held-out starts (the resources their players had): damage 1,068 on
average, 2,877 at the 90th percentile, 4,143 at most (people from the same starts: 502,
1,534, 2,926), an Instant Charge in 30% of them. Against the agent in whole matches it
loses (2-0, slot 1-4 of D:/tasogare/EFZ/replay): its neutral is still the clone's, its
training having started at hits already landed.

People's combos by the resources at their start (`combo_library.py`; the RF gauge as the
HUD draws it, `evaluate.rf_state`: blue under 500, growing fast, no Instant Charge or RF
move; red 500-999, growing slowly, one Instant Charge (22C) or one RF move; cyan from
full until spent, not growing and drained by hits, one Instant Charge that also gives
back five times the gauge in proration (up to 50%), or RF moves at 250 each; and the bars
of power):

| RF \ bars | 0 | 1 | 2 | 3 |
|---|---|---|---|---|
| blue | 1,540 / 2,884 / 5,883 | 1,399 / 2,686 / 4,343 | 1,350 / 2,674 / 4,321 | 1,298 / 2,472 / 4,152 |
| red | 1,688 / 3,071 / 5,883 | 1,594 / 3,002 / 6,601 | 1,561 / 2,998 / 7,123 | 1,520 / 2,904 / 6,635 |
| cyan | 2,189 / 4,227 / 7,421 | 1,970 / 4,277 / 7,079 | 1,897 / 3,918 / 6,952 | 1,767 / 3,654 / 6,235 |

(average / 90th percentile / most; the bars counted at the first hit, after a super
starting the combo has spent them.) Every combo of 6,000 and more used a cyan Instant
Charge and a super. So the red team's trials now start with resources drawn from these 12
groups (`combo.py --rich`, the library's `efz_env_set_gauges`), with two helpers (the
user's): the juggle (the defender's untech time, potential-based shaping) and a cost on
the super gauge (`combo-red2/`, training). And built-in combos (`macros.py`): people's
284 most damaging combos as action sequences, the one to play chosen by a selector learnt
from trials. Played blindly from another start a recorded combo makes 22% of its damage
(6% of them 80% or more); the best of up to 12 per start, with cyan RF and 3 bars, makes
2,317 on average and 6,165 at most, where the red team alone makes 1,312 and 4,386.

The agent against it (`agent-red/`, from 10M at level 4, a quarter of its mirror matches
against the red team, which sees the game as it is): to 14M steps, more guarding (13.5 a
minute against the CPU) and less damage taken from the red team's combos (6,800 to 6,050
a minute), its own combos about as before; stopped while the red team improves.

The selector (`macros/`, 10,682 combo trials and 1,248 of the red team's own play from
the training starts) helps only with full resources; the best option in hindsight is
50-70% above the red team alone in every group:

| Held-out starts | Red team alone | With the selector | Best in hindsight |
|---|---|---|---|
| blue RF, 0 bars | 651 / 1,524 / 2,533 | 587 / 1,859 / 2,533 | 994 / 2,283 / 3,053 |
| red RF, 0 bars | 960 / 2,464 / 3,479 | 821 / 2,415 / 3,113 | 1,329 / 2,999 / 4,589 |
| cyan RF, 0 bars | 1,083 / 2,821 / 4,268 | 970 / 2,667 / 3,317 | 1,825 / 4,434 / 5,480 |
| cyan RF, 3 bars | 1,378 / 3,599 / 4,386 | 1,521 / 3,798 / 4,593 | 2,336 / 5,228 / 6,165 |

So the red team doesn't predict: `redteam.py` tries, at each of its first hits, the
library combos with that starter and its own play on copies of the game (save states, a
batch of its own) and plays the best: the hindsight column by construction. Each plan
also gives the hit's conversion potential, the most any option made from it: the
measure of an "easy location" (the user's: a hit from which a big combo is likely),
which the agent should learn to avoid giving even where it doesn't take fewer hits.
`finetune.py --lookahead` puts it in front of the agent (from 14.1M, a quarter of the
mirror matches) and reports, against it, the potential of the hits the agent took and
the share worth 3,000 or more.

The in-air bar (the user's point: it costs nothing, so people spend it with longer
combos): the proration left at the end of combos of 3 hits or more is 64% for people,
74% for the agent at 14M, 79% for the red team. `combo.py --leftover-cost` charges for it
(the red team of `combo-red3/`, with the juggle helper and a super cost of 0.1 a bar;
`combo-red2/`, with 0.5 a bar, fell behind with 3 bars and was stopped at 15M).

Phase 2 against the lookahead red team, to 30.2M steps: it wins 66% against the level-4
CPU (random characters), 100% against the curriculum agent and 94% against the red team.
Red team 3, to 24.2M: 1,097 / 3,064 / 4,143 on people's resources (average / 90th
percentile / most; the 12M red team 1,068 / 2,877 / 4,143), cyan RF and 3 bars 1,359 /
3,700 / 4,386.

## Defence and tactics

The measures since 5 November, in `Events` (`evaluate.py`) and `tactics.py`, both ways
(one's own play and the opponent's), with people's numbers in `people.json`:

- **Damage taken.** HP lost a minute, and the opponent's combos on one (average, 90th
  percentile, most, and by the attacker's resources). People's Ayu takes 7,428 a minute
  and deals 6,796; the combos on her average 934, p90 2,189, most 8,066.
- **Pressure, in frames.** After each guard, the frame advantage: the step the defender
  is free minus the step the attacker is (each contact found by the guard restarting;
  the advantage taken from the move that made the last one). A minus guard matters
  only if the defender can use it (the user's point): it is *punishable* when the
  defender has a move as fast as the disadvantage that reaches, by the game's own frame
  data (`framedata.py`: per character and move, its startup, reach and invulnerable
  frames, from the `.pat` files; `framedata.json` is made on each machine and kept out
  of the repository). People's Ayu: median +2, 54% of guards plus, 19% punishable; the
  defender fights back after 25% of the punishable ones, 16.5% of the safe minus ones,
  14% of the plus ones; about 36 power gained per guard. By the move guarded last,
  0x107 is the "stupid move": -10, punishable 76% of the time, fought back 47%.
- **Ways out** (the user's: invincible moves and the like). What the defender started
  after a guard: an invincible move (invulnerable in its first frames by the frame data,
  or by the timer some moves set: a reversal), another move (a mash), a jump, a backdash;
  and RG, with what followed it. For Ayu under pressure, invincible moves got her out
  60% of the time (trapped 4.5%), mashes 34% (trapped 25%).
- **Wake-up.** Per knockdown, the riser's choice and how it went (who hit first, the HP
  swing over 3 seconds), and the attacker's setup (frames free before the rise, meaty,
  airborne, close, objects out). Ayu rising: guard 56%, mash 19%, invincible 10%, jump
  10%; an invincible reversal swings 527 HP her way, waiting costs her 509.
- **Free time.** Steps free while the opponent can't act, and their use: a setup (a move
  that put out an object: a trap), a charge (`tactics.CHARGE`: Kano's 5D and 236D for her
  magic gauge), another move, closing in, waiting. Mizuka uses 32% of hers for setups,
  Misuzu 6.6%, Kano charges in 7.5%; most characters set up in under 2%.
- **The CPU's tiers.** At level 4 the CPU is hardest as Kanna, then Ayu and Mishio, then
  the rest (the user's); below level 4 all are easy. `evaluate.py --chars ayu tiers`
  plays a third of the matches against each tier and reports the wins by tier;
  `finetune.py` evaluates level 4 that way (`--cpu-chars`). What the source says: the
  level sets `m_cpuSkill`, and a CPU guards an attack when `rand() <= m_cpuSkill * 10000`
  (`CPlayer::HoldsGuard`, src/player.cpp:551), choosing the right height itself; `rand()`
  tops at 32,767, so it guards 31%, 61%, 92% and, at level 4, 100% of what it can,
  every character alike. The level also scales the random chances in each character's
  `CpuInput`. So the tiers come from the characters' own routines and moves, not from
  guarding; and since Mishio's `CpuInput` is byte-identical to Kano's, Ikumi's and
  Shiori's (docs/naming/kano-ikumi-mishio-shiori.md), the routine alone doesn't make
  her tier either. Why these three is not worked out.

## Other characters: clones, exploiters, a league

From 5 November the scripts take any character: `dataset.py --char`, `bc.py --char`,
`people.py --char`, and `finetune.py --char` with `--vs MODEL:CHAR` (frozen opponents of
other characters, playing `--vs-share` of the matches against agents), `--focus` (a
shaping reward for what an opponent is meant to be good at, `focus.py`: `setup`, a move
in free time that puts out an object; `charge`, Kano's charge moves in free time) and
`--stop-win`. Each character's run is in its own folder (`mizukab/`, `kano/`...): people's
measures (`people.json`), the clone with a 14-frame reaction time (`bc-d14.zip`, as
Ayu's), and the exploiter (`exploiter/`), trained against a frozen copy of the agent
(`target.zip`: `agent-red` at 22.2M steps), a quarter of its matches against the CPU,
with its focus and a KL pull toward its clone. The checkpoints are on Hugging Face.

| Character | People's sides (in sync) | Clone: held-out nll, press recall | People's free time used for | Clone vs the agent | Exploiter vs the agent |
|---|---|---|---|---|---|
| Ayu (`bc-d14`) | 1,908 | 0.349, 3% | setups 3% | | |
| Mizuka (`mizukab`) | 2,573 | 0.320, 8.7% | setups 31% | 0% | 84% after 3M steps (focus: setup) |
| Kano | 2,963 | 0.295, 9.8% | charge 7%, setups 4% | 28% (16% cut) | 100% after 1M steps (focus: charge) |

Both exploiters found holes in the agent within a few million steps:

- **Mizuka** wins by trap pressure: she uses 43% of her free windows for setups (her
  clone 18%), and after her guarded strings the agent is a median of 10 frames minus
  (-1 against the clone); the agent guards 17 times a minute (7) and is still hit 13
  times, mostly just holding guard (60% of the gaps, trapped 24%). The agent deals 5,957
  a minute, she 8,230. Replays: EFZ's REPLAY menu, page 1, slots 7-9 (two of the agent's
  wins, then one of hers).
- **Kano** stopped guarding (6 a minute, her clone 17) and attacks, sets up and charges
  in free time (18% of it); the agent is knocked down 5.4 times a minute and hit in the
  air 2.8, and deals 4,749 a minute to her 7,972. She also beats the level-3 CPU 72%.

The agent had met other characters only as the CPU, which neither sets traps nor zones
like this. `agent-league/` continues it from `agent-red` at 30.2M against the league: the
CPU, the clone, a frozen copy, the curriculum agent, the team, red team 3 with the
lookahead, and the two exploiters (40% of the matches against agents; from 38.3M shared
between them by `finetune.py --pfsp 2`, (1 - the last win) squared, so mostly Kano's).
To 50.4M steps, then 64 matches each on the same seeds (`agent-league/compare/`):

| Agent | Level-4 CPU: Kanna / Ayu, Mishio / the rest | Mizuka's exploiter | Kano's exploiter |
|---|---|---|---|
| `agent-red`, 30.2M | 0% / 67% / 81% | 33% | 16% |
| `agent-league`, 50.4M | 0% / 67% / 86% | **69%** | 19% |

Mizuka's hole closed (it deals her 8,257 a minute, from 6,504; her strings leave it -6, from
-9), keeping people's rates (1.6 presses a second, 13 jumps and 10 guards a minute).
Kano's didn't: it still jumps 19 times a minute against her and is hit in the air 2.4
times and knocked down 5.5 (her anti-airs and okizeme), a change within the noise; its
per-chunk evaluations against her stayed at 3-19% throughout. The level-4 CPU's Kanna is
still never beaten. The evaluations of 32 matches swing by +-8%: the one against Mizuka
went 31, 41, 34, 50, 62, 34, 44, 25, 59, 75% over the chunks.

**Round 2** (6 November, on the Linux machine): new exploiters from the clones against a
frozen `agent-league` at 50.4M (`target2.zip`; `mizukab/exploiter2/`, `kano/exploiter2/`,
the same settings as the first). Mizuka's beat it 81% after 6.1M steps (by chunk, on 32
matches: 12, 19, 28, 31, 38, 81%), Kano's 72% after 1M. On 64 matches
(`agent-league/compare/agent-league-*2.json`):

| `agent-league` against | Agent wins | Its guards / hits in the air a minute | Damage it takes a minute |
|---|---|---|---|
| Mizuka's exploiter 1 | 69% | 11.0 / 1.8 | 7,329 |
| Mizuka's exploiter 2 | 23% | 17.3 / 2.3 | 8,928 |
| Kano's exploiter 1 | 19% | 9.9 / 2.4 | 8,543 |
| Kano's exploiter 2 | 19% | 9.6 / 2.7 | 8,638 |

The new Mizuka plays the first one's trap pressure further: after her guarded strings the
agent is a median of 10 frames minus (6 against the first), fights back after 13% of them
(21%), and her objects are out 30% of the time (14%), setups in 44% of her free windows.
The new Kano found the old hole (19 jumps a minute, anti-aired).
`agent-league2/` (the exploiters 60% of the agent matches) and `agent-league2-kl/` (a
pull of 0.05 toward the clone) continue `agent-league` against all four.

Datasets of people's Misuzu (2,651 sides in sync) and Mishio (2,609) are made; their
clones were stopped (the system ran short of memory) and are next.

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
| `finetune.py` | PPO from the clone, every frame, KL to it; half the matches against the level-4 CPU with any character, half Ayu's mirror against a frozen copy, the clone, the curriculum agent and the `--team` of players' clones; any character (`--char`), opponents of other characters (`--vs`, shared by `--pfsp`), a focus (`--focus`), `--stop-win` |
| `evaluate.py` | matches to the end, with how each side played (`Events`: presses, jumps, guards, recoil guards and counters, punishes after an RG, the 623 guesses, combos with their 90th percentile and most, Instant Charge, inputs while unable to move, damage taken, and `tactics.py`'s); `--chars ayu tiers` for the level-4 CPU's tiers; plays language models too (`runs/llm-ayu`) |
| `tactics.py` | pressure (frame advantage, punishable or safe, ways out, RG), wake-up and free time, both ways |
| `focus.py` | an opponent's focus as a shaping reward (`finetune.py --focus`): setups and charges in free time |
| `framedata.py` | the characters' frame data from the game's `.pat` files: startup, reach, invulnerable frames (`framedata.json`) |
| `people.py` | the same measures of people, overall, by opponent and by player |
| `compare.py` | people and agents side by side, as the tables here |
| `team_check.py` | whether players' clones predict their players better than the clone of everyone |
| `combo_starts.py` | where people's combos started, kept as a replay and a step |
| `combo.py` | the combo master: trials from those starts, rewarded for the combo's damage |
