# Training v2: an agent that beats strong players, within human limits

How the Ayu agent is trained, what it is made of, how it is measured and where it stands.
This page is kept current: a section is rewritten when its facts change, and nothing is
appended to it. The measurements behind each statement, in the order they were made, are
in [training-v2-log.md](training-v2-log.md) (a closed record). How to run each script is in
[runs/human-ayu/README.md](../runs/human-ayu/README.md); the agent file and the modules as
the game plays them are in [agents.md](agents.md).

## Goal and rules

The goal, in the user's words: "We are not targetting to get an average player, but a very
strong agent that can beat the best players."

- **The bar** is the strongest Ayu players in the community's replays, the opponents who
  beat Ayu players most, and the tester, and past them. People's averages describe, and
  serve as the prior for an opponent not yet seen; they are never the bar.
- **Human limits are the hard line.** The agent sees the game 11 frames late (172 ms; the
  best players react in 120-170 ms), presses at people's rate (1.2-2.1 presses a second,
  no more than 2.2 while hit or guarding), and has no instant confirm: what it plans, it
  plans from its delayed view, on copies of the game.
- **Advantages are the opponents'.** Scripted habits, sight without delay and a combo
  started on the step after a hit (`route_confirm`) exist for training and benchmark
  opponents only.
- **No level-4 CPU as a training opponent** but Kanna: the CPU's guard height is perfect,
  which teaches that mix-ups do not work.
- **One tester is one data point.** A play-test finding is acted on where the league or the
  replays agree; the agent goes to the community after a few rounds.
- **It must adapt within a set of games**: one strategy is found and exploited by a person.
- **A release is one `.efzagent`** that the game plays and the tools can unpack and train
  on from. Nothing in a file executes.
- **A win rate near 100% is reported with the agent's own HP lost**, which tells a hard
  win from an easy one.

## Status

### The file

`agent-league25-stay-s1-round25.efzagent` (`round25`): round 25's policy (the arm trained
against defenders that stay in a corner as people do; the average of its ten chunks) with
the modules `policy:1, routes:1, okiplan:2, airthrow:1, rise:1, risk:1` and the settings
of the file before it, `round22d`. It has no pressure planner, no pressure hold and no
jump account (each was measured and left out; see "The agent").

Round 28 is a playable candidate for a human test against Sayuri. It learns when to jump back from a close walk-in using the same 11-frame observation delay. Round 25 is the public reference. [Round 28 results and test instructions](round28.md)

### Where it stands

Opponents see 11 frames late as it does; 64 matches an opponent; ± is one standard error.
The two right columns are the strongest Ayu player of the replays (487 matches, 72% won)
and all Ayu players, where the measure exists for people.

| measure | `round25` | `round22d` | the strongest | all |
|---|---|---|---|---|
| plain league (eleven opponents): wins / own HP lost | 99.6 ±0.2% / 34.9 ±0.6% | 99.1 ±0.3% / 37.0 ±0.7% * | | |
| the league with their characters' combos: wins / own HP lost | 81.8 ±1.4% / 59.1 ±0.9% | 78.8 ±1.4% / 61.0 ±0.9% | | |
| every scripted habit at once (`sparring`): wins / own HP lost | 93.1 ±1.6% / 45.3 ±1.5% | 93.8 ±1.4% / 47.4 ±1.2% * | | |
| level-4 CPU given the file's combos: wins / own HP lost | 37.5 ±6.5% / 82.3 ±2.2% | 35.9 ±6.4% / 83.8 ±1.8% * | | |
| opponents that press (`press`): wins / own HP lost | 57.8 ±2.7% / 73.3 ±1.2% | 51.6 ±2.6% / 76.3 ±1.1% | | |
| its net under their pressure, HP a minute | +178 ±84 | +341 ±99 | +86 | -513 |
| opponents that put objects out (`objects`): wins / own HP lost | 74.0 ±2.0% / 63.4 ±1.1% | 71.1 ±2.0% / 66.9 ±1.2% | | |
| opponents that anti-air and keep score (`antiair`): wins / own HP lost | 52.8 ±2.4% / 77.7 ±1.0% | 40.3 ±2.6% / 81.0 ±1.1% | | |
| its net where it came by air there, HP a minute | -248 ±137 | -409 ±153 | -77 | -361 |
| opponents that press back in its gaps (`gaps`): wins / own HP lost | 80.3 ±2.3% / 57.1 ±1.4% | 75.6 ±2.3% / 58.7 ±1.3% | | |
| the net of its own pressure there, HP a minute | -179 ±112 | -662 ±117 | +492 | +133 |
| its strings a minute there | 3.79 ±0.06 | 3.77 ±0.07 | 5.90 | 4.97 |
| a guarded move of its followed by its hit | 21.3 ±0.8% | 21.7 ±0.8% | 26.9% | 22.7% |
| the same opponents staying in a corner as people do (`stays`): wins / own HP lost | 69.1 ±2.7% / 66.5 ±1.5% | 59.7 ±2.8% / 71.7 ±1.1% | | |
| the net of its own pressure there, HP a minute | +31 ±123 | -362 ±130 | +492 | +133 |
| the match it has the opponent cornered there | 41.7 ±0.7% | 40.8 ±0.7% | 27.9% | 22.1% |
| a corner stay the opponent spends guarding there | 6.6 ±0.2% | 6.2 ±0.2% | 12.9% | 12.4% |
| corner stays the opponent leaves on its own there | 58.5 ±0.8% | 54.5 ±1.0% | 63.9% | 61.6% |
| its moves in a corner stay made in the air there | 60.9 ±0.4% | 58.7 ±0.4% | 45.5% | 45.1% |

