"""Modules: parts of an agent that take its inputs over in some situation, the agent's own
network left as it is (runs/human-ayu/combo_support.py's built-in routes, the first: its
combos from people's library once it sees its hit). One way to write a module, and one host
for each place an agent plays, so a module written once plays in all of them and several
play together:

    class Module          what a module is (below)
    Stack                 several, in order: the first that wants the step has it
    Switch                a module that is another player's play in some situation
    ModularAgent          an efz_env Agent with modules: evaluations (controls(obs, step)
                          over a batch) and a person's matches (HumanMatch's policy)
    ModularOpponent       a frozen model with modules, an EfzSB3VecEnv's opponent
    efz_env.sb3.ModularLearner   the learner of an EfzSB3VecEnv with modules (a VecEnv)

    agent = ModularAgent(Agent('avg.zip', n=64), [routes, okizeme])
    agent.attach(env, side=0)          # or attach_match(human_match, **its set_matches)

A module, every step and for each environment i, is shown the step (watch(i, ctx)) and
asked for its action (act(i, ctx)): an action index, or None, "not mine", and the next
module is asked, the agent's own play the last. ctx (Context) is what the host knows of
the step: ctx.view, what the player sees (`delay` steps old: the human limits, which a
module keeps by deciding from it), its input history, and for planning on copies of the
game ctx.save() and ctx.now, the game as it is. A module that was playing and finds
ctx.last another's name was interrupted by a module before it.

What an agent is made of is written beside its model, agent.json (load_manifest):

    {"format": 1, "model": "agent-league15-s1/avg.zip",
     "modules": [{"kind": "routes", "code": "combo_support",
                  "files": {"library": "combo-library-victims.npz"},
                  "options": {"replan": true, "per_start": 24}}]}

`code` is the Python module that registers the kind (register(kind, factory)), found on
sys.path; build() makes the modules for a host: factory(agent, where, files, options,
data) -> Module, where 'play' (a person's match, in real time) or 'batch' (evaluations),
files' paths absolute, data the game's folder. The order of "modules" is the order they
are asked in.
"""

import importlib
import json
import os

import numpy as np

MANIFEST = 'agent.json'
FORMAT = 1


class Context:
    """A step of environment i, as its host tells a module:

    view    what the player sees: its side's observation `delay` steps ago
    seen    its last delay + 1 views, newest first (seen[delay] is view)
    hist, prev   its input history's buffer and last controls (None, 0: it has none)
    now     its side's observation as the game is (for the copies; not for deciding)
    save    () -> the game's saved state (None where the host has no copies)
    side    0 or 1
    policy  views (batch, width) -> its own play's actions, for the copies; value: its critic
    last    the name of the module that played its last step (None: its own play)

    The arrays are the host's to change after the call: copy what is kept."""
    __slots__ = ('view', 'seen', 'hist', 'prev', 'now', 'save', 'side', 'policy', 'value',
                 'last')

    def __init__(self, view, now, seen=None, hist=None, prev=0, save=None, side=0,
                 policy=None, value=None, last=None):
        self.view, self.now, self.seen, self.hist, self.prev = view, now, seen, hist, prev
        self.save, self.side, self.policy, self.value, self.last = save, side, policy, value, last


class Module:
    """A part of an agent. Every method has a default that does nothing."""
    name = 'module'

    def attach(self, host):
        """Once, before it plays: host.agent, host.env, host.side; a person's match:
        host.match and host.matches (what its set_matches was given)."""

    def batch(self, n):
        """It plays n environments from now on (a new match in each)."""
        self.reset()

    def reset(self, mask=None):
        """A new match (in the environments of mask; None: all)."""

    def see(self, obs, step):
        """Every step, before any watch: the batch's observations (n, dim) as the game is
        (a module with a player of its own shows it the step here)."""

    def watch(self, i, ctx):
        """Every step, before environment i's decision."""

    def act(self, i, ctx):
        """Its action index for environment i now, or None: not its step."""
        return None

    def observe(self, controls):
        """The controls the player played on the step (n,), whoever chose them."""

    def stats(self):
        """What it did so far, for a report."""
        return {}

    def close(self):
        pass


