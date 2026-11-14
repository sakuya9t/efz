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
FairComboAgent plays an Agent so (evaluate.py --p1-assist), LiveRoutes against a person in
real time (python/examples/play.py --assist), ChosenRoutes the same with combo_net.py's
chooser in the planner's place (play.py --assist --chooser), ComboAssist the learner of
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
    planner = redteam.Planner(data_dir, macros.load_library(library),
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
                and self.playing.get(i) is None
                and self.planner.plans_against(seen_view)):
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


def sampler(model, deterministic=False):
    """views (batch, width) -> `model`'s actions, as predict's but without its overhead."""
    import torch
    policy = model.policy
    policy.set_training_mode(False)

    def act(view):
        with torch.no_grad():
            t = torch.as_tensor(np.asarray(view, np.float32), device=policy.device)
            return policy._predict(t, deterministic=deterministic).cpu().numpy()
    return act


def _live_worker(conn, data_dir, model_path, library, env_config, deterministic, victims,
                 per_start):
    """LiveRoutes's planner, a process of its own: a copy of the match (not drawn), played
    the same inputs frame by frame, and redteam's planner on copies of that."""
    import time
    import torch
    from stable_baselines3 import PPO
    from efz_env import ActionTable, EfzVecEnv
    from efz_env.actions import BACK
    import macros
    import redteam
    torch.set_num_threads(1)
    try:
        model = PPO.load(model_path, device='cpu')
        planner = redteam.Planner(data_dir, macros.load_library(library), model,
                                  per_start=per_start, victims=victims)
        shadow = EfzVecEnv(data_dir, 1, frame_skip=1, skip_noninteractive=False,
                           autoreset='disabled', **env_config)
        policy, table, sim = sampler(model, deterministic), ActionTable().table, planner.sim
        conn.send(('ready', None))
    except Exception as e:  # (the game's folder, the library, the model)
        conn.send(('error', repr(e)))
        return
    controls = np.zeros((1, 2), np.uint8)
    pre = np.zeros((sim.num_envs, 2), np.uint8)
    while True:
        try:
            kind, arg = conn.recv()
        except EOFError:
            return
        if kind == 'step':
            controls[0] = np.frombuffer(arg, np.uint8)
            shadow.step(controls)
        elif kind == 'reset':
            shadow.reset(seed=arg)
        elif kind == 'matches':
            shadow.set_matches(**arg)
        elif kind == 'close':
            return
        elif kind == 'plan':
            t0 = time.perf_counter()
            key, side, starter, actions, hist, prev, now = arg
            if not np.array_equal(shadow.obs[0], now):  # not the game the person plays
                conn.send(('plan', (key, 'apart', None, 0, 0, None, 0)))
                continue
            if not planner.plans_against(now[side]):
                conn.send(('plan', (key, 'own', None, 0, 0, None, 0)))
                continue
            # The steps until the player sees its hit: its own inputs, chosen already.
            sim.load_state(0, shadow.save_state(0))
            seen = [sim.obs[0, side].copy()]
            for a in actions:
                pre[0, side], pre[0, 1 - side] = table[a], BACK
                seen.insert(0, sim.step(pre)[0][0, side].copy())
            chosen, best, own = planner.plan(sim.save_state(0), side, starter, hist, prev,
                                             offset=len(actions), seen=np.stack(seen),
                                             policy=policy)
            conn.send(('plan', (key, 'planned', chosen, best, own, seen[0],
                                time.perf_counter() - t0)))


class _Mirror:
    """HumanMatch's environment, telling LiveRoutes's planner every match and step."""

    def __init__(self, env, send):
        self.__dict__.update(_env=env, _send=send)

    def __getattr__(self, name):
        return getattr(self._env, name)

    def set_matches(self, **kwargs):
        self._env.set_matches(**kwargs)
        self._send(('matches', kwargs))

    def reset(self, mask=None, seed=None):
        if seed is None:  # a seed of its own, for the copy to start the same match
            seed = int.from_bytes(os.urandom(6), 'little')
        obs = self._env.reset(mask, seed=seed)
        self._send(('reset', seed))
        return obs

    def step(self, controls):
        self._send(('step', bytes(np.asarray(controls, np.uint8)[0])))
        return self._env.step(controls)


