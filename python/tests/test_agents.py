"""Agent files (efz_env.export, port/agent/policy.h): a model written as one plays as the
model does, run by the library as the game runs it; its routes are planned as
runs/human-ayu/redteam.py's planner plans them (port/agent/routes.h). Needs the efz_env
library and stable-baselines3; the matches played need the game's data ($EFZ_DATA) too."""

import json
import os
import sys
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


RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class PlansAsRedteam(unittest.TestCase):
    """At each hit of a match, the game's planner (efz_env_agent_plan) and redteam.py's, as
    combo_support.py's _live_worker runs it for play.py --assist, on the same game: the
    same routes tried, the same damage from each, the same choice, the same view expected;
    and the game left as it was."""

    HISTORY, DELAY = 4, 5

    def script(self, f):
        return 0x10 if f % 7 == 0 else 0x01  # forward, and A now and then

    def hits(self, env, frames=2400):
        """The match played by the script: at each of player 1's hits (its combo counter
        from 0), the frame, the state, the starter and its input history."""
        from efz_env.history import InputHistory
        env.reset(seed=4)
        hist = InputHistory((1,), self.HISTORY)
        controls = np.zeros((1, 2), np.uint8)
        out, prev_hits = [], 0
        for f in range(frames):
            obs = env.obs[0, 0].copy()
            hits = int(round(float(obs[30]) * 30))
            if hits > 0 and prev_hits == 0:
                out.append(dict(frame=f, state=env.save_state(0), starter=int(round(float(obs[18]))),
                                hist=hist.buf[0].copy(), prev=int(hist.prev[0]), obs=obs))
            prev_hits = hits
            controls[0, 0] = self.script(f)
            hist.push(controls[:, 0])
            _, _, term, trunc, _ = env.step(controls)
            if term[0] or trunc[0]:
                break
        return out

    def test_same_plans(self):
        sys.path.insert(0, RUNS)
        try:
            import redteam
            from combo_support import sampler
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        from stable_baselines3 import PPO
        from efz_env import ActionTable, EfzVecEnv
        from efz_env.actions import BACK
        from efz_env.history import InputHistory
        table = ActionTable().table
        env = EfzVecEnv(DATA, 1, num_threads=1, frame_skip=1, skip_noninteractive=False,
                        autoreset='disabled', max_frames=0)
        env.set_matches(chars=('ayu', 'mai'), stage=0, cpu=(False, False))
        hits = self.hits(env)
        self.assertGreater(len(hits), 2)
        # A library of random routes for the starters seen, and some for none of them; half
        # landed on mai, kept for that victim (theirs first), half on akane.
        rng = np.random.default_rng(9)
        library = []
        for starter in sorted({h['starter'] for h in hits}) + [9999]:
            for k in range(16):
                n = int(rng.integers(self.DELAY + 1, 160))
                acts = np.where(rng.random(n) < 0.6, rng.integers(0, 45, n), 0)
                library.append(dict(starter=starter, actions=acts.astype(np.int64),
                                    opponent='mai' if k % 2 else 'akane',
                                    kept_for='victim' if k % 3 else 'overall'))
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False, library=library)
            native = NativeAgent(out, deterministic=True)
            self.assertEqual(native.routes, len(library))
            model = PPO.load(path, device='cpu')
            planner = redteam.Planner(DATA, library, model, per_start=12, history=self.HISTORY)
            policy = sampler(model, deterministic=True)
            sim = planner.sim
            pre = np.zeros((sim.num_envs, 2), np.uint8)
            index = {id(m): i for i, m in enumerate(library)}
            compared = routes_chosen = 0
            for h in hits[:8]:
                env.load_state(0, h['state'])
                actions = rng.integers(0, 45, self.DELAY)
                hist = InputHistory((1,), self.HISTORY)
                hist.buf[0], hist.prev[0] = h['hist'], h['prev']
                for a in actions:
                    hist.push(table[np.array([a])])
                mine = native.plan(env, 0, 0, h['starter'], actions, hist.buf[0], int(hist.prev[0]))
                self.assertEqual(env.save_state(0), h['state'])  # the game as it was
                # _live_worker's steps, then the planner's.
                sim.load_state(0, h['state'])
                seen = [sim.obs[0, 0].copy()]
                for a in actions:
                    pre[0, 0], pre[0, 1] = table[a], BACK
                    seen.insert(0, sim.step(pre)[0][0, 0].copy())
                chosen, best, own = planner.plan(sim.save_state(0), 0, h['starter'],
                                                 hist.buf[0].copy(), int(hist.prev[0]),
                                                 offset=self.DELAY, seen=np.stack(seen),
                                                 policy=policy)
                theirs = planner.last
                self.assertEqual(mine['outcome'], 'planned')
                self.assertEqual(mine['tried'], [index[id(m)] for m in theirs['picked']] + [-1])
                np.testing.assert_array_equal(mine['dealt'], theirs['dealt'].astype(np.float32))
                np.testing.assert_array_equal(mine['expected'][1:], seen[0][1:])
                want = None if chosen is None else index[id(next(
                    m for m in theirs['picked'] if np.array_equal(m['actions'][self.DELAY:], chosen)))]
                self.assertEqual(mine['chosen'], want)
                compared += 1
                routes_chosen += want is not None
            self.assertGreater(compared, 2)
            native.close()
        env.close()


if __name__ == '__main__':
    unittest.main()
