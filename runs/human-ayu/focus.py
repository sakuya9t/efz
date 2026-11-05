"""A focus for an opponent: a shaping reward, on top of the game's, for what it is
meant to be good at, by tactics.py's definitions, for finetune.py --focus.

    env = Focus(EfzSB3VecEnv(...), 'setup', coef=0.02)

'setup': a move started in free time (the learner free, its opponent not: tactics'
    free time) that puts out an object of its own within SETUP_WINDOW steps (a trap, a
    projectile: Mizuka's, Misuzu's game);
'charge': a move that builds the character's own resource (tactics.CHARGE: Kano's 5D,
    236D) started in free time.

Each such event adds `coef` to the step's reward (the game's: damage dealt minus taken
in full bars, so 0.02 is 200 HP's worth). The learner is player 1; the events are read
from its current view (as the game is, not as it sees it late). `counts` keeps the
events and steps since the last `take()`, for the log.
"""

import numpy as np
from stable_baselines3.common.vec_env import VecEnvWrapper

import tactics

ACT_SELF, ACT_OPP = 18, 50
OBJECTS = [72 + 6 * k for k in range(8)]  # self_obj<k>_active
SETUP_WINDOW = 30
FOCUSES = ('setup', 'charge')


class Focus(VecEnvWrapper):
    def __init__(self, venv, focus, coef=0.02, char=None):
        if focus not in FOCUSES:
            raise ValueError(f'focus: one of {FOCUSES}')
        super().__init__(venv)
        self.focus, self.coef = focus, coef
        self.charge = set(tactics.CHARGE.get(char, []))
        if focus == 'charge' and not self.charge:
            raise ValueError(f"{char} has no charge moves (tactics.CHARGE)")
        n = venv.num_envs
        self.prev = None
        self.pending = np.full(n, -1)          # steps left for a setup's object to appear
        self.pending_objects = np.zeros(n, int)
        self.counts = dict(events=0, steps=0)

    def _raw(self):
        return self.venv.env.obs[:, 0]  # EfzSB3VecEnv's game: player 1's current view

    def reset(self):
        obs = self.venv.reset()
        self.prev = self._raw().copy()
        self.pending[:] = -1
        return obs

    def take(self):
        c = dict(self.counts)
        self.counts = dict(events=0, steps=0)
        return c

    def step_wait(self):
        obs, reward, done, infos = self.venv.step_wait()
        raw = self._raw()
        now = np.where(done[:, None], self.venv.env.final_obs[:, 0], raw)  # before a reset
        prev = self.prev
        a0, o0 = np.round(prev[:, ACT_SELF]).astype(int), np.round(prev[:, ACT_OPP]).astype(int)
        a = np.round(now[:, ACT_SELF]).astype(int)
        free = np.isin(a0, tactics.FREE) & ~np.isin(o0, tactics.FREE)
        started = (a != a0) & (a >= tactics.FIRST_OWN) & free
        bonus = np.zeros(len(a))
        if self.focus == 'setup':
            objects_before = (prev[:, OBJECTS] > 0).sum(1)
            objects = (now[:, OBJECTS] > 0).sum(1)
            new = started & (self.pending < 0)
            self.pending[new] = SETUP_WINDOW
            self.pending_objects[new] = objects_before[new]
            live = self.pending > 0
            hit = live & (objects > self.pending_objects)
            bonus[hit] = self.coef
            self.pending[hit] = -1
            self.pending[live & ~hit] -= 1
            self.pending[self.pending == 0] = -1
        else:
            bonus[started & np.isin(a, list(self.charge))] = self.coef
        self.pending[done] = -1
        self.prev = raw.copy()
        self.counts['events'] += int((bonus > 0).sum())
        self.counts['steps'] += len(a)
        return obs, reward + bonus.astype(reward.dtype), done, infos
