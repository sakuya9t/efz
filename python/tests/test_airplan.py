"""runs/human-ayu/airplan.py, the planned catch, and air_library.py: what an air recovery
out of the viewer's combo and its catch are in a recorded match, which of the library's
entries a recovery is given, the shares its answers get, what the opponent of the copies
presses, and the module's steps around a plan (a planner that tries nothing); with the
game's data ($EFZ_DATA) the options tried from a game."""

import os
import sys
import unittest

import numpy as np

RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')
sys.path.insert(0, RUNS)
try:
    import air_library
    import airplan
    import okiplan
    from efz_env import modules
    from efz_env.actions import encode
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
HIT, RECOVERY, THROWN, AIR_THROW = 0x40, 0x9d, 0x64, 0xf0
SELF_CHAR, AYU = 34, 1


def entry(cls='air move', move_at=20, dist=60, up=40, air=True, lead=27, opponent='mai',
          corner=False, length=60, press=7):
    actions = np.zeros(length, np.int64)
    if move_at >= 0:
        actions[move_at] = press
    return dict(actions=actions, dist=np.full(length, dist, np.int16),
                up=np.full(length, up, np.int16), air=np.full(length, air, bool), cls=cls,
                move_at=move_at, lead=lead, opponent=opponent, corner=corner)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Library(unittest.TestCase):
    def match(self, T=260):
        """Ayu's match of nothing: both in the air 60 pixels apart, the opponent 40 over."""
        obs = np.zeros((T, 168), np.float32)
        obs[:, 4] = 60 / 640           # dx
        obs[:, 5] = -40 / 240          # dy: the opponent higher
        obs[:, SELF_CHAR] = AYU
        obs[:, 39] = obs[:, 71] = 1    # both in the air
        return obs, np.zeros(T, np.uint8)

    def recovered(self, obs, at, held=27):
        """The opponent hit from 20 steps before `at`, recovering at `at` for `held` steps."""
        obs[at - 20:at, 50] = HIT
        obs[at - 20:at, 52] = 1
        obs[at:at + held, 50] = RECOVERY

    def test_an_air_throw_that_caught(self):
        obs, inputs = self.match()
        self.recovered(obs, 60)
        obs[75:80, 18] = AIR_THROW     # the viewer's air throw, 15 steps in
        obs[77:100, 50] = THROWN       # ... that caught
        inputs[74] = 0x41
        found = list(air_library.catches(obs, inputs))
        self.assertEqual(len(found), 1)
        m = found[0]
        self.assertEqual((m['start'], m['cls'], m['result'], m['move_at']),
                         (60, 'air throw', 'throw', 15))
        self.assertEqual((m['distance'], m['height'], m['own_air']), (60, 40, True))
        self.assertEqual(len(m['inputs']), 77 - 60 + 20)
        self.assertEqual(m['inputs'][14], 0x41)
        self.assertEqual(len(m['dist']), len(m['inputs']))
        self.assertTrue((m['up'] == 40).all() and m['air'].all())

    def test_what_the_opponent_did_out_of_it(self):
        obs, inputs = self.match()
        self.recovered(obs, 60, held=20)
        obs[84:95, 50] = 0xc9          # a move of its own, 4 steps out of the recovery
        obs[90:100, 20] = 1            # ... that hit the viewer
        m, = air_library.catches(obs, inputs)
        self.assertEqual((m['lead'], m['theirs'], m['result'], m['cls']),
                         (20, 'move', 'hurt', 'none'))

    def test_not_from_afar_and_not_a_recovery_out_of_nothing(self):
        obs, inputs = self.match()
        self.recovered(obs, 60)
        obs[:, 4] = 400 / 640
        self.assertEqual(list(air_library.catches(obs, inputs)), [])
        obs, inputs = self.match()
        obs[60:87, 50] = RECOVERY      # (no hit reaction before it)
        self.assertEqual(list(air_library.catches(obs, inputs)), [])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Jumps(unittest.TestCase):
    def match(self, T=300):
        """Ayu's match of nothing: both standing 120 pixels apart."""
        obs = np.zeros((T, 168), np.float32)
        obs[:, 4] = 120 / 640
        obs[:, SELF_CHAR] = AYU
        return obs, np.zeros(T, np.uint8)

    def jump(self, obs, at, land=50, attack=None):
        """The opponent's forward jump from `at`, in the air 4 steps later until `land`
        steps after; attack: the step of the jump its move starts on."""
        obs[at:at + land, 50] = 0x5
        obs[at + 4:at + land, 71] = 1
        obs[at + 4:at + land, 5] = -60 / 240
        if attack is not None:
            obs[at + attack:at + land, 50] = 0xc9

    def test_a_jump_in_guarded(self):
        obs, inputs = self.match()
        self.jump(obs, 60, attack=30)
        obs[70:110, 18] = 0x2             # the viewer walks back: a guard held
        obs[100:112, 18] = 0x96           # ... and guards the attack, 40 steps in
        m, = air_library.jumps(obs, inputs)
        self.assertEqual((m['start'], m['cls'], m['result'], m['contact'], m['land']),
                         (60, 'none: guard', 'guarded', 40, 50))
        self.assertEqual((m['theirs'], m['their_move'], m['crossed'], m['distance']),
                         ('attack', 30, False, 120))
        self.assertEqual(len(m['inputs']), 40 + 20)

    def test_an_anti_air_that_hit_and_an_empty_jump(self):
        obs, inputs = self.match()
        self.jump(obs, 60)
        obs[80:95, 18] = 0xc9             # the viewer's move from the ground
        obs[86:100, 52] = 1               # ... hits the jumper
        m, = air_library.jumps(obs, inputs)
        self.assertEqual((m['cls'], m['result'], m['move_at'], m['theirs']),
                         ('ground move', 'hit', 20, 'empty'))

    def test_not_at_a_player_in_the_air_or_far_away(self):
        obs, inputs = self.match()
        self.jump(obs, 60)
        obs[:, 39] = 1
        self.assertEqual(list(air_library.jumps(obs, inputs)), [])
        obs, inputs = self.match()
        self.jump(obs, 60)
        obs[:, 4] = 400 / 640
        self.assertEqual(list(air_library.jumps(obs, inputs)), [])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Catches(unittest.TestCase):
    def pick(self, lib, since=14, lead=13, distance=60, up=40, air=True, victim='mai',
             corner=False, **kw):
        return [k for k, _ in airplan.Catches(lib, **kw).pick(since, lead, distance, up, air,
                                                              victim, corner)]

    def test_the_same_place_and_the_move_not_yet_pressed(self):
        lib = [entry(press=1), entry(dist=200, press=2), entry(up=150, press=3),
               entry(air=False, press=4), entry(move_at=10, press=5),
               entry('none', move_at=-1)]
        self.assertEqual(self.pick(lib, per_class=4), [0, 5])
        self.assertEqual(self.pick(lib, air=False, per_class=4), [3])

    def test_an_entry_is_played_from_the_step_that_is_now(self):
        lib = [entry(move_at=20, press=9)]
        (k, actions), = airplan.Catches(lib).pick(14, 13, 60, 40, True, 'mai', False)
        self.assertEqual((k, len(actions), int(actions[6])), (0, 60 - 14, 9))

    def test_a_kind_at_most_twice_its_best_first_and_the_same_inputs_once(self):
        lib = [entry(dist=60 + d, press=1 + d) for d in range(4)] + \
              [entry('air throw', dist=66), entry('air throw', dist=66),
               entry(press=1, opponent='akane')]
        self.assertEqual(self.pick(lib, per_class=2), [0, 4, 1])

    def test_a_recovery_as_long_comes_first(self):
        lib = [entry(lead=40, press=1), entry(lead=27, press=2)]
        self.assertEqual(self.pick(lib, since=14, lead=13), [1, 0])


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Belief(unittest.TestCase):
    def test_the_prior_and_what_was_seen(self):
        names = airplan.ANSWERS
        b = airplan.belief(np.zeros(len(names)))
        self.assertAlmostEqual(float(b.sum()), 1.0)
        self.assertAlmostEqual(float(b[names.index('move')]), airplan.PRIOR['move'])
        counts = np.zeros(len(names))
        counts[names.index('guard')] = 18   # it holds a guard out of every recovery
        b = airplan.belief(counts)
        self.assertGreater(float(b[names.index('guard')]), 0.7)
        self.assertLess(float(b[names.index('move')]), 0.15)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Answers(unittest.TestCase):
    def test_what_the_opponent_of_the_copies_presses(self):
        planner = airplan.AirPlanner.__new__(airplan.AirPlanner)  # (no game: their_controls() alone)
        answer = np.arange(5)
        early = planner.their_controls(0, 10, answer, 0, [], None)
        self.assertEqual(list(early), [encode(5), encode(4), encode(5), encode(5), encode(5)])
        out = planner.their_controls(10, 10, answer, 0, [], None)
        self.assertEqual(list(out), [encode(5), encode(4), encode(5, 'A'), encode(7), encode(4)])
        after = planner.their_controls(11, 10, answer, 0, [], None)
        self.assertEqual(list(after), [encode(5), encode(4), encode(5), encode(5), encode(5)])
        self.assertEqual(planner.their_controls(12, 10, answer, 0, [], None)[4], encode(4))
        self.assertEqual(planner.count_from(10), 0)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class JumpAnswers(unittest.TestCase):
    def test_what_the_jumper_of_the_copies_presses(self):
        planner = airplan.JumpPlanner.__new__(airplan.JumpPlanner)
        answer = np.arange(5)
        press = [encode(5, 'B'), encode(5), encode(5), encode(5), encode(7)]
        self.assertEqual(list(planner.their_controls(0, 30, answer, 0, [], None)), press)
        self.assertEqual(list(planner.their_controls(1, 30, answer, 0, [], None)), [encode(5)] * 5)
        late = planner.their_controls(30 - airplan.LATE, 30, answer, 0, [], None)
        self.assertEqual(late[1], encode(5, 'B'))
        down = planner.their_controls(30, 30, answer, 0, [], None)
        self.assertEqual((down[2], down[3]), (encode(1), encode(2, 'A')))

    def test_the_prior_is_of_its_answers(self):
        b = airplan.belief(np.zeros(5), 6.0, airplan.JUMP_ANSWERS, airplan.JUMP_PRIOR)
        self.assertAlmostEqual(float(b.sum()), 1.0)
        self.assertAlmostEqual(float(b[airplan.JUMP_ANSWERS.index('late')]),
                               airplan.JUMP_PRIOR['late'])


