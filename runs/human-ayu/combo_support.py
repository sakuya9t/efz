"""Built-in combo support for an agent (the user's, after Hisoutensoku's scripted AIs, whose
combos are written in rather than learnt): ways to play an agent whose combos come from
elsewhere, as evaluate.py's players (--p1-combo, --p1-lookahead).

    agent = ComboSwitch(Agent('agent.zip'), Agent('combo/combo.zip'))   # the combo master's
    agent = lookahead(data_dir, 'agent.zip', 'combo-library.npz')       # the best route, tried

ComboSwitch: while the agent's combo runs (its combo counter, as the agent sees the game:
`delay` steps late, a person's hit-confirm; confirm='now' for none), the combo player's
controls are played, else the agent's own. Both see every step and every input, so either
can take over at once. The combo master (combo.py) was trained as the agent was (the
reaction time, a pull toward people's play) on trials from people's combo starts.

lookahead: at each first hit (as the game is: an upper bound) people's library combos
with that starter and the agent's own play are tried on copies of the game and the most
damaging is played (redteam.py's planner, the red team's): "a player who knows the routes
and lands them", the defender guarding once it can.

FairAssist, "strong but fair" (the user's choice): the same, but only once the player sees
its hit (its combo counter, `delay` steps late: no instant hit-confirm). From the game as
it is then, people's library combos with the move that hit are tried from their step
`delay` (the player's own inputs made the steps before), and its own play seeing the
copies as late as it sees the game; the most damaging is played until it ends or drops.
FairComboAgent plays an Agent so (evaluate.py --p1-assist), ComboAssist the learner of
finetune.py --assist, marking the steps a route played (infos[i]['assisted']) for the
policy's loss to leave out, FairAssistOpponent a frozen agent as an exploiter's opponent
(finetune.py --vs-assist: an agent trained so is met as it plays).
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

import numpy as np
from stable_baselines3.common.vec_env.base_vec_env import VecEnv

COMBO_HITS, ACTION = 30, 18  # self_combo_hits (/ 30), self_action


class ComboSwitch:
    def __init__(self, base, combo, confirm='seen'):
        if confirm not in ('seen', 'now'):
            raise ValueError("confirm: 'seen' or 'now'")
        self.base, self.combo, self.confirm = base, combo, confirm
        self.frame_skip, self.history = 1, base.history
        self.steps = self.switched = 0

    def batch(self, n):
        self.base.batch(n)
        self.combo.batch(n)

    def reset(self, mask=None):
        self.base.reset(mask)
        self.combo.reset(mask)

    def controls(self, obs, step):
        own = self.base.controls(obs, step)
        alt = self.combo.controls(obs, step)
        if self.confirm == 'seen' and self.base.delay:
            view = self.base.seen.buf[:, self.base.delay]  # what the agent sees now
        else:
            view = obs
        use = np.round(view[:, COMBO_HITS] * 30) > 0
        self.steps += len(use)
        self.switched += int(use.sum())
        return np.where(use, alt, own)

    def observe(self, controls):
        self.base.observe(controls)
        self.combo.observe(controls)


def lookahead(data_dir, path, library, per_start=12):
    from stable_baselines3 import PPO
    import macros
    import redteam
    planner = redteam.Planner(data_dir, macros.load_library(library, 300),
                              PPO.load(path, device='cpu'), per_start=per_start)
    return redteam.RedTeamAgent(planner, path)


def _hits(view):
    return int(round(float(view[COMBO_HITS]) * 30))


class FairAssist:
    """The routes being played and the plans made, per environment."""

    def __init__(self, planner, delay):
        if delay <= 0:
            raise ValueError('FairAssist plans when the player sees its hit: delay > 0')
        self.planner, self.delay = planner, delay
        self.playing = {}    # env -> [actions, step]
        self.prev_seen = {}  # env -> combo hits it saw last step
        self.plans = []      # (the most an option made, its own play's, a route chosen)

    def clear(self, i=None):
        if i is None:
            self.playing.clear()
            self.prev_seen.clear()
        else:
            self.playing.pop(i, None)
            self.prev_seen.pop(i, None)

    def update(self, i, seen_view, now_view, save, seen, hist, prev, side, policy, value=None):
        """Before environment i's next decision: plans if the player now sees its hit and
        the combo goes on. seen_view: what it sees; now_view: the game as it is; policy,
        value: its own play's and its critic's (the planner's score='value')."""
        hits = _hits(seen_view)
        if (hits > 0 and self.prev_seen.get(i, 0) == 0 and _hits(now_view) > 0
                and self.playing.get(i) is None):
            starter = int(round(float(seen_view[ACTION])))  # the move that hit
            chosen, best, own = self.planner.plan(save(), side, starter, hist, prev,
                                                  offset=self.delay, seen=seen, policy=policy,
                                                  value=value)
            self.plans.append((best, own, chosen is not None))
            self.playing[i] = [chosen, 0] if chosen is not None else None
        self.prev_seen[i] = hits

    def action(self, i, now_hits):
        """The route's action for environment i now, or None (its own play)."""
        m = self.playing.get(i)
        if m is None:
            return None
        if (now_hits == 0 and m[1] > 0) or m[1] >= len(m[0]):  # it ended, or dropped
            self.playing[i] = None
            return None
        a = int(m[0][m[1]])
        m[1] += 1
        return a

    def take_plans(self):
        """The plans since the last call: their count, the share that chose a route, and
        the damage the best option and its own play made on average."""
        p, self.plans = self.plans, []
        if not p:
            return dict(plans=0)
        return dict(plans=len(p), route=round(float(np.mean([x[2] for x in p])), 3),
                    best=round(float(np.mean([x[0] for x in p]))),
                    own=round(float(np.mean([x[1] for x in p]))))


class FairComboAgent:
    """An efz_env Agent with FairAssist, for evaluate.py (attach(env, side) first)."""

    def __init__(self, agent, planner):
        from efz_env import ActionTable
        self.agent = agent
        self.assist = FairAssist(planner, agent.delay)
        self.value = None
        if getattr(planner, 'score', 'damage') == 'value':  # the agent's critic, not the planner's
            import redteam
            self.value = redteam.critic(agent.model)
        self.frame_skip, self.history = 1, agent.history
        self.table = ActionTable()
        self.env, self.side = None, 0

    @property
    def plans(self):
        return self.assist.plans

    def policy(self, view):
        return self.agent.model.predict(view, deterministic=self.agent.deterministic)[0]

    def attach(self, env, side):
        self.env, self.side = env, side

    def batch(self, n):
        self.agent.batch(n)
        self.assist.clear()

    def reset(self, mask=None):
        self.agent.reset(mask)
        if mask is None:
            self.assist.clear()
        else:
            for i in np.flatnonzero(mask):
                self.assist.clear(int(i))

    def controls(self, obs, step):
        out = self.agent.controls(obs, step).copy()  # (it pushes obs into its view)
        seen = self.agent.seen.buf                  # (n, delay + 1, dim), newest first
        hist = self.agent.hist
        for i in range(len(obs)):
            self.assist.update(i, seen[i, self.agent.delay], obs[i],
                               lambda i=i: self.env.save_state(i), seen[i].copy(),
                               hist.buf[i].copy(), int(hist.prev[i]), self.side, self.policy,
                               self.value)
            a = self.assist.action(i, _hits(obs[i]))
            if a is not None:
                out[i] = self.table.table[a]
        return out

    def observe(self, controls):
        self.agent.observe(controls)


class FairAssistOpponent:
    """EfzSB3VecEnv's opponent (player 2, seeing the game `delay` steps late) with
    FairAssist: an agent trained with finetune.py --assist, played as it was trained, by
    an exploiter's training (finetune.py --vs-assist). attach(venv) first."""
    takes_index = True

    def __init__(self, planner, model):
        from efz_env.sb3 import frozen
        self.inner = frozen(model)
        self.planner = planner
        self.venv = self.assist = None

    @property
    def plans(self):
        return self.assist.plans if self.assist is not None else []

    def attach(self, venv):
        if venv.delay is None or venv.opponent_delay is not None and (
                venv.opponent_delay != venv.delay.steps).any():
            raise ValueError('FairAssistOpponent: player 2 sees the game delay steps late')
        self.venv = venv
        self.assist = FairAssist(self.planner, venv.delay.steps)

    def __call__(self, obs, idx):
        actions = np.asarray(self.inner(obs)).copy()
        v, d = self.venv, self.assist.delay
        for k, i in enumerate(idx):
            i = int(i)
            if v._length[i] == 0:  # a new match
                self.assist.clear(i)
            seen, now = v.delay.buf[i, 1], v.env.obs[i, 1]
            self.assist.update(i, seen[d], now, lambda i=i: v.env.save_state(i), seen.copy(),
                               v.history.buf[i, 1].copy(), int(v.history.prev[i, 1]), 1,
                               self.inner)
            a = self.assist.action(i, _hits(now))
            if a is not None:
                actions[k] = a
        return actions


class ComboAssist(VecEnv):
    """finetune.py's learner (player 1 of an EfzSB3VecEnv) with FairAssist, as a VecEnv:
    the steps a route plays carry infos[i]['assisted']. policy: its own play on the
    copies (frozen(model), this chunk's); value: its critic's (redteam.critic(model), for
    the planner's score='value')."""

    def __init__(self, venv, planner, policy, value=None):
        self.venv, self.policy, self.value = venv, policy, value
        self.delay = venv.delay.steps
        self.assist = FairAssist(planner, self.delay)
        self.assisted = np.zeros(venv.num_envs, bool)
        super().__init__(venv.num_envs, venv.observation_space, venv.action_space)

    def reset(self):
        self.assist.clear()
        return self.venv.reset()

    def step_async(self, actions):
        actions = np.array(actions).copy()
        now = self.venv.env.obs[:, 0]
        self.assisted[:] = False
        for i in range(self.num_envs):
            a = self.assist.action(i, _hits(now[i]))
            if a is not None:
                actions[i] = a
                self.assisted[i] = True
        self.venv.step_async(actions)

    def step_wait(self):
        obs, rewards, dones, infos = self.venv.step_wait()
        for i in range(self.num_envs):
            infos[i]['assisted'] = bool(self.assisted[i])
        seen = self.venv.delay.buf[:, 0]  # the learner's views, newest first
        now = self.venv.env.obs[:, 0]
        hist = self.venv.history
        for i in range(self.num_envs):
            if dones[i]:
                self.assist.clear(i)
                continue
            self.assist.update(i, seen[i, self.delay], now[i],
                               lambda i=i: self.venv.env.save_state(i), seen[i].copy(),
                               hist.buf[i, 0].copy(), int(hist.prev[i, 0]), 0, self.policy,
                               self.value)
        return obs, rewards, dones, infos

    def close(self):
        self.venv.close()

    def get_attr(self, attr_name, indices=None):
        return [getattr(self, attr_name)] * len(self._get_indices(indices))

    def set_attr(self, attr_name, value, indices=None):
        setattr(self, attr_name, value)

    def env_method(self, method_name, *args, indices=None, **kwargs):
        result = getattr(self, method_name)(*args, **kwargs)
        return [result] * len(self._get_indices(indices))

    def env_is_wrapped(self, wrapper_class, indices=None):
        return [False] * len(self._get_indices(indices))