class Stack:
    """Modules in the order they are asked. owner: environment -> the name of the module
    that played its last step; steps, played: decisions made, and those each module made."""

    def __init__(self, modules):
        self.modules = list(modules)
        names = [m.name for m in self.modules]
        if len(set(names)) != len(names):
            raise ValueError(f'modules: one of each name ({names})')
        self.owner = {}
        self.steps = 0
        self.played = {name: 0 for name in names}

    def __iter__(self):
        return iter(self.modules)

    def __len__(self):
        return len(self.modules)

    def get(self, name):
        for m in self.modules:
            if m.name == name:
                return m
        return None

    def reset(self, mask=None):
        if mask is None:
            self.owner.clear()
        else:
            for i in np.flatnonzero(mask):
                self.owner.pop(int(i), None)
        for m in self.modules:
            m.reset(mask)

    def reset_one(self, i, n):
        """A new match in environment i of n."""
        mask = np.zeros(n, bool)
        mask[i] = True
        self.reset(mask)

    def watch(self, i, ctx):
        ctx.last = self.owner.get(i)
        for m in self.modules:
            m.watch(i, ctx)

    def act(self, i, ctx):
        self.steps += 1
        for m in self.modules:
            a = m.act(i, ctx)
            if a is not None:
                self.owner[i] = m.name
                self.played[m.name] += 1
                return a
        self.owner.pop(i, None)
        return None

    def decide(self, i, ctx):
        self.watch(i, ctx)
        return self.act(i, ctx)

    def stats(self):
        """Each module's stats() under its name, and `played`: the share of the decisions
        each made."""
        out = {m.name: m.stats() for m in self.modules}
        out['played'] = {k: round(v / max(1, self.steps), 4) for k, v in self.played.items()}
        return out


class Switch(Module):
    """Another player's play in some situation: `agent` (an efz_env Agent of its own, seeing
    every step and every input as it was trained to: its delay, its input history) plays
    the steps on which gate(view) says so (view: what the host's player sees, ctx.view) and
    `after` steps more; `until(view)`, if given, ends it at once (the situation is over).
    stats(): the times it began, and the steps a time."""

    def __init__(self, name, agent, gate, after=0, until=None):
        if agent.frame_skip != 1:
            raise ValueError('Switch: an agent deciding every frame')
        self.name, self.agent, self.gate, self.after, self.until = name, agent, gate, after, until
        self.sample = sampler(agent.model, agent.deterministic)
        self.left = np.zeros(0, int)
        self.view = None
        self.began = self.steps = 0

    def batch(self, n):
        self.agent.batch(n)
        self.left = np.zeros(n, int)
        self.view = None

    def reset(self, mask=None):
        self.agent.reset(mask)
        if mask is None:
            self.left[:] = 0
        else:
            self.left[np.asarray(mask, bool)[:len(self.left)]] = 0

    def see(self, obs, step):
        if len(self.left) != len(obs):  # (a host that names no batch)
            self.batch(len(obs))
        self.view = self.agent.view(np.asarray(obs, np.float32))  # (its own view of the step)

    def watch(self, i, ctx):
        if self.until is not None and self.until(ctx.view):
            self.left[i] = 0
        elif self.gate(ctx.view):
            self.began += self.left[i] == 0
            self.left[i] = self.after + 1
        elif self.left[i] > 0:
            self.left[i] -= 1

    def act(self, i, ctx):
        if self.left[i] <= 0:
            return None
        self.steps += 1
        return int(self.sample(self.view[i:i + 1])[0])

    def observe(self, controls):
        self.agent.observe(controls)

    def stats(self):
        return dict(began=int(self.began),
                    steps=round(self.steps / max(1, int(self.began)), 1))


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


