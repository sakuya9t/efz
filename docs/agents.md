# Agents in the game

A trained agent plays in the native game itself: a side of VS HUMAN, chosen on character
select, or this computer's side of a network match. The game runs the agent's network
on its own, from an agent file, without Python or any machine learning library, so an
agent can go to anyone who has the game.

| Source | What it is |
|---|---|
| `python/efz_env/export.py`, `python/examples/export_agent.py` | A pack (or a model.zip and its config.json) written as one agent file (`.efzagent`), checked against what it came from |
| `port/agent/observe.cpp` | The agent's view of a fight, 168 numbers: the training library's observation, one file for both |
| `port/agent/policy.cpp` | The agent file read (its modules checked), its networks run, and an agent playing a side as `play.py` plays it |
| `port/agent/routes.cpp` | Its combos from a library's routes, planned on copies of the fight as `play.py --assist` plans them |
| `port/agent/play.cpp`, `port/agents.h` | The game's side: character select, the fight, the NET PLAY row, what the screen shows |

## Making an agent file

```sh
python python/examples/export_agent.py tmp/efz-round15b-pack.zip
#   tmp/round15b/agent-league15-s1/avg.zip: in the file: policy
#   tmp/round15b/combo-library-victims.npz: in the file: routes
#   tmp/round15b/combo-library-victims.marks.json: in the file: routes (its join points)
#   tmp/round15b/combo-chooser15/chooser.pt: in the file: chooser
#   runs/human-ayu/redteam.py: not needed: the pack's code: the game plays its own (port/agent)
#   ...
# .../agent-league15-s1-round15b.efzagent (11.1 MB): "agent-league15-s1 round15b",
# policy:1,routes:1,chooser:1; its combos from 848 routes, planned again at each new move's
# hit (10110 joined at a later move); the chooser's when a plan is late. ...
python python/examples/export_agent.py --show agents/agent-league15-s1-round15b.efzagent
```

