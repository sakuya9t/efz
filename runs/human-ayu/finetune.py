"""Reinforcement learning from the clone of people's Ayu (bc.py), kept close to how they
play: PPO, every frame, with a KL penalty toward the clone (efz_env.policy).

    python runs/human-ayu/finetune.py --data "$EFZ_DIR" --out runs/human-ayu/agent   # continues it
    python runs/human-ayu/finetune.py --data "$EFZ_DIR" --out runs/mine --prior-coef 0

Ayu plays player 1. In --cpu-share of the matches player 2 is the game's CPU, from
--level up (a level higher once it wins --promote of its matches there), playing a
character drawn from all of them (people's Ayu met them all); in the rest it
is Ayu played by one of: a frozen copy of the policy (taken at each chunk's start), the
clone, the agent of runs/curriculum (every 4 frames, as it was trained), and the --team:
clones of single players (bc.py --players), each with its own habits, so that no one
way of winning works against all of them (a league, as against self-play's narrowing),
and the --combo master (combo.py): a red-team opponent, seeing the game as it is
(without the reaction time the others have), that lands the most damaging combo it can,
so that a hit taken costs what it can. With --combo-teacher it is also the target of the
pull while the agent's own combo runs (people's play elsewhere). The reward
is the damage dealt minus taken (full bars) and 1 for the match, as the clone's critic
learnt it from people's matches. Each chunk (--chunk steps) is followed by matches
played to the end against the CPU (at the level of the chunk) and the curriculum
agent, with how it played (evaluate.py's Events: people's are people.py's). --out gets
model.zip, chunkNNN.zip, finetune.json (the evaluations) and config.json.
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np
import torch
from stable_baselines3 import PPO
from stable_baselines3.common.callbacks import BaseCallback

from efz_env import ActionTable
from efz_env.sb3 import EfzSB3VecEnv, frozen, held, mixture

import evaluate as ev

TABLE = ActionTable()


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default=os.path.join(HERE, 'agent'))
    p.add_argument('--start', default=os.path.join(HERE, 'bc.zip'))
    p.add_argument('--prior', default=os.path.join(HERE, 'bc.zip'),
                   help='the policy to stay close to')
    p.add_argument('--prior-coef', type=float, default=0.1)
    p.add_argument('--old', default=os.path.join(REPO, 'runs', 'curriculum', 'model.zip'),
                   help='an agent of frame_skip 4 among the opponents')
    p.add_argument('--team', nargs='*', default=[], help="players' clones among the opponents")
    p.add_argument('--combo', help="combo.py's combo master: a red-team opponent")
    p.add_argument('--combo-teacher', action='store_true',
                   help="the combo master as the pull's target in the agent's own combos")
    p.add_argument('--combo-delay', type=int, default=0, help="the combo master's reaction time")
    p.add_argument('--lookahead', help="combo_library.py's library: the combo master tries its "
                   "options at each hit on copies of the game and plays the best (redteam.py)")
    p.add_argument('--combo-share', type=float, default=0.25,
                   help='share of the matches against agents that the combo master plays')
    p.add_argument('--level', type=int, default=2, help="the CPU's level to start at")
    p.add_argument('--promote', type=float, default=0.6,
                   help='share of wins against the CPU to move up a level')
    p.add_argument('--envs', type=int, default=64)
    p.add_argument('--cpu-share', type=float, default=0.5)
    p.add_argument('--history', type=int, default=16)
    p.add_argument('--delay', type=int, default=0,
                   help='steps late every player sees the game (the prior must be trained '
                        'with the same: bc.py --delay)')
    p.add_argument('--chunk', type=float, default=3e6)
    p.add_argument('--budget', type=float, default=6e7)
    p.add_argument('--minutes', type=float, default=5)
    p.add_argument('--eval', type=int, default=48)
    p.add_argument('--cpu-chars', default='tiers', choices=('tiers', 'random'),
                   help="the level-4 CPU's characters in evaluations: a third per tier "
                        "(evaluate.TIERS) or drawn")
    p.add_argument('--lr', type=float, default=1e-4)
    p.add_argument('--ent-coef', type=float, default=0.005)
    p.add_argument('--torch-threads', type=int, default=8)
    return p.parse_args()


def ppo_settings(args):
    return dict(learning_rate=args.lr, n_steps=256, batch_size=8192, n_epochs=3,
                gamma=0.999, gae_lambda=0.98, ent_coef=args.ent_coef, clip_range=0.1,
                vf_coef=0.5, max_grad_norm=0.5)


def make_env(args, opponents, seed, level):
    n = args.envs
    n_cpu = int(round(n * args.cpu_share))
    cpu_envs = np.arange(n) >= n - n_cpu
    # The matches against agents: Ayu's mirror, shared out among the opponents; the
    # combo master (the last of them) plays --combo-share of them.
    assignment = np.where(cpu_envs, -1, np.arange(n) % len(opponents))
    red = len(opponents) - 1 if args.combo else -2
    if args.combo:
        mirror = np.flatnonzero(~cpu_envs)
        k = int(round(len(mirror) * args.combo_share))
        others = len(opponents) - 1
        assignment[mirror] = [red if j < k else j % others for j in range(len(mirror))]
    chars = [('ayu', None) if c else ('ayu', 'ayu') for c in cpu_envs]
    # The combo master has a reaction time of its own.
    opponent_delay = np.where(assignment == red, min(args.combo_delay, args.delay), args.delay)
    env = EfzSB3VecEnv(args.data, n, opponent=mixture(opponents, assignment),
                        cpu_envs=cpu_envs, chars=chars, frame_skip=1, history=args.history,
                        delay=args.delay, opponent_delay=opponent_delay if args.delay else None,
                        max_frames=int(args.minutes * 3840), cpu_level=level,
                        reward_round=0.0, reward_match=1.0, seed=seed)
    for o in opponents:  # the lookahead red team saves this environment's games
        if hasattr(o, 'attach'):
            o.attach(env)
    return env


class KLLog(BaseCallback):
    def _on_rollout_end(self):
        self.logger.record('train/prior_kl', self.model.policy.prior_kl)

    def _on_step(self):
        return True


def evaluate(args, model_path, level):
    class A:
        pass
    a = A()
    a.data, a.minutes = args.data, args.minutes
    me = ev.Agent(model_path)
    out = {}
    a.chars = ('ayu', args.cpu_chars if level == 4 else 'random')  # tiers: level 4's
    out['cpu'] = ev.play(a, me, 'cpu', args.eval, level)
    out['cpu']['level'] = level
    if args.old and os.path.exists(args.old):
        a.chars = ('ayu', 'ayu')
        out['old'] = ev.play(a, me, ev.Agent(args.old), args.eval)
    if args.combo:
        a.chars = ('ayu', 'ayu')
        red = RED['agent'] if RED else ev.Agent(args.combo)
        n = len(red.plans) if RED else 0
        out['red'] = ev.play(a, me, red, args.eval)
        if RED:  # what the hits the agent took were worth to the red team
            plans = red.plans[n:]
            out['red']['plans'] = dict(
                n=len(plans), potential=float(np.mean([p[0] for p in plans])) if plans else None,
                own=float(np.mean([p[1] for p in plans])) if plans else None,
                library=float(np.mean([p[2] for p in plans])) if plans else None,
                big=float(np.mean([p[0] >= 3000 for p in plans])) if plans else None)
    return out


RED = {}  # the lookahead red team: its planner, opponent and agent


def show(results):
    parts = []
    for k, r in results.items():
        s = r['sides'][0]
        parts.append(f"{k}: win {r['win']:.0%} loss {r['loss']:.0%} cut {r['cut']:.0%}, "
                     f"{s['presses_per_second']} presses/s, per min {s['jumps_per_min']} jumps "
                     f"{s['guard_ground_per_min']} guards {s['hit_ground_per_min']}+"
                     f"{s['hit_air_per_min']} hits, RG {s['rg_ground']}/{s['rg_air']} "
                     f"RC {s['rc']}, after RG move/hit {s['rg_move']}/{s['rg_punish']}, "
                     f"combo avg/p90/max {s.get('combo_damage')}/{s.get('combo_damage_p90')}/"
                     f"{s.get('combo_damage_max')} IC {s.get('combo_ic')}"
                     + (f", taken {r['sides'][1].get('combo_damage_per_min')}/min" if k == 'red' else '')
                     + (' [' + ', '.join(f"{t} {v['win']:.0%}" for t, v in r['by_tier'].items()) + ']'
                        if k == 'cpu' and r.get('by_tier') else ''))
    return ' | '.join(parts)


def main():
    args = parse()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    torch.set_num_threads(args.torch_threads)
    os.makedirs(args.out, exist_ok=True)
    state_path = os.path.join(args.out, 'finetune.json')
    history, start, level = [], args.start, args.level
    if os.path.exists(state_path):
        with open(state_path) as f:
            saved = json.load(f)
        history, level = saved['history'], saved['level']
        start = os.path.join(args.out, 'model.zip')
        print(f'continuing {args.out} after chunk {len(history)}', flush=True)
    settings = ppo_settings(args)
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(dict(frame_skip=1, history=args.history, delay=args.delay, chars=['ayu', None],
                       prior=os.path.relpath(args.prior, REPO), prior_coef=args.prior_coef,
                       team=[os.path.relpath(t, REPO) for t in args.team],
                       combo=args.combo and os.path.relpath(args.combo, REPO),
                       combo_teacher=args.combo_teacher, combo_delay=args.combo_delay,
                       lookahead=args.lookahead,
                       level=args.level, ppo=settings,
                       actions=[TABLE.describe(i) for i in range(len(TABLE))]), f, indent=1)
    prior = PPO.load(args.prior, device='cpu')
    clone = frozen(prior)
    old = held(frozen(PPO.load(args.old, device='cpu')), 4) if args.old else None
    team = [frozen(PPO.load(t, device='cpu')) for t in args.team]
    master = PPO.load(args.combo, device='cpu') if args.combo else None
    if master is not None and args.lookahead:
        import macros
        import redteam
        planner = redteam.Planner(args.data, macros.load_library(args.lookahead, 300), master)
        RED.update(opponent=redteam.RedTeamOpponent(planner, master),
                   agent=redteam.RedTeamAgent(planner, args.combo))
        team.append(RED['opponent'])
    elif master is not None:
        team.append(frozen(master))
    opponents = lambda snapshot: [o for o in (snapshot, clone, old) if o is not None] + team
    env = make_env(args, opponents(clone), len(history), level)
    model = PPO.load(start, env=env, device='cpu', **settings)
    if args.prior_coef > 0:
        teacher = master.policy if master is not None and args.combo_teacher else None
        model.policy.set_prior(prior.policy, args.prior_coef, args.ent_coef, combo=teacher)
    print('starting from', start, flush=True)
    if not history:
        before = evaluate(args, start, level)
        print('before:', show(before), flush=True)
        history.append(dict(steps=0, level=level, eval=before))
    while model.num_timesteps < args.budget:
        env.close()
        env = make_env(args, opponents(frozen(model)), len(history) + 1, level)
        model.set_env(env)
        t = time.time()
        model.learn(int(args.chunk), reset_num_timesteps=False, callback=KLLog())
        seconds = time.time() - t
        path = os.path.join(args.out, 'model.zip')
        model.save(path)
        model.save(os.path.join(args.out, f'chunk{len(history):03d}.zip'))
        results = evaluate(args, path, level)
        returns = [e['r'] for e in model.ep_info_buffer]
        history.append(dict(steps=model.num_timesteps, level=level, train_seconds=seconds,
                            prior_kl=model.policy.prior_kl,
                            ep_return=float(np.mean(returns)) if returns else None,
                            eval=results))
        print(f'[{model.num_timesteps / 1e6:.1f}M steps, {seconds:.0f}s, L{level}, '
              f'KL {model.policy.prior_kl:.3f}] ' + show(results), flush=True)
        if results['cpu']['win'] >= args.promote and level < 4:
            level += 1
            print(f'promoted to level {level}', flush=True)
        with open(state_path, 'w') as f:
            json.dump(dict(level=level, history=history), f, indent=1)
    env.close()
    print('done', flush=True)


if __name__ == '__main__':
    main()
