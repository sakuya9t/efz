# Agents in the game

A trained agent plays in the native game itself: a side of VS HUMAN, chosen on character
select, or this computer's side of a network match. The game runs the agent's network
on its own, from an agent file, without Python or any machine learning library, so an
agent can go to anyone who has the game.

| Source | What it is |
|---|---|
| `python/efz_env/export.py`, `python/examples/export_agent.py` | A pack (or a model.zip and its config.json) written as one agent file (`.efzagent`), checked against what it came from |
| `python/examples/unpack_agent.py` (`export.py`'s `unpack_agent`) | An agent file back as a model.zip, its config.json and its combo library: to train it further or work on it |
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
Beside its modules a file carries its training part, which a game doesn't read (below,
"Working on from an agent file"). The game
still reads the first files (format 1, before November 15: the policy and perhaps its
routes); a game from before then can't read format 2 ("an agent file of another
version").

## Working on from an agent file

An agent file is also how an agent is released: one file to play in the game, to train
further, and to measure. So it carries, beside the modules a game plays, a **training
part**: the rest of the model (the critic: its features, layers and value), the model's
`config.json` (`train.config`: how it sees the game and what it was trained against; the
home folder written as `~`), PPO's settings (`train.sb3`), and with `--optimizer` Adam's
moments. The routes carry what the planner in Python reads beyond the game's (each one's
damage, whether it was kept for its victim, its join points). These are keys and tensors
of no module (`train`, `train.*`, `routes.damage`, `routes.kept`, `routes.marks*`): a game
reads past them, so a game that played the file before plays it now, and
`export_agent.py --no-train` writes a file without them (half the size, to play only).
Round 16's agent with 848 routes: 5.2 MB to play only, 9.6 MB with its training part,
27 MB with the optimizer's moments.

```sh
python python/examples/unpack_agent.py agents/ayu.efzagent --out work/ayu
#   work/ayu/model.zip: the file's model, the critic too (log-probabilities within 4e-05 of the file's)
#   work/ayu/config.json: its settings
#   work/ayu/combo-library.npz: its routes, as a combo library (--assist)
python runs/human-ayu/finetune.py --start work/ayu/model.zip --out runs/mine ...
python runs/human-ayu/evaluate.py --p1 work/ayu/model.zip --p1-assist work/ayu/combo-library.npz ...
python python/examples/export_agent.py runs/mine/avg.zip --parts-from agents/ayu.efzagent
```

- **Unpacking** makes the model anew from the file's numbers and its JSON: a
  Stable-Baselines3 PPO model with the file's weights (round 16's agent: all 27 tensors
  the same to the last bit, its steps and PPO's settings too), its `config.json`, and
  the routes as a combo library with its join points (`load_routes` reads the same 848
  routes from it as from the library they came from). Nothing in the file is run or
  unpickled, so a file from anyone can be unpacked. `packed.json` beside them says which
  file they came from.
