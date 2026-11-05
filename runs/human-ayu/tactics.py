"""Tactics, measured from a player's views of a match, both ways (one's own and the
opponent's): pressure, wake-up and free time. evaluate.py's Events reports them.

Pressure (pressure()): the defender's guard, in runs (its blockstun, RG included), each
with its contacts (the guard pattern restarting). After a run, the frame advantage: the
step the defender is free (its guard ends) minus the step the attacker is (free, or
acting again, after the move that made the last contact): plus, the attacker acts first.
A minus guard matters only if the defender can use it (the user's): it is punishable if
the defender has a move whose startup is within the disadvantage and whose attack boxes
reach (framedata.json, the game's own frame data); else the attacker is safe, and gained
power from the guard. What came next, the first within AFTER steps: another guard (the
pressure goes on; the gap is the steps the defender was free between), the attacker's
hit, the defender's (it fought back), else a reset. The defender's ways out of it (the
user's: invincible moves and the like): what it started after the guard (escape():
an invincible move, invulnerable in its first frames, a reversal; another move, a mash;
a jump; a backdash) and how each went, and RG.

Wake-up (wakeup()): each knockdown, the riser's choice (guard, wait, rising attack,
escape()) and how it went (who hit first, the HP swing over 3 s), and the attacker's
setup: frames free before the rise, in a move as it rose (meaty), airborne, close, the
steps to the first contact, objects out (traps, projectiles).

Free time (free_time()): the runs of steps in which a player is free and the opponent
isn't (in a guard, a hit, a knockdown, a move's recovery): the usable advantage, and
what was done with it: a setup (a move that put an object out: a trap, a projectile,
the way Mizuka and Misuzu play, the user's), a charge (a move that builds a resource
of the character's own: Kano's magic, CHARGE), another move, closing in, or waiting.
"""

import functools
import json
import os

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))

# The observation's columns these read (evaluate.py appends them to its COLUMNS):
# self_/opp_ action, action_frame, hitstun, airborne, invulnerable (a timer some moves
# set), character, gauge (/ 3000), hp (/ 9999); intro, round_over, dx (/ 640); then
# self's and opp's 8 objects' active.
OBS = [18, 50, 19, 51, 20, 52, 39, 71, 25, 57, 34, 66, 9, 41, 8, 40, 2, 3, 4] + \
    [72 + 6 * k for k in range(8)] + [120 + 6 * k for k in range(8)]

# src/efz.h's common actions.
FREE = [0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xe, 0xf, 0x10]  # stand, walk,
#   crouch, jump, fall, air jump: free to do anything (landing 0xd isn't)
BLOCKING = [0x2, 0x3, 0x8]  # walking back, crouching: holding a guard
GUARDS = list(range(0x96, 0x9d)) + [0xa8, 0xa9, 0xaa]  # guards, air guard, RG
RG = [0xa8, 0xa9, 0xaa]
DOWN = [0x60, 0x61, 0x62, 0x63]  # wake-up, the two knockdowns, lying
WAKEUP_ATTACK = 0xa2             # rising with an attack (1000 power)
DASH, BACKDASH = 0xa3, 0xa4
FIRST_OWN = 0xc8                 # the character's own moves
FIRST_OBJECT = 0x190             # patterns from here are its objects'

AFTER = 64        # steps after a guard ends in which what came next is looked for
STRING_GAP = 24   # the guards of a blockstring: at most this many steps apart
WAKE_CHOICE = 16  # steps after rising in which the riser's choice is looked for
WAKE_RESULT = 96  # ... and who hits first
VALUE = 192       # ... and the HP each loses in this many (3 s)
PLUS, MINUS = 2, -2  # frame advantage bins: plus (>= 2), even, minus (<= -2)
REACH_MARGIN = 25    # pixels: the target's body beyond its position
CLOSE = 100          # pixels
ESCAPES = ('invincible', 'move', 'jump', 'backdash', 'dash')
# Per character, the moves that build a resource of its own (src/efz.h): Kano's 5D
# (0xfa, chants, filling m_chargeGauge) and 236D (0xfb, RF gauge into it).
CHARGE = {'kano': [0xfa, 0xfb]}


