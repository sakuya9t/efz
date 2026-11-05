"""A player's view of the game as text, for a language model to read, and its action as
one of the 45 of efz_env's ActionTable (9 directions x none/A/B/C/D, by name: '5', '2A').

    text = prompt(view, my_moves, opp_moves, inputs, player='473')

view: the player's observation (168 floats, efz_env's), seen `delay` steps late as an
agent with a reaction time sees it; my_moves, opp_moves: the actions (pattern numbers)
each player was in before its current one, oldest first, as those views showed them;
inputs: the player's own last steps of input, as action indices (efz_env.history's
action_labels: the direction, and a button that went down), oldest first, known at
once; player: who plays (a pseudonym's number from the replays' players.csv) or '?'.
Training (train.py) and playing (llm.LLMAgent) build these the same way: Context.
A prompt looks like:

    Ayu (player 473) vs Kanna. Round 2, rounds 0-1.
    Me: HP 73% power 1.2 RF 64 cyan guard 100%. x 210 y 0, moving 3 0. Doing m204 frame 3, airborne.
    Opponent: HP 51% power 0.4 RF 12 red guard 80%. x 330 y -40, moving -2 4. Doing guard frame 2, guarding.
    Opponent 120 px ahead, 40 px above.
    Objects: mine 40,-30 hitting; theirs none.
    Before: me stand walk-forward; opponent jump-forward air-guard.
    My inputs: 5x8 2x3 3 6A
    Action:
"""

import numpy as np

from efz_env import ActionTable

TABLE = ActionTable()
ACTIONS = [TABLE.describe(i) for i in range(len(TABLE))]

# The game's characters, in its order (kCharacterNames); display names.
CHARACTERS = ['Nanase', 'Ayu', 'Mai', 'Makoto', 'Akane', 'Mayu', 'Nagamori', 'Misaki',
              'Shiori', 'Sayuri', 'Nayuki', 'Mio', 'EX Nanase', 'Kaori', 'Ikumi', 'Mishio',
              'Akiko', 'Nayuki (sleepy)', 'Mizuka', 'Kanna', 'Kano', 'Minagi', 'Nayuki (2)',
              'Misuzu', 'Mizuka (boss)']

# The common actions' names (src/efz.h); a character's own moves are 'm<number>'.
COMMON = {0x0: 'stand', 0x1: 'walk-forward', 0x2: 'walk-back', 0x3: 'crouch', 0x4: 'jump',
          0x5: 'jump-forward', 0x6: 'jump-back', 0x7: 'stand-up', 0x8: 'crouch-down',
          0x9: 'fall', 0xa: 'super-jump', 0xb: 'super-jump', 0xc: 'super-jump', 0xd: 'land',
          0xe: 'air-jump', 0xf: 'air-jump-forward', 0x10: 'air-jump-back',
          0x60: 'wake-up', 0x61: 'knockdown', 0x62: 'knockdown', 0x63: 'lying',
          0x9c: 'air-guard', 0x9d: 'air-recover', 0x9e: 'air-recover', 0xa2: 'wake-up-attack',
          0xa3: 'dash', 0xa4: 'backdash', 0xa5: 'air-dash', 0xa6: 'air-backdash',
          0xa7: 'instant-charge', 0xa8: 'recoil-guard', 0xa9: 'recoil-guard',
          0xaa: 'air-recoil-guard', 0xab: 'air-instant-charge', 0xb2: 'dash-stop'}

# Observation columns (efz_env: env.observation_names).
ROUND, INTRO, ROUND_OVER, DX, DY = 1, 2, 3, 4, 5
SELF, OPP = 8, 40  # each player's block of 32
HP, GAUGE, RF, BLUE, GUARD_GAUGE, X, Y, VX, VY, FACING, ACT, FRAME, HITSTUN, GUARDING, \
    DASHING, HITSTOP, FREEZE, INVUL, NO_GUARD, ARMOR, THROW_PROT, UNTECH, COMBO_HITS, \
    PRORATION, ROUNDS_WON, AIR_ACTIONS, CHAR, OWN, CPU, SEALED, COMBO_DAMAGE, AIRBORNE = range(32)
