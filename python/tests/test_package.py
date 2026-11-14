"""The Python package against the library, without the game's data (ctest -L headless,
or python -m unittest discover -s python/tests -t python). The games themselves are
the compatibility suite's (tools/compat.py)."""

import ctypes
import unittest

try:
    import numpy as np
except ImportError:  # the package needs numpy
    raise unittest.SkipTest('numpy is not installed')

from efz_env import EfzVecEnv, actions, character_names
from efz_env import _native


class Layout(unittest.TestCase):
    def test_structures_match_the_header(self):
        # port/headless/efz_env.h; tests/headless_test.cpp checks the C side.
        self.assertEqual(ctypes.sizeof(_native.Config), 72)
        self.assertEqual(_native.VERSION, 6)
        self.assertEqual(ctypes.sizeof(_native.Match), 20)
        self.assertEqual(ctypes.sizeof(_native.Info), 36)
        self.assertEqual(ctypes.sizeof(_native.Buffers), 6 * ctypes.sizeof(ctypes.c_void_p))
        self.assertEqual(ctypes.sizeof(_native.SoundEvent), 60)

    def test_library(self):
        lib = _native.library()
        self.assertEqual(lib.efz_env_version(), _native.VERSION)
        dim = lib.efz_env_obs_dim()
        names = [lib.efz_env_obs_name(i).decode() for i in range(dim)]
        self.assertEqual(dim, 168)
        self.assertEqual(len(set(names)), dim)
        self.assertIsNone(lib.efz_env_obs_name(dim))
        self.assertEqual(character_names()[1], 'ayu')
        self.assertEqual(len(character_names()), 25)

    def test_info_as_numpy(self):
        info = np.ctypeslib.as_array((_native.Info * 2)())
        self.assertEqual(info.dtype.itemsize, 36)
        self.assertEqual(info['hp'].shape, (2, 2))
        self.assertEqual(info['input'].shape, (2, 2))


class Actions(unittest.TestCase):
    def test_encoding(self):
        self.assertEqual(actions.encode(6, 'A'), actions.FORWARD | actions.A)
        self.assertEqual(actions.encode(1, 'bd'), actions.DOWN | actions.BACK | actions.B | actions.D)
        self.assertEqual(actions.encode(5), 0)

    def test_table(self):
        table = actions.ActionTable()
        self.assertEqual(len(table), 45)
        self.assertEqual(len(set(table.table.tolist())), 45)
        out = table.to_bytes(np.arange(90).reshape(45, 2) % 45)
        self.assertEqual(out.dtype, np.uint8)
        self.assertEqual(out.shape, (45, 2))
        self.assertEqual(table.describe(table.actions.index((6, 'C'))), '6C')


class History(unittest.TestCase):
    def controls(self, n=300):
        rng = np.random.default_rng(3)
        table = actions.ActionTable()
        # Held for a few steps at a time, as people hold them; some with two buttons.
        c = table.to_bytes(np.repeat(rng.integers(0, 45, n // 3), 3))
        c[::7] |= actions.A
        return c

    def test_online_is_offline(self):
        from efz_env.history import InputHistory, history_features
        c = self.controls()
        offline = history_features(c, frames=8)
        hist = InputHistory((1,), frames=8)
        for t in range(len(c)):
            np.testing.assert_array_equal(hist.features()[0], offline[t])
            hist.push(c[t:t + 1])

    def test_delay_online_is_offline(self):
        from efz_env.history import Delay, delayed
        obs = np.arange(40, dtype=np.float32).reshape(20, 2)
        d = Delay((1,), 5, 2)
        seen = []
        for t in range(len(obs)):
            if t == 12:  # a new match: its first view fills the buffer
                d.clear()
            seen.append(d.push(obs[t:t + 1])[0])
        want = np.concatenate([delayed(obs[:12], 5), delayed(obs[12:], 5)])
        np.testing.assert_array_equal(np.stack(seen), want)
        np.testing.assert_array_equal(d.peek(obs[:1])[0], obs[19 - 4])

    def test_features(self):
        from efz_env.history import input_features
        f = input_features(np.array([actions.UP | actions.BACK | actions.A | actions.C]),
                           np.array([actions.A]))
        np.testing.assert_array_equal(f[0], [-1, 1, 0, 0, 1, 0])  # C went down, A was held

    def test_labels_play_the_same_presses(self):
        # Playing the labels gives the game the same directions and the same buttons
        # going down (with one button where two went down together).
        from efz_env.history import action_labels, input_features
        table = actions.ActionTable()
        c = self.controls()
        played = table.to_bytes(action_labels(c, table))
        prev = np.concatenate([[0], c[:-1]]).astype(np.uint8)
        prev_played = np.concatenate([[0], played[:-1]]).astype(np.uint8)
        want, got = input_features(c, prev), input_features(played, prev_played)
        np.testing.assert_array_equal(got[:, :2], want[:, :2])
        went_down = want[:, 2:].sum(1) > 0
        np.testing.assert_array_equal(got[:, 2:].sum(1) > 0, went_down)
        self.assertTrue((got[:, 2:] <= want[:, 2:]).all())


class WithoutData(unittest.TestCase):
    def test_says_so(self):
        with self.assertRaisesRegex(RuntimeError, 'no game data'):
            EfzVecEnv('no-such-efz-folder', num_envs=2)


if __name__ == '__main__':
    unittest.main()
