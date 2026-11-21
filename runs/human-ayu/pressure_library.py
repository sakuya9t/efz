"""People's Ayu pressure as a library: what its players did next each time a move of
theirs was guarded and they could act again, close to the guarding player. An entry is
the inputs (relative to facing, as an agent's) from that first free step to their next
contact (a hit, a guard, a throw) and a little after, with what it was (the next move:
how they came in, how it is guarded; a throw; or no move: holding, backing off, jumping
away), how many steps of the guard the opponent then had left (the frame advantage a
planner matches its own to), the distance, and how it went. A planner tries them on
copies of the game from a guarded move of its own (pressplan.py), as okiplan.py tries
oki_library.py's from a knockdown.

    python runs/human-ayu/pressure_library.py --dataset ~/data/efz-replays/datasets/ayu \
        --out ~/data/efz-replays/pressure-library.npz

The anchor: the first step the player is free on the ground after a move of its own was
guarded, at most --reach steps after that guard's last contact, neither player hit in
between, the opponent within --near pixels. The entry runs to --tail steps after the next
contact within --look steps, or --look steps when there is none.

The entries hold the match's id and the side, the opponent's character and numbers: no
player's name.

    python runs/human-ayu/pressure_library.py --answers ~/data/efz-replays/pressure-library.npz

writes the library's answers beside it (pressure-library.answers.json), for an agent
file's planner in the game (python/efz_env/export.py's pressplan): each character's
reversals out of a guard, fastest first (advantages.py's invincible_moves), and the moves
that are invincible from their start (framedata.json).
"""

import argparse
import collections
import csv
import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import tactics
from tactics import OBS, Side, _first, _prev

OPP_X = 45
THROWN = range(0x64, 0x7a)
THROW = 0xdc


def followups(obs, inputs, reach=30, look=45, tail=20, near=160):
    """A dict per first free step of the viewer's after a guarded move of its own."""
    c = obs[:, OBS].astype(np.float32)
    me, opp = Side(c, 0), Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    px = np.abs(c[:, 18]) * 640
    T = len(obs)
    thrown = np.isin(opp.act, list(THROWN))
    thrown_in = thrown & ~_prev(thrown, False)
    touch = opp.contact | opp.hit | thrown_in
    free = me.free & ~me.air
    contacts = np.flatnonzero(opp.contact)
    if not len(contacts):
        return
    air_in = me.air & ~_prev(me.air, False)
    for a in np.flatnonzero(free & ~_prev(free, False)):
        k = int(np.searchsorted(contacts, a)) - 1
        if k < 0:
            continue
        tc = int(contacts[k])
        if not 1 <= a - tc <= reach or a + look + tail >= T or px[a] > near:
            continue
        if not live[tc:a + look + tail].all():
            continue
        if me.hitstun[tc:a + 1].any() or opp.hitstun[tc:a + 1].any():
            continue  # the string hit, or was hit, before the player was free
        if free[tc:a].any() or me.guard[tc:a].any() or not (me.act[tc:a] >= tactics.FIRST_OWN).any():
            continue  # (an object's contact with the player free: not a move's recovery)
        if opp.guard[a]:  # the guard's steps left: the player's advantage
            f = _first(~opp.guard, a, a + look + 1)
            adv = (f if f is not None else a + look) - a
        else:
            g = np.flatnonzero(opp.guard[tc:a])
            adv = (tc + int(g[-1]) + 1) - a if len(g) else -(a - tc)
        hi = a + look + 1
        t, h, b = _first(touch, a + 1, hi), _first(me.hit, a, hi), _first(me.move, a, hi)
        if b is not None and (t is None or b <= t) and (h is None or b <= h):
            act = int(me.act[b])
            seen = me.act[a:b + 1]
            way = ('fly' if np.isin(seen, tactics.AIRDASH).any() else
                   'dash' if (seen == tactics.DASH).any() else
                   'jump' if me.air[b] or air_in[a:b + 1].any() else 'ground')
            height = me.heights.get(act, 'mid')
            cls = 'throw' if act == THROW or height == 'unguardable' else f'{way} {height}'
        else:  # no move of its own came first
            b, act = None, 0
            seen = me.act[a:a + look]
            cls = ('none: jump' if me.air[a:a + look].any() else
                   'none: backdash' if (seen == tactics.BACKDASH).any() else
                   'none: back' if px[a + look - 1] > px[a] + 40 else 'none: hold')
        hurt = h is not None and (t is None or h <= t)
        result = ('hurt' if hurt else 'none' if t is None else 'throw' if thrown_in[t] else
                  'hit' if opp.hit[t] else 'guard')
        e = min(T, (h if hurt else t if t is not None else a + look) + tail)
        yield dict(start=int(a), since=int(a - tc), adv=int(adv), cls=cls, result=result,
                   move=act, move_at=int(b - a) if b is not None else -1,
                   contact=int(t - a) if t is not None else -1,
                   guarded=int(me.act[tc]), distance=round(float(px[a])),
                   corner=bool(abs(float(obs[a, OPP_X])) > 0.8),
                   prev=int(inputs[a - 1]), inputs=inputs[a:e].copy())