\* `round22d` measured without its rising hold (`rise_hold`), which moved the combos row
by two points and nothing else.

Against the tester it won 7 of 12 games, the first session above half; the files before
it won between none and half ("Play-tests"). What the records and the drills agree on:

- **Strong:** combos (1,900 HP a combo against people's 890-970), the lead once it has
  one, the air against opponents that do not anti-air, okizeme against an opponent that
  guards, the guard on its own rising, the answer to a recoil guard.
- **Under pressure it no longer loses, in one session.** The earlier files left their
  guard (the league made them guard 4-7 times a minute, the tester 13-18) and lost 290
  to 1,460 HP a minute net under the tester's pressure. `round25` guards 24 times a
  minute against the tester and comes out of the tester's pressure ahead (+524 ±390 HP a
  minute); what it loses opened after a guard is half of before (400 for 720-780). No
  training opponent stays on it as the tester does, so this rests on twelve games.
- **Weak with objects out against some characters.** Over the session it loses 1.2 times
  the HP a minute with one of the tester's objects out (earlier files 1.7-2.2 times),
  but 1.8 times against Mishio, and against Kano seven tenths of what it lost came with
  an object out.
- **Its own pressure no longer loses HP, and still does not hold.** Against an opponent
  that stays in the corner and presses back in the gaps `round25` wins 69.1% (`round22d`
  59.7%) and the net of its pressure is about nothing (+31 ±123 HP a minute, from -362;
  people +133, the strongest +492). It got there by not being hit in its gaps, not by
  keeping the opponent in a guard: the opponent guards 6.6% of a corner stay (people
  12%), leaves more of them, and six in ten of its corner moves are in the air (people
  45%). Against the tester it makes 2.4 strings a minute of 1.6 guards (the tester 7
  a minute against it).
- **It wins and loses in the air.** Against the tester its jumps earned 1,270 HP a
  minute in the games it won and lost 1,300 in the games it lost (Mishio twice, Kano,
  Sayuri twice), the largest difference between the two. An opponent that anti-airs
  with a record of what worked took six matches in ten from `round22d` and takes under
  half from `round25`, whose jumps there still lose HP on net: the anti-airs take
  1,700 HP a minute more from its jumps and it jumps as before (see "Paused").
- **Its okizeme is worth nothing against the tester** (+65 ±220 HP a minute: 640 gained,
  570 lost), as with the files before it.

### Paused

Nothing is training. `round25` is being played in the community and the games are being
collected; they decide the next direction. Four arms since round 25 changed the opponents
or a reward within the same league and none beat it: more of the same is not expected to
pay ("Next").

A subsequent replay experiment compared round 25 with an older policy, short ground
entries, and human input sequences at the same pre-contact positions. On the three
held-out defenders, round 25 won 16 of 36 complete matches, the chooser won 13, and the
chooser learning within each set won 12. Testing an alternative at the first planned
jump tied round 25 at 15 of 36 on fresh seeds. The experiment also isolated the simulated
opponents' anti-air records per set. Earlier batched anti-air scores used pooled records.
The paired results, follow-up experiments and reproduction commands are in
[Round 25 neutral decisions](neutral-trials.md).

Against three simulated Sayuri policies, jumping back when she walked into close range
won 64 of 96 matches against 58 for round 25 on the same seeds. The cue preceded four
ordinary ground throws in the original tester session and none in eight separate replays.
The eight-frame intervention ran in the headless evaluator. Round 28 distills it into
a native policy and tests it on additional human replays and live defenders.
[Sayuri throw study](sayuri-throws.md) and [Round 28](round28.md)

**Round 27**, the last league training run: one trainer, from round 25's policy with its league, its
defenders that stay in a corner as people do and its corner reward. What is new is how
often the opponent anti-airs: in every match with advantages, in both profiles and on
every chance (`antiair=1`, `--vs-extra`), and the advantages are in 85% of the league's
matches. That is about 89 of the 104 league matches; round 26's first arm had the habit in
about 42, on six chances in ten, and did not move.

The reason is one comparison. The same five opponents, with the habit off and on, take
`round25` from 77.5% of the matches to 52.8% and from 58 to 78% of its HP lost. Where it
came by air it gains 2,600 HP a minute either way and loses 1,200 without the anti-airs
and 2,900 with them; its okizeme falls from +1,050 to +220 and its pressure from +660 to
-140, because both begin from a jump. On the ground it gains 630 HP a minute in both. The
agent has one way in, and it does not change when that way is answered.

On the `antiair` drill, the one it was built to move, nothing is outside noise: 46.6 ±2.4%
won (52.8), 78.7 ±1.0% of its HP lost (77.7), its net by air -248 to +2 ±137 HP a minute.
The rest of the bench is not judged (five of the eleven opponents with combos: 80.9 to
78.8% won).

### Picking it up again

