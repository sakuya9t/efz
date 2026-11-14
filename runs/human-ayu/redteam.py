"""The red team with lookahead: the combo master's own play, and at each combo's first
hit the most damaging of its options, found by trying them on copies of the game.

A red team needn't be fair, so it needn't predict: when a hit of its lands (its combo
counter goes from 0 to 1), it saves the game and plays on copies of it, side by side,
each library combo with that starter (people's, combo_library.py, as action sequences:
macros.load_library) and its own play, the defender guarding once it can; then it plays
the one that made the most, recorded inputs and all (with a library kept per victim,
combo_library.py --per-victim, those landed on the character it faces first: combos hold
on some characters and not others). That is "the most damaging combo
whenever it can" (the user's), from whatever resources it has. Each plan also says what
the hit was worth: the most any option made from it (its conversion potential), which is
how much a hit there costs, the measure of an "easy location" (the user's: a hit from
which a big combo is likely).

    planner = Planner(data_dir, library, model)       # a batch of copies of its own
    red = RedTeamOpponent(planner, model)             # an opponent for EfzSB3VecEnv
    red.attach(venv)                                  #   (it saves the venv's games)
    red = RedTeamAgent(planner, path)                 # for evaluate.py, record_replay.py

Both keep `plans`: per plan, the potential, what its own play made, and whether a
library combo was chosen.

score='value' (combo_support's built-in combos: Planner(..., score='value')) chooses by
what an option is worth to the player rather than its damage: the damage (the match's
reward, per full bar) plus its critic's value of the game the option left, discounted by
the steps it took (gamma, PPO's). A route that deals a little more but takes long, spends
the gauge or leaves the opponent free is then not chosen over the player's own play.
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

import numpy as np

from efz_env import ActionTable, EfzVecEnv
from efz_env.actions import BACK
from efz_env.history import FEATURES, InputHistory

TABLE = ActionTable()
COMBO_HITS, ACTION = 30, 18
OPP_CHARACTER = 66  # opp_character, the efz_env.vec.character_names() index
REWARD_PER_HP = 1 / 9999  # the match's reward (efz_env's): damage per full bar


def critic(model):
    """views (batch) -> `model`'s value of them: a copy of its critic as it is now."""
    import torch
    from efz_env.sb3 import copy_policy
    policy = copy_policy(model.policy)
    width = policy.observation_space.shape[0]

    def value(obs):
        with torch.no_grad():
            t = torch.as_tensor(np.asarray(obs, np.float32)[:, :width], device=policy.device)
            return policy.predict_values(t).cpu().numpy().ravel()
    return value


def route_pool(by_starter, starter, victim, offset, per_start):
    """The library combos tried from a hit of `starter`: of those long enough to be played
    from their step `offset`, the first per_start (each starter's list is by damage); with
    a victim (a library kept per victim), the combos landed on that character first."""
    pool = by_starter.get(starter, [])
    if victim is not None:
        pool = ([m for m in pool if m.get('opponent') == victim] +
                [m for m in pool if m.get('opponent') != victim])
    return [m for m in pool if len(m['actions']) > offset][:per_start]


