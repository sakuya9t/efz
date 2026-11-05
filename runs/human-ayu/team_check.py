"""Whether players' clones are theirs: on each player's held-out matches, how well the
clone of everyone and the player's own clone predict the player's inputs (bc.py's
measures; lower nll is better).

    python runs/human-ayu/team_check.py --dataset D:/tasogare/efz-replays/datasets/ayu \\
        --base runs/human-ayu/bc-d14.zip --delay 14 runs/human-ayu/team/player*.zip
"""

import argparse
import json
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

from stable_baselines3 import PPO

import bc


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--dataset', required=True)
    p.add_argument('--base', required=True)
    p.add_argument('--delay', type=int, default=0)
    p.add_argument('clones', nargs='+')
    args = p.parse_args()
    base = PPO.load(args.base, device='cpu').policy
    out = {}
    for path in args.clones:
        player = re.search(r'player(\d+)', os.path.basename(path)).group(1)
        a = argparse.Namespace(dataset=args.dataset, players=player, who=None, limit=0,
                               history=16, delay=args.delay, keep=1.0, gamma=0.999)
        data, matches, _ = bc.load(a)
        own = PPO.load(path, device='cpu').policy
        out[player] = dict(matches=matches, base=bc.evaluate(base, data['val']),
                           own=bc.evaluate(own, data['val']))
        print(f"player {player} ({matches} matches): held-out nll {out[player]['base']['nll']:.4f}"
              f" by everyone's clone, {out[player]['own']['nll']:.4f} by its own", flush=True)
    with open(os.path.join(HERE, 'team', 'check.json'), 'w') as f:
        json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
