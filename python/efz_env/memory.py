"""A match memory: what a player has seen its opponent do in this match and the ones before
it in the set, and how its own choices went: counts kept as the game goes, each a share
with how much is behind it.

    memory = Memory(n)                # n viewers
    memory.update(view)               # every step: each viewer's view (n, obs_dim >= 72)
    features = memory.features()      # (n, SIZE) float32
    memory.end(ended, won, new_set)   # a match ended (where `ended`)

A policy sees the game as it is (late) and its own last inputs: nothing of what the
opponent did on its last three wake-ups, or how the policy's own last four low attacks
went. A person remembers that, and plays the fortieth match of a set differently from
the first (docs/training-v2.md, "Adapting during a match"). This is that memory as
inputs, for a policy trained with them (EfzSB3VecEnv's memory=, Agent's).

The counts are made from the view they are given, a step at a time. Given the view a
delayed agent has (the game `delay` steps ago, as EfzSB3VecEnv and Agent give it), the
memory holds what a person could have seen by then, no more: it stays inside the human
limits. The steps below are an environment's of frame_skip=1 (frames).

What is counted, for the viewer ("I") of the opponent ("it"):

- Its wake-ups (it leaves the rising state): what it did within CHOICE steps: a move, one
  of them invincible (the invulnerability timer in its first INV steps, or the move in
  `invincible`, by character: the frame data's), a jump, a backdash (else: a guard or
  nothing); whether I was in a move as it rose (a meaty); and who was hit first within
  RESULT steps, apart for my meaties and my waits.
- After its guard ends (my string, guarded): what it did within CHOICE steps: a move, an
  invincible one, a jump, a backdash; who was hit first within AFTER steps.
- Its guard: of its guards on the ground, the share crouching; of all, the share recoil
  guards.
- My openings (my first hit on it, or my throw): the share that found it crouching,
  standing, in a move of its own, in the air; the share that were throws.
- Its openings on me: the share that found me in a move, in the air, crouching; that were
  throws; that came from the air. And of its attacks' starts on me (an opening, or a
  guard after STRING_GAP steps without one), the share that hit, and that came from the
  air.
- My wake-ups: the share it made contact on within CHOICE steps, from the air, with a
  throw; the share I rose with a move on (within REVERSAL steps); who was hit first, apart
  for those and the others.
- My air attacks that touched it on the ground: the share that hit.
- The set: the matches played in it (up to SET), the share I won.

At a match's end the counts are kept for the next match of the set, each scaled by
`decay` (what is older counts for less); a new set starts from nothing.
"""

import numpy as np

# The view's columns (efz_env_obs_name): the viewer's and the opponent's.
INTRO, ROUND_OVER = 2, 3
SELF = dict(act=18, frame=19, stun=20, inv=25, char=34, air=39)
OPP = dict(act=50, frame=51, stun=52, inv=57, char=66, air=71)

# src/efz.h's common actions.
RISING = 0x60
DOWN = (0x60, 0x61, 0x62, 0x63)
WAKEUP_ATTACK = 0xa2
DASH, BACKDASH = 0xa3, 0xa4
GUARDS = tuple(range(0x96, 0x9d)) + (0xa8, 0xa9, 0xaa)
GUARDS_CROUCH = (0x99, 0x9a, 0x9b, 0xa9)
GUARDS_GROUND = (0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0xa8, 0xa9)
RG = (0xa8, 0xa9, 0xaa)
THROWN = tuple(range(0x64, 0x79))
FIRST_OWN = 0xc8
CROUCHING = (0x3, 0x8) + GUARDS_CROUCH
STANDING = (0x0, 0x1, 0x2, 0x7, 0xd, 0x96, 0x97, 0x98, 0xa8)
ACTS = 0x400  # an action's number is under this (objects' patterns too)

