"""Fit a neutral option chooser on development branches and compare it in paired sets."""
import argparse
import collections
import json
from pathlib import Path

import numpy as np

from neutral_trials import DELAY, Duel, HORIZON, OPTIONS, cues, eligible, input_cues
from tactics import GUARDS


def rows(path):
    with path.open() as f:
        return [json.loads(line) for line in f]


def features(x):
    distance, rf, air, move, objects, wall, velocity = x[:7]
    d = np.clip((distance-160)/80, -2, 2)
    return np.array([1, d, 2*rf-1, air, move, min(2, objects), wall, velocity, d*move, d*air, *x[7:]])


def joined(primary, extra=None, context=None):
    main = rows(primary)
    if context:
        past = {(r['char'], r['replay'], r['frame']): r for r in rows(context)}
        for r in main:
            entry = past[r['char'], r['replay'], r['frame']]
            if r['x'] != entry['x']:
                raise ValueError('Context lookup has a different visible state')
            r['x'] = r['x'] + entry['inputs']
    if extra is None:
        return main
    def key(row):
        return row['char'], row['replay'], row['frame'], row['draw']
    additions = {key(r): r for r in rows(extra)}
    for r in main:
        other = additions.pop(key(r))
        if (r['hp']['round25'], r['x'][:7], r['habit']) != (other['hp']['round25'], other['x'], other['habit']):
            raise ValueError('The demonstration and main trials do not share a baseline')
        r['hp']['demo'] = other['hp']['demo']
    if additions:
        raise ValueError('Unmatched demonstration trials')
    return main


class Chooser:
    def __init__(self, development):
        if not development or any(r['split'] != 'dev' for r in development):
            raise ValueError('fit on development replays only')
        self.corrections = {}
        self.with_inputs = len(development[0]['x']) > 7
        self.delta, self.fixed, self.absolute = {}, {}, {}
        self.options = OPTIONS + (('demo',) if 'demo' in development[0]['hp'] else ())
        for choice in self.options:
            subset = [r for r in development if choice in r['hp']]
            x = np.stack([features(r['x']) for r in subset])
            # Draws from the same start share unit weight.
            weights = collections.Counter((r['replay'], r['frame']) for r in subset)
            w = np.array([1/weights[r['replay'], r['frame']] for r in subset])
            z = x.T * w
            penalty = np.diag([0.01] + [20.0]*(x.shape[1]-1))
            reward = np.array([r['hp'][choice] for r in subset])
            delta = reward - [r['hp']['round25'] for r in subset]
            self.absolute[choice] = np.linalg.solve(z @ x + penalty, z @ reward)
            self.delta[choice] = np.linalg.solve(z @ x + penalty, z @ delta)
            self.fixed[choice] = np.average(delta, weights=w)

        # A control that varies its play at the development chooser's frequencies.
        self.mixes = collections.defaultdict(collections.Counter)
        for r in development:
            action = self.pick(r['x'], r['hp'], 'context')
            self.mixes['236C' in r['hp']][action] += 1

    def learn_matchup(self, extra, char):
        if not extra or any(r['split'] != 'matchup' or r['char'] != char for r in extra):
            raise ValueError('Expected independent practice games of one character')
        for name in ('exploiter16', 'exploiter18'):
            generation = [r for r in extra if r['generation'] == name]
            if not generation:
                raise ValueError(f'Missing practice defender {name}')
            offsets = {}
            for o in self.options:
                residuals = collections.defaultdict(list)
                for r in generation:
                    if o in r['hp']:
                        observed = r['hp'][o] - r['hp']['round25']
                        residuals[r['replay'], r['frame']].append(observed - self.delta[o] @ features(r['x']))
                offsets[o] = sum(np.mean(v) for v in residuals.values()) / (12 + len(residuals))
            self.corrections[name] = offsets

    def pick(self, x, options, mode, residual=None, rng=None):
        if mode == 'round25':
            return mode
        if mode == 'mixture':
            weights = self.mixes['236C' in options]
            choices = list(weights)
            p = np.array([weights[o] for o in choices], float)
            return str(rng.choice(choices, p=p/p.sum()))
        if mode == 'fixed':
            return max(options, key=self.fixed.get)
        f = features(x)
        def score(choice):
            s = self.delta[choice] @ f
            if mode == 'matchup':
                s += min(offsets[choice] for offsets in self.corrections.values())
            if residual is not None:
                total, n = residual[choice]
                s += total / (12 + n)
            return s
        return max(options, key=score)


def credit(memory, pending, final_net):
    """Record a completed exchange after its damage is visible, or at a round's end."""
    paid = final_net - pending['initial_net']
    account = memory[pending['choice']]
    account[0] += np.clip(paid - pending['predicted'], -3000, 3000)
    account[1] += 1