**What is kept.** The checkout holds the code and this page; nearly everything a round
makes is ignored by git and lives beside it.

| what | where |
|---|---|
| the file in play | `agent-league25-stay-s1-round25.efzagent`; its policy is `runs/human-ayu/agent-league25-stay-s1/avg.zip` |
| every run (checkpoints, `config.json` with each option it trained with), the league's exploiters, the generated data | `runs/human-ayu/` |
| the bench results | `runs/human-ayu/bench/TAG/DRILL-CHARACTER.json`; `round25` is `r25s` (`press`, `objects`, `combos`, `league`, `sparring`, `recoil`, `cpu`) and `r25s-n` (`gaps`, `stays`, `antiair`); round 27 is `r27a`, `r27a-n`, with 10 of its 59 results |
| a copy of all of `runs/human-ayu` outside the checkout | `~/data/efz-agent-state-688f174f` (hard links; its README says how to put it back) |
| the rounds' and the judging's shell scripts, the readings of play-test records, the frozen copies of the code the bench ran, every exported file | `~/data/efz-scratch-688f174f` (`restore.sh` puts them back where they ran) |

**A round** is three steps, one trainer and one or two evaluations at a time on the shared
machine ("Cost").

1. Train `finetune.py` from the pick's `avg.zip`. The latest recipe in full is
   `runs/human-ayu/agent-league27-aa-s1/config.json`; a new round changes what its row in
   "Rounds" names and nothing else.
2. Export the run's `avg.zip` with the parts and settings of the file in play, and scan
   the file for names and paths:

   ```
   python python/examples/export_agent.py RUN/avg.zip --parts-from FILE_IN_PLAY \
     --keep routes chooser okiplan airthrow --rise --rise-option land=1 \
     --rise-option sight=11 --rise-option recoil=60 \
     --rise-option recoil_punish=0x1,0x4,0x5,0x25 --rise-option hold=30 \
     --risk --risk-option ahead=1 --version NAME --out NAME.efzagent
   ```
3. Judge it with `bench.py jobs` and `bench.py table` against `round25`'s tags
   ("Protocol"). Two results compare only if the same copy of the code measured both:
   with a newer build, measure `round25` again first.

**The community's games** are read as the tester's were: the game's session records
through `from_record.py`, then HP a minute by situation, the agent's and the opponent's
pressure strings, the time with an object out, and what each jump earned and lost. The
questions to put to them first:

- Do many players beat it the way the tester does (its jumps answered, objects, Sayuri's
  throws), or by something the tester does not do?
- Which characters and which players win, and by how much more than the tester?
- Within a set, does a player who has found something keep winning with it? That is the
  measure of adapting, and no drill has it.
- Where does the agent do what the strongest players do not, when it is ahead and when it
  is behind?

### Open

- The tester has said the okizeme of the files since round 17 feels weaker. The records
  cannot separate the files from the tester's own improved rising; two files (`round17c`
  or `round18k4`, and `round25`) played in one sitting can.
- Whether a guard that follows a cross-up by itself (the held "back" changing sides) is
  within human limits.
- Whether the planned jump (`jumpplan`) is ported to the game.

## The agent

A policy network plays every frame; modules take the stick where a plan made on copies of
the game does better than the policy. Everything sees the game 11 frames late.

**The policy** is a PPO fine-tune of people's clone (`bc-d14.zip`, behaviour cloning of the
community's Ayu replays), held near the clone by a KL pull of 0.01.

### In the file

