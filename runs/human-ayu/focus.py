"""A focus for an opponent: a shaping reward, on top of the game's, for what it is
meant to be good at, by tactics.py's definitions, for finetune.py --focus.

    env = Focus(EfzSB3VecEnv(...), 'setup', coef=0.02)

'setup': a move started in free time (the learner free, its opponent not: tactics'
    free time) that puts out an object of its own within SETUP_WINDOW steps (a trap, a
    projectile: Mizuka's, Misuzu's game);
'charge': a move that builds the character's own resource (tactics.CHARGE: Kano's 5D,
    236D) started in free time;
'reversal': an invincible attack of its own (framedata.json: invulnerable in its first
    steps; not a throw) started as it rises (within WAKE_WINDOW steps of a knockdown's
    end) or after a recoil guard (within RG_WINDOW steps), that hits the opponent within
    REVERSAL_WINDOW steps, before the learner is hit itself: the user's answer to an agent
    that presses the same thing at every wake-up and in every string ("a wake-up
    invincible, or an RG and an invincible during it").

Each such event adds `coef` to the step's reward (the game's: damage dealt minus taken
in full bars, so 0.02 is 200 HP's worth). The learner is player 1; the events are read
from its current view (as the game is, not as it sees it late). `counts` keeps the
events and steps since the last `take()`, for the log.
"""

import numpy as np
from stable_baselines3.common.vec_env import VecEnvWrapper

import tactics

ACT_SELF, ACT_OPP = 18, 50
HITSTUN_SELF, HITSTUN_OPP = 20, 52
OBJECTS = [72 + 6 * k for k in range(8)]  # self_obj<k>_active
SETUP_WINDOW = 30
WAKE_WINDOW = 8       # steps after a knockdown's end in which a reversal is a wake-up one
RG_WINDOW = 20        # ... after a recoil guard
REVERSAL_WINDOW = 40  # steps in which a reversal must hit
FOCUSES = ('setup', 'charge', 'reversal')


def reversal_moves(char):
    """A character's invincible attacks (framedata.json), throws left out (level 0)."""
    import json
    import os
    path = os.path.join(tactics.HERE, 'framedata.json')
    data = json.load(open(path)).get(char, {}) if os.path.exists(path) else {}
    return {int(k, 16) for k, m in data.items()
            if m['invincible'] and m['startup'] is not None and m['level'] >= 10
            and int(k, 16) < tactics.FIRST_OBJECT}


class Focus(VecEnvWrapper):
    def __init__(self, venv, focus, coef=0.02, char=None):
        if focus not in FOCUSES:
            raise ValueError(f'focus: one of {FOCUSES}')
        super().__init__(venv)
        self.focus, self.coef = focus, coef
        self.charge = set(tactics.CHARGE.get(char, []))
        if focus == 'charge' and not self.charge:
            raise ValueError(f"{char} has no charge moves (tactics.CHARGE)")
        self.reversals = reversal_moves(char) if focus == 'reversal' else set()
        if focus == 'reversal' and not self.reversals:
            raise ValueError(f'{char} has no invincible attacks (framedata.json)')
        n = venv.num_envs
        self.prev = None
        self.pending = np.full(n, -1)          # steps left for a setup's object to appear
        self.pending_objects = np.zeros(n, int)
        self.since_down = np.full(n, 999)      # steps since it rose from a knockdown
        self.since_rg = np.full(n, 999)        # ... since a recoil guard
        self.counts = dict(events=0, steps=0)

    def _raw(self):
        return self.venv.env.obs[:, 0]  # EfzSB3VecEnv's game: player 1's current view

    def reset(self):
        obs = self.venv.reset()
        self.prev = self._raw().copy()
        self.pending[:] = -1
        self.since_down[:] = 999
        self.since_rg[:] = 999
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
        elif self.focus == 'charge':
            bonus[started & np.isin(a, list(self.charge))] = self.coef
        else:
            rose = np.isin(a0, tactics.DOWN) & ~np.isin(a, tactics.DOWN)
            self.since_down = np.where(rose, 0, np.minimum(self.since_down + 1, 999))
            self.since_rg = np.where(np.isin(a, tactics.RG), 0, np.minimum(self.since_rg + 1, 999))
            new = (a != a0) & np.isin(a, list(self.reversals)) & (self.pending < 0) & (
                (self.since_down <= WAKE_WINDOW) | (self.since_rg <= RG_WINDOW))
            self.pending[new] = REVERSAL_WINDOW
            live = self.pending > 0
            hit_opp = (now[:, HITSTUN_OPP] > 0) & ~(prev[:, HITSTUN_OPP] > 0)
            hit_me = (now[:, HITSTUN_SELF] > 0) & ~(prev[:, HITSTUN_SELF] > 0)
            landed = live & hit_opp & ~hit_me
            bonus[landed] = self.coef
            self.pending[landed | (live & hit_me)] = -1
            self.pending[live & ~landed & ~hit_me] -= 1
            self.pending[self.pending == 0] = -1
            self.since_down[done] = 999
            self.since_rg[done] = 999
        self.pending[done] = -1
        self.prev = raw.copy()
        self.counts['events'] += int((bonus > 0).sum())
        self.counts['steps'] += len(a)
        return obs, reward + bonus.astype(reward.dtype), done, infos
