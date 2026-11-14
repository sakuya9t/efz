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
| `port/agent/play.cpp`, `port/agents.h` | The game's side: character select, the fight, the NET PLAY row, what the screen shows |

## Making an agent file

```sh
python python/examples/export_agent.py tmp/round15/agent-league15-s1/avg.zip
# tmp/round15/agent-league15-s1/agent-league15-s1.efzagent (4.5 MB): "agent-league15-s1"; ...
```

The model is a `model.zip` (or `avg.zip`) from `train.py` or `runs/human-ayu/finetune.py`,
with the `config.json` beside it that `play.py` reads too: how often it decides
(`frame_skip`), how many steps of its own inputs it sees (`history`) and how late it sees
the game (`delay`, the reaction time). A pack (`play.py`'s zip) works as well.
`--name` sets what the game shows (default: the model's folder), `--char` the character
it plays (default: the first of its training's `chars`), `--out` the file. Exporting
needs stable-baselines3 and the efz_env library, and checks the file: run in the
library, its log-probabilities must be the model's (round 15's agent's agree to 5e-5).

Copy the file into a folder named `agents` in the game's folder, or in its save folder
(where `key.ini` is written). The game reads the folders at startup, at each F5 or F6,
and each time NET PLAY's screen opens.

What the file holds: the actor of the model's policy (`efz_env.policy.EfzPolicy`'s
features, embeddings and layers, or SB3's MlpPolicy), the 45 control bytes of its
actions, and the settings above; its layout is in `port/agent/policy.h`. The critic, the
optimiser and everything else of the training are left out.

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

## Checking it

- `python/tests/test_agents.py`: an exported EfzPolicy and an exported MlpPolicy give the
  model's log-probabilities; a damaged file is refused; and over a match against the CPU,
  the exported agent run as the game runs it makes the same decisions as
  `efz_env.agent.Agent`, frame for frame, with a delay, a history, and with and without a
  frame skip.
- The library's observations are byte for byte what they were before the view moved to
  `port/agent/observe.cpp` (4,000 frames of 8 matches compared).
- Round 15's agent (`agent-league15-s1`), exported, against the CPU for a whole match:
  6,078 decisions, every one the same as `efz_env.agent.Agent`'s (both choosing their
  likeliest action).
- In the game, `--agent-p1` and `--agent-p2` with `--keys` through the title play a match
  of two agents from character select (both pick Ayu) to the results: 7,503 frames of
  fight, 3 ms a frame with both agents deciding.
- Two games on one machine (Linux, November 2026), each a network match from the title:

  | Sides | Link | Delay | Frames | Rollback | Sync records |
  |---|---|---|---|---|---|
  | An agent each (`--host --agent`, `--join --agent`) | Loopback | 0 | 15,661 | every frame | all the same |
  | An agent against scripted input | Loopback, 60 ± 20 ms each way from the joiner | 2 | 8,642 | 3,504 rollbacks, 3,505 and 5,749 frames run again | all the same |

- The compatibility suite (`tools/compat.py check`): 254 of 254 cases as the reference,
  in the game and headless: with no agent chosen, the game is the same.

## Not yet

- **Built-in routes** (`play.py --assist`, `--chooser`): the agent plays its own combos.
  The chooser network and the route library could be exported and played the same way.
- **A controller's button** for F5 and F6: the keyboard only.