| module | what it does | what it is worth |
|---|---|---|
| `routes:1` | Its combos. At each hit of its moves, up to 24 routes from people's combo library are played on copies and the best is taken; a chooser network picks when a plan is late, and a late plan is settled from the options already played to their end. | The `person` set went from 58% to 65% with routes, then from 81% to 90% when planned again at each hit (1,240 to 1,530 HP a combo). |
| `okiplan:2` | Its okizeme. At a knockdown it takes five options from people's okizeme library near where it stands, a wait and its own play, plays each on copies against five answers of the riser (crouching guard, standing guard, reversal, jump, button), weighs the answers by what this opponent has shown over the community's prior, and draws. The copies' riser guards by what it saw 14 steps ago (`oki_sight`). | 93.8% against 88.7% on `crowdt`; okizeme from 82% low to 20% low and 62% high; throws from 0.01 to 0.27 a minute. Against a person who guards it is the difference between a mix-up and a 2A at seven knockdowns in ten. |
| `airthrow:1` | A sure air throw inside the opponent's air recovery, where only a throw touches. | Recoveries caught 43% against 36%; a throw exists after one recovery in six and lands 94% of the time. |
| `rise:1` | The guard on its own rising: through the rising and after it by sight (standing under an attacker in the air until the predicted landing, then crouching; `rise_land`, `rise_sight` 11), held while the attacker is in a move or in the air within reach (`rise_hold` 30). Whether it guards at all is a read of how often this opponent has a move out as it rises. The same module answers a recoil guard of its move (`rise_recoil`: nothing held, an A in the chain's place, the guard by sight through the string) and punishes after its own recoil guard with 623B (`rise_recoil_punish`). | Scripted jump-ins that hit its rising from 38% to 19-20%; against the tester its rising went from -872 to -47 HP a minute. After a recoil guard it is the one hit 22% of the time, from 39%. |
| `risk:1` | An account of its raw specials. A press of the policy's is tried on a copy; if a raw special with an account would start, the press is stopped with a probability from the move's worth this match over a prior (its own HP a use against opponents with combos). Inputs the planners chose ahead are drawn for too (`risk_ahead`). | Raw specials from -989 to +278 HP a minute against the tester; raw 623C and the level-one super gone. |

### Measured and left out

| what | why it is out |
|---|---|
| `pressplan` (people's follow-ups to a guarded move, planned as the okizeme is) | It was the leak in the agent's own pressure: without it wins against opponents with combos went from 63.8% to 76.4%, and the net of its pressure in the recoil drill from 284 to 1,049 HP a minute. People's follow-ups lose to an opponent that presses 2A in the gap, and a follow-up planner cannot make pressure for a policy that does not start strings. In the code. |
| The pressure hold (`rise_press`: the guard held through the opponent's string) | Against the tester it held 32 of 33 strings and was thrown for 627 HP a minute while dealing 1,300 less. A reworked read that counts the cost of holding guards more pokes and wins nothing on the `press` drill. What to do after a guard is the policy's to learn. |
| The jump account (`risk_jump`) | Stopping jumps only delayed them: jumps a minute stayed at 19-20, and with a hold they came back straight up and from cancels, at 41% wins for 46%. An account can take a losing move away; it cannot put a skill in its place. |
| A knockdown valued at a combo's end (`route_ending`) | Forced knockdown endings lose every time measured (90.6, 88.3, 83.6% at 0, 400, 800 HP). A combo's ending is worth what the okizeme behind it returns. Stays 0. |
| `oki_bait`, `press_sight`, the option matrix for the air catch, `endplan` | No gain. Weighing scripted answers on copies fails where the opponent does not act on cue. |
| `oki_out` (`okiplan:3`: a cornered riser's jump modelled as the jump out, not a back jump) | Off. In sets against opponents that always jump out it hits 68% of the jumping risers first for 38%, and at the bench's size it catches more of their corner jumps (28.0 ±0.9% for 24.9 ±0.9%; 68.6% get out for 71.7%). Wins and own HP lost do not move on `gaps` (77.8 ±2.3% for 75.6 ±2.3%) or on `stays` (60.0 ±2.4% for 59.7 ±2.8%): people's cornered risers jump on 6.5% of their rises, and four in ten of their corner jumps stay in the corner. |
| People's clone playing the okizeme (`okizeme.py`); routes trained into the network; a combo network | The clone has people's mix without the timing and loses 120-210 HP a knockdown; routes in the one network cost it its neutral three times; a network copying route steps starts routes that do not connect. |
| A guard on sight of a jump | 36.9% to 31.8%. |
| The opponent's habits told to the policy; the match memory as a policy input | No read and no gain after 260M steps: an input can only choose among things the policy already does. What adapts is outside the policy, in the planners' counts. |
| `jumpplan` (a planned jump-in), `cancel` (22C on a guarded 623) | Python only. `jumpplan` gained four points on round 17's policy and nothing on round 18's. |

## The training loop

`finetune.py`: PPO from the previous round's pick (the average of its ten chunks'
weights), 20 million steps a round in chunks of two million, learning rate 1e-4 falling to
1e-5, 1,024 steps a rollout, the pull to people's clone at 0.01, a cost of 0.004 on a
press made while hit or guarding (the input rate is a human limit). About four matches in
five are against frozen league opponents; the rest are a mirror and the level-4 Kanna.

A round is judged on the average of its chunks (`average.py`), never on a peak: rounds
8-13 picked peaks and wandered, because one rollout's gradient is 99% noise.

### The league

Ninety opponents over the 22 characters, one match slot each. Each is a model trained to
beat an earlier agent (an exploiter), and each plays as an agent file through the game's
own code (`--vs-native`) with its character's combos (`league_combos.py`: 878-949 combos a
character, started on the step after a hit). Without the combos the league flattered every
agent: the same file went from 95% to 56% when the opponents got theirs.

| exploiters | trained against | note |
|---|---|---|
| `exploiter15` | the policy alone, from each character's strongest model | the generation before trained against a broken frozen copy (see "What misleads") |
| `exploiter16` | the same, paid for air hits (`--focus air`) | |
| `exploiter17` | round 17's policy | won 0-12% against the whole agent with its modules |
| `exploiter18` | the whole agent file, played by the game's code | in the league since round 19; the drills' opponents |
| `exploiter18o` | the same, paid for getting away (`--focus out`) | a learned escaper punishes; a scripted one only measures |
| `exploiter19` | round 22's policy, paid for pressure (`--focus press`) | the reward did little; they are stronger opponents by 5-31 points and replace each character's oldest |

### Scripted habits

On top of an opponent's own play, `advantages.py` makes it do one thing a person does, on
a share of its chances. A profile is a set of them.

| habit | what the opponent does |
|---|---|
| `rg`, `reversal` | recoil-guards, and reverses after a recoil guard if the agent presses on |
| `throw`, `bait`, `damage` | throws a held guard; waits out and punishes the agent's reversals; hits harder |
| `patient` | holds its guard after guarding or rising |
| `wake`, `blind` | reverses on rising when the agent is committed (or blind) |
| `jumpin`, `low` | lands a jump-in on the agent's rising; makes a share of them empty, then a low |
| `tech`, `techsafe`, `techhit`, `techway` | recovers in the air from combos, safely, with a hit, either way |
| `escape` | jumps out of a corner when it is free there, on that share of the moments |
| `press` | runs in and presses 2A into the cancels that reach, guards a moment, and comes again |
| `object` | puts out its object with the most cover, and presses behind it |
| `meaty` | times a 2A to the agent's rising, then presses |
| `antiair` | anti-airs the agent's jumps from a probed table of sure places, keeping each move's record and dropping what loses |
| `gap`, `mash` | presses its fastest normal into the gaps of the agent's pressure, by a read or blind |
| `adapt`, `weak`, `habits` | repeats what worked; keeps a quarter of one area's values; draws its habits afresh for a set |

The profile in training is `sparring` (`rg=0.3,reversal=0.8,damage=1.5,tech=1,techsafe=1,t
echhit=1,escape=1,jumpin=0.5,low=0.6,throw=0.5,bait=0.5` plus the round's own habits), in
two of three matches with advantages; `person` has the rest, with the habits `--vs-extra`
names on top (round 27: `antiair`). It is the first opponent written for the purpose,
whose guard can be opened and which punishes what a person punishes, and it gave the first
gain outside noise since round 18.

`escape=1` is ten times people's rate (people leave a corner by a jump 8% of the time out
of a guard and 11% at a rise). Round 25's second arm and the `stays` drill use 0.1.

### Rewards

The match's result, the press cost, and at most one shaping reward at a small coefficient
(`focus.py`): `air`, `out` and `press` for exploiters, and `corner` for the learner in
round 25 (the opponent's guard touched, a hit within 60 steps of such a guard, each
doubled while the opponent is cornered, and a hit on an airborne opponent there).

### Cost

About 1,100-1,200 steps a second with the opponents played by the game's code, 4-6 GB a
run and 10 GB more at its own evaluations; a bench evaluation is 3.5-5.5 GB. The machine
is shared and about half its 92 GB is held by other work, so a round is one trainer with
one evaluation beside it; with the memory free it ran three trainers or five evaluations.
Training stays on the CPU: a PPO update of 8,192 steps takes 0.13 s there and 0.015 s on
the GPU, but the updates are 6% of a chunk and the rest is the game.

## Measurement

### Protocol

The file as the game plays it (`evaluate.py --p1-native`), opponents at the same 11-frame
delay (`--p2-delay 11`), 64 seeded matches an opponent, jackknife errors (`--folds 16`). A
difference past three errors is real, two to three likely. A round's rule is fixed before
it runs.

### The drills (`bench.py`)

| drill | opponents | what it measures |
|---|---|---|
| `league` | the eleven, no habit | wins, own HP lost, leads kept; saturated |
| `combos` | the eleven with their characters' combos | wins and own HP lost when a hit costs what it costs |
| `sparring` | every habit at once | wins |
| `recoil` | `rg=0.3,reversal=0.8` | who is hit after a recoil guard; its pressure there |
| `cpu` | the level-4 CPU given the file's combos | wins; the CPU's neutral beats the agent's |
| `press` | `press=1,throw=0.5` | what leaving the guard costs against a poke with a combo behind it |
| `objects` | `object=1,press=1,throw=0.5` | the same with an object out |
| `antiair` | `antiair=1`, keeping score | what a jump costs |
| `gaps` | `gap=0.6,mash=0.15,escape=1` and the sparring defence | its own pressure: strings, guards opened, what gets away |
| `stays` | the same with `escape=0.1` | its corner against an opponent that stays as people do |
| `rise`, `riselow`, `reversal`, `bait`, `hold`, `ends`, `handicap`, `planners`, `mirror` | one habit each | its rising, its okizeme, its misses, combo endings, a handicap, another file |

Beside wins, `evaluate.py` gives the HP net by situation (`net_ledger`: its okizeme, its
rising, its pressure, under pressure, by air), the share of time and the rate in each of
eight situations (`areas`), corner stays and what they are made of (`corner`), okizeme
mix-ups, raw specials and flights. `people.py` computes the same for the community's
replays (`people.json`), and `from_record.py` for the tester's recorded games
(`bench.py record`). `--sets N` plays sets against the same opponent with what the agent
counted kept between matches, as the game keeps it.

### What misleads

- **League wins are saturated**: 86-99% for every file since round 18. Judge by the
  drills and the event measures against the strongest player.
- **A seed is worth two points** of league wins and three of own HP lost, as much as a
  round on an exhausted league.
- **An agent that sees sooner than its opponents is flattered**: half of the gain from the
  11-frame delay was out-reacting 14-frame opponents.
- **Planners in the judged file can hide a round**: round 22's eleven points were
  invisible while the files carried the pressure planner.
- **The suite's opponents answer okizeme and strings with a move, where a person guards.**
  What the planned okizeme is worth cannot be read from them; without it the tester saw
  the okizeme gone.
- **A drill's rows can be the script's.** `gaps`' corner rows (the opponent guarding 1.2%
  of a stay, jumps out 72%) measure `escape=1`; the first anti-air table lost to the
  agent's air B for two characters; the `rise` drill had no low.
- **HP reads slowly, events fast.** Telling two opponents apart takes 91 matches by the HP
  net under their okizeme and 8-11 by who hits first or whether the attack is meaty.
- **A play-test session of 14-24 games has an error of 10-12 points.** One session cannot
  tell a file from the tester's play that evening.
- **Every match of an evaluation is a set's first** unless `--sets` is given.
- **Frozen copies were broken until round 15**: every training opponent had the critic's
  weights over the actor's and was a pushover (`copy_policy` fixed it; evaluation was
  always right).

