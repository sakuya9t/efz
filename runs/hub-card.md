---
tags:
- reinforcement-learning
- game-ai
- fighting-game
---

# EFZ agents

Agents that play Eternal Fighter Zero, as Ayu against any character, inside the native
port of the game in [sakuya9t/efz](https://github.com/sakuya9t/efz). Each one is a single
agent file (`.efzagent`): the policy network the game runs, its combos (routes planned
from people's replays), the modules the game plays beside them, and a training part (the
critic and the training settings) to train it further. Nothing in a file is run: the game
and the Python tools read only its numbers and text, so a file from anyone is safe to load.
The `cpu` folder holds one more file for each character, which gives the game's own CPU
its combos ([below](#the-games-cpu-with-combos-cpu)).

They learnt from the community's replays (a clone of people's play, reacting as late as a
person does), then from a league of trained opponents. How each round was trained and
judged: [docs/training-v2.md](https://github.com/sakuya9t/efz/blob/release/next/docs/training-v2.md);
the file format and the modules: [docs/agents.md](https://github.com/sakuya9t/efz/blob/release/next/docs/agents.md).

## The files

| File | Built | Sees the game | Modules | What it is |
|---|---|---|---|---|
| `agent-league20-spar-s1-round20.efzagent` | 20 Nov 2026 | 11 frames late | policy, routes, okiplan:2, pressplan:1, airthrow, rise, risk | **The one to play.** Round 20: trained at the delay it plays at, against opponents scripted with people's habits (recoil guards, reversals, techs, escapes, jump-ins, lows, throws, bait). Its wake-up guard answers a recoil guard as the match has shown it and punishes it. |
| `agent-league18-s2-round18k8.efzagent` | 20 Nov 2026 | 11 frames late | the same | Round 18's policy (trained seeing 14 frames late) run at 11, with the wake-up guard, the raw specials' accounts and the recoil-guard answer read from the match. The mark round 20 was judged against. |
| `agent-league17-s1-round17c.efzagent` | 16 Nov 2026 | 14 frames late | policy, routes, okiplan:1, pressplan:1, airthrow | Round 17: okizeme and pressure planned from people's, and an air throw that catches an opponent recovering in the air out of its combo. |
| `agent-league16-calm-s2-round16.efzagent` | 15 Nov 2026 | 14 frames late | policy, routes | Round 16: the policy and its combos only. The first file with a training part, and the only one here that a game without the later modules plays. |

Round 20 beside round 18k8, 64 matches a pairing played through the game's own code, the
opponents also 11 frames late (± one standard error):

| | round 18k8 | round 20 |
|---|---|---|
| wins against the league's eleven trained opponents | 93.5 ±0.9 % | 95.3 ±0.7 % |
| its own HP lost a round there | 54.8 ±0.7 % | 50.2 ±0.8 % |
| wins against every scripted habit at once | 75.0 ±2.3 % | 90.0 ±1.6 % |
| wins against recoil guards | 80.0 ±2.0 % | 88.8 ±1.3 % |
| wins against the level-4 CPU given the agent's own combos | 31.2 ±6.2 % | 43.8 ±4.8 % |

Where round 20 is still weak: the level-4 CPU with combos wins more than half; it lets an
opponent out of the corner; an opponent gets out of half its big combos by recovering; it
starts moves into strikes already out.

## Playing one

Build the game from the repository's `release/next` branch (afac5c4 or later: the round 18k8
and round 20 files use its wake-up guard; `main` plays only the round 16 file until it
takes those changes). Put the file in an `agents` folder in the game's folder (or in its
save folder), then:

- **VS HUMAN**: on character select, F5 switches who plays P1 (you, then each agent in
  turn), F6 the same for P2; the agent picks its own character. Or start the game with
  `--agent-p1 FILE` / `--agent-p2 FILE`.
- **Over the network**: NET PLAY's **PLAYED BY** row (or `--agent FILE`): the agent plays
  this computer's side through the same one byte of input a frame a player's controls
  send, so the other side can be EfzRevival 1.02h as usual.

## The game's CPU with combos (`cpu/`)

With these files the game's own CPU, in ARCADE and VS CPU, plays combos the way the agents
plan theirs, from people's routes for its character. The rest of its play (moving,
guarding, recoil guards, okizeme) is still the game's own.

1. Build the game from the repository's `release/next` branch, df8208d or later (the
   CPU COMBO option).
2. Put the files in `agents/cpu/` in the game's folder (or in its save folder):

   ```sh
   hf download sakuya9t/efz --include "cpu/*" --local-dir agents
   # or, in a checkout of the repository:
   python runs/hub.py download cpu                                  # into agents/cpu/
   ```

3. In OPTIONS, set **CPUコンボ** (the row after CPU難易度) to **あり**. The setting is saved in
   `options.ini` in the save folder. `--cpu-combos on` or `--cpu-combos off` on the command
   line sets it for one run only.

**The CPU's level sets the damage.** At level 4 the CPU plays the most damaging combo the
planner finds at each hit. At levels 3, 2 and 1 it plays the combo nearest 75%, 50% and 25%
of that. In ARCADE with score, the stage's level counts. In test fights (Akane's file
against an opponent standing still, the planner given unlimited time), a combo dealt 400,
489, 688 and 1,244 HP on average at levels 1 to 4.

**How it plays.** When the CPU lands a hit, it hands its side to its character's file
until the opponent leaves the hit reaction, is knocked down, or the round ends. The file's
route starts 8 frames after the hit. The planner works in the time between frames, and a
frame waits for it at most 8 ms, so the game never stutters. On a slow machine, a plan that
isn't finished in time is picked from the routes tried so far, and a level-4 combo may deal
less. A fight record keeps each hand-off and the inputs pressed, so it replays without the
files. Network matches have no CPU and aren't affected.

**What the files are.** Each is a trained opponent from the agents' training league,
packed with that character's combo library from the community's replays
(`runs/human-ayu/league_combos.py`). They have no training part. The CPU uses a file only
while it plays a combo, and the F5/F6 agent list doesn't show them. Each comes from that
character's newest exploiter (an opponent trained to beat the Ayu agent):

- `exploiter18`: exnanase, ikumi, kano, kaori, makoto, mayu, mishio, mizukab, nanase,
  nayukib, sayuri
- `exploiter`: akane, akiko, mai, minagi, mio, misaki, nayuki, shiori
- `exploiter14`: nagamori; `exploiter3`: misuzu
- Ayu has no exploiter; its file is the `reversal` opponent's.

There are no files yet for kanna, mizuka and nayuki2. Their CPU keeps its own combos.

## Downloading, and training further

```sh
hf download sakuya9t/efz agent-league20-spar-s1-round20.efzagent --local-dir agents
# or, in a checkout of the repository:
python runs/hub.py download agent-league20-spar-s1-round20       # into agents/

# back to a Stable-Baselines3 model, its config.json and its combo library:
python python/examples/unpack_agent.py agents/agent-league20-spar-s1-round20.efzagent --out work/round20
# the tools also take the file itself where they take a model:
python runs/human-ayu/finetune.py --start agents/agent-league20-spar-s1-round20.efzagent --out runs/mine ...
python python/examples/export_agent.py runs/mine/avg.zip --parts-from agents/agent-league20-spar-s1-round20.efzagent
```

Until 20 November 2026 this repository held the training runs' Stable-Baselines3
checkpoints (`runs/<run>/*.zip`, rounds 1 to 12). They were taken down then; this
repository's history keeps them (revision `f0dbd7b7`).
