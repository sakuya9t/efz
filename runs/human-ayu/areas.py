"""The scorecard by area (docs/training-v2.md, "Playing to the opponent's weak areas"):
what a player makes in each situation of tactics.SITUATIONS, by the time spent in it,
against each opponent; how far opponents differ in each (the community's and the
league's); and how many matches it takes to read an opponent's area.

    python runs/human-ayu/areas.py people ~/data/efz-replays --out runs/human-ayu/people-areas.json
    python runs/human-ayu/areas.py table runs/human-ayu/people-areas.json
    python runs/human-ayu/areas.py bench r21 [--drill league combos] [--people runs/human-ayu/people-areas.json]

Everything is from the viewer's side (the agent's, or the community's Ayu player's):
the HP it is ahead by in a situation. The opponent's skill in an area is the other side
of one situation (OPPONENT): what the agent makes on its own okizeme is the opponent's
okizeme defence, what it makes where it came by air is the opponent's anti-air. Three of
the situations are the agent's to enter (CHOSEN: its pressure, its air approach, its
okizeme through how its combos end), three are the opponent's, two are both players'.

`people`: the community's in-sync Ayu matches (datasets/ayu, players.csv: the players'
numbers, no names), by Ayu player, by the opponent's player number and by the opponent's
character: each area's `rate` (HP a second ahead while in it), `share` (of the match) and
`net` (HP a minute, as tactics.exchanges_report's). And per area, over the opponents met
in MIN matches or more: `spread`, the standard deviation of the opponents' true rates (the
spread of their rates less what their own noise explains), `noise`, a match's error on
one opponent's rate, and `matches`, how many it takes for that error to come down to half
the spread: an area an opponent can be read on within a set or not.

`bench`: a benchmark tag's results (bench/TAG/DRILL-OPPONENT.json, evaluate.py's) by
opponent, each area's rate with its error (`net` a minute where a result is older than
the scorecard), and the spread of the league's opponents beside the community's.
"""

import argparse
import collections
import csv
import glob
import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import tactics  # noqa: E402

S = tactics.SITUATIONS
SHORT = dict(zip(S, ('myOki', 'itsOki', 'myPress', 'itsPress', 'I-air', 'it-air', 'bothAir', 'ground')))
# The opponent's skill each situation measures (the viewer's rate there is its weakness).
OPPONENT = {'my okizeme': 'okizeme defence', 'its okizeme': 'okizeme', 'my pressure': 'anti-pressure',
            'its pressure': 'pressure', 'I came by air': 'anti-air', 'it came by air': 'air approach',
            'both in the air': 'air-to-air', 'on the ground': 'ground'}
CHOSEN = ('my okizeme', 'my pressure', 'I came by air')  # the viewer's to enter
MIN = 20  # matches an opponent is counted in the spread from
STEPS = 64  # a second


# The match record's columns, per situation: net HP and live steps (the rate's), episodes,
# those the viewer hit first in and those it was hit first in (tactics.episodes()), and the
# match's live steps (the same in every row).
NET, TIME, EPS, WON, LOST, ALL = range(6)
# What a group is read by: (name, numerator column, denominator column, scale): the rate
# (HP a second in the situation), the shares of its episodes won and lost first, and the
# net HP a minute of the match (tactics.exchanges_report's, as older results have it).
READS = (('rate', NET, TIME, STEPS), ('won', WON, EPS, 1), ('lost', LOST, EPS, 1),
         ('net', NET, ALL, STEPS * 60))


def match_record(c):
    """One player's match (its views' tactics.OBS columns) -> (8, 6): per situation the
    columns above; and its live steps."""
    c = np.asarray(c, np.float32)
    me, op = tactics.Side(c, 0), tactics.Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    mine, theirs = tactics.losses(me, op, live), tactics.losses(op, me, live)
    x = np.zeros((len(S), 6))
    x[:, ALL] = live.sum()
    for k, v in tactics.exchanges(me, op, live, mine, theirs):
        x[S.index(k), NET] += v
    for k, n in tactics.situation_time(me, op, live):
        x[S.index(k), TIME] = n
    for k, first, _ in tactics.episodes(me, op, live, mine, theirs):
        i = S.index(k)
        x[i, EPS] += 1
        x[i, WON] += first > 0
        x[i, LOST] += first < 0
    return x, int(live.sum())