## What people's play looks like

From 1,908 in-sync Ayu matches of the community's replays.

**The strongest player** (HP a minute): deals 8,480, loses 6,049, net +2,431; own okizeme
+1,165, own pressure +492, own rising +219, under pressure +86, coming by air -77, raw
specials +235. Keeps a 3,000 HP lead 88.8% of the time. Strong players have relative
weaknesses (one is weak on its own rising, one in the air), but a relative weakness cannot
be read within a set; only a hole three spreads deep shows in 2-5 matches.

**Rising.** A knockdown lasts 73 steps. Risers guard 53-56%, press a button 17-19%, reverse
10-13%, jump 6.5%, and a corner does not change that. The attacker has a move out as the
opponent rises on 56% of knockdowns. Habits are the player's and do not drift within a
set: a wake-up reversal on 0.00-0.27 of risings by player.

**Okizeme.** 47% low, 36% high, 1% a throw, 2% crossing; best are a jump then a low (+375
HP) and a flight then a low (+230). Against air attacks 95% stand; against ground attacks
92% crouch.

**Pressure.** People's opponents make 5.2 strings a minute of 1.41 guards each. After a
guarded move the attacker makes another grounded move 60% of the time, nothing 24%, an
overhead 11%, a throw 3.6% (it lands 88%); the guard opens 24%. The defender moves after
guarding a string 37% of the time and recoil-guards 36% of guarded moves. Ayu players are
under pressure 10.7% of a match.

