# Training v2: a loop that learns, opponents that defend like people

Plan of 11 November 2026, after rounds 8-13 (`runs/human-ayu/README.md`) and the user's
games of 8-10 November. What was measured, what changes, how round 14 is judged. The
results go in `runs/human-ayu/README.md` ("Round 14") as each phase ends; the last
section here says where each phase stands.

## The goal (written 18 November, the user's words)

"We are not targetting to get an average player, but a very strong agent that can beat
the best players." Within the human limits, which stay the hard line (what it sees 14
frames late, people's input speed, no instant confirm).

What that fixes in this document and the code, where people's numbers appear:

- **People's averages are not a bar.** They are used for two things only: as the prior
  of what an opponent not yet seen will do (a planner's shares before its counts), and
  to describe. A round is not judged against them and an opponent is not made to play
  like them.
- **The bar is the strongest players**: in the community's replays the Ayu players who
  win most (the table in "The games of 18 November"), the opponents who beat Ayu
  players most, and the user; and past them, since the aim is to beat them.
- **Opponents in training are to punish as the strongest do, or harder**, not as the
  crowd does on average. The `crowd` profile (rounds 16 to 19) was set to the replay
  collection's averages, which was this session's reading of "don't overfit on me" and
  is too weak a teacher for this goal: many players, yes; their average, no.

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

## Round 18 (16 November): opponents that recover in the air, and that learn the agent

**1. The exploiters of round 17's agent.** The eleven `exploiter17`s (from each
`exploiter16/league.zip`, the firmer recipe of round 17) all ended: ten held 70% of 64
matches against the bare agent and stopped (Sayuri's, Nayuki's and Makoto's after one
chunk of a million steps, Mayu's after two, Mishio's after five, the others after eight
to thirteen); Nanase's never did in 24 chunks (55-61% at the end). `CHAR/exploiter17/
model.zip` is what the league meets. They beat the agent as it trains, without its
routes; what it does against them with the routes is the round's first measure (below).

**2. The league and the arms.** From round 17's agent (`agent-league17-s1/avg.zip`, 261M
steps), round 14's loop, 20M steps; the league: round 17's (the 46, the `exploiter14`s,
`15`s and `16`s) and the `exploiter17`s; `person` and `crowd` each in a quarter of the
`--vs` matches; `--press-cost 0.004` in every arm (round 17's decision: the input rate is
a human limit, not a thing to trade). The match memory is not in the policy (the told
experiment: training does not use a read); what adapts is on the opponents' side. Three
arms of two seeds, each one change on the one before, on a frozen copy of the code at
52cec3c (`--vs-tech` added):

| Arm | Change | Question |
|---|---|---|
| `agent-league18` | round 17's opponents | the control: what do 20M steps more and the `exploiter17`s give? |
| `agent-league18-tech` | both profiles recover in the air from 0.7 of the combos they take there (`--vs-tech 0.7`, `tech=0.7`) | does it learn combos that end in a knockdown once the other end costs? (a person recovered from 41% of its big combos, the league from 10%) |
| `agent-league18-adapt` | `-tech`, and in half of the sets the profiles' habits are drawn from people's ranges and move within the set by how they went (`--vs-habits 0.5 --vs-habits-wide 0 --vs-adapt 0.3`, sets of 1 to 5 matches) | does an opponent that repeats what worked teach it to close the hole it showed? |

0.7 is my estimate (the league's policies recover from about one combo in ten, the user
from most of those the game allowed; no count of people's own recoveries by player was
made).

Judged by `avg.zip` on 64 seeded matches an opponent with the routes planned again (24
tried), no other module: the `exploiter17`s in the plain game; the `crowd` set and the
`crowdt` set (`crowd` with `tech=0.9`); the 46 with its own combos; and in sets of four
(`evaluate.py --sets 4`) the `learner` set (`crowd` with `tech=0.7`, every set's habits
drawn from people's ranges, `adapt=0.3`) over the same eight opponents. **The rules,
fixed before the runs:**

- An arm's seed can replace round 17's agent if it beats it over the `exploiter17`s and
  is not more than two points under it on the `crowd` set or over the 46. An arm is
  taken only if both its seeds can.
- `-tech` is taken over `agent-league18` if both its seeds end more of their big combos
  (1000 HP or more) in a knockdown on the `crowdt` set than both of `agent-league18`'s,
  and neither is more than two points under `agent-league18`'s mean on the `crowd` set
  or over the `exploiter17`s.
- `-adapt` is taken over `-tech` if both its seeds win more of the third and fourth
  matches of the `learner` sets than both of `-tech`'s, and neither is more than two
  points under `-tech`'s mean on the `crowd` set or over the `exploiter17`s.
- Within the arm taken, the seed that does better on the `crowd` set (as rounds 16 and
  17 chose). Reported, not gates: presses while hit or guarding (the target 2.2 a
  second), the frontal jump-ins' share that hit, wins by the match's number in a set.
- The pick is then measured with the planned okizeme and pressure through the game's
  own code (`--p1-native`) before it is packed.

**3. The result (17 November).** Five runs ended on the 16th; `agent-league18-tech-s2`
was killed by the kernel at 10:00 when six trainers and four planner evaluations filled
the machine's 92 GB (the evaluations were mine and too many), and was trained again from
the start once the others had ended. Every run's `avg.zip` (the ten chunks' mean), 64
matches an opponent:

| Run | `exploiter17`s (11) | `crowd` (8) | `crowdt` (8) | big combos to a knockdown | `learner` sets | their matches 3-4 | the 46 | presses a second, hit or guarding | frontal jump-ins that hit |
|---|---|---|---|---|---|---|---|---|---|
| round 17's agent | 80.1% (66%) | 89.6% (59%) | 90.6% (58%) | 42.5% | 88.1% (58%) | 88.3% | 99.4% (32%) | 2.73 | 46% |
| `agent-league18-s1` | 87.8% (59%) | 93.2% (52%) | 90.8% (53%) | 41.5% | 93.2% (52%) | 92.2% | 99.3% (31%) | 1.89 | 45% |
| **`agent-league18-s2`** | **88.9% (60%)** | **96.9% (52%)** | 93.6% (54%) | 43.5% | 91.4% (53%) | 89.1% | 99.5% (30%) | 2.02 | 43% |
| `agent-league18-tech-s1` | 84.7% (61%) | 92.8% (52%) | 93.2% (54%) | 42.8% | 92.2% (53%) | 92.2% | 99.7% (29%) | 1.92 | 35% |
| `agent-league18-tech-s2` | 86.5% (60%) | 94.5% (52%) | 94.5% (52%) | 41.8% | 92.4% (52%) | 91.0% | 99.3% (31%) | 1.63 | 38% |
| `agent-league18-adapt-s1` | 86.9% (62%) | 91.2% (56%) | 93.4% (54%) | 41.2% | 93.4% (53%) | 91.8% | 98.8% (32%) | 2.07 | 41% |
| `agent-league18-adapt-s2` | 84.4% (61%) | 92.0% (53%) | 91.6% (53%) | 43.6% | 90.6% (53%) | 89.5% | 99.2% (31%) | 1.83 | 34% |

By the rules:

- Every seed of every arm can replace round 17's agent: four to nine points over it
  against its own exploiters, over it on the `crowd` set, level over the 46.
- `-tech` is not taken. Opponents that recover from 0.7 of the combos they take in the
  air did not move how its combos end: 42.8% and 41.8% of the big ones in a knockdown
  for 41.5% and 43.5% without (round 17's 42.5%), and its first seed is 3.6 points under
  the control's mean against the `exploiter17`s. So the answer to the arm's question is
  no: an ending that costs in training is not enough for the policy to learn the other
  ending, at this weight and in 20M steps. The combos' endings stay the routes' business
  (the planner's `--ending`, which a person has to judge: the `-kd` file).
- `-adapt` is not taken: 91.8% and 89.5% of the third and fourth matches for `-tech`'s
  92.2% and 91.0%. No run gets better within a set against an opponent that repeats what
  worked: by the match's number (128 matches a cell, so about three points of noise)

  | Run | match 1 | 2 | 3 | 4 |
  |---|---|---|---|---|
  | round 17's agent | 88.3% | 87.5% | 89.8% | 86.7% |
  | `agent-league18-s1` | 94.5% | 93.8% | 93.0% | 91.4% |
  | `agent-league18-s2` | 94.5% | 93.0% | 87.5% | 90.6% |
  | `agent-league18-tech-s1` | 94.5% | 89.8% | 90.6% | 93.8% |
  | `agent-league18-tech-s2` | 94.5% | 93.0% | 90.6% | 91.4% |
  | `agent-league18-adapt-s1` | 96.9% | 93.0% | 93.0% | 90.6% |
  | `agent-league18-adapt-s2` | 93.8% | 89.8% | 89.8% | 89.1% |

  Round 18's runs all start a set higher than round 17's agent and lose three or four
  points by its end, the arm trained against such opponents no less than the others. As
  the told experiment said: what adapts has to be outside the policy (the planners'
  counts), and these sets are the measure for it.
- Within `agent-league18` the second seed, by the `crowd` set (96.9% for 93.2%). It is
  also the best against the `exploiter17`s, and the only run that holds the hardest of
  them, Nayuki's, over half (67%; round 17's agent 41%, the others 39-53%); Ikumi's 72%
  for 59%. Its weak cell is the third match of the `learner` sets (87.5%).

**Round 18's agent is `agent-league18-s2/avg.zip`** (281M steps). What 20M steps more and
the `exploiter17`s gave, against round 17's agent: 80 to 89% against the opponents trained
to beat round 17's, 90 to 97% on the `crowd` set with less of its own HP lost (59 to 52%),
and 2.0 presses a second while hit or guarding for 2.7 (the target was 2.2: reached, with
the press cost at 0.004 in every arm). Not moved: the 46 (99.5%), how its combos end, and
the frontal jump-ins that hit it (43% for 46%; the `-tech` and `-adapt` runs took fewer,
34-41%, which I have no account of and did not gate on).

(On those fewer jump-ins: all four runs with opponents that recover in the air guard more
of them, 55-60% for the control's 49-51%. An opponent that recovers comes down on the
agent attacking, so those arms met more attacks from the air; a guess, with nothing
measured behind it. If the next round wants the jump-ins guarded, `--vs-tech` is a
cheaper way to try than the jump-in exploiters were.)

**4. The pick as the game plays it.** `agent-league18-s2-round18.efzagent`: the pick
with `round17c`'s parts as they are (`export_agent.py --parts-from`: the routes planned
again, the planned okizeme and pressure, the catch). Through the game's own code
(`--p1-native`), 64 matches an opponent, beside `round17c` (round 17's agent, the same
parts):

| | the `exploiter17`s (704) | `crowd` (512) | `crowdt` (512) | presses a second, hit or guarding | frontal jump-ins that hit |
|---|---|---|---|---|---|
| `round17c` | 96.9% (49%) | 94.9% (48%) | 93.8% (50%) | 2.25 / 2.64 / 2.72 | 49% / 33% / 50% |
| `round18` | 95.5% (47%) | 95.3% (45%) | 95.7% (48%) | 1.57 / 1.89 / 1.90 | 41% / 37% / 39% |
| round 18's agent, routes only (Python) | 88.9% (60%) | 96.9% (52%) | 93.6% (54%) | | 43% / 28% / 36% |

- **With the game's modules the two files win as often**: a point and a half under on
  one set, two over on another, level on the third, each difference inside the noise
  (about a point and a half on 512 matches). The exploiters of round 17's agent, which
  beat it in one match of five when it plays with its routes alone, take 3% from the
  whole `round17c`: they were trained against the bare policy, and its okizeme and
  pressure are not what they learned to answer. So what round 18's training gained on
  them (80 to 89%) the modules had already covered, by other means.
- **What is left of the round in the file**: two to three points less of its own HP lost
  on every set, 1.6-1.9 presses a second while hit or guarding for 2.3-2.7 (the modules
  do not change that; it is the policy's), and fewer jump-ins that hit on two sets of
  three.
- **The leagues no longer tell whole agents apart.** Everything here is at 94-97%. The
  next measure has to be opponents trained against the agent as the game plays it (the
  file through `--p1-native` as the training's opponent; not built), or people.
- Round 18's file a match on `crowdt`: 73 route plans, 5 okizeme plans (none late), 11
  pressure plans, 4 recoveries looked at for a catch, of which 0.7 with a sure throw; a
  route plan 100 ms, an okizeme plan 184 ms, a pressure plan 48 ms, a catch 14 ms. The
  recoveries caught: 44% for 34% without the modules; air throws 0.36 a minute.

Handed over, `~/dev/efz/tmp/agent-league18-s2-round18.efzagent` (16.0 MB with the
training part; no path under a home folder, no login or mail name, no player's name;
unpacked once: the model and its critic back within 5e-05). It needs the game of
`release/next` at c45725f or later, as `round17c` does.

## The air (16 November): the recovery caught, and the jump at the agent

The user's fourth point of 15 November ("Air still weak. In-air throwing is a very
important skill the agent should have"), in numbers of that session: the agent caught
the user again after 28% of the user's air recoveries and was hit back after 28%, the
user caught it after 67% of its own; air throws 0 a minute against the user's 0.29; air
exchanges won 0.80 a minute and lost 1.43. Two situations of it have an event a planner can start from, as the
knockdown and the guarded move have.

**1. The opponent recovers in the air out of the agent's combo.** `air_library.py`
(`~/data/efz-replays/air-library.npz`: 3,808 recoveries out of Ayu players' combos in the
1,908 matches, the player's inputs from the recovery to the next contact, where both
were at each step; the match's id, the side and the opponent's character, no player's
name). What people do there, and how it goes:

| The player's next | Share | Caught (hit or thrown) | The player hit first |
|---|---|---|---|
| a move in the air | 47% | 21% | 15% |
| a move from the ground | 17% | 18% | 12% |
| a jump, no move | 14% | 26% | 15% |
| nothing | 10% | 18% | 17% |
| **an air throw** | **7%** | **51%** | **7%** |
| backing off | 5% | 18% | 9% |

The recovery holds its player 27 steps at the median (15 to 36), and the game lets it be
thrown in them (`src/ayu.cpp`: an air throw starts on C with forward held, within 100
pixels of an opponent in the air that is in no hit reaction and no guard; the recovery's
actions 0x9d and 0x9e are neither), while nothing else touches it. That is the user's
point from the game's side: the air throw is the one catch that does not wait for the
recovery to end. Out of their recoveries the opponents pressed a move 38% of the time
(the player then hit first in 29% and caught them in 15%), fell without anything 35%
(caught 45%), dashed 12%, jumped again 10%, held a guard 5%.

**2. The opponent jumps at the agent.** `air_library.py --kind jump`
(`~/data/efz-replays/jump-library.npz`: 6,207 forward jumps begun within 320 pixels of an
Ayu player on the ground). The jumper attacked in the air in 72% (half of those within
24 steps of the jump's start), landed without attacking in 14%, jumped again or dashed in
12%; it crossed sides in 21%; it was down 54 steps after the jump began at the median.

| The player's answer | Share | Hit the jumper | Guarded it | Was hit |
|---|---|---|---|---|
| a move from the ground | 46% | 25% | 7% | 23% |
| a guard held | 20% | 0% | 82% | 12% |
| a move in the air | 15% | 27% | 3% | 21% |
| a jump, no move | 11% | 4% | 31% | 29% |
| nothing | 8% | 38% | 13% | 26% |

People gamble on the jump as often as they guard it, and win the gamble as often as they
lose it. The guard-on-sight module of 14 November lost wins because it guarded every
jump through; a planner can take the gamble only where the copies say it wins.

**The planners** (`airplan.py`: the modules `airplan` and `jumpplan`, built on
`okiplan.py`'s planner). As the okizeme's: the library's entries whose player was where
the agent is, as many steps after the event as have passed, tried on copies of the game
against the opponent's answers, one drawn by its expected worth.

- *After a recovery*: the entries; an air throw of its own timing (C with forward held
  after 0, 4 or 8 steps in the air, or 7, 11 or 15 steps into a jump at the opponent);
  back held; its own play. Against an opponent that falls, guards, presses a button,
  jumps again or dashes back; the shares from what this opponent did out of its
  recoveries so far, over the community's.
- *At a jump* (the agent on the ground, the jumper within 260 pixels): the entries; the
  jump with an air throw at three timings; a standing guard held until the jumper is
  down; its own play. Against a jumper that attacks at once, attacks 10 steps before it
  lands, lands and guards, lands and presses a low, or jumps again; the shares from this
  opponent's jumps over the community's (an early attack 0.40, a late one 0.32, none
  0.12 and 0.04, another jump 0.12).
- `think`: the plan made for the game as it will be that many steps on, back held until
  then, and dropped if the game is not there: what a planner beside the game can do
  (the first measure plans at once, which the game cannot).

**The catch, measured.** Round 17's agent with its routes planned again, the `crowdt` set
(the opponents recover from 0.9 of the combos they take in the air: 4.5 recoveries a
match), 64 matches an opponent:

| | Wins (own HP lost) | After the opponent's recoveries: caught / hit back | Air throws a minute, landed (tried) |
|---|---|---|---|
| no module (512 matches) | 90.6% (58%) | 37% / 22% | 0.00 (0.02) |
| the options against the answers, first four opponents (256) | 85.2% (60%); none: 88.7% (61%) | 37% / 21%; none: 38% / 26% | 0.15 (0.38) |
| **a sure throw or its own play** (512) | **91.2% (56%)** | **44% / 18%** | **0.34 (0.36)** |

- *Weighing options against answers does not pay here.* The copies gave the option drawn
  688 HP of expected worth against 367 for the agent's own play, and the matches gave
  nothing: what a recovered opponent does next is not one of five scripts, and the best
  of eleven options by five samples each is mostly the luckiest. The agent's own play
  after a recovery was already people's (it catches 37%; the community's Ayu players
  33%).
- *Why the air throw works for people, from the library*: of its 139 catches every one
  lands on the last step of the recovery as recorded, which is the throw ending it. The
  throw is pressed inside the recovery (a step before, at the median), from 38 pixels at
  the median (19 to 103). It is not a read: the opponent cannot answer.
- *So the planner looks for that and nothing else* (`sure`, the default; `matrix=0`
  leaves the rest to the agent's own play): C with forward held after every second step
  of holding forward, of a second jump or a dash at the opponent, or of a jump from the
  ground, each on a copy until the recovery's end; the one that catches soonest is
  played, and without one nothing is changed. A throw exists after 16% of the recoveries
  (the agent in reach: 34 pixels at the median where one is found, 96 where none is,
  with 13 to 20 steps of the recovery left when it sees it), and 94% of those tried land:
  0.34 a minute, the user's rate (0.29). Seven points more recoveries caught, four fewer
  answered with a hit, two points less HP lost; the wins level within the noise.
- The limit is reach, not timing: the recoveries of this set come where the opponent's
  untech time runs out, mid-combo, often with the agent a move's length away.

**In the game** (`port/agent/mix.h`'s `Catch`, `BeginThrow`; the module `airthrow:1`,
`export_agent.py --air-throw`): the sure throw alone, since it needs no library, no
answers and no counts. Planned on the frame the recovery begins, over the 14 frames
until the agent sees it (its inputs for them chosen at once, as the pressure's), played
when it sees the recovery if the game is where the plan expected; at most 32 throws of
at most 60 frames a plan. `tests.test_agents.CatchAsAirplan`: the game's plan is
`airplan.live_throw`'s (the view expected, the recovery's frames left, the throw).

**The catch through the game's own code** (`--p1-native`: round 17's file with its routes,
okizeme and pressure, and the same with `airthrow:1`; the `crowdt` set, 512 matches each):

| | Wins (own HP lost) | After the opponent's recoveries: caught / hit back | Air throws a minute, landed (tried) |
|---|---|---|---|
| routes, okizeme, pressure (`round17b`) | 93.8% (52%) | 36% / 23% | 0.01 (0.02) |
| + the catch (`round17c`) | 93.8% (50%) | 43% / 19% | 0.30 (0.32) |

The game's code does what the Python planner did: seven points more recoveries caught,
four fewer answered with a hit, the wins level. (The frontal jump-ins that hit it: 50% of
576 for 42% of 617; the Python measure had 36% for 38%. Not followed up: one of them is
noise, or the throws leave it in the air more often.) Handed over:
`agent-league17-s1-round17c.efzagent` (16.0 MB, with the training part; no path under a
home folder, no player's name), which needs a game built with `airthrow:1`.

**The jump at the agent, first measure** (`jumpplan`, the plan made at once; round 17's
agent with its routes against the first four `exploiter17`s in the plain game, 256
matches each): 89.1% (own HP lost 62%) for 85.5% (63%) without; the frontal jump-ins hit
it 29% of the time for 37%; air exchanges won 1.07 a minute for 0.78; 2.6 plans a match,
of which a jump with an air throw in two of five, a move from the ground in one of five,
a guard in one of ten. A gain of the size of the noise on four opponents, with the plan
made at once; the other seven and the plan a game could make (`think=6`: back held six
steps while it is made, dropped if the jumper did something in them) are running.

**The jump at the agent, over the eleven** (round 17's agent with its routes against all
the `exploiter17`s in the plain game, 704 matches a row):

| | Wins (own HP lost) | Air throws a minute, landed (tried) | Air exchanges a minute, won / lost | Frontal jump-ins that hit |
|---|---|---|---|---|
| no module | 80.1% (66%) | 0.00 (0.02) | 0.78 / 1.06 | 46% of 1,384 |
| `jumpplan`, the plan made at once | 84.1% (64%) | 0.24 (0.30) | 1.02 / 1.03 | 46% of 1,324 |
| `jumpplan`, `think=6` (4 entries, 40 steps, a guard after an option) | 83.2% (66%) | 0.22 (0.26) | 0.96 / 1.07 | 44% of 1,380 |

Four and three points, about two and one and a half times the noise of 704 matches, the
same way in both. What it buys is not the guard: the jump-ins that hit it are as many.
It is the jump met in the air, with an air throw in two plans of five (2.3 plans a
match): a quarter more air exchanges won. The plan a game could make (six steps of
holding back while it is made, dropped if the jumper acted meanwhile) keeps three of the
four points. Not in the game yet: it needs its library in the agent file and its answers
in `mix.cpp`, as the okizeme's; and the jump-ins that hit are still the open half of the
user's point.

**The same on round 18's agent** (17 November; `agent-league18-s2` with its routes, the
plan made at once, the same 704 matches): 88.6% (59%) for 88.9% (60%) without. The air
throws are there as before (0.26 a minute landed of 0.31 tried, air exchanges won 1.16 a
minute for 0.92, lost 1.04 for 1.15) and the wins don't move; the frontal jump-ins that
hit, 42% for 43%. So the four points on round 17's agent were a hole that round 18's
training closed by itself, and on wins the planner is not worth its port to the game.
What it still gives is what the user asked for by name, a jump met with an air throw
(none without it), at no cost: whether that is worth a library in the file and its
answers in the game's code is the user's call.

## Opponents trained against the whole agent (17 November)

Round 18's file and `round17c` win 94-97% of everything the leagues have, because every
exploiter so far was trained against a bare policy: what a person meets in the game (the
policy with its routes, its planned okizeme and pressure, its catch) no opponent has
ever trained against. So the next exploiters do.

**`finetune.py --vs FILE.efzagent --vs-native`**: a `--vs` opponent that is an agent file
is played by the game's own code in the training's matches and in the evaluation's
(`native_agent.NativeOpponent`: a player of the file attached to each of its matches,
as `evaluate.py --p1-native` attaches P1's; `EfzSB3VecEnv.opponent_controls`, a hook
that lets a player 2 write its own control bytes). The file plays with its own reaction
time and settings. Checked: with a file without planners the attached player's bytes
are the file's player's for the same views; the same bytes again on a second run and
with its players' steps on threads (`tests.test_agents.NativeAsOpponent`).

What it costs: the file's plans are made to their end inside the step that needs them
(about 100 ms a route plan, 70 a match), so a training process makes about 1,250 steps a
second whatever its number of matches (threads help only when two matches plan on the
same step), a tenth of training against a bare policy; and each player holds 20 to 50 MB
of game copies, so a trainer of 48 such matches with a 64-match evaluation peaks at
about 5 GB once the chunk's players are closed before the evaluation (8 GB before that
was done: the first six runs, two of which I stopped and started again for the room).

**The `exploiter18`s**: for each of the eleven characters, from its `exploiter17`,
against `agent-league18-s2/round18.efzagent` (the file handed over), round 17's recipe
otherwise (`--focus air` at 0.05, Kano's `charge`, Mizuka's `setup`; 64 matches an
evaluation; the stop at 70%), 12M steps more at most. Before any training, the
`exploiter17`s against the whole agent, 64 matches each (as P1: their wins): Nayuki's
12%, Sayuri's 11%, Mayu's 6%, Ikumi's 5%, Nanase's 2%, Kaori's 0%.

### The first to end: Nayuki's, and what it found (17 November)

Nayuki's `exploiter18` held 72% of 64 matches after 6M steps and stopped (12% before
any training; 28, 16, 52, 55, 50% on the way). The same 64 matches before and after, the
agent's side of them:

| the whole `round18` against Nayuki's exploiter | before (its `exploiter17`) | after 6M steps |
|---|---|---|
| the agent's wins | 88% | 28% |
| damage a minute: the agent's / the exploiter's | 10,200 / 6,300 | 7,400 / 9,000 |
| the agent's bigger combos ending in a knockdown / in a recovery | 87% / 12% | 55% / 44% |
| after such a recovery: the agent catches it / is hit back | 57% / 10% | 23% / 47% |
| the agent's throws a minute | 0.88 | 0.40 |
| its wake-up reversals that hit | 47% | 32% |
| two of its whiffed moves punished (`0xc9`, `0xcc`) | 3%, 4% | 31%, 29% |
| the exploiter's frontal jump-ins a minute (hit) | 4.5 (33%) | 2.8 (13%) |

It stopped jumping in, learned not to be thrown, and **recovers in the air out of the
agent's combos and hits back**: the user's point 2 of 15 November, found by an opponent
because it trained against the agent as the game plays it (round 18's `--vs-tech`
opponents recovered and punished nothing, and the learner they were shown to doesn't
choose its combos: the planner does).

So the planner's knockdown ending, tried again where a recovery is punished: `round18`
with `route_ending` 400 and 800 (the same file otherwise; `export_agent.py --parts-from
FILE --ending HP` now changes the setting of the routes it takes, it was ignored
before), by the game's code, 64 seeded matches against Nayuki's `exploiter18`:

| a knockdown ending worth | wins (own HP lost) | bigger combos ending in a knockdown / a recovery | after a recovery: hit back | a combo's damage | its damage a minute |
|---|---|---|---|---|---|
| 0 HP (`round18`) | 45% (85%) | 55% / 44% | 53% of 192 | 1,650 | 7,900 |
| 400 HP | 25% (88%) | 85% / 15% | 45% of 93 | 1,531 | 7,200 |
| 800 HP | 30% (90%) | 90% / 9% | 38% of 69 | 1,427 | 6,900 |

**It loses here too**, by 15 to 20 points (two standard errors of a difference of 64
matches near 40% are about 17, the seeds the same: one opponent, so a lead and not a
proof). The knob does what it says, the recoveries fall from 192 to 69, and the damage
it gives up is not paid back by the okizeme that follows (40% more knockdowns planned
for: 546-560 for 388). Twice measured, against opponents that recover and don't punish
and against one that does: the ending stays at 0. What is left of point 2 is the other
half, what the agent does when its combo does end in a recovery (it is hit back in half
of them): the catch looks at a recovery only when a throw is sure, and the policy,
trained against opponents that never recovered, is in a move of its own two times in
three.

Why the knockdowns pay nothing, from the same matches: this opponent has learned the
agent's okizeme. An okizeme of the agent's is worth 18 HP to it at 0, -122 at 400 and 33
at 800 (the attacker's hit in 28-33% of them, the riser's in 17-22%), against the 120
to 220 HP of damage a combo that the ending gives up. And the fewer hits back change
nothing that shows: the opponent's damage is 8,550 to 8,700 a minute at all three, so
what it wins by is elsewhere (its own openings: the two whiffed moves it punishes, the
agent's jump-ins it stops), not in the recoveries. The hit back after a recovery is
real, and here it is not what decides.

(The agent's wins differ between the exploiter's own evaluation, 28%, and this one, 45%:
other seeds and the agent as player 1; 64 matches each.)

### The learner with its planners: `finetune.py --module` (17 November)

The other half of the same gap. The league's learner has always trained as a bare policy
(round 15's `-routes` arm apart) and is then played with its routes, its planned okizeme
and pressure and its catch. Round 18 showed what that costs: what 20M steps taught the
policy against the `exploiter17`s (80 to 89% of them with the routes alone) the planners
already did by other means (97% and 96% as whole agents). A share of every round goes to
steps the game never asks of the policy.

`--module KIND:key=value,...` (several; `evaluate.py --p1-module`'s kinds and options)
makes the learner play with those modules in the training's matches and in its
evaluations (`efz_env.sb3.ModularLearner`, which `--assist`'s routes already used; the
planners are the Python ones, with the options that play as the game's do). A module's
steps are kept out of the policy's loss and the critic learns from all of them, as with
`--assist`. What had to be added: the wrapper tells a module its batch and shows it the
learner's delayed views where an `Agent`'s are (the planned okizeme and pressure keep
their count of the opponent's answers from them), and passes on the environment's
attributes to the wrappers around it (`--press-cost` reads the input history).

A trial (round 18's agent, 16 matches against Nayuki's and Sayuri's `exploiter17`, two
chunks of 16,384 steps, the game's four modules: routes planned again with 24 tried,
`okiplan` and `pressplan` with the game's options, `airplan` with the sure throw only):

- **The modules play 27-28% of the learner's steps**: the routes 14-15%, the okizeme
  4-8%, the pressure 6-9%, the catch 0.2% at most. A bare learner spends that quarter of
  its steps (and more of its reward: they are the steps around its hits and knockdowns)
  on play the game replaces.
- It costs: about 160 plans in 16,384 steps, each on copies of the game in the training's
  own process, so about 400 steps a second with 16 matches where a bare learner makes
  2,300 with 128; the plans, not the matches, set the pace. Measured afterwards with 128
  matches (one rollout of 131,072 steps, the machine loaded): 560 steps a second, 2,557
  plans (about 85 ms each, most of the time), the process 5.2 GB; so 20M steps in about
  ten hours without the evaluations.
- Memory: each planner holds its own batch of game copies (26 to 35 of them, 20-50 MB
  each), so a set of the four is about 2.5 GB whatever the number of matches. The
  evaluations in the training's process use the training's set; each evaluation worker
  has its own.
- The evaluations are plan-bound too. With two workers (the trial again, Nayuki's
  `exploiter18` added: 64 matches an evaluation) one took 580-630 s, about 19 s a match
  a worker on a machine that six other trainers were loading, where a bare learner's
  takes under 4 s; the three processes held 10.5 GB at most. Round 18's evaluation
  (1,300 matches) would take two hours a chunk at that pace.

### Round 19: the plan (17 November, before the `exploiter18`s have ended)

Fixed before the runs, as every round's. From round 18's agent (`agent-league18-s2/
avg.zip`, 282M steps), round 14's loop, 20M steps, `--press-cost 0.004`, `person` and
`crowd` as in round 18's control arm (no `--vs-tech`, no habits: neither taught
anything). The league: round 18's, and the eleven `exploiter18`s as they end
(`CHAR/exploiter18/model.zip`; they are plain policies, so they cost nothing more than
the others to meet). Two arms of two seeds:

| Arm | Change | Question |
|---|---|---|
| `agent-league19` | the `exploiter18`s in the league | the control: does a bare learner gain on opponents that learned the whole agent? |
| `agent-league19-whole` | the learner trains and is evaluated with the game's four modules (`--module`, the trial's) | does the policy learn more of what is left to it when the planners play their part in training? |

Both arms evaluate 8 matches an opponent a chunk where round 18 played 16 (fixed after
the trial with workers and before the runs: with the planners an evaluation of the 91
opponents is about 730 matches, half an hour to an hour with four workers, so a
`-whole` run is sixteen to twenty hours where a control run is four or five). The
evaluations choose the league's opponents (`--pfsp`, over the last three: 24 matches an
opponent where round 18 had 48) and nothing else: the judging is the native one below.

Judged as a person meets them: each run's `avg.zip` packed as an agent file with
`round18`'s parts and played by the game's code (`evaluate.py --p1-native`), 64 seeded
matches an opponent, on the `exploiter18`s (704 matches), `crowd` and `crowdt` (512
each), with `round18` itself on the same matches as the mark. The rules:

1. A run can replace `round18` if it wins more of the `exploiter18`s by more than four
   points (two standard errors of a difference on 704 matches near 50-90%) and is not
   more than two points under it on `crowd` or on `crowdt`.
2. `-whole` is the arm taken if both its seeds are over both of the control's on the
   `exploiter18`s; the control otherwise (it is the cheaper way to train).
3. Within the arm, the seed with the better `crowd`, as in round 18.
4. The `exploiter18`s are opponents the round trains against, so a gain on them is a gain
   on seen opponents: what a run does against opponents that never met it is `crowdt`'s
   and a person's to say. If rule 1 passes, exploiters of the new file (as the
   `exploiter18`s were made) are the next measure; if nothing passes, the round says the
   league's way of training has run out against the whole agent, and the next work is in
   the planners and their options rather than in the policy.

Own HP lost, presses a second, frontal jump-ins that hit and the modules' plans a match
are reported beside the wins and decide nothing.

## The games of 16 November, evening: `round17c` in the game (measured 17 November)

The user played `round17c` (round 17's policy with the routes planned again, the planned
okizeme and pressure and the catch) in the game: 23 matches, all replayed exactly by
`from_record.py`, 56 minutes. **The agent took 7 of 23** (15 November, round 17 with
routes only: 13 of 28; other characters and another evening, so not a step back by
itself), dealing 6,700 HP a minute and taking 8,800. The user's points, and what the
records say of each (`people` is the community's Ayu, 1,908 matches, 4,800 minutes;
scratch `six.py` and `trap.py` for the new counts):

| | agent, 16 Nov (`round17c`) | agent, 15 Nov (r17) | the user, 16 Nov | people's Ayu |
|---|---|---|---|---|
| a combo's damage, on average | 1,263 | 1,298 | 942 | |
| combos of 1,000 HP or more ending in the victim's air recovery | 41% | 41% | 16% | 14% |
| after that recovery: caught again / hit back | 33% / 29% | 28% / 28% | 61% / 12% | 33% / 25% |
| the corner trap (a flight back, then 214A, in a combo): matches with one | 0 of 23 | 0 of 28 | | 52 of 1,908 |
| flights a minute | 2.2 | 2.0 | | 5.5 |
| ... that end in a hit or a guard / in being hit | 15% / 10% | 10% / 6% | | 32% / 14% |
| okizeme: the commonest opener's share; the attacker's hit; worth | 35%; 38%; +234 HP | 80%; 19%; +25 HP | | |
| a frontal jump-in at it hits | 43% of 68 | 29% of 103 | | 14% |
| air exchanges a minute: won / lost | 0.81 / 1.94 | 0.80 / 1.43 | 1.94 / 0.81 | 0.76 / 1.00 |
| the opponent's invincible moves: it is hit by | 25% of 87 | 32% of 88 | 30% of 138 | 21% |
| ... the ones that miss it, punished | 9% (6 of 65) | 7% (4 of 60) | 36% | 12% |
| 236C a minute; of those that don't hit, punished | 1.02; 71% (15 of 21) | 0.95; 50% | | 0.48; 40% |
| 623C a minute; of those that don't hit, punished | 0.25; 3 of 4 | 0.50; 62% (8 of 13) | | 0.12; 53% |
| what a punished 236C / 623C costs | 730 / 1,770 HP | 820 / 1,960 HP | | 640 / 380 HP |
| its move recoil-guarded: it recoil-guards back | 0 of 2 | 0 of 8 | | 28 of 324 |
| throws landed a minute (tried) | 0.19 (0.21) | 0.00 (0.00) | 0.08 | 0.21 (0.24) |
| air throws landed a minute (tried) | 0.12 (0.12) | 0.00 (0.06) | 0.33 (0.58) | 0.04 (0.12) |
| presses a second | 1.99 | 2.11 | | 1.2-2.1 |

1. **"Combo damage is good; it still fails to catch escapes. Ayu players end corner air
   combos with a flight back and 214A to catch the recovery."** Both halves hold. The
   combos are worth what they were, and 41% of the bigger ones still end in the victim's
   air recovery (people: 14%), after which it catches a third and is hit back as often;
   the user catches 61% of the agent's. The catch that is in the file (`airthrow:1`)
   landed 0.12 air throws a minute, all it tried: it only looks at a recovery when a
   throw is sure. The trap the user names is in the community's replays exactly as
   described: a flight back (0xa6) then 214A (0x100) inside a corner combo, 49 of the 57
   times it appears. It is a few players' habit, not the crowd's (52 of 1,908 matches,
   never more than two a match), and it works: when the victim recovers the 214A hits 8
   of 13, and when it doesn't the attacker has lost nothing (36 of 38 times nothing
   happens and the knockdown stands). The agent has never done it. The commonest catch
   in the crowd is plainer, an air normal after the last hit (0xd0: 62% of 162
   recoveries caught in the corner).
2. **"More variance and mix-ups, but still green: easy to predict and to see. Expert
   Ayu players fly and land in ways that are hard to predict."** The variance is there
   in the okizeme (the commonest opener 35% of them where it was 80%, the attacker's hit
   38% for 19%, worth 234 HP a knockdown for 25). The flights are not: 2.2 a minute
   against people's 5.5, and only 15% of them end in a hit or a guard (people's 32%):
   three in four of the agent's flights lead to nothing. No module plans an approach:
   routes, okizeme, pressure and the catch all start from a hit, a knockdown or a guard.
3. **"Still easy to hit with invincible moves; it doesn't bait."** It is hit by a
   quarter of the user's invincible moves, about people's rate (21%), and by half of the
   12 on wake-up (people: 47%). What it lacks is the other half of a bait: of the 65 that
   missed it, it punished 6 (the user punishes 36% of the agent's; people 12%), and none
   of the 6 on wake-up (people: a third).
4. **"Throws are coming up."** 0.19 ground throws a minute, people's rate (0.21), from
   none.
5. **"Risk management: a vulnerable move guarded or recoil-guarded (623) leaves Ayu open
   to a big air combo; it should mind the hit back."** It does 236C twice as often as
   people and 623C twice as often, and when they don't hit they are punished 71% and 3
   times in 4 (people: 40% and 53%), for 730 and 1,770 HP a time (people: 640 and 380):
   its invincible moves are thrown where a miss is at its most expensive. Its moves were
   recoil-guarded only twice in these matches (ten times over the two evenings) and it
   never recoil-guarded back (people: 9%), so that part is a few cases; the cost of the
   guarded and whiffed ones is the larger. The frontal jump-in is no better (43% hit it)
   and the air exchanges are worse (lost 1.94 a minute to 0.81).

What follows, in the order of what the counts say costs most (after round 19's judging,
which already trains against opponents that punish its whiffs): **the end of a combo**
(people's endings from the last hit on, the trap among them, tried on copies against a
victim that recovers each way or not at all: the routes' family, begun before the
recovery and not on seeing it); **the cost of a miss** (the non-hitting 236C and 623C
counted in every evaluation, as `six.py` counts them, and opponents that guard and
punish in the league); **the approach** (people's flights into contact, as a planner of
the okizeme's kind); the bait is the planned okizeme's to do, and what it did with the
user's eleven wake-up reversals is to be read from the game's log before anything is
built.

### The end of a combo: `endplan` (17 November, the first build)

Point 1's answer as a module of the planners' family (Python only so far:
`runs/human-ayu/airplan.py`, kind `endplan`, before `routes` in the stack):

- **The library** (`air_library.py --kind ending`): the community's Ayu players from the
  last hit of each combo of 600 HP or more that ended on an opponent in the air, to the
  next contact: 10,253 of them. The victim came down in 82% and recovered in 18% (then
  fell 39%, pressed 33%, dashed 14%, jumped 10%, guarded 4%). After the last hit the
  player pressed a move in the air in half (it caught 21% of the recoveries), one from
  the ground in a quarter (20%), an air throw in 1.2% (63%, tried once the recovery was
  seen), and flew or dashed back first in 0.9% (an air move after it: 8 of 19 recoveries
  caught).
- **When it plans.** When the agent sees a hit of its own on an opponent in the air, a
  copy of the game is played on with the route's remaining inputs against a victim that
  presses out at its first chance: if that victim is in its recovery within 30 steps,
  the combo is about to let go and the end is planned now; if not, the combo holds it and
  nothing is done (the next hit asks again). The first trigger tried, the last hit of the
  route as its plan foresaw it, was wrong by hundreds of steps: the route planner's
  copies are played against a victim that never presses out, and what they count as one
  combo ends much earlier against one that does.
- **What it tries**, each on copies against a victim that comes down, and one that
  recovers and then falls, guards, presses, jumps or dashes back: the library's ends from
  where the agent is (as many steps after its last hit), the trap of its own timing (a
  flight back, then 214A after 2, 8 or 14 steps), the route's own rest, a wait, its own
  play. The draw is the okizeme planner's, by what this opponent did at the ends of the
  combos the agent saw over the community's prior.

A first look (8 matches against Nayuki's `exploiter18`, the routes and this module
alone): 632 hits seen on an opponent in the air, the combo held it at 604, 28 plans,
about one for each recovery that followed. On the copies the trap after 2 steps is worth
300 to 700 HP against every way of recovering (its own play: 150 to 650), a timed air
throw 600 to 750 where the library has one. Being measured: 64 matches each against
Nayuki's and Ikumi's `exploiter18` and two of the `crowdt` set, the four modules of the
file with and without it.

### Round 19: the control arm, judged (18 November)

Started 17 November about 17:15 (a first start at 16:11 stalled: the worktree that held
the Python environment was removed under the runs; rebuilt with the versions the
checkpoints record, a seeded evaluation repeated on it to the last digit). The two
control seeds ended at 21:00 (20M steps, 22 minutes a chunk with its evaluation). The
`-whole` seeds take three hours a chunk on the machine as loaded (100 minutes of training
at 340 steps a second, 75 of evaluation) and end in the night of 18 to 19 November.

Each `avg.zip` as an agent file with `round18`'s parts, through the game's own code, 64
matches an opponent:

| | `exploiter18`s (704) | `crowd` (512) | `crowdt` (512) |
|---|---|---|---|
| `round18` (the mark) | 86.2% (own HP lost 62%) | 95.3% (45%) | 95.7% (48%) |
| `round17c` | 81.5% (66%) | 94.9% (48%) | 93.8% (50%) |
| `agent-league19-s1` | 89.6% (61%) | 96.1% (46%) | 95.5% (46%) |
| `agent-league19-s2` | 89.8% (60%) | 96.5% (45%) | 93.0% (49%) |

By opponent (Sayuri, Mio, Mayu, Nanase, Kaori, Mishio, Ikumi, Nayuki, Kano, Mizuka,
Makoto's): `round18` 84 91 94 86 98 100 81 **45** 81 95 92; s1 91 92 88 97 94 100 78
**64** 89 98 95; s2 84 94 94 94 95 97 83 **58** 95 97 97.

**Rule 1 does not pass.** Both seeds gain on the `exploiter18`s, by 3.4 and 3.6 points
where the rule asks for more than four, and s2 is 2.7 under the mark on `crowdt`. The
gain is the same in both seeds and most of it is one opponent (Nayuki's: 45% to 64% and
58%), so it is likely real and it is small: a bare learner that trains against the
opponents that learned the whole agent closes a third of the gap to the one that found
a hole, and nothing else moves (own HP lost 60-61% for 62%, a frontal jump-in hits it 47%
and 41% for 45%, its bigger combos end in a recovery as often). `round18` stays the
file; whether `-whole` does more is the other arm's to say.

Against all eleven, `round18` is ahead of `round17c` (86.2% to 81.5%): the opponents
were trained against `round18` and beat the older file more, which says the hole they
found is not `round18`'s own.

**Measured (18 November): it does not pay yet.** Round 18's policy with the file's four
modules in Python, with and without `endplan`, 64 seeded matches an opponent (Nayuki's
and Ikumi's `exploiter18`, and Nayuki's and Kaori's `exploiter15` with the `crowdt`
profile, which recover at the first chance and do not punish):

| build | wins: N18 / I18 / N15t / K15t | mean | recoveries caught (same four) |
|---|---|---|---|
| without | 43.8 / 68.8 / 84.4 / 98.4% | 73.9% | 32 / 49 / 38 / 42% |
| 1: the options against the answers, drawn | 40.6 / 65.6 / 93.8 / 96.9% | 74.2% | 21 / 51 / 38 / 49% |
| 2: the same, a recovering victim's HP counted from its recovery's end | 37.5 / - / 93.8 / -% | | 24 / - / 37 / -% |
| 3: a timed air throw or nothing | 37.5 / 65.6 / 92.2 / 92.2% | 71.9% | 31 / 66 / 46 / 50% |
| 4: ... only one that catches both ways of recovering, against an opponent seen to recover where it could | 35.9 / 75.0 / 82.8 / 95.3% | 72.3% | 23 / 52 / 43 / 47% |

What the builds told, each plan followed in the game to how it went:

- **The copies' answers do not say which end catches.** They valued the trap highest
  (300 to 700 HP against every way of recovering) and people's air moves lowest; in the
  game the trap as scripted caught 16 to 36% of the recoveries it was played into, its
  own play 7 to 36%. Counting a recovering victim's HP only from its recovery's end
  changed nothing: on a copy the agent's own play catches a victim that falls or
  presses, and in the game the opponent does neither on cue.
- **An air throw timed into the recovery does catch, when it covers both ways.** One
  found on copies to connect whether the victim recovers backward or forward caught 80
  of 88 recoveries in build 3 and 39 of 47 in build 4; one that covers a single way 41
  of 94, no better than nothing.
- **It is seldom there, and a throw at a victim that stays down costs.** Such a throw
  exists at about one chance to recover in nine (the limit is where the route leaves
  the agent, as for the catch after a recovery it sees: `airthrow:1`'s one in six).
  Against the `exploiter18`s, which stay down at 60 to 85% of their chances, build 3
  whiffed and gave up the route's end and the okizeme; build 4 waits until it has seen
  the opponent recover where a copy said it could (the chances and the recoveries are
  counted from the game, not from knockdowns it had no way out of).
- **No build wins more.** The differences are within what 64 matches tell, and against
  Nayuki's `exploiter18` every active build is under the mark (36 to 41% for 44%).

So the end of a combo is not a thing to bolt on after the route: twenty throws in 64
matches cannot move a result, and for more of them the route itself has to end where a
throw covers both recoveries. That is the route planner's to weigh (a route's worth: its
damage, and what its end leaves against an opponent that recovers as this one has), on
copies whose victim presses out; today its copies' victim never does, and a route it
counts as one combo runs hundreds of steps past where a recovering opponent leaves it.
`endplan` stays in the tree as built, off unless asked for, Python only, without a unit
test of its own yet; `air_library.py --kind ending` and the per-plan follow-up
(`came`, `asked` in its report) are the parts that will be used again.

### Round 19: the `-whole` arm's first seed, judged (18 November, evening)

`agent-league19-whole-s1` ended 18 November 19:52 (ten chunks; one was lost to memory at
noon and the run continued from its seventh, whose evaluation is the one missing from
its log; its `avg.zip` is the mean of all ten). As an agent file with `round18`'s parts,
through the game's own code, 64 matches an opponent, the eleven `exploiter18`s in the
order above: 83 88 94 94 94 91 70 75 80 97 94: **87.1%** (own HP lost
63%), for `round18`'s 86.2% and the control seeds' 89.6% and 89.8%.

**Rule 1 does not pass and rule 2 cannot.** It is 0.9 points over the mark where the
rule asks for more than four, and under both control seeds, so the `-whole` arm is not
the arm taken whatever its second seed does (which ends in the night and is judged on
the eleven for the record). It beats Nayuki's `exploiter18` 75% of the time, where
`round18` wins 45% and the control seeds 64% and 58%, and gives that back against
Ikumi's (70% for 81%), Mishio's and Kaori's: training with the planners in the loop
closed the hole one opponent had found and opened others. Sixteen hours of training for
the result of a four-hour control run.

**So round 19 ends as its rule 4 said it might**: nothing passes, "the league's way of
training has run out against the whole agent, and the next work is in the planners and
their options rather than in the policy". The same evening one option of a planner (the
okizeme's `sight`, below) moved the same measure by more than either arm, and the
user's games of the same evening said the measure itself is the wrong one ("The games
of 18 November", at the end).

**The second seed** (ended 18 November 23:32, judged the same way): 81 94 92 97 94 89 69
41 80 97 94 = **84.2%** (own HP lost 64%), under `round18`'s 86.2% and with the first
seed's hole back (Nayuki's 41%). The two seeds, 87.1% and 84.2%, straddle `round18`:
the arm taught nothing a seed's luck does not cover. Not taken.

## Opponents that get away, and the corner held (18 November)

The user, on point 1 and on the pressure: *an opponent that always recovers, or tries to
whenever it is safe, so that catching it or not makes a difference; and one that tries
to escape corner pressure whenever possible, so that how long the agent keeps it in the
corner can be observed.* Three things came of it.

**The scripted opponent** (`advantages.py`, with `tech`): `techsafe` (it presses out
only while the agent cannot throw it: in a move of its own, or more than 110 pixels
away; otherwise it falls), `techhit` (out of its recovery it attacks at the agent:
forward and B while it is in the air and the agent within 160 pixels), `techway` (the
share of its recoveries made forward), and `escape` (free on the ground in a corner, the
agent on the open side within 220 pixels, it jumps out over the agent: up-forward, a
second jump, forward held). Profiles on top of `crowd`: `crowdth` (`tech=1,techhit=1`),
`crowdts` (and `techsafe=1`), `crowde` (and `escape=1`).

**The measure** (`evaluate.py`'s `corner`, in every evaluation's report from now): the
opponent held in a corner from the step it is within 0.80 of a wall (positions run to
0.95) with the player on the open side within 220 pixels, until it is out past 0.68,
the player is no longer on the open side or is 330 pixels away, or the round ends; stays
of 20 steps or more: how many a minute, how long, the share of the match, the HP dealt
and lost a stay, how it ended. In the user's games:

| | stays a minute | seconds: mean (median) | of the match | HP dealt a stay | ended: out by air / the holder hit away |
|---|---|---|---|---|---|
| the agent holding the user, 16 Nov (`round17c`) | 2.7 | 4.1 (2.7) | 18% | 870 | 51% / 33% |
| the user holding the agent, 16 Nov | 3.7 | 4.4 (2.7) | 28% | 1,040 | 47% / 26% |
| the agent holding the user, 15 Nov (r17) | 3.0 | 4.2 (2.8) | 21% | 810 | 49% / 32% |
| the user holding the agent, 15 Nov | 3.9 | 3.9 (2.6) | 25% | 780 | 46% / 23% |

A hold of the agent's lasts as long as one of the user's; the user gets there more often
(3.7 to 2.7 a minute), and the agent is hit out of a third of its own.

**`round18` against the scripted ones** (the file through the game's code, Sayuri's,
Mayu's, Kaori's and Nayuki's `exploiter15`, 64 matches each):

| profile | wins (own HP lost) | bigger combos ending in a recovery | after it: caught / hit back | the corner held: seconds, mean (median) | of the match | ended: out by air / hit away |
|---|---|---|---|---|---|---|
| `crowd` | 92.6% (51%) | 8% | 49% / 12% | 8.4 (5.6) | 46% | 28% / 47% |
| `crowdth` | 92.6% (52%) | 60% | 49% / 19% | 7.5 (5.4) | 45% | 33% / 45% |
| `crowde` | 98.4% (39%) | 54% | 62% / 14% | 5.2 (3.1) | 34% | 77% / 14% |

The scripts do what they say (1,186 recoveries, 1,158 of them followed by the attack;
2,087 jumps out of a corner) and **they are not hard**: a fixed attack out of a
recovery hits the agent after 19% of them for 12%, and wins do not move; an opponent
that always jumps out of the corner the same way leaves it sooner (holds of 5.2 seconds
for 8.4) and is hit doing it (the agent wins 98%). They measure: the corner's hold and
the share of recoveries caught are read off them. They do not make a recovery left
uncaught cost anything, which was the point.

**The learned one** (`finetune.py --focus out`, `focus.py`): an exploiter paid 0.05
(500 HP's worth) for an air recovery of its own after which it is not hit or thrown
again within 40 steps, and for leaving a corner it was held in for 20 steps under
contact, and left to learn from the game's own reward what to do next. From each
character's `exploiter18` against `round18` as the game plays it, 6M steps at most, the
stop at 70% of 64 matches (`CHAR/exploiter18o`; Nayuki's first, Sayuri's, Ikumi's and
Mayu's queued behind round 19's `-whole` runs).

**The routes planned against a victim that presses out** (18 November; `route_ending`
1: the copies' victim recovers at its first chance and a knockdown is worth one HP more,
so nothing but the damage it really takes decides; `round18`'s file otherwise, through
the game, 64 matches an opponent):

| `route_ending` | `exploiter18`s (704) | `crowdt` (512) | a combo's damage | bigger combos ending in a recovery (`crowdt`) |
|---|---|---|---|---|
| 0 (`round18`) | 86.2% (own HP lost 62%) | 95.7% (48%) | 1,414 / 1,541 | 56% |
| 1 | 81.7% (65%) | 95.9% (46%) | 1,330 / 1,464 | 53% |

No better, and against the `exploiter18`s a little worse (5% less damage a combo). And
the recoveries stay: against opponents that always press out, half the agent's bigger
combos still end with the victim free in the air whichever victim the routes were
planned on. They are not combos that a recovery breaks; they are air combos whose last
hit leaves the victim in the air with its untech time running out, and a route that
ends otherwise (a knockdown: `route_ending` 400, 800) costs more damage than its
okizeme returns. What decides point 1 is then what happens after that last hit, against
an opponent for which it matters: the learned ones (`--focus out`, above).

**The first learned one: Nayuki's `exploiter18o`** (18 November). It ended at the stop
(70% of 64 matches against the file) after 4M steps, getting away 3.4 to 3.5 times a
minute by the bonus's count. `round18` through the game against it and against the
`exploiter18` it started from, 64 matches each:

| against Nayuki's | wins (own HP lost) | bigger combos ending in a recovery | after it: caught / hit back | the corner held: seconds, mean (median) | of the match | HP dealt / lost a stay | ended: out by air / the agent hit away |
|---|---|---|---|---|---|---|---|
| `exploiter18` | 45.3% (85%) | 44% | 24% / 53% | 8.8 (6.5) | 62% | 447 / 607 | 29% / 60% |
| `exploiter18o` | 34.4% (87%) | 46% | 20% / 47% | 6.6 (5.0) | 48% | 388 / 550 | 37% / 53% |

Two things the new measure shows that the wins did not. **The agent's corner is where
this opponent beats it**: it keeps Nayuki's `exploiter18` in the corner for 62% of the
match and loses more HP there than it takes (607 to 447 a stay; against the `crowd`
opponents 167 to 744), six holds in ten ending with the agent hit out of its own
pressure. And **the escape artist is harder to hold and no easier to catch**: a quarter
shorter holds (6.6 seconds for 8.8), more of them left through the air, a recovery
caught one time in five and answered with a hit one time in two. Here a recovery left
uncaught and a pressure that does not hold cost the agent the match (34%): the
opponent the user asked for. Sayuri's, Ikumi's and Mayu's follow when round 19's runs
leave the room.

**Round 19, a run lost and resumed** (18 November). `agent-league19-whole-s1` was ended
by the kernel for memory about 12:20, in its seventh evaluation of ten: my doing, two
more evaluations and an exploiter's training started beside the two `-whole` runs while
both were at their evaluations' peak (40 GB between them), on a day the machine's other
use had grown. Its four evaluation workers lived on as orphans (12 GB) until found. It
was started again at 12:45 from its chunk 7 (`finetune.py` picks up `model.zip`,
`avg.zip` and `finetune.json` from the run's folder; the average's count set to the 7
chunks `avg.zip` holds). What differs from a run left alone: its seventh evaluation is
not in its history, so the opponents of chunk 8 were chosen from evaluations 4 to 6.
Since then: nothing else of this session's beside the two runs but one evaluation at a
time, and `memwatch.sh` ends the evaluations under 8 GB available.

## What a miss costs, the flights, the bait: three more measures (18 November)

The user's points 5, 2 and 3 of 17 November ("risk management ... Ayu's 623 being RGed",
"flying and landing mixups", "doesn't know how to bait") had counts only in a script
over the user's own recordings. They are in `evaluate.py` now, for every evaluation
(`tactics.py`; `tests/test_endings.py`):

- **`risks`**, per risky move (Ayu's 623A, 623B, 623C and 236C by name, any other
  invincible move of the frame data by its number): how often a minute, the share that
  were a combo's piece (the opponent already hit: no risk taken), and of the raw ones the
  shares that hit, were guarded, recoil-guarded and whiffed, the HP a hit led to; of the
  misses the share the opponent punished (it hit the player first, from the guard or the
  move's start until 40 steps after the player is out of its move), the HP a miss cost,
  the shares answered with a recoil guard (`back`) and cancelled with an Instant Charge
  (`ic`); and **`net`**, the HP a raw use is worth: (all dealt − all lost) / uses.
- **`faced_risks`**, the same of the opponent's risky moves: `hit` is how often the
  player is hit by them, `punished` how often it punishes their misses. A bait is a miss
  made and punished.
- **`flights`**, the player's air dashes (Ayu's flights): a minute, the share flown
  back, what it did next (a move in the air, a move once landed, a throw, nothing), what
  came of it, and `mix`, the entropy in bits of what it did next.

The yardstick, people's Ayu in the community's replays (1,908 matches, 80 hours), and
the user's games of 16 November against `round17c` (23 matches; a few uses a move):

| | a minute | raw uses: hit / guarded / RG / whiff | a hit leads to | a miss: punished | costs | cancelled | **net HP a raw use** |
|---|---|---|---|---|---|---|---|
| people's 623A | 0.23 | 34% / 18% / 7% / 41% | 1,009 | 66% | 748 | 24% | **−155** |
| people's 623B | 0.33 | 35% / 18% / 7% / 41% | 1,152 | 59% | 668 | 27% | **−37** |
| people's 623C | 0.12 | 62% / 10% / 8% / 21% | 879 | 73% | 683 | 11% | **+278** |
| people's 236C | 0.48 | 55% / 22% / 6% / 17% | 1,121 | 56% | 690 | 7% | **+309** |
| the agent's 623B, against the user (15 raw) | 0.47 | 27% / 20% / 0 / 53% | 544 | 91% | 1,053 | 0 | **−627** |
| the agent's 623C, against the user (13) | 0.23 | 69% / 8% / 0 / 23% | 712 | 75% | 1,325 | 0 | **+85** |
| the agent's 236C, against the user (53) | 0.95 | 62% / 25% / 4% / 9% | 817 | 80% | 569 | 0 | **+294** |

So the user's point holds beyond the user: for people too a raw 623A or 623B loses HP on
average, 623C and 236C (invincible from their first steps) pay about 300 a use. People
are hit by 44% of the risky moves they face and punish 40% of the misses (428 HP a
miss); people fly 5.5 times a minute, 11% of it back, with 0.86 bits of mix in what
follows (82% a move in the air, 12% nothing, 5% a move once landed).

**The cancel.** What people do about a guarded 623 is the Instant Charge: of their raw
623A and 623B that were guarded while they had the gauge for one (500 of the RF gauge,
or cyan), 69% and 81% were cancelled with 22C, and the opponent then hit them first 29%
and 23% of the time; left uncancelled, 86% and 76%. They start these moves with that
gauge in hand (77-87% of the raw ones that touched the opponent; of 623C and 236C,
which spend the gauge themselves, 17-28%).
Half of the cancels come within 13 steps of the guard, pressed without waiting to see:
the same 22C goes on into a combo when the move hits (47-52% of the hits). The agent's
routes take the hit's side, planned when it sees its hit; nothing took the guard's:
against the user it cancelled none of its misses. In the game (`ic_check.py` of the
session: Ayu's 623B guarded by Mai, 600 of gauge): 22C begun up to 20 steps after the
first guarded step comes out as the charge (2 steps later), from 24 steps on it is too
late; an agent that sees 14 steps late and presses on sight is inside the window, with
the charge 16 steps after the contact. People's cancels as late as that (17 steps or
more) still leave them punished 35-38% of the time, for 76-86%.

`cancel.py`, the module `cancel` (`tests/test_cancel.py`): when the agent sees a move
named in `moves` (default `623A+623B`) of its own guarded, or recoil-guarded (`rg`), and
has the gauge, it presses 22C, once a move; `stats()`: guarded, no_gauge, tried, came. In
Python only so far; it goes before `pressplan` in the list, whose follow-up to a guarded
move it replaces for these moves. What it costs is the gauge, which a combo would have
used. Its measure (`risks`' ic, punished and net, the wins and HP) is below.

### The league by the three measures (18 November, evening)

`round18`, the file through the game's own code, against the eleven `exploiter18`s (704
matches; `avg-native-risk-x19-*.json`), beside people's numbers:

| raw uses | a match | hit / guarded / RG / whiff | a hit leads to | a miss: punished | costs | cancelled | **net HP a use** |
|---|---|---|---|---|---|---|---|
| 623A | 0.26 | 17% / 27% / 4% / 52% | 1,462 | 56% | 485 | 2% | **−159** |
| 623B | 0.45 | 29% / 24% / 5% / 42% | 728 | 49% | 400 | 6% | **−73** |
| 623C | 0.62 | 44% / 15% / 7% / 34% | 696 | 56% | 382 | 0 | **+91** |
| 236C | 2.2 | 38% / 37% / 8% / 17% | 1,514 | 46% | 530 | 1% | **+248** |
| 641236A (0x132) | 0.61 | 22% / 32% / 4% / 42% | 1,787 | 27% | 210 | 0 | **+230** |
| **236236A (0x13b)** | **0.75** | 10% / 58% / 2% / 30% | 1,287 | 68% | 812 | 0 | **−611** |
| people's 641236A | 0.40 | 38% / 23% / 15% / 23% | 2,432 | 44% | 596 | 30% | **+571** |
| people's 236236A | 0.08 | 13% / 34% / 18% / 35% | 1,531 | 38% | 305 | 18% | **−63** |

- **The 623s are people's.** A raw 623A or 623B is worth about what people's is (−159 and
  −73 for −155 and −37), 623C and 236C pay less than people's (+91 and +248 for +278 and
  +309) because they hit less often (44% and 38% for 62% and 55%), and the agent cancels
  almost none of its misses (0-6% for people's 7-27%). Half of its raw 623A and 623B
  whiff, which no cancel helps; a quarter are guarded.
- **The leak is one move: the level-one super 236236A, raw.** Nine times as often as
  people (0.75 a match for 0.08), it hits one time in ten, is guarded 58% of the time and
  costs 611 HP a use against every one of the eleven (−195 to −932): 460 HP a match,
  where the 623A and 623B together cost 75. Against the user (16 November) the same:
  27 raw uses in 23 matches at −569.
- **It is a wake-up reversal.** `risks` now tells the raw uses that began within 10 steps
  of the player's own knockdown (`wake`, `wake_hit`, `wake_net`). Against the user 23 of
  the 27 raw 236236A were wake-up ones (−625 each), as were 12 of its 15 raw 641236A
  (−273), 10 of its 15 raw 623B (−771, a move that is not invincible) and 12 of its 13
  raw 623C (+120): about 1,100 HP a match lost rising with a move, which is the user's
  point 5 more than the guarded 623 in a string is. People's wake-up reversals are
  641236A (67% of their raw ones are wake-up ones, +509 each, hitting 37%) and 623C (74%,
  +316, hitting 61%); their raw 236236A is rare and a wake-up one 29% of the time (+4).
- **Whether to rise with a move is a matter of how often, and the league does not say.**
  People's Ayu (the same replays, 17,355 wake-ups) rise with an invincible move on 10%
  of them and are 527 HP ahead for it (it hits first 48% of the time, the opponent 20%),
  with another move on 19% (+86), and guard on 56% (168 behind). The agent against the
  league (the older `wakeup` measure, the same 704 matches, 9.9 wake-ups a match): an
  invincible move on 22% (+122 by that measure's 96 steps, which end before a guarded
  super's punishment does), a guard on 22% (−161). The league's opponents attack its
  rising, and the `crowd` profile waits out 8% of its reversals (65 of 826 in the set),
  so the league does not teach it to guard more. What it gets wrong there is which
  move: 236236A, which hits one time in ten, where people's wake-up supers are 641236A.
  Twenty million steps against the `exploiter18`s do not remove it: round 19's first
  `-whole` seed still rises with it (34 and 56 raw uses against Sayuri's and Mio's,
  three in four and five in six of them wake-up ones at −166 and −494 each, where its
  wake-up 641236A makes +252 and +572). Against a person who waits it is how often: the
  user saw the reversal whiff or guarded it four times in five. That is a choice by the
  match's counts, as its okizeme's is; the module `rise` below makes it.

**The bait** (`faced_risks`): the agent is hit by 59% of the 816 raw risky moves it
faced (people 44%) and punishes 41% of the misses (people 40%; 635 HP a miss). Two
opponents make two thirds of it: Nanase's `exploiter18` rises with 623B (0x101) on 41% of
its wake-ups and with another move on 30%, and the agent is hit by 77% of them; Mayu's
uses 236C (0x105) 304 times, 74% hitting. Without the two it is hit by 36%. Against
Nanase's the planned okizeme loses 503 HP a knockdown (all eleven: +9 when the riser
guards, −645 when it reverses, −403 when it presses), and it waits on 5% of them. The
reason is in the planner as the file runs it (`after=guard`): after an option's inputs
the copies hold a crouching guard, so a reversal that is guarded or whiffs is worth
nothing to any option, and the wait, worth nothing against every answer, is not drawn
however often the opponent has reversed. The punish is the policy's to play and the
copies do not play it.

`okiplan`'s new option **`bait`** (default 0: as before; `tests/test_okiplan.py`) is the
worth of that punish: on a copy where the riser's reversal came out and neither side hit
first, the option is credited `bait` HP. 600 is the league's measure (a miss of the
opponent's costs it 635 with the agent's punishes as they are, 428 among people). With
it a wait is worth 600 times the reversal's share, so an opponent seen to reverse draws
it, and one that never does costs a wait only as often as the prior's 10% makes it
attractive.

*Measured (Python, Nanase's `exploiter18`, 64 matches): nothing.* 85.9% (own HP lost
62%) for 89.1% (61%), the okizeme −596 HP a knockdown for −476. The credit went to one
plan in eight, mostly to attacks that the copy's reversal happened to miss, and the
wait was drawn at 3.6% of the knockdowns for 2.0%. On the copies the reversal comes at
one timing; the opponent's comes when it has seen the agent commit. Waiting the
reversal out is not something a worth on these copies finds: the option stays (0 by
default) and is in the game's planner for the measure with `sight` (`round18sb`).

**The flights**: 3.0 a minute (people 5.5), 9% of them back (11%); what follows is a
move in the air 90% of the time, nothing 7%, a move once landed 3%, a throw 0.2% (people
82 / 12 / 5 / 0.4%): 0.47 bits of mix for people's 0.86. What comes of a flight: the
opponent hit 5%, its guard 19%, the agent hit 6%, nothing 70% (people 16 / 16 / 14 /
54%). People's flights are three times as dangerous to the opponent and twice as
dangerous to themselves: the agent flies seldom, safely and to little effect, as the
user saw.

Where a flight is flown from (`flights`' `where`, added the same evening: inside a combo,
over an opponent that is down, out of a guarded string, in the open), a minute, with the
shares that came to a hit and to being hit:

| | in a combo | okizeme | out of a string | **in the open** |
|---|---|---|---|---|
| people's Ayu | 1.74 | 0.67 (26% / 13%) | 0.26 (25% / 16%) | **2.81 (22% / 23%)** |
| the user, 16 November | 1.48 | 0.86 (25% / 13%) | 0.11 | **1.40 (22% / 14%)** |
| `round17c` against the user | 1.22 | 0.32 (39% / 0) | 0.02 | **0.50 (4% / 43%)** |

The combos' flights are there (the routes'). The gap is the open field: people fly at
the opponent nearly three times a minute and are hit as often as they hit; the agent
does it once in two minutes, lands one in twenty-five and is knocked out of the air by
the user nearly every second time. Out of a guarded string, people's pressure reset, it
does not fly at all. Nothing is built for either yet; the league's numbers by `where`
come with the next evaluations.

### The agent's own rising by the match's record: `rise` (18 November, the first build)

`rise.py`, the module `rise` (`tests/test_rise.py`; Python only). From what the agent
sees it keeps two accounts for the match: the HP swing (the opponent's HP lost less its
own, over 240 steps after it sees itself up, or until it sees itself down again or the
round ends) of the wake-ups it rose with a move on (a move of its own seen within 10
steps of rising) and of the others. An account's worth is its mean over a prior: +150
for a move and −165 for the others, counting as four wake-ups each (between people's
and the league's numbers above). When it sees itself knocked down it draws: with the
probability 1 / (1 + exp((a move's worth − the others') / 75)) this rising is guarded
through. A rising guarded through: while it sees itself down, the policy's own action if
that is a back direction without a button (its guard, standing or crouching by its own
read, or a jump back), else a guard, standing if it sees the opponent in the air. It
sees 14 steps late, so that covers the first 14 steps after it is up, where a wake-up
move would come out; then its own play again.

Nothing changes until a wake-up move was punished: 1.5% of the risings are guarded
through at a match's start, 42% after one wake-up move that cost a combo (1,300 HP), 90%
after two; a wake-up move that hit puts it back under 0.1%, and a guard that is opened
as often brings the move back. `carry=true` keeps the accounts for the next match
against the same opponent, scaled by 0.7, as the planners' counts are kept.

**Measured: the class is not the leak** (the file's four modules in Python with and
without `rise`, `carry=true`, 64 matches an opponent): Ikumi's `exploiter18` 71.9% (own
HP lost 70%) for 68.8% (72%); Kaori's `exploiter15` with the profile `crowdb` (the
`crowd` profile waiting out nine in ten of the wake-up reversals it is free to guard)
93.8% (50%) for 95.3% (47%). It guarded 13% and 22% of the risings through and nothing
moved, because by its own accounts a wake-up move pays there as a class: against
Ikumi's +174 HP a rising with a move (332) and −77 without (542). The loss is one move
inside the class: against that opponent the baseline's level-one 236236 super came out
raw 88 times in 64 matches, nine in ten of them wake-up ones, at −960 HP each (its
wake-up 641236A: +198).

**The second build: that move, seen coming.** The level-one 236236 super (0x13b: the
agent enters it as 236236C with one bar, which the game makes the level-one one; called
236236A above) has an account of its own, with a prior of −400 (the league's −166 to
−960, the user's −625; people's is +4 and rare). The module draws and plays the
policy's own inputs while it sees itself down, so what it reads is what is played; when
they hold two down-to-forward sweeps within 24 steps and then a button that makes the
level-one super (A, or any with one bar), the rising is guarded through with the
probability that account gives against the others' (94% at the priors; less where its
guard has been losing in this match). A first run of eight matches against Ikumi's: 12
seen coming, 8 stopped, 2 came out (−1,040 each).

**Measured: stopping the super does not pay either** (64 matches an opponent, the four
modules with and without). With the class's draw and the super's (`pyrise2`), Ikumi's:
93 of 103 supers seen coming stopped, 65.6% for 68.8%; the class's draw guarded another
fifth of the risings through and halved the wake-up 641236A that pays, so it is off
unless asked for (`moves=true`). With the super's alone (`pyrise3`):

| `exploiter18` | wins (own HP lost), without | with `rise` | supers seen coming, stopped | raw wake-up supers | HP it loses a minute |
|---|---|---|---|---|---|
| Ikumi's | 68.8% (72%) | 56.2% (74%) | 166, 149 | 79 to 18 | 5,162 to 5,194 |
| Kaori's | 93.8% (63%) | 96.9% (56%) | 88, 76 | 37 to 9 | 5,480 to 5,133 |
| Nanase's | 89.1% (61%) | 90.6% (66%) | 26, 23 | 15 to 3 | 6,781 to 7,278 |
| Kaori's `exploiter15`, `crowd` | 95.3% (47%) | 96.9% (48%) | 65, 59 | | 5,488 to 5,188 |

86.8% to 85.2% over the four: nothing, with the super gone. The guard that takes its
place loses as much (against Ikumi's the largest loss in the ledger is then being
thrown, 2,191 HP a minute: that opponent grabs a rising that guards). The wake-up super
is a symptom; what is wrong is underneath, in the next section but one ("Its own rising
against an attacker who is on it"). `rise` stays a Python module, not in the game.

### The landing mix-up: a riser that guards by sight (18 November, evening)

The user's point 2 ("flying and landing mixups that are very hard to predict") has a
number in the okizeme. By kind (`okizeme.mixups`; people's Ayu at 13,706 knockdowns of
the replays, `round18` at 5,831 against the eleven `exploiter18`s), the share and the HP
a knockdown is then worth:

| okizeme | people's share | hits first | worth | the agent's share | hits first | worth |
|---|---|---|---|---|---|---|
| a jump, then a high (jump high) | 19% | 37% | +34 | **35%** | 23% | **−115** |
| from the ground, low | 17% | 48% | +329 | 15% | 27% | −75 |
| from the ground, mid | 11% | 40% | +88 | 12% | 34% | +141 |
| **a jump, then a low** | **11%** | **54%** | **+375** | 4% | 46% | 0 |
| a flight, then a high | 9% | 40% | +106 | 12% | 27% | +66 |
| **a flight, then a low** | **7%** | 46% | **+230** | 1% | | |
| a dash, then a high | 4% | 36% | +7 | 8% | 34% | +97 |
| nothing | 9% | | −419 | 4% | | −443 |

People's commonest kind is one knockdown in five and their mix is 3.14 bits; the agent's
is one in three and 2.89 bits. The kind the planner draws most loses HP on average
(against seven of the eleven); the landing lows, people's best, are a twentieth of its
okizeme.

**Why: the copies' riser does not look.** Its two guard answers are a crouching guard
and a standing guard held whatever the agent does, in the shares the opponent's guards
have shown over a prior of 0.8 crouching. So on the copies an overhead off a jump hits
four times in five and a low after landing is guarded four times in five. People guard
by sight (the replays, the first touch of an attack on a defender on the ground): of
their guards against an attack from the air 95% stand (Ayu's opponents; 82% Ayu's own),
of those against one from the ground 92% crouch (87%). The 0.8 was every guard counted
together. An overhead off a jump is guarded by nearly everyone who is guarding at all;
what opens a guard is the height changed faster than it is seen: the low on landing.

**`okiplan`'s option `sight`** (0: as before; N: `tests/test_okiplan.py`): the riser's
'crouch' answer guards by what it saw of the agent N steps ago, standing against one in
the air and crouching otherwise; the 'stand' answer (a standing guard throughout) is 8%
of its guards, whatever its guards showed (`SIGHT_STAND`; from the two shares above:
87% by sight, 8% standing, 5% crouching, the last left out). With N = 14, the reaction
the agent itself has, a low within 14 steps of landing finds the riser standing and an
overhead within 14 steps of leaving the ground finds it crouching. The pressure planner
has the same option (`pressplan`'s `sight`: a guarding player looks too).

**First measure** (round 18's policy with the file's four modules in Python, 64 seeded
matches an opponent; `pyall2` without, `pysight` with `sight=14`):

| | wins (own HP lost) | HP a knockdown is worth | its okizeme hits first | jump, then high | landing lows (jump or flight, then low) | lows / highs | mix |
|---|---|---|---|---|---|---|---|
| Ikumi's `exploiter18`, without | 68.8% (72%) | −21 | 20% | 36% | 3% | 17% / 61% | 2.80 bits |
| ... with `sight` | **82.8% (63%)** | **+78** | **38%** | 8% | **30%** (hit 67%: +865 and +946) | 48% / 20% | 3.08 bits |
| Nanase's, without | 89.1% (61%) | −476 | 25% | 36% | 7% | 26% / 58% | 2.78 bits |
| ... with `sight` | **96.9% (62%)** | −538 | 30% | 29% | 11% | 31% / 45% | 2.91 bits |

Fourteen and eight points on the two (64 matches each: about two standard errors and
one), the landing lows hitting two times in three against Ikumi's, and the combo damage
a minute up by a fifth there (7,402 for 6,050). Against Nanase's the okizeme still loses
HP: that opponent reverses, which is `bait`'s side. The rest of the measure is through
the game's own code, below.

**In the game** (`port/agent/mix.h`, `mix.cpp`; `okiplan:2`, `pressplan:2`). The keys
`oki_sight`, `oki_bait` and `press_sight`; a play keeps what the opponent has seen of the
agent (in the air or not, a frame each) and whether the opponent's own move came out.
A file says `okiplan:2` or `pressplan:2` only when it uses one of them, so a file
without is one a game of the first version still loads, and that game refuses a file
that needs them rather than reading past the keys. `export_agent.py --okizeme-option
sight=14`, `bait=600`, `--pressure-option sight=14`. `tests.test_agents`: the game's
plans are `okiplan.py`'s and `pressplan.py`'s with the options on (worths, who hit
first, the mix; seven and five settings). Three files of round 18's policy for the
measure: `round18s` (the okizeme by sight), `round18sb` (and the bait at 600),
`round18sp` (the okizeme and the pressure by sight); against the eleven `exploiter18`s:

| through the game's code, 64 matches each | Sayuri | EX Nanase | Mayu | Nanase | Kaori | Mishio | Ikumi | Nayuki | Kano | Mizuka | Makoto | all |
|---|---|---|---|---|---|---|---|---|---|---|---|---|
| `round18` | 84 | 91 | 94 | 86 | 98 | 100 | 81 | 45 | 81 | 95 | 92 | 86.2% (own HP lost 62%) |
| `round18s` | 95 | 98 | 98 | 88 | 92 | 92 | 89 | 58 | 83 | 97 | 94 | **89.5%** (55%) |

Three points and a ninth less HP lost, ahead or level against nine of the eleven. The
bait (`round18sb`: Nanase's 91, Ikumi's 88, Nayuki's 56) and the pressure by sight
(`round18sp`: 91, 89, 53) are the same as `round18s` on the three measured (78.1% and
77.6% for 78.1%): not kept on, and their other jobs were dropped.

## The games of 18 November: `round18` in the game, and where the HP goes

The user's session of 18 November (`efz-session-20261118-213601-4cd2.zip`, 14 matches
with `round18` against Mio, Mishio, Ikumi, Shiori, Mizuka and Sayuri, all replayed frame
for frame), beside the session of 16 November with `round17c` (23 matches). The user's
words: "I feel it's weaker than 17c"; pressure more varied but more conservative, "I can
easily get out from corners"; combos worse, "unnecessary ICs in mid screen", the ending
"doesn't stop me from getting away"; the air "is becoming a real threat now"; against
Mizuka "its behavior becomes random at the end of the round"; "it's not calculating
what'd be the outcome if that doesn't work"; and: "we are dropping into another local
optima other than the previous one".

**The result did not move.** `round18` won 4 of 14 matches and 13 of 35 rounds;
`round17c` 7 of 23 and 19 of 53: 29% and 30% of the matches, 37% and 36% of the rounds,
while the same step was +4.7 points against the `exploiter18`s (81.5% to 86.2%).

**The user's points, counted** (`h1118.py`, `ic_use.py` of the session's scratch):

| | `round17c`, 16 Nov | `round18`, 18 Nov |
|---|---|---|
| a corner hold: seconds, HP dealt / lost in it | 4.1 s, 867 / 240 | 3.6 s, 643 / 298 |
| ... ended by the agent being hit away | 33% | 40% |
| after a guarded move with the advantage: its next attack hits / the pressure is lost | 25% / 17% | 15% / 19% |
| ... at a small disadvantage: the pressure is lost | 30% | 54% |
| combo damage on average, hits | 1,263, 5.3 | 1,200, 4.5 |
| mid-screen Instant Charges inside a combo: HP the combo makes after it; nothing after it | 959; 19% | 471; 41% |
| big combos that end in the user's air recovery | 41% | 33% |
| okizeme: HP a knockdown, the agent / the user hits first | +234, 38% / 25% | +173, 32% / 35% |
| air exchanges a minute, won / lost | 0.80 / 1.93 | 1.08 / 1.46 |
| frontal jump-ins that hit it | 43% | 36% |

Each of the five has its number: the pressure lets go more and holds the corner less,
the mid-screen charge buys half of what it did, the air is better.

**Where the HP goes** (`account3.py`: each loss of HP by what the loser was doing when
it began, a minute; people's Ayu are the 1,908 matches of the community's replays):

| the agent loses HP | to the user, `round17c` | to the user, `round18` | people's Ayu lose |
|---|---|---|---|
| **in the air, attacking** | **2,587 (2.00 times)** | **2,508 (1.91)** | **1,161 (1.22)** |
| in a move, in neutral | 1,363 | 1,330 | 1,177 |
| free on the ground | 1,368 | 753 | 1,050 |
| in the air, not attacking | 973 | 676 | 862 |
| rising (with a move, or not acting) | 885 | 1,018 | 638 |
| opened after guarding | 519 | 488 | 938 |
| in a move after guarding | 387 | 527 | 438 |
| its move guarded, then punished | 150 | 429 | 441 |
| thrown in the air | 92 | 361 | 133 |
| all | 8,811 | 8,505 | 7,429 |

- The agent deals the user 6,725 and 6,832 HP a minute in combos; people's Ayu deal
  their opponents 6,796 on average. That average is no bar (the goal, at the top): it
  is twelve players from 0% to 72% of their matches won. The ones who win:

  | (`people_ledger.py`, `people-ledger.json`) | deals a minute | loses a minute | hit attacking in the air: HP a minute (times), of it from the open |
  |---|---|---|---|
  | the Ayu player with the most matches (487, 72% won) | 8,480 | 6,049 | 1,056 (1.25), 468 |
  | the next (120, 65% won) | 7,822 | 6,662 | 924 (1.06), 515 |
  | all 1,908 matches (44% won) | 6,929 | 7,428 | 1,161 (1.22), 609 |
  | the three who win under 5% | 4,100 to 4,700 | 8,700 to 11,300 | 1,650 to 2,320 (1.8 to 2.2) |
  | Ayu players against the strongest opponent of the collection (534 matches, 13% won) | 5,278 | 9,108 | 1,523 (1.66), 825 |
  | the agent against the user, `round17c` | 6,856 | 8,704 | 2,570 (1.98), 1,779 |
  | the agent against the user, `round18` | 7,043 | 8,403 | 2,466 (1.85), 1,336 |

  The bar: the strongest Ayu player is 2,400 a minute ahead of the opposition they met;
  the agent is 1,400 to 1,800 behind against the user. Against an opponent of the
  user's kind (the collection's strongest wins 87% of 534 matches against Ayu players)
  the collection's Ayu players do worse than the agent does, so it is above them and
  both sides of its ledger are still short of the bar: the offence by a fifth to a
  quarter, the defence by 2,400 a minute, of which the air is the largest part.
- It loses 1,100 a minute more than people's Ayu do, and one line is more than all of
  that: hit while attacking in the air, twice a minute for 1,300 each where people are
  hit 1.2 times for 950. Under pressure it loses half of what people do.
- That line by situation (`airloss.py`): half in the open (1,343 to 1,891 a minute: a
  jump-in from 120 to 250 pixels or closer, met by a normal from the ground or in the
  air), 420 to 440 in its okizeme, 300 to 660 in its pressure, 210 to 320 on a combo
  that dropped.
- The league does not charge for it: the `exploiter18`s hit `round18` in the air 2.3
  times a minute and the `crowd` set 1.7 times, the user 3.8 to 4.4, and people's Ayu
  are hit 2.6 times. So a round can gain against the league, as this one did, and
  change nothing here.

**Netted, it is not one line** (`tactics.exchanges`, `evaluate.py`'s `net_ledger`, added
the same night: every loss of HP of either player by the situation it began in, from the
agent's side, so that what a situation costs is set against what it brings; HP a
minute, net with what was gained and lost):

| | the agent against the user, `round17c` | ... `round18` | the strongest Ayu player of the replays (487 matches, 72% won) | Ayu players against the strongest opponent of the replays (534, 13% won) |
|---|---|---|---|---|
| its okizeme (the opponent rising) | +926 | +684 (1,348 − 664) | +1,165 | −10 |
| the opponent's okizeme (its own rising) | −345 | **−877** (1,077 − 1,954) | +219 | −793 |
| its pressure (the opponent guarded just before) | +100 | **−547** (962 − 1,509) | +492 | −455 |
| the opponent's pressure | −369 | −379 | +86 | −1,054 |
| it came by air | −819 | **−652** (1,217 − 1,869) | −77 | −840 |
| the opponent came by air | −241 | +429 | +556 | +47 |
| both in the air | −934 | −267 | +114 | −288 |
| on the ground | −306 | +147 | −123 | −438 |
| **all** | **−1,987** | **−1,464** | **+2,431** | **−3,830** |

- The first reading above ("one line is more than all of the deficit") counted the cost
  of the air and not what it brings, and compared with an average: wrong twice. Netted
  and against the bar, `round18` is behind in six of the eight situations, most on its
  own rising (1,100 a minute under the strongest Ayu player's), in its own pressure
  (1,040 under: it loses more than it gains while it presses, which is the user's first
  point exactly, and it was +100 with `round17c`), coming in by air (575), in its
  okizeme (480) and under pressure (465).
- What did improve from `round17c` is what the user named: the opponent coming by air
  (−241 to +429) and the air-to-air (−934 to −267). What got worse: its own rising and
  its own pressure.
- Against an opponent of the user's strength the collection's Ayu players lose 3,830 a
  minute, in the same places (their rising, their pressure, coming by air, under
  pressure); the agent loses 1,464. To beat such a player the total has to be above
  zero against them, not level with anyone's.

**The local optimum, as the numbers put it.** Two loops have been run: the league
trains the policy against opponents made from the agent, and the planners decide what
follows once the agent has touched the opponent (a hit, a knockdown, a guarded move, a
recovery). The games against a person are decided before that, by who touches first in
the open, and there the policy plays alone, without a look ahead and without what it
saw earlier in the match, against a league that does not punish its approach. Both
loops can go on improving their own measures without the result moving. What follows
from it is in the next round's plan, not yet written: the measure a round is judged by
(the net ledger against the strongest players' and the user's, not the wins against the
league), opponents that punish by line as the strongest players do or harder, and the
lines in the order the net ledger gives them: its own rising, its own pressure, the
approach by air.

### Its own rising against an attacker who is on it (18 November, night)

The net ledger's largest gap to the bar is the agent's own rising. By the knockdown
(`tactics.wakeup`, in every evaluation's `wakeup`: the HP the attacker gains less what it
loses in the three seconds after the rise, and the riser's first choice):

| the riser | knockdowns a minute | HP a knockdown, for the attacker | a move of the attacker's is out as it rises | guards | an invincible move | another move | jumps |
|---|---|---|---|---|---|---|---|
| the agent against the user, `round17c` | 4.56 | +248 | 72% | 25% (+265) | 24% (−70) | 31% (+485) | 17% (+146) |
| ... `round18` | 4.78 | **+302** | 75% | 33% (+372) | 28% (+126) | 20% (+636) | 16% (−38) |
| the strongest Ayu player of the replays | 3.28 | **+13** | 58% | 53% (+112) | 13% (−486) | 18% (−104) | 11% (+131) |
| Ayu players against the strongest opponent | 5.00 | +71 | 57% | 53% (+182) | 9% (−411) | 25% (−35) | 7% (+13) |
| all Ayu players of the replays | 3.86 | +51 | 56% | 56% (+168) | 10% (−527) | 19% (−86) | 10% (+24) |
| `round18` against the eleven `exploiter18`s | 4.08 | **+27** | 16-36% for eight of them | 11-35% | 15-34% | 20-38% | 12-55% |

290 HP a knockdown over the strongest player's, 4.8 times a minute: about 1,400 HP a
minute, the size of the whole deficit against the user (−1,464). And the league does not
see it: its opponents leave the rising alone (a move out on 16-36% of the agent's
knockdowns for eight of the eleven, and +27 a knockdown over all), so the agent's
wake-up habits were learned where a move on rising wins. The exceptions say the same:
Kano's `exploiter18` is on it (70%) and takes +322 a knockdown (the agent's guard +482,
its jump +233); the `crowd` profile's scripted jump-in, one knockdown in five, hits the
rising agent 35-55% of the times against the eight `exploiter15`s, in matches it wins
89-100%.

What it loses to, in the user's games with `round18` (173 knockdowns; `risedetail.py`,
`riseguard.py` in the scratch folder, by what the agent could see 14 steps before it
rose):

- **The user on it (129, 75%): +427 a knockdown; not on it (44): −65.** Its guard there
  +404, an invincible move +292, another move +697 (236B: 7 times, hit every time, 963
  each; 623B: 8 times, 935 each).
- **The attacker close and in the air (56, a third): +540.** It guards 34% of them and
  loses 742 doing it. Of the 26 air attacks that hit it rising, the attacker was in the
  air in its own late view for 25, at a median of 5.5 steps after the rise; it held a
  standing guard under 7 of them, a crouching one under 4, up under 4, nothing or forward
  under 11, and had pressed a button in the last 12 steps under 14. `round17c`: 31 air
  attacks, 29 in view, a standing guard under 2.
- **Its invincible moves** come out on 28% of its risings and hit first 19% of the times
  (the attacker first 40%); the strongest player's on 13%, first 54% (the attacker 16%).

So three things, by size: moves into a meaty (about 145 HP a knockdown over the strongest
player's), invincible moves that are read or late (100), and a guard that is not held (65).
None needs a read to fix at the first step: an attacker in the air above a rising player
is guarded standing, and it is in view.

**The guard by sight** (`rise.py`, `guard=true`; `tests.test_rise`, 8 tests). A rising
on which the agent sees the attacker on it (while it sees itself down: the attacker in a
move of its own, or within 130 pixels, or in the air within 200) is guarded through with
the probability two accounts of the match give (`met_move`, `met_still`: the risings the
attacker was on, with a move of the agent's own and without; priors −300 and −150 over
four risings: 88% guarded at a match's start, its own play back when the guard is what
gets opened, 4% after two guards opened for a combo each). The guard is held by sight:
standing while it sees the attacker in the air, else its own play's guard, else
crouching; no button, no jump. It covers what the agent's delay covers: the rising and
the first 14 steps after it.

**Measured** (64 matches each; `pyall2` and `pyrise4` in Python, `round18s` and
`round18r` through the game's code; wins, own HP lost, and the HP a knockdown is worth
to the attacker; a new profile `crowdj` is the `crowd` profile jumping in on nine
knockdowns in ten):

| | without | with the guard | hold=40 | game: without | game: with |
|---|---|---|---|---|---|
| Kano's `exploiter18` (on it 70%) | 73.4% (68%) +272 | 84.4% (62%) +306 | 82.8% (66%) +326 | 82.8% (59%) +272 | 92.2% (61%) +361 |
| Mishio's `exploiter15`, `crowdj` | 92.2% (51%) +105 | 100% (42%) +96 | 98.4% (51%) +164 | 100% (46%) +53 | 98.4% (45%) +65 |
| Sayuri's `exploiter15`, `crowdj` | 79.7% (63%) +113 | 87.5% (63%) +164 | | | |
| Ikumi's `exploiter18` (on it 18%; throws) | 68.8% (72%) −51 | 64.1% (74%) −20 | 82.8% (68%) −3 | 89.1% (51%) −182 | 79.7% (65%) −53 |
| EX Nanase's | 95.3% (56%) −7 | 95.3% (54%) +84 | | | |
| Kaori's | 93.8% (63%) +10 | 93.8% (58%) +25 | | | |

- Against the attackers that are on it the wins go up 8 to 11 points, in Python and in
  the game; against the scripted jump-in the guard's own worth goes from +548 to +95 a
  knockdown (Mishio's) and +325 to +195 (Sayuri's), and the highs that hit from 48% to
  35-39%.
- **The guard itself holds**: with it always on (a debug run, Sayuri's `crowdj`, 131
  risings guarded through) 4 were hit while it was held: one thrown, one by a low after
  the landing, two in a string. What hits afterwards is the pressure that follows, 14
  steps after the rising and on, where its own play presses again: the guarded risings
  are still hit first 28% of the times over the next 96 steps.
- **"Near" was too wide.** With `near` at 130 pixels every rising against Ikumi's was one
  the attacker was "on" (it stands close, to throw), the guard was held through them,
  and the wins fell 9 points in the game (5 in Python): the policy's own answers there (a
  jump, 33% of its risings at −48; a move, −206) are the right ones. `near` is 0 now:
  on it means in a move, or in the air within 200 pixels. Measured again (`round18r2`).
- The hold (`hold=40`: the guard goes on while the attacker's string does) is level
  with the plain guard on three opponents (88.0% for 82.8%, carried by Ikumi's alone):
  left off.
- **The accounts were split the wrong way.** `near` at 0 did not bring Ikumi's back
  (`round18r2`: 82.8% for 89.1%, own HP lost 64% for 51%): that opponent is in a move or
  in the air on 88% of the risings too, and the agent's own answer to it, a jump away (a
  third of its risings, 429 HP ahead each), is worth far more than a guard (+36 for the
  attacker). The accounts should have found that within a match and did not: they
  compared the risings with a move of the agent's own against all the others, so the
  jump's wins were counted beside the guard's and the guard went on at 79%. They are now
  what the draw decides between: the risings left to its own play, whatever it did
  (`met_own`), and those the module guarded through (`met_guard`), with a prior that
  counts as two risings. `round18r3`, `round18k2`.
- The HP a knockdown is worth does not fall against the trained opponents, though the
  wins rise: there the policy's own mix of answers was already matched to each opponent,
  and a held guard gives up the rising's own counter-hits. The gain is where the
  attacker's move is what hits a rising that is doing something else: the scripted
  jump-in, and the user's games.

**The accounts of HP say nothing in time** (19 November; `round18r3`: the guard with the
corrected accounts; `round18k2`: with `risk` as well; through the game's code, 64 matches
each, wins and own HP lost):

| | `round18s` | `round18r3` | `round18k2` |
|---|---|---|---|
| Sayuri's `exploiter18` | 95.3% (51%) | 90.6% (59%) | 95.3% (56%) |
| EX Nanase's | 98.4% (48%) | 96.9% (47%) | 96.9% (48%) |
| Mayu's | 98.4% (55%) | 100% (47%) | 92.2% (54%) |
| Nanase's | 87.5% (57%) | 89.1% (62%) | 98.4% (56%) |
| Kaori's | 92.2% (55%) | 92.2% (55%) | 93.8% (56%) |
| Mishio's | 92.2% (57%) | 95.3% (52%) | 96.9% (57%) |
| Ikumi's | 89.1% (51%) | 85.9% (61%) | 84.4% (64%) |
| Nayuki's (awake) | 57.8% (80%) | 60.9% (77%) | 57.8% (78%) |
| Kano's | 82.8% (59%) | 84.4% (59%) | 87.5% (58%) |
| Mizuka's | 96.9% (48%) | 98.4% (47%) | 98.4% (44%) |
| Makoto's | 93.8% (47%) | 100% (45%) | 96.9% (44%) |
| **the eleven** | **89.5% (55%)** | **90.3% (56%)** | **90.8% (56%)** |
| Mishio's `exploiter15`, `crowdj` | 100% (46%) | 100% (42%) | 100% (46%) |
| Sayuri's `exploiter15`, `crowdj` | 84.4% (68%) | 81.2% (66%) | 81.2% (65%) |

Level, all three; the league does not tell them apart. What it does show:

- The sight works. The high attacks at its rising that hit: Sayuri's `crowdj` 53% of 412
  to 36-38%, Ikumi's 56% to 33-42%, Mayu's 29% to 17%, Sayuri's 30% to 23%.
- The accounts did not adapt. Against Ikumi's the module's own accounts had its own play
  232 HP ahead a rising and the guard 4 ahead, and it still guarded 70% of them: about
  eleven risings a match, a thousand HP either way each, a prior that starts at 88%
  guarded so that the other account is hardly ever fed. Against Kano's the guard loses
  394 a rising, as much as before, and was held at 68-75%.
- **"The attacker on it" is nearly every knockdown.** 704 of 804 against Ikumi's, 451 of
  459 against Kano's, 786 of 810 against Sayuri's: the move that knocked it down is a
  move of the attacker's, seen while it is down. The measure that tells the opponents
  apart is the one this section began with, a move of the attacker's out *as the agent
  rises*: 18% Ikumi's, 23% Nanase's, 30% Sayuri's, 34% Mayu's, 55-63% the two `crowdj`,
  71% Kano's, 75% the user, 56% the community's replays. Where it is low the guard
  costs (own HP lost: Ikumi's 51% to 61-64%, Sayuri's 51% to 56-59%), where it is
  high it is level or ahead.

**The read of the attacker** (19 November; `round18r4`: the guard; `round18k3`: with
`risk`). The accounts of HP are gone. The guard's probability is read from what the
match has shown of this attacker: the share of the risings the agent has seen in it at
which the attacker was in a move of its own as the agent saw itself up (what the agent
did then, and what it cost, has no part in it), over the community's 0.56 counting as
two risings; none are guarded at 0.3, all at 0.6, in a line between. 87% at a match's
start; after one rising left alone 24%, after two none; all against an attacker who is
there each time; kept into the next match at 0.7. Through the game's code:

| | a move out as it rises | the module's read | risings guarded | `round18s` | `round18r4` | `round18k3` |
|---|---|---|---|---|---|---|
| Ikumi's `exploiter18` | 18% | 19% | 21% | 89.1% (51%) | 92.2% (62%) | 93.8% (60%) |
| Makoto's | 24% | 24% | 32% | 93.8% (47%) | | 98.4% (42%) |
| Nanase's | 24% | 25% | 44% | 87.5% (57%) | 92.2% (62%) | 95.3% (56%) |
| Kaori's | 24% | 25% | 36% | 92.2% (55%) | | 95.3% (52%) |
| Nayuki's (awake) | 24% | 25% | 31% | 57.8% (80%) | | 43.8% (82%) |
| Mishio's | 33% | 33% | 47% | 92.2% (57%) | | 92.2% (54%) |
| Sayuri's | 36% | 37% | 49% | 95.3% (51%) | 95.3% (57%) | 93.8% (55%) |
| Mayu's | 36% | 39% | 52% | 98.4% (55%) | 93.8% (50%) | 98.4% (50%) |
| EX Nanase's | 49% | 50% | 70% | 98.4% (48%) | | 96.9% (46%) |
| Mizuka's | 57% | 57% | 74% | 96.9% (48%) | | 100% (44%) |
| Kano's | 65% | 65% | 86% | 82.8% (59%) | 87.5% (60%) | 92.2% (60%) |
| **the eleven** | | | | **89.5% (55.3%)** | | **90.9% (54.6%)** |
| Mishio's `exploiter15`, `crowdj` | 54% | 54% | 75% | 100% (46%) | 100% (45%) | 100% (45%) |
| Sayuri's `exploiter15`, `crowdj` | 63% | 63% | 86% | 84.4% (68%) | 81.2% (69%) | 87.5% (62%) |

- The read is the measure (the module's count against `evaluate.py`'s, within three
  points for every opponent), and the guard follows it: one rising in five against
  Ikumi's, six in seven against Kano's and the scripted jump-in.
- Level in the league again (90.9% for 89.5%, own HP lost 54.6% for 55.3%; the earlier
  builds 90.3% and 90.8% at 56%): a league whose opponents were trained against this
  agent's own risings has little to give a guard. Ikumi's is back (93.8% for 84-86%);
  its own HP lost there stays at 60%, as in every build with the guard, at the same
  damage taken a minute (4,839 for 4,802): what it gives up is its own damage (7,676 a
  minute for 8,802, 4.7 combos a minute for 5.2), the risings it used to win against an
  attacker coming to throw, and the matches last longer. Nayuki's is 43.8% for 57.8%
  (the Python stack without either module: 43.8%; 64 matches near an even pairing).
- What the league cannot show is what it was built for: an attacker in a move at three
  risings in four, with high attacks that hit a rising that is doing something else.
  That is the user's play and the strongest replay players', and the next games.

**In the game** (`port/agent/policy.h`'s `Rise`, `policy.cpp`'s `RiseWatch` and
`RiseAct`; the module `rise:1`, keys `rise_prior`, `rise_meaty`, `rise_low`, `rise_high`,
`rise_near`, `rise_fly`, `rise_decay`). The guard and its read only (not the super's
draw, which measured nothing), with the counts kept from match to match at 0.7 as
`carry=true` keeps them (once a match: the game resets an agent at a fight's end and at
the next one's start). `export_agent.py --rise`
(`--rise-option KEY=VALUE`); a file packed from another keeps it (`--keep`). The log
says what it did ("P1's risings: ..."). `tests.test_agents.RiseAsRisePy`: from the same
views the guard is held on the same steps (standing under an attacker in the air), its
own play elsewhere, and the read gives the same probability as `rise.py`'s after
each rising and into the next match. `efz_env_agent_rise_stats`,
`efz_env_agent_next_match` (`NativeAgent.next_match()`: a new match against the same
opponent for an agent that is not attached; `reset()` there starts it afresh). The files:
`round18r4` is `round18s` (the okizeme by sight) with `rise`, `round18k3` with `rise` and
`risk` (`round18r`, `r2`, `r3`, `k`, `k2`: the builds before, above). `round18k3` and
`round18k4` (the same with `risk_ahead`, below: the one to play) are in `~/dev/efz/tmp`
as `agent-league18-s2-round18k3.efzagent` and `...-round18k4.efzagent` (modules
`okiplan:2`, `rise:1`, `risk:1`: they need a game built from this code).

### The raw moves: the whole of the deficit (19 November)

`evaluate.py`'s `risks` (a raw special: not a combo's piece; its HP on net a use), with
236A and 236B added to it (`tactics.RISKY`: they were never measured), HP a minute as
uses a minute times the net of one:

| raw move | the agent against the user, `round18` | ... `round17c` | the strongest Ayu player of the replays | Ayu players against the strongest opponent |
|---|---|---|---|---|
| 623B | 0.64 × −644 = **−412** | 0.50 × −627 = −314 | 0.17 × −326 = −55 | 0.51 × −270 |
| 236236, level one | 1.13 × −367 = **−415** (nine in ten on rising) | 0.92 × −569 = −523 | 0.16 × −232 = −37 (one in fourteen on rising) | 0.19 × +21 |
| 236B | 0.78 × −402 = **−314** (`move_use.py`: 13 of 27 whiff at −969, 6 guarded at −503) | 0.59 × −591 = −349 | 0.14 × −131 = −18 | 0.48 × −264 |
| 623C | 0.19 × −898 = −171 | 0.25 × +85 | 0.11 × +580 = +64 | 0.25 × +144 |
| 623A | 0.22 × −672 = −148 | 0.19 × +118 | 0.25 × −180 = −45 | 0.40 × −197 |
| 236C | 1.19 × +11 = +13 | 1.01 × +294 = +297 | 0.59 × +333 = +196 | 0.47 × +129 |
| 641236A | 0.47 × −49 = −23 | 0.34 × −46 | 0.15 × +195 = +29 | 0.14 × +188 |
| **all raw specials** | **about −1,470** | about −900 | **about +150** | |

The agent's whole deficit against the user (−1,464 a minute) is the size of what its raw
specials lose. The strongest player has the same moves and uses the losing ones four to
seven times less often. Two of the three largest are wake-up moves, which the guard by
sight takes; the third, 236B thrown in the open, belongs to no situation the planners
cover. (What the pressure tables called "0x107 guarded" is this too: 0x107 is the end of
236A/B/C on contact, `src/efz.h`'s `k236End`, not a follow-up; `who.py`, a module that
only counts, has every one of them started by the policy's own play, not by a planner.)
This is the user's "risk management" (17 November) and "it's not calculating what'd be
the outcome if that doesn't work" (18 November) as a number.

**`risk`** (`risk.py`, `tests/test_risk.py`; Python). The last of the modules: a step no
planner took is its own play's, drawn by this module. When that action presses a button
and the agent does not see its opponent in a hit reaction, the press is tried on a copy
of the game as it is, the opponent pressing nothing: the press, then ten frames of
nothing (fifty while the agent is down), and the first action the agent was not in
already. Which move its own hands are about to start is its own knowledge, not the
opponent's; one frame shows a special started from standing (`risk_probe.py`), but the
game keeps a press made during a move, or while rising, and plays it later: the first
build looked one frame ahead, stopped 31 of 31 presses that started 623B at once against
Kano's `exploiter18`, and the match's record still had 21 raw 623B. If what starts is a
move with an account, the account decides. An account: the mean HP swing over 180 steps of the times
the move was let out in this match, over a prior of four uses at the strongest player's
HP a raw use (the column above); the press is stopped (the same direction, no button)
with the probability 1 / (1 + exp(worth / 75)): 623B 99 times in 100 at a match's start,
the level-one super 96, 623A 92, 236B and 236A 85, 236C 1, 623C and the 641236 supers
almost never. A move that hits in this match comes back; one that is punished goes (236C
after one that cost a combo: half; after two: 94 in 100). With it `rise` runs `plain`
(the guard alone; the super's account is `risk`'s). First eight matches against Nanase's
`exploiter18`: 11 of 14 raw 236B stopped, 4 of 4 level-one supers, 623B and 623A; 15 of
19 236C and every 641236 let out. A combo it has seen is let through whatever the game
is now (its own late view, as everything it decides by).

**In the game** (`port/agent/policy.h`'s `Risk`; `Player::SetRisk`, `RiskStarts`,
`RiskAct`, `RiskWatch`; the module `risk:1`, keys `risk_prior`, `risk_temperature`,
`risk_window`, `risk_look`, `risk_look_down`, `risk_decay` and `risk_moves`, a list of
action:prior). The look is made on the fight itself through the planners' `World` (saved,
the press and the frames after it played, put back: a millisecond for ten frames), on
the steps that are its own play's and not the guard on rising's. `export_agent.py --risk`
(`--risk-option 623B=-326`, `look=10`, ...), kept by `--keep` when a file is packed from
another. `tests.test_agents.RiskAsRiskPy`: from the same game the same move started (or
none) by seven presses at every step of 236, 623, 236236 and 641236, the game left as it
was; a press the game keeps inside a normal is found by both; the same probability at
the priors. `efz_env_agent_risk_starts`, `efz_env_agent_risk_stats`,
`efz_env_agent_modules` (a file's modules whole: the info structure holds 63 characters,
and a file with every module is past that). The file `round18k`: `round18s` with `rise`
and `risk`. A first eight matches through the game's code against Kano's: 25 presses
drawn for, 8 stopped, and no raw 623B, 236B or level-one super in the record.

**In the league** (`raw_table.py`: the eleven `exploiter18`s, 704 matches a file, through
the game's code; raw uses a match × the net HP of one; `round18r3` is the same file
without `risk`):

| raw move | `round18r3` | `round18k2`, with `risk` |
|---|---|---|
| 623B | 0.22 × −102 = −22 | 0.06 × −194 = −11 |
| 623A | 0.15 × −275 = −42 | 0.08 × −327 = −27 |
| 236236, level one | 0.40 × −662 = −267 | 0.12 × −929 = −111 |
| 236B | 0.88 × −295 = −258 | 0.34 × −366 = −125 |
| 236A | 1.24 × −200 = −248 | 1.14 × −270 = −307 |
| 236C | 2.12 × +296 = +627 | 2.09 × +297 = +621 |
| 623C | 0.34 × +40 = +13 | 0.30 × +43 = +13 |
| 641236A/B/C | 0.37 a match: +117 | 0.44: +188 |
| 236236, levels two and three | 0.18: +117 | 0.21: +118 |
| **all** | **+36 a match** | **+359 a match** |

The moves it stops are a quarter to a third as frequent (623B, the level-one super,
236B), the ones that pay are untouched, and the wins are level (90.3% and 90.8%, above):
320 HP a match that the league's win rate does not see. Against the user the same moves
were the whole deficit.

What it does not reach, and why (`who.py` on sixteen matches against Mishio's
`exploiter18`, `round18k2`'s modules in Python): of 20 raw 236A and 236B on a guard, 15
were played by the pressure planner, not by the policy's own steps. Not as its options:
they are the agent's own inputs for the 14 steps between a contact on a guard and its
seeing it, which the live plan draws at once and plays itself ("what it would have
pressed anyway": a normal cancelled into the special before it knows the normal was
guarded), so `risk`, which draws the steps no planner took, never sees them. A first
try at the planner's side (its guarding answers punishing a special they guarded:
`punish`, Python, taken out again) changed nothing, for the same reason: 11 for 12.

**The inputs chosen ahead** (`risk_ahead`, the game's code; `export_agent.py
--risk-option ahead=1`; `round18k4`). The inputs of its own play that a planner chooses
ahead (the routes' at a hit, the okizeme's at a knockdown, the pressure's at a contact on
a guard, the catch's) are now drawn for as they are played, as any step of its own play
is: every one of them, whatever the contact was, since the agent has not seen it (drawn
for only after a guard it would be a confirm inside the 14 frames; before this they were
drawn for only where nothing had touched, which was one too). A plan made from an input
that is then left out finds the game elsewhere and is dropped. Over the eleven
`exploiter18`s (`round18k3` to `round18k4`): raw 236A 1.04 a match to 0.49 (−261 HP a
match to −142), all raw specials +280 a match to +377, presses drawn for 3,741 to 4,408
and stopped 1,504 to 2,052; its combos as many and as long (6.13 and 6.15 a minute, 1,529
and 1,522 HP each); wins 91.6% (own HP lost 55.1%) for 90.9% (54.6%), 100% (42%) and
85.9% (69%) against the two `crowdj`. Raw 236B does not move (0.34 a match to 0.32, −407 and
−453 each): those are not its own inputs but the plans' (people's follow-ups that end in
236B, against a guarding player that never punishes on the copies; the `punish` try
above did not change the choice, and why not is open: a 2A may not reach after it). Not
in Python (`risk.py` draws the steps no module took); the file's key is tested, the
behaviour only by the measure above.

## Round 20: the plan (19 November; proposed, not started)

The goal is an agent that beats the best players within a person's limits; the bar is the
strongest replay players and the user's games, never the league's average. Three rounds
of results say the same thing about the league: its win rate no longer tells builds apart
(86-92% over the eleven `exploiter18`s for every build since round 18, two more seeds of
round 19 included), while the measures taken from a person's games move by whole
deficits. So round 20 is judged by those measures and trains against opponents that make
them matter.

**Judged by** (each beside the strongest replay player's row and the last games against
the user; a build is taken when none is worse and one is better by more than its noise):

1. the HP a knockdown of its own is worth to the attacker (`wakeup`: +302 against the
   user, +13 for the strongest player), by how often the attacker is in a move as it
   rises;
2. its raw specials, HP a minute (`risks`: −1,470 against the user, +150 for the
   strongest player);
3. its guarded strings: what a guarded move of its own leads to (`exchanges`: its next
   attack hits 15% for 27%, punishable 26% for 15%), with the raw 236B the plans end on;
4. the corner: escapes allowed (`escapes`) and the HP a combo's end leaves on the table;
5. wins and own HP lost over the eleven and the `crowd` sets, as a floor only.

**Opponents that make them matter** (the league's own exploiters leave its rising alone
on two knockdowns in three and punish half of what a person punishes):

- `crowdj` (jumps in on its rising) and Kano's `exploiter18` kept in every set;
- a punishing profile for the scripted opponents: after guarding a special, the largest
  combo that reaches (the routes' planner on its side), so that a guarded 236B costs in
  the league what it costs against a person;
- exploiters trained against the agent *with its modules on* (`round18k4` through the
  game's code as the frozen opponent), which the last ones were not: they found the
  wake-up habits the modules now cover.

**The work, in the order of what the user's games lost** (modules where the policy does
not use what it saw; training where it does):

1. the plans' own unsafe ends (236B on a guard: the planner's guarding answer must punish
   what a person punishes);
2. pressure when ahead (the user's first point: too careful with the advantage; the
   corner let go);
3. the combo's end and the mid-screen IC (the second point; `endplan`'s first build);
4. the end of a round against Mizuka (the fourth point: not looked at yet);
5. then a training round against the opponents above, the modules on while it trains.

## The benchmark suite (19 November): measures that have room to move

The user's question: "How applicable can we find some new benchmarks? Improving from 85 to
87 in something is likely more noisy than improving from 10 to 50 in something else." The
league's win rate is the 85-to-87 kind: at 92% over 704 matches its error is 0.9 of a
point and two builds differ by 1.3 before anything is real, and every build since round
18 is inside that. `runs/human-ayu/bench.py` is the other kind: a set of drills, each
whole matches against an `exploiter18` with one scripted habit on top (advantages.py), so
that the measure read from it has many events a match and a known cause; every number
with its error; beside it the same number of the strongest Ayu player of the replays.

**What was built.**

- `evaluate.py --folds K` (16): every number of a result with its standard error, by the
  jackknife over K groups of the matches (`spread()`; the result's `se`, the same tree),
  and `per_match` for a paired count outside. A measure made of events (a rate of the
  combos that end in a recovery) has no simple error; this gives one for all of them.
- `bench.py jobs FILE.efzagent --tag T`: the suite's commands. The drills: `league` (the
  eleven, no habit), `handicap` (the eleven, the agent taking twice the damage), `hold`
  (`escape=1`: opponents that leave a corner), `ends` (`tech=1`: opponents that recover
  from every combo they can), `rise` (`jumpin=0.9,throw=0.7`: its own rising attacked),
  `bait` (`bait=0.9`: its raw moves punished), `reversal` (`wake=0.6,blind=0.5`: its
  okizeme met with reversals), the last five against Kano's, Nayuki's, Ikumi's,
  Sayuri's and Mizuka's; `mirror`: another build's file as the opponent (the game's code
  on both sides).
- `bench.py table A [B]`: the scoreboard, a measure a row, pooled over its drill's
  opponents; with two builds the difference in errors (past 3 real, 2 to 3 likely, under
  2 noise). `bench.py noise A B`: two seeds of one build, which should differ by one
  error. `bench.py record TAG FOLDER --name N`: a person's games (from_record.py's
  recordings) scored the same way, so a play-test sits on the scoreboard with what its
  few matches can tell.
- New measures in tactics.py: `rounds` (a lead of 3,000 HP kept, a deficit turned, the
  seconds and the HP it takes to close a round whose opponent is under 2,500), `raw` (the
  raw risky moves as one account, HP a minute), `corner.left` (corner stays the opponent
  ended by leaving), `after_recovery.net`, and `ledger.into` (below, "The games of 19
  November").
- `people.json` made again with all of them, by player: the reference column is the
  player with the most wins among those with 100 matches (72% of 487).

**The first scoreboard** (`round18k4`, 64 matches a pairing, seed 7):

| measure | drill | `round18k4` | strongest player | all players |
|---|---|---|---|---|
| wins | league | 91.6 ±0.9 % | | |
| own HP lost a round | league | 55.1 ±0.7 % | | |
| raw specials, HP a minute | league | +183 ±41 | +235 | +197 |
| lead of 3,000 kept | league | 93.7 ±0.7 % | 88.8 | 78.9 |
| deficit of 3,000 turned | league | 66.5 ±2.2 % | 26.9 | 15.4 |
| a round closed, seconds | league | 18.6 ±0.4 | 18.9 | 18.8 |
| wins taking twice the damage | handicap | 49.9 ±1.8 % | | |
| corner stays the opponent left | hold | 84.4 ±0.5 % | 63.9 | 61.6 |
| a corner stay, median seconds | hold | 1.78 ±0.07 | 3.12 | 2.70 |
| HP a minute out of its pressure | hold | +102 ±72 | +492 | +133 |
| big combos that end in a recovery | ends | 52.4 ±1.0 % | 12.1 | 13.9 |
| recoveries caught less hit back | ends | +13.2 ±2.6 % | +22.6 | +8.6 |
| HP a minute on its own rising | rise | −36 ±62 | +219 | −326 |
| jump-ins on it that hit | rise | 21.8 ±1.5 % | 17.6 | 14.1 |
| its misses punished | bait | 47.5 ±1.5 % | 46.7 | 49.3 |
| HP a minute on its okizeme | reversal | +668 ±86 | +1,165 | +584 |

What it says:

- **The handicap is a scale that does not run out.** Twice the damage puts the wins at a
  half and spreads the opponents from 14% (Nayuki's) to 69% (Mizuka's), where the plain
  league shows 48% to 100%.
- **Three drills have the room the user asked for.** An opponent that recovers gets out
  of 52% of its big combos (the strongest player's opponents: 12%); one that leaves the
  corner leaves 84% of the stays (64%) after 1.8 seconds (3.1); its pressure is worth a
  fifth of the strongest player's. These are the user's points of 18 November (the
  corner let go, the endings), now at tens of points with errors of one.
- **The lead measures are saturated against the league**: it keeps leads and closes
  rounds there as the strongest player does against people. Against the user it kept
  61% (`round17c`, `round18`) and 78% (`round18k4`): that weakness shows only against a
  person, and a drill has to make it show before it measures anything.
- **The rising drill does not hold what the user sees** (below): it attacks the rising
  with a jump-in and a throw and never with a low, and the agent's rising is now lost to
  lows.
- The strongest player's column is a prior, not the same test: their numbers are against
  people, the agent's against trained opponents.

**What a play-test can tell.** With 14 to 24 matches a session the error of the win rate
is 10 to 12 points: two builds at 25 matches each differ for certain (3 errors) only 39
points apart. The measures made of many events are better: the share of jump-ins that
hit has an error of 2 to 9 points, the raw specials 200 to 260 HP a minute. So a session
is read by those, and the wins as the floor.

**The cost.** An evaluation through the game's code is 4 to 5.5 GB at 64 matches (the
planners' copies), 7 GB with an agent file on both sides. Nine at once drove the
machine's available memory to 6 GB and the watcher stopped the queue (nothing else was
touched); five at once leaves 24 GB. A build's whole suite is 49 pairings, about two and
a half hours at five at once.

## The games of 19 November: `round18k4` in the game

`round18k4` is round 18's policy with the modules of 18 and 19 November (`okiplan:2`,
`rise:1` with the guard by sight, `risk:1`: the raw moves' accounts). The user played it
24 matches (59 minutes, against ten characters; session `20261119-195241-01c9`, the game
at `f4062f7`); all 24 play again exactly (from_record.py). **The agent took 12 of 24**
(`round17c` 7 of 23, `round18` 4 of 14), and the user's points:

1. "Air strike absolutely strong."
2. "Combo strong, but not as much damage as 17c. Some mid-finish and weird choices are
   observed, but better than 18."
3. "When being okizeme, upper guard is good, but often hit by lower hit, especially when
   opponent approach in air but hit low."
4. "Not calm enough when under pressure to look for opportunities. Sometimes it behaves
   like it cannot predict what is going to happen after 1s, given the case where the
   opponent is sending out a strike. This is more severe when handling objects."
5. "Still not doing good pressure, better than 18, but still sometimes wastes frame
   advantages. Baits are seldom."

The three sessions on the scoreboard (`bench.py record`; each number's error from the
jackknife over the session's matches):

| against the user | `round17c` (23) | `round18` (14) | `round18k4` (24) | strongest player |
|---|---|---|---|---|
| matches won | 30 ±10 % | 29 ±13 % | 50 ±10 % | |
| HP ahead a minute, all exchanges | −1,848 ±712 | −1,360 ±765 | −363 ±487 | +2,431 |
| raw specials, HP a minute | −571 ±259 | −989 ±198 | +278 ±239 | +235 |
| where it came by air, HP a minute | −761 ±360 | −606 ±619 | +283 ±289 | −77 |
| both in the air | −869 ±350 | −248 ±240 | +222 ±220 | |
| frontal jump-ins on it that hit | 43 ±10 % | 36 ±7 % | 13 ±2 % | 18 |
| the opponent's missed risky moves punished | 29 ±18 % | 27 ±19 % | 54 ±8 % | 46 |
| a lead of 3,000 kept | 61 ±11 % | 61 ±10 % | 78 ±9 % | 89 |
| HP a combo | 1,263 ±61 | 1,200 ±63 | 1,283 ±49 | 891 |
| big combos that end in a recovery | 41 ±4 % | 33 ±5 % | 35 ±4 % | 12 |
| on its own rising, HP a minute | −321 ±191 | −815 ±422 | −872 ±231 | +219 |
| out of its pressure, HP a minute | +93 ±199 | −508 ±347 | −398 ±180 | +492 |
| lost starting something into what was out | 421 ±135 | 645 ±246 | 767 ±125 | 288 |

What moved for certain (3 errors): the raw specials (the accounts stop 100 of 225 presses
that would start one: from −989 to +278 HP a minute, the strongest player's +235), and
the jump-ins that hit it (36% to 13%). Likely (2 errors): the air, the net of all
exchanges. Not moved: its rising, its pressure, the endings.

**1, the air: confirmed.** Coming by air is worth +283 HP a minute where it lost 600 to
760; air to air +222 for −869; the HP it loses attacking in the air halved (2,570 to
1,270 a minute).

**2, the combos: the same damage by count, and a cause for the odd ends that is not the
build's.** The mean is 1,283 HP for `round17c`'s 1,263, the 90th percentile 2,950 for
2,960; only the largest is lower (5,340 for 6,150). One combo in five ends with the
opponent standing (20%; 16% for `round17c`). And the game's log says that **26% of the
route plans are dropped as late** in every session (300 of 1,119, 184 of 707, 355 of
1,372: 109 ms a plan on the user's machine, 193 ms at most), where an evaluation works
every plan to its end: a quarter of the re-plans at a later hit never arrive, and the
combo goes on with what it had. The evaluated agent and the played one differ by that
quarter. Not looked into further yet; it is the first thing to check for "mid-finish and
weird choices".

**3, the rising: the standing guard holds, the low opens it, and the cause is in the
module.** `rise` guards 359 of 360 risings through (a guard 92% of the wake-ups by the
measure, 25-33% before; a reversal 0.3% for 24-28%), standing where it sees the
attacker in the air. High okizeme now hits 29-31% (a jump-in, a flight, a dash and an air
move: 65-71% before for the dash). The user answered within the session: lows are 25% of
the okizeme on it for 13-16%, and they hit: from the ground 45% (13 of 29), after a dash
35%, **after a jump 70% (7 of 10)**. That last is the user's sentence. The module picks
the guard's height by whether it sees the opponent in the air, 14 steps late: an empty
jump that lands into a low is past before the view shows the landing. A person holds
the standing guard until the last moment a jump attack could still hit and then
crouches; the landing can be predicted from the height and the fall the agent does see.
Next work. The `rise` drill of the suite has no low in it (a jump-in and a throw), so
it shows −36 HP a minute where the user's games show −872: the drill needs the empty
jump into a low before it measures this.

**4, what is on the screen: confirmed with a new measure.** `ledger.into` (tactics.py,
`losses`): of the hits it takes, those by a move that had been out 20 steps or more (or
by an object whose owner was free again), which a player 14 steps late could have seen
and answered (`seen`); of them those where it started something of its own (a move, a
jump, a dash) after it could see it (`began`); and of those the ones an object made.
`round18k4` against the user: hit by something there to be seen 2.0 times a minute
(1.1-1.2 for the two builds before), started into it 1.08 times a minute for 767 HP
(0.50, 0.64); by objects 0.43 times a minute (0.10, 0.30). People's Ayu in the replays:
0.35 times a minute, 341 HP; the strongest player 0.30 and 288, by objects 0.06. The
user, against the agent, in the first count of the same thing: 0.02 times a minute. So
the agent walks into what is already out three times as often as people do and seven
times as often with objects, and `round18k4` more than the builds before it (2 errors:
likely). Under the opponent's pressure itself the count is calmer than before (it starts
a move after 25% of its guards for 36%, nothing after 43% for 27%) and its net there is
level (−61 ±290 a minute): the user's point is the strike that is coming, not the string.

**5, the pressure: confirmed.** −398 HP a minute out of its own pressure (`round17c`
+93, the strongest player +492); when a guard leaves it ahead its next attack hits 26%
and 18% of the times nothing follows; the planned pressure chose the bait (`wait`) 37
times in 437 guarded moves, 0.6 a minute.

### The level-4 CPU with the agent's combos (19 November)

The user: "I'm wondering how it would behave with cpu lv4, but with very good combos like
itself. CPU lv4's RG and counter rate is very high, I'm curious how the agent would
handle that."

**How it is made.** `evaluate.py --p2 FILE --p2-cpu-combos 4`: the game's level-4 CPU
plays P2, and on the step after one of its hits lands the side is handed to `--p2` (here
`round18k4` itself: its policy and its routes, planned on copies as in the game) until
the agent is out of the hit reaction or lies on the ground; then the CPU has it back.
The neutral, the guard, the recoil guards, the counters and the okizeme are the CPU's;
the combos are the agent's. The environment got the call that hands a side over in the
middle of a match (`efz_env_set_cpu`, `EfzVecEnv.set_cpu`; tests.test_agents.HandOver),
and one correction with it: on the copies an attached agent plans on, neither side is
the CPU's for the frames played there. Before, a plan against a CPU side played the CPU
itself on the copy, with the game's own rand(): the plan saw the CPU's coming decisions,
and the inputs it meant for the opponent were ignored. Now a plan against the CPU is
what a plan against a person is.

**The result** (the mirror: Ayu against the CPU's Ayu, 64 matches, seed 7):

| `round18k4` against | wins | own HP lost a round | the opponent's combo, HP | 90th pct. | its combos a minute |
|---|---|---|---|---|---|
| the level-4 CPU | 92.2 ±3.8 % (59) | 63.6 ±2.2 % | 651 | 1,300 | 10.2 |
| the level-4 CPU with its combos | 28.1 ±5.0 % (18) | 87.8 ±1.9 % | 1,287 | 3,258 | 8.1 |

The agent's own combos are the same in both (1,243 and 1,372 HP, 8.2 and 6.3 a minute).
So the plain CPU hits it more often than it hits the CPU (10.2 combos a minute for 8.2)
and loses only because a hit of the CPU's is worth half of one of the agent's; with the
same combos on both sides the agent loses 72% of the matches.

**How it handles the recoil guard: it does not.** In both settings the CPU recoil-guards
half of the agent's guarded moves (55%, 50%; the user 27%, people's opponents 36%) and
answers 98% of those at once (an invincible move 42%, another move 56%). After a recoil
guard the agent is hit 63-64% of the times and its own next attack lands 15-17% (against
the user: hit 36%, lands 30%; people: 24% and 25%). The lines of the ledger against the
CPU with combos: a move of its own started in neutral and beaten 2,380 HP a minute, its
move guarded and then punished 1,850 (1.5 times a minute at 1,230 each), free on the
ground 1,730. A lead of 3,000 HP is kept in 56% of the rounds (93% against the plain CPU)
and a deficit turned in 18% (72%).

**What to read from it.** (1) The agent's neutral and its strings against something that
recoil-guards and counters are worth less than nothing; its results rest on what its
hits are worth. A person who guards as the CPU does and has combos beats it; the user's
own recoil guards (27% of its guarded moves, answered successfully 36%) are the same
lever at half strength. (2) The league teaches little of it: the `exploiter18`s
recoil-guard 10-21% of its guarded moves (the CPU 50-55%) and hit it after 19-40% of
those (the CPU 64%). The advantages' `rg` and `reversal` knobs exist (9 November) and
are in no drill of the suite; a drill with them is the measure ("hit after its move was
recoil-guarded": 64% here, 24% for people). (3) Its okizeme and
its pressure against the CPU say little about a person (the CPU's guard is at the right
height by construction: docs, "No CPU but Kanna"); the recoil guard and the counter are
what this opponent adds. It is a benchmark, not a training opponent.

Still playing when this was written: the same pair against the other eleven characters
(the plain CPU, and the CPU with that character's `exploiter18` playing its combos).

## After the games of 19 November: the three fixes, the plans' time, the reaction (19 November, night)

The user, on the three proposals (the wake-up guard, the late plans, a recoil-guard
drill): "go ahead with all three, and we can slightly tune the 14f. From some sources it
says the best competitive players' reaction times are 120-170ms, we can adjust the
prediction a bit." Then: "it seems we got a benchmark it doesn't beat so far. I think
during the tuning and training, you can write better heuristics other than the factory
cpu logic." And: "you mentioned that the planner timeout caused combo drops. Can we
improve its efficiency so it keeps better quality?"

The game runs 64 frames a second: 14 frames are 219 ms, and 120-170 ms are 8 to 11.

### The plans' time: where it goes, and a plan that is late

**Where a plan's time goes** (`round18k4` against Kano's `exploiter18`, 270 plans, this
machine): a plan plays 26 options, 3,445 frames on copies, of them 119 its own play's.
A frame on a copy costs 14 µs; one of its own play's cost 0.36 ms more, the network's
decision. So its own play, one option of 26, was 45% of a plan's time (43 of 94 ms); the
25 routes the rest. The routes share next to nothing: playing common beginnings once
would save 3% of their frames.

**What was changed.**

1. *The network.* `Net::Forward` summed each row in one running double, a chain the
   compiler must keep in order; it now sums sixteen lanes side by side in single
   precision (`Dot`, port/agent/policy.cpp) and adds them in double. A decision goes
   from 0.33 ms to 0.20 ms here (the weights no longer fit the cache they are read
   from: that is the rest); the log-probabilities agree with the model's within 5e-05
   as before. It is also what every frame of the agent's play costs.
2. *A plan that is not done when it is due is no longer dropped whole*
   (`Planner::Settle`): it is chosen from the options played to their end. For that the
   options are now played in another order: first what the agent goes on with if no
   plan comes (the rest of the route it is on, else its own play), then the routes by
   damage, its own play last unless it was first. A settled plan takes the first unless
   another played option is worth more. A plan done in time is chosen exactly as before
   (tests.test_agents.PlansAsRedteam: the same plans as redteam.py's).
3. *An evaluation can play as a machine with less time does*
   (`efz_env_agent_plan_budget`, `evaluate.py --p1-plan-budget COST[,OWN]`,
   `--p1-plan-drop`): a plan may take COST frames on copies before it is due, one of
   its own play's counting OWN (27 with the old network, 15 with the new). At 7,700
   and 27 a quarter of the plans are late, as in the user's sessions.

**What the lateness cost, and what is back** (64 matches against Kano's):

| | every plan to its end | the user's machine, before | after |
|---|---|---|---|
| plans dropped as late | 0 | 19% | 0 (11% settled) |
| HP a combo | 1,801 ±39 | 1,631 ±40 | 1,805 ±30 |
| combo HP a minute | 9,986 ±310 | 9,260 ±390 | 9,620 ±280 |

The late plans cost a tenth of each combo (3 errors); with the faster network and the
settled plans the combos are the unlimited planner's again. (The other two opponents and
the window of an 11-frame delay, 6,050: below, when they have played.)

What is left for the game itself: plans are worked only in the frames' idle time (each
frame's 15.6 ms less the game's own work and a 1.5 ms margin), on the game's one fight,
so a second thread cannot take them. The headless library can run several fights; a
planner on a thread of its own with its own copy of the fight would have the whole
window (219 ms a plan at 14 frames, 172 at 11) and is the next step if the settled
plans still leave quality behind on the user's machine. The log line of the routes now
says how many plans were settled.

### The wake-up guard: standing until the landing, then crouching (`rise_land`, `rise_sight`)

The cause (above): the guard stood while it saw the attacker in the air, 14 steps late,
so an empty jump had landed and its low had hit before the view showed the landing.

**The landing can be predicted.** From the user's 1,888 flights in the three sessions:
a step moves the height by 2.478 vy + 2.037 g (g the fall's gain a step, read from two
views, 0.09 where they give none), and the landing predicted from a view 11 steps old is
within 2 steps of the true one in 94% of the flights that do not change course after
(87% at 14 steps, 97% at 8); a third of the flights do change course (a second jump, an
air dash) and land later than predicted. And the timing leaves room: a low after a
landing makes contact 4 steps or more after it in 97% (median 9), an air attack 4 steps
or more before it in 95%.

**The rule** (`Rise::land`, `rise.py`'s `land`; `StepsToLand` / `steps_to_land`): under
an attacker it sees in the air the standing guard is held while the predicted landing
has not passed, the crouching one from the step after. On the user's 1,712 clean
flights the crouch then begins within 3 steps of the landing in 98% (the old rule: 14
steps after, every time), at the cost of crouching 3 steps or more too early on 7.5% of
the steps under a flight (5.2% at 11 steps of sight).

**The reaction** (`rise_sight`): the guard's height may be chosen from a view fewer
steps old than the agent's delay. The file made for the test uses 11 (172 ms: the slow
end of the range the user gave); the policy itself is trained at 14 and stays there
until a round trains it at another (the trial of the same policy seeing 11 late,
untrained: below).

**The opponent that makes it measurable**: advantages.py's `low`, the share of its
jump-ins on the agent's rising that are empty, with its fastest low normal from the
landing (2A for ten of the eleven, 2B for Kano); the drill `riselow`
(`jumpin=0.9,low=0.6,throw=0.3`).

### The recoil guard, the CPU and a sparring partner in the suite

- `recoil` (`rg=0.3,reversal=0.8` on the five): the opponent recoil-guards three guards
  in ten and counters with an invincible move when the agent presses on.
- `cpu`: the level-4 CPU with the file's own combos, as a drill (`bench.py jobs` writes
  `--p2 FILE --p2-cpu-combos 4`).
- `sparring`: every scripted habit at once (`rg`, `reversal`, `tech`, `escape`,
  `jumpin` with `low`, `throw`, `bait`) with hits worth half as much again: the first
  opponent written to be what the factory CPU is not, one whose guard can be opened
  (the CPU's is at the right height by construction) and that punishes what a person
  punishes. It is the benchmark the user asked for in place of the CPU's logic, and the
  profile the next round trains against.

### What the four changes measured (19 November, midnight)

**The plans' time** (64 matches each against Kano's, Nayuki's and Sayuri's `exploiter18`;
"before": 7,700 frames a plan at 27 a frame of its own play, late plans dropped, the
user's machine as it was; "after": the same time with the faster network, 15, and late
plans settled; the last column a window of 11 frames instead of 14, 6,050):

| HP a combo | every plan to its end | before | after | after, 11-frame window |
|---|---|---|---|---|
| Kano's | 1,801 ±39 | 1,631 ±40 | 1,805 ±30 | 1,784 ±38 |
| Nayuki's | 1,748 ±46 | 1,540 ±31 | 1,690 ±44 | 1,749 ±45 |
| Sayuri's | 1,460 ±33 | 1,302 ±39 | 1,459 ±34 | 1,450 ±38 |
| plans dropped late / settled | 0 | 19-20% / 0 | 0 / 4-11% | 0 / 18-22% |

The plans dropped as late cost a tenth of every combo (1,491 for 1,670 over the three:
6 errors), and its own HP lost rose two points with it. With the two changes the combos
are the unlimited planner's again (1,651; and 1,661 with the shorter window, where one
plan in five is settled). The wins do not separate (74 to 79 ±2.5 in all four).

**The wake-up guard** (`riselow` on the five; the opponents' own counts of their
scripted jump-ins, six in ten of them empty jumps into a low):

| the scripted jump-ins | `round18k4` | `land`, 14 steps of sight | `land`, 11 |
|---|---|---|---|
| played | 1,130 | 1,120 | 1,174 |
| hit the agent | 425 (38%) | 211 (19%) | 232 (20%) |
| guarded | 219 | 422 | 433 |
| the agent hit first | 195 | 172 | 208 |
| its own rising, HP a minute | +65 ±69 | +233 ±85 | +122 ±68 |
| wins | 84.1 ±2.0 | 85.3 ±1.9 | 83.1 ±1.9 |

The jump-ins on its rising hit half as often, and are guarded twice as often. The
drill's totals are inside their errors: a scripted jump-in comes 3.5 times a match there
and the 0.7 hits fewer are a point of its HP a round. The two sights do not differ on a
script's plain jump; the shorter is for the flights that change course (5.2% of the steps
under a flight crouched too early for 7.5%). `tactics.wakeup`'s kinds do not hold the
scripted low apart (it is counted among the lows from the ground and the mids), so the
drill is read by the opponents' counts.

**The reaction: the policy 11 steps late instead of 14, untrained there**
(`round18k5`: `config.json`'s delay 11, the guard above at the same sight, everything
else `round18k4`'s; the league's Sayuri's, Kano's and Nayuki's):

| | `round18k4` (14) | `round18k5` (11) |
|---|---|---|
| wins | 79.2 ±2.5 | 90.1 ±1.9 |
| own HP lost a round | 65.1 ±1.4 | 56.9 ±1.6 |
| HP ahead a minute | 2,353 ±240 | 3,953 ±284 |
| against Nayuki's | 48 ±6 | 81 ±4 |

Three and a half to four errors on each, with no training: the policy was trained seeing
14 steps late and plays better seeing 11. Its routes are played from where it sees its
hit, 11 steps after it now (still no instant confirm); the planned okizeme's own
settings (`oki_think`, `oki_sight`: 14) were left as they were. 172 ms is the slow end
of the range the user gave for the best players. Its input rate is unchanged (1.6-1.9 presses a second). The whole
suite for it is playing; a round trained at 11 is the next step after it.

**The new drills, `round18k4`:**

| measure | drill | `round18k4` | strongest player |
|---|---|---|---|
| wins against every habit at once | `sparring` | 67.2 ±2.6 % (55 to 83 by opponent) | |
| own HP lost a round there | `sparring` | 67.8 ±1.3 % | |
| hit after its move was recoil-guarded | `recoil` | 40.7 ±0.9 % | 22.0 |
| its next attack lands after one | `recoil` | 22.2 ±0.9 % | 29.9 |
| HP a minute out of its pressure there | `recoil` | −370 ±81 | +492 |
| wins against the level-4 CPU with its combos | `cpu` | 28.1 ±5.0 % | |

**The level-4 CPU of the other characters, with their `exploiter18` playing its combos**
(`--p2-cpu-combos 4`, 64 matches each, all eleven): 94 to 100% (Nanase 94, Nayuki 97,
Makoto and Mizuka 98, the other seven 100; the plain CPU: 95 to 100), its own HP lost a
round 26 to 55% for 24 to 58%. The CPU's combos are no larger for it (595-781 HP for
561-784): an `exploiter18` handed a hit the CPU started does not turn it into its
own combo. So the hard benchmark is the mirror alone, where the combos are the routes'
planner's; for the other characters "combos as good as the agent's" needs routes of
their own (their combos on Ayu are in the same replays), or a scale on the damage as
`handicap` and `sparring` have.

## 20 November: equal reactions, the recoil guard answered, round 20 started

### The reaction, with opponents that react as fast

The trial of 19 November gave the agent 11 steps and left its opponents their 14: an
`exploiter18` reads its delay from its own `config.json`. `evaluate.py --p2-delay N`
gives P2 another, and the same three pairings were played with both sides at 11:

| 64 matches each | `round18k4`, 14 against 14 | `round18k5`, 11 against 14 | `round18k5`, 11 against 11 |
|---|---|---|---|
| Sayuri's | 95 ±3 % | 97 ±2 | 92 ±3 |
| Kano's | 94 ±4 | 92 ±3 | 89 ±4 |
| Nayuki's | 48 ±6 | 81 ±4 | 73 ±7 |
| the three | 79.2 ±2.5 | 90.1 ±1.9 | 84.9 ±2.8 |
| own HP lost a round | 65.1 ±1.4 % | 56.9 ±1.6 | 62.2 ±1.6 |
| HP ahead a minute | 2,353 | 3,953 | 2,953 |

About half of the gain was the agent reacting faster than its opponents. With equal
reactions it is 5.7 points ahead of the 14-step agent (1.5 errors: likely no more than
that), nearly all of it against Nayuki's. So the suite's numbers for an 11-step build
against 14-step opponents flatter it, and a round trained at 11 has its opponents at 11
too (finetune.py's `--delay` is every player's). Against a person the question is what
the person's reaction is; the user's range for the best players is the agent's.

**The whole suite for `round18k5`** (60 pairings, the opponents at their own 14 steps:
read it with the table above in mind):

| measure | drill | `round18k4` | `round18k5` | errors |
|---|---|---|---|---|
| wins | league | 91.6 ±0.9 % | 96.2 ±0.6 | +4.2 |
| own HP lost a round | league | 55.1 ±0.7 % | 48.3 ±0.8 | −6.3 |
| wins taking twice the damage | handicap | 49.9 ±1.8 % | 63.9 ±1.9 | +5.4 |
| wins against every habit at once | sparring | 67.2 ±2.6 % | 80.6 ±2.1 | +4.1 |
| jump-ins on its rising that hit | rise | 21.8 ±1.5 % | 12.9 ±1.1 | −4.8 |
| scripted jump-ins, six in ten into a low, that hit | riselow | 37.5 ±1.9 % | 26.3 ±1.7 | −4.5 |
| ... that it guarded | riselow | 21.0 ±1.7 % | 36.5 ±1.8 | +6.3 |
| HP a minute on its own rising | rise | −36 ±62 | +206 ±65 | +2.7 |
| HP a minute out of its pressure against recoil guards | recoil | −370 ±81 | −21 ±99 | +2.7 |
| hit after its move was recoil-guarded | recoil | 40.7 ±0.9 % | 38.8 ±0.8 | −1.6 |
| scripted reversals after a recoil guard that hit it | recoil | 70.6 ±2.8 % | 71.6 ±3.7 | +0.2 |
| wins against the level-4 CPU with its combos | cpu | 28.1 ±5.0 % | 34.4 ±6.0 | +0.8 |
| corner stays the opponent left | hold | 84.4 ±0.5 % | 83.5 ±0.7 | −1.1 |
| big combos that end in a recovery | ends | 52.4 ±1.0 % | 52.6 ±1.2 | +0.1 |
| its misses punished | bait | 47.5 ±1.5 % | 45.7 ±2.0 | −0.7 |

What a faster reaction and the landing rule move: everything decided by seeing in time
(wins, HP, its rising, jump-ins). What they do not move at all: the corner let go, the
endings that let the opponent recover, the recoil guard and the CPU. Those four are
what it does, not how fast it sees. (The two `riselow` rows are new: the scripted
opponents' own counts, `bench.py`'s `script` measures.)

### The recoil guard: what the game does, and an answer inside a person's reaction

The measure (the `recoil` drill, and the level-4 CPU with the agent's combos): the agent
is the one hit after 39-41% of its recoil-guarded moves against the scripted habit and
62-64% against the CPU, the strongest replay player after 22%.

**What happens after one** (24 traced matches against Kano's `exploiter18` with
`rg=0.3,reversal=0.8`, the agent's side; 193 recoil guards): the hit lands 32 steps after
the recoil guard at the median and 28 at the tenth percentile (26 and 23 against the
CPU); a move of the agent's own comes out as the freeze ends after 40% of them (a chain
pressed before it could see the recoil guard, or its next press); it guards the counter
after 19%. It sees the recoil guard 11 steps after it: there is time.

**The game's rules, frame by frame** (a scripted mirror in the headless game: Ayu's 2A,
2C, 5B, 5C recoil-guarded, the other side countering with a 2A at every delay; and
src/scene3.cpp, src/player.cpp):

- Both players are frozen for about 20 steps. The first counter lands at step 23 (the
  CPU's) to 25.
- A guard is a recoil guard when back was pressed from neutral no more than 9 steps
  before the hit; a second press does not count for 18 steps after the first. A guard
  held from early in the freeze is a plain one by the time anything lands.
- The player whose move was recoil-guarded can recoil-guard the counter even from the
  recovery of that move (`m_canRecoilCounter`, until its next move starts). A plain
  guard is not there until the move has ended: 29 steps after the recoil guard for a
  2A, 40 for a 2C.
- The last button pressed during a move is kept without an end (`m_bufferedPress`) and
  comes out as the freeze ends, at step 19: a chain pressed blind ends the recoil
  counter and is in its start as the counter lands. A later press takes its place, and
  an A does not chain from a normal of the same stance or a stronger one.

**The answer** (`rise_recoil`, in the module that guards by sight: port/agent/policy.cpp
`RiseWatch` / `RiseAct`, runs/human-ayu/rise.py; the same step for step,
tests.test_agents.RiseAsRisePy.test_a_move_recoil_guarded): when it sees its opponent
enter a recoil guard within 240 pixels while it sees itself in a move, its inputs are
the module's: nothing held until step 22 after the recoil guard, on the second of those
steps an A where the move was a ground normal (in the kept chain's place:
`rise_recoil_clear`), then the guard by sight (crouching; standing under an opponent in
the air until its landing), until it sees its own guard touched, itself hit, or the
opponent free on the ground for 8 steps; 60 steps at most. Everything in it is a
reaction to what it has seen, at its delay.

**The traced drill** (24 matches each, the agent's side; the first two builds are the
record of what the timing costs):

| after its move is recoil-guarded | no answer | back at step 12 | back at step 23 | and the A |
|---|---|---|---|---|
| recoil guards | 193 | 172 | 184 | 238 |
| it is hit | 51% | 42% | 28% | 29% |
| its next attack hits | 21% | 9% | 16% | 10% |
| counters guarded (with a recoil guard) | 37 (7) | 71 (1) | 107 (66) | 142 (69) |
| a move of its own out as the freeze ends | 40% | 27% | 26% | 13% |

A guard held as soon as it sees the recoil guard is hit in the move that was
recoil-guarded as often as before (46 times of 172): the press has run out. Timed, the
counters are guarded 58% of the time and it is hit half as often. After its own recoil
guard it does nothing with the advantage yet (neither side hits in 80 of 107): a punish
there is the next piece.

**The drills** (`recoil` on the five and `cpu`, 64 matches a pairing; `round18k6`: the
answer with the press at 22 and the A, `round18k6n`: without the A; both still let go at
the first guard they see touched):

| | `round18k5` | `round18k6` | `round18k6n` | strongest player |
|---|---|---|---|---|
| hit after its move was recoil-guarded | 38.8 ±0.8 % | 18.4 ±0.6 | 22.5 ±0.8 | 22.0 |
| its next attack lands after one | 25.9 ±0.9 % | 9.1 ±0.5 | 9.3 ±0.6 | 29.9 |
| HP a minute out of its pressure there | −21 ±99 | −298 ±78 | −323 ±71 | +492 |
| wins there | 82.8 ±1.9 % | 85.9 ±1.6 | 82.2 ±1.9 | |
| against the CPU with its combos: hit after | 62.3 ±2.0 % | 34.7 ±1.5 | 33.8 ±2.2 | |
| ... wins | 34.4 ±6.0 % | 50.0 ±5.6 | 35.9 ±6.4 | |

It is hit after a recoil guard as seldom as the strongest replay player, and half as
often against the CPU. The price is its own pressure: its next attack lands a third as
often and the pressure's net falls by 280 HP a minute (2 errors); the wins do not fall
(with the A they rise against the CPU by 16 points, 1.9 errors). So the guard is right
and what is missing is what comes after it.

**Two flaws the traces showed, mended** (`round18k7`). The guard ended at the first guard
of its own it saw touched, and its own play then let the guard go inside the opponent's
string (22 hits after 107 counters guarded): the guard now goes on through the string,
until the opponent has been free for 8 steps. And the A in the kept chain's place
completed a motion where one had been entered (an A after 236 is 236A: a traced 5C went
into a special by it): it is pressed only where its last 12 inputs held one direction.

| | `round18k5` | `round18k7` | strongest player |
|---|---|---|---|
| hit after its move was recoil-guarded (`recoil`) | 38.8 ±0.8 % | 14.0 ±0.6 | 22.0 |
| HP a minute out of its pressure there | −21 ±99 | −82 ±80 | +492 |
| wins there | 82.8 ±1.9 % | 86.9 ±1.7 | |
| the CPU with its combos: hit after | 62.3 ±2.0 % | 32.9 ±2.2 | |
| ... wins | 34.4 ±6.0 % | 43.8 ±6.2 | |
| wins against every habit at once (`sparring`) | 80.6 ±2.1 % | 80.9 ±2.0 | |
| wins, the league's Sayuri's, Kano's, Nayuki's | 90.1 ±1.9 % | 84.9 ±2.1 | |

The pressure's net is back within its error, and the drill it was built for is won more.
But the three league pairings fall by 5 points (1.8 errors), nearly all against Nayuki's
(81 ±4 to 66 ±5; a second sample of 24 matches each went the other way, 67 and 88:
together 77% and 72% of 88, inside the noise). Whether or not that fall is real, the
traces say why it could be: her recoil guards carry no counter in time (a move of hers
starts 61 steps after one at the median, the CPU's 22, the scripted drill's 27), and
against her the agent's next attack lands after 32% of them unanswered and 9% answered.

**So the answer is read from the match** (`round18k8`: `rise_recoil_counter`,
`rise_recoil_prior`, `rise_recoil_low`, `rise_recoil_high`, `rise_recoil_soon`), as the
guard on rising is: the share of this opponent's recoil guards of its moves after which
it saw a move of the opponent's (or itself hit) within 34 steps, over a prior of 0.6
counting as two; none answered at 0.3, all at 0.6. By the traces that share is 0.74 for
the CPU (every one answered), 0.66 for the scripted drill unanswered and 0.46 answered
(the script and the opponent's own play counter less into a guard: about half answered,
which is the mix that holds), 0.20 to 0.24 for Nayuki's (the first one answered, none
after the second).

| | `round18k5` | `round18k7` (every one answered) | `round18k8` (by the match) |
|---|---|---|---|
| wins, the league's eleven | 96.2 ±0.6 % | 94.7 ±0.7 | 95.0 ±0.7 |
| HP ahead a minute there | 5,162 ±132 | 4,721 ±116 | 4,990 ±125 |
| against Nayuki's | 81 ±4 % | 66 ±5 | 72 ±5 |
| hit after its move was recoil-guarded (`recoil`) | 38.8 ±0.8 % | 14.0 ±0.6 | 22.4 ±0.8 |
| wins there | 82.8 ±1.9 % | 86.9 ±1.7 | 84.1 ±2.2 |
| wins against every habit at once | 80.6 ±2.1 % | 80.9 ±2.0 | 81.2 ±1.9 |
| the CPU with its combos: hit after | 62.3 ±2.0 % | 32.9 ±2.2 | 35.2 ±2.6 |
| ... wins | 34.4 ±6.0 % | 43.8 ±6.2 | 31.2 ±6.2 |

Read plainly: the answer does what it was built to do (hit after a recoil guard as
seldom as the strongest replay player, or less) and the matches' results do not move by
more than their noise either way: +1 to +4 points where the opponents counter after
their recoil guards, −1.2 to −1.5 in the plain league, the CPU anywhere between 31% and
50% over four builds whose answer is the same there. The read from the match recovers
most of the league's net (4,990 for 4,721; the league's opponents are still answered six
times in ten: they do counter, late), not Nayuki's. A defence that is right and wins
nothing yet says the same as the pressure's rows: the HP is in what follows the guard,
its own recoil guard included, and nothing follows yet. `round18k8` is the file kept
(`agent-league18-s2-round18k8.efzagent`), for the recoil guards of a person.

**What follows its own recoil guard** (`rise_recoil_punish`, `round18k9`). The same
scripted mirror, one step on: Ayu recoil-guards the counter (a 2A the other side goes on
pressing, or follows with a guard), and plays something from the pose.

| played after its own recoil guard | against a 2A pressed on | against a guard after the one 2A |
|---|---|---|
| the guard, on | guards it | nothing |
| 2A or 2B at steps 21 to 23 | hit at 23 by the kept chain (−338 HP) | hit (−175) |
| 623A at 21, 22 | hit (−489) | hit (−175) |
| 623B, its button at 20 to 23 | hits (+745, a knockdown) | hits (+745) |
| 623B, its button at 24 | too late: hit (−339) | |

The opponent's kept chain comes out at step 20 and is active at 23, before anything
pressed from the pose (which the game lets go at 22) can be: a normal loses, 623B wins
against both. So when it sees itself in a recoil guard on the ground, the opponent in a
move within 80 pixels and not in the air, the guard goes on and 6, 2, 3, 3+B are played
so that the button lands 22 steps after its recoil guard, which is 11 steps after it
sees it. First trace (24 matches against Kano's with the recoil habit): 56 of its own
recoil guards followed by it; after a counter it guarded it is the one that hits 32
times of 77 (5 of 107 before) and is hit 10; all 24 matches won, 49% of its HP lost a
round (57% for `round18k5` on the same matches, 62% with the guard alone).

**Its drills** (`round18k9`, the opponents at their 14 steps as the columns beside it):

| | `round18k5` | `round18k8` (the guard) | `round18k9` (and the punish) |
|---|---|---|---|
| wins, the league's eleven | 96.2 ±0.6 % | 95.0 ±0.7 | 95.0 ±0.6 |
| own HP lost a round there | 48.3 ±0.8 % | 48.6 ±0.7 | 46.2 ±0.8 |
| HP ahead a minute there | 5,162 ±132 | 4,990 ±125 | 5,469 ±134 |
| wins against every habit at once | 80.6 ±2.1 % | 81.2 ±1.9 | 86.9 ±1.9 |
| HP ahead a minute there | 3,597 ±244 | 3,389 ±200 | 4,161 ±217 |
| wins, `recoil` | 82.8 ±1.9 % | 84.1 ±2.2 | 89.7 ±1.6 |
| HP a minute out of its pressure there | −21 ±99 | −148 ±67 | +364 ±96 |
| wins against the CPU with its combos | 34.4 ±6.0 % | 31.2 ±6.2 | 34.4 ±6.0 |

With something after it the guard pays: six points in `sparring` (2.2 errors), seven in
`recoil` (2.8), the pressure there from nothing to +364 HP a minute (the strongest
player's +492), and in the plain league the same wins for two points less of its HP.
Not against the CPU: its 623B there hits 40% and misses 39% of 190 (the CPU moves out,
and recoil-guards one in ten), +214 HP a use for +709 against Sayuri's and +1,083
against Nayuki's.

**The distance.** By the trace the punish hit 22 of 24 times from under 40 pixels, 8 of
12 from 40 to 55 and 3 of 15 from further, and a miss was punished 15 times of 17. With
`rise_recoil_punish_near` 48 (it was 80) it hits 86% for 69% and misses 7% for 27% (24
matches again), 1,350 HP a use for 990. That is the build kept: `k10`.

**The queues stopped once** (20 November 08:59): nine evaluations at once (seven of
round 20's judging and two of these) with the machine's other use growing left 9 GB
available, and the watcher stopped both queues (nothing else); the 32 evaluations not
done were run again four at a time. Four or five at once in all is the limit here.

A reading error on the way, for whoever reads such traces again: evaluate.py's
`Events.add_match` is given all of P1's matches and then all of P2's, not the two sides
of a match in turn; the first breakdowns here took every other entry and were half the
opponent's.

### The level-4 CPU of all eleven, with their `exploiter18`'s combos

Finished for all eleven (the table of 19 November had five): 94 to 100% for the agent,
as against the plain CPU. The mirror is the one hard CPU benchmark.

### Round 20, as started

`agent-league20-spar-s1` (started 20 November 01:53; scratch `league20.sh`,
`round20-arm.sh`, the code frozen as `snap20`): round 19's league and loop from round
18's agent, with two changes. Every player sees the game 11 steps late (`--delay 11`;
the prior is still the clone trained at 14, at its weak pull of 0.01). And the scripted
habits of the matches with advantages are the suite's `sparring` profile in two of three
(`rg=0.3,reversal=0.8,damage=1.5,tech=1,techsafe=1,techhit=1,escape=1,jumpin=0.5,
low=0.6,throw=0.5,bait=0.5`), `person` in the rest, six in ten of the `--vs` matches
with advantages. The other arm (`d11`: the same at 11 steps with round 19's `crowd`
profile, which tells the delay's part from the profile's) starts when the suite's
evaluations leave the memory for it. Judged by the suite with the opponents at 11
steps, beside `round18k5` played the same way.

### Round 20, judged (20 November)

Both arms ended in the morning (20M steps each, about five hours with the machine as
loaded). Each `avg.zip` as an agent file with `round18k8`'s parts, through the game's
code, 64 matches a pairing, **the opponents at 11 steps too** (`bench.py jobs --p2-delay
11`), beside `round18k8` played the same way:

| | `round18k8` | `-d11-s1` (the delay alone) | `-spar-s1` (and the sparring profile) |
|---|---|---|---|
| wins, the league's eleven | 93.5 ±0.9 % | 95.9 ±0.7 | 95.2 ±0.8 |
| own HP lost a round there | 54.8 ±0.7 % | 49.9 ±0.8 | 51.3 ±0.8 |
| HP ahead a minute there | 3,914 ±109 | 4,508 ±127 | 4,408 ±123 |
| where it came by air, HP a minute | 644 ±65 | 1,070 ±67 | 904 ±61 |
| wins against every habit at once | 75.0 ±2.3 % | 80.3 ±2.0 | 86.2 ±2.0 |
| own HP lost a round there | 63.5 ±1.3 % | 61.9 ±1.3 | 57.6 ±1.4 |
| wins, `recoil` | 80.0 ±2.0 % | 85.0 ±2.0 | 87.2 ±1.7 |
| HP a minute out of its pressure there | −35 ±95 | −301 ±71 | −95 ±74 |
| wins against the CPU with its combos | 31.2 ±6.2 % | 28.1 ±5.5 | 50.0 ±7.9 |
| own HP lost a round there | 84.4 ±1.8 % | 88.5 ±2.0 | 79.4 ±2.8 |

By opponent in the league (Sayuri, Mio, Mayu, Nanase, Kaori, Mishio, Ikumi, Nayuki,
Kano, Mizuka, Makoto's): `round18k8` 88 98 97 97 97 97 95 77 84 100 98; `-d11` 98 100
97 97 100 98 89 81 95 100 98; `-spar` 97 100 100 97 100 98 95 75 86 98 100.

**The round passes, and the sparring arm is the one taken.** A policy trained at the
delay it plays at is better than one trained at 14 and run at 11: the league's HP by
three to four and a half errors in both arms, the wins by 1.4 and 2.1. The sparring
profile adds what it was written for and costs nothing measurable in the league: eleven
points against every habit at once (3.7 errors over the mark, 2.1 over the other arm),
seven in `recoil`, and against the level-4 CPU with its combos a half of the matches for
three in ten (1.9 errors: likely, on 64 matches). The first round since 18 whose gain is
outside the noise, and the first trained against an opponent written for the purpose
rather than found. One seed an arm; a second seed of the sparring arm
(`agent-league20-spar-s2`) is training as a check.

What it did not move: the pressure against recoil guards (−95 ±74: the module's part),
Nayuki's (75%), Kano's in the sparring arm (86 for the other arm's 95).

**The build** is the sparring arm's policy with `k10`'s modules (the guard read from the
match, the punish within 48 pixels), judged the same way (the opponents at 11 steps):

| | `round18k8` (the mark) | round 18's policy, `k10` | round 20's, `k8` | **round 20's, `k10`** |
|---|---|---|---|---|
| wins, the league's eleven | 93.5 ±0.9 % | | 95.2 ±0.8 | 95.3 ±0.7 |
| own HP lost a round there | 54.8 ±0.7 % | | 51.3 ±0.8 | 50.2 ±0.8 |
| HP ahead a minute there | 3,914 ±109 | | 4,408 ±123 | 4,679 ±126 |
| wins against every habit at once | 75.0 ±2.3 % | 81.9 ±2.2 | 86.2 ±2.0 | 90.0 ±1.6 |
| wins, `recoil` | 80.0 ±2.0 % | 86.6 ±2.1 | 87.2 ±1.7 | 88.8 ±1.3 |
| HP a minute out of its pressure there | −35 ±95 | | −95 ±74 | +250 ±79 |
| wins against the CPU with its combos | 31.2 ±6.2 % | 25.0 ±4.0 | 50.0 ±7.9 | 43.8 ±4.8 |

The round's policy and the day's modules add up: against every scripted habit at once
75% to 90% (five errors), `recoil` 80% to 89%, the league's HP ahead by 770 a minute
(four and a half errors) for the same reactions on both sides. The file is
`agent-league20-spar-s1-round20.efzagent` (the policy at 11 steps; `rise:1` with
`rise_land`, `rise_sight` 11, `rise_recoil` and its punish; the routes' planner that
settles a late plan). What is still as it was: the level-4 CPU with its combos wins more
than half, Nayuki's `exploiter18` a fifth to a quarter, and the suite's three rows that
no build of the day moved (the corner let go, the endings that let the opponent recover,
what it starts into a strike already out).

**The second seed** (`agent-league20-spar-s2`, ended 20 November about noon; with `k10`'s
modules, judged the same way): league 94.5 ±0.8% (own HP lost 49.7%, 4,675 HP ahead a
minute), every habit at once 87.5 ±1.9%, `recoil` 87.8 ±1.9%, the CPU with its combos
34 ±9%. Beside the first seed's 95.3, 90.0, 88.8 and 44 ±5, and the mark's 93.5, 75.0,
80.0 and 31: the league's HP, the sparring drill and the recoil drill repeat within an
error; the gain against the CPU does not (a seed's 44% and a seed's 34% around the
mark's 31%: nothing can be said of it on 64 matches a build). The first seed stays the
file.

## Round 21: combos for the league (20 November, evening; the plan and the first parts)

The user, after round 20: "we need to build standard big planner combos for all the
league we used to train. Only our agent has combo while the opponent not creates an
advantage." And: "build combos for all 22 characters."

The asymmetry in numbers: the agent's combos are planned from people's routes, 1,750 HP
each with a 90th percentile of 4,070; its trained opponents play their models alone, 560
to 780 HP a combo (860 for Kano's). A hit costs the agent a third of what it costs them,
in every training match and every benchmark since round 15, and the level-4 CPU with the
agent's own combos (the one opponent whose hits cost as much) still wins more than half.

**The plan.**

1. A combo library for each of the 22 characters of the league, from the community's
   replays of that character (`combo_library.py` on its dataset: the 300 most damaging
   and 40 landed on each victim, with their join points), as the agent's own was made.
2. Each trained opponent as an agent file: its model with its character's library
   through the game's route planner (`league_combos.py files`), played by the game's own
   code as the agent's file is. The eleven `exploiter18`s first (the benchmark's), then
   all 90 of the league.
3. A drill of the suite against them (`combos`), and the round 20 file measured there:
   what the agent is worth once a hit costs it what its own costs.
4. A training round whose `--vs` opponents are those files (`finetune.py --vs
   FILE.efzagent --vs-native`), with the sparring profile and the 11 steps of round 20:
   first a trial for its speed and memory (every opponent's plans are made in the
   training loop), then the round.
5. Judged by the suite with the `combos` drill beside the league's.

**The libraries** (`league_combos.py libraries`, 15 seconds a character): 878 to 949
combos each from 17,000 to 32,000 combos of 2,080 to 2,960 matches; the median combo of a
character's players 965 (Shiori, Akane) to 1,670 HP (Nayuki awake), the 90th percentile
2,160 to 4,020.

**A route an opponent can use** (`route_confirm`, `export_agent.py --confirm`). The
first file, Kano's `exploiter18` with her library as the agent has its own (the route
from where it sees its hit, 14 steps after it): 1,084 HP a combo for 860, a route chosen
at a third of its plans. Not for want of meter (a library of her combos without an
Instant Charge or a super: 1,019 HP, a route at 27%). The 14 steps: until its route
begins it plays its own inputs, as the agent does, and an opponent trained without
routes does not press what people's combos go on from. With the route begun sooner (16
matches each against the round 20 file):

| the route begins | a route chosen | HP a combo | 90th percentile |
|---|---|---|---|
| no routes | | 860 | 1,618 |
| 14 steps after its hit (its delay) | 34% of its plans | 1,084 | 1,976 |
| 8 | 46% | 1,220 | 2,398 |
| 4 | 61% | 1,319 | 2,714 |
| 1 | 64% | 1,413 | 3,308 |

So the opponents' files begin a route on the step after the hit. It is a combo confirmed
before the hit is seen, which the agent may not do and an opponent may: what it stands
for is a person's string pressed ahead, and what it is for is the price of a hit. The
option says so where it is set (policy.h's `Routes::confirm`), and the agent's own file
has none. Their models see the game 11 steps late, as round 20's opponents did.

**The opponents' files, and what they cost the agent** (`league_combos.py files`: all 90
of the league, `combos.efzagent` beside each model; the suite's `combos` drill: the
eleven `exploiter18`s as their files; the round 20 file, 64 matches a pairing):

| against the eleven | as they were | with their combos |
|---|---|---|
| wins | 95.3 ±0.7% | 55.8 ±1.8% |
| own HP lost a round | 50% | 75% |
| HP ahead a minute | +4,679 | +534 ±139 |
| HP a combo of theirs | 869 | 1,718 (90th percentile 3,597) |
| HP a combo of its own | 1,563 | 1,641 |
| by opponent, wins (Sayuri, Mio, Mayu, Nanase, Kaori, Mishio, Ikumi, Nayuki, Kano, Mizuka, Makoto) | 98 98 100 97 98 97 92 83 84 100 100 | 33 69 56 81 58 34 62 23 58 61 78 |

A route is chosen at 53 to 84% of their plans (their models at 11 steps carry more of a
combo than Kano's did at 14). Once a hit costs it what its own costs, the league the
agent wins nineteen matches in twenty of is an even one. That is the user's point in a
number, and the measure of how much of every result so far was the price of a hit.

**Round 21 is training** (`agent-league21-combos-s1`, started 20 November 20:00; scratch
`league21.sh`, `round21-arm.sh`, the code frozen as `snap21`): round 20's sparring arm
with the 90 `--vs` opponents as their files through the game's code (`--vs-native`),
from round 20's agent. Three things had to be made for it: the scripted habits' inputs
written over a file's own bytes last (an `opponent_controls` hook with `order` 1:
advantages.AdvantagedOpponent; before, a file's bytes overwrote the script's), the
wrapper attaching and releasing the file's players, and the route option above. A
rollout of 131,072 steps takes 110 seconds (1,190 steps a second, about half of round
20's speed: the opponents' plans are made in the loop) and the trainer 4.6 GB.

## The games of 20 November: the round 20 file in the game

The user played `agent-league20-spar-s1-round20` 11 matches (session
`20261120-191846-8b04`, the game at `2825fd8`: the first session with the day's modules
in the game: the settled plans, the landing rule, the recoil guard's answer and its
punish), all 11 playing again exactly. **The agent took 7 of 11**: Doppel Nanase 3-0,
Nagamori 2-0, Sayuri 2-1, Mishio 0-2, Kano 0-1. The user: "Very strong ... Overall
strong, and overcomed quite a lot of issues we had before", and three observations:

1. "It relys heavily on 'be the first to hit when both are hitting', both in air and
   ground. When air-to-air can't win, it gets pressured. This can be observed in Mishio
   and Kano game."
2. "It sometimes make unnecessary gambling and get punished."
3. "When it can't get advantage during air-to-air, it doesn't adjust the strategy to
   gain more damage from more tense pressure and okizeme. So, no in-game adjustment."

| against the user | `round18k4` (24) | round 20 (11) | ... the 8 it won 7 of | ... Mishio, Kano (3) | strongest player |
|---|---|---|---|---|---|
| matches won | 50% | 64 ±15% | 88% | 0% | |
| HP ahead a minute | −363 ±487 | +594 ±1,100 | +2,190 | −2,920 | +2,431 |
| both in the air | +222 | +432 | +773 | −321 | +114 |
| where it came by air | +283 | +585 | +762 | +194 | −77 |
| where the user came by air | −163 | +877 | +973 | +664 | +556 |
| under the user's pressure | −61 | −472 ±240 | −302 | −847 | +86 |
| on its own rising | −872 | −219 | +516 | −1,842 | +219 |
| out of its own okizeme | +611 | −208 | −100 | −446 | +1,165 |
| out of its own pressure | −398 | −122 | −252 | +164 | +492 |
| raw specials, HP a minute | +278 | −281 ±320 | −335 | −161 | +235 |
| jumps a minute | 18.1 | 18.4 | 17.3 | 20.8 | |

**What moved**: the first session with the HP ahead (+594 a minute; the error is as
large), the user's jump-ins from −163 to +877, its own rising from −872 to −219.

**1, the air and what is behind it: confirmed.** Half of all the HP that moves in these
games moves in the air (it gains 1,474 a minute there and loses 1,043). Where the air
pays (+773 a minute) it wins 7 of 8; against Mishio and Kano the air is lost (−321) and
nothing takes its place: under the user's pressure it gains 84 HP a minute and loses
932, on its own rising it gains 64 and loses 1,906. And it jumps more there, not less
(20.8 a minute for 17.3).

**2, the gamble: one move.** The raw 236C: 32 times in 11 matches, 1.1 a minute (the
community's players 0.5, the strongest 0.6); it hits 44% and is guarded 38% (theirs: 55
to 57% and 20 to 22%), and two guarded or missed in three are punished: −251 HP a use
where it is +310 to +330 for people and was +266 in `round18k4`'s games. The accounts
that stop a raw special start each move at the league's worth (+333 for this one) and
need a few punished uses to turn; three uses a match do not turn them in time. The
supers the same in small (0x133 three times, −1,085 each). The new 623B after its own
recoil guard is not in it: 18 uses, +289 each.

**3, no adjustment: confirmed, and its okizeme is worth less than before.** Out of its
own okizeme −208 HP a minute (`round18k4` +611, the strongest player +1,165): −112 HP a
knockdown. The policy of round 20 was trained against opponents that rise with a
reversal eight times in ten (the sparring profile) and the planner is the same; what the
policy does around the plan changed. Nothing in the agent reads "the air is not paying"
and shifts weight: the accounts it keeps are of raw specials, risings and recoil guards.

**The gamble's price, from the same drill** (`risk.py`'s `PRIORS`, the agent file's
`risk_moves`). The accounts that stop a raw special started each move at the strongest
replay player's HP a use. Against opponents with combos the agent's own uses are worth
(704 matches, the moves used 50 times or more): 236C +53 (the player's +333; in the
league as it was +243), 236A −649 (−130), 236B −1,012 (−131), 623C −460 (+580), 641236A
+83 (+195), 641236B +669 (+290), 236236A −1,577 (−232), 236236B −106 (+90). Those are now
what the accounts start at: 236C is stopped one time in three before anything is known of
the opponent and 95 in 100 after one that cost a combo (1 in 100, and a half, before);
236A, 236B, 623C and the level-one super nearly every time until they have hit. Build
`round20b` (the round 20 file with them), on the `combos`, `sparring` and league drills
as this is written.

Judged (21 November; opponents at 11 steps, 64 matches a pairing):

| | round 20 file | `round20b` | z |
|---|---|---|---|
| opponents with combos: wins | 55.8 ±1.8 | 56.1 ±1.8 | +0.1 |
| ... own HP lost | 74.8 ±0.7 | 74.0 ±0.7 | −0.8 |
| ... HP a combo of its own | 1,641 ±15 | 1,679 ±15 | +1.8 |
| sparring: wins | 90.0 ±1.6 | 90.9 ±1.6 | +0.4 |
| league: wins | 95.3 ±0.7 | 93.5 ±1.0 | −1.5 |
| league: own HP lost | 50.2 ±0.8 | 50.2 ±0.8 | 0.0 |

Nothing outside noise in the matches won. What changed is what it was meant to change:
against the opponents with combos its raw specials went from 2,532 to 1,966 uses (704
matches) and from +94 to +238 HP a use (league: 2,759 at +309 to 2,076 at +404;
sparring: 953 at +266 to 701 at +498); the risk account stopped 68% of the presses it
saw for 43%; 623C and the level-one super are gone, 236C 869 uses to 674. `round20b` is
the base of the next file.

What is left, and is not the account's: 236A (102 uses at −622) and 236B (103 at −799)
are guarded 75-80% of the time, hit 6-7%, punished 38%: cancels out of a guarded string
(236A is counted "in combo" 80% of the time), which a planner's string or the policy's
own cancel plays and the account, which reads a press tried from where it stands with
the opponent pressing nothing, lets by. About 200 HP a match; not traced yet.

### The jump at the opponent, by how it has paid in the match (`risk_jump`; 20 November, night)

The user's first and third points say one thing in two ways: its game is the air, and
when the air does not pay it has no other game and does not look for one. The games say
when the air pays (a forward jump within 400 pixels, the HP swing over the two seconds
after it):

| match | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
| against | Mio | Mio | Mio | Nagamori | Nagamori | Sayuri | Sayuri | Sayuri | Mishio | Mishio | Kano |
| the agent | won | won | won | won | won | won | won | lost | lost | lost | lost |
| forward jumps | 19 | 21 | 33 | 31 | 19 | 21 | 24 | 33 | 35 | 23 | 78 |
| HP a jump | +552 | +502 | +217 | +275 | +332 | +171 | +131 | −56 | +12 | −239 | −115 |

Every match it won, a jump was worth 130 HP or more; every match it lost, 12 or less;
and against Kano it jumped twice as often (19.9 a minute for 10 to 14), at −115 each. A
match has 19 to 35 of them: enough to read inside the match, which a raw special's three
uses are not. Against the opponents with their combos (12 traced matches each): Nanase's
+157 a jump, Nayuki's +33, Mishio's +8, Kano's +2; 1,326 jumps at +55, their spread 614.

So the jump has an account as a raw special has (`Risk::jump`, risk.py's `jump`;
`JumpAct`, `jumping`): its own play's action up and forward while it is free on the
ground with the opponent within 400 pixels (not in a combo it sees); a jump let out and
seen is followed for 130 steps and its HP swing goes to the account; its worth the mean
over a prior counting as 6 jumps; stopped with the probability 1 / (1 + exp(worth /
100)), the action then the same buttons with forward alone, so that what it does
instead is from the ground: its own play's and the planners' (okizeme, pressure). The
account is kept to the next match of the same opponent, older for less, as the others
are. The game's and risk.py's, tested (tests.test_risk, tests.test_agents.RiskAsRiskPy).

Where the account starts is a choice the benchmark is asked: at +250 a jump (optimistic:
8% of the forward jumps stopped before anything is known, more than half only once two
dozen jumps have lost) or at the +55 measured against opponents with combos (38% stopped
from the start, which is a different agent). Both builds (`r20c`, `r20d`: the round 20
policy with the day's modules and the new starting worths of the raw specials) are on
the `combos` drill against the six opponents that punish the air most.

Judged (21 November; Kano, Nayuki, Ikumi, Sayuri, Mizuka, Mishio with their combos, 64
matches each):

| | `round20b` | `r20c` (+250) | `r20d` (+50) |
|---|---|---|---|
| wins (mean of the six) | 45.6 ±2.5 | 46.6 ±2.5 | 45.1 ±2.4 |
| own HP lost | 77.2 | 78.5 | 77.1 |
| draws stopped | - | 37% | 56% |
| jumps a minute | 20.4 | 19.7 | 19.3 |

Nothing, and the last row says why: the account stopped half of what it drew and the
match had as many jumps. A draw holds for the same press (12 steps); the policy asks for
the jump again a moment later, and that is a new draw: at a half a time the jump is out
two tries later. The account delayed jumps; it did not choose the ground.

So a stop lasts: `jump_hold` (`Risk::jumpHold`, `risk_jump_hold`; steps): after a draw
that stops one, every jump at the opponent for that many steps is stopped without a new
draw (a jump let out holds nothing). At 128 steps (two seconds) a match whose account
stops half the draws should lose about four jumps in ten. Builds `r20e` (+50, hold 128)
and `r20f` (+250, hold 128) are on the same six.

Judged (the same six, 64 matches each):

| | `round20b` | `r20d` (+50) | `r20e` (+50, hold 128) | `r20f` (+250, hold 128) |
|---|---|---|---|---|
| wins (mean of the six) | 45.6 ±2.5 | 45.1 ±2.4 | 41.9 ±2.2 | 40.9 ±2.4 |
| own HP lost | 77.2 | 77.1 | 79.5 | 79.2 |
| HP ahead a minute | −329 | −194 | −940 | −856 |
| draws stopped | - | 56% | 55% | 33% |
| jumps a minute | 20.4 | 19.3 | 18.9 | 19.5 |

Worse, if anything (z −1.1 and −1.4 in the wins, both builds and the HP the same way),
and still as many jumps. Sixteen traced matches against Mishio of the base and of
`r20e` say where they come from (jumps a minute, by the direction pressed):

| | forward | straight up | back | from a move (a cancel) | all |
|---|---|---|---|---|---|
| `round20b` | 11.0 | 1.1 | 0.7 | 3.2 | 16.0 |
| `r20e` | 8.6 | 2.3 | 1.1 | 4.0 | 16.0 |

The account let out 45% of the forward jumps it drew there, and the forward jumps fell
by a fifth: 318 forward jumps for the 110 or so the account let out, so two in three
were never drawn (it draws for its own play's jump with the opponent free: a planner's
jump, or one over an opponent in a hit reaction or down, passes; which of the two was
not traced), and what it lost of its own it took back straight up, backwards and out of
its moves. The forward jumps that were
left were worth more (−42 HP a jump to +98), and the match was not: the time it did not
spend jumping in was not spent on anything that pays.

What this says about the user's third point: an account can take a losing move away;
it cannot put a ground game in its place, and this policy has none to fall back on
(every league it trained in paid for the air). The jump's account stays in the code,
off (no `risk_jump` in the next file), until the policy has trained against opponents
that punish the air with a combo's worth: which is round 21.

## Round 21, judged; round 22 started (21 November)

Round 21 as run: `agent-league21-combos-s1`, from round 20's `agent-league20-spar-s1`
average, 20.9M steps (ten chunks, 20:00 to 03:56), every trained opponent of the league
its file with its character's combos through the game's code (`--vs-native`), 11 steps
for every player, the sparring profile as round 20's arm. Its own score against those
opponents (two matches each, so noisy): 0.52 at the start, then 0.51 0.52 0.52 0.58 0.57
0.52 0.59 0.60 0.54 0.61.

Its average as a file with the day's modules (`round21`: the modules of `round20b`, no
jump account), beside `round20b` (the same modules on round 20's policy); opponents at
11 steps, 64 matches a pairing:

| | `round20b` | `round21` | z |
|---|---|---|---|
| opponents with combos: wins | 56.1 ±1.8 | 63.1 ±1.7 | +2.8 |
| ... own HP lost | 74.0 ±0.7 | 71.8 ±0.7 | −2.2 |
| ... HP ahead a minute | 558 ±138 | 1,087 ±125 | +2.8 |
| ... HP a combo: theirs / its own | 1,714 / 1,679 | 1,732 / 1,683 | |
| league (no combos): wins | 93.5 ±1.0 | 96.2 ±0.6 | +2.3 |
| ... own HP lost | 50.2 ±0.8 | 47.0 ±0.8 | −2.8 |
| ... HP ahead a minute | 4,644 ±125 | 5,037 ±123 | +2.2 |
| ... by air, HP a minute | 970 ±63 | 1,137 ±66 | +1.8 |
| sparring: wins | 90.9 ±1.6 | 90.6 ±1.3 | −0.1 |
| ... own HP lost | 55.0 ±1.4 | 52.3 ±1.3 | −1.4 |
| recoil: wins (round 20 file 88.8 ±1.3) | - | 88.4 ±1.7 | |
| ... hit after its recoil-guarded moves (25.9 ±0.8) | - | 23.8 ±0.8 | −1.9 |
| level-4 CPU with combos: wins (43.8 ±4.8) | - | 42.2 ±6.3 | |

The first round judged where the opponents hit as hard as it does, and the gain is there
and outside noise: seven points of wins against the opponents with combos, and the
league without combos better too (it loses less HP: what a combo's worth of punishment
taught carries over). Sparring, the recoil drill and the CPU are level.

Against the opponents with combos, by opponent (wins; own HP lost):

| | `round20b` | `round21` |
|---|---|---|
| Mishio | 31 ±6 (84%) | 58 ±6 (78%) |
| Kaori | 42 ±6 (80%) | 56 ±7 (76%) |
| Mizuka | 53 ±7 (71%) | 69 ±5 (71%) |
| Makoto | 77 ±6 (61%) | 86 ±5 (58%) |
| Ikumi | 72 ±7 (68%) | 80 ±4 (66%) |
| Nayuki | 17 ±4 (87%) | 25 ±6 (83%) |
| Kano | 64 ±7 (72%) | 67 ±4 (70%) |
| Sayuri | 36 ±6 (81%) | 39 ±6 (79%) |
| Doppel Nanase | 69 ±5 (73%) | 72 ±6 (71%) |
| Nanase | 84 ±5 (67%) | 83 ±4 (67%) |
| Mayu | 72 ±6 (70%) | 59 ±7 (71%) |

Up against nine of eleven, Mishio most (where it came by air: −2,252 HP a minute to
−1,121); Nayuki (25%) and Sayuri (39%) are still lost. It takes fewer combos a minute
against ten of the eleven and jumps as often as before (18-24 a minute): it is the same
air game, played with more care, not a different one.

Pick: `agent-league21-combos-s1` (one seed; its gain is 2.8 errors on the drill it
trained for and 2.3-2.8 on the league it did not). File for the game:
`agent-league21-combos-s1-round21.efzagent`.

Round 22, started 05:28: the same league from round 21's average (its ten chunks, kept
as `avg10.zip`), two seeds (`agent-league22-combos-s1`, `-s2`; 20.9M steps each): the
score was still rising when round 21 ended, and two seeds from one start say what a
seed is worth here.

## Playing to the opponent's weak areas (21 November): the plan, and the first measures

The user's idea (21 November): "The agent can score opponent on different dimensions
such as: anti-pressure, pressure, air-to-air, combo damage, defending on okizeme,
okizeme, etc. Based on the advantage/disadvantages of the opponent, it focus on the area
where the other side is bad at, and not try to beat its strength. This might be helpful
to resolve its too much dependency on air-to-air. Our training league should have
diversity too. There are very good players mostly everything is 10/10, but at least they
have relative weakness like 8/10."

One condition comes from the earlier tries: choosing an area pays only if the agent can
play there. The told-habits experiment, round 18's `-adapt` arm and the jump account
(above) all came to the same end: an input or an account can steer a policy away from
what loses, but not toward a skill it lacks. Against Mishio and Kano on 20 November it had
nowhere to go: −472 HP a minute under the user's pressure, −1,842 on its own rising, its
own okizeme −208 a minute where the strongest Ayu player of the replays makes +1,165.

### The scorecard

The areas are `tactics.exchanges`' eight situations. Each is read from the viewer's side
(the agent's, or the community's Ayu player's), and each is the other side of one of the
opponent's skills:

| Situation (the viewer's side) | The opponent's skill it measures | Entered by |
|---|---|---|
| my okizeme | okizeme defence | the viewer (how its combos end) |
| its okizeme | okizeme | the opponent |
| my pressure | anti-pressure | the viewer |
| its pressure | pressure | the opponent |
| I came by air | anti-air | the viewer |
| it came by air | air approach | the opponent |
| both in the air | air-to-air | both |
| on the ground | ground neutral | both |

Combo damage is `opening`: the HP of a hit, either way. Only three areas are the agent's to
enter (its pressure, its jumps, its okizeme through how its combos end): those are what a
choice can move. The opponent's three can only be answered by defence.

Built (21 November): `tactics.situations` (each step's situation, by `exchanges`' own
rule; `exchanges` now uses it and gives the same records as before on 150 replay matches,
5,054 exchanges), `situation_time` (the steps in each) and `episodes` (each time a
situation is entered: who hit first in it, and its HP), reported by `evaluate.py` as
`areas`. For each situation the report gives:

- `share` of the match;
- `rate`, the HP a second ahead while in it (per second in the situation, so that how
  often it comes up does not enter: what one more second spent there is worth);
- `entered` a minute, and the shares of episodes `won` and `lost_first`;
- `each`, the HP of an episode.

`runs/human-ayu/areas.py` tabulates it. `areas.py people` runs it over the community's
matches into `people-areas.json`: by Ayu player, by the opponent's player number and by
the opponent's character, with the read-out below. `areas.py bench TAG` does it by
opponent from a benchmark's results, beside the community's spread. Results older than
the scorecard have the per-minute `net_ledger` only, which it shows instead.

### The community's opponents: strong ones have relative weaknesses

All 1,908 in-sync Ayu matches (2.4 minutes each). The average rate, HP a second for the
Ayu player: my okizeme +78, its okizeme −37, my pressure +19, its pressure −80, I came by
air −44, it came by air +77, both in the air −12, on the ground −30. Each opponent's rate
less that average (−: the opponent is strong there):

| Opponent | Ayu won | My oki | Its oki | My pressure | Its pressure | I came by air | It came by air | Both air | Ground |
|---|---|---|---|---|---|---|---|---|---|
| 473 (534 matches) | 13% | −80 | −28 | −93 | −81 | −56 | −64 | −16 | −41 |
| 438 | 17% | −10 | −45 | −102 | −122 | −14 | −53 | −26 | +6 |
| 449 | 12% | **+72** | −40 | −29 | −46 | −7 | −13 | −27 | +12 |
| 208 | 14% | −49 | +7 | −63 | −41 | −32 | −33 | −23 | −12 |
| 87 | 41% | +16 | +57 | +42 | +77 | **−102** | +82 | −27 | −7 |
| 160 | 40% | −40 | −47 | +6 | +8 | +40 | **−92** | −16 | −10 |

As the user said:
- 473 is strong everywhere, least so in air-to-air.
- 449 is strong but weak on its own rising.
- 438 is strongest on both sides of pressure and about average against a jump.
- 87 is a wall against jump-ins and weak at everything else.

The strongest Ayu player (player 473) is above the average in all eight areas, most under
pressure (+97) and on its own rising (+67).

### How many matches it takes to read an opponent's area

Over the 18 opponents with 20 or more matches, per area: the spread of their true values
(their values' variance less what their own noise explains), a match's noise on one
opponent's value, and the matches it takes for that noise to come down to half the
spread. The rate, then the share of episodes won (the per-attempt read):

| | My oki | Its oki | My pressure | Its pressure | I came by air | It came by air | Both air | Ground |
|---|---|---|---|---|---|---|---|---|
| spread of the rate, HP a second | 66 | 70 | 107 | 104 | 72 | 84 | 26 | 32 |
| a match's noise | 210 | 164 | 223 | 238 | 178 | 255 | 79 | 195 |
| matches (rate) | 41 | 22 | 17 | 21 | 25 | 37 | 38 | 153 |
| matches (share won) | 27 | 21 | 21 | 23 | **7** | 50 | 28 | 55 |

A match holds 2-13 episodes a minute of each, and opponents differ by 2-7 points in the
shares, so the per-attempt read is no faster except for the agent's own jumps. **An 8/10
against a 10/10 (about one spread) takes some 20 matches to see, a whole evening against
one person; it cannot be read within a match or a set.** A hole is another matter: the
matches needed fall with the square of its size, so a hole three spreads deep shows in
2-5 matches. Against an opponent it hasn't read, the agent's best guide is a prior: what
pays against opponents in general. The character explains little of it (by character the
spread is 19-44 HP a second, by player 26-107): who plays matters more than whom they play.

### How diverse the league is

The spread of the agent's per-minute net (round 21's file) across the eleven opponents
with combos (the `combos` drill), beside the spread across the community's opponents,
HP a minute (`areas.py bench r21`):

| | My oki | Its oki | My pressure | Its pressure | I came by air | It came by air | Both air | Ground |
|---|---|---|---|---|---|---|---|---|
| the league with combos | 422 | **177** | 825 | **202** | 860 | 1,359 | 443 | 556 |
| the community | 867 | 580 | 731 | 680 | 620 | 329 | 320 | 205 |

The league varies more than people do in the air (Nayuki's jump-ins: −3,691 a minute) and
on the ground. It varies a third as much in the opponent's okizeme and pressure, and half
as much in its okizeme defence: the three areas where people differ most. The league's
exploiters leave the agent's rising alone (18 November, above), and its opponents'
pressure is the trained policies' own (the scripted knobs throw, jump in and reverse, but
none makes a string).

### The plan, as the measures leave it

1. **The scorecard everywhere** (done for evaluations, play-tests through `bench.py
   record`, the community). From round 22's file on, a benchmark's results carry `areas`,
   and the agent's own row sits beside the strongest player's.
2. **A league that differs where people differ (round 23).** Planners are given to the
   league's opponents as combos were in round 21: its files with the okizeme and pressure
   planners (`okiplan`, `pressplan`) at a strength drawn per opponent. And spiky scripted
   profiles: the sparring profile with the knobs of one area lowered, drawn per set
   (okizeme on the agent: `jumpin`, `low`, `bait`; okizeme defence: `wake`, `blind`,
   `patient`, `crouch`; anti-pressure: `rg`, `reversal`, `escape`, `throw`). Rule, fixed
   before: the new league is taken if, with the current file against it, its spread in
   its okizeme and its pressure reaches half the community's or more. Then round 23 is
   judged as round 21 was: the drills with their errors, plus the agent's areas beside
   the strongest player's.
3. **The agent's own choices steered by the scorecard, for holes only.** The levers that
   exist:
   - knockdown endings (`route_ending`), against an opponent whose rising is weak (lost
     twice as a global setting);
   - the jump account (`risk_jump`), only where the air loses and the ground holds;
   - the raw specials' priors, per opponent.

   A lever is moved when the area's read is two errors or more below the prior (a hole),
   with the read carried across a session, not a match. The read is of episode counts (who
   hit first, per situation), not HP: "What a read should count", below. It is judged on drills whose
   opponent has a known hole (a spiky profile) and kept if it gains two errors there and
   loses under one on the plain league.
4. **A style input only after 2 and 3**: if the agent has the areas but shifts between them
   too little, it gets a style token trained with a reward for that area's play, and a
   selector chooses the style from the scorecard. Not before: an input alone was not used
   (the told-habits experiment).

### Step 2, built (21 November)

- `league_combos.py libraries --kind oki|press`: people's okizeme and follow-ups to a guard
  for the eleven league characters (`~/data/efz-replays/oki/CHAR.npz`,
  `~/data/efz-replays/press/CHAR.npz`, with their answers). They hold 7,397 (Nanase) to
  18,873 (Kano) okizeme that touched the riser within 20 steps, and 11,065 to 36,037
  follow-ups.
- `league_combos.py files --oki --press` puts them into each opponent's file as its planned
  okizeme and pressure. The settings are the agent's own (`OKI`, `PRESS`), with
  `--oki-skip`/`--press-skip` the share of chances it leaves to its model. These are the
  `planners.efzagent` files beside the `exploiter18`s: routes, `okiplan:2`, `pressplan:1`,
  19.4 MB for Kano's.
- In a two-match look through the game's own code, Kano's file planned 15 okizeme (played
  14) and its pressure 9 times (played 8).
- bench.py's drill `planners`: the eleven as those files.
- `advantages.py`'s `weak`: the share of matches (of sets, with sets) in which one area of
  the scripted profile (okizeme: `jumpin`, `bait`; okizeme defence: `wake`, `blind`;
  anti-pressure: `reversal`, `patient`, `throw`) keeps `WEAK` (a quarter) of its values.
  That gives an opponent strong everywhere but in one area, drawn afresh. The area is drawn
  among those the profile has; the sparring profile has no okizeme defence (`wake` 0).

### Step 2, measured (21 November): the rule is not met

Round 21's file against the eleven with planners (`bench/r21p`, 64 matches each through
the game's own code), beside the same eleven with combos only (`bench/r21`). The spread
across opponents of the agent's net, HP a minute (`areas.py bench DIR --net`; in brackets
the range a resampling of the opponents and of their errors gives, 16th to 84th
percentile):

| | Its okizeme | Its pressure | bar (half the community's) |
|---|---|---|---|
| combos only | 177 (0-269) | 202 (0-277) | |
| with planners | 273 (0-360) | 0 (0-111) | |
| both kinds, 22 opponents | 279 (175-336) | 125 (0-192) | 290 and 340 |

By the rule fixed before, the league with planners is **not taken as the answer to
diversity**: its okizeme stops just under the bar, inside its error either way, and its
pressure is nowhere near.

What the planners did change is the level of the opponents' okizeme, not how far they
differ:

| The opponents' side, mean of eleven | combos only | with planners | people's opponents |
|---|---|---|---|
| The agent's wins | 63% | 56% | |
| The agent's net under their okizeme, HP a minute | +164 | −168 (a fall of 333 ± 85) | −326 (the strongest player: +219) |
| Their okizeme hits first | 18% | 28% | |
| Their okizeme meaty | 38% | 49% | |
| Their strings a minute | 2.3 | 2.6 | 5.2 |
| Guards a string | 1.19 | 1.23 | 1.41 |
| After a guard, guarded again | 20% | 22% | 35% |
| The agent's net under their pressure, HP a minute | +142 | +102 (−40 ± 72) | −513 (the strongest: +86) |

No other area moved by more than its error. Nayuki's file gains most (the agent wins 11%,
from 25%), Ikumi's next (50% from 80%).

Two readings:

- **The okizeme planner makes the league's okizeme as strong as people's** (the agent's
  net under it is now below zero, as the community's players' is). That is a change of
  level in an area the play-tests named (19 November: rising lost to lows), to be judged
  as the combos were: a round trained against these files, kept if it gains against them
  and loses nothing elsewhere. The spread between opponents can come from the share of
  chances the planner takes (`--oki-skip`), drawn per opponent, since the planner's effect
  already differs by character (a spread of 320 in the shift).
- **The pressure planner does not make pressure.** It continues a string after a guard,
  but the league's opponents start half as many strings as people and the agent is under
  pressure 3.3% of a match (people 10.7%, the strongest player 8.5%; 2.3 times a minute
  against 4.7 and 4.1). What is missing is the start of pressure (the approach that makes
  the agent guard on the ground) and staying on it, neither of which a follow-up planner
  supplies. At 3% of a match an opponent's pressure cannot be read at all: the errors on
  the per-second rate are 38-171 HP against a community spread of 104.

### What a read should count (for step 3)

The two kinds of file are the same opponent with a strong okizeme and without one: a
known difference of about the size people differ by (333 HP a minute; the community's
spread is 580). How many matches each figure needs to tell them apart, by its noise a
match (the error over 64 matches times 8) and the mean shift over the eleven
(4·noise²/shift², two errors):

| Figure | combos only | with planners | noise a match | matches |
|---|---|---|---|---|
| The agent's net under its okizeme, HP a minute | +164 | −168 | 1,588 | 91 |
| HP lost under it, a minute | 804 | 1,281 | 1,133 | 23 |
| Its okizeme hits first | 18% | 28% | 17 points | 11 |
| Its okizeme is meaty | 38% | 49% | 19 points | 11 |
| Its okizeme makes contact | 39% | 54% | 21 points | 8 |
| The agent's wins | 63% | 56% | 45 points | 185 |

HP is the slowest read by far: one combo more or less in a match swamps it. What happened
in each episode (who hit first, whether the okizeme was on time, whether it touched)
reads in 8-11 matches what HP reads in 91. So step 3's read is of episode counts, with
HP kept for judging afterwards, and even so a difference of this size takes a session,
not a match. The scripted habits are no deeper: the sparring profile's okizeme (`jumpin`,
`low`, `throw`, `bait`) costs the agent about 290 HP a minute under it against the plain
opponents (five opponents, `bench/r21`), so `weak`, which leaves a quarter of it, makes a
difference of about 220.

So step 2 stays open for pressure. The scripted profile has no knob that starts
pressure (it throws, jumps in on a knockdown and reverses), so the candidates are all new
work, in the order of their cost: clones of the community's players who press most
(`people.json`'s by-player figures give who: 5.9 strings a minute for the strongest
against 3.4 for the least), as league opponents; a scripted approach that seeks the
agent's guard, drawn strong for some opponents as `weak` draws an area weak; a pressure
exploiter trained with a reward for time on the agent's guard.

## Round 22, judged, and continued (21 November, afternoon)

Round 22 as run: `agent-league22-combos-s1` and `-s2`, two seeds from round 21's average
(`avg10.zip`), the same league (every trained opponent its file with its character's
combos), 20.9M steps each, 05:28 to 11:36 side by side. Their own scores against the
training opponents (two matches each, noisy): seed 1 0.59 0.57 0.57 0.56 0.59 0.60 0.62
0.64 0.62 0.61; seed 2 0.62 0.58 0.57 0.64 0.63 0.65 0.63 0.69 0.64 0.69 (round 21 ended
at 0.61).

Their averages as files with round 21's modules (`round22s1`, `round22s2`), beside
`round21`; opponents at 11 steps, 64 matches a pairing, z against `round21`:

| | `round21` | `round22s1` | z | `round22s2` | z |
|---|---|---|---|---|---|
| opponents with combos: wins | 63.1 ±1.7 | 64.3 ±1.7 | +0.5 | 63.8 ±1.7 | +0.3 |
| ... own HP lost | 71.8 ±0.7 | 71.0 ±0.8 | −0.8 | 70.8 ±0.7 | −1.0 |
| ... HP ahead a minute | 1,087 ±125 | 1,264 ±140 | +0.9 | 1,295 ±126 | +1.2 |
| league (no combos): wins | 96.2 ±0.6 | 96.7 ±0.7 | +0.5 | 98.0 ±0.5 | +2.3 |
| ... own HP lost | 47.0 ±0.8 | 47.4 ±0.8 | +0.4 | 44.1 ±0.8 | −2.6 |
| ... HP ahead a minute | 5,037 ±123 | 4,835 ±130 | −1.1 | 5,285 ±128 | +1.4 |
| ... by air, HP a minute | 1,137 ±66 | 1,282 ±60 | +1.6 | 1,306 ±63 | +1.9 |
| sparring: wins | 90.6 ±1.3 | 90.6 ±1.4 | 0 | 90.6 ±1.6 | 0 |
| ... own HP lost | 52.3 ±1.3 | 52.4 ±1.2 | 0 | 51.0 ±1.1 | −0.8 |
| recoil: wins | 88.4 ±1.7 | 91.6 ±1.1 | +1.6 | 94.7 ±1.2 | +3.0 |
| ... hit after its recoil-guarded moves | 23.8 ±0.8 | 21.5 ±0.8 | −2.0 | 22.1 ±0.8 | −1.5 |
| level-4 CPU with combos: wins | 42.2 ±6.3 | 35.9 ±5.6 | −0.7 | 40.6 ±5.0 | −0.2 |

Against the opponents with combos the second round added nothing that can be told from
noise: 63.1 to 64.3 and 63.8 (the two seeds together 64.0 ±1.2: +0.4 errors). Round 21
took the seven points that were there for a policy that had never been hit that hard;
a second round of the same did not find more, as these files measure it. (They carry the
pressure planner, which hides it: without the planners round 22 is worth eleven points
there. "The planners, off", below.) Seed 2 is better where the opponents have
no combos (league 98.0%, less HP lost, and the recoil drill 88 to 95%), seed 1 is level
with round 21 there: a seed is worth about two points of league wins and three of its
own HP, as much as a round.

By opponent, against the opponents with combos (wins; ±5-7 each):

| | `round20b` | `round21` | `round22s1` | `round22s2` |
|---|---|---|---|---|
| Nayuki | 17 | 25 | 36 | 41 |
| Sayuri | 36 | 39 | 36 | 36 |
| Kaori | 42 | 56 | 58 | 61 |
| Mishio | 31 | 58 | 63 | 67 |
| Mayu | 72 | 59 | 63 | 67 |
| Kano | 64 | 67 | 73 | 58 |
| Mizuka | 53 | 69 | 75 | 67 |
| Doppel Nanase | 69 | 72 | 75 | 67 |
| Ikumi | 72 | 80 | 66 | 69 |
| Makoto | 77 | 86 | 72 | 80 |
| Nanase | 84 | 83 | 92 | 89 |

Nayuki keeps coming up (17, 25, 36-41: where she came by air −3,691 HP a minute to
−1,626), Mishio too; Sayuri has not moved in three rounds; the others move inside
their errors. It jumps as often as ever (21 a minute).

Where the HP goes, by situation (HP a minute gained − lost, the mean of the eleven
opponents; `round22s2`, with `round20b` to `round22s1` in brackets where it moved):

| situation | with combos | without |
|---|---|---|
| its okizeme (the opponent down) | 1,443 − 891 = +553 | +1,223 |
| the opponent's okizeme | +225 | +407 |
| **its pressure (the opponent guarded)** | **1,543 − 2,137 = −594** (−686, −702, −554) | +504 |
| the opponent's pressure | +19 | +350 |
| it came by air | 1,870 − 1,244 = +626 (+21, +434, +447) | +1,306 |
| the opponent came by air | +374 (+163, +216, +393) | +793 |
| both in the air | +8 | +307 |
| on the ground | +83 | +394 |

Every situation is at or above even but one: after the opponent has guarded a move of
its own, it loses 2,100 HP a minute and gains 1,500, and two rounds against opponents
with combos have not moved that (the air is what they moved: +21 to +626). Against
Sayuri it is 1,122 − 3,505, against Mayu 1,170 − 2,954, Kano 1,376 − 2,539, Mishio
1,272 − 2,478; only Nanase (+1,879) and Ikumi (+193) are above even. Without combos the
same pressure is +504: by what a loss costs it is hit out of it about as often,
and each time costs 2,000 HP instead of 1,000. The user's third point of 20 November
(no more damage from pressure and okizeme when the air does not pay) from the other
side: its pressure is where an opponent that converts gets its HP. Traced below: it is
the pressure planner's.

Pick: `agent-league22-combos-s2` (level with round 21 against the opponents with combos;
ahead on the league, its own HP and the recoil drill). File for the game:
`agent-league22-combos-s2-round22.efzagent`.

Started 14:57: one seed more of the same league from seed 2's average, so the training
goes on (the folder is `agent-league23-combos-s1`; it is round 22 continued, not the
round 23 of "Playing to the opponent's weak areas" above, whose league is new); the
second place was kept for an arm against the pressure leak, which turned out to need no
training (below). Its score after four chunks: 0.67 0.69 0.68 0.66.

### The planners, off (21 November, evening)

**The trace.** 24 matches each against Sayuri's, Mayu's and Kano's files with combos
(`round22s2`; scratch `ptrace.py`), the losses that began within 45 steps of the
opponent's guard: 3,110, 3,243 and 2,017 HP a minute, against 1,048, 1,079 and 1,296
gained. What it was doing when hit:

- in no move on the ground (871, 1,705, 630 HP a minute): walking forward or standing
  (not crouching: 0x1 and 0x0 are 60-80% of it), free for 8-11 steps, 39 px away,
  hit by a move that had been out 3-6 steps: the opponent's 2A (Sayuri 1,200 HP a
  minute, Kano 1,234, Mayu 1,085) or Mayu's invincible rising move (1,458). Nothing an
  11-step player can see coming;
- having jumped out of its string (Sayuri 838);
- in the next move of its string, 2C or 2B after a guarded 5B (Kano 924).

The opponents answer 38-48% of its strings with a move and get out (30-36%) more often
than they are caught (21-28%); each time out is 2,000 HP with combos.

**Whose pressure.** Training has no planner on the agent's side (`assist` none): the
policy presses by itself there. The file has `pressplan`: after a guarded move the game
plays a follow-up from people's library, 360 times in those 24 matches against Sayuri.
People's follow-ups (walk in, press again after a gap) are played against people who
guard; the league's opponents with combos press 2A in the gap.

**Measured.** Round 22 seed 2's policy with both planners (`round22s2`), without the
pressure planner (`r22np`: routes, chooser, okiplan, airthrow, rise, risk) and without
either planner (`r22no`: no okiplan); opponents at 11 steps, 64 matches a pairing, the
whole suite:

| | both planners | no pressure planner | no planners |
|---|---|---|---|
| opponents with combos: wins | 63.8 ±1.7 | 76.4 ±1.7 | 79.5 ±1.5 |
| ... own HP lost | 70.8 ±0.7 | 62.8 ±0.9 | 60.4 ±0.9 |
| ... HP ahead a minute | 1,295 ±126 | 2,652 ±152 | 2,794 ±138 |
| ... HP a combo of its own | 1,683 | 1,882 | 1,877 |
| league (no combos): wins | 98.0 ±0.5 | 99.1 ±0.3 | 98.3 ±0.5 |
| ... own HP lost | 44.1 ±0.8 | 37.0 ±0.7 | 37.9 ±0.7 |
| ... HP ahead a minute | 5,285 ±128 | 6,353 ±128 | 5,895 ±118 |
| ... rounds won from 3,000 HP behind | 71.1 ±4.2 | 84.3 ±2.7 | 83.6 ±2.6 |
| sparring: wins | 90.6 ±1.6 | 93.8 ±1.4 | 97.2 ±0.9 |
| ... own HP lost | 51.0 ±1.1 | 47.4 ±1.2 | 43.7 ±1.2 |
| recoil: wins | 94.7 ±1.2 | 96.9 ±0.9 | 95.6 ±1.2 |
| ... HP a minute out of its pressure | 284 ±94 | 1,049 ±100 | 1,089 ±115 |
| level-4 CPU with combos: wins | 40.6 ±5.0 | 35.9 ±6.4 | 59.4 ±6.4 |
| ... own HP lost | 83.7 ±1.9 | 83.8 ±1.8 | 79.5 ±2.4 |

Without the pressure planner: 12.6 points of wins against the opponents with combos
(5.2 errors), eight points less of its HP lost there and seven on the league, its
pressure in the recoil drill 284 to 1,049 HP a minute; nothing is worse (the CPU is
inside its error). By opponent with combos: Sayuri 36 to 75, Kano 58 to 88, Makoto 80
to 95, Nayuki 41 to 56, Mizuka 67 to 83, Mayu 67 to 83, Kaori 61 to 73; Ikumi 69 to 55
is the one that fell. Its pressure against the four traced: −1,634 HP a minute to +197.

Without the okizeme planner as well: three points more against the opponents with
combos (1.4 errors), sparring 93.8 to 97.2 (2.0), the CPU with combos 36 to 59 (2.6);
the league's HP ahead a minute 6,353 to 5,895 (−2.6; its wins 99.1 and 98.3). The
planned okizeme pays against opponents that cannot make it cost and loses against those
that can. (On the opponents' side it is the other way about: "Step 2, measured", above:
the okizeme planner made the league's okizeme as strong as people's.)

**Round 22 again, without planners.** Round 21's policy with the same modules (`r21no`)
beside `r22no`:

| | round 21 | round 22 (seed 2) | z |
|---|---|---|---|
| opponents with combos: wins | 68.5 ±1.5 | 79.5 ±1.5 | +5.2 |
| ... own HP lost | 67.6 ±0.7 | 60.4 ±0.9 | −6.3 |
| league (no combos): wins | 97.2 ±0.5 | 98.3 ±0.5 | +1.6 |
| ... own HP lost | 42.0 ±0.7 | 37.9 ±0.7 | −4.1 |

Nayuki 25 to 66, Sayuri 47 to 78, Mishio 55 to 73, Doppel Nanase 63 to 81, Mizuka 63
to 75; Ikumi 80 to 64. So the round was worth eleven points against the opponents with
combos, not one: the planner's losses were what both rounds' files had in common, and
what the policy had learnt about pressing these opponents was never played. The rounds
of this league are still paying, and the continuation is worth its time.

**The file.** `round22b`: seed 2's policy with routes, chooser, airthrow, rise and risk,
no planners (`agent-league22-combos-s2-round22b.efzagent`); `round22` with both planners
stays beside it for the comparison in the game. Left open, and the reason the planners
stay in the code:

- every opponent of the suite is a trained model or a script. Against a person who
  guards a string through, people's follow-ups may be worth what they were built for;
  the games decide.
- the planners as a choice by the scorecard ("Playing to the opponent's weak areas",
  step 3): planned pressure against an opponent that does not answer strings with a
  move, planned okizeme against one whose rising is weak, the policy's own otherwise.
  How often its strings are answered with a move is an episode count, the kind of read
  that is fast.

### Round 22 continued, judged

`agent-league23-combos-s1` (seed 1, ten chunks from round 22 seed 2's average, the same
league), its average with round 22b's modules (`r23no`) beside round 22's (`r22no`), 64
matches a pairing:

| | round 22 | continued | z |
|---|---|---|---|
| opponents with combos: wins | 79.5% ±1.5 | 78.8% ±1.6 | -0.3 |
| ... own HP lost | 60.4% | 60.8% | +0.3 |
| league without combos: wins | 98.3% ±0.5 | 99.0% ±0.4 | +1.1 |
| ... net HP a minute | 5,895 ±118 | 6,201 ±115 | +1.9 |
| sparring: wins | 97.2% ±0.9 | 97.2% ±0.8 | 0 |
| recoil drill: wins | 95.6% ±1.2 | 97.2% ±1.0 | +1.0 |
| level-4 CPU with combos: wins | 59.4% ±6.4 | 40.6% ±7.9 | -1.8 |

Nothing outside noise: a third round of the same league teaches no more (Sayuri 78 to
67%, Mizuka 75 to 61%, Mayu 80 to 86%: by opponent it moves both ways). Round 22's
policy stays the pick, and the next round needs opponents this one has not met.

## The games of 21 November: under pressure

The user (21 November, round 21's file with both planners, session
`20261121-203817-72c5`): "It relys heavily on air-to-air, and sucks under pressure and
handle objects." Ten matches, the agent lost all ten (20 November, round 20's file: 7 of
11): nine with round 21's file and one, the second against Nagamori, with round 20's (the
game's selector was left on it). Opponents: Nagamori four times, Nanase twice, Kano,
Sayuri, Ikumi, Shiori. Three of the ten did not play again from their records at first:
the user pressed a button in a round's intro, which the game starts no move from and the
headless match did; `from_record.py` now leaves such a press out until it is let go, and
all ten play again exactly.

One session of one file each: what follows cannot tell round 21's file from the user's
play that evening (the one match round 20's file played was lost too, -1,393 HP a
minute).

### By the ledger

HP a minute by the situation an exchange began in, the agent's side (`bench.py record`,
the errors by jackknife; `h1120`, `h1121` in `bench/`):

| | round 20, 20 Nov (11 matches) | round 21, 21 Nov (9 matches) |
|---|---|---|
| all | +594 | -2,330 |
| the user's okizeme | -219 ±540 | -1,550 ±410 |
| the user's pressure | -472 ±240 | -1,460 ±380 |
| the user came by air | +877 ±420 | -89 ±380 |
| both in the air | +432 ±440 | -426 ±250 |
| it came by air | +585 ±610 | +733 ±640 |
| its okizeme | -208 ±400 | +338 ±280 |
| its pressure | -122 ±420 | -75 ±210 |
| on the ground | -279 ±260 | +201 ±150 |

The user's three points, counted:

- **The air.** 56% of the HP it takes off the user is taken in the two air situations it
  gains in (3,610 of 6,490 a minute). It loses 3,270 HP a minute attacking in the air
  (2,240 the day before, 1,270 on 19 November), 2,070 of them to moves from the ground,
  2,750 in the open field. 18.8 jumps a minute, as before.
- **Under pressure.** Of the 1,890 HP a minute it loses there (the losses that began
  within 45 steps of a guard of its own), 860 are lost in the air or in a jump's start
  (it jumped out), 605 in a move of its own, 300 opened in its guard and 140 in chip:
  three quarters by leaving the guard, and 1,300 of them 26 to 60 steps after its last
  guard: the user lets the string go and hits what comes out. After a guard it jumps 35%
  of the time (19% the day before): 2% get away, 27% are hit. It presses a move 26%: 27%
  hit first, 42% are hit. Its strings: 1.8 a minute (3.3), the gap in them 18.5 steps
  (11).
- **Objects.** With one of the user's objects out it loses 15,300 HP a minute of that
  time, without one 6,900; 12,600 and 7,000 on 19 November, 14,100 and 5,900 on the
  20th: the same weakness in each session. What changed is the share of the time: 31%
  for 19%, and half of all it lost came with an object out (36%), 2,200 a minute of it
  in the air (1,090). The measure of 19 November (a hit by an object it started
  something into) says little of this: 481 ±160 for 351 ±180.

On its rising it loses 2,370 HP a minute (1,290): 790 rising without acting, 530 opened
in its guard, 550 in the air; the attacker hits first at 40% of its risings (24%).

### Why the league does not teach it

Against the league's opponents (`r22no`, the four drills) the agent guards 4 to 7 times
a minute; against the user 13 to 18. There a move pressed after a guard hits first 31 to
37% of the time and is hit 14 to 19%, a jump out is hit 16 to 18%, and the agent's
balance under their pressure is +8 to +350 HP a minute. Nothing in the league holds it
in a guard, so what it has learnt to do after one is press or jump, and that is what the
user punishes. The planners of step 2 above (people's pressure for the league's
opponents) "do not make pressure" by the other session's measure, for the same reason:
a model that does not press gives its planner nothing to plan from.

### What is built

**A reward for pressure** (`focus.py`'s `press`, `finetune.py --focus press`): a move of
the learner's that the opponent guards (a guard touched, not a recoil guard) adds a
fifth of the coefficient, and a hit that begins the opponent's hit reaction (or a throw)
within 60 steps of such a guard adds all of it. Exploiters of round 22's agent as the
game plays it (`round22b.efzagent`, `--vs-native`) are in training with it at 0.05
(500 HP's worth a hit, 100 a guard), from each character's `exploiter18`, 6M steps
each: `CHAR/exploiter19`, the eleven characters of the league, four at a time.

**The guard under pressure** (`rise.py`'s `press`, the game's `rise_press`: the same
code path as the rising's guard by sight). A string (a guard of its own on the ground
that it sees touched, none in the 36 steps before) is drawn for once; one that is held
is guarded on by sight, standing under an opponent in the air, from the first view of
the guard until 36 steps after the last (a new guard starts the count again), or until
it sees itself or the opponent hit, or the opponent further than 200 pixels for 8 steps.
Whether a string is held is read from the match: of its exits (a move, or itself in the
air, seen within 30 steps of a guard in a string not held) those caught (itself hit
within 50 steps) less those that won (the opponent hit first), an exit, over a prior of
+0.1 counting as 4 exits; none held at -0.05, all at +0.15. Read over the user's three
sessions as recorded (no string held: `pressread.py` in the scratch folder): -0.11 an
exit on 19 November (its exits won 33% and were caught 22%: the session its balance
under pressure was -61), -0.01 on the 20th (-472), +0.13 on the 21st (-1,460), where it
holds the strings of six of the nine matches by their middle. A first build counted the
caught alone (21 to 28% against the user, about 17% against the league: too close).

It gives the policy nothing to do from a guard but guard: a throw and a high-low
guess still open it, and what it should do when the string is over is the policy's.
Whether holding costs against opponents whose pressure is weak is the league's drills
to say, and whether it saves anything against pressure is the `exploiter19`s' and the
user's games.

### The same evening, round 22b's file (no planners)

The user (21 November, session `20261121-212955-6582`, `round22b`): "Similar issue with
pressure and objects, and it seems losing almost everything about okizeme (air, reverse)
from r17." Fourteen matches (Mishio three times, Nagamori three, Sayuri, Doppel Nanase,
Ikumi and Kano twice each), the agent took 6 (round 21's file an hour before: 0 of 9);
-1,000 HP a minute (-2,330). The user's pressure -437 ±300 (-1,460), the user's okizeme
-614 ±330 (-1,550), its own pressure +454 ±370 (-75 with the pressure planner, -122 with
round 20's), and it guarded 21 times a minute (15). With an object out it lost 11,400 HP
a minute of that time for 6,700 without (28% of the time).

Its okizeme, by session against the user (`bench.py record`):

| | 17c, 16 Nov | 18k4, 19 Nov | r20, 20 Nov | r21, 21 Nov | 22b, 21 Nov |
|---|---|---|---|---|---|
| the okizeme planner in the file | yes | yes | yes | yes | no |
| HP a minute, net | +861 | +611 | -208 | +338 | -389 |
| HP a knockdown | +234 | +120 | -112 | +24 | -304 |
| it hits first | 38% | 32% | 25% | 32% | 7% |
| from the air | 55% | 42% | 39% | 46% | 7% |
| low / high | 29 / 55% | 34 / 33% | 33 / 35% | 31 / 53% | 75 / 6% |
| cross-up | 6.8% | 2.5% | 4.5% | 3.1% | 0 |

Without the planner the policy's okizeme is a 2A at seven knockdowns in ten, as round
15's was, and a person guards it. So "The planners, off" above holds for the pressure
planner and not for the okizeme planner: the suite's opponents answer an okizeme with a
move (the planner loses to that) and the user with a guard (the policy's own loses to
that), and the suite could not tell, as that section said. The next file is round 22's
policy with the okizeme planner and without the pressure planner (the middle column of
that section's table: 76.4% against the opponents with combos, 99.1% the league, 93.8%
sparring): `round22c`, with `rise_hold` 30 and `rise_press` 36 beside it, which act in a
game built with them.

What the table also shows and nothing here explains yet: with the planner in, its
okizeme was worth less against the user in each file after 17c, with fewer cross-ups and
less of it from the air.

### The guard on its rising, once it is up

Of the 2,370 HP a minute round 21's file lost on its rising against the user, about
1,250 were lost 12 to 32 steps after it was up: 670 "rising, not acting", 250 in a move
pressed there, 330 in a jump begun there. The guard on rising ends where the agent sees
itself up, which is its delay (11 steps) after it is: in the records the guard is let go
exactly 11 steps after the rising at four risings in ten, and a move of the attacker's
that is still out then (a late meaty, Nagamori's hop, a jump-in) hits what its own play
does next. `rise.py` had the answer (`hold`: the guard goes on by sight while the
attacker is in a move or in the air within reach, until 8 steps without) and the game's
code did not: `Rise::hold` (`rise_hold`, steps; `rise_gap`), step for step with
`rise.py`'s (`test_the_guard_goes_on_once_it_is_up`).

### The two guards against the user's recorded okizeme and strings

A check that needs no opponent: each fight of the two sessions is played again from its
record, and at each knockdown of the agent's (351) and at each first guard of a string
(104, none in the 60 steps before) the game is saved and an agent file plays the agent's
side from there against the inputs the user pressed, the game then put back (`cf.py` in
the scratch folder; a fresh agent warmed on the 80 frames before each point, so the
files' reads are forced: every rising guarded, every string held). The user pressed
those inputs against another agent, so only the first second means anything, and a
person who met a guard would do something else next: it says what the guards do to the
okizeme and the strings as they were played, not what they are worth. Round 22's policy
without planners:

| | recorded | no hold | `hold` 30 | `press` 36 | both |
|---|---|---|---|---|---|
| risings, round 21's session (144): hit in the 45 steps after it is up | 26% | 24% | 3% | 15% | 1% |
| risings, round 22b's session (207) | 16% | 19% | 6% | 14% | 5% |
| strings, round 21's session (44): hit in the 80 steps from the first guard | 23% | 27% | 27% | 11% | 11% |
| ... HP lost / dealt a string | 237 / 84 | 289 / 94 | | 136 / 41 | |
| strings, round 22b's session (60) | 15% | 17% | 17% | 2% | 2% |
| ... HP lost / dealt a string | 92 / 80 | 74 / 95 | | 32 / 20 | |

The rising's hold closes most of what the okizeme as played hit it with, at no cost
measured (it deals 16 HP a rising without and 5 with). A string held every time halves
what it loses and takes away most of what its exits win: -195 HP a string to -95 in
round 21's session, +21 to -12 in round 22b's, where its exits paid: what the read is
for (+0.13 an exit in the first session, held; +0.02 in the second, a third held).

### The guards in the user's game (22 November, round 22c)

Session `20261122-001919-5d48`, the game built at the merge with both guards, `round22c`
(round 22's policy, the okizeme planner, `rise_hold` 30, `rise_press` 36): five matches
(Sayuri, Nagamori twice, Mishio, Ikumi), the agent took one. HP a minute, the agent's
side (`h1122`; five matches, the errors several hundred on each row):

| | round 21 | 22b | 22c |
|---|---|---|---|
| the user's okizeme | -1,550 ±410 | -614 ±330 | -47 ±340 |
| the user's pressure | -1,460 ±380 | -437 ±300 | -287 ±360 |
| it came by air | +733 ±640 | -6 ±440 | -1,080 ±540 |
| both in the air | -426 | -391 | -710 |
| its okizeme | +338 | -389 | +94 |
| combo HP it deals | 6,430 | 6,480 | 5,180 ±640 |
| lost thrown | 149 | 106 | 627 ±320 |
| all | -2,330 | -1,000 | -2,050 |

**The rising's hold does what the records said it would.** Rising without acting costs it
57 HP a minute (727 with round 21's file, 166 with 22b's), the attacker hits first at 23%
of its risings (40%, 28%), and by the game's log it guarded 250 to 570 steps a match
"more once up". Against this session's recorded okizeme (`cf.py`, 81 risings) a file
without the hold is hit in 28% of the 45 steps after it is up, with it 6%; as played, 10%.

**The pressure's hold was too sticky.** The log of the first two matches: "33 strings, 32
held (4609 steps guarded on); 1 exits out of the others", "19 strings, 19 held": 29% of
the first match in a forced guard. The read is of the exits out of strings not held, a
held string has none, and the prior holds three strings in four: so the record that
should switch it off does not fill, and one caught exit over the prior makes it all of
them. Where exits were sampled they came out even or ahead (matches three to five: 33
exits, 6 caught, 10 that hit first) and it stopped holding (1 of 26, 5 of 18). What the
held strings cost: thrown for 627 HP a minute, 31.6 guards a minute (21.3), 14.8 jumps
(18.5), and 1,300 HP a minute less dealt; what they saved under pressure, 150. Against
this session's recorded strings, which were pressed against a guard that holds, a file
that never holds loses 88 HP a string and deals 108, one that always holds 17 and 13.

So `round22d` (22 November): `rise_hold` 30 and no `rise_press`. The pressure's hold
needs, before it is in a file again: exits sampled whatever the read says (a share of
strings never held), and what the held strings come to (opened, thrown) counted beside
what the exits come to.

With an object of the user's out it lost 7,960 HP a minute of that time for 7,500
without (38% of the time): the gap of the three sessions before (1.7 to 2.2 times) is
not in this one. Five matches.

**The pressure's hold, its read made again (22 November).** Two changes, in `rise.py` and
the game's code alike (`rise_press_open`, `rise_press_free`): what holding costs is
counted (the held strings in which it saw itself hit or thrown, over a prior of 0.15 as
4 held strings) and taken from what leaving the guard costs (caught less won, an exit);
and a share of the strings (0.34) is never held, whatever the read says, so that the
exits go on being read. At the defaults no string is held at a match's start (0.1 less
0.15 is the line's low end), six exits with four more caught than won hold two strings
in three, and five of six held strings opened let go again. Not in a file: it is to be
measured against the pressure exploiters first.

## The league's pressure (22 November)

### The two guards against the league

The benchmark queue that was running (`bench/r22c`, `r22ch`, `r22cp` beside `r22np`: round
22's policy with the okizeme planner and no guard of the two). The frozen copy of the code
it ran on plays the two pairings repeated from the earlier copy to the step (423,995 and
583,145 steps, every figure the same), so the tags compare.

Against the opponents with their characters' combos (eleven, 64 matches each):

| | no guard held | `rise_hold` 30 (`round22d`) | `rise_press` 36, the first read | both (`round22c`) |
|---|---|---|---|---|
| wins | 76.4 ±1.7 | 78.8 ±1.4 | 80.3 ±1.6 | 79.5 ±1.6 |
| own HP lost a round | 62.8 ±0.9 | 61.0 ±0.9 | 62.0 ±0.8 | 60.4 ±0.9 |

`round22c` over the whole suite: the league 99.1 ±0.3 to 97.4 ±0.5 (2.7 errors down; its
net there 6,353 to 5,856 HP a minute, its raw specials 589 to 438), the level-4 CPU 35.9
±6.4 to 45.3 ±7.6, sparring 93.8 to 95.0, the recoil drill 96.9 to 96.2. So the guards
cost nothing that the suite sees against opponents that hit back, and the two together a
point and a half against the plain league, where no opponent presses. Which of the two
that is, the league drill of `round22d`'s settings says: 98.4 ±0.6 (its net 6,297, its
raw specials 508 ±41). The hold on its rising costs half a point at the most, inside the
error; the rest was the pressure hold's first read.

### The pressure exploiters, judged

Round 22's policy without planners (`round22b`, their target) against the first four
`exploiter19`s as files with their characters' combos, beside the same characters'
`exploiter18`s (`bench/r22no-x19`, `r22no`; 64 matches each):

| | wins, `exploiter18` | `exploiter19` | own HP lost | its guards a minute |
|---|---|---|---|---|
| Nanase | 95.3 | 98.4 | 0.58 to 0.48 | 2.9 to 2.0 |
| Sayuri | 78.1 ±5.5 | 50.0 ±7.6 | 0.61 to 0.77 | 2.6 to 4.2 |
| Ikumi | 64.1 ±4.5 | 37.5 ±6.5 | 0.67 to 0.83 | 1.0 to 2.5 |
| Kano | 89.1 | 84.4 | 0.48 to 0.67 | 4.7 to 6.0 |

They are stronger opponents (three of four take more of the agent's HP, two of them half
the matches or more), and that is a retargeting, 6M steps against this policy as the game
plays it: the reward for pressure did little. In their training logs the guards they
touched a minute stayed where they began at 0.05 (10, 12 to 15, 8; Kano 15.6 to 19.3),
and at 0.2 Mishio's went 12.0 to 18.2 and Makoto's 18.2 to 20.4. Those two judged the
same way: Mishio 73.4 ±5.3 to 46.9 ±4.5 (own HP lost 0.62 to 0.81, its guards a minute
2.2 to 6.4), Makoto 93.8 to 68.8 ±6.2 (0.41 to 0.66, 3.2 to 5.7). The agent guards 2 to
6 times a minute against all six; against the user 13 to 31.

The last five, trained at 0.2 (their guards touched a minute from first chunk to last:
Doppel Nanase 13.9 to 25.4, Nayuki asleep 13.6 to 24.9, Mayu 10.3 to 19.4, Mizuka b 12.9
to 15.6, Kaori 6.6 to 6.5), judged the same way: Mayu 79.7 to 51.6 ±3.6, Kaori 79.7 to
48.4 ±3.6, Doppel Nanase 81.2 to 57.8 ±6.7, Nayuki asleep 65.6 to 43.8 ±8.1, Mizuka b
75.0 to 51.6 ±5.8; the agent's guards a minute 1.5 to 5.5 against them. All eleven are
stronger opponents by 5 to 31 points of the agent's wins (Nanase's alone is not), and
none makes it guard as a person does. The five are for the next round's league. The three not started yet train
at 0.2. All of them go into the next round's league in the place of their characters'
oldest exploiter of the model itself (the league has a match slot for each of its 90
opponents and little more).

### What the user's strings are made of

Every contact on the agent's guard in the five sessions' records (`gtrace.py` in the
scratch folder), a minute; a string is the contacts with no more than 45 steps between:

| | 18k4 | round 20 | round 21 | 22b | 22c |
|---|---|---|---|---|---|
| contacts a minute | 25.8 | 24.2 | 21.3 | 29.4 | 40.2 |
| strings a minute | 6.6 | 5.9 | 6.4 | 7.0 | 10.3 |
| ... begun on its rising | 4.2 | 3.4 | 3.3 | 3.9 | 4.9 |
| ... as it lands | 1.6 | 1.8 | 2.1 | 2.2 | 1.3 |
| ... after a move of its own, or a hit | 0.7 | 0.5 | 0.9 | 0.6 | 0.7 |
| ... on the ground, free | 0.1 | 0.2 | 0.2 | 0.3 | 3.5 |
| contacts with an object of the user's out | 34% | 29% | 55% | 51% | 43% |

A person's pressure begins where the agent has to guard: nine strings in ten on its
rising or its landing, almost none on an agent standing free (22c's 3.5 are its own
pressure hold keeping it there). Then it goes on: 3.3 to 4.2 contacts a string, and half
of them with an object out. By the same count the league's opponents with combos make
3 to 12 contacts a minute in 1.1 to 4.5 strings (Ikumi's and Kano's): about as long a
string, a third as many. So what the league lacks is not the first guard's follow-up
(the pressure planner's) but being on the agent again and again.

### A scripted pressure: `press`

`advantages.py`'s `press`, a habit like `jumpin` or `throw`, for any opponent in
training and in evaluations: the share of its chances in which it presses. A chance:
itself free on the ground and the agent on the ground within 260 pixels, not down, not
in a hit reaction, not in a move; or a normal of its own play that the agent guards (its
okizeme's, a landing caught). It goes in (a run from further than 110 pixels), presses
its 2A from inside its reach, and as each normal is guarded presses the next the game
cancels it into that still reaches (2A 5A 5B 2B 2C at the most, the 2C in four strings
in ten); the string over, a crouching guard for 0 to 14 steps and the next chance at
once. It lets go when the agent is in a move near it or in the air, when it is hit, and
when its normal hits (the combo is its own play's and its file's routes') or is
recoil-guarded.

Two things it needed from the game, both tried there (`motions.py --add pokes`, in
`motions.json`): from how far each normal touches a crouching guard, and which normals
the game cancels into which on a guard. `framedata.json`'s reach is the move's own box
and is 2 to 32 pixels more than a guard is touched from: with it the first build's 2A
was pressed from where it does not reach (Sayuri's from 62 pixels, it touches from 55)
and never met a guard. The cancels are the same for nearly all: 2A into 5A, 5B, 2B, 2C;
5A into 5B, 2A, 2B, 2C; 5B into 2B (some) and 2C; 2B into 2C. Against an Ayu that only
holds a crouching guard its strings are 1.2 (Nanase) to 3.5 (Mayu) guards long, 90 to
140 contacts a minute.

Against `round22d`'s file (16 matches each, `press=1` on an `exploiter18`):

| | contacts a minute | strings | the agent's wins |
|---|---|---|---|
| Kano's model, no habit (64 matches) | 11.8 | 4.2 | 98% |
| Kano's model, pressing | 22.1 | 6.5 | 94% |
| Sayuri's model, pressing (8.0 and 2.9 without) | 14.1 | 4.9 | 100% |
| Kano's file with combos, pressing (12.1 and 4.5 without) | 18.5 | 6.0 | 63% (94%) |
| Ikumi's file with combos, pressing (2.9 and 1.1 without) | 11.4 | 2.9 | 44% (63%) |

It reaches the lower end of what the user does (21 contacts and 6 strings a minute), and
with combos behind the pokes the agent loses to it. What keeps it from more is the
agent: 20 to 23 jumps a minute and a move out most of the time, so two ways in of three
are let go, and after a guard the agent is hit next 17 to 22% of the time and guards
again 15 to 21% (the rest it gets away or hits first), which is the thing the user
punishes.

The bench has the drill: `press` (five opponents' files with combos, `press=1,throw=0.5`:
the throw so that a guard held for ever is not free), with its wins, own HP lost and the
agent's net under their pressure.

`round22d`'s first three pairings of it (64 matches each), beside the same files without
the habits (`bench/r22d`, `r22ch`): Kano 93.8 to 65.6 ±6.8, Ikumi 62.5 to 42.2 ±5.0,
Nayuki (asleep) 53.1 to 34.4 ±6.4; its HP lost a round 0.45 to 0.70, 0.71 to 0.82, 0.74
to 0.82. Twenty to twenty-eight points to a 2A, a chain and a throw: the weakness the
user named, now in an opponent it can train against and be measured by.

All five, and the reworked pressure hold beside it (`r22e`: `round22d`'s settings with
`rise_press` 36 on the read made again, `press_open` 0.15 and `press_free` 0.34):

| | no habits | `round22d` | `r22e` |
|---|---|---|---|
| Kano | 93.8 | 65.6 ±6.8 | 65.6 ±6.0 |
| Ikumi | 62.5 | 42.2 ±5.0 | 35.9 ±3.9 |
| Nayuki (asleep) | 53.1 | 34.4 ±6.4 | 50.0 ±5.6 |
| Sayuri | 78.1 | 37.5 ±5.6 | 50.0 ±6.9 |
| Mizuka (b) | 68.8 | 78.1 ±5.0 | 59.4 ±5.5 |
| all five: wins | 71.3 | 51.6 ±2.6 | 52.2 ±2.5 |
| own HP lost a round | 0.65 | 0.763 ±0.011 | 0.747 ±0.012 |
| HP a minute net under their pressure | | 341 ±99 | 379 ±100 |

Twenty points over the five. The pressure hold does what it is for (the opponents' pokes
guarded go from 523 to 870 against Kano, 899 to 1,389 against Sayuri, 546 to 1,010
against Nayuki; a string 1.1 to 1.3 guards long becomes 1.1 to 1.4) and it wins nothing:
0.6 points, one standard error of HP. Holding the guard longer is not the answer to an
opponent that throws a held guard and pokes again; what to do after the guard is, and
that is the policy's to learn. `round22d` stays the file, the pressure hold off.

What the drill is not: the user's pressure. The agent guards 3 to 8 times a minute in
it, a string is one guard and a little, and half of the opponent's ways in are let go
because the agent is in the air or in a move (731 of 1,390 for Kano, 2,017 of 2,929 for
Ikumi). It measures what leaving the guard costs against a poke with a combo behind it,
not what staying in a long string costs.

### Objects: `object`

The other half of the user's sentence. With one of the user's objects out the agent
lost 1.7 to 2.2 times as much HP a minute in three sessions of four, and 29 to 55% of
the contacts on its guard came with one out; the league's Sayuri has an object out 1 to
2% of her free time, Makoto 11%.

`advantages.py`'s `object`: the share of its chances to put an object out in which it
does. Its moves are those that leave it free on the ground with an object of theirs out
(`motions.py --add objects`, tried in the game from a round's start: the steps of cover,
the move's length; an object that was out before the move, as Kano's, is not the
move's), the one with the most cover its gauges allow, no super. 19 of the 24 characters
have one (of the league's eleven not Mishio, Mayu, Kaori, Doppel Nanase, Nayuki asleep).
A chance: the agent knocked down with the move's length left to lie (once a knockdown,
on the first step it is free), or the agent 160 pixels away or more, on the ground and
in no move, every 45 steps; never with an object of its own out. With `press` it goes
in behind it.

Against `round22d`'s file (16 matches each, `object=1,press=1` on the files with
combos): Sayuri puts one out 5.2 times a minute (2.3 start) and has one out 10% of her
free time (1%), Makoto 2.8 times and 25% (11%). The agent took 38% from Sayuri so (25%
with the press alone, 78% without either) and 88% from Makoto (97%): the pressure is
what costs it, and sixteen matches do not show the objects adding to that. The bench's
drill `objects`: the six of the league's characters with such a move, `object=1,press=1,
throw=0.5` on their files with combos.

`round22d`'s baseline on it (64 matches each, `bench/r22d`), beside the same files with
no habit and, where the press drill has the character, with the press alone:

| | no habits | pressing | objects and pressing | its HP lost a round |
|---|---|---|---|---|
| Sayuri | 78.1 | 37.5 | 60.9 ±6.8 | 0.68 to 0.73 |
| Kano | 93.8 | 65.6 | 73.4 ±5.3 | 0.45 to 0.69 |
| Ikumi | 62.5 | 42.2 | 46.9 ±5.0 | 0.71 to 0.79 |
| Mizuka (b) | 68.8 | 78.1 | 56.2 ±4.8 | 0.66 to 0.78 |
| Nanase | 98.4 | | 98.4 | 0.58 to 0.52 |
| Makoto | 96.9 | | 90.6 ±3.9 | 0.44 to 0.51 |
| all six | 83.1 | | 71.1 | |

Twelve points over the six, and less than the press alone costs for Sayuri and Kano:
the steps an opponent spends putting an object out (Sayuri 5 tries a minute, half of
them start) are steps it does not press in, and the agent wins more against it. As a
scripted habit the object is cover the opponent pays for; it does not yet do what the
user's objects do, which is to hold the agent in its guard while the user moves.

### Its okizeme since 17c: a check that cannot tell

The files since 18k4 carry `okiplan:2` with `oki_sight` 14 (the planner takes the riser
to guard by sight), 17c's `okiplan:1`; nothing else of the planner's settings differs.
`cfoki.py` in the scratch folder plays each fight again from its record and, at each
knockdown of the user's, lets a file's agent with its planner play the agent's side
against the inputs the user pressed. `round22d` as it is, with the sight off, and with
sight and thinking time at 11, over four sessions (333 knockdowns):

| | as recorded | sight 14 | sight off | sight 11 |
|---|---|---|---|---|
| it hits first | 8 to 26% | 40 to 48% | 45 to 52% | 33 to 45% |
| HP it deals a knockdown | 44 to 136 | 174 to 203 | 207 to 262 | 149 to 213 |
| from the air | 30 to 63% | 58 to 73% | 63 to 78% | 61 to 70% |

Every file does far better than what was played, because the user rose against another
okizeme and could not answer this one: the check flatters whatever it is given, and most
the file that takes the riser not to look. What it does say: the planner still comes
from the air six times in ten and changes sides one time in ten in every file, so the
okizeme's kinds have not gone; and the sight is not shown to be the cause. The fall the
user saw (38% of its okizeme hitting first with 17c, 25 to 32% since) may as well be the
user reading it better, session after session. The test that can tell is an old file
and a new one in the same sitting.

### Round 24, started

Two arms from round 22's pick, 20M steps each in ten chunks, round 23's league with the
six `exploiter19`s that had ended (Nanase, Sayuri, Ikumi, Kano, Mishio, Makoto) in the
place of those characters' `exploiter14`/`15`:

- `agent-league24-press-s1` (22 November, 04:00): the sparring profile pressing too
  (`press=0.6` beside its other habits, in four of ten of the opponents' matches), on
  the frozen code `snap24`.
- `agent-league24-pressobj-s1` (04:25): the same with `object=0.6`, on `snap25`.

Judged as the rounds before, with the two new drills beside the suite.

A note on the machine: at 04:01 the memory watch stopped my benchmark queues at 9 GB
available (seven evaluations, two exploiter trainers and the first arm starting at
once); they were queued again three, then two at a time. And the object probe's first
run died while writing and left `motions.json` cut short for a few minutes (nothing
read it: every run uses a frozen copy); it is restored, and `motions.py` now writes the
file whole or not at all.

### On the agent's rising: `meaty`

`press` begins its strings on an agent standing free; a person's begin on its rising.
`advantages.py`'s `meaty`: the share of the agent's knockdowns in which the opponent
goes into its 2A's reach, waits, and presses so that the 2A touches two steps after the
agent's first free one (the knockdown's lengths and each normal's steps from press to
contact are `motions.json`'s); guarded, the string goes on as `press`'s. Against an Ayu
thrown and then holding a guard it lands on the step it is aimed at for the ten
characters it could be tried with so (eight of the league's eleven, Mio and Akiko; 7 to
15 knockdowns each, all but two guarded, 2 to 4 guards a string after it; Sayuri's and
Mayu's throws leave the Ayu further than they walk in a knockdown, Mishio's does not
knock down).

Two things the game showed:

- Sayuri's and Mayu's runs leave the ground, and no normal on the ground comes out of
  them: a way in that began with a run was let go every time, in `press` too (some of
  the 1,517 of Sayuri's 2,202 ways in let go in the drill above). A character whose run
  is seen to leave the ground walks in from then on.
- After a whole combo the agent lies as far as the screen lets it, 280 pixels, in 54 of
  Kano's 102 knockdowns, and Kano covers 160 pixels in a knockdown (her run is a step
  of twenty frames, then a walk). Run at regardless, 63 of the 102 ended short of her
  reach. So a knockdown is a chance only where the reach can be had in time, at 2.5
  pixels a step until the character has been seen to cover more; the others stay its
  own play's.

Against `round22d` (16 matches, Kano's file with combos, `press=1,throw=0.5,meaty=1`):
39 of 111 knockdowns in reach, 35 of them poked: 23 guarded, 6 hit, 6 beaten by a move
on rising, none missed. The agent's wins 62.5% (62.5% with the press alone, sixteen
matches each): about one more string a minute, and no more than that from Kano, whose
combos throw the agent out of her reach two times in three. No drill for it yet; it is
for the next round's profile, beside `jumpin` (the far knockdowns are a jump's).

### Its okizeme, counted again

What the agent did on each of the user's knockdowns, as recorded (`cfoki.py` with no
file), session by session:

| | 17c | 18k4 | round 20 | round 21 | 22b | 22c |
|---|---|---|---|---|---|---|
| knockdowns | 140 | 193 | 75 | 53 | 60 | 27 |
| it hits first | 36% | 26% | 19% | 25% | 8% | 22% |
| it is hit first | 12% | 20% | 20% | 15% | 25% | 19% |
| from the air | 66% | 59% | 61% | 55% | 30% | 63% |
| the side changed | 17% | 10% | 7% | 17% | 0% | 7% |
| HP dealt, lost a knockdown | 164, 66 | 114, 85 | 90, 103 | 102, 81 | 44, 151 | 136, 138 |

"Losing almost everything about okizeme (air, reverse)" is `round22b` to the letter: the
file without the planner came from the air half as often and never changed sides. With
the planner back (22c) the air is where it was; what is still under 17c is how often it
hits first (36% to 19-26%), how often it is hit first (12% to 15-20%) and the side
changes (17% to 7-10%, round 21's 17% aside).

The stored benchmarks have the same count for every file since 18k4 (`okitab.py` in the
scratch folder, the agent's okizeme pooled over a drill's pairings). Against the
sparring profile, the nearest thing to a person's rising:

| | 18k4 | round 20 | round 21 | 22c | 22, no planner |
|---|---|---|---|---|---|
| it hits first | 44% | 46% | 49% | 53% | 47% |
| it is hit first | 17% | 16% | 15% | 12% | 7% |
| from the air | 40% | 42% | 44% | 46% | 1% |
| the side changed | 12.9% | 12.9% | 15.4% | 13.5% | 2.0% |
| low, high | 37%, 29% | 39%, 34% | 36%, 36% | 38%, 42% | 91%, 4% |

By this the planned okizeme has not got worse since 18k4, and the policy alone has one
okizeme, a low on the ground (82% of its knockdowns). Against the plain league it hits
first less than it did (35% to 29%) and has fewer okizeme a minute (3.5 to 2.7).

17c itself on today's sparring drill (`bench/round17c`; 18k4 run again beside it,
`bench/k4today`, gives its stored figures to the digit):

| | 17c | 18k4 | 22c |
|---|---|---|---|
| it hits first | 47% | 44% | 53% |
| it is hit first | 17% | 17% | 12% |
| from the air | 57% | 40% | 46% |
| the side changed | 11.7% | 12.9% | 13.5% |
| low, high | 21%, 53% | 37%, 29% | 38%, 42% |
| its okizeme's net, HP a minute | 1,655 | 1,385 | 1,974 |
| matches won there | 70.3% | 67.2% | 95.0% |

17c's okizeme was another kind, not a better one: more from the air (57% of its
knockdowns, a jump with a high 28% of them) and high where today's is half low. Against
the same scripted riser today's hits first more often, is hit first less and is worth
more. So the fall the user felt has two parts that can be named: `round22b` had no
planner at all, and since 18k4 the planner comes from the air less (57% to 40-46%),
which is what "air" in the user's sentence saw. That it hits the user less often than
17c did (36% to 22%) the scripted riser does not show; the user's rising against it has
got better (it is hit first 12% of the time in 17c's session and 15 to 25% since), and
only the two files in one sitting can split that from the files.

### What a jump costs: `antiair`

The user's first sentence of 21 November: the agent "relys heavily on air-to-air". The
HP the agent loses a minute while it is in the air, by what hit it (`ledger`'s `air_by`):

| | from the ground | from the air | its jumps a minute |
|---|---|---|---|
| the league, plain | 486 | 377 | 24.0 |
| the league with combos | 1,128 | 555 | 22.4 |
| the user: 17c, 18k4, round 20 | 1,476, 810, 1,202 | 911, 437, 750 | 18.6, 18.1, 18.4 |
| the user: round 21, 22b, 22c | 2,070, 1,633, 1,772 | 1,202, 604, 765 | 18.8, 18.5, 14.8 |

A jump costs the agent 20 HP against the plain league, 50 against the opponents with
combos and 45 to 120 against the user (88 to 120 in the last three sessions). Where it came by air it nets +977 HP a minute
against the league with combos, and against the user between -1,076 and +733. Nothing
it trained against made a jump cost what a person makes it cost, so it jumps.

`advantages.py`'s `antiair`: the share of the agent's jumps at it that the opponent
anti-airs. Which move from where is tried in the game (`motions.py --add antiair`, 20
seconds a character): each normal on the ground and 623A/623B, pressed at every other
step of an Ayu's jump from ten distances, the Ayu jumping empty, holding an air guard,
pressing each air button early, in the middle and late, jumping again, dashing in the
air, or jumping straight up; 3,300 tries a move, counted by where the jumper was as the
move was pressed (cells of 16 pixels across and 24 up, rising or falling). A place has
a sure move if one hit first in 70% of four tries or more from there and was hit first
in 10% at the most. Every character has 59 to 151 such places: Kano her 2C and 5C,
Nanase her 2B, most of the others their 623.

Two limits, both from the first trials against `round22d` (Kano's file with combos,
sixteen matches each):

- The agent has been in the air for eleven steps before it is answered: what a person
  has seen of a jump, and the agent's own delay.
- Only on its way down. Pressed at a rising agent the sure moves hit 19% of the time
  (19 of 101; it jumps again or dashes on, out of the place the move was sure from) and
  64% at a falling one (44 of 69).

With both: 222 anti-airs in sixteen matches (5.8 a minute of the agent's 21 jumps), 150
hit, 24 hit back, 48 nothing. The agent's HP lost in the air to the ground 707 to 3,094
a minute, its net where it came by air +2,720 to -32, its HP lost a round 0.45 to
0.74, its wins 94% to 75%. At `antiair=1` that is more than the user makes a jump cost;
at 0.6 about as much.

The bench has the drill `antiair` (the five opponents' files with combos, `antiair=1`:
wins, own HP lost, the net where it came by air). Round 24 has a third arm for it,
`agent-league24-antiair-s1` (the sparring profile with `antiair=0.6`, no press, on the
frozen code `snap26`; started at 09:39, when the last exploiters' judgement had ended), so that
the three habits can be told apart: press, press and objects, anti-airs.

#### The drill's baseline, and the anti-airs that lost

`round22d` on the drill (`bench/r22d`, the habit as round 24's arm trains against it,
`snapbench23`): wins 61.9 ±2.7% (71.3% against the same five files without the habit),
own HP lost 0.74 a round (0.65). But opponent by opponent the habit was two things:

| the opponent | wins without, with | its anti-airs: hit, hit back, nothing |
|---|---|---|
| Kano | 93.8, 70.3 | 511, 88, 190 |
| Nayuki (awake) | 53.1, 31.2 | 239, 99, 170 |
| Mizuka | 68.8, 53.1 | 269, 149, 239 |
| Ikumi | 62.5, 76.6 | 280, 321, 150 |
| Sayuri | 78.1, 78.1 | 289, 321, 173 |

Ikumi's and Sayuri's "sure" moves were hit first more often than they hit, and the
agent won more against an Ikumi that anti-airs than against one that does not. A lab
copy that logs each anti-air (sixteen matches each) showed why: seven in ten of the
losses are to the agent's air B (0xd0), and they come from two places the probe's Ayu
never was. One is the top of a jump, a second jump above all (the agent in action
0xf, 400 pixels up: Ikumi's 623A there 0 hits, 36 hit back): the agent has not chosen
its button's step yet. The other is a late B on the way down out of a second jump: the
probe's Ayu pressed its buttons at fixed steps of a first jump and, after a second
jump, nothing later than eight steps past its top.

Three changes, in the order they were tried:

1. The table is keyed on the action the jumper is in as well (its first jump 0x9, its
   second 0xf, an air dash, each air move out), and the probe's Ayu presses A, B or C
   at nine steps of a first jump and a B at every sixth step after a second jump, down
   to its landing (60 scripts for 16; 70 seconds a character). Each character has 250
   to 460 sure places now, a handful of them against a second jump (Ikumi 12, then 1).
2. That alone did not do it (Ikumi 72 hits to 92 hit back): the agent times its B to
   the opponent, which no script at fixed steps does. So the habit keeps each move's
   record in the game against each kind of jump (the jumper's action, and whether it
   falls under 2, under 5 or more pixels a step), and after six tries a move that was
   hit first more than half as often as it hit is left out there: the place's next
   sure move instead, or none. Forty such chances later half the record is forgotten
   and the move is tried again (an agent in training changes).
3. A place keeps all its sure moves, the surest first, for that.

With all three (32 matches each): Sayuri's anti-airs 217 hits to 87 hit back (before:
82 to 90), the agent's wins against her 44% (56 to 88% in the three labs before), its
net where it came by air -3,710 HP a minute; Ikumi's 112 to 95 (69 to 80), wins 53%
(62 to 100%). Ikumi has one move that holds (her 5A at a first jump's fall: 71 to 8)
and the record takes more than 32 matches to find the rest out. The arm in training
(`snap26`) has the first table; the bench copy with the new habit is `snapbench24`
(reference tag `r22d-n`).

### Its own pressure, the corners above all (22 November)

The user, while round 24 was being judged: **"I think in order to learn how to handle
pressure, it needs to understand how to pressure properly, especially at corners."**
The agent's own pressure, from the games already stored (evaluate.py's `pressure` and
`corner`, the agent's side):

| | strings a minute | the next thing after a guarded move is its hit | a move pressed against it gets away | corner stays ended by a jump out |
|---|---|---|---|---|
| people's Ayu players (1,908 matches) | 5.0 | 23% | 37% | 41% |
| the agent against the league | 8.2 | 11% | 23% | 35% |
| against the league with combos | 7.1 | 10% | 23% | 33% |
| against the sparring profile (it leaves corners) | 4.5 | 18% | 18% | 76% |
| against the user, five sessions | 3.2, 3.3, 1.8, 2.4, 1.4 | 18, 16, 14, 10, 9% | 50, 51, 54, 47, 18% | 53, 51, 45, 35, 46% |

Against the user it hardly presses (1.4 strings a minute in the last session, 8.2 in
the league), half of the user's buttons against its pressure get away, and its
strings open a guard half as often as people's. The league never asked for more: its
opponents hold a guard after seven in ten of the agent's guarded moves and are still
opened only one time in ten, and against the one profile that leaves a corner three
in four corner stays end with the jump out. And the agent's frozen copies press as
the agent does, so its defence has met no pressure either: this morning's finding on
the `press` drill (it loses its own turn there, not the time it is held in a guard)
is the same thing seen from the other side.

What was built for it:

- **`mash`** (advantages.py): after a guard, on its first free step, the opponent's
  fastest normal that reaches, blind. Tried first, and it is not the teacher: against
  `round22d` Kano's button hit 6 times and was hit back 20 (sixteen matches), the
  agent's pressure net +1,286 HP a minute. The agent's strings hold against a button
  pressed at once.
- **`gap`**: the same button with a read. Within 45 steps of a guard, free and in
  reach, it presses where the agent cannot hit first: the agent between two moves (a
  walk or run back in: a reset), in a move's start with more steps left than the
  button takes (framedata.json's startup, counted from the step the action began), or
  past a move's active steps. Kano's, sixteen matches: 28 chances (the agent makes her
  guard seldom), 8 hits, 3 hit back, 17 nothing; the agent's pressure net -143.
- Both labs: **the corner does not hold.** 78 to 81% of the agent's corner stays end
  with Kano's jump out (`escape=1`), after 5 to 6 seconds.
- The drill **`gaps`** (bench.py): the five opponents' files with combos and
  `gap=0.6,mash=0.15,escape=1,rg=0.3,reversal=0.8,tech=1,techsafe=1,techhit=1`. Its
  measures: wins, own HP lost, the net of its own pressure, its strings a minute, the
  share of guarded moves followed by its hit, the share of moves pressed against it
  that get away, the corner stays the opponent left on its own, HP dealt a stay.
- The reward **`corner`** (focus.py, `finetune.py --focus corner`): press's two events
  (the opponent's guard touched: a fifth of the coefficient; a hit within 60 steps of
  such a guard: the coefficient), each twice as much while the opponent is held in a
  corner, and twice the coefficient for a hit on an opponent in the air there: its
  jump out caught.

**Can the corner be held at all?** A scratch probe (`cornerprobe.py`): the opponent
backed into its corner, Ayu at 50 to 200 pixels, the opponent jumps out as `escape`
does, and Ayu answers 11, 15 or 19 steps after it left the ground with each normal,
her 623A/B/C, or a jump (back, up, forward) with an air button 6 to 18 steps into it;
seven opponents. At 11 steps: from 140 pixels and further her 623 (any strength)
catches every one of the seven (Nayuki's and Mizuka's from 170); from 80 to 170 a
jump straight up with C catches Kano's and Ikumi's; from 50 to 110 nothing of hers
catches a jump on sight. So a corner is held from a step back, with the 623 or the
jump C on the jump, or point-blank by strings that leave the jump no step to start
in: both are there to be learned, and neither is what the agent does (it stands in
close and lets the string end).

**Round 25, first arm** (`agent-league25-corner-s1`, scratch `round25-arm.sh`, started
13:37 on the frozen code `snap27`): round 24's league and start (round 22's seed 2
average, the six pressure exploiters), the sparring profile with `gap=0.5,mash=0.15`
(it already leaves corners), and the learner's reward `corner` at 0.01 (100 HP for a
guard opened, 200 in a corner or for a jump out caught). 20 million steps in ten
chunks. The plan after it: the `gaps` drill beside the suite; then frozen copies of
what holds a corner go into the league as the defence's teachers. (Its opening
evaluation took 89 minutes with the machine full; the first chunk began at 15:07.)

#### What a corner stay is made of

The probe says what could hold a corner; the replays say what people do there.
`evaluate.py`'s `corner` now carries a `hold` (`corner_hold()`): of a stay's steps, the
share the opponent spends in a guard and in a hit; where the player stands while the
opponent is free on the ground; the player's moves a stay and the share of them made
in the air; and the opponent's own jumps there, by what became of each within 50
steps (out of the corner, still in it, the player hit first, caught in the air).
`people.json` is recomputed with it (nothing else in it moved), and the user's five
sessions are read both ways (scratch `holdrec.py`):

| the corner stays of | share of the match | seconds | moves a stay | of them in the air | opponent guarding | in a hit | its jumps: out / caught |
|---|---|---|---|---|---|---|---|
| people's Ayu players (13,027 stays) | 22% | 4.9 | 6.1 | 45% | 12% | 50% | 52% / 12% |
| the strongest of them | 28% | 5.6 | 7.5 | 46% | 13% | 52% | 48% / 16% |
| the user, on the agent (five sessions) | 28, 24, 30, 31, 48% | 4.3, 4.1, 4.4, 4.8, 7.3 | 4.9, 4.7, 5.3, 6.0, 9.9 | 31, 32, 40, 29, 30% | 17, 16, 11, 17, 25% | 48, 51, 58, 53, 46% | 46/13, 49/20, 52/15, 57/15, 60/21 |
| the agent, on the user | 15, 21, 15, 16, 9% | 3.6, 4.9, 3.3, 4.4, 3.0 | 4.5, 6.9, 4.2, 6.0, 4.0 | 56, 60, 66, 56, 62% | 5, 8, 3, 7, 3% | 59, 67, 59, 68, 67% | 57/19, 53/30, 34/14, 65/8, 62/25 |

Three things in it:

- **Nobody locks a corner.** Half of the opponent's jumps there take it out against
  people, against the strongest of them, against the user; one in eight to one in six
  is caught, and by an air B or C or a 2B already on its way (a quarter of the jumps
  made while the player was in a move are caught, one in eight of those made while it
  stood free), not by a 623 on sight. The probe's answer exists and people do not
  rely on it: a corner is where the damage is done (400 HP a stay, half of it spent in
  a hit), and it is kept by being back in it soon.
- **The agent's corner is a combo and nothing after.** Against the user the opponent
  spends 3 to 8% of the agent's stays in a guard (people's 12%, the user's own 11 to
  25% on the agent): the combo that carried the opponent there ends and the stay ends
  with it, after 3 to 5 seconds. Its jumps out are caught as often as anybody's.
- **It is there from the air**: 56 to 66% of its moves in a stay are made in the air
  (people's 45%, the user's 30%), the same reliance the user named first.

And the share of the match: the agent has the user in a corner 9 to 21% of the time,
the user has the agent there 24 to 48% (48% in the last session, at 9.9 moves a stay).
So the measure of "pressure properly, in the corners" is not the jump caught; it is
the time the opponent is kept there **guarding**, the stays a match, and what they
are made from. The `gaps` drill gained those rows: the share of the match with the
opponent cornered, the share of a stay it guards, the share of the agent's moves
there made in the air, the stay spent in a hit, and the jumps out and caught.

### Round 24, judged

**The press arm** (`agent-league24-press-s1`, its ten chunks' average with `round22d`'s
settings, tag `r24p`; 11-step delay on both sides, the three new drills beside the suite):

| measure | `round22d` (the suite's rows: the reference tag `r22np`) | press arm | |
|---|---|---|---|
| press: wins | 51.6 ±2.6 | 57.8 ±2.7 | +1.7σ |
| press: own HP lost | 76.3 ±1.1 | 74.4 ±1.1 | -1.3σ |
| press: net under their pressure | 341 ±99 | 546 ±98 | +1.5σ |
| objects: wins | 71.1 ±2.0 | 70.3 ±2.1 | |
| antiair: wins | 61.9 ±2.7 | 63.4 ±2.4 | |
| antiair: own HP lost | 74.1 ±1.1 | 70.6 ±1.2 | -2.2σ |
| antiair: net by air | 1536 ±159 | 1884 ±157 | +1.6σ |
| league: wins / own HP lost | 99.1 ±0.3 / 37.0 | 98.4 ±0.4 / 36.7 | |
| combos: wins / own HP lost | 76.4 ±1.7 / 62.8 | 78.1 ±1.6 / 61.4 | |
| sparring: wins / own HP lost | 93.8 ±1.4 / 47.4 | 94.4 ±1.2 / 46.0 | |
| recoil: wins / pressure net | 96.9 ±0.9 / 1049 ±100 | 97.2 ±0.8 / 877 ±113 | |
| level-4 CPU with combos: wins / own HP lost | 35.9 ±6.4 / 83.8 | 46.9 ±6.4 / 80.3 | |

Twenty million steps against opponents that press moved the press drill by six points,
inside two errors, and nothing else: Nayuki's and Sayuri's matches there went from 34
and 38% to 55 and 50%, Kano's fell from 66 to 59%, and the agent's own strings a minute
and guards opened did not move on any opponent (6.4 and 7% against Ikumi before and
after). It is the baseline the user's direction of the same afternoon is measured
against: defence trained against a scripted pressure buys little while the agent's own
pressure stays what it was.