def _prev(x, fill):
    return np.concatenate([[fill], x[:-1]])


def _runs(mask):
    """Starts and ends (exclusive) of the runs of True."""
    d = np.diff(np.concatenate([[0], mask.astype(np.int8), [0]]))
    return np.flatnonzero(d == 1), np.flatnonzero(d == -1)


def _first(x, lo, hi):
    """The first index in [lo, hi) where x is True, or None."""
    hi = min(hi, len(x))
    if lo >= hi:
        return None
    k = np.flatnonzero(x[lo:hi])
    return lo + int(k[0]) if len(k) else None


@functools.lru_cache(maxsize=None)
def names():
    try:
        from efz_env.vec import character_names
        return character_names()
    except Exception:  # no library here: the game's order (kCharacterNames)
        return ['nanase', 'ayu', 'mai', 'makoto', 'akane', 'mayu', 'nagamori', 'misaki',
                'shiori', 'sayuri', 'nayuki', 'mio', 'exnanase', 'kaori', 'ikumi', 'mishio',
                'akiko', 'nayukib', 'mizukab', 'kanna', 'kano', 'minagi', 'nayuki2',
                'misuzu', 'mizuka']


@functools.lru_cache(maxsize=None)
def frame_data():
    """Per character number: (its invincible moves, its punishers [(startup, reach)]:
    the ground moves it can start on its own, normals and specials), from
    framedata.json (framedata.py); {} without it."""
    path = os.path.join(HERE, 'framedata.json')
    if not os.path.exists(path):
        return {}
    data = json.load(open(path))
    out = {}
    for c, name in enumerate(names()):
        moves = data.get(name)
        if moves is None:
            continue
        inv = {int(k, 16) for k, m in moves.items() if m['invincible']}
        punish = sorted((m['startup'], m['reach']) for k, m in moves.items()
                        if int(k, 16) < FIRST_OBJECT and m['startup'] and
                        (10 <= m['level'] <= 30 or m['level'] == 50))
        out[c] = (inv, punish)
    return out


class Side:
    """One player's columns over a match (k: 0 the viewer, 1 the opponent)."""

    def __init__(self, c, k):
        self.act = np.round(c[:, k]).astype(int)
        self.frame = np.round(c[:, 2 + k]).astype(int)
        stun = c[:, 4 + k] > 0
        self.hit = stun & ~_prev(stun, False)  # a hit reaction starts
        self.air = c[:, 6 + k] > 0
        self.inv_timer = c[:, 8 + k] > 0
        self.char = int(round(float(c[0, 10 + k])))
        self.gauge = c[:, 12 + k] * 3000
        self.hp = c[:, 14 + k] * 9999
        self.objects = (c[:, 19 + 8 * k:27 + 8 * k] > 0).sum(1)
        self.new = self.act != _prev(self.act, -1)
        self.free = np.isin(self.act, FREE)
        self.move = self.new & (self.act >= FIRST_OWN)
        jump = self.air & ~_prev(self.air, False)
        self.acts = (self.new & ((self.act >= FIRST_OWN) | np.isin(self.act, [DASH, BACKDASH]))) | jump
        self.guard = np.isin(self.act, GUARDS)
        # A contact on its guard: a guard starts, or restarts (its frame goes back).
        self.contact = self.guard & (~_prev(self.guard, False) | self.new |
                                     (self.frame < _prev(self.frame, 0)))
        self.inv_moves, self.punishers = frame_data().get(self.char, (set(), []))
        name = names()[self.char] if 0 <= self.char < len(names()) else ''
        self.charge_moves = set(CHARGE.get(name, []))

    def escape(self, t):
        """What it started at step t: 'invincible' (a move invulnerable in its first
        frames by the frame data, or by its invulnerability timer: a reversal), 'move'
        (any other: a mash), 'jump', 'backdash', 'dash', or None."""
        a = self.act[t]
        if self.new[t] and a >= FIRST_OWN:
            inv = a in self.inv_moves or self.inv_timer[t:t + 8].any()
            return 'invincible' if inv else 'move'
        if self.new[t] and a == BACKDASH:
            return 'backdash'
        if self.new[t] and a == DASH:
            return 'dash'
        if self.air[t] and (t == 0 or not self.air[t - 1]):
            return 'jump'
        return None

    def can_punish(self, frames, distance):
        """A move of its own as fast as `frames` that reaches `distance` pixels."""
        return any(s <= frames and r + REACH_MARGIN >= distance for s, r in self.punishers)