class Copies:
    """Copies of a game in which an air throw catches only if pressed on step `at` or
    later, by a player in the air."""

    def __init__(self, n, at, side=0):
        self.num_envs, self.at, self.side = n, at, side
        self.obs = np.zeros((n, 2, 168), np.float32)
        self.t = np.zeros(n, int)

    def load_state(self, e, state):
        self.t[e] = 0
        self.obs[e] = 0

    def step(self, controls):
        throw = okiplan.TABLE.table[airplan.THROW]
        for e in range(self.num_envs):
            if controls[e, self.side] == throw and self.t[e] >= self.at:
                self.obs[e, :, okiplan.OPP_ACT] = THROWN
            self.t[e] += 1
        return self.obs, None, None, None, None


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class SureThrow(unittest.TestCase):
    def planner(self, at):
        planner = airplan.AirPlanner.__new__(airplan.AirPlanner)
        planner.sim = Copies(40, at)
        return planner

    def now(self, air=True):
        now = np.zeros(168, np.float32)
        now[okiplan.SELF_AIR] = float(air)
        return now

    def test_the_throw_that_catches_soonest(self):
        got = self.planner(4).sure_throw(b'', 0, 12, self.now())
        self.assertEqual(list(got), [airplan.FORWARD] * 4 + [airplan.THROW] * 2)
        got = self.planner(0).sure_throw(b'', 0, 12, self.now())
        self.assertEqual(list(got), [airplan.THROW] * 2)

    def test_from_the_ground_a_jump_first(self):
        got = self.planner(6).sure_throw(b'', 0, 12, self.now(air=False))
        self.assertEqual(list(got), [airplan.UP_FORWARD] * 6 + [airplan.THROW] * 2)

    def test_the_throws_tried(self):
        air = airplan.AirPlanner.throws(40, True)
        self.assertEqual(air[0], [airplan.THROW] * 2)
        self.assertEqual(len(air), 12 + 2 * 10)      # every second step up to SURE_SPAN
        self.assertEqual(max(len(q) for q in air), airplan.SURE_SPAN - 2 + 2)
        ground = airplan.AirPlanner.throws(9, False)
        self.assertEqual(ground, [[airplan.UP_FORWARD] * d + [airplan.THROW] * 2 if k == 0 else
                                  [airplan.UP] * d + [airplan.THROW] * 2
                                  for d in (4, 6, 8) for k in (0, 1)])

    def test_none_that_catches_inside_the_recovery(self):
        self.assertIsNone(self.planner(30).sure_throw(b'', 0, 12, self.now()))
        self.assertIsNone(self.planner(0).sure_throw(b'', 0, 2, self.now()))


