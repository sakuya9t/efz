# Trained agents

The first agents trained on `efz_env` ([docs/headless.md](../docs/headless.md)), 3-4
November 2026, on a Ryzen 7 6800U laptop (PyTorch on the CPU). Each `.zip` is a
Stable-Baselines3 PPO model: an MLP (256, 256) over the library's 168 observations,
choosing among the default `ActionTable`'s 45 actions (nine directions, with no button or
one of A-D) every 4 frames. **All of them know only Ayu against Ayu** (random stages):
they were never shown another character.

| Run | What | Made by | Result |
|---|---|---|---|
| [`curriculum/`](curriculum/) | The best: `model.zip` | `curriculum/curriculum.py`, from `pbt/best.zip`: 2 chunks of 2M steps (10 minutes), the CPU's level raised as it won | On full matches (64 each, cut at 5 minutes) against the CPU it wins 100% at level 2, 94% at level 3, 77% at level 4 |
| [`pbt/`](pbt/) | `best.zip`, the best of a population | `python/examples/pbt.py --population 4 --generations 4 --steps 1e5 --envs 64 --chars ayu ayu` (16 minutes) | Rated 1345 with the level-2 CPU at 1000; wins 84% of full matches against it |
| [`vs-cpu/`](vs-cpu/) | `model.zip`, the first run | `python/examples/train.py --opponent cpu --chars ayu ayu --cpu-level 2 --steps 1.5e6 --max-frames 7680` (3.5 minutes) | Against the level-2 CPU in 2-minute matches: 5% won, none lost, the rest timed out; mean return +0.60 (random play: -0.16) |

How the best plays: it lands its own moves (about 60% of the time in one) and uses all
four buttons, but it never blocks (0% of the time guarding) and spends about a third of
the time in the air. The game's CPU doesn't punish that; people will. Making it play more
like a person is the plan in [docs/training.md](../docs/training.md), "Human-like
agents".

## Using them

```sh
# Play the best yourself (you are player 2: arrows, Z X C V = A B C D, or a gamepad):
python python/examples/play.py --data "$EFZ_DIR" --agent runs/curriculum/model.zip --chars ayu ayu
# Record two of them into a replay slot, which EFZ's REPLAY menu plays (page 1, slot 1):
python python/examples/record_replay.py --data "$EFZ_DIR" --p1 runs/curriculum/model.zip --p2 runs/pbt/best.zip --slot 1-1
# Train the best further (continues runs/curriculum), or a run of your own from it:
python runs/curriculum/curriculum.py --data "$EFZ_DIR"
python runs/curriculum/curriculum.py --data "$EFZ_DIR" --out runs/mine
```

## What each folder holds

- `curriculum/`: `model.zip`; `curriculum.py`, the script that trained it (each chunk
  three quarters against the CPU, a quarter against a frozen copy of itself, then an
  evaluation at the current level and the next); `curriculum.json`, every evaluation
  (wins, losses, damage dealt and taken, time in the air, guarding, its own moves, the
  buttons it chose); `config.json`, read by `play.py` and `record_replay.py`;
  `train.log`. The script fixes one thing of the run's: its stop test looked at the
  level-3 evaluation where the level-4 one was meant (that one, 77%, passed anyway).
- `pbt/`: `best.zip` (member m03 after 4 generations), `log.jsonl` (each generation's
  ratings, scores against each other and the CPU, settings, replacements),
  `state.json`, `config.json`, `train.log`. The run's other members and archive aren't
  kept, so `pbt.py` can't continue it from here. Each member's turns were too short for
  its matches to end (100,000 steps over 64 matches), so only damage taught them;
  `pbt.py` now warns of that.
- `vs-cpu/`: `model.zip`, `config.json` (`train.py`'s settings), `train.log` (SB3's
  tables).
