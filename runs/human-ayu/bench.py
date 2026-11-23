"""A benchmark suite for an agent file: measures with room to move, each with its error.

Why (the user's, 19 November: "Improving from 85 to 87 in something is likely more noisy
than improving from 10 to 50 in something else"). The league's win rate is near its
ceiling (about 90% over the eleven `exploiter18`s; one standard error of a difference
between two builds there is 1.6 points over 704 matches) and no longer tells builds
apart. What is far from its ceiling is what a person sees: whether a corner holds,
whether a combo's end lets the opponent go, what its own rising costs against an attacker
who is on it, what its raw specials pay, what it makes of a lead. This file names those
as numbers (MEASURES), each read from matches against the opponents that test it
(DRILLS), through the game's own code, with the error evaluate.py --folds gives every
number, beside the same number of the community's strongest Ayu player (people.json).

    python runs/human-ayu/bench.py jobs FILE.efzagent --tag k4 > jobs   # one command a line
    python runs/human-ayu/bench.py table k4                             # the scoreboard
    python runs/human-ayu/bench.py table round18 k4                     # two: what moved, in errors
    python runs/human-ayu/bench.py noise k4 k4-seed11                   # the errors checked
    python runs/human-ayu/bench.py record round18 RECORDINGS --name user # a play-test, the same way

A drill is whole matches, 64 a pairing, against a trained opponent (an `exploiter18`)
with one scripted habit on top of its play (advantages.py): what a strong person does
where the agent is weak, and nothing else changed, so that the measure read from it has
many events a match and one cause. `league` has no habit (the floor: wins, own HP lost);
`handicap` is the league with the agent taking twice the damage (wins near a half
there: a scale that does not run out); `mirror` is another build's file as the opponent
(the game's code on both sides: near even by construction, the most a win rate can
tell).

The scoreboard: a measure's value is the mean over its drill's opponents, its error the
opponents' errors together (independent matches). With two builds, the difference
between them in errors (z): past 3 it is real, between 2 and 3 likely, under 2
noise. `noise` takes two runs of one build with different seeds: the z of every cell
should then be noise (about one in twenty past 2), which is what says the errors can be
believed. `people`: the strongest replay player's number and all players', where the
measure can be read from a replay (no error: one count of their matches).

Results: runs/human-ayu/bench/TAG/DRILL-OPPONENT.json (evaluate.py's).
"""

import argparse
import json
import math
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
ELEVEN = ['sayuri', 'exnanase', 'mayu', 'nanase', 'kaori', 'mishio', 'ikumi', 'nayukib', 'kano',
          'mizukab', 'makoto']
# The drills' opponents: the one that is on the agent's rising most (Kano's), the near-even
# pairing (Nayuki's), the one its damage is slowest against (Ikumi's), Sayuri's, and
# Mizuka's (the end of a round against her: the user's, 18 November).
FIVE = ['kano', 'nayukib', 'ikumi', 'sayuri', 'mizukab']
EXPLOITER = 'exploiter18/model.zip'

