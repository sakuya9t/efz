"""The library's autoreset modes and seeding, and the adapters for Gymnasium,
Stable-Baselines3, PettingZoo and human play, each checked by the framework's own tests
where it has them. Needs the game's data ($EFZ_DATA); each part is skipped without its
framework installed."""

import os
import tempfile
import unittest

try:
    import numpy as np
except ImportError:
    raise unittest.SkipTest('numpy is not installed')

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
if not DATA or not os.path.isdir(DATA):
    raise unittest.SkipTest('no game data: set EFZ_DATA to an EFZ 4.02 install')

from efz_env import EfzVecEnv


def vec(n=2, **config):
    config.setdefault('max_frames', 40)
    config.setdefault('num_threads', 2)
    env = EfzVecEnv(DATA, n, **config)
    env.set_matches(chars=('ayu', 'mai'), cpu=(False, True))
    return env


def run_to_end(env, actions=None):
    """Steps until some match ends; returns the step's results (copied)."""
    actions = np.zeros((env.num_envs, 2), np.uint8) if actions is None else actions
    for _ in range(1000):
        obs, reward, term, trunc, info = env.step(actions)
        if (term | trunc).any():
            return obs.copy(), reward.copy(), term.copy(), trunc.copy(), info.copy()
    raise AssertionError('no match ended')


class Autoreset(unittest.TestCase):
    def test_same_step(self):
        env = vec(autoreset='same_step')
        env.reset()
        obs, _, term, trunc, info = run_to_end(env)
        self.assertTrue(trunc.all())
        self.assertTrue(info['ended'].all())
        self.assertFalse(np.array_equal(obs, env.final_obs))  # obs is the next match's
        env.close()

    def test_next_step(self):
        env = vec(autoreset='next_step')
        env.reset()
        obs, _, term, trunc, info = run_to_end(env)
        np.testing.assert_array_equal(obs, env.final_obs)
        self.assertTrue(info['ended'].all())
        episode = info['episode'].copy()
        obs2, reward, term2, trunc2, info2 = env.step(np.zeros((2, 2), np.uint8))
        self.assertFalse((term2 | trunc2).any())
        self.assertTrue((reward == 0).all())
        self.assertTrue((info2['frame'] == 0).all())
        self.assertTrue((info2['episode'] == episode + 1).all())
        env.close()

    def test_disabled(self):
        env = vec(autoreset='disabled')
        env.reset()
        obs, _, term, trunc, info = run_to_end(env)
        for _ in range(5):  # stays ended
            o, r, t, u, i = env.step(np.zeros((2, 2), np.uint8))
            np.testing.assert_array_equal(o, obs)
            self.assertTrue(u.all())
            self.assertTrue((r == 0).all())
        env.reset(mask=np.array([1, 0], bool))
        o, r, t, u, i = env.step(np.zeros((2, 2), np.uint8))
        self.assertFalse(u[0])
        self.assertTrue(u[1])
        env.close()


class Seeding(unittest.TestCase):
    def rollout(self, env, seed, steps=150):
        rng = np.random.default_rng(0)
        out = [env.reset(seed=seed).copy()]
        for _ in range(steps):  # the same controls in every environment
            controls = rng.integers(0, 256, (1, 2), dtype=np.uint8).repeat(env.num_envs, 0)
            out.append(env.step(controls)[0].copy())
        return np.stack(out)

    def test_same_seed_same_games(self):
        env = EfzVecEnv(DATA, 2, num_threads=2, max_frames=0)
        env.set_matches(cpu=(False, True))  # random characters and stages, the CPU's rand
        a = self.rollout(env, 11)
        b = self.rollout(env, 11)
        np.testing.assert_array_equal(a, b)
        c = self.rollout(env, [5, 5])  # one seed for both: the same game in each
        np.testing.assert_array_equal(c[:, 0], c[:, 1])
        env.close()


try:
    import gymnasium
except ImportError:
    gymnasium = None