def summary(recs):
    """Matches' records (match_record()'s) -> per area: rate, share, net a minute,
    episodes a minute and the shares won and lost first."""
    a = np.sum([r for r, _ in recs], 0)
    steps = sum(n for _, n in recs)
    per_min = STEPS * 60 / steps if steps else None
    out = dict(matches=len(recs), minutes=round(steps / STEPS / 60, 1),
               net=round(a[:, NET].sum() * per_min) if steps else None)
    for i, k in enumerate(S):
        sec, n = a[i, TIME] / STEPS, a[i, EPS]
        out[k] = dict(rate=round(a[i, NET] / sec, 1) if sec else None,
                      share=round(a[i, TIME] / steps, 4) if steps else None,
                      net=round(a[i, NET] * per_min) if steps else None,
                      entered=round(n * per_min, 2) if steps else None,
                      won=round(a[i, WON] / n, 3) if n else None,
                      lost=round(a[i, LOST] / n, 3) if n else None)
    return out


def components(groups):
    """{group: [match records]} (MIN or more each) -> per area and read (READS): the
    opponents' true spread, a match's noise on one opponent's value, and the matches for
    that noise to be half the spread (the ratio estimator's error over a group's
    matches; the spread is the groups' values' less what that error explains)."""
    out = {}
    for i, k in enumerate(S):
        out[k] = {}
        for name, num, den, scale in READS:
            vals, var, per_match = [], [], []
            for recs in groups.values():
                x = np.array([r[i] for r, _ in recs], float)
                d = x[:, den] / scale
                if d.sum() <= 0:
                    continue
                v = x[:, num].sum() / d.sum()
                e = x[:, num] - v * d
                vals.append(v)
                var.append((e ** 2).sum() / d.sum() ** 2)
                per_match.append(np.sqrt((e ** 2).mean()) / d.mean())
            if len(vals) < 3:
                continue
            spread2 = max(0.0, float(np.var(vals, ddof=1) - np.mean(var)))
            noise = float(np.sqrt(np.mean(np.square(per_match))))
            out[k][name] = dict(groups=len(vals), spread=float(f'{np.sqrt(spread2):.3g}'),
                                noise=float(f'{noise:.3g}'),
                                matches=round(4 * noise ** 2 / spread2, 1) if spread2 > 0 else None)
    return out


def people(args):
    D = os.path.expanduser(args.data)
    who = {(r['id'], r['side']): r['player'] for r in csv.DictReader(open(os.path.join(D, 'players.csv'), encoding='utf-8'))}
    DS = os.path.join(D, 'datasets', 'ayu')
    rows = [r for r in csv.DictReader(open(os.path.join(DS, 'matches.csv'), encoding='utf-8'))
            if r['in_sync'] == '1' and r['winner'] in ('0', '1')]
    G, won = collections.defaultdict(list), collections.defaultdict(list)
    for j, r in enumerate(rows):
        with np.load(os.path.join(DS, f"{r['id']}-{r['side']}.npz")) as z:
            c = z['obs'][:, tactics.OBS]
        rec = match_record(c)
        pl, opp = who.get((r['id'], r['side'])), who.get((r['id'], str(1 - int(r['side']))))
        for key in (('all',), ('player', pl), ('opponent', opp), ('char', r['opponent'])):
            if key[-1] is not None:
                G['/'.join(key)].append(rec)
                won['/'.join(key)].append(r['winner'] == r['side'])
        if (j + 1) % 200 == 0:
            print(f'{j + 1} of {len(rows)}', file=sys.stderr)
    out = dict(groups={k: dict(summary(v), ayu_won=round(float(np.mean(won[k])), 3))
                       for k, v in G.items() if k == 'all' or len(v) >= args.min})
    for kind in ('opponent', 'char', 'player'):
        out[kind] = components({k: v for k, v in G.items() if k.startswith(kind + '/') and len(v) >= args.min})
    json.dump(out, open(args.out, 'w'), indent=1)
    show(out)


UNITS = dict(rate='HP a second in the situation', net='HP a minute', share='% of the match',
             entered='episodes a minute', won='% of its episodes hit first',
             lost='% of its episodes hit first by the opponent')


def row(name, n, vals, fmt='{:+.0f}'):
    return f'{name:16s} {n:>5} ' + ' '.join('%8s' % ('' if v is None else fmt.format(v)) for v in vals)