OBJECTS = (72, 120)  # each player's 8 objects, 6 floats each: active, x, y, vx, vy, can_hit


def move_name(a):
    a = int(round(float(a)))
    if a >= 0xc8:
        return f'm{a}'
    if a in COMMON:
        return COMMON[a]
    if 0x32 <= a < 0x60:
        return 'hit'
    if 0x64 <= a < 0x7a:
        return 'thrown'
    if 0x96 <= a < 0x9c:
        return 'guard'
    return f'c{a}'


def inputs_text(labels):
    """Action indices -> '5x8 2x3 3 6A': runs of the same, oldest first."""
    out, prev, n = [], None, 0
    for a in labels:
        a = int(a)
        if a == prev:
            n += 1
            continue
        if prev is not None:
            out.append(ACTIONS[prev] + (f'x{n}' if n > 1 else ''))
        prev, n = a, 1
    if prev is not None:
        out.append(ACTIONS[prev] + (f'x{n}' if n > 1 else ''))
    return ' '.join(out) if out else 'none'


def _player(v, b, who):
    hp = v[b + HP] * 100
    rf = v[b + RF] * 1000
    state = 'blue' if v[b + BLUE] > 0 else 'cyan' if rf >= 500 else 'red'
    s = (f'{who}: HP {hp:.0f}% power {v[b + GAUGE] * 3:.1f} RF {rf / 10:.0f} {state} '
         f'guard {v[b + GUARD_GAUGE] * 100:.0f}%. x {v[b + X] * 320 + 320:.0f} y {v[b + Y] * 240:.0f}')
    vx, vy = v[b + VX] * 20, v[b + VY] * 20
    if abs(vx) >= 0.5 or abs(vy) >= 0.5:
        s += f', moving {vx:.0f} {vy:.0f}'
    s += f'. Doing {move_name(v[b + ACT])} frame {int(round(float(v[b + FRAME])))}'
    flags = [name for k, name in ((HITSTUN, 'hitstun'), (GUARDING, 'guarding'),
                                  (DASHING, 'dashing'), (FREEZE, 'frozen'),
                                  (INVUL, 'invulnerable'), (NO_GUARD, 'unable to guard'),
                                  (ARMOR, 'armor'), (THROW_PROT, 'throw-protected'),
                                  (AIRBORNE, 'airborne')) if v[b + k] > 0]
    if v[b + HITSTOP] > 0:
        flags.append(f'hitstop {v[b + HITSTOP] * 30:.0f}')
    if v[b + UNTECH] > 0:
        flags.append(f'untech {v[b + UNTECH] * 100:.0f}')
    if v[b + SEALED] > 0:
        flags.append(f'sealed {v[b + SEALED]:.0f}')
    hits = int(round(float(v[b + COMBO_HITS]) * 30))
    if hits:
        flags.append(f'combo {hits} hits {v[b + COMBO_DAMAGE] * 9999:.0f} damage, '
                     f'proration {v[b + PRORATION] * 100:.0f}%')
    if flags:
        s += ', ' + ', '.join(flags)
    return s + '.'


def _objects(v, k):
    out = []
    base = OBJECTS[k]
    for j in range(8):
        o = v[base + 6 * j:base + 6 * j + 6]
        if o[0] > 0 and len(out) < 3:
            out.append(f'{o[1] * 320:.0f},{o[2] * 240:.0f}' + (' hitting' if o[5] > 0 else ''))
    return '; '.join(out) if out else 'none'


def prompt(view, my_moves, opp_moves, inputs, player='?'):
    v = np.asarray(view, np.float32)
    me = CHARACTERS[int(round(float(v[SELF + CHAR])))]
    opp = CHARACTERS[int(round(float(v[OPP + CHAR])))]
    head = (f'{me} (player {player}) vs {opp}. Round {v[ROUND]:.0f}, rounds '
            f'{v[SELF + ROUNDS_WON]:.0f}-{v[OPP + ROUNDS_WON]:.0f}')
    if v[INTRO] > 0:
        head += ', intro'
    if v[ROUND_OVER] > 0:
        head += ', KO'
    dx, dy = v[DX] * 640, v[DY] * 240
    ahead = dx * (1 if v[SELF + FACING] >= 0 else -1)
    gap = (f'Opponent {abs(dx):.0f} px {"ahead" if ahead >= 0 else "behind"}, ' +
           (f'{abs(dy):.0f} px {"above" if dy < 0 else "below"}.' if abs(dy) >= 0.5 else 'level.'))
    before = (f'Before: me {" ".join(move_name(a) for a in my_moves) or "none"}; '
              f'opponent {" ".join(move_name(a) for a in opp_moves) or "none"}.')
    return '\n'.join([
        head + '.', _player(v, SELF, 'Me'), _player(v, OPP, 'Opponent'), gap,
        f'Objects: mine {_objects(v, 0)}; theirs {_objects(v, 1)}.', before,
        f'My inputs: {inputs_text(inputs)}', 'Action:'])


