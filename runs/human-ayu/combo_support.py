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

The routes are a module of the agent (python/efz_env/modules.py: what a module is, and the
hosts that play an agent with its modules): FairAssist is the module where the game can
be copied at once (evaluations, training; with combo_net.py's chooser anywhere), LiveRoutes
the same module for a person's match, its planner beside the game. The classes named above
are those hosts with the routes alone, kept by their names; an agent with more modules is
efz_env.modules.ModularAgent([routes, ...]) (the kind 'routes' of an agent.json: routes()
below).
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

import numpy as np

from efz_env import modules
from efz_env.modules import Module, ModularAgent, ModularOpponent, sampler
from efz_env.sb3 import ModularLearner

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


class FairAssist(Module):
    """The routes being played and the plans made, per environment: the module 'routes'
    (watch: update, act: action)."""
    name = 'routes'

    def __init__(self, planner, delay):
        if delay <= 0:
            raise ValueError('FairAssist plans when the player sees its hit: delay > 0')
        self.planner, self.delay = planner, delay
        # (a planner with replan: a plan again at each new move's hit it sees)
        self.replan = bool(getattr(planner, 'replan', False))
        self.playing = {}    # env -> [actions, step]
        self.prev_seen = {}  # env -> combo hits it saw last step
        self.planned = {}    # env -> the move whose hit it planned on last
        self.plans = []      # (the most an option made, its own play's, a route chosen)

    def clear(self, i=None):
        if i is None:
            self.playing.clear()
            self.prev_seen.clear()
            self.planned.clear()
        else:
            self.playing.pop(i, None)
            self.prev_seen.pop(i, None)
            self.planned.pop(i, None)

    def reset(self, mask=None):
        if mask is None:
            self.clear()
        else:
            for i in np.flatnonzero(mask):
                self.clear(int(i))

    def watch(self, i, ctx):
        self.update(i, ctx.view, ctx.now, ctx.save, ctx.seen, ctx.hist, ctx.prev, ctx.side,
                    ctx.policy, ctx.value)

    def act(self, i, ctx):
        return self.action(i, _hits(ctx.now))

    def stats(self):
        """The plans so far (take_plans: since the last call, and forgets them)."""
        p, out = self.plans, self.take_plans()
        self.plans = p
        return out

    def update(self, i, seen_view, now_view, save, seen, hist, prev, side, policy, value=None):
        """Before environment i's next decision: plans if the player now sees its hit and
        the combo goes on. seen_view: what it sees; now_view: the game as it is; policy,
        value: its own play's and its critic's (the planner's score='value')."""
        hits = _hits(seen_view)
        before = self.prev_seen.get(i, 0)
        starter = int(round(float(seen_view[ACTION])))  # the move that hit
        route = self.playing.get(i)
        first = hits > 0 and before == 0 and route is None
        again = self.replan and hits > before > 0 and starter != self.planned.get(i)
        if hits == 0:
            self.planned.pop(i, None)
        if ((first or again) and _hits(now_view) > 0
                and self.planner.plans_against(seen_view)):
            more = {}
            if again and route is not None:  # the route it is on: one of the options
                more = dict(extra=route[0][route[1]:])
            chosen, best, own = self.planner.plan(save(), side, starter, hist, prev,
                                                  offset=self.delay, seen=seen, policy=policy,
                                                  value=value, **more)
            self.plans.append((best, own, chosen is not None))
            self.playing[i] = [chosen, 0] if chosen is not None else None
            self.planned[i] = starter
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


class FairComboAgent(ModularAgent):
    """An efz_env Agent with FairAssist alone, for evaluate.py (attach(env, side) first)."""

    def __init__(self, agent, planner):
        value = None
        if getattr(planner, 'score', 'damage') == 'value':  # the agent's critic, not the planner's
            import redteam
            value = redteam.critic(agent.model)
        super().__init__(agent, [FairAssist(planner, agent.delay)], value)

    @property
    def assist(self):
        return self.stack.get('routes')

    @property
    def plans(self):
        return self.assist.plans


def _live_worker(conn, data_dir, model_path, library, env_config, deterministic, victims,
                 per_start, replan, ending=0.0):
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
                                  per_start=per_start, victims=victims, replan=replan,
                                  ending=ending)
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
            key, side, starter, actions, hist, prev, now, late, extra = arg
            if not np.array_equal(shadow.obs[0], now):  # not the game the person plays
                conn.send(('plan', (key, 'apart', None, 0, 0, None, 0)))
                continue
            if not planner.plans_against(now[side]):
                conn.send(('plan', (key, 'own', None, 0, 0, None, 0)))
                continue
            # The steps until the player sees its hit: its inputs, chosen already (its
            # own, or the route's it is on; `late`: steps since the hit, extra: the rest
            # of that route after them, one of the options).
            sim.load_state(0, shadow.save_state(0))
            seen = [sim.obs[0, side].copy()]
            for a in actions:
                pre[0, side], pre[0, 1 - side] = table[a], BACK
                seen.insert(0, sim.step(pre)[0][0, side].copy())
            chosen, best, own = planner.plan(sim.save_state(0), side, starter, hist, prev,
                                             offset=len(actions) + late, seen=np.stack(seen),
                                             policy=policy, extra=extra)
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


