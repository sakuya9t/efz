"""Built-in combos for the red team, as the 2012 Reimu AI had its combos: people's most
damaging Ayu combos (combo_library.py) played as they were, the one to play chosen by a
selector learnt from trials.

    python runs/human-ayu/macros.py --red runs/human-ayu/combo-red/combo.zip

A recorded combo played blindly from another start mostly drops (6% of them make 80% of
their damage there: the spacing, the corner, the opponent differ), but the right one for
the situation makes about twice what the red team makes alone. So: each library combo is
a sequence of the agent's actions (efz_env.history.action_labels of its inputs: their
directions and the buttons going down), and the selector predicts, from the situation
(the attacker's view at the first hit, its resources: evaluate.resources) and a combo's
description (its damage where it was made, hits, length, the gauges it had, Instant
Charge, super, corner), how much the combo will make here; and, from the situation alone,
how much the red team's own play will. It plays the combo that it expects the most from
when that beats its own play.

Trained on trials from the training starts (combo_starts.py, made again by playback):
every library combo with the start's starter (the move that hit), and the red team's own
play, with resources drawn from the 12 groups. Evaluated on the held-out starts at
--eval-groups: what the selector makes against the red team alone and against the best
combo chosen knowing the outcome. --out gets macros.json (the library as actions, the
evaluation) and selector.pt.
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np
import torch as th

import combo
from efz_env import ActionTable, EfzVecEnv
from efz_env.actions import BACK
from efz_env.history import action_labels
from evaluate import GROUPS

TABLE = ActionTable()
STARTER = 18
LIMIT = 1200


def load_library(path, top):
    lib = np.load(path)
    meta = json.loads(str(lib['meta']))
    out, seen = [], set()
    for k, m in enumerate(meta[:top]):
        inputs = lib[f'inputs{k}']
        acts = action_labels(np.concatenate([[m.get('prev', 0)], inputs]).astype(np.uint8),
                             TABLE)[1:]
        key = (m['starter'], acts.tobytes())
        if key in seen:  # the same combo played again (a player's series)
            continue
        seen.add(key)
        out.append(dict(m, actions=acts))
    return out


def describe(m):
    """A combo's description, for the selector."""
    return np.array([m['damage'] / 1000, m['hits'] / 30, m['frames'] / 1000, m['power'] / 3000,
                     m['rf'] / 1000, float(m['blue']), float(m['ic'] > 0), float(m['ic_blue']),
                     float(m['super']), float(m['corner'])], np.float32)


def onehot(group):
    v = np.zeros(len(GROUPS), np.float32)
    v[GROUPS.index(group)] = 1
    return v


def play_macros(data_dir, jobs, envs=64):
    """jobs: (start, group, combo) -> each one's damage, played as it was recorded, the
    defender guarding once it can."""
    env = EfzVecEnv(data_dir, envs, frame_skip=1, rounds_to_win=2, max_frames=0,
                    autoreset='disabled')
    env.reset()
    rng = np.random.default_rng(3)
    out = []
    for b in range(0, len(jobs), envs):
        batch = jobs[b:b + envs]
        n = len(batch)
        side = np.array([st['side'] for st, _, _ in batch])
        hp0 = np.zeros(n)
        for i, (st, group, m) in enumerate(batch):
            env.load_state(i, st['state'])
            power, rf, blue = combo.group_gauges(group, rng)
            env.set_gauges(i, side[i], power=power, rf=rf, blue=blue)
            hp0[i] = env.info['hp'][i, 1 - side[i]]
        done = np.zeros(n, bool)
        dealt = np.zeros(n)
        controls = np.zeros((envs, 2), np.uint8)
        longest = min(LIMIT, max(len(m['actions']) for _, _, m in batch) + 60)
        for t in range(longest):
            for i, (_, _, m) in enumerate(batch):
                a = m['actions']
                controls[i, side[i]] = TABLE.table[a[t]] if t < len(a) else 0
                controls[i, 1 - side[i]] = BACK
            obs, _, term, trunc, info = env.step(controls)
            for i in np.flatnonzero(~done):
                s = side[i]
                dealt[i] = max(dealt[i], hp0[i] - float(info['hp'][i, 1 - s]))
                if round(float(obs[i, s, combo.COMBO_HITS]) * 30) == 0 or term[i] or trunc[i]:
                    done[i] = True
            if done[:n].all():
                break
        out += list(dealt)
    env.close()
    return out


