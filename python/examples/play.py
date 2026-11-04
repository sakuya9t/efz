"""Plays against an agent, or the game's CPU, in a window; every match is recorded.

    python python/examples/play.py --agent runs/self/model.zip
    python python/examples/play.py --cpu --cpu-level 4 --chars ayu mai

Keys: arrows, Z X C V for A B C D (--keys to change them), or a gamepad; Esc stops.
You are player 2 unless --side 1. Matches go to --record (default recordings/) as
.npz + .json (efz_env.human). Needs pygame-ce; an --agent needs stable-baselines3.
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

from efz_env.human import HumanMatch


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--agent', help='a model.zip from train.py')
    p.add_argument('--cpu', action='store_true', help="play the game's CPU instead")
    p.add_argument('--cpu-level', type=int, default=2)
    p.add_argument('--side', type=int, choices=[1, 2], default=2, help='the side you play')
    p.add_argument('--chars', nargs=2, default=None, metavar=('P1', 'P2'))
    p.add_argument('--stage', type=int, default=None)
    p.add_argument('--rounds', type=int, default=2)
    p.add_argument('--frame-skip', type=int, default=None,
                   help="the agent's frames per decision (default: its training's)")
    p.add_argument('--deterministic', action='store_true', help="the agent's likeliest action")
    p.add_argument('--matches', type=int, default=None)
    p.add_argument('--record', default='recordings')
    p.add_argument('--keys', help='JSON of key names: {"A": "a", "up": "w", ...}')
    p.add_argument('--scale', type=int, default=3)
    args = p.parse_args()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    if not args.agent and not args.cpu:
        sys.exit('pass --agent model.zip, or --cpu')
    policy, frame_skip = None, args.frame_skip
    if args.agent:
        from stable_baselines3 import PPO
        model = PPO.load(args.agent, device='cpu')
        config = os.path.join(os.path.dirname(args.agent), 'config.json')
        if frame_skip is None and os.path.exists(config):
            with open(config) as f:
                frame_skip = json.load(f).get('frame_skip')

        def policy(obs):
            action, _ = model.predict(obs, deterministic=args.deterministic)
            return int(action)
    chars = tuple(None if c == 'any' else c for c in args.chars) if args.chars else (None, None)
    match = HumanMatch(args.data, human=args.side - 1,
                       opponent='cpu' if args.cpu else 'agent', chars=chars, stage=args.stage,
                       frame_skip=frame_skip or 4, record_dir=args.record,
                       agent_name=args.agent or f'cpu-{args.cpu_level}', scale=args.scale,
                       keys=json.loads(args.keys) if args.keys else None,
                       cpu_level=args.cpu_level, rounds_to_win=args.rounds)
    results = match.play(policy, matches=args.matches)
    match.close()
    print(f'matches: {len(results)}, you won {sum(r == -1 for r in results)}, '
          f'lost {sum(r == 1 for r in results)}; recorded in {args.record}')


if __name__ == '__main__':
    main()
