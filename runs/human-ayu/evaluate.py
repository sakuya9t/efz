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

    python runs/human-ayu/evaluate.py --p1 A.efzagent --p1-native --p2 A.efzagent --p2-cpu-combos 4 --chars ayu ayu

--p2-cpu-combos LEVEL: P2 is the game's CPU at that level except for its combos, which
--p2 plays (the side handed over while P1 is in a hit reaction): the CPU's guard, recoil
guards and counters with combos worth an agent's.
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
           ] + tactics.OBS + [13, 45]  # + what tactics.py reads; + self_x, opp_x (corner())
TAKEN = 14  # where those start
TACTICS = 20  # and tactics.OBS
POSITIONS = TACTICS + len(tactics.OBS)  # and the two positions
# corner(): the opponent is held in a corner from the step it is within CORNER_IN of a
# wall (positions run to +-0.95) with the player on the open side within CORNER_NEAR
# pixels, until it is CORNER_OUT from the wall, the player is no longer on the open side
# or is CORNER_FAR pixels away, or the round ends; a stay of CORNER_LEAST steps counts.
CORNER_IN, CORNER_OUT, CORNER_NEAR, CORNER_FAR, CORNER_LEAST = 0.80, 0.68, 220, 330, 20
# Where a press is made (presses_where): hit or guarding; the opponent in its combo; the
# opponent guarding; neither.
WHERE = ('defending', 'combo', 'pressure', 'neutral')
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
# The observation's: no fight yet / a KO; the viewer's action and whether it is in a hit
# reaction (lying on the ground and rising count as one: LAID).
INTRO, ROUND_OVER, SELF_ACTION, SELF_HITSTUN = 2, 3, 18, 20
LAID = (0x60, 0x63)


def invincible_moves(char):
    """A character's invincible moves (tactics.frame_data: framedata.json); none unknown."""
    try:
        return tactics.frame_data().get(tactics.names().index(char), (set(), []))[0]
    except ValueError:
        return set()

def corner_stays(c, x):
    """corner()'s stays as (first step, the step after the last), with the live steps and
    the distance in pixels (tactics.OBS's columns `c`, the positions `x`: self_x, opp_x)."""
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    dist = np.abs(c[:, 18]) * 640
    mx, ox = np.abs(x[:, 0]), np.abs(x[:, 1])
    open_side = (mx < ox) & (np.sign(x[:, 0]) * np.sign(x[:, 1]) >= 0) | (mx < 0.3)
    start = live & (ox > CORNER_IN) & open_side & (dist <= CORNER_NEAR)
    hold = live & (ox > CORNER_OUT) & open_side & (dist <= CORNER_FAR)
    out, T, t = [], len(c), 0
    while t < T:
        if not start[t]:
            t += 1
            continue
        e = t
        while e < T and hold[e]:
            e += 1
        if e - t >= CORNER_LEAST:
            out.append((t, e))
        t = e + 1
    return out, live, dist


def corner(c, x):
    """The stays of the opponent in a corner under the player (tactics.OBS's columns `c`,
    the two positions `x`: self_x, opp_x): a list of (steps, HP the opponent lost in it,
    HP the player lost in it, how it ended: 0 the round ended or the match's record did,
    1 the opponent left through the air (over the player or past it), 2 it left on the
    ground or the player backed off, 3 the player was hit away)."""
    me, op = tactics.Side(c, 0), tactics.Side(c, 1)
    stays, live, _ = corner_stays(c, x)
    out, T = [], len(c)
    for t, e in stays:
        how = (0 if e >= T or not live[e] else
               3 if me.hitstun[e] or me.hitstun[max(t, e - 20):e].any() else
               1 if op.air[e] or op.air[max(t, e - 6):e].any() else 2)
        out.append((e - t, float(op.hp[t] - op.hp[min(e, T - 1)]),
                    float(me.hp[t] - me.hp[min(e, T - 1)]), how))
    return out


# corner_hold(): what a corner stay is made of. The distances the player stands at (pixels,
# the last band: further), and the steps after a jump of the opponent's in which what
# became of it is looked for.
HOLD_BANDS, HOLD_WATCH = (60, 110, 170), 50
HOLD = ('steps', 'guard', 'hit') + tuple(f'<{b}' for b in HOLD_BANDS) + ('further',) + (
    'moves', 'air moves', 'jumps', 'out', 'stayed in', 'player hit', 'caught')


