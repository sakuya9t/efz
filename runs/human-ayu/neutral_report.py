"""Summarize snapshot and complete-set comparisons from neutral_trials and neutral_sets."""
import argparse
import collections
from pathlib import Path

import numpy as np

from neutral_sets import Chooser, joined, rows


def interval(groups):
    """Equal weight per group, with a paired percentile interval over groups."""
    values = np.array([np.mean(groups[key], axis=0) for key in sorted(groups)])
    rng = np.random.default_rng(206)
    draws = rng.choice(len(values), (5000, len(values)))
    bounds = np.quantile(values[draws].mean(axis=1), [.025, .975], axis=0)
    return np.round(values.mean(axis=0), 2), np.round(bounds.T, 2)


def branches(data, chooser):
    starts = collections.defaultdict(list)
    for r in data:
        starts[r['replay'], r['frame']].append(r)
    by_mode = collections.defaultdict(lambda: collections.defaultdict(list))
    counts = collections.Counter()
    for (replay, _), pair in starts.items():
        assert len(pair) == 2 and {r['draw'] for r in pair} == {0, 1}
        for r, other in (pair, pair[::-1]):
            hp = r['hp']
            labels = dict(fixed=chooser.pick(r['x'], hp, 'fixed'),
                          context=chooser.pick(r['x'], hp, 'context'),
                          hindsight=max(hp, key=hp.get),
                          repeat_best=max(other['hp'], key=other['hp'].get))
            counts[labels['context']] += 1
            for o in chooser.options:
                labels[o] = o if o in hp else 'round25'
            for mode, opt in labels.items():
                by_mode[mode][replay].append(hp[opt] - hp['round25'])
    print('replays', len({r['replay'] for r in data}), 'starts', len(starts), 'context picks', dict(counts))
    for mode, values in by_mode.items():
        print(mode, *interval(values))


def replicated(data):
    """Choose using independent simulation draws; score on a different draw at that start."""
    starts = collections.defaultdict(list)
    for r in data:
        starts[r['replay'], r['frame']].append(r)
    scores = collections.defaultdict(lambda: collections.defaultdict(list))
    for (replay, _), trials in starts.items():
        trials.sort(key=lambda r: r['draw'])
        assert len(trials) == 10 and [r['draw'] for r in trials] == list(range(10))
        for i, row in enumerate(trials):
            hp = row['hp']
            for n in (1, 3, 5, 9):
                others = [trials[(i-j-1)%10]['hp'] for j in range(n)]
                best = max(hp, key=lambda o: sum(s[o] for s in others))
                scores[n][replay].append(hp[best] - hp['round25'])
    print('replicated starts', len(starts))
    for n, groups in scores.items():
        print('independent ranking draws', n, *interval(groups))


def commands(data, traces):
    by_key = {(r['replay'], r['frame']): r for r in data if r['draw'] == 0 and '236C' in r['hp']}
    counts = collections.defaultdict(collections.Counter)
    for trace in traces:
        r = by_key.pop((trace['replay'], trace['frame']))
        assert trace['hp'] == r['hp']['236C'] and trace['came'] == r['used_236c']['236C']
        counter = counts[trace['forward']]
        counter['attempts'] += 1
        counter['236C in 32 frames'] += trace['came']
        first = trace['trace'][0][1] if trace['trace'] else None
        counter['first new move 623C'] += first in (0xfb, 0x10b)
    assert not by_key
    safe = {(t['replay'],t['frame']) for t in traces if not t['forward']}
    gated = collections.defaultdict(list)
    for r in data:
        use = (r['replay'],r['frame']) in safe and not r['x'][7]
        delta = r['hp']['236C'] - r['hp']['round25'] if use else 0
        gated[r['replay']].append(delta)
    print('236C with recent forward and jump excluded', *interval(gated))
    print('command results by prior forward', {k: dict(v) for k, v in counts.items()})


def recorded_entries(data, recorded):
    baseline = {(r['replay'], r['frame'], r['draw']): r for r in data}
    options = collections.defaultdict(lambda: collections.defaultdict(list))
    for r in recorded:
        paired = baseline.pop((r['replay'], r['frame'], r['draw']))
        hp = r['hp']['round25']
        if hp != paired['hp']['round25'] or r['habit'] != paired['habit']:
            raise ValueError('Recorded human input and retrieval trials have different baselines')
        options['recorded'][r['replay']].append(r['hp']['recorded'] - hp)
        options['retrieved'][r['replay']].append(paired['hp']['demo'] - hp)
        options['recorded minus retrieved'][r['replay']].append(r['hp']['recorded'] - paired['hp']['demo'])
    if baseline:
        raise ValueError('Missing recorded-entry trials')
    for choice, groups in options.items():
        print(choice, 'HP/decision', *interval(groups))


def takeoffs(data, chooser):
    by_mode = collections.defaultdict(lambda: collections.defaultdict(list))
    positions = set()
    airborne = set()
    for r in data:
        key = r['replay'], r['frame']
        positions.add(key)
        if r['already_airborne']:
            airborne.add(key)
        hp = r['hp']
        options = [o for o in chooser.options if o in hp]
        choice = chooser.pick(r['x'], options, 'context')
        selected = 'takeoff' if choice == 'round25' else choice
        for mode, option in [(o,o) for o in options] + [('context', selected)]:
            by_mode[mode][r['replay']].append(hp[option] - hp['takeoff'])
    print('round 25 planned jumps', len(positions), 'already airborne', len(airborne))
    for mode, values in by_mode.items():
        print(mode, 'HP vs issuing the proposed up', *interval(values),
              'per replay', {k: round(np.mean(v)) for k, v in values.items()})


