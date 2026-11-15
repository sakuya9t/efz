# Agents in the game

A trained agent plays in the native game itself: a side of VS HUMAN, chosen on character
select, or this computer's side of a network match. The game runs the agent's network
on its own, from an agent file, without Python or any machine learning library, so an
agent can go to anyone who has the game.

| Source | What it is |
|---|---|
| `python/efz_env/export.py`, `python/examples/export_agent.py` | A model.zip and its config.json written as an agent file (`.efzagent`), checked against the model |
| `port/agent/observe.cpp` | The agent's view of a fight, 168 numbers: the training library's observation, one file for both |
| `port/agent/policy.cpp` | The agent file read, its network run, and an agent playing a side as `play.py` plays it |
| `port/agent/routes.cpp` | Its combos from a library's routes, planned on copies of the fight as `play.py --assist` plans them |
| `port/agent/play.cpp`, `port/agents.h` | The game's side: character select, the fight, the NET PLAY row, what the screen shows |

## Making an agent file

```sh
python python/examples/export_agent.py tmp/efz-round15-pack.zip
# .../agent-league15-s1.efzagent (4.9 MB): "agent-league15-s1", its combos from 848 routes of
# combo-library-victims.npz; ...
python python/examples/export_agent.py tmp/round15/agent-league15-s1/avg.zip \
    --library tmp/round15/combo-library-victims.npz
```

The model is a `model.zip` (or `avg.zip`) from `train.py` or `runs/human-ayu/finetune.py`,
with the `config.json` beside it that `play.py` reads too: how often it decides
(`frame_skip`), how many steps of its own inputs it sees (`history`) and how late it sees
the game (`delay`, the reaction time). A pack (`play.py`'s zip) works as well.
`--name` sets what the game shows (default: the model's folder), `--char` the character
it plays (default: the first of its training's `chars`), `--out` the file. `--library`
gives it its combos from a combo library's routes, as `play.py --assist LIBRARY` plays
them (below); a pack's library is taken unless `--no-routes`, and `--victims` keeps the
routes to those characters (`play.py --assist-victims`). Exporting
needs stable-baselines3 and the efz_env library, and checks the file: run in the
library, its log-probabilities must be the model's (round 15's agent's agree to 5e-5).

Copy the file into a folder named `agents` in the game's folder, or in its save folder
(where `key.ini` is written). The game reads the folders at startup, at each F5 or F6,
and each time NET PLAY's screen opens.

What the file holds: the actor of the model's policy (`efz_env.policy.EfzPolicy`'s
features, embeddings and layers, or SB3's MlpPolicy), the 45 control bytes of its
actions, the settings above, and the library's routes if it has some (each combo's
inputs as actions, the move it starts from and the character it was landed on: no
player names); its layout is in `port/agent/policy.h`. The critic, the optimiser and
everything else of the training are left out.

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
back. From there the library's combos that start with the move that hit (the first 12
long enough, those landed on this opponent first) and its own play are each played on a
copy, the opponent guarding once it can, until the combo ends. When it sees its hit, it
plays the one that dealt the most if that beats its own play, and if the game is where
the plan expected (the opponent did hold back, or it didn't matter) and the combo goes
on; else it plays on by itself.

The copies are the game's own fight, saved and written back as netplay's rollback saves
it (`agent/routes.h`, `agent/play.cpp`), and worked on in the time between frames: a plan
is about 50 ms of a fight's frames run on copies (100-150 at most), and a frame leaves
about 12 of its 15.6 free, so the 14 frames before the agent sees its hit are enough. If a
plan isn't done by then, the frame waits for it 40 ms at most (8 in a network match),
then the agent plays on by itself. The copies' frames are not drawn, heard, recorded or
sent: no sound (`sound.cpp`), no keys (`input.cpp`, and the network match's function
keys), no replay written, the fight recorder's tick hooks set aside, and when the fight is
written back nothing of them is left. With `--fast` (no time between frames) each plan is
waited for until it is done.

What the routes did goes to `efz.log` at each fight's end: plans made and routes chosen,
plans dropped and why (late, the game elsewhere, the combo over), the time a plan took
and the time the game waited for one.

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
  model's log-probabilities; a damaged file is refused; and over a match against the CPU,
  the exported agent run as the game runs it makes the same decisions as
  `efz_env.agent.Agent`, frame for frame, with a delay, a history, and with and without a
  frame skip.
- `python/tests/test_agents.py`'s `PlansAsRedteam`: at each hit of a match, the game's
  planner (`efz_env_agent_plan`) and `redteam.py`'s, run as `combo_support.py`'s
  `_live_worker` runs it, on the same game with a library of random routes: the same
  routes tried, the same damage from each and from its own play, the same route chosen,
  the same view expected; and the game left byte for byte as it was.
- Round 15's agent and its library (848 routes), at its hits against the CPU's Mai,
  Nayuki (B) and Misaki: 40 plans of the game's planner beside `redteam.py`'s, as
  `_live_worker` makes them. Every route dealt the same, but 5 KOs before the last round
  (above); the same route chosen in all 36 that could be compared; its own play on the
  copies the same in 36 of 38 (two near-ties of its likeliest action, which the network's
  float differences from PyTorch, 5e-5, tip). A plan took 77 ms at the median in the
  library (whose copies are whole games), the Python planner's 139.
- `tests/headless_test.cpp`: the routes read from an agent file, and the player and planner
  on a game of a few numbers: the inputs chosen at the hit, then the route that deals the
  most; dropped when the game is elsewhere, or when there's no time to plan; the same plan
  worked on in pieces.
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
- Two games on one machine (Linux, November 2026), each a network match from the title:

  | Sides | Link | Delay | Frames | Rollback | Sync records |
  |---|---|---|---|---|---|
  | An agent each (`--host --agent`, `--join --agent`) | Loopback | 0 | 15,661 | every frame | all the same |
  | An agent against scripted input | Loopback, 60 ± 20 ms each way from the joiner | 2 | 8,642 | 3,504 rollbacks, 3,505 and 5,749 frames run again | all the same |
  | An agent with routes each (round 15's, 848 routes) | Loopback, 60 ± 20 ms each way from the joiner | 2 | 11,644 | 8,332 rollbacks, 9,298 and 8,336 frames run again | all the same |

  With routes: 39 plans, a route chosen in 11; 6 dropped, all for the game elsewhere; the
  game waited 2.6 ms for a plan at most.

- The compatibility suite (`tools/compat.py check`): 254 of 254 cases as the reference,
  in the game and headless: with no agent chosen, the game is the same.

## Not yet

- **The chooser** (`play.py --assist --chooser`): a network choosing the route instead of
  copies of the fight; the routes here are the planner's.
- **Planning again at each new hit of a combo** (round 15b's pack): a plan is made once,
  at the combo's first hit, as round 15's `play.py --assist` made it.
- **A controller's button** for F5 and F6: the keyboard only.