def corner_hold(c, x):
    """What corner()'s stays are made of, as counts in HOLD's order: their steps, those
    with the opponent in a guard and in a hit; the steps the opponent was free on the
    ground with the player not hit, by the distance between them (HOLD_BANDS); the
    player's moves begun there and those of them in the air; and the opponent's own jumps
    there (it left the ground out of no hit), by what became of each within HOLD_WATCH
    steps: it was out of the corner, still in it, the player was hit first, or the
    player's hit caught it in the air."""
    me, op = tactics.Side(c, 0), tactics.Side(c, 1)
    stays, _, dist = corner_stays(c, x)
    n, T = np.zeros(len(HOLD)), len(c)
    rise = op.air & ~_prev(op.air, False)
    for t, e in stays:
        s = slice(t, e)
        n[0] += e - t
        n[1] += op.guard[s].sum()
        n[2] += op.hitstun[s].sum()
        calm = ~op.guard[s] & ~op.hitstun[s] & ~op.air[s] & ~me.hitstun[s]
        n[3:3 + len(HOLD_BANDS) + 1] += np.bincount(
            np.searchsorted(HOLD_BANDS, dist[s][calm], side='right'), minlength=len(HOLD_BANDS) + 1)
        k = 3 + len(HOLD_BANDS) + 1
        n[k] += me.move[s].sum()
        n[k + 1] += (me.move[s] & me.air[s]).sum()
        for j in np.flatnonzero(rise[s]) + t:
            if j == t or op.hitstun[j] or op.hitstun[j - 1]:
                continue
            end = min(T, j + HOLD_WATCH)
            caught = np.flatnonzero(op.hit[j:end] & op.air[j:end])
            took = np.flatnonzero(me.hit[j:end])
            n[k + 2] += 1
            if len(caught) and not (len(took) and took[0] < caught[0]):
                n[k + 6] += 1
            elif len(took):
                n[k + 5] += 1
            elif e < end:
                n[k + 3] += 1
            else:
                n[k + 4] += 1
    return n


