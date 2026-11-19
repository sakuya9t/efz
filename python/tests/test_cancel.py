"""runs/human-ayu/cancel.py, the module 'cancel': a risky move seen guarded is cancelled
with 22C when the gauge is there, once a move, and not when it hit."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import cancel
    from efz_env import modules
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

M623B, GUARD, RECOIL, HIT = 0xfc, 0x96, 0xa8, 0x32


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Cancel(unittest.TestCase):
    def module(self, **options):
        m = modules.REGISTRY['cancel'](None, 'batch', {}, options, None)
        m.batch(1)
        return m

    def run_steps(self, m, steps, rf=0.6, blue=False):
        """steps: (its own action, the opponent's, itself hit) as it sees them."""
        out = []
        for a, o, *hit in steps:
            v = np.zeros(168, np.float32)
            v[cancel.SELF_ACT], v[cancel.OPP_ACT] = a, o
            v[cancel.OPP_HITSTUN] = float(o == HIT)
            v[cancel.SELF_HITSTUN] = float(bool(hit and hit[0]))
            v[cancel.SELF_RF], v[cancel.SELF_RF_BLUE] = rf, float(blue)
            ctx = modules.Context(v, v)
            m.watch(0, ctx)
            out.append(m.act(0, ctx))
        return out

    def test_a_guarded_623b_with_the_gauge_gets_22c_once(self):
        m = self.module()
        got = self.run_steps(m, [(M623B, 0)] * 2 + [(M623B, GUARD)] * 6 + [(0xa7, 0)] * 2)
        self.assertEqual(got, [None, None] + list(cancel.MOTION) + [None] * 4)
        self.assertEqual([cancel.TABLE.describe(a) for a in cancel.MOTION], ['2', '5', '2C', '2C'])
        self.assertEqual(m.stats(), dict(guarded=1, no_gauge=0, tried=1, came=1))

    def test_not_without_the_gauge_not_on_a_hit_and_not_another_move(self):
        m = self.module()
        self.assertEqual(self.run_steps(m, [(M623B, GUARD)] * 3, rf=0.4), [None] * 3)
        self.assertEqual(m.stats()['no_gauge'], 1)
        self.assertEqual(self.run_steps(m, [(0, 0), (M623B, GUARD)], rf=0.1, blue=True)[1],
                         cancel.MOTION[0])                   # cyan: it has one
        m = self.module()
        self.assertEqual(self.run_steps(m, [(M623B, HIT)] * 3), [None] * 3)
        self.assertEqual(self.run_steps(m, [(0xfb, GUARD)] * 3), [None] * 3)   # 623C: not named
        self.assertEqual(m.stats()['guarded'], 0)
        m = self.module(moves='623C')
        self.assertEqual(self.run_steps(m, [(0xfb, GUARD)])[0], cancel.MOTION[0])
        with self.assertRaises(ValueError):
            self.module(moves='5A')

    def test_a_recoil_guard_by_option_and_it_lets_go_when_hit(self):
        m = self.module(rg=False)
        self.assertEqual(self.run_steps(m, [(M623B, RECOIL)] * 2), [None] * 2)
        m = self.module()
        got = self.run_steps(m, [(M623B, RECOIL), (M623B, RECOIL), (0x32, 0, True), (0x32, 0, True)])
        self.assertEqual(got, [cancel.MOTION[0], cancel.MOTION[1], None, None])
        m.reset()
        self.assertFalse(m.playing)


if __name__ == '__main__':
    unittest.main()
