"""Plays against an agent, or the game's CPU, in a window; every match is recorded.

    python python/examples/play.py --agent runs/self/model.zip
    python python/examples/play.py --cpu --cpu-level 4 --chars ayu mai

    python python/examples/play.py --agent runs/human-ayu/model.zip --assist combo-library.npz

Keys: arrows, Z X C V for A B C D (--keys to change them), or a gamepad; Esc stops.
You are player 2 unless --side 1. Matches go to --record (default recordings/) as
.npz + .json (efz_env.human). Needs pygame-ce; an --agent needs stable-baselines3.

--assist: the agent's combos from built-in routes (runs/human-ayu/combo_support.py's
LiveRoutes): once it sees its hit, as late as it sees everything, people's combos from the
library (runs/human-ayu/combo_library.py's) that begin with the move that hit are tried on
copies of the game and the most damaging is played, if it beats the agent's own play.
With --chooser (runs/human-ayu/combo_net.py's chooser.pt, trained for that agent and
library) nothing is tried on copies: a network says from the agent's view which combo to
play (ChosenRoutes): no second process, a little less damage.
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
    p.add_argument('--assist', metavar='LIBRARY',
                   help="the agent's combos from the built-in routes of this library")
    p.add_argument('--assist-victims', nargs='+', metavar='CHAR',
                   help='--assist only against these characters')
    p.add_argument('--chooser', metavar='CHOOSER.pt',
                   help="--assist's combo chosen by this network, not on copies of the game")
    args = p.parse_args()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    if not args.agent and not args.cpu:
        sys.exit('pass --agent model.zip, or --cpu')
    if args.assist and not args.agent:
        sys.exit('--assist: the combos of an --agent')
    if args.chooser and not args.assist:
        sys.exit("--chooser: with --assist LIBRARY (the chooser's library)")
    policy, routes, frame_skip = None, None, args.frame_skip
    if args.agent:
        # As trained: deciding every frame_skip frames, with its input history.
        from efz_env.agent import Agent
        policy = Agent(args.agent, deterministic=args.deterministic, frame_skip=frame_skip)
        frame_skip = policy.frame_skip
        if args.assist:
            sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'runs',
                                            'human-ayu'))
            import combo_support
            if args.chooser:
                import combo_net
                routes = combo_support.ChosenRoutes(policy, combo_net.NetPlanner(
                    combo_net.load_routes(args.assist), policy.model, args.chooser))
            else:
                routes = combo_support.LiveRoutes(policy, args.data, args.assist,
                                                  victims=args.assist_victims)
    chars = tuple(None if c == 'any' else c for c in args.chars) if args.chars else (None, None)
    match = HumanMatch(args.data, human=args.side - 1,
                       opponent='cpu' if args.cpu else 'agent', chars=chars, stage=args.stage,
                       frame_skip=frame_skip or 4, record_dir=args.record,
                       agent_name=args.agent + ' +routes' * bool(routes) +
                       ' (chooser)' * bool(args.chooser) if args.agent
                       else f'cpu-{args.cpu_level}', scale=args.scale,
                       keys=json.loads(args.keys) if args.keys else None,
                       cpu_level=args.cpu_level, rounds_to_win=args.rounds)
    if routes:  # (its planner follows the match: what set_matches was given)
        routes.attach(match, chars=chars, stage=args.stage, cpu=(False, False))
        policy = routes
    results = match.play(policy, matches=args.matches)
    match.close()
    if routes:
        routes.close()
        print('routes:', json.dumps(routes.stats()))
    print(f'matches: {len(results)}, you won {sum(r == -1 for r in results)}, '
          f'lost {sum(r == 1 for r in results)}; recorded in {args.record}')


if __name__ == '__main__':
    main()
