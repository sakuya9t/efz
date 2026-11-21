"""People's Ayu okizeme as a library: what its players did from each knockdown they made to
their first contact on the riser (a hit, a guard, a throw), with what it was (how they
came in, how it is guarded, the side), when it touched relative to the rising, and the
inputs that made it (relative to facing, as an agent's) and how far from the riser the
player was at each step (and whether in the air), for a planner to try on copies
of the game from a knockdown of its own (okiplan.py), as combo_library.py's combos are
from a hit.

    python runs/human-ayu/oki_library.py --dataset ~/data/efz-replays/datasets/ayu \
        --out ~/data/efz-replays/oki-library.npz

An entry is kept if its player touched the riser within --within steps of the rising
(default 20: a meaty, or close to one) without being hit first, and is cut --tail steps
after the contact (what the player went on to press: its string, or its combo's start).
Its timing is the knockdown's: `rise` is the step of its inputs at which the riser was
up, so a planner plays it with that step on the step its own opponent rises.

The entries hold the match's id and the side, the opponent's character and numbers: no
player's name.

    python runs/human-ayu/oki_library.py --answers ~/data/efz-replays/oki-library.npz

writes the library's answers beside it (oki-library.answers.json), for an agent file's
planner in the game (python/efz_env/export.py's okiplan, port/agent/mix.h): each
character's reversals on rising in the order a riser prefers them (advantages.py's
wake_moves: the motion, the button, what it needs), and the moves that are invincible
from their start (framedata.json: what the planner's counts read a reversal by). The
game has neither motions.json nor framedata.json.
"""

import argparse
import csv
import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)

import tactics
from tactics import DOWN, FIRST_OWN, OBS, Side, _first, _runs

THROWN = range(0x64, 0x79)
SELF_X, OPP_X = 13, 45
APPROACH = tactics.APPROACH


def okizeme_of(obs, inputs, within=20, tail=20):
    """A dict per knockdown of the opponent's that the viewer's okizeme touched."""
    c = obs[:, OBS].astype(np.float32)
    me, opp = Side(c, 0), Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    dx = c[:, 18]
    T = len(obs)
    guard_in = opp.guard & ~tactics._prev(opp.guard, False)
    thrown = np.isin(opp.act, list(THROWN))
    thrown_in = thrown & ~tactics._prev(thrown, False)
    touch = guard_in | opp.hit | thrown_in
    starts, ends = _runs(np.isin(opp.act, DOWN))
    for s, w in zip(starts, ends):
        if s == 0 or w + within + tail >= T or not live[s:w + within + tail].all():
            continue
        if 0x32 <= opp.act[w] < 0x96 and not thrown[w]:
            continue  # hit lying: the combo went on, not an okizeme
        t = _first(touch, w, w + within + 1)
        if t is None:
            continue
        h = _first(me.hit, s, t + 1)
        if h is not None:
            continue  # the viewer was hit first
        kind = 'throw' if thrown_in[t] else 'hit' if opp.hit[t] else 'guard'
        moves = np.flatnonzero(me.move[s:t + 1])
        if not len(moves):
            continue  # no move of its own made it (an object's, set before)
        b = s + int(moves[-1])
        lo = max(s, b - APPROACH)
        seen = me.act[lo:b + 1]
        way = ('fly' if np.isin(seen, tactics.AIRDASH).any() else
               'dash' if (seen == tactics.DASH).any() else
               'jump' if me.air[b] or (me.air[lo + 1:b + 1] & ~me.air[lo:b]).any() else
               'ground')
        height = me.heights.get(int(me.act[b]), 'mid')
        height = 'throw' if (height == 'unguardable' or kind == 'throw') else height
        crossed = bool(dx[w] != 0 and dx[t] != 0 and np.sign(dx[w]) != np.sign(dx[t]))
        f = _first(me.free, s, w + 1)
        e = t + tail
        yield dict(start=int(s), rise=int(w - s), contact=int(t - s), end=int(e),
                   free=int(f - s) if f is not None else -1,
                   down=int(opp.act[s]), move=int(me.act[b]), move_at=int(b - s),
                   way=way, height=height, cross=crossed, kind=kind,
                   meaty=bool(me.act[w] >= FIRST_OWN),
                   objects=int(me.objects[w]),
                   own_act=int(me.act[s]), own_air=bool(me.air[s]),
                   distance=round(float(abs(dx[s]) * 640)),
                   distance_rise=round(float(abs(dx[w]) * 640)),
                   corner=bool(abs(float(obs[s, OPP_X])) > 0.8),
                   prev=int(inputs[s - 1]), inputs=inputs[s:e].copy(),
                   # (what a planner matches its own knockdown to: where the player was)
                   dist=np.round(np.abs(dx[s:e]) * 640).astype(np.int16),
                   air=me.air[s:e].copy())


