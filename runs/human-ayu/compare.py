"""People's Ayu next to agents', by evaluate.py's measures: a markdown table.

    python runs/human-ayu/compare.py people.json name=eval.json[:key] ...

people.json is people.py's; each eval.json is evaluate.py --json's (key: which of its
matches, 'cpu4' or 'vs'; the first if left out), P1's side shown.
"""

import json
import sys

ROWS = [
    ('Wins / losses / cut', None),
    ('Presses a second', 'presses_per_second'),
    ('Jumps a minute', 'jumps_per_min'),
    ('Guards a minute (ground)', 'guard_ground_per_min'),
    ('Hits taken a minute, ground + air', ('hit_ground_per_min', 'hit_air_per_min')),
    ('Recoil guard, ground / air', ('rg_ground', 'rg_air')),
    ('Recoil counter', 'rc'),
    ('After its RG: a move / it hit', ('rg_move', 'rg_punish')),
    ('After its RG: a long or RF move', 'rg_long'),
    ('623A / 623B a minute', ('guess_623A_per_min', 'guess_623B_per_min')),
    ('623A / 623B counter hits', ('guess_623A_counter', 'guess_623B_counter')),
    ('Combos a minute; damage a minute', ('combos_per_min', 'combo_damage_per_min')),
    ('A combo: hits; damage (HP)', ('combo_hits', 'combo_damage')),
    ('Combo damage: 90th percentile; most', ('combo_damage_p90', 'combo_damage_max')),
    ('Combo hits: 90th percentile; most', ('combo_hits_p90', 'combo_hits_max')),
    ('Combos of 3+ hits', 'combo_3plus'),
    ('Combos (2+) with a special; with IC', ('combo_special', 'combo_ic')),
    ('Instant Charges a minute', 'ic_per_min'),
    ('Presses; turns made while unable to move', ('busy_presses', 'busy_turns')),
]


def fmt(v, key):
    if v is None:
        return '-'
    if key.endswith(('_per_min', '_per_second')):
        return f'{v:.2f}' if v < 100 else f'{v:.0f}'
    if key.startswith(('combo_hits', 'combo_damage')):
        return f'{v:.2f}' if v < 100 else f'{v:.0f}'
    return f'{v:.0%}' if v >= 0.01 or v == 0 else f'{v:.1%}'


def main():
    people = json.load(open(sys.argv[1]))['all']
    cols = [('People', people, None)]
    for arg in sys.argv[2:]:
        name, path = arg.split('=', 1)
        key = None
        if ':' in path[2:]:
            path, key = path.rsplit(':', 1)
        data = json.load(open(path))
        r = data[key] if key else next(iter(data.values()))
        cols.append((name, r['sides'][0], r))
    print('| | ' + ' | '.join(c[0] for c in cols) + ' |')
    print('|---' * (len(cols) + 1) + '|')
    for label, k in ROWS:
        cells = []
        for _, side, r in cols:
            if k is None:
                cells.append('-' if r is None else
                             f"{r['win']:.0%} / {r['loss']:.0%} / {r['cut']:.0%}")
            elif isinstance(k, tuple):
                cells.append(' / '.join(fmt(side.get(x), x) for x in k))
            else:
                cells.append(fmt(side.get(k), k))
        print(f'| {label} | ' + ' | '.join(cells) + ' |')


if __name__ == '__main__':
    main()