def step_labels(prev, cur):
    """Action indices for a batch of steps: the controls `cur` after `prev` (uint8
    arrays), as efz_env.history.action_labels labels a sequence."""
    from efz_env.actions import BACK, DOWN, FORWARD, UP
    c, p = np.asarray(cur, np.uint8), np.asarray(prev, np.uint8)
    h = ((c & FORWARD) > 0).astype(int) - ((c & BACK) > 0)
    v = ((c & UP) > 0).astype(int) - ((c & DOWN) > 0)
    numpad = 5 + h + 3 * v
    pressed = (c & ~p) >> 4
    button = np.zeros(c.shape, int)
    for b in (3, 2, 1, 0):  # the first that went down wins
        button = np.where((pressed >> b) & 1, b + 1, button)
    return button * 9 + (numpad - 1)  # ActionTable's order: buttons outer, directions inner


class Context:
    """The moves seen and inputs made so far, per environment, as a prompt needs them:
    push each step's view (as seen) and, after the step, its controls."""

    def __init__(self, n, moves=4, history=16):
        self.n, self.moves, self.history = n, moves, history
        self.clear()

    def clear(self, mask=None):
        idx = range(self.n) if mask is None else np.flatnonzero(mask)
        if mask is None:
            self.mine = [[] for _ in range(self.n)]
            self.theirs = [[] for _ in range(self.n)]
            self.inputs = [[] for _ in range(self.n)]
            self.last = np.full((self.n, 2), -1)
            self.prev = np.zeros(self.n, np.uint8)
            return
        for i in idx:
            self.mine[i], self.theirs[i], self.inputs[i] = [], [], []
            self.last[i] = -1
            self.prev[i] = 0

    def view(self, views):
        """This step's views (n, 168), as the player sees them."""
        acts = np.round(views[:, [SELF + ACT, OPP + ACT]]).astype(int)
        for i in range(self.n):
            for k, seq in ((0, self.mine[i]), (1, self.theirs[i])):
                if acts[i, k] != self.last[i, k]:
                    seq.append(int(acts[i, k]))
                    del seq[:-(self.moves + 1)]
        self.last = acts

    def played(self, controls):
        labels = step_labels(self.prev, controls)
        for i in range(self.n):
            self.inputs[i].append(int(labels[i]))
            del self.inputs[i][:-self.history]
        self.prev = np.asarray(controls, np.uint8).copy()

    def prompts(self, views, players):
        return [prompt(views[i], self.mine[i][:-1], self.theirs[i][:-1], self.inputs[i],
                       players[i] if not isinstance(players, str) else players)
                for i in range(self.n)]


def match_context(acts, labels, moves=4, history=16):
    """For training: one player's match, its views' actions as seen (T, 2: its own and
    the opponent's, view[SELF + ACT] and view[OPP + ACT]) and its inputs' labels (T,) ->
    a function of t giving prompt()'s (my_moves, opp_moves, inputs) as Context would
    have them at step t."""
    acts = np.asarray(acts).astype(int)
    changes = [np.flatnonzero(acts[:, k] != np.concatenate([[-1], acts[:-1, k]])) for k in (0, 1)]

    def at(t):
        out = []
        for k in (0, 1):
            j = int(np.searchsorted(changes[k], t, side='right'))  # changes up to t
            out.append([int(a) for a in acts[changes[k][max(0, j - moves - 1):j - 1], k]])
        return out[0], out[1], [int(a) for a in labels[max(0, t - history):t]]
    return at
