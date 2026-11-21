"""The native game's fight records as play.py's recordings: what the measures here read.

    python runs/human-ayu/from_record.py OUT SESSION_FOLDER_OR_FIGHT.jsonl ... [--agent-side 0]

The game keeps a record of every fight (docs/logging.md: <save folder>/logs/SESSION/
fight-NNN.jsonl, each tick's inputs and a few of each player's fields). A match against an
agent in the game is one of these, and holds less than the observation the measures need
(evaluate.Events, tactics.py). So each fight is played again in the headless game from
its inputs, and written as python/examples/play.py writes a match: OUT/SESSION-NNN.npz
(obs (T, 2, obs_dim): each player's view before the frame; controls (T, 2): the inputs,
relative to facing; reward) and .json (chars, winner, rounds_won, human, agent, ...).

The fight played again is checked against the record at every frame (each player's
action, x, HP and RF gauge) and at its end (the winner, the rounds): a fight that
differs anywhere is said and not written. For the two to agree the headless match needs
the record's start: rand()'s state (the hits' effects and some moves draw from it), found
by inverting the environment's seeding; and the RF gauge at 0, where the headless
match begins with an intro's worth of it.

Only matches between two players at the controls that ended with a winner are taken
(mode "vs human": an agent in the game plays through a player's controls); the others
are named and left out.
"""

import argparse
import glob
import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env.human import to_relative  # noqa: E402
from efz_env.vec import EfzVecEnv  # noqa: E402

M = (1 << 64) - 1
GAMMA = 0x9e3779b97f4a7c15
C1, C2 = 0xbf58476d1ce4e5b9, 0x94d049bb133111eb


def mix(z):
    """SplitMix64's output for the state z (port/headless/env.cpp's SplitMix, after its step)."""
    z = ((z ^ (z >> 30)) * C1) & M
    z = ((z ^ (z >> 27)) * C2) & M
    return z ^ (z >> 31)


