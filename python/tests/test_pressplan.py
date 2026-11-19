"""runs/human-ayu/pressplan.py, the planned pressure, and pressure_library.py: what a
guarded move's follow-ups are in a recorded match, which of the library's entries a
guarded move is given, the shares its answers get, and the module's steps around a plan
(a planner that tries nothing); with the game's data ($EFZ_DATA) a plan beside a
guarding opponent, a throw among its options."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import okiplan
    import pressplan
    import pressure_library
    import tactics
    from efz_env import modules
    from efz_env.memory import K
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
# (the opponents' moves, made on each machine from the game: not in the repository)
NO_MOVES = not os.path.exists(os.path.join(RUNS, 'motions.json'))
GUARD, MOVE = 0x99, 0xc9


def entry(cls='ground low', adv=2, distance=50, opponent='mai', corner=False, press=7):
    actions = np.zeros(40, np.int64)
    actions[3] = press
    return dict(actions=actions, cls=cls, adv=adv, distance=distance, opponent=opponent,
                corner=corner)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Library(unittest.TestCase):
    def match(self, T=200):
        """A viewer's match of nothing: both standing 60 pixels apart."""
        obs = np.zeros((T, 168), np.float32)
        obs[:, 4] = 60 / 640  # dx
        return obs, np.zeros(T, np.uint8)

    def guarded(self, obs, at, recovery=8, guard=14):
        """The viewer's move from `at`, guarded 2 steps in: its recovery, the guard's steps."""
        obs[at:at + 2 + recovery, 18] = MOVE
        obs[at + 2:at + 2 + guard, 50] = GUARD

    def test_a_follow_up_its_advantage_and_what_came_next(self):
        obs, inputs = self.match()
        self.guarded(obs, 20)             # free at 30, the guard over at 36: plus 6
        obs[40:50, 18] = 0xdc             # a throw next
        obs[42:60, 50] = 0x64             # ... that caught
        inputs[38] = 0x21
        found = list(pressure_library.followups(obs, inputs))
        self.assertEqual(len(found), 1)
        m = found[0]
        self.assertEqual((m['start'], m['adv'], m['cls'], m['result']), (30, 6, 'throw', 'throw'))
        self.assertEqual(m['distance'], 60)
        self.assertEqual(len(m['inputs']), 42 - 30 + 20)
        self.assertEqual(m['inputs'][8], 0x21)

    def test_minus_and_no_move(self):
        obs, inputs = self.match()
        self.guarded(obs, 20, recovery=20, guard=10)  # free at 42, the guard over at 32
        found = list(pressure_library.followups(obs, inputs))
        self.assertEqual([(m['start'], m['adv'], m['cls'], m['result']) for m in found],
                         [(42, -10, 'none: hold', 'none')])

    def test_not_after_a_hit_or_from_afar(self):
        obs, inputs = self.match()
        self.guarded(obs, 20)
        obs[26:30, 52] = 1                # the opponent hit before the viewer is free
        self.assertEqual(list(pressure_library.followups(obs, inputs)), [])
        obs, inputs = self.match()
        self.guarded(obs, 20)
        obs[:, 4] = 300 / 640
        self.assertEqual(list(pressure_library.followups(obs, inputs)), [])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Followups(unittest.TestCase):
    def test_the_same_advantage_and_distance(self):
        lib = [entry(adv=2, distance=50, press=1), entry(adv=8, distance=50, press=2),
               entry(adv=2, distance=120, press=3), entry(adv=3, distance=44, press=4)]
        f = pressplan.Followups(lib, per_class=4)
        self.assertEqual([k for k, _ in f.pick(2, 50, 'mai', False)], [0, 3])
        self.assertEqual([k for k, _ in f.pick(8, 50, 'mai', False)], [1])
        self.assertEqual(f.pick(-6, 50, 'mai', False), [])

    def test_a_kind_at_most_twice_its_best_first_and_the_same_inputs_once(self):
        lib = [entry(distance=50 + d, press=1 + d) for d in range(4)] + \
              [entry('throw', distance=56), entry('throw', distance=56),
               entry(distance=50, press=1, opponent='akane')]
        got = [k for k, _ in pressplan.Followups(lib, per_class=2).pick(2, 50, 'mai', False)]
        self.assertEqual(got, [0, 4, 1])  # (a throw's twin and the other victim's twin left out)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Belief(unittest.TestCase):
    def test_the_prior_and_what_was_seen(self):
        c = np.zeros(len(K))
        b = pressplan.belief(c)
        self.assertAlmostEqual(float(b.sum()), 1.0)
        names = okiplan.ANSWERS
        self.assertAlmostEqual(float(b[names.index('jump')]), pressplan.PRIOR['jump'])
        c[K['p_n']] = 24
        c[K['p_jump']] = 24               # it jumps out every time
        b = pressplan.belief(c)
        self.assertGreater(float(b[names.index('jump')]), 0.75)
        self.assertLess(float(b[names.index('crouch')]), 0.2)
        b = pressplan.belief(np.zeros(len(K)), sight=True)   # the guard by sight (okiplan's)
        self.assertAlmostEqual(float(b[1] / (b[0] + b[1])), okiplan.SIGHT_STAND)