**Corners.** Nobody locks one.

| | share of the match | seconds a stay | moves in the air | the opponent guarding | in a hit | its jumps: out / caught |
|---|---|---|---|---|---|---|
| all players (13,027 stays) | 22% | 4.9 | 45% | 12% | 50% | 52% / 12% |
| the strongest | 28% | 5.6 | 46% | 13% | 52% | 48% / 16% |

A stay is worth about 400 HP, and the corner is kept by being back in it soon. The jumps
caught are caught by an air B or C or a 2B already under way, not by a 623 on sight.
What a cornered player does first when it comes free on the ground:

| it came out of | share | guards | a move | jumps | is hit first |
|---|---|---|---|---|---|
| a guard | 36% | 70% | 14% | 8% | 6% |
| its own move | 24% | 25% | 28% | 30% | 2% |
| a rise | 22% | 54% | 16% | 11% | 12% |
| a hit that ended standing | 7% | 70% | 12% | 8% | 6% |
| a landing | 6% | 27% | 27% | 28% | 3% |

**The air.** A frontal jump-in hits people 14%, a crossing one 42%. Against a forward jump
the answer is a ground move 46% of the time and a guard 20%. After an opponent's air
recovery an air throw is 7% of answers and catches 51%; nothing else touches the recovery.

**Combos and risks.** Big combos end in a knockdown 84% of the time. Raw 236C is worth
+310 HP a use, 623A -155, the level-one super -63; a guarded 623 is cancelled with 22C
69-81% of the time, which takes its punishment from 76-86% to 23-29%.

**The tester's strings**: 21-40 contacts and 5.9-10.3 strings a minute, 3.3-4.2 contacts a
string; nine in ten begin on the agent's rising or landing; 29-55% of contacts come with
an object out. The league's opponents make strings as long and a third as many.

## Rounds

Each round starts from the pick before it. Rounds 8-13 are in
[runs/human-ayu/README.md](../runs/human-ayu/README.md).

