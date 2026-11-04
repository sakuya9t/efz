"""Trains an agent with Stable-Baselines3's PPO.

    python python/examples/train.py --opponent cpu  --steps 2e6 --out runs/vs-cpu
    python python/examples/train.py --opponent self --steps 2e6 --out runs/self
    python python/examples/train.py --opponent past --steps 2e6 --out runs/past
    python python/examples/train.py --opponent human --load runs/self/model.zip --out runs/human

--opponent:
    cpu    player 1 learns against the game's CPU (--cpu-level).
    self   both players are the policy being trained (one policy, either side).
    past   player 1 learns against a frozen copy of itself, refreshed every --refresh steps.
    human  you play player 2 in a window (efz_env.human; pygame-ce) and the agent learns
           from those matches as they are played; every match is also recorded
           (--record) for learning from later. Start from a trained agent (--load):
           a new one only flails.

The run's folder (--out) gets model.zip (and checkpoints), config.json (what play.py
and later runs need to use the model the same way) and TensorBoard logs if tensorboard
is installed. --load continues from a model.zip. Needs stable-baselines3 and torch.
The game's data: --data or $EFZ_DATA.
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))  # python/, for a checkout without pip install

import numpy as np
import torch
from stable_baselines3 import PPO
from stable_baselines3.common.callbacks import BaseCallback, CallbackList, CheckpointCallback

from efz_env import ActionTable
from efz_env.sb3 import EfzSB3VecEnv, frozen


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--opponent', choices=['cpu', 'self', 'past', 'human'], default='cpu')
    p.add_argument('--envs', type=int, default=64, help='matches stepped at once')
    p.add_argument('--threads', type=int, default=0, help='threads stepping them (0: all)')
    p.add_argument('--torch-threads', type=int, default=4)
    p.add_argument('--steps', type=float, default=2e6, help='agent steps to train for')
    p.add_argument('--frame-skip', type=int, default=4, help='frames per decision')
    p.add_argument('--chars', nargs=2, default=None, metavar=('P1', 'P2'),
                   help="characters ('ayu', 'mai'...; 'any' for random); default random")
    p.add_argument('--char-pool', nargs='+', default=None, help='random characters from these')
    p.add_argument('--stage', type=int, default=None)
    p.add_argument('--cpu-level', type=int, default=2)
    p.add_argument('--rounds', type=int, default=2, help='rounds to win a match')
    p.add_argument('--max-frames', type=int, default=64 * 240, help='a match is cut short after')
    p.add_argument('--seed', type=int, default=0)
    p.add_argument('--load', help='a model.zip to continue from')
    p.add_argument('--out', default='runs/ppo', help="the run's folder")
    p.add_argument('--save-every', type=float, default=5e5, help='checkpoint every (steps)')
    p.add_argument('--refresh', type=float, default=2e5, help='past: refresh the copy every (steps)')
    # PPO
    p.add_argument('--lr', type=float, default=2.5e-4)
    p.add_argument('--n-steps', type=int, default=None, help='steps per env per update')
    p.add_argument('--batch', type=int, default=None)
    p.add_argument('--epochs', type=int, default=4)
    p.add_argument('--gamma', type=float, default=0.99)
    p.add_argument('--ent', type=float, default=0.01)
    p.add_argument('--device', default='auto')
    # human
    p.add_argument('--human-side', type=int, choices=[1, 2], default=2)
    p.add_argument('--keys', help='JSON of key names: {"A": "a", "up": "w", ...}')
    p.add_argument('--scale', type=int, default=3, help='window size: 320x240 times this')
    p.add_argument('--record', default=None, help='where human matches are recorded '
                   '(default: <out>/recordings)')
    return p.parse_args()


def chars_of(args):
    if not args.chars:
        return (None, None)
    return tuple(None if c == 'any' else c for c in args.chars)


class RefreshOpponent(BaseCallback):
    """--opponent past: the opponent becomes a frozen copy of the policy every `every` steps."""

    def __init__(self, venv, every):
        super().__init__()
        self.venv, self.every, self.last = venv, int(every), 0

    def _on_step(self):
        if self.num_timesteps - self.last >= self.every:
            self.venv.set_opponent(frozen(self.model))
            self.last = self.num_timesteps
        return True


def main():
    args = parse()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    torch.set_num_threads(args.torch_threads)
    os.makedirs(args.out, exist_ok=True)
    table = ActionTable()
    config = dict(frame_skip=args.frame_skip, cpu_level=args.cpu_level,
                  rounds_to_win=args.rounds, max_frames=args.max_frames)
    callbacks = []
    human = args.opponent == 'human'
    if human:
        from efz_env.human import HumanMatch, HumanVecEnv, LearningNotice, Quit
        if not args.load:
            print('note: no --load: the agent starts from nothing and will only flail')
        match = HumanMatch(args.data, human=args.human_side - 1, opponent='agent',
                           chars=chars_of(args), char_pool=args.char_pool, stage=args.stage,
                           frame_skip=args.frame_skip, action_table=table,
                           record_dir=args.record or os.path.join(args.out, 'recordings'),
                           agent_name=args.load or 'new', scale=args.scale,
                           keys=json.loads(args.keys) if args.keys else None,
                           cpu_level=args.cpu_level, rounds_to_win=args.rounds,
                           max_frames=args.max_frames)
        venv = HumanVecEnv(match)
        callbacks.append(LearningNotice(match))
        n_steps, batch = args.n_steps or 256, args.batch or 64
    else:
        opponent = args.opponent
        if opponent == 'past':
            opponent = lambda obs: np.zeros(len(obs), dtype=np.int64)  # until the first copy
        venv = EfzSB3VecEnv(args.data, args.envs, opponent=opponent, action_table=table,
                            chars=chars_of(args), char_pool=args.char_pool, stage=args.stage,
                            num_threads=args.threads, seed=args.seed, **config)
        n_steps = args.n_steps or 128
        batch = args.batch or min(4096, n_steps * venv.num_envs // 4)
    tensorboard = None
    try:
        import tensorboard as _  # noqa: F401
        tensorboard = os.path.join(args.out, 'tb')
    except ImportError:
        pass
    if args.load:
        model = PPO.load(args.load, env=venv, device=args.device, n_steps=n_steps,
                         batch_size=batch, tensorboard_log=tensorboard)
    else:
        model = PPO('MlpPolicy', venv, learning_rate=args.lr, n_steps=n_steps, batch_size=batch,
                    n_epochs=args.epochs, gamma=args.gamma, gae_lambda=0.95, ent_coef=args.ent,
                    clip_range=0.2, policy_kwargs=dict(net_arch=[256, 256]), verbose=1,
                    seed=args.seed, device=args.device, tensorboard_log=tensorboard)
    if args.opponent == 'past':
        venv.set_opponent(frozen(model))
        callbacks.append(RefreshOpponent(venv, args.refresh))
    every = max(1, int(args.save_every) // venv.num_envs)
    callbacks.append(CheckpointCallback(every, os.path.join(args.out, 'checkpoints'), 'model'))
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(dict(vars(args), actions=[table.describe(i) for i in range(len(table))],
                       obs_dim=venv.observation_space.shape[0]), f, indent=1)
    try:
        model.learn(total_timesteps=int(args.steps), callback=CallbackList(callbacks),
                    reset_num_timesteps=not args.load, progress_bar=False)
    except KeyboardInterrupt:
        print('stopped')
    except Exception as e:
        if not (human and type(e).__name__ == 'Quit'):
            raise
        print('stopped by the player')
    model.save(os.path.join(args.out, 'model.zip'))
    print('saved', os.path.join(args.out, 'model.zip'))
    if human:
        r = match.results
        print(f'matches: {len(r)}, agent won {sum(x == 1 for x in r)}, '
              f'you won {sum(x == -1 for x in r)}; recorded in {match.record_dir}')
    venv.close()


if __name__ == '__main__':
    main()
