"""Find held-out Ayu–Sayuri walk-ins in the community archive for native replay tests."""
import argparse
import csv
import hashlib
import json
from pathlib import Path

import numpy as np

from sayuri_throws import COOLDOWN, DELAY, GROUND, THROWN


def walks(view):
    # Detect entries in the same delayed view as native_walk_trials(), including
    # its 48-frame warm-up after a round change. Only the observer's side is used.
    walk = ((view[:, 50] == 1) & np.isin(view[:, 18], (0, 1, 2, 3, 4, 8))
            & ~(view[:, [2, 3, 20, 39, 52, 71]] != 0).any(axis=1)
            & (abs(view[:, 4].astype(float)) * 640 <= 42))
    eligible = np.zeros(len(view), dtype=bool)
    eligible[48:] = (view[48:, 1] == view[:-48, 1]) & walk[48-DELAY:-DELAY]
    entries = np.flatnonzero(eligible & ~np.r_[False, eligible[:-1]])
    thrown = np.isin(view[:, 18], sorted(THROWN))
    ground = np.flatnonzero(thrown & ~np.r_[False, thrown[:-1]] & np.isin(view[:, 50], GROUND))
    result = []
    for tick in entries:
        if result and tick - result[-1]['tick'] < COOLDOWN and view[tick, 1] == view[result[-1]['tick'], 1]:
            continue
        result.append(dict(tick=int(tick), prior_ground=bool(len(ground) and ground[0] <= tick - DELAY),
                           ground=bool(((ground > tick) & (ground <= tick + 32)
                                       & (view[ground, 1] == view[tick, 1])).any())))
    return result


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--archive', type=Path, required=True)
    parser.add_argument('--exclude', nargs='+', required=True, help='IDs used in the fit or earlier replay checks')
    parser.add_argument('--out', type=Path, required=True)
    args = parser.parse_args()
    data = args.archive / 'datasets/ayu'
    with (args.archive/'index.csv').open() as f:
        files = {r['id']: str(args.archive.joinpath(*r['path'].split('\\'))) for r in csv.DictReader(f)}
    with (args.archive/'players.csv').open() as f:
        players = {(r['id'], r['side']): r['player'] for r in csv.DictReader(f) if r['char'].lower() == 'sayuri'}
    with (data/'matches.csv').open() as f:
        records = [r for r in csv.DictReader(f) if r['opponent'] == 'sayuri' and r['in_sync'] == '1']
    seen = set()
    excluded = set(args.exclude)
    rows = []
    # Seed both the order of duplicated replays and the later per-opponent sampling.
    np.random.default_rng(87412).shuffle(records)
    # Fingerprint excluded records first, so a copy with a different archive ID is excluded too.
    for r in sorted(records, key=lambda r: r['id'] not in excluded):
        key, side = r['id'], r['side']
        with np.load(data/f'{key}-{side}.npz') as game:
            inputs = game['input']
            digest = hashlib.sha256(inputs.tobytes()).digest()
            if digest in seen:
                continue
            seen.add(digest)
            if key in excluded:
                continue
            points = walks(game['obs'])
        rows.append(dict(id=key, path=files[key], side=int(side), winner=int(r['winner']), frames=int(r['frames']),
                         player=players.get((key, str(1-int(side)))), walks=points))
    # Two strata expose both the target and its cost. One replay per player in each
    # stratum improves coverage of players who appear only occasionally in the archive.
    picked = []
    for positive in (True, False):
        opponents = set()
        for r in rows:
            if (r['walks'] and any(p['ground'] for p in r['walks']) == positive
                    and r['player'] is not None and r['player'] not in opponents):
                picked.append(dict(id=r['id'], positive=positive))
                opponents.add(r['player'])
                if len(opponents) == 12:
                    break
    with args.out.open('x') as f:
        json.dump(dict(matches=rows, sample=picked), f, indent=2)


if __name__ == '__main__':
    main()