| round | what was new | result | pick |
|---|---|---|---|
| 14 | chunk averages; fewer mirror and CPU matches; the `person` profile; pull 0.01 | `person` set 40% to 58% | `agent-league14-person-pull01-s1` |
| 15 | frozen copies fixed; exploiters in the league; routes at evaluation | `person` set 81% with routes, 97% over the league | `agent-league15-s1` |
| 16 | `exploiter15`s, the `crowd` profile, the press cost | `crowd` 67% to 82-84%; presses while hit or guarding from 4.5-4.9 to 2.8-3.1 a second | `agent-league16-calm-s2` |
| 17 | `exploiter16`s (air) | 75% to 91% over them; frontal jump-ins still hit 30-37% | `agent-league17-s1` |
| 18 | arms with air recoveries (`tech`) and adapting opponents | the control arm won; neither arm taught anything | `agent-league18-s2` |
| 19 | `exploiter18`s; an arm trained with the modules on | nothing passed; one planner option moved more than either arm | none |
| 20 | everyone at 11 frames; the `sparring` profile | every habit at once 75.0 to 86.2 ±2.0; CPU with combos 31 to 50 | `agent-league20-spar-s1` |
| 21 | the league with combos | against combos 56.1 to 63.1 ±1.7; league 93.5 to 96.2 | `agent-league21-combos-s1` |
| 22 | the same league again | against combos 68.5 to 79.5 ±1.5 (files without planners); own HP lost 67.6 to 60.4 | `agent-league22-combos-s2` |
| 23 | the same league a third time | nothing outside noise | none |
| 24 | six `exploiter19`s; three arms from round 22: opponents that `press`, that press behind an `object`, that `antiair` | press arm +6 points on the press drill only; object arm +5 on the objects drill only; the anti-air arm does not move its own drill (`antiair` 40.3 to 43.8 ±2.8) and gains on the others: `gaps` 75.6 to 82.8 ±1.8, `press` 51.6 to 59.1 ±2.6, `stays` 59.7 to 63.4 ±2.4 (inside noise), every habit at once 93.8 to 97.5 ±1.0 with own HP lost 47.4 to 42.8 ±1.4, own HP lost against combos 62.8 to 60.0 ±0.9; plain league flat (99.1 to 98.6), its raw specials worth less (589 to 436 ±41 HP a minute) | none: round 25's stay arm, from the same start, is ahead of the anti-air arm where it matters (below) |
| 25 | from round 22: the `corner` reward, opponents that press into gaps; an arm with defenders that always leave a corner and an arm with defenders that leave as people do (one free moment in ten) | the arm whose defenders always leave: nothing outside noise on `gaps` (79.1 ±2.1) or `stays` (60.3 ±2.7). The arm whose defenders stay: `stays` 59.7 to 69.1 ±2.7 with its pressure's net -362 to +31 ±123 HP a minute, `antiair` 40.3 to 52.8 ±2.4, against combos 76.4 to 81.8 ±1.4, `press` 51.6 to 57.8 ±2.7, league own HP lost 37.0 to 34.9 ±0.6; every habit at once flat (93.1 ±1.6, where round 24's anti-air arm has 97.5). Neither arm keeps the opponent in a guard longer (6.6-6.8% of a corner stay) or moves to the ground in the corner | `agent-league25-stay-s1` |
| 26 | from round 25: its stay defenders and opponents that anti-air (four league matches in ten, six chances in ten); arms with opponents that also press from the agent's rising, and with the corner reward five times as large (0.05) | the first arm: nothing outside noise (`antiair` 52.8 to 47.8 ±2.8 with its net by air there -248 to +150 ±134, combos 81.8 to 84.1 ±1.3, `press` 57.8 to 61.3 ±2.6, `stays` 69.1 to 66.9 ±2.1). The arm with opponents that press from its rising: worse (`antiair` 39.4 ±2.7, own HP lost with every habit at once 45.3 to 49.4 ±1.1, plain league 99.6 to 98.2 ±0.6), nothing gained. The arm with the larger reward moves what the reward names and pays for it: in the corner 57.9 ±0.4% of its moves are in the air (60.9), the opponent leaves 53.5 ±1.0% of its stays (58.5), a guarded move is followed by its hit 25.2 ±0.7% of the time on `gaps` (21.3), and the opponent still guards 6.7% of a stay; its pressure's net falls from +31 to -359 ±123 HP a minute on `stays` and from -179 to -441 ±96 on `gaps`, against combos 81.8 to 77.3 ±1.6 with 1,901 to 1,822 ±15 HP a combo, own HP lost with every habit at once 45.3 to 51.3 ±1.3 and in the plain league 34.9 to 37.6 ±0.7; `press` 57.8 to 52.5 ±2.6 with its net under their pressure +178 to +461 ±85 | none |
| 27 | from round 25, one trainer: opponents that anti-air on every chance in 85% of the league's matches | `antiair` 52.8 to 46.6 ±2.4 with its net by air there -248 to +2 ±137: not moved; the rest of the bench not judged | none |

## Play-tests

The tester's games, read from the game's records.

| file | games won | what the records showed |
|---|---|---|
| round 12's | 3 of 18 | offence against a guard: okizeme 88% low, no throws |
| round 15's with routes | 11 of 40 | "much more like a human"; open to air attacks and reversals; pressure simple |
| round 17's, routes only | 13 of 28 | pressure two guards long; 41% of combos end in a recovery; no throws |
| `round17c` (planned okizeme and pressure, the air catch) | 7 of 23 | okizeme varied; raw wake-up supers the largest leak; air exchanges lost |
| `round18` | 4 of 14 | the air better; its rising (-877 HP a minute) and raw specials (-1,470) worse |
| `round18k4` (rising guard, risk account) | 12 of 24 | raw specials and frontal jump-ins fixed; rising lost to empty jumps into a low |
| round 20's | 7 of 11 | "relies on hitting first, above all in the air"; raw 236C gambles; no shift to pressure |
| `round21` | 0 of 10 | "sucks under pressure and handle objects" |
| `round22b` (no planners) | 6 of 14 | its okizeme gone: a 2A at seven knockdowns in ten |
| `round22c` (rising hold, pressure hold) | 1 of 5 | the rising hold works; the pressure hold is thrown |
| `round25` (trained against defenders that stay) | 7 of 12 | ahead under the tester's pressure for the first time (+524 ±390 HP a minute); HP lost 6,270 a minute for 7,300-9,000; the five losses (Mishio twice, Kano, Sayuri twice) are the games its jumps lose in; Sayuri puts it in a thrown pose 21 times across two games, including six normal ground throws, two air throws, six parry counters, four running grabs and three entries during two supers. [Replay checks and defense trials](sayuri-throws.md) |