class Planner:
    """Tries a hit's options on copies of the game and says which made the most."""

    def __init__(self, data_dir, library, model, per_start=12, limit=900, history=16,
                 score='damage', gamma=0.999, victims=None):
        if score not in ('damage', 'value'):
            raise ValueError("score: 'damage' or 'value'")
        self.library, self.per_start, self.limit = library, per_start, limit
        self.score, self.gamma = score, gamma
        self.value = critic(model) if score == 'value' else None
        self.changed = 0  # plans whose value choice differs from the most damaging
        self.by_starter = {}
        for m in library:
            self.by_starter.setdefault(m['starter'], []).append(m)
        # A library kept per victim: the combos landed on the character faced come first.
        self.by_victim = any(m.get('kept_for') == 'victim' for m in library)
        from efz_env.vec import character_names
        self.names = character_names()
        # victims: the characters it plans against (None: all); against the rest the
        # player's own play, as a person keeps routes for the characters they hold on.
        self.victims = None if victims is None else set(victims)
        unknown = (self.victims or set()) - set(self.names)
        if unknown:
            raise ValueError(f'victims: no such characters {sorted(unknown)}')
        self.sim = EfzVecEnv(data_dir, per_start + 1, frame_skip=1, rounds_to_win=2,
                             max_frames=0, autoreset='disabled')
        self.sim.reset()
        self.model = model
        self.width = model.observation_space.shape[0]
        self.H = history

    def plans_against(self, view):
        """Whether it plans against the character this view (the player's) faces."""
        return (self.victims is None or
                self.names[int(round(float(view[OPP_CHARACTER])))] in self.victims)

    def plan(self, state, side, starter, hist, prev, offset=0, seen=None, policy=None,
             value=None):
        """state: the game at the first hit (or `offset` steps after it); side: the
        attacker's; hist (H, 6), prev: its input history then. offset: the library combos
        are played from that step of theirs (combo_support's fair assist plans when the
        player sees its hit, `delay` steps after it). seen: the player's views up to now,
        newest first ((delay + 1, dim): efz_env.history.Delay's buffer), for its own play
        to see the copies as late as it sees the game; policy: its own play's (obs batch
        -> actions), default the planner's model; value: its critic's (score='value': obs
        batch -> values), default the planner's model's. Returns (actions of the chosen
        library combo from offset, or None for its own play; the most an option made;
        what its own play made)."""
        sim = self.sim
        victim = None
        if self.by_victim:
            sim.load_state(0, state)
            victim = self.names[int(round(float(sim.obs[0, side, OPP_CHARACTER])))]
        picked = route_pool(self.by_starter, starter, victim, offset, self.per_start)
        cands = [m['actions'][offset:] for m in picked]
        n = len(cands) + 1  # the last: its own play
        delayed = None if seen is None else np.array(seen, np.float32)  # newest first
        hp0 = np.zeros(n)
        for j in range(n):
            sim.load_state(j, state)
            hp0[j] = sim.info['hp'][j, 1 - side]
        own_hist = InputHistory((1,), self.H)
        own_hist.buf[0] = hist
        own_hist.prev[0] = prev
        controls = np.zeros((sim.num_envs, 2), np.uint8)
        dealt = np.zeros(n)
        done = np.zeros(n, bool)
        longest = min(self.limit, max([len(m) for m in cands] + [0]) + 60)
        longest = max(longest, 240)  # its own play's combo, at least this long
        track = self.score == 'value'
        if track:  # every option's views (as late as the player sees) and inputs
            views = np.repeat((delayed if delayed is not None else
                               sim.obs[n - 1, side][None]).astype(np.float32)[None], n, 0)
            hists = InputHistory((n,), self.H)
            hists.buf[:] = hist
            hists.prev[:] = prev
            ends = np.zeros((n, self.width), np.float32)
            steps = np.zeros(n)
        for t in range(longest):
            for j, m in enumerate(cands):
                controls[j, side] = TABLE.table[m[t]] if t < len(m) else 0
            now = sim.obs[n - 1, side]
            if delayed is not None:  # as late as the player sees the game
                if t > 0:  # (seen holds the view of the state planned from already)
                    delayed[1:] = delayed[:-1]
                    delayed[0] = now
                now = delayed[-1]
            view = np.concatenate([now, own_hist.features()[0]])[None, :self.width]
            if policy is not None:
                own = int(np.asarray(policy(view))[0])
            else:
                own = int(self.model.predict(view, deterministic=False)[0][0])
            controls[n - 1, side] = TABLE.table[own]
            controls[:n, 1 - side] = BACK
            obs, _, term, trunc, info = sim.step(controls)
            own_hist.push(info['input'][n - 1:n, side])
            if track:
                views[:, 1:] = views[:, :-1]
                views[:, 0] = obs[:n, side]
                hists.push(info['input'][:n, side])
                feats = hists.features()
            for j in np.flatnonzero(~done):
                dealt[j] = max(dealt[j], hp0[j] - float(info['hp'][j, 1 - side]))
                if round(float(obs[j, side, COMBO_HITS]) * 30) == 0 or term[j] or trunc[j]:
                    done[j] = True
                if track and (done[j] or t == longest - 1):
                    ends[j] = np.concatenate([views[j, -1], feats[j]])[:self.width]
                    steps[j] = t + 1
            if done.all():
                break
        if track:  # (an option still going at the last step is valued there)
            worth = (dealt * REWARD_PER_HP +
                     self.gamma ** steps * (value or self.value)(ends))
        else:
            worth = dealt
        best = int(np.argmax(worth))
        chosen = cands[best] if best < len(cands) and worth[best] > worth[-1] else None
        # (the plan as tried, for combo_net.py: the combos, what each and its own play dealt)
        self.last = dict(picked=picked, dealt=dealt[:n].copy())
        if track and best != int(np.argmax(dealt)):
            self.changed += 1
        return chosen, float(dealt.max()), float(dealt[-1])


