"""Tactics, measured from a player's views of a match, both ways (one's own and the
opponent's): pressure, wake-up, strings and free time. evaluate.py's Events reports them.

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
steps to the first contact, objects out (traps, projectiles); its okizeme (the move it
was in or started first, and how often it pressed it again) and the mix-up that was
(how it came in: ground, 66, flying, jumping; low, high or either way; a cross-up).

Strings (strings(), with the player's inputs): its moves one after another (gatlings,
links, a jump-in and a landing move), each move one a button press made, and how each
string went (hit, guarded, whiffed; punished after a guard), from what (the opponent
free, guarding, hit): how varied a player's offence is (the user's: an agent that plays
one string again and again).

Free time (free_time()): the runs of steps in which a player is free and the opponent
isn't (in a guard, a hit, a knockdown, a move's recovery): the usable advantage, and
what was done with it: a setup (a move that put an object out: a trap, a projectile,
the way Mizuka and Misuzu play, the user's), a charge (a move that builds a resource
of the character's own: Kano's magic, CHARGE), another move, closing in, or waiting.
"""

import collections
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
AIRDASH = [0xa5, 0xa6]           # forward, back (Ayu's flight)
FIRST_OWN = 0xc8                 # the character's own moves
FIRST_OBJECT = 0x190             # patterns from here are its objects'

AFTER = 64        # steps after a guard ends in which what came next is looked for
STRING_GAP = 24   # the guards of a blockstring: at most this many steps apart
WAKE_CHOICE = 16  # steps after rising in which the riser's choice is looked for
WAKE_RESULT = 96  # ... and who hits first
APPROACH = 60     # steps before the attacker's move in which how it came in is looked for
LINK_GAP = 6      # a string: its moves at most this many steps free apart
PUNISH = 40       # steps after a guarded string in which a hit back is its punishment
BUTTONS = 0xf0    # A B C D in a control byte
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


@functools.lru_cache(maxsize=None)
def guards():
    """Per character number: {move: how it is guarded ('low', 'high', 'mid',
    'unguardable')}, from framedata.json; {} without it (or before its guard field)."""
    path = os.path.join(HERE, 'framedata.json')
    if not os.path.exists(path):
        return {}
    data = json.load(open(path))
    return {c: {int(k, 16): m['guard'] for k, m in data[name].items() if m.get('guard')}
            for c, name in enumerate(names()) if name in data}