class Planner:
    """A PressPlanner that tries nothing: the same option every plan."""

    def __init__(self, option):
        self.option, self.calls, self.last = option, [], None

    def plan(self, state, side, hist, prev, seen, policy, shares, free_for=0):
        self.calls.append((np.asarray(shares).copy(), int(free_for)))
        self.last = dict(adv=3, lead=3, kinds=['throw', 'wait', 'own'], chosen=0,
                         expected=np.array([500.0, 100.0, 0.0]), mix=np.array([1.0, 0, 0]))
        return self.option


def context(seen_opp=0, opp=0, own=0, hit=False, last=None, dx=50, air=False):
    view = np.zeros(168, np.float32)
    view[okiplan.OPP_ACT] = seen_opp
    view[okiplan.SELF_HITSTUN] = float(hit)
    now = np.zeros(168, np.float32)
    now[okiplan.OPP_ACT], now[okiplan.SELF_ACT] = opp, own
    now[okiplan.DX] = dx / 640
    now[okiplan.SELF_AIR] = float(air)
    return modules.Context(view, now, save=lambda: b'', last=last)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Module(unittest.TestCase):
    def module(self, option=(7, 8, 9), **kw):
        m = pressplan.PressPlan(Planner(np.array(option)), delay=14, **kw)
        m.batch(2)
        return m

    def step(self, m, i, ctx):
        m.watch(i, ctx)
        return m.act(i, ctx)

    def test_a_plan_once_it_saw_the_guard_and_is_free(self):
        m = self.module()
        self.assertIsNone(self.step(m, 0, context()))                      # nothing guarded
        self.assertIsNone(self.step(m, 0, context(GUARD, own=MOVE)))       # seen; still in its move
        got = [self.step(m, 0, context(GUARD, last=None if t == 0 else 'pressplan'))
               for t in range(5)]
        self.assertEqual(got, [7, 8, 9, None, None])                       # once a contact
        self.assertEqual(len(m.planner.calls), 1)
        self.assertIsNone(self.step(m, 0, context(0)))
        self.assertEqual(self.step(m, 0, context(GUARD)), 7)               # guarded again: another
        self.assertEqual(m.stats()['chosen'], {'throw': 1.0})

    def test_not_from_afar_in_the_air_or_long_after(self):
        for ctx in (context(GUARD, dx=300), context(GUARD, air=True), context(GUARD, hit=True)):
            m = self.module()
            self.assertIsNone(self.step(m, 0, ctx))
            self.assertEqual(m.planner.calls, [])
        m = self.module(fresh=5)
        self.assertIsNone(self.step(m, 0, context(GUARD, own=MOVE)))
        for _ in range(6):
            self.assertIsNone(self.step(m, 0, context(0, own=MOVE)))
        self.assertIsNone(self.step(m, 0, context(0)))                     # too long ago
        self.assertEqual(m.planner.calls, [])

    def test_the_steps_the_opponent_has_been_free(self):
        m = self.module()
        self.step(m, 0, context(GUARD, opp=GUARD, own=MOVE))
        for _ in range(3):
            self.step(m, 0, context(GUARD, opp=0, own=MOVE))
        self.assertEqual(self.step(m, 0, context(GUARD, opp=0)), 7)
        self.assertEqual(m.planner.calls[0][1], 4)

    def test_it_lets_go(self):
        m = self.module()
        self.assertEqual(self.step(m, 1, context(GUARD)), 7)
        self.assertEqual(self.step(m, 1, context(0, last='pressplan')), 8)
        self.assertIsNone(self.step(m, 1, context(0, last='routes')))      # the routes took a step
        m = self.module()
        self.assertEqual(self.step(m, 0, context(GUARD)), 7)
        self.assertIsNone(self.step(m, 0, context(0, hit=True, last='pressplan')))