def show(out, field='rate'):
    scale = 100 if field in ('share', 'won', 'lost') else 1
    fmt = '{:+.0f}' if field in ('rate', 'net') else '{:.0f}' if scale == 100 else '{:.1f}'
    print(f'{field} ({UNITS[field]}), the Ayu player ahead (+); groups with {MIN}+ matches, '
          'by net HP a minute')
    print(' ' * 23 + ' '.join('%8s' % SHORT[k] for k in S))
    G = out['groups']

    def line(k):
        g = G[k]
        return row(k, g['matches'], [None if g[s][field] is None else g[s][field] * scale for s in S], fmt)
    print(line('all'))
    for kind in ('player', 'opponent', 'char'):
        ks = sorted((k for k in G if k.startswith(kind + '/')), key=lambda k: -G[k]['net'])
        print(f'-- by {kind}')
        for k in ks:
            print(line(k))
        c = {s: v.get(field) for s, v in out.get(kind, {}).items() if v.get(field)}
        if c:
            sc = scale if field != 'rate' else 1
            print(row('  spread', '', [c[s]['spread'] * sc if s in c else None for s in S], '{:.1f}'))
            print(row('  noise/match', '', [c[s]['noise'] * sc if s in c else None for s in S], '{:.1f}'))
            print(row('  matches', '', [c[s]['matches'] if s in c else None for s in S], '{:.1f}'))


def bench(args):
    folder = os.path.join(HERE, 'bench', args.tag) if not os.path.isdir(args.tag) else args.tag
    ref = json.load(open(args.people)) if args.people and os.path.exists(args.people) else None
    for drill in args.drill:
        files = sorted(glob.glob(os.path.join(folder, f'{drill}-*.json')))
        if not files:
            continue
        rates, field = {}, None
        print(f'== {args.tag} {drill}')
        for f in files:
            d = json.load(open(f))['vs']
            side, se = d['sides'][0], d['se']['sides'][0]
            areas = side.get('areas')
            field = 'rate' if areas else 'net'
            src, err = (areas, se.get('areas', {})) if areas else (side['net_ledger'], se.get('net_ledger', {}))
            name = os.path.basename(f)[len(drill) + 1:-5]
            cells = []
            for k in S:
                v, e = src[k][field] if src[k] else None, (err.get(k) or {}).get(field)
                rates.setdefault(k, []).append((v, e))
                cells.append('%11s' % ('' if v is None else f'{v:+.0f}' + (f'({e:.0f})' if e is not None else '')))
            print(f'{name:9s} {100 * d["win"]:4.0f} ' + ' '.join(cells))
        print(f'(the agent ahead, HP a {"second in the situation" if field == "rate" else "minute"})')
        spread = {}
        for k in S:
            v = np.array([x for x, _ in rates[k] if x is not None], float)
            e = np.array([y for x, y in rates[k] if x is not None and y is not None], float)
            if len(v) >= 3:
                spread[k] = np.sqrt(max(0.0, np.var(v, ddof=1) - (np.mean(e ** 2) if len(e) else 0)))
        print('spread    ' + '     ' + ' '.join('%11s' % (f'{spread[k]:.0f}' if k in spread else '') for k in S))
        if ref:
            # the community's opponents' spread, in the same unit
            cs = {k: v[field] for k, v in ref['opponent'].items() if field in v}
            print('community ' + '     ' + ' '.join('%11s' % (f'{cs[k]["spread"]:.0f}' if k in cs else '') for k in S))
            # the community's Ayu players, all and the strongest (bench.py's: the most
            # matches won of those with 100 or more), in the same unit
            G = ref['groups']
            best = max((k for k, v in G.items() if k.startswith('player/') and v['matches'] >= 100),
                       key=lambda k: G[k].get('ayu_won', 0), default=None)
            for name, g in (('people', G['all']), ('strongest', G.get(best))):
                if g:
                    print(f'{name:9s} {100 * g.get("ayu_won", 0):4.0f} '
                          + ' '.join('%11s' % f'{g[k][field]:+.0f}' for k in S))
        print('header    ' + '     ' + ' '.join('%11s' % SHORT[k] for k in S))


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = p.add_subparsers(dest='cmd', required=True)
    a = sub.add_parser('people')
    a.add_argument('data', help='the replays folder (datasets/ayu, players.csv)')
    a.add_argument('--out', default=os.path.join(HERE, 'people-areas.json'))
    a.add_argument('--min', type=int, default=MIN)
    a = sub.add_parser('table')
    a.add_argument('file')
    a.add_argument('--field', default='rate', choices=tuple(UNITS))
    a = sub.add_parser('bench')
    a.add_argument('tag')
    a.add_argument('--drill', nargs='+', default=['league', 'combos'])
    a.add_argument('--people', default=os.path.join(HERE, 'people-areas.json'))
    args = p.parse_args()
    if args.cmd == 'people':
        people(args)
    elif args.cmd == 'table':
        show(json.load(open(args.file)), args.field)
    else:
        bench(args)


if __name__ == '__main__':
    main()
