"""Practice among the agent's matches: combo trials (combo.py's ComboTrials) in a share of
finetune.py's environments (--practice), as a player practises in training mode: from a
hit, with the resources preset and the opponent a dummy, for the combo's damage (the
user's idea).

    pool = StartPool(size=400)                                   # the agent's own first hits
    pool = StartPool.people(data_dir, starts_folder, replays)    # or people's (combo_starts.py)
    trials = ComboTrials(data_dir, [], k, delay, history, sample=pool.sample,
                         reward_scale=1 / 9999, bootstrap=True, rich=0.5)
    env = Practice(matches, trials, pool, harvest=agent_matches)   # one VecEnv for PPO

A trial's reward is the match's own (damage dealt, per full bar) and its end is a time
limit to SB3, which values the state the combo left as the match's: practice and matches
teach one thing, and the KL pull toward the clone and the reaction time hold in both.

Own starts: when the learner (player 1) lands a first hit in a match against an agent (not
the CPU: a saved game keeps who is the CPU, and a trial's dummy must be the program's),
with probability `keep` the game is saved with the views and inputs the learner had; once
the pool is full a new start replaces one at random, so the pool follows the learner.
People's starts are fixed: those of people's Ayu (combo_starts.py), made again by playing
their replays back. Either way trials draw a situation evenly (the opponent in the air or
on the ground, in the corner or not: what a player sets up in training mode), then a start
in it; the resources are the start's, or in `rich` of the trials drawn from evaluate.GROUPS.
"""

import numpy as np
from stable_baselines3.common.vec_env.base_vec_env import VecEnv

COMBO_HITS, OPP_X, OPP_AIRBORNE = 30, 45, 71  # self_combo_hits (/ 30), opp_x ((x-320)/320)
CORNER = 0.7  # |opp_x| beyond this: within about 100 px of a wall


def kind(view):
    """A start's situation: 'air' or 'ground', 'corner' or 'mid'."""
    return (('air' if view[OPP_AIRBORNE] > 0 else 'ground') + '-' +
            ('corner' if abs(view[OPP_X]) > CORNER else 'mid'))


def _base(env):
    """The EfzSB3VecEnv under any wrappers (focus.Focus)."""
    while not hasattr(env, 'delay'):
        env = env.venv
    return env


class StartPool:
    def __init__(self, size=400, keep=0.25, seed=0):
        self.size, self.keep = size, keep
        self.rng = np.random.default_rng(seed)
        self.starts = []
        self.growing = True
        self.offered = 0

    @classmethod
    def people(cls, data_dir, folder, replays, split='train', limit=500, seed=0):
        import combo
        rng = np.random.default_rng(seed)
        starts = combo.load_starts(folder, split, limit, rng)
        combo.restore(data_dir, replays, starts)
        pool = cls(size=len(starts), seed=seed)
        pool.starts = [dict(st, kind=kind(st['seen'][-1])) for st in starts if 'state' in st]
        pool.growing = False
        return pool

    def kinds(self):
        out = {}
        for st in self.starts:
            out[st['kind']] = out.get(st['kind'], 0) + 1
        return out

    def sample(self, rng):
        """A situation drawn evenly, then a start in it."""
        if not self.starts:
            raise RuntimeError('practice: no starts yet (fill() the pool first)')
        kinds = np.array([st['kind'] for st in self.starts])
        k = rng.choice(np.unique(kinds))
        return self.starts[rng.choice(np.flatnonzero(kinds == k))]

    def offer(self, base, i):
        """The learner's first hit in environment i of `base` (an EfzSB3VecEnv), as a start
        with probability keep."""
        self.offered += 1
        if self.rng.random() >= self.keep:
            return
        view = base.env.obs[i, 0]
        st = dict(state=base.env.save_state(i), side=0,
                  seen=base.delay.buf[i, 0][::-1].copy(),   # oldest first, the start last
                  hist=base.history.buf[i, 0].copy(), prev=int(base.history.prev[i, 0]),
                  kind=kind(view), file='own')
        if len(self.starts) < self.size:
            self.starts.append(st)
        else:
            self.starts[self.rng.integers(self.size)] = st


