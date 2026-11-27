"""Compare native Ayu builds on matched sets and replay positions."""
import argparse
from collections import Counter, defaultdict
import json
from pathlib import Path

import numpy as np


def read(path):
    return [json.loads(line) for line in path.read_text().splitlines()]


def summarize(groups, title):
    reference = groups['r25']
    seeds = sorted(reference)
    for name, sets in sorted(groups.items()):
        if set(sets) != set(seeds):
            raise ValueError(f'Unpaired seeds in {title} for {name}')
        legs = [leg for seed in seeds for leg in sets[seed]]
        diffs = []
        for seed in seeds:
            a, b = sets[seed], reference[seed]
            if len(a) != len(b) or not a:
                raise ValueError(f'Unpaired games in {title} for {name}, seed {seed}')
            diffs.append([np.mean([x[k] - y[k] for x, y in zip(a, b)]) for k in ('win', 'net')])
        # Draw sets together to account for opponent memory persisting between games.
        # For the two held-out policies we draw their common seed together as well.
        changes = np.array(diffs) * [100, 1]
        draws = np.random.default_rng(712).integers(len(seeds), size=(5000, len(seeds)))
        ci = np.quantile(changes[draws].mean(axis=1), [.025, .975], axis=0).T
        counts = Counter()
        for leg in legs:
            counts.update(leg['counts'])
        frames = sum(g['frames'] for g in legs)
        pressure_frames = sum(g['pressure'] for g in legs)
        print(title, name, 'wins', sum(g['win'] for g in legs), '/', len(legs),
              'net HP/game', round(np.mean([g['net'] for g in legs])),
              'change (win points, HP/game)', changes.mean(axis=0).round(1).tolist(),
              'paired seed 95% intervals', ci.round(1).tolist(),
              'presses/s', round(64 * sum(g['presses'] for g in legs) / frames, 2),
              'under pressure', round(64 * sum(g['pressure_presses'] for g in legs) / pressure_frames, 2),
              'ground throws taken', counts['ground'], 'counts', dict(sorted(counts.items())))


def pooled(profiles, names):
    result = defaultdict(dict)
    first, second = (profiles[n] for n in names)
    for agent in first:
        if set(first[agent]) != set(second[agent]):
            raise ValueError(f'Unpaired seeds between {names} for {agent}')
        for seed, legs in first[agent].items():
            result[agent][seed] = legs + second[agent][seed]
    return result


def replay_summary(folder):
    by_source = defaultdict(lambda: defaultdict(list))
    for path in sorted(folder.glob('*.jsonl')):
        source = path.stem.split('-')[0]
        for row in read(path):
            by_source[source][path.stem, row['frame']].append(row)
    for source, positions in sorted(by_source.items()):
        games = {game for game, _ in positions}
        print(source, len(positions), 'walks in', len(games), 'games containing a cue')
        for position, rows in sorted(positions.items()):
            if {row['draw'] for row in rows} != set(range(8)) or len(rows) != 8:
                raise ValueError(f'Incomplete draws at {position}')
        rows = [row for outcomes in positions.values() for row in outcomes]
        for name in sorted(rows[0]['outcomes']):
            outcomes = [r['outcomes'][name] for r in rows]
            print(name, 'ground throws', sum(x['ground'] for x in outcomes), '/', len(rows),
                  'initial up-back', sum(x['first'] == 10 for x in outcomes),
                  'net HP per 120 frames', round(np.mean([x['net'] for x in outcomes])))