class LiveRoutes(Module):
    """The fair built-in routes against a person, in real time (python/examples/play.py
    --assist): the module 'routes' of a ModularAgent that is HumanMatch's policy (its
    attach_match(match, **what set_matches got) first, its close() at the end).

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

    replan (as redteam.Planner's, FairAssist's): a plan again at each new move's hit, the
    rest of the route it is on one of the options. Until it sees that hit it plays that
    route on (its own play where the route has ended), and if the plan is dropped, on
    after that. One plan at a time: a hit that lands while a plan is awaited is planned
    on when that plan is in, the later by those steps (the combos joined that much
    further in). The game waits `patience` seconds for a combo's first plan and
    `patience_again` (half a frame) for a later one: on a machine too slow for the
    planner the combo goes on as it was and the game doesn't stall (stats(): dropped,
    'late').

    stats(): the plans (as FairAssist.take_plans), those dropped, the planner's seconds a
    plan and the seconds the game waited for one."""
    name = 'routes'

    def __init__(self, agent, data_dir, library, victims=None, per_start=12, patience=0.1,
                 replan=False, patience_again=0.008, ending=0.0):
        import multiprocessing
        if agent.frame_skip != 1 or not agent.delay or agent.hist is None:
            raise ValueError('LiveRoutes: an agent deciding every frame, with a delay and '
                             'its input history')
        self.agent, self.delay, self.patience = agent, agent.delay, patience
        self.patience_again, self.waits = patience_again, patience
        self.frame_skip, self.history = 1, agent.history
        self.sample = sampler(agent.model, agent.deterministic)
        self.table = agent.table
        self.data_dir, self.library = data_dir, library
        self.victims, self.per_start, self.replan = victims, per_start, replan
        self.ending = ending
        self.mp = multiprocessing.get_context('spawn')
        self.conn = self.worker = self.env = None
        self.side = 0
        self.key = 0
        self.plans, self.dropped, self.took, self.waited = [], {}, [], []
        self.again = 0  # plans made on a later move's hit
        self._clear()

    def _clear(self):
        self.queue, self.pending, self.route, self.prev_hits = [], None, None, 0
        self.kept = None       # the route it was on when it asked for a plan, after the wait
        self.planned = None    # the move whose hit it planned on last, this combo
        self.hit_move, self.hit_age = None, 0  # its last hit's move, the steps since

    def attach(self, host):
        """host: the ModularAgent, attached to a HumanMatch (the planner's copy of the
        match is told what the match is told from here on: host.matches first)."""
        match, matches = host.match, host.matches
        if match is None:
            raise ValueError('LiveRoutes: a person\'s match (ModularAgent.attach_match); '
                             'FairAssist elsewhere')
        env = match.env
        config = {k: int(getattr(env.config, k)) for k in
                  ('max_frames', 'rounds_to_win', 'cpu_level', 'damage_level',
                   'first_intro')}  # (the copy starts where the match does)
        self.conn, child = self.mp.Pipe()
        self.worker = self.mp.Process(
            target=_live_worker, daemon=True,
            args=(child, self.data_dir, self.agent.path, self.library, config,
                  self.agent.deterministic, self.victims, self.per_start, self.replan,
                  self.ending))
        self.worker.start()
        child.close()
        kind, error = self.conn.recv()
        if kind != 'ready':
            raise RuntimeError(f"LiveRoutes: the planner didn't start: {error}")
        self.side = match.side
        self.env = match.env = _Mirror(env, self.conn.send)
        self.env.set_matches(**matches)

    def reset(self, mask=None):
        self._clear()

    def _begin(self):
        """At its hit (or hit_age steps after: a plan was awaited): its inputs for the
        `delay` steps until it sees it, chosen now, and the plan asked for. The inputs: the
        route's it is on, then its own play's from what it will see then (the views it
        has, oldest first)."""
        import copy
        seen, hist = self.agent.seen.buf[0], copy.deepcopy(self.agent.hist)
        rest = self.route[0][self.route[1]:] if self.route is not None else ()
        actions = []
        for k in range(self.delay):
            if k < len(rest):
                a = int(rest[k])
            else:
                view = np.concatenate([seen[self.delay - k], hist.features()[0]])
                a = int(self.sample(view[None, :self.agent.width])[0])
            actions.append(a)
            hist.push(self.table.to_bytes(np.array([a])))
        self.key += 1
        self.again += self.planned is not None
        self.waits = self.patience if self.planned is None else self.patience_again
        self.kept = [rest, self.delay] if len(rest) > self.delay else None
        self.conn.send(('plan', (self.key, self.side, self.hit_move, actions,
                                 hist.buf[0].copy(), int(hist.prev[0]), self.env.obs[0].copy(),
                                 self.hit_age, None if self.kept is None else
                                 np.asarray(rest[self.delay:]))))
        self.queue, self.pending, self.route = actions, self.key, None
        self.planned = self.hit_move

    def _result(self, obs):
        """`delay` steps after its hit: the plan, if the game is where it was planned from."""
        import time
        t0, got = time.perf_counter(), None
        while got is None and self.conn.poll(max(0.0, self.waits - (time.perf_counter() - t0))):
            kind, got = self.conn.recv()
            if got[0] != self.pending:  # an earlier one, dropped since
                got = None
        self.waited.append(time.perf_counter() - t0)
        self.pending = None
        kept, self.kept = self.kept, None
        if _hits(obs) > 0:  # until a plan says otherwise: on with the route it was on
            self.route = kept
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

    def watch(self, i, ctx):
        obs = ctx.now
        hits = _hits(obs)
        if hits > self.prev_hits:
            self.hit_move, self.hit_age = int(round(float(obs[ACTION]))), 0
        else:
            self.hit_age += 1
        if hits == 0:
            self.planned = None
        if self.pending is not None and not self.queue:
            self._result(obs)
        if self.route is not None and ((hits == 0 and self.route[1] > 0) or
                                       self.route[1] >= len(self.route[0])):
            self.route = None  # it ended, or dropped
        if self.pending is None and hits > 0 and (
                self.hit_move != self.planned if self.replan else
                self.prev_hits == 0 and self.route is None):
            self._begin()
        self.prev_hits = hits

    def act(self, i, ctx):
        if self.queue:
            return self.queue.pop(0)
        if self.route is not None:
            action = int(self.route[0][self.route[1]])
            self.route[1] += 1
            return action
        return None

    def stats(self):
        p = self.plans
        out = dict(plans=len(p), again=self.again, dropped=dict(self.dropped))
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


