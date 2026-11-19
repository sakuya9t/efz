"""runs/human-ayu/risk.py, the module 'risk': a raw special of the agent's own play let out
or stopped at its input by how that move has paid in the match."""

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
class Risk(unittest.TestCase):
    DELAY = 3

    def module(self, **options):
        self.copy = Copy()
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
        m = self.module()
        for name, want in (('623B', 0.987), ('236236A', 0.957), ('623A', 0.917), ('236B', 0.852),
                           ('236C', 0.012), ('623C', 0.0004)):
            self.assertAlmostEqual(m.chance(0, name), want, delta=0.003, msg=name)

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
        self.assertAlmostEqual(m.chance(0, '236C'), 0.48, delta=0.02)   # (333 x 4 - 1300) / 5: 6 HP
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
        self.assertAlmostEqual(m.chance(0, '236C'), 0.012, delta=0.003)  # another opponent


if __name__ == '__main__':
    unittest.main()