def _unshift(z, k):
    out = z
    for _ in range(64 // k + 1):
        out = z ^ (out >> k)
    return out


def unmix(z):
    z = _unshift(z, 31)
    z = (z * pow(C2, -1, 1 << 64)) & M
    z = _unshift(z, 27)
    z = (z * pow(C1, -1, 1 << 64)) & M
    return _unshift(z, 30)


def seed_for(rand_state):
    """The environment seed whose next match begins with the game's rand() at
    `rand_state`: efz_env_seed keeps SplitMix(seed) as the slot's state; a match whose
    characters and stage are given draws nothing from it; then srand((unsigned)
    SplitMix(state))."""
    state = (unmix(rand_state) - GAMMA) & M
    seed = (unmix(state) - GAMMA) & M
    assert mix((mix((seed + GAMMA) & M) + GAMMA) & M) & 0xffffffff == rand_state
    return seed


def read(path):
    """A record's header, its ticks by the frame they ran in, and its end line."""
    head, frames, end = None, {}, None
    with open(path, encoding='utf-8') as f:
        for line in f:
            try:
                r = json.loads(line)
            except json.JSONDecodeError:  # the last line of a game that crashed
                continue
            if r['type'] == 'fight':
                head = r
            elif r['type'] == 'tick':
                frames.setdefault(r['f'], []).append(r)
            elif r['type'] == 'end':
                end = r
    return head, frames, end


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('out')
    p.add_argument('records', nargs='+', help='session folders, or fight-NNN.jsonl files')
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--agent-side', type=int, choices=[0, 1], default=0,
                   help='the side the agent played (0: player 1)')
    p.add_argument('--agent-name', default='',
                   help="the recordings' agent_name (default: the session's)")
    args = p.parse_args()
    paths = []
    for r in args.records:
        paths += sorted(glob.glob(os.path.join(r, 'fight-*.jsonl'))) if os.path.isdir(r) else [r]
    os.makedirs(args.out, exist_ok=True)
    env, written = None, 0
    for path in paths:
        head, frames, end = read(path)
        if head is None:
            print(f'{path}: no header')
            continue
        name = f"{head['session']}-{head['fight']:03d}"
        if head['mode_name'] != 'vs human' or not end or end['reason'] != 'match_end':
            print(f"{name}: left out ({head['mode_name']}, {end['reason'] if end else 'no end'})")
            continue
        if env is None or env.config.rounds_to_win != head['rounds_to_win']:
            env = EfzVecEnv(args.data, 1, frame_skip=1, skip_noninteractive=False,
                            relative_actions=True, autoreset='disabled', num_threads=1,
                            rounds_to_win=head['rounds_to_win'])
            names = env.observation_names
            ix = {n: i for i, n in enumerate(names)}
        chars = tuple(pl['name'] for pl in head['players'])
        env.set_matches(chars=chars, stage=head['stage'], cpu=(False, False),
                        palettes=tuple(pl['palette'] for pl in head['players']))
        env.seed(0, seed_for(head['rng']))
        env.reset()
        for s in (0, 1):
            env.set_gauges(0, s, rf=0.0)
        obs, controls, rewards, differs, ended = [], [], [], None, False
        for f in sorted(frames):
            ticks = frames[f]
            o = env.obs[0]
            ctl = np.array([[to_relative(ticks[0]['in'][s], o[s, ix['self_facing']])
                             for s in (0, 1)]], np.uint8)
            obs.append(o.copy())
            controls.append(ctl[0].copy())
            _, reward, term, trunc, _ = env.step(ctl)
            rewards.append(reward[0].copy())
            o = env.obs[0]
            for s in (0, 1):
                rec = ticks[-1]['p'][s]  # (action, frame, x, y, vx, vy, facing, hp, gauge, guard, rf, ...)
                same = (int(round(float(o[s, ix['self_action']]))) == rec[0] and
                        abs(float(o[s, ix['self_x']]) * 320 + 320 - rec[2]) < 0.01 and
                        abs(float(o[s, ix['self_hp']]) * 9999 - rec[7]) < 1 and
                        abs(float(o[s, ix['self_rf_gauge']]) * 1000 - rec[10]) < 0.5)
                if not same and differs is None:
                    differs = f
            if term[0] or trunc[0]:
                ended = True
                break
        info = env.info[0]
        winner, rounds = int(info['winner']), [int(x) for x in info['rounds_won']]
        if differs is not None or not ended or winner != end['winner'] or rounds != end['rounds_won']:
            print(f'{name}: {chars[0]} vs {chars[1]}: NOT as recorded ' +
                  (f'from frame {differs}' if differs is not None else
                   f'(ended {ended}, winner {winner} for {end["winner"]}, rounds {rounds})'))
            continue
        np.savez_compressed(os.path.join(args.out, name + '.npz'),
                            obs=np.stack(obs).astype(np.float32),
                            controls=np.stack(controls).astype(np.uint8),
                            reward=np.stack(rewards).astype(np.float32),
                            final_obs=env.obs[0].copy())
        meta = dict(frame=int(info['frame']), winner=winner, rounds_won=rounds,
                    chars=[int(x) for x in info['chars']], stage=int(info['stage']),
                    human=1 - args.agent_side, agent=args.agent_side, opponent='agent',
                    agent_name=args.agent_name or f"in the game, session {head['session']}",
                    frame_skip=1, frames=len(obs), fps=64, observation_names=names,
                    date=head['started'], record=os.path.basename(path),
                    build=head['build']['revision'])
        with open(os.path.join(args.out, name + '.json'), 'w', encoding='utf-8') as f:
            json.dump(meta, f, indent=1)
        written += 1
        print(f'{name}: {chars[0]} vs {chars[1]}, {len(obs)} frames, rounds {rounds}: as recorded')
    print(f'{written} matches written to {args.out}')


if __name__ == '__main__':
    main()
