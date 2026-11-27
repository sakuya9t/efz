"""Summarize the paired Sayuri study produced by sayuri_throws.py."""
import argparse
from collections import Counter
import json
from pathlib import Path

import numpy as np


def rows(paths):
    return [json.loads(line) for path in sorted(paths) for line in path.read_text().splitlines()]


def replays(data):
    for cue in ('walk', 'rush', 'stance'):
        samples = [r['options'] for r in data if {'cue': cue} in r['labels']]
        if not samples:
            continue
        for action in samples[0]:
            net = [s[action]['net']-s['base']['net'] for s in samples]
            caught = Counter(k for s in samples for _,k in s[action]['catches'])
            print(cue, len(samples), action, 'mean HP difference', round(np.mean(net)), 'entries', dict(caught))


def commitments(path):
    for r in rows(path.glob('commit-*.jsonl')):
        for z in r['labels']:
            if 'commit' in z:
                print('before punished move', hex(z['commit']), 'frames to opening hit', z['hit']-r['frame'],
                      'retreat vs base HP', r['options']['retreat']['net']-r['options']['base']['net'])
    for f in sorted(path.glob('allcast-*.jsonl')):
        data = rows([f])
        for move in sorted({r['labels'][0]['commit'] for r in data}):
            opts = [r['options'] for r in data if r['labels'][0]['commit'] == move]
            diffs = [o['retreat']['net']-o['base']['net'] for o in opts]
            print(f.stem, hex(move), 'uses',len(opts),'retreat mean HP difference', round(np.mean(diffs)))


def paired_sets(path, profile, mode, first, count=6):
    def load(name):
        data = rows(path.glob(f'{name}-{profile}-*.jsonl'))
        selected = [r for r in data if first <= r['seed'] < first+count]
        assert len(selected) == len({r['seed'] for r in selected}) == count
        return {r['seed']: r for r in selected}

    base, candidate = load('base'), load(mode)
    deltas = []
    for name, data in [('base',base), (mode,candidate)]:
        legs = [g for r in data.values() for g in r['legs']]
        counts = Counter()
        for g in legs:
            counts.update(g['counts'])
        frames = sum(g['frames'] for g in legs)
        print(profile,name,'wins',sum(g['win'] for g in legs),'of',len(legs),
              'sets won',sum(sum(g['win'] for g in r['legs']) >= 2 for r in data.values()),
              'mean net',round(np.mean([g['net'] for g in legs])),
              'ground throws/min',round(counts['ground']*3840/frames,2),
              'presses/sec',round(sum(g['presses'] for g in legs)*64/frames,2),
              'under pressure',round(64*sum(g['pressure_presses'] for g in legs)/sum(g['pressure'] for g in legs),2),
              'events',dict(counts))
    for seed in sorted(base):
        b, c = base[seed], candidate[seed]
        assert (b['generation'], b['throw']) == (c['generation'], c['throw'])
        assert len(b['legs']) == len(c['legs']) == 3
        deltas.append([np.mean([y[k]-x[k] for x,y in zip(b['legs'],c['legs'])]) for k in ('win','net')])
    d = np.array(deltas)
    sampled = d[np.random.default_rng(711).integers(0,len(d),(10000,len(d)))].mean(axis=1)
    print('paired change (win fraction, HP/game)',d.mean(axis=0).round(2).tolist(),
          '95% set-bootstrap', np.quantile(sampled,[.025,.975],axis=0).T.round(2).tolist())


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('folder', type=Path)
    args = parser.parse_args()
    print('tester')
    replays(rows(args.folder.glob('replay-*.jsonl')))
    print('validation')
    replays(rows(args.folder.glob('valid-*.jsonl')))
    commitments(args.folder)
    for mode, first in [('jump',240),('jump',260),('conditioned',260)]:
        print('set seeds',first,'through',first+5)
        for profile in ('ordinary','grabs'):
            paired_sets(args.folder,profile,mode,first)
    print('third defender, set seeds 280 through 287')
    for mode in ('jump','conditioned'):
        paired_sets(args.folder,'transfer',mode,280,8)
