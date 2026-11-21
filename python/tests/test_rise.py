"""runs/human-ayu/rise.py, the module 'rise': the agent's wake-up guarded through once
its wake-up moves have cost it in this match, and its moves back once its guard has."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import rise
    from efz_env import modules
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

LYING, SUPER, MOVE, HIT = 0x62, 0x13b, 0xfb, 0x3b


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Rise(unittest.TestCase):
    def module(self, **options):
        m = modules.REGISTRY['rise'](None, 'batch', {}, dict(window=30, **options), None)
        m.batch(1)
        self.hp = [1.0, 1.0]
        return m

    def run_steps(self, m, steps, policy=None):
        """steps: (its own action as it sees it, its HP lost on the step, the opponent's,
        the opponent in the air)."""
        out = []
        for a, mine, *rest in steps:
            self.hp[0] -= mine / rise.HP
            self.hp[1] -= (rest[0] if rest else 0) / rise.HP
            v = np.zeros(168, np.float32)
            v[rise.SELF_ACT], v[rise.SELF_HP], v[rise.OPP_HP] = a, self.hp[0], self.hp[1]
            v[rise.OPP_AIR] = float(len(rest) > 1 and rest[1])
            v[rise.SELF_GAUGE] = getattr(self, 'gauge', 0.4)     # (one bar and a little)
            v[rise.DX] = getattr(self, 'dx', 400) / rise.PIXELS   # (the attacker far, unless set)
            v[rise.OPP_ACT] = getattr(self, 'opp_act', 0)
            ctx = modules.Context(v, v, hist=np.zeros((16, 6), np.float32), policy=policy)
            m.watch(0, ctx)
            out.append(m.act(0, ctx))
        return out

    def wake_up(self, m, move, lost=0, dealt=0):
        """A knockdown, a rising with `move` (or none), and what it cost and took."""
        self.run_steps(m, [(LYING, 0)] * 5 + [(move or 0, 0)] * 3 + [(HIT if lost else 0, lost, dealt)]
                       + [(0, 0)] * 30)

    def test_nothing_changes_until_a_wake_up_move_was_punished(self):
        m = self.module(moves=True)
        self.assertAlmostEqual(m.chance(0), 0.015, delta=0.003)
        self.wake_up(m, MOVE, lost=1300)
        self.assertEqual(m.stats()['move'], dict(n=1, swing=-1300))
        self.assertAlmostEqual(m.chance(0), 0.42, delta=0.02)
        self.wake_up(m, MOVE, lost=1300)
        self.assertAlmostEqual(m.chance(0), 0.90, delta=0.02)
        self.assertEqual(m.stats()['still']['n'], 0)

    def test_a_move_that_hit_and_a_guard_that_was_opened(self):
        m = self.module(moves=True)
        self.wake_up(m, MOVE, dealt=1500)                   # the reversal hit:
        self.assertLess(m.chance(0), 0.001)
        m = self.module(moves=True)
        self.wake_up(m, MOVE, lost=1300)
        self.wake_up(m, MOVE, lost=1300)
        before = m.chance(0)
        self.wake_up(m, None, lost=1300)                     # then its guard is opened:
        self.wake_up(m, None, lost=1300)
        self.assertEqual(m.stats()['still'], dict(n=2, swing=-1300))
        self.assertLess(m.chance(0), before - 0.3)           # the move is back

    def test_a_rising_guarded_through(self):
        m = self.module(moves=True)
        m.count[0, rise.MOVE], m.total[0, rise.MOVE] = 3, -5000   # (its moves have cost it)
        got = self.run_steps(m, [(0, 0)] + [(LYING, 0)] * 3 + [(LYING, 0, 0, True)] + [(0, 0)] * 2)
        self.assertEqual(got, [None] + [rise.CROUCH_GUARD] * 3 + [rise.STAND_GUARD] + [None] * 2)
        self.assertEqual((m.stats()['knockdowns'], m.stats()['guarded']), (1, 1))
        # Its own play's guard and jump back are kept; a button or a step forward is not.
        for own, kept in (((4, ''), True), ((7, ''), True), ((6, ''), False), ((1, 'A'), False)):
            m = self.module(moves=True)
            m.count[0, rise.MOVE], m.total[0, rise.MOVE] = 3, -5000
            a = rise.INDEX[own]
            got = self.run_steps(m, [(LYING, 0)] * 2, policy=lambda x: np.array([a]))
            self.assertEqual(got, [a if kept else rise.CROUCH_GUARD] * 2)
            self.assertEqual(m.stats()['kept'], 2 if kept else 0)

    def test_guard_by_sight_when_the_attacker_is_on_it(self):
        press = rise.INDEX[(6, 'A')]
        own = lambda x: np.array([press])
        # The attacker far and not in a move: its own play, whatever `guard` says.
        m = self.module(guard=True, seed=1)
        self.assertEqual(self.run_steps(m, [(LYING, 0)] * 3, policy=own), [press] * 3)
        self.assertEqual(m.stats()['met'], 0)
        # Near, in a move of its own, or in the air within reach: drawn once, 87% guarded.
        m = self.module(guard=True)
        self.assertAlmostEqual(m.guard_chance(0), 0.867, delta=0.001)
        for dx, act, air, want in ((100, 0, False, rise.CROUCH_GUARD), (400, 0xd0, False, rise.CROUCH_GUARD),
                                   (180, 0, True, rise.STAND_GUARD), (300, 0, True, press)):
            m = self.module(guard=True, near=130, seed=1)
            self.dx, self.opp_act = dx, act
            got = self.run_steps(m, [(LYING, 0, 0, air)] * 3 + [(0, 0)], policy=own)
            self.assertEqual(got, [want] * 3 + [None], (dx, act, air))
            self.assertEqual(m.stats()['met'], int(want != press))
        # Merely near is not on it unless `near` says so.
        m = self.module(guard=True, seed=1)
        self.dx, self.opp_act = 100, 0
        self.assertEqual(self.run_steps(m, [(LYING, 0)] * 3, policy=own), [press] * 3)
        # Held by sight: standing while the attacker is seen in the air, crouching once it
        # is seen landed; its own play's guard kept on the ground, its jump back not.
        for a, ground in (((4, ''), rise.STAND_GUARD), ((7, ''), rise.CROUCH_GUARD), ((1, ''), rise.CROUCH_GUARD)):
            m = self.module(guard=True, near=130, seed=1)
            self.dx, self.opp_act = 100, 0
            got = self.run_steps(m, [(LYING, 0, 0, True)] * 2 + [(LYING, 0)] * 2, policy=lambda x: np.array([rise.INDEX[a]]))
            self.assertEqual(got, [rise.STAND_GUARD] * 2 + [ground] * 2)
        self.assertEqual(m.stats()['stood'], 2)
        del self.dx, self.opp_act

    def test_the_guard_goes_on_while_the_attacker_does(self):
        press = rise.INDEX[(6, 'A')]
        own = lambda x: np.array([press])
        # Up with the attacker still in a move: the guard goes on, standing while it is
        # seen in the air; eight steps without the attacker going on and its own play is back.
        m = self.module(guard=True, hold=40, seed=1)
        self.dx, self.opp_act = 100, 0xd0
        got = self.run_steps(m, [(LYING, 0)] * 3 + [(0, 0)] * 4 + [(0, 0, 0, True)] * 2, policy=own)
        self.assertEqual(got, [rise.CROUCH_GUARD] * 7 + [rise.STAND_GUARD] * 2)
        self.opp_act, self.dx = 0, 300
        got = self.run_steps(m, [(0, 0)] * 10, policy=own)
        self.assertEqual(got, [rise.CROUCH_GUARD] * 7 + [None] * 3)
        self.assertEqual(m.stats()['held'], 13)
        # Hit while it holds: let go. And at most `hold` steps.
        m = self.module(guard=True, hold=40, seed=1)
        self.dx, self.opp_act = 100, 0xd0
        got = self.run_steps(m, [(LYING, 0)] * 3 + [(0, 0)] * 2 + [(HIT, 500)] + [(0, 0)] * 2, policy=own)
        self.assertEqual(got, [rise.CROUCH_GUARD] * 5 + [None] * 3)
        m = self.module(guard=True, hold=5, seed=1)
        self.dx, self.opp_act = 100, 0xd0
        got = self.run_steps(m, [(LYING, 0)] * 3 + [(0, 0)] * 8, policy=own)
        self.assertEqual(got, [rise.CROUCH_GUARD] * 8 + [None] * 3)
        # Without `hold`: its own play as soon as it sees itself up.
        m = self.module(guard=True, seed=1)
        self.dx, self.opp_act = 100, 0xd0
        got = self.run_steps(m, [(LYING, 0)] * 3 + [(0, 0)] * 2, policy=own)
        self.assertEqual(got, [rise.CROUCH_GUARD] * 3 + [None] * 2)
        del self.dx, self.opp_act

    def test_the_guard_is_as_frequent_as_the_attacker_is_there(self):
        # An attacker that leaves its rising alone (no move of its own as the agent sees
        # itself up): one rising, a quarter guarded; two, none. What the agent did, and
        # what it cost, has no part in it.
        m = self.module(guard=True)
        self.wake_up(m, None)
        self.assertAlmostEqual(m.rate(0), 1.12 / 3, delta=1e-6)
        self.assertAlmostEqual(m.guard_chance(0), 0.244, delta=0.001)
        self.wake_up(m, MOVE, lost=1300)
        self.assertEqual(m.guard_chance(0), 0.0)
        self.assertEqual((m.stats()['risings'], m.stats()['attacked']), (2, 0))
        # One that is in a move each time: all guarded from the first.
        m = self.module(guard=True)
        self.opp_act = 0xd0
        self.wake_up(m, None, dealt=900)
        self.assertEqual(m.guard_chance(0), 1.0)
        self.assertEqual((m.stats()['risings'], m.stats()['attacked']), (1, 1))
        # ... and what it showed lasts into the next match, older.
        m = self.module(guard=True, carry=True)
        self.wake_up(m, None)
        self.wake_up(m, None)
        m.reset()
        self.assertAlmostEqual(m.seen[0], 1.4)
        self.assertAlmostEqual(m.on[0], 1.4)
        del self.opp_act
        # The rates between which it goes from none to all are options.
        self.assertEqual(self.module(guard=True, low=0.6, high=0.9).guard_chance(0), 0.0)
        self.assertEqual(self.module(guard=True, low=0.0, high=0.5).guard_chance(0), 1.0)

    def test_the_wake_up_super_is_seen_coming_in_its_own_inputs(self):
        self.assertEqual(rise.sweeps([2, 3, 6, 2, 3, 6]), 2)
        self.assertEqual(rise.sweeps([6, 4, 1, 2, 3, 6]), 1)      # 641236
        self.assertEqual(rise.sweeps([6, 2, 3]), 0)               # 623
        inputs = [(2, ''), (3, ''), (6, ''), (2, ''), (3, ''), (6, 'A'), (6, 'A'), (6, '')]
        play = lambda m: self.run_steps(
            m, [(LYING, 0)] * len(inputs),
            policy=(lambda seq: lambda x: np.array([rise.INDEX[next(seq)]]))(iter(inputs)))
        m = self.module()                                         # (the prior: stopped)
        got = play(m)
        self.assertEqual(got[:5], [rise.INDEX[a] for a in inputs[:5]])   # its own inputs, played
        self.assertEqual(got[5:], [rise.CROUCH_GUARD] * 3)        # the press and after: a guard
        self.assertEqual((m.stats()['supers'], m.stats()['stopped']), (1, 1))
        m = self.module(super=5000)                               # (an account that says it pays)
        self.assertEqual(play(m), [rise.INDEX[a] for a in inputs])
        self.assertEqual((m.stats()['supers'], m.stats()['stopped']), (1, 0))
        self.gauge = 0.7                                          # two bars: C is level two,
        m = self.module()
        self.assertEqual(play(m)[5:], [rise.CROUCH_GUARD] * 3)    # A is still level one;
        self.assertEqual(m.stats()['supers'], 1)
        inputs = [(a, 'C' if b else '') for a, b in inputs]
        m = self.module()
        self.assertEqual(play(m), [rise.INDEX[a] for a in inputs])   # not the one
        self.assertEqual(m.stats()['supers'], 0)
        self.gauge = 0.4                                          # one bar: C is the one
        m = self.module()
        self.assertEqual(play(m)[5:], [rise.CROUCH_GUARD] * 3)
        m = self.module()                                         # 641236A: not its business
        other = [(6, ''), (4, ''), (1, ''), (2, ''), (3, ''), (6, 'A')]
        got = self.run_steps(m, [(LYING, 0)] * 6, policy=(
            lambda seq: lambda x: np.array([rise.INDEX[next(seq)]]))(iter(other)))
        self.assertEqual(got, [rise.INDEX[a] for a in other])
        self.assertEqual(m.stats()['supers'], 0)
        # A wake-up super that came out goes to its own account, not the moves'.
        m = self.module()
        self.wake_up(m, SUPER, lost=1300)
        self.assertEqual((m.stats()['super'], m.stats()['move']['n']),
                         (dict(n=1, swing=-1300), 0))

    def test_the_class_is_left_alone_unless_asked(self):
        m = self.module()
        m.count[0, rise.MOVE], m.total[0, rise.MOVE] = 3, -5000   # (its moves have cost it)
        self.assertEqual(self.run_steps(m, [(LYING, 0)] * 4), [None] * 4)
        self.assertEqual(m.stats()['guarded'], 0)

    def test_not_drawn_without_cause_and_a_new_match(self):
        m = self.module(moves=True)
        m.count[0, rise.MOVE], m.total[0, rise.MOVE] = 3, 5000    # (its moves pay)
        self.assertEqual(self.run_steps(m, [(LYING, 0)] * 4), [None] * 4)
        m.reset()
        self.assertEqual(m.count[0, rise.MOVE], 0)                # another opponent
        m = self.module(moves=True, carry=True)
        self.wake_up(m, MOVE, lost=1300)
        m.reset()                                                 # the same one: kept, older
        self.assertAlmostEqual(m.count[0, rise.MOVE], 0.7)
        self.assertAlmostEqual(m.total[0, rise.MOVE], -910, delta=1)
        with self.assertRaises(ValueError):
            modules.REGISTRY['rise'](None, 'batch', {}, dict(nope=1), None)


if __name__ == '__main__':
    unittest.main()
