"""Stable-Baselines3's VecEnv over EfzVecEnv.

    from stable_baselines3 import PPO
    from efz_env.sb3 import EfzSB3VecEnv
    venv = EfzSB3VecEnv('/path/to/EFZ', num_envs=64, opponent='self', frame_skip=4)
    model = PPO('MlpPolicy', venv).learn(1_000_000)

opponent:
    'cpu'   player 1 is the agent, player 2 the game's CPU (num_envs agents).
    'self'  both players are agents of the policy being trained (2 * num_envs agents:
            match m's players are agents 2m and 2m+1); relative_actions makes one policy
            play either side.
    a callable: player 2 plays what it returns for player 2's observations, (n, obs_dim)
            -> n action indices; e.g. frozen(model) for a copy of a policy as it was.

Matches that end restart in the same step, as SB3 expects: infos[i] then holds
'terminal_observation', 'TimeLimit.truncated' and 'episode' ({'r', 'l', 't'}, as SB3's
Monitor writes it, so SB3 logs ep_rew_mean without a VecMonitor).
"""

import time

import numpy as np
from gymnasium import spaces
from stable_baselines3.common.vec_env.base_vec_env import VecEnv

from .actions import ActionTable
from .vec import EfzVecEnv


def frozen(model, deterministic=False):
    """An opponent for EfzSB3VecEnv: a copy of `model`'s policy as it is now."""
    source = model.policy
    policy = type(source)(**source._get_constructor_parameters()).to(source.device)
    policy.load_state_dict(source.state_dict())
    policy.set_training_mode(False)

    def act(obs):
        actions, _ = policy.predict(obs, deterministic=deterministic)
        return actions
    return act


class EfzSB3VecEnv(VecEnv):
    def __init__(self, data_dir=None, num_envs=64, *, opponent='cpu', action_table=None,
                 chars=(None, None), stage=None, char_pool=None, stage_pool=None,
                 **config):
        if 'autoreset' in config and config['autoreset'] != 'same_step':
            raise ValueError("SB3 VecEnvs reset in the same step: leave autoreset alone")
        self.env = EfzVecEnv(data_dir, num_envs, autoreset='same_step', **config)
        self.table = action_table or ActionTable()
        self.n = num_envs
        self.opponent = None
        self.selfplay = opponent == 'self'
        if callable(opponent):
            self.opponent = opponent
        elif opponent not in ('cpu', 'self'):
            raise ValueError("opponent: 'cpu', 'self' or a callable")
        self.env.set_matches(chars=chars, stage=stage, cpu=(False, opponent == 'cpu'),
                             char_pool=char_pool, stage_pool=stage_pool)
        self.k = 2 if self.selfplay else 1
        self._controls = np.zeros((num_envs, 2), dtype=np.uint8)
        self._length = np.zeros(num_envs, dtype=np.int64)
        self._start = time.time()
        obs_space = spaces.Box(-np.inf, np.inf, (self.env.obs_dim,), np.float32)
        super().__init__(self.k * num_envs, obs_space, spaces.Discrete(len(self.table)))

    def set_opponent(self, opponent):
        """Changes player 2's policy (a callable, as `opponent`), e.g. to a newer frozen
        copy. Only for an environment made with a callable opponent."""
        if self.opponent is None:
            raise ValueError('made with a fixed opponent')
        self.opponent = opponent

    def _agents(self, a):
        """(num_envs, 2, ...) -> per agent."""
        return a.reshape((2 * self.n,) + a.shape[2:]) if self.selfplay else a[:, 0]

    def reset(self):
        seeds = [s for s in getattr(self, '_seeds', [])][::self.k] or None
        if seeds is not None and all(s is None for s in seeds):
            seeds = None
        self._length[:] = 0
        obs = self.env.reset(seed=seeds)
        if hasattr(self, '_reset_seeds'):
            self._reset_seeds()
        if hasattr(self, '_reset_options'):
            self._reset_options()
        return self._agents(obs).copy()

    def step_async(self, actions):
        controls = self.table.to_bytes(np.asarray(actions))
        if self.selfplay:
            self._controls[:] = controls.reshape(self.n, 2)
        else:
            self._controls[:, 0] = controls
            if self.opponent is not None:
                self._controls[:, 1] = self.table.to_bytes(self.opponent(self.env.obs[:, 1]))
        self.env.step_async(self._controls)

    def step_wait(self):
        obs, reward, terminated, truncated, info = self.env.step_wait()
        self._length += 1
        ended = terminated | truncated
        infos = [{} for _ in range(self.num_envs)]
        if ended.any():
            final = self._agents(self.env.final_obs)
            elapsed = round(time.time() - self._start, 6)
            for m in np.flatnonzero(ended):
                for p in range(self.k):
                    i = m * self.k + p
                    infos[i] = {
                        'terminal_observation': final[i].copy(),
                        'TimeLimit.truncated': bool(truncated[m] and not terminated[m]),
                        'episode': {'r': float(info['episode_return'][m, p]),
                                    'l': int(self._length[m]), 't': elapsed},
                        'winner': int(info['winner'][m]),
                    }
                self._length[m] = 0
        dones = np.repeat(ended, self.k)
        return self._agents(obs).copy(), self._agents(reward).copy(), dones, infos

    def close(self):
        self.env.close()

    def get_images(self):
        if not self.env.drawing:
            return []
        return [self.env.render(i) for i in range(self.n)]

    # The batch is one object: attributes and methods are the adapter's own.
    def get_attr(self, attr_name, indices=None):
        return [getattr(self, attr_name)] * len(self._get_indices(indices))

    def set_attr(self, attr_name, value, indices=None):
        setattr(self, attr_name, value)

    def env_method(self, method_name, *args, indices=None, **kwargs):
        result = getattr(self, method_name)(*args, **kwargs)
        return [result] * len(self._get_indices(indices))

    def env_is_wrapped(self, wrapper_class, indices=None):
        return [False] * len(self._get_indices(indices))
