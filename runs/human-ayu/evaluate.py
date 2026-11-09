"""Matches between agents, or an agent and the game's CPU, played to the end, with how
each side played.

    python runs/human-ayu/evaluate.py --p1 runs/human-ayu/bc.zip --p2 cpu --level 4
    python runs/human-ayu/evaluate.py --p1 runs/human-ayu/model.zip --p2 runs/curriculum/model.zip --chars ayu ayu

A model is an SB3 model.zip with its config.json beside it (frame_skip, history): the
environment steps every frame and each model decides every frame_skip of them, holding
its choice in between, with the input history it was trained with; or a language model's
folder (runs/llm-ayu: llm.json), played by llm.LLMAgent (on CUDA if there is one). --chars: P1's and
P2's characters ('random': drawn per match from the 23; for P2 'tiers': a third of
the matches each against the level-4 CPU's tiers, TIERS). Prints and returns (as JSON
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

import tactics  # noqa: E402  (runs/human-ayu is on the path)

TABLE = ActionTable()
# The observation's columns events are read from: self_action, self_hitstun,
# self_airborne, opp_action, opp_hitstun, opp_own_action, self_combo_hits (the combo
# one is doing: the attacker's counter, / 30) and self_combo_damage (/ 9999).
COLUMNS = [18, 20, 39, 50, 52, 67, 30, 38, 23, 35,  # + self_hitstop, self_own_action
           9, 10, 11,  # + self_gauge (/ 3000), self_rf_gauge (/ 1000), self_rf_blue
           31,  # + self_proration (/ 10000)
           8, 62, 70, 41, 42, 43,  # + self_hp (/ 9999); the combo done to one: opp_combo_hits,
           # opp_combo_damage; and the attacker's resources: opp_gauge, opp_rf_gauge, opp_rf_blue
           ] + tactics.OBS  # + what tactics.py reads
TAKEN = 14  # where those start
TACTICS = 20  # and tactics.OBS
INSTANT_CHARGE = [0xa7, 0xab]  # 22C on the ground and in the air: cancels a move that hit


def rf_state(rf, full):
    """The RF gauge as the HUD draws it (src/player.cpp, src/scene3_draw.cpp). 'blue',
    under 500: no Instant Charge or RF move, it grows fast (0.3 a frame, twice that
    guarding); 'red', 500-999: one Instant Charge or one RF move (500), it grows slowly
    (0.1); 'cyan', once it reaches 1000 (the game's m_rfBlue, obs rf_blue) until it is
    spent: it no longer grows and drains when hit; one Instant Charge, which also adds
    five times the gauge to the combo's proration (up to 50%), or RF moves at 250 each (up
    to 4). An Instant Charge empties it in any state. Damage dealt is also multiplied by
    1 + gauge / 10000."""
    return 'cyan' if full else 'red' if rf >= 500 else 'blue'


def resources(power, rf, full):
    """A resource group: the RF gauge's state (rf_state) and the bars of power, 'cyan2'
    etc."""
    return f'{rf_state(rf, full)}{min(3, int(power // 1000))}'


# In the gauge's order (macros.py's one-hot inputs are by this order).
GROUPS = [f'{s}{b}' for s in ('blue', 'red', 'cyan') for b in range(4)]
GUARD_GROUND, GUARD_AIR = list(range(0x96, 0x9c)), [0x9c]
THROWN = list(range(0x64, 0x79))  # the poses a throw puts its victim in (src/efz.h kThrown*)
THROW_WINDOW = 384  # steps after a throw in which its follow-up is looked for (6 s)
OPP_HP = TACTICS + 15  # tactics.OBS's opp_hp (/ 9999)
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
MAX_HP = 9999       # every character's, at each round's start


def invincible_moves(char):
    """A character's invincible moves (tactics.frame_data: framedata.json); none unknown."""
    try:
        return tactics.frame_data().get(tactics.names().index(char), (set(), []))[0]
    except ValueError:
        return set()