class ModularAgent:
    """An efz_env Agent with modules, played as the Agent is: over a batch, deciding every
    frame (controls(obs, step), observe(controls); evaluate.py's players, attach(env,
    side) first), or one decision a call in a person's match (HumanMatch's policy;
    attach_match(match, **what set_matches got) first, close() at the end)."""

    def __init__(self, agent, modules, value=None):
        if agent.frame_skip != 1 and modules:
            raise ValueError('modules: an agent deciding every frame')
        self.agent = agent
        self.stack = modules if isinstance(modules, Stack) else Stack(modules)
        self.value = value
        self.frame_skip, self.history, self.delay = 1, agent.history, agent.delay
        self.table = agent.table
        self.env = self.match = None
        self.side, self.matches = 0, {}
        self.sample = None  # (a person's match: made at the first decision)
        self.step = 0

    @property
    def modules(self):
        return self.stack.modules

    @property
    def model(self):
        return self.agent.model

    def policy(self, view):
        return self.agent.model.predict(view, deterministic=self.agent.deterministic)[0]

    def attach(self, env, side=0):
        self.env, self.side = env, side
        for m in self.stack:
            m.attach(self)

    def attach_match(self, match, **matches):
        """match: the HumanMatch; matches: set_matches's arguments, as it was given them
        (a module may put itself around match.env: self.env is the match's, after)."""
        self.match, self.matches = match, matches
        self.env, self.side = match.env, match.side
        for m in self.stack:
            m.attach(self)
            self.env = match.env

    def batch(self, n):
        self.agent.batch(n)
        self.stack.owner.clear()
        for m in self.stack:
            m.batch(n)

    def reset(self, mask=None):
        self.agent.reset(mask)
        self.stack.reset(mask)

    def _context(self, i, obs, save):
        a = self.agent
        if a.delay:
            seen = a.seen.buf[i]
            view, seen = seen[a.delay], seen.copy()
        else:
            view, seen = obs, obs[None]
        hist = a.hist
        return Context(view, obs, seen, None if hist is None else hist.buf[i].copy(),
                       0 if hist is None else int(hist.prev[i]), save, self.side, self.policy,
                       self.value)

    def controls(self, obs, step):
        out = self.agent.controls(obs, step).copy()  # (it pushes obs into its view)
        for m in self.stack:
            m.see(obs, step)
        table = self.table.table
        for i in range(len(obs)):
            a = self.stack.decide(i, self._context(i, obs[i], lambda i=i: self.env.save_state(i)))
            if a is not None:
                out[i] = table[a]
        return out

    def observe(self, controls):
        self.agent.observe(controls)
        for m in self.stack:
            m.observe(controls)

    def __call__(self, obs):
        obs = np.asarray(obs, np.float32)
        a = self.agent
        if self.sample is None:
            self.sample = sampler(a.model, a.deterministic)
        view = a.view(obs[None])  # (its view of this step, `delay` steps old)
        for m in self.stack:
            m.see(obs[None], self.step)
        self.step += 1
        action = self.stack.decide(0, self._context(0, obs, lambda: None))
        if action is None:
            action = int(self.sample(view)[0])
        controls = self.table.to_bytes(np.array([action]))
        a.observe(controls)
        for m in self.stack:
            m.observe(controls)
        return action

    def stats(self):
        return self.stack.stats()

    def close(self):
        for m in self.stack:
            m.close()


class ModularOpponent:
    """A frozen model with modules as an EfzSB3VecEnv's opponent (player 2, seeing the game
    `delay` steps late): attach(venv) first. modules: a list, or venv -> a list (those
    that need the environment's delay to be made)."""
    takes_index = True

    def __init__(self, model, modules):
        from .sb3 import frozen
        self.inner = frozen(model)
        self._modules = modules
        self.stack = self.venv = self.env = None
        self.side, self.agent = 1, None

    def attach(self, venv):
        if venv.delay is None or venv.opponent_delay is not None and (
                venv.opponent_delay != venv.delay.steps).any():
            raise ValueError('ModularOpponent: player 2 sees the game delay steps late')
        self.venv, self.env = venv, venv.env
        modules = self._modules(venv) if callable(self._modules) else self._modules
        self.stack = Stack(modules)
        for m in self.stack:
            m.attach(self)

    def __call__(self, obs, idx):
        actions = np.asarray(self.inner(obs)).copy()
        v, d = self.venv, self.venv.delay.steps
        hist = v.history
        for m in self.stack:  # (the controls it played last step, then this step)
            m.observe(hist.prev[:, 1])
            m.see(v.env.obs[:, 1], None)
        for k, i in enumerate(idx):
            i = int(i)
            if v._length[i] == 0:  # a new match
                self.stack.reset_one(i, v.num_envs)
            seen, now = v.delay.buf[i, 1], v.env.obs[i, 1]
            ctx = Context(seen[d], now, seen.copy(), hist.buf[i, 1].copy(),
                          int(hist.prev[i, 1]), lambda i=i: v.env.save_state(i), 1, self.inner)
            a = self.stack.decide(i, ctx)
            if a is not None:
                actions[k] = a
        return actions


