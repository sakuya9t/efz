"""Trained agents for the game: an agent file (.efzagent) written from a model.zip and
the config.json beside it, which the native game plays on character select and in
netplay (docs/agents.md), and which the library runs as the game does (NativeAgent),
with no machine learning library.

    from efz_env.export import export_agent, NativeAgent
    export_agent('runs/human-ayu/agent/avg.zip', 'agents/ayu.efzagent')   # needs SB3
    agent = NativeAgent('agents/ayu.efzagent')                             # needs only the library
    agent.reset()
    controls = agent.step(obs[0, side], actionable)   # each frame: the frame's control byte

The file holds the actor of the model's policy (python/efz_env/policy.py's EfzPolicy, or
SB3's MlpPolicy) and what efz_env.agent.Agent reads from config.json: frame_skip,
history, delay. Its layout is port/agent/policy.h's.
"""

import ctypes
import datetime
import os
import struct

import numpy as np

from . import _native
from .actions import ActionTable
from .agent import load_config

MAGIC = b'EFZAGENT'
FORMAT = 1


def _character_index(c):
    if c is None or c == 'any':
        return -1
    if isinstance(c, (int, np.integer)):
        return int(c)
    from .vec import character_names
    names = character_names()
    if c.lower() not in names:
        raise ValueError(f'no character {c!r}; they are {names}')
    return names.index(c.lower())


def _tensor(name, array, integer=False):
    a = np.ascontiguousarray(np.asarray(array), dtype='<i4' if integer else '<f4')
    key = name.encode()
    return (struct.pack('<H', len(key)) + key + struct.pack('<BB', int(integer), a.ndim) +
            struct.pack(f'<{a.ndim}I', *a.shape) + a.tobytes())


def _actor(policy):
    """(features: 'efz' or 'flat', its tensors, activation, [(weight, bias)], (weight, bias))
    of an SB3 ActorCriticPolicy's actor."""
    import torch as th
    from stable_baselines3.common.torch_layers import FlattenExtractor
    from .policy import EfzFeatures
    ext = policy.pi_features_extractor
    tensors = []
    if isinstance(ext, EfzFeatures):
        features = 'efz'
        tensors = [('features.cont', ext.cont.cpu().numpy(), True),
                   ('features.mean', ext.mean.cpu().numpy(), False),
                   ('features.scale', ext.scale.cpu().numpy(), False),
                   ('features.action', ext.action.weight.detach().cpu().numpy(), False),
                   ('features.own_action', ext.own_action.weight.detach().cpu().numpy(), False),
                   ('features.char', ext.char.weight.detach().cpu().numpy(), False)]
    elif isinstance(ext, FlattenExtractor):
        features = 'flat'
    else:
        raise ValueError(f'the policy reads its view with {type(ext).__name__}: the game knows '
                         'EfzFeatures and FlattenExtractor')
    activations = {th.nn.ReLU: 'relu', th.nn.Tanh: 'tanh'}
    if policy.activation_fn not in activations:
        raise ValueError(f'the policy uses {policy.activation_fn.__name__}: the game knows ReLU '
                         'and Tanh')
    layers = []
    for m in policy.mlp_extractor.policy_net:
        if isinstance(m, th.nn.Linear):
            layers.append((m.weight.detach().cpu().numpy(), m.bias.detach().cpu().numpy()))
        elif not isinstance(m, policy.activation_fn):
            raise ValueError(f'the policy network has a {type(m).__name__}')
    out = policy.action_net
    return (features, tensors, activations[policy.activation_fn], layers,
            (out.weight.detach().cpu().numpy(), out.bias.detach().cpu().numpy()))


def torch_log_probs(policy, views):
    """The model's own log-probabilities of each action for views (n, width)."""
    import torch as th
    with th.no_grad():
        obs = th.as_tensor(np.asarray(views, np.float32))
        latent = policy.mlp_extractor.forward_actor(policy.pi_features_extractor(obs))
        return th.log_softmax(policy.action_net(latent), dim=-1).numpy()


def sample_views(width, n=256, seed=0):
    """Views for checking an export: noise, with actions (0-599) and characters (0-24)
    where EfzFeatures embeds them and inputs as an input history has them."""
    from .policy import OBS_DIM, OPP_ACTION, OPP_CHAR, SELF_ACTION, SELF_CHAR
    rng = np.random.default_rng(seed)
    v = rng.normal(size=(n, width)).astype(np.float32)
    for col, top in ((SELF_ACTION, 600), (OPP_ACTION, 600), (SELF_CHAR, 25), (OPP_CHAR, 25)):
        if col < width:
            v[:, col] = rng.integers(0, top, n)
    if width > OBS_DIM:
        v[:, OBS_DIM:] = rng.integers(-1, 2, (n, width - OBS_DIM))
    return v