def one_set(args, duel, chooser, seed, habit, mode):
    env = duel.env
    env.set_matches(chars=('ayu', duel.char))
    env.seed(0, seed)
    env.reset()
    duel.attach(0, seed, habit)
    rng = np.random.default_rng(seed+747)
    memory = {o: [0, 0] for o in chooser.options}
    legs = []
    for leg in range(args.legs):
        if leg:
            duel.ayu.next_match()
            duel.enemy.next_match()
            duel.old.next_match()
            duel.aa.clear(0)
            env.reset()
        recent = collections.deque(maxlen=DELAY)
        controls_seen = collections.deque([0]*(DELAY+1), maxlen=DELAY+1)
        pending = None
        last_jump_sample = -DELAY
        net = presses = blocked_presses = blocked_frames = frames = prev = 0
        nchoices = collections.Counter()
        last_round = int(env.obs[0, 0, 1])
        while True:
            me = env.obs[0, 0]
            if int(me[1]) != last_round:
                if pending:
                    credit(memory, pending, net)
                    pending = None
                recent.clear()
                last_jump_sample = -DELAY
                last_round = int(me[1])
            seen, seen_net = recent[0] if len(recent) == DELAY else (None, None)
            if pending and seen is not None:
                age_seen = frames - pending['start'] - DELAY
                if age_seen >= HORIZON and (age_seen >= 2*HORIZON or not (seen[30] or seen[62])):
                    credit(memory, pending, seen_net)
                    pending = None
            jump_eligible = False
            if mode == 'resample_jump':
                jump_eligible = (seen is not None and eligible(seen) and frames-last_jump_sample >= DELAY
                                 and not any(bits & 8 for bits in list(controls_seen)[-DELAY:]))
            elif pending is None and seen is not None and eligible(seen):
                x = cues(seen)
                if chooser.with_inputs:
                    x.extend(input_cues(controls_seen))
                options = [o for o in chooser.options if o != '236C' or seen[10] >= .5 or seen[11]]
                choice = chooser.pick(x, options, mode, memory if mode == 'adaptive' else None, rng)
                nchoices[choice] += 1
                pending = dict(start=frames, choice=choice, initial_net=net,
                               predicted=float(chooser.absolute[choice] @ features(x)))
            recent.append((me.copy(), net))
            blocked = bool(me[20] or int(me[18]) in GUARDS)
            if jump_eligible:
                swing, done = duel.step('resample_jump')
                if duel.jump_sample is not None:
                    nchoices[duel.jump_sample] += 1
                    last_jump_sample = frames
            elif pending:
                swing, done = duel.step(pending['choice'], frames-pending['start'], seen)
            else:
                swing, done = duel.step()
            frames += 1
            net += swing
            controls = int(env.info['input'][0,0])
            controls_seen.append(controls)
            pressed = ((controls & ~prev) >> 4).bit_count()
            presses += pressed
            blocked_presses += blocked * pressed
            blocked_frames += blocked
            prev = controls
            if done:
                if pending:
                    credit(memory, pending, net)
                legs.append(dict(won=int(env.info['winner'][0] == 0), net=net, frames=frames,
                                 presses=presses, blocked_frames=blocked_frames,
                                 blocked_presses=blocked_presses, choices=dict(nchoices)))
                break
    return legs


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('data', 'agent', 'teacher', 'dev', 'out'):
        parser.add_argument('--'+name, type=Path, required=True)
    parser.add_argument('--char', required=True)
    parser.add_argument('--generation', default='exploiter19')
    parser.add_argument('--sets', type=int, default=4)
    parser.add_argument('--legs', type=int, default=3)
    parser.add_argument('--seed', type=int, default=70)
    parser.add_argument('--modes', nargs='+', default=['round25', 'fixed', 'mixture', 'context', 'adaptive'],
                        choices=['round25', 'fixed', 'mixture', 'context', 'adaptive', 'matchup', 'resample_jump'])
    parser.add_argument('--demos', type=Path)
    parser.add_argument('--dev-demo', type=Path)
    parser.add_argument('--dev-context', type=Path)
    parser.add_argument('--matchup-training', type=Path)
    args = parser.parse_args()
    if bool(args.dev_demo) != bool(args.demos):
        parser.error('--demos and --dev-demo go together')
    chooser = Chooser(joined(args.dev, args.dev_demo, args.dev_context))
    if 'matchup' in args.modes:
        if not args.matchup_training or not args.dev_context:
            parser.error('--modes matchup needs --matchup-training and --dev-context')
        chooser.learn_matchup(rows(args.matchup_training), args.char)
    duels = {}
    with args.out.open('x') as out:
        for k in range(args.sets):
            seed = args.seed + k
            for mode in args.modes:
                second = args.agent if mode == 'resample_jump' else args.teacher
                if second not in duels:
                    duels[second] = Duel(args, args.char, args.generation, second_policy=second)
                duel = duels[second]
                legs = one_set(args, duel, chooser, seed, seed%2, mode)
                row = dict(char=args.char, generation=args.generation, seed=seed, habit=seed%2, mode=mode, legs=legs)
                print(json.dumps(row), file=out, flush=True)
                print(args.char, seed, mode, [r['won'] for r in legs], flush=True)
    for duel in duels.values():
        duel.close()


if __name__ == '__main__':
    main()