def answers():
    """{'reversal': {character: [[directions, button, needs], ...]}, 'invincible':
    {character: [actions]}}."""
    import advantages
    names = tactics.names()
    reversal = {}
    for c in names:
        moves = [[list(dirs), button, needs]
                 for dirs, button, _, needs, *_ in advantages.invincible_moves(c)]
        if moves:
            reversal[c] = moves
    inv = {names[c]: sorted(int(a) for a in v[0]) for c, v in tactics.frame_data().items()
           if v[0]}
    return dict(reversal=reversal, invincible=inv)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--answers', metavar='LIBRARY.npz',
                   help="write that library's answers beside it and stop")
    p.add_argument('--dataset')
    p.add_argument('--out')
    p.add_argument('--reach', type=int, default=30)
    p.add_argument('--look', type=int, default=45)
    p.add_argument('--tail', type=int, default=20)
    p.add_argument('--near', type=int, default=160)
    p.add_argument('--limit', type=int, default=0, help='the first this many matches (a look)')
    args = p.parse_args()
    if args.answers:
        out = os.path.splitext(os.path.expanduser(args.answers))[0] + '.answers.json'
        a = answers()
        json.dump(a, open(out, 'w'))
        print(f"{out}: reversals out of a guard for {len(a['reversal'])} characters, invincible "
              f"moves for {len(a['invincible'])}")
        return
    if not args.dataset or not args.out:
        p.error('--dataset and --out (or --answers)')
    dataset = os.path.expanduser(args.dataset)
    rows = [r for r in csv.DictReader(open(os.path.join(dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    if args.limit:
        rows = rows[:args.limit]
    found = []
    for r in rows:
        with np.load(os.path.join(dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inputs = z['obs'], z['input']
        for m in followups(obs, inputs, args.reach, args.look, args.tail, args.near):
            m.update(id=r['id'], side=int(r['side']), opponent=r['opponent'])
            found.append(m)
    n = len(found)
    print(f'{n} follow-ups to a guarded move, in {len(rows)} matches')
    for key in ('since', 'adv', 'distance'):
        x = np.array([m[key] for m in found])
        print(f'  {key}: 10th {np.percentile(x, 10):.0f}, median {np.median(x):.0f}, '
              f'90th {np.percentile(x, 90):.0f}')
    by = collections.defaultdict(list)
    for m in found:
        by[m['cls']].append(m)
    print('  by what came next (count, share; then how it went: opened the guard, guarded, '
          'no contact, the player hit first; the advantage it was done at, median):')
    for cls, ms in sorted(by.items(), key=lambda kv: -len(kv[1])):
        res = collections.Counter(m['result'] for m in ms)
        opened = (res['hit'] + res['throw']) / len(ms)
        print(f"    {cls:16s} {len(ms):6d} {len(ms) / n:5.1%}   opened {opened:4.0%}  guarded "
              f"{res['guard'] / len(ms):4.0%}  none {res['none'] / len(ms):4.0%}  hurt "
              f"{res['hurt'] / len(ms):4.0%}   adv {np.median([m['adv'] for m in ms]):+.0f}")
    adv = np.array([m['adv'] for m in found])
    for name, mask in (('plus (2 or more)', adv >= 2), ('even', np.abs(adv) < 2),
                       ('minus (-2 to -9)', (adv <= -2) & (adv > -10)), ('minus 10 or worse', adv <= -10)):
        ms = [m for m, ok in zip(found, mask) if ok]
        top = collections.Counter(m['cls'] for m in ms).most_common(6)
        print(f'  {name}: {len(ms)} ({len(ms) / n:.0%}): ' +
              ', '.join(f'{c} {k / len(ms):.0%}' for c, k in top))
    out = os.path.expanduser(args.out)
    meta = [{k: v for k, v in m.items() if k != 'inputs'} for m in found]
    lengths = np.array([len(m['inputs']) for m in found], np.int32)
    np.savez_compressed(out, meta=json.dumps(meta), lengths=lengths,
                        inputs=np.concatenate([m['inputs'] for m in found]).astype(np.uint8))
    print(f'{out}: {n} entries')


if __name__ == '__main__':
    main()
