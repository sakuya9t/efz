# Training v2: a loop that learns, opponents that defend like people

Plan of 11 November 2026, after rounds 8-13 (`runs/human-ayu/README.md`) and the user's
games of 8-10 November. What was measured, what changes, how round 14 is judged. The
results go in `runs/human-ayu/README.md` ("Round 14") as each phase ends; the last
section here says where each phase stands.

## What was measured

**The rounds pick peaks, they don't learn.** In all ten arms of rounds 8-12 the mean
16-match score of the trained chunks is at or below the start's; round 11's step forward
was the 0.914 peak of a series that averaged 0.850 from a start of 0.852. Consecutive
chunks differ by 3-6 points (the evaluation's own noise is about 1.5), and the changes
against Kano's exploiters and against the rest move together (r = +0.55 over 70 chunk
pairs): the whole policy wanders. Rounds 12 and 13 (the league of 39) never passed their
start; round 11's best (`agent-league11-r7/best.zip`, 86% over the 39 on 64 seeded
matches) stays the best checkpoint.

**The average of a round's checkpoints is the better agent.** The plain mean of
`agent-league11-r7`'s ten chunks' weights wins 90.4% over the 39 on the same 64 seeded
matches (own HP lost 50% a round; round 11's best 85.6%, 53%), the 17 helpers 86.4%
(75.6%); better against 24 opponents, worse against 9 (Kano's fifth 77% from 92%, Nanase
80% from 91%). Checked in the plain game only.

**Why it wanders** (fresh rollouts from round 11's best in round 13's league: 30 rollouts
of 32,768 steps, then 12 real updates):

- The policy sits where the reward's gradient and the pull toward the clone cancel. The
  KL to the clone follows the pull in every run since round 1 (0.1: 0.04 nats a frame;
  0.05: 0.07-0.09; 0.02: 0.12-0.14) and has not moved since the pull reached 0.02.
- One rollout's policy gradient is about 99% noise (the cosine between two rollouts'
  gradients about 0.01). Updates three or more apart are uncorrelated (0.008); twelve
  moved the weights 0.86 against 0.8 for a random walk of the same steps. PPO's clip never
  binds (approximate KL 0.0004, 1% clipped): small steps in random directions.
- The mirror and CPU matches (52 of 128 environments) give 46% of the gradient's power
  and no repeatable signal.

**Where the time goes** (round 12, py-spy on round 13): a 2M-step chunk takes about 20
minutes, 54% training and 46% the evaluation after it (16 matches against each of 42
opponents, one after another). Of training: the frozen opponents' separate `predict`
calls 52%, PPO's update 33%, the learner's forward pass 6.5%, the game 4%.

**What the user's games show** (the 10 November batch: 18 matches, 33 minutes, mostly
round 12's advantaged fourth chunk; the agent took 3 matches, 10 rounds of 41). Every
loss of HP sorted by what the player was doing as it began, beside the same checkpoint
against six exploiters of the characters the user played:

| A minute | Against the user | Against the exploiters |
|---|---|---|
| HP the agent deals | 6,800 | 11,600 |
| HP the agent takes | 10,700 | 8,200 |

The gap is the agent's offence. Against a person who guards it gets far fewer openings,
at the same damage each: the exploiters press a button after guarding its string 48% of
the time (people in the replays 37%, the user 24%), rise with a normal move into its
meaty, and are hit 50% of the times they guard on wake-up (people 39%, the user 23%).
Its okizeme is low 88%, high under 1%, never a throw (people's Ayu: 40% low, 38% high,
0.26 throws a minute). The user rises with a reversal on 27% of wake-ups (exploiters 2%,
people 11%) and it wins 74%; the user's jump-ins on its wake-up hit 76% (the exploiters'
52%, and they are hit back 43% of the time). None of `advantages.py`'s five (rg,
reversal, throw, bait, damage) makes an opponent guard patiently or reverse on wake-up.

## Phase 0: a loop whose result can be read

1. **The averaged model as the start.** `average.py` (the policies' mean weights over a
   run's chunks) makes `agent-league11-avg/model.zip` from `agent-league11-r7`'s ten. It
   gets the checks it hasn't had, beside round 11's best: the level-4 CPU's tiers (63
   matches), Kanna (64), the seven advantaged opponents of rounds 12-13 (64 each), the
   human-limit measures (presses a second, inputs while unable to move). It replaces
   round 11's best as the start unless it is clearly worse on one of them. (The user
   playing it is the last check; that waits for the user.)