def _prev(x, fill):
    return np.concatenate([[fill], x[:-1]])


class Events:
    """How a player played, counted over whole matches (Ayu's moves for the counts of
    moves): per minute, its presses, jumps, guards, recoil guards (RG: a guard within 10
    frames of pressing back; in the air the only guard against what can't be guarded
    there, anti-airs among them), hits taken, and throws landed and suffered
    (throws_per_min, thrown_per_min: the victim enters a thrown pose, THROWN; command
    throws too); of its throws, throw_damage, the victim's HP lost from the throw until
    it is free again, and throw_combo, the share followed by more damage after the throw
    itself (a combo from it: the user's, for Nanase, Akane, Mayu, Mai, Shiori, Mishio,
    Minagi, Unknown and others); and how often

    rg_ground, rg_air: an attack met there was recoil-guarded (of RG, guard and hit);
    rc: after the opponent recoil-guarded one's attack, its counterattack was
        recoil-guarded back (the recoil counter; of RG, guard and hit);
    rg_move, rg_punish: after one's RG, a move of one's own started within the window,
        and hit; rg_long: a long or RF one (C specials, supers) started; rg_long_hit:
        of those, the share that hit;
    guess_<move>_counter: of the times it did the move (623A, 623B), the share that hit
        the opponent in a move of its own (the counter hit a right guess gets);
    reversals_per_min: its invincible moves (any: framedata.py's, invulnerable in their
        first frames) started; reversal_hit, reversal_counter: the share that hit, and that
        hit the opponent in a move of its own, overriding it (how level-4 Kanna is beaten
        without throws, the user's: her moves are slow and long, so an invincible move
        put out when she acts, a prediction, wins and starts a combo);
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
    damage taken (defence): damage_taken_per_min, the HP lost a minute (combos, chip,
        throws: everything); the opponent's combos on one (its combo counter), per
        minute, their damage on average, at the 90th percentile and the most, and the
        same by the attacker's resource group at the combo's start (taken_by_resources);
    tactics (tactics.py has the definitions), both ways: pressure (one's attacks
        guarded) and under_pressure (the opponent's): the frame advantage after each
        guard, what came next by advantage (plus, even, minus the defender could punish
        by the frame data, minus safe), power gained per guard, blockstring gaps, the
        defender's ways out (invincible moves, mashes, jumps, backdashes; RG and what
        followed it) and how each went, and for one's own the moves guarded last;
        okizeme (the opponent's knockdowns) and wakeup (one's own): the riser's choices
        and how each went, the attacker's setup; free_time and opponent_free_time: the
        steps free while the other can't act, and what they were used for (a setup: an
        object out, a trap; a move; closing in; waiting);
    busy_presses, busy_turns: the share of its presses, and of its changes of direction,
        made while it couldn't move (in a move of its own, or in hitstop): what a cancel
        is made of, a motion buffered for the moment the move connects.
    """

    def __init__(self, char='ayu'):
        self.moves = MOVES.get(char, dict(long=[], special=[], guess={}))
        keys = ['frames', 'jumps', 'throws', 'thrown', 'guard_ground', 'guard_air', 'rg_ground', 'rg_air',
                'hit_ground', 'hit_air', 'rc', 'rc_guard', 'rc_hit', 'rg', 'rg_move',
                'rg_punish', 'rg_long', 'rg_long_hit', 'ic', 'combos', 'combo_hits',
                'combo_damage', 'combos3', 'combos2', 'combo_special', 'combo_ic',
                'presses_all', 'presses_busy', 'turns_all', 'turns_busy']
        for g in self.moves['guess']:
            keys += [f'guess_{g}', f'guess_{g}_counter']
        keys += ['reversals', 'reversal_hit', 'reversal_counter']
        self.n = dict.fromkeys(keys, 0)
        self.invincible = invincible_moves(char)
        self.n['presses'] = np.zeros(4)
        self.n['combo_list'] = []  # each combo's (hits, damage, resource group)
        self.n['proration_left'] = []  # at the end of each of 3 hits or more
        self.n['hp_lost'] = 0.0
        self.n['throw_list'] = []  # each throw landed: (HP the victim lost, of it after the throw)
        self.n['taken_list'] = []  # each of the opponent's combos on one: (damage, its group)
        for k in ('press_off', 'press_def', 'oki_off', 'oki_def', 'free_self', 'free_opp',
                  'strings'):
            self.n[k] = []  # tactics.measure()'s

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
        othrown = np.isin(oa, THROWN)
        throws = np.flatnonzero(othrown & ~_prev(othrown, False))
        n['throws'] += len(throws)
        if cols.shape[1] > OPP_HP:
            ohp = cols[:, OPP_HP] * 9999
            ofree = np.isin(oa, tactics.FREE)
            for t in throws:
                hi = min(T, t + THROW_WINDOW)
                after = np.flatnonzero(~othrown[t:hi])
                released = t + int(after[0]) if len(after) else hi - 1
                free = np.flatnonzero(ofree[released:hi])
                end = released + int(free[0]) if len(free) else hi - 1
                before = ohp[t - 1] if t > 0 else ohp[t]
                n['throw_list'].append((float(before - ohp[end]), float(ohp[released] - ohp[end])))
        n['thrown'] += int((enter & np.isin(a, THROWN) & ~np.isin(_prev(a, -1), THROWN)).sum())
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
        # Damage taken: HP lost (it refills between rounds: only the drops count), and
        # the opponent's combos on one.
        if cols.shape[1] > TAKEN + 5:
            hp = cols[:, TAKEN] * 9999
            n['hp_lost'] += float(np.clip(hp[:-1] - hp[1:], 0, None).sum())
            hits = np.round(cols[:, TAKEN + 1] * 30).astype(int)
            dmg = cols[:, TAKEN + 2] * 9999
            on = hits > 0
            starts = np.flatnonzero(on & ~_prev(on, False))
            ends = np.flatnonzero(~on & _prev(on, False))
            for b in starts:
                later = ends[ends > b]
                e = later[0] if len(later) else T
                g = resources(cols[b, TAKEN + 3] * 3000, cols[b, TAKEN + 4] * 1000,
                              cols[b, TAKEN + 5] > 0)
                n['taken_list'].append((float(dmg[b:e].max()), g))
        # Pressure, wake-up and free time, both ways (tactics.py).
        if cols.shape[1] >= TACTICS + len(tactics.OBS):
            for k, v in tactics.measure(cols[:, TACTICS:TACTICS + len(tactics.OBS)],
                                        controls).items():
                n[k] += v
        # The guesses: a counter hit is a hit on an opponent in a move of its own.
        for g, acts in self.moves['guess'].items():
            for t in np.flatnonzero(enter & np.isin(a, acts)):
                n[f'guess_{g}'] += 1
                hits = np.flatnonzero(ohit[t:min(T, t + HIT_WINDOW)])
                if len(hits) and oown[max(0, t + hits[0] - 1)]:
                    n[f'guess_{g}_counter'] += 1
        # Reversals: any invincible move, and whether it hit, overriding a move of theirs.
        if self.invincible:
            for t in np.flatnonzero(enter & np.isin(a, list(self.invincible))):
                n['reversals'] += 1
                hits = np.flatnonzero(ohit[t:min(T, t + HIT_WINDOW)])
                if len(hits):
                    n['reversal_hit'] += 1
                    if oown[max(0, t + hits[0] - 1)]:
                        n['reversal_counter'] += 1

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
        for k in ('jumps', 'throws', 'thrown', 'guard_ground', 'guard_air', 'rg_ground',
                  'rg_air', 'hit_ground', 'hit_air'):
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
        out['reversals_per_min'] = round(n['reversals'] * per_min, 2)
        out['reversal_hit'] = share(n['reversal_hit'], n['reversals'])
        out['reversal_counter'] = share(n['reversal_counter'], n['reversals'])
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
        out['damage_taken_per_min'] = round(n['hp_lost'] * per_min)
        th = n['throw_list']
        out['throw_damage'] = round(float(np.mean([x[0] for x in th]))) if th else None
        out['throw_combo'] = share(sum(x[1] > 0 for x in th), len(th))
        taken = n['taken_list']
        out['taken_combos_per_min'] = round(len(taken) * per_min, 2)
        if taken:
            dmg = np.array([x[0] for x in taken], float)
            groups = np.array([x[1] for x in taken])
            out['taken_combo_damage'] = round(float(dmg.mean()))
            out['taken_combo_damage_p90'] = round(float(np.percentile(dmg, 90)))
            out['taken_combo_damage_max'] = round(float(dmg.max()))
            out['taken_by_resources'] = {
                g: dict(n=int((groups == g).sum()), damage=round(float(dmg[groups == g].mean())),
                        p90=round(float(np.percentile(dmg[groups == g], 90))),
                        most=round(float(dmg[groups == g].max())))
                for g in GROUPS if (groups == g).any()}
        out.update(tactics.report(n, per_min))
        return out


