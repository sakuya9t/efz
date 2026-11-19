"""The HP ledger (tactics.losses) of the community's Ayu players, by player and by the opponents they met, by win rate
(aggregates by the collection's player numbers; no names), written to people-ledger.json:
    python runs/human-ayu/people_ledger.py . ~/data/efz-replays runs/human-ayu/people-ledger.json"""
import csv, json, os, sys, collections
import numpy as np
W, D, OUT = sys.argv[1:4]
sys.path.insert(0, os.path.join(W, 'python')); sys.path.insert(0, os.path.join(W, 'runs', 'human-ayu'))
import tactics as tc
who = {(r['id'], r['side']): r['player'] for r in csv.DictReader(open(os.path.join(D, 'players.csv'), encoding='utf-8'))}
DS = os.path.join(D, 'datasets', 'ayu')
rows = [r for r in csv.DictReader(open(os.path.join(DS, 'matches.csv'), encoding='utf-8')) if r['in_sync'] == '1' and r['winner'] in ('0', '1')]
G = collections.defaultdict(lambda: dict(n=0, won=0, frames=0, lose=[], deal=[], ex=[]))
for r in rows:
    with np.load(os.path.join(DS, f"{r['id']}-{r['side']}.npz")) as z:
        c = z['obs'][:, tc.OBS].astype(np.float32)
    me, op = tc.Side(c, 0), tc.Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    lose, deal = tc.losses(me, op, live), tc.losses(op, me, live)
    ex = tc.exchanges(me, op, live, lose, deal)
    won = r['winner'] == r['side']
    pl, opp = who.get((r['id'], r['side'])), who.get((r['id'], str(1 - int(r['side']))))
    for key in (('all',), ('player', pl), ('opponent', opp)):
        if key[-1] is None: continue
        g = G[key]; g['n'] += 1; g['won'] += won; g['frames'] += len(c); g['lose'] += lose; g['deal'] += deal; g['ex'] += ex
out = {}
for key, g in G.items():
    if g['n'] < 30: continue
    per = 64 * 60 / g['frames']
    out['/'.join(key)] = dict(matches=g['n'], ayu_won=round(g['won'] / g['n'], 3), minutes=round(g['frames'] / 3840),
                              ledger=tc.losses_report(g['lose'], per), dealt_ledger=tc.losses_report(g['deal'], per),
                              net_ledger=tc.exchanges_report(g['ex'], per))
json.dump(out, open(OUT, 'w'), indent=1)
def row(k):
    v = out[k]; L, Dl = v['ledger'], v['dealt_ledger']
    a = L['kinds'].get('in the air, attacking', dict(hp=0, times=0, each=0))
    N = v['net_ledger']
    return (f"{k:16s} {v['matches']:4d} matches, Ayu won {v['ayu_won']:.0%}: deals {Dl['hp']:5d} loses {L['hp']:5d} | net {N['net']:+5d}: "
            + ', '.join(f"{s} {N[s]['net']:+d}" for s in tc.SITUATIONS))
print(row('all'))
for k in sorted((k for k in out if k.startswith('player')), key=lambda k: -out[k]['ayu_won']): print(row(k))
print('by the opponent they met:')
for k in sorted((k for k in out if k.startswith('opponent')), key=lambda k: out[k]['ayu_won']): print(row(k))
