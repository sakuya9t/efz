"""runs/human-ayu/okiplan.py, the planned okizeme: which of the library's entries a
knockdown is given, the shares its answers get from the match's counts, and the module's
steps around a plan (a planner that tries nothing); with the game's data ($EFZ_DATA) the
steps to a rising as the planner finds them, and a plan on a real knockdown."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import okiplan
    from efz_env import modules
    from efz_env.memory import K
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
# (the opponents' moves, made on each machine from the game: not in the repository)
NO_MOVES = not os.path.exists(os.path.join(RUNS, 'motions.json'))


def entry(cls='ground low', rise=70, move_at=60, dist=40, air=False, opponent='mai',
          corner=False, length=100, press=7):
    actions = np.zeros(length, np.int64)
    actions[move_at - 2] = press
    return dict(actions=actions, dist=np.full(length, dist, np.int16),
                air=np.full(length, air, bool), rise=rise, move_at=move_at, cls=cls,
                opponent=opponent, corner=corner)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Entries(unittest.TestCase):
    def pick(self, library, lead=50, distance=40, air=False, victim='mai', corner=False, **kw):
        return okiplan.Entries(library, **kw).pick(lead, distance, air, victim, corner)

    def test_an_entry_is_played_from_its_step_that_is_now(self):
        m = entry(rise=70, move_at=60)
        (k, actions), = self.pick([m], lead=50)
        self.assertEqual((k, len(actions)), (0, 100 - 20))  # its rising on this one's
        self.assertEqual(int(np.flatnonzero(actions)[0]), 60 - 2 - 20)

    def test_what_is_left_out(self):
        self.assertEqual(self.pick([entry(rise=40)], lead=50), [])       # more time than it took
        self.assertEqual(self.pick([entry(move_at=24)], lead=50), [])    # its move pressed already
        self.assertEqual(self.pick([entry(dist=80)]), [])                # its player stood elsewhere
        self.assertEqual(self.pick([entry(air=True)]), [])               # ... was in the air
        self.assertEqual(len(self.pick([entry(dist=80)], tolerance=40)), 1)

    def test_the_closest_of_each_kind_and_a_kind_at_most_twice(self):
        lib = [entry('ground low', dist=40, press=7), entry('ground low', dist=44, press=8),
               entry('ground low', dist=41, press=9), entry('jump high', dist=50, press=10),
               entry('throw', dist=46, press=11)]
        picked = [k for k, _ in self.pick(lib)]
        self.assertEqual(picked, [0, 4, 3, 2])  # each kind's best by closeness, then seconds
        self.assertEqual([k for k, _ in self.pick(lib, per_plan=2)], [0, 4])

    def test_the_same_inputs_once_and_the_same_character_first(self):
        lib = [entry(dist=40, press=7), entry(dist=40, press=7),
               entry(dist=41, press=8, opponent='ayu'), entry(dist=40, press=9, corner=True)]
        self.assertEqual([k for k, _ in self.pick(lib, per_class=3)], [0, 2, 3])
        self.assertEqual([k for k, _ in self.pick(lib, per_class=3, victim='ayu')], [2, 0, 3])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Belief(unittest.TestCase):
    def test_the_prior_and_what_was_seen(self):
        c = np.zeros(len(K))
        b = okiplan.belief(c)
        self.assertAlmostEqual(float(b.sum()), 1.0)
        prior = okiplan.PRIOR
        self.assertAlmostEqual(b[okiplan.ANSWERS.index('reversal')], prior['reversal'])
        self.assertAlmostEqual(b[0] / (b[0] + b[1]), prior['crouch'])
        c[K['w_n']], c[K['w_move']], c[K['w_inv']] = 10, 10, 10  # it reversed on every one
        b = okiplan.belief(c, prior=6)
        self.assertAlmostEqual(b[okiplan.ANSWERS.index('reversal')], (0.6 + 10) / 16)
        self.assertAlmostEqual(float(b.sum()), 1.0)
        c[K['g_n']], c[K['g_crouch']] = 20, 0  # and never guards crouching
        b = okiplan.belief(c, prior=6, crouch_prior=6)
        self.assertAlmostEqual(b[0] / (b[0] + b[1]), 6 * prior['crouch'] / 26)
        b = okiplan.belief(c, prior=6, sight=True)  # by sight: what its guards showed isn't asked
        self.assertAlmostEqual(b[1] / (b[0] + b[1]), okiplan.SIGHT_STAND)
        self.assertAlmostEqual(float(b.sum()), 1.0)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Maximin(unittest.TestCase):
    def test_known_games(self):
        rps = np.array([[0, -1, 1], [1, 0, -1], [-1, 1, 0]], float)
        np.testing.assert_allclose(okiplan.maximin(rps), [1 / 3] * 3, atol=0.02)
        # A row that is never better is not played; one answer to everything is.
        self.assertLess(okiplan.maximin(np.array([[2, 2], [1, 0]], float))[1], 0.02)
        # Matching pennies with one side worth double: the mix that leaves no better reply.
        m = okiplan.maximin(np.array([[2, -1], [-1, 1]], float))
        np.testing.assert_allclose(m, [0.4, 0.6], atol=0.02)

    def test_doubt_spreads_the_draw(self):
        worth = np.array([[1300.0, 0.0], [0.0, 1300.0], [100.0, 100.0]])
        shares = np.array([0.8, 0.2])
        expected = worth @ shares
        sure = okiplan.maximin(expected[:, None] + 0 * worth)
        self.assertGreater(sure[0], 0.98)  # no doubt: the best against the shares
        unsure = okiplan.maximin(0.5 * expected[:, None] + 0.5 * worth)
        self.assertGreater(unsure[0], unsure[1])
        self.assertGreater(unsure[1], 0.1)


class Planner:
    """An OkiPlanner that tries nothing: the same option every plan."""

    def __init__(self, option):
        self.option, self.calls, self.last = option, [], None

    def plan(self, state, side, hist, prev, seen, policy, shares):
        self.calls.append(np.asarray(shares).copy())
        self.last = dict(lead=50, kinds=['ground low', 'wait', 'own'], chosen=0,
                         expected=np.array([500.0, 100.0, 0.0]), mix=np.array([1.0, 0, 0]))
        return self.option


def context(opp=0, now_opp=None, hit=False, last=None):
    view = np.zeros(168, np.float32)
    view[okiplan.OPP_ACT] = opp
    view[okiplan.SELF_HITSTUN] = float(hit)
    now = view.copy()
    now[okiplan.OPP_ACT] = opp if now_opp is None else now_opp
    return modules.Context(view, now, save=lambda: b'', last=last)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Module(unittest.TestCase):
    def module(self, option=(7, 8, 9), **kw):
        m = okiplan.OkiPlan(Planner(np.array(option)), delay=14, **kw)
        m.batch(2)
        return m

    def step(self, m, i, ctx):
        m.watch(i, ctx)
        return m.act(i, ctx)

    def test_one_plan_a_knockdown_played_to_its_end(self):
        m = self.module()
        self.assertIsNone(self.step(m, 0, context(0)))
        got = [self.step(m, 0, context(0x62, last=None if t == 0 else 'okiplan'))
               for t in range(5)]
        self.assertEqual(got, [7, 8, 9, None, None])
        self.assertEqual(len(m.planner.calls), 1)
        self.assertIsNone(self.step(m, 0, context(0)))          # up
        self.assertEqual(self.step(m, 0, context(0x62)), 7)     # down again: another
        self.assertEqual(len(m.planner.calls), 2)
        self.assertEqual(m.stats()['chosen'], {'ground low': 1.0})

    def test_it_lets_go(self):
        m = self.module()
        self.assertEqual(self.step(m, 0, context(0x62)), 7)
        self.assertIsNone(self.step(m, 0, context(0x62, hit=True, last='okiplan')))
        m = self.module()
        self.assertEqual(self.step(m, 1, context(0x62)), 7)
        self.assertEqual(self.step(m, 1, context(0x62, last='okiplan')), 8)
        # (the routes took a step: what is left is not played after them)
        self.assertIsNone(self.step(m, 1, context(0x62, last='routes')))
        self.assertEqual(len(m.planner.calls), 1)

    def test_nothing_planned_once_the_opponent_is_up_or_while_it_is_hit(self):
        m = self.module()
        self.assertIsNone(self.step(m, 0, context(0x62, now_opp=0)))  # seen down, up by now
        self.assertIsNone(self.step(m, 0, context(0x62)))             # (once a knockdown)
        self.assertEqual(m.planner.calls, [])
        m = self.module(option=())
        self.assertIsNone(self.step(m, 0, context(0x62)))             # its own play chosen
        self.assertEqual(len(m.planner.calls), 1)

    def test_what_it_saw_is_kept_for_the_same_opponent_only(self):
        for carry, kept in ((False, 0.0), (True, 10 * 0.7)):
            m = self.module(carry=carry)
            m.memory.c[:, K['w_n']] = 10
            m.memory.c[:, K['w_inv']] = m.memory.c[:, K['w_move']] = 10
            m.reset(np.array([True, False]))
            self.assertAlmostEqual(float(m.memory.c[0, K['w_n']]), kept)
            self.assertEqual(float(m.memory.c[1, K['w_n']]), 10.0)
            self.step(m, 0, context(0x62))
            rev = okiplan.ANSWERS.index('reversal')
            self.assertAlmostEqual(float(m.planner.calls[0][rev]), (0.6 + kept) / (6 + kept))

    def test_an_answer_to_plan_for(self):
        m = self.module(fixed='reversal')
        self.step(m, 0, context(0x62))
        self.assertEqual(list(m.planner.calls[0]), [0, 0, 1, 0, 0])


@unittest.skipIf(MISSING or not DATA or not os.path.isdir(DATA or ''),
                 'no game data: set EFZ_DATA')
@unittest.skipIf(NO_MOVES, 'no runs/human-ayu/motions.json: python runs/human-ayu/motions.py makes it')
class OnTheGame(unittest.TestCase):
    def test_the_rising_and_a_plan(self):
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        env = EfzVecEnv(DATA, 8, frame_skip=1, rounds_to_win=2, max_frames=0, cpu_level=4,
                        seed=3, autoreset='disabled')
        env.set_matches(chars=('ayu', 'mai'))  # (a CPU would not take the answers' inputs)
        obs = env.reset()
        rng = np.random.default_rng(0)
        found = None
        for _ in range(20000):  # until side 0's opponent is down
            a = np.zeros((8, 2), np.uint8)
            a[:, 0] = okiplan.TABLE.table[rng.integers(len(okiplan.TABLE), size=8)]
            a[:, 1] = okiplan.TABLE.table[rng.integers(9, size=8)]  # (it only moves)
            obs, _, term, trunc, _ = env.step(a)
            down = np.isin(np.round(obs[:, 0, okiplan.OPP_ACT]), [0x62]) & ~(term | trunc)
            if down.any():
                found = int(np.flatnonzero(down)[0])
                break
        self.assertIsNotNone(found, 'no knockdown in 20000 random steps')
        state = env.save_state(found)
        seen = np.repeat(obs[found, 0][None], 15, 0)
        air = bool(obs[found, 0, okiplan.SELF_AIR] > 0)
        library = [dict(actions=np.full(120, okiplan.INDEX[(2, button)], np.int64),
                        dist=np.full(120, d, np.int16), air=np.full(120, air), rise=80,
                        move_at=75, cls=c, opponent='mai', corner=False)
                   for c, d, button in (('ground low', 0, 'A'), ('ground mid', 100, 'B'),
                                        ('jump high', 200, 'C'), ('fly low', 300, 'A'),
                                        ('dash high', 400, 'B'))]
        planner = okiplan.OkiPlanner(DATA, library, 264, 14, per_plan=3, tolerance=1000)
        lead, now = planner.lead(state, 0)
        self.assertIsNotNone(lead)
        # The same count on the game itself, both holding a guard.
        a = np.zeros((8, 2), np.uint8)
        a[:, :] = encode(1)
        steps = 0
        while int(round(float(env.obs[found, 0, okiplan.OPP_ACT]))) in okiplan.DOWN:
            env.step(a)
            steps += 1
            self.assertLess(steps, 200)
        self.assertEqual(lead, steps)
        self.assertGreaterEqual(lead, okiplan.MIN_LEAD)  # (seen at the knockdown's start)
        if True:
            policy = lambda views: np.full(len(views), okiplan.NEUTRAL)
            hist = np.zeros((16, 6), np.float32)
            chosen = planner.plan(state, 0, hist, 0, seen, policy, okiplan.belief(np.zeros(len(K))))
            last = planner.last
            self.assertEqual(last['lead'], lead)
            self.assertEqual(last['kinds'][-2:], ['wait', 'own'])
            self.assertEqual(last['worth'].shape, (len(last['kinds']), len(okiplan.ANSWERS)))
            self.assertTrue(np.isfinite(last['worth']).all())
            self.assertEqual(len(last['entries']), 3)  # (per_plan of the five kinds)
            if last['kinds'][last['chosen']] == 'own':
                self.assertIsNone(chosen)
            else:
                self.assertGreater(len(chosen), 0)
            # bait: on the copies where the riser's reversal came out and neither was hit
            # first, the punish's worth is added; nothing else changes.
            again = okiplan.OkiPlanner(DATA, library, 264, 14, per_plan=3, tolerance=1000, bait=600)
            again.plan(state, 0, hist, 0, seen, policy, okiplan.belief(np.zeros(len(K))))
            credit = again.last['baited']
            r = okiplan.ANSWERS.index('reversal')
            self.assertFalse(np.delete(credit, r, 1).any())
            self.assertFalse(last['baited'].any())
            np.testing.assert_allclose(again.last['worth'], last['worth'] + 600 * credit)
            came = bool(planner.wake_schedule('mai', planner.theirs, lead))
            wait = again.last['kinds'].index('wait')
            if came:  # (a wait guards it: the reversal came out and did not hit)
                self.assertTrue(credit[wait, r])
                self.assertEqual(again.last['first'][wait, r], 0)
            else:
                self.assertFalse(credit.any())
            again.one.close()
            again.sim.close()
            # sight: the riser's 'crouch' answer stands against an agent it saw in the air
            # `sight` steps ago; the others are as they were.
            from efz_env.actions import encode
            sighted = okiplan.OkiPlanner(DATA, library, 264, 14, per_plan=3, tolerance=1000, sight=3)
            answer = np.array([0, 0, 1, 2, 4])
            air = np.array([True, False, False, True, True])
            sighted.seen_air = [air, ~air, ~air, ~air]            # (three steps ago: `air`)
            np.testing.assert_array_equal(
                sighted.their_controls(0, 30, answer, 0, None, None),
                [encode(4), encode(1), encode(4), encode(1), encode(1)])
            sighted.seen_air = [~air, air]                        # (not that long yet: the first)
            self.assertEqual(sighted.their_controls(0, 30, answer, 0, None, None)[1], encode(4))
            sighted.plan(state, 0, hist, 0, seen, policy, okiplan.belief(np.zeros(len(K)), sight=True))
            self.assertTrue(np.isfinite(sighted.last['worth']).all())
            self.assertEqual(len(sighted.seen_air), sighted.last['lead'] + sighted.window + 1)
            sighted.one.close()
            sighted.sim.close()
        env.close()
        planner.one.close()
        planner.sim.close()


if __name__ == '__main__':
    unittest.main()
