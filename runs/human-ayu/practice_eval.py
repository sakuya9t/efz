"""Models' combos from the same starts, the same resources: the yardstick of practice
(finetune.py --practice), as combo.py's evaluation is the combo master's.

    python runs/human-ayu/practice_eval.py --models runs/human-ayu/agent-league2-base/model.zip \
        runs/human-ayu/agent-league2-own/model.zip --json runs/human-ayu/eval/practice.json
    python runs/human-ayu/practice_eval.py --models ... --starts $REPLAYS/combo-starts

The starts: 'own' (default), --n first hits of --source (P1) against --vs (P2, Ayu
against Ayu), collected once, in this process (save states load only in the process that
made them), the same for every model; or combo_starts.py's held-out starts (its test
split: people's, with what their players made from them). Each model plays each start
once with the resources it had, then with each of --groups' (evaluate.GROUPS: the RF
gauge's state and bars of power); the defender guards once it can, standing or crouching
at random, as in combo.py.
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np


def own_starts(args):
    from stable_baselines3 import PPO
    from efz_env.sb3 import EfzSB3VecEnv, frozen
    import practice
    pool = practice.StartPool(size=args.n, keep=1.0, seed=args.seed)
    vs = frozen(PPO.load(args.vs, device='cpu'))
    env = EfzSB3VecEnv(args.data, 32, opponent=vs, chars=('ayu', 'ayu'), frame_skip=1,
                       history=args.history, delay=args.delay, max_frames=5 * 3840,
                       reward_round=0.0, reward_match=1.0, seed=args.seed)
    source = PPO.load(args.source, device='cpu')
    practice.fill(pool, env, source, n=args.n, max_steps=200000)
    env.close()
    return pool.starts


def people_starts(args):
    import combo
    rng = np.random.default_rng(0)
    starts = combo.load_starts(args.starts, 'test', 1000, rng)
    replays = args.replays or os.path.dirname(os.path.abspath(args.starts))
    combo.restore(args.data, replays, starts)
    return [st for st in starts if 'state' in st]


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--models', nargs='+', required=True)
    p.add_argument('--starts', default='own', help="'own' or combo_starts.py's folder")
    p.add_argument('--replays', help="the folder with index.csv (default: the starts' parent)")
    p.add_argument('--source', default=os.path.join(HERE, 'agent-league', 'model.zip'),
                   help='own starts: whose first hits')
    p.add_argument('--vs', default=os.path.join(HERE, 'bc-d14.zip'), help='own starts: against whom')
    p.add_argument('--n', type=int, default=200, help='own starts: how many')
    p.add_argument('--groups', nargs='*', default=['blue0', 'red0', 'cyan0', 'cyan3'])
    p.add_argument('--delay', type=int, default=14)
    p.add_argument('--history', type=int, default=16)
    p.add_argument('--limit', type=int, default=600)
    p.add_argument('--seed', type=int, default=7)
    p.add_argument('--json')
    args = p.parse_args()
    import combo
    from stable_baselines3 import PPO
    starts = own_starts(args) if args.starts == 'own' else people_starts(args)
    kinds = {}
    for st in starts:
        import practice
        k = st.get('kind') or practice.kind(st['seen'][-1])
        kinds[k] = kinds.get(k, 0) + 1
    print(f'{len(starts)} starts ({args.starts}): {kinds}', flush=True)
    out = dict(starts=args.starts, n=len(starts), kinds=kinds, models={})
    for path in args.models:
        model = PPO.load(path, device='cpu')
        r = {'as-is': combo.evaluate(args, model, starts)}
        for g in args.groups:
            r[g] = combo.evaluate(args, model, starts, gauges=g)
        out['models'][os.path.relpath(path, REPO)] = r
        line = ' | '.join(f"{g} {v['damage']:.0f}/{v['damage_p90']:.0f}/{v['damage_max']:.0f} "
                          f"IC {v['ic']:.0%}" for g, v in r.items())
        print(f'{os.path.relpath(path, REPO)}: {line}', flush=True)
        if args.starts != 'own':
            v = r['as-is']
            print(f"  people from the same starts: {v['human_damage']:.0f}/{v['human_damage_p90']:.0f}/"
                  f"{v['human_damage_max']:.0f}; better than the player {v['better']:.0%}", flush=True)
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