@unittest.skipIf(gymnasium is None, 'gymnasium is not installed')
class Gymnasium(unittest.TestCase):
    def test_check_env(self):
        from gymnasium.utils.env_checker import check_env
        import efz_env.gym  # noqa: F401  (registers efz/VsCpu-v0)
        env = gymnasium.make('efz/VsCpu-v0', data_dir=DATA, chars=('ayu', 'mai'),
                             max_frames=200)
        check_env(env.unwrapped, skip_render_check=True)
        env.close()

    def test_vector_and_wrappers(self):
        import efz_env.gym  # noqa: F401
        from gymnasium.wrappers.vector import NormalizeObservation, RecordEpisodeStatistics
        envs = gymnasium.make_vec('efz/VsCpu-v0', num_envs=4,
                                  vectorization_mode='vector_entry_point', data_dir=DATA,
                                  chars=('ayu', 'mai'), max_frames=60, num_threads=2)
        self.assertEqual(envs.metadata['autoreset_mode'], envs.autoreset_mode)
        envs = NormalizeObservation(RecordEpisodeStatistics(envs))
        envs.reset(seed=1)
        ended = 0
        for _ in range(200):
            _, _, _, _, info = envs.step(envs.action_space.sample())
            if 'episode' in info:
                ended += int(info['_episode'].sum())
        self.assertGreater(ended, 0)
        envs.close()

    def test_same_step_final_obs(self):
        from efz_env.gym import EfzVsCpu
        envs = EfzVsCpu(DATA, 2, chars=('ayu', 'mai'), max_frames=40, num_threads=2,
                        autoreset_mode='same_step')
        envs.reset()
        for _ in range(200):
            _, _, term, trunc, info = envs.step(envs.action_space.sample())
            if (term | trunc).any():
                self.assertIn('final_obs', info)
                self.assertTrue(info['_final_obs'].any())
                break
        else:
            self.fail('no match ended')
        envs.close()


try:
    import pettingzoo
except ImportError:
    pettingzoo = None


@unittest.skipIf(pettingzoo is None or gymnasium is None, 'pettingzoo is not installed')
class PettingZoo(unittest.TestCase):
    def test_parallel_api(self):
        from pettingzoo.test import parallel_api_test, parallel_seed_test
        from efz_env.pettingzoo import EfzParallelEnv
        parallel_api_test(EfzParallelEnv(DATA, chars=('ayu', 'mai'), max_frames=300),
                          num_cycles=500)
        parallel_seed_test(lambda: EfzParallelEnv(DATA, char_pool=['ayu', 'mai', 'akane'],
                                                  max_frames=300))


try:
    import stable_baselines3
except ImportError:
    stable_baselines3 = None


@unittest.skipIf(stable_baselines3 is None, 'stable-baselines3 is not installed')
class StableBaselines3(unittest.TestCase):
    def learn(self, venv, steps):
        from stable_baselines3 import PPO
        model = PPO('MlpPolicy', venv, n_steps=16, batch_size=32, n_epochs=1, verbose=0,
                    device='cpu')
        model.learn(steps)
        return model

    def test_vs_cpu(self):
        from efz_env.sb3 import EfzSB3VecEnv
        venv = EfzSB3VecEnv(DATA, 4, opponent='cpu', chars=('ayu', 'mai'), max_frames=20,
                            num_threads=2)
        model = self.learn(venv, 128)
        self.assertGreater(len(model.ep_info_buffer), 0)
        venv.close()

    def test_self_play_and_frozen(self):
        from efz_env.sb3 import EfzSB3VecEnv, frozen
        venv = EfzSB3VecEnv(DATA, 2, opponent='self', chars=('ayu', 'mai'), max_frames=40,
                            num_threads=2)
        self.assertEqual(venv.num_envs, 4)
        model = self.learn(venv, 128)
        venv.close()
        venv = EfzSB3VecEnv(DATA, 2, opponent=frozen(model), chars=('ayu', 'mai'),
                            max_frames=40, num_threads=2)
        self.learn(venv, 64)
        venv.close()


