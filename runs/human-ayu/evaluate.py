"""Matches between agents, or an agent and the game's CPU, played to the end, with how
each side played.

    python runs/human-ayu/evaluate.py --p1 runs/human-ayu/bc.zip --p2 cpu --level 4
    python runs/human-ayu/evaluate.py --p1 runs/human-ayu/model.zip --p2 runs/curriculum/model.zip --chars ayu ayu

A model is an SB3 model.zip with its config.json beside it (frame_skip, history): the
environment steps every frame and each model decides every frame_skip of them, holding
its choice in between, with the input history it was trained with. --chars: P1's and
P2's characters ('random': drawn per match from the 23). Prints and returns (as JSON
with --json) P1's wins, losses and matches cut short at --minutes, and per side how it
played (Events): presses per second (and per frame, by button), and per minute its
jumps, guards, recoil guards (RG: a guard within 10 frames of pressing back, the only
guard in the air against what can't be guarded there, anti-airs among them) and hits
taken, on the ground and in the air, and how often it recoil-guards, recoil-counters,
punishes after an RG (with a long or RF move or not) and guesses 623A/B right (Events
has the definitions). People's Ayu by the same measure: people.py over the dataset.
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))

import numpy as np

from efz_env import ActionTable, EfzVecEnv
from efz_env.agent import Agent
from efz_env.history import input_features

TABLE = ActionTable()
# The observation's columns events are read from: self_action, self_hitstun,
# self_airborne, opp_action, opp_hitstun, opp_own_action, self_combo_hits (the combo
# one is doing: the attacker's counter, / 30) and self_combo_damage (/ 9999).
COLUMNS = [18, 20, 39, 50, 52, 67, 30, 38, 23, 35,  # + self_hitstop, self_own_action
           9, 10, 11,  # + self_gauge (/ 3000), self_rf_gauge (/ 1000), self_rf_blue
           31]  # + self_proration (/ 10000)
INSTANT_CHARGE = [0xa7, 0xab]  # 22C on the ground and in the air: cancels a move that hit


def resources(power, rf, blue):
    """A resource group: the RF gauge as the HUD draws it (red under 500: no Instant
    Charge; cyan 500-999: 22C cancels; blue, full: it also gives back proration) and the
    bars of power, 'blue2' etc."""
    state = 'blue' if blue else 'cyan' if rf >= 500 else 'red'
    return f'{state}{min(3, int(power // 1000))}'


GROUPS = [f'{s}{b}' for s in ('red', 'cyan', 'blue') for b in range(4)]
GUARD_GROUND, GUARD_AIR = list(range(0x96, 0x9c)), [0x9c]
RG_GROUND, RG_AIR = [0xa8, 0xa9], [0xaa]
RG = RG_GROUND + RG_AIR
FIRST_OWN = 0xc8  # kFirstCharacterAction: the character's own moves from here
# Per character: its moves that take a long input or the RF gauge (C specials, supers),
# and the moves whose choice is a guess (Ayu's 623A and 623B).
MOVES = {
    'ayu': dict(long=[0xfb, 0x102, 0x106, 0x10b] + list(range(0x12c, 0x135)) +
                list(range(0x13b, 0x13e)),
                special=list(range(0xfa, 0x13e)),  # specials and supers
                guess={'623A': [0xfa], '623B': [0xfc]}),
}
RC_WINDOW = 90      # steps after the opponent's RG in which its counterattack is looked for
PUNISH_WINDOW = 40  # steps after one's own RG in which a move of one's own is looked for
HIT_WINDOW = 40     # steps after a move starts in which it can hit


def _prev(x, fill):
    return np.concatenate([[fill], x[:-1]])


class Events:
    """How a player played, counted over whole matches (Ayu's moves for the counts of
    moves): per minute, its presses, jumps, guards, recoil guards (RG: a guard within 10
    frames of pressing back; in the air the only guard against what can't be guarded
    there, anti-airs among them) and hits taken; and how often

    rg_ground, rg_air: an attack met there was recoil-guarded (of RG, guard and hit);
    rc: after the opponent recoil-guarded one's attack, its counterattack was
        recoil-guarded back (the recoil counter; of RG, guard and hit);
    rg_move, rg_punish: after one's RG, a move of one's own started within the window,
        and hit; rg_long: a long or RF one (C specials, supers) started; rg_long_hit:
        of those, the share that hit;
    guess_<move>_counter: of the times it did the move (623A, 623B), the share that hit
        the opponent in a move of its own (the counter hit a right guess gets);
    combos (one's own, from the combo counter): per minute, their hits and damage on
        average (in HP, 9999 a bar), at the 90th percentile and the most, the share of 3
        hits or more, the damage a minute;
        combo_special, combo_ic: the share of combos of 2 hits or more in which a
        special or super, and an Instant Charge (22C), came out; ic_per_min;
        combo_proration_left: the attacker's proration at the end of its combos of 3
        hits or more (/ 10000; each hit cuts it, and with it the hits' damage and the
        untech time they give: the in-air bar, which costs nothing, so a combo ending
        with much of it left could have gone on: the user's);
        combo_by_resources: per resource group at the combo's start (resources(): the
        RF gauge red, cyan or blue, and the bars of power), the combos' count, damage on
        average, at the 90th percentile and the most;
    busy_presses, busy_turns: the share of its presses, and of its changes of direction,
        made while it couldn't move (in a move of its own, or in hitstop): what a cancel
        is made of, a motion buffered for the moment the move connects.
    """

    def __init__(self, char='ayu'):
        self.moves = MOVES.get(char, dict(long=[], special=[], guess={}))
        keys = ['frames', 'jumps', 'guard_ground', 'guard_air', 'rg_ground', 'rg_air',
                'hit_ground', 'hit_air', 'rc', 'rc_guard', 'rc_hit', 'rg', 'rg_move',
                'rg_punish', 'rg_long', 'rg_long_hit', 'ic', 'combos', 'combo_hits',
                'combo_damage', 'combos3', 'combos2', 'combo_special', 'combo_ic',
                'presses_all', 'presses_busy', 'turns_all', 'turns_busy']
        for g in self.moves['guess']:
            keys += [f'guess_{g}', f'guess_{g}_counter']
        self.n = dict.fromkeys(keys, 0)
        self.n['presses'] = np.zeros(4)
        self.n['combo_list'] = []  # each combo's (hits, damage, resource group)
        self.n['proration_left'] = []  # at the end of each of 3 hits or more

    def add_match(self, cols, controls):
        """One player's match: cols (T, len(COLUMNS)), the observation's COLUMNS before
        each step, and controls (T,), its input on each step."""
        n = self.n
        cols = np.asarray(cols, np.float32)
        controls = np.asarray(controls, np.uint8)
        T = len(cols)
        if T < 2:
            return
        n['frames'] += T
        prev_c = _prev(controls, 0).astype(np.uint8)
        n['presses'] += input_features(controls, prev_c)[:, 2:].sum(0)
        a = np.round(cols[:, 0]).astype(int)
        oa = np.round(cols[:, 3]).astype(int)
        enter, oenter = a != _prev(a, -1), oa != _prev(oa, -1)
        air = cols[:, 2] > 0
        hit = (cols[:, 1] > 0) & ~_prev(cols[:, 1] > 0, False)
        ohit = (cols[:, 4] > 0) & ~_prev(cols[:, 4] > 0, False)
        oown = cols[:, 5] > 0
        n['jumps'] += int((air & ~_prev(air, False)).sum())
        n['hit_ground'] += int((hit & ~air).sum())
        n['hit_air'] += int((hit & air).sum())
        for k, acts in (('guard_ground', GUARD_GROUND), ('guard_air', GUARD_AIR),
                        ('rg_ground', RG_GROUND), ('rg_air', RG_AIR)):
            n[k] += int((enter & np.isin(a, acts)).sum())
        my_rg = enter & np.isin(a, RG)
        my_guard = enter & np.isin(a, GUARD_GROUND + GUARD_AIR)
        own = enter & (a >= FIRST_OWN)
        # The recoil counter: the opponent's RG, then what met its counterattack first.
        for t in np.flatnonzero(oenter & np.isin(oa, RG)):
            w = slice(t + 1, min(T, t + 1 + RC_WINDOW))
            first = {}
            for k, x in (('rc', my_rg), ('rc_guard', my_guard), ('rc_hit', hit)):
                at = np.flatnonzero(x[w])
                if len(at):
                    first[k] = at[0]
            if first:
                n[min(first, key=first.get)] += 1
        # After one's own RG: a move of one's own, a long one, and whether they hit.
        for t in np.flatnonzero(my_rg):
            n['rg'] += 1
            starts = np.flatnonzero(own[t + 1:min(T, t + 1 + PUNISH_WINDOW)])
            if not len(starts):
                continue
            s0 = t + 1 + starts[0]
            landed = bool(ohit[s0:min(T, s0 + HIT_WINDOW)].any())
            n['rg_move'] += 1
            n['rg_punish'] += int(landed)
            if a[s0] in self.moves['long']:
                n['rg_long'] += 1
                n['rg_long_hit'] += int(landed)
        # Inputs while it can't move.
        if cols.shape[1] > 9:
            busy = (cols[:, 8] > 0) | (cols[:, 9] > 0)
            f = input_features(controls, prev_c)
            pressed = f[:, 2:].sum(1) > 0
            d = np.round(f[:, 0]).astype(int) * 3 + np.round(f[:, 1]).astype(int)
            turned = d != _prev(d, 0)
            n['presses_all'] += int(pressed.sum())
            n['presses_busy'] += int((pressed & busy).sum())
            n['turns_all'] += int(turned.sum())
            n['turns_busy'] += int((turned & busy).sum())
        # Combos: runs of the combo counter, with what came out during them.
        n['ic'] += int((enter & np.isin(a, INSTANT_CHARGE)).sum())
        if cols.shape[1] > 7:
            hits = np.round(cols[:, 6] * 30).astype(int)
            dmg = cols[:, 7] * 9999
            on = hits > 0
            starts = np.flatnonzero(on & ~_prev(on, False))
            ends = np.flatnonzero(~on & _prev(on, False))
            for b in starts:
                later = ends[ends > b]
                e = later[0] if len(later) else T
                h, d = int(hits[b:e].max()), float(dmg[b:e].max())
                n['combos'] += 1
                if cols.shape[1] > 13 and h >= 3:
                    n['proration_left'].append(float(cols[e - 1, 13]))
                if cols.shape[1] > 12:
                    g = resources(cols[b, 10] * 3000, cols[b, 11] * 1000, cols[b, 12] > 0)
                else:
                    g = None
                n['combo_list'].append((h, d, g))
                n['combo_hits'] += h
                n['combo_damage'] += d
                n['combos3'] += int(h >= 3)
                if h >= 2:
                    n['combos2'] += 1
                    seg = enter[b:e]
                    n['combo_special'] += int((seg & np.isin(a[b:e], self.moves['special'])).any())
                    n['combo_ic'] += int((seg & np.isin(a[b:e], INSTANT_CHARGE)).any())
        # The guesses: a counter hit is a hit on an opponent in a move of its own.
        for g, acts in self.moves['guess'].items():
            for t in np.flatnonzero(enter & np.isin(a, acts)):
                n[f'guess_{g}'] += 1
                hits = np.flatnonzero(ohit[t:min(T, t + HIT_WINDOW)])
                if len(hits) and oown[max(0, t + hits[0] - 1)]:
                    n[f'guess_{g}_counter'] += 1

    def merge(self, other):
        for k, v in other.n.items():
            self.n[k] = self.n[k] + v
        return self

    def report(self):
        n = self.n
        frames = max(1, n['frames'])
        per_min = 64 * 60 / frames

        def share(a, b):
            return round(a / b, 3) if b else None
        out = dict(presses={b: round(float(n['presses'][i] / frames), 4)
                            for i, b in enumerate('ABCD')},
                   presses_per_second=round(float(n['presses'].sum() / frames * 64), 2))
        for k in ('jumps', 'guard_ground', 'guard_air', 'rg_ground', 'rg_air', 'hit_ground',
                  'hit_air'):
            out[k + '_per_min'] = round(n[k] * per_min, 2)
        for where in ('ground', 'air'):
            out['rg_' + where] = share(n['rg_' + where], n['rg_' + where] +
                                       n['guard_' + where] + n['hit_' + where])
        chances = n['rc'] + n['rc_guard'] + n['rc_hit']
        out['rc'] = share(n['rc'], chances)
        out['rc_chances_per_min'] = round(chances * per_min, 2)
        out['rg_move'] = share(n['rg_move'], n['rg'])
        out['rg_punish'] = share(n['rg_punish'], n['rg'])
        out['rg_long'] = share(n['rg_long'], n['rg'])
        out['rg_long_hit'] = share(n['rg_long_hit'], n['rg_long'])
        for g in self.moves['guess']:
            out[f'guess_{g}_per_min'] = round(n[f'guess_{g}'] * per_min, 2)
            out[f'guess_{g}_counter'] = share(n[f'guess_{g}_counter'], n[f'guess_{g}'])
        c = n['combos']
        out['combos_per_min'] = round(c * per_min, 2)
        out['combo_hits'] = round(n['combo_hits'] / c, 2) if c else None
        out['combo_damage'] = round(n['combo_damage'] / c) if c else None
        if c:
            hits = np.array([x[0] for x in n['combo_list']], float)
            dmg = np.array([x[1] for x in n['combo_list']], float)
            groups = np.array([x[2] or '' for x in n['combo_list']])
            out['combo_by_resources'] = {
                g: dict(n=int((groups == g).sum()), damage=round(float(dmg[groups == g].mean())),
                        p90=round(float(np.percentile(dmg[groups == g], 90))),
                        most=round(float(dmg[groups == g].max())))
                for g in GROUPS if (groups == g).any()}
            out['combo_damage_p90'] = round(float(np.percentile(dmg, 90)))
            out['combo_damage_max'] = round(float(dmg.max()))
            out['combo_hits_p90'] = round(float(np.percentile(hits, 90)), 1)
            out['combo_hits_max'] = int(hits.max())
        left = n['proration_left']
        out['combo_proration_left'] = round(float(np.mean(left)), 3) if left else None
        out['combo_3plus'] = share(n['combos3'], c)
        out['combo_damage_per_min'] = round(n['combo_damage'] * per_min)
        out['combo_special'] = share(n['combo_special'], n['combos2'])
        out['combo_ic'] = share(n['combo_ic'], n['combos2'])
        out['ic_per_min'] = round(n['ic'] * per_min, 2)
        out['busy_presses'] = share(n['presses_busy'], n['presses_all'])
        out['busy_turns'] = share(n['turns_busy'], n['turns_all'])
        return out


def play(args, p1, p2, matches, level=4, seed=7):
    env = EfzVecEnv(args.data, matches, frame_skip=1, max_frames=int(args.minutes * 3840),
                    cpu_level=level, autoreset='disabled', seed=seed,
                    reward_round=0.0, reward_match=1.0)
    chars = [None if c == 'random' else c for c in args.chars]
    env.set_matches(chars=tuple(chars), cpu=(False, p2 == 'cpu'))
    agents = [p1] + ([] if p2 == 'cpu' else [p2])
    for side, a in enumerate(agents):
        a.batch(matches)
        if hasattr(a, 'attach'):  # the lookahead red team (redteam.py) saves the games
            a.attach(env, side)
    obs = env.reset()
    done = np.zeros(matches, bool)
    result = np.zeros(matches, int)  # 1 P1 won, -1 lost, 0 cut short
    seen = [[[] for _ in range(matches)] for _ in range(2)]  # per side: (cols, input)
    step = 0
    chars_played = np.zeros((matches, 2), int)
    while not done.all():
        controls = np.zeros((matches, 2), np.uint8)
        for side, a in enumerate(agents):
            controls[:, side] = a.controls(obs[:, side], step)
        view = obs[:, :, COLUMNS].copy()
        obs, _, term, trunc, info = env.step(controls)
        for side, a in enumerate(agents):
            a.observe(info['input'][:, side])
        step += 1
        live = ~done
        for s in range(2):
            for i in np.flatnonzero(live):
                seen[s][i].append((view[i, s], info['input'][i, s]))
        ended = (term | trunc) & live
        for i in np.flatnonzero(ended):
            w = int(info['winner'][i])
            result[i] = 1 if w == 0 else -1 if w == 1 else 0
            chars_played[i] = info['chars'][i]
        done |= term | trunc
    env.close()
    events = []
    for s in range(2):
        e = Events(args.chars[s])
        for match in seen[s]:
            e.add_match(np.array([c for c, _ in match]), np.array([u for _, u in match]))
        events.append(e)
    return dict(win=float((result == 1).mean()), loss=float((result == -1).mean()),
                cut=float((result == 0).mean()), matches=matches,
                sides=[e.report() for e in events],
                by_opponent=_by_opponent(result, chars_played))


def _by_opponent(result, chars):
    from efz_env.vec import character_names
    names = character_names()
    out = {}
    for c in np.unique(chars[:, 1]):
        r = result[chars[:, 1] == c]
        out[names[c]] = [int((r == 1).sum()), int((r == -1).sum()), int((r == 0).sum())]
    return out


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--p1', required=True)
    p.add_argument('--p2', default='cpu', help="'cpu' or a model.zip")
    p.add_argument('--chars', nargs=2, default=('ayu', 'random'))
    p.add_argument('--level', type=int, nargs='+', default=[4])
    p.add_argument('--matches', type=int, default=64)
    p.add_argument('--minutes', type=float, default=5)
    p.add_argument('--deterministic', action='store_true')
    p.add_argument('--json', help='write the results here')
    args = p.parse_args()
    p1 = Agent(args.p1, deterministic=args.deterministic)
    p2 = 'cpu' if args.p2 == 'cpu' else Agent(args.p2, deterministic=args.deterministic)
    out = {}
    for level in (args.level if p2 == 'cpu' else [0]):
        r = play(args, p1, p2, args.matches, level)
        key = f'cpu{level}' if p2 == 'cpu' else 'vs'
        out[key] = r
        print(key, json.dumps({k: v for k, v in r.items() if k != 'by_opponent'}), flush=True)
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
