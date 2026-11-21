"""runs/human-ayu/risk.py, the module 'risk': a raw special of the agent's own play let out
or stopped at its input by how that move has paid in the match."""

import math
import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import risk
    from efz_env import modules
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

HIT = 0x3b


class Copy:
    """A game's copy for the module: the press starts `move` (the agent's action `after`
    frames on), or nothing."""

    def __init__(self):
        self.move, self.after, self.loaded, self.pressed = 0, 1, 0, []

    def load_state(self, i, state):
        self.loaded += 1
        self.frame = 0

    def step(self, controls):
        self.pressed.append(int(controls[0, 0]))
        self.frame += 1
        obs = np.zeros((1, 2, 168), np.float32)
        obs[0, 0, risk.SELF_ACT] = self.move if self.frame >= self.after else self.now
        return (obs,)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Sure:
    """A draw that stops (True) or lets (False) whatever the chance."""

    def __init__(self, stop):
        self.stop = stop

    def random(self):
        return 0.0 if self.stop else 1.0


class Risk(unittest.TestCase):
    DELAY = 3

    # (worths the cases below are written for: a move worth its risk, 623C; one that
    # loses, 623B; one that loses a little, 236B; the module's own are measurements)
    PRIORS = {'236B': -131, '236C': 333, '623B': -326, '623C': 580}

    def module(self, own=False, **options):
        self.copy = Copy()
        if not own:
            options.setdefault('priors', self.PRIORS)
        m = risk.Risk(None, None, self.DELAY, sim=self.copy, **options)
        m.batch(1)
        self.hp = [1.0, 1.0]
        return m

    def step(self, m, action, act=0, lost=0, dealt=0, opp_hit=False):
        """A step: its own play's action, what it sees itself in, the HP either lost."""
        self.hp[0] -= lost / risk.HP
        self.hp[1] -= dealt / risk.HP
        v = np.zeros(168, np.float32)
        v[risk.SELF_ACT], v[risk.SELF_HP], v[risk.OPP_HP] = act, self.hp[0], self.hp[1]
        v[risk.OPP_HITSTUN], v[risk.OPP_ACT] = float(opp_hit), HIT if opp_hit else 0
        now = np.zeros(168, np.float32)
        now[risk.SELF_ACT] = self.copy.now = getattr(self, 'now', 0)
        ctx = modules.Context(v, now, hist=np.zeros((4, 6), np.float32), save=lambda: b'state',
                              policy=lambda x: np.array([action]))
        m.watch(0, ctx)
        return m.act(0, ctx)

    def use(self, m, name, lost=0, dealt=0):
        """A press that starts `name` let out (the account's own draw aside), seen, and
        what it cost and took; then nothing for the rest of its window."""
        press = risk.INDEX[(6, 'B')]
        self.copy.move = risk.MOVES[name]
        m.drawn[0] = (name, int(m.t[0]) + 1, False)  # (let out: the same press, drawn already)
        m.open[0] = [name, 0, self.hp[0] * risk.HP, self.hp[1] * risk.HP, False]
        self.step(m, press)
        self.copy.move = 0
        for k in range(m.window):
            self.step(m, risk.INDEX[(5, '')], act=risk.MOVES[name] if 2 < k < 12 else 0,
                      lost=lost if k == 20 else 0, dealt=dealt if k == 20 else 0)

    def test_the_priors(self):
        m = self.module(own=True)
        # (a move stopped with the chance 1 / (1 + exp(its worth / 75)): its prior, unused)
        for name in ('623B', '236236A', '623A', '236B', '236C', '623C'):
            want = 1 / (1 + math.exp(risk.PRIORS[name] / 75))
            self.assertAlmostEqual(m.chance(0, name), want, delta=0.003, msg=name)
        self.assertGreater(m.chance(0, '236B'), 0.99)   # what loses against a combo: nearly never
        self.assertAlmostEqual(m.chance(0, '236C'), 0.34, delta=0.01)  # the gamble: one in three stopped

    def jump_step(self, m, action, air=False, lost=0, dealt=0, dx=100, now_air=False, opp_hit=False):
        """A step for the jump's account: its own play's action; what it sees (itself in
        the air or not, the distance, both HP) and the game as it is (in the air or not)."""
        self.hp[0] -= lost / risk.HP
        self.hp[1] -= dealt / risk.HP
        v = np.zeros(168, np.float32)
        v[risk.SELF_AIR], v[risk.DX] = float(air), dx / risk.PIXELS
        v[risk.SELF_HP], v[risk.OPP_HP] = self.hp
        v[risk.OPP_HITSTUN], v[risk.OPP_ACT] = float(opp_hit), HIT if opp_hit else 0
        now = np.zeros(168, np.float32)
        now[risk.SELF_AIR] = float(now_air)
        now[risk.SELF_ACT] = getattr(self, 'now', 0)
        ctx = modules.Context(v, now, hist=np.zeros((4, 6), np.float32), save=lambda: b'state',
                              policy=lambda x: np.array([action]))
        m.watch(0, ctx)
        return m.act(0, ctx)

    def jump(self, m, lost=0, dealt=0):
        """A jump at the opponent let out (the account's own draw aside), seen, and followed
        to its window's end."""
        up = risk.INDEX[(9, '')]
        m.jdrawn[0] = None
        m.rng = Sure(False)
        self.assertEqual(self.jump_step(m, up), up)
        for k in range(m.jump_window):
            self.jump_step(m, risk.INDEX[(5, '')], air=2 < k < 40, lost=lost if k == 50 else 0,
                           dealt=dealt if k == 50 else 0, now_air=2 < k < 40)

    def test_the_jump_at_the_opponent_by_how_it_has_paid(self):
        up, forward, idle = risk.INDEX[(9, '')], risk.INDEX[(6, '')], risk.INDEX[(5, '')]
        m = self.module()  # (no account of the jump: its own)
        self.assertEqual(self.jump_step(m, up), up)
        self.assertNotIn('jump', m.stats())
        m = self.module(jump=250.0)
        self.assertAlmostEqual(m.jump_chance(0), 1 / (1 + math.exp(250 / 100)), places=6)
        # Jumps that lose: the account turns, and a stopped jump is the same without up.
        for _ in range(8):
            self.jump(m, lost=900)
        self.assertEqual(m.stats()['jump']['n'], 8)
        self.assertEqual(m.stats()['jump']['swing'], -900)
        worth = (250 * 6 - 900 * 8) / 14  # (its prior counts as 6 jumps)
        self.assertAlmostEqual(m.jump_chance(0), 1 / (1 + math.exp(worth / 100)), places=6)
        self.assertGreater(m.jump_chance(0), 0.98)
        m.rng, m.jdrawn[0] = Sure(True), None
        self.assertEqual(self.jump_step(m, up), forward)
        self.assertEqual(self.jump_step(m, risk.INDEX[(9, 'A')]), risk.INDEX[(6, 'A')])  # (the same press)
        # Not its jump at the opponent: far away, in the air already, not free, a combo it sees; another direction.
        for kw in (dict(dx=500), dict(now_air=True), dict(opp_hit=True)):
            self.assertEqual(self.jump_step(m, up, **kw), up, kw)
        self.now = 0xcc
        self.assertEqual(self.jump_step(m, up), up)
        del self.now
        for other in (risk.INDEX[(8, '')], risk.INDEX[(7, '')], idle):
            self.assertEqual(self.jump_step(m, other), other)
        # Jumps that pay bring it back; another opponent: the prior again.
        for _ in range(30):
            self.jump(m, dealt=1200)
        self.assertLess(m.jump_chance(0), 0.01)
        m.reset()
        self.assertAlmostEqual(m.jump_chance(0), 1 / (1 + math.exp(250 / 100)), places=6)
        # A press that started no jump it saw is not counted.
        n = m.stats()['jump']['n']
        m.rng, m.jdrawn[0] = Sure(False), None
        self.jump_step(m, up)
        for _ in range(m.jump_window):
            self.jump_step(m, idle, lost=10)
        self.assertEqual(m.stats()['jump']['n'], n)

    def test_a_stopped_jump_stays_stopped_for_its_hold(self):
        up, forward, idle = risk.INDEX[(9, '')], risk.INDEX[(6, '')], risk.INDEX[(5, '')]
        for hold, later in ((0, up), (40, forward)):
            m = self.module(jump=250.0, jump_hold=hold)
            m.rng = Sure(True)
            self.assertEqual(self.jump_step(m, up), forward)
            m.rng = Sure(False)  # (the next draw would let it out)
            for _ in range(20):  # (longer than the same press)
                self.jump_step(m, idle)
            # Asked for again 21 steps after the stop: a new draw without a hold, the stop with one.
            self.assertEqual(self.jump_step(m, up), later, hold)
            self.assertEqual(m.stats()['jump']['seen'], 2 if hold == 0 else 1)
            for _ in range(20):
                self.jump_step(m, idle)
            self.assertEqual(self.jump_step(m, up), up, hold)  # 42 steps after it: drawn anew
        # A jump let out is not held: the next one is its own draw.
        m = self.module(jump=250.0, jump_hold=40)
        m.rng = Sure(False)
        self.assertEqual(self.jump_step(m, up), up)
        m.rng = Sure(True)
        for _ in range(20):
            self.jump_step(m, idle)
        self.assertEqual(self.jump_step(m, up), forward)

    def test_a_press_that_starts_nothing_risky_is_its_own(self):
        m = self.module()
        plain, press = risk.INDEX[(5, '')], risk.INDEX[(2, 'A')]
        self.assertEqual(self.step(m, plain), plain)
        self.assertEqual(self.copy.loaded, 0)          # no button: no copy
        self.assertEqual(self.step(m, press), press)   # a button that starts a normal
        self.assertEqual(self.copy.pressed, [risk.TABLE.table[press]] + [0] * 9)  # then nothing
        self.copy.move = risk.MOVES['623B']
        self.assertEqual(self.step(m, press, opp_hit=True), press)  # a combo it has seen
        self.assertEqual(self.copy.loaded, 1)
        self.assertEqual(m.stats(), {})

    def test_a_losing_move_is_stopped_and_the_button_left_out(self):
        m = self.module(seed=1)
        press = risk.INDEX[(6, 'B')]
        self.copy.move = risk.MOVES['623B']
        got = [self.step(m, press) for _ in range(5)]
        self.assertEqual(got, [risk.INDEX[(6, '')]] * 5)   # the same direction, nothing pressed
        self.assertEqual(m.stats()['623B'], dict(seen=1, stopped=1, let=0, came=0, n=0, swing=None))
        # A move worth its risk comes out, and is followed once from its first press.
        self.copy.move = risk.MOVES['623C']
        self.assertEqual([self.step(m, press) for _ in range(3)], [press] * 3)
        self.assertEqual(m.stats()['623C']['let'], 1)

    def test_a_press_the_game_keeps_and_one_made_while_down(self):
        press, stopped = risk.INDEX[(6, 'B')], risk.INDEX[(6, '')]
        # In a normal, the special comes out 8 frames on: seen on the copy, stopped.
        m = self.module(seed=1)
        self.now, self.copy.move, self.copy.after = 0xc9, risk.MOVES['623B'], 8
        self.assertEqual(self.step(m, press), stopped)
        # 20 frames on is past what it looks at standing, and within it while down.
        m = self.module(seed=1)
        self.copy.move, self.copy.after = risk.MOVES['623B'], 20
        self.assertEqual(self.step(m, press), press)
        self.now = 0x62
        self.assertEqual(self.step(m, press), stopped)
        # The move it is already in is not one this press starts.
        m = self.module(seed=1)
        self.now, self.copy.move, self.copy.after = risk.MOVES['623B'], risk.MOVES['623B'], 1
        self.assertEqual(self.step(m, press), press)
        del self.now

    def test_the_accounts(self):
        m = self.module()
        before = m.chance(0, '236C')
        self.use(m, '236C', lost=1300)
        self.assertEqual(m.stats()['236C'], dict(seen=0, stopped=0, let=0, came=1, n=1, swing=-1300))
        worth = (self.PRIORS['236C'] * 4 - 1300) / 5  # (its prior counts as 4 uses)
        self.assertAlmostEqual(m.chance(0, '236C'), 1 / (1 + math.exp(worth / 75)), delta=0.02)
        self.use(m, '236C', lost=1300)
        self.assertGreater(m.chance(0, '236C'), 0.9)
        self.assertGreater(m.chance(0, '236C'), before)
        # One that hits comes back.
        m = self.module()
        self.use(m, '236B', dealt=1500)
        self.use(m, '236B', dealt=1500)
        self.assertLess(m.chance(0, '236B'), 0.01)
        # A press that started nothing it saw is not counted.
        m = self.module()
        press = risk.INDEX[(6, 'C')]
        self.copy.move = risk.MOVES['236C']
        m.rng = np.random.default_rng(3)
        self.step(m, press)
        self.copy.move = 0
        for _ in range(m.window):
            self.step(m, risk.INDEX[(5, '')], lost=10)
        self.assertEqual(m.stats()['236C']['n'], 0)

    def test_a_new_match(self):
        m = self.module(carry=True)
        self.use(m, '236C', lost=1300)
        kept = m.chance(0, '236C')
        m.reset()
        self.assertLess(m.chance(0, '236C'), kept)       # older: counts for less
        self.assertGreater(m.chance(0, '236C'), 0.1)
        m = self.module()
        self.use(m, '236C', lost=1300)
        m.reset()
        self.assertAlmostEqual(m.chance(0, '236C'), 1 / (1 + math.exp(self.PRIORS['236C'] / 75)),
                               delta=0.003)  # another opponent


if __name__ == '__main__':
    unittest.main()