# name: (the opponents, the habit on top of their play, what it tests)
DRILLS = {
    'league': (ELEVEN, None, 'the trained opponents as they play'),
    'handicap': (ELEVEN, 'damage=2', 'the same, the agent taking twice the damage'),
    'hold': (FIVE, 'escape=1', 'an opponent that jumps out of the corner when it is free there'),
    'ends': (FIVE, 'tech=1,techsafe=1,techhit=1',
             'one that recovers in the air out of a combo when it is safe and attacks out of it'),
    'rise': (FIVE, 'jumpin=0.9,throw=0.7',
             "one that jumps in on the agent's rising and throws"),
    'bait': (FIVE, 'bait=0.9', "one that waits out the agent's wake-up reversal and punishes it"),
    'reversal': (FIVE, 'wake=0.6,blind=0.5',
                 'one that rises with a reversal, half of them whatever the agent does'),
    'cpu': (['ayu'], 'cpu-combos=4',
            "the game's level-4 CPU with the agent's own combos (evaluate.py --p2-cpu-combos: "
            "its guard, recoil guards and counters; a hit of its is worth what the agent's is)"),
    'sparring': (FIVE, 'rg=0.3,reversal=0.8,damage=1.5,tech=1,techsafe=1,techhit=1,escape=1,'
                       'jumpin=0.5,low=0.6,throw=0.5,bait=0.5',
                 'every scripted habit at once, its hits worth half as much again: what a '
                 'strong person does where the agent is weak, in one opponent'),
    'riselow': (FIVE, 'jumpin=0.9,low=0.6,throw=0.3',
                "one that jumps in on the agent's rising, six times in ten with nothing in "
                "the air and a low as it lands"),
    'recoil': (FIVE, 'rg=0.3,reversal=0.8',
               "one that recoil-guards three guards in ten and counters with an invincible "
               "move when the agent presses on (the level-4 CPU's defence)"),
    'combos': (ELEVEN, 'file=exploiter18/combos.efzagent',
               "the trained opponents with their characters' combos: each as an agent file "
               "(league_combos.py: people's routes for its character through the game's "
               "planner, a route from the step after its hit, its model 11 steps late), so "
               "that a hit costs the agent what its own costs them"),
    'planners': (ELEVEN, 'file=exploiter18/planners.efzagent',
                 "the same with their characters' planned okizeme and pressure too "
                 "(league_combos.py files --oki --press: people's okizeme and follow-ups to a "
                 "guard for its character, the agent's own planners' settings): the areas "
                 "where the league varied a third as much as people do"),
    'press': (FIVE, 'file=exploiter18/combos.efzagent;press=1,throw=0.5',
              "the opponents with their characters' combos that press (advantages.py's "
              "press: they go in on the agent, chain their normals on its guard and stay on "
              "it) and throw: what the league's own play does a third as often as a person"),
    'objects': (['sayuri', 'kano', 'ikumi', 'nanase', 'makoto', 'mizukab'],
                'file=exploiter18/combos.efzagent;object=1,press=1,throw=0.5',
                "the same of those with a move that leaves an object out (advantages.py's "
                "object): they put one out on the agent's knockdown and from afar, and go in "
                "behind it"),
    'antiair': (FIVE, 'file=exploiter18/combos.efzagent;antiair=1',
                "the opponents with their characters' combos that anti-air (advantages.py's "
                "antiair: at each jump of the agent's at them, the move that hits a jump-in "
                "first from where it is): what a jump costs against a person"),
    'gaps': (FIVE, 'file=exploiter18/combos.efzagent;gap=0.6,mash=0.15,escape=1,rg=0.3,'
                   'reversal=0.8,tech=1,techsafe=1,techhit=1',
             "the agent's own pressure (the user's, 22 November: to handle pressure it has to "
             "know how to pressure, in the corners above all): the opponents with their "
             "characters' combos that press their fastest normal into the gaps of its "
             "pressure (advantages.py's gap: a reset, a slow move's start, a recovery; and "
             "mash, blind, now and then), jump out of a corner when they are free there, "
             "guard by recoil and rise with an invincible move: what a string with a gap and "
             "a corner that does not hold cost against a person"),
}