CHOICE = 16       # steps after rising, or after a guard, in which a choice is looked for
REVERSAL = 8      # ... in which the viewer's own move is a wake-up one
INV = 8           # a move's first steps in which its invulnerability makes it invincible
RESULT = 96       # steps after rising in which who hits first is looked for
AFTER = 64        # ... after a guard
STRING_GAP = 24   # an attack starts: a guard after this many steps without one
SET = 4           # the matches of a set that are counted (more read as this many)
WEIGHT = 3.0      # how much is behind a share: count / (count + WEIGHT)

COUNTS = (
    'w_n', 'w_move', 'w_inv', 'w_jump', 'w_back', 'w_meaty', 'w_m_won', 'w_m_lost',
    'w_w_won', 'w_w_lost',
    'p_n', 'p_move', 'p_inv', 'p_jump', 'p_back', 'p_won', 'p_lost',
    'g_n', 'g_crouch', 'c_n', 'c_rg',
    'o_n', 'o_crouch', 'o_stand', 'o_throw', 'o_move', 'o_air',
    'h_n', 'h_move', 'h_air', 'h_crouch', 'h_throw', 'h_byair', 'a_n', 'a_air',
    'r_n', 'r_pressed', 'r_air', 'r_throw', 'r_rev', 'r_rev_won', 'r_rev_lost', 'r_g_won',
    'r_g_lost',
    'j_n', 'j_hit',
    's_n', 's_won',
)
K = {name: i for i, name in enumerate(COUNTS)}
# The features: (name, count, of): the share count / of ("of" a count, or one less
# another), or (name, None, of): how much is behind the shares of "of".
FEATURES = (
    ('wake', None, 'w_n'), ('wake_move', 'w_move', 'w_n'), ('wake_invincible', 'w_inv', 'w_n'),
    ('wake_jump', 'w_jump', 'w_n'), ('wake_backdash', 'w_back', 'w_n'),
    ('wake_meaty', 'w_meaty', 'w_n'),
    ('wake_meaty_won', 'w_m_won', 'w_meaty'), ('wake_meaty_lost', 'w_m_lost', 'w_meaty'),
    ('wake_wait_won', 'w_w_won', ('w_n', 'w_meaty')),
    ('wake_wait_lost', 'w_w_lost', ('w_n', 'w_meaty')),
    ('guarded', None, 'p_n'), ('guarded_move', 'p_move', 'p_n'),
    ('guarded_invincible', 'p_inv', 'p_n'), ('guarded_jump', 'p_jump', 'p_n'),
    ('guarded_backdash', 'p_back', 'p_n'), ('guarded_won', 'p_won', 'p_n'),
    ('guarded_lost', 'p_lost', 'p_n'),
    ('guard', None, 'g_n'), ('guard_crouch', 'g_crouch', 'g_n'), ('guard_rg', 'c_rg', 'c_n'),
    ('opened', None, 'o_n'), ('opened_crouching', 'o_crouch', 'o_n'),
    ('opened_standing', 'o_stand', 'o_n'), ('opened_throw', 'o_throw', 'o_n'),
    ('opened_move', 'o_move', 'o_n'), ('opened_air', 'o_air', 'o_n'),
    ('hit', None, 'h_n'), ('hit_move', 'h_move', 'h_n'), ('hit_air', 'h_air', 'h_n'),
    ('hit_crouching', 'h_crouch', 'h_n'), ('hit_throw', 'h_throw', 'h_n'),
    ('hit_from_air', 'h_byair', 'h_n'),
    ('attacked', None, 'a_n'), ('attacked_hit', 'h_n', 'a_n'), ('attacked_air', 'a_air', 'a_n'),
    ('rise', None, 'r_n'), ('rise_pressed', 'r_pressed', 'r_n'), ('rise_air', 'r_air', 'r_n'),
    ('rise_throw', 'r_throw', 'r_n'), ('rise_reversal', 'r_rev', 'r_n'),
    ('rise_reversal_won', 'r_rev_won', 'r_rev'), ('rise_reversal_lost', 'r_rev_lost', 'r_rev'),
    ('rise_guard_won', 'r_g_won', ('r_n', 'r_rev')),
    ('rise_guard_lost', 'r_g_lost', ('r_n', 'r_rev')),
    ('air', None, 'j_n'), ('air_hit', 'j_hit', 'j_n'),
    ('set', None, None), ('set_won', 's_won', 's_n'),
)
NAMES = tuple(f[0] for f in FEATURES)
SIZE = len(FEATURES)