2. **`finetune.py`**:
   - `--lr-end`: the learning rate falls linearly from `--lr` to this over the run (1e-4
     to 1e-5): the wandering's spread shrinks with the step.
   - `--average`: a running mean of the chunks' weights (`avg.zip`) is what is evaluated
     after each chunk, what `best.zip`, PFSP's shares and the round's result come from.
     The learner itself trains on as before.
   - `--seed`: torch's generator and the environments' seeds, for replicate runs (two
     runs of the same command were nearly the same run before: torch's default seed is
     fixed and the environments' seeds come from the chunk's number).
   - PPO's own numbers per chunk in `finetune.json` (approximate KL, clipped share,
     entropy, value loss, explained variance, learning rate) and the chunk's drift: how
     far the weights went over the length of a random walk of its updates (1: a random
     walk; more: a direction).
   - `--n-steps` (PPO's rollout per environment; 1,024 in round 14, from 256).
   - `--eval-workers`: the evaluation's pairings in worker processes (seeded, the same
     numbers as one after another); `--eval-old 0` leaves out the curriculum agent (beaten
     100% in every evaluation since round 6).
3. **`efz_env.sb3.mixture`**: the frozen opponents of one architecture are stacked and
   called once a step (`torch.func`), in buckets by their share of the matches, instead of
   one `predict` each. The same logits; the draws from them differ only in order.
4. **The batch**: the CPU (Kanna) from 20% of the environments to 10%, the `--vs`
   opponents from 75% of the rest to 90% (mirror and CPU together 19%, from 40%).
   Kanna stays in every evaluation; Kano's seven keep half the `--vs` matches.

## Phase 1: opponents that defend like people

Three more advantages in `advantages.py` (the opponent's, never the agent's: the agent
keeps the 14-frame delay and every human limit):

| Advantage | What the opponent does | From → toward |
|---|---|---|
| `patient` | After guarding (each guard's end) and on rising, with this share, it holds a guard for 20 steps (40 after rising), a fresh choice of crouching or standing each time (85/15, not the height the attack needs), pressing nothing | starts a move after a guard 48% → 25-35% |
| `wake` | On rising, with this share, the invincible move of its that best beats a meaty, input while rising so it comes out on its first free step, if the agent is committed to its okizeme (`motions.py` probes the timing and the moves) | rises with a reversal 2% → 20-25% |
| `jumpin` | On the agent's knockdown, with this share, a jump (forward, or straight up from close) timed to land its air attack 4 steps into the agent's rise | well-timed jump-ins on the agent's wake-up 3% → 10%+ |

With the old ones set toward the user's rates (recoil guards 22% of the agent's attacks,
an invincible move after a quarter of its RGs, more throws), the profile is `person`.
Calibration comes before any training: the averaged model against the six exploiters
with `person` should deal about the HP a minute it dealt the user (6,800, from 11,600),
or the proxy is wrong and is fixed first. The shares are set between the user's rates
and the replays' people's, so the agent isn't tuned to one player.

Every comparison from here on also reports, against the `person` opponents: the share
of the agent's okizeme that is high, low or a throw; its throws a minute; how often its
string guarded is followed by its hit; how often its guard on rising is opened.

## Phase 2: round 14

