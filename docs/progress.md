# Progress: human-like EFZ agents (to 7 November 2026)

Where the agent work stands, what lives where, and how to pick it up on another machine.
Since 6 November it runs on a Linux machine with an NVIDIA GPU (below, "The Linux
machine"). The plan behind it is
[training.md](training.md) ("Human-like agents"); the details and every number are in
[../runs/human-ayu/README.md](../runs/human-ayu/README.md) and
[../runs/llm-ayu/README.md](../runs/llm-ayu/README.md).

## In short

- **Ayu, cloned from people.** 1,908 in-sync sides of the community's replays; the clone
  plays at people's rates (presses, jumps, guards, 623s), with a 14-frame reaction time
  in `bc-d14`; six players' own clones (`team/`).
- **The agent** (PPO from the clone, a KL pull toward it): `agent/` → `agent-red/` (the
  lookahead red team, to 30.2M steps) → `agent-league/` (other characters' exploiters
  too, to 50.4M). It beats the level-4 CPU's ordinary characters 86% and Ayu and Mishio
  67%, but never Kanna; it beats Mizuka's exploiter 69% (from 33%), Kano's only 19%.
- **Red teams** (`combo*/`): combo masters that land the most damaging combo they can,
  and `redteam.py`, which tries people's combos on copies of the game at each hit and
  plays the best.
- **Measures** (`evaluate.py`, `tactics.py`): combos by resources, damage taken,
  pressure in frames (punishable or safe by the game's frame data), escapes, wake-up,
  free time (setups, charges), the CPU's tiers. People's numbers per character.
- **Other characters**: datasets of Mizuka, Kano, Misuzu, Mishio; Mizuka and Kano cloned,
  each with an exploiter of the agent.
- **A language-model agent** (`runs/llm-ayu`): SmolLM2-135M training on the GPU, one
  epoch (77,120 steps); at 41% of it, held-out nll 0.340, below `bc-d14`'s 0.349, press
  recall 5.4% (3%).
- **Since 6 November** (the Linux machine): round 2 and 3 exploiters, and the league
  against them: a weaker pull toward the clone (0.05) closed Kano's and Mizuka's second
  holes (`agent-league2-kl`, `agent-league3`); Kano's third exploiter still wins (people's
  own habit, jumping, farmed). The level-4 CPU's tiers explained from the source and each
  character measured; throws counted (people's and the agents'); the RF gauge's colours
  corrected (blue, red, cyan). Combo practice among matches (`--practice`) didn't help;
  built-in combos (people's routes tried on copies once the agent sees its hit,
  `--assist`) do at play time and are training.

## Where everything is

**Code.** Branch `asm-session/7d5819c6` on the Linux machine (it carries the laptop's
`asm-session/28c0039a` and what followed), ahead of `origin/main`, **not pushed**: push it
(or `git bundle`) to move it. Everything below is committed.

**The Linux machine.** RTX A3000 12 GB (a laptop GPU, 80 W, about 6 GB of it taken by other
programs), Ryzen 9 7945HX (32 threads), 92 GB. The replays' data in `~/data/efz-replays`
(`datasets/ayu`, `mizukab`, `kano`, `misuzu`, `mishio`, `players.csv`,
`combo-library.npz`; checked against the laptop's SHA256SUMS), and since 8 November all
the rest (`index.csv`, `replays/`, `archives/`, `combo-starts/`, `player_names.csv`):
every path in `index.csv` is there, replays play back as on the laptop (`dataset.py`'s
views equal but for the frame count, which the policies drop; 80 of 80 combo starts
rebuilt with the views kept). `index.csv`'s paths are Windows', split on `\` by
`dataset.py`, `combo_starts.py` and `combo.py`. EFZ_DIR: the decompilation's
`efz-unpacked/tasogare/EFZ`. `runs/llm-ayu/setup-linux.sh` worked with cmake from pip
(the host has none), after a fix: the headless library failed to load after torch
("cannot allocate memory in static TLS block"; port/guest.h now gives the static TLS
model to the arena's two pointers only). The checkpoints through round 8 are on the Hub
since 8 November (`best.zip` and `model.zip` of each run; the `chunk*.zip` only here).

**Checkpoints.** Hugging Face, https://huggingface.co/sakuya9t/efz, under the repository's
paths: `python runs/hub.py download human-ayu` puts them back into `runs/human-ayu/`
(`agent/`, `agent-red/`, `agent-league/`, `combo*/`, `team/`, `mizukab/`, `kano/`, the
clones). The `.zip` files of those folders are ignored by git; the clones `bc.zip`,
`bc-d14.zip` and `team/` are also in git.

**Data outside the repository** (on the laptop under `D:/tasogare/efz-replays`, on the
Linux machine `~/data/efz-replays`; keep the layout, the scripts find `players.csv`
beside the datasets' parent):

| What | Size | Needed for |
|---|---|---|
| `datasets/ayu`, `mizukab`, `kano`, `misuzu`, `mishio` (`dataset.py`: each side's views, inputs, rewards) | 5.6, 7.9, 9.1, 8.3, 7.3 GB | cloning (`bc.py`, `llm-ayu/train.py`), people's measures |
| `players.csv` (who played each side, as pseudonyms' numbers) | 2 MB | players' clones, the LLM's player names |
| `index.csv`, `replays/` (55,424 extracted), `archives/` (552 MB) | | new datasets (`dataset.py`), the combo starts |
| `combo-starts/` (706 starts, kept as replay and step) | 1.5 GB | `combo.py`, `macros.py` (rebuilt by playing the replays back: needs `replays/`) |
| `combo-library.npz` (people's best combos as actions) | 0.5 MB | `--lookahead` (the red team), `macros.py` |

Don't move `player_names.csv` (the players' names): it stays with the replays and out of
the repository and the Hub. The datasets carry no names.

**The game's data.** The EFZ 4.02 install (786 MB) or a compatibility pack made from it
(`tools/compatpack.py build OUT --efz DIR`, about 1 MB): `EFZ_DIR`. Each machine makes
`runs/human-ayu/framedata.json` (the frame data the pressure measures use) from it:
`python runs/human-ayu/framedata.py --data "$EFZ_DIR"` (kept out of git: game data).

## Setting up the CUDA machine

```sh
git clone https://github.com/sakuya9t/efz.git && cd efz && git checkout asm-session/28c0039a
runs/llm-ayu/setup-linux.sh --efz /data/EFZ --dataset /data/efz-replays/datasets/ayu
source .venv-llm/bin/activate
export EFZ_ENV_LIBRARY=$PWD/build/headless/libefz_env.so EFZ_DIR=/data/EFZ
hf auth login                         # for runs/hub.py: the checkpoints
python runs/hub.py download human-ayu
```

`setup-linux.sh` builds the headless library (CI builds it on Linux; it hasn't been run
on Linux here), installs CUDA torch, transformers, SB3 and the rest, checks the GPU and
the game, and writes the frame data. Not yet run on a GPU anywhere.

What the GPU changes: the language model (training and playing) needs it. The RL runs
(`finetune.py`, `combo.py`) are bound by the game's simulation on the CPU (PPO's policies
are small MLPs, trained on the CPU here, about 1,300 steps a second per job while sharing
8 cores); on a machine with more cores they go faster, and efz_env can hand observations
to CUDA directly (`env.pin_memory(torch)`, docs/headless.md) if a policy moves there.

## The runs, where they stand

| Run | What | Last result |
|---|---|---|
| `bc.zip`, `bc-d14.zip` | Ayu's clones (no reaction time; 14 frames) | held-out nll 0.344 / 0.349; `bc-d14` beats the level-1 CPU 88%, level 4 0% |
| `team/` | six players' clones (`bc.py --players`) | each predicts its player 1-3.5% better than `bc-d14`, but keeps little of their habits; 8-38% against the level-2 CPU |
| `agent/` | PPO from `bc`, to 10M | level-3 CPU 75%, the curriculum agent 91% |
| `agent-red/` | from `bc-d14`, with the red team, to 30.2M | level-4 CPU 66% (random characters), old agent 100%, red team 94% |
| `agent-league/` | from `agent-red`, with the exploiters (`--vs`, `--pfsp 2` from 38.3M), to 50.4M | on 64 matches: level-4 CPU Kanna 0%, Ayu and Mishio 67%, the rest 86%; Mizuka's exploiter 69%, Kano's 19% |
| `combo/`, `combo-red/`, `combo-red2/`, `combo-red3/` | combo masters from people's combo starts; red teams | `combo-red3` (24.2M): 1,097 / 3,064 / 4,143 (average / p90 / most) on people's resources |
| `macros/` | a learnt selector of people's combos | helps only with full resources: why `redteam.py` looks ahead instead |
| `mizukab/`, `kano/` | people's clones (`bc-d14`) and exploiters of `agent-red` at 22.2M | Mizuka's 84% after 3M steps (focus: setup), Kano's 100% after 1M (focus: charge) |
| `misuzu/`, `mishio/` | datasets made | clones not made (the cloning job was stopped when the laptop ran short of memory) |
| `runs/llm-ayu/smollm135` | SmolLM2-135M reading the game as text (prompt `statetext-2`) | training on the GPU: 52 examples/s with `--compile`, length-grouped batches and `--grad-ckpt`, an epoch ~26 h; nll 0.340 at step 32,000 |
| `mizukab/exploiter2`, `kano/exploiter2` | round 2, against `agent-league` at 50.4M | Mizuka's 81% after 6.1M, Kano's 72% after 1M; on 64 matches the agent wins 23% / 19% |
| `agent-league2`, `agent-league2-kl` | from `agent-league`, four exploiters, to 70.5M: exploiters 60% of agent matches; pull 0.05 | the pull: Kano 1 / 2 59% / 62% (from 19% / 19%), Mizuka 2 75% (23%); guards 6.2 a minute against the CPU (9.6) |
| `mizukab/exploiter3`, `kano/exploiter3` | round 3, against `agent-league2-kl` | Kano's 94% after 3M (12% on 64), Mizuka's after 9.1M |
| `agent-league3` | from `agent-league2-kl`, five exploiters, to 90.7M | Mizuka 3 78% (never met), Kano 3 still 12%; level-4 CPU 0 / 62 / 95% |
| `agent-league2-base`, `-own`, `-own10` | combo practice from its own hits, x1 and x10, against controls | no gain in matches; x10 much worse |
| `eval/cpu4-chars/` | `agent-league` against each level-4 CPU | Kanna 0%, Unknown 28%, Ayu 31% ... Mishio 94% |
| `eval/combo-support/` | built-in combos at play time on `agent-league2-kl` | lookahead: CPU's middle tier 81% (62%), Kano 2 91% (62%), combos 1,261 / 2,800 (820 / 1,646) |
| `agent-league3-assist` | `agent-league3`'s settings with `--assist` (strong but fair) | training (slow: it plans at every confirm; `--eval-every 3`) |

## What's next (7 November)

0. **Built-in combos** (`--assist`): judge `agent-league3-assist` against `agent-league3`
   (CPU tiers, the six exploiters, combos against people's) when it reaches 90.5M. Then
   people's starts for the comparison the user asked for (practice from people's starts:
   needs `combo-starts/` and `replays/` here), and Mizuka's third exploiter in the league.
1. **Kano's third exploiter** wins by people's own habit (jumping into anti-airs): decide
   with the user how far below people's jump rate the agent may go.
2. **Clone Misuzu and Mishio** (their datasets are here now), then their exploiters.
3. **The language model**: finish the epoch, play it (`evaluate.py`), then Qwen2.5-0.5B.

The list below is from 5 November:

1. **Train the language model** (`runs/llm-ayu/README.md`): SmolLM2-135M first (about
   2-3 hours an epoch on a 4090 or A100, estimated), then Qwen2.5-0.5B; compare its
   held-out numbers with `bc-d14`'s and play it with `evaluate.py`.
2. **Kano's hole.** The agent jumps 19 times a minute against her and is anti-aired (2.4
   air hits, 5.5 knockdowns a minute). Try giving the exploiters more of the matches
   (`--vs-share` above 0.4) or a weaker pull toward the clone (`--prior-coef`, 0.1 now),
   which jumps about as often; then 64-match evaluations to judge (32 swing by ±8%).
3. **More characters.** Clone Misuzu and Mishio (`bc.py --char`, one at a time: a clone
   holds about 6 GB), give Misuzu an exploiter (`--focus setup`), add both to the
   league. People's most played: Sayuri, Mayu, Nayuki (sleepy), Nanase, Akiko (5,000-11,000
   sides each); Kanna has only 232.
4. **Round 2.** New exploiters against `agent-league`, to find its next holes.
5. **Kanna** at level 4 is never beaten (her CPU is the hardest tier).
6. **Not done yet** (from the plan): focus rewards for pressure and punishing (only
   setup and charge exist, `focus.py`); the guard rate by the conversion potential of a
   hit (guarding where a big combo follows); the persona parameters as targets
   (execution rates: RG, RC, punishes, 623 guesses; for Rumi, `nanase`, the home-run rate).

## Resuming each run

Every script takes `--data "$EFZ_DIR"`; `$REPLAYS` is the replays' folder (the laptop's `D:/tasogare/efz-replays`, the Linux machine's `~/data/efz-replays`).

```sh
# The league run: continues from runs/human-ayu/agent-league/finetune.json (raise --budget)
python runs/human-ayu/finetune.py --out runs/human-ayu/agent-league --start runs/human-ayu/agent-red/model.zip \
    --prior runs/human-ayu/bc-d14.zip --delay 14 --team runs/human-ayu/team/player{473,596,208,639,143,479}.zip \
    --combo runs/human-ayu/combo-red3/combo.zip --lookahead $REPLAYS/combo-library.npz \
    --vs runs/human-ayu/mizukab/exploiter/model.zip:mizukab runs/human-ayu/kano/exploiter/model.zip:kano \
    --vs-share 0.4 --pfsp 2 --level 4 --chunk 2e6 --budget 7e7 --eval 32 --torch-threads 10

# An exploiter (a clone first: dataset.py --char X, then bc.py --char X --delay 14 --name bc-d14 --out runs/human-ayu/X)
python runs/human-ayu/finetune.py --char misuzu --start runs/human-ayu/misuzu/bc-d14.zip \
    --prior runs/human-ayu/misuzu/bc-d14.zip --delay 14 --out runs/human-ayu/misuzu/exploiter \
    --vs runs/human-ayu/agent-league/model.zip:ayu --vs-share 1 --cpu-share 0.25 --level 3 \
    --focus setup --chunk 1e6 --budget 1e7 --eval 32 --stop-win 0.6

# Measures and matches
python runs/human-ayu/people.py --dataset $REPLAYS/datasets/kano --char kano --out runs/human-ayu/kano/people.json
python runs/human-ayu/evaluate.py --p1 runs/human-ayu/agent-league/model.zip --p2 cpu --level 4 --chars ayu tiers --matches 63
python python/examples/record_replay.py --p1 A.zip --p2 B.zip --chars ayu kano --slot 2-1
```

`dataset.py` continues where it stopped (its `matches.csv`); `combo.py --resume`
continues a combo master.

## Lessons kept

- Don't edit a module a running job will import later: a clone was lost when its save
  imported a half-patched package.
- Save states belong to the process that made them (`efz_env` refuses others'): starts
  are kept as a replay and a step, and rebuilt by playback.
- Thinning the data needs weights (1 / the share kept), or the clone presses and turns
  that many times too often.
- 32-match evaluations swing by ±8%; decide on 64 or more, on the same seeds.
- A clone loads its whole dataset: about 6 GB for 2,600 sides.
- People's combos are best compared from the hit after the first; combo damage needs
  its maximum and 90th percentile, not only the average, and its resources.
- An EfzVecEnv's save folder is the process's: making another environment (a planner's)
  sets it back to the game's, so replays recorded after went among the game's.
- Practice among matches at the match's reward scale is too weak against the pull
  toward the clone; at ten times it distorts the match. Built-in routes (tried on copies,
  out of the policy's loss) worked where learning didn't.
- An agent that plans in every evaluated match makes evaluations the slow part: evaluate
  every few chunks.