@unittest.skipIf(stable_baselines3 is None, 'stable-baselines3 is not installed')
class PopulationBasedTraining(unittest.TestCase):
    def test_bradley_terry(self):
        from efz_env.pbt import bradley_terry
        results = [('a', 'cpu', 1.0)] * 30 + [('a', 'cpu', 0.0)] * 10 + \
                  [('b', 'cpu', 0.5)] * 40 + [('a', 'b', 1.0)] * 20
        elo = bradley_terry(results, ['a', 'b', 'cpu'])
        self.assertEqual(elo['cpu'], 1000.0)
        self.assertGreater(elo['a'], elo['b'])
        self.assertAlmostEqual(elo['b'], 1000.0, delta=60)

    def test_perturb_stays_in_bounds(self):
        from efz_env.pbt import SEARCH_SPACE, perturb, sample
        rng = np.random.default_rng(0)
        settings = sample(rng)
        for _ in range(200):
            settings = perturb(rng, settings)
            for name, (lo, hi, _) in SEARCH_SPACE.items():
                self.assertTrue(lo <= settings[name] <= hi, (name, settings[name]))

    def test_generations_and_resume(self):
        import json
        from efz_env.pbt import Population
        with tempfile.TemporaryDirectory() as out:
            def population():
                return Population(out, DATA, size=2, steps_per_generation=128, num_envs=4,
                                  num_threads=2, chars=('ayu', 'mai'), max_frames=40,
                                  eval_matches=4, eval_max_frames=60, verbose=0,
                                  ppo=dict(n_steps=16, batch_size=32, n_epochs=1,
                                           policy_kwargs=dict(net_arch=[32])))
            pop = population()
            pop.run(1)
            members = pop.state['members']
            self.assertEqual(len(members[0]['elo']), 1)
            self.assertEqual(sum(m['parent'] is not None for m in members), 1)  # one replaced
            for name in ('state.json', 'best.zip', 'config.json', 'log.jsonl'):
                self.assertTrue(os.path.exists(os.path.join(out, name)), name)
            self.assertEqual(len(pop.state['archive']), 2)
            pop = population()  # resumes
            self.assertEqual(pop.state['generation'], 1)
            pop.run(2)
            with open(os.path.join(out, 'state.json')) as f:
                state = json.load(f)
            self.assertEqual(state['generation'], 2)
            self.assertEqual(len(state['members'][0]['elo']), 2)


class ScriptedHuman:
    """A 'human' for tests: walks forward and presses A every 8 frames."""

    def __init__(self):
        self.n = 0

    def screen_bits(self):
        from efz_env import actions
        self.n += 1
        return actions.LEFT | (actions.A if self.n % 8 == 0 else 0)


class Human(unittest.TestCase):
    def match(self, folder, **kw):
        from efz_env.human import HumanMatch
        return HumanMatch(DATA, human=1, chars=('ayu', 'mai'), window=None,
                          controls=ScriptedHuman(), realtime=False, record_dir=folder,
                          max_frames=200, **kw)

    def test_relative(self):
        from efz_env import actions
        from efz_env.human import to_relative
        self.assertEqual(to_relative(actions.RIGHT | actions.A, 1), actions.RIGHT | actions.A)
        self.assertEqual(to_relative(actions.RIGHT | actions.A, -1), actions.LEFT | actions.A)
        self.assertEqual(to_relative(actions.LEFT | actions.DOWN, -1),
                         actions.RIGHT | actions.DOWN)

    def test_play_and_record(self):
        with tempfile.TemporaryDirectory() as folder:
            match = self.match(folder)
            results = match.play(lambda obs: 0, matches=2)
            match.close()
            self.assertEqual(len(results), 2)
            files = sorted(os.listdir(folder))
            self.assertEqual(len([f for f in files if f.endswith('.npz')]), 2)
            with np.load(os.path.join(folder, files[0].replace('.json', '.npz'))) as data:
                t = len(data['controls'])
                self.assertGreaterEqual(t, 200)
                self.assertEqual(data['obs'].shape, (t, 2, 168))
                # The human (player 2) starts facing left: screen left is forward.
                self.assertEqual(int(data['human_screen'][0]) & 3, 2)
                self.assertEqual(int(data['controls'][0, 1]) & 3, 1)
                decisions = data['agent_action'] >= 0
                self.assertGreater(decisions.sum(), 0)

    @unittest.skipIf(stable_baselines3 is None, 'stable-baselines3 is not installed')
    def test_learns_from_human_games(self):
        from stable_baselines3 import PPO
        from efz_env.human import HumanVecEnv
        with tempfile.TemporaryDirectory() as folder:
            venv = HumanVecEnv(self.match(folder))
            model = PPO('MlpPolicy', venv, n_steps=32, batch_size=16, n_epochs=1, verbose=0,
                        device='cpu')
            model.learn(96)
            self.assertGreater(len(model.ep_info_buffer), 0)
            venv.close()


if __name__ == '__main__':
    unittest.main()