def harvest(pool, base, prev_hits, mask, done):
    """Offers the learner's first hits of this step to the pool; returns the hits now."""
    hits = np.round(base.env.obs[:, 0, COMBO_HITS] * 30).astype(int)
    first = (prev_hits == 0) & (hits > 0) & mask & ~done
    for i in np.flatnonzero(first):
        pool.offer(base, i)
    return np.where(done, 0, hits)


def fill(pool, matches, model, n=48, max_steps=30000, mask=None):
    """Plays the matches with the model until the pool holds n starts (every first hit
    kept meanwhile): trials need some from the start."""
    base = _base(matches)
    mask = np.ones(matches.num_envs, bool) if mask is None else np.asarray(mask, bool)
    keep, pool.keep = pool.keep, 1.0
    obs = matches.reset()
    prev = np.zeros(matches.num_envs, int)
    for _ in range(max_steps):
        if len(pool.starts) >= n:
            break
        obs, _, done, _ = matches.step(model.predict(obs, deterministic=False)[0])
        prev = harvest(pool, base, prev, mask, done)
    pool.keep = keep
    return len(pool.starts)


class Practice(VecEnv):
    """The matches' environments, then the trials', as one VecEnv. harvest: the matches
    whose learner's first hits go to the pool (those against agents); none for a fixed
    pool."""

    def __init__(self, matches, trials, pool=None, harvest=None):
        self.matches, self.trials, self.pool = matches, trials, pool
        self.m, self.k = matches.num_envs, trials.num_envs
        self.base = _base(matches)
        self.mask = (np.ones(self.m, bool) if harvest is None
                     else np.asarray(harvest, bool).copy())
        self.prev_hits = np.zeros(self.m, int)
        super().__init__(self.m + self.k, matches.observation_space, matches.action_space)

    def reset(self):
        self.prev_hits[:] = 0
        return np.concatenate([self.matches.reset(), self.trials.reset()]).astype(np.float32)

    def step_async(self, actions):
        actions = np.asarray(actions)
        self.matches.step_async(actions[:self.m])
        self.trials.step_async(actions[self.m:])

    def step_wait(self):
        a_obs, a_r, a_d, a_i = self.matches.step_wait()
        b_obs, b_r, b_d, b_i = self.trials.step_wait()
        if self.pool is not None and self.pool.growing:
            self.prev_hits = harvest(self.pool, self.base, self.prev_hits, self.mask, a_d)
        return (np.concatenate([a_obs, b_obs]).astype(np.float32),
                np.concatenate([a_r, b_r]).astype(np.float32),
                np.concatenate([a_d, b_d]), list(a_i) + list(b_i))

    def take(self):
        """The matches' focus events (focus.Focus), for finetune.py's log."""
        return self.matches.take()

    def take_trials(self):
        """The trials since the last call: their count, combo damage (average, 90th
        percentile, most), hits, and shares with an Instant Charge and a special."""
        r, self.trials.recent = self.trials.recent, []
        if not r:
            return dict(trials=0)
        d = np.array([x['damage'] for x in r])
        return dict(trials=len(r), damage=round(float(d.mean())),
                    damage_p90=round(float(np.percentile(d, 90))), damage_max=round(float(d.max())),
                    hits=round(float(np.mean([x['hits'] for x in r])), 2),
                    ic=round(float(np.mean([x['ic'] for x in r])), 3),
                    special=round(float(np.mean([x['special'] for x in r])), 3))

    def close(self):
        self.matches.close()
        self.trials.close()

    def get_attr(self, attr_name, indices=None):
        return [getattr(self, attr_name)] * len(self._get_indices(indices))

    def set_attr(self, attr_name, value, indices=None):
        setattr(self, attr_name, value)

    def env_method(self, method_name, *args, indices=None, **kwargs):
        result = getattr(self, method_name)(*args, **kwargs)
        return [result] * len(self._get_indices(indices))

    def env_is_wrapped(self, wrapper_class, indices=None):
        return [False] * len(self._get_indices(indices))
