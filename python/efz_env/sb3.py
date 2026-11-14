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
            -> n action indices; e.g. frozen(model) for a copy of a policy as it was, or
            mixture([...], assignment) for several, each in its own matches. With
            cpu_envs (a mask of the matches), the game's CPU plays player 2 in those.

history: frames of each agent's own inputs appended to its observation
(efz_env.history: what a policy acting every frame needs to carry a motion through),
for the opponent's observations too. An opponent made by frozen() from a policy over
fewer features (one trained without history) gets the observation it knows.

delay: a reaction time, in steps: every view the environment gives (the agents' and
the opponent's) is the game as it was that many steps before (efz_env.history.Delay);
the input history stays current, as a player knows what it pressed. opponent_delay:
the opponent's own, per match or for all, up to delay (0: it sees the game as it is, a
red-team opponent without a person's limits). delay_most: the agents' reaction time
varies, drawn each match from delay to delay_most (the opponent's stays its own).

Matches that end restart in the same step, as SB3 expects: infos[i] then holds
'terminal_observation', 'TimeLimit.truncated' and 'episode' ({'r', 'l', 't'}, as SB3's
Monitor writes it, so SB3 logs ep_rew_mean without a VecMonitor).
"""

import time

import numpy as np
from gymnasium import spaces
from stable_baselines3.common.vec_env.base_vec_env import VecEnv

from .actions import ActionTable
from .history import Delay, InputHistory
from .vec import EfzVecEnv


def copy_policy(source):
    """A copy of an SB3 policy as it is now, in evaluation mode.

    SB3's _get_constructor_parameters leaves share_features_extractor out, so a policy
    made from it alone shares one extractor between actor and critic whatever the source
    does; loading the source's weights then writes the critic's extractor over the
    actor's, and the copy plays with the wrong embeddings (until 12 November 2026 every
    frozen() copy did: the true agent beat such a copy of an exploiter 100% of the time
    and the exploiter itself 41%). The copy's weights are checked against the source's."""
    import torch
    kwargs = source._get_constructor_parameters()
    if hasattr(source, 'share_features_extractor'):
        kwargs['share_features_extractor'] = source.share_features_extractor
    policy = type(source)(**kwargs).to(source.device)
    state = source.state_dict()
    policy.load_state_dict(state)
    for name, value in policy.state_dict().items():
        if not torch.equal(value, state[name]):
            raise RuntimeError(f"copy_policy: the copy's {name} is not the source's")
    policy.set_training_mode(False)
    return policy


def frozen(model, deterministic=False):
    """An opponent for EfzSB3VecEnv: a copy of `model`'s policy as it is now."""
    policy = copy_policy(model.policy)
    width = policy.observation_space.shape[0]

    def act(obs):
        actions, _ = policy.predict(obs[:, :width], deterministic=deterministic)
        return actions
    # What mixture() needs to call it together with others of its architecture.
    act.policy, act.width, act.deterministic = policy, width, deterministic
    return act


_ACTOR = []  # the class, made once (torch is imported only when stacking)


def _actor(policy):
    """An ActorCriticPolicy's actor path (features, policy MLP, action head) as one
    module: its logits for observations of its own width."""
    if not _ACTOR:
        import torch

        class Actor(torch.nn.Module):
            def __init__(self, p):
                super().__init__()
                self.features = p.pi_features_extractor if not p.share_features_extractor \
                    else p.features_extractor
                self.mlp = p.mlp_extractor.policy_net
                self.head = p.action_net

            def forward(self, x):
                return self.head(self.mlp(self.features(x)))
        _ACTOR.append(Actor)
    return _ACTOR[0](policy)


def _stackable(policy):
    """The frozen() policy behind a mixture member (itself, or the `inner` of a member
    with a `post` step, such as advantages.AdvantagedOpponent), or None."""
    if getattr(policy, 'policy', None) is not None and hasattr(policy, 'width'):
        return policy
    inner = getattr(policy, 'inner', None)
    if hasattr(policy, 'post') and getattr(inner, 'policy', None) is not None:
        return inner
    return None


class _Stack:
    """Frozen policies of one architecture called as one: their weights stacked
    (torch.func.stack_module_state), each on its own matches' rows, padded to the most
    rows any of them has (a bucket keeps that close to their own). The same logits as
    each policy's own predict; the actions are drawn from them the same way."""

    def __init__(self, members):
        import copy
        import torch
        from torch.func import functional_call, stack_module_state, vmap
        self.members = members  # [(member, its frozen policy, idx)]
        actors = [_actor(f.policy) for _, f, _ in members]
        self.width = members[0][1].width
        self.deterministic = members[0][1].deterministic
        size = max(len(idx) for _, _, idx in members)
        self.gather = np.stack([np.resize(idx, size) for _, _, idx in members])  # repeats rows to pad
        self.efz = _EfzStack.make(actors)  # the policies of efz_env.policy: batched by hand
        if self.efz is None:
            self.params, self.buffers = stack_module_state(actors)
            base = copy.deepcopy(actors[0]).to('meta')
            self.fn = vmap(lambda p, b, x: functional_call(base, (p, b), (x,)))

    def logits(self, obs):
        import torch
        x = torch.as_tensor(np.asarray(obs, np.float32)[self.gather][:, :, :self.width])
        with torch.no_grad():
            if self.efz is not None:
                return self.efz(x)
            return self.fn(self.params, self.buffers, x)

    def __call__(self, obs):
        import torch
        logits = self.logits(obs)
        with torch.no_grad():
            a = (logits.argmax(-1) if self.deterministic else
                 torch.distributions.Categorical(logits=logits).sample())
        a = a.numpy()
        return [a[m, :len(idx)] for m, (_, _, idx) in enumerate(self.members)]


class _EfzStack:
    """The actors of efz_env.policy.EfzPolicy (EfzFeatures, a ReLU MLP, a linear head),
    stacked, as batched matrix products: torch.func's vmap does the same, its dispatch
    costing more than the arithmetic at a league's few rows per policy."""

    @classmethod
    def make(cls, actors):
        import torch
        from .policy import EfzFeatures
        a0 = actors[0]
        if not isinstance(a0.features, EfzFeatures):
            return None
        layers = list(a0.mlp) if isinstance(a0.mlp, torch.nn.Sequential) else None
        if not layers or not all(isinstance(m, (torch.nn.Linear, torch.nn.ReLU)) for m in layers):
            return None
        if not all(torch.equal(a.features.cont, a0.features.cont) for a in actors):
            return None
        return cls(actors, [type(m) for m in layers])

    def __init__(self, actors, kinds):
        import torch
        from . import policy as P
        st = lambda get: torch.stack([get(a).detach() for a in actors])
        f = lambda a: a.features
        self.cont = actors[0].features.cont
        self.mean, self.scale = st(lambda a: f(a).mean)[:, None], st(lambda a: f(a).scale)[:, None]
        self.action, self.own = st(lambda a: f(a).action.weight), st(lambda a: f(a).own_action.weight)
        self.char = st(lambda a: f(a).char.weight)
        self.layers = []
        for k, kind in enumerate(kinds):
            if kind is torch.nn.Linear:
                self.layers.append((st(lambda a: a.mlp[k].weight).transpose(1, 2).contiguous(),
                                    st(lambda a: a.mlp[k].bias)[:, None]))
            else:
                self.layers.append(None)  # ReLU
        self.head = (st(lambda a: a.head.weight).transpose(1, 2).contiguous(),
                     st(lambda a: a.head.bias)[:, None])
        self.m = torch.arange(len(actors))[:, None]
        self.cols = (P.SELF_ACTION, P.SELF_CHAR, P.OPP_ACTION, P.OPP_CHAR)
        self.n_actions, self.n_chars = P.ACTIONS, P.CHARACTERS

    def __call__(self, x):
        import torch
        m = self.m
        parts = [((x[..., self.cont] - self.mean) * self.scale).clamp(-10, 10)]
        sa, sc, oa, oc = self.cols
        chars = {}
        for a_col, c_col in ((sa, sc), (oa, oc)):
            act = x[..., a_col].round().long().clamp(0, self.n_actions - 1)
            char = x[..., c_col].round().long().clamp(0, self.n_chars - 1)
            chars[c_col] = char
            parts += [self.action[m, act], self.own[m, char * self.n_actions + act]]
        parts += [self.char[m, chars[sc]], self.char[m, chars[oc]]]
        h = torch.cat(parts, dim=-1)
        for layer in self.layers:
            h = torch.relu(h) if layer is None else torch.baddbmm(layer[1], h, layer[0])
        return torch.baddbmm(self.head[1], h, self.head[0])


def _stacks(groups):
    """groups [(policy, idx)] -> (stacks, the rest): the stackable members with matches,
    by architecture and observation width, in buckets of up to twice as many rows as the
    fewest among them."""
    keyed, rest = {}, []
    for policy, idx in groups:
        f = _stackable(policy) if policy is not None and len(idx) else None
        if f is None:
            rest.append((policy, idx))
            continue
        shapes = tuple((k, tuple(v.shape)) for k, v in f.policy.state_dict().items())
        key = (type(f.policy), shapes, f.width, f.deterministic,
               int(np.ceil(np.log2(len(idx)))))
        keyed.setdefault(key, []).append((policy, f, idx))
    return [_Stack(m) for m in keyed.values()], rest


def held(opponent, steps):
    """An opponent that decides every `steps` steps and holds its choice in between: a
    policy trained with frame_skip=steps, playing in an environment of frame_skip=1."""
    state = {'k': 0, 'last': None}

    def act(obs):
        if state['last'] is None or len(state['last']) != len(obs) or state['k'] % steps == 0:
            state['last'] = np.asarray(opponent(obs))
        state['k'] += 1
        return state['last']
    return act


def mixture(policies, assignment, stack=True):
    """An opponent of several policies: match i is played by policies[assignment[i]]
    (each a callable as EfzSB3VecEnv's opponent; None for matches the CPU plays). A
    policy with takes_index set is given its matches' indices too: policy(obs, idx).

    stack: frozen() policies of one architecture are called together, once a step
    (_Stack: their separate predict calls were half of a league's training time), as
    are the frozen policies inside members with a `post` step (post(actions, idx): the
    member's own change to them, advantages.AdvantagedOpponent's)."""
    assignment = np.asarray(assignment)
    groups = [(p, np.flatnonzero(assignment == k)) for k, p in enumerate(policies)]
    stacks, rest = _stacks(groups) if stack else ([], groups)

    def act(obs):
        actions = np.zeros(len(obs), dtype=np.int64)
        for st in stacks:
            for (member, f, idx), a in zip(st.members, st(obs)):
                actions[idx] = member.post(a.copy(), idx) if member is not f else a
        for policy, idx in rest:
            if policy is not None and len(idx):
                if getattr(policy, 'takes_index', False):
                    actions[idx] = policy(obs[idx], idx)
                else:
                    actions[idx] = policy(obs[idx])
        return actions
    return act


class EfzSB3VecEnv(VecEnv):
    def __init__(self, data_dir=None, num_envs=64, *, opponent='cpu', cpu_envs=None,
                 action_table=None, chars=(None, None), stage=None, char_pool=None,
                 stage_pool=None, history=0, delay=0, opponent_delay=None, delay_most=None,
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
        cpu = (False, opponent == 'cpu')
        if cpu_envs is not None:
            if self.opponent is None:
                raise ValueError('cpu_envs mixes the CPU in with a callable opponent')
            mask = np.broadcast_to(np.asarray(cpu_envs, dtype=bool), (num_envs,))
            cpu = [(False, bool(c)) for c in mask]
        self.env.set_matches(chars=chars, stage=stage, cpu=cpu, char_pool=char_pool,
                             stage_pool=stage_pool)
        self.k = 2 if self.selfplay else 1
        self._controls = np.zeros((num_envs, 2), dtype=np.uint8)
        self._length = np.zeros(num_envs, dtype=np.int64)
        self._start = time.time()
        self.history = InputHistory((num_envs, 2), history) if history else None
        self.delay = (Delay((num_envs, 2), delay, self.env.obs_dim, most=delay_most,
                            seed=config.get('seed')) if delay else None)
        self.opponent_delay = None
        if opponent_delay is not None and delay:
            d = np.broadcast_to(np.asarray(opponent_delay, dtype=int), (num_envs,)).copy()
            if (d < 0).any() or (d > delay).any():
                raise ValueError('opponent_delay: from 0 to delay')
            self.opponent_delay = d
        self._view = None  # what the players see now (delayed)
        width = self.env.obs_dim + (self.history.size if self.history else 0)
        obs_space = spaces.Box(-np.inf, np.inf, (width,), np.float32)
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

    def _with_history(self, obs):
        if self.history is None:
            return obs
        return np.concatenate([obs, self.history.features()], axis=-1)

    def reset(self):
        seeds = [s for s in getattr(self, '_seeds', [])][::self.k] or None
        if seeds is not None and all(s is None for s in seeds):
            seeds = None
        self._length[:] = 0
        obs = self.env.reset(seed=seeds)
        if self.history is not None:
            self.history.clear()
        if self.delay is not None:
            self.delay.clear()
            obs = self.delay.push(obs)
        self._view = obs
        obs = self._with_history(obs)
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
                view = self._with_history(self._view)[:, 1]
                if self.opponent_delay is not None:  # its own: so many steps ago
                    seen = self.delay.buf[np.arange(self.n), 1, self.opponent_delay]
                    view = np.concatenate([seen, view[:, seen.shape[1]:]], axis=1)
                self._controls[:, 1] = self.table.to_bytes(self.opponent(view))
        self.env.step_async(self._controls)

    def step_wait(self):
        obs, reward, terminated, truncated, info = self.env.step_wait()
        self._length += 1
        ended = terminated | truncated
        infos = [{} for _ in range(self.num_envs)]
        if self.history is not None:
            self.history.push(info['input'])
        if ended.any():
            final = self.env.final_obs if self.delay is None else self.delay.peek(self.env.final_obs)
            final = self._agents(self._with_history(final))
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
        if self.history is not None and ended.any():
            self.history.clear(ended)  # the next match's first view: nothing input yet
        if self.delay is not None:
            self.delay.clear(ended)
            obs = self.delay.push(obs)
        self._view = obs
        dones = np.repeat(ended, self.k)
        obs = self._with_history(obs)
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
