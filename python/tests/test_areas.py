"""The scorecard by area (tactics.situations, situation_time, episodes, areas_report:
evaluate.py's `areas`; areas.py's read-out), on matches made up here: no game data."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import advantages
    import areas
    import tactics
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)
# (the characters' moves, made on each machine from the game: not in the repository)
NO_MOVES = not os.path.exists(os.path.join(RUNS, 'motions.json'))

N = len(tactics.OBS) if not MISSING else 0
ME_ACT, OPP_ACT, ME_STUN, OPP_STUN, ME_AIR, OPP_AIR, ME_HP, OPP_HP = 0, 1, 4, 5, 6, 7, 14, 15
GUARD, LYING = 0x96, 0x62


def match(T):
    c = np.zeros((T, N), np.float32)
    c[:, ME_HP] = c[:, OPP_HP] = 1.0
    return c


def hit(c, who, at, damage=0.1, steps=10):
    """A hit on `who` (0 the viewer, 1 the opponent) at step `at`."""
    c[at:at + steps, ME_STUN + who] = 1
    c[at:, ME_HP + who] -= damage


def sides(c):
    return tactics.Side(c, 0), tactics.Side(c, 1), np.ones(len(c), bool)


def by_rule(me, opp, t):
    """exchanges()' rule as it was written before situations(): the first that holds."""
    mdown, odown = np.isin(me.act, tactics.DOWN), np.isin(opp.act, tactics.DOWN)
    lo = max(0, t - tactics.EXCHANGE_GUARD)
    if odown[max(0, t - tactics.EXCHANGE_DOWN):t + 1].any():
        return 'my okizeme'
    if mdown[max(0, t - tactics.EXCHANGE_DOWN):t + 1].any():
        return 'its okizeme'
    if opp.guard[lo:t + 1].any():
        return 'my pressure'
    if me.guard[lo:t + 1].any():
        return 'its pressure'
    a = me.air[max(0, t - tactics.EXCHANGE_AIR):t + 1].any()
    b = opp.air[max(0, t - tactics.EXCHANGE_AIR):t + 1].any()
    return 'both in the air' if a and b else 'I came by air' if a else 'it came by air' if b else 'on the ground'


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Situations(unittest.TestCase):
    def test_recent_is_the_window_up_to_the_step(self):
        x = np.array([0, 1, 0, 0, 0, 0], bool)
        self.assertEqual(tactics._recent(x, 2).tolist(), [False, True, True, True, False, False])

    def test_every_step_by_the_rule(self):
        rng = np.random.default_rng(1)
        c = match(3000)
        for col, value, runs in ((ME_ACT, GUARD, 20), (OPP_ACT, GUARD, 20), (ME_ACT, LYING, 6),
                                 (OPP_ACT, LYING, 6), (ME_AIR, 1, 30), (OPP_AIR, 1, 30)):
            for s in rng.integers(0, 2950, runs):
                c[s:s + rng.integers(3, 40), col] = value
        me, opp, _ = sides(c)
        got = tactics.situations(me, opp)
        for t in range(0, 3000, 7):
            self.assertEqual(tactics.SITUATIONS[got[t]], by_rule(me, opp, t), t)

    def test_time_episodes_and_the_report(self):
        c = match(1200)
        c[100:130, ME_AIR] = 1          # it jumps in and hits
        hit(c, 1, 120, 0.2)
        c[300:360, OPP_ACT] = LYING     # the opponent down: its reversal hits the viewer
        hit(c, 0, 400, 0.1)
        c[700:710, OPP_ACT] = GUARD     # a guarded string, nothing after
        me, opp, live = sides(c)
        time = dict(tactics.situation_time(me, opp, live))
        self.assertEqual(sum(time.values()), 1200)
        self.assertEqual(time['I came by air'], 30 + tactics.EXCHANGE_AIR)
        self.assertEqual(time['my okizeme'], 60 + tactics.EXCHANGE_DOWN)
        self.assertEqual(time['my pressure'], 10 + tactics.EXCHANGE_GUARD)
        eps = tactics.episodes(me, opp, live)
        got = {(k, first) for k, first, _ in eps if k != 'on the ground'}
        self.assertEqual(got, {('I came by air', 1), ('my okizeme', -1), ('my pressure', 0)})
        air = [hp for k, _, hp in eps if k == 'I came by air'][0]
        self.assertAlmostEqual(air, 0.2 * 9999, delta=1)
        n = tactics.measure(c)
        rep = tactics.areas_report(n['exchanges'], n['situation_time'], n['losses_opp'],
                                   n['losses'], n['episodes'], 64 * 60 / 1200)
        a = rep['I came by air']
        self.assertAlmostEqual(a['rate'], 0.2 * 9999 / (42 / 64), delta=1)
        self.assertAlmostEqual(a['share'], 42 / 1200, places=3)
        self.assertEqual((a['won'], a['lost_first']), (1.0, 0.0))
        self.assertEqual(rep['my okizeme']['lost_first'], 1.0)
        self.assertAlmostEqual(rep['opening']['dealt'], 0.2 * 9999, delta=1)
        self.assertEqual(rep['both in the air']['rate'], None)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class ReadOut(unittest.TestCase):
    def record(self, rate, seconds=10.0):
        """A match's record with every situation at `rate` HP a second."""
        x = np.zeros((len(tactics.SITUATIONS), 6))
        x[:, areas.TIME] = seconds * areas.STEPS
        x[:, areas.NET] = rate * seconds
        x[:, areas.EPS], x[:, areas.WON] = 10, 5
        x[:, areas.ALL] = 8 * seconds * areas.STEPS
        return x, int(8 * seconds * areas.STEPS)

    def test_alike_opponents_have_no_spread(self):
        rng = np.random.default_rng(2)
        groups = {g: [self.record(rng.normal(0, 50)) for _ in range(30)] for g in range(5)}
        got = areas.components(groups)['my pressure']['rate']
        self.assertLess(got['spread'], 15)
        self.assertGreater(got['noise'], 30)

    def test_apart_opponents_are_read_in_few_matches(self):
        rng = np.random.default_rng(3)
        groups = {g: [self.record(300 * g + rng.normal(0, 50)) for _ in range(30)] for g in range(5)}
        got = areas.components(groups)['my pressure']['rate']
        self.assertGreater(got['spread'], 250)
        self.assertLess(got['matches'], 1)
        s = areas.summary(groups[1])
        self.assertAlmostEqual(s['my pressure']['won'], 0.5)
        self.assertAlmostEqual(s['my pressure']['share'], 1 / 8)


