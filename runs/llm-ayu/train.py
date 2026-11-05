"""Behavioural cloning of people's Ayu with a language model: it reads each step of
people's matches as text (statetext.py) and learns the action the player took.

    python runs/llm-ayu/train.py --dataset /data/efz-replays/datasets/ayu --out runs/llm-ayu/smollm
    python runs/llm-ayu/train.py ... --base Qwen/Qwen2.5-0.5B --batch 32 --accum 2
    python runs/llm-ayu/train.py ... --base Qwen/Qwen2.5-1.5B --lora 32 --grad-ckpt

The data is runs/human-ayu/dataset.py's (the community's replays played back), the same
as bc.py's, split the same way (every tenth replay by id held out) and thinned the same
way (every step where a button goes down or the direction changes, and --keep of the
rest, weighing 1 / --keep), so the two clones' held-out numbers compare: nll, action,
direction, press_recall, press_precision (bc.py's evaluate). The model (llm.LLMPolicy) is
--base's body with a head over the 45 actions, started from the LM's embeddings of their
names; full fine-tuning, or with --lora R, LoRA adapters of rank R on the body (the head
trained in full). It sees the game --delay steps late (a reaction time, 14 as
bc-d14) and its own inputs at once. A prompt names the player (players.csv, beside the
replays: the pseudonyms' numbers) when the player has --min-matches matches in the
training split, else '?', and '?' in --player-drop of the training prompts, so that one
model plays everyone ('?') or someone.

--out gets the best model by held-out nll (body/, head.pt, llm.json: its settings, and
the evaluations), and train.log. Needs torch, transformers and (for --lora) peft; meant
for a CUDA machine (README.md), and runs on a CPU for a smoke test (--limit, --max-steps).
"""

import argparse
import csv
import json
import math
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)
os.environ.setdefault('TOKENIZERS_PARALLELISM', 'false')

import numpy as np
import torch as th

import statetext as st
from efz_env.history import action_labels
from llm import LLMPolicy, device_default

FORMAT = 'statetext-1'


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--dataset', required=True, help="dataset.py's folder (matches.csv, <id>-<side>.npz)")
    p.add_argument('--players', help="players.csv (default: beside the dataset's replays)")
    p.add_argument('--out', default=os.path.join(HERE, 'model'))
    p.add_argument('--base', default='HuggingFaceTB/SmolLM2-135M', help='a causal LM on the Hub, or a folder')
    p.add_argument('--delay', type=int, default=14)
    p.add_argument('--history', type=int, default=16, help='steps of its own inputs in a prompt')
    p.add_argument('--moves', type=int, default=4, help="each player's moves before the current")
    p.add_argument('--keep', type=float, default=0.25)
    p.add_argument('--min-matches', type=int, default=20)
    p.add_argument('--player-drop', type=float, default=0.2)
    p.add_argument('--epochs', type=float, default=1.0)
    p.add_argument('--max-steps', type=int, default=0, help='optimizer steps at most (0: --epochs)')
    p.add_argument('--batch', type=int, default=64)
    p.add_argument('--accum', type=int, default=1, help='batches per optimizer step')
    p.add_argument('--lr', type=float, default=None, help='default 1e-4, 2e-4 with --lora')
    p.add_argument('--warmup', type=int, default=500)
    p.add_argument('--weight-decay', type=float, default=0.01)
    p.add_argument('--lora', type=int, default=0, help='LoRA rank (0: full fine-tuning)')
    p.add_argument('--grad-ckpt', action='store_true', help='gradient checkpointing (less memory)')
    p.add_argument('--max-len', type=int, default=320)
    p.add_argument('--val-steps', type=int, default=50000, help='held-out steps evaluated')
    p.add_argument('--eval-every', type=int, default=2000, help='optimizer steps')
    p.add_argument('--limit', type=int, default=0, help='at most this many matches (0 all)')
    p.add_argument('--workers', type=int, default=4)
    p.add_argument('--device', default=None)
    p.add_argument('--seed', type=int, default=0)
    return p.parse_args()