- **The tools take the file itself** where they take a model.zip: `efz_env.agent.Agent`
  (so `evaluate.py --p1 FILE.efzagent`, `play.py --agent`), and `finetune.py`'s `--start`
  (unpacked into the run's folder), `--vs`, `--team`, `--prior`, `--old`, `--combo`:
  released agents as the start of a run, or as its opponents. An evaluation of the file
  is the model's: 12 seeded matches gave the same results to the last count.
- **Packing again**: `export_agent.py MODEL --library ...` as before, or `--parts-from
  FILE.efzagent` for a model trained further without the library at hand: the file's
  routes and chooser go into the new one as they are (`--keep routes`: without the
  chooser, which was trained for the agent it came with).
- **Older files** (written before 15 November, or with `--no-train`) hold only the actor:
  unpacked, the critic is new (its features the actor's) and training has to teach the
  value again first; their routes stay in the file (no damage kept: `--parts-from`
  carries them over, a combo library isn't written).
- Not carried: the chooser as `combo_net.py`'s `chooser.pt` (it goes from file to file
  with `--parts-from`), a run's history (`finetune.json`), and the prior a run pulled
  toward.

## Playing against one

On the title, VS HUMAN, then on character select:

- **F5** switches who plays P1: you, then each agent in the folders in turn (by the name
  in the file), then you again. **F6** does the same for P2. **Shift+F5** and
  **Shift+F6** go the other way, so the last agent is one press from you. The bottom of
  the screen says who plays each side.
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

Each fight's record ([logging.md](logging.md)) names the agent that played each side, and
the REPLAY menu's records (Tab) play it back, the agent's side labelled as in the fight.

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

## Its okizeme: planned from people's

An agent file with the module `okiplan:1` plans what it does at its opponent's knockdowns
as `runs/human-ayu/okiplan.py` does in evaluations (`port/agent/mix.h`; the reasons and
the measures: docs/training-v2.md, "The planned okizeme"). Without it an agent's okizeme
is its network's, which is one low attack whoever it plays.

    python runs/human-ayu/oki_library.py --answers ~/data/efz-replays/oki-library.npz
    python python/examples/export_agent.py runs/human-ayu/agent-league17-s1/avg.zip \
        --library ~/data/efz-replays/combo-library-victims.npz --replan \
        --okizeme ~/data/efz-replays/oki-library.npz \
        --okizeme-option per_plan=5 --okizeme-option window=40 \
        --okizeme-option skip=0.05 --okizeme-option think=14

The library (`oki_library.py`) is what a character's players did in the community's
replays from each knockdown they made to their first contact on the riser, with its
timing: 8,499 for Ayu. `--answers` writes beside it what the game needs and has no other
way to know: each character's reversals on rising and the moves that are invincible from
their start. The file is about 5 MB larger for them.

- **When.** On the frame its opponent is knocked down (as the game is), it chooses its
  inputs for the 14 frames until it sees the knockdown, as the routes do at a hit, and
  then `think` frames of crouching guard; the planner works in the game's spare time
  over those frames, from where they leave the fight. A knockdown at a combo's end
  waits until the routes' plan and route are done.
- **What it tries.** The library's okizeme whose player stood where the agent stands, as
  many frames before the rising as are left (an entry is played with its recorded rising
  on the frame this opponent rises), at most `per_class` of a kind (how it comes in, how
  it is guarded, the side; a throw) and `per_plan` in all; a wait (a crouching guard
  through the rising: the bait); and its own play. Each against a riser that guards
  crouching, guards standing, reverses, jumps away, or presses a button; an answer this
  opponent is expected to give less than `skip` of the time isn't played.
- **What it draws.** Each answer's share comes from what it has seen this opponent do on
  its wake-ups and how it guards (counted from its own late view; kept from one match to
  the next of the same seat, older matches counting 0.7 each), over a prior of the
  community's players. An option's worth is the HP it took less the HP it lost by
  `window` frames after the rising, a first hit either way counted as a combo; the draw
  is by exp(expected worth / `temperature`), or with `doubt` the mix that still does
  well if the shares are wrong.
- **Playing it.** Once it sees the knockdown and the game is where the plan expected, it
  plays what was drawn, until the inputs end or it sees itself hit. If the okizeme hits,
  the routes plan from that hit with the rest of the okizeme as one of their options.

The game's planner differs from an evaluation's `okiplan` module in what a frame's spare
time affords: fewer options (5 or 6, not 10), a shorter look after the rising, a
crouching guard after an option's inputs on the copies instead of the network on every
copy (`okiplan.py`'s `after=guard`), and the `think` frames. An evaluation with those
settings is what the game plays; `evaluate.py --p1 FILE.efzagent --p1-native` runs the
game's own code (`runs/human-ayu/native_agent.py`: each match's player attached to its
environment, `NativeAgent.attach`), which is how a file is measured before a person
meets it. `tests.test_agents.OkizemeAsOkiplan`: the same counts from the same views as
`efz_env.memory`, at a knockdown the same options, the same worth against each answer
and the same mix as `okiplan.py`, and plans made and played in a match.

The log has a line a fight: knockdowns planned for, plans made and played and what was
drawn by kind, plans dropped and why, the time a plan took and the game waited, and what
it now expects of this opponent's wake-ups.

A file's okizeme is carried into a file of a model trained further by `--parts-from`
(`--keep routes chooser okiplan pressplan airthrow`, the default); `unpack_agent.py` doesn't write the
library back as a file. A game older than the module refuses the file and says which
module it doesn't play.

## Its pressure: planned from people's

An agent file with the module `pressplan:1` plans what follows each of its guarded moves
as `runs/human-ayu/pressplan.py`'s live plan does (`mix.h`'s `Press`, the okizeme's
planner from a guard instead of a knockdown; docs/training-v2.md, "The planned
pressure"). Without it an agent's pressure is a low or nothing after each guard, with no
throw.

    python runs/human-ayu/pressure_library.py --answers ~/data/efz-replays/pressure-library.npz
    python python/examples/export_agent.py MODEL.zip --library ... --okizeme ... \
        --pressure ~/data/efz-replays/pressure-library.npz

The library is what a character's players did next when a move of theirs was guarded and
they could act again beside the guarding player (17,963 for Ayu: the next move, a throw,
an overhead, holding, backing off), each with the frame advantage it was done at.

- **When.** A plan has no time between seeing a guard and acting on it. So on the frame a
  move of the agent's touches the opponent's guard (as the game is), its inputs for the
  14 frames until it sees the guard are chosen at once (its own play's, from what it has
  seen: what it would have pressed anyway), and the planner works over those frames, from
  where they leave the fight with the opponent holding its guard: then a crouching guard
  until the agent is free (at most `max_wait` frames, else nothing is planned), then the
  follow-up.
- **What it tries.** The library's follow-ups done at the same frame advantage (within
  `slack` frames) and distance (within `tolerance` pixels), a wait (the bait) and its own
  play, each against a guarding player that goes on guarding crouching or standing,
  reverses on its first free frame, jumps away, or presses a button. The shares come from
  what this opponent did after its guards so far; the draw is the mix that holds up if
  those shares are wrong (`doubt` 0.3).
- **Playing it.** When it sees the guard and the game is where the plan expected (the
  opponent did hold its guard), it plays the wait and the follow-up; if the follow-up is
  guarded it plans again from that contact, and if it hits the routes take it from the
  hit. Nothing planned (a hit either way first, the agent not free in time, the opponent
  gone): its own play.

A plan is about 0.6 of a route plan (4 options, the answers expected 5% of the time or
more, 40 frames past the guard). `tests.test_agents.PressureAsPressplan`: from the frame
of a contact the same wait, the same view expected, the same options and worth as
`pressplan.live_plan`, and plans made in a match. The log has a line a fight, as the
okizeme's.

## Its catch: an air throw inside the recovery

An agent file with the module `airthrow:1` air-throws an opponent that recovers in the air
out of its combo, when a throw catches before the recovery is over (`mix.h`'s `Catch`,
`runs/human-ayu/airplan.py`'s sure throw; docs/training-v2.md, "The air"). An opponent
that presses out of a combo in the air is free again beside the agent, and nothing
touches it until its recovery ends, except an air throw (`src/ayu.cpp`: C with forward
held, in the air within 100 pixels of an opponent in the air that is in no hit reaction
and no guard). In the community's replays that is the catch that works: half of the air
throws tried on a recovery catch, a fifth of anything else.

    python python/examples/export_agent.py MODEL.zip --library ... --air-throw

No library and no guess about the opponent: until its recovery ends it can do nothing,
so what a copy of the fight shows is what will happen.

- **When.** On the frame the opponent goes from a hit reaction into its air recovery (as
  the game is), the agent's inputs for the 14 frames until it sees the recovery are
  chosen at once (its own play's), and the planner works over those frames from where
  they leave the fight.
- **What it tries.** C with forward held after every second frame, up to 24 and the
  recovery's end: of holding forward in the air, of a second jump at the opponent, of a
  dash at it; from the ground, that far into a jump at it or straight up. Each on a copy
  until the recovery's end; the one that catches soonest.
- **Playing it.** When it sees the recovery and the game is where the plan expected, it
  plays that throw. None that catches (the opponent too far, the agent still in a move,
  under 3 frames of the recovery left, further apart than `air_near` pixels): its own
  play, as before.

A plan is at most 32 throws of at most 60 frames on copies. `tests.test_agents.
CatchAsAirplan`: from the frame of a recovery the same view expected, the same frames of
the recovery left and the same throw as `airplan.live_throw`, and plans made in a match.
The log has a line a fight ("...'s catches").

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

## The CPU's combos

The game's own CPU (`CpuInput`) guards, recoil-guards and wakes up well at level 4, but its
combos are short. With **CPU COMBO** on in OPTIONS, the CPU of ARCADE (with score or not)
and VS CPU plays its combos from an agent file of its character, planned on copies of the
fight as an agent's are. This is the training's level-4 CPU with combos
(`evaluate.py --p2-cpu-combos`, the benchmark's `cpu` drill), in the game.

**The files.** One for each character, in the `cpu` folder of an agents folder
(`agents/cpu/` in the save folder or the game's; the first by name of each character is
the one played). The Hub has the 22 of 20 November in its `cpu` folder, and its card
says how to set them up:

```sh
hf download sakuya9t/efz --include "cpu/*" --local-dir agents   # into agents/cpu/
python runs/hub.py download cpu                                  # the same
```

`league_combos.py cpu` gathers them from the league's trained opponents, each the newest
exploiter's model with its character's combo library (`league_combos.py files`), and
`hub.py upload --into cpu` sends them up:

```sh
python runs/human-ayu/league_combos.py cpu --out ~/dev/efz/tmp/cpu-combos
#   kano: kano/exploiter18/combos.efzagent -> .../cpu-combos/kano.efzagent (5.2 MB)
#   ...  (22 characters on 20 November: all but Kanna, Mizuka and Nayuki's other form)
python runs/hub.py upload --into cpu ~/dev/efz/tmp/cpu-combos/*.efzagent \
    --names ~/data/efz-replays/player_names.csv   # (edit runs/hub-card.md's list with it)
```

A character with no file there keeps the CPU's own combos; the log says so at the fight.

**How it plays.** The CPU plays as it always does: its neutral, its guard, its recoil
guards and okizeme are its own. The file's player watches the whole fight as it would play
it, and while the CPU's opponent is in a hit reaction (and not down) the side is the
file's: `CPlayer::m_cpu` is off for those frames, so the CPU's decisions stop and the
side reads its controls, which the file gives. Once the opponent is out of the hit
reaction, down, or the round over, the CPU has the side back. The file's player sees what
the CPU pressed in the frames it played, as its own inputs (`Player::Played`).

Its route begins 8 frames after its hit (`kCpuLead`), whatever the file says (the
league's files begin theirs on the step after, which needs a plan made at once); the
plan is made in the time between frames, as an agent's, and a frame waits at most 8 ms
for one, so the person's side never stutters. A plan not done when it is due is chosen
from the routes played by then: for the CPU the routes are played first and the file's
own play last (`Planner::SetOwnLast`), the network's frames on the copies being half of a
plan's time.

**The level.** OPTIONS' CPU level (in ARCADE with score, the stage's: the CPU's
`m_cpuSkill`) sets what a combo aims at (`Planner::SetShare`): at level 4 the most
damaging option the planner finds at the hit; at 3 the one nearest three quarters of
that, at 2 half, at 1 a quarter, its own play among the options. A later plan of the same
combo (the routes are planned again at each new move's hit) aims at what is left of the
combo's target, so that the shares don't compound.

**Records.** A fight's record names the file (`cpu_combos`, and `cpu_combo_share`) and has
a `cpu` line at each tick the side changed hands ([logging.md](logging.md)); replaying the
record hands the side over at the same ticks, so it plays as it was played. A network
match has no CPU, and a record being watched or converted runs none of this.

**The setting** is in `options.ini` in the save folder (`cpu_combos=1`), not in
`key.ini`: that file is the original's, which config.exe and EfzRevival also read and
write. `--cpu-combos on` or `off` sets it for one run. In OPTIONS it is CPU COMBO on the
fourth page, NATIVE (Tab or C turns the pages: the game's own first, then EfzRevival's
two, then the native game's; [native.md](native.md), "OPTIONS").

Measured on 20 November (this Linux machine; VS CPU, Akane's file against an idle
Nagamori): with no time limit on the plans (`--fast`), the combos' damage rose with the
level, a mean of 400, 489, 688 and 1,244 HP from level 1 to 4 (the CPU's first hit
included); in real time at level 4, 51 plans in a minute's fight, a route played in 48,
49 of them chosen from the routes played by then, the game waiting 8 ms a plan.

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

- **Other modules**: of an `agent.json`'s modules the file takes `routes` and, through
  `--okizeme`, `--pressure` and `--air-throw`, the planned okizeme and pressure and the
  catch; not `oki` (people's okizeme played by a second network), routes chosen by the
  chooser alone (`by: chooser`), or `airplan`'s and `jumpplan`'s options tried against
  answers (measured in evaluations only: docs/training-v2.md, "The air").
- **A real EfzRevival 1.02h peer**: the network matches above are this game against
  itself.
- **A controller's button** for F5 and F6: the keyboard only.
