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
- **Round 16, done (15 November).** See "Round 16" below: exploiters trained against the
  model itself (`CHAR/exploiter15`), the `crowd` profile from the community's replays,
  the routes planned again at each move's hit. **Round 16's agent is
  `agent-league16-calm-s2/avg.zip`**: with its routes 84% (own HP lost 64%) on the
  `crowd` set from round 15's 67% (73%), 92% (56%) over the `exploiter15`s from 78%
  (68%), 95% (52%) on the `person` set from 90% (55%), 99.4% (32%) over the 46; its
  presses while hit or guarding 3.05 a second on `crowd` from 3.63 (people's players at
  most 2.2). The okizeme arm and the okizeme module both lost wins. Open: jump-ins (it
  is hit by 72% of the slow frontal ones, people by 22%), Kanna, its okizeme and throws.
- **Round 17, done (15 November).** See "Round 17" below: exploiters whose jump-ins land
  (`CHAR/exploiter16`). **Round 17's agent is `agent-league17-s1/avg.zip`**, released as
  `agent-league17-s1-round17.efzagent`: with its routes 91% (own HP lost 58%) over the
  `exploiter16`s from 75% (69%), 98% (46%) over the `exploiter15`s from 92%, 90% (59%)
  on the `crowd` set from 84%, 99.4% over the 46. The arm that never met the
  `exploiter16`s gained as much, less a point; the calmer arm (`-calm4`) reaches
  people's press rate while hit or guarding (2.0 a second for 2.7) at a point or two of
  wins and missed its rule by 0.4, so the next round carries its press cost everywhere.
  Open, unchanged: jump-ins (30-37% of the frontal ones hit it), Kanna, its okizeme
  (lows in 82%, a throw in none).
- **Adapting within a match (15 November).** The "told habits" experiment is read: an
  agent told its opponent's habits plays and wins as one that is not, in both seeds and
  with the told inputs made ten times as large. Training at this budget does not turn a
  read into different play, because the answers (a wait that punishes, an overhead, a
  throw) are not things the policy does. So the match memory is not in round 18 as an
  input; the work goes to options that are timed on copies of the game and chosen by
  the match's counts ("Adapting during a match", below).

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

## Round 16 (14 November): opponents by the community's measure

**What started it.** The user played round 15's agent with its routes, 20 matches (13
November): it took 5 of the 20 and 15 rounds of 47 (10 November, round 13's: 3 of 18,
10 of 41), "much more like a human", and still open to air attacks and invincible
moves, its pressure "simple and easy to predict, still focus on low attacks", with "no
lures, traps and deceptive set ups"; its combos "hit a lot" but drop where "the
conditions are different (mid screen vs corner) but it still tries the same combo". And
the rule for what follows: "Don't overfit on me. I plan to train a few rounds and bring
it to the community for wider testing." So each of these is taken up only where the
league or the community's replays say the same, and the opponents' numbers come from the
replays' players (1,908 matches of people's Ayu, 13 players with 40 or more), not from
the user's games.

**1. Routes that fit the position** (done; README, "Routes that fit where the players
are"). The planner plans again at each new move's hit the agent sees, the rest of its
route one of the options, the library's combos joined where that move hit in them. On
the `person` set round 15's agent goes from 81% (own HP lost 64%) to 90% (55%) with 24
combos tried, 1,240 HP a combo to 1,530, 4.9 hits to 7.3. `play.py --assist` does it in
real time.

**2. What the community's replays say of round 15's agent** (`people.py` over the
dataset, `evaluate.py` over the `person` set, 64 matches each, the agent with its
routes):

| | People's Ayu (players' quartiles) | Round 15's agent |
|---|---|---|
| Its okizeme: high / low | 38% / 40% (32-44% / 36-46%) | 12% / 72% |
| Its okizeme with an object out | 30% (25-36%) | 7% |
| Its okizeme crossing sides | 4.1% | 0.9% |
| A set-up after a string guarded with advantage | 9.5% (7-13%) | 1.2% |
| Its throws a minute | 0.26 (0.09-0.29) | 0.01 |
| Presses a second: hit or guarding | 1.05 (0.76-1.10; the most 2.21) | 2.8-3.8 |
| ... in its combo / its string guarded / neither | 2.0 / 2.0 / 1.4 | 1.6-2.0 / 1.8-2.2 / 2.1-2.7 |