# What an agent is made of: the manifest beside its model, and the kinds of module.

REGISTRY = {}


def register(kind, factory=None):
    """factory(agent, where, files, options, data) -> Module makes a module of `kind`
    (also a decorator: @register('routes'))."""
    if factory is None:
        return lambda f: register(kind, f) or f
    REGISTRY[kind] = factory


def load_manifest(path):
    """A manifest's {"model", "modules"}, the paths in it absolute. path: the agent.json,
    or a folder that holds one; None if there is none."""
    if os.path.isdir(path):
        path = os.path.join(path, MANIFEST)
    if not os.path.isfile(path):
        return None
    with open(path) as f:
        m = json.load(f)
    if m.get('format', 1) > FORMAT:
        raise ValueError(f'{path}: format {m["format"]}, this code reads up to {FORMAT}: '
                         'a newer checkout is needed')
    root = os.path.dirname(os.path.abspath(path))
    place = lambda p: os.path.normpath(os.path.join(root, *p.split('/')))
    out = dict(m, model=place(m['model']), modules=[])
    for spec in m.get('modules', []):
        out['modules'].append(dict(spec, files={k: place(v) for k, v in
                                                spec.get('files', {}).items()},
                                   options=dict(spec.get('options', {}))))
    return out


def save_manifest(path, model, modules):
    """Writes agent.json: model and the modules' files as paths from its folder."""
    root = os.path.dirname(os.path.abspath(path))
    rel = lambda p: os.path.relpath(os.path.abspath(p), root).replace(os.sep, '/')
    specs = [dict(kind=s['kind'], code=s.get('code'),
                  files={k: rel(v) for k, v in s.get('files', {}).items()},
                  options=s.get('options', {})) for s in modules]
    with open(path, 'w') as f:
        json.dump(dict(format=FORMAT, model=rel(model), modules=specs), f, indent=1)


def parse_spec(text):
    """'KIND:key=value,...' (a command line's module) -> a spec: a value that names an
    existing file goes to files, the others to options (numbers and true/false read)."""
    kind, _, rest = text.partition(':')
    spec = dict(kind=kind, code=None, files={}, options={})
    for part in filter(None, rest.split(',')):
        key, eq, value = part.partition('=')
        if not eq:
            spec['options'][key] = True
        elif os.path.exists(value):
            spec['files'][key] = os.path.abspath(value)
        else:
            try:
                spec['options'][key] = json.loads(value)
            except ValueError:
                spec['options'][key] = value
    return spec


def build(agent, specs, where, data=None):
    """The modules of `specs` (a manifest's, in its order) for a host: where 'play' or
    'batch'; data: the game's folder. A spec's `code` is imported first (it registers its
    kinds)."""
    out = []
    for spec in specs:
        if spec.get('code') and spec['kind'] not in REGISTRY:
            importlib.import_module(spec['code'])
        if spec['kind'] not in REGISTRY:
            raise ValueError(f"no module of kind {spec['kind']!r} (known: {sorted(REGISTRY)}): "
                             'a newer checkout, or its code not imported')
        out.append(REGISTRY[spec['kind']](agent, where, spec.get('files', {}),
                                          spec.get('options', {}), data))
    return out
