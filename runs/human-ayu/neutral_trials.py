"""Paired neutral decisions on playable snapshots of human and agent replays.

Provide a round25 .efzagent and a policy-only export of league11-r7 at delay 11.
See docs/neutral-trials.md for the experiment and commands.
"""
import argparse
import collections
import csv
import json
from pathlib import Path
import sys

import numpy as np

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parents[1] / 'python'))
from efz_env import EfzVecEnv
from efz_env.actions import encode
from efz_env.export import NativeAgent
import advantages
import tactics

# Only delayed information is used to offer or execute an option.
DELAY = 11
WARM = 40
HORIZON = 160
OPTIONS = ('round25', 'old', 'walk_guard', 'walk_poke', '236C', 'wait')
DEV = ('kano', 'ikumi', 'mishio')
TEST = ('sayuri', 'mizukab', 'exnanase')
FREE_GROUND = (0, 1, 2, 3, 4)
IDLE = np.zeros((1, 2), np.uint8)
# Confirmed P1 Ayu games from the November 25 BattleLog and replay frame counts.
OCI_GAMES = {
    '20261125-195649': ('exnanase', 11105),
    '20261125-200057': ('sayuri', 8260),
    '20261125-200322': ('mishio', 6012),
}


def eligible(v):
    return (v[2] == v[3] == 0 and v[39] == 0 and int(v[18]) in FREE_GROUND
            and v[30] == v[62] == 0 and not v[52] and int(v[50]) not in tactics.DOWN
            and int(v[50]) not in tactics.GUARDS and 65 <= abs(v[4]) * 640 <= 260)


def cues(v):
    """Visible separation, charge, airborne, committed, projectiles, wall and closing speed."""
    return [abs(float(v[4])) * 640, float(v[10]), float(v[71]),
            float(v[50] >= tactics.FIRST_OWN), float(v[120:168:6].sum()),
            abs(float(v[45])), float(np.sign(v[4]) * (v[15] - v[47]))]


def input_cues(controls):
    """The player's own inputs since the delayed view, available without delay."""
    c = np.asarray(controls, np.uint8)
    return [float(np.any(c[-DELAY:] & 8)),
            float(np.any((c[1:] & ~c[:-1]) >> 4)),
            float(np.mean((c[-DELAY:] & 1) != 0))]


class Demonstrations:
    """Nearest observed 24-frame ground entry, using only cues visible at its start."""
    def __init__(self, path):
        with np.load(path) as library:
            self.x = library['x']
            self.inputs = library['inputs']
            self.ids = library['ids']
        self.scale = np.array([70, .6, 1, 1, 1, .6, .45])

    def choose(self, seen, exclude):
        distance = np.square((self.x - cues(seen)) / self.scale).sum(axis=1)
        distance[self.ids == exclude] = np.inf
        index = np.argmin(distance)
        if not np.isfinite(distance[index]):
            raise ValueError('No demonstration from another replay')
        return self.inputs[index]


def harvest(args):
    xs, sequences, ids = [], [], []
    for split, _, rid, side, *_ in records(args):
        if split != 'dev':
            continue
        path = args.archive / 'datasets/ayu' / f'{rid}-{side}.npz'
        with np.load(path) as data:
            v, controls = data['obs'].astype(np.float32), data['input']
        last = -24
        for t in range(DELAY, len(v)-24):
            if t-last < 24 or not eligible(v[t-DELAY]):
                continue
            prefix = v[t:t+24]
            if np.any(prefix[:,39]) or np.any(prefix[:,20]) or np.any(prefix[:,1] != prefix[0,1]):
                continue
            toward = np.sign(prefix[0,4]) * (prefix[:,13]-prefix[0,13]) * 320
            if toward.max() < 12 or not np.any((controls[t:t+24] & 1) != 0):
                continue
            last = t
            xs.append(cues(v[t-DELAY]))
            sequences.append(controls[t:t+24].copy())
            ids.append(rid)
    with args.out.open('xb') as out:
        np.savez_compressed(out, x=xs, inputs=sequences, ids=ids)
    print(f'{len(xs)} ground entries from {len(set(ids))} replays')


def override(choice, t, seen, old, demo):
    if choice == 'round25' or t >= 24 or seen[20] or seen[52] or seen[30] or seen[62]:
        return None
    if choice in ('demo', 'recorded'):
        return int(demo[t]) if t < len(demo) else None
    if choice == 'old':
        return old
    if choice == 'wait':
        return encode(1) if t < 16 else None
    if choice == 'walk_guard':
        return encode(6 if t < 12 else 1)
    if choice == 'walk_poke':
        if t < 10:
            return encode(6)
        return encode(2, 'B') if t == 10 else None
    if choice == '236C':
        return (encode(2), encode(3), encode(6, 'C'))[t] if t < 3 else None
    raise ValueError(choice)