def pressure(att, dfn, dx, live):
    """The attacker's guarded moves: a dict per run of the defender's guard."""
    T = len(att.act)
    out = []
    starts, ends = _runs(dfn.guard)
    for b, e in zip(starts, ends):
        if e >= T or not live[b:min(T, e + AFTER)].all():
            continue
        contacts = np.flatnonzero(dfn.contact[b:e]) + b
        last = int(contacts[-1]) if len(contacts) else b
        moves = np.flatnonzero(att.move[max(0, b - 60):last + 1])
        if not len(moves):
            continue  # (no move of the attacker's: nothing to measure from)
        m0 = max(0, b - 60) + int(moves[-1])
        free = _first(att.free, m0 + 1, e + 120)
        again = _first(att.acts, last + 1, e + 120)  # acting again after the last contact
        f = min(x for x in (free, again) if x is not None) if (free or again) else None
        if f is None:
            continue
        adv = e - f
        dist = float(abs(dx[e]) * 640)
        nxt = {k: _first(x, e, e + AFTER) for k, x in
               (('guard', dfn.contact), ('hit', dfn.hit), ('fought_back', att.hit))}
        nxt = {k: v for k, v in nxt.items() if v is not None}
        what = min(nxt, key=nxt.get) if nxt else 'reset'
        end = nxt[what] if nxt else e + AFTER
        t = _first(dfn.acts, e, end + 1)
        out.append(dict(
            adv=int(adv), next=what, gap=int(nxt['guard'] - e) if what == 'guard' else -1,
            escape=(dfn.escape(t) or '') if t is not None else '',
            move=int(att.act[m0]), contacts=int(max(1, len(contacts))),
            rg=bool(np.isin(dfn.act[b:e], RG).any()), distance=round(dist),
            power=float(att.gauge[e] - att.gauge[max(0, b - 1)]),
            punishable=bool(adv <= MINUS and not dfn.air[e] and dfn.can_punish(-adv, dist)),
            setup=bool(att.objects[min(T - 1, end)] > att.objects[e])))
    return out


def wakeup(dfn, att, dx, live):
    """The defender's knockdowns: a dict per knockdown it rose from."""
    T = len(dfn.act)
    guard_in = dfn.guard & ~_prev(dfn.guard, False)
    out = []
    starts, ends = _runs(np.isin(dfn.act, DOWN))
    for s, w in zip(starts, ends):
        if w + VALUE >= T or not live[s:w + VALUE].all() or 0x32 <= dfn.act[w] < 0x96:
            continue  # the round ends, or it is hit lying (a knockdown again)
        if dfn.act[w] == WAKEUP_ATTACK:
            choice = 'wakeup_attack'
        else:
            choice, upto = None, min(T, w + WAKE_CHOICE)
            for t in range(w, upto):
                choice = dfn.escape(t)
                if choice or guard_in[t] or dfn.hit[t]:
                    upto = t + 1
                    break
            if choice is None:
                choice = 'guard' if (guard_in[w:upto].any() or
                                     np.isin(dfn.act[w:upto], BLOCKING).any()) else 'wait'
        h = _first(dfn.hit, w, w + WAKE_RESULT)
        k = _first(att.hit, w, w + WAKE_RESULT)
        result = 'attacker' if h is not None and (k is None or h < k) else \
            'defender' if k is not None else 'none'
        swing = (dfn.hp[w] - dfn.hp[w + VALUE]) - (att.hp[w] - att.hp[w + VALUE])
        f = _first(att.free, s, w + 1)
        contact = _first(guard_in | dfn.hit, w, w + WAKE_RESULT)
        out.append(dict(choice=choice, result=result, swing=float(swing),
                        setup_frames=int(w - f) if f is not None else -1,
                        meaty=bool(att.act[w] >= FIRST_OWN), airborne=bool(att.air[w]),
                        distance=round(float(abs(dx[w]) * 640)),
                        contact=int(contact - w) if contact is not None else -1,
                        objects=int(att.objects[w])))
    return out


