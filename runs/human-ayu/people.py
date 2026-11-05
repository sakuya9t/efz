"""How people played Ayu in the dataset's matches, by evaluate.py's measure (Events):
presses, jumps, guards, recoil guards and hits taken, per minute. Writes people.json.

    python runs/human-ayu/people.py --dataset D:/tasogare/efz-replays/datasets/ayu

--split val: the matches bc.py holds out (every tenth replay by id); all: every one.
--by-player: also per player with at least --min matches, by the pseudonyms of
players.csv (beside the replays' index: who played each side, as numbers).
"""

import argparse
import csv
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

import numpy as np

from evaluate import COLUMNS, Events


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--dataset', required=True)
    p.add_argument('--split', choices=('val', 'all'), default='all')
    p.add_argument('--out', default=os.path.join(HERE, 'people.json'))
    p.add_argument('--by-player', help="players.csv (the replays' pseudonyms)")
    p.add_argument('--min', type=int, default=40)
    args = p.parse_args()
    rows = [r for r in csv.DictReader(open(os.path.join(args.dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    if args.split == 'val':
        rows = [r for r in rows if int(r['id']) % 10 == 0]
    who = {}
    if args.by_player:
        for r in csv.DictReader(open(args.by_player, encoding='utf-8')):
            who[(r['id'], r['side'])] = r['player']
    by_opponent, by_player = {}, {}
    total = Events('ayu')
    for r in rows:
        with np.load(os.path.join(args.dataset, f"{r['id']}-{r['side']}.npz")) as z:
            cols, inputs = z['obs'][:, COLUMNS], z['input']
        e = Events('ayu')
        e.add_match(cols, inputs)
        total.merge(e)
        by_opponent.setdefault(r['opponent'], Events('ayu')).merge(e)
        if who:
            pl = who.get((r['id'], r['side']), 'unnamed')
            by_player.setdefault(pl, [0, Events('ayu')])
            by_player[pl][0] += 1
            by_player[pl][1].merge(e)
    out = dict(split=args.split, matches=len(rows), minutes=round(total.n['frames'] / 3840, 1),
               all=total.report(),
               by_opponent={k: v.report() for k, v in sorted(by_opponent.items())},
               by_player={k: dict(matches=n, **e.report()) for k, (n, e) in
                          sorted(by_player.items(), key=lambda kv: -kv[1][0])
                          if n >= args.min})
    with open(args.out, 'w') as f:
        json.dump(out, f, indent=1)
    print(json.dumps(out['all']))
    keys = ['matches', 'presses_per_second', 'jumps_per_min', 'guard_ground_per_min',
            'rg_ground', 'rg_air', 'rc', 'rg_move', 'rg_punish', 'guess_623A_per_min',
            'guess_623B_per_min', 'hit_ground_per_min']
    if out['by_player']:
        print('player ' + ' '.join(k[:14].rjust(14) for k in keys))
        for pl, r in out['by_player'].items():
            print(f'{pl:>6} ' + ' '.join(str(r[k]).rjust(14) for k in keys))


if __name__ == '__main__':
    main()