def answers():
    """{'wake': {character: [[directions, button, needs], ...]}, 'invincible':
    {character: [actions]}}."""
    import advantages
    names = tactics.names()
    wake = {}
    for c in names:
        moves = [[list(dirs), button, needs]
                 for dirs, button, needs, *_ in advantages.wake_moves(c)]
        if moves:
            wake[c] = moves
    inv = {names[c]: sorted(int(a) for a in v[0]) for c, v in tactics.frame_data().items()
           if v[0]}
    return dict(wake=wake, invincible=inv)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--answers', metavar='LIBRARY.npz',
                   help="write that library's answers beside it and stop")
    p.add_argument('--dataset')
    p.add_argument('--out')
    p.add_argument('--within', type=int, default=20)
    p.add_argument('--tail', type=int, default=20)
    p.add_argument('--limit', type=int, default=0, help='the first this many matches (a look)')
    args = p.parse_args()
    if args.answers:
        out = os.path.splitext(os.path.expanduser(args.answers))[0] + '.answers.json'
        a = answers()
        json.dump(a, open(out, 'w'))
        print(f"{out}: reversals on rising for {len(a['wake'])} characters, invincible moves "
              f"for {len(a['invincible'])}")
        return
    if not args.dataset or not args.out:
        p.error('--dataset and --out (or --answers)')
    dataset = os.path.expanduser(args.dataset)
    rows = [r for r in csv.DictReader(open(os.path.join(dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    if args.limit:
        rows = rows[:args.limit]
    found, downs = [], 0
    for r in rows:
        with np.load(os.path.join(dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inputs = z['obs'], z['input']
        act = np.round(obs[:, 50].astype(np.float32)).astype(int)
        downs += len(_runs(np.isin(act, DOWN))[0])
        for m in okizeme_of(obs, inputs, args.within, args.tail):
            m.update(id=r['id'], side=int(r['side']), opponent=r['opponent'])
            found.append(m)
    n = len(found)
    print(f'{n} okizeme that touched the riser within {args.within} steps, of {downs} '
          f'knockdowns in {len(rows)} matches')
    share = lambda f: np.mean([bool(f(m)) for m in found]) if found else 0.0
    for name, f in (('hit', lambda m: m['kind'] == 'hit'), ('guarded', lambda m: m['kind'] == 'guard'),
                    ('throw', lambda m: m['kind'] == 'throw'), ('low', lambda m: m['height'] == 'low'),
                    ('high', lambda m: m['height'] == 'high'), ('mid', lambda m: m['height'] == 'mid'),
                    ('cross', lambda m: m['cross']), ('meaty', lambda m: m['meaty']),
                    ('an object out', lambda m: m['objects'] > 0),
                    ('fly', lambda m: m['way'] == 'fly'), ('dash', lambda m: m['way'] == 'dash'),
                    ('jump', lambda m: m['way'] == 'jump'), ('ground', lambda m: m['way'] == 'ground'),
                    ('corner', lambda m: m['corner'])):
        print(f'  {name}: {share(f):.0%}', end='')
    print()
    for key in ('rise', 'contact', 'free', 'distance'):
        x = np.array([m[key] for m in found])
        print(f'  {key}: 10th {np.percentile(x, 10):.0f}, median {np.median(x):.0f}, '
              f'90th {np.percentile(x, 90):.0f}')
    x = np.array([m['contact'] - m['rise'] for m in found])
    print('  contact after the rising: ' + ', '.join(
        f'{k}: {np.mean(x == k):.0%}' for k in range(0, 9)) + f', later {np.mean(x > 8):.0%}')
    by = {}
    for m in found:
        by.setdefault(hex(m['down']), []).append(m['rise'])
    print('  by the knockdown it began as: ' + ', '.join(
        f'{k}: {len(v)} (rise median {np.median(v):.0f}, {np.percentile(v, 10):.0f}-'
        f'{np.percentile(v, 90):.0f})' for k, v in sorted(by.items(), key=lambda kv: -len(kv[1]))))
    hit_by = {}
    for m in found:
        hit_by.setdefault(f"{m['way']} {m['height']}" + (' cross' if m['cross'] else ''), []).append(
            m['kind'] != 'guard')
    print('  by what it was (count, the share that opened the riser): ' + ', '.join(
        f'{k}: {len(v)} {np.mean(v):.0%}' for k, v in sorted(hit_by.items(), key=lambda kv: -len(kv[1]))))
    out = os.path.expanduser(args.out)
    arrays = ('inputs', 'dist', 'air')
    meta = [{k: v for k, v in m.items() if k not in arrays} for m in found]
    np.savez_compressed(out, meta=json.dumps(meta),
                        **{f'{a}{k}': m[a] for k, m in enumerate(found) for a in arrays})
    print(f'{out}: {n} entries')


if __name__ == '__main__':
    main()