class Planner:
    """An AirPlanner that tries nothing: the same option every plan."""

    think = 0

    def __init__(self, option):
        self.option, self.calls, self.last = option, [], None

    def plan(self, state, side, hist, prev, seen, policy, shares, since=0):
        self.calls.append((np.asarray(shares).copy(), int(since)))
        self.last = dict(lead=12, kinds=['throw +0', 'wait', 'own'], chosen=0,
                         expected=np.array([500.0, 100.0, 0.0]), mix=np.array([1.0, 0, 0]),
                         worth=np.zeros((3, 5)))
        return self.option


def context(seen_opp=0, opp=0, hit=False, last=None, dx=60, seen_air=True):
    view = np.zeros(168, np.float32)
    view[okiplan.OPP_ACT] = seen_opp
    view[okiplan.SELF_HITSTUN] = float(hit)
    view[airplan.OPP_AIR] = float(seen_air)
    now = np.zeros(168, np.float32)
    now[okiplan.OPP_ACT] = opp
    now[okiplan.DX] = dx / 640
    return modules.Context(view, now, save=lambda: b'', last=last)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class Module(unittest.TestCase):
    def module(self, option=(7, 8, 9), delay=3, **kw):
        m = airplan.AirPlan(Planner(np.array(option)), delay, **kw)
        m.batch(1)
        return m

    def run_steps(self, m, steps):
        """steps: (the opponent's action seen, as the game is). Returns the actions."""
        out, last = [], None
        for seen_opp, opp in steps:
            ctx = context(seen_opp, opp, last=last)
            m.watch(0, ctx)
            a = m.act(0, ctx)
            last = m.name if a is not None else None
            out.append(a)
        return out

    def test_it_plans_when_it_sees_the_recovery_and_plays_the_plan(self):
        m = self.module()
        # hit; the recovery begins as the game is, seen three steps later
        steps = [(HIT, HIT)] * 2 + [(HIT, RECOVERY)] * 3 + [(RECOVERY, RECOVERY)] * 5
        got = self.run_steps(m, steps)
        self.assertEqual(got, [None] * 5 + [7, 8, 9, None, None])
        (shares, since), = m.planner.calls
        self.assertEqual(since, 3)                       # the recovery's clock, as the game is
        self.assertAlmostEqual(float(shares.sum()), 1.0)
        self.assertEqual(m.stats()['plans'], 1)

    def test_not_a_recovery_out_of_nothing_and_not_from_afar(self):
        m = self.module()
        self.assertEqual(self.run_steps(m, [(0, 0)] * 2 + [(RECOVERY, RECOVERY)] * 3), [None] * 5)
        m = self.module()
        out = []
        for seen_opp, opp in [(HIT, HIT), (RECOVERY, RECOVERY)]:
            ctx = context(seen_opp, opp, dx=500)
            m.watch(0, ctx)
            out.append(m.act(0, ctx))
        self.assertEqual(out, [None, None])
        self.assertEqual(m.planner.calls, [])

    def test_a_plan_with_think_steps_is_dropped_if_the_game_is_elsewhere(self):
        for moved, want in ((False, [None, 5, 5, 7, 8]), (True, [None, 5, 5, None, None])):
            m = self.module(option=(5, 5, 7, 8))
            m.planner.think = 2
            expected = context(RECOVERY, RECOVERY).now.copy()
            plan = m.planner.plan

            def with_view(*a, plan=plan, expected=expected, **kw):
                out = plan(*a, **kw)
                m.planner.last['view'] = expected
                return out
            m.planner.plan = with_view
            out, last = [], None
            for k, (seen_opp, opp) in enumerate([(HIT, HIT)] + [(RECOVERY, RECOVERY)] * 4):
                ctx = context(seen_opp, opp, last=last)
                if moved and k == 3:      # (the step its think steps are over)
                    ctx.now[okiplan.DX] = 200 / 640
                m.watch(0, ctx)
                a = m.act(0, ctx)
                last = m.name if a is not None else None
                out.append(a)
            self.assertEqual(out, want)
            self.assertEqual(m.elsewhere, int(moved))

    def test_it_lets_go_when_it_sees_itself_hit(self):
        m = self.module()
        self.run_steps(m, [(HIT, HIT), (RECOVERY, RECOVERY)])
        ctx = context(RECOVERY, RECOVERY, hit=True, last=m.name)
        m.watch(0, ctx)
        self.assertIsNone(m.act(0, ctx))

    def test_it_counts_what_the_opponent_did_out_of_its_recoveries(self):
        m = self.module(option=())
        names = airplan.ANSWERS
        self.run_steps(m, [(HIT, HIT), (RECOVERY, RECOVERY), (RECOVERY, 0), (0xc9, 0xc9)])
        self.assertEqual(int(m.counts[0, names.index('move')]), 1)
        self.run_steps(m, [(HIT, HIT), (RECOVERY, RECOVERY), (0x96, 0x96)])
        self.assertEqual(int(m.counts[0, names.index('guard')]), 1)
        m.reset()
        self.assertEqual(float(m.counts.sum()), 0.0)
        m = self.module(option=(), carry=True)
        self.run_steps(m, [(HIT, HIT), (RECOVERY, RECOVERY), (0xc9, 0xc9)])
        m.reset()
        self.assertAlmostEqual(float(m.counts[0, names.index('move')]), 0.7)


