"""Behavioural cloning of people's Ayu: a policy acting every frame, trained to input
what the players input, from the data dataset.py made of the community's replays.

    python runs/human-ayu/bc.py --dataset D:/tasogare/efz-replays/datasets/ayu

The policy (efz_env.policy.EfzPolicy) sees the 168 features and the last --history
steps of its own inputs (efz_env.history), and picks one of the 45 actions (9
directions x none/A/B/C/D) each frame: the label of a step is its direction, and the
button that went down on it (efz_env.history.action_labels). Its critic learns the
discounted return of the matches as they went (people's play, so a start for PPO's).

Every tenth replay (by id) is held out: the log says how well the inputs there are
predicted (the direction, and the presses found among the steps that have one); the
epoch that predicts them best is kept. Steps are thinned for training: every step where
a button goes down or the direction changes, and --keep of the rest, each of those
weighing 1 / --keep in the loss (unweighted, the thinning would make the clone press
and turn as many times more often as the rest was thinned). With --delay the
policy sees the game that many steps late (a reaction time), its inputs at once. --out
gets <name>.zip (a PPO model whose policy is the clone: examples/play.py,
record_replay.py and finetune.py load it), <name>.json (the evaluations) and its
settings (config.json, or <name>.config.json).

Another character: --char (its dataset: dataset.py --char), Ayu by default.

A player's clone: --players (numbers of the replays' players.csv, the pseudonyms kept
beside the replays) learns from those players' matches alone, best started from the
clone of everyone (--init bc.zip) at a lower --lr for an epoch or two: the game from
everyone, the habits from them.
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

import numpy as np
import torch as th
from gymnasium import spaces

from efz_env import ActionTable
from efz_env.history import action_labels, delayed, history_features
from efz_env.policy import EfzPolicy, policy_kwargs

from evaluate import COLUMNS, Events

TABLE = ActionTable()


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--dataset', required=True)
    p.add_argument('--char', default='ayu', help="the dataset's character")
    p.add_argument('--out', default=HERE)
    p.add_argument('--history', type=int, default=16, help='steps of own inputs seen')
    p.add_argument('--delay', type=int, default=0,
                   help='steps late the game is seen (a reaction time; 0 none)')
    p.add_argument('--name', default='bc', help='the model is OUT/<name>.zip')
    p.add_argument('--keep', type=float, default=0.25,
                   help='share of the steps without a change kept for training')
    p.add_argument('--epochs', type=int, default=4)
    p.add_argument('--batch', type=int, default=4096)
    p.add_argument('--lr', type=float, default=1e-3)
    p.add_argument('--gamma', type=float, default=0.999)
    p.add_argument('--width', type=int, default=512)
    p.add_argument('--vf-coef', type=float, default=0.5)
    p.add_argument('--limit', type=int, default=0, help='at most this many matches (0 all)')
    p.add_argument('--players', help="only these players' sides: numbers, comma-separated")
    p.add_argument('--who', help="players.csv (default: beside the dataset's replays)")
    p.add_argument('--init', help='a clone (.zip) to start from')
    p.add_argument('--torch-threads', type=int, default=12)
    return p.parse_args()


def returns(reward, gamma):
    out = np.zeros(len(reward), np.float32)
    g = 0.0
    for t in range(len(reward) - 1, -1, -1):
        g = reward[t] + gamma * g
        out[t] = g
    return out


def load(args):
    rows = [r for r in csv.DictReader(open(os.path.join(args.dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    if args.players:
        who = args.who or os.path.join(os.path.dirname(os.path.dirname(
            os.path.abspath(args.dataset))), 'players.csv')
        mine = set(args.players.split(','))
        sides = {(r['id'], r['side']) for r in csv.DictReader(open(who, encoding='utf-8'))
                 if r['player'] in mine}
        rows = [r for r in rows if (r['id'], r['side']) in sides]
    if args.limit:
        rows = rows[:args.limit]
    rng = np.random.default_rng(0)
    parts = {'train': [], 'val': []}
    people = Events(args.char)  # how people played, in the held-out matches
    for r in rows:
        with np.load(os.path.join(args.dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inp, rew = z['obs'], z['input'], z['reward']
        hist = history_features(inp, args.history).astype(np.float16)
        seen = delayed(obs, args.delay) if args.delay else obs
        y = action_labels(inp, TABLE)
        g = returns(rew, args.gamma)
        split = 'val' if int(r['id']) % 10 == 0 else 'train'
        if split == 'val':
            people.add_match(obs[:, COLUMNS], inp)
        if split == 'train':
            d = (y % 9)  # direction (numpad - 1)
            change = np.concatenate([[True], d[1:] != d[:-1]]) | (y >= 9)
            keep = change | (rng.random(len(y)) < args.keep)
            w = np.where(change, 1.0, 1.0 / args.keep).astype(np.float32)[keep]
            seen, hist, y, g = seen[keep], hist[keep], y[keep], g[keep]
        else:
            w = np.ones(len(y), np.float32)
        parts[split].append((np.concatenate([seen, hist], 1), y.astype(np.int16), g, w))
    out = {}
    for split, items in parts.items():
        out[split] = tuple(np.concatenate([it[k] for it in items]) for k in range(4))
    return out, len(rows), people.report()


def evaluate(policy, data, batch=16384):
    x, y = data[:2]
    policy.set_training_mode(False)
    nll, hit_dir, hit, n = 0.0, 0, 0, 0
    pred_press, true_press, both = 0, 0, 0
    with th.no_grad():
        for i in range(0, len(x), batch):
            xb = th.as_tensor(x[i:i + batch].astype(np.float32))
            yb = th.as_tensor(y[i:i + batch].astype(np.int64))
            logp = policy.logits(xb)
            nll += float(th.nn.functional.nll_loss(logp, yb, reduction='sum'))
            p = logp.argmax(1)
            hit += int((p == yb).sum())
            hit_dir += int((p % 9 == yb % 9).sum())
            pp, tp = p >= 9, yb >= 9
            pred_press += int(pp.sum())
            true_press += int(tp.sum())
            both += int((pp & tp & (p // 9 == yb // 9)).sum())
            n += len(yb)
    return dict(nll=nll / n, action=hit / n, direction=hit_dir / n,
                press_recall=both / max(1, true_press), press_precision=both / max(1, pred_press),
                presses=true_press / n)


def main():
    args = parse()
    th.set_num_threads(args.torch_threads)
    t0 = time.time()
    data, matches, people = load(args)
    print('people (held out):', json.dumps(people), flush=True)
    xt, yt, gt, wt = data['train']
    print(f"{matches} matches: {len(yt):,} training steps, {len(data['val'][1]):,} held out "
          f"({time.time() - t0:.0f}s)", flush=True)
    sample = xt[np.random.default_rng(1).choice(len(xt), min(len(xt), 500_000), replace=False)]
    sample = sample.astype(np.float32)
    mean, std = sample.mean(0), sample.std(0)

    obs_space = spaces.Box(-np.inf, np.inf, (xt.shape[1],), np.float32)
    kwargs = policy_kwargs(width=args.width)
    policy = EfzPolicy(obs_space, spaces.Discrete(len(TABLE)), lambda _: args.lr, **kwargs)
    policy.set_scale(mean, std)
    if args.init:  # its scale too: the features as the clone it starts from saw them
        from stable_baselines3 import PPO
        policy.load_state_dict(PPO.load(args.init, device='cpu').policy.state_dict())
        print('starting from', args.init, flush=True)
    opt = th.optim.AdamW(policy.parameters(), lr=args.lr, weight_decay=1e-5)
    steps_per_epoch = math.ceil(len(yt) / args.batch)
    total = steps_per_epoch * args.epochs
    sched = th.optim.lr_scheduler.LambdaLR(
        opt, lambda s: min(1.0, s / 500) * 0.5 * (1 + math.cos(math.pi * min(1.0, s / total))))
    history = []
    best, best_state = float('inf'), None
    rng = np.random.default_rng(2)
    for epoch in range(args.epochs):
        policy.set_training_mode(True)
        perm = rng.permutation(len(yt))
        start, seen, loss_pi, loss_vf = time.time(), 0, 0.0, 0.0
        for k in range(steps_per_epoch):
            idx = np.sort(perm[k * args.batch:(k + 1) * args.batch])
            xb = th.as_tensor(xt[idx].astype(np.float32))
            yb = th.as_tensor(yt[idx].astype(np.int64))
            gb = th.as_tensor(gt[idx])
            wb = th.as_tensor(wt[idx])
            logp = policy.logits(xb)
            lp = (th.nn.functional.nll_loss(logp, yb, reduction='none') * wb).sum() / wb.sum()
            lv = (((policy.predict_values(xb).squeeze(1) - gb) ** 2) * wb).sum() / wb.sum()
            loss = lp + args.vf_coef * lv
            opt.zero_grad()
            loss.backward()
            th.nn.utils.clip_grad_norm_(policy.parameters(), 1.0)
            opt.step()
            sched.step()
            loss_pi += lp.item() * len(idx)
            loss_vf += lv.item() * len(idx)
            seen += len(idx)
            if k % 500 == 0:
                print(f'  epoch {epoch} batch {k}/{steps_per_epoch}: nll {lp.item():.3f} '
                      f'value {lv.item():.4f}', flush=True)
        ev = evaluate(policy, data['val'])
        ev.update(epoch=epoch, train_nll=loss_pi / seen, train_value=loss_vf / seen,
                  seconds=time.time() - start)
        history.append(ev)
        print(json.dumps(ev), flush=True)
        if ev['nll'] < best:
            best = ev['nll']
            best_state = {k: v.detach().clone() for k, v in policy.state_dict().items()}
    policy.load_state_dict(best_state)
    print(f'kept the epoch with held-out nll {best:.4f}', flush=True)

    # As an SB3 model, for what loads one.
    from stable_baselines3 import PPO
    from efz_env.sb3 import EfzSB3VecEnv
    venv = EfzSB3VecEnv(args.data, 1, frame_skip=1, history=args.history, chars=(args.char, None))
    model = PPO(EfzPolicy, venv, policy_kwargs=kwargs, device='cpu', verbose=0)
    model.policy.load_state_dict(policy.state_dict())
    model.save(os.path.join(args.out, f'{args.name}.zip'))
    venv.close()
    with open(os.path.join(args.out, f'{args.name}.json'), 'w') as f:
        json.dump(dict(args=vars(args), matches=matches, people=people, train_steps=int(len(yt)),
                       val_steps=int(len(data['val'][1])), epochs=history), f, indent=1)
    config = os.path.join(args.out, 'config.json')
    if args.name != 'bc':
        config = os.path.join(args.out, f'{args.name}.config.json')
    with open(config, 'w') as f:
        json.dump(dict(frame_skip=1, history=args.history, delay=args.delay, chars=[args.char, None],
                       actions=[TABLE.describe(i) for i in range(len(TABLE))]), f, indent=1)
    print(f'done in {time.time() - t0:.0f}s')


if __name__ == '__main__':
    main()