def free_time(me, opp, dx, live):
    """The runs of steps in which `me` is free and `opp` isn't: a dict each (its length,
    what `me` did with it)."""
    T = len(me.act)
    out = []
    starts, ends = _runs(me.free & ~opp.free & live)
    for b, e in zip(starts, ends):
        if e >= T - 30:
            continue
        if me.move[e] and me.act[e] in me.charge_moves:
            use = 'charge'
        elif me.acts[e] and me.move[e]:
            spawned = me.objects[e:e + 30].max() > me.objects[e]
            use = 'setup' if spawned else 'move'
        elif me.acts[e]:
            use = 'move'  # a jump, a dash
        elif abs(dx[e]) * 640 < abs(dx[b]) * 640 - 16:
            use = 'close_in'
        else:
            use = 'wait'
        out.append(dict(frames=int(e - b), use=use, objects=int(me.objects[e])))
    return out


def measure(c):
    """Both ways, for one player's match: c, its views' OBS columns (T, len(OBS))."""
    c = np.asarray(c, np.float32)
    me, opp = Side(c, 0), Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    dx = c[:, 18]
    return dict(press_off=pressure(me, opp, dx, live), press_def=pressure(opp, me, dx, live),
                oki_off=wakeup(opp, me, dx, live), oki_def=wakeup(me, opp, dx, live),
                free_self=free_time(me, opp, dx, live), free_opp=free_time(opp, me, dx, live))


# Reports.

def _mean(x):
    return round(float(np.mean(x)), 3) if len(x) else None


def pressure_report(recs, per_min, moves=False):
    if not recs:
        return None
    adv = np.array([r['adv'] for r in recs], float)
    what = np.array([r['next'] for r in recs])
    kind = np.array([r['escape'] for r in recs])
    gap = np.array([r['gap'] for r in recs], float)
    rg = np.array([r['rg'] for r in recs])
    pun = np.array([r['punishable'] for r in recs])
    power = np.array([r['power'] for r in recs], float)
    strings = 1 + sum(1 for a in recs[:-1] if not (a['next'] == 'guard' and 0 <= a['gap'] <= STRING_GAP))
    plus, minus = adv >= PLUS, adv <= MINUS

    def shares(mask):
        n = int(mask.sum())
        return dict(n=n, **{k: round(float((what[mask] == k).mean()), 3) if n else None
                            for k in ('guard', 'hit', 'fought_back', 'reset')})
    out = dict(guards_per_min=round(len(recs) * per_min, 2),
               strings_per_min=round(strings * per_min, 2),
               guards_per_string=round(len(recs) / strings, 2),
               contacts_per_guard=round(float(np.mean([r['contacts'] for r in recs])), 2),
               advantage=round(float(np.median(adv)), 1),
               plus=_mean(plus), minus=_mean(minus),
               # minus that the defender could use, and what it did; the rest is safe
               punishable=_mean(pun),
               next=shares(np.ones(len(recs), bool)),
               next_when_plus=shares(plus),
               next_when_even=shares(~plus & ~minus),
               next_when_punishable=shares(pun),
               next_when_minus_safe=shares(minus & ~pun),
               power_per_guard=round(float(power.mean()), 1),
               setup_when_plus=_mean([r['setup'] for r, p in zip(recs, plus) if p]))
    cont = what == 'guard'
    if cont.any():
        out['gap'] = round(float(np.median(gap[cont])), 1)
        out['gap_tight'] = _mean(gap[cont] <= 3)
    # The defender's ways out: what it started after a guard (escape()), and RG.
    out['escapes'] = {}
    for k in ESCAPES + ('',):
        m = kind == k
        if m.any():
            out['escapes'][k or 'none'] = dict(
                share=_mean(m), n=int(m.sum()),
                escaped=_mean(what[m] == 'fought_back'), trapped=_mean(what[m] == 'hit'),
                when_minus=_mean(adv[m] <= MINUS))
    # RG and what came of it (the user's: RG and a move after it turn the pressure):
    # the advantage after it (the attacker's: minus, the defender acts first), what
    # the defender did, and how that went.
    out['rg'] = _mean(rg)
    if rg.any():
        out['after_rg'] = shares(rg)
        out['rg_advantage'] = round(float(np.median(adv[rg])), 1)
        out['rg_then'] = {}
        for k in ESCAPES + ('',):
            m = rg & (kind == k)
            if m.any():
                out['rg_then'][k or 'none'] = dict(
                    share=round(float(m.sum() / rg.sum()), 3), n=int(m.sum()),
                    escaped=_mean(what[m] == 'fought_back'), trapped=_mean(what[m] == 'hit'))
    if moves:
        by = {}
        for r in recs:
            by.setdefault(r['move'], []).append(r)
        top = sorted(by.items(), key=lambda kv: -len(kv[1]))[:12]
        out['moves'] = {hex(m): dict(n=len(rs), advantage=float(np.median([r['adv'] for r in rs])),
                                     punishable=_mean([r['punishable'] for r in rs]),
                                     fought_back=_mean([r['next'] == 'fought_back' for r in rs]))
                        for m, rs in top}
    return out


