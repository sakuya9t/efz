"""Agent files (efz_env.export, port/agent/policy.h): a model written as one plays as the
model does, run by the library as the game runs it. Needs the efz_env library and
stable-baselines3; the match played needs the game's data ($EFZ_DATA) too."""

import json
import os
import tempfile
import unittest

try:
    import numpy as np
    import gymnasium
    import stable_baselines3  # noqa: F401
    import torch as th
except ImportError:
    raise unittest.SkipTest('needs numpy, gymnasium, stable-baselines3 and torch')

from efz_env.export import NativeAgent, export_agent, sample_views, torch_log_probs

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
OBS_DIM = 168


class Spaces(gymnasium.Env):
    """Only the spaces, for making a model to export."""

    def __init__(self, width):
        self.observation_space = gymnasium.spaces.Box(-np.inf, np.inf, (width,), np.float32)
        self.action_space = gymnasium.spaces.Discrete(45)

    def reset(self, seed=None, options=None):
        return np.zeros(self.observation_space.shape, np.float32), {}

    def step(self, action):
        return np.zeros(self.observation_space.shape, np.float32), 0.0, True, False, {}


def make_model(folder, efz=True, history=2, delay=3, frame_skip=1, seed=0):
    """A model of random weights, saved with its config.json; its path."""
    from stable_baselines3 import PPO
    from efz_env.policy import EfzPolicy, policy_kwargs
    th.manual_seed(seed)
    width = OBS_DIM + 6 * history
    if efz:
        model = PPO(EfzPolicy, Spaces(width), policy_kwargs=policy_kwargs(width=64), device='cpu',
                    n_steps=64, batch_size=64)
        rng = np.random.default_rng(seed)
        model.policy.set_scale(rng.normal(size=width), rng.uniform(0.5, 2, width))
        with th.no_grad():  # embeddings that matter
            for p in model.policy.parameters():
                p.add_(th.randn_like(p) * 0.3)
    else:  # SB3's MlpPolicy: tanh, no embeddings
        model = PPO('MlpPolicy', Spaces(width), device='cpu', n_steps=64, batch_size=64,
                    policy_kwargs=dict(net_arch=dict(pi=[32, 32], vf=[32, 32])))
    path = os.path.join(folder, 'model.zip')
    model.save(path)
    with open(os.path.join(folder, 'config.json'), 'w') as f:
        json.dump(dict(frame_skip=frame_skip, history=history, delay=delay,
                       chars=['ayu', None]), f)
    return path, model


class Export(unittest.TestCase):
    def check(self, efz):
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder, efz=efz)
            out = os.path.join(folder, 'agent.efzagent')
            diff = export_agent(path, out)
            self.assertLess(diff, 1e-4)
            agent = NativeAgent(out)
            self.assertEqual((agent.width, agent.actions), (OBS_DIM + 12, 45))
            self.assertEqual((agent.frame_skip, agent.history, agent.delay), (1, 2, 3))
            self.assertEqual(agent.character, 1)  # ayu
            self.assertEqual(agent.name, os.path.basename(folder))
            views = sample_views(agent.width, 64, seed=5)
            np.testing.assert_allclose(agent.log_probs(views), torch_log_probs(model.policy, views),
                                       atol=1e-4)
            agent.close()

    def test_efz_policy(self):
        self.check(True)

    def test_mlp_policy(self):
        self.check(False)

    def test_refuses_what_isnt_one(self):
        with tempfile.TemporaryDirectory() as folder:
            path = os.path.join(folder, 'x.efzagent')
            with open(path, 'wb') as f:
                f.write(b'not an agent')
            with self.assertRaisesRegex(RuntimeError, 'not an agent file'):
                NativeAgent(path)


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class PlaysAsTheModel(unittest.TestCase):
    def play(self, frame_skip):
        # The exported agent beside efz_env.agent.Agent, both choosing their likeliest
        # action, on the views of a match against the CPU that the exported one plays,
        # stepped as play.py's HumanMatch steps an agent: the same decisions.
        from efz_env import EfzVecEnv
        from efz_env.agent import Agent
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=4, delay=5, frame_skip=frame_skip, seed=2)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            native = NativeAgent(out, deterministic=True)
            agent = Agent(path, deterministic=True)
            env = EfzVecEnv(DATA, 1, num_threads=1, frame_skip=1, skip_noninteractive=False,
                            autoreset='disabled', max_frames=0)
            env.set_matches(chars=('ayu', 'mai'), stage=0, cpu=(False, True))
            names = env.observation_names
            intro, over = names.index('intro'), names.index('round_over')
            env.reset(seed=1)
            native.reset()
            agent.reset()
            controls = np.zeros((1, 2), np.uint8)
            held, decisions = 0, 0
            for _ in range(1500):
                obs = env.obs[0, 0].copy()
                actionable = obs[intro] == 0 and obs[over] == 0
                controls[0, 0] = native.step(obs, actionable)
                if held == 0 and actionable:
                    self.assertEqual(native.last_action, agent(obs))
                    held, decisions = frame_skip, decisions + 1
                held = max(0, held - 1)
                _, _, term, trunc, _ = env.step(controls)
                if term[0] or trunc[0]:
                    break
            self.assertGreater(decisions, 1500 // frame_skip // 2)
            env.close()
            native.close()

    def test_every_frame(self):
        self.play(1)

    def test_frame_skip(self):
        self.play(3)


if __name__ == '__main__':
    unittest.main()