@unittest.skipIf(MISSING or not DATA or not os.path.isdir(DATA or ''),
                 'no game data: set EFZ_DATA')
@unittest.skipIf(NO_MOVES, 'no runs/human-ayu/motions.json: python runs/human-ayu/motions.py makes it')
class OnTheGame(unittest.TestCase):
    def test_a_plan_beside_a_guarding_opponent(self):
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                        autoreset='disabled')
        env.set_matches(chars=('ayu', 'mai'))
        obs = env.reset()
        a = np.zeros((1, 2), np.uint8)
        guards = np.array(sorted(tactics.GUARDS))
        found = None
        for t in range(3000):  # walk in, press A; the opponent holds a crouching guard
            close = abs(float(obs[0, 0, okiplan.DX])) * 640 < 36
            a[0, 0] = encode(2, 'A') if close and t % 12 == 0 else encode(5) if close else encode(6)
            a[0, 1] = encode(1)
            obs, _, term, trunc, _ = env.step(a)
            self.assertFalse(term[0] or trunc[0])
            free = int(round(float(obs[0, 0, okiplan.SELF_ACT]))) in tactics.FREE
            if found is None and int(round(float(obs[0, 0, okiplan.OPP_ACT]))) in guards:
                found = t
            if found is not None and free:
                break
        self.assertIsNotNone(found, 'no guard in 3000 steps')
        state = env.save_state(0)
        seen = np.repeat(obs[0, 0][None], 15, 0)
        throw = np.array([okiplan.INDEX[(6, '')]] * 12 + [okiplan.INDEX[(6, 'C')]] * 2 +
                         [okiplan.NEUTRAL] * 20, np.int64)
        low = np.array([okiplan.INDEX[(2, 'A')], okiplan.INDEX[(2, '')]] * 10, np.int64)
        library = [dict(actions=throw, cls='throw', adv=0, distance=50, opponent='mai', corner=False),
                   dict(actions=low, cls='ground low', adv=0, distance=50, opponent='mai',
                        corner=False)]
        planner = pressplan.PressPlanner(DATA, library, 264, 14, per_plan=3, tolerance=1000,
                                         slack=1000)
        policy = lambda views: np.full(len(views), okiplan.NEUTRAL)
        hist = np.zeros((16, 6), np.float32)
        chosen = planner.plan(state, 0, hist, 0, seen, policy,
                              pressplan.belief(np.zeros(len(K))), free_for=1)
        last = planner.last
        self.assertEqual(last['kinds'], ['throw', 'ground low', 'wait', 'own'])
        self.assertEqual(last['worth'].shape, (4, len(okiplan.ANSWERS)))
        self.assertTrue(np.isfinite(last['worth']).all())
        crouch, jump = okiplan.ANSWERS.index('crouch'), okiplan.ANSWERS.index('jump')
        # A throw opens a guard that a low doesn't, and misses an opponent that jumped.
        self.assertGreater(last['worth'][0, crouch], last['worth'][1, crouch])
        self.assertGreater(last['worth'][0, crouch], last['worth'][0, jump])
        if last['kinds'][last['chosen']] != 'own':
            self.assertGreater(len(chosen), 0)
        env.close()
        for e in (planner.one, planner.sim):
            e.close()