class _Macros:
    """The library combos being played, per environment."""

    def __init__(self, planner):
        self.planner = planner
        self.playing = {}   # env -> [actions, step]
        self.prev_hits = {}
        self.plans = []     # (potential, own play's, a library combo chosen)

    def step(self, i, view, own_action, save, hist, prev, side):
        hits = round(float(view[COMBO_HITS]) * 30)
        if hits > 0 and self.prev_hits.get(i, 0) == 0:  # a hit of its own landed: plan
            chosen, potential, own = self.planner.plan(save(), side,
                                                       int(round(float(view[ACTION]))), hist, prev)
            self.plans.append((potential, own, chosen is not None))
            self.playing[i] = [chosen, 0] if chosen is not None else None
        self.prev_hits[i] = hits
        m = self.playing.get(i)
        if m is None:
            return own_action
        if (hits == 0 and m[1] > 0) or m[1] >= len(m[0]):  # it ended, or dropped
            self.playing[i] = None
            return own_action
        a = int(m[0][m[1]])
        m[1] += 1
        return a


class RedTeamOpponent:
    """EfzSB3VecEnv's opponent (player 2, seeing the game as it is: opponent_delay 0)."""
    takes_index = True

    def __init__(self, planner, model):
        from efz_env.sb3 import frozen
        self.inner = frozen(model)
        self.macros = _Macros(planner)
        self.venv = None

    @property
    def plans(self):
        return self.macros.plans

    def attach(self, venv):
        self.venv = venv
        self.macros.playing.clear()
        self.macros.prev_hits.clear()

    def __call__(self, obs, idx):
        actions = np.asarray(self.inner(obs)).copy()
        h = self.venv.history
        for k, i in enumerate(idx):
            actions[k] = self.macros.step(
                int(i), obs[k], int(actions[k]), lambda i=i: self.venv.env.save_state(int(i)),
                h.buf[i, 1].copy(), int(h.prev[i, 1]), 1)
        return actions


class RedTeamAgent:
    """As efz_env.agent.Agent (controls, observe, batch, reset), for evaluate.py and
    record_replay.py: attach(env, side) before playing."""

    def __init__(self, planner, path):
        from efz_env.agent import Agent
        self.agent = Agent(path)
        self.macros = _Macros(planner)
        self.frame_skip, self.history = 1, self.agent.history
        self.env, self.side = None, 1

    @property
    def plans(self):
        return self.macros.plans

    def attach(self, env, side):
        self.env, self.side = env, side

    def batch(self, n):
        self.agent.batch(n)
        self.macros.playing.clear()
        self.macros.prev_hits.clear()

    def reset(self, mask=None):
        self.agent.reset(mask)

    def controls(self, obs, step):
        own = self.agent.controls(obs, step)
        out = own.copy()
        hist = self.agent.hist
        for i in range(len(obs)):
            idx = int(self.agent.last[i])  # its own play's action (it decides every step)
            a = self.macros.step(i, obs[i], idx, lambda i=i: self.env.save_state(i),
                                 hist.buf[i].copy() if hist is not None else np.zeros((16, FEATURES)),
                                 int(hist.prev[i]) if hist is not None else 0, self.side)
            out[i] = TABLE.table[a]
        return out

    def observe(self, controls):
        self.agent.observe(controls)
