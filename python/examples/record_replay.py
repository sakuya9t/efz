"""Records a match between two agents into one of EFZ's replay slots.

    python python/examples/record_replay.py --data "$EFZ_DIR" --p1 runs/a/model.zip --p2 runs/b/model.zip --slot 1-1

The game writes replay/data<page>-<slot>.rep in the EFZ folder (or --save-dir), as the
replay menu's record item does, and EFZ's REPLAY menu plays it back: pick the page and
slot there. Both sides are agents (a model.zip, 'random' or 'idle'): a replay can't hold
the game's CPU, whose decisions aren't in it. A slot that holds a replay is left alone
unless --overwrite. Needs stable-baselines3 for model.zip players.
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

import numpy as np

from efz_env import ActionTable, EfzVecEnv, character_names


def player(spec, rng):
    if spec == 'idle':
        return lambda obs: np.zeros(len(obs), np.int64), None
    if spec == 'random':
        return lambda obs: rng.integers(0, 45, len(obs)), None
    from stable_baselines3 import PPO
    model = PPO.load(spec, device='cpu')
    frame_skip = None
    config = os.path.join(os.path.dirname(spec), 'config.json')
    if os.path.exists(config):
        with open(config) as f:
            frame_skip = json.load(f).get('frame_skip')
    return (lambda obs: model.predict(obs, deterministic=False)[0]), frame_skip


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--p1', required=True, help="a model.zip, 'random' or 'idle'")
    p.add_argument('--p2', required=True, help="a model.zip, 'random' or 'idle'")
    p.add_argument('--slot', default='1-1', help='page-slot of the REPLAY menu, 1-9 each')
    p.add_argument('--chars', nargs=2, default=('ayu', 'ayu'), metavar=('P1', 'P2'))
    p.add_argument('--stage', type=int, default=None)
    p.add_argument('--rounds', type=int, default=2, help='rounds to win the match')
    p.add_argument('--frame-skip', type=int, default=None,
                   help="frames per decision (default: the models' training's, else 4)")
    p.add_argument('--minutes', type=float, default=10, help='cut the match short after')
    p.add_argument('--seed', type=int, default=0)
    p.add_argument('--save-dir', default=None, help='write replay/ here instead of the EFZ folder')
    p.add_argument('--overwrite', action='store_true')
    args = p.parse_args()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    page, slot = (int(x) for x in args.slot.split('-'))
    rng = np.random.default_rng(args.seed)
    (act1, fs1), (act2, fs2) = player(args.p1, rng), player(args.p2, rng)
    frame_skip = args.frame_skip or fs1 or fs2 or 4
    env = EfzVecEnv(args.data, 1, frame_skip=frame_skip, rounds_to_win=args.rounds,
                    max_frames=int(args.minutes * 60 * 64), autoreset='disabled',
                    seed=args.seed, num_threads=1, save_dir=args.save_dir)
    env.set_matches(chars=tuple(args.chars), stage=args.stage, cpu=(False, False))
    path = env.record(0, page, slot, overwrite=args.overwrite)
    table = ActionTable()
    obs = env.reset()
    controls = np.zeros((1, 2), np.uint8)
    while True:
        controls[0, 0] = table.table[int(act1(obs[:, 0])[0])]
        controls[0, 1] = table.table[int(act2(obs[:, 1])[0])]
        obs, _, terminated, truncated, info = env.step(controls)
        if terminated[0] or truncated[0]:
            break
    i = info[0]
    env.close()
    names = character_names()
    winner = {0: f'P1 ({args.p1})', 1: f'P2 ({args.p2})'}.get(int(i['winner']), 'nobody (cut short)')
    print(f"recorded {path}: {names[i['chars'][0]]} vs {names[i['chars'][1]]} on stage "
          f"{int(i['stage'])}, {int(i['frame']) / 64:.0f} s; rounds {[int(x) for x in i['rounds_won']]}, "
          f"won by {winner}. In EFZ: REPLAY, page {page}, slot {slot}.")


if __name__ == '__main__':
    main()