def play_own(args, model, jobs):
    """jobs: (start, group) -> the red team's own play's damage from each."""
    starts = [dict(st, group=group, job=k) for k, (st, group) in enumerate(jobs)]
    a = argparse.Namespace(data=args.data, delay=args.delay, history=16, limit=LIMIT)
    trials = combo.ComboTrials(a.data, starts, min(64, len(starts)), a.delay, 16, LIMIT,
                               order=True)
    obs = trials.reset()
    while trials.active.any():
        obs, _, _, _ = trials.step(model.predict(obs, deterministic=False)[0])
    trials.close()
    by_job = {r['job']: r['damage'] for r in trials.results}  # in the order they ended
    return [by_job[k] for k in range(len(jobs))]


class Selector(th.nn.Module):
    """Predicts a combo's damage (in 1000s) from the situation and its description, and
    the own play's from the situation alone."""

    def __init__(self, dim):
        super().__init__()
        self.situation = th.nn.Sequential(th.nn.Linear(dim + len(GROUPS), 256), th.nn.ReLU())
        self.combo = th.nn.Sequential(th.nn.Linear(256 + 10, 256), th.nn.ReLU(),
                                      th.nn.Linear(256, 1))
        self.own = th.nn.Sequential(th.nn.Linear(256, 128), th.nn.ReLU(), th.nn.Linear(128, 1))
        self.register_buffer('mean', th.zeros(dim))
        self.register_buffer('scale', th.ones(dim))

    def encode(self, view, group):
        return self.situation(th.cat([(view - self.mean) * self.scale, group], 1))

    def forward(self, view, group, desc):
        h = self.encode(view, group)
        return self.combo(th.cat([h, desc], 1)).squeeze(1), self.own(h).squeeze(1)