class LiveRoutes:
    """An efz_env Agent with the fair built-in routes against a person, in real time
    (python/examples/play.py --assist): HumanMatch's policy (obs -> an action, once a
    frame). attach(match, **what set_matches got) first; close() at the end.

    As FairAssist: the routes are tried from the game as it is when the player sees its
    hit, `delay` steps after it, and played from then. A plan takes 50-400 ms, which a
    match at the game's speed hasn't got, so it is made while those `delay` steps pass:
    what the player will see in them it has seen already (the game up to the hit), so its
    inputs for them are chosen at the hit, as its policy would choose them one by one,
    and a planner in a process of its own plays them on a copy of the match (kept in step
    by the same inputs every frame, not drawn: copies of a drawn game are ten times as
    slow), the opponent guarding once it can, then plans from there. If the game is not
    there after `delay` steps (the opponent did something else and it mattered), the plan
    is dropped and the player plays on by itself.

    stats(): the plans (as FairAssist.take_plans), those dropped, the planner's seconds a
    plan and the seconds the game waited for one."""

    def __init__(self, agent, data_dir, library, victims=None, per_start=12, patience=1.0):
        import multiprocessing
        if agent.frame_skip != 1 or not agent.delay or agent.hist is None:
            raise ValueError('LiveRoutes: an agent deciding every frame, with a delay and '
                             'its input history')
        self.agent, self.delay, self.patience = agent, agent.delay, patience
        self.frame_skip, self.history = 1, agent.history
        self.sample = sampler(agent.model, agent.deterministic)
        self.table = agent.table
        self.data_dir, self.library = data_dir, library
        self.victims, self.per_start = victims, per_start
        self.mp = multiprocessing.get_context('spawn')
        self.conn = self.worker = self.env = None
        self.side = 0
        self.key = 0
        self.plans, self.dropped, self.took, self.waited = [], {}, [], []
        self._clear()

    def _clear(self):
        self.queue, self.pending, self.route, self.prev_hits = [], None, None, 0

    def attach(self, match, **matches):
        """match: the HumanMatch; matches: set_matches's arguments, as it was given them."""
        env = match.env
        config = {k: int(getattr(env.config, k)) for k in
                  ('max_frames', 'rounds_to_win', 'cpu_level', 'damage_level')}
        self.conn, child = self.mp.Pipe()
        self.worker = self.mp.Process(
            target=_live_worker, daemon=True,
            args=(child, self.data_dir, self.agent.path, self.library, config,
                  self.agent.deterministic, self.victims, self.per_start))
        self.worker.start()
        child.close()
        kind, error = self.conn.recv()
        if kind != 'ready':
            raise RuntimeError(f"LiveRoutes: the planner didn't start: {error}")
        self.side = match.side
        self.env = match.env = _Mirror(env, self.conn.send)
        self.env.set_matches(**matches)

    def reset(self):
        self.agent.reset()
        self._clear()

    def _begin(self, obs):
        """At its hit: its inputs for the `delay` steps until it sees it, chosen now from
        what it will see then (the views it has, oldest first), and the plan asked for."""
        import copy
        seen, hist = self.agent.seen.buf[0], copy.deepcopy(self.agent.hist)
        actions = []
        for k in range(self.delay):
            view = np.concatenate([seen[self.delay - k], hist.features()[0]])
            a = int(self.sample(view[None, :self.agent.width])[0])
            actions.append(a)
            hist.push(self.table.to_bytes(np.array([a])))
        self.key += 1
        self.conn.send(('plan', (self.key, self.side, int(round(float(obs[ACTION]))), actions,
                                 hist.buf[0].copy(), int(hist.prev[0]), self.env.obs[0].copy())))
        self.queue, self.pending = actions, self.key

    def _result(self, obs):
        """`delay` steps after its hit: the plan, if the game is where it was planned from."""
        import time
        t0, got = time.perf_counter(), None
        while got is None and self.conn.poll(max(0.0, self.patience - (time.perf_counter() - t0))):
            kind, got = self.conn.recv()
            if got[0] != self.pending:  # an earlier one, dropped since
                got = None
        self.waited.append(time.perf_counter() - t0)
        self.pending = None
        if got is None:
            return self._drop('late')
        _, state, chosen, best, own, expected, took = got
        if state != 'planned':
            return self._drop(state)
        self.took.append(took)
        if _hits(obs) == 0:
            return self._drop('combo over')
        if not np.array_equal(expected, obs):
            return self._drop('game elsewhere')
        self.plans.append((best, own, chosen is not None))
        self.route = [chosen, 0] if chosen is not None else None

    def _drop(self, why):
        self.dropped[why] = self.dropped.get(why, 0) + 1

    def __call__(self, obs):
        obs = np.asarray(obs, np.float32)
        view = self.agent.view(obs[None])  # (its view of this step, `delay` steps old)
        hits = _hits(obs)
        if self.pending is not None and not self.queue:
            self._result(obs)
        if self.queue:
            action = self.queue.pop(0)
        elif self.route is not None and not (hits == 0 and self.route[1] > 0) \
                and self.route[1] < len(self.route[0]):
            action = int(self.route[0][self.route[1]])
            self.route[1] += 1
        else:
            self.route = None
            if hits > 0 and self.prev_hits == 0 and self.pending is None:
                self._begin(obs)
                action = self.queue.pop(0)
            else:
                action = int(self.sample(view)[0])
        self.prev_hits = hits
        self.agent.observe(self.table.to_bytes(np.array([action])))
        return action

    def stats(self):
        p = self.plans
        out = dict(plans=len(p), dropped=dict(self.dropped))
        if p:
            out.update(route=round(float(np.mean([x[2] for x in p])), 3),
                       best=round(float(np.mean([x[0] for x in p]))),
                       own=round(float(np.mean([x[1] for x in p]))))
        for name, x in (('plan_ms', self.took), ('wait_ms', self.waited)):
            if x:
                x = np.asarray(x) * 1000
                out[name] = dict(median=round(float(np.median(x)), 1),
                                 p90=round(float(np.percentile(x, 90)), 1),
                                 most=round(float(x.max()), 1))
        return out

    def close(self):
        if self.conn is not None:
            try:
                self.conn.send(('close', None))
            except OSError:
                pass
            self.worker.join(2)
            if self.worker.is_alive():
                self.worker.terminate()
            self.conn = None


