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


def is_agent_file(path):
    return os.fspath(path).lower().endswith('.efzagent')


def model_file(path):
    """A model's zip: `path`, or for an agent file (.efzagent) the model it carries,
    unpacked for this process (efz_env.export.unpacked_model)."""
    if is_agent_file(path):
        from .export import unpacked_model
        return unpacked_model(path)
    return path


def load_config(path):
    """The settings of a model: <name>.config.json beside <name>.zip if there is one, else
    the folder's config.json, else {}. Of an agent file (.efzagent): the ones it carries."""
    path = os.path.abspath(model_file(path))
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
        self.model = PPO.load(model_file(path), device='cpu')  # (a packed agent: its model)
        self.frame_skip = int(frame_skip or cfg.get('frame_skip', 4))
        self.history = int(history if history is not None else cfg.get('history', 0))
        self.delay = int(delay if delay is not None else cfg.get('delay', 0))
        self.width = self.model.observation_space.shape[0]
        # memory: efz_env.memory.Memory's arguments, for a model trained with a match
        # memory (EfzSB3VecEnv's memory=): its features are the last of what it sees.
        self.memory_config = cfg.get('memory')
        self.deterministic = deterministic
        self.table = ActionTable()
        self.batch(n)

    def batch(self, n):
        """Plays n environments from now on (a new match in each)."""
        self.hist = InputHistory((n,), self.history) if self.history else None
        self.seen = None  # Delay, made at the first view (its width)
        self.n = n
        self.last = None
        # What it is told beyond the game's view, (n, k): the features after its input
        # history, for a model trained with them (EfzSB3VecEnv's extra); its host writes
        # them (evaluate.py: the opponent's habits), 0 where nobody does.
        self.told = None
        self.memory = None
        self._next = None
        if self.memory_config is not None:
            from .memory import Memory
            self.memory = Memory(n, **self.memory_config)

    def reset(self, mask=None, won=None, new_set=None):
        """A new match (where mask): no inputs yet. Its memory, if it has one: where
        new_set (default: everywhere) the match is against someone new and nothing is
        kept; elsewhere the set goes on (won: where it won the match that ended)."""
        if self.hist is not None:
            self.hist.clear(mask)
        if self.seen is not None:
            self.seen.clear(mask)
        if self.memory is not None:
            ended = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
            if won is None and new_set is None and self._next is not None:
                won, new_set = self._next  # (said before, through hosts that pass a mask only)
            self._next = None
            self.memory.end(ended, won, ended if new_set is None else new_set)
        if mask is None:
            self.last = None

    def set_next(self, won=None, new_set=None):
        """What the next reset(mask) is to know, for a host whose wrappers pass it a
        mask only: where the agent won the matches that end, and where a new set starts."""
        self._next = (won, new_set)

    def view(self, obs):
        if self.delay:
            if self.seen is None:
                self.seen = Delay((len(obs),), self.delay, obs.shape[1])
            obs = self.seen.push(obs)
        remembered = None
        if self.memory is not None:  # of what it sees (late, if it sees late)
            self.memory.update(obs)
            remembered = self.memory.features()
        if self.hist is not None:
            obs = np.concatenate([obs, self.hist.features()], axis=1)
        room = self.width - obs.shape[1] - (0 if remembered is None else remembered.shape[1])
        if room > 0:  # a model that is told more
            more = np.zeros((len(obs), room), np.float32)
            if self.told is not None:
                more[:] = self.told
            obs = np.concatenate([obs, more], axis=1)
        if remembered is not None:
            obs = np.concatenate([obs, remembered], axis=1)
        return obs[:, :self.width]

    def decide(self, obs):
        """Action indices for a batch of observations (n, obs_dim)."""
        return self.model.predict(self.view(obs), deterministic=self.deterministic)[0]

    def controls(self, obs, step):
        """Control bytes: a new decision every frame_skip steps, held in between (call
        it every step: a delayed agent sees every step)."""
        if (self.delay or self.memory is not None) and \
                not (self.last is None or step % self.frame_skip == 0):
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