@unittest.skipIf(MISSING or NO_MOVES, f'needs runs/human-ayu and motions.json: {MISSING}')
class WeakArea(unittest.TestCase):
    """advantages.py's weak: one area of the profile drawn to be its weak one."""
    PROFILE = dict(reversal=0.8, throw=0.5, jumpin=0.5, bait=0.5)

    def logic(self, weak):
        return advantages.Advantages('kano', 1, seed=4, weak=weak, **self.PROFILE)

    def test_one_area_of_those_it_has(self):
        a = self.logic(1.0)
        seen = {}
        for _ in range(200):
            a.draw(0)
            area = a.weak_area[0]
            seen[area] = seen.get(area, 0) + 1
            for name, v in self.PROFILE.items():
                low = name in advantages.WEAK_AREAS[area]
                self.assertAlmostEqual(a.k[name][0], v * advantages.WEAK if low else v)
        self.assertEqual(set(seen), {'okizeme', 'anti-pressure'})  # none of wake, blind
        self.assertGreater(min(seen.values()), 60)
        self.assertEqual(a.counts['weak_okizeme'] + a.counts['weak_anti_pressure'], 200)

    def test_without_it_the_profile_as_it_is(self):
        a = self.logic(0.0)
        a.draw(0)
        self.assertIsNone(a.weak_area[0])
        self.assertEqual({n: a.k[n][0] for n in self.PROFILE}, self.PROFILE)
        self.assertEqual(advantages.parse('weak=0.5')['weak'], 0.5)


if __name__ == '__main__':
    unittest.main()