def _table(acts):
    t = np.zeros(ACTS, bool)
    t[list(acts)] = True
    return t


_GUARD, _GUARD_GROUND, _GUARD_CROUCH, _RG = (_table(x) for x in
                                              (GUARDS, GUARDS_GROUND, GUARDS_CROUCH, RG))
_THROWN, _DOWN, _CROUCHING, _STANDING = (_table(x) for x in (THROWN, DOWN, CROUCHING, STANDING))
_MOVE = np.zeros(ACTS, bool)  # a move of its own, a dash or a backdash: something started
_MOVE[FIRST_OWN:0x190] = True
_MOVE[[WAKEUP_ATTACK, DASH, BACKDASH]] = True


class _Side:
    """A player's signals on a step, from its columns of the view and the step before."""

    def __init__(self, n, cols):
        self.cols = cols
        self.act = np.full(n, -1)
        self.frame = np.zeros(n, int)
        self.stun = np.zeros(n, bool)
        self.guard = np.zeros(n, bool)
        self.air = np.zeros(n, bool)
        self.thrown_state = np.zeros(n, bool)

    def step(self, view, invincible):
        c = self.cols
        act = np.clip(np.rint(view[:, c['act']]).astype(int), 0, ACTS - 1)
        frame = np.rint(view[:, c['frame']]).astype(int)
        stun, air = view[:, c['stun']] > 0, view[:, c['air']] > 0
        self.was, self.was_air, self.was_guard = self.act, self.air, self.guard
        self.new = act != self.act
        guard, thrown = _GUARD[act], _THROWN[act]
        self.hit = stun & ~self.stun           # a hit reaction starts
        self.thrown = thrown & ~self.thrown_state
        self.struck = self.hit | self.thrown
        self.contact = guard & (~self.guard | self.new | (frame < self.frame))
        self.move = self.new & (act >= FIRST_OWN) & (act < 0x190) | \
            self.new & (act == WAKEUP_ATTACK)
        self.backdash = self.new & (act == BACKDASH)
        self.jump = air & ~self.air & ~stun & ~thrown & ~guard
        self.rose = ((self.act == RISING) & (act != RISING)) | \
            (self.new & (act == WAKEUP_ATTACK) & _DOWN[np.maximum(self.act, 0)])
        self.inv = view[:, c['inv']] > 0
        if invincible is not None:
            char = np.clip(np.rint(view[:, c['char']]).astype(int), 0, len(invincible) - 1)
            self.inv = self.inv | invincible[char, act]
        self.act, self.frame, self.stun, self.guard = act, frame, stun, guard
        self.air, self.thrown_state = air, thrown

    def clear(self, mask):
        self.act[mask] = -1
        self.frame[mask] = 0
        for x in (self.stun, self.guard, self.air, self.thrown_state):
            x[mask] = False


class _Window:
    """A situation that opened (a rising, a guard's end): the steps since, per viewer
    (-1: none open), whether its choice and its result were found, and what it opened
    with (`kind`: the viewer's meaty, the viewer's reversal)."""

    def __init__(self, n, choice, result):
        self.age = np.full(n, -1)
        self.chose = np.zeros(n, bool)
        self.done = np.zeros(n, bool)
        self.kind = np.zeros(n, bool)
        self.moved = np.zeros(n, int)  # steps left in which the chosen move may prove invincible
        self.choice, self.result = choice, result

    def open(self, mask, kind=False):
        self.age[mask] = 0
        self.chose[mask] = self.done[mask] = False
        self.kind[mask] = kind[mask] if isinstance(kind, np.ndarray) else kind
        self.moved[mask] = 0

    def choosing(self):
        return (self.age >= 0) & ~self.chose & (self.age < self.choice)

    def awaiting(self):
        return (self.age >= 0) & ~self.done & (self.age < self.result)

    def tick(self):
        on = self.age >= 0
        self.age[on] += 1
        self.moved[self.moved > 0] -= 1
        self.age[self.age >= max(self.choice, self.result)] = -1

    def close(self, mask):
        self.age[mask] = -1
        self.moved[mask] = 0