def export_agent(model_path, out_path, name=None, character=None, check=True):
    """Writes model_path (a model.zip, with its config.json) as an agent file at out_path.
    name: what the game shows (default: the model's folder for avg.zip / model.zip, else
    its file name). character: the one it plays (a name or 0-24; default the first of
    config.json's chars, else any). check: run the file in the library and compare its
    log-probabilities with the model's (the largest difference is returned)."""
    from stable_baselines3 import PPO
    cfg = load_config(model_path)
    model = PPO.load(model_path, device='cpu')
    policy = model.policy
    width = int(model.observation_space.shape[0])
    table = ActionTable().table  # as efz_env.agent.Agent plays it
    if model.action_space.n != len(table):
        raise ValueError(f'the model has {model.action_space.n} actions; the game plays '
                         f'the {len(table)} of ActionTable()')
    if character is None:
        chars = cfg.get('chars') or [None]
        character = chars[0] if isinstance(chars, (list, tuple)) else chars
    stem = os.path.splitext(os.path.basename(model_path))[0]
    if name is None:
        folder = os.path.basename(os.path.dirname(os.path.abspath(model_path)))
        name = folder if stem in ('avg', 'model', 'best') and folder else stem
    features, feature_tensors, activation, layers, out = _actor(policy)
    from .policy import OPP_ACTION, OPP_CHAR, SELF_ACTION, SELF_CHAR, ACTIONS, CHARACTERS
    keys = {
        'name': name.replace('\n', ' '),
        'character': _character_index(character),
        'frame_skip': int(cfg.get('frame_skip', 4)),
        'history': int(cfg.get('history', 0)),
        'delay': int(cfg.get('delay', 0)),
        'width': width,
        'actions': len(table),
        'table': bytes(table).hex(),
        'features': features,
        'activation': activation,
        'layers': len(layers),
        'self_action': SELF_ACTION, 'opp_action': OPP_ACTION,
        'self_char': SELF_CHAR, 'opp_char': OPP_CHAR,
        'action_vocab': ACTIONS, 'characters': CHARACTERS,
        'source': os.path.basename(model_path),
        'exported': datetime.datetime.now().isoformat(timespec='seconds'),
    }
    text = ''.join(f'{k}={v}\n' for k, v in keys.items()).encode()
    tensors = list(feature_tensors)
    for k, (w, b) in enumerate(layers):
        tensors += [(f'pi.{k}.weight', w, False), (f'pi.{k}.bias', b, False)]
    tensors += [('action.weight', out[0], False), ('action.bias', out[1], False)]
    blob = [MAGIC, struct.pack('<I', FORMAT), struct.pack('<I', len(text)), text,
            struct.pack('<I', len(tensors))] + [_tensor(*t) for t in tensors]
    os.makedirs(os.path.dirname(os.path.abspath(out_path)), exist_ok=True)
    with open(out_path, 'wb') as f:
        f.write(b''.join(blob))
    if not check:
        return None
    views = sample_views(width)
    native = NativeAgent(out_path)
    try:
        return float(np.abs(native.log_probs(views) - torch_log_probs(policy, views)).max())
    finally:
        native.close()


class NativeAgent:
    """An agent file run by the library, as the game runs it (port/agent/policy.h): each
    frame step(view, actionable) gives the control byte (forward/back relative), deciding
    on frames the controls do something and holding each decision frame_skip frames,
    seeing the game `delay` decisions late and its own last `history` inputs."""

    def __init__(self, path, deterministic=False, seed=None):
        self._lib = lib = _native.library()
        error = ctypes.create_string_buffer(512)
        self._h = lib.efz_env_agent_load(os.fsencode(path), error, 512)
        if not self._h:
            raise RuntimeError(f'{path}: {error.value.decode(errors="replace")}')
        info = _native.AgentInfo()
        lib.efz_env_agent_info(self._h, ctypes.byref(info))
        self.path = path
        self.name = info.name.decode(errors='replace')
        self.width, self.actions = info.width, info.actions
        self.frame_skip, self.history, self.delay = info.frame_skip, info.history, info.delay
        self.character = info.character
        self.deterministic = deterministic
        self.reset(seed)

    def log_probs(self, views):
        """(n, width) views -> (n, actions) log-probabilities."""
        v = np.ascontiguousarray(views, np.float32).reshape(-1, self.width)
        out = np.empty((len(v), self.actions), np.float32)
        self._lib.efz_env_agent_log_probs(self._h, v.ctypes.data, len(v), out.ctypes.data)
        return out

    def reset(self, seed=None):
        """A new match."""
        if seed is None:
            seed = int.from_bytes(os.urandom(8), 'little')
        self._lib.efz_env_agent_reset(self._h, seed)

    def step(self, view, actionable=True):
        """The frame's control byte for the player's view (obs_dim numbers)."""
        v = np.ascontiguousarray(view, np.float32)
        return int(self._lib.efz_env_agent_step(self._h, v.ctypes.data, int(bool(actionable)),
                                            int(self.deterministic)))

    @property
    def last_action(self):
        return int(self._lib.efz_env_agent_last_action(self._h))

    def close(self):
        if getattr(self, '_h', None):
            self._lib.efz_env_agent_free(self._h)
            self._h = None

    def __del__(self):
        self.close()