def jumpins(c):
    """The opponent's airborne attacks that met the player on the ground and not in a move of
    its own (it could have guarded), from tactics.OBS's columns `c`: [[hit, guarded,
    recoil-guarded] from the front, the same having crossed sides in the 25 steps before],
    each followed by what it was doing on the step before: walking back (a standing guard
    held), crouching, walking forward, anything else."""
    me, op = tactics.Side(c, 0), tactics.Side(c, 1)
    side = np.sign(c[:, 18])
    out = np.zeros((2, 7))
    for t in np.flatnonzero((me.hit | me.contact) & op.air):
        if t < 2 or me.air[t - 1] or me.act[t - 1] >= tactics.FIRST_OWN:
            continue
        crossed = bool((side[max(0, t - 25):t] * side[t] < 0).any())
        out[int(crossed), 0 if me.hit[t] else 2 if me.act[t] in tactics.RG else 1] += 1
        out[int(crossed), 3 + {0x2: 0, 0x3: 1, 0x8: 1, 0x1: 2}.get(int(me.act[t - 1]), 3)] += 1
    return out


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
    how combos end (tactics.endings): combo_ends, one's own (all, and those of 1000 HP
        or more: big), the shares left in a knockdown (the opponent rises into one's
        okizeme), in an air recovery (the untech time ran out in the air: the opponent
        is free), standing, or a KO, and after a recovery who was hit first;
        taken_combo_ends, the opponent's on one. grabs: throws and air throws a minute
        (tried, landed), the chances for one, and the air exchanges won and lost.
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
    risks (tactics.risks): per risky move (Ayu's 623A/B/C and 236C, and any invincible
        one): a minute, the share inside a combo, and of the raw ones the shares that
        hit, were guarded, recoil-guarded and whiffed, the share of the misses the
        opponent punished and the HP a miss cost, net, the HP a raw use is worth, and
        of the raw ones the wake-up reversals: their share, their hits, their own net;
        faced_risks: the same of the opponent's risky moves (hit: it was hit by them;
        punished: it punished their misses: what a bait is for);
    ledger (tactics.losses): where its HP goes: every loss of HP by what it was doing
        when the loss began (in the air attacking, by where it came from and what hit
        it; in a move in neutral, after guarding, rising; opened after guarding; free
        on the ground; rising; thrown; chip ...), HP a minute, times a minute, HP a
        time; dealt_ledger: the same of the opponent's losses to it; net_ledger
        (tactics.exchanges): the HP a minute it is ahead or behind in all and by the
        situation an exchange began in, whoever was hit (its okizeme, the opponent's,
        its pressure, the opponent's, it came by air, the opponent did, both in the
        air, on the ground: net, gained, lost). What a round is judged by, beside the
        strongest players' (people-ledger.json; docs/training-v2-log.md); areas
        (tactics.areas_report): the same situations as a scorecard, by the time spent
        in each: its share of the match and the HP a second ahead while in it, and the
        HP of a hit either way (areas.py tabulates them by opponent);
    flights (tactics.flights): its air dashes a minute (Ayu's flights), the share back,
        what it did next and what came of it, and how mixed what it did next was;
    raw (tactics.raw_report): the raw risky moves as one account: a minute, the HP a use
        is worth and the HP a minute; faced_raw: the opponent's, with the share of its
        misses the player punished;
    rounds (tactics.rounds): what it makes of an advantage: of the rounds it was 3,000 HP
        ahead in, the share it won and the HP it lost after; of those it was that far
        behind in, the share it turned; of those there to be closed (the opponent at a
        quarter of its HP, the player ahead), the share won, the seconds that took and
        the HP it cost;
    presses_where: its presses a second, and the share of the time, in each of WHERE;
    corner: the opponent held in a corner (corner(): within CORNER_IN of a wall, the
        player on the open side and near): stays a minute, their length in seconds (mean,
        median, 90th percentile), the share of the match spent so, the HP dealt and lost
        a stay, and how the stays ended (the round over, the opponent out through the
        air, out on the ground or the player backing off, the player hit away): how well
        its pressure keeps an opponent that wants out (the user's, 18 November);
        its `hold` (corner_hold()): what the stays are made of: the share of their steps
        the opponent is in a guard and in a hit, where the player stands while it is
        free, the player's moves a stay and the share of them in the air, and the
        opponent's jumps there with what became of them (out, still in, the player hit
        first, caught in the air): the user's, 22 November (to handle pressure it has to
        know how to pressure, in the corners above all);
    jumpins: the opponent's airborne attacks that met it on the ground, able to guard: a
        minute, and from the front and crossing sides the share hit, guarded, recoil-guarded,
        and what it was doing just before (walking back, crouching, walking forward, other);
    busy_presses, busy_turns: the share of its presses, and of its changes of direction,
        made while it couldn't move (in a move of its own, or in hitstop): what a cancel
        is made of, a motion buffered for the moment the move connects.
    """

    def __init__(self, char='ayu'):
        self.char = char
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
        self.n['press_where'] = np.zeros((len(WHERE), 2))  # presses, steps in each of WHERE
        self.n['jumpin'] = np.zeros((2, 7))  # jumpins()'s
        self.n['corner_list'] = []  # corner()'s stays
        self.n['corner_steps'] = 0  # the live steps they are out of
        self.n['corner_hold'] = np.zeros(len(HOLD))  # corner_hold()'s
        self.n['combo_list'] = []  # each combo's (hits, damage, resource group)
        self.n['proration_left'] = []  # at the end of each of 3 hits or more
        self.n['hp_lost'] = 0.0
        self.n['throw_list'] = []  # each throw landed: (HP the victim lost, of it after the throw)
        self.n['taken_list'] = []  # each of the opponent's combos on one: (damage, its group)
        for k in ('press_off', 'press_def', 'oki_off', 'oki_def', 'free_self', 'free_opp',
                  'strings', 'ends_off', 'ends_def', 'grabs', 'risks', 'risks_def',
                  'flights', 'losses', 'losses_opp', 'exchanges', 'situation_time', 'episodes',
                  'rounds'):
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
            tc = cols[:, TACTICS:TACTICS + len(tactics.OBS)]
            me, op = tactics.Side(tc, 0), tactics.Side(tc, 1)
            where = np.where(me.hitstun | me.guard, 0, np.where(op.hitstun, 1,
                                                                 np.where(op.guard, 2, 3)))
            count = input_features(controls, prev_c)[:, 2:].sum(1)
            for w in range(len(WHERE)):
                n['press_where'][w] += count[where == w].sum(), (where == w).sum()
            for k, v in tactics.measure(cols[:, TACTICS:TACTICS + len(tactics.OBS)],
                                        controls).items():
                n[k] += v
            n['jumpin'] += jumpins(cols[:, TACTICS:TACTICS + len(tactics.OBS)])
            if cols.shape[1] >= POSITIONS + 2:
                n['corner_list'] = n['corner_list'] + corner(
                    cols[:, TACTICS:TACTICS + len(tactics.OBS)], cols[:, POSITIONS:POSITIONS + 2])
                n['corner_steps'] += int(((cols[:, TACTICS + 16] == 0) &
                                          (cols[:, TACTICS + 17] == 0)).sum())
                n['corner_hold'] = n['corner_hold'] + corner_hold(
                    cols[:, TACTICS:TACTICS + len(tactics.OBS)], cols[:, POSITIONS:POSITIONS + 2])
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
        pw = n['press_where']
        if pw[:, 1].sum():  # where: [presses a second there, the share of the time there]
            out['presses_where'] = {w: [round(float(pw[i, 0] / max(1, pw[i, 1]) * 64), 2),
                                        round(float(pw[i, 1] / pw[:, 1].sum()), 3)]
                                    for i, w in enumerate(WHERE)}
        cl = n['corner_list']
        if n['corner_steps']:
            # The opponent held in a corner: stays a minute, how long (seconds: 60 steps),
            # the share of the match spent so, the HP dealt and lost a stay, and how the
            # stays ended.
            steps = np.array([x[0] for x in cl], float)
            ends = np.array([x[3] for x in cl], int)
            out['corner'] = dict(
                per_min=round(len(cl) * 3600 / n['corner_steps'], 2), n=len(cl),
                share=round(float(steps.sum() / n['corner_steps']), 3),
                seconds=round(float(steps.mean() / 60), 2) if len(cl) else None,
                seconds_median=round(float(np.median(steps) / 60), 2) if len(cl) else None,
                seconds_p90=round(float(np.percentile(steps, 90) / 60), 2) if len(cl) else None,
                dealt=round(float(np.mean([x[1] for x in cl]))) if len(cl) else None,
                lost=round(float(np.mean([x[2] for x in cl]))) if len(cl) else None,
                ended={k: share(int((ends == j).sum()), len(cl)) for j, k in
                       enumerate(('round', 'out by air', 'out on the ground', 'hit away'))},
                # (the stays the opponent left on its own, by air or on the ground)
                left=share(int(((ends == 1) | (ends == 2)).sum()), len(cl)))
            h = dict(zip(HOLD, (float(v) for v in n['corner_hold'])))
            if h['steps']:
                # What the stays are made of (corner_hold()): the share of their steps the
                # opponent is in a guard and in a hit, where the player stands while it
                # is free, the player's moves a stay and the share of them in the air,
                # the opponent's jumps a stay and what became of them.
                stand = [f'<{b}' for b in HOLD_BANDS] + ['further']
                ways = ('out', 'stayed in', 'player hit', 'caught')
                out['corner']['hold'] = dict(
                    guard=share(h['guard'], h['steps']), hit=share(h['hit'], h['steps']),
                    stands={k: share(h[k], sum(h[b] for b in stand)) for k in stand},
                    moves=round(h['moves'] / max(1, len(cl)), 2),
                    air_moves=share(h['air moves'], h['moves']),
                    jumps=round(h['jumps'] / max(1, len(cl)), 2), jumps_n=int(h['jumps']),
                    jump={k: share(h[k], h['jumps']) for k in ways})
        ji = n['jumpin']
        if ji.sum():  # met a minute; from the front and crossing: how many, and how they ended
            out['jumpins'] = dict(per_min=round(float(ji[:, :3].sum() * per_min), 2), **{
                w: dict(n=int(ji[i, :3].sum()),
                        **{k: share(ji[i, j], ji[i, :3].sum())
                           for j, k in enumerate(('hit', 'guard', 'rg'))},
                        before={k: share(ji[i, 3 + j], ji[i, 3:].sum())
                                for j, k in enumerate(('back', 'crouch', 'forward', 'other'))})
                for i, w in enumerate(('front', 'cross'))})
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


def spread(full, without):
    """The standard error of every number of `full` (a tree of dicts: a pairing's result)
    by the jackknife over groups of matches: without[k] is the same tree counted without
    group k. A number missing or not a number in any of them has none (a rate with
    nothing under it in one of the counts). The same tree's shape, numbers only: a
    measure made of many events of a match (a rate, a mean of HP, a share) has an error
    here without anything known of how it is made."""
    K = len(without)

    def number(x):
        return isinstance(x, (int, float)) and not isinstance(x, bool) and np.isfinite(x)

    def walk(f, ws):
        if isinstance(f, dict):
            out = {}
            for key, v in f.items():
                sub = [w.get(key) if isinstance(w, dict) else None for w in ws]
                got = walk(v, sub)
                if got is not None and got != {}:
                    out[key] = got
            return out
        if isinstance(f, list) and f and all(isinstance(x, dict) for x in f):
            out = [walk(v, [w[j] if isinstance(w, list) and len(w) > j else None for w in ws])
                   for j, v in enumerate(f)]
            return out
        if number(f) and all(number(w) for w in ws):
            a = np.array(ws, float)
            se = float(np.sqrt((K - 1) / K * ((a - a.mean()) ** 2).sum()))
            return float(f'{se:.3g}')
        return None

    return walk(full, without)


def play(args, p1, p2, matches, level=4, seed=7):
    """The matches played to the end. seed: the game's, and the agents' draws of their
    actions (torch's generator, seeded here and given back as it was: the caller's,
    finetune.py's training, goes on as if nothing were drawn), so a run is repeated."""
    import torch
    with torch.random.fork_rng(devices=[]):
        torch.manual_seed(seed)
        return _play(args, p1, p2, matches, level, seed)


def _base(a):
    """The efz_env.agent.Agent under an agent's hosts and wrappers."""
    seen = set()
    while id(a) not in seen:
        seen.add(id(a))
        inner = a.__dict__.get('agent', a.__dict__.get('base'))
        if inner is None:
            break
        a = inner
    return a


def _play(args, p1, p2, matches, level, seed):
    # --sets N: the matches in sets of N against the same opponent (its habits the
    # set's, an agent's match memory carried): matches / N environments, each playing N
    # matches one after another; match leg * n + i is environment i's match number leg.
    legs = max(1, int(getattr(args, 'sets', 1) or 1))
    total, matches = (matches // legs) * legs, matches // legs
    # --p2-cpu-combos LEVEL: P2 the game's CPU at that level, but for its combos: while P1
    # is in a hit reaction (not yet lying on the ground) --p2 plays, handed the side on
    # the step after the hit lands, and the CPU has it back when the combo is over: the
    # CPU's own neutral, guard, recoil guards and okizeme.
    hybrid = int(getattr(args, 'p2_cpu_combos', 0) or 0) if p2 != 'cpu' else 0
    env = EfzVecEnv(args.data, matches, frame_skip=1, max_frames=int(args.minutes * 3840),
                    cpu_level=hybrid or level, autoreset='disabled', seed=seed,
                    reward_round=0.0, reward_match=1.0)
    chars = [None if c in ('random', 'tiers') else c for c in args.chars]
    if args.chars[1] == 'tiers':
        env.set_matches(chars=[(chars[0], c) for c in tier_opponents(matches, seed)],
                        cpu=(False, p2 == 'cpu' or hybrid > 0))
    else:
        env.set_matches(chars=tuple(chars), cpu=(False, p2 == 'cpu' or hybrid > 0))
    handed = dict(steps=0, agent=0, times=0)  # P2's steps, those --p2 played, its turns
    agents = [p1] + ([] if p2 == 'cpu' else [p2])
    for side, a in enumerate(agents):
        a.batch(matches)
        if hasattr(a, 'attach'):  # the lookahead red team (redteam.py) saves the games
            a.attach(env, side)
    # P2's habits by match (advantages.py), told to a P1 that takes them (unless --p1-untold).
    logic = getattr(p2, 'logic', None)
    habits = np.stack([logic.told(i) for i in range(matches)]) if logic is not None else None
    base = getattr(p1, 'agent', p1)
    if habits is not None and hasattr(base, 'told') and not getattr(args, 'p1_untold', False):
        base.told = habits
    if habits is not None:
        habits = np.tile(habits, (legs, 1))
    result = np.zeros(total, int)  # 1 P1 won, -1 lost, 0 cut short
    seen = [[[] for _ in range(total)] for _ in range(2)]  # per side: (cols, input)
    step = 0
    chars_played = np.zeros((total, 2), int)
    # Each round, the share of P2's HP P1 took and of P1's P2 took (9999 a bar), and P1's
    # rounds won.
    taken = [[] for _ in range(total)]
    lost = [[] for _ in range(total)]
    rounds_won = np.zeros(total, int)
    for leg in range(legs):
      at = leg * matches  # (this leg's matches: at + i)
      if leg:  # the set goes on: the agents' next match, their memories kept
          everywhere = np.ones(matches, bool)
          for side, a in enumerate(agents):
              b = _base(a)
              if hasattr(b, 'set_next'):
                  w = result[at - matches:at] == (1 if side == 0 else -1)
                  b.set_next(won=w, new_set=np.zeros(matches, bool))
              a.reset(everywhere)
      obs = env.reset()
      done = np.zeros(matches, bool)
      cur_round = np.zeros(matches, int)
      last_hp = np.full((matches, 2), MAX_HP)
      cpu_plays = np.ones(matches, bool)  # --p2-cpu-combos: who has P2 (a match starts the CPU's)
      while not done.all():
          if hybrid:
              fight = (obs[:, 0, INTRO] == 0) & (obs[:, 0, ROUND_OVER] == 0)
              want = ~((obs[:, 0, SELF_HITSTUN] > 0) & fight &
                       ~np.isin(obs[:, 0, SELF_ACTION].astype(int), LAID))
              for i in np.flatnonzero((want != cpu_plays) & ~done):
                  if env.set_cpu(i, 1, bool(want[i])):
                      cpu_plays[i] = want[i]
                      handed['times'] += not want[i]
              handed['steps'] += int((~done).sum())
              handed['agent'] += int((~cpu_plays & ~done).sum())
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
                  seen[s][at + i].append((view[i, s], info['input'][i, s]))
          for i in np.flatnonzero(live):  # a new round: HP back to full on the same step
              r = int(info['round'][i])
              if cur_round[i] and r != cur_round[i]:
                  taken[at + i].append((MAX_HP - last_hp[i, 1]) / MAX_HP)
                  lost[at + i].append((MAX_HP - last_hp[i, 0]) / MAX_HP)
              cur_round[i] = r
              last_hp[i] = info['hp'][i]
          ended = (term | trunc) & live
          for i in np.flatnonzero(ended):
              w = int(info['winner'][i])
              result[at + i] = 1 if w == 0 else -1 if w == 1 else 0
              chars_played[at + i] = info['chars'][i]
              taken[at + i].append((MAX_HP - last_hp[i, 1]) / MAX_HP)
              lost[at + i].append((MAX_HP - last_hp[i, 0]) / MAX_HP)
              rounds_won[at + i] = int(info['rounds_won'][i, 0])
          done |= term | trunc
    env.close()
    matches = total
    events, detail = [], [dict(result=int(result[i]), set_match=1 + i // (total // legs))
                          for i in range(matches)]
    # --folds K: the matches in K groups (a set's matches in one), each side's events
    # kept by group, for every number's standard error (spread()).
    per_leg = total // legs
    folds = max(0, min(int(getattr(args, 'folds', 0) or 0), per_leg))
    fold = (np.arange(matches) % per_leg) % folds if folds > 1 else None
    parts = []
    for s in range(2):
        char = args.chars[s] if args.chars[s] not in ('random', 'tiers') else ''
        e = Events(char)
        parts.append([Events(char) for _ in range(folds)] if fold is not None else None)
        for i, match in enumerate(seen[s]):
            before = {k: len(e.n[k]) for k in ('oki_off', 'oki_def', 'press_off')}
            one = Events(char)
            one.add_match(np.array([c for c, _ in match]), np.array([u for _, u in match]))
            e.merge(one)
            if fold is not None:
                parts[s][fold[i]].merge(one)
            if s == 0 and habits is not None:  # P1's match, for its play by P2's habits
                detail[i].update(habits=[round(float(x), 3) for x in habits[i]],
                                 lost=float(np.mean(lost[i])), taken=float(np.mean(taken[i])),  # a round
                                 **{k: [{kk: vv.item() if hasattr(vv, 'item') else vv for kk, vv in r.items()}
                                        for r in e.n[k][n:]] for k, n in before.items()})
        events.append(e)
    hp = HpTaken(taken, rounds_won, lost)

    def top(which):
        r = result[which]
        return dict(win=float((r == 1).mean()), loss=float((r == -1).mean()),
                    cut=float((r == 0).mean()), **hp.of(which))

    sides = [e.report() for e in events]
    more = {}
    if fold is not None:
        # Each number without one group of the matches (the events of the others merged).
        without = []
        for k in range(folds):
            w = top(fold != k)
            w['sides'] = []
            for s in range(2):
                rest = Events(events[s].char)
                for j in range(folds):
                    if j != k:
                        rest.merge(parts[s][j])
                w['sides'].append(rest.report())
            without.append(w)
        more['se'] = dict(folds=folds, **spread(dict(top(slice(None)), sides=sides), without))
    # Each match, for a count of its own outside (a bootstrap, a paired comparison).
    more['per_match'] = [dict(result=int(result[i]), rounds_won=int(rounds_won[i]),
                              taken=[round(float(x), 4) for x in taken[i]],
                              lost=[round(float(x), 4) for x in lost[i]],
                              steps=len(seen[0][i])) for i in range(matches)]
    return dict(**(dict(detail=detail) if habits is not None and
                   getattr(args, 'detail', False) else {}), win=float((result == 1).mean()), loss=float((result == -1).mean()),
                cut=float((result == 0).mean()), matches=matches, **hp.of(slice(None)),
                sides=sides, **more,
                **(dict(cpu_combos=dict(level=hybrid, agent_steps=round(handed['agent'] / max(1, handed['steps']), 4),
                                        turns_a_match=round(handed['times'] / matches, 2)))
                   if hybrid else {}),
                by_tier=_by_tier(result, chars_played, hp) if p2 == 'cpu' and level == 4 else {},
                by_opponent=_by_opponent(result, chars_played),
                hp_by_opponent=_hp_by_opponent(chars_played, hp),
                **(dict(by_set_match=[dict(match=k + 1, win=float((result[sl] == 1).mean()),
                                           **hp.of(sl))
                                      for k in range(legs)
                                      for sl in [slice(k * (total // legs), (k + 1) * (total // legs))]])
                   if legs > 1 else {}))


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
    p.add_argument('--p2', default='cpu',
                   help="'cpu', a model.zip, or an agent file (.efzagent: played by the game's "
                        "own code with its modules, as --p1-native plays P1's: one build "
                        "against another)")
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
    p.add_argument('--p2-delay', type=int,
                   help="P2 (a model.zip) sees the game this many steps late, instead of its "
                        "config's: an opponent with the agent's reaction")
    p.add_argument('--json', help='write the results here')
    p.add_argument('--p2-advantage', help="a red team's advantages for P2 (advantages.py), e.g. "
                                          "rg=0.5,reversal=0.8,throw=0.3,damage=2,bait=0.5")
    p.add_argument('--p1-combo', help="combo_support.ComboSwitch: P1's combos played by this "
                                      "model (combo.py's combo master)")
    p.add_argument('--p1-combo-deterministic', action='store_true',
                   help="--p1-combo's likeliest action (combo_net.py's network: a route "
                        "learnt is played, not drawn from)")
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
    p.add_argument('--assist-ending', type=float, default=0.0, metavar='HP',
                   help="--p1-assist: what a knockdown at a combo's end is worth over any other "
                        "end, and the copies' victim recovers in the air when it can "
                        "(redteam.Planner's ending)")
    p.add_argument('--assist-per-start', type=int, default=12,
                   help="--p1-assist: the library combos tried at a hit")
    p.add_argument('--assist-replan', action='store_true',
                   help="--p1-assist plans again at each new move's hit P1 sees, the combos "
                        "joined where that move hit in them (the library's marks: "
                        "combo_library.py --marks)")
    p.add_argument('--assist-chooser', metavar='CHOOSER.pt',
                   help="--p1-assist's choice by combo_net.py's chooser (from P1's view when "
                        "it sees its hit) instead of on copies of the game")
    p.add_argument('--assist-margin', type=float, default=200.0,
                   help="--assist-chooser: the HP a combo must promise over P1's own play")
    p.add_argument('--p1-untold', action='store_true',
                   help="a P1 that is told P2's habits (finetune.py --tell) plays without "
                        "being told")
    p.add_argument('--sets', type=int, default=1, metavar='N',
                   help="the matches in sets of N against the same opponent (--matches / N "
                        "sets): P2's habits (--p2-advantage ...,habits=1) are a set's, and an "
                        "agent with a match memory keeps it over the set; the results also "
                        "by the match's number in its set (by_set_match)")
    p.add_argument('--detail', action='store_true',
                   help="with --p2-advantage: each match's result, P2's habits in it "
                        "(advantages.told()) and P1's knockdowns and guarded attacks (tactics.py's "
                        "records), in the results' detail")
    p.add_argument('--p1-module', action='append', default=[], metavar='KIND:key=value,...',
                   help="a module of P1 (python/efz_env/modules.py; the kinds: "
                        "agent_modules.py), asked after --p1-assist's routes and those "
                        "named before it; a value that is a file's path is one of its files")
    p.add_argument('--folds', type=int, default=16, metavar='K',
                   help="every number's standard error, by the jackknife over K groups of the "
                        "matches (the result's `se`: the same tree, an error where the number "
                        "is; 0: none). A difference between two results is real past two or "
                        "three of them, not before")
    p.add_argument('--p2-cpu-combos', type=int, default=0, metavar='LEVEL',
                   help="P2 is the game's CPU at this level (1-4) except while P1 is in a hit "
                        "reaction, when --p2 (an agent) plays: the CPU's neutral, guard and "
                        "recoil guards with an agent's combos")
    p.add_argument('--p1-plan-budget', metavar='COST[,OWN]',
                   help="with --p1-native: the work a combo's plan may take before it is due, "
                        "in frames on copies (one of its own play's counts OWN, 15), where an "
                        "evaluation otherwise works every plan to its end: the game on a "
                        "machine with that much time (the user's, 16-19 November: 7700,27)")
    p.add_argument('--p1-plan-drop', action='store_true',
                   help="with --p1-plan-budget: a plan not done when due is dropped whole "
                        "(the game before 19 November), not chosen from the options played")
    p.add_argument('--p1-native', action='store_true',
                   help="--p1 is an agent file, played by the game's own code (port/agent: "
                        "its routes and planned okizeme as the file has them): native_agent.py")
    args = p.parse_args()
    if args.p1_native:
        if args.p1_combo or args.p1_lookahead or args.p1_assist or args.p1_module:
            p.error("--p1-native plays the file's own modules: none of --p1-combo, "
                    "--p1-lookahead, --p1-assist, --p1-module")
        import native_agent
        budget = None
        if args.p1_plan_budget:  # COST[,OWN]: the routes' plans as a machine with that much time
            parts = [int(x) for x in args.p1_plan_budget.split(',')]
            budget = (parts[0], not args.p1_plan_drop, parts[1] if len(parts) > 1 else 15)
        p1 = native_agent.NativePlayers(args.p1, args.deterministic, budget=budget)
    else:
        p1 = make_agent(args.p1, args.deterministic, args.p1_delay)
    if sum(bool(x) for x in (args.p1_combo, args.p1_lookahead, args.p1_assist)) > 1:
        p.error('one of --p1-combo, --p1-lookahead, --p1-assist')
    if args.p1_combo or args.p1_lookahead or args.p1_assist:
        import combo_support
        if args.p1_assist:
            import macros
            import redteam
            if args.assist_chooser:  # (no copies of the game: the chooser says)
                import combo_net
                planner = combo_net.NetPlanner(combo_net.load_routes(args.p1_assist), p1.model,
                                               args.assist_chooser, margin=args.assist_margin)
            else:
                planner = redteam.Planner(args.data, macros.load_library(args.p1_assist),
                                          p1.model, score=args.assist_score,
                                          victims=args.assist_victims,
                                          per_start=args.assist_per_start,
                                          replan=args.assist_replan,
                                          ending=args.assist_ending)
            p1 = combo_support.FairComboAgent(p1, planner)
        if args.p1_lookahead:
            p1 = combo_support.lookahead(args.data, args.p1, args.p1_lookahead)
        if args.p1_combo:
            p1 = combo_support.ComboSwitch(
                p1, make_agent(args.p1_combo, args.deterministic or args.p1_combo_deterministic),
                args.p1_confirm)
    if args.p1_module:
        from efz_env import modules
        import agent_modules  # noqa: F401  (the kinds)
        if args.p1_combo or args.p1_lookahead:
            p.error('--p1-module: not with --p1-combo or --p1-lookahead')
        base = p1.agent if isinstance(p1, modules.ModularAgent) else p1
        more = modules.build(base, [modules.parse_spec(m) for m in args.p1_module], 'batch',
                             data=args.data)
        if isinstance(p1, modules.ModularAgent):
            p1.stack = modules.Stack(p1.modules + more)
        else:
            p1 = modules.ModularAgent(p1, more)
    if args.p2.endswith('.efzagent'):  # an agent file: the game's own code plays it
        import native_agent
        p2 = native_agent.NativePlayers(args.p2, args.deterministic, seed=1)
    else:
        p2 = 'cpu' if args.p2 == 'cpu' else make_agent(args.p2, args.deterministic, args.p2_delay)
    if args.p2_advantage:
        import advantages
        if p2 == 'cpu' or args.chars[1] in ('random', 'tiers'):
            p.error('--p2-advantage: P2 an agent, of one character')
        p2 = advantages.AdvantagedAgent(p2, args.chars[1], advantages.parse(args.p2_advantage),
                                        learner=args.chars[0])
    out = {}
    for level in (args.level if p2 == 'cpu' else [0]):
        r = play(args, p1, p2, args.matches, level, seed=args.seed)
        key = f'cpu{level}' if p2 == 'cpu' else 'vs'
        out[key] = r
        print(key, json.dumps({k: v for k, v in r.items()
                               if k not in ('by_opponent', 'hp_by_opponent', 'sides', 'by_tier',
                                            'detail', 'se', 'per_match')}),
              flush=True)
        if r['by_tier']:
            print('  by tier:', ', '.join(f"{t} {v['win']:.0%} of {v['matches']} (HP taken a round "
                                          f"{v['opp_hp_taken']:.0%}, its own lost "
                                          f"{v['self_hp_taken']:.0%}, rounds {v['rounds_won']:.2f})"
                                          for t, v in r['by_tier'].items()), flush=True)
    if args.p2_advantage:  # what its advantages did
        out['p2_advantage'] = dict(advantages.parse(args.p2_advantage), **p2.logic.take())
        print('p2 advantage', json.dumps(out['p2_advantage']), flush=True)
    if args.p1_assist:  # its plans: how many, the share a route won, the damage options made
        out['assist'] = dict(p1.assist.take_plans(), score=args.assist_score,
                             changed=planner.changed, victims=args.assist_victims,
                             chooser=args.assist_chooser, per_start=args.assist_per_start,
                             replan=args.assist_replan, ending=args.assist_ending,
                             endings=getattr(planner, 'endings', None))
        print('assist', json.dumps(out['assist']), flush=True)
    if args.p1_module:  # what each module did, and the share of P1's decisions it made
        out['modules'] = p1.stats()
        print('modules', json.dumps(out['modules']), flush=True)
    if args.p1_native:  # the game's planners: plans made, dropped, their time
        out['native'] = p1.stats()
        print('native', json.dumps(out['native']), flush=True)
        p1.close()
    if args.p2.endswith('.efzagent'):
        out['native_p2'] = getattr(p2, 'agent', p2).stats()
        getattr(p2, 'agent', p2).close()
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