class Memory:
    def __init__(self, n, decay=0.7, invincible=None):
        """invincible: the moves invulnerable in their first frames by the frame data,
        {character number: [actions]} (as a model's config.json keeps it) or a
        (characters, ACTS) bool table; without it only the invulnerability timer says."""
        self.n, self.decay = n, decay
        if isinstance(invincible, dict):
            invincible = invincible_table(invincible)
        self.invincible = None if invincible is None else np.asarray(invincible, bool)
        self.c = np.zeros((n, len(COUNTS)), np.float32)
        self.me, self.it = _Side(n, SELF), _Side(n, OPP)
        self.wake = _Window(n, CHOICE, RESULT)    # its wake-up
        self.press = _Window(n, CHOICE, AFTER)    # after its guard
        self.rise = _Window(n, CHOICE, RESULT)    # my wake-up
        self.since_guard = np.full(n, STRING_GAP + 1)  # steps since my last guard
        self._num = np.array([K[f[1]] if f[1] else 0 for f in FEATURES])
        of = [f[2] if not isinstance(f[2], tuple) else f[2][0] for f in FEATURES]
        self._of = np.array([K[x] if x else 0 for x in of])
        self._less = np.array([K[f[2][1]] if isinstance(f[2], tuple) else -1 for f in FEATURES])
        self._behind = np.array([f[1] is None and f[2] is not None for f in FEATURES])
        self._set = NAMES.index('set')

    def add(self, name, mask):
        self.c[mask, K[name]] += 1

    def update(self, view):
        """A step: each viewer's view (n, obs_dim)."""
        view = np.asarray(view)
        me, it = self.me, self.it
        me.step(view, self.invincible)
        it.step(view, self.invincible)
        live = (view[:, INTRO] == 0) & (view[:, ROUND_OVER] == 0)
        for w in (self.wake, self.press, self.rise):
            w.close(~live)
        add = self.add

        # Its wake-up.
        w = self.wake
        w.open(it.rose & live, me.act >= FIRST_OWN)
        add('w_n', it.rose & live)
        add('w_meaty', it.rose & live & w.kind)
        self._choice(w, it, 'w')
        r = w.awaiting()
        won, lost = r & it.struck, r & me.struck & ~it.struck
        add('w_m_won', won & w.kind)
        add('w_m_lost', lost & w.kind)
        add('w_w_won', won & ~w.kind)
        add('w_w_lost', lost & ~w.kind)
        w.done |= won | lost

        # After its guard.
        p = self.press
        ended = it.was_guard & ~it.guard & live
        p.open(ended)
        add('p_n', ended)
        self._choice(p, it, 'p')
        r = p.awaiting()
        won, lost = r & it.struck, r & me.struck & ~it.struck
        add('p_won', won)
        add('p_lost', lost)
        p.done |= won | lost

        # Its guard.
        contact = it.contact & live
        add('c_n', contact)
        add('c_rg', contact & _RG[it.act])
        ground = contact & _GUARD_GROUND[it.act]
        add('g_n', ground)
        add('g_crouch', ground & _GUARD_CROUCH[it.act])

        # The openings, mine and its.
        for a, b, k in ((me, it, 'o'), (it, me, 'h')):  # a opens b
            was = np.maximum(b.was, 0)
            throw = b.thrown & live
            hit = b.hit & ~b.thrown & live
            air = hit & b.was_air
            move = hit & ~air & _MOVE[was]
            crouch = hit & ~air & ~move & _CROUCHING[was]
            stand = hit & ~air & ~move & _STANDING[was]
            opened = throw | air | move | crouch | stand
            add(k + '_n', opened)
            add(k + '_throw', throw)
            add(k + '_air', air)
            add(k + '_move', move)
            add(k + '_crouch', crouch)
            if k == 'o':
                add('o_stand', stand)
            else:
                add('h_byair', opened & a.air)
                # Its attacks' starts on me: an opening, or a guard after a while without.
                start = (me.contact & live & (self.since_guard > STRING_GAP)) & ~opened
                add('a_n', opened | start)
                add('a_air', (opened | start) & a.air)
        self.since_guard += 1
        self.since_guard[me.guard] = 0

        # My wake-up.
        r = self.rise
        r.open(me.rose & live)
        add('r_n', me.rose & live)
        early = (r.age >= 0) & (r.age < REVERSAL) & ~r.kind & ~r.done & me.move
        r.kind |= early  # (kind: I rose with a move)
        add('r_rev', early)
        c = r.choosing() & (me.contact | me.struck)
        add('r_pressed', c)
        add('r_air', c & it.air)
        add('r_throw', c & me.thrown)
        r.chose |= c
        a = r.awaiting()
        won, lost = a & it.struck & ~me.struck, a & me.struck
        add('r_rev_won', won & r.kind)
        add('r_rev_lost', lost & r.kind)
        add('r_g_won', won & ~r.kind)
        add('r_g_lost', lost & ~r.kind)
        r.done |= won | lost

        # My air attacks on it on the ground.
        touch = me.air & ~it.was_air & live & (it.contact | it.hit)
        add('j_n', touch)
        add('j_hit', touch & it.hit)

        for w in (self.wake, self.press, self.rise):
            w.tick()

    def _choice(self, w, who, k):
        """The first thing `who` does in the window w: counts k_move, k_inv, k_jump,
        k_back; a guard or a hit taken ends the looking."""
        c = w.choosing()
        move, back, jump = c & who.move, c & who.backdash, c & who.jump & ~who.move
        self.add(k + '_move', move)
        self.add(k + '_back', back)
        self.add(k + '_jump', jump)
        w.moved[move] = INV
        inv = (w.age >= 0) & (w.moved > 0) & who.inv
        self.add(k + '_inv', inv)
        w.moved[inv] = 0
        w.chose |= move | back | jump | (c & (who.contact | who.struck))

    def features(self):
        """(n, SIZE): the shares, and how much is behind each group."""
        of = self.c[:, self._of]
        less = np.where(self._less >= 0, self.c[:, np.maximum(self._less, 0)], 0)
        of = np.maximum(of - less, 0)
        out = np.where(self._behind, of / (of + WEIGHT),
                       np.divide(self.c[:, self._num], of, out=np.zeros_like(of),
                                 where=of > 1e-6))
        out[:, self._set] = np.minimum(self.c[:, K['s_n']], SET) / SET
        return np.clip(out, 0, 1).astype(np.float32)

    def end(self, ended, won=None, new_set=None):
        """A match ended where `ended`: where `won`, the viewer won it. Where `new_set`
        (default: everywhere it ended) the next is against another opponent: nothing
        is kept; else the counts are scaled by decay."""
        ended = np.asarray(ended, bool)
        new_set = ended if new_set is None else (np.asarray(new_set, bool) & ended)
        keep = ended & ~new_set
        played, wins = self.c[:, K['s_n']].copy(), self.c[:, K['s_won']].copy()
        self.c[keep] *= self.decay
        self.c[:, K['s_n']] = played + keep  # (the set's matches are counted whole)
        self.c[:, K['s_won']] = wins if won is None else wins + (keep & np.asarray(won, bool))
        self.c[new_set] = 0
        for s in (self.me, self.it):
            s.clear(ended)
        for w in (self.wake, self.press, self.rise):
            w.close(ended)
        self.since_guard[ended] = STRING_GAP + 1

    def clear(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        self.end(mask, new_set=mask)


def invincible_table(frame_data, characters=64):
    """Memory's `invincible` from {character index: its invincible moves' actions}."""
    t = np.zeros((characters, ACTS), bool)
    for char, moves in frame_data.items():
        for a in moves:
            if 0 <= int(char) < characters and 0 <= int(a) < ACTS:
                t[int(char), int(a)] = True
    return t
