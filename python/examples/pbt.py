"""Population-based training: a population of PPO agents in a league (efz_env.pbt).

    python python/examples/pbt.py --data "$EFZ_DIR" --out runs/pbt --population 6 --generations 20
    python python/examples/play.py --data "$EFZ_DIR" --agent runs/pbt/best.zip

Each generation trains every member (against the CPU, each other and older versions),
rates them all by Elo (the CPU at --cpu-level is 1000), and has the bottom quarter take
the weights and perturbed settings of the top quarter. Run it again with the same --out
to continue (raise --generations). Needs stable-baselines3 and torch.
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

import torch

from efz_env.pbt import Population


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default='runs/pbt')
    p.add_argument('--population', type=int, default=6)
    p.add_argument('--generations', type=int, default=20, help='run until this many are done')
    p.add_argument('--steps', type=float, default=2e5, help='steps per member per generation')
    p.add_argument('--envs', type=int, default=32, help='matches per member at once')
    p.add_argument('--threads', type=int, default=0)
    p.add_argument('--torch-threads', type=int, default=4)
    p.add_argument('--frame-skip', type=int, default=4)
    p.add_argument('--chars', nargs=2, default=None, metavar=('P1', 'P2'))
    p.add_argument('--char-pool', nargs='+', default=None)
    p.add_argument('--stage', type=int, default=None)
    p.add_argument('--cpu-level', type=int, default=2)
    p.add_argument('--cpu-share', type=float, default=0.25,
                   help="share of training matches against the game's CPU")
    p.add_argument('--opponents', type=int, default=3, help='opponents per member per generation')
    p.add_argument('--eval-matches', type=int, default=32, help='matches per pairing when rating')
    p.add_argument('--truncation', type=float, default=0.25,
                   help='share replaced each generation (and share copied from)')
    p.add_argument('--seed', type=int, default=0)
    p.add_argument('--device', default='cpu')
    args = p.parse_args()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    torch.set_num_threads(args.torch_threads)
    chars = tuple(None if c == 'any' else c for c in args.chars) if args.chars else (None, None)
    pop = Population(args.out, args.data, size=args.population,
                     steps_per_generation=args.steps, num_envs=args.envs,
                     num_threads=args.threads, frame_skip=args.frame_skip, chars=chars,
                     char_pool=args.char_pool, stage=args.stage, cpu_level=args.cpu_level,
                     cpu_share=args.cpu_share, opponents_per_member=args.opponents,
                     eval_matches=args.eval_matches, truncation=args.truncation,
                     seed=args.seed, device=args.device)
    try:
        pop.run(args.generations)
    except KeyboardInterrupt:
        print(f"stopped; {args.out} resumes from generation {pop.state['generation']}")
    print('best:', os.path.join(args.out, 'best.zip'))


if __name__ == '__main__':
    main()