class Side:
    """One player's columns over a match (k: 0 the viewer, 1 the opponent)."""

    def __init__(self, c, k):
        self.act = np.round(c[:, k]).astype(int)
        self.frame = np.round(c[:, 2 + k]).astype(int)
        stun = c[:, 4 + k] > 0
        self.hitstun = stun
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
        self.heights = guards().get(self.char, {})
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
            escape_move=hex(int(dfn.act[t])) if t is not None and dfn.escape(t) in
            ('invincible', 'move') else '',
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
        # The attacker's okizeme: the move it was in as the defender rose (a meaty), else
        # what it started first within WAKE_CHOICE steps (a move, a jump, a dash), else
        # 'none' (it waited, walked or guarded); and how many times it started that move
        # again before the result window ended (pressing it over and over).
        if att.act[w] >= FIRST_OWN:
            oki = hex(int(att.act[w]))
            m0 = int(np.flatnonzero(att.new[:w + 1])[-1])  # where it started
        else:
            m0 = _first(att.acts, w + 1, w + WAKE_CHOICE)
            oki = 'none' if m0 is None else (
                hex(int(att.act[m0])) if att.act[m0] >= FIRST_OWN else
                'backdash' if att.act[m0] == BACKDASH else
                'dash' if att.act[m0] == DASH else 'jump')
        again = 0
        if oki.startswith('0x'):
            a = int(oki, 16)
            again = int((att.new[m0 + 1:w + WAKE_RESULT] & (att.act[m0 + 1:w + WAKE_RESULT] == a)).sum())
        # The mix-up it was (the user's, for Ayu: a 2A, low; 66 into an air B or a 2A,
        # up or down; flying in (an air dash) and dropping with jB, in front or behind):
        # the move that made the first contact (else the okizeme move), how it is guarded
        # (frame data), how the attacker came in (fly: an air dash; dash: 66; jump: a jump
        # or a move started in the air; else ground) and whether it struck from the other
        # side than the riser rose to (a cross-up). 'none': no move of its own.
        mix, t = 'none', contact if contact is not None else (m0 if oki.startswith('0x') else None)
        starts = np.flatnonzero(att.move[s:t + 1]) if t is not None else []
        if len(starts):
            b = s + int(starts[-1])
            lo = max(s, b - APPROACH)
            seen = att.act[lo:b + 1]
            way = ('fly' if np.isin(seen, AIRDASH).any() else
                   'dash' if (seen == DASH).any() else
                   'jump' if att.air[b] or (att.air[lo + 1:b + 1] & ~att.air[lo:b]).any() else
                   'ground')
            height = att.heights.get(int(att.act[b]), 'mid')
            height = 'throw' if height == 'unguardable' else height
            crossed = dx[w] != 0 and dx[t] != 0 and np.sign(dx[w]) != np.sign(dx[t])
            mix = f'{way} {height}' + (' cross' if crossed else '')
        out.append(dict(choice=choice, result=result, swing=float(swing), oki=oki,
                        oki_again=again, mix=mix,
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


def strings(me, opp, live, controls):
    """`me`'s strings: its moves one after another, each within LINK_GAP free steps of
    the last (a gatling, a link, a jump-in and a landing move), a dict each: the moves (a
    move is a start of its own that a button press made since the last: a follow-up of
    one, 236A's ending, a throw's hit, is the same move), what the opponent was doing at
    the first (free, guard, hit, down, busy), and how it went (hit: the opponent was hit
    during it; guarded; whiff), and for a guarded one whether the opponent hit back
    within PUNISH steps of its last move."""
    T = len(me.act)
    c = np.asarray(controls, np.int64)
    press = (c & BUTTONS & ~_prev(c, 0) & BUTTONS) != 0
    pressed = np.cumsum(press)  # presses up to and including each step
    out, cur, last = [], None, -1
    free_run = 0
    ostate = np.where(opp.guard, 1, np.where(opp.hitstun, 2, np.where(np.isin(opp.act, DOWN), 3,
                      np.where(opp.free, 0, 4))))
    names = ('free', 'guard', 'hit', 'down', 'busy')

    def close(st):
        if st is None:
            return
        b, e = st['t0'], min(T, st['t1'] + 1)
        hit = bool(opp.hit[b:e + 8].any())
        guarded = bool(opp.contact[b:e + 8].any())
        how = 'hit' if hit else 'guarded' if guarded else 'whiff'
        free = _first(me.free, st['t1'], min(T, st['t1'] + 120))
        back = how == 'guarded' and free is not None and \
            _first(me.hit, st['t1'], min(T, free + PUNISH)) is not None
        out.append(dict(moves='-'.join(hex(int(a)) for a in st['moves']), start=names[st['opp']],
                        how=how, punished=bool(back)))
    for t in range(T):
        if me.free[t]:
            free_run += 1
            if cur is not None and free_run > LINK_GAP:
                close(cur)
                cur = None
            continue
        if me.move[t] and live[t] and (last < 0 or pressed[t] > pressed[last]):
            if cur is None:
                cur = dict(t0=t, moves=[], opp=int(ostate[t]))
            cur['moves'].append(int(me.act[t]))
            cur['t1'] = t
            last = t
        if not me.free[t]:
            free_run = 0
        if cur is not None and (me.hitstun[t] or not live[t]):  # it was hit, or the round ended
            close(cur)
            cur = None
    close(cur)
    return out


THROWN = list(range(0x64, 0x7a))  # the poses a throw puts its victim in
AIR_RECOVERY = (0x9d, 0x9e)       # recovering in the air from a hit, forward and back
LYING = (0x61, 0x62, 0x63)
THROW = 0xdc                      # every character's throw; + 1: it caught
AIR_THROW_F0 = ('ayu', 'mai', 'akane', 'akiko')  # their air throw is 0xf0, the others' 0xf8
ENDINGS = ('knockdown', 'recovery', 'standing', 'ko')
BIG = 1000                        # HP: a combo worth ending well
AFTER_END = 150                   # steps after an air recovery in which who hits first is looked for


def endings(att, dfn, live):
    """How att's combos on dfn end, a record each: the HP it took and where it left dfn:
    'knockdown' (lying, to rise into att's okizeme), 'recovery' (dfn recovered in the
    air: untech time ran out before the ground, and dfn is free to act), 'standing' (a
    ground hit's stun ran out), 'ko'. For a recovery also whether att was still in a move
    of its own (busy) and who was hit first after it (next: 'caught', 'hit back',
    'guarded', 'nothing')."""
    T = len(dfn.act)
    react = ((dfn.act >= 0x32) & (dfn.act < 0x60)) | np.isin(dfn.act, THROWN)
    lying = np.isin(dfn.act, LYING)
    starts = np.flatnonzero(react & ~_prev(react, False))
    out, k = [], 0
    while k < len(starts):
        s = e = int(starts[k])
        while True:
            while e < T and react[e]:
                e += 1
            f = e
            while f < T and lying[f]:
                f += 1
            if f > e and f < T and react[f]:  # hit again lying: the combo goes on
                e = f
                continue
            break
        while k < len(starts) and starts[k] < e:
            k += 1
        if e >= T or s == 0:
            continue
        a = int(dfn.act[e])
        kind = ('ko' if not live[e] or dfn.hp[e] <= 0 else 'recovery' if a in AIR_RECOVERY else
                'knockdown' if a in LYING or a == 0x60 or dfn.air[e] else 'standing')
        rec = dict(damage=float(dfn.hp[s - 1] - dfn.hp[e]), kind=kind)
        if kind == 'recovery':
            ev = [(x, name) for x, name in ((_first(dfn.hit, e + 1, e + AFTER_END), 'caught'),
                                            (_first(att.hit, e + 1, e + AFTER_END), 'hit back'),
                                            (_first(dfn.contact, e + 1, e + AFTER_END), 'guarded'))
                  if x is not None]
            rec.update(busy=bool(att.act[e] >= FIRST_OWN), next=min(ev)[1] if ev else 'nothing')
        out.append(rec)
    return out


def endings_report(recs):
    big = [r for r in recs if r['damage'] >= BIG]
    out = dict(n=len(recs), n_big=len(big))
    for name, rs in (('all', recs), ('big', big)):
        out[name] = {k: round(float(np.mean([r['kind'] == k for r in rs])), 3) for k in ENDINGS} if rs else None
    rec = [r for r in recs if r['kind'] == 'recovery']
    if rec:
        out['after_recovery'] = dict(
            n=len(rec), busy=round(float(np.mean([r['busy'] for r in rec])), 3),
            **{k: round(float(np.mean([r['next'] == k for r in rec])), 3)
               for k in ('caught', 'hit back', 'guarded', 'nothing')})
        # (caught less hit back: what a recovery left to the opponent is worth, in shares)
        out['after_recovery']['net'] = round(float(np.mean(
            [(r['next'] == 'caught') - (r['next'] == 'hit back') for r in rec])), 3)
    return out


def grabs(me, opp, dx, live):
    """One record a match: me's throws and air throws (tried: the move came out; landed),
    the times it could have tried one (free within reach of an opponent on the ground
    that is free or guarding; of one in the air that isn't being hit), and the air
    exchanges (both in the air when one is hit: won, lost)."""
    px = np.abs(dx) * 640
    at = 0xf0 if names()[me.char] in AIR_THROW_F0 else 0xf8
    ground = ~me.air & ~opp.air & (px < 45) & me.free & (opp.free | opp.guard) & live
    air = me.air & opp.air & (px < 100) & me.free & ~opp.hitstun & live
    return [dict(throw_tries=int((me.new & (me.act == THROW)).sum()),
                 throws=int((me.new & (me.act == THROW + 1)).sum()),
                 air_tries=int((me.new & (me.act == at)).sum()),
                 air_throws=int((me.new & (me.act == at + 1)).sum()),
                 throw_chances=len(_runs(ground)[0]), air_chances=len(_runs(air)[0]),
                 air_won=int((opp.hit & me.air & opp.air).sum()),
                 air_lost=int((me.hit & me.air & opp.air).sum()))]


def grabs_report(recs, per_min):
    tot = {k: sum(r[k] for r in recs) for k in recs[0]} if recs else {}
    return {k + '_per_min': round(v * per_min, 2) for k, v in tot.items()}



# The player's risky moves: per character the ones a guard or a miss leaves open, and
# every invincible one of the frame data but the throws (a guess that loses to a guard).
RISKY = {'ayu': {0xfa: '623A', 0xfc: '623B', 0xfb: '623C', 0x106: '236C', 0x105: '236B',
                 0x104: '236A'}}
RISK_HIT = 40      # steps after the move starts in which it hits or is guarded, at least;
RISK_FLASH = 50    # ... or this many after its startup (a super's flash comes on top)
RISK_AFTER = 40    # steps after the move is over in which the opponent's hit is its punishment
RISK_LONGEST = 240  # steps a move and what it goes on into are followed for
RISK_IC = (0xa7, 0xab)  # Instant Charge: the cancel that makes a guarded move safe
RISK_WAKE = 10     # steps after me is up from a knockdown in which a raw move is a wake-up one


@functools.lru_cache(maxsize=None)
def startups():
    """Per character number: {move: its startup in steps}, from framedata.json; {} without."""
    path = os.path.join(HERE, 'framedata.json')
    if not os.path.exists(path):
        return {}
    data = json.load(open(path))
    return {c: {int(k, 16): m['startup'] for k, m in data[name].items() if m.get('startup')}
            for c, name in enumerate(names()) if name in data}


def risks(me, opp, live):
    """me's risky moves (RISKY, and the frame data's invincible ones), a record each:
    the move, whether it was a combo's piece (the opponent already in a hit reaction: no
    risk taken), else its result ('hit', 'guarded', 'rg': recoil-guarded, 'whiff'), the
    HP it dealt (a hit: until the opponent is out of its reactions) and, for one that did
    not hit, whether the opponent hit me first (punished: from the guard, or the move's
    start, until RISK_AFTER steps after me is out of its move) and the HP that cost,
    whether me recoil-guarded the answer (back) and whether me cancelled the move with an
    Instant Charge (ic); and whether a raw one was a wake-up one (wake: me was down or
    rising less than RISK_WAKE steps before: a reversal, which an opponent that waits
    for it guards). What a guess costs when it is wrong, the user's (17 November):
    Ayu's 623 recoil-guarded leaves her open to a full air combo."""
    T = len(me.act)
    name = names()[me.char] if 0 <= me.char < len(names()) else ''
    table = dict(RISKY.get(name, {}))
    at = 0xf0 if name in AIR_THROW_F0 else 0xf8
    for a in set(me.inv_moves) - {THROW, THROW + 1, at, at + 1}:  # but the throws
        table.setdefault(a, f'{a:#x}')
    if not table:
        return []
    startup = startups().get(me.char, {})
    lying = np.isin(me.act, LYING), np.isin(opp.act, LYING)
    down = np.isin(me.act, DOWN)
    react = [((s.act >= 0x32) & (s.act < 0x60)) | np.isin(s.act, THROWN) for s in (me, opp)]
    got = [r & ~_prev(r, False) for r in react]
    moving = (me.act >= FIRST_OWN) | np.isin(me.act, RISK_IC)

    def lost(s, k, at):  # the HP side s loses from the reaction starting at `at`
        e = at
        while e < T and live[e] and (react[k][e] or lying[k][e]):
            e += 1
        return float(s.hp[max(0, at - 1)] - s.hp[max(0, at - 1):max(e, at) + 1].min())
    out = []
    for t in np.flatnonzero(me.new & np.isin(me.act, list(table)) & live):
        a = int(me.act[t])
        rec = dict(move=table[a], combo=bool(react[1][t] or lying[1][t]))
        out.append(rec)
        if rec['combo']:
            continue
        rec['wake'] = bool(down[max(0, t - RISK_WAKE):t].any())
        hi = t + max(RISK_HIT, startup.get(a, 0) + RISK_FLASH)
        h, g = _first(got[1], t, hi), _first(opp.contact, t, hi)
        if h is not None and (g is None or h <= g):
            rec.update(result='hit', dealt=lost(opp, 1, h))
            continue
        if g is None:
            rec['result'], g = 'whiff', t
        else:
            rec['result'] = 'rg' if np.isin(opp.act[g:g + 3], RG).any() else 'guarded'
        e = t
        while e < min(T, t + RISK_LONGEST) and moving[e]:
            e += 1
        p = _first(got[0], g, e + RISK_AFTER)
        punished = p is not None and _first(got[1], g, p) is None
        rec.update(punished=punished, lost=lost(me, 0, p) if punished else 0.0,
                   back=_first(me.new & np.isin(me.act, RG), g, e + RISK_AFTER) is not None,
                   ic=_first(me.new & np.isin(me.act, RISK_IC), t, e + 1) is not None)
    return out


def risks_report(recs, per_min):
    """Per move: a minute, the share that were a combo's piece, and of the others (raw):
    how many, the shares that hit, were guarded, recoil-guarded and whiffed, the HP a hit
    dealt; of those that did not hit, the share punished, the HP a miss cost, the shares
    answered with a recoil guard and cancelled; `net`, the HP a raw use is worth: (all
    dealt - all lost) / raw uses; and the wake-up ones among the raw: their share (wake),
    the share of them that hit (wake_hit) and their own net (wake_net)."""
    out = {}
    for move in sorted({r['move'] for r in recs}):
        rs = [r for r in recs if r['move'] == move]
        raw = [r for r in rs if not r['combo']]
        miss = [r for r in raw if r['result'] != 'hit']
        hit = [r for r in raw if r['result'] == 'hit']
        d = dict(per_min=round(len(rs) * per_min, 2), in_combo=round(1 - len(raw) / len(rs), 3),
                 n=len(raw))
        if raw:
            d.update({k: round(float(np.mean([r['result'] == k for r in raw])), 3)
                      for k in ('hit', 'guarded', 'rg', 'whiff')})
            d['dealt'] = round(float(np.mean([r['dealt'] for r in hit]))) if hit else None
            if miss:
                d.update(punished=round(float(np.mean([r['punished'] for r in miss])), 3),
                         lost=round(float(np.mean([r['lost'] for r in miss]))),
                         back=round(float(np.mean([r['back'] for r in miss])), 3),
                         ic=round(float(np.mean([r['ic'] for r in miss])), 3))
            d['net'] = round((sum(r['dealt'] for r in hit) - sum(r['lost'] for r in miss)) / len(raw))
            wake = [r for r in raw if r['wake']]
            d['wake'] = round(len(wake) / len(raw), 3)
            if wake:
                d['wake_hit'] = round(float(np.mean([r['result'] == 'hit' for r in wake])), 3)
                d['wake_net'] = round(sum(r['dealt'] if r['result'] == 'hit' else -r['lost']
                                          for r in wake) / len(wake))
        out[move] = d
    return out


def raw_report(recs, per_min):
    """All the risky moves that were not a combo's piece, as one account: a minute, the HP
    a use is worth (`net`) and the HP a minute they are worth together (`hp_per_min`: what
    a round is judged by); the share that did not hit (`missed`), of those the share
    punished and the share cancelled with an Instant Charge. Of the opponent's
    (faced_raw), `punished` is the player's doing: what it makes of a miss."""
    raw = [r for r in recs if not r['combo']]
    out = dict(per_min=round(len(raw) * per_min, 2), n=len(raw))
    if raw:
        miss = [r for r in raw if r['result'] != 'hit']
        net = sum(r['dealt'] for r in raw if r['result'] == 'hit') - sum(r['lost'] for r in miss)
        out.update(net=round(net / len(raw)), hp_per_min=round(net * per_min),
                   missed=round(len(miss) / len(raw), 3))
        if miss:
            out.update(punished=round(float(np.mean([r['punished'] for r in miss])), 3),
                       cancelled=round(float(np.mean([r['ic'] for r in miss])), 3),
                       lost=round(float(np.mean([r['lost'] for r in miss]))))
    return out


FLIGHT_AFTER = 90  # steps after an air dash in which what came of it is looked for
FLIGHT_NEXT = ('air move', 'landed move', 'throw', 'nothing')
FLIGHT_CAME = ('hit', 'guarded', 'was hit', 'nothing')
FLIGHT_WHERE = ('combo', 'okizeme', 'string', 'open')
FLIGHT_STRING = 30  # steps after the opponent's guard in which a flight is out of a string


def flights(me, opp, live):
    """me's air dashes (AIRDASH: Ayu's flights), a record each: back or forward, what me
    started next within FLIGHT_AFTER steps (a move in the air, a move once landed, a
    throw or air throw, nothing) and what came first of it: the opponent hit or thrown,
    its guard, me hit, nothing; and where it was flown from: inside a combo (the opponent
    in a hit reaction), over an opponent that is down (okizeme), out of a string (the
    opponent guarded less than FLIGHT_STRING steps before), or in the open. How an Ayu
    comes in: people's fly 5.5 times a minute and
    mix what follows, round 17's agent 2.2 (the user's, 17 November)."""
    name = names()[me.char] if 0 <= me.char < len(names()) else ''
    at = 0xf0 if name in AIR_THROW_F0 else 0xf8
    thrown = np.isin(opp.act, THROWN)
    took = opp.hit | (thrown & ~_prev(thrown, False))
    hurt = ((opp.act >= 0x32) & (opp.act < 0x60)) | thrown
    down = np.isin(opp.act, DOWN)
    out = []
    for t in np.flatnonzero(me.new & np.isin(me.act, AIRDASH) & live):
        where = ('combo' if hurt[t] else 'okizeme' if down[t] else
                 'string' if opp.guard[max(0, t - FLIGHT_STRING):t + 1].any() else 'open')
        hi = t + FLIGHT_AFTER
        u = _first(me.move, t + 1, hi)
        nxt = ('nothing' if u is None else 'throw' if me.act[u] in (THROW, at) else
               'air move' if me.air[u] else 'landed move')
        ev = [(x, k) for x, k in ((_first(took, t + 1, hi), 'hit'), (_first(me.hit, t + 1, hi), 'was hit'),
                                  (_first(opp.contact, t + 1, hi), 'guarded')) if x is not None]
        out.append(dict(back=bool(me.act[t] == AIRDASH[1]), next=nxt, where=where,
                        came=min(ev)[1] if ev else 'nothing'))
    return out


def flights_report(recs, per_min):
    """A minute, the share flown back, the shares of what followed and of what came of
    it, `mix`: the entropy in bits of what followed (0: always the same), and by where it
    was flown from (FLIGHT_WHERE): a minute, and the shares that came to a hit and to
    being hit."""
    out = dict(per_min=round(len(recs) * per_min, 2), n=len(recs))
    if recs:
        nxt = np.array([np.mean([r['next'] == k for r in recs]) for k in FLIGHT_NEXT])
        out.update(back=round(float(np.mean([r['back'] for r in recs])), 3),
                   next={k: round(float(v), 3) for k, v in zip(FLIGHT_NEXT, nxt)},
                   came={k: round(float(np.mean([r['came'] == k for r in recs])), 3)
                         for k in FLIGHT_CAME},
                   mix=round(float(-(nxt[nxt > 0] * np.log2(nxt[nxt > 0])).sum()), 2))
        out['where'] = {}
        for k in FLIGHT_WHERE:
            rs = [r for r in recs if r['where'] == k]
            if rs:
                out['where'][k] = dict(
                    per_min=round(len(rs) * per_min, 2),
                    hit=round(float(np.mean([r['came'] == 'hit' for r in rs])), 3),
                    was_hit=round(float(np.mean([r['came'] == 'was hit' for r in rs])), 3))
    return out


LOSS_GAP = 20      # steps free and unhit that end one loss of HP (a combo on the player)
SEEN = 20          # steps a move or an object was out by which a player (14 late) saw it and could answer
SEE_LATE = 14      # ... of them, the steps before it is seen at all
BEGAN_BACK = 60    # steps before a hit in which what the player started is looked for
LOSS_BEFORE = 40   # steps before a hit in which a guard, and what a jump came from, are looked for
LOSS_WOKE = 30     # ... in which the player was down: it was rising


def losses(me, opp, live):
    """me's losses of HP, a record each: `hp`, `t` (the step it began on), and `kind`, what me was doing when the
    loss began: 'in the air, attacking' (with `where`: 'open', 'okizeme' (the opponent
    was down when me left the ground), 'pressure' (it had guarded just before), 'combo'
    (it was in a hit reaction: a combo of me's that dropped); and `by`: what hit it, 'air'
    (the opponent in the air too), 'reversal' (its invincible move), 'ground'), 'in the
    air, not attacking', 'in a move, in neutral', 'in a move, after guarding' (a mash),
    'in a move, rising', 'its invincible move beaten', 'its move guarded, then punished',
    'dashing', 'rising, not acting', 'opened after guarding', 'free on the ground',
    'thrown', 'chip'. Where the HP goes (the user, 18 November: a round that gains
    against the league and changes nothing against a person): the ledger a round is
    judged by, beside the strongest players'.

    And for a loss that began with a hit, what hit and since when it was there to see
    (the user, 19 November: "it behaves like it cannot predict what is going to happen
    after 1s, given the case where the opponent is sending out a strike ... more severe
    when handling objects"): `thing`, 'move' (the opponent in a move of its own at the
    hit), 'object' (not in one, an object of its out: the object hit) or None; `out_for`,
    the steps since that move began or that the objects had been out; `began`: it had
    been out SEEN steps or more and me started something (a move, a jump, a dash) after
    it could see it, inside the BEGAN_BACK steps before the hit: it walked into what was
    on the screen."""
    T = len(me.act)
    drop = np.clip(np.concatenate([[0], me.hp[:-1] - me.hp[1:]]), 0, None)
    drop[~live] = 0  # (a new round's HP is not a gain, and nothing is lost between rounds)
    at = np.flatnonzero(drop > 0)
    out = []
    if not len(at):
        return out
    clean = me.free & ~me.hitstun
    groups, cur = [], [int(at[0])]
    for t in at[1:]:
        t = int(t)
        if t - cur[-1] <= LOSS_GAP or not clean[cur[-1] + 1:t].any():
            cur.append(t)
        else:
            groups.append(cur)
            cur = [t]
    groups.append(cur)
    thrown = np.isin(me.act, THROWN)
    thrown_in = thrown & ~_prev(thrown, False)
    down, odown = np.isin(me.act, DOWN), np.isin(opp.act, DOWN)
    woke = lambda t: bool(down[max(0, t - LOSS_WOKE):t + 1].any())
    guarded = lambda t: bool(me.guard[max(0, t - LOSS_BEFORE):t].any())
    for g in groups:
        t0, t1 = g[0], g[-1]
        rec = dict(hp=float(drop[g].sum()), t=int(t0))
        out.append(rec)
        lo = max(0, t0 - LOSS_BEFORE)
        th = np.flatnonzero(thrown_in[max(0, t0 - 240):t0 + 2])
        if len(th) and thrown[max(0, t0 - 3):t1 + 1].any():
            rec['kind'] = 'thrown'
            continue
        hits = np.flatnonzero(me.hit[lo:t1 + 1])
        if not len(hits):
            rec['kind'] = 'chip'
            continue
        near = [lo + int(h) for h in hits if lo + int(h) <= t0 + 1]
        h = near[-1] if near else lo + int(hits[0])
        p = max(0, h - 1)
        a = int(me.act[p])
        k = p
        if opp.act[p] >= FIRST_OWN:
            while k > 0 and not opp.new[k]:
                k -= 1
            rec.update(thing='move', out_for=int(h - k))
        elif opp.objects[p] > 0:
            while k > 0 and opp.objects[k - 1] > 0:
                k -= 1
            rec.update(thing='object', out_for=int(h - k))
        else:
            rec.update(thing=None, out_for=0)
        mine = np.flatnonzero(me.acts[max(0, h - BEGAN_BACK):h])
        rec['began'] = bool(rec['out_for'] >= SEEN and len(mine) and
                            max(0, h - BEGAN_BACK) + int(mine[-1]) >= h - rec['out_for'] + SEE_LATE)
        if me.air[p]:
            if a < FIRST_OWN:
                rec['kind'] = 'in the air, not attacking'
                continue
            rec['kind'] = 'in the air, attacking'
            j = p
            while j > 0 and me.air[j]:
                j -= 1  # (where it left the ground)
            before = slice(max(0, j - LOSS_BEFORE), h)
            rec['where'] = ('okizeme' if odown[max(0, j - LOSS_WOKE):h + 1].any() else
                            'pressure' if opp.guard[before].any() else
                            'combo' if opp.hitstun[before].any() else 'open')
            oa = int(opp.act[h])
            rec['by'] = ('air' if opp.air[h] else 'reversal'
                         if oa in opp.inv_moves or opp.inv_timer[max(0, h - 12):h + 1].any()
                         else 'ground')
        elif a >= FIRST_OWN:
            m0 = int(np.flatnonzero(me.new[:p + 1])[-1])
            if a in me.inv_moves or me.inv_timer[m0:m0 + 8].any():
                rec['kind'] = 'its invincible move beaten'
            elif opp.guard[m0:h].any():
                rec['kind'] = 'its move guarded, then punished'
            else:
                rec['kind'] = 'in a move, ' + ('after guarding' if guarded(m0) else
                                               'rising' if woke(m0) else 'in neutral')
        elif a in (DASH, BACKDASH):
            rec['kind'] = 'dashing'
        elif woke(p) and not guarded(p):
            rec['kind'] = 'rising, not acting'
        elif guarded(p) or me.guard[p]:
            rec['kind'] = 'opened after guarding'
        else:
            rec['kind'] = 'free on the ground'
    return out


def losses_report(recs, per_min):
    """The ledger: HP lost a minute in all (`hp`) and how many times (`times`), and by
    kind the HP a minute, the times a minute and the HP a time; the air-attacking line
    also by where it was flown or jumped from and by what hit it (HP a minute)."""
    out = dict(hp=round(sum(r['hp'] for r in recs) * per_min), times=round(len(recs) * per_min, 2),
               kinds={})
    for k in sorted({r['kind'] for r in recs}, key=lambda k: -sum(r['hp'] for r in recs if r['kind'] == k)):
        rs = [r for r in recs if r['kind'] == k]
        hp = sum(r['hp'] for r in rs)
        out['kinds'][k] = dict(hp=round(hp * per_min), times=round(len(rs) * per_min, 2),
                               each=round(hp / len(rs)))
    air = [r for r in recs if r['kind'] == 'in the air, attacking']
    for field in ('where', 'by'):
        out['air_' + field] = {v: round(sum(r['hp'] for r in air if r[field] == v) * per_min)
                               for v in sorted({r[field] for r in air})}
    # What was on the screen (losses()): the hits by something out long enough to be seen
    # (`seen`), of them those me started something into (`began`), and those of the
    # latter that an object made (`object`): HP a minute, and times a minute.
    seen = [r for r in recs if r.get('out_for', 0) >= SEEN]
    began = [r for r in seen if r.get('began')]
    thing = [r for r in began if r.get('thing') == 'object']
    out['into'] = {k: dict(hp=round(sum(r['hp'] for r in rs) * per_min),
                           times=round(len(rs) * per_min, 3))
                   for k, rs in (('seen', seen), ('began', began), ('object', thing))}
    return out


SITUATIONS = ('my okizeme', 'its okizeme', 'my pressure', 'its pressure', 'I came by air',
              'it came by air', 'both in the air', 'on the ground')
EXCHANGE_DOWN = 70    # steps after a knockdown's end in which an exchange is that okizeme's
EXCHANGE_GUARD = 45   # ... after a guard in which it is that pressure's
EXCHANGE_AIR = 12     # ... before it in which a player in the air came by air


def exchanges(me, opp, live, mine=None, theirs=None):
    """Every loss of HP of either player (losses(): mine, theirs, made here if not given)
    as (the situation it began in, the HP: + the opponent's, - me's). The situation, from
    me's side, the first that holds: 'my okizeme' (the opponent was down within
    EXCHANGE_DOWN steps before: my hit on its rising, or its reversal's on me), 'its
    okizeme', 'my pressure' (it guarded within EXCHANGE_GUARD steps before: my opening
    it, or its way out hitting me), 'its pressure', 'I came by air' (I was in the air
    within EXCHANGE_AIR steps before and it was not), 'it came by air', 'both in the
    air', 'on the ground'. What each kind of situation is worth on net: where a player
    is ahead and where it is behind, whoever was hit."""
    mine = losses(me, opp, live) if mine is None else mine
    theirs = losses(opp, me, live) if theirs is None else theirs
    mdown, odown = np.isin(me.act, DOWN), np.isin(opp.act, DOWN)
    out = []
    for sign, recs in ((-1, mine), (1, theirs)):
        for r in recs:
            t = r['t']
            lo = max(0, t - EXCHANGE_GUARD)
            if odown[max(0, t - EXCHANGE_DOWN):t + 1].any():
                where = 'my okizeme'
            elif mdown[max(0, t - EXCHANGE_DOWN):t + 1].any():
                where = 'its okizeme'
            elif opp.guard[lo:t + 1].any():
                where = 'my pressure'
            elif me.guard[lo:t + 1].any():
                where = 'its pressure'
            else:
                a = me.air[max(0, t - EXCHANGE_AIR):t + 1].any()
                b = opp.air[max(0, t - EXCHANGE_AIR):t + 1].any()
                where = ('both in the air' if a and b else 'I came by air' if a else
                         'it came by air' if b else 'on the ground')
            out.append((where, sign * r['hp']))
    return out


def exchanges_report(recs, per_min):
    """The net ledger: HP a minute on net in all, and by situation the net, what was
    gained and what was lost."""
    out = dict(net=round(sum(v for _, v in recs) * per_min))
    for k in SITUATIONS:
        v = [x for s, x in recs if s == k]
        gained, lost = sum(x for x in v if x > 0), -sum(x for x in v if x < 0)
        out[k] = dict(net=round((gained - lost) * per_min), gained=round(gained * per_min),
                      lost=round(lost * per_min))
    return out


LEAD = 3000    # HP ahead (a bar is 9999) from which a round is the leader's to lose
CLOSE = 2500   # the opponent's HP from which, the player ahead, the round is there to close
ROUND_LEAST = 60  # steps: a round shorter than this is not one
ROUND_AGAIN = 2000  # HP more than on the step before: a new round's
ROUND_OVER = 1000   # HP at a round's last step at or under which it was fought to its end
#   (a dataset's last step of a round is before the hit that ends it: the loser's HP then
#   is under that hit's damage; a round the record cuts short has both above it)


def rounds(me, opp, live):
    """Each round the match's record holds to its end, by what the player made of its
    leads: a dict a round: won; steps; lead: None, or (kept, HP lost after) from the
    first step it was LEAD HP ahead: kept, it won the round; behind: None, or whether it
    won from the first step it was LEAD behind; close: None, or (won, steps to the
    round's end, its own HP lost in them) from the first step the opponent was at CLOSE
    HP or less with the player ahead: a round that is there to be closed, how long that
    took and what it cost. What is made of an advantage (the user's, 18 November: "it
    doesn't fully use its advantage"; "its behavior becomes random at the end of the
    round")."""
    out, T, t = [], len(live), 0
    d = me.hp - opp.hp
    # A round also ends where the HP is full again on the next step (a replay dataset's
    # matches hold the fight's steps only: its rounds follow one another).
    again = np.zeros(T, bool)
    again[1:] = (np.diff(me.hp) > ROUND_AGAIN) | (np.diff(opp.hp) > ROUND_AGAIN)
    while t < T:
        if not live[t]:
            t += 1
            continue
        e = t + 1
        while e < T and live[e] and not again[e]:
            e += 1
        end = e if e < T and not live[e] else e - 1  # (the step that shows how it ended)
        # (a round the record does not hold to its end, cut short or timed out: none)
        if e - t >= ROUND_LEAST and min(me.hp[end], opp.hp[end]) <= ROUND_OVER:
            won = bool(opp.hp[end] < me.hp[end])
            rec = dict(won=won, steps=e - t, lead=None, behind=None, close=None)
            at = np.flatnonzero(d[t:e] >= LEAD)
            if len(at):
                rec['lead'] = (won, float(me.hp[t + at[0]] - me.hp[end]))
            at = np.flatnonzero(d[t:e] <= -LEAD)
            if len(at):
                rec['behind'] = won
            at = np.flatnonzero((opp.hp[t:e] <= CLOSE) & (d[t:e] > 0))
            if len(at):
                rec['close'] = (won, int(e - t - at[0]), float(me.hp[t + at[0]] - me.hp[end]))
            out.append(rec)
        t = e
    return out


def rounds_report(recs):
    """Of the rounds: the share won; lead: the share of rounds it was LEAD ahead in, the
    share of those it kept (won), the HP it lost after the lead; behind: the share it was
    LEAD behind in, and of those the share it turned; close: the share there to be
    closed, of those the share won, the seconds a won one took from there (mean, 90th
    percentile) and the HP it lost in them."""
    if not recs:
        return None
    n = len(recs)
    lead = [r['lead'] for r in recs if r['lead'] is not None]
    behind = [r['behind'] for r in recs if r['behind'] is not None]
    close = [r['close'] for r in recs if r['close'] is not None]
    secs = [c[1] / 60 for c in close if c[0]]
    return dict(n=n, won=round(float(np.mean([r['won'] for r in recs])), 3),
                lead=dict(n=len(lead), share=round(len(lead) / n, 3),
                          kept=_mean([x[0] for x in lead]),
                          lost=round(float(np.mean([x[1] for x in lead]))) if lead else None),
                behind=dict(n=len(behind), share=round(len(behind) / n, 3), turned=_mean(behind)),
                close=dict(n=len(close), share=round(len(close) / n, 3),
                           won=_mean([c[0] for c in close]),
                           seconds=round(float(np.mean(secs)), 2) if secs else None,
                           seconds_p90=round(float(np.percentile(secs, 90)), 2) if secs else None,
                           lost=round(float(np.mean([c[2] for c in close]))) if close else None))


def measure(c, controls=None):
    """Both ways, for one player's match: c, its views' OBS columns (T, len(OBS));
    controls (T,), its inputs: with them also its strings (strings())."""
    c = np.asarray(c, np.float32)
    me, opp = Side(c, 0), Side(c, 1)
    live = (c[:, 16] == 0) & (c[:, 17] == 0)
    dx = c[:, 18]
    extra = dict(strings=strings(me, opp, live, controls)) if controls is not None else {}
    lost, dealt = losses(me, opp, live), losses(opp, me, live)
    return dict(**extra, ends_off=endings(me, opp, live), ends_def=endings(opp, me, live),
                risks=risks(me, opp, live), risks_def=risks(opp, me, live),
                flights=flights(me, opp, live), rounds=rounds(me, opp, live),
                losses=lost, losses_opp=dealt,
                exchanges=exchanges(me, opp, live, lost, dealt),
                grabs=grabs(me, opp, dx, live),
                press_off=pressure(me, opp, dx, live), press_def=pressure(opp, me, dx, live),
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
    # Which moves it started out of the guard (the user's: an agent that presses its 2A
    # under pressure, slower than the opponent's next attack), how each went, how often
    # at a disadvantage.
    em = np.array([r.get('escape_move', '') for r in recs])
    by = collections.Counter(em[em != ''])
    if by:
        out['escape_moves'] = {}
        for k, c in by.most_common(8):
            m = em == k
            out['escape_moves'][k] = dict(share=round(c / len(recs), 3), n=int(c),
                                          escaped=_mean(what[m] == 'fought_back'),
                                          trapped=_mean(what[m] == 'hit'),
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
    # The attacker's okizeme, by what it did (a move by its number): how often, how it
    # went, how many times it pressed it again, and how often the riser answered it
    # with an invincible move.
    oki = np.array([r.get('oki', '') for r in recs])
    again = np.array([r.get('oki_again', 0) for r in recs], float)
    by = collections.Counter(oki[oki != ''])
    if by:
        out['okizeme'] = {}
        for k, n in by.most_common(10):
            m = oki == k
            out['okizeme'][k] = dict(share=_mean(m), n=int(n),
                                     hit=_mean(result[m] == 'attacker'),
                                     hit_back=_mean(result[m] == 'defender'),
                                     value=round(float(swing[m].mean())),
                                     again=round(float(again[m].mean()), 2),
                                     invincible=_mean(choice[m] == 'invincible'))
    # The mix-ups (wakeup()'s mix: how it came in, how the move is guarded, a cross-up):
    # their shares and how each went, how often it struck low, high, from behind; and
    # `top`, the share of the commonest: how predictable it is.
    mix = np.array([r.get('mix', '') for r in recs])
    by = collections.Counter(mix[mix != ''])
    if by:
        moved = (mix != '') & (mix != 'none')
        out['mix'] = dict(top=_mean(mix[mix != ''] == by.most_common(1)[0][0]),
                          low=_mean([' low' in x for x in mix[moved]]),
                          high=_mean([' high' in x for x in mix[moved]]),
                          throw=_mean([' throw' in x for x in mix[moved]]),
                          cross=_mean([x.endswith(' cross') for x in mix[moved]]))
        out['mixups'] = {}
        for k, n in by.most_common(12):
            m = mix == k
            out['mixups'][k] = dict(share=_mean(m), n=int(n),
                                    hit=_mean(result[m] == 'attacker'),
                                    hit_back=_mean(result[m] == 'defender'),
                                    value=round(float(swing[m].mean())),
                                    invincible=_mean(choice[m] == 'invincible'))
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


def strings_report(recs, per_min, top=12):
    """strings()' records: how many, how long, how varied (`top`: the share of the
    commonest; `repeat`: of a string the same as the one before), and the commonest
    routes: how each went, from where."""
    if not recs:
        return None
    moves = [r['moves'] for r in recs]
    by = collections.Counter(moves)
    singles = collections.Counter(m for r in moves for m in r.split('-'))
    total = sum(singles.values())
    out = dict(per_min=round(len(recs) * per_min, 2),
               moves_per_string=round(total / len(recs), 2),
               top=_mean([m == by.most_common(1)[0][0] for m in moves]),
               repeat=_mean([a == b for a, b in zip(moves[1:], moves[:-1])]),
               routes_for_half=next(k + 1 for k, c in enumerate(np.cumsum(
                   [v for _, v in by.most_common()])) if c >= len(recs) / 2),
               moves={m: round(v / total, 3) for m, v in singles.most_common(10)},
               routes={})
    for m, n in by.most_common(top):
        rs = [r for r in recs if r['moves'] == m]
        guarded = [r for r in rs if r['how'] == 'guarded']
        out['routes'][m] = dict(share=round(n / len(recs), 3), n=n,
                                **{k: _mean([r['how'] == k for r in rs]) for k in ('hit', 'guarded', 'whiff')},
                                from_free=_mean([r['start'] == 'free' for r in rs]),
                                punished=_mean([r['punished'] for r in guarded]) if guarded else None)
    return out


def report(n, per_min):
    """Events' lists (measure()'s, concatenated) -> its report's entries."""
    return dict(strings=strings_report(n.get('strings', []), per_min),
                combo_ends=endings_report(n.get('ends_off', [])),
                taken_combo_ends=endings_report(n.get('ends_def', [])),
                grabs=grabs_report(n.get('grabs', []), per_min),
                risks=risks_report(n.get('risks', []), per_min),
                faced_risks=risks_report(n.get('risks_def', []), per_min),
                raw=raw_report(n.get('risks', []), per_min),
                faced_raw=raw_report(n.get('risks_def', []), per_min),
                flights=flights_report(n.get('flights', []), per_min),
                ledger=losses_report(n.get('losses', []), per_min),
                dealt_ledger=losses_report(n.get('losses_opp', []), per_min),
                net_ledger=exchanges_report(n.get('exchanges', []), per_min),
                rounds=rounds_report(n.get('rounds', [])),
                pressure=pressure_report(n['press_off'], per_min, moves=True),
                under_pressure=pressure_report(n['press_def'], per_min),
                okizeme=wakeup_report(n['oki_off'], per_min),
                wakeup=wakeup_report(n['oki_def'], per_min),
                free_time=free_report(n['free_self'], per_min),
                opponent_free_time=free_report(n['free_opp'], per_min))