## What was learned

**Combos.** Planned on copies at each hit, from people's library; training them into the
network failed three times. Half its big combos end with the victim free in the air, and a
forced knockdown ending costs more than it returns: the ending is the routes' business,
and it is worth what the okizeme behind it is worth.

**Okizeme.** People's mix by a clone or a prior has no timing and costs wins; timing is a
planner's problem, and the planner's simulation is accurate (options it rated at 1,000 HP
or more against a jumping riser hit first in 70 of 71 cases, those rated 0 or less in 4 of
32). It pays against those who guard and loses to those who answer with a move, so the
league cannot tell what it is worth and a person can.

**Its own rising.** Accounts of HP within a match adapt too slowly (a match has about
eleven risings); a read of the opponent's behaviour works. Guard by what is seen: standing
under a jump until the landing, then low.

**Under pressure.** Nothing in the league holds the agent in a guard, so it learned to
press or jump after one. Holding the guard longer is not the answer to an opponent that
throws a held guard and pokes again. A scripted pressure in the opponents is worth a few
points on the drill made of that script and nothing else. What the league lacks is being
on the agent again and again.

**Its own pressure and the corner.** The direction, in the user's words: "in order to
learn how to handle pressure, it needs to understand how to pressure properly, especially
at corners". Measured, "properly" is this: when the cornered opponent comes free the
tester already has a ground move going more than half the time (people 20%, the agent
10-30%, with four moments in ten in the air), and people's cornered opponents guard seven
times in ten. The corner is held or lost by what the agent does with a guard that stays,
not by catching a jump: a defender that always jumps out trains the wrong thing. Two
arms that differed only in how often the defender leaves showed it: against the one that
always leaves nothing was learned, against the one that leaves as people do the agent
stopped losing HP out of its pressure and won nine points more. What it learned is not
being hit in its gaps. Keeping the opponent in a guard, on the ground, is still not
there. A reward of 0.01 for it moved nothing; at 0.05 the agent does more of what the
reward names (more corner moves on the ground, fewer opponents out, more hits after a
guarded move) and its pressure loses 260-390 HP a minute more, with losses on the drills
that have nothing to do with a corner. A reward buys the look of pressure, not its
result.

**The air.** The league never charged for a jump: a jump costs the agent 20 HP against the
plain league, 50 against combos and 88-120 against the tester. Scripted jump-ins, a guard
on sight and exploiters paid for air hits did not teach it to guard a jump-in; the rising
guard by sight did (frontal jump-ins that hit, 36% to 13% against the tester), and a sure
air throw catches recoveries. Against anti-airs that keep score it has nothing else to
win with: its jumps gain the same and lose 2.4 times as much, its okizeme and pressure
fall with them because both begin from a jump, and what it earns on the ground does not
grow. Training against those anti-airs does not change that, at any share of the matches
(rounds 24, 26 and 27): its jumps stop losing HP there and it wins no more, because it
learns to jump more safely, not to come in another way.

**Raw specials.** An account with priors from its own results removed the losing ones.
The wake-up super was a symptom: the guard that replaced it lost as much until the rising
guard existed.

**Recoil guard.** A correct defence wins nothing until something follows it; the answer
and the punish together were worth seven points on the drill.

**Adapting.** Told habits, adapting opponents and accounts of the agent's own moves all
ended the same way: a read can choose among things the agent can already do. What adapts
is the planners' counts of this opponent (the riser's answers, the attacker on its
rising, the recoil guard), kept through a set. Choosing an area to play in pays only once
the agent can play there.

**Training.** Judge averages, not peaks. An opponent written for the purpose beats a third
round on the same league, and one that behaves as people do beats one that does the thing
every time: the two broad gains since round 22 came from a defender that stays in the
corner and an opponent that anti-airs, each also on drills made of neither. Training at
the delay played matters. Meeting an exploiter in training is worth about a point; what
the modules already cover, training the bare policy does not add.

## Next

1. The community's games with `round25`: the records of many players, read as the
   tester's were (where the HP goes by situation, under whose pressure, with objects out,
   by air), to choose the next direction. More arms of the same kind are not expected to
   pay.
2. A way in on the ground. The agent's offence is its jump; a second way in is what the
   anti-air rounds did not produce and what "playing to an opponent's hole" needs.
3. A defender that holds its guard after guarding, as people do seven times in ten
   (`patient`, guarding low): against one opponent it cut `round25`'s wins from 93.8 to
   89.1% and what its pressure earns from 1,360 to 820 HP a minute, and what follows a
   guarded move of the agent's came close to the tester's (the next move guarded 40%,
   a hit 20%; the tester 43% and 16%). A drill first, then an arm.
4. Frozen copies of the agent into the league as the defence's teachers, once a copy
   keeps an opponent in a guard; until then they would teach what the league already
   does.
5. Objects: an opponent whose object holds the agent in its guard, which the scripted one
   does not.
6. Playing to an opponent's hole (the levers exist: the raw specials' priors, the planners
   as a choice), once there is a second area the agent can play in.