def archive_summary(folder):
    manifest = json.loads((folder / 'archive-survey.json').read_text())
    records = manifest['matches']
    print('Community survey', len(records), 'unique games,', sum(bool(r['walks']) for r in records),
          'with a walk,', sum(any(p['ground'] for p in r['walks']) for r in records), 'with a walk to throw')
    measures = defaultdict(list)
    by_player = defaultdict(list)
    by_game = []
    prior_throw = []
    for record in records:
        if not record['walks']:
            continue
        rows = read(folder / 'external' / (record['id'] + '.jsonl'))
        expected = {(p['tick'], p['ground'], draw) for p in record['walks'] for draw in range(8)}
        observed = {(r['frame'], r['original_ground'], r['draw']) for r in rows}
        if expected != observed or len(rows) != len(expected):
            raise ValueError(f"Survey and native replay differ in game {record['id']}")
        observed_throws = {p['tick']: p.get('prior_ground') for p in record['walks']}
        totals = [0, 0, 0]
        for row in rows:
            base = row['outcomes']['agent-league25-stay-s1-round25']
            new = row['outcomes']['ayu-round28']
            metrics = [base['ground'], new['ground'], new['net'] - base['net']]
            measures[row['original_ground']].append(metrics)
            by_player[record['player']].append(metrics)
            if observed_throws[row['frame']]:
                prior_throw.append(metrics)
            totals[0] += base['ground'] - new['ground']
            totals[1] += new['net'] - base['net']
            totals[2] += 1
        by_game.append(totals)
    for label, rows in [('all', measures[True] + measures[False]), ('original throw', measures[True]),
                        ('other walk', measures[False])]:
        values = np.array(rows)
        print('community', label, len(rows) // 8, 'walks, ground throws r25/r28',
              values[:, :2].sum(axis=0).tolist(), '/', len(rows), 'mean HP change', round(values[:, 2].mean(), 1))
    # Every eligible walk receives the same weight. Keep each full game's walks
    # and all their repeated draws together during uncertainty estimation.
    by_game = np.array(by_game)
    indices = np.random.default_rng(7791).integers(len(by_game), size=(5000, len(by_game)))
    draws = by_game[indices].sum(axis=1)
    ci = np.quantile(draws[:, :2] / draws[:, 2, None] * [100, 1], [.025, .975], axis=0).T
    print('community game-cluster 95% intervals, throws prevented (points) and HP/cue', ci.round(1).tolist())
    if prior_throw:
        values = np.array(prior_throw)
        print('after an earlier visible ground throw', len(values) // 8, 'walks, throws r25/r28',
              values[:, :2].sum(axis=0).tolist(), 'mean HP change', round(values[:, 2].mean(), 1))
    for player, rows in sorted(by_player.items(), key=lambda item: str(item[0])):
        values = np.array(rows)
        print('player', player, 'walks', len(rows) // 8, 'throws prevented',
              int((values[:, 0] - values[:, 1]).sum()), 'mean HP change', round(values[:, 2].mean(), 1))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('folder', type=Path)
    args = parser.parse_args()
    profiles = defaultdict(lambda: defaultdict(dict))
    duels = defaultdict(list)
    for path in sorted(args.folder.glob('*.jsonl')):
        if path.stem.startswith('duel-'):
            _, name, opponent = path.stem.split('-')
            for row in read(path):
                duels[name, opponent].extend(row['legs'])
            continue
        if path.stem.startswith('control-'):
            _, name, profile = path.stem.split('-')
        elif path.stem.startswith('challenge-'):
            _, name, _ = path.stem.split('-')
            profile = 'challenge'
        else:
            name, profile, _ = path.stem.rsplit('-', 2)
        name = {'ayu-round28': 'r28', 'ayu-round28b': 'r28b'}.get(name, name)
        for row in read(path):
            runs = profiles[profile][name]
            if len(row['legs']) != 3 or row['seed'] in runs:
                raise ValueError(f'Incomplete or duplicate set in {name} {profile}')
            runs[row['seed']] = row['legs']
    for profile, sets in sorted(profiles.items()):
        summarize(sets, profile)
    for pair in [('mixed', 'transfer'), ('walkthrow', 'walkfeint')]:
        if all(n in profiles for n in pair):
            summarize(pooled(profiles, pair), '+'.join(pair))
    for (a, b), legs in sorted(duels.items()):
        print('mirror P1', a, 'P2', b, 'P1 wins', sum(g['win'] for g in legs), '/', len(legs))
    replay_summary(args.folder / 'human-branches')
    if (args.folder / 'archive-survey.json').exists():
        archive_summary(args.folder)


if __name__ == '__main__':
    main()