So "low, predictable, no set-ups" is the community's measure too, not one player's; and
its presses, over people's range since round 15 (2.2 a second on the `person` set,
people's players 1.22-2.06), are over it where a press does nothing: while it is hit or
guarding (`evaluate.py`'s `presses_where`, new).

**3. `crowd`: the opponents' defence by the replays.** `person` was set between the
user's rates and the replays'. Against the replays alone it guards too patiently and
reverses too often:

| The opponent, against Ayu | The community (quartiles) | Plain | `person` | `crowd` |
|---|---|---|---|---|
| Starts a move after guarding a string | 37% (33-47%) | 41% | 19% | 35% |
| ... an invincible one | 2.1% | 0.9% | 7.9% | 2.8% |
| Its guards that are recoil guards | 36% (37-41%) | 18% | 22% | 38% |
| An invincible move after its RG | 3.4% (2.2-4.3%) | 1.9% | 31% | 5.8% |
| Rises with an invincible move | 10.7% (9.5-11.5%) | 2.0% | 23% | 11% |
| Rises with another move | 17% (12-20%) | 22% | 6% | 12% |
| Its guard on rising opened | 39% (30-41%) | 58% | 23% | 43% |
| In the air over Ayu's rise | 37% (31-43%) | 30% | 35% | 36% |
| Throws Ayu, a minute | 0.73 (0.49-1.01) | 0.23 | 0.76 | 0.63 |
| Round 15's agent wins (its own combos, 32 matches each) | | 97% | 68% | 89% |

`crowd`: `rg=0.2,reversal=0.04,throw=0.7,bait=0.2,damage=1.2,patient=0.3,wake=0.25,jumpin=0.2`
(the table's column is its first try, with `reversal=0.06`). `finetune.py --vs-profile2
SPEC` plays a second profile in a share of the matches with the advantages (half), drawn
each chunk: `person` and `crowd` side by side, a patient defender who reverses and the
community's average.

**4. Exploiters of the model itself** (`CHAR/exploiter15`). Every exploiter before 12
November trained against a broken copy of its target. New ones against round 15's agent,
for the eight characters people's Ayu meets most in the replays (Sayuri, Ex-Nanase,
Mayu, Nanase, Kaori, Mishio, Ikumi, Nayuki (awake): 59% of the matches), then Kano,
Mizuka and Makoto (the league's two finders of holes, and the character it does worst
against). The recipe of rounds 8-14 (the target alone, a quarter against the level-3
CPU, the pull 0.1 to the character's clone, 24M steps or 60% wins), but each from its
character's strongest model against round 15's agent, not from the clone.

All eleven reached the 60% (32 matches a chunk) inside the 24M steps: Nayuki's in 1M,
Ex-Nanase's, Ikumi's and Kano's in 2M, Makoto's in 4M, Kaori's 5M, Mayu's 6M, Sayuri's
and Mishio's 8M, Nanase's 10M, Mizuka's 23M. Round 15's agent against their `best.zip`,
64 seeded matches, win (own HP lost):

| `exploiter15` of | Its own combos | Routes (12, the first hit) | Routes planned again (24) |
|---|---|---|---|
| Sayuri | 45% (87%) | 64% (79%) | 81% (71%) |
| Ex-Nanase | 72% (74%) | 91% (64%) | 89% (54%) |
| Mayu | 72% (76%) | 86% (62%) | 89% (63%) |
| Nanase | 50% (79%) | 78% (72%) | 77% (62%) |
| Kaori | 36% (87%) | 61% (77%) | 78% (71%) |
| Mishio | 59% (86%) | 81% (74%) | 91% (64%) |
| Ikumi | 33% (85%) | 77% (67%) | 84% (67%) |
| Nayuki (awake) | 41% (82%) | 66% (74%) | 77% (72%) |
| Kano | 0% (98%) | 6% (95%) | 34% (86%) |
| Mizuka | 25% (87%) | 55% (80%) | 70% (79%) |
| Makoto | 67% (73%) | 83% (63%) | 91% (56%) |
| The eleven | 45% (83%) | 68% (73%) | 78% (68%) |

So the 97% over the 46 was the measure of opponents trained against a broken copy: an
opponent trained against the model itself takes it apart in a few million steps, Kano's
entirely (0 of 64). The routes buy back most of it and the wins stay hard (two thirds of
its HP lost); Kano's hole is the neutral's, not the combos'.

**5. Round 16.** From round 15's agent, round 15's loop, 20M steps; the league: the 46
and the `exploiter15`s; `person` and `crowd` in half the `--vs` matches (a quarter
each). Three arms of two seeds:

| Arm | Change | Question |
|---|---|---|
| `agent-league16` | none | what do opponents that beat it teach it? |
| `agent-league16-calm` | `--press-cost 0.002`: each button pressed while hit or guarding costs 20 HP's worth of reward (`focus.Calm`) | do its presses come down to people's where they do nothing, at no cost? |
| `agent-league16-oki` | `--prior-down 10`: the pull to people's clone ten times as strong while it sees the opponent knocked down (the clone's okizeme against `crowd`: 23-28% high, 25-28% low, an object out in 20-28%) | does people's okizeme, kept, beat its 2A? |

Judged by `avg.zip` on 64 seeded matches, played with the routes planned again (24
tried): the `crowd` set (the `exploiter15`s of the eight most met, `crowd` on), the
`person` set, the 46 and the `exploiter15`s in the plain game, Kanna, the level-4 CPU's
tiers, the human limits with `presses_where`, the okizeme's mix. **The rules, fixed
before the runs:**

- `agent-league16` replaces round 15's agent if both its seeds beat it over the
  `exploiter15`s in the plain game and on the `crowd` set, and neither loses more than
  two points over the 46.
- `-calm` is taken over `agent-league16` if both its seeds press under 2.2 times a second
  while hit or guarding (the most of people's players) and neither is more than two
  points under `agent-league16`'s mean on the `crowd` set or over the league.
- `-oki` beats `agent-league16` if both its seeds beat both of the other's on the `crowd`
  set and neither loses more than two points over the league; its okizeme's mix and the
  HP a knockdown is worth are reported either way.

**6. Round 16's results (15 November).** The six runs' `avg.zip` (20M steps each) and
round 15's agent, 64 seeded matches an opponent, the routes planned again (24 tried)
except where said; win (own HP lost), the mean over the set's opponents:

| | Round 15 | `16` s1 | `16` s2 | `-calm` s1 | `-calm` s2 | `-oki` s1 | `-oki` s2 |
|---|---|---|---|---|---|---|---|
| The `crowd` set (8) | 67.0% (73%) | 80.9% (65%) | 80.1% (65%) | 82.2% (66%) | 84.0% (64%) | 81.6% (65%) | 77.1% (67%) |
| The `exploiter15`s, plain (11) | 78.3% (68%) | 91.6% (55%) | 89.2% (58%) | 88.5% (58%) | 92.2% (56%) | 91.3% (57%) | 87.8% (60%) |
| The `person` set (8) | 89.8% (55%) | 95.9% (51%) | 91.6% (54%) | 94.3% (50%) | 95.1% (52%) | 93.8% (52%) | 90.6% (54%) |
| The 46, plain | 98.9% (36%) | 99.5% (32%) | 99.5% (33%) | 99.5% (31%) | 99.4% (32%) | not run | not run |
| The 46, its own combos | 97.3% (39%) | 98.6% (35%) | 98.5% (37%) | 98.3% (35%) | 99.1% (33%) | 95.0% (48%) | 95.3% (46%) |
| The level-4 CPU's tiers | 74.6% (58%) | 68.3% (58%) | 69.8% (57%) | 73.0% (56%) | 73.0% (57%) | not run | not run |
| Kanna (level 4), its own combos | 0% (98%) | 0% (98%) | 0% (99%) | 2% (98%) | 3% (97%) | 0% (99%) | 2% (98%) |
| Presses a second on the `crowd` set | 2.45 | 2.78 | 2.68 | 2.28 | 2.32 | 2.79 | 2.72 |
| ... while hit or guarding: `crowd` | 3.63 | 4.85 | 4.52 | 2.75 | 3.05 | 5.02 | 4.58 |
| ... the `exploiter15`s, plain | 3.06 | 4.01 | 3.78 | 2.27 | 2.48 | 4.20 | 3.82 |
| ... the `person` set | | 3.88 | 3.77 | 2.09 | 2.46 | 4.06 | 3.92 |
| Its okizeme on `crowd`: high / low | 3% / 83% | 5% / 81% | 4% / 83% | 4% / 85% | 4% / 84% | 8% / 62% | 7% / 63% |
| ... with an object out | 1.0% | 1.0% | 1.5% | 0.9% | 0.8% | 2.1% | 2.7% |
| HP a knockdown is worth on `crowd` | +21 | -46 | -23 | -23 | -59 | -54 | -75 |

By the rules:

- **`agent-league16` replaces round 15's agent.** Both seeds beat it over the
  `exploiter15`s (91.6% and 89.2% against 78.3%) and on the `crowd` set (80.9% and 80.1%
  against 67.0%), and gain over the 46 (99.5% from 98.9%). Opponents that beat the model
  itself taught it what the 46 could not: thirteen points on each set, and against
  Kano's exploiter, where round 15's agent won 34%, these win 88% and 72%.
- **`-calm` does not pass its rule as written, and is the better agent.** Its presses
  while hit or guarding are not under 2.2 a second on every set (2.09-3.05), so the rule
  says no. But the unchanged arm *raised* them (3.6 to 4.5-4.9 on `crowd`: against
  opponents that beat it, it mashes more), and the press cost took them under round 15's
  (2.75, 3.05) at no cost in strength: `crowd` 82.2% and 84.0% (the unchanged arm's mean
  80.5%), the `exploiter15`s 88.5% and 92.2% (90.4%), the 46 99.5% and 99.4% (99.5%),
  the CPU's tiers 73% (69%). The human limits are the hard line and the rule was written
  to hold `-calm` to them, not to keep an arm that is further from them: **round 16's
  agent is `agent-league16-calm-s2/avg.zip`** (of the two seeds the stronger on `crowd`,
  the `exploiter15`s and the `person` set). This is a choice made against the rule's
  letter and said as one. Round 17 has the press cost in every arm, and a stronger one
  in one of them, to reach the 2.2.
- **`-oki` does not beat `agent-league16`.** One seed does on `crowd` (81.6%), the other
  doesn't (77.1%), and both lose three points over the 46 with their own combos (95%).
  The pull moved the mix a little (high 7-8% from 4-5%, low 62-63% from 81-83%, an
  object out in 2-3%; people's 38% / 40% / 30%) and a knockdown was worth no more HP.
  With the module's result ("The okizeme module, measured", below) that is two ways of
  giving it people's okizeme that both cost wins: its 2A is what its okizeme's timing
  can carry, and a better okizeme is a planner's work, not a prior's.

What didn't move: Kanna (0-3%), the okizeme's mix, the throws (0.01 a minute). What got
worse: the level-4 CPU's tiers in the unchanged arm (68-70% from 75%; `-calm` 73%), and
the HP a knockdown is worth against `crowd` in every arm (round 15's +21, these -23 to
-75; why is not looked into yet).

## The games of 14 November: the agent in the game, and jump-ins

The user's third batch, the first played in the native game: round 15's agent as an
in-game agent (`agent-league15-s1.efzagent`, its routes planned in the game), 20 matches,
nine characters. The game records each fight (docs/logging.md: every tick's inputs, a few
fields of each player), not the observation; `from_record.py` plays each fight again in
the headless game from its inputs and writes play.py's recordings, checking every frame
against the record. All 20 matches play again exactly. Two things the headless game needs
for that: the record's `rand()` state (found by inverting the environment's seeding) and
the RF gauge at 0 (a headless match that plays its intro begins 233 ahead: play.py's
matches had the RF gauge that much fuller than the game's).

| | 13 Nov (play.py) | 14 Nov (in the game) |
|---|---|---|
| Matches the agent won | 5 of 20 | 6 of 20 |
| Rounds | 15 of 47 | 18 of 49 |
| HP a minute: it deals / takes | 6,900 / 9,300 | 7,400 / 8,100 |
| Its combo, on average | 1,050 | 1,120 |
| Presses a second (hit or guarding) | 2.62 (3.69) | 2.51 (3.67) |
| Its okizeme that is 2A | 76% | 72% |
| Its okizeme, HP a knockdown | -100 | +107 |
| The user's rises with an invincible move | 15% | 6% |

- **The agent in the game is the agent.** Its measures are the play.py batch's. The
  game's planner kept up: 310 plans (15.5 a match), 1 late, 50-97 ms a plan; a route was
  chosen in 30%.
- **The game has the routes planned once.** Its port is of the pushed version; the routes
  planned again at each new move's hit (section "Routes that fit where the players are" of
  the README) are not in it.
- **One session is noise on some measures.** The last two rows changed sign or halved with
  the same agent. The okizeme's value and the reversals on wake-up are not to be steered
  by one batch.
- **Jump-ins are steady, and not the user's alone.** Airborne attacks are 32-37% of the HP
  it loses in both batches. `evaluate.Events` now counts them (`jumpins`: the opponent's
  airborne attacks that met the player on the ground and not in a move of its own):

| Jumped in on | By | From the front: hit | Crossing: hit | Met a minute |
|---|---|---|---|---|
| Round 15's agent | the user, 14 Nov | 39% | 77% (of 13) | 2.0 |
| Round 15's agent | the user, 13 Nov | 34% | 56% (of 9) | 2.2 |
| Round 15's agent | the `crowd` set | 40% | 64% | 1.1 |
| `agent-league16-s1` | the `crowd` set | 35% | 73% | 1.0 |
| `agent-league16-calm-s2` | the `crowd` set | 29% | 64% | 1.1 |
| People's Ayu (1,949 matches) | their opponents | 14% | 42% | 2.9 |

  (The `crowd` set in the plain game with its own combos, 64 matches each. People: the
  median match 15%, the 90th percentile 40%.) The league's opponents jump in at 40% of
  people's rate, and the agent guards them as badly as it guards the user's.

**Guarding on sight is not the answer.** A module that held a standing guard while the
agent, free on the ground, saw the opponent in the air within 192 pixels (tried on round
15's agent over the `crowd` set, then removed):

| | Wins (own HP lost) | From the front: hit | It deals a minute |
|---|---|---|---|
| Round 15's agent | 36.9% (85%) | 40% | 7,420 |
| + guard when an airborne attack is seen | 34.4% (86%) | 34% | 7,245 |
| + guard when the opponent is seen in the air | 31.8% (87%) | 24% | 7,117 |

Even guarding from the moment the jump is seen leaves 24%, and the time spent holding
back costs more than the hits saved: the module guards through all of the opponent's
time in the air, and people don't.

**What people do, and the agent doesn't** (15 November). The jump-ins a reaction can
answer: from the front, the attacker 30 steps or more in the air at contact (half of
people's frontal jump-ins, seven in ten of the user's), a jump-in's contacts counted once.
People's Ayu over the 1,949 matches, round 15's agent over the user's 40:

| A slow jump-in from the front | People's Ayu (3,123) | Round 15's agent (81) |
|---|---|---|
| Hit | 22% | 72% |
| At contact: a standing guard held | 69% (3% of them hit) | 26% (14%) |
| ... a crouching guard | 11% (46%) | 17% (86%) |
| ... no guard | 20% (78%) | 57% (93%) |
| A standing guard held 20 steps before, 8 before, at contact | 24%, 48%, 69% | 14%, 16%, 26% |

- **People stand up into a guard in the last 20 steps**, three times as many holding it
  at contact as 20 steps before: a reaction to the jump, inside what the agent's 14 steps
  of delay allow (a jump is 40-60 steps from its start to its contact). The agent's
  share hardly moves. So the 14% is not anticipation only, as written above the day
  before: it is a reaction the agent hasn't learned.
- **The agent walks into them.** Of its 46 met with no guard, it was holding forward in
  70% (people: 27%), with no move of its own in the 30 steps before in 65% and no button
  pressed in the 14 before in 80%: not a whiffed attack punished, an approach that
  doesn't stop for the jump.
- **Its crouching guard is its other habit**: one in six, nearly all hit (an air attack
  is a high).

Why the league never taught it: its opponents jump in at 40% of people's rate, so
walking in costs little there.

**A scripted jump-in is not a person's.** Tried and removed: a knob of `advantages.py`
that made an opponent, free on the ground at a distance one of its character's probed
jump-ins starts from, jump in at a chance a second. Round 15's agent against the `crowd`
set with it, 512 matches a row:

| Chance a second | Jump-ins begun a match | Hit the agent | The agent hit it first | Wins (own HP lost) | Jump-ins met a minute (`jumpins`) |
|---|---|---|---|---|---|
| none | | | | 36.9% (85%) | 1.13 |
| 0.4 | 1.9 | 25% | 46% | 35.9% (86%) | 1.12 |
| 0.8 | 3.2 | 27% | 44% | 37.7% (85%) | 1.16 |

A jump from a moment drawn at random is one the agent sees coming and hits out of the
air: it was holding back or crouching at 78% of the takeoffs. What hits it is a jump-in
chosen for the moment (it is walking in, or pinned in a guard), which is an opponent's
to learn, not a script's.

So round 17's jump-ins come from exploiters: `finetune.py --focus air` (`focus.py`: a
hit made in the air that begins the hit reaction of an opponent on the ground is worth
200 HP more) for the exploiters of round 16's agent, and `jumpins` (with what the agent
was doing on the step before: walking back, crouching, walking forward) is one of the
round's measures.


## The okizeme module, measured (15 November)

`okizeme.py` (the kind `oki`): while the agent sees its opponent knocked down, people's
clone (`bc-d14.zip`) plays in its place. Round 15's agent with the routes planned again
(24 tried), without the module and with it, 64 seeded matches against each of the eight
opponents of a set. `through_combo` begins the okizeme as soon as the opponent is seen
down; without it the module waits until the agent's combo count is gone, 14 steps late.

| The `crowd` set | Wins (own HP lost) | Its okizeme: low / high / object out | Meaty | The agent hit first | HP a knockdown |
|---|---|---|---|---|---|
| Routes | 67.0% (73%) | 83% / 3% / 1% | 73% | 15% | +21 |
| + `oki` | 62.5% (75%) | 38% / 6% / 2% | 37% | | -123 |
| + `oki`, `through_combo` | 68.0% (72%) | 24% / 30% / 17% | 37% | 27% | -122 |

| The `person` set | Wins (own HP lost) | Its okizeme: low / high / object out | Meaty | The agent hit first | HP a knockdown |
|---|---|---|---|---|---|
| Routes | 89.8% (55%) | 81% / 3% / 2% | 64% | 24% | -77 |
| + `oki`, `through_combo` | 83.6% (63%) | 24% / 33% / 18% | 35% | 36% | -210 |

(People's Ayu: 40% low, 38% high, an object out in 30%.)

- **The mix is people's, the wins are not.** With `through_combo` the okizeme is as
  varied as people's. Against the community's average defender that is worth nothing
  (68.0% for 67.0%, inside the noise of 512 matches); against the defender who reverses
  on rising it costs six points, on seven of the eight opponents.
- **Why: the clone's okizeme is late.** Half as many of its okizeme attacks are meaty
  (35-37% for 64-73%), so the riser's move comes out first: the agent is the one hit
  first half again to twice as often, and a knockdown loses it 120-210 HP.
- **Without `through_combo` the module starts too late to matter.** It waits out the
  combo's count as the agent sees it, and what is left of the knockdown is too short for
  a set-up: 6% high, 2% with an object.
- **The same in training.** Round 16's `-oki` arm (the pull to the clone ten times as
  strong while the opponent is down) moved the mix a little (7-8% high, 62-64% low) and
  won no more than the base arm.

So the module is not part of the agent that ships. It stays in the code as an example of
a module (and for a match where variety matters more than winning). The okizeme that
wins has to be timed as well as mixed, which the clone is not: a set-up's timing is the
planner's kind of problem (tried on copies of the game from the knockdown, as the routes
are from a hit), not a clone's.

## Round 17 (15 November): opponents whose jump-ins land

**What starts it.** Round 16's agent is hit by jump-ins people would guard ("The games of
14 November", above), a scripted jump-in is not a person's, and the league's opponents
jump in on it less than people's do. So the opponents are taught to: exploiters of round
16's agent with `finetune.py --focus air` (`focus.py`: each hit made in the air that
begins the hit reaction of an opponent on the ground adds to the reward).

**1. The `exploiter16`s.** The recipe of the `exploiter15`s, each from its character's
`exploiter15` against `agent-league16-calm-s2/avg.zip` (`CHAR/target16.zip`), `--focus
air` (Kano `charge`, Mizuka `setup`, as theirs were).

- **The first five stopped on noise.** At `--focus-coef 0.02` and the old stop (60% of 32
  matches) Sayuri's, Ex-Nanase's, Nayuki's, Mayu's and Nanase's stopped after 3-7M steps,
  and against the agent with its routes they are their `exploiter15`s: the agent wins
  87% for 90%, meets 0.68 jump-ins a minute for 0.88, is hit by 27% of the frontal ones
  for 24% (`CHAR/exploiter16a`; two of the five `best.zip` *are* the `exploiter15`:
  `best.zip` counts the CPU's wins in, and the CPU's level rose). A stop on 32 matches
  at 60% is passed by an even opponent one chunk in nine.
- **The recipe since:** `--focus-coef 0.05` (a jump-in that lands is worth 500 HP),
  `--eval 64 --stop-win 0.7`, and the model at the stop (`model.zip`), not `best.zip`.
  The five were taken up again from where they stopped.

Round 16's agent with its routes (planned again, 24) against each, 64 seeded matches;
the jump-ins are `evaluate.py`'s `jumpins` (the agent hit or guarding a grounded
opponent's air attack), the frontal ones' share that hit it, and the share before which
it was walking forward:

| Exploiter of | `exploiter15`: win (own HP lost) | jump-ins a minute | frontal, hit | forward | `exploiter16`: win (own HP lost) | jump-ins a minute | frontal, hit | forward |
|---|---|---|---|---|---|---|---|---|
| Sayuri | 87.5% (67%) | 0.87 | 36% | 11% | 50.0% (84%) | 1.02 | 31% | 14% |
| Ex-Nanase | 96.9% (43%) | 1.02 | 45% | 25% | 81.2% (60%) | 2.28 | 54% | 23% |
| Nayuki (awake) | 82.8% (63%) | 0.24 | 23% | 4% | 79.7% (66%) | 0.54 | 57% | 48% |
| Mayu | 90.6% (57%) | 1.82 | 9% | 4% | 82.8% (66%) | 1.02 | 23% | 12% |
| Kaori | 96.9% (57%) | 0.22 | 58% | 14% | 75.0% (74%) | 0.51 | 43% | 8% |
| Mishio | 93.8% (58%) | 1.36 | 50% | 18% | 84.4% (67%) | 1.71 | 50% | 20% |
| Kano | 84.4% (68%) | 0.15 | 67% | 54% | 71.9% (76%) | 0.41 | 62% | 46% |
| Makoto | 98.4% (41%) | 2.06 | 15% | 5% | 90.6% (53%) | 2.40 | 12% | 2% |
| Ikumi | 95.3% (40%) | 0.06 | 38% | 12% | 56.2% (76%) | 0.14 | 39% | 6% |
| Nanase | 93.8% (56%) | 0.47 | 25% | 12% | 81.2% (63%) | 0.48 | 20% | 2% |
| Mizuka | 93.8% (61%) | 1.85 | 41% | 26% | 75.0% (76%) | 1.98 | 46% | 29% |
| The eleven | 92.2% (56%) | 0.92 | 29% | 13% | 75.3% (69%) | 1.14 | 37% | 17% |

(Nanase's and Mizuka's never held 70%: after 13M and 17M steps theirs are the chunks
that did best against the target, 66% and 69% of 64, `CHAR/exploiter16/league.zip`, as
the others' `model.zip` is.)

So with the firmer recipe they are opponents the agent has not met: seventeen points
fewer wins with its routes, a quarter more jump-ins, and the frontal ones hit it 37% of
the time for 29% (people are hit by 22% of the slow ones). Sayuri's and Ikumi's take
half their matches from it. Ex-Nanase's jumps in twice as
often and hits with more than half; Nayuki's and Kano's catch it walking forward in half
of theirs: the habit the user's games showed, now in the league.

**2. The league and the arms.** From round 16's agent, round 16's loop, 20M steps; the
league: the 46, the `exploiter15`s and the `exploiter16`s; `person` and `crowd` each in a
quarter of the `--vs` matches. The press cost is in every arm. Three arms of two seeds:

| Arm | Change | Question |
|---|---|---|
| `agent-league17` | `--press-cost 0.002` (round 16's `-calm`) | what do opponents whose jump-ins land teach it? |
| `agent-league17-calm4` | `--press-cost 0.004` | do its presses while hit or guarding reach people's (2.2 a second at most)? |
| `agent-league17-nox16` | the league without the `exploiter16`s | the control: is it the `exploiter16`s, or 20M steps more? |

Judged by `avg.zip` on 64 seeded matches with the routes planned again (24 tried): the
`exploiter16`s and the `exploiter15`s in the plain game, the `crowd` set, the `person`
set; the 46 with its own combos (the cheap one: 46 opponents a run); Kanna and the
level-4 CPU's tiers; `presses_where`; `jumpins` over the `exploiter16`s (a minute, the
frontal ones' share that hit, the share walked into). **The rules, fixed before the
runs:**

- `agent-league17` replaces round 16's agent if both its seeds beat it over the
  `exploiter16`s, and neither is more than two points under it on the `crowd` set, over
  the `exploiter15`s or over the 46.
- `-calm4` is taken over `agent-league17` if both its seeds press less while hit or
  guarding on the `crowd` set than both of `agent-league17`'s, and neither is more than
  two points under `agent-league17`'s mean on the `crowd` set or over the `exploiter16`s.
  Whether it is under 2.2 is reported as the target met or not (round 16's rule made the
  target the test, and the better arm failed it).
- The `exploiter16`s are what taught it if both seeds of `agent-league17` beat both of
  `-nox16`'s over the `exploiter16`s. If they don't, the next round's exploiters are not
  worth their hours as they are.
- Jump-ins: the frontal ones' share that hit it over the `exploiter16`s, each arm
  against round 16's agent (37% over the eleven), is reported, not a gate: the
  measure that counts is people's games, the user's next ones and the community's.

**3. The result (15 November, 19:50).** Each run's `avg.zip`, 64 seeded matches an
opponent, wins (own HP lost a round). The `-nox16` arm was run only where its rule needs
it; the `person` set was left out for the arms (report only, and the machine was shared).

| | round 16's agent | `agent-league17` s1 / s2 | `-calm4` s1 / s2 | `-nox16` s1 / s2 |
|---|---|---|---|---|
| the eleven `exploiter16`s | 75.3% (69%) | 91.2% (58%) / 90.8% (58%) | 89.5% (58%) / 88.6% (59%) | 90.3% (57%) / 89.5% (57%) |
| the eleven `exploiter15`s | 92.2% (56%) | 97.7% (46%) / 97.3% (46%) | 96.3% (47%) / 97.4% (48%) | |
| the `crowd` set | 84.0% (64%) | 89.6% (59%) / 87.9% (58%) | 86.9% (58%) / 88.9% (60%) | |
| the 46, its own combos | 99.1% (33%) | 99.4% (32%) / 98.7% (33%) | 98.9% (33%) / 99.1% (32%) | |
| the level-4 CPU's tiers | 73.0% (57%) | 71.4% (51%) / 71.4% (56%) | 65.1% (59%) / 69.8% (57%) | |
| Kanna (level 4), its own combos | 3.1% (97%) | 0% (99%) / 0% (99%) | 1.6% (98%) / 0% (98%) | |
| presses a second while hit or guarding, `crowd` | 3.05 | 2.73 / 2.62 | 2.05 / 1.96 | |
| the same over the `exploiter16`s | 2.58 | 2.34 / 2.22 | 1.69 / 1.59 | 2.13 / 2.30 |
| frontal jump-ins that hit it, `exploiter16`s | 37% of 1,521 | 37% of 1,047 / 30% of 1,415 | 34% / 32% | 38% / 36% |
| ... before which it was walking forward | 17% | 15% / 14% | 15% / 14% | 17% / 15% |

By the rules:

- **`agent-league17` replaces round 16's agent.** Both seeds beat it over the
  `exploiter16`s by fifteen points, and neither is under it on the `crowd` set (+5.6,
  +3.9), over the `exploiter15`s (+5.5, +5.1) or over the 46 (+0.3, -0.4). **Round 17's
  agent is `agent-league17-s1/avg.zip`** (of the two seeds the stronger on `crowd`, as
  round 16's was chosen).
- **`-calm4` is not taken, by 0.4 of a point.** It presses less while hit or guarding
  than both base seeds (2.05 and 1.96 a second on `crowd` for 2.73 and 2.62) and is
  within two points of the base arm's mean on `crowd` (88.8%), but seed 2 is 2.4 points
  under the base arm's mean over the `exploiter16`s (88.6% for 91.0%). The target (2.2 a
  second, the most of people's players) is met by both its seeds and by neither of the
  base arm's. The cost of the doubled press cost is one to two points of wins, which is
  inside what 704 matches tell apart; so the next round carries `--press-cost 0.004` in
  every arm rather than as an arm (the input rate is part of the human limits, not a
  thing to trade), and `-calm4`'s seed 2 is packed beside the pick for anyone who wants
  the calmer one.
- **The `exploiter16`s taught it, by the letter and no more.** Both base seeds are above
  both `-nox16` seeds over the `exploiter16`s, by 0.5 to 1.7 points: noise. The arm that
  never met them gained fourteen of the fifteen points. So meeting an exploiter in
  training is worth about a point; the fifteen come from the round's other twenty
  million steps (and are real: the check below).
- **Jump-ins: not fixed.** The frontal ones hit the base arm 37% and 30% of the time
  (round 16's agent 37%, people 22% of the slow ones); it walks forward into as many.
  Winning more against opponents that jump in did not teach it to guard them.
- Kanna and the level-4 CPU's tiers are where they were (the CPU is no training
  opponent but Kanna, and Kanna is not being learned at a tenth of the matches).

Per opponent, the `exploiter16`s: Sayuri's still takes a third of its matches from the
pick (68.8%, own HP lost 76%; round 16's agent 50.0%), Mizuka's one in seven (85.9%,
71%); the other nine are at 89-100%.

**The check: do the `exploiter16`s beat only the agent they were trained on?** If they
did, any other agent would score well against them and the fifteen points would measure
nothing. Round 16's other seed (`agent-league16-calm-s1`: the same training, never an
exploiter's target), with its routes, against the three finished of the eleven: Nayuki's
62.5% (the target itself 79.7%), Sayuri's 50.0% (50.0%), Ex-Nanase's 92.2% (81.2%); 68%
over the three for the target's 70%, and round 17's pick 85%. So they are not beaten by
being someone else: what they do works on round 16's agents and works less on round
17's, whose gain is its own (twenty million steps more against the league and the two
profiles), not the exploiters' being stale. (The other eight were stopped when the
machine ran short of memory; they are run again when it has room.)

**The pick as a release.** `agent-league17-s1-round17.efzagent` (9.6 MB: the model, its
routes planned again at each move's hit, its training part; unpacked again it is the
same weights to the last bit) and `agent-league17-calm4-s2-round17.efzagent`, in the
folder of handed-over files; neither holds a path under a home folder or a name from the
replays' player list.

## Adapting during a match: the plan (15 November)

**What starts it.** The user, 15 November: "we need to make the agent somehow adaptive
during test time, learn to exploit the opponent during games"; "if it keeps one strategy
it will be exploited facing human". The user's 40 recorded matches against round 15's
agent say the same of the user: the first match with a character 10 won of 16 (rounds
23-15), the second 11 of 15 (23-12), the third on 8 of 9 (17-6). A warm-up with the
character is in that too, and 40 matches are few; but an agent that plays the fortieth
match as the first is learned in two or three.

**Why training has not given it this.**

- *It has no memory.* The policy sees the game as it was 14 steps ago and its own last 16
  inputs. What the opponent did on its last three wake-ups, or how its own last four low
  attacks went, is nowhere in what it sees.
- *No opponent has a habit it could read.* A league opponent plays the last round as the
  first. The `person` and `crowd` profiles draw each choice afresh (a wake-up reversal
  in `wake` of the risings, a crouching guard in 85% of the patient ones), and the
  wake-up reversal is scripted to come out only when the agent is committed, which it
  reads from the game as it is: a habit that can't be baited is not one to learn from.
- *No opponent learns it.* An exploiter does, over millions of steps, and is then frozen.
  Within a match nothing punishes the agent for doing the same thing again. (The profiles
  already hold a crouching guard against most of its low attacks, and it still goes low
  four times in five, so an opponent that only *counted* its lows would change little:
  the gain is not there. It is in the choices where a read pays: the wake-up, the guard
  after a string, the jump-in.)

**The plan.** Two parts that need each other, and a measure.

1. **A match memory** (`efz_env`: a block of inputs after the input history, as the
   history is after the game's view). Running counts over the match, and carried with a
   decay over the matches of a session against the same opponent, of what the opponent
   did in the situations `tactics.py` already names (its wake-ups: an invincible move,
   another move, a guard, a jump, a backdash; after guarding a string: a move, a recoil
   guard, a reversal out of it; its guard's height; its jump-ins and throws a minute; on
   the agent's wake-ups: a meaty, a wait, a jump-in, a throw) and of how the agent's own
   choices went (its okizeme by height, its wake-up options, its jump-ins). Each a share
   with the count behind it. Read from the view the agent has, 14 steps late: what a
   person remembers of the match, so inside the human limits. A model without the block
   gets the observation it knows (as one without history does), so the league's frozen
   opponents and the clone are untouched; the agent's first layer is widened with zeros,
   so it starts as the agent it was.
2. **Opponents with habits, and opponents that adapt.** (a) Honest habits, drawn for each
   match from ranges as wide as the community's players (`people.py`'s spread, not one
   player's): a wake-up reversal that comes out whether or not the agent is committed, a
   guard's height with a lean, a throw or a jump-in more or less often, a press after a
   guarded string or none. Against these a read pays, and the memory is what makes the
   read possible. (b) Adapting ones: the profile's choice at each of those points drawn
   by what has worked against this agent in this match (a bandit over its options, by who
   was hit first), so that repeating an answer costs more each time. (b) is what makes
   "one strategy" lose in training; (a) is what teaches the memory's use.
3. **Judged in sets.** A set of matches against one opponent, the memory carried: the win
   rate by the match's number in the set, against the habit opponents (it should rise)
   and the adapting ones (it should not fall), beside the same agent with the memory
   cleared; and the plain measures of the rounds before, which it must not lose. For
   people: the user's sets by match number, and the community's.

**First steps, in order.** The memory block and its test against `evaluate.py`'s counts
of the same matches; the habit knobs, drawn a match; a short run from round 17's agent
with and without the block against habit opponents only (does PPO learn to read it? if
an agent *told* the opponent's habits can't beat one that isn't, the memory won't
either); then round 18 with the whole of it. The agent in the game needs the block
computed in its C++ (`port/agent/observe.cpp`, on `release/next`): the same counts, to
be checked against these as the observation was.


### The "told habits" experiment (15 November): can training use a read at all?

The cheap test before the memory is built: an agent that is simply *told* the opponent's
habits of the match (the answer a perfect memory would converge to) against one that is
not, both trained the same way against opponents whose habits change every match. If
being told does not change how it plays or how often it wins, a memory that has to
estimate the same numbers won't either, and the opponents' habits are what needs work
first.

**What is built** (in a scratch copy while round 17's judging uses the live files; to be
applied after):

- `advantages.py`: each knob of a profile is now a value per match (`Advantages.k`), and
  with `habits=1` the match's are drawn from `HABITS` (the wake-up reversal 0, 0.15, 0.4
  or 0.8 of the rises, `blind` 0 or 1: whether it comes out without reading the agent's
  commitment, the patient guard 0, 0.3, 0.9, the crouching share of its guard 0.3 to 1,
  the throw 0, 0.3, 0.9, the reversal after a recoil guard 0, 0.3, 0.8, the jump-in 0,
  0.2, 0.6). Uniform draws, not yet the community's spread: enough to ask the question,
  not to calibrate a round. Without the new keys a profile plays exactly as before (16
  seeded matches against the `person` profile: the same results to the last count).
- `EfzSB3VecEnv(extra=N)`: N more features after the input history, 0 until written;
  `AdvantagedOpponent` writes `told()` there for the learner at each match's start (a 1,
  then the eight knobs), and nothing for the matches without a profile (the CPU, the
  team, the plain `--vs` matches: all 0, "not told"). Checked on a short-match
  environment: the block equals the opponent's knobs at every step, and a match's last
  view carries its own habits, not the next match's.
- `efz_env.policy.widen`: the start's policy with the first layers widened by zeros (its
  log-probabilities for the same view differ by 3e-5, rounding); `finetune.py --tell
  --vs-habits`; `evaluate.py --detail` (each match's habits, result and the agent's
  knockdown records, for its play *by habit*), `--p1-untold` (the told agent with the
  block blanked).

**The runs.** From round 16's agent, 20M steps, round 17's loop (the pull 0.01, the press
cost 0.002, the team, the combo master, Kanna in a tenth); the `--vs` matches are the
eleven exploiter15s and the eleven exploiter16s, every one with a profile (`person`'s
game part in half, `crowd`'s in half) and its habits drawn each match. Two arms, the same
seeds: `told-exp/told-sN` (`--tell`) and `told-exp/untold-sN`. (Seed 1 first; seed 2
when the judging frees the memory.)

**How it is read**, fixed before the results: each arm's average against the eight
most-met exploiter15s under `person,habits=1`, 64 seeded matches each, its own combos.

- *It reads the habit* if the told agent's play differs by the habit where the untold
  one's does not: the share of the opponent's wake-ups it meets with a meaty, between the
  matches where the opponent never reverses on wake-up and those where it reverses 0.8 of
  the time blind (round 16's agent, 16 matches: a meaty at 83% of the wake-ups whatever
  the habit, and hit back at 31% of the knockdowns against the 0.8 ones); its lows
  against a guard that crouches 0.3 of the time and one that always does.
- *The read pays* if the told agent wins more than the untold one of its seed, and loses
  that margin when the block is blanked (`--p1-untold`).
- Both seeds the same way, or it is said to be undecided.

**The first pair's result (seed 1, 15 November), and why it doesn't answer yet.** 512
matches each against the eight most-met exploiter15s under `person,habits=1`, its own
combos.

| | wins (own HP lost a round) | meaty at wake-ups, opponent never reversing / on 80% | hit back there | lows of its mix-ups, crouch 0.3 / always |
|---|---|---|---|---|
| round 16's agent (the start) | 61% (71%) | 77% / 72% | 10% / 31% | 88% / 89% |
| untold, seed 1 | 73% (66%) | 75% / 72% | 11% / 31% | 86% / 85% |
| told, seed 1 | 75% (67%) | 78% / 74% | 13% / 31% | 85% / 85% |
| told, the block blanked | 72% (67%) | 80% / 76% | 11% / 29% | 88% / 87% |

By the rules above: the told agent does not read the habit (its meaty share falls by 4
points from the opponent that never reverses to the one that does on 80% of its
wake-ups, as the untold one's does by 3 and the start's by 5; its lows are 85% whatever
the guard's height), and being told is worth 2 to 3 points of wins at most (75% against
73% untold and 72% blanked: inside what 512 matches can tell apart). Both arms gained 12
points on the start: 20M steps against opponents whose habits vary is worth that with or
without the block.

It is not yet the answer to "can training use a read", because the told inputs were
hardly learned at all: their weights into the first layer ended at 0.10 to 0.16 (the
policy's) where the other columns' stand at 1.06. They start at zero, the inputs are 0 to
1 beside columns scaled to a unit spread, and Adam at a falling 1e-4 moves each weight
about as far a step whatever its input's size; 20M steps were not enough to make the
block matter. So the test is run again with the one thing changed: `--widen-gain 10`
(`told-gain10-s1`, `-s2`, the told inputs ten times as large on the way in, which is ten
times the learning rate for them alone), read by the same rules against the same untold
runs. If the told agent then reads the habit and wins more, the memory goes into round
18 with a gain; if it still does not, the habits' signal itself is too weak for PPO at
this budget and the opponents' side (2b, the opponents that adapt) carries round 18
alone. Seed 2 of the first pair finishes as planned.

**The whole result (15 November, 20:00): training does not use the read.** Both seeds,
and the rerun with the told inputs ten times as large (`told-gain10-sN`, against the same
untold runs), 512 matches each as above.

| | wins (own HP lost a round) | meaty at wake-ups, opponent never reversing / on 80% | hit back there | lows of its mix-ups, crouch 0.3 / always |
|---|---|---|---|---|
| untold, seed 1 / 2 | 73% (66%) / 73% (66%) | 75% / 72%; 79% / 74% | 11% / 31%; 11% / 28% | 86% / 85%; 86% / 85% |
| told, seed 1 / 2 | 75% (67%) / 74% (65%) | 78% / 74%; 76% / 73% | 13% / 31%; 12% / 30% | 85% / 85%; 86% / 87% |
| told, the block blanked | 72% (67%) / 74% (66%) | 80% / 76%; 75% / 73% | 11% / 29%; 12% / 31% | 88% / 87%; 89% / 88% |
| told with the gain, seed 1 / 2 | 72% (67%) / 68% (69%) | 74% / 73%; 76% / 73% | 11% / 29%; 13% / 30% | 87% / 86%; 86% / 84% |
| the gain, the block blanked | 67% (68%) / 65% (70%) | 77% / 73%; 77% / 76% | 9% / 29%; 13% / 30% | 87% / 87%; 86% / 83% |

- *It does not read the habit*, in either seed, with or without the gain: a meaty at
  three wake-ups in four whether the opponent never reverses or does on 80% of its
  risings (and it is hit back at 30% of those knockdowns for 11%), lows in 84-87% of its
  mix-ups whether the guard crouches 30% of the time or always, a throw in none.
- *The read does not pay.* Told is 2 and 1 points above untold (the blanked one 3 under
  and level): nothing in 512 matches. With the gain the told agent is one and five
  points *under* its untold twin. The gain did what it was for, the policy leans on the
  block (blanked it loses 5 and 3 points more), but what it learned from it is not a
  read: its play by habit is the untold one's.
- So by the rule fixed above the memory is not in round 18, and the game's C++ needs no
  port of it yet. `efz_env/memory.py`, the sets and `evaluate.py --sets` stay (the
  judging in sets needs them, and a module can read the counts: below).

**Why, as far as these runs show.** The habits are worth something to an agent that had
the answers: against the opponent that reverses on 80% of its wake-ups the agent is hit
first at three knockdowns in ten, and against the guard that always crouches it wins 58
to 72% for 79 to 86% against the one that crouches 30%. The answers are a wait and a
punish on the first, an overhead or a throw on the second, and the agent has neither as
a thing it does: it waits at 2-6% of the knockdowns, goes high in 4-7% of its mix-ups and
throws in none, whoever it plays, after 260M steps. PPO at an entropy this low does not
find a three-step answer it has never been paid for, told or not; a habit input can only
choose between things the policy already does. That is the okizeme module's finding from
the other side (the clone has the mix and not the timing, and loses), and it says where
adapting within a match has to be built: as *options that work* (a timed meaty, a timed
overhead, a throw, a wait that punishes: each tried on copies of the game from the
knockdown, as the routes are from a hit) with the choice between them made from what the
match has shown, by count, not by a gradient. The memory's counts are that input.

### The planned okizeme (15 November): options that are timed, chosen by count

**People's okizeme as a library** (`oki_library.py` -> `oki-library.npz`, beside the
combo library). Every knockdown an Ayu player made in the 1,908 matches whose okizeme
touched the riser within 20 steps of the rising without the player being hit first:
8,499 of 15,087 knockdowns, each with its inputs from the knockdown to 20 steps past the
contact, where its player was at each step, and what it was.

| | share | opened the riser |
|---|---|---|
| ground low | 21% | 40% |
| jump high | 21% | 39% |
| jump low (a jump, landing into a low) | 15% | 49% |
| fly (Ayu's air dash) high / low | 10% / 9% | 28% / 39% |
| ground mid | 9% | 23% |
| dash high / low | 4% / 2% | 37% / 38% |
| a cross-up of any kind | 2% | 60-70% |
| a throw | 1% | (all) |

A knockdown lasts 73 steps (69 to 79) from the fall to the riser being up, the same
parts for every character, so an agent that sees it 14 steps late has about a second
left; people's contact comes 0 to 3 steps after the rising in half of these. Their mix is
not the agent's (a ground low in four of five): it comes in by a jump or a flight more
often than on the ground, and a throw is as rare for them as for it.

**The module** (`okiplan.py`, the kind `okiplan`; `python/tests/test_okiplan.py`). When
the agent sees the opponent knocked down and the routes have no step to play:

1. *The time left* is counted on a copy of the game (the steps until the opponent is up).
2. *The options*: the library's entries whose player stood where the agent stands now
   (within 24 pixels, in the air or not as it is), that many steps before their recorded
   rising, and had not yet pressed the move that touched; the closest of each kind, two
   of a kind and ten in all; a wait (a crouching guard through the rising and 40 steps
   more); and the agent's own play. An entry is played so that its recorded rising falls
   on this opponent's: the timing is the knockdown's, which is what the clone lacked.
3. *The answers*: every option is played on copies against a riser that guards
   crouching, guards standing, reverses (its invincible move as it rises, timed as the
   profiles' is), jumps away, or presses a button; the agent's own play goes on after an
   option's inputs, seeing each copy as late as it sees the game. An option's worth
   against an answer is the HP it took less the HP it lost by 70 steps after the rising,
   a first hit of its own counted as at least 1,300 (what its routes make of one) and a
   hit taken as at least 1,200.
4. *The choice*: the opponent's wake-ups so far (the memory's counts, of what the agent
   saw) over a prior of the community's players (a reversal on 0.10 of the risings,
   another move 0.19, a jump or backdash 0.04, a guard the rest, crouching in 0.8 of
   them; the prior weighs as six wake-ups) give each answer a share; an option is drawn
   with the weight exp(expected worth / 200). It varies from knockdown to knockdown, and
   as an opponent shows what it does on rising the draw leans to what beats that.

It decides from what the agent sees (the knockdown, 14 steps late) and plans on copies
of the game as it is, as the routes do: the human limits are kept the same way. A plan
is 60 copies for about 145 steps, a third of a second on one thread. It is built for
evaluations; a person's match needs its plans made beside the game as the live routes
are, and the game itself needs it in C++ as the routes are: neither is done before it is
shown to be worth it.

**The first measure: the `crowd` set** (round 17's agent, its routes planned again, 64
seeded matches against each of the eight; the module as first built: a wait of 24 steps).

| | routes | routes + `okiplan` |
|---|---|---|
| wins (own HP lost a round) | 89.6% (59%) | **94.9% (48%)** |
| by opponent: Sayuri, Ex-Nanase, Mayu, Nanase | 89 / 91 / 92 / 92% | 91 / 94 / 94 / 98% |
| ... Kaori, Mishio, Ikumi, Nayuki | 84 / 97 / 95 / 77% | 97 / 100 / 100 / 86% |
| its okizeme: low / high / a throw / a cross-up | 82% / 6% / 0% / 1% | 14% / 67% / 1% / 4% |
| HP a knockdown is worth to it | -86 | +36 |
| knockdowns it makes a minute | 3.6 | 4.3 |
| throws a minute | 0.01 | 0.27 |
| combos a minute (their damage) | 6.2 (1,597) | 7.6 (1,550) |
| HP it loses a minute | 6,387 | 5,975 |
| presses a second | 2.33 | 2.30 |

Better or level against each of the eight, 5.3 points over the set and a sixth less of
its own HP lost: the first thing since the routes that moves the `crowd` set without a
round of training. The planner chose a library entry at nine knockdowns in ten (its own
play at 5%, the wait at 2%), expecting 830 HP of an option where its own play's
expectation was 240. What it chose is no longer one move, and it is now lopsided the
other way: two in three are overheads (dash, flight and jump-ins), because the prior
says a riser guards crouching four times in five and the draw at 200 HP is close to
picking the best. People's own split is 47% low to 36% high. Against a person who sees
"always high after a knockdown" that is as readable as "always low" was, until the
counts of their standing guards move the draw: the sets below are the test of that, and
the draw's width is the knob.

**Opponents without a profile: the eleven `exploiter16`s, plain** (64 matches each, the
first build's wait of 24): **96.7% (own HP lost 46%) against 91.2% (58%)** without the
module, ten of the eleven as good or better within a match or two (Sayuri's 85.9% from
68.8%, Mizuka's 96.9% from 85.9%, Nayuki's 100% from 89.1%). It draws a throw on 7-13% of
its knockdowns against most of them: the agent's first throws in any round. So the gain
isn't the profiles' guard: policies trained to beat this agent lose to it more with its
okizeme planned.

**In sets** (`--sets 4 --detail`, the eight met opponents with the profile `habits`:
`person` with each habit drawn afresh a set; the module with `carry`): **96.9% (own HP
lost 41%) against 92.0% (52%)**.

| match of the set | 1 | 2 | 3 | 4 |
|---|---|---|---|---|
| without | 90.6% (53%) | 91.4% (50%) | 93.8% (50%) | 92.2% (53%) |
| planned okizeme | 96.1% (42%) | 98.4% (41%) | 96.1% (39%) | 96.9% (40%) |

The wins don't rise through a set: they start at 96%. What the counts move is the
okizeme's own result against the opponents that reverse on wake-up (`wake` 0.4 or more):
worth -53 HP a knockdown in a set's first match and +46 in its third and fourth, the
riser hitting first on 25% of them and then on 17% (against the others +33 and +58;
without the module -238 and -128, the riser first on 31% and 29%). The lean between high
and low does not follow the opponent's guard: 14% lows whether it guards crouching 60%
of the time or 85% and more. So within a set it learns to respect a reversal and not
which height to hit: the standing guard's counts are too few against the prior, or the
copies' answers too coarse (a riser that guards standing guards every option standing).

Not yet shown: the robust draw (`doubt`).

### What people's habits look like in the community's replays (15 November)

Measured while the experiment ran, so that the habit opponents are the community's and not
one player's: every match of the Ayu dataset (1,908, 107 opponent players by pseudonym)
through `tactics.py`, counting the *opponent's* wake-up choice at each of the Ayu player's
knockdowns and its way out of the Ayu player's pressure, by player, by match, and by the
match's number in a set (the same two players, replay ids within 3 of each other: 364
sets, 146 of four matches or more).

| | across players (median; 10th-90th; least-most) | a player's matches: spread, and what chance alone gives |
|---|---|---|
| wake-up: an invincible move | 0.10; 0.01-0.23; 0.00-0.27 (19 players, 150+ wake-ups) | 0.10 / 0.10 |
| wake-up: any move | 0.29; 0.17-0.41; 0.15-0.55 | 0.16 / 0.15 |
| wake-up: guard or wait | 0.67; 0.53-0.82; 0.41-0.83 | 0.17 / 0.15 |
| under pressure: a move | 0.33; 0.29-0.45; 0.27-0.48 (16 players, 400+ guards) | 0.12 / 0.10 |
| under pressure: an invincible move | 0.02; 0.01-0.04; 0.00-0.08 | 0.03 / 0.03 |

- **The habit is the player's, not the match's.** Players differ a great deal (a reversal
  at 1% of the wake-ups or at 27%; a move at 15% or 55%), and a player's matches differ
  from each other by what chance alone gives. So a memory has to last the set: one match
  holds 6-15 wake-ups, too few to tell a 5% player from a 20% one, and a set holds enough.
- **No drift by the match's number.** Over the sets of four or more, the opponent's
  wake-up reversal is 0.117 of the rises in match 1, 0.120 in match 2, 0.099 in 3-4, 0.107
  in 5-8, 0.112 from 9 on; any move 0.289, 0.280, 0.263, 0.288, 0.281; its moves out of
  pressure 0.404, 0.375, 0.389, 0.400, 0.399. Between a set's halves a habit moves by
  5-6 points beyond chance (0.089 where chance gives 0.075; 0.128 for 0.112; 0.101 for
  0.079), in either direction.
- **What this says about the plan.** (1) The experiment's ranges (a wake-up reversal at 0
  to 0.8 of the rises, redrawn every match) are far wider than people's and change far
  more often: it stays the test of whether training can use a read at all, an upper
  bound, and round 18's habit opponents take the community's ranges (per player, kept
  for a set) instead. (2) These counts do not show people changing their habits through
  a set against each other, while the user's results against the agent rose with the
  match's number (10 of 16, 11 of 15, 8 of 9). The two fit if what a person learns over a
  set is *the agent's* holes (the jump-in that lands, the counter to its low) rather
  than a new habit of their own: both players of a human set adapt, and the shares stay
  put. That puts more weight on the plan's 2b (an opponent that finds what works against
  this agent and repeats it, so that a hole costs more each time it is shown) and on a
  memory of *what was done to the agent and how it went*, than on reading the opponent's
  fixed habits (2a). Only two families of habit are counted here (the wake-up, the way
  out of pressure), from one character's matches; it is a pointer, not a proof.

### The rebase on `release/next`, and the parts of round 18 as built (15 November)

**The rebase.** The branch now sits on `release/next` (d2b1fb4: the agents in the game,
the one-file agent format 2, the library's version 10 with `first_intro`), its three code
commits replayed without a conflict. The Python tests pass (67 with the memory's), and two
seeded evaluations of round 16's agent (12 matches against Sayuri's exploiter15 with the
`person` profile; 12 with the routes planned again) give the same result files to the
byte on the old code with the old library and on the rebased code with the library built
from it: the numbers of the rounds before still compare. Round 17's judging was already
running, so it finishes on a frozen copy of the code and library as they were (all of
round 17 judged on one state); the "told habits" runs likewise on theirs.

**The match memory** (`python/efz_env/memory.py`; plan's part 1). 48 features after the
input history (and after what the agent is told, if anything): counts kept as the game
goes, each a share with how much is behind it (count / (count + 3)).

| Group | What is counted |
|---|---|
| The opponent's wake-ups | a move within 16 steps of rising, an invincible one (the invulnerability timer in its first 8 steps, or the frame data's flag), a jump, a backdash; whether the agent was in a move as it rose (a meaty); who was hit first within 96 steps, apart for the agent's meaties and its waits |
| After the opponent's guard ends | a move, an invincible one, a jump, a backdash within 16 steps; who was hit first within 64 |
| The opponent's guard | of its guards on the ground the share crouching; of all the share recoil guards |
| The agent's openings | its first hits and throws by what they found: the opponent crouching, standing, in a move, in the air; the share that were throws |
| The opponent's openings | the same of the agent (in a move, in the air, crouching, thrown), the share from the air; of its attacks' starts the share that hit, and that came from the air |
| The agent's wake-ups | the share the opponent made contact on within 16 steps, from the air, with a throw; the share the agent rose with a move on; who was hit first, apart for those and the others |
| The agent's air attacks | of those that touched the opponent on the ground, the share that hit |
| The set | the matches played in it (up to 4), the share won |

It is made from the view it is given, a step at a time, so given the agent's own view (14
steps late, as `EfzSB3VecEnv` and `Agent` give it) it holds what a person could have seen
by then: inside the human limits. At a match's end the counts are kept for the next
match of the set, scaled by 0.7 (`decay`), and a new set starts from nothing. Checked
against `tactics.py` on the user's 20 recorded matches of 14 November (both sides' views,
the game as it was): a move on wake-up 0.350 of the risings against 0.346, an invincible
one 0.126 against 0.131, a meaty 0.647 against 0.625, jumps and backdashes the same
counts (33, 2); `tactics.py` leaves out the knockdowns within three seconds of a round's
end, the memory cannot know the end is coming and counts them (428 risings for 381). In
an environment the features the learner is given equal a second memory fed the learner's
views, step for step, through match ends and sets (`python/tests/test_memory.py`).

How it reaches a policy: `EfzSB3VecEnv(memory={...}, sets=(1, 2, 3, 4, 5))`
(`finetune.py --memory --sets ...`); `Agent` makes its own from the model's `config.json`
(`memory`: the decay and the frame data's invincible moves by character, so an agent file
carries all it needs); a `--start` without the features is widened with zeros as for the
told block and plays as before (the logits differ by 4e-5: float rounding). `widen(...,
gain)` / `--widen-gain`: the new features are scaled on the way in. The told runs showed
why: the new columns' weights start at zero and Adam moves a weight about as far a step
whatever its input's size, so after 6M steps they stood at 0.1 where the other columns'
stand at 1.06; a gain of g is g times the learning rate for those inputs alone.

**Sets** (`EfzSB3VecEnv(sets=...)`): an environment's matches come in sets against the
same opponent, a length drawn a set. The memory is kept over a set; the habit opponents
draw their habits at a set's start, not a match's (`AdvantagedOpponent.new_match`), as
people's are the player's and not the match's. `info['set_match']`: the match's number
in its set. `evaluate.py --sets N` plays its matches the same way (matches / N
environments, N matches each, the opponent's habits and the agent's memory kept) and adds
the results by the match's number in the set (`by_set_match`): the plan's part 3.

**Opponents that adapt** (`advantages.py`, `adapt=RATE`; `finetune.py --vs-adapt`; plan's
part 2b). A profile's habits now move within a set by how its own choices went. Each time
a wake-up reversal, a reversal after a recoil guard, a throw or a jump-in pays (the agent
hit, or thrown), that habit moves RATE of the way to the most `HABITS` has for it; each
time it costs (the profile hit first), to the least. The guard's height moves toward the
one that would have held (hit while holding a standing guard: crouching more; a crouching
one: less). The patient guard goes up when the profile's own play after a guard is hit,
down when that play hits or when it is thrown holding a guard; the wake-up reversal goes
up when a guard on rising is opened. A hole shown twice is used more the third time,
which is what the user's sets did to the agent and no league opponent has. Each set
starts from the profile (or the set's drawn habits) again. With `adapt=0` a profile plays
as before (the `person` evaluation above: the same matches to the last count).

**People's ranges** (`advantages.py`, `PEOPLE`, `wide=SHARE`). The told experiment's
`HABITS` reach further than people do, on purpose. `PEOPLE` are ranges about as far apart
as the community's players (a wake-up reversal on 0 to 0.3 of the risings, a reversal
after a recoil guard 0 to 0.3, a patient guard 0.2 to 0.9, a crouching share 0.6 to 1, a
throw 0.4 to 0.9, a jump-in 0 to 0.4); `wide` is the share of the drawn sets that take
`HABITS`, the rest take `PEOPLE`. Only the wake-up and the way out of pressure were
measured by player; the other ranges are set around the `person` and `crowd` profiles'
values, which were calibrated to the user's and the community's totals: my estimate.

Not yet done: the same memory in the game's C++ (`port/agent/observe.cpp`): an agent
file of a model with a memory needs it, as a new module's version, with the counts
checked against these as the observation was.

### Releases as agent files (15 November)

The user, 15 November: "From now on, released checkpoints should be packed and published
into the .efzagent format. We should have tools to unpack the checkpoint and finetuning
and further working on any packed version." So a round's agent is released as one agent
file, and the file now carries its training part (the critic, the run's `config.json`,
PPO's settings) beside what a game plays; `unpack_agent.py` gives the model back, and
`finetune.py`, `evaluate.py` and `play.py` take the file itself. docs/agents.md, "Working
on from an agent file", has the format and the checks (round 16's agent: the same weights
to the last bit after packing and unpacking, the same evaluation from the file as from
`avg.zip`). The files handed over before today (rounds 15, 15b, 16) hold the actor only.
An agent with the match memory can't be packed until the game's C++ has the memory.

## The games of 15 November, evening: round 17 in the game, and five things a person sees

The user played round 17's agent (`agent-league17-s1-round17.efzagent`, its routes
planned again at each move's hit) in the game: 31 fights, of them 28 matches replayed
exactly by `from_record.py` (one a demo; two part from the record near frame 250 and
are left out, not looked into yet). **The agent took 13 of 28** (14 November, round 15's
agent: 6 of 20), dealing 7,100 HP a minute and taking 8,000. The user's five points, and
what the records say of each (the measures are now in `evaluate.py`: `combo_ends`,
`taken_combo_ends`, `grabs`; `people` is the community's Ayu, 1,908 matches):

| | agent, 15 Nov (r17) | agent, 14 Nov (r15) | the user, 15 Nov | people's Ayu |
|---|---|---|---|---|
| throws landed a minute (tried) | 0.00 (0.00) | 0.00 (0.00) | 0.03 | 0.21 (0.24) |
| air throws landed a minute (tried) | 0.00 (0.06) | 0.00 (0.00) | 0.29 (0.67) | 0.04 (0.12) |
| air exchanges a minute: won / lost | 0.80 / 1.43 | 0.65 / 0.88 | 1.43 / 0.80 | 0.76 / 1.00 |
| share of the hits it takes that are in the air | 45% | 26% | 31% | 33% |
| combos of 1,000 HP or more ending in a knockdown | 54% | 80% | 76% | 84% |
| ... in the victim's air recovery | 41% | 15% | 16% | 14% |
| after that recovery: caught again / hit back | 28% / 28% | 34% / 34% | 67% / 15% | 33% / 25% |
| okizeme: low / high / throw / crossing | 81 / 7 / 0 / 5% | 79 / 8 / 0 / 2% | | 47 / 36 / 1 / 2% |
| after its guarded string: the guard opened | 18% | 17% | 22% | 24% |
| ... the opponent jumps out | 22% | 17% | 42% | 18% |
| presses a second | 2.11 | 2.51 | | 1.2-2.1 |

1. **"Pressure is too simple: wait patiently and double jump."** Its strings are two
   guards long (median), the next thing after a guard is a low or nothing, and nothing
   in them punishes holding the guard: no throw, 7% overheads. The user jumped out of a
   fifth of them; a jump out is caught 30% of the time and hits the agent back 27%.
2. **"The combo has no trap at the end: the opponent techs out."** Measured, and it is
   round 17's regression: 41% of its bigger combos leave the victim recovering in the
   air (round 15's, planned once: 15%; people: 14%), the agent still in a move of its own
   at that moment more than half the time. The cause is in two places, see below.
3. **"Okizeme has left/right only, no up/down."** 81% lows, as every round's. The
   planned okizeme (above) is the answer and isn't in the game yet.
4. **"Air still weak; the air throw is an important skill."** It loses the air
   exchanges 1.43 to 0.80 a minute and 45% of the hits it takes are in the air (it jumps
   17.7 times a minute against 13.4 the day before). It never air-throws (tried 4 times
   in 62 minutes); the user lands one every three and a half minutes. People's Ayu
   air-throws seldom (0.04 a minute), so the user's rate is a strong player's with other
   characters, not the crowd's: an air throw is worth having as an option, not as a
   rate to match.
5. **"No throw on the ground."** None in 62 minutes, as in every round; people's Ayu
   0.21 a minute. A guard held forever costs nothing against it.

Frontal jump-ins hit it 29% of the time (14 November: 39%; people 14%): round 17's
training against the air exploiters moved that.

### Why its combos let the opponent go (point 2)

The game doesn't let a combo go on past its untech time: once it is out, nothing hits
the victim (`CPlayer::CanAirRecover`), and a button with a direction recovers it in the
air (`TryAirRecovery`), free to act; a victim that presses nothing falls and lies, to
rise into an okizeme. Two things hid the difference from the agent:

- **The planner's copies.** `redteam.Planner` (and the game's, `port/agent/routes.cpp`)
  plays each route on copies whose victim only holds back, and takes the most damage. A
  route that ends in the air with the untech time out and one that ends in a knockdown
  look the same there: both victims fall and lie. Planned again at each hit with 24
  routes (round 17's file), the damage chase picks the first kind more often.
- **The league.** Its policies seldom recover: against the `crowd` set the agent's
  bigger combos end in the opponent's recovery 12% of the time, in the user's 41%.
  So neither training nor judging ever charged for it.

Built (15 November, evening):

- `redteam.Planner(ending=HP)` (`evaluate.py --assist-ending`, the routes module's
  option `ending`, the agent file's `route_ending`, `export_agent.py --ending`): the
  copies' victim presses a button every other step, so it recovers as soon as the game
  lets it, each option is watched to 12 steps past its combo's end, and one that leaves
  the victim lying and not recovered is worth that many HP more. The game's planner does
  the same step for step (`tests.test_agents.PlansAsRedteam.test_same_plans_by_ending`).
- `advantages.py`'s `tech`: the share of the combos a scripted opponent takes in the air
  that it recovers from at the first chance; the profile `crowdt` is `crowd` with
  `tech=0.9`.

**The A/B (64 matches against each of the eight met opponents; the profile `crowdt`, whose
opponents recover in the air from 90% of the combos they take; routes planned again, 24
tried):**

| a knockdown ending worth | wins (own HP lost) | bigger combos ending in a knockdown / a recovery | a combo's damage | okizeme a minute | plans it changed |
|---|---|---|---|---|---|
| 0 HP (damage alone) | 90.6% (58%) | 43% / 57% | 1,569 | 2.33 | |
| 400 HP | 88.3% (60%) | 67% / 33% | 1,445 | 3.23 | 10% |
| 800 HP | 83.6% (64%) | 83% / 17% | 1,358 | 3.80 | 19% |

Against opponents that recover, the routes chosen for damage alone leave more than half
of the bigger combos in a recovery: the league now shows what the user saw. The knob does
what it says (83% knockdowns at 800), and by itself it **loses**: each step gives up
damage for knockdowns that this agent's own okizeme makes nothing of (it loses 86 HP a
knockdown on the `crowd` set, above), and its opponents don't punish a recovery much
either (the agent is hit first after one 17-21% of the time, the user's 28%). So the
ending is worth what the okizeme behind it is worth: it is tried again with the planned
okizeme below, and stays at 0 in a file until that shows a gain.

### The planned okizeme in the game (16 November)

The okizeme planner is the answer to points 3 and 5 that is measured (the crowd set, the
eleven plain exploiters, the sets: five to six points and a fifth less HP lost each
time, with the agent's first throws), so it went into the game's C++ first
(docs/agents.md, "Its okizeme: planned from people's"): the module `okiplan:1` of an
agent file (`port/agent/mix.h`), written by `export_agent.py --okizeme`.

- **The same plan.** The riser's reversal became a schedule (the motion, the button from
  two steps before it is up: on 478 option-knockdowns the same worth as
  `advantages.py`'s step-by-step logic in every one), a copy stops at a round's end, and
  the library's answers (reversals by character, invincible moves) go into the file.
  `tests.test_agents.OkizemeAsOkiplan`: the game's counts of its opponent equal
  `efz_env.memory`'s on a match's views, and at real knockdowns its options, its worth
  against each answer and its mix equal `okiplan.py`'s.
- **A frame's spare time.** A plan as the evaluations made it (10 options, 5 answers,
  the network after every option) costs 2.6 route plans, and a route plan already takes
  the 14 frames it has (112 ms on the user's machine). So the game's planner tries 5
  options, looks 40 frames past the rising, holds a crouching guard after an option's
  inputs instead of running the network on every copy (`after=guard`), leaves out an
  answer expected under 5% of the time (`skip`), and takes 14 more frames, a crouching
  guard, before its first input (`think`): 1.6 route plans in 28 frames. `okiplan.py` has
  the same options, so an evaluation can run exactly what the game does.
- **The game's own code, measured.** `evaluate.py --p1 FILE.efzagent --p1-native`
  (`native_agent.py`) plays an agent file through `port/agent` itself, each match's
  player attached to its environment with its route and okizeme planners. In a first six
  matches against the `crowdt` Sayuri: 477 route plans and 34 okizeme plans made, 30
  played, none dropped.

**The ending with the planned okizeme behind it** (the `crowdt` set, 64 matches each of
eight): the planned okizeme with damage alone 93.8% (own HP lost 51%); with a knockdown
ending worth 400 HP 91.0% (52%), 70% of the bigger combos ending in a knockdown instead of
45% and 1,409 HP a combo instead of 1,567. So the ending doesn't pay on the league even
with an okizeme that is worth something: `route_ending` stays 0 in a file. What the league
can't say is what a person does with a recovery (the user hit the agent back after 28% of
them, these opponents after 20%): a file with it on is for a person to judge.

Running: the game's settings in the Python module, and the file through the game's code,
both on the `crowdt` set.

### The planned pressure (16 November): the first measure

`pressure_library.py` -> `~/data/efz-replays/pressure-library.npz`: 17,963 follow-ups of
people's Ayu to a guarded move of their own, from their first free step beside the
guarding player, with the frame advantage they were done at (median +2 steps). What came
next: another grounded move 60% (mid 43%, low 17%; it opened the guard 11-15% of the
time), nothing for 45 steps 24% (holding 12%, jumping away 9%, backing off 3%), an
overhead from a jump, a dash or a flight 11% (a dash's opened 39%, a flight's 24%), **a
throw 3.6%, which landed 88% of the time**. `pressplan.py` is `okiplan.py`'s planner from
a guard instead of a knockdown: when the agent has seen its move guarded and is free
beside the opponent, the entries done at the same advantage (within 2 steps) and distance
(within 16 pixels), a wait and its own play, each against a guarding player that goes on
guarding crouching or standing, reverses on its first free step, jumps away, or presses a
button; the shares from what this opponent did after its guards (`efz_env.memory`'s
counts) over a prior; the robust draw (`doubt` 0.3).

Round 17's agent, routes planned again, the eight met opponents with `crowdt` (64 matches
each):

| | without | planned pressure |
|---|---|---|
| wins (own HP lost) | 90.6% (58%) | 92.2% (55%) |
| throws landed a minute (tried) | 0.01 (0.01) | 0.29 (0.51) |
| after one of its guarded moves: the guard opened | 12% | 22% |
| ... guarded again / the opponent fought back / reset | 59% / 14% / 15% | 39% / 19% / 20% |
| guards a string | 1.99 | 1.29 |
| combos a minute | 6.7 | 7.4 |

12 plans a match; drawn: the wait 14%, an overhead from a jump 14%, its own play 14%, a
low 11%, a throw 8%, an overhead from a flight 6%. So its pressure now opens a guard about
as often as people's Ayu does (24% in the replays) and throws at people's rate (0.21 a
minute), where it did neither. The wins move a point and a half, inside the noise of 512
matches: these opponents didn't make it pay for the old pressure as a person does, so
the measure that matters here is what it does, not what it wins. Evaluations only so
far; in the game a plan has the 14 frames of the delay and no more (a guard held longer
is the pressure given up), so its port needs a cheaper plan than the okizeme's.

**In the game (16 November).** The live plan is in `pressplan.py` (`live=true`: the
inputs of the delay chosen at the contact, the plan made for where they leave the game,
dropped if the game isn't there) and in the game's planner (the module `pressplan:1`,
docs/agents.md, "Its pressure: planned from people's"), which makes the same plan from
the same contact (`tests.test_agents.PressureAsPressplan`). Through the game's code, three
matches with all three planners: 224 route plans, 17 okizeme plans of 17 knockdowns, and
of 37 guarded moves 16 pressure plans (15 nothing to plan: a hit first, or the agent not
free in time; 6 the game elsewhere: the opponent didn't hold its guard), none late; a
pressure plan 0.6 of a route plan. Running: the live plan and the game's settings on the
`crowdt` set, and the whole file through the game's code.

### The file through the game's own code (16 November)

`evaluate.py --p1 FILE.efzagent --p1-native`, the `crowdt` set (64 matches against each of
the eight met opponents), round 17's agent in each file; beside each the Python agent
with the same settings:

| the file | wins (own HP lost) | the Python agent | okizeme low / high | throws a minute | a guard opened |
|---|---|---|---|---|---|
| routes only (round 17's file, as handed over) | 88.7% (57%) | 90.6% (58%) | 82 / 7% | 0.01 | 12% |
| + the planned okizeme | 93.8% (52%) | 92.6% (51%) | 20 / 62% | 0.08 | 15% |
| + the planned pressure (`round17b`) | **93.8% (52%)** | | 19 / 62% | 0.30 | 16% |

The game's code plays as the Python agents do, within the noise of 512 matches (about a
point and a half). A match has 74 route plans, 5 okizeme plans (every knockdown planned
for, none late, none elsewhere) and 30 guarded moves planned from, of which 11 plans (16
nothing to plan, 2 the game elsewhere). On this machine, loaded: a route plan 144 ms, an
okizeme plan 254 ms, a pressure plan 63 ms.

The live pressure plan in the Python module, alone: 88.9% (58%) with an evaluation's
settings and 88.9% (59%) with the game's, against 90.6% (58%) without and the first
measure's 92.2% (55%) for the plan made at once; throws 0.31 and 0.36 a minute, a guard
opened after 20% and 15% of its guarded moves (12% without). So what it does changes as
the first measure's did, and on this league the wins don't follow: a point or two under,
inside the noise but the same way twice (the wait for the agent to be free, a crouching
guard, may give the turn away; not looked into). With the okizeme in the game's code it
neither adds nor costs (93.8% both). Its worth is against someone who holds a guard
through a low string, which these opponents seldom make pay: a person's to judge. The okizeme's draw with `doubt` 0.3
(93.0%, 52%) is narrower than without (1.3 options a draw against 2.7) and throws less:
the okizeme keeps the weighted draw.

Handed over, `~/dev/efz/tmp` (no path, no player's name in them): `agent-league17-s1-
round17b.efzagent` (routes planned again, the okizeme with the game's settings, the
pressure; 16.0 MB with the training part) and `...-round17b-kd.efzagent`, the same with a
knockdown ending worth 400 HP, for a person to judge what the league couldn't. They need
a game built from this branch: an older one refuses the modules by name.

Still open of the user's five: the air (4: the air throw, and the recovery caught), and
what a combo's ending is worth against a person (2). The okizeme leans high where it
leaned low: 62% overheads against an opponent it has seen little of, moving with the
counts of its standing guards.
