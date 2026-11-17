"""People's Ayu catches as a library: what its players did each time an opponent recovered
in the air out of a combo of theirs (the untech time ran out before the ground and the
opponent pressed out: free again, in the air, beside the player). An entry is the inputs
(relative to facing, as an agent's) from the step of the recovery to the next contact
(a hit, a guard, a throw) and a little after, with what it was (an air throw, a move in
the air, a move from the ground, or no move: a guard held, backing off, a jump), where
both players were at each step (the distance, the opponent's height over the player, the
player in the air or not: what a planner matches its own place to), and how it went. A
planner tries them on copies of the game from a recovery out of its own combo
(airplan.py), as okiplan.py tries oki_library.py's from a knockdown.

    python runs/human-ayu/air_library.py --dataset ~/data/efz-replays/datasets/ayu \
        --out ~/data/efz-replays/air-library.npz

The anchor: the step an opponent in a hit reaction of the player's goes into its air
recovery (src/player.cpp's TryAirRecovery: actions 0x9d forward, 0x9e back), within
--near pixels. The entry runs to --tail steps after the next contact within --look steps,
or --look steps when there is none.

The entries hold the match's id and the side, the opponent's character and numbers: no
player's name.
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
from tactics import AIR_RECOVERY, OBS, Side, _first, _prev

DY, OPP_X, OPP_Y, SELF_X, SELF_Y = 5, 45, 46, 13, 14
JUMP_FORWARD = 0x5
THROWN = range(0x64, 0x7a)
AIR_JUMP = (0xe, 0xf, 0x10)
AIR_THROW_F0 = ('ayu', 'mai', 'akane', 'akiko')  # their air throw is 0xf0, the others' 0xf8


def air_throw(char):
    return 0xf0 if char in AIR_THROW_F0 else 0xf8


def catches(obs, inputs, look=70, tail=20, near=320):
    """A dict per air recovery of the opponent's out of a combo of the viewer's."""
    c = obs[:, OBS].astype(np.float32)
    me, opp = Side(c, 0), Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    px = np.abs(c[:, 18]) * 640
    up = -(obs[:, DY].astype(np.float32)) * 240  # the opponent's height over the viewer
    T = len(obs)
    grab = air_throw(tactics.names()[me.char])
    thrown = np.isin(opp.act, list(THROWN))
    thrown_in = thrown & ~_prev(thrown, False)
    touch = opp.contact | opp.hit | thrown_in
    rec = np.isin(opp.act, AIR_RECOVERY)
    react = (opp.act >= 0x32) & (opp.act < 0x60)
    air_in = me.air & ~_prev(me.air, False)
    for e in np.flatnonzero(rec & _prev(react, False)):
        e = int(e)
        if e < 2 or e + look + tail >= T or px[e] > near or not live[e:e + look + tail].all():
            continue
        hi = e + look + 1
        t, h = _first(touch, e + 1, hi), _first(me.hit, e, hi)
        g = _first(me.new & (me.act == grab), e, hi)   # an air throw tried
        b = _first(me.move, e + 1, hi)                 # a move of its own started
        first = min([x for x in (t, h) if x is not None], default=None)
        if g is not None and (first is None or g <= first):
            cls, at, act = 'air throw', g, grab
        elif b is not None and (first is None or b <= first):
            cls, at, act = ('air move' if me.air[b] else 'ground move'), b, int(me.act[b])
        else:  # no move of its own came first (one already out may still touch)
            at, act = None, 0
            seen = me.act[e:e + look]
            cls = ('none: jump' if air_in[e + 1:e + look].any() else
                   'none: back' if px[min(T - 1, e + look - 1)] > px[e] + 40 else
                   'none: guard' if np.isin(seen, tactics.BLOCKING).mean() > 0.5 else 'none')
        hurt = h is not None and (t is None or h <= t)
        result = ('hurt' if hurt else 'none' if t is None else 'throw' if thrown_in[t] else
                  'hit' if opp.hit[t] else 'guard')
        end = min(T, (h if hurt else t if t is not None else e + look) + tail)
        # The opponent: how long its recovery held it, and what it did first after.
        out = _first(~rec, e, e + look)
        theirs, lead = 'none', -1
        if out is not None:
            lead = out - e
            w = slice(out, min(T, out + 30))
            landed = _first(~opp.air, out, out + 30)
            w = slice(out, landed if landed is not None else min(T, out + 30))
            theirs = ('guard' if (opp.guard[w] | np.isin(opp.act[w], tactics.BLOCKING)).any() and
                      not opp.move[w].any() else
                      'move' if opp.move[w].any() else
                      'dash' if np.isin(opp.act[w], tactics.AIRDASH).any() else
                      'jump' if (np.isin(opp.act[w], AIR_JUMP) & opp.new[w]).any() else 'fall')
        f = _first(me.free, e, hi)
        yield dict(start=e, cls=cls, result=result, move=act,
                   move_at=int(at - e) if at is not None else -1,
                   contact=int(t - e) if t is not None else -1,
                   busy=bool(me.act[e] >= tactics.FIRST_OWN),
                   free=int(f - e) if f is not None else -1,
                   own_air=bool(me.air[e]), back=bool(opp.act[e] == 0x9e),
                   lead=int(lead), theirs=theirs,
                   distance=round(float(px[e])), height=round(float(up[e])),
                   corner=bool(abs(float(obs[e, OPP_X])) > 0.8),
                   prev=int(inputs[e - 1]), inputs=inputs[e:end].copy(),
                   dist=np.round(px[e:end]).astype(np.int16),
                   up=np.round(up[e:end]).astype(np.int16), air=me.air[e:end].copy())


def jumps(obs, inputs, look=90, tail=20, near=320):
    """A dict per jump of the opponent's at the viewer (a forward jump begun within
    `near` pixels, the viewer on the ground and not being hit), from the step the jump
    begins to the next contact (an attack of either's that hit or was guarded, a throw)
    and `tail` steps more, or to `look` steps when there is none."""
    c = obs[:, OBS].astype(np.float32)
    me, opp = Side(c, 0), Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    px = np.abs(c[:, 18]) * 640
    side = np.sign(c[:, 18])
    up = -(obs[:, DY].astype(np.float32)) * 240
    T = len(obs)
    grab = air_throw(tactics.names()[me.char])
    thrown = np.isin(opp.act, list(THROWN))
    thrown_in = thrown & ~_prev(thrown, False)
    caught = np.isin(me.act, list(THROWN))
    caught_in = caught & ~_prev(caught, False)
    touch = opp.contact | opp.hit | thrown_in      # the viewer's attack met the jumper
    met = me.contact | me.hit | caught_in          # the jumper's met the viewer
    down = np.isin(me.act, tactics.DOWN)
    air_in = me.air & ~_prev(me.air, False)
    for e in np.flatnonzero(opp.new & (opp.act == JUMP_FORWARD)):
        e = int(e)
        if e < 2 or e + look + tail >= T or px[e] > near or not live[e:e + look + tail].all():
            continue
        if me.air[e] or me.hitstun[e] or down[e] or caught[e]:
            continue
        hi = e + look + 1
        t, h = _first(touch, e + 1, hi), _first(met, e + 1, hi)
        first = min([x for x in (t, h) if x is not None], default=None)
        stop = first if first is not None else e + look
        g = _first(me.new & (me.act == grab), e, stop + 1)
        b = _first(me.move, e + 1, stop + 1)
        if g is not None:
            cls, at, act = 'air throw', g, grab
        elif b is not None:
            cls, at, act = ('air move' if me.air[b] else 'ground move'), b, int(me.act[b])
        else:
            at, act = None, 0
            seen = me.act[e:stop + 1]
            last = me.act[max(e, stop - 10):stop + 1]
            cls = ('none: jump' if air_in[e + 1:stop + 1].any() else
                   'none: backdash' if (seen == tactics.BACKDASH).any() else
                   'none: dash' if (seen == tactics.DASH).any() else
                   'none: guard' if (np.isin(last, tactics.BLOCKING) |
                                     np.isin(last, tactics.GUARDS)).mean() > 0.5 else 'none')
        mine_first = t is not None and (h is None or t < h)
        result = ('none' if first is None else
                  ('throw' if thrown_in[t] else 'hit' if opp.hit[t] else 'made to guard')
                  if mine_first else
                  ('thrown' if caught_in[h] else 'hurt' if me.hit[h] else 'guarded'))
        end = min(T, stop + tail)
        # The jumper: its attack in the air (how long after the jump began), or none and
        # what it did on landing; whether it crossed the viewer's side.
        land = _first(~opp.air, e + 8, hi)
        w_end = land if land is not None else stop + 1
        a = _first(opp.move & opp.air, e, w_end + 1)
        if a is not None:
            theirs, move_step = 'attack', a - e
        elif (np.isin(opp.act[e:w_end], AIR_JUMP) | np.isin(opp.act[e:w_end], tactics.AIRDASH)).any():
            theirs, move_step = 'again', -1
        else:
            m2 = _first(opp.move, w_end, w_end + 12) if land is not None else None
            theirs = 'empty' if m2 is None else \
                'empty throw' if opp.act[m2] == tactics.THROW else 'empty move'
            move_step = -1
        crossed = bool((side[e:w_end + 1] * side[e] < 0).any()) if side[e] != 0 else False
        yield dict(start=e, cls=cls, result=result, move=act,
                   move_at=int(at - e) if at is not None else -1,
                   contact=int(first - e) if first is not None else -1,
                   land=int(land - e) if land is not None else -1,
                   own_act=int(me.act[e]), theirs=theirs, their_move=int(move_step),
                   crossed=crossed, distance=round(float(px[e])),
                   corner=bool(abs(float(obs[e, SELF_X])) > 0.8),
                   prev=int(inputs[e - 1]), inputs=inputs[e:end].copy(),
                   dist=np.round(px[e:end]).astype(np.int16),
                   up=np.round(up[e:end]).astype(np.int16), air=me.air[e:end].copy())


def _save(out, found):
    arrays = ('inputs', 'dist', 'up', 'air')
    meta = [{k: v for k, v in m.items() if k not in arrays} for m in found]
    np.savez_compressed(out, meta=json.dumps(meta),
                        lengths=np.array([len(m['inputs']) for m in found], np.int32),
                        inputs=np.concatenate([m['inputs'] for m in found]).astype(np.uint8),
                        dist=np.concatenate([m['dist'] for m in found]),
                        up=np.concatenate([m['up'] for m in found]),
                        air=np.concatenate([m['air'] for m in found]))
    print(f'{out}: {len(found)} entries')


def jumps_main(args, rows, dataset):
    found = []
    for r in rows:
        with np.load(os.path.join(dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inputs = z['obs'], z['input']
        for m in jumps(obs, inputs, args.look, args.tail, args.near):
            m.update(id=r['id'], side=int(r['side']), opponent=r['opponent'])
            found.append(m)
    n = len(found)
    print(f"{n} jumps at the player, in {len(rows)} matches")
    for key in ('distance', 'land', 'contact'):
        x = np.array([m[key] for m in found if m[key] >= 0])
        print(f'  {key}: 10th {np.percentile(x, 10):.0f}, median {np.median(x):.0f}, '
              f'90th {np.percentile(x, 90):.0f}')
    theirs = collections.Counter(m['theirs'] for m in found)
    print('  what the jumper did: ' + ', '.join(f'{k} {v / n:.0%}' for k, v in theirs.most_common()) +
          f"; crossed sides {np.mean([m['crossed'] for m in found]):.0%}")
    at = np.array([m['their_move'] for m in found if m['their_move'] >= 0])
    print(f'  its attack, steps after the jump began: 10th {np.percentile(at, 10):.0f}, median '
          f'{np.median(at):.0f}, 90th {np.percentile(at, 90):.0f}')
    results = ('hit', 'throw', 'made to guard', 'guarded', 'hurt', 'thrown', 'none')
    by = collections.defaultdict(list)
    for m in found:
        by[m['cls']].append(m)
    print('  by what the player did (count, share; how it went: ' + ', '.join(results) + '):')
    for cls, ms in sorted(by.items(), key=lambda kv: -len(kv[1])):
        res = collections.Counter(m['result'] for m in ms)
        print(f"    {cls:15s} {len(ms):5d} {len(ms) / n:5.1%}   " +
              '  '.join(f'{res[k] / len(ms):4.0%}' for k in results) +
              f"   its move at step {np.median([m['move_at'] for m in ms]):.0f}")
    for k in theirs:
        ms = [m for m in found if m['theirs'] == k]
        res = collections.Counter(m['result'] for m in ms)
        print(f"    against {k:11s} ({len(ms)}): " + ', '.join(f'{r} {res[r] / len(ms):.0%}' for r in results))
    _save(os.path.expanduser(args.out), found)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--kind', choices=('recovery', 'jump'), default='recovery',
                   help="the opponent's air recoveries out of the player's combos, or its "
                        'jumps at the player')
    p.add_argument('--dataset', required=True)
    p.add_argument('--out', required=True)
    p.add_argument('--look', type=int, default=70)
    p.add_argument('--tail', type=int, default=20)
    p.add_argument('--near', type=int, default=320)
    p.add_argument('--limit', type=int, default=0, help='the first this many matches (a look)')
    args = p.parse_args()
    dataset = os.path.expanduser(args.dataset)
    rows = [r for r in csv.DictReader(open(os.path.join(dataset, 'matches.csv'),
                                           encoding='utf-8')) if r['in_sync'] == '1']
    if args.limit:
        rows = rows[:args.limit]
    if args.kind == 'jump':
        if args.look == 70:
            args.look = 90
        return jumps_main(args, rows, dataset)
    found = []
    for r in rows:
        with np.load(os.path.join(dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs, inputs = z['obs'], z['input']
        for m in catches(obs, inputs, args.look, args.tail, args.near):
            m.update(id=r['id'], side=int(r['side']), opponent=r['opponent'])
            found.append(m)
    n = len(found)
    print(f"{n} air recoveries out of the player's combos, in {len(rows)} matches")
    for key in ('lead', 'distance', 'height', 'free'):
        x = np.array([m[key] for m in found])
        print(f'  {key}: 10th {np.percentile(x, 10):.0f}, median {np.median(x):.0f}, '
              f'90th {np.percentile(x, 90):.0f}')
    print(f"  the player still in a move at the recovery: {np.mean([m['busy'] for m in found]):.0%}; "
          f"in the air: {np.mean([m['own_air'] for m in found]):.0%}; the recovery backward: "
          f"{np.mean([m['back'] for m in found]):.0%}")
    by = collections.defaultdict(list)
    for m in found:
        by[m['cls']].append(m)
    print('  by what the player did (count, share; how it went: caught (a hit or a throw), '
          'guarded, no contact, the player hit first):')
    for cls, ms in sorted(by.items(), key=lambda kv: -len(kv[1])):
        res = collections.Counter(m['result'] for m in ms)
        print(f"    {cls:14s} {len(ms):5d} {len(ms) / n:5.1%}   caught "
              f"{(res['hit'] + res['throw']) / len(ms):4.0%}  guarded {res['guard'] / len(ms):4.0%}  "
              f"none {res['none'] / len(ms):4.0%}  hurt {res['hurt'] / len(ms):4.0%}   "
              f"its move at step {np.median([m['move_at'] for m in ms]):.0f}")
    theirs = collections.Counter(m['theirs'] for m in found)
    print('  what the opponent did first out of its recovery: ' +
          ', '.join(f'{k} {v / n:.0%}' for k, v in theirs.most_common()))
    for k in theirs:
        ms = [m for m in found if m['theirs'] == k]
        res = collections.Counter(m['result'] for m in ms)
        print(f"    {k:6s}: caught {(res['hit'] + res['throw']) / len(ms):4.0%}, the player hurt "
              f"{res['hurt'] / len(ms):4.0%}")
    _save(os.path.expanduser(args.out), found)


if __name__ == '__main__':
    main()
