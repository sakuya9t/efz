"""efz_env.memory: the match memory's counts on made-up views, and in an environment
(with the game's data, $EFZ_DATA): the features an agent is given are those of the views
it was given."""

import os
import unittest

import numpy as np

from efz_env import memory
from efz_env.memory import K, Memory, NAMES, OPP, SELF, SIZE

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
MOVE, OTHER = 0xd0, 0xd4


def view(me=None, it=None, **top):
    v = np.zeros((1, 168), np.float32)
    for cols, d in ((SELF, me or {}), (OPP, it or {})):
        for k, x in d.items():
            v[0, cols[k]] = x
    for k, x in top.items():
        v[0, dict(intro=memory.INTRO, round_over=memory.ROUND_OVER)[k]] = x
    return v


def play(m, steps):
    for me, it in steps:
        m.update(view(me, it))


def feature(m, name):
    return float(m.features()[0, NAMES.index(name)])


class Counts(unittest.TestCase):
    def test_its_wake_up_reversal_into_my_meaty(self):
        m = Memory(1)
        play(m, [({'act': 0}, {'act': 0x62}),
                 ({'act': MOVE}, {'act': 0x60}),
                 ({'act': MOVE}, {'act': 0x60}),
                 ({'act': MOVE}, {'act': OTHER, 'inv': 1}),          # it rises with a move
                 ({'act': 0x32, 'stun': 1}, {'act': OTHER})])        # and hits me
        c = m.c[0]
        for name, n in (('w_n', 1), ('w_move', 1), ('w_inv', 1), ('w_meaty', 1), ('w_m_lost', 1),
                        ('w_m_won', 0), ('w_jump', 0), ('h_n', 1), ('h_move', 1), ('a_n', 1)):
            self.assertEqual(c[K[name]], n, name)
        self.assertAlmostEqual(feature(m, 'wake'), 1 / (1 + memory.WEIGHT))
        for name in ('wake_move', 'wake_invincible', 'wake_meaty', 'wake_meaty_lost',
                     'hit_move', 'attacked_hit'):
            self.assertEqual(feature(m, name), 1.0, name)
        self.assertEqual(feature(m, 'wake_wait_lost'), 0.0)

    def test_invincible_by_the_frame_data(self):
        steps = [({'act': 0}, {'act': 0x60, 'char': 3}), ({'act': 0}, {'act': OTHER, 'char': 3})]
        m = Memory(1)
        play(m, steps)
        self.assertEqual((m.c[0, K['w_move']], m.c[0, K['w_inv']]), (1, 0))
        m = Memory(1, invincible={'3': [OTHER]})
        play(m, steps)
        self.assertEqual((m.c[0, K['w_move']], m.c[0, K['w_inv']]), (1, 1))

    def test_a_wait_that_is_punished(self):
        m = Memory(1)
        play(m, [({'act': 0}, {'act': 0x60}),
                 ({'act': 0}, {'act': 0}),                            # it rises, I wait
                 ({'act': 0}, {'act': 0, 'air': 1}),                  # it jumps
                 ({'act': MOVE}, {'act': 0x3b, 'stun': 1, 'air': 1})])  # I hit it in the air
        c = m.c[0]
        for name, n in (('w_n', 1), ('w_meaty', 0), ('w_jump', 1), ('w_move', 0), ('w_w_won', 1),
                        ('o_n', 1), ('o_air', 1), ('o_crouch', 0)):
            self.assertEqual(c[K[name]], n, name)
        self.assertEqual(feature(m, 'wake_wait_won'), 1.0)

    def test_its_guard_and_what_follows(self):
        m = Memory(1)
        play(m, [({'act': MOVE}, {'act': 0}),
                 ({'act': MOVE}, {'act': 0x99, 'frame': 0}),          # a crouching guard
                 ({'act': MOVE}, {'act': 0x99, 'frame': 1}),
                 ({'act': MOVE}, {'act': 0x99, 'frame': 0}),          # again (the guard restarts)
                 ({'act': 0}, {'act': 0xa8, 'frame': 0}),             # a standing recoil guard
                 ({'act': 0}, {'act': 0}),                            # its guard ends
                 ({'act': 0}, {'act': memory.BACKDASH})])
        c = m.c[0]
        for name, n in (('c_n', 3), ('g_n', 3), ('g_crouch', 2), ('c_rg', 1), ('p_n', 1),
                        ('p_back', 1), ('p_move', 0)):
            self.assertEqual(c[K[name]], n, name)
        self.assertAlmostEqual(feature(m, 'guard_crouch'), 2 / 3, places=6)

    def test_openings_by_what_they_found(self):
        m = Memory(1)
        play(m, [({'act': MOVE}, {'act': 0x3}),                       # it crouches
                 ({'act': MOVE}, {'act': 0x4a, 'stun': 1}),           # and is hit
                 ({'act': 0}, {'act': 0}),
                 ({'act': 0}, {'act': 0}),
                 ({'act': MOVE}, {'act': 0x64})])                     # thrown
        c = m.c[0]
        for name, n in (('o_n', 2), ('o_crouch', 1), ('o_throw', 1), ('o_stand', 0)):
            self.assertEqual(c[K[name]], n, name)

    def test_my_wake_up(self):
        m = Memory(1)
        play(m, [({'act': 0x60}, {'act': MOVE}),
                 ({'act': OTHER}, {'act': MOVE}),                     # I rise with a move
                 ({'act': OTHER}, {'act': 0x32, 'stun': 1})])         # and it hits
        c = m.c[0]
        for name, n in (('r_n', 1), ('r_rev', 1), ('r_rev_won', 1), ('r_g_won', 0), ('r_pressed', 0)):
            self.assertEqual(c[K[name]], n, name)
        m = Memory(1)
        play(m, [({'act': 0x60}, {'act': MOVE, 'air': 1}),
                 ({'act': 0}, {'act': MOVE, 'air': 1}),               # I rise and guard
                 ({'act': 0x96}, {'act': MOVE, 'air': 1})])           # its jump-in
        c = m.c[0]
        for name, n in (('r_n', 1), ('r_rev', 0), ('r_pressed', 1), ('r_air', 1), ('a_n', 1),
                        ('a_air', 1), ('h_n', 0)):
            self.assertEqual(c[K[name]], n, name)

    def test_nothing_counts_outside_a_round(self):
        m = Memory(1)
        m.update(view({'act': 0}, {'act': 0x60}, intro=1))
        m.update(view({'act': 0}, {'act': OTHER}, intro=1))
        m.update(view({'act': 0}, {'act': 0x32, 'stun': 1}, round_over=1))
        self.assertEqual(float(m.c.sum()), 0.0)

    def test_sets(self):
        m = Memory(2, decay=0.5)
        for _ in range(4):
            m.update(np.concatenate([view({'act': 0}, {'act': 0x60})] * 2))
            m.update(np.concatenate([view({'act': 0}, {'act': OTHER})] * 2))
        self.assertEqual(list(m.c[:, K['w_n']]), [4, 4])
        m.end(np.array([True, True]), won=np.array([True, False]),
              new_set=np.array([False, True]))
        self.assertEqual(list(m.c[:, K['w_n']]), [2, 0])       # kept, older; a new set
        self.assertEqual(list(m.c[:, K['s_n']]), [1, 0])
        self.assertEqual(list(m.c[:, K['s_won']]), [1, 0])
        f = m.features()
        self.assertEqual(f.shape, (2, SIZE))
        self.assertAlmostEqual(float(f[0, NAMES.index('set')]), 1 / memory.SET)
        self.assertEqual(float(f[0, NAMES.index('set_won')]), 1.0)
        self.assertEqual(float(f[1].sum()), 0.0)
        m.end(np.array([True, False]), won=np.array([False, False]),
              new_set=np.array([False, False]))
        self.assertEqual(list(m.c[:, K['s_n']]), [2, 0])
        self.assertEqual(float(m.features()[0, NAMES.index('set_won')]), 0.5)

    def test_features_are_shares(self):
        rng = np.random.default_rng(0)
        m = Memory(8)
        acts = np.array([0, 0x3, 0x60, 0x62, 0x96, 0x99, 0xa8, 0x64, 0x32, MOVE, OTHER, 0xa4])
        for _ in range(3000):
            v = np.zeros((8, 168), np.float32)
            for cols in (SELF, OPP):
                v[:, cols['act']] = acts[rng.integers(len(acts), size=8)]
                v[:, cols['stun']] = rng.random(8) < 0.2
                v[:, cols['air']] = rng.random(8) < 0.2
                v[:, cols['inv']] = rng.random(8) < 0.1
                v[:, cols['frame']] = rng.integers(4, size=8)
            m.update(v)
        f = m.features()
        self.assertTrue(np.isfinite(f).all() and (f >= 0).all() and (f <= 1).all())
        self.assertGreater(float(f.min(axis=0).max()), 0.0)  # (something of everything happened)


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class InAnEnvironment(unittest.TestCase):
    def test_the_agent_sees_its_views_memory(self):
        from efz_env.sb3 import EfzSB3VecEnv
        n, history, delay = 3, 4, 5
        env = EfzSB3VecEnv(DATA, n, opponent='cpu', chars=('ayu', 'mai'), frame_skip=1,
                           history=history, delay=delay, memory={'decay': 0.5}, sets=(2,),
                           max_frames=900, cpu_level=4, seed=5, num_threads=1)
        base = 168 + env.history.size
        self.assertEqual(env.observation_space.shape, (base + SIZE,))
        mine = Memory(n, decay=0.5)
        rng = np.random.default_rng(1)
        obs = env.reset()
        mine.update(obs[:, :168])
        ends, numbers = 0, []
        for _ in range(4000):
            np.testing.assert_array_equal(obs[:, base:], mine.features())
            obs, _, dones, infos = env.step(rng.integers(env.action_space.n, size=n))
            for i in np.flatnonzero(dones):
                ends += 1
                numbers.append(infos[i]['set_match'])
                mine.end(np.arange(n) == i, won=np.full(n, infos[i]['winner'] == 0),
                         new_set=np.full(n, infos[i]['set_match'] == 2))
            mine.update(obs[:, :168])
        env.close()
        self.assertGreater(ends, 6)
        self.assertEqual(set(numbers), {1, 2})
        self.assertGreater(float(mine.c.sum()), 0.0)


if __name__ == '__main__':
    unittest.main()
