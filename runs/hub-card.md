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