# (name, drill, path, better: +1 more is better or -1, what). The path is into the
# pairing's result; 'side' is the agent's own measures (sides[0]).
MEASURES = [
    ('wins', 'league', ('win',), +1, 'matches won'),
    ('own HP lost', 'league', ('self_hp_taken',), -1, 'the share of its HP lost a round'),
    ('net HP a minute', 'league', ('side', 'net_ledger', 'net'), +1, 'HP ahead a minute, all exchanges'),
    ('raw specials', 'league', ('side', 'raw', 'hp_per_min'), +1, 'HP a minute its raw risky moves are worth'),
    ('by air', 'league', ('side', 'net_ledger', 'I came by air', 'net'), +1, 'HP a minute net where it came by air'),
    ('into a strike', 'league', ('side', 'ledger', 'into', 'began', 'hp'), -1,
     'HP a minute lost starting something into a move or object already out'),
    ('lead kept', 'league', ('side', 'rounds', 'lead', 'kept'), +1, 'rounds won of those it led by 3,000 HP'),
    ('turned', 'league', ('side', 'rounds', 'behind', 'turned'), +1, 'rounds won of those it trailed by 3,000 HP'),
    ('close: seconds', 'league', ('side', 'rounds', 'close', 'seconds'), -1, 'seconds to end a round that is there to close'),
    ('close: HP lost', 'league', ('side', 'rounds', 'close', 'lost'), -1, 'HP lost while closing it'),
    ('handicap wins', 'handicap', ('win',), +1, 'matches won taking twice the damage'),
    ('handicap net', 'handicap', ('side', 'net_ledger', 'net'), +1, 'HP ahead a minute there (as dealt)'),
    ('corner: left', 'hold', ('side', 'corner', 'left'), -1, 'corner stays the opponent left on its own'),
    ('corner: seconds', 'hold', ('side', 'corner', 'seconds_median'), +1, 'a corner stay, median seconds'),
    ('corner: HP dealt', 'hold', ('side', 'corner', 'dealt'), +1, 'HP dealt a corner stay'),
    ('pressure net', 'hold', ('side', 'net_ledger', 'my pressure', 'net'), +1, 'HP a minute net out of its pressure'),
    ('ends: let go', 'ends', ('side', 'combo_ends', 'big', 'recovery'), -1, 'big combos that end in the opponent recovering'),
    ('ends: caught', 'ends', ('side', 'combo_ends', 'after_recovery', 'net'), +1, 'recoveries caught less hit back out of'),
    ('ends: combo HP', 'ends', ('side', 'combo_damage'), +1, 'HP a combo'),
    ('ends: wins', 'ends', ('win',), +1, 'matches won there'),
    ('rising net', 'rise', ('side', 'net_ledger', 'its okizeme', 'net'), +1, 'HP a minute net on its own rising'),
    ('rising: jump-in hits', 'rise', ('side', 'jumpins', 'front', 'hit'), -1, 'jump-ins on it that hit'),
    ('rising: own HP lost', 'rise', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('bait: raw specials', 'bait', ('side', 'raw', 'hp_per_min'), +1, 'HP a minute its raw moves are worth against a punisher'),
    ('bait: punished', 'bait', ('side', 'raw', 'punished'), -1, 'its misses punished'),
    ('cpu: wins', 'cpu', ('win',), +1, "matches won against the level-4 CPU with its combos"),
    ('cpu: hit after RG', 'cpu', ('side', 'pressure', 'after_rg', 'fought_back'), -1,
     'its recoil-guarded moves after which it is the one hit, there'),
    ('cpu: own HP lost', 'cpu', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('sparring: wins', 'sparring', ('win',), +1, 'matches won against every habit at once'),
    ('sparring: net', 'sparring', ('side', 'net_ledger', 'net'), +1, 'HP ahead a minute there (as dealt)'),
    ('sparring: own HP lost', 'sparring', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('rising low: net', 'riselow', ('side', 'net_ledger', 'its okizeme', 'net'), +1,
     'HP a minute net on its own rising against empty jumps into lows'),
    ('rising low: jump-ins hit', 'riselow', ('script', 'jumpin_hit', 'jumpins'), -1,
     "the opponents' scripted jump-ins on its rising that hit (six in ten empty, into a low; their own count)"),
    ('rising low: jump-ins guarded', 'riselow', ('script', 'jumpin_guarded', 'jumpins'), +1,
     'and those it guarded'),
    ('rising low: lows hit', 'riselow', ('side', 'wakeup', 'mixups', 'ground low', 'hit'), -1,
     'lows on its rising that hit (an empty jump\'s low is one from the ground: it starts after the landing)'),
    ('rising low: a low\'s worth', 'riselow', ('side', 'wakeup', 'mixups', 'ground low', 'value'), -1,
     'HP a low on its rising is worth to the attacker'),
    ('rising low: highs hit', 'riselow', ('side', 'wakeup', 'mixups', 'jump high', 'hit'), -1,
     'jump attacks on its rising that hit'),
    ('rising low: wins', 'riselow', ('win',), +1, 'matches won there'),
    ('recoil: hit after', 'recoil', ('side', 'pressure', 'after_rg', 'fought_back'), -1,
     'its recoil-guarded moves after which it is the one hit'),
    ('recoil: lands after', 'recoil', ('side', 'pressure', 'after_rg', 'hit'), +1,
     'its recoil-guarded moves after which its next attack hits'),
    ('recoil: reversals hit', 'recoil', ('script', 'reversal_hit', 'reversals_started'), -1,
     "the opponents' scripted reversals after a recoil guard that hit it (their own count)"),
    ('recoil: pressure net', 'recoil', ('side', 'net_ledger', 'my pressure', 'net'), +1,
     'HP a minute net out of its pressure there'),
    ('recoil: wins', 'recoil', ('win',), +1, 'matches won there'),
    ('combos: wins', 'combos', ('win',), +1, "matches won against the opponents with their characters' combos"),
    ('combos: own HP lost', 'combos', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('combos: net', 'combos', ('side', 'net_ledger', 'net'), +1, 'HP ahead a minute there'),
    ('combos: their combo HP', 'combos', ('other', 'combo_damage'), -1, "HP a combo of the opponents'"),
    ('combos: its combo HP', 'combos', ('side', 'combo_damage'), +1, 'HP a combo of its own there'),
    ('press: wins', 'press', ('win',), +1, 'matches won against the opponents that press'),
    ('press: own HP lost', 'press', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('press: under pressure', 'press', ('side', 'net_ledger', 'its pressure', 'net'), +1,
     'HP a minute net under their pressure there'),
    ('objects: wins', 'objects', ('win',), +1, 'matches won against the opponents that put objects out and press'),
    ('objects: own HP lost', 'objects', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('antiair: wins', 'antiair', ('win',), +1, 'matches won against the opponents that anti-air'),
    ('antiair: own HP lost', 'antiair', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('antiair: by air', 'antiair', ('side', 'net_ledger', 'I came by air', 'net'), +1,
     'HP a minute net where it came by air there'),
    ('gaps: wins', 'gaps', ('win',), +1, 'matches won against the opponents that press back in a gap and leave a corner'),
    ('gaps: own HP lost', 'gaps', ('self_hp_taken',), -1, 'the share of its HP lost a round there'),
    ('gaps: its pressure', 'gaps', ('side', 'net_ledger', 'my pressure', 'net'), +1,
     'HP a minute net out of its own pressure there'),
    ('gaps: strings', 'gaps', ('side', 'pressure', 'strings_per_min'), +1, 'its strings a minute there'),
    ('gaps: opened', 'gaps', ('side', 'pressure', 'next', 'hit'), +1,
     'after a move of its that was guarded, the share in which the next thing is its hit'),
    ('gaps: got away', 'gaps', ('side', 'pressure', 'escapes', 'move', 'escaped'), -1,
     'moves pressed against its pressure that got away'),
    ('gaps: corner left', 'gaps', ('side', 'corner', 'left'), -1, 'corner stays the opponent left on its own there'),
    ('gaps: corner HP', 'gaps', ('side', 'corner', 'dealt'), +1, 'HP dealt a corner stay there'),
    ('gaps: corner share', 'gaps', ('side', 'corner', 'share'), +1,
     'the share of the match it has the opponent in a corner there'),
    ('gaps: corner in a guard', 'gaps', ('side', 'corner', 'hold', 'guard'), +1,
     'the share of a corner stay the opponent spends guarding there: pressure after the combo'),
    ('gaps: corner air moves', 'gaps', ('side', 'corner', 'hold', 'air_moves'), -1,
     'the share of its moves in a corner stay made in the air there'),
    ('gaps: corner in a hit', 'gaps', ('side', 'corner', 'hold', 'hit'), +1,
     'the share of a corner stay the opponent spends in a hit there'),
    ('gaps: jumps out', 'gaps', ('side', 'corner', 'hold', 'jump', 'out'), -1,
     "the opponent's jumps in a corner that took it out there"),
    ('gaps: jumps caught', 'gaps', ('side', 'corner', 'hold', 'jump', 'caught'), +1,
     "the opponent's jumps in a corner caught in the air there"),
    ('okizeme net', 'reversal', ('side', 'net_ledger', 'my okizeme', 'net'), +1, 'HP a minute net on its okizeme against reversals'),
    ('punishes', 'reversal', ('side', 'faced_raw', 'punished'), +1, "the opponent's missed risky moves it punished"),
]


def get(d, path):
    for k in path:
        if not isinstance(d, dict) or d.get(k) is None:
            return None
        d = d[k]
    return d if isinstance(d, (int, float)) and not isinstance(d, bool) else None


def cell(tag, drill, opponent, path, root=None):
    """(value, error) of one pairing, or None: its result's number and evaluate.py's `se`."""
    f = os.path.join(root or os.path.join(HERE, 'bench'), tag, f'{drill}-{opponent}.json')
    if not os.path.exists(f):
        return None
    if path[0] == 'script':  # the scripted opponent's own counts: path[1] of its path[2]
        a = _whole(f).get('p2_advantage') or {}
        n, of = a.get(path[1]), a.get(path[2])
        if not of or n is None:
            return None
        p = n / of
        return p, math.sqrt(p * (1 - p) / of)
    r = _load(f)
    where = lambda t: t['sides'][0] if path[0] == 'side' else t['sides'][1] if path[0] == 'other' else t
    rest = path[1:] if path[0] in ('side', 'other') else path
    v = get(where(r), rest)
    if v is None:
        return None
    se = get(where(r['se']), rest) if 'se' in r else None
    return float(v), se


_CACHE = {}


def _whole(f):
    if f not in _CACHE:
        _CACHE[f] = json.load(open(f))
    return _CACHE[f]


def _load(f):
    return _whole(f)['vs']


def opponents(drill, mirrors=()):
    return list(mirrors) if drill == 'mirror' else DRILLS[drill][0]


def pooled(tag, drill, path, root=None, only=None):
    """A measure over its drill's opponents: (mean, error, pairings read), or None. The
    error is the pairings' together; a pairing without one counts as none."""
    got = [c for o in (only or opponents(drill)) for c in [cell(tag, drill, o, path, root)] if c]
    if not got:
        return None
    n = len(got)
    v = sum(c[0] for c in got) / n
    se = math.sqrt(sum((c[1] or 0.0) ** 2 for c in got)) / n if all(c[1] is not None for c in got) else None
    return v, se, n


def people(path, file=None):
    """The strongest replay player's number and all players' (people.json: evaluate.py's
    measures of the community's Ayu players; `best`, the one with the most matches won of
    those with 100 or more, people-ledger.json), or (None, None)."""
    if path[0] != 'side':
        return None, None
    try:
        d = json.load(open(file or os.path.join(HERE, 'people.json')))
        ledger = json.load(open(os.path.join(HERE, 'people-ledger.json')))
    except FileNotFoundError:
        return None, None
    best = max((k for k, v in d['by_player'].items()
                if v['matches'] >= 100 and ledger.get('player/' + k, {}).get('ayu_won') is not None),
               key=lambda k: ledger['player/' + k]['ayu_won'], default=None)
    return (get(d['by_player'][best], path[1:]) if best else None), get(d['all'], path[1:])


def fmt(v, se=None, pct=False):
    if v is None:
        return '-'
    if pct:
        return f'{100 * v:.1f}' + (f' ±{100 * se:.1f}' if se is not None else '')
    digits = 0 if abs(v) >= 100 else 1 if abs(v) >= 10 else 2
    return f'{v:.{digits}f}' + (f' ±{se:.{digits}f}' if se is not None else '')


def is_share(path):
    return path[0] == 'script' or path[-1] in ('win', 'self_hp_taken', 'kept', 'turned', 'left', 'recovery', 'net', 'hit', 'fought_back',
                        'punished') and 'net_ledger' not in path and path[-2:] != ('raw', 'net') \
        or path[-2:] in (('jump', 'out'), ('jump', 'caught'), ('hold', 'guard'), ('hold', 'air_moves'), ('corner', 'share'))


def z(a, b):
    """The difference b - a in errors, or None."""
    if a is None or b is None or a[1] is None or b[1] is None:
        return None
    e = math.hypot(a[1], b[1])
    return (b[0] - a[0]) / e if e > 0 else None


def verdict(x):
    return '' if x is None else 'real' if abs(x) >= 3 else 'likely' if abs(x) >= 2 else 'noise'


def jobs(args):
    """One evaluate.py command a line: the suite's pairings a result is missing for."""
    snap = args.snap or os.path.dirname(os.path.dirname(HERE))
    ev = os.path.join(snap, 'runs', 'human-ayu', 'evaluate.py')
    out = os.path.join(args.root or os.path.join(HERE, 'bench'), args.tag)
    lib = f'EFZ_ENV_LIBRARY={snap}/lib/libefz_env.so ' if args.snap else ''
    for drill in args.drills or list(DRILLS) + (['mirror'] if args.mirror else []):
        for o in ([os.path.splitext(os.path.basename(m))[0] for m in args.mirror]
                  if drill == 'mirror' else DRILLS[drill][0]):
            f = os.path.join(out, f'{drill}-{o}.json')
            if os.path.exists(f):
                continue
            if drill == 'mirror':
                p2 = next(m for m in args.mirror if os.path.splitext(os.path.basename(m))[0] == o)
                rest = f'--p2 {p2} --chars ayu ayu'
            else:
                adv = DRILLS[drill][1]
                if adv and adv.startswith('cpu-combos='):  # the CPU, the file's own combos
                    rest = f'--p2 {args.file} --p2-cpu-combos {adv.split("=")[1]} --chars ayu {o}'
                elif adv and adv.startswith('file='):  # the opponent as an agent file of its own
                    name, _, habits = adv.partition('=')[2].partition(';')  # (;its habits on top)
                    rest = (f'--p2 {HERE}/{o}/{name} --chars ayu {o}' +
                            (f' --p2-advantage {habits}' if habits else ''))
                else:
                    rest = (f'--p2 {HERE}/{o}/{EXPLOITER} --chars ayu {o}' +
                            (f' --p2-advantage {adv}' if adv else '') +
                            (f' --p2-delay {args.p2_delay}' if args.p2_delay is not None else ''))
            print(f'mkdir -p {out} && {lib}OMP_NUM_THREADS=1 nice -n {args.nice} python {ev} '
                  f'--p1 {args.file} --p1-native {rest} --matches {args.matches} --seed {args.seed} '
                  f'--folds {args.folds} --json {f} > {f[:-5]}.log 2>&1 && rm -f {f[:-5]}.log '
                  f'&& echo "finished {f}" || echo "FAILED {f}"')


def table(args):
    tags = args.tags
    two = len(tags) == 2
    head = f"{'measure':22s} {'drill':9s} " + ' '.join(f'{t:>16s}' for t in tags)
    print(head + (f"{'z':>7s} {'':6s}" if two else '') + f"{'best player':>13s} {'all':>8s}   what")
    for name, drill, path, better, what in MEASURES:
        got = [pooled(t, drill, path, args.root) for t in tags]
        if not any(got):
            continue
        pct = is_share(path)
        row = f'{name:22s} {drill:9s} ' + ' '.join(
            f'{fmt(g[0], g[1], pct) if g else "-":>16s}' for g in got)
        if two:
            x = z(got[0], got[1])
            good = '' if x is None else ('+' if x * better > 0 else '-')
            row += f"{'' if x is None else f'{x:+.1f}':>7s} {verdict(x) + good:6s}"
        best, everyone = people(path, args.people)
        scale = 100 if pct else 1
        row += f"{'-' if best is None else fmt(best * scale):>13s} {'-' if everyone is None else fmt(everyone * scale):>8s}"
        print(row + f"   {'more' if better > 0 else 'less'}: {what}")
    if args.person:  # the same numbers out of a person's matches against each build
        print(f"\nagainst {args.person} (a play-test's matches; `record`):")
        seen = set()
        for name, drill, path, better, what in [('wins', '', ('win',), 1, 'matches won')] + MEASURES:
            if path in seen or path == ('self_hp_taken',):
                continue
            seen.add(path)
            got = [cell(t, 'person', args.person, path, args.root) for t in tags]
            if not any(got):
                continue
            pct = is_share(path)
            row = f'{name.split(": ")[-1] if drill in ("handicap",) else name:22s} {"":9s} ' + ' '.join(
                f'{fmt(g[0], g[1], pct) if g else "-":>16s}' for g in got)
            if two:
                x = z(got[0], got[1])
                good = '' if x is None else ('+' if x * better > 0 else '-')
                row += f"{'' if x is None else f'{x:+.1f}':>7s} {verdict(x) + good:6s}"
            print(row + f"   {'more' if better > 0 else 'less'}: {what}")
    if args.mirror:
        for t in tags:
            for m in args.mirror:
                c = cell(t, 'mirror', m, ('win',), args.root)
                if c:
                    print(f'{t} against {m}: {fmt(c[0], c[1], True)}% of matches won')


def cells(a, b, root=None):
    """Every (measure, opponent) both runs have: (name, opponent, a's cell, b's, z)."""
    out = []
    for name, drill, path, better, _ in MEASURES:
        for o in DRILLS[drill][0]:
            ca, cb = cell(a, drill, o, path, root), cell(b, drill, o, path, root)
            if ca and cb:
                out.append((name, o, ca, cb, z(ca, cb)))
    return out


def noise(args):
    """Two runs of one build: are the differences as large as the errors say?"""
    zs = [c[4] for c in cells(args.a, args.b, args.root) if c[4] is not None]
    if not zs:
        sys.exit('no cells in common')
    n = len(zs)
    rms = math.sqrt(sum(x * x for x in zs) / n)
    print(f'{n} cells (a measure against one opponent) in both runs of the same build')
    print(f'  the differences in errors: root mean square {rms:.2f} (1.00 if the errors are right), '
          f'{sum(abs(x) > 2 for x in zs) / n:.0%} past 2 (5% expected), '
          f'{sum(abs(x) > 3 for x in zs) / n:.1%} past 3 (0.3%)')
    by = {}
    for name, o, ca, cb, x in cells(args.a, args.b, args.root):
        if x is not None:
            by.setdefault(name, []).append(x)
    for name, xs in by.items():
        print(f'  {name:22s} {len(xs):2d} cells, root mean square {math.sqrt(sum(x * x for x in xs) / len(xs)):.2f}')


def record(args):
    """A person's matches against a build (from_record.py's or play.py's recordings: a
    folder of NAME.npz and NAME.json) as a pairing's result, bench/TAG/person-NAME.json:
    the agent's side by evaluate.py's measures, each number's error by the jackknife over
    the matches (in at most --folds groups). A play-test is then read on the scoreboard
    as a drill is, with what its few matches can and cannot tell."""
    import numpy as np
    import evaluate as ev
    files = sorted(f for f in os.listdir(args.folder) if f.endswith('.json'))
    each, won = [], []
    for f in files:
        j = json.load(open(os.path.join(args.folder, f)))
        with np.load(os.path.join(args.folder, f[:-5] + '.npz')) as zf:
            a = j['agent']
            e = ev.Events('ayu')
            e.add_match(zf['obs'][:, a][:, ev.COLUMNS], zf['controls'][:, a])
        each.append(e)
        won.append(j['winner'] == a)
    n = len(each)
    if n < 2:
        sys.exit(f'{args.folder}: {n} matches')
    won = np.array(won, float)

    def count(which):
        e = ev.Events('ayu')
        for i in which:
            e.merge(each[i])
        return dict(win=float(won[list(which)].mean()), sides=[e.report()])

    K = min(args.folds, n)
    full = count(range(n))
    se = ev.spread(full, [count([i for i in range(n) if i % K != k]) for k in range(K)])
    out = os.path.join(args.root or os.path.join(HERE, 'bench'), args.tag)
    os.makedirs(out, exist_ok=True)
    with open(os.path.join(out, f'person-{args.name}.json'), 'w') as f:
        json.dump(dict(vs=dict(full, matches=n, se=dict(folds=K, **se))), f, indent=1)
    print(f"{args.tag} against {args.name}: {n} matches, {fmt(full['win'], se.get('win'), True)}% won")


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = p.add_subparsers(dest='cmd', required=True)
    j = sub.add_parser('jobs', help="the suite's evaluate.py commands for an agent file")
    j.add_argument('file')
    j.add_argument('--tag', required=True, help="the results' folder under bench/")
    j.add_argument('--drills', nargs='+', choices=list(DRILLS) + ['mirror'])
    j.add_argument('--mirror', nargs='*', default=[], metavar='FILE.efzagent',
                   help="other builds' files, as opponents (the game's code plays both)")
    j.add_argument('--matches', type=int, default=64)
    j.add_argument('--seed', type=int, default=7)
    j.add_argument('--folds', type=int, default=16)
    j.add_argument('--nice', type=int, default=5)
    j.add_argument('--p2-delay', type=int, metavar='STEPS',
                   help="the opponents see the game this many steps late instead of their own 14 "
                        "(evaluate.py --p2-delay): for a build that reacts faster than they were "
                        "trained to, so that it is not measured by out-reacting them; not the cpu "
                        "drill's or a mirror's")
    j.add_argument('--snap', help="a frozen copy of the code to run from (its runs/human-ayu "
                                  "and lib/libefz_env.so), while the tree changes")
    t = sub.add_parser('table', help='the scoreboard of one or more builds (two: with z)')
    t.add_argument('tags', nargs='+')
    t.add_argument('--mirror', nargs='*', default=[])
    t.add_argument('--people', help='people.json (default: the one here)')
    t.add_argument('--person', metavar='NAME', help="also a play-test's rows (`record`'s person-NAME)")
    r = sub.add_parser('record', help="a person's recorded matches against a build, as a result")
    r.add_argument('tag')
    r.add_argument('folder', help="from_record.py's output: NAME.npz and NAME.json a match")
    r.add_argument('--name', default='person')
    r.add_argument('--folds', type=int, default=16)
    c = sub.add_parser('noise', help="two runs of one build with different seeds: the errors' check")
    c.add_argument('a')
    c.add_argument('b')
    for s in (j, t, c, r):
        s.add_argument('--root', help='where the results are (default: bench/ here)')
    args = p.parse_args()
    dict(jobs=jobs, table=table, noise=noise, record=record)[args.cmd](args)


if __name__ == '__main__':
    main()