def env_for(data):
    return EfzVecEnv(data, 1, num_threads=1, autoreset='disabled', reward_match=0)


def records(args):
    def read(path):
        with path.open(encoding='utf-8-sig') as f:
            return list(csv.DictReader(f))
    archive = args.archive
    who = {(r['id'], r['side']): r['player'] for r in read(archive / 'players.csv')}
    files = {r['id']: archive.joinpath(*r['path'].split('\\')) for r in read(archive / 'index.csv')}
    rows = [r for r in read(archive / 'datasets/ayu/matches.csv') if r['in_sync'] == '1']
    rng = np.random.default_rng(117)
    rng.shuffle(rows)
    people = set()
    held_out = set()
    for split, chars in [('dev', DEV), ('test', TEST)]:
        for char in chars:
            n = 0
            for r in rows:
                if r['opponent'] != char:
                    continue
                rid, side = r['id'], int(r['side'])
                pair = {who.get((rid, str(i))) for i in range(2)}
                if None in pair or (split == 'test' and people.intersection(pair)):
                    continue
                if split == 'dev':
                    people.update(pair)
                else:
                    held_out.update(pair)
                yield split, char, rid, side, files[rid], int(r['winner']), int(r['frames'])
                n += 1
                if n == args.games:
                    break
    if getattr(args, 'split', None) == 'matchup':
        for char in TEST:
            n = 0
            for r in rows:
                rid = r['id']
                pair = {who.get((rid, str(i))) for i in range(2)}
                if r['opponent'] != char or None in pair or held_out.intersection(pair):
                    continue
                yield 'matchup', char, rid, int(r['side']), files[rid], int(r['winner']), int(r['frames'])
                n += 1
                if n == args.games:
                    break
    if args.oci:
        for rid, (char, frames) in OCI_GAMES.items():
            path, = args.oci.glob(f'{rid} *.rep')
            yield 'oci', char, rid, 0, path, 0, frames


def starts(env, path, side, seed, limit, winner, frames, jump_intent=False):
    env.play(0, path)
    env.reset()
    inputs, views = [], []
    while True:
        views.append(env.obs[0].copy())
        _, _, term, cut, info = env.step(IDLE)
        inputs.append(info['input'][0].copy())
        if term[0] or cut[0]:
            break
    if not term[0] or info['winner'][0] != winner or (frames and info['frame'][0] != frames):
        raise ValueError(f'Replay did not reproduce its result: {path}')
    views = np.stack(views)
    candidates = [t for t in range(WARM, len(views)-1)
                  if eligible(views[t-DELAY, side]) and views[t-WARM, side, 1] == views[t, side, 1]]
    if jump_intent:
        candidates = [t for t in candidates if inputs[t][side] & 8
                      and all(not (bits[side] & 8) for bits in inputs[t-DELAY:t])]
    rng = np.random.default_rng(seed)
    rng.shuffle(candidates)
    picks = []
    for t in candidates:
        if all(abs(t - prev) >= HORIZON for prev in picks):
            picks.append(t)
        if len(picks) == limit:
            break
    env.play(0, path)
    env.reset()
    current = 0
    for t in sorted(picks):
        while current < t - WARM:
            env.step(IDLE)
            current += 1
        past = np.asarray(inputs[max(0, t-60):t], np.uint8)[:, side]
        recorded = np.asarray(inputs[t:t+24], np.uint8)[:, side]
        yield t, env.save_state(0), inputs[t-WARM:t], views[t-WARM:t+1], past, recorded


