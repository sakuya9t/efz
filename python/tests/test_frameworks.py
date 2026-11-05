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


class Recording(unittest.TestCase):
    def test_records_a_replay_slot(self):
        with tempfile.TemporaryDirectory() as save:
            env = EfzVecEnv(DATA, 1, num_threads=1, frame_skip=4, max_frames=64 * 600,
                            rounds_to_win=1, autoreset='disabled', save_dir=save, seed=3)
            env.set_matches(chars=('ayu', 'mai'), stage=2, cpu=(False, False))
            path = env.record(0, 2, 3)
            self.assertTrue(path.endswith(os.path.join('replay', 'data2-3.rep')))
            env.reset()
            from efz_env import actions
            for k in range(20000):  # player 1 walks in and attacks; player 2 stands
                controls = np.array([[actions.FORWARD | (actions.A if k % 2 else 0), 0]],
                                    np.uint8)
                _, _, term, trunc, info = env.step(controls)
                if term[0] or trunc[0]:
                    break
            self.assertTrue(term[0])
            size = os.path.getsize(path)
            words = np.fromfile(path, dtype='<i2')
            # The header (src/scene2.cpp): P1, P2, 104, stage, P1 palette, P2 palette.
            self.assertEqual(words[:6].tolist(), [1, 2, 104, 2, 0, 0])
            frames = int(info['frame'][0])
            # Each frame at least two refill words and an input word per player.
            self.assertGreater(len(words), 6 + 4 * frames)
            # The file was closed with the match: stepping on doesn't grow it.
            env.step(np.zeros((1, 2), np.uint8))
            self.assertEqual(os.path.getsize(path), size)
            # A slot that holds a replay isn't overwritten unless asked.
            with self.assertRaises(FileExistsError):
                env.record(0, 2, 3)
            env.record(0, 2, 3, overwrite=True)
            env.close()

    def test_refuses_the_cpu(self):
        with tempfile.TemporaryDirectory() as save:
            env = EfzVecEnv(DATA, 1, num_threads=1, save_dir=save)
            env.set_matches(chars=('ayu', 'mai'), cpu=(False, True))
            with self.assertRaisesRegex(RuntimeError, 'CPU'):
                env.record(0, 1, 1)
            env.close()


