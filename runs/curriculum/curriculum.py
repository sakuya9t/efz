"""The run of runs/curriculum: PPO against the game's CPU a level at a time, with a share
of self-play, evaluated on full-length matches after every chunk.

    python runs/curriculum/curriculum.py --data "$EFZ_DIR"                    # continues this run
    python runs/curriculum/curriculum.py --data "$EFZ_DIR" --out runs/mine     # a new one, from runs/pbt/best.zip
    python runs/curriculum/curriculum.py --data "$EFZ_DIR" --out runs/mine --start ''   # from nothing

Each chunk trains --chunk steps: the CPU at the current level plays player 2 in
three quarters of the matches, a frozen copy of the policy (taken when the chunk begins)
in the rest. Then --eval matches at the current level and the next, played to the end
(cut at --minutes), measure it: wins (by KO), losses, damage, and how it plays (air,
guard, its own moves, buttons). It moves up a level when it wins --promote of them, and
stops when it wins --goal at level 4, or at --budget steps. --out gets model.zip (the
latest), chunkNNN-L<level>.zip after each chunk, curriculum.json (the evaluations) and
config.json (for examples/play.py and record_replay.py); a folder that has
curriculum.json is continued. Needs stable-baselines3 and torch.
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))

import numpy as np
import torch
from stable_baselines3 import PPO

from efz_env import ActionTable, EfzVecEnv
from efz_env.sb3 import EfzSB3VecEnv, frozen, mixture

TABLE = ActionTable()
PPO_SETTINGS = dict(learning_rate=3e-4, n_steps=256, batch_size=4096, n_epochs=4,
                    gamma=0.995, gae_lambda=0.95, ent_coef=0.005, clip_range=0.2)


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default=HERE)
    p.add_argument('--start', default=os.path.join(REPO, 'runs', 'pbt', 'best.zip'),
                   help="a model.zip to start from ('' for a new policy)")
    p.add_argument('--chars', nargs=2, default=('ayu', 'ayu'), metavar=('P1', 'P2'))
    p.add_argument('--level', type=int, default=2, help='the CPU level to start at')
    p.add_argument('--envs', type=int, default=64)
    p.add_argument('--self-share', type=float, default=0.25,
                   help='share of matches against a frozen copy instead of the CPU')
    p.add_argument('--chunk', type=float, default=2e6, help='steps between evaluations')
    p.add_argument('--budget', type=float, default=8e7, help='stop after this many steps')
    p.add_argument('--minutes', type=float, default=5, help='a match is cut short after')
    p.add_argument('--eval', type=int, default=64, help='matches per evaluation')
    p.add_argument('--promote', type=float, default=0.6, help='win share to move up a level')
    p.add_argument('--goal', type=float, default=0.5, help='win share at level 4 to stop')
    p.add_argument('--torch-threads', type=int, default=6)
    return p.parse_args()


def make_env(args, level, snapshot, seed):
    n_self = int(args.envs * args.self_share)
    cpu_envs = np.arange(args.envs) >= n_self  # the first share play the frozen copy
    assignment = np.where(cpu_envs, -1, 0)
    return EfzSB3VecEnv(args.data, args.envs, opponent=mixture([snapshot], assignment),
                        cpu_envs=cpu_envs, chars=tuple(args.chars), frame_skip=4,
                        max_frames=int(args.minutes * 60 * 64), cpu_level=level,
                        reward_round=0.3, reward_match=1.0, seed=seed)


def evaluate(args, model, level, seed=999):
    """args.eval full matches against the CPU at `level`."""
    n = args.eval
    env = EfzVecEnv(args.data, n, frame_skip=4, max_frames=int(args.minutes * 60 * 64),
                    cpu_level=level, autoreset='disabled', seed=seed)
    env.set_matches(chars=tuple(args.chars), cpu=(False, True))
    names = env.observation_names
    col = {k: names.index('self_' + k) for k in ('airborne', 'guarding', 'own_action')}
    obs = env.reset()
    controls = np.zeros((n, 2), np.uint8)
    done = np.zeros(n, bool)
    winner = np.full(n, -1)
    frames = np.zeros(n)
    dealt, taken = np.zeros(n), np.zeros(n)
    seen = {k: 0.0 for k in col}
    steps = 0
    chosen = np.zeros(len(TABLE))
    prev_hp = None
    while not done.all():
        live = ~done
        a = model.predict(obs[:, 0], deterministic=False)[0]
        np.add.at(chosen, a[live], 1)
        controls[:, 0] = TABLE.to_bytes(a)
        for k, c in col.items():
            seen[k] += float((obs[live, 0, c] > 0).sum())
        steps += int(live.sum())
        obs, _, terminated, truncated, info = env.step(controls)
        hp = info['hp'].astype(float)
        if prev_hp is not None:  # damage from HP drops (the refill between rounds isn't)
            dealt += np.where(live, np.clip(prev_hp[:, 1] - hp[:, 1], 0, None), 0)
            taken += np.where(live, np.clip(prev_hp[:, 0] - hp[:, 0], 0, None), 0)
        prev_hp = hp
        new = (terminated | truncated) & ~done
        winner[new] = info['winner'][new]
        frames[new] = info['frame'][new]
        done |= terminated | truncated
    env.close()
    share = chosen / chosen.sum()
    buttons = {b or 'none': float(sum(share[i] for i, (_, bb) in enumerate(TABLE.actions)
                                      if bb == b)) for b in ('', 'A', 'B', 'C', 'D')}
    return dict(level=level, win=float(np.mean(winner == 0)), loss=float(np.mean(winner == 1)),
                cut=float(np.mean(winner == -1)), seconds=float(np.median(frames) / 64),
                dealt=float(dealt.mean() / 9999), taken=float(taken.mean() / 9999),
                airborne=seen['airborne'] / steps, guarding=seen['guarding'] / steps,
                own_moves=seen['own_action'] / steps, buttons=buttons)


def show(r):
    return (f"L{r['level']}: win {r['win']:.0%} loss {r['loss']:.0%} cut {r['cut']:.0%}, "
            f"{r['seconds']:.0f}s, bars dealt {r['dealt']:.2f} taken {r['taken']:.2f}, "
            f"air {r['airborne']:.0%} guard {r['guarding']:.0%} own-moves {r['own_moves']:.0%}, "
            'buttons ' + ' '.join(f'{k} {v:.0%}' for k, v in r['buttons'].items()))


def main():
    args = parse()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    torch.set_num_threads(args.torch_threads)
    os.makedirs(args.out, exist_ok=True)
    state_path = os.path.join(args.out, 'curriculum.json')
    level, history, start = args.level, [], args.start
    if os.path.exists(state_path):
        with open(state_path) as f:
            saved = json.load(f)
        level, history = saved['level'], saved['history']
        start = os.path.join(args.out, 'model.zip')
        print(f'continuing {args.out} at level {level}', flush=True)
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(dict(frame_skip=4, chars=list(args.chars), ppo=PPO_SETTINGS,
                       actions=[TABLE.describe(i) for i in range(len(TABLE))]), f, indent=1)
    snapshot = lambda obs: np.zeros(len(obs), np.int64)
    env = make_env(args, level, snapshot, seed=len(history))
    if start:
        model = PPO.load(start, env=env, device='cpu', **PPO_SETTINGS)
        print('starting from', start, flush=True)
    else:
        model = PPO('MlpPolicy', env, device='cpu', verbose=0,
                    policy_kwargs=dict(net_arch=[256, 256]), **PPO_SETTINGS)
    print('before:', show(evaluate(args, model, level)), flush=True)
    while model.num_timesteps < args.budget:
        env.close()
        env = make_env(args, level, frozen(model), seed=len(history) + 1)
        model.set_env(env)
        t = time.time()
        model.learn(int(args.chunk), reset_num_timesteps=False)
        seconds = time.time() - t
        model.save(os.path.join(args.out, 'model.zip'))
        results = [evaluate(args, model, level)]
        if level < 4:
            results.append(evaluate(args, model, level + 1))
        returns = [e['r'] for e in model.ep_info_buffer]
        entry = dict(steps=model.num_timesteps, level=level, train_seconds=seconds,
                     ep_return=float(np.mean(returns)) if returns else None, eval=results)
        history.append(entry)
        model.save(os.path.join(args.out, f'chunk{len(history):03d}-L{level}.zip'))
        print(f'[{model.num_timesteps / 1e6:.1f}M steps, {seconds:.0f}s] ' +
              ' | '.join(show(r) for r in results), flush=True)
        if results[0]['win'] >= args.promote and level < 4:
            level += 1
            print(f'promoted to level {level}', flush=True)
        with open(state_path, 'w') as f:
            json.dump(dict(level=level, history=history), f, indent=1)
        at4 = [r for r in results if r['level'] == 4]
        if at4 and at4[0]['win'] >= args.goal:
            print(f"goal: wins {at4[0]['win']:.0%} of its matches against the level-4 CPU",
                  flush=True)
            break
    env.close()
    print('done', flush=True)


if __name__ == '__main__':
    main()
