"""A trained agent as it was trained: its model.zip, and the config.json beside it saying
how often it decides (frame_skip), how many steps of its own inputs it sees (history,
efz_env.history) and how many steps late it sees the game (delay).

    agent = Agent('runs/human-ayu/model.zip', n=num_envs)   # in an environment of frame_skip=1
    agent.reset()
    for step in itertools.count():
        controls[:, 0] = agent.controls(obs[:, 0], step)   # decides every agent.frame_skip steps
        obs, _, term, trunc, info = env.step(controls)
        agent.observe(info['input'][:, 0])
        agent.reset(term | trunc)

or, deciding once per call and remembering its own choice (HumanMatch's policy, which
holds it for agent.frame_skip frames): action = agent(obs). Needs stable-baselines3.
"""

import json
import os

import numpy as np

from .actions import ActionTable
from .history import Delay, InputHistory


def load_config(path):
    """The settings of a model: <name>.config.json beside <name>.zip if there is one, else
    the folder's config.json, else {}."""
    path = os.path.abspath(path)
    stem = path[:-4] if path.endswith('.zip') else path
    for p in (stem + '.config.json', os.path.join(os.path.dirname(path), 'config.json')):
        if os.path.exists(p):
            with open(p) as f:
                return json.load(f)
    return {}


class Agent:
    def __init__(self, path, n=1, deterministic=False, frame_skip=None, history=None,
                 delay=None):
        from stable_baselines3 import PPO
        cfg = load_config(path)
        self.path = path
        self.model = PPO.load(path, device='cpu')
        self.frame_skip = int(frame_skip or cfg.get('frame_skip', 4))
        self.history = int(history if history is not None else cfg.get('history', 0))
        self.delay = int(delay if delay is not None else cfg.get('delay', 0))
        self.width = self.model.observation_space.shape[0]
        self.deterministic = deterministic
        self.table = ActionTable()
        self.batch(n)

    def batch(self, n):
        """Plays n environments from now on (a new match in each)."""
        self.hist = InputHistory((n,), self.history) if self.history else None
        self.seen = None  # Delay, made at the first view (its width)
        self.n = n
        self.last = None

    def reset(self, mask=None):
        """A new match (where mask): no inputs yet."""
        if self.hist is not None:
            self.hist.clear(mask)
        if self.seen is not None:
            self.seen.clear(mask)
        if mask is None:
            self.last = None

    def view(self, obs):
        if self.delay:
            if self.seen is None:
                self.seen = Delay((len(obs),), self.delay, obs.shape[1])
            obs = self.seen.push(obs)
        if self.hist is None:
            return obs[:, :self.width]
        return np.concatenate([obs, self.hist.features()], axis=1)[:, :self.width]

    def decide(self, obs):
        """Action indices for a batch of observations (n, obs_dim)."""
        return self.model.predict(self.view(obs), deterministic=self.deterministic)[0]

    def controls(self, obs, step):
        """Control bytes: a new decision every frame_skip steps, held in between (call
        it every step: a delayed agent sees every step)."""
        if self.delay and not (self.last is None or step % self.frame_skip == 0):
            self.view(obs)  # seen, though not decided on
        if self.last is None or len(self.last) != len(obs) or step % self.frame_skip == 0:
            self.last = self.decide(obs)
        return self.table.to_bytes(self.last)

    def observe(self, controls):
        """The controls it played on the step (info['input'] of its side)."""
        if self.hist is not None:
            self.hist.push(np.asarray(controls, np.uint8))

    def __call__(self, obs):
        """One decision for one environment (obs_dim,), its controls remembered."""
        action = int(self.decide(np.asarray(obs)[None])[0])
        self.observe(self.table.to_bytes(np.array([action])))
        return action