Three arms, two seeds each (six runs at once), from the averaged model, 20M steps, all
with phase 0's settings (`--lr 1e-4 --lr-end 1e-5 --average --n-steps 1024 --cpu-share
0.1 --vs-share 0.9`), the league of 39, the pull 0.02 unless said:

| Arm | Change | Question |
|---|---|---|
| A (`agent-league14`) | none | does the loop learn now? (its average against its start) |
| B (`agent-league14-person`) | `person` in half the `--vs` matches | does it learn to open a guarding person? |
| C (`agent-league14-person-pull01`) | B, the pull 0.01 | is the pull the ceiling that's left? |

Each run is judged by its averaged model (`avg.zip`), on 64 seeded matches: the 39 in
the plain game; the `person` set (the exploiters of the characters the user played,
and Shiori's: Ex-Nanase, Nanase, Nagamori, Mishio's third, Sayuri, Kano's seventh,
Mizuka's seventh, Shiori) with `person` on; Kanna; the level-4 CPU's tiers; the human
limits; phase 1's proxies. **The rule, fixed before the runs:** an arm beats A only if
both its seeds beat both of A's on the `person` set and neither loses more than two
points over the 39 in the plain game. A beats its start under the same rule. The best
run whose human-limit measures stay where people's are is round 14's agent.

## Phase 3: the user, and the next league

1. The user plays round 14's agent, the same characters, 15 matches or more
   (`python/examples/play.py`); the recordings go through the same accounting as the
   10 November batch, so the two compare.
2. New exploiters of round 14's agent for the characters the user played, by the
   exploiter recipe of rounds 8-12; in the next league they play with `person` on.
3. If it still plays one answer to each situation, the next step is a memory of the
   opponent's habits within the match (the policy sees one moment and its own 16
   inputs). Not before 1 and 2 have been read.

## Targets

| Measure | Round 11's best | Round 14 |
|---|---|---|
| The 39, 64 matches | 86% (the average: 90%) | 90%, the seeds agreeing |
| The agent's okizeme that is high | under 1% | 15% (people's Ayu 38%) |
| Its throws a minute | 0 | 0.1 (people's Ayu 0.26) |
| Rounds taken from the user | 10 of 41 | clearly more, over 15+ matches |
| Human limits | within | unchanged |

## Where it stands

- **Phase 0, done (11 November).** `average.py` made `agent-league11-avg` (the mean of
  `agent-league11-r7`'s ten chunks). Against round 11's best on 64 seeded matches
  (`scorecard.py`): the 39 90% (own HP lost 50%) from 86% (53%), the helpers 86% from
  76%, the advantaged seven 42% from 32%, the level-4 CPU's hard and rest tiers 100% /
  100% from 76% / 95%, Kanna's HP 61.9% from 51.4%, the same presses (1.55 a second) and
  inputs while unable to move (54% / 55%). It is round 14's start. `finetune.py` has
  `--lr-end`, `--average`, `--seed`, `--n-steps`, `--eval-workers`, `--eval-old`, PPO's
  numbers and the drift in `finetune.json`; `efz_env.sb3.mixture` stacks the frozen
  opponents (the same logits to 1e-4). A 2M-step chunk of round 14's league trains in
  about 5 minutes on 4 threads alone (round 12: 11 minutes on 12) and its evaluation 5
  (from 9); with six runs at once on the 32 cores, 13 minutes and 7-8 (21 a chunk).
- **Phase 1, done.** The three advantages, calibrated against the averaged model on the
  `person` set, 32 matches each, nine rounds of it (below). The profile `person`:
  `rg=0.08,reversal=0.6,throw=0.9,bait=0.2,damage=1.2,patient=0.9,wake=0.6,jumpin=0.2`.
- **Phase 2, done (11 November, 04:58).** The tables are in `runs/human-ayu/README.md`,
  "Round 14". By the rule:
  - A beats its start: 46% and 46% on the `person` set against 40%, 89% and 90% over
    the 39 against 90%.
  - B doesn't beat A: it gains on the set (48%, 54%) and loses five and six points over
    the 39 (85%, 84%).
  - C beats A: 58% and 54% on the set, 90% and 90% over the 39.

  **Round 14's agent is `agent-league14-person-pull01-s1/avg.zip`.** Its human-limit
  measures are where people's are: 1.82 presses a second, people's Ayu players
  1.22-2.06; 54% of them while it can't move, the start's 54%.

  Against the targets:
  - The 39: met (90%, both of C's seeds).
  - The okizeme high and its throws: not met (1% and 0.00 a minute). The gain is in its
    strings (guarded, then its hit, 15% from 11%), not the mix-up.

  It lost Kanna's HP (58.8% from 61.9%) and the level-4 CPU's hard tier (67% of 21 from
  100%).
- **Phase 3.2, done (11 November, 07:26).** An exploiter of round 14's agent for each
  character the user played: `exnanase`, `nanase`, `nagamori`, `mishio`, `sayuri`,
  `kano`, `mizukab`, each `CHAR/exploiter14` against `CHAR/target14.zip` (README, "Round
  14's exploiters"). Two find something in the plain game:
  - Kano's wins 59% against round 14's agent and 39% against its start: a hole round 14
    opened.
  - Ex-Nanase's wins 30% (its start: 44%).

  The other five win 3-5%. Next: a league of the 39 and these seven, with `person` on.
- **Phase 3.1** waits for the user's games, now against round 15's agent with its
  routes (below).
- **Round 15, done (13 November).** See "Round 15" below: the frozen copies' bug, the
  agent `agent-league15-s1/avg.zip`, the routes when the user plays, the chooser.

### Phase 1 as built: what the calibration found

What made the first versions wrong, each found against the user's games:

- **The riser can't be hit on its first two free steps.** A jump-in timed to land on the
  rise whiffed (7-13% hit); landing it 4 steps after the first free one hits 55-80% of
  the times (the user's 76%). `JUMP_LATE = 4`. After a throw the thrower recovers too
  late for any forward jump to be meaty: straight-up jumps from close cover that
  (`motions.py --add jump` finds both, every 8 pixels).
- **A reversal is input while rising.** The game keeps a motion and a press made in the
  rising animation (from 12 steps before) and starts the move on the first step it can,
  as the user's did; `motions.py`'s first probe, knocking down by a throw, found only
  inputs after the rise worked, because a throw that crosses sides makes the game read
  a motion made while rising the other way. A reversal two or three steps late loses to
  the agent's meaty 2A, which is active on the riser's first free step.
- **Which reversal, not the fastest.** Against a meaty 2A at every timing
  (`motions.py --add meaty`), Nanase's 4136A wins 42% and her 623A 100% (the user lost
  5 of 5 with 4136A, won 4 of 4 with 623B); Ex-Nanase's 4136C 25%, her 623C 100%.
- **Into a meaty, or it is punished.** Put out regardless, the reversal was guarded and
  punished (the agent learnt that against round 12's bait). It is put out when the agent
  is in a move, in the air close by, or standing in within 70 pixels not holding a guard;
  else the riser guards.
- **A throw tried as it rises fails** and its forward + C comes out into the meaty: 1,500
  HP a minute dealt to the opponents, none to the user. No throw for 12 steps after the
  `person` opponent rises.

The averaged model against the `person` set (32 matches each) beside the user's games:

| | The user, 10 November | The plain game | `person` |
|---|---|---|---|
| The agent wins | (10 rounds of 41) | 83% | 47% |
| HP it deals / takes a minute | 6,300 / 10,700 | 12,000 / 7,800 | 8,300 / 9,000 |
| Its combos a minute | 6.9 | 12 | 8.5 |
| The opponent moves after guarding its string | 24% | 44% | 20% |
| Its string guarded, then its hit | 11% | 28% | 13% |
| The opponent recoil-guards | 22% | 17% | 20% |
| The opponent rises with an invincible move | 27% | 3% | 25% |
| The opponent's guard on rising opened | 23% | 55% | 24% |
| A jump-in on its rise: of its wake-ups, hit | 11%, 76% | 9%, 31% | 13%, 61% |
| It is thrown a minute | 1.44 | 0.28 | 0.93 |

Its okizeme stays 1% high and it doesn't throw: that is what round 14 trains.

## Round 15 (12 November): the routes, and the opponents training never met

Written before the runs ended; the results are in `runs/human-ayu/README.md` ("Round
15") and, in short, at the end of this section.

**What started it.** The agents don't spend the combo's percentage (the proration shown
on screen: each hit lowers what the next deals). Round 14's agent ends its combos of
three hits or more with 74% left, people with 64%; its combos carry an Instant Charge
0.6% of the time, people's 16.5%. Restarting at 100% is no excuse (the user's point): a
new combo has to open the opponent's guard again and can be countered, a longer one is
free. Measured against the `person` set, 64 matches each: with the fair built-in routes
at play time (`evaluate.py --p1-assist`) round 14's agent wins 65% (own HP lost 70%)
against 58% (73%) with its own combos: 1,250 HP a combo from 987, 66% left, an Instant
Charge in 19.5%, better against every one of the eight.

**1. The routes against a person** (`python/examples/play.py --assist LIBRARY`,
`combo_support.LiveRoutes`). A plan takes 50-400 ms, and a match at the game's speed has
16 ms a frame. The agent sees its hit 14 steps late, and what it will see during those 14
steps it has seen already, so its inputs for them are chosen at the hit, and a planner in
a process of its own (a copy of the match, not drawn, fed the same inputs every frame)
plans meanwhile from where those inputs lead. The route starts on the step the agent sees
its hit, as `FairAssist`'s does; if the game isn't where the plan expected, the plan is
dropped. In real time the game waited 0.1 ms for a plan at the median and 45 ms at most;
no plan was dropped in 190 (against scripted players: one that walks in pressing a
button, one that guards).

**The copies' bug** (`efz_env.sb3.frozen`, found on the way). SB3's
`_get_constructor_parameters` leaves `share_features_extractor` out, so every copy
`frozen()` made since 3 November had one extractor for actor and critic, and loading the
weights wrote the critic's over the actor's: the copy played with the wrong embeddings of
actions and characters. Every frozen opponent of `finetune.py` was such a copy (the
`--vs` exploiters, the mirror, the team, the red team's own play, the routes' own play on
the planner's copies); `evaluate.py` and `play.py` load the models themselves and were
right. On 64 seeded matches:

| Round 14's agent against | The model itself | The copy training met |
|---|---|---|
| Kano's exploiter 14 | 41% (own HP lost 78%) | 100% (15%) |
| Kano's seventh | 44% (75%) | 100% (6%) |
| Ex-Nanase's exploiter 14 | 70% (68%) | 100% (4%) |
| Mishio's third | 91% (53%) | 100% (2%) |
| Nanase | 94% (36%) | 100% (7%) |
| Mizuka's seventh | 100% (38%) | 100% (8%) |

And a copy of the agent, which is what the exploiters trained against, wins 0-2% against
them. So in every round the league's opponents were pushovers in training (a training
return of 2.4 a match in round 14) and themselves in evaluation: what a round "learnt"
against the exploiters came from the pull, the CPU, the scripted `person` behaviour (which
is real, on top of a broken copy) and from picking checkpoints on the evaluation. The
routes' own play on the planner's copies was a broken copy too (149 HP a hit against
1,031 for the model itself), so training with routes took a route too often (rounds 5,
7, 8: 54% of the hits in round 15's league before the fix; 42% after it, in a test
against Kano's seventh). `copy_policy` fixes it and checks every copy's weights against the source's.

**2. Round 15.** From round 14's agent, round 14's loop and settings (`person` in half
the `--vs` matches, the pull 0.01), the league of 39 and round 14's seven exploiters, 20M
steps, three arms of two seeds:

| Arm | The frozen copies | Routes in training |
|---|---|---|
| `agent-league15-old` | as before (the bug) | no |
| `agent-league15` | fixed | no |
| `agent-league15-routes` | fixed | `--assist`: the learner plays with the routes, their steps out of the policy's loss |

Judged as round 14 was (`avg.zip`, 64 seeded matches): the `person` set with `person`
on, the 46 in the plain game, Kanna, the level-4 CPU's tiers, the human limits. **The
rules, fixed before the runs ended:** `agent-league15` beats `agent-league15-old` if both
its seeds beat both of the other's on the `person` set and neither loses more than two
points over the 46. `agent-league15-routes` beats `agent-league15` under the same rule
with both played with the routes (as the user plays them). Round 15's agent is the best
run that also beats round 14's agent played the same way.

**3. A network of its own for the combos** (`combo_net.py`). Routes trained into the
agent's one network cost it its neutral three times. Instead a second network, a copy of
the agent's, learns the routes' steps (the route's action where a route played, the
agent's own probabilities elsewhere) from the agent's matches with routes, and plays only
while the agent sees its own combo running (`evaluate.py --p1-combo ...
--p1-combo-deterministic`); the agent's network isn't touched. Measured against the same
58% (its own combos) and 65% (the routes).

**The results (13 November).** By the rules above:

- `agent-league15` beats `agent-league15-old`: 69% and 73% against 63% and 64% on the
  `person` set, 97% and 97% against 89% and 90% over the 46. The fix alone is worth
  eight points in the plain league and the two holes round 14 had (Kano's seventh and
  her exploiter 14, 44% and 41%, now 92-98%).
- `agent-league15-routes` doesn't beat `agent-league15` (played with the routes: 80% and
  81% against 81% and 81%).
- **Round 15's agent is `agent-league15-s1/avg.zip`.** With the routes (as the user
  plays it: `play.py --assist`) it wins 81% of the `person` set (own HP lost 64%) and
  97% of the 46; round 14's agent 65% and 90%. With its own combos 69% and 97%.
- The network of its own for the combos, as first written (a copy of the agent's network
  taught the routes' steps), plays worse than the agent's own combos (47% against 58%
  for round 14's agent), and with a clock and its combo's actions still does (52%): they
  start routes that don't connect from where the agent stands. What works is a network
  that chooses (what each library combo would deal from the agent's view; the chosen
  recording is played as the planner's is): 78% of the `person` set for round 15's agent
  with no copies of the game, against the planner's 81% (`combo_net.py train-chooser`,
  `runs/human-ayu/combo-chooser15`).

Open after it: the 46 are opponents the agent trained against, each of them trained
against a broken copy of its target. Exploiters of round 15's agent trained against the
model itself are the test it hasn't had. It presses 2.02 times a second (2.14 with the
routes), at the top of people's range (1.22-2.06). Throws and Kanna are where they were.
