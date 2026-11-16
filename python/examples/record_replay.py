"""Records a match between two agents into one of EFZ's replay slots.

    python python/examples/record_replay.py --data "$EFZ_DIR" --p1 runs/a/model.zip --p2 runs/b/model.zip --slot 1-1

The game writes replay/data<page>-<slot>.rep in the EFZ folder (or --save-dir), as the
replay menu's record item does, and EFZ's REPLAY menu plays it back: pick the page and
slot there. Both sides are agents (a model.zip, 'random' or 'idle'): a replay can't hold
the game's CPU, whose decisions aren't in it. The match steps every frame; each model
decides every frame_skip frames of its config.json (holding its choice in between),
with the input history it was trained with (efz_env.agent). A slot that holds a replay is left alone
unless --overwrite. Needs stable-baselines3 for model.zip players.
"""

import argparse
import itertools
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

import numpy as np

from efz_env import ActionTable, EfzVecEnv, character_names


class Scripted:
    """'idle' or 'random', deciding every frame_skip frames as a model would."""

    def __init__(self, kind, rng, frame_skip):
        self.kind, self.rng, self.frame_skip = kind, rng, frame_skip
        self.table = ActionTable()
        self.last = None

    def controls(self, obs, step):
        if self.last is None or step % self.frame_skip == 0:
            self.last = (np.zeros(len(obs), np.int64) if self.kind == 'idle'
                         else self.rng.integers(0, len(self.table), len(obs)))
        return self.table.to_bytes(self.last)

    def observe(self, controls):
        pass


def player(spec, rng, frame_skip):
    if spec in ('idle', 'random'):
        return Scripted(spec, rng, frame_skip or 4)
    from efz_env.agent import Agent
    return Agent(spec, frame_skip=frame_skip)


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
                   help="frames per decision (default: each model's training's, else 4)")
    p.add_argument('--minutes', type=float, default=10, help='cut the match short after')
    p.add_argument('--seed', type=int, default=0)
    p.add_argument('--save-dir', default=None, help='write replay/ here instead of the EFZ folder')
    p.add_argument('--overwrite', action='store_true')
    args = p.parse_args()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    page, slot = (int(x) for x in args.slot.split('-'))
    rng = np.random.default_rng(args.seed)
    players = [player(args.p1, rng, args.frame_skip), player(args.p2, rng, args.frame_skip)]
    env = EfzVecEnv(args.data, 1, frame_skip=1, rounds_to_win=args.rounds,
                    max_frames=int(args.minutes * 60 * 64), autoreset='disabled',
                    seed=args.seed, num_threads=1, save_dir=args.save_dir)
    env.set_matches(chars=tuple(args.chars), stage=args.stage, cpu=(False, False))
    path = env.record(0, page, slot, overwrite=args.overwrite)
    obs = env.reset()
    controls = np.zeros((1, 2), np.uint8)
    for step in itertools.count():
        for side, p in enumerate(players):
            controls[:, side] = p.controls(obs[:, side], step)
        obs, _, terminated, truncated, info = env.step(controls)
        for side, p in enumerate(players):
            p.observe(info['input'][:, side])
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