A pack (`play.py`'s zip, the one that carries an agent by hand) goes into the file whole:
its model, its combo library's routes, the library's join points and its chooser, so the
one file is all the agent plays with. It plays as the pack's `play.py` plays it: as an
`agent.json` in the pack says (runs/human-ayu's `efz_env.modules` manifest: its `routes`
module's library, chooser, `replan`, `per_start`, `victims`); without one, a library with
join points (round 15b's) is planned again at each new move's hit, 24 routes a plan, and
one without (round 15's) once at the first hit, 12. Each of the pack's files is listed with
what became of it: carried in the file, or not needed (the pack's Python code, which the
game has natively in `port/agent`; its README, launcher, the chooser's training record).
A file the agent file can't carry (another kind of module, such as `agent.json`'s `oki`,
or anything it doesn't know) stops the export, naming it; `--drop` leaves it out, as it
does a part: `--drop chooser`, `--drop marks` (planned once), `--drop routes` (its own
combos). `--replan` / `--once` and `--per-start N` change how it plans.

A model alone works too: a `model.zip` (or `avg.zip`) from `train.py` or
`runs/human-ayu/finetune.py`, with the `config.json` beside it that `play.py` reads too:
how often it decides (`frame_skip`), how many steps of its own inputs it sees (`history`)
and how late it sees the game (`delay`, the reaction time). `--library` gives it its
combos from a combo library's routes (its join points beside it, `LIBRARY.marks.json`),
`--chooser` that library's chooser, `--victims` keeps the routes to those characters
(`play.py --assist-victims`).

`--name` sets what the game shows (default: the model's folder), `--version` what it shows
beside it (default: a pack's name, `round15b` for `efz-round15b-pack.zip`), `--char` the
character it plays (default: the first of its training's `chars`), `--out` the file
(default beside the pack or model, `NAME-VERSION.efzagent`). Exporting needs
stable-baselines3, torch and the efz_env library, and checks the file, each part against
what it came from: run in the library, its log-probabilities must be the model's (round
15's agent's agree to 5e-5), its chooser's values the chooser's (within 0.01 HP), its
routes and their pool as many as written.

Copy the file into a folder named `agents` in the game's folder, or in its save folder
(where `key.ini` is written). The game reads the folders at startup, at each F5 or F6,
and each time NET PLAY's screen opens.

What the file holds (its layout is in `port/agent/policy.h`), in modules, each of a
version, which its header lists (`modules=policy:1,routes:1,chooser:1`):

| Module | What |
|---|---|
| `policy:1` | The actor of the model's policy (`efz_env.policy.EfzPolicy`'s features, embeddings and layers, or SB3's MlpPolicy), the 45 control bytes of its actions, the settings above |
| `routes:1` | The library's routes (each combo's inputs as actions, the move it starts from and the character it was landed on: no player names), how the planner takes them, and with replanning its pool: each route from its start and from each of its join points, in the planner's order |
| `chooser:1` | The chooser's network (a copy of the agent's features and its head) |

A game refuses a file with a module, or a version of one, that it doesn't play, and says
which ("the agent has the module oki:1, which this game doesn't play ...: a newer game
does"). The header also says where each part came from (`source.pack`, `source.model`,
`source.library`, `source.marks`, `source.chooser`: its name and SHA-256), the exporter
and its revision, when, and what of the pack was dropped; the game writes those to
`efz.log` when it first plays the file, and the menus show the version beside the name.
The critic, the optimiser and everything else of the training are left out. The game
still reads the first files (format 1, before November 15: the policy and perhaps its
routes); a game from before then can't read format 2 ("an agent file of another
version").

## Playing against one

On the title, VS HUMAN, then on character select:

- **F5** switches who plays P1: you, then each agent in the folders in turn, then you
  again. **F6** does the same for P2. The bottom of the screen says who plays each side.
- An agent's side picks its own character (the one it was trained to play) by moving the
  cursor and pressing A, and keeps the colour it lands on. The stage is yours to pick.
- With P1 an agent, you play P2 with P1's controls (your usual keys) as well as P2's.
- Two agents can play each other: F5 and F6 both.

In the fight the agent plays as `play.py` plays it: from the first frame the controls do
something, a decision every `frame_skip` frames, the game seen `delay` decisions late (14
frames for the human-like agents: a person's reaction), its own last inputs seen at once,
nothing pressed during the intros and KOs. It draws its choices at random by the
network's probabilities, as `play.py` does without `--deterministic`, from a random
generator of its own.

`--agent-p1 FILE` and `--agent-p2 FILE` on the command line start with those sides played
by those agent files (a name in the agents folders, or a path).

## Its combos: the routes

An agent file with routes plays its combos as `play.py --assist` does
(`runs/human-ayu/combo_support.py`'s LiveRoutes, with `redteam.py`'s planner); the fight's
label says `+routes`. At the frame its hit lands (its combo counter goes from 0), it
chooses its inputs for the 14 frames until it sees the hit, from what it has seen already;
the game is copied, and on the copy those inputs are played with the opponent holding
back. From there the library's combos that start with the move that hit (the first 12, or
24 replanning, long enough, those landed on this opponent first) and its own play are
each played on a copy, the opponent guarding once it can, until the combo ends. When it
sees its hit, it plays the one that dealt the most if that beats its own play, and if the
game is where the plan expected (the opponent did hold back, or it didn't matter) and the
combo goes on; else it plays on by itself.

**Planned again** (round 15b's, `route_replan`): a recorded combo fits the position it was
made in (the corner, mid-screen) and hardly any other, so at each hit of a new move in the
combo it plans again. Its inputs until it sees that hit are the route's it is on; the
options are the rest of that route, the library's combos joined where that same move hit
in them (their join points: from there their inputs are what followed that move, worth
the damage they made after it), and its own play. A hit that lands while a plan is awaited
is planned on once it is in, the routes joined that much further in. On the eight
person-like league opponents this took round 15's agent from 81% of wins (own HP lost 64%)
to 90% (55%), 1,240 HP a combo to 1,530 (README-round15b).

The copies are the game's own fight, saved and written back as netplay's rollback saves
it (`agent/routes.h`, `agent/play.cpp`), and worked on in the time between frames. A plan
of 24 routes is about 100 ms of a fight's frames run on copies (150-270 at most), and a
frame leaves about 12 of its 15.6 free, so the 14 frames before the agent sees its hit
are about enough. If a combo's first plan isn't done by then, the frame waits for it 40 ms
at most (8 in a network match), then **the chooser** decides, if the file has one: from
what the agent sees then, it says what each of the library's combos of that move (the
first 12) and its own play would deal, and the most promising is played from memory if it
promises 200 HP more than its own play (`combo_net.py`'s NetPlanner); without a chooser,
or if it says its own play, the agent plays on by itself. A later plan not done in half a
frame (8 ms): the combo goes on with the route it is on. The copies' frames are not
drawn, heard, recorded or sent: no sound (`sound.cpp`), no keys (`input.cpp`, and the
network match's function keys), no replay written, the fight recorder's tick hooks set
aside, and when the fight is written back nothing of them is left. With `--fast` (no time
between frames) each plan is waited for until it is done.

What the routes did goes to `efz.log` at each fight's end: plans asked (and of them at a
later move's hit), made, routes chosen, plans dropped and why (late, and of those how many
the chooser played for; the game elsewhere, the combo over), the time a plan took and the
time the game waited for one.

One difference from `play.py`: a route that ends a round before the last with a KO is
counted at what it dealt, the opponent's whole HP. The Python planner's copies run on
through a KO within a step (`skip_noninteractive`), so they miss the KO's last blow and
count such a route short.

## Over the network

NET PLAY's screen has a row **PLAYED BY**: YOU, or an agent (left and right switch; it is
kept in `netplay.ini`). With an agent there, the agent plays this computer's side of the
match: it picks its character, then you pick the stage, and it plays every fight. The
match screen writes `[agent NAME]` after your name. From the command line:

```sh
efz --data DIR --host --agent agent-league15-s1.efzagent
```

The other player sees a player: an agent plays through this side's input, the one byte a
frame that Revival's protocol carries, exactly where your controls' byte would be
(`Session::ReadInput`). Nothing else changes, which is what keeps it playing EfzRevival
1.02h:

- **Not the game's random numbers.** The agent's choices come from its own generator, not
  `rand()`, which Revival replaces with a generator both sides keep in step.
- **Once a frame.** It decides once for each frame of input, when the session reads this
  side's input; rollback runs frames again with the inputs already decided and never asks
  it again.
- **What a player sees.** It sees the frame the screen shows, the one the session runs
  last with the drawing on (`Session::RunFightFrames`), with the other side's latest inputs
  predicted as for a person; then the input delay applies to it as to a person.

So the agent's reaction is its trained `delay` plus the match's input delay, as a person's
is their own plus the input delay. On character select it waits for each press to show
(the ping's frames) before the next.

Its routes too: a plan starts from the frame shown, the one it sees, and is made on copies
between frames, out of the session's frames; nothing of it reaches the match, its sounds,
its replay or the sync records. A plan is dropped more often online (the game elsewhere):
the opponent's inputs, or a rollback, change the frames it was made for.

## Checking it

- `python/tests/test_agents.py`: an exported EfzPolicy and an exported MlpPolicy give the
  model's log-probabilities; a damaged file is refused, so is one with a module (or a
  module's version, or a format) the library doesn't play, by name, and a format 1 file
  is read; the header says where each part came from; a chooser gives the chooser's
  values and NetPlanner's picks; a pack goes in whole (model, library, join points,
  chooser), each file accounted for, one it can't carry refused unless dropped; and over a
  match against the CPU,
  the exported agent run as the game runs it makes the same decisions as
  `efz_env.agent.Agent`, frame for frame, with a delay, a history, and with and without a
  frame skip.
- `python/tests/test_agents.py`'s `PlansAsRedteam`: at each hit of a match, the game's
  planner (`efz_env_agent_plan`) and `redteam.py`'s, run as `combo_support.py`'s
  `_live_worker` runs it, on the same game with a library of random routes: the same
  routes tried, the same damage from each and from its own play, the same route chosen,
  the same view expected; and the game left byte for byte as it was. `test_same_replans`:
  the same with round 15b's planner (`replan=True`, which this checkout's
  `runs/human-ayu/redteam.py` has once round 15b's code is in it; skipped before), at
  each new move's hit: the same pools, the same routes joined, the extra option and a plan
  made late; run against round 15b's pack's code, it passes.
- Round 15's agent and its library (848 routes), at its hits against the CPU's Mai,
  Nayuki (B) and Misaki: 40 plans of the game's planner beside `redteam.py`'s, as
  `_live_worker` makes them. Every route dealt the same, but 5 KOs before the last round
  (above); the same route chosen in all 36 that could be compared; its own play on the
  copies the same in 36 of 38 (two near-ties of its likeliest action, which the network's
  float differences from PyTorch, 5e-5, tip). A plan took 77 ms at the median in the
  library (whose copies are whole games), the Python planner's 139.
- Round 15b's pack as one file, at each new move's hit of round 15's agent against the
  CPU's Mai: 60 plans of the game's planner beside round 15b's `redteam.py`
  `Planner(replan=True)` (33 at a later move, 15 made 2 frames late, 33 with the rest of a
  route as an option), on its real library (848 combos, 10,110 joined at their join
  points; the pools the same, entry for entry). Every route dealt the same but KOs before
  the last round (above); the same choice in all 52 without one (33 routes, among them
  joined ones, and once the rest of the route); its own play the same in all of them. The
  chooser's pick was NetPlanner's at all 12 first hits. A plan took 100 ms at the median
  in the library (194 at most), the Python planner's 291, on a machine busy with training.
- `tests/headless_test.cpp`: the routes read from an agent file, and the player and planner
  on a game of a few numbers: the inputs chosen at the hit, then the route that deals the
  most; dropped when the game is elsewhere, or when there's no time to plan; the same plan
  worked on in pieces. Replanning: at a new move's hit a route joined there is chosen over
  the rest of the route and its own play, or the rest of the route over a shorter one; a
  first plan late plays the chooser's pick, or its own play if the pick doesn't promise
  the margin. Format 2: a module this game doesn't play refused by name, format 1 read.
- The library's observations are byte for byte what they were before the view moved to
  `port/agent/observe.cpp` (4,000 frames of 8 matches compared).
- Round 15's agent (`agent-league15-s1`), exported, against the CPU for a whole match:
  6,078 decisions, every one the same as `efz_env.agent.Agent`'s (both choosing their
  likeliest action).
- In the game, `--agent-p1` and `--agent-p2` with `--keys` through the title play a match
  of two agents from character select (both pick Ayu) to the results: 7,503 frames of
  fight, 3 ms a frame with both agents deciding.
- The same with round 15's agent and its library (`efz-round15-pack.zip`, 848 routes) at
  the game's speed: 5,817 frames of fight at 64 a second; 25 plans, a route chosen in 6,
  none dropped; a plan took 46-49 ms on average (111 at most) in the time between frames,
  and the game never waited for one.
- Round 15b's file in the game (P1) against round 15's format 1 file (P2), from the title.
  With `--fast`: 67 plans for P1 (55 at a later move's hit), a route chosen in 42; P2's 13
  plans once a combo. At the game's speed, on a machine running training (load 150 on 32
  threads): 62 plans asked for P1, 36 made, 26 late (the chooser's route for 2 of them),
  the game waiting 6 ms a plan (41 at most); P2's 11, none late.
- Two games on one machine (Linux, November 2026), each a network match from the title:

  | Sides | Link | Delay | Frames | Rollback | Sync records |
  |---|---|---|---|---|---|
  | An agent each (`--host --agent`, `--join --agent`) | Loopback | 0 | 15,661 | every frame | all the same |
  | An agent against scripted input | Loopback, 60 ± 20 ms each way from the joiner | 2 | 8,642 | 3,504 rollbacks, 3,505 and 5,749 frames run again | all the same |
  | An agent with routes each (round 15's, 848 routes) | Loopback, 60 ± 20 ms each way from the joiner | 2 | 11,644 | 8,332 rollbacks, 9,298 and 8,336 frames run again | all the same |

  | Round 15b's file each (replanning, the chooser) | Loopback, 60 ± 20 ms each way from the joiner | 2 | 11,650 | 10,183 rollbacks, 10,206 and 20,391 frames run again | all the same |

  With round 15's routes: 39 plans, a route chosen in 11; 6 dropped, all for the game
  elsewhere; the game waited 2.6 ms for a plan at most. With round 15b's, on the busy
  machine: 71 and 60 plans asked, 39 and 34 made; 24 and 18 late (the chooser's route for
  4 each), 8 and 8 for the game elsewhere; the game waited 8.7 ms for a plan at most.

- The compatibility suite (`tools/compat.py check`): 254 of 254 cases as the reference,
  in the game and headless: with no agent chosen, the game is the same.

## Not yet

- **Other modules**: an `agent.json`'s modules besides `routes` (`oki`, people's okizeme
  played by a second network) can't go into a file yet; nor routes chosen by the chooser
  alone (`by: chooser`).
- **A real EfzRevival 1.02h peer**: the network matches above are this game against
  itself.
- **A controller's button** for F5 and F6: the keyboard only.