def chosen_routes(agent, planner):
    """The fair built-in routes with combo_net.py's chooser in the planner's place
    (planner: combo_net.NetPlanner; play.py --assist LIBRARY --chooser CHOOSER.pt): nothing
    is tried on copies of the game, so there is nothing to wait for and no second process:
    on the step the agent sees its hit the chooser says, from that view, which library
    combo to play from memory, or its own play. FairAssist, for any host."""
    if agent.frame_skip != 1 or not agent.delay or agent.hist is None:
        raise ValueError('the routes: an agent deciding every frame, with a delay and its '
                         'input history')
    return FairAssist(planner, agent.delay)


class FairAssistOpponent(ModularOpponent):
    """EfzSB3VecEnv's opponent (player 2, seeing the game `delay` steps late) with
    FairAssist alone: an agent trained with finetune.py --assist, played as it was trained,
    by an exploiter's training (finetune.py --vs-assist). attach(venv) first."""

    def __init__(self, planner, model):
        super().__init__(model, lambda venv: [FairAssist(planner, venv.delay.steps)])
        self.planner = planner

    @property
    def assist(self):
        return self.stack.get('routes') if self.stack is not None else None

    @property
    def plans(self):
        return self.assist.plans if self.assist is not None else []


class ComboAssist(ModularLearner):
    """finetune.py's learner (player 1 of an EfzSB3VecEnv) with FairAssist alone, as a
    VecEnv: the steps a route plays carry infos[i]['assisted'] and the route's action,
    infos[i]['route_action'] (finetune.py --assist-distill: a target); only (a mask of the
    environments, default all): where routes are planned (finetune.py --assist-where cpu:
    the CPU's matches, whose guarding the planner's defender is). policy: its own play on the
    copies (frozen(model), this chunk's); value: its critic's (redteam.critic(model), for
    the planner's score='value')."""

    def __init__(self, venv, planner, policy, value=None, only=None):
        super().__init__(venv, [FairAssist(planner, venv.delay.steps)], policy, value, only)

    @property
    def assist(self):
        return self.stack.get('routes')


