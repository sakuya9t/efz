"""PettingZoo's Parallel API: one match, both players agents.

    from efz_env.pettingzoo import EfzParallelEnv
    env = EfzParallelEnv('/path/to/EFZ', chars=('ayu', 'mai'))
    obs, infos = env.reset(seed=0)
    while env.agents:
        actions = {a: env.action_space(a).sample() for a in env.agents}
        obs, rewards, terminations, truncations, infos = env.step(actions)

PettingZoo has no batched form: each EfzParallelEnv is a batch of one, so many of them
step one after another. For training many matches at once use efz_env.sb3 (opponent=
'self') or EfzVecEnv, which step every match of a batch in parallel.
"""

import functools

import numpy as np
from gymnasium import spaces
from pettingzoo import ParallelEnv

from .actions import ActionTable
from .vec import EfzVecEnv


class EfzParallelEnv(ParallelEnv):
    metadata = {'name': 'efz_v0', 'render_modes': ['rgb_array'], 'render_fps': 64}
    possible_agents = ['player_1', 'player_2']

    def __init__(self, data_dir=None, *, action_table=None, chars=(None, None), stage=None,
                 char_pool=None, stage_pool=None, cpu=(False, False), render_mode=None,
                 **config):
        if any(cpu):
            raise ValueError('both players are agents here: for the CPU use efz_env.gym')
        if render_mode == 'rgb_array':
            config['drawing'] = True
        config.setdefault('num_threads', 1)
        self.env = EfzVecEnv(data_dir, 1, autoreset='disabled', **config)
        self.env.set_matches(chars=chars, stage=stage, char_pool=char_pool,
                             stage_pool=stage_pool)
        self.table = action_table or ActionTable()
        self.render_mode = render_mode
        self.agents = []
        self._controls = np.zeros((1, 2), dtype=np.uint8)
        self._obs_space = spaces.Box(-np.inf, np.inf, (self.env.obs_dim,), np.float32)
        self._act_space = spaces.Discrete(len(self.table))

    @functools.lru_cache(maxsize=None)
    def observation_space(self, agent):
        return self._obs_space

    @functools.lru_cache(maxsize=None)
    def action_space(self, agent):
        return self._act_space

    def _infos(self):
        i = self.env.info[0]
        return {a: {'frame': int(i['frame']), 'round': int(i['round']),
                    'hp': int(i['hp'][p]), 'rounds_won': int(i['rounds_won'][p]),
                    'winner': int(i['winner'])}
                for p, a in enumerate(self.agents)}

    def reset(self, seed=None, options=None):
        self.agents = list(self.possible_agents)
        obs = self.env.reset(seed=seed)
        return {a: obs[0, p].copy() for p, a in enumerate(self.agents)}, self._infos()

    def step(self, actions):
        for p, a in enumerate(self.possible_agents):
            self._controls[0, p] = self.table.table[int(actions.get(a, 0))]
        obs, reward, terminated, truncated, _ = self.env.step(self._controls)
        agents = self.agents
        out = ({a: obs[0, p].copy() for p, a in enumerate(agents)},
               {a: float(reward[0, p]) for p, a in enumerate(agents)},
               {a: bool(terminated[0]) for a in agents},
               {a: bool(truncated[0]) for a in agents},
               self._infos())
        if terminated[0] or truncated[0]:
            self.agents = []
        return out

    def render(self):
        if self.render_mode != 'rgb_array':
            return None
        return self.env.render(0)

    def close(self):
        self.env.close()
