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
]


def fmt(v, key):
    if v is None:
        return '-'
    if key.endswith(('_per_min', '_per_second')):
        return f'{v:.2f}'
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