class Playback(unittest.TestCase):
    def test_plays_a_recorded_match_back(self):
        from efz_env import actions
        config = dict(num_threads=1, frame_skip=1, max_frames=64 * 600, rounds_to_win=1,
                      autoreset='disabled')
        with tempfile.TemporaryDirectory() as save:
            env = EfzVecEnv(DATA, 1, save_dir=save, seed=5, **config)
            env.set_matches(chars=('ayu', 'mai'), stage=4, cpu=(False, False))
            path = env.record(0, 1, 1)
            env.reset()
            table = actions.ActionTable()
            rng = np.random.default_rng(1)
            played, views = [], [env.obs.copy()]
            for k in range(64 * 600):  # player 1 walks in pressing A; player 2 at random
                controls = np.array([[actions.FORWARD | (actions.A if k % 2 else 0),
                                      table.to_bytes(rng.integers(0, len(table)))]], np.uint8)
                _, _, term, trunc, info = env.step(controls)
                np.testing.assert_array_equal(info['input'][0], controls[0])
                self.assertEqual(info['replay'][0], 0)
                played.append(controls[0])
                views.append(env.final_obs.copy() if term[0] or trunc[0] else env.obs.copy())
                if term[0] or trunc[0]:
                    break
            self.assertTrue(term[0])
            end = info.copy()
            env.close()

            # The replay's inputs play, whatever the actions; the same game step by step.
            env = EfzVecEnv(DATA, 1, **config)
            env.play(0, path)
            env.reset()
            self.assertEqual(env.info['replay'][0], 1)
            self.assertEqual(env.info['chars'][0].tolist(), [1, 2])
            np.testing.assert_array_equal(env.obs, views[0])
            for k, controls in enumerate(played):
                _, _, term, trunc, info = env.step(np.full((1, 2), 0x55, np.uint8))
                np.testing.assert_array_equal(info['input'][0], controls, err_msg=f'step {k}')
                view = env.final_obs if term[0] or trunc[0] else env.obs
                np.testing.assert_array_equal(view, views[k + 1], err_msg=f'step {k}')
                self.assertEqual(bool(term[0] or trunc[0]), k == len(played) - 1)
            self.assertTrue(term[0])
            for field in ('frame', 'winner', 'hp', 'rounds_won'):
                np.testing.assert_array_equal(info[field], end[field])
            # Afterwards it plays the program's matches again.
            env.reset()
            self.assertEqual(env.info['replay'][0], 0)
            env.close()

    def test_refuses_what_isnt_a_replay(self):
        env = EfzVecEnv(DATA, 1, num_threads=1)
        with tempfile.TemporaryDirectory() as tmp:
            with self.assertRaisesRegex(ValueError, 'cannot read'):
                env.play(0, os.path.join(tmp, 'missing.rep'))
            junk = os.path.join(tmp, 'junk.rep')
            with open(junk, 'wb') as f:
                f.write(b'\x7f\x00' * 8)
            with self.assertRaisesRegex(ValueError, 'not a replay'):
                env.play(0, junk)
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

    def test_delay(self):
        # Every view is the game of `delay` steps before; the input history is current.
        from efz_env.sb3 import EfzSB3VecEnv
        venv = EfzSB3VecEnv(DATA, 2, opponent=lambda o: np.zeros(len(o), np.int64),
                            chars=('ayu', 'mai'), max_frames=400, num_threads=2, history=2,
                            delay=3)
        raw = [venv.reset()]
        live = [venv.env.obs[:, 0].copy()]
        forward_a = venv.table.actions.index((6, 'A'))
        for _ in range(6):
            venv.step_async(np.full(2, forward_a))
            raw.append(venv.step_wait()[0])
            live.append(venv.env.obs[:, 0].copy())
        for t in range(7):
            np.testing.assert_array_equal(raw[t][:, :168], live[max(0, t - 3)])
        np.testing.assert_array_equal(raw[1][:, 168:174], [[1, 0, 1, 0, 0, 0]] * 2)
        venv.close()

    def test_history_and_prior(self):
        # Observations with the input history; EfzPolicy pulled toward a prior; an
        # opponent without history (the 168 features) among ones with.
        from stable_baselines3 import PPO
        from efz_env.history import FEATURES
        from efz_env.policy import EfzPolicy, policy_kwargs
        from efz_env.sb3 import EfzSB3VecEnv, frozen
        plain = self.learn(EfzSB3VecEnv(DATA, 2, opponent='cpu', chars=('ayu', 'mai'),
                                        max_frames=20, num_threads=2), 64)
        venv = EfzSB3VecEnv(DATA, 2, opponent=frozen(plain), chars=('ayu', 'mai'),
                            max_frames=30, num_threads=2, history=4)
        self.assertEqual(venv.observation_space.shape, (168 + 4 * FEATURES,))
        obs = venv.reset()
        self.assertTrue((obs[:, 168:] == 0).all())
        venv.step_async(np.full(2, venv.table.actions.index((6, 'A'))))
        obs, _, _, _ = venv.step_wait()
        np.testing.assert_array_equal(obs[:, 168:168 + FEATURES], [[1, 0, 1, 0, 0, 0]] * 2)
        kw = dict(n_steps=16, batch_size=32, n_epochs=1, verbose=0, device='cpu',
                  ent_coef=0.01, policy_kwargs=policy_kwargs(width=32))
        prior = PPO(EfzPolicy, venv, **kw)
        model = PPO(EfzPolicy, venv, **kw)
        model.policy.set_prior(prior.policy, coef=0.1, ent_coef=0.01)
        model.learn(64)
        self.assertGreaterEqual(model.policy.prior_kl, 0.0)
        with tempfile.TemporaryDirectory() as tmp:  # saved and loaded without the prior
            model.save(os.path.join(tmp, 'm.zip'))
            loaded = PPO.load(os.path.join(tmp, 'm.zip'), device='cpu')
            self.assertNotIn('prior', loaded.policy.__dict__)
            np.testing.assert_allclose(loaded.policy.logits(
                loaded.policy.obs_to_tensor(obs)[0]).detach().numpy(),
                model.policy.logits(model.policy.obs_to_tensor(obs)[0]).detach().numpy(),
                rtol=1e-5, atol=1e-6)
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
