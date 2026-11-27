"""Fit starting values for round 28's raw-special accounts from paired replay branches."""
import argparse
from collections import defaultdict
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[2] / 'python'))
from efz_env.export import RISK_OPTIONS, export_agent, read_agent


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--agent', required=True, type=Path)
    parser.add_argument('--model', required=True, type=Path)
    parser.add_argument('--trials', nargs='+', required=True, type=Path)
    parser.add_argument('--out', required=True, type=Path)
    args = parser.parse_args()
    _, keys, _ = read_agent(args.agent)
    prior = {int(a,0):float(v) for a,v in (s.split(':') for s in keys['risk_moves'].split(','))}
    returns = defaultdict(list)
    fights = defaultdict(set)
    for path in args.trials:
        for line in path.read_text().splitlines():
            row = json.loads(line)
            move = row['labels'][0]['commit']
            options = row['options']
            returns[move].append(options['base']['net'] - options['release']['net'])
            fights[move].add(row['fight'])
    # Eight prior uses stabilize the estimate. A previously untracked move starts
    # at +150 HP (88% allowed under the standard 75-HP temperature).
    for move, values in sorted(returns.items()):
        if len(fights[move]) >= 3:
            prior[move] = (8*prior.get(move,150.)+sum(values))/(8+len(values))
            print(hex(move),len(values),'paired uses;',round(prior[move]),'HP prior')
    risk = {k: type(v)(keys['risk_'+k]) for k,v in RISK_OPTIONS.items() if 'risk_'+k in keys}
    risk['moves'] = prior
    check = export_agent(args.model,args.out,name='Ayu',version='round28b',parts_from=args.agent,
                         keep=('routes','chooser','okiplan','airthrow','rise'),risk=risk)
    print(check)


if __name__=='__main__':
    main()