class Duel:
    def __init__(self, args, char, generation, second_policy=None):
        self.env = env_for(args.data)
        self.ayu = NativeAgent(args.agent)
        self.old = NativeAgent(args.teacher if second_policy is None else second_policy)
        self.enemy = NativeAgent(HERE / char / generation / 'combos.efzagent')
        self.char = char
        self.demos = Demonstrations(args.demos) if getattr(args, "demos", None) else None
        self.exclude = ""
        self.demo = None
        self.aa = advantages.Advantages(char, 1, antiair=1, seed=1)
        if self.ayu.delay != DELAY or self.old.delay != DELAY or self.enemy.delay != DELAY:
            raise ValueError('The trial expects all three players to have 11-frame sight')

    def attach(self, side, seed, habit):
        self.side = side
        self.ayu.attach(self.env, 0, side, seed=seed)
        self.enemy.attach(self.env, 0, 1-side, seed=seed+1)
        self.old.attach(self.env, 0, side, seed=seed+2)
        self.aa.resize(1)
        self.aa.rng = np.random.default_rng(seed+3)
        self.habit = habit

    def step(self, choice='round25', age=24, seen=None, forced=None):
        s = self.side
        me, op = self.env.obs[0, s], self.env.obs[0, 1-s]
        live = not (me[2] or me[3])
        mine = self.ayu.step(me, live)
        old = self.old.step(me, live)
        enemy = self.enemy.step(op, live)
        if forced is not None:
            mine, enemy = forced[s], forced[1-s]
        else:
            if self.habit:
                action = self.aa.step(0, op)
                if action is not None:
                    enemy = encode(*action)
            if choice == 'resample_jump':
                self.jump_sample = None
                if mine & 8:
                    mine = old
                    self.jump_sample = 'up again' if mine & 8 else 'other input'
            elif choice == 'takeoff':
                if age == 0:
                    mine = self.planned
            elif choice != 'round25' and seen is not None:
                if choice == "demo" and age == 0:
                    self.demo = self.demos.choose(seen, self.exclude)
                action = override(choice, age, seen, old, self.demo)
                if action is not None:
                    mine = action
        self.ayu.played(mine)
        self.old.played(mine)
        self.enemy.played(enemy)
        actions = [[mine, enemy] if s == 0 else [enemy, mine]]
        _, reward, term, cut, info = self.env.step(np.asarray(actions, np.uint8))
        return int(round(reward[0, s]*9999)), bool(term[0] or cut[0])

    def trial(self, side, seed, habit, state, inputs, views, choice, trace=None):
        self.env.load_state(0, state)
        self.attach(side, seed, habit)
        for bits in inputs:
            self.step(forced=bits)
        np.testing.assert_allclose(self.env.obs[0], views[-1], rtol=0, atol=1e-6)
        recent = collections.deque(views[-DELAY-1:-1, side], maxlen=DELAY)
        hp = 0
        used_236c = False
        # Finish a combo in progress at the cutoff, up to another 160 frames.
        before = int(views[-1, side, 18])
        for t in range(2*HORIZON):
            me = self.env.obs[0, side]
            if t >= HORIZON and not (me[30] or me[62]):
                break
            action = int(me[18])
            if trace is not None and t < 32 and action != before and action >= tactics.FIRST_OWN:
                trace.append((t, action))
            before = action
            if t < 32 and action == 0x106:
                used_236c = True
            seen = recent[0]
            recent.append(me.copy())
            swing, done = self.step(choice, t, seen)
            hp += swing
            if done or self.env.obs[0, side, 1] != views[-1, side, 1]:
                break
        return hp, used_236c

    def close(self):
        for agent in (self.ayu, self.old, self.enemy):
            agent.close()
        self.env.close()


