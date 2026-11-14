"""A checkpoint's 64-match comparisons in one table, beside others' (docs/training-v2.md's
judging): the league of 39 in the plain game (the twenty, the two reversal exploiters,
the seventeen helpers, Kano's seven), the level-4 CPU's tiers, Kanna's HP, each advantage
profile's set, the human limits, and against a profile's opponents what a person's
defence asks for (the agent's okizeme high / low / throw, its throws, its string guarded
then its hit, its guard on rising opened).

    python runs/human-ayu/scorecard.py NAME=PREFIX[@TAG][,KANNA] ... [--profile person]

PREFIX: the files PREFIX-<opponent>.json and PREFIX-<profile>-<opponent>.json of
evaluate.py --json (runs/human-ayu/<run>/compare/<name>); KANNA: eval/kanna/<name>.json
(default: eval/kanna/<run>.json). @TAG: the files PREFIX-TAG-<opponent>.json and
PREFIX-<profile>-TAG-<opponent>.json instead (@routes: the agent played with its built-in
routes, evaluate.py --p1-assist). Opponents it lacks are left out of its means; a mean
over fewer opponents than the others' is marked (n). Round 14's seven exploiters
(x14-<character>) have a row where a card has them.
"""

import argparse
import json
import os

HERE = os.path.dirname(os.path.abspath(__file__))
TWENTY = ['kano', 'kano2', 'kano3', 'kano4', 'kano5', 'kano6', 'kano7', 'mizukab', 'mizukab2',
          'mizukab3', 'mizukab4', 'mizukab5', 'mizukab6', 'mizukab7', 'misuzu', 'misuzu2',
          'misuzu3', 'mishio', 'mishio2', 'mishio3']
REVERSAL = ['ayurev', 'mishiorev']
HELPERS = ['sayuri', 'mayu', 'nayukib', 'nanase', 'akiko', 'exnanase', 'mio', 'kaori', 'ikumi',
           'akane', 'misaki', 'nagamori', 'mai', 'shiori', 'makoto', 'minagi', 'nayuki']
ALL = TWENTY + REVERSAL + HELPERS
X14 = ['x14-' + c for c in ('exnanase', 'nanase', 'nagamori', 'mishio', 'sayuri', 'kano',
                            'mizukab')]  # round 14's exploiters (CHAR/exploiter14)
KANO = [o for o in TWENTY if o.startswith('kano')]
# Each profile's opponents: rounds 12-13's advantaged seven (the awake Nayuki is nayukib),
# and docs/training-v2.md's person set (the exploiters of the characters the user played,
# and Shiori's).
SETS = {'adv': ['mayu', 'sayuri', 'exnanase', 'nayukib', 'shiori', 'kano7', 'mishio3'],
        'person': ['exnanase', 'nanase', 'nagamori', 'mishio3', 'sayuri', 'kano7', 'mizukab7',
                   'shiori']}
PROFILES = list(SETS)


def load(path):
    try:
        with open(path) as f:
            d = json.load(f)
    except (OSError, ValueError):
        return None
    return d.get('vs') or next(iter(d.values()))


def mean(xs):
    xs = [x for x in xs if x is not None]
    return sum(xs) / len(xs) if xs else None


def get(d, *keys):
    for k in keys:
        if not isinstance(d, dict):
            return None
        d = d.get(k)
    return d


class Card:
    def __init__(self, name, prefix, kanna=None, tag=''):
        self.name, self.prefix = name, prefix
        tag = tag and tag + '-'
        self.plain = {o: load(f'{prefix}-{tag}{o}.json') for o in ALL + X14}
        self.plain = {o: r for o, r in self.plain.items() if r}
        self.the39 = {o: r for o, r in self.plain.items() if o in ALL}
        self.prof = {}
        for p in PROFILES:
            got = {}
            for o in ALL:
                r = load(f'{prefix}-{p}-{tag}{o}.json')
                if r:
                    got[o] = r
            if got:
                self.prof[p] = got
        cpu = load(f'{prefix}-{tag}cpu.json')
        self.tiers = cpu.get('by_tier') if cpu else None
        if kanna is None:
            run = os.path.basename(os.path.dirname(os.path.dirname(prefix)))
            kanna = os.path.join(HERE, 'eval', 'kanna', f"{run}{tag and '-' + tag[:-1]}.json")
        self.kanna = load(kanna)

    def group(self, opps, results=None):
        results = self.plain if results is None else results
        have = [o for o in opps if o in results]
        return (mean([results[o]['win'] for o in have]),
                mean([results[o].get('self_hp_taken') for o in have]), len(have))

    def side(self, results, *keys):
        return mean([get(r['sides'][0], *keys) for r in results.values()])


