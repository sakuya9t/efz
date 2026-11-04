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
        self.assertEqual(_native.VERSION, 3)
        self.assertEqual(ctypes.sizeof(_native.Match), 20)
        self.assertEqual(ctypes.sizeof(_native.Info), 32)
        self.assertEqual(ctypes.sizeof(_native.Buffers), 6 * ctypes.sizeof(ctypes.c_void_p))

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
        self.assertEqual(info.dtype.itemsize, 32)
        self.assertEqual(info['hp'].shape, (2, 2))


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


class WithoutData(unittest.TestCase):
    def test_says_so(self):
        with self.assertRaisesRegex(RuntimeError, 'no game data'):
            EfzVecEnv('no-such-efz-folder', num_envs=2)


if __name__ == '__main__':
    unittest.main()