@unittest.skipIf(MISSING, f'needs runs/human-ayu and its imports: {MISSING}')
class JumpModule(unittest.TestCase):
    JUMP = 0x5

    def module(self, option=(7, 8, 9), delay=3, **kw):
        m = airplan.JumpPlan(Planner(np.array(option)), delay, **kw)
        m.batch(1)
        return m

    def run_steps(self, m, steps, **kw):
        out, last = [], None
        for seen_opp, opp, seen_air in steps:
            ctx = context(seen_opp, opp, last=last, seen_air=seen_air, **kw)
            m.watch(0, ctx)
            a = m.act(0, ctx)
            last = m.name if a is not None else None
            out.append(a)
        return out

    def test_it_plans_when_it_sees_the_jump(self):
        m = self.module()
        steps = [(0, 0, False)] + [(0, self.JUMP, False)] * 3 + [(self.JUMP, self.JUMP, True)] * 5
        self.assertEqual(self.run_steps(m, steps), [None] * 4 + [7, 8, 9, None, None])
        (shares, since), = m.planner.calls
        self.assertEqual(since, 3)
        self.assertEqual(len(shares), len(airplan.JUMP_ANSWERS))

    def test_not_from_afar_and_not_in_the_air_itself(self):
        m = self.module()
        self.assertEqual(self.run_steps(m, [(0, 0, False), (self.JUMP, self.JUMP, True)], dx=400),
                         [None, None])
        m = self.module()
        out = []
        for seen_opp, opp in [(0, 0), (self.JUMP, self.JUMP)]:
            ctx = context(seen_opp, opp)
            ctx.now[okiplan.SELF_AIR] = 1
            m.watch(0, ctx)
            out.append(m.act(0, ctx))
        self.assertEqual(out, [None, None])
        self.assertEqual(m.planner.calls, [])

    def test_it_counts_what_the_jumper_did(self):
        names = airplan.JUMP_ANSWERS
        m = self.module(option=())
        early = [(0, 0, False), (self.JUMP, self.JUMP, True)] + [(self.JUMP, 0, True)] * 5 + \
            [(0xc9, 0, True)]
        self.run_steps(m, early)
        self.assertEqual(int(m.counts[0, names.index('attack')]), 1)
        late = [(0, 0, False), (self.JUMP, self.JUMP, True)] + [(self.JUMP, 0, True)] * 25 + \
            [(0xc9, 0, True)]
        self.run_steps(m, late)
        self.assertEqual(int(m.counts[0, names.index('late')]), 1)
        empty = [(0, 0, False), (self.JUMP, self.JUMP, True)] + [(self.JUMP, 0, True)] * 25 + \
            [(0, 0, False)] * 14
        self.run_steps(m, empty)
        self.assertEqual(int(m.counts[0, names.index('empty')]), 1)
        low = [(0, 0, False), (self.JUMP, self.JUMP, True)] + [(self.JUMP, 0, True)] * 25 + \
            [(0, 0, False)] * 3 + [(0xc9, 0, False)]
        self.run_steps(m, low)
        self.assertEqual(int(m.counts[0, names.index('low')]), 1)


