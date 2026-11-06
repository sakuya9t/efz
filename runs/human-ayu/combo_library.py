"""People's Ayu combos as a library: every combo of the dataset's matches with its damage,
hits, length, the move it started from, the gauges it had (power, RF, blue), whether it
used an Instant Charge (with the RF gauge red or cyan) or a super, and whether in the corner; and the
inputs that made it, from the step after its first hit to its end (relative to facing,
as an agent's), with the one before (prev: what the first of them presses follows from). Writes --out (npz: the --keep most damaging) and prints the best.

    python runs/human-ayu/combo_library.py --dataset D:/tasogare/efz-replays/datasets/ayu
"""

import argparse
import csv
import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))

ACTION, GAUGE, RF, BLUE, OPP_X = 18, 9, 10, 11, 45
HITS, DAMAGE = 30, 38
IC = (0xa7, 0xab)
SUPERS = range(0x12c, 0x13e)


def combos_of(obs, inputs):
    hits = np.round(obs[:, HITS].astype(np.float32) * 30).astype(int)
    on = hits > 0
    starts = np.flatnonzero(on & ~np.concatenate([[False], on[:-1]]))
    ends = np.flatnonzero(~on & np.concatenate([[False], on[:-1]]))
    act = np.round(obs[:, ACTION].astype(np.float32)).astype(int)
    for b in starts:
        later = ends[ends > b]
        e = later[0] if len(later) else len(obs)
        seg = act[b:e]
        ic_at = [k for k in range(b, e) if act[k] in IC and (k == b or act[k - 1] not in IC)]
        yield dict(start=int(b), end=int(e), frames=int(e - b), hits=int(hits[b:e].max()),
                   damage=float(obs[b:e, DAMAGE].astype(np.float32).max() * 9999),
                   starter=int(act[b]), power=int(round(float(obs[b, GAUGE]) * 3000)),
                   rf=int(round(float(obs[b, RF]) * 1000)), blue=bool(obs[b, BLUE] > 0),
                   ic=len(ic_at), ic_blue=any(obs[max(0, k - 1), BLUE] > 0 for k in ic_at),
                   super=bool(np.isin(seg, list(SUPERS)).any()),
                   corner=bool(abs(float(obs[b, OPP_X])) > 0.8),
                   prev=int(inputs[b - 1]) if b > 0 else 0, inputs=inputs[b:e].copy())


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--dataset', required=True)
    p.add_argument('--out', default=os.path.join('D:/tasogare/efz-replays', 'combo-library.npz'))
    p.add_argument('--keep', type=int, default=300)
    p.add_argument('--show', type=int, default=25)
    args = p.parse_args()
    rows = [r for r in csv.DictReader(open(os.path.join(args.dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    found = []
    for r in rows:
        with np.load(os.path.join(args.dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inputs = z['obs'], z['input']
        for c in combos_of(obs, inputs):
            if c['hits'] >= 2:
                c.update(id=r['id'], side=int(r['side']), opponent=r['opponent'])
                found.append(c)
    found.sort(key=lambda c: -c['damage'])
    dmg = np.array([c['damage'] for c in found])
    print(f'{len(found)} combos of 2 hits or more in {len(rows)} matches; damage: median '
          f'{np.median(dmg):.0f}, 90th percentile {np.percentile(dmg, 90):.0f}, '
          f'99th {np.percentile(dmg, 99):.0f}, most {dmg.max():.0f}')
    for t in (3000, 4000, 5000, 6000, 7000):
        top = [c for c in found if c['damage'] >= t]
        if top:
            share = lambda k: np.mean([bool(c[k]) for c in top])
            print(f'  {len(top):5d} of {t}+: cyan IC {share("ic_blue"):.0%}, any IC {share("ic"):.0%}, '
                  f'super {share("super"):.0%}, corner {share("corner"):.0%}, started with '
                  f'cyan RF {share("blue"):.0%}, power {np.mean([c["power"] for c in top]):.0f}')
    sys.path.insert(0, HERE)
    from evaluate import GROUPS, resources
    print('by resources at the start (RF gauge blue < 500, red 500-999, cyan full; bars of power):')
    for g in GROUPS:
        d = np.array([c['damage'] for c in found
                      if resources(c['power'], c['rf'], c['blue']) == g])
        if len(d):
            print(f'  {g:6s} {len(d):5d} combos: average {d.mean():5.0f}, 90th percentile '
                  f'{np.percentile(d, 90):5.0f}, most {d.max():5.0f}')
    print('the best:')
    for c in found[:args.show]:
        print(f"  {c['damage']:5.0f} HP {c['hits']:2d} hits {c['frames']:4d} frames, starter 0x{c['starter']:x}, "
              f"power {c['power']} RF {c['rf']}{' blue' if c['blue'] else ''}, IC {c['ic']}"
              f"{' (blue)' if c['ic_blue'] else ''}{', super' if c['super'] else ''}"
              f"{', corner' if c['corner'] else ''}, vs {c['opponent']} (replay {c['id']})")
    keep = found[:args.keep]
    meta = [{k: v for k, v in c.items() if k != 'inputs'} for c in keep]
    np.savez(args.out, meta=json.dumps(meta),
             **{f'inputs{k}': c['inputs'] for k, c in enumerate(keep)})
    print('kept', len(keep), 'in', args.out)


if __name__ == '__main__':
    main()