def play(args, p1, p2, matches, level=4, seed=7):
    env = EfzVecEnv(args.data, matches, frame_skip=1, max_frames=int(args.minutes * 3840),
                    cpu_level=level, autoreset='disabled', seed=seed,
                    reward_round=0.0, reward_match=1.0)
    chars = [None if c in ('random', 'tiers') else c for c in args.chars]
    if args.chars[1] == 'tiers':
        env.set_matches(chars=[(chars[0], c) for c in tier_opponents(matches, seed)],
                        cpu=(False, p2 == 'cpu'))
    else:
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
    # Each round, the share of P2's HP P1 took and of P1's P2 took (9999 a bar), and P1's
    # rounds won.
    cur_round = np.zeros(matches, int)
    last_hp = np.full((matches, 2), MAX_HP)
    taken = [[] for _ in range(matches)]
    lost = [[] for _ in range(matches)]
    rounds_won = np.zeros(matches, int)
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
        for i in np.flatnonzero(live):  # a new round: HP back to full on the same step
            r = int(info['round'][i])
            if cur_round[i] and r != cur_round[i]:
                taken[i].append((MAX_HP - last_hp[i, 1]) / MAX_HP)
                lost[i].append((MAX_HP - last_hp[i, 0]) / MAX_HP)
            cur_round[i] = r
            last_hp[i] = info['hp'][i]
        ended = (term | trunc) & live
        for i in np.flatnonzero(ended):
            w = int(info['winner'][i])
            result[i] = 1 if w == 0 else -1 if w == 1 else 0
            chars_played[i] = info['chars'][i]
            taken[i].append((MAX_HP - last_hp[i, 1]) / MAX_HP)
            lost[i].append((MAX_HP - last_hp[i, 0]) / MAX_HP)
            rounds_won[i] = int(info['rounds_won'][i, 0])
        done |= term | trunc
    env.close()
    events = []
    for s in range(2):
        e = Events(args.chars[s] if args.chars[s] not in ('random', 'tiers') else '')
        for match in seen[s]:
            e.add_match(np.array([c for c, _ in match]), np.array([u for _, u in match]))
        events.append(e)
    hp = HpTaken(taken, rounds_won, lost)
    return dict(win=float((result == 1).mean()), loss=float((result == -1).mean()),
                cut=float((result == 0).mean()), matches=matches, **hp.of(slice(None)),
                sides=[e.report() for e in events],
                by_tier=_by_tier(result, chars_played, hp) if p2 == 'cpu' and level == 4 else {},
                by_opponent=_by_opponent(result, chars_played),
                hp_by_opponent=_hp_by_opponent(chars_played, hp))


