"""How combos end and what a throw is, as runs/human-ayu counts them (tactics.endings,
tactics.grabs: evaluate.py's combo_ends and grabs), and the scripted opponents' air
recovery (advantages.py's tech)."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import advantages
    import tactics
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

N = len(tactics.OBS) if not MISSING else 0
# (the opponents' moves, made on each machine from the game: not in the repository)
NO_MOVES = not os.path.exists(os.path.join(RUNS, 'motions.json'))
ME_ACT, OPP_ACT, ME_STUN, OPP_STUN, ME_AIR, OPP_AIR, ME_HP, OPP_HP, DX = 0, 1, 4, 5, 6, 7, 14, 15, 18


def match(T=400):
    c = np.zeros((T, N), np.float32)
    c[:, ME_HP] = c[:, OPP_HP] = 1.0
    c[:, DX] = 60 / 640
    return c


def combo(c, at, steps, then, damage=0.2, air=True):
    """The viewer's combo on the opponent from `at`: an air hit reaction for `steps`, then
    the action `then` for 30 steps."""
    c[at:at + steps, OPP_ACT] = 0x3b
    c[at:at + steps, OPP_STUN] = 1
    c[at:at + steps + 30, OPP_AIR] = float(air)
    c[at + steps:at + steps + 30, OPP_ACT] = then
    c[at + 2:, OPP_HP] -= damage


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Endings(unittest.TestCase):
    def sides(self, c):
        live = np.ones(len(c), bool)
        return tactics.Side(c, 0), tactics.Side(c, 1), live

    def test_a_knockdown_a_recovery_and_a_standing_end(self):
        c = match(600)
        combo(c, 20, 30, 0x62)               # lies
        combo(c, 120, 30, 0x9e)              # recovers in the air
        c[450:460, OPP_ACT], c[450:460, OPP_STUN] = 0x32, 1  # a ground hit, then standing
        c[451:, OPP_HP] -= 0.01
        me, opp, live = self.sides(c)
        got = tactics.endings(me, opp, live)
        self.assertEqual([r['kind'] for r in got], ['knockdown', 'recovery', 'standing'])
        self.assertAlmostEqual(got[0]['damage'], 0.2 * 9999, delta=1)
        self.assertEqual(got[1]['next'], 'nothing')
        self.assertFalse(got[1]['busy'])
        rep = tactics.endings_report(got)
        self.assertEqual((rep['n'], rep['n_big']), (3, 2))
        self.assertEqual(rep['big']['knockdown'], 0.5)
        self.assertEqual(rep['big']['recovery'], 0.5)

    def test_hit_again_lying_is_the_same_combo_and_who_is_hit_after_a_recovery(self):
        c = match()
        combo(c, 20, 30, 0x61)               # lies, hittable ...
        c[55:70, OPP_ACT], c[55:70, OPP_STUN] = 0x3b, 1   # ... and is hit again
        c[70:100, OPP_ACT] = 0x9d            # then recovers
        c[70:75, ME_ACT] = 0xc9              # the viewer still in a move
        c[90:100, ME_STUN] = 1               # and hit first after it
        me, opp, live = self.sides(c)
        got = tactics.endings(me, opp, live)
        self.assertEqual(len(got), 1)
        self.assertEqual((got[0]['kind'], got[0]['busy'], got[0]['next']),
                         ('recovery', True, 'hit back'))

    def test_throws_and_chances(self):
        c = match()
        c[:, DX] = 30 / 640                  # within a throw's reach, both free: a chance
        c[100:110, ME_ACT] = 0xdc            # a throw tried
        c[110:120, ME_ACT] = 0xdd            # ... that caught
        c[200:230, ME_AIR] = c[200:230, OPP_AIR] = 1
        c[210:215, ME_ACT] = 0xf8            # an air throw tried (not Ayu: 0xf8), missed
        me, opp, live = self.sides(c)
        g = tactics.grabs(me, opp, c[:, DX], live)[0]
        self.assertEqual((g['throw_tries'], g['throws'], g['air_tries'], g['air_throws']),
                         (1, 1, 1, 0))
        self.assertGreaterEqual(g['throw_chances'], 1)
        self.assertGreaterEqual(g['air_chances'], 1)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
@unittest.skipIf(NO_MOVES, 'no runs/human-ayu/motions.json: python runs/human-ayu/motions.py makes it')
class Tech(unittest.TestCase):
    def view(self, act=0, air=False):
        v = np.zeros(168, np.float32)
        v[advantages.SELF_ACT] = act
        v[advantages.SELF_AIRBORNE] = float(air)
        v[advantages.DX] = 300 / 640
        return v

    def test_it_presses_back_and_a_button_every_other_step_in_the_air(self):
        self.assertEqual(advantages.parse('tech=0.9')['tech'], 0.9)
        logic = advantages.Advantages('mai', 1, tech=1.0)
        logic.clear(0)
        self.assertIsNone(logic.step(0, self.view()))
        got = [logic.step(0, self.view(0x3b, air=True)) for _ in range(4)]
        self.assertEqual(got, [(4, 'A'), (4, ''), (4, 'A'), (4, '')])
        self.assertIsNone(logic.step(0, self.view(0x32)))        # hit on the ground: nothing
        logic.step(0, self.view(0x3b, air=True))
        logic.step(0, self.view(0x9e, air=True))                 # it recovered
        self.assertEqual(logic.take()['recoveries'], 1)

    def test_none_of_it_at_zero(self):
        logic = advantages.Advantages('mai', 1)
        logic.clear(0)
        self.assertIsNone(logic.step(0, self.view(0x3b, air=True)))