def trials(args):
    replay = env_for(args.data)
    duels = {}
    sampled = set()
    game_number = collections.Counter()
    with args.out.open('x') as out:
        for split, char, rid, side, path, winner, frames in records(args):
            if args.split and split != args.split or args.char and char != args.char:
                continue
            if args.replicate:
                if (split, char) in sampled:
                    continue
                sampled.add((split, char))
            generation = 'exploiter18' if split == 'dev' else 'exploiter19'
            if split == 'matchup':
                generation = ('exploiter16', 'exploiter18')[game_number[char] % 2]
                game_number[char] += 1
            key = char, generation
            if key not in duels:
                duels[key] = Duel(args, *key)
            duel = duels[key]
            duel.exclude = rid
            origin = int(rid) if rid.isdigit() else int(rid[-6:])
            count = 0
            snapshots = starts(replay, path, side, origin, args.starts, winner, frames, args.jump_intent)
            for index, (t, snapshot, inputs, views, past, recorded) in enumerate(snapshots):
                if args.replicate and count >= 3:
                    break
                duel.env.load_state(0, snapshot)
                for controls in inputs:
                    duel.env.step(np.array([controls], np.uint8))
                difference = abs(duel.env.obs[0] - views[-1])
                if not np.all(difference <= 1e-6):
                    fields = [duel.env.observation_names[col] for col in np.where(difference > 1e-6)[1]]
                    excluded = dict(split=split, replay=rid, frame=t, fields=sorted(set(fields)))
                    print('excluded warm-up mismatch', json.dumps(excluded), flush=True)
                    with args.out.with_suffix('.excluded.jsonl').open('a') as rejected:
                        print(json.dumps(excluded), file=rejected)
                    continue
                x = cues(views[-1-DELAY, side])
                if args.context_only:
                    history = [bits[side] for bits in inputs[-DELAY-1:]]
                    current = views[-1, side]
                    row = dict(char=char, replay=rid, frame=t, x=x, inputs=input_cues(history),
                               airborne=bool(current[39]), action=int(current[18]))
                    print(json.dumps(row), file=out, flush=True)
                    count += 1
                    continue
                habit = (origin + index) % 2
                options = [o for o in OPTIONS if o != '236C' or max(views[-1-DELAY, side, 10:12]) >= 0.5]
                if args.command_probe:
                    if '236C' in options:
                        trace = []
                        seed = (origin * 20011 + t * 31) % (2**31)
                        hp, came = duel.trial(side, seed, habit, snapshot, inputs, views, '236C', trace)
                        # A preceding forward can complete 623 before the input parser checks 236.
                        # Exact 6, excluding diagonals, is the first part of that motion.
                        forward = bool(np.any((past[-57:] & 15) == 1))
                        row = dict(char=char, replay=rid, frame=t, hp=hp, came=came,
                                   forward=forward, trace=trace)
                        print(json.dumps(row), file=out, flush=True)
                    count += 1
                    continue
                if args.jump_intent:
                    duel.planned = int(recorded[0])
                    options += ['takeoff', 'demo']
                elif args.recorded_entry:
                    duel.demo = recorded
                    options = ['round25', 'recorded']
                elif args.replicate or split == 'matchup':
                    options.append('demo')
                elif args.demos:
                    options = ['round25', 'demo']
                for draw in range(args.draws):
                    seed = (origin * 20011 + t * 31 + draw * 1009) % (2**31)
                    outcomes = {o: duel.trial(side, seed, habit, snapshot, inputs, views, o) for o in options}
                    hp = {o: value[0] for o, value in outcomes.items()}
                    if count == draw == 0:
                        repeat = duel.trial(side, seed, habit, snapshot, inputs, views, 'round25')
                        if repeat != outcomes['round25']:
                            raise RuntimeError('Repeated baseline differs at identical start and seed')
                    row = dict(split=split, char=char, replay=rid, frame=t, draw=draw,
                               habit=habit, x=x, hp=hp, generation=generation, used_236c={o: v[1] for o, v in outcomes.items()})
                    if split == "matchup":
                        row["x"] = x + input_cues(past[-DELAY-1:])
                    if args.jump_intent:
                        row['x'] = x + input_cues(past[-DELAY-1:])
                        row['planned'] = duel.planned
                        row['already_airborne'] = bool(views[-1, side, 39])
                    print(json.dumps(row), file=out, flush=True)
                count += 1
            print(split, char, rid, count, 'positions', flush=True)
    for duel in duels.values():
        duel.close()
    replay.close()


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('data', 'archive', 'agent', 'teacher', 'out'):
        parser.add_argument('--'+name, type=Path, required=True)
    parser.add_argument('--oci', type=Path)
    parser.add_argument('--split', choices=['dev', 'test', 'oci', 'matchup'])
    parser.add_argument('--games', type=int, default=5)
    parser.add_argument('--starts', type=int, default=6)
    parser.add_argument('--draws', type=int, default=2)
    parser.add_argument('--command-probe', action='store_true', help='record which character move the 236C input produced')
    parser.add_argument('--char', help='process one character from the unchanged split')
    parser.add_argument('--replicate', action='store_true',
                        help='all options on three positions of the first replay per character')
    parser.add_argument('--context-only', action='store_true', help='record known input history and execution diagnostics')
    parser.add_argument('--recorded-entry', action='store_true',
                        help='score the original human input prefix as an offline control')
    parser.add_argument('--jump-intent', action='store_true',
                        help='branch at the first proposed up input in round 25 netplay')
    parser.add_argument('--demos', type=Path, help='try retrieved ground entries against round25')
    parser.add_argument('--harvest', action='store_true', help='extract demonstration clips from development replays')
    args = parser.parse_args()
    if args.recorded_entry and (args.split != 'test' or args.demos or args.replicate or args.harvest
                                or args.context_only or args.command_probe):
        parser.error('--recorded-entry uses the human test split and no other probe')
    if args.jump_intent and (args.split != 'oci' or not args.oci or not args.demos or args.replicate
                             or args.harvest or args.context_only or args.command_probe):
        parser.error('--jump-intent requires --split oci, --oci and --demos and no other probe')
    if (args.replicate or args.split == 'matchup') and not args.demos:
        parser.error('the repeated-draw and known-matchup trials require --demos')
    if args.harvest:
        harvest(args)
    else:
        trials(args)


if __name__ == '__main__':
    main()