# The level-4 CPU by how hard it is to beat (the user's): Kanna the hardest, then Ayu
# and Mishio, then the rest; at level 3 and below every character is easy, so results
# there have no tiers (README.md, "The CPU's tiers": why, and each character measured).
# The 23 playable characters: all but 22 (Nayuki's second) and 24 (Mizuka, the boss), as
# efz_env draws them.
TIERS = {'kanna': 'hardest', 'ayu': 'hard', 'mishio': 'hard'}
TIER_ORDER = ('hardest', 'hard', 'rest')
UNPLAYABLE = ('nayuki2', 'mizuka')


def tier_opponents(n, seed=7):
    """P2's characters for n matches, a third per tier: Kanna; Ayu and Mishio in turn;
    one of the rest, drawn."""
    from efz_env.vec import character_names
    rest = [c for c in character_names() if c not in TIERS and c not in UNPLAYABLE]
    rng = np.random.default_rng(seed)
    return ['kanna' if i % 3 == 0 else ('ayu', 'mishio')[(i // 3) % 2] if i % 3 == 1
            else rest[rng.integers(len(rest))] for i in range(n)]


class HpTaken:
    """Per match, the share of P2's HP P1 took in each round, and P1's rounds won: a
    measure short of winning (level-4 Kanna is never beaten: the user's). And the share
    of P1's own HP P2 took a round (self_hp_taken; with lost): a measure past winning,
    telling hard wins from easy ones where P1 wins nearly always (the user's)."""

    def __init__(self, taken, rounds_won, lost=None):
        self.taken, self.rounds_won, self.lost = taken, np.asarray(rounds_won), lost

    def of(self, which):
        idx = np.arange(len(self.taken))[which]
        rounds = [x for i in idx for x in self.taken[i]]
        if not len(idx):
            return {}
        out = dict(opp_hp_taken=round(float(np.mean(rounds)), 3) if rounds else None,
                   opp_hp_taken_best=round(float(np.max(rounds)), 3) if rounds else None,
                   rounds_won=round(float(self.rounds_won[idx].mean()), 3))
        if self.lost is not None:
            own = [x for i in idx for x in self.lost[i]]
            out['self_hp_taken'] = round(float(np.mean(own)), 3) if own else None
        return out


def _by_tier(result, chars, hp=None):
    from efz_env.vec import character_names
    names = character_names()
    tiers = np.array([TIERS.get(names[c], 'rest') for c in chars[:, 1]])
    out = {}
    for t in TIER_ORDER:
        r = result[tiers == t]
        if len(r):
            out[t] = dict(matches=len(r), win=round(float((r == 1).mean()), 3),
                          loss=round(float((r == -1).mean()), 3),
                          cut=round(float((r == 0).mean()), 3),
                          **(hp.of(tiers == t) if hp is not None else {}))
    return out


def _hp_by_opponent(chars, hp):
    from efz_env.vec import character_names
    names = character_names()
    return {names[c]: hp.of(chars[:, 1] == c) for c in np.unique(chars[:, 1])}


def _by_opponent(result, chars):
    from efz_env.vec import character_names
    names = character_names()
    out = {}
    for c in np.unique(chars[:, 1]):
        r = result[chars[:, 1] == c]
        out[names[c]] = [int((r == 1).sum()), int((r == -1).sum()), int((r == 0).sum())]
    return out


def make_agent(path, deterministic=False, delay=None):
    """An SB3 model.zip's Agent, or a language model's folder's (llm.json) LLMAgent. delay:
    how many steps late it sees the game, instead of its config's."""
    if os.path.isdir(path) and os.path.exists(os.path.join(path, 'llm.json')):
        sys.path.insert(0, os.path.join(REPO, 'runs', 'llm-ayu'))
        from llm import LLMAgent
        return LLMAgent(path, deterministic=deterministic)
    return Agent(path, deterministic=deterministic, delay=delay)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--p1', required=True)
    p.add_argument('--p2', default='cpu', help="'cpu' or a model.zip")
    p.add_argument('--chars', nargs=2, default=('ayu', 'random'),
                   help="P1's and P2's: names, 'random', or for P2 'tiers' (TIERS)")
    p.add_argument('--level', type=int, nargs='+', default=[4])
    p.add_argument('--matches', type=int, default=64)
    p.add_argument('--minutes', type=float, default=5)
    p.add_argument('--deterministic', action='store_true')
    p.add_argument('--seed', type=int, default=7,
                   help="the matches' seed (finetune.py's evaluations play seed 7)")
    p.add_argument('--p1-delay', type=int,
                   help="P1 sees the game this many steps late, instead of its config's")
    p.add_argument('--json', help='write the results here')
    p.add_argument('--p1-combo', help="combo_support.ComboSwitch: P1's combos played by this "
                                      "model (combo.py's combo master)")
    p.add_argument('--p1-confirm', default='seen', choices=('seen', 'now'),
                   help="--p1-combo takes over once P1 sees its hit (its delay) or at once")
    p.add_argument('--p1-lookahead', help="combo_support.lookahead: P1's routes tried on copies "
                                          "from this library (combo_library.py's)")
    p.add_argument('--p1-assist', help="combo_support.FairComboAgent: the same once P1 sees its "
                                       "hit (strong but fair), from this library")
    p.add_argument('--assist-victims', nargs='+',
                   help="--p1-assist only against these characters (its own play against "
                        "the rest), e.g. kanna")
    p.add_argument('--assist-score', default='damage', choices=('damage', 'value'),
                   help="--p1-assist's choice: the most damaging option, or the most worth to "
                        "P1 (damage plus its critic's value of the game it left: redteam.Planner)")
    args = p.parse_args()
    p1 = make_agent(args.p1, args.deterministic, args.p1_delay)
    if sum(bool(x) for x in (args.p1_combo, args.p1_lookahead, args.p1_assist)) > 1:
        p.error('one of --p1-combo, --p1-lookahead, --p1-assist')
    if args.p1_combo or args.p1_lookahead or args.p1_assist:
        import combo_support
        if args.p1_assist:
            import macros
            import redteam
            planner = redteam.Planner(args.data, macros.load_library(args.p1_assist), p1.model,
                                      score=args.assist_score, victims=args.assist_victims)
            p1 = combo_support.FairComboAgent(p1, planner)
        if args.p1_lookahead:
            p1 = combo_support.lookahead(args.data, args.p1, args.p1_lookahead)
        if args.p1_combo:
            p1 = combo_support.ComboSwitch(p1, make_agent(args.p1_combo, args.deterministic),
                                           args.p1_confirm)
    p2 = 'cpu' if args.p2 == 'cpu' else make_agent(args.p2, args.deterministic)
    out = {}
    for level in (args.level if p2 == 'cpu' else [0]):
        r = play(args, p1, p2, args.matches, level, seed=args.seed)
        key = f'cpu{level}' if p2 == 'cpu' else 'vs'
        out[key] = r
        print(key, json.dumps({k: v for k, v in r.items()
                               if k not in ('by_opponent', 'hp_by_opponent', 'sides', 'by_tier')}),
              flush=True)
        if r['by_tier']:
            print('  by tier:', ', '.join(f"{t} {v['win']:.0%} of {v['matches']} (HP taken a round "
                                          f"{v['opp_hp_taken']:.0%}, its own lost "
                                          f"{v['self_hp_taken']:.0%}, rounds {v['rounds_won']:.2f})"
                                          for t, v in r['by_tier'].items()), flush=True)
    if args.p1_assist:  # its plans: how many, the share a route won, the damage options made
        out['assist'] = dict(p1.assist.take_plans(), score=args.assist_score,
                             changed=planner.changed, victims=args.assist_victims)
        print('assist', json.dumps(out['assist']), flush=True)
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