@modules.register('routes')
def routes(agent, where, files, options, data):
    """The kind 'routes' of an agent.json. files: library (a combo library .npz, its
    .marks.json beside it), chooser (combo_net.py's chooser.pt, optional). options: replan
    (default true), per_start (24), victims, by ('planner', the default: the combos tried
    on copies; 'chooser': the chooser picks, nothing is tried), margin (the chooser's,
    200), score, ending (the HP a knockdown at a combo's end is worth over any other end,
    default 0: redteam.Planner's);
    a person's match: patience, patience_again (LiveRoutes's: the seconds the game waits
    for a plan)."""
    library, o = files['library'], dict(options)
    if o.get('by', 'planner') not in ('planner', 'chooser'):
        raise ValueError(f"routes: by 'planner' or 'chooser', not {o['by']!r}")
    if o.get('by') == 'chooser':
        import combo_net
        if not files.get('chooser'):
            raise ValueError("routes: by the chooser, and no chooser.pt among its files")
        return chosen_routes(agent, combo_net.NetPlanner(
            combo_net.load_routes(library), agent.model, files['chooser'],
            margin=o.get('margin', 200.0)))
    per_start, replan = int(o.get('per_start', 24)), bool(o.get('replan', True))
    if where == 'play':
        waits = {k: float(o[k]) for k in ('patience', 'patience_again') if k in o}
        return LiveRoutes(agent, data, library, victims=o.get('victims'), per_start=per_start,
                          replan=replan, ending=float(o.get('ending', 0.0)), **waits)
    import macros
    import redteam
    return FairAssist(redteam.Planner(data, macros.load_library(library), agent.model,
                                      score=o.get('score', 'damage'), victims=o.get('victims'),
                                      per_start=per_start, replan=replan,
                                      ending=float(o.get('ending', 0.0))), agent.delay)