def cell(win, lost, n, full):
    if win is None:
        return '-'
    s = f'{win:.0%}' + (f' ({lost:.0%})' if lost is not None else '')
    return s + (f' [{n}]' if n != full else '')


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('cards', nargs='+', help='NAME=PREFIX[@TAG][,KANNA]')
    p.add_argument('--profile', default='person', help='the profile whose opponents the '
                   "defence rows are read against ('adv', 'person'; else the plain 39)")
    args = p.parse_args()
    cards = []
    for c in args.cards:
        name, _, rest = c.partition('=')
        prefix, _, kanna = rest.partition(',')
        prefix, _, tag = prefix.partition('@')
        cards.append(Card(name, prefix, kanna or None, tag))
    rows = []
    for label, opps in (('All 39 (own HP lost)', ALL), ('The twenty', TWENTY),
                        ('Reversal exploiters', REVERSAL), ('17 helpers', HELPERS),
                        ('Kano 1-7', KANO)):
        rows.append((label, [cell(*c.group(opps), len(opps)) for c in cards]))
    if any(o in c.plain for c in cards for o in X14):
        rows.append(("Round 14's seven exploiters", [cell(*c.group(X14), len(X14)) for c in cards]))
        rows.append(('All 46', [cell(*c.group(ALL + X14), len(ALL + X14)) for c in cards]))
    for prof in PROFILES:
        sets = [c.prof.get(prof, {}) for c in cards]
        if any(sets):
            opps = SETS[prof]
            rows.append((f'`{prof}` set ({", ".join(opps)})',
                         [cell(*c.group(opps, s), len(opps)) if s else '-'
                          for c, s in zip(cards, sets)]))
    rows.append(('Level-4 CPU: Kanna / hard / rest tiers',
                 [' / '.join(f"{get(c.tiers, t, 'win'):.0%}" for t in ('hardest', 'hard', 'rest'))
                  if c.tiers else '-' for c in cards]))
    rows.append(("Kanna's HP taken (64)",
                 [f"{c.kanna['opp_hp_taken']:.1%}" if c.kanna else '-' for c in cards]))
    lim = [('Presses a second', ('presses_per_second',), '{:.2f}'),
           ('Presses, turns while unable to move', (('busy_presses',), ('busy_turns',)), None)]
    for label, keys, fmt in lim:
        out = []
        for c in cards:
            if not c.plain:
                out.append('-')
            elif fmt:
                out.append(fmt.format(c.side(c.the39, *keys)))
            else:
                out.append(' / '.join(f'{c.side(c.the39, *k):.0%}' for k in keys))
        rows.append((label + ' (the 39)', out))
    defence = [('Its okizeme high / low / throw', [('okizeme', 'mix', 'high'),
                                                   ('okizeme', 'mix', 'low'),
                                                   ('okizeme', 'mix', 'throw')], '{:.0%}'),
               ('Its throws a minute', [('throws_per_min',)], '{:.2f}'),
               ('Its string guarded, then its hit', [('pressure', 'next', 'hit')], '{:.0%}'),
               ('Opponent moves after guarding it', [('pressure', 'escapes', 'move', 'share')], '{:.0%}'),
               ('Its guard on rising opened', [('wakeup', 'choices', 'guard', 'hit')], '{:.0%}'),
               ('HP a minute dealt / taken', [('combo_damage_per_min',), ('damage_taken_per_min',)], '{:,.0f}')]
    where = args.profile if any(args.profile in c.prof for c in cards) else None
    for label, keys, fmt in defence:
        out = []
        for c in cards:
            res = c.prof.get(where) if where else c.the39
            if res and where:
                res = {o: r for o, r in res.items() if o in SETS[where]}
            if not res:
                out.append('-')
                continue
            vals = [c.side(res, *k) for k in keys]
            out.append(' / '.join('-' if v is None else fmt.format(v) for v in vals))
        rows.append((label + (f' (`{where}`)' if where else ' (the 39)'), out))
    print('| | ' + ' | '.join(c.name for c in cards) + ' |')
    print('|---' * (len(cards) + 1) + '|')
    for label, cells in rows:
        print(f'| {label} | ' + ' | '.join(cells) + ' |')


if __name__ == '__main__':
    main()