def wakeup_report(recs, per_min):
    if not recs:
        return None
    choice = np.array([r['choice'] for r in recs])
    result = np.array([r['result'] for r in recs])
    swing = np.array([r['swing'] for r in recs], float)
    c = [r['contact'] for r in recs if r['contact'] >= 0]
    out = dict(per_min=round(len(recs) * per_min, 2),
               value=round(float(swing.mean())),  # the HP swing for the attacker
               result={k: _mean(result == k) for k in ('attacker', 'defender', 'none')},
               setup_frames=round(float(np.median([r['setup_frames'] for r in recs])), 1),
               meaty=_mean([r['meaty'] for r in recs]),
               airborne=_mean([r['airborne'] for r in recs]),
               close=_mean([r['distance'] <= CLOSE for r in recs]),
               objects=_mean([r['objects'] > 0 for r in recs]),
               contact=_mean([r['contact'] >= 0 for r in recs]),
               contact_frames=round(float(np.median(c)), 1) if c else None)
    out['choices'] = {}
    for k in ('guard', 'wait', 'wakeup_attack') + ESCAPES:
        m = choice == k
        if m.any():
            out['choices'][k] = dict(share=_mean(m), n=int(m.sum()),
                                     hit=_mean(result[m] == 'attacker'),
                                     hit_back=_mean(result[m] == 'defender'),
                                     value=round(float(swing[m].mean())))
    return out


def free_report(recs, per_min):
    if not recs:
        return None
    frames = np.array([r['frames'] for r in recs], float)
    use = np.array([r['use'] for r in recs])
    out = dict(windows_per_min=round(len(recs) * per_min, 2),
               frames_per_min=round(float(frames.sum()) * per_min),
               frames=round(float(np.median(frames)), 1),
               objects_out=_mean([r['objects'] > 0 for r in recs]))
    for k in ('setup', 'charge', 'move', 'close_in', 'wait'):
        m = use == k
        out[k] = dict(share=_mean(m), frames=round(float(np.median(frames[m])), 1) if m.any() else None)
    return out


def report(n, per_min):
    """Events' lists (measure()'s, concatenated) -> its report's entries."""
    return dict(pressure=pressure_report(n['press_off'], per_min, moves=True),
                under_pressure=pressure_report(n['press_def'], per_min),
                okizeme=wakeup_report(n['oki_off'], per_min),
                wakeup=wakeup_report(n['oki_def'], per_min),
                free_time=free_report(n['free_self'], per_min),
                opponent_free_time=free_report(n['free_opp'], per_min))
