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
  `finetune.py` evaluates level 4 that way (`--cpu-chars`).

  *Why, in the source* (6 November). The level sets `m_cpuSkill`; a CPU guards an attack
  when `rand() <= m_cpuSkill * 10000` (`CPlayer::HoldsGuard`, src/player.cpp:551), the
  height chosen for it, and `rand()` tops at 32,767: 31%, 61%, 92% and at level 4 100% of
  what it can, every character alike. Each routine also opens the recoil-guard window at
  random each tick (kanna.cpp:703-711) and starts something after an RG, and the level
  scales its other chances. What separates the characters is how their routine's few
  choices fit their moves (the user's guess):
  - **Ayu:** a x2000 where x2 was meant (ayu.cpp:790) makes every hit that lands while
    she is in guard stun a recoil guard, and her favourite move after one is 623C,
    invincible from its 2nd step.
  - **Mishio:** Shiori's routine (byte for byte, as Kano's and Ikumi's), whose top pick
    after an RG and against an attack is 623C (mishio.cpp:1144): for Mishio an
    invincible 623 of 6-9 steps, which also grants her power-ups; Kano has no such
    command, Ikumi's takes 28 steps, Shiori's 12.
  - **Kanna:** any hit, guard or knockdown state sets a 180-tick cooldown
    (kanna.cpp:697-699) that switches off all her neutral attacks (:1464-1529): she never
    presses into frame traps, guards everything, keeps only her invincible 623A/236C
    reactions, and has the cast's strongest anti-air (623A, 6% a tick against a jump
    attack, :1551-1555). The same rule is her flaw (the user's): a throw (C + forward or
    back within 30 px, unblockable, which nobody, CPU or human, can break; only 27 ticks
    of immunity after a jump start, a guard, a knockdown or a wake-up) puts her in a hit
    state, so each throw renews the cooldown, and up close she only stands or walks. The
    community beats her by throwing her again and again, or with Nanase's home run.

  *Measured* (`eval/cpu4-chars/`: `agent-league` against each level-4 CPU, 32 matches
  each): Kanna 0%, Unknown (`mizukab`) 28%, Ayu 31%, Nanase 47%, Mai 50%, Sayuri 56%,
  Shiori 66%, ... Mishio 94%, Ikumi, Kano, Minagi and EXNanase 100%. Across the 23 the
  agent's wins follow how often the CPU hits it in the air (Spearman -0.79) and the
  damage it deals (-0.72) more than its reversals (-0.3): Kanna deals 15,406 a minute
  (the others 5,400-9,700) and anti-airs 4.2 times a minute; Ayu's CPU escapes the
  agent's pressure with an invincible move 38% of the time, 85% of them working. Of a
  routine shared by several characters one is clearly strongest: Shiori 66% against
  Mishio 94%, Ikumi and Kano 100%; Misaki 78% against Misuzu 97% and Minagi 100%. This
  agent finds Mishio easy, against the tier. It throws 0.01-0.07 times a minute (people's
  Ayu 0.26: `throws_per_min`), so it never found Kanna's flaw. Beating level-4 Kanna is
  a diagnostic, not a target: a rise in it is to be checked against the agent's throws
  before it is believed.

  *Short of winning* (7 November; the user's measure). Nothing has beaten her yet, so
  `evaluate.py` also gives the share of the opponent's HP taken a round
  (`opp_hp_taken`, its best round, rounds won: overall, by tier and by opponent), and
  the agent's reversals (`reversals_per_min`: any invincible move of its, from
  framedata.json; `reversal_hit`, `reversal_counter`: of them, the share that hit, and
  that hit her in a move of her own). Without throws the way to beat her (the user's)
  is big combos and invincible moves put out as she acts, overriding her slow, long
  moves and starting a combo. Her attacks start in 4-16 steps (her supers 51 and 59),
  so with the 14-step reaction an invincible move beats them only as a prediction, as a
  player learns the CPU's habits; Ayu's quickest (0xf0, 0xfb) start in 2. Against
  level-4 Kanna, 64 matches each (`eval/kanna/`):

  | Agent | Her HP taken a round | Rounds won a match | Dealt / taken a minute | Reversals a minute (hit, counter-hit) | Throws a minute |
  |---|---|---|---|---|---|
  | the clone, `bc-d14` | 8.4% | 0 | 1.6k / 19.0k | 0.8 (57%, 24%) | 0.12 |
  | `agent` | 17.9% | 0 | 2.8k / 17.0k | 2.3 (42%, 40%) | 0.03 |
  | `agent-league` | 22.0% | 0 | 3.2k / 16.1k | 2.2 (36%, 32%) | 0.04 |
  | `agent-league2-kl` | 29.8% | 0 | 3.9k / 14.8k | 3.2 (34%, 31%) | 0.01 |
  | `agent-league3` | 34.3% | 0.02 | 4.1k / 13.4k | 3.0 (38%, 36%) | 0.02 |
  | `agent-league4-kl02` | 36.7% | 0.02 | 4.3k / 13.3k | 3.9 (35%, 31%) | 0.04 |
  | `agent-league5-base`, 127.0M | 39.3% | 0.02 | 4.5k / 12.9k | 3.9 (43%, 41%) | 0.02 |
  | `agent-league5-base`, 131.0M | 40.9% | 0.06 | 5.1k / 13.1k | 4.0 (36%, 32%) | 0.01 |
  | `agent-league6`, 145.1M (`best.zip`) | **47.5%** | 0.09 | 5.0k / 11.9k | 4.0 (39%, 36%) | 0.03 |
  | `agent-league6`, 147.1M | 46.8% | 0.03 | 4.8k / 11.7k | 4.5 (34%, 32%) | 0.02 |
  | `agent-league7`, 157.2M (`best.zip`) | 49.9% | 0.08 | 5.0k / 10.9k | 4.7 (44%, 39%) | 0.03 |
  | `agent-league7`, 165.2M | **54.1%** | 0.05 | 4.9k / 9.9k | 4.0 (48%, 45%) | 0 |
  | `agent-league7-distill`, 165.2M | 48.8% | 0.02 | 5.1k / 11.2k | 4.3 (42%, 39%) | 0 |
  | `agent-league8`, 169.3M (`best.zip`) | 50.7% | 0.08 | 5.0k / 11.1k | 4.5 (39%, 37%) | 0.01 |
  | `agent-league8`, 177.3M | 46.0% | 0.03 | 5.0k / 12.4k | 5.0 (30%, 26%) | 0.03 |
  | `agent-league8-kanna6`, 163.2M (`best.zip`) | 46.9% | 0.06 | 4.4k / 10.5k | 3.9 (39%, 36%) | 0.01 |
  | `agent-league8-kanna6`, 177.3M | 51.2% | 0.05 | 4.5k / 9.7k | 4.5 (45%, 40%) | 0.02 |

  Each league took more of her, without throwing. It met her in one CPU match in 23;
  with a quarter of them (`finetune.py --cpu-focus kanna:0.25`, round 6) it took 8
  points more, won a round in one match in ten, and its last checkpoint won its first
  match against her (1 of 21 in the tiers evaluation). With 40% (round 7) its last
  checkpoint took 54.1% of her HP a round and again won 1 of 21, never throwing; the gain
  is its guard, not its damage (taken 9.9k a minute, from 11.9k; dealt 4.9k, as before),
  so its rounds last longer, and its reversals counter-hit her 45% of the time (36%).

  *Where her damage comes from* (7 November; `kanna_study.py`, 64 matches each,
  `eval/kanna-study/`; her moves by src/efz.h's `CKanna` names; a rerun moves the
  shares by a few points). `agent-league6`'s best loses 12.4k HP a minute (127.0M
  12.7k, the clone 19.0k):
  - Her **236C**, an invincible beam (startup 7, reach 468) that costs 500 of her RF
    gauge, starts 20% of the damage of her combos (2.3k a minute; 127.0M 24%, the clone
    5%); 88% of them come while the agent is in a move of its own, and 76% hit. It is
    her answer to a move (a tick's 0.1% chance while the opponent is in one, more after
    her RG and on her neutral roll), and only while her RF gauge is red or cyan, which
    the agent sees (`opp_rf_gauge`): 57% of the time. The agent starts more moves then
    (38.3 a minute against 21.0): its pressure fills her gauge as she guards.
  - Her jump attacks (j.B, j.C) start 16% and hit 59% and 39% of the time; her 2A
    (startup 4) 12%.
  - It beats her attacks by overriding them, not by punishing misses (she rarely
    misses): of her 236A/B 28% are hit out before they can hit, 5% punished after; of
    her 2B 30% and 5%; her 236C almost never (1% and 4%).
  - Its reversals (4.0 a minute) counter-hit her 32% of the time (40% against her
    236A/B, startup 11, reach 340, her most common attack); but a third come while she
    isn't attacking (27% counter-hits, 12% punished), and against her 41236A/B (a
    99-hit shot) 54% are punished. A counter-hit leads to 785 HP on average, under its
    usual combo on her (934; the 90th percentile 1.8k): the big combo after the
    override is the short part. Nor does it spend for damage: with one to three bars of
    power its combos on her average 816-1,023 (799 with none), and it Instant Charges in
    0.4% of them (people 16.5%).
  - None of her normals or specials starts slowly enough to be beaten on sight (4-16
    steps; a reversal needs 17 after the 14-step reaction), so overriding her is a read
    of when she will act. Her routine has a rhythm: no neutral attack for 180 ticks
    after she was last hit, guarding or knocked down (`m_cpuHitCooldown`), then a roll
    each tick by distance. The agent sees the game 14 steps late and keeps 16 steps of
    its own inputs, too little to count 180 ticks, but the rhythm predicts less than it
    seems: 42% of her attacks (out of her combos) and 55% of the damage come inside the
    lock, from the routines it doesn't gate (anti-airs, answers to an RG or a move),
    and of those after it 77% come more than 120 steps after it ended. What it would
    tell the agent: its reversals inside the lock counter-hit her 24% of the time,
    after it 38%.

  *Bigger combos* (the user's other half). The same agent with the fair built-in routes
  at play time (`evaluate.py --p1-assist`: once it sees its hit, people's library
  combos are tried on copies and the best played) takes **58.8%** of her HP a round and
  won 4 of 64 matches (0.31 rounds a match; combos 1,180 on average, 2,618 at the 90th
  percentile, Instant Charge in 17%; throws 0.07 a minute). Damage per hit, more than
  the neutral, stands between it and her. Trained with routes before (`--assist`), a
  third of its steps were the routes', left out of the policy's loss, and its own
  combos faded; `finetune.py --assist-distill` makes them targets instead (after each
  update, the cross-entropy toward the routes' actions on their steps).

  *Combos by victim* (the user's: some combos hold only on certain characters or take
  another rhythm, and on Ayu, Mayu, Sayuri, Unknown and Kano they drop more easily;
  `combo_victims.py`, `combo_victims.json`). People's Ayu lands its shortest combos on
  Akiko, Sayuri, Ayu and Mayu (5.8-6.1 hits, 1,298-1,433 HP, against 6.5-8.9 hits
  elsewhere); with Akane, Nagamori and Mishio they are also the ones teched out of most
  (16-28% end in an air recovery, the rest 6-16%). Unknown is in the middle, and Kano's
  sample is small (412 hits) and long. The agent combos about the same on everyone (4-5
  hits, 1,220-1,470 HP against each level-4 CPU, 8 matches each:
  `eval/combo-victims-league6-best.json`), except Kanna: 41% of its hits on her go on
  to a combo (59-87% on the others) and 24% of its combos on her end with her teching
  out (0-7%). People's library has no combos on her (11 hits in the dataset) and few on
  Ayu, Kano and Unknown among its 300 most damaging (3, 7, 9), so a planner tried mostly
  combos landed on others. `combo_library.py --per-victim 40` also keeps each victim's
  40 most damaging (of 1,500 HP or more; 848 combos), and `redteam.Planner` tries the
  ones landed on the character it faces first. Round 6's best with routes, 64 matches
  each:

  | Routes | Kano 3 | Unknown 4 | Kanna's HP a round | Its combos on Kanna |
  |---|---|---|---|---|
  | none (its own combos) | 64% | 98% | 47.5% | 934 / 1,791 |
  | the 300 most damaging | 48% | 81% | 58.8% | 1,180 / 2,618 |
  | kept per victim | **66%** | 89% | 58.2% | 1,280 / 2,866 |

  The routes' cost against the exploiters was mostly combos landed on others: kept per
  victim they beat its own play against Kano's third. On Kanna nothing changes, as
  there are no people's combos on her to keep (4 matches won with the old library, none
  with the new: within 64 matches' noise). Round 7's best with the routes kept per
  victim takes **60.1%** of her HP a round and won 3 of 64 matches (0.28 rounds a match;
  its own play 49.9% and none), throwing 0.06 times a minute; against Kano's sixth and
  seventh they cost it 10 and 9 points (56% and 41%), as before: a route deals more a
  combo, but the agent lands fewer.

  *Routes learnt* (round 7, `agent-league7-distill`: `agent-league7` with the routes kept
  per victim played in the CPU's matches, `--assist-where cpu`, and learnt,
  `--assist-distill 1`). It learnt them (it chose the route's action on 90% of their
  steps at first, 94% at the end) and lost: after its first 2M steps it won 17% of its
  evaluation against the exploiters (83% before), and on 64 matches at the end 35% over
  the sixteen (`agent-league7` 82%). Its own combos got smaller (808 HP against the
  exploiters, 785 against the CPU; the plain arm 1,045 and 999), with Instant Charge in
  9% of them (the plain arm 0.4%, people 16.5%); it jumps 13.1 times a minute against the
  exploiters (9.0) and is hit in the air twice as often: what the routes do (jump
  cancels, long strings) spread to its neutral. On Kanna 48.8% (54.1%). The weight was
  too much: each rollout (16,384 steps) took 6 PPO steps and 4 full steps of
  cross-entropy toward the routes, which all pull one way, from the 9% of its steps the
  routes played. A tenth of the weight (round 8, `agent-league8-distill01`:
  `--assist-distill 0.1`, Kanna in 40% of the CPU matches, otherwise round 8's plain arm,
  its control) did not collapse but went the same way: it kept the routes (91% agreement)
  and its evaluation score (the exploiters' and the CPU's wins) fell from 0.85 to
  0.57-0.68 (the control 0.80-0.88), so no checkpoint beat its start and `best.zip` is
  `agent-league7`'s. At the end,
  on 64 matches: 60% over the twenty exploiters (the control 85%; Kano's sixth and
  seventh 9% and 3%), the level-4 CPU's hard tier 67%, Kanna 49.4% (the control 46.0%).
  Its own combos 873 HP against the CPU, 844 against Kano's sixth (the control 1,024 and
  1,118), Instant Charge in 3%, 2.3 presses a second (1.7), 16.6 jumps a minute against
  Kano's sixth. That makes three times that routes trained in cost the agent its own play
  (round 5's `--assist`, and these two); at play time they stay an option.

  *Routes against Kanna only* (`evaluate.py --assist-victims kanna`,
  `redteam.Planner(victims=...)`: the planner plans only against the characters named,
  as a person keeps routes for the characters they hold on, and the agent plays its own
  combos against the rest). Round 7's best so takes **58.8%** of Kanna's HP a round and
  won 2 of 64 (combos 1,128 / 2,456, Instant Charge in 8%, throws 0.02 a minute), and
  against Kano's sixth makes no plans and wins 70% (its own play 66%, the routes on
  everyone 56%): Kanna's gain without Kano's cost. That is the agent to play against
  her: `agent-league7/best.zip` with `--p1-assist combo-library-victims.npz
  --assist-victims kanna`.

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
pull of 0.05 toward the clone, from 0.1) continued `agent-league` against all four, to
70.5M steps. On the same seeds (`<run>/compare/`; 64 matches against each exploiter, 63
against the CPU):

