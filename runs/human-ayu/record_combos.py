"""Records a combo master's most damaging combos as replays, to watch in EFZ.

    python runs/human-ayu/record_combos.py --master runs/human-ayu/combo-red3/combo.zip \
        --vs runs/human-ayu/bc-d14.zip --out runs/human-ayu/replays/combos --slots 4 5 6
    python runs/human-ayu/record_combos.py ... --lookahead $REPLAYS/combo-library.npz

Plays --matches whole matches (P1 the master, P2 --vs, Ayu against Ayu by default), each
recorded (a replay holds both players' inputs, so both are agents, not the CPU), and keeps
the ones with the master's most damaging combos: --out/replay/data<page>-<slot>.rep, one
per slot of --slots on --page, in EFZ's REPLAY menu once copied into the game's replay/
folder. --out/combos.txt says where each combo is (the round, and the seconds into its
fight), its damage and hits, and the resources at its first hit (evaluate.resources: the
RF gauge's state and the bars of power). With --lookahead the master plays as the red team
(redteam.py): at each first hit it tries the library's combos and its own play on copies of
the game and plays the most damaging; the copies write no replay.

These are matches from the start, as a replay must be: the combos come from the hits the
master lands and the resources it has built, not from people's starts with resources set
(combo.py's trials), which a replay can't hold.
"""

import argparse
import os
import shutil
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np

from efz_env import EfzVecEnv
from efz_env.agent import Agent

from evaluate import resources

# The observation's columns (player 1's view): combo hits (/ 30) and damage (/ 9999) of the
# combo one is doing; power (/ 3000), RF gauge (/ 1000), rf_blue; intro; rounds won.
COMBO_HITS, COMBO_DAMAGE, GAUGE, RF, RF_FULL, INTRO = 30, 38, 9, 10, 11, 2
ROUNDS_SELF, ROUNDS_OPP = 32, 64


def master_player(args):
    if not args.lookahead:
        return Agent(args.master)
    from stable_baselines3 import PPO
    import macros
    import redteam
    model = PPO.load(args.master, device='cpu')
    planner = redteam.Planner(args.data, macros.load_library(args.lookahead, 300), model)
    return redteam.RedTeamAgent(planner, args.master)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--master', required=True, help="combo.py's model (combo.zip)")
    p.add_argument('--vs', default=os.path.join(HERE, 'bc-d14.zip'), help='P2, a model.zip')
    p.add_argument('--lookahead', help="combo_library.py's library: play as the red team")
    p.add_argument('--chars', nargs=2, default=('ayu', 'ayu'))
    p.add_argument('--matches', type=int, default=32, help='at most 81')
    p.add_argument('--minutes', type=float, default=6)
    p.add_argument('--out', default=os.path.join(HERE, 'replays', 'combos'))
    p.add_argument('--page', type=int, default=1)
    p.add_argument('--slots', type=int, nargs='+', default=[1, 2, 3])
    p.add_argument('--label', default=None, help="combos.txt's name for the master")
    p.add_argument('--seed', type=int, default=0)
    args = p.parse_args()
    n = min(81, args.matches)
    work = tempfile.mkdtemp(prefix='combos-')
    os.makedirs(os.path.join(work, 'replay'))  # (the game writes replays only into one)
    # The players first: the red team's planner makes an environment of its own, and making
    # one sets the process's save folder back to the data folder (EfzVecEnv: save_dir is
    # the process's), which would put the replays among the game's.
    players = [master_player(args), Agent(args.vs)]
    env = EfzVecEnv(args.data, n, frame_skip=1, rounds_to_win=2,
                    max_frames=int(args.minutes * 3840), autoreset='disabled',
                    seed=args.seed, save_dir=work)
    env.set_matches(chars=tuple(args.chars), cpu=(False, False))
    for i in range(n):
        env.record(i, 1 + i // 9, 1 + i % 9)
    for side, a in enumerate(players):
        a.batch(n)
        if hasattr(a, 'attach'):
            a.attach(env, side)
    obs = env.reset()
    done = np.zeros(n, bool)
    best = [None] * n            # per match: its master's most damaging combo
    current = [None] * n         # the combo going on
    fight_start = np.zeros(n, int)
    step = 0
    while not done.all():
        controls = np.zeros((n, 2), np.uint8)
        for side, a in enumerate(players):
            controls[:, side] = a.controls(obs[:, side], step)
        obs, _, term, trunc, info = env.step(controls)
        for side, a in enumerate(players):
            a.observe(info['input'][:, side])
        step += 1
        v = obs[:, 0]
        for i in np.flatnonzero(~done):
            if v[i, INTRO] > 0:
                fight_start[i] = step
            hits = int(round(float(v[i, COMBO_HITS]) * 30))
            c = current[i]
            if hits > 0 and c is None:
                current[i] = c = dict(
                    round=int(round(float(v[i, ROUNDS_SELF] + v[i, ROUNDS_OPP]))) + 1,
                    at=(step - fight_start[i]) / 64,
                    resources=resources(float(v[i, GAUGE]) * 3000, float(v[i, RF]) * 1000,
                                        v[i, RF_FULL] > 0), hits=0, damage=0)
            if c is not None and hits > 0:
                c['hits'] = max(c['hits'], hits)
                c['damage'] = max(c['damage'], round(float(v[i, COMBO_DAMAGE]) * 9999))
            if c is not None and (hits == 0 or term[i] or trunc[i]):
                if best[i] is None or c['damage'] > best[i]['damage']:
                    best[i] = c
                current[i] = None
        done |= term | trunc
    env.close()
    order = [i for i in sorted(range(n), key=lambda i: -(best[i] or {}).get('damage', 0))
             if best[i]]
    os.makedirs(os.path.join(args.out, 'replay'), exist_ok=True)
    label = args.label or (os.path.relpath(args.master, REPO) +
                           (' + lookahead' if args.lookahead else ''))
    damages = sorted((b['damage'] for b in best if b), reverse=True)
    lines = [f'{label} (P1) vs {os.path.relpath(args.vs, REPO)} (P2), {args.chars[0]} vs '
             f'{args.chars[1]}: {n} matches; each match\'s most damaging combo: '
             f'median {np.median(damages):.0f}, most {damages[0]}']
    for slot, i in zip(args.slots, order):
        b = best[i]
        src = env.replay_path(1 + i // 9, 1 + i % 9)
        dst = os.path.join(args.out, 'replay', f'data{args.page}-{slot}.rep')
        shutil.copyfile(src, dst)
        lines.append(f'  page {args.page} slot {slot}: {b["damage"]} damage, {b["hits"]} hits, '
                     f'round {b["round"]}, {b["at"]:.0f} s into its fight, from {b["resources"]}')
    shutil.rmtree(work, ignore_errors=True)
    text = '\n'.join(lines)
    print(text)
    with open(os.path.join(args.out, 'combos.txt'), 'a', encoding='utf-8') as f:
        f.write(text + '\n')


if __name__ == '__main__':
    main()
