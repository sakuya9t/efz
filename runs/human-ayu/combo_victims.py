"""Combos by the character they land on: some hold only on certain characters or need
another rhythm, and on Ayu, Mayu, Sayuri, Unknown (mizukab) and Kano they are easier to
drop (the user's). For people's Ayu (a dataset of dataset.py), per victim:

- runs: the combo counter's runs (a hit and what followed it); conversion, the share of
  them that went on to 2 hits or more;
- of the combos (2 hits or more): their hits and damage on average and at the 90th
  percentile, and how they ended: in a knockdown (the victim hit the ground, 0x61-0x63),
  an air recovery (0x9d, 0x9e: the victim teched out) or neither (it recovered on its
  feet or guarded); dropped, the share that ended without a knockdown, a proxy for a
  combo that broke rather than finished.

    python runs/human-ayu/combo_victims.py --dataset ~/data/efz-replays/datasets/ayu --json runs/human-ayu/combo_victims.json

--agent instead: an agent (Ayu) against the CPU (--level) as each character, --matches
each, the same table for its combos.

    python runs/human-ayu/combo_victims.py --agent runs/human-ayu/agent-league6/best.zip --matches 8
"""

import argparse
import csv
import json
import os

import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))

HITS, DAMAGE, OPP_ACTION = 30, 38, 50  # self_combo_hits (/ 30), self_combo_damage (/ 9999)
KNOCKDOWN = (0x61, 0x62, 0x63)
AIR_RECOVERY = (0x9d, 0x9e)
AFTER = 90  # steps after a combo's end in which how it ended is looked for


def ending(oa, e):
    """How a combo that ended at step e ended, from the victim's actions after it."""
    for t in range(max(0, e - 1), min(len(oa), e + AFTER)):
        if oa[t] in KNOCKDOWN:
            return 'knockdown'
        if oa[t] in AIR_RECOVERY:
            return 'air_recovery'
        if oa[t] < 0x32 or 0x96 <= oa[t] <= 0x9c:  # free, or guarding: on its feet
            return 'neither'
    return 'neither'


def combos(obs):
    hits = np.round(obs[:, HITS].astype(np.float32) * 30).astype(int)
    dmg = obs[:, DAMAGE].astype(np.float32) * 9999
    oa = np.round(obs[:, OPP_ACTION].astype(np.float32)).astype(int)
    on = hits > 0
    starts = np.flatnonzero(on & ~np.concatenate([[False], on[:-1]]))
    ends = np.flatnonzero(~on & np.concatenate([[False], on[:-1]]))
    for b in starts:
        later = ends[ends > b]
        e = int(later[0]) if len(later) else len(obs)
        yield int(hits[b:e].max()), float(dmg[b:e].max()), ending(oa, e)


def summarize(rows):
    out = {}
    for victim, runs in sorted(rows.items()):
        c = [r for r in runs if r[0] >= 2]
        if not c:
            continue
        ends = [r[2] for r in c]
        d = np.array([r[1] for r in c])
        out[victim] = dict(
            runs=len(runs), conversion=round(len(c) / len(runs), 3), combos=len(c),
            hits=round(float(np.mean([r[0] for r in c])), 2),
            damage=round(float(d.mean())), damage_p90=round(float(np.percentile(d, 90))),
            knockdown=round(ends.count('knockdown') / len(c), 3),
            air_recovery=round(ends.count('air_recovery') / len(c), 3),
            neither=round(ends.count('neither') / len(c), 3),
            dropped=round(1 - ends.count('knockdown') / len(c), 3))
    return out


def people(dataset):
    rows = {}
    for r in csv.DictReader(open(os.path.join(dataset, 'matches.csv'), encoding='utf-8')):
        if r['in_sync'] != '1':
            continue
        with np.load(os.path.join(dataset, f"{r['id']}-{r['side']}.npz")) as z:
            obs = z['obs']
        rows.setdefault(r['opponent'], []).extend(combos(obs))
    return rows


def agent_vs_cpu(data, path, matches, level, minutes=10, seed=7):
    sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
    from efz_env import EfzVecEnv
    from efz_env.agent import Agent
    from efz_env.vec import character_names
    chars = [c for c in character_names() if c not in ('nayuki2', 'mizuka')]
    victims = [c for c in chars for _ in range(matches)]
    n = len(victims)
    env = EfzVecEnv(data, n, frame_skip=1, max_frames=int(minutes * 3840), cpu_level=level,
                    autoreset='disabled', seed=seed, reward_round=0.0, reward_match=1.0)
    env.set_matches(chars=[('ayu', c) for c in victims], cpu=(False, True))
    me = Agent(path)
    me.batch(n)
    obs = env.reset()
    done = np.zeros(n, bool)
    rec = [[] for _ in range(n)]
    cols = [HITS, DAMAGE, OPP_ACTION]
    step = 0
    while not done.all():
        controls = np.zeros((n, 2), np.uint8)
        controls[:, 0] = me.controls(obs[:, 0], step)
        view = obs[:, 0].copy()
        obs, _, term, trunc, info = env.step(controls)
        me.observe(info['input'][:, 0])
        step += 1
        for i in np.flatnonzero(~done):
            rec[i].append(view[i, cols])
        done |= term | trunc
    env.close()
    rows = {}
    for i, v in enumerate(victims):
        o = np.zeros((len(rec[i]), max(cols) + 1), np.float32)
        o[:, cols] = np.array(rec[i], np.float32)
        rows.setdefault(v, []).extend(combos(o))
    return rows


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    p.add_argument('--dataset', help="people's: dataset.py's folder")
    p.add_argument('--agent', help='or an agent against the CPU as each character')
    p.add_argument('--matches', type=int, default=8)
    p.add_argument('--level', type=int, default=4)
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--json')
    args = p.parse_args()
    if args.agent:
        rows = agent_vs_cpu(args.data, args.agent, args.matches, args.level)
    else:
        rows = people(args.dataset)
    out = summarize(rows)
    print(f"{'victim':10} {'runs':>6} {'conv':>5} {'combos':>6} {'hits':>5} {'dmg':>5} {'p90':>5} "
          f"{'KD':>5} {'tech':>5} {'feet':>5} {'drop':>5}")
    for v, s in sorted(out.items(), key=lambda kv: kv[1]['dropped']):
        print(f"{v:10} {s['runs']:6d} {s['conversion']:5.0%} {s['combos']:6d} {s['hits']:5.2f} "
              f"{s['damage']:5d} {s['damage_p90']:5d} {s['knockdown']:5.0%} "
              f"{s['air_recovery']:5.0%} {s['neither']:5.0%} {s['dropped']:5.0%}")
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
