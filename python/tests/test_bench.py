"""runs/human-ayu's benchmark suite: every number's error by the jackknife
(evaluate.spread) and the scoreboard's arithmetic (bench.py)."""

import json
import math
import os
import sys
import tempfile
import unittest

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import bench
    import evaluate
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Spread(unittest.TestCase):
    def test_a_mean_s_error_is_the_usual_one(self):
        # The jackknife of a mean over K values is their standard error.
        x = [1.0, 2.0, 4.0, 7.0]
        full = dict(win=sum(x) / 4)
        without = [dict(win=(sum(x) - v) / 3) for v in x]
        mean = sum(x) / 4
        usual = math.sqrt(sum((v - mean) ** 2 for v in x) / 3 / 4)
        self.assertAlmostEqual(evaluate.spread(full, without)['win'], usual, places=2)

    def test_the_tree_s_shape_and_what_has_no_error(self):
        full = dict(win=0.5, sides=[dict(a=dict(b=2.0, name='x', none=None), n=[1, 2])], flag=True)
        without = [dict(win=0.4, sides=[dict(a=dict(b=1.0, name='x', none=None), n=[1, 2])], flag=True),
                   dict(win=0.6, sides=[dict(a=dict(b=3.0, name='x', none=1.0), n=[1, 2])], flag=True)]
        got = evaluate.spread(full, without)
        self.assertEqual(sorted(got), ['sides', 'win'])            # no text, no flag
        self.assertEqual(list(got['sides'][0]), ['a'])             # no list of numbers
        self.assertEqual(list(got['sides'][0]['a']), ['b'])        # none where a count had none
        self.assertAlmostEqual(got['sides'][0]['a']['b'], 1.0, places=3)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Scoreboard(unittest.TestCase):
    def setUp(self):
        self.tmp = tempfile.TemporaryDirectory()
        self.addCleanup(self.tmp.cleanup)
        bench._CACHE.clear()

    def write(self, tag, drill, opponent, win, se, left=None):
        d = os.path.join(self.tmp.name, tag)
        os.makedirs(d, exist_ok=True)
        side = dict(corner=dict(left=left)) if left is not None else {}
        with open(os.path.join(d, f'{drill}-{opponent}.json'), 'w') as f:
            json.dump(dict(vs=dict(win=win, sides=[side, {}],
                                   se=dict(win=se, sides=[dict(corner=dict(left=0.03)) if side else {}, {}]))), f)

    def test_a_measure_over_its_opponents_and_a_difference_in_errors(self):
        self.write('a', 'league', 'kano', 0.80, 0.04)
        self.write('a', 'league', 'ikumi', 0.60, 0.03)
        self.write('b', 'league', 'kano', 0.90, 0.04)
        self.write('b', 'league', 'ikumi', 0.90, 0.03)
        a = bench.pooled('a', 'league', ('win',), self.tmp.name)
        b = bench.pooled('b', 'league', ('win',), self.tmp.name)
        self.assertAlmostEqual(a[0], 0.70)
        self.assertAlmostEqual(a[1], 0.025)            # sqrt(0.04^2 + 0.03^2) / 2
        self.assertEqual(a[2], 2)                      # (the pairings it has)
        x = bench.z(a, b)
        self.assertAlmostEqual(x, 0.20 / math.hypot(0.025, 0.025))
        self.assertEqual(bench.verdict(x), 'real')
        self.assertEqual(bench.verdict(1.2), 'noise')
        self.assertIsNone(bench.pooled('c', 'league', ('win',), self.tmp.name))

    def test_the_agent_s_own_measures_are_its_side_s(self):
        self.write('a', 'hold', 'kano', 0.5, 0.05, left=0.9)
        got = bench.cell('a', 'hold', 'kano', ('side', 'corner', 'left'), self.tmp.name)
        self.assertEqual(got, (0.9, 0.03))

    def test_every_measure_names_a_drill(self):
        for name, drill, path, better, what in bench.MEASURES:
            self.assertIn(drill, bench.DRILLS, name)
            self.assertIn(better, (1, -1), name)


if __name__ == '__main__':
    unittest.main()