class ChosenRoutes:
    """The fair built-in routes against a person with combo_net.py's chooser in the
    planner's place (python/examples/play.py --assist LIBRARY --chooser CHOOSER.pt):
    HumanMatch's policy. Nothing is tried on copies of the game, so there is nothing to
    wait for and no second process: on the step the agent sees its hit the chooser says,
    from that view, which library combo to play from memory, or its own play
    (FairAssist, with combo_net.NetPlanner). stats(): the plans, as FairAssist's."""

    def __init__(self, agent, planner):
        if agent.frame_skip != 1 or not agent.delay or agent.hist is None:
            raise ValueError('ChosenRoutes: an agent deciding every frame, with a delay and '
                             'its input history')
        self.agent = agent
        self.assist = FairAssist(planner, agent.delay)
        self.frame_skip, self.history = 1, agent.history
        self.sample = sampler(agent.model, agent.deterministic)
        self.table = agent.table
        self.plans = []

    def attach(self, match, **matches):
        pass

    def reset(self):
        self.agent.reset()
        self.assist.clear()

    def __call__(self, obs):
        obs = np.asarray(obs, np.float32)
        a = self.agent
        view = a.view(obs[None])  # (its view of this step, `delay` steps old)
        self.assist.update(0, a.seen.buf[0, a.delay], obs, lambda: None, a.seen.buf[0].copy(),
                           a.hist.buf[0].copy(), int(a.hist.prev[0]), 0, None)
        action = self.assist.action(0, _hits(obs))
        if action is None:
            action = int(self.sample(view)[0])
        a.observe(self.table.to_bytes(np.array([action])))
        return action

    def stats(self):
        self.plans += self.assist.plans
        self.assist.plans = []
        p = self.plans
        out = dict(plans=len(p))
        if p:
            out.update(route=round(float(np.mean([x[2] for x in p])), 3),
                       best=round(float(np.mean([x[0] for x in p]))),
                       own=round(float(np.mean([x[1] for x in p]))))
        return out

    def close(self):
        pass


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
    the steps a route plays carry infos[i]['assisted'] and the route's action,
    infos[i]['route_action'] (finetune.py --assist-distill: a target); only (a mask of the
    environments, default all): where routes are planned (finetune.py --assist-where cpu:
    the CPU's matches, whose guarding the planner's defender is). policy: its own play on the
    copies (frozen(model), this chunk's); value: its critic's (redteam.critic(model), for
    the planner's score='value')."""

    def __init__(self, venv, planner, policy, value=None, only=None):
        self.venv, self.policy, self.value = venv, policy, value
        self.only = np.ones(venv.num_envs, bool) if only is None else np.asarray(only, bool)
        self.delay = venv.delay.steps
        self.assist = FairAssist(planner, self.delay)
        self.assisted = np.zeros(venv.num_envs, bool)
        self.route = np.zeros(venv.num_envs, int)
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
                self.route[i] = a
        self.venv.step_async(actions)

    def step_wait(self):
        obs, rewards, dones, infos = self.venv.step_wait()
        for i in range(self.num_envs):
            infos[i]['assisted'] = bool(self.assisted[i])
            if self.assisted[i]:
                infos[i]['route_action'] = int(self.route[i])
        seen = self.venv.delay.buf[:, 0]  # the learner's views, newest first
        now = self.venv.env.obs[:, 0]
        hist = self.venv.history
        for i in range(self.num_envs):
            if dones[i] or not self.only[i]:
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