| Agent | Level-4 CPU: Kanna / Ayu, Mishio / the rest | Mizuka 1 | Mizuka 2 | Kano 1 | Kano 2 | Guards a minute (CPU) |
|---|---|---|---|---|---|---|
| `agent-league`, 50.4M | 0% / 67% / 86% | 69% | 23% | 19% | 19% | 9.6 |
| `agent-league2` (share 0.6) | 0% / 62% / 86% | 69% | 61% | 25% | 38% | 8.4 |
| `agent-league2-kl` (pull 0.05) | 0% / 62% / 90% | **84%** | **75%** | **59%** | **62%** | 6.2 |

The weaker pull closes Kano's hole (she was beaten 19% of the time), and the second
Mizuka's; more of the exploiters' matches alone does much less. What it costs: it guards
the CPU 6.2 times a minute (people 11.7 against people), its other rates as before
(presses 1.66 a second, jumps 13.7 a minute, combos 820 / 1,650 at the 90th percentile;
KL to the clone 0.071, from 0.04). These are the exploiters it trained against: a third
round of exploiters is what would say whether it is robust or only knows these four.

**Round 3.** Fresh exploiters against `agent-league2-kl` (`target3.zip`): Kano's beat it
94% after 3M steps (her round-2 one needed 1M against `agent-league`), with the old hole
(on 64 matches the agent wins 12%: 20 jumps a minute, hit in the air 3.3); Mizuka's needed
9.1M. `agent-league3` continued `agent-league2-kl` against five exploiters (Kano's third
added) to 90.7M:

| Agent | Level-4 CPU | Mizuka 1 / 2 / 3 | Kano 1 / 2 / 3 |
|---|---|---|---|
| `agent-league2-kl`, 70.5M | 0% / 62% / 90% | 84% / 75% / 53% | 59% / 62% / 12% |
| `agent-league3`, 90.7M | 0% / 62% / 95% | 89% / 84% / **78%** | 67% / 61% / **12%** |

It improved against Mizuka's third, which it never met (53% to 78%), but not against
Kano's third, which it trained against (3-31% by chunk throughout; PFSP gave her 6 of the
13 exploiter matches, some 2M steps). People's Ayu jumps more against Kano than against
anyone (21.5 a minute, hit in the air 2.9): the agent's 20 is people's habit, and an
exploiter with better anti-airs than any person farms it. Closing it means jumping less
than people do.

**Round 4.** The user's rule from here: people's statistics are a guide, human limits
(the 14-step reaction time, input rates a person can make) the hard line. Two arms from
`agent-league3` against all six exploiters (Mizuka's third added), to 110.7M:

| Agent | Level-4 CPU | Mizuka 1 / 2 / 3 | Kano 1 / 2 / 3 | Presses a second |
|---|---|---|---|---|
| `agent-league3`, 90.7M | 0% / 62% / 95% | 89% / 84% / 78% | 67% / 61% / 12% | 1.77 |
| `agent-league4` (pull 0.05) | 0% / 81% / 100% | 80% / 70% / 61% | 41% / 59% / 14% | 1.64 |
| `agent-league4-kl02` (pull 0.02) | 0% / 81% / 100% | 91% / 88% / 95% | 83% / 83% / **41%** | 1.79 |

The weaker pull is the better agent everywhere. Against Kano's third it jumps 12.9 times a
minute (17.9 with 0.05; people's Ayu 21.5 against Kano) and is hit in the air 2.1 (3.2):
it learnt the opponent's anti-air, away from people's habit. Its input rates stay a
person's (1.79 presses a second, 45% of them while it can't move: buffered cancels).

**Built-in combos** (the user's idea, after Hisoutensoku's scripted AIs; `combo_support.py`).
Practice among matches (`finetune.py --practice`, from the agent's own first hits) didn't
help: at the match's reward scale nothing changed, at ten times it lost matches. Routes
did: once the agent sees its hit (14 steps late: "strong but fair", the user's choice),
people's library combos with the move that hit and its own play are tried on copies and
the best is played (`FairAssist`). `finetune.py --assist` trains with it, the routes' steps
left out of the policy's loss (`AssistMask`), so its critic learns what a hit is worth.
Against `agent-league3` (same settings, 90.7M; 63 matches against the CPU, 64 against each
exploiter):

| Agent | Level-4 CPU | Mizuka 2 / 3 | Kano 2 / 3 | Combos against the CPU | IC |
|---|---|---|---|---|---|
| `agent-league3`, no routes | 0% / 62% / 95% | 84% / 78% | 61% / 12% | 859 / 1,707 / 4,241 | 0.8% |
| the same, routes at play time | 0% / 81% / 100% | 92% / 69% | 59% / 22% | 1,070 / 2,352 / 4,610 | 18% |
| `agent-league3-assist`, trained with them | 0% / 90% / 100% | 67% / 83% | 75% / 31% | 1,078 / 2,534 / 4,534 | 25% |
| people (against people) | | | | 970 / 2,357 / 7,421 | 16.5% |

Fair routes make its combos people's (the 90th percentile and IC as theirs; the most,
people's 3-bar cyan combos, not yet), and the middle tier of the level-4 CPU 81-90%
(62%). Training with them adds a little against the CPU and Kano, less against Mizuka 2;
`agent-league4-kl02` (no routes, the weaker pull) is better against the exploiters than
either, so the next league has both.

**Round 5.** Round-4 exploiters against `agent-league4-kl02` (Kano's beat it after 3M
steps, Mizuka's after 12.2M) joined the league; `agent-league5` continued `kl02` with the
routes trained in (`--assist`) against all eight, to 131.0M. On 64 matches each (63
against the CPU), `<run>/compare/{<run>,assisted,value}-*.json`:

| Agent | Level-4 CPU | Mizuka 1 / 2 / 3 / 4 | Kano 1 / 2 / 3 / 4 | Combos (CPU), IC |
|---|---|---|---|---|
| `kl02`, its own combos | 0% / 81% / 100% | 91% / 88% / 95% / 38% | 83% / 83% / 41% / 36% | 915, 0% |
| `kl02`, routes at play time | 0% / 76% / 100% | 95% / 84% / 86% / 25% | 69% / 92% / 28% / 36% | 1,084, 17% |
| `kl02`, routes chosen by value | 0% / 81% / 95% | 94% / 75% / 92% / 30% | 72% / 88% / 30% / 30% | 1,006, 12% |
| `agent-league5`, its own combos | 0% / 57% / 95% | 84% / 52% / 58% / 33% | 14% / 41% / 2% / 0% | 688, 1% |
| `agent-league5`, routes (as trained) | 0% / 90% / 100% | 94% / 80% / 80% / 38% | 59% / 70% / 19% / 28% | 1,114, 23% |

Routes no longer help. `kl02` had learnt combos of its own that are worth as much a
minute: a route deals more per combo (1,084 to 915) but takes longer, so it lands fewer
(9.5 a minute against Kano 1, from 11.8), and the damage a minute is the same or less.
Over the eight exploiters it wins 69% on its own, 64% with routes. Choosing the route by
its worth to the agent (`--assist-score value`: the damage plus the critic's value of the
game the route left, discounted by its length; `redteam.Planner(score='value')`) instead
of its damage changes a different choice in more than half the plans but not the result.
Trained with routes, `agent-league5` lost its own combos (the routes' steps are out of
the policy's loss) and is no better with them than `kl02` without; it jumps 17-18 times
a minute against Kano (`kl02` 11-13), the old hole. What improved is its guard against
Mizuka 4 (damage taken 10.4k a minute, `kl02` 14.8k). `finetune.py --vs-assist` plays an
agent trained with routes as an exploiter's opponent with them
(`combo_support.FairAssistOpponent`).

The control, `agent-league5-base` (the same without routes), is the better agent:

| Agent | Level-4 CPU | Mizuka 1 / 2 / 3 / 4 | Kano 1 / 2 / 3 / 4 | Exploiters | Presses a second |
|---|---|---|---|---|---|
| `kl02`, 110.9M | 0% / 81% / 100% | 91% / 88% / 95% / 38% | 83% / 83% / 41% / 36% | 69% | 1.79 |
| `agent-league5-base`, 127.0M (`chunk008`, `best.zip`) | 0% / 95% / 100% | 98% / 95% / 100% / **94%** | 95% / 98% / **66%** / **59%** | **88%** | 1.64 |
| `agent-league5-base`, 131.0M | 0% / 90% / 100% | 98% / 97% / 81% / 70% | 77% / 80% / 28% / 45% | 72% | 1.65 |

Two chunks later it is back to 72%: PFSP moves the matches away from the exploiters it
beats and it forgets them (Kano 3 by chunk: 6, 56, 50, 25, 38, 50, 31, 44, 38, 25%). The
127.0M checkpoint, picked by its 16-match evaluation and confirmed on 64, is the target of
round 5 (`kano/target5.zip`, `mizukab/target5.zip`, `misuzu/target.zip`). It jumps 13-16
times a minute against Kano, guards the CPU 6.5 times a minute (people 11.7) and presses as
a person does (48% of its presses while it can't move: buffered).

**Round 5's exploiters**, against 127.0M: Kano's fifth stopped at 66% after 4.1M steps
(32 matches; 58% on 64), her third's and fourth's play, no new hole. Mizuka's fifth
(24.4M steps) and the first exploiters of Misuzu and Mishio (from clones of people's
Misuzu, 2,651 sides, and Mishio, 2,609; 24M steps each) never beat it (at most 12%, 16%
and 19% of their evaluations).

**Round 6** (`agent-league6`): from 127.0M, 20M steps against all twelve, PFSP over the
last three evaluations (`--pfsp-window 3`), Kanna in a quarter of the CPU matches, the
best checkpoint kept by its evaluation (the mean of the exploiters' and the CPU's wins:
`best.zip`). 64 matches each (63 against the CPU):

| Agent | Level-4 CPU | Kano 1 / 2 / 3 / 4 / 5 | Mizuka 1 / 2 / 3 / 4 / 5 | Misuzu / Mishio | 12 exploiters | Kanna's HP a round |
|---|---|---|---|---|---|---|
| `agent-league5-base`, 127.0M | 0% / 95% / 100% | 95 / 98 / 66 / 59 / 42% | 98 / 95 / 100 / 94 / 97% | 98 / 97% | 87% | 39.3% |
| `agent-league6`, 145.1M (`best.zip`) | 0% / 86% / 100% | 97 / 100 / 64 / 72 / **62%** | 100 / 100 / 97 / 98 / 100% | 91 / 97% | **90%** | **47.5%** |
| `agent-league6`, 147.1M | 5% / 81% / 100% | 88 / 94 / 53 / 77 / 50% | 98 / 97 / 98 / 89 / 100% | 98 / 97% | 87% | 46.8% |

Keeping the best worked: the last checkpoint slipped back against Kano (PFSP's
forgetting), the best kept its gains. Against the middle tier it lost 9 points (Ayu's
CPU 8 of 11, from 10: few matches, to watch). The best is round 7's target
(`kano/target6.zip`, `mizukab/target6.zip`, `misuzu/target2.zip`, `mishio/target2.zip`).

**Round 7's exploiters**, against 145.1M: Kano's sixth stopped at 88% after 11.2M steps
and won 67% on 64 matches (the target jumps 15.4 times a minute against it and is hit in
the air 3.8: the anti-air hole again). Mishio's second reached 53% (22.3M steps; 22% on
64), Misuzu's second 28% (5%), Unknown's sixth 16% (0%).

**Round 7** (`agent-league7`): from 145.1M, 20M steps against all sixteen (the new four
at their best checkpoints), Kanna in 40% of the CPU matches; a second arm also learnt
the routes (`agent-league7-distill`, above). 64 matches each (63 against the CPU):

| Agent | Level-4 CPU | Kano 1-6 | Mizuka 1-6 | Misuzu 1 / 2, Mishio 1 / 2 | 12 old | 16 | Kanna's HP |
|---|---|---|---|---|---|---|---|
| `agent-league6`, 145.1M (`best.zip`) | 0% / 86% / 100% | 97 / 100 / 64 / 72 / 62 / 33% | 100 / 100 / 97 / 98 / 100 / 100% | 91 / 95, 97 / 78% | 90% | 87% | 47.5% |
| `agent-league7`, 157.2M (`best.zip`) | 0% / **100%** / 100% | 98 / 97 / 77 / 83 / 70 / **66%** | 100 / 100 / 100 / 88 / 100 / 95% | 98 / 98, 98 / 91% | **92%** | **91%** | 49.9% |
| `agent-league7`, 165.2M | 5% / 86% / 100% | 95 / 98 / 78 / 80 / 48 / 30% | 97 / 88 / 98 / 50 / 100 / 92% | 94 / 97, 95 / 72% | 85% | 82% | **54.1%** |
| `agent-league7-distill`, 165.2M | 0% / 62% / 71% | 52 / 67 / 16 / 19 / 9 / 2% | 70 / 33 / 67 / 3 / 70 / 41% | 25 / 36, 48 / 8% | 40% | 35% | 48.8% |

The best checkpoint closed Kano's sixth by its anti-air read, not by jumping less: hit
in the air 1.7 times a minute (3.8), jumping 14.1 (15.4), damage taken 7.9k a minute
(10.3k); and it won all the CPU's middle tier. The last checkpoint forgot Kano's sixth
again (30%), as round 6's last did, while it took the most of Kanna yet. The best is
round 8's target (`kano/target7.zip`, `mizukab/target7.zip`, `misuzu/target3.zip`,
`mishio/target3.zip`). Round 7 had 16 matches for its 16 exploiters (half of the 32
against agents), so PFSP, which shares only the matches beyond one each, did nothing
(round 6: 16 for 12); `vs_counts` now refuses fewer matches than opponents.

**Round 8's exploiters**, against 157.2M: Kano's seventh stopped at 75% after 14.2M
steps and won 50% on 64 matches, with no jumping hole (the target is hit in the air 1.0
times a minute): a guard-heavy game (16.6 guards a minute, 2.0 presses a second) that
trades damage even. Mishio's third won 27%, Unknown's seventh 16%, Misuzu's third 12%
(24.4M steps each). Round 8 (`agent-league8`) meets all twenty, 24 matches for them
(`--vs-share 0.75`), Kanna in 40% of the CPU matches; `agent-league8-kanna6` in 60%.

**Round 8** (`agent-league8`, `agent-league8-kanna6`): from 157.2M, 20M steps. 64 matches
each (63 against the CPU); the twenty exploiters' mean, and the sixteen before round 8's:

| Agent | Level-4 CPU | Kano 6 / 7 | Mizuka 7 | Misuzu 3 | Mishio 3 | 16 old | 20 | Kanna's HP |
|---|---|---|---|---|---|---|---|---|
| `agent-league7`, 157.2M (`best.zip`) | 0% / 100% / 100% | **66 / 50%** | 84% | 88% | 73% | **91%** | **88%** | 49.9% |
| `agent-league8`, 169.3M (`best.zip`) | 0% / 100% / 100% | 33 / 39% | 95% | 92% | **95%** | 88% | 86% | 50.7% |
| `agent-league8`, 177.3M | 0% / 90% / 100% | 53 / 34% | **98%** | 88% | 97% | 86% | 85% | 46.0% |
| `agent-league8-kanna6`, 163.2M (`best.zip`) | 0% / 90% / 100% | 55 / 38% | 83% | 88% | 91% | 89% | 86% | 46.9% |
| `agent-league8-kanna6`, 177.3M | 0% / 90% / 100% | 45 / 23% | 69% | 80% | 69% | 83% | 79% | 51.2% |
| `agent-league8-distill01`, 177.3M | 0% / 67% / 95% | 9 / 3% | 36% | 62% | 66% | 65% | 60% | 49.4% |

No step forward. Round 8 learnt the new Mizuka and Mishio and lost Kano: its best jumps
19.6 times a minute against Kano's sixth and is hit in the air 4.8 times (157.2M: 14.1
and 1.7), the hole round 7 had closed. Its best checkpoint was picked by 16-match
evaluations (Kano's sixth 62% there, 33% on 64): with 21 opponents and 11 checkpoints,
the best of noisy evaluations. Kanna in 60% of the CPU matches took no more of her (Kanna's HP
46.9-51.2% against 46.0-50.7%; 64 matches tell apart about 4 points) and lost more to
the exploiters. The routes learnt at a tenth of the weight (`agent-league8-distill01`,
above under Kanna) lost to every exploiter more. `agent-league7`'s best stays the best
agent.

**Round 10's exploiters: reversals** (the user, playing round 8's: "a wake-up invincible,
or an RG and an invincible during it"). `finetune.py --focus reversal` (`focus.py`: an
invincible attack within 8 steps of rising or 20 of a recoil guard that hits first,
weighted 0.05), against 157.2M: Ayu's (`ayu/reversal`, from her clone; 623C is
invincible from its 2nd step) and Mishio's (`mishio/reversal`), 24.4M steps each, neither
reaching the 60% stop. Round 7's best beats them 97% and 81% on 64 matches: they learnt
the answer and little else. They rise with an invincible move at 22% and 17% of its
wake-up attacks (people's clones 4-11%, the exploiters before them 0%) and it hits
first 44% and 67% of the time; when they reverse, its meaty is worth -416 and -278 HP
over the next 3 seconds, when they guard +587 and +418.

**Round 10** (`agent-league10-kanna`; the user's rule from here: no level-4 CPU but
Kanna, since the CPU's guard can't be mixed up, `--cpu-focus kanna:1 --cpu-chars kanna`,
`best.zip` by the share of her HP taken): from 157.2M, 20M steps, round 8's settings
otherwise (the twenty exploiters, `--vs-share 0.75`). 64 matches each (63 against the
CPU's tiers, measured only):

| Agent | Level-4 CPU | Kano 5 / 6 / 7 | Mizuka 7 | Misuzu 3 | Mishio 3 | 20 | Ayu / Mishio reversal | Kanna's HP |
|---|---|---|---|---|---|---|---|---|
| `agent-league7`, 157.2M (`best.zip`) | 0% / 100% / 100% | **70 / 66 / 50%** | 84% | 88% | 73% | **88%** | **97 / 81%** | 49.9% |
| `agent-league8`, 169.3M (`best.zip`) | 0% / 100% / 100% | 67 / 33 / 39% | **95%** | **92%** | **95%** | 86% | | 50.7% |
| `agent-league10-kanna`, 165.2M (`best.zip`) | 0% / 90% / 100% | 61 / 55 / 31% | 86% | 67% | 86% | 84% | 89 / 81% | 46.7% |
| `agent-league10-kanna`, 177.3M | 0% / 90% / 95% | 14 / 22 / 20% | 88% | 89% | 80% | 75% | 81 / 69% | 48.4% |

No better, and no nearer Kanna (46.7-48.4% of her HP, a round in 3-6% of the matches;
round 7's best 49.9%, 8%). Its best is within the noise of round 7's (a second draw of
both, below under "What is overfitted": 86% and 86%), its last checkpoint clearly worse. It lost Kano as round 8 did: against her fifth to seventh it
jumps 16-19 times a minute and is hit in the air 1.9-2.8 times (round 7's best 12-14
and 0.9-1.7). Its habits barely moved (below, under "What is overfitted"), and the
reversals hurt it more: against its last checkpoint they hit first 72% and 84% of the
time (round 7's 44% and 67%). `agent-league7`'s best stays the best agent. Round 11
(`agent-league11`, and `agent-league11-pull05` at the pull 0.05) goes on from round 10's
best against the twenty and both reversal exploiters.

## Ayu's agent as other characters

What it learnt for Ayu and what any character keeps (8 November; `eval/transfer/`): the
best agent (`agent-league7`, 157.2M) and Ayu's clone (`bc-d14`) played as eight other
characters, and those characters' own clones and exploiters as references, 63 matches
each against the level-4 CPU's tiers (`evaluate.py --chars X tiers`). The obs carry
the character it plays, which the agent only ever saw as Ayu; the actions are the same
45 inputs for everyone.

| As Ayu / as the others (mean of 8) | Ayu's clone | The agent | Own clones (4) | Exploiters (4) | Carried over |
|---|---|---|---|---|---|
| CPU's HP taken a round | 32% / 26% | 82% / 36% | 42% | 64% | 21% |
| Jumps a minute | 18.8 / 31.3 | 7.8 / 14.1 | 15.1 | 11.8 | all |
| Hit in the air a minute | 3.2 / 6.8 | 0.7 / 1.5 | 2.4 | 1.9 | all |
| Air recoil guard | 9% / 5% | 12% / 10% | 9% | 7% | all |
| Combos a minute | 5.5 / 4.2 | 10.3 / 6.8 | 6.3 | 8.8 | 55% |
| Combo damage | 539 / 547 | 1,000 / 632 | 582 | 687 | 18% |
| Reversals a minute | 0.9 / 1.3 | 4.2 / 2.5 | 1.1 | 0.8 | 35% |
| Guards a minute (ground) | 16.0 / 4.6 | 8.4 / 16.2 | 18.9 | 14.3 | - |
| Hit on the ground a minute | 10.5 / 6.6 | 8.7 / 16.7 | 10.7 | 9.4 | none |
| Damage taken a minute | 9.2k / 8.7k | 8.0k / 11.9k | 8.7k | 8.2k | none |
| Presses a second | 1.18 / 2.01 | 1.44 / 0.87 | 1.29 | 1.72 | - |

(Carried over: the agent's gain over Ayu's clone as the others, as a share of its gain
as Ayu.) As another character it wins almost nothing (0-10% of the easiest tier; Ayu's
clone 0%, the others' clones up to 19%), but it takes more of the CPU than Ayu's clone
there, as much as their own clones as Mishio, Sayuri and Nanase (40-52%).

- **General** (any character keeps it): staying on the ground against anti-airs and not
  being hit in the air (the lesson of Kano's exploiters), recoil-guarding in the air,
  turning hits into combos more often, and putting out invincible moves (2.5 a minute,
  their clones 1.1).
- **Ayu's**: the damage of its combos (her routes) and its ground defence. As the others
  it guards twice as often and is hit twice as often (16.7 a minute, its own clones 10.7),
  taking more than any clone. Most likely holding guard was safe for Ayu because of her
  ways out (a reversal that starts in 2 steps, her spacing), which other characters'
  frame data don't give it, and it presses too little (0.87 a second) to make its own. Its CPU wins as Ayu (100% of the middle tier) are all hers.

The exploiters, trained for 14-24M steps as their character against the agent and a
quarter against the level-3 CPU, beat the level-4 CPU's middle tier 14-81% and take 58-72%
of it: a run per character learns its character fast; the Ayu agent's general habits
are a smaller part of its strength than its character's.

`kano/transfer7`, `mizukab/transfer7`: Kano and Mizuka trained from the Ayu agent
instead of their clones, round 8's exploiter recipe otherwise (their target
`agent-league7`, their clone as the prior), against `kano/exploiter7` and
`mizukab/exploiter7`: whether Ayu's agent is a better start for a character than
people's play of it. Per 1M-step chunk, its 32-match evaluation (a single run each):

| | beats its target 60% | most vs target | level-3 CPU: most / last |
|---|---|---|---|
| Kano from the Ayu agent | 7.1M | 69% | 38% / 28% |
| Kano from its clone (`exploiter7`) | 14.2M | 75% | 78% / 59% |
| Mizuka from the Ayu agent | not in 24M | 38% | 59% / 59% |
| Mizuka from its clone (`exploiter7`) | not in 24M | 34% | 62% / 53% |

Started from the Ayu agent, Kano found the agent's holes in half the steps, but
played the CPU far worse throughout (3% in its first chunk, at most 38%). What it brings is knowing
the agent, its own line's habits, not playing Kano. Mizuka gained nothing either way: about the clone's numbers on
both. A character's sparring partner is better started from people's play of it; the
Ayu agent's start is worth it only to hunt the agent itself.

## What is overfitted

The best agent (`agent-league7`, 157.2M) under changed conditions, 63-64 matches each
(`eval/overfit/`, `evaluate.py --seed`, `--p1-delay`):

- **Its reaction time, most of all.** It trained seeing the game 14 steps late; seeing
  it earlier, which gives it more, makes it worse, as does later:

  | Steps late | 8 | 11 | **14** | 17 | 20 |
  |---|---|---|---|---|---|
  | Level-4 CPU (tiers) | 51% (0/62/90%) | 60% | **67%** (0/100/100%) | 52% | 46% |
  | Kano's sixth | 23% | 52% | **66%** | 16% | 0% |
  | Its combos on the CPU | 781 | 941 | **1,000** | 762 | 670 |

  Its play, combos most, is timed against the lag itself: it continues a combo by the
  step it sees the hit, and its anti-air reads by when it sees the jump. A person who
  reacts faster plays better; it plays worse. People's reaction times vary from moment to
  moment, and the training's delay doesn't. A delay drawn per match or per moment
  (14-20 steps, the human limit and slower) should make it hold up and drop fewer combos.
  Round 9, `agent-league9-jitter`, tried it: round 8's settings (Kanna in 40% of the CPU
  matches) with each player's delay drawn per match from 14-20 steps (`finetune.py
  --delay-most 20`), 20M steps from round 7's best. Its evaluations, at 14 steps, never
  beat its start (0.63-0.82 against 0.854), so its `best.zip` is round 7's own; its last
  checkpoint (`model.zip`, 177.3M):

  | Steps late | 8 | 11 | **14** | 17 | 20 |
  |---|---|---|---|---|---|
  | Level-4 CPU (tiers) | 52% | 57% | 59% (0/76/100%) | 59% | 52% |
  | Kano's sixth | 12% | 25% | 36% | 22% | 11% |
  | Its combos on the CPU | 812 | 901 | 960 | 915 | 813 |

  Flatter: at 17 and 20 steps, the slower people it may meet, it holds better than
  round 7's best (the CPU 59% and 52% against 52% and 46%, its combos 915 and 813
  against 762 and 670, Kano's sixth 22% and 11% against 16% and 0%), and worse at 14.
  Round 8's best, its control, also lost Kano's sixth at 14 (33%, the CPU 67%), so most
  of that is the round's, not the delay's; faster than 14, never trained, it is no
  better. A reaction time that varies works, at a price where the league itself lost.
- **The evaluation seed: noise, not a bias.** Its best checkpoints were picked on
  evaluations of seed 7 (`finetune.py`'s, and `evaluate.py`'s default) and measured on
  seed 7: on seeds 11 and 23 the CPU's middle tier 90% and 81% (100%), Unknown's fourth
  80% and 81% (88%), Kano's sixth 58% and 84% (66%), Kano's seventh 56% and 44% (50%).
  But until 9 November the seed fixed the game only: the agents draw their actions at
  random (SB3's `predict`, torch's generator), and that draw wasn't seeded, so the same
  64 matches played again were another sample. Round 7's best again against the
  twenty: Kano's seventh 39% (50%), fifth 59% (70%), Mishio's third 86% (73%), the
  mean 86% (88%). Seed 7 flattered nothing; any one opponent's win on 64 matches is
  good to about ±12 points (95%, at 50%), the mean of twenty to about ±2. `evaluate.play`
  now seeds the draw too (and gives training's generator back as it was), so a run
  repeats exactly and a different seed is a different sample.
- **The checkpoint pick:** over the exploiters, a best checkpoint's 16-match evaluation
  against its 64-match measure: round 6 90.1% / 89.8%, round 7 90.2% / 91.2%, round 8
  89.7% / 86.2%, `kanna6` 88.1% / 85.9%; the drops are on the hardest (Kano's fourth to
  sixth, up to 29 points).
- **Its wake-up attack: one option.** At the opponent's wake-up (`tactics.wakeup`: the
  move that made the first contact, how Ayu came in before it, its guard height from
  `framedata.json`'s new `guard`, and whether it struck from behind), people's Ayu
  mixes (the user's: a 2A; 66 into an air B or a 2A, up or down; flying in and dropping
  with jB, in front or behind); the agent plays a ground 2A, 2C at most, against
  everyone (64 matches each, eval/oki; people: all 12.7k of their wake-ups):

  | At the opponent's wake-up | ground low (2A) | 66 high / low | fly high / low | jump high / low | low / high in all | cross-ups | commonest |
  |---|---|---|---|---|---|---|---|
  | people's Ayu, against people | 17% | 4 / 1% | 9 / 7% | 21 / 11% | 40 / 38% | 4.1% | 19% |
  | Ayu's clone, level-4 CPU | 10% | 2 / 0% | 6 / 2% | 12 / 4% | 26 / 31% | 5.0% | 28% |
  | the first agent, level-4 CPU | 30% | 2 / 1% | 2 / 0% | 4 / 8% | 47 / 10% | 3.6% | 30% |
  | round 3's | 57% | 0 / 1% | 0 / 0% | 1 / 6% | 65 / 1% | 1.4% | 56% |
  | round 5's best | 74% | 0 / 0% | 0 / 0% | 0 / 11% | 87 / 1% | 0% | 74% |
  | round 7's best | 89% | 0 / 1% | 0 / 0% | 0 / 3% | 95 / 0% | 0.6% | 89% |
  | round 9's last (delay 14-20) | 58% (and 33% a mid) | 0 / 0% | 0 / 0% | 0 / 3% | 63 / 1% | 1.5% | 58% |
  | round 7's, against Kano's clone | 92% | 0 / 1% | 0 / 0% | 0 / 1% | 95 / 0% | 0.1% | 92% |
  | round 7's, against Kano's seventh | 92% | 0 / 1% | 0 / 0% | 0 / 2% | 96 / 0% | 0.2% | 92% |
  | round 7's, against Kanna | 76% | 0 / 1% | 0 / 0% | 0 / 0% | 82 / 1% | 0.2% | 76% |
  | round 10's last (no CPU but Kanna), level-4 CPU | 66% (and 23% a mid) | 0 / 0% | 0 / 0% | 0 / 7% | 76 / 1% | 0.9% | 66% |
  | round 10's last, against Kanna | 16% (and 76% a mid, 5B 52%) | 0 / 0% | 0 / 0% | 1 / 3% | 20 / 2% | 0.2% | 72% |
  | round 10's last, against Kano's clone | 85% | 0 / 0% | 0 / 0% | 0 / 3% | 89 / 0% | 0.1% | 85% |
  | round 10's last, against Ayu's reversal exploiter | 79% | 0 / 1% | 0 / 0% | 0 / 10% | 90 / 0% | 0.2% | 79% |

  The clone keeps people's mix against every opponent (low 19-32%, high 15-38%); each
  round of training took more of it away. The level-4 CPU can't be mixed up: when it
  guards it takes the height the attack needs as it lands (`CPlayer::HoldsGuard`,
  src/player.cpp:551-559), and it is half the agent's matches; so a high is worth no
  more than a low against it, and the fastest, safest meaty, 2A (+2 guarded), is all
  that pays. Nothing else it meets reads it either: people's clones and the exploiters
  rise as people do, and its 2A hits first 41-61% of the time against them, +317 to
  +549 HP over the next 3 seconds a wake-up (against the CPU +143), none of them
  reversing (0-6%; people's risers 11%). People's own lows pay most (against people a
  ground 2A +329, an empty jump into 2A +375, 66 into 2A +395; their highs +7 to +106),
  but their highs are what keep a riser standing for them: a person who meets a 2A
  every time guards crouching or reverses, and the agent has no way to open that.
  Overfitted to opponents that don't adapt; the fix is one that does (a riser trained
  to punish its wake-up attack, kept in the league), not a CPU that guesses: against
  any opponent that doesn't read it, one option is always the best. Round 10, with no
  CPU but Kanna, bears that out: less 2A against the CPU's tiers, but against Kanna
  one option traded for another (a 5B; both lose HP to her, -186 and -282 over the next
  3 seconds), and against everyone else the 2A as before (79-85%).
- **Its strings: one route, everywhere** (the user, playing round 8's: "2A-5B-2C-236A
  again and again, in free actions as well as combos"). `tactics.strings`: a player's
  moves one after another (each a button press made, at most 6 free steps apart), 64
  matches each (eval/strings; people: all their matches):

  | | moves a string | the 2A > 5B > f5B > 2C > 236A route | 2A, 5B, f5B, 2C, 236A of all moves | jB | anything else |
  |---|---|---|---|---|---|
  | people's Ayu | 2.06 | 2% | 34% (236A 0%) | 20% | 45% |
  | Ayu's clone, level-4 CPU | 1.37 | 0% | 38% | 16% | 48% |
  | the first agent | 1.80 | 0% | 59% | 6% | 34% |
  | round 1's | 2.03 | 9% | 68% | 6% | 27% |
  | round 5's best | 2.43 | 18% | 76% | 6% | 18% |
  | round 8's best | 2.39 | 18% | 78% | 5% | 17% |
  | round 8's, against Kano's clone | 2.89 | 23% | 79% | 9% | 11% |
  | round 8's, against Ayu's clone | 3.25 | 42% | 89% | 3% | 9% |
  | round 9's last | 2.46 | 13% | 71% | 2% | 26% |
  | round 10's last (no CPU but Kanna) | 2.40 | 21% | 77% | 5% | 18% |
  | round 10's last, against Kanna | 2.19 | 8% | 67% | 6% | 28% |
  | round 10's last, against Kano's clone | 2.70 | 29% | 84% | 4% | 11% |

  In neutral it pokes with a lone 2A (14% of its strings; 74% whiff), a jB or a 236B/C
  that whiff; when a 2A connects (a normal cancels into the next only on contact) the
  route follows, which hits 86% of the time against the CPU. People's Ayu plays the
  route almost never and 236A not at all; their offence is jumps (jB 20%, jC 12% of
  moves) and a spread of normals. Five moves went from a third of what Ayu does to
  four fifths, the pull toward people's play lowered over the rounds (0.1 in round 1,
  0.05 in round 3, 0.02 from round 5). A person reads it at once (the user: "a wake-up
  invincible, or an RG and an invincible during it"), and against the agent nothing does:
  the exploiters recoil-guard its pressure 13-15% of the time (people 36%, Mishio's
  third 32%) and follow an RG with an invincible move never (the level-4 CPU: 35% of its
  RGs, at random), and rise with one 0-6% of the time (people 11%). Exploiters trained
  for it (`focus.py --focus reversal`, Ayu's and Mishio's, round 10 above) found it at
  once: they rise with an invincible move 17-22% of the time and it hits first 44-84%
  of the time. Round 11 trains against them.
- **Out of a guard, the same 2A** (the user: "under pressure, where its 2A is not as
  fast as the opponent's"). What round 8's best starts right after a guard
  (`escape_moves`, eval/guard): its invincible 236C most (9-33% of its guards, hitting
  first 58-74% of the time), then 2A (4-39%), which is hit first more than people's:
  hit 37% of the time against the CPU, 48% against Kano's clone, 59% against Mishio's
  third (people's Ayu 28%), a quarter to a half of them pressed at a disadvantage. It
  is rarely under pressure (1.4-2.5 guards a minute; against the exploiters 5-6, people
  7.4), and against the exploiters that frame-trap it, it presses 2A less (4-9%): it
  adapts to an opponent's character, not to what this opponent did a moment ago.
  Round 10's last much the same: its 2A out of a guard hit 42% of the time against the
  CPU, 29% against Kano's clone, 61% against Mishio's third, 66% against Mishio's
  reversal exploiter (round 7's best 50%).
- **Not overfitted:** people's play it never met (the clones of Kano, Mizuka, Misuzu and
  Mishio: 100% each, 99% of their HP, taking 2.7-3.8k a minute where the same
  characters' exploiters deal 6.7-10.1k); the CPU's lower levels (100%, 100%, 81% at
  levels 1-3, so nothing is tied to level 4's patterns); and the exploiters don't
  overfit their target either: each beats the older agents as well as, or better than,
  the agent it was trained against (Kano's seventh beats round 5's best 67% and round
  6's 61%, its target 50%; Mishio's third round 6's 31%, its target 27%). Their holes
  are the lineage's, not one checkpoint's:

  | Agent \ exploiter | Kano 3 / 4 / 5 / 6 / 7 | Mizuka 7 | Misuzu 3 | Mishio 3 |
  |---|---|---|---|---|
  | `agent-league5-base`, 127.0M | 66 / 59 / 42* / 42 / 33% | 81% | 83% | 95% |
  | `agent-league6`, 145.1M | 64 / 72 / 62 / 33* / 39% | 84% | 70% | 69% |
  | `agent-league7`, 157.2M | 77 / 83 / 70 / 66 / 50*% | 84%* | 88%* | 73%* |
  | `agent-league8`, 169.3M | 72 / 70 / 67 / 33 / 39% | 95% | 92% | 95% |

  (the agent's wins; * the exploiter's own target.) Round 7's best beats every Kano
  exploiter better than the agents before it: real progress, not the last round's
  answer only.

## The models

On Hugging Face, https://huggingface.co/sakuya9t/efz, under the same paths:
`python runs/hub.py download human-ayu` (the clones, the team, the agent's checkpoints,
the combo master). The repository keeps the clones and the team too; the agent's and
the combo master's checkpoints are only there. Uploaded 8 November: every run's
`best.zip` and last `model.zip` (not the `chunk*.zip` between) through round 8, and the
exploiters of Kano (1-7), Mizuka (1-7), Misuzu (1-3) and Mishio (1-3) with their targets
(`python runs/hub.py upload human-ayu --exclude '*chunk*.zip'`). The best agent is
`agent-league7/best.zip`. Round 9 on (`agent-league9-jitter`, `agent-league10-kanna`,
`agent-league11*`, the reversal exploiters, `kano/transfer7`, `mizukab/transfer7`) are
only on the Linux machine until the next upload.

## The scripts

| Script | What |
|---|---|
| `dataset.py` | replays to data: per Ayu side, the views, inputs and rewards of each step |
| `bc.py` | the clone: the 45 actions people's inputs come to each frame, and the critic from their matches' returns; `--delay` for a reaction time, `--players` for one player's clone (from the clone of everyone, `--init`) |
| `finetune.py` | PPO from the clone, every frame, KL to it; half the matches against the level-4 CPU with any character, half Ayu's mirror against a frozen copy, the clone, the curriculum agent and the `--team` of players' clones; any character (`--char`), opponents of other characters (`--vs`, shared by `--pfsp`), a focus (`--focus`), `--stop-win` |
| `evaluate.py` | matches to the end, the share of each side's HP the other took a round (`opp_hp_taken`, where it never wins, as against Kanna; `self_hp_taken`, its own lost, where it nearly always wins: hard wins from easy ones, the user's), with how each side played (`Events`: presses, jumps, guards, recoil guards and counters, punishes after an RG, the 623 guesses, combos with their 90th percentile and most, Instant Charge, inputs while unable to move, damage taken, and `tactics.py`'s); `--chars ayu tiers` for the level-4 CPU's tiers; plays language models too (`runs/llm-ayu`) |
| `combo_victims.py` | combos by the character they land on: conversion, hits, damage, and how they ended (knockdown, air recovery, neither), for people's Ayu or an agent against each CPU character |
| `kanna_study.py` | where an agent's HP goes against the level-4 CPU's Kanna (her attacks out of her combos, by move, and the damage of the combos each started), its reversals and how they went, and her RF gauge (236C) |
| `tactics.py` | pressure (frame advantage, punishable or safe, ways out, RG), wake-up (the riser's choice, the attacker's okizeme and mix-up) and free time, both ways |
| `focus.py` | an opponent's focus as a shaping reward (`finetune.py --focus`): setups and charges in free time |
| `framedata.py` | the characters' frame data from the game's `.pat` files: startup, reach, invulnerable frames, guard height (`framedata.json`) |
| `people.py` | the same measures of people, overall, by opponent and by player |
| `compare.py` | people and agents side by side, as the tables here |
| `team_check.py` | whether players' clones predict their players better than the clone of everyone |
| `combo_starts.py` | where people's combos started, kept as a replay and a step |
| `combo.py` | the combo master: trials from those starts, rewarded for the combo's damage |
| `record_combos.py` | a combo master's most damaging combos in whole matches, as replays for EFZ's REPLAY menu, with where each combo is (`replays/combos/combos.txt`) |