def sets(data):
    groups = collections.defaultdict(dict)
    opponents = {}
    for r in data:
        key = r['char'], r['seed']
        # The original held-out baselines used the evaluator's default defender.
        defender = r.get('generation', 'exploiter19'), r['habit'], len(r['legs'])
        if opponents.setdefault(key, defender) != defender:
            raise ValueError(f'Different defender or set length for {key}')
        if r['mode'] in groups[key]:
            raise ValueError(f'Duplicate set {key} {r["mode"]}')
        groups[key][r['mode']] = r['legs']
    modes = sorted(set.union(*(set(r) for r in groups.values())))
    for key, pair in groups.items():
        if 'round25' not in pair or set(pair) != set(modes):
            raise ValueError(f'Incomplete comparison for {key}')
    print('paired sets', len(groups), 'games per policy', sum(len(r['round25']) for r in groups.values()))
    for mode in modes:
        values = {}
        leg_wins = np.zeros(len(next(iter(groups.values()))['round25']), dtype=int)
        against_context = {}
        blocked = presses = time = blocked_time = wins = set_wins = 0
        picks = collections.Counter()
        for key, pair in groups.items():
            base, current = pair['round25'], pair[mode]
            base_wins = sum(r['won'] for r in base)
            n = sum(r['won'] for r in current)
            wins += n
            leg_wins += [r['won'] for r in current]
            if mode == 'adaptive' and 'context' in pair:
                static = pair['context']
                against_context[key] = [np.mean([r['net']-b['net'] for r,b in zip(current,static)])]
            set_wins += n > len(base)/2
            values[key] = [(100*(n-base_wins)/len(base),
                            np.mean([r['net']-b['net'] for r,b in zip(current,base)]),
                            100*(int(n>len(base)/2)-int(base_wins>len(base)/2)))]
            for r in current:
                picks.update(r['choices'])
                presses += r['presses']
                time += r['frames']
                blocked += r['blocked_presses']
                blocked_time += r['blocked_frames']
        print(mode, 'games/sets won', wins, set_wins, 'delta games(pp), HP/game, sets(pp)',
              *interval(values), 'presses/s overall and under pressure',
              round(64*presses/time,2), round(64*blocked/blocked_time,2), 'picks', dict(picks),
              'wins by leg', leg_wins.tolist())
        if against_context:
            print('adaptation minus context, HP/game', *interval(against_context))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('folder', type=Path)
    args = parser.parse_args()
    folder = args.folder
    chooser = Chooser(joined(folder/'dev.jsonl', folder/'demo-dev.jsonl', folder/'context-dev.jsonl'))
    for split in ('dev','test','oci'):
        print(split)
        data = joined(folder/f'{split}.jsonl', folder/f'demo-{split}.jsonl', folder/f'context-{split}.jsonl')
        branches(data, chooser)
        commands(data, rows(folder/f'command-{split}.jsonl'))
        if split != 'dev':
            replicated(rows(folder/f'replicate-{split}.jsonl'))
    known = collections.defaultdict(list)
    test = joined(folder/'test.jsonl', folder/'demo-test.jsonl', folder/'context-test.jsonl')
    recorded = [r for path in sorted(folder.glob('recorded-*.jsonl')) for r in rows(path)]
    if recorded:
        recorded_entries(test, recorded)
    jumps = [r for path in sorted(folder.glob('jump-*.jsonl')) for r in rows(path)]
    if jumps:
        takeoffs(jumps, chooser)
    for char in sorted({r['char'] for r in test}):
        practice = rows(folder/f'matchup-{char}.jsonl')
        chooser.learn_matchup(practice, char)
        for r in test:
            if r['char'] == char:
                choice = chooser.pick(r['x'], r['hp'], 'matchup')
                known[r['replay']].append(r['hp'][choice] - r['hp']['round25'])
        print('practice', char, len(practice)//2, 'starts')
    print('matchup-specific chooser, held-out HP/decision', *interval(known))
    games = [r for path in sorted(folder.glob('sets-*.jsonl')) for r in rows(path)]
    for label, chars in [('held-out', ['sayuri','exnanase','mizukab']), ('controls', ['kano','ikumi'])]:
        print(label)
        sets([r for r in games if r['char'] in chars])
    confirm = [r for path in sorted(folder.glob('confirm-*.jsonl')) for r in rows(path)]
    if confirm:
        print('known matchups, fresh seeds')
        sets(confirm)
    redraw = [r for path in sorted(folder.glob('redraw-*.jsonl')) for r in rows(path)]
    if redraw:
        for label, chars in [('held-out', ['sayuri','exnanase','mizukab']), ('controls', ['kano','ikumi'])]:
            print('first jump resampling,', label)
            sets([r for r in redraw if r['char'] in chars])


if __name__ == '__main__':
    main()