def situations(starts, groups):
    return (th.as_tensor(np.stack([st['seen'][-1][:168] for st in starts])),
            th.as_tensor(np.stack([onehot(g) for g in groups])))


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--starts', default='D:/tasogare/efz-replays/combo-starts')
    p.add_argument('--library', default='D:/tasogare/efz-replays/combo-library.npz')
    p.add_argument('--red', required=True, help="the red team's model (combo.py)")
    p.add_argument('--delay', type=int, default=0, help="the red team's reaction time")
    p.add_argument('--top', type=int, default=300, help='library combos used')
    p.add_argument('--per-start', type=int, default=12, help='combos tried from each start')
    p.add_argument('--draws', type=int, default=2, help='resource groups drawn per start')
    p.add_argument('--eval-groups', nargs='*', default=['blue0', 'red0', 'cyan0', 'cyan3'])
    p.add_argument('--out', default=os.path.join(HERE, 'macros'))
    args = p.parse_args()
    from stable_baselines3 import PPO
    th.set_num_threads(8)
    os.makedirs(args.out, exist_ok=True)
    t0 = time.time()
    library = load_library(args.library, args.top)
    rng = np.random.default_rng(0)
    train = combo.load_starts(args.starts, 'train', 10000, rng)
    test = combo.load_starts(args.starts, 'test', 10000, rng)
    combo.restore(args.data, os.path.dirname(os.path.abspath(args.starts)), train + test)
    print(f'{len(library)} library combos, {len(train)} training starts, {len(test)} held out '
          f'({time.time() - t0:.0f}s)', flush=True)
    red = PPO.load(args.red, device='cpu')

    def candidates(st):
        starter = int(round(float(st['seen'][-1][STARTER])))
        return [m for m in library if m['starter'] == starter][:args.per_start]

    # Trials: (start, group) situations, each with its candidates and the own play.
    sit, macro_jobs = [], []
    for st in train:
        for _ in range(args.draws):
            g = GROUPS[rng.integers(len(GROUPS))]
            sit.append((st, g))
            macro_jobs += [(st, g, m) for m in candidates(st)]
    t = time.time()
    macro_damage = play_macros(args.data, macro_jobs)
    own_damage = play_own(args, red, sit)
    print(f'{len(macro_jobs)} combo trials and {len(sit)} of its own play in '
          f'{time.time() - t:.0f}s', flush=True)

    # The selector.
    sel = Selector(168)
    views = np.stack([st['seen'][-1][:168] for st, _ in sit])
    sel.mean.copy_(th.as_tensor(views.mean(0)))
    sel.scale.copy_(th.as_tensor(1 / np.maximum(views.std(0), 1e-3)))
    mv, mg = situations([st for st, _, _ in macro_jobs], [g for _, g, _ in macro_jobs])
    md = th.as_tensor(np.stack([describe(m) for _, _, m in macro_jobs]))
    my = th.as_tensor(np.array(macro_damage, np.float32) / 1000)
    ov, og = situations([st for st, _ in sit], [g for _, g in sit])
    oy = th.as_tensor(np.array(own_damage, np.float32) / 1000)
    opt = th.optim.Adam(sel.parameters(), lr=1e-3, weight_decay=1e-5)
    for epoch in range(300):
        perm = th.randperm(len(my))
        for i in range(0, len(my), 512):
            idx = perm[i:i + 512]
            pred, _ = sel(mv[idx], mg[idx], md[idx])
            _, own = sel(ov, og, th.zeros(len(oy), 10))
            loss = th.nn.functional.smooth_l1_loss(pred, my[idx]) + \
                th.nn.functional.smooth_l1_loss(own, oy)
            opt.zero_grad()
            loss.backward()
            opt.step()
    print(f'selector trained ({time.time() - t0:.0f}s), loss {loss.item():.3f}', flush=True)

    # Held out: the selector's choice against own play and the best in hindsight.
    report = {}
    for g in args.eval_groups:
        jobs = [(st, g, m) for st in test for m in candidates(st)]
        dmg = play_macros(args.data, jobs)
        own = play_own(args, red, [(st, g) for st in test])
        chosen, best = [], []
        k = 0
        for si, st in enumerate(test):
            cands = candidates(st)
            d = np.array(dmg[k:k + len(cands)])
            k += len(cands)
            v, gr = situations([st] * max(1, len(cands)), [g] * max(1, len(cands)))
            with th.no_grad():
                pred, pown = sel(v, gr, th.as_tensor(np.stack([describe(m) for m in cands]))
                                 if cands else th.zeros(1, 10))
            if cands and float(pred.max()) > float(pown[0]):
                chosen.append(float(d[int(pred.argmax())]))
            else:
                chosen.append(own[si])
            best.append(max([own[si]] + list(d)))
        stats = lambda x: dict(damage=round(float(np.mean(x))), p90=round(float(np.percentile(x, 90))),
                               most=round(float(np.max(x))))
        report[g] = dict(own=stats(own), selector=stats(chosen), hindsight=stats(best),
                         macro_used=float(np.mean([c != o for c, o in zip(chosen, own)])))
        print(g, json.dumps(report[g]), flush=True)
    th.save(sel.state_dict(), os.path.join(args.out, 'selector.pt'))
    with open(os.path.join(args.out, 'macros.json'), 'w') as f:
        json.dump(dict(args=vars(args), eval=report,
                       library=[dict({k: v for k, v in m.items() if k not in ('inputs', 'actions')},
                                     actions=m['actions'].tolist()) for m in library]), f)
    print(f'done in {time.time() - t0:.0f}s', flush=True)


if __name__ == '__main__':
    main()