@unittest.skipIf(MISSING or not DATA or not os.path.isdir(DATA or ''),
                 'no game data: set EFZ_DATA')
class OnTheGame(unittest.TestCase):
    def test_no_plan_beside_an_opponent_on_the_ground_and_the_options_tried(self):
        from efz_env import EfzVecEnv
        env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                        autoreset='disabled', skip_noninteractive=False)
        env.set_matches(chars=('ayu', 'mai'))
        obs = env.reset()
        controls = np.zeros((1, 2), np.uint8)
        for _ in range(400):  # the intro over, both standing
            obs, *_ = env.step(controls)
        planner = airplan.AirPlanner(DATA, [entry(length=40)], 168 + 16 * 6, 3, per_plan=2,
                                     window=20)
        try:
            state = env.save_state(0)
            seen = np.repeat(obs[0, 0][None], 4, 0)
            hist = np.zeros((16, 6), np.float32)
            policy = lambda views: np.zeros(len(views), int)
            shares = airplan.belief(np.zeros(5))
            self.assertIsNone(planner.plan(state, 0, hist, 0, seen, policy, shares, since=14))
            self.assertIsNone(planner.last)  # (the opponent is on the ground: nothing to catch)
            options = [np.array([airplan.THROW] * 2), np.full(10, airplan.BACK), np.zeros(0, int)]
            planner.tryout(state, 0, 5, options, ['throw +0', 'wait', 'own'], [], hist, 0, seen,
                           policy, shares, schedule=[])
            last = planner.last
            self.assertEqual(last['worth'].shape, (3, 5))
            self.assertAlmostEqual(float(last['mix'].sum()), 1.0)
        finally:
            env.close()
            planner.one.close()
            planner.sim.close()


if __name__ == '__main__':
    unittest.main()
