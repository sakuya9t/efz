# A language model that plays Ayu

A small pretrained language model, fine-tuned to read the game as text and answer with
an action, trained on the same people's matches as the MLP clone
([../human-ayu](../human-ayu/README.md), `bc.py`) and measured the same way, so the two
compare. Meant for a Linux machine with an NVIDIA GPU; it runs on a CPU only for a
smoke test.

| File | What |
|---|---|
| `statetext.py` | The view as text (`prompt()`), the moves and inputs a prompt carries (`Context`, the same in training and play) |
| `llm.py` | `LLMPolicy` (the LM's body and a head over the 45 actions) and `LLMAgent` (plays as `efz_env.agent.Agent`) |
| `train.py` | Behavioural cloning from the replays' dataset |
| `setup-linux.sh` | Builds the headless library, makes the Python environment, checks the GPU and the game |
| `requirements.txt` | The packages |

## How it works

**The prompt.** What the agent sees at a step (as `bc-d14`: the game 14 steps late,
a reaction time, and its own inputs at once), about 200 tokens:

```
Ayu (player 473) vs Nagamori. Round 2, rounds 1-0.
Me: HP 37% power 2.4 RF 63 cyan guard 29%. x 325 y 0. Doing m204 frame 2, hitstop 19.
Opponent: HP 77% power 0.7 RF 51 cyan guard 0%. x 287 y 0, moving -1 0. Doing guard frame 0, guarding, throw-protected, hitstop 19.
Opponent 37 px ahead, level.
Objects: mine none; theirs 299,-43.
Before: me m208 land crouch-down crouch; opponent knockdown lying wake-up recoil-guard.
My inputs: 1 1A 1x7 4 5x6
Action:
```

Common actions by name (from `src/efz.h`), a character's own moves as `m<number>`;
the players' last four moves; its last 16 steps of input, run-length coded in numpad
notation. The player is named by the replays' pseudonym when they have 20 or more
matches, else `?` (and `?` in a fifth of the training prompts), so one model plays
everyone or someone: `LLMAgent(..., player='473')`.

**The answer.** One of the 45 actions (9 directions × none/A/B/C/D: `5`, `2A`...). The
head over them starts as the LM's own output embeddings of their names, so the model
begins as its next-token choice restricted to those names, and one forward pass gives
all 45 logits (no decoding loop). Trained with the cross-entropy of people's actions,
the steps thinned and weighted as `bc.py`'s (every press and turn, a quarter of the
rest at weight 4), held-out replays the same (every tenth by id).

**Measured as the clone is.** `train.py` reports `bc.py`'s held-out measures (nll,
action, direction, press recall and precision; `bc-d14`: nll 0.349, action 0.914,
press recall 0.03), and `runs/human-ayu/evaluate.py` plays a model folder as it plays
a `.zip`, with every behaviour measure (presses, RG, combos, damage taken, pressure,
wake-up, free time) against the CPU (`--chars ayu tiers` at level 4: Kanna, Ayu and
Mishio, the rest) or another agent.

## On the Linux machine

What to copy there (none of it is in the repository):

- the game's data: the EFZ 4.02 install (786 MB), or a compatibility pack made from it,
  about 1 MB: `tools/compatpack.py build efz-pack --efz D:/tasogare/EFZ`;
- the dataset: `D:/tasogare/efz-replays/datasets/ayu` (5.6 GB, `runs/human-ayu/dataset.py`'s)
  and `D:/tasogare/efz-replays/players.csv` beside its parent, keeping the layout
  (`efz-replays/datasets/ayu`, `efz-replays/players.csv`).

Then:

```sh
runs/llm-ayu/setup-linux.sh --efz /data/EFZ --dataset /data/efz-replays/datasets/ayu
source .venv-llm/bin/activate
export EFZ_ENV_LIBRARY=$PWD/build/headless/libefz_env.so EFZ_DIR=/data/EFZ

# SmolLM2-135M, full fine-tuning, an epoch (4.9M examples)
python runs/llm-ayu/train.py --dataset /data/efz-replays/datasets/ayu --out runs/llm-ayu/smollm135

# bigger: Qwen2.5-0.5B; or 1.5B with LoRA and gradient checkpointing
python runs/llm-ayu/train.py --dataset ... --out runs/llm-ayu/qwen05 --base Qwen/Qwen2.5-0.5B --batch 32 --accum 2
python runs/llm-ayu/train.py --dataset ... --out runs/llm-ayu/qwen15-lora --base Qwen/Qwen2.5-1.5B --lora 32 --grad-ckpt

# playing it
python runs/human-ayu/evaluate.py --p1 runs/llm-ayu/smollm135 --p2 cpu --level 4 --chars ayu tiers --matches 48
python runs/human-ayu/evaluate.py --p1 runs/llm-ayu/smollm135 --p2 runs/human-ayu/bc-d14.zip --chars ayu ayu

# the model to the Hub (runs/hub.py: body/, head.pt, llm.json)
python runs/hub.py upload llm-ayu
```

`setup-linux.sh` also writes `runs/human-ayu/framedata.json` from the game's data
(the frame data the pressure measures use; kept out of the repository).

**Costs, estimated (not yet measured on a GPU).** A training example is about 200
tokens: SmolLM2-135M takes about 170 GFLOP to learn from one, an epoch about 8 × 10^17,
so 2–3 hours on an RTX 4090 or A100 at a realistic utilisation; Qwen2.5-0.5B about four
times that. Playing, a decision is one forward pass of the prompt: 64 matches of 5
minutes (1.2 million decisions) are some 15–30 minutes for the 135M model. On this
laptop's CPU, with the RL jobs running, it trained at 1 example a second and played 3
decisions a second: the smoke test only.

## Status

Built and smoke-tested on the Windows laptop's CPU (2026-11-05): 12 matches, 30 steps
of SmolLM2-135M, saved, loaded and played against the CPU by `evaluate.py`; the prompts
built in training and in play are the same at every step of a match (checked). Not yet
trained for real.