def load(args):
    rows = [r for r in csv.DictReader(open(os.path.join(args.dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    if args.limit:
        rows = rows[:args.limit]
    who_path = args.players or os.path.join(os.path.dirname(os.path.dirname(
        os.path.abspath(args.dataset))), 'players.csv')
    who = {}
    if os.path.exists(who_path):
        for r in csv.DictReader(open(who_path, encoding='utf-8')):
            who[(r['id'], r['side'])] = r['player']
    train_rows = [r for r in rows if int(r['id']) % 10 != 0]
    counts = {}
    for r in train_rows:
        pl = who.get((r['id'], r['side']))
        if pl is not None:
            counts[pl] = counts.get(pl, 0) + 1
    named = sorted((p for p, n in counts.items() if n >= args.min_matches), key=int)
    rng = np.random.default_rng(args.seed)
    matches = []  # (obs, acts as seen, labels, player)
    index = {'train': [], 'val': [], 'w': []}
    for r in rows:
        with np.load(os.path.join(args.dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inp = z['obs'], z['input']
        y = action_labels(inp)
        T = len(y)
        seen_idx = np.maximum(np.arange(T) - args.delay, 0)
        acts = np.round(obs[seen_idx][:, [st.SELF + st.ACT, st.OPP + st.ACT]].astype(np.float32)).astype(np.int16)
        pl = who.get((r['id'], r['side']))
        m = len(matches)
        matches.append((obs, acts, y.astype(np.int8), pl if pl in named else '?'))
        if int(r['id']) % 10 == 0:
            index['val'].append(np.stack([np.full(T, m), np.arange(T)], 1))
        else:
            d = y % 9
            change = np.concatenate([[True], d[1:] != d[:-1]]) | (y >= 9)
            keep = change | (rng.random(T) < args.keep)
            t = np.flatnonzero(keep)
            index['train'].append(np.stack([np.full(len(t), m), t], 1))
            index['w'].append(np.where(change[t], 1.0, 1.0 / args.keep))
    out = {k: np.concatenate(v) if v else np.zeros((0, 2) if k != 'w' else 0)
           for k, v in index.items()}
    if len(out['val']) > args.val_steps:
        out['val'] = out['val'][np.sort(rng.choice(len(out['val']), args.val_steps, replace=False))]
    return matches, out, named, len(rows)


class Steps(th.utils.data.Dataset):
    """The examples: (prompt, action, weight)."""

    def __init__(self, matches, index, weights, args, drop=0.0):
        self.matches, self.index, self.weights = matches, index, weights
        self.delay, self.moves, self.history, self.drop = args.delay, args.moves, args.history, drop
        self.ctx = {}

    def __len__(self):
        return len(self.index)

    def __getitem__(self, k):
        m, t = (int(x) for x in self.index[k])
        obs, acts, y, player = self.matches[m]
        at = self.ctx.get(m)
        if at is None:  # (per worker: its own cache)
            at = self.ctx[m] = st.match_context(acts, y, self.moves, self.history)
        if self.drop and np.random.random() < self.drop:
            player = '?'
        view = obs[max(0, t - self.delay)].astype(np.float32)
        mine, theirs, inputs = at(t)
        w = float(self.weights[k]) if self.weights is not None else 1.0
        return st.prompt(view, mine, theirs, inputs, player), int(y[t]), w


def collate(tokenizer, max_len):
    def fn(items):
        texts, y, w = zip(*items)
        b = tokenizer(list(texts), padding=True, truncation=True, max_length=max_len,
                      return_tensors='pt')
        return b['input_ids'], b['attention_mask'], th.tensor(y), th.tensor(w, dtype=th.float32)
    return fn


def loader(ds, args, tokenizer, shuffle, batch):
    return th.utils.data.DataLoader(
        ds, batch_size=batch, shuffle=shuffle, num_workers=args.workers,
        collate_fn=collate(tokenizer, args.max_len), pin_memory=th.cuda.is_available(),
        persistent_workers=args.workers > 0, drop_last=shuffle,
        worker_init_fn=lambda i: np.random.seed((args.seed * 1000 + i) % 2 ** 32))


def autocast(device):
    if device.startswith('cuda'):
        return th.autocast('cuda', dtype=th.bfloat16)
    return th.autocast('cpu', enabled=False)


@th.no_grad()
def evaluate(policy, dl, device):
    """bc.py's measures on the held-out steps."""
    policy.eval()
    nll, hit, hit_dir, n, pred_press, true_press, both = 0.0, 0, 0, 0, 0, 0, 0
    for ids, mask, y, _ in dl:
        ids, mask, y = ids.to(device), mask.to(device), y.to(device)
        with autocast(device):
            logits = policy(ids, mask)
        logp = th.log_softmax(logits.float(), 1)
        nll += float(th.nn.functional.nll_loss(logp, y, reduction='sum'))
        p = logp.argmax(1)
        hit += int((p == y).sum())
        hit_dir += int((p % 9 == y % 9).sum())
        pp, tp = p >= 9, y >= 9
        pred_press += int(pp.sum())
        true_press += int(tp.sum())
        both += int((pp & tp & (p // 9 == y // 9)).sum())
        n += len(y)
    policy.train()
    return dict(nll=nll / n, action=hit / n, direction=hit_dir / n,
                press_recall=both / max(1, true_press), press_precision=both / max(1, pred_press),
                presses=true_press / n)


def main():
    args = parse()
    device = args.device or device_default()
    th.manual_seed(args.seed)
    np.random.seed(args.seed)
    lr = args.lr or (2e-4 if args.lora else 1e-4)
    os.makedirs(args.out, exist_ok=True)
    log = open(os.path.join(args.out, 'train.log'), 'a', encoding='utf-8')

    def say(*parts):
        line = ' '.join(str(p) for p in parts)
        print(line, flush=True)
        log.write(line + '\n')
        log.flush()

    t0 = time.time()
    matches, index, named, n_rows = load(args)
    say(f'{n_rows} matches: {len(index["train"]):,} training steps, {len(index["val"]):,} '
        f'held out evaluated; {len(named)} players named ({time.time() - t0:.0f}s)')

    policy = LLMPolicy.pretrained(args.base)
    if args.grad_ckpt:
        policy.body.gradient_checkpointing_enable()
    if args.lora:
        from peft import LoraConfig, get_peft_model
        cfg = LoraConfig(r=args.lora, lora_alpha=2 * args.lora, lora_dropout=0.05,
                         target_modules=['q_proj', 'k_proj', 'v_proj', 'o_proj',
                                         'gate_proj', 'up_proj', 'down_proj'])
        policy.body = get_peft_model(policy.body, cfg)
    policy.to(device).train()
    params = [p for p in policy.parameters() if p.requires_grad]
    say(f'{args.base}: {sum(p.numel() for p in policy.parameters()) / 1e6:.0f}M parameters, '
        f'{sum(p.numel() for p in params) / 1e6:.1f}M trained, on {device}')

    tok = policy.tokenizer
    train = Steps(matches, index['train'], index['w'], args, drop=args.player_drop)
    val = Steps(matches, index['val'], None, args)
    dl = loader(train, args, tok, True, args.batch)
    vdl = loader(val, args, tok, False, args.batch * 2)
    per_epoch = len(dl) // args.accum
    total = args.max_steps or max(1, int(per_epoch * args.epochs))
    opt = th.optim.AdamW(params, lr=lr, weight_decay=args.weight_decay, betas=(0.9, 0.95))

    def schedule(step):  # warmup, then cosine to a tenth
        if step < args.warmup:
            return (step + 1) / args.warmup
        q = (step - args.warmup) / max(1, total - args.warmup)
        return 0.1 + 0.9 * 0.5 * (1 + math.cos(math.pi * min(1.0, q)))
    sched = th.optim.lr_scheduler.LambdaLR(opt, schedule)
    config = dict(format=FORMAT, base=args.base, delay=args.delay, history=args.history,
                  moves=args.moves, max_len=args.max_len, players=named, args=vars(args))
    history, best = [], None

    def checkpoint(step):
        nonlocal best
        ev = evaluate(policy, vdl, device)
        ev.update(step=step, examples=step * args.batch * args.accum,
                  seconds=round(time.time() - t0))
        history.append(ev)
        say('eval', json.dumps(ev))
        if best is None or ev['nll'] < best['nll']:
            best = ev
            policy.save(args.out, dict(config, eval=ev, evals=history))
            say('  saved (best held-out nll)')
        with open(os.path.join(args.out, 'history.json'), 'w') as f:
            json.dump(history, f, indent=1)

    say(f'{total} optimizer steps ({per_epoch} an epoch), lr {lr}')
    step, seen_tokens, t_log = 0, 0, time.time()
    run_loss, run_n = 0.0, 0
    while step < total:
        for k, (ids, mask, y, w) in enumerate(dl):
            ids, mask, y, w = ids.to(device), mask.to(device), y.to(device), w.to(device)
            with autocast(device):
                logits = policy(ids, mask)
            nll = th.nn.functional.cross_entropy(logits.float(), y, reduction='none')
            loss = (nll * w).sum() / w.sum()
            (loss / args.accum).backward()
            run_loss += float(loss.detach())
            run_n += 1
            seen_tokens += int(mask.sum())
            if (k + 1) % args.accum:
                continue
            th.nn.utils.clip_grad_norm_(params, 1.0)
            opt.step()
            sched.step()
            opt.zero_grad(set_to_none=True)
            step += 1
            if step % 50 == 0 or step == total:
                dt = time.time() - t_log
                say(f'step {step}/{total} loss {run_loss / run_n:.4f} lr {sched.get_last_lr()[0]:.2e} '
                    f'{50 * args.batch * args.accum / dt:.0f} examples/s {seen_tokens / dt:.0f} tokens/s')
                t_log, seen_tokens, run_loss, run_n = time.time(), 0, 0.0, 0
            if step % args.eval_every == 0 or step == total:
                checkpoint(step)
            if step >= total:
                break
    say(f'done in {time.time() - t0:.0f}s; best held-out', json.dumps(best))


if __name__ == '__main__':
    main()
