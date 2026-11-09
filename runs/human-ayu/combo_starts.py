"""Where people's combos start: plays back replays of the dataset and keeps, for some of
Ayu's combos, the game at its first hit (a save state), what the player saw and input
just before it, and what the player then made of it. combo.py's trials start there.

    python runs/human-ayu/combo_starts.py --replays D:/tasogare/efz-replays \\
        --dataset D:/tasogare/efz-replays/datasets/ayu --out D:/tasogare/efz-replays/combo-starts

A start is a step on which the combo counter of Ayu's side goes from 0 to 1. Each is
kept with --share's chance, from the matches bc.py trains on (every tenth replay by id,
which it holds out, gives the --test starts instead). OUT/<id>-<side>-<step>.npz:

    side      Ayu's side (0, 1)
    seen      (--delay + 1, obs_dim): Ayu's views of the steps up to the start, newest last
    inputs    (--history,): Ayu's inputs on the steps up to it, newest last
    hits, damage   the combo the player made from there (its hits, and damage in HP)

and OUT/starts.csv a line per start. The game at the start isn't kept: a save state holds
the library's addresses and loads only where it is loaded at the same place (efz_env.h),
so combo.py makes it again by playing the replay back to <step>, which is good anywhere.
"""

import argparse
import collections
import csv
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

import numpy as np

from efz_env import EfzVecEnv
from efz_env.vec import character_names

COMBO_HITS, COMBO_DAMAGE = 30, 38  # self_combo_hits (/ 30), self_combo_damage (/ 9999)


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--replays', required=True, help='the folder with index.csv')
    p.add_argument('--dataset', required=True, help="dataset.py's folder (matches.csv)")
    p.add_argument('--out', required=True)
    p.add_argument('--matches', type=int, default=300, help='replays to look through')
    p.add_argument('--share', type=float, default=0.25, help='chance a start is kept')
    p.add_argument('--envs', type=int, default=32)
    p.add_argument('--delay', type=int, default=14)
    p.add_argument('--history', type=int, default=16)
    p.add_argument('--seed', type=int, default=0)
    return p.parse_args()


def main():
    args = parse()
    os.makedirs(args.out, exist_ok=True)
    ayu = character_names().index('ayu')
    index = {r['id']: r for r in csv.DictReader(open(os.path.join(args.replays, 'index.csv'),
                                                      encoding='utf-8'))}
    rows = [r for r in csv.DictReader(open(os.path.join(args.dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    ids = list(dict.fromkeys(r['id'] for r in rows))  # replays, each once
    rng = np.random.default_rng(args.seed)
    rng.shuffle(ids)
    test = [i for i in ids if int(i) % 10 == 0][:max(1, args.matches // 10)]
    train = [i for i in ids if int(i) % 10 != 0][:args.matches]
    queue = collections.deque([(i, 'test') for i in test] + [(i, 'train') for i in train])
    n = min(args.envs, len(queue))
    env = EfzVecEnv(args.data, n, frame_skip=1, rounds_to_win=2, max_frames=64 * 60 * 30,
                    autoreset='disabled')
    current = [None] * n
    look = args.delay + 1

    def start(i):
        while queue:
            rid, split = queue.popleft()
            try:
                env.play(i, os.path.join(args.replays, *index[rid]['path'].split('\\')))
            except ValueError:
                continue
            env.reset(mask=np.arange(n) == i)
            if env.terminated[i] or not env.info['replay'][i]:
                continue
            sides = [s for s in range(2) if int(env.info['chars'][i][s]) == ayu]
            current[i] = dict(id=rid, split=split, step=0, sides=sides,
                              seen={s: collections.deque([env.obs[i, s].copy()], look) for s in sides},
                              inputs={s: collections.deque([0] * args.history, args.history)
                                      for s in sides},
                              open={})  # side -> a start waiting for its combo's end
            return True
        current[i] = None
        return False

    for i in range(n):
        start(i)
    out_csv = open(os.path.join(args.out, 'starts.csv'), 'a', newline='', encoding='utf-8')
    w = csv.DictWriter(out_csv, fieldnames=['file', 'id', 'side', 'split', 'opponent',
                                            'hits', 'damage'])
    if out_csv.tell() == 0:
        w.writeheader()
    names = character_names()
    kept, t0 = 0, time.time()
    idle = np.zeros((n, 2), np.uint8)
    while any(c is not None for c in current):
        obs, _, term, trunc, info = env.step(idle)
        for i in range(n):
            c = current[i]
            if c is None:
                continue
            c['step'] += 1
            for s in c['sides']:
                c['inputs'][s].append(int(info['input'][i, s]))
                hits = round(float(obs[i, s, COMBO_HITS]) * 30)
                prev_hits = round(float(c['seen'][s][-1][COMBO_HITS]) * 30)
                c['seen'][s].append(obs[i, s].copy())
                o = c['open'].get(s)
                if o is not None:  # the player's combo so far
                    o['hits'] = max(o['hits'], hits)
                    o['damage'] = max(o['damage'], float(obs[i, s, COMBO_DAMAGE]) * 9999)
                    if hits == 0 or term[i] or trunc[i]:
                        name = f"{c['id']}-{s}-{o['step']}.npz"
                        np.savez(os.path.join(args.out, name), side=s, seen=o['seen'],
                                 inputs=o['inputs'], hits=o['hits'], damage=o['damage'])
                        w.writerow(dict(file=name, id=c['id'], side=s, split=c['split'],
                                        opponent=names[int(info['chars'][i][1 - s])],
                                        hits=o['hits'], damage=round(o['damage'])))
                        kept += 1
                        del c['open'][s]
                elif prev_hits == 0 and hits > 0 and not (term[i] or trunc[i]) and \
                        len(c['seen'][s]) == look and rng.random() < args.share:
                    c['open'][s] = dict(step=c['step'], hits=hits,
                                        damage=float(obs[i, s, COMBO_DAMAGE]) * 9999,
                                        seen=np.stack(c['seen'][s]).astype(np.float32),
                                        inputs=np.array(c['inputs'][s], np.uint8))
            if term[i] or trunc[i]:
                start(i)
        if kept and kept % 50 == 0:
            out_csv.flush()
    out_csv.close()
    env.close()
    print(f'{kept} starts in {time.time() - t0:.0f}s', flush=True)


if __name__ == '__main__':
    main()
