"""Trained agents for the game: an agent file (.efzagent) written from a model.zip and
the config.json beside it, or from a pack (play.py's zip carrying an agent by hand: its
model, combo library, the library's join points and its chooser, all of it in the one
file), which the native game plays on character select and in netplay (docs/agents.md),
and which the library runs as the game does (NativeAgent), with no machine learning
library.

    from efz_env.export import export_agent, export_pack, NativeAgent
    export_agent('runs/human-ayu/agent/avg.zip', 'agents/ayu.efzagent')   # needs SB3
    export_pack('tmp/efz-round15b-pack.zip', 'agents/ayu.efzagent')       # needs SB3, torch
    agent = NativeAgent('agents/ayu.efzagent')                             # needs only the library
    agent.reset()
    controls = agent.step(obs[0, side], actionable)   # each frame: the frame's control byte

The file (port/agent/policy.h's layout, format 2) is made of modules, each of a version
(MODULES), and says which; a game refuses a module it doesn't play, by name:

    policy   the actor of the model's policy (python/efz_env/policy.py's EfzPolicy, or SB3's
             MlpPolicy) and what efz_env.agent.Agent reads from config.json: frame_skip,
             history, delay
    routes   a combo library's routes: the game plays the agent's combos as play.py --assist
             does (runs/human-ayu/combo_support.py's LiveRoutes), trying them on copies of
             the fight at each hit (port/agent/routes.h); with replan (round 15b's) again at
             each new move's hit, the routes joined where that move hit in them (the
             library's join points, combo_library.py --marks)
    chooser  runs/human-ayu/combo_net.py's chooser for that agent and library: the route
             it picks is played when a combo's first plan isn't ready in time

and records where each part came from (source.*: the file and its SHA-256), the exporter's
revision, and a version to show (export_agent(..., version=)).

An agent file is also how a trained agent is released and worked on from (the user's, 15
November: "released checkpoints should be packed and published into the .efzagent format
... tools to unpack the checkpoint and finetuning and further working on any packed
version"). So beside its modules, which a game plays, a file carries a training part,
which a game doesn't read and doesn't need (keys and tensors of no module: an older game
plays the file as before):

    train    the rest of the model a game leaves out: the critic (its features, layers and
             value), the model's config.json (train.config) and PPO's settings
             (train.sb3); with optimizer=True Adam's moments too. The routes carry what
             the planner in Python needs beyond the game's (each one's damage, whether it
             was kept for its victim, its join points).

    from efz_env.export import unpack_agent
    got = unpack_agent('agents/ayu.efzagent', 'work/ayu')   # needs SB3, torch
    # work/ayu/model.zip + config.json (finetune.py --start, evaluate.py, play.py), and
    # work/ayu/combo-library.npz + .marks.json (their --assist) if the file has routes

unpack_agent makes the model anew from the file's numbers and JSON: nothing of the file
is run or unpickled, so a file from anyone can be unpacked. efz_env.agent.Agent takes an
agent file where it takes a model.zip (it unpacks it), and so do the tools that use it.
export_agent(..., parts_from=FILE) writes a model with the routes and chooser of an
agent file as they are: a packed agent trained further and packed again.
"""

import ctypes
import datetime
import hashlib
import json
import os
import struct
import subprocess
import tempfile
import zipfile

import numpy as np

from . import _native
from .actions import ActionTable
from .agent import load_config

MAGIC = b'EFZAGENT'
FORMAT = 2
# The modules this exporter writes, each's version (port/agent/policy.h's kModules).
MODULES = {'policy': 1, 'routes': 1, 'chooser': 1}
TRAIN = 1  # the training part's version (key train)
# PPO's settings a file keeps (train.sb3) and unpack_agent makes the model with.
HYPER = ('n_steps', 'batch_size', 'n_epochs', 'gamma', 'gae_lambda', 'ent_coef', 'vf_coef',
         'max_grad_norm', 'normalize_advantage')
# The planner's settings, redteam.py's Planner as play.py --assist makes it: round 15's
# (one plan at the first hit) 12 routes a plan; round 15b's (replan) 24.
PER_START, PER_START_REPLAN, LIMIT = 12, 24, 900
# The chooser's, combo_net.py's NetPlanner's.
CHOOSER_PER_START, CHOOSER_MARGIN = 12, 200.0


def load_routes(path):
    """A combo library (runs/human-ayu/combo_library.py's .npz) as the planner reads it
    (runs/human-ayu/macros.py's load_library): each combo's starter (the action of the
    move that hit), the character it was landed on, whether it was kept for that victim,
    its damage, its join points (LIBRARY.marks.json beside it, if there is one: where each
    new move of it first hit) and its inputs as actions of ActionTable(), a combo played
    again left out. A combo's place in the list is the one combo_net.py's chooser knows it
    by."""
    from .history import action_labels
    table = ActionTable()
    lib = np.load(path)
    meta = json.loads(str(lib['meta']))
    marks = {}
    if os.path.exists(marks_path(path)):
        with open(marks_path(path)) as f:
            marks = json.load(f)
    out, seen = [], set()
    for k, m in enumerate(meta):
        inputs = lib[f'inputs{k}']
        acts = action_labels(np.concatenate([[m.get('prev', 0)], inputs]).astype(np.uint8),
                             table)[1:]
        key = (m['starter'], acts.tobytes())
        if key in seen:
            continue
        seen.add(key)
        out.append(dict(starter=int(m['starter']), opponent=m.get('opponent'),
                        kept_for=m.get('kept_for'), damage=m.get('damage'),
                        marks=marks.get(str(k), []), actions=acts))
    return out


def marks_path(library):
    """Where a library's join points are (combo_library.py --marks writes them)."""
    return os.path.splitext(os.fspath(library))[0] + '.marks.json'


def replan_pool(routes):
    """redteam.Planner(replan=True)'s pools: per starter, its entries (the route's place in
    `routes`, the step it is played from, what it is worth) in the order the planner takes
    them, by damage: each route from its start, and from each of its join points but the
    first (where a later move of it first hit: from there its inputs are what followed that
    move), worth the damage the recording made after it."""
    if any(m.get('damage') is None for m in routes):
        raise ValueError("routes: replanning orders them by damage, and the library's combos "
                         "have none")
    by = {}
    for k, m in enumerate(routes):
        by.setdefault(int(m['starter']), []).append((k, 0, m['damage']))
    for k, m in enumerate(routes):
        for step, move, before, _ in m.get('marks', [])[1:]:
            by.setdefault(int(move), []).append((k, int(step), m['damage'] - before))
    for pool in by.values():
        pool.sort(key=lambda e: -e[2])
    return by


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
    """integer: False float32 (type 0), True int32 (1), 'u8' uint8 (2)."""
    kind = 2 if integer == 'u8' else int(bool(integer))
    a = np.ascontiguousarray(np.asarray(array), dtype=('<f4', '<i4', 'u1')[kind])
    key = name.encode()
    return (struct.pack('<H', len(key)) + key + struct.pack('<BB', kind, a.ndim) +
            struct.pack(f'<{a.ndim}I', *a.shape) + a.tobytes())


def _route_parts(routes, victims, history, delay, frame_skip, replan=False, per_start=None):
    """The routes' keys and tensors for the agent file."""
    from .vec import character_names
    if frame_skip != 1 or delay <= 0 or history <= 0:
        raise ValueError('routes: an agent deciding every frame (frame_skip 1), with a delay '
                         'and its input history, as LiveRoutes plays one')
    names = character_names()
    if victims:
        unknown = set(victims) - set(names)
        if unknown:
            raise ValueError(f'victims: no such characters {sorted(unknown)}')
    acts = [np.asarray(m['actions'], np.int64) for m in routes]
    if any(len(a) and (a.min() < 0 or a.max() > 255) for a in acts):
        raise ValueError('routes: actions out of 0-255')
    offsets = np.concatenate([[0], np.cumsum([len(a) for a in acts])]).astype(np.int64)
    if offsets[-1] >= 2 ** 31:
        raise ValueError('routes: too many inputs')
    if per_start is None:
        per_start = PER_START_REPLAN if replan else PER_START
    pool = []
    if replan:  # (the pool in the planner's order, each starter's entries in theirs)
        for starter, entries in sorted(replan_pool(routes).items()):
            pool += [(k, step, starter) for k, step, _ in entries]
    keys = {
        'routes': len(routes),
        'route_per_start': int(per_start),
        'route_limit': LIMIT,
        'route_by_victim': int(any(m.get('kept_for') == 'victim' for m in routes)),
        'route_victims': ','.join(str(names.index(v)) for v in victims or []),
        'route_replan': int(bool(replan)),
        'route_pool': len(pool),
    }
    tensors = [
        ('routes.starter', [m['starter'] for m in routes], True),
        ('routes.opponent', [names.index(m['opponent']) if m.get('opponent') in names else -1
                             for m in routes], True),
        ('routes.offset', offsets, True),
        ('routes.actions', np.concatenate(acts) if acts else np.zeros(0, np.uint8), 'u8'),
    ]
    if pool:
        p = np.array(pool, np.int64)
        tensors += [('routes.pool.route', p[:, 0], True), ('routes.pool.at', p[:, 1], True),
                    ('routes.pool.starter', p[:, 2], True)]
    # What the planner in Python reads beyond these (unpack_agent's library): each route's
    # damage, whether it was kept for its victim, and its join points (step, move, the
    # damage before it, hits), all the routes' one after another.
    if routes and all(m.get('damage') is not None for m in routes):
        marks = [np.asarray(m.get('marks') or np.zeros((0, 4)), np.float32).reshape(-1, 4)
                 for m in routes]
        tensors += [('routes.damage', [m['damage'] for m in routes], False),
                    ('routes.kept', [m.get('kept_for') == 'victim' for m in routes], 'u8'),
                    ('routes.marks.offset',
                     np.concatenate([[0], np.cumsum([len(x) for x in marks])]), True),
                    ('routes.marks', np.concatenate(marks) if marks else np.zeros((0, 4)), False)]
    return keys, tensors


def _features(ext, prefix=''):
    """('efz' or 'flat', its tensors) of a features extractor, the tensors' names under
    prefix."""
    from stable_baselines3.common.torch_layers import FlattenExtractor
    from .policy import EfzFeatures
    if isinstance(ext, EfzFeatures):
        f = prefix + 'features.'
        return 'efz', [(f + 'cont', ext.cont.cpu().numpy(), True),
                       (f + 'mean', ext.mean.cpu().numpy(), False),
                       (f + 'scale', ext.scale.cpu().numpy(), False),
                       (f + 'action', ext.action.weight.detach().cpu().numpy(), False),
                       (f + 'own_action', ext.own_action.weight.detach().cpu().numpy(), False),
                       (f + 'char', ext.char.weight.detach().cpu().numpy(), False)]
    if isinstance(ext, FlattenExtractor):
        return 'flat', []
    raise ValueError(f'the policy reads its view with {type(ext).__name__}: the game knows '
                     'EfzFeatures and FlattenExtractor')


def _chooser_parts(model, path, routes, margin=CHOOSER_MARGIN):
    """A chooser (runs/human-ayu/combo_net.py train-chooser's chooser.pt: a copy of the
    agent's features, trained on, and a head Linear-ReLU-Linear-ReLU-Linear saying what each
    of the library's routes and its own play (the last) would deal, in thousands of HP):
    its keys and tensors for the agent file, and its own values (views -> HP) to check the
    file's against."""
    import copy
    import torch as th
    saved = th.load(path, map_location='cpu', weights_only=False)
    if int(saved.get('routes', -1)) != len(routes):
        raise ValueError(f"{path}: a chooser of a library of {saved.get('routes')} combos, "
                         f"and the library has {len(routes)}")
    state = saved['state']
    ext = copy.deepcopy(model.policy.pi_features_extractor)
    ext.load_state_dict({k[len('features.'):]: v for k, v in state.items()
                         if k.startswith('features.')})
    ext.eval()
    heads = sorted({int(k.split('.')[1]) for k in state if k.startswith('head.')})
    if heads != [0, 2, 4]:
        raise ValueError(f"{path}: the chooser's head isn't Linear-ReLU-Linear-ReLU-Linear")
    lin = [(state[f'head.{i}.weight'].float(), state[f'head.{i}.bias'].float()) for i in heads]
    if lin[-1][0].shape[0] != len(routes) + 1:
        raise ValueError(f"{path}: the chooser says {lin[-1][0].shape[0]} values, the library "
                         f"has {len(routes)} combos (and its own play)")
    features, tensors = _features(ext, 'chooser.')
    for k, (w, b) in enumerate(lin[:-1]):
        tensors += [(f'chooser.layer.{k}.weight', w.numpy(), False),
                    (f'chooser.layer.{k}.bias', b.numpy(), False)]
    tensors += [('chooser.out.weight', lin[-1][0].numpy(), False),
                ('chooser.out.bias', lin[-1][1].numpy(), False)]
    keys = {'chooser_features': features, 'chooser_activation': 'relu',
            'chooser_layers': len(lin) - 1, 'chooser_per_start': CHOOSER_PER_START,
            'chooser_margin': float(margin)}

    def values(views):
        with th.no_grad():
            x = ext(th.as_tensor(np.asarray(views, np.float32)))
            for k, (w, b) in enumerate(lin):
                x = th.nn.functional.linear(x, w, b)
                if k < len(lin) - 1:
                    x = th.relu(x)
            return x.numpy() * 1000
    return keys, tensors, values


def _actor(policy):
    """(features: 'efz' or 'flat', its tensors, activation, [(weight, bias)], (weight, bias))
    of an SB3 ActorCriticPolicy's actor."""
    import torch as th
    features, tensors = _features(policy.pi_features_extractor)
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


def _line(obj):
    """An object as one line of JSON for the header, the home folder written as ~ (a
    file goes to other people)."""
    text = json.dumps(obj, separators=(',', ':'))
    home = os.path.expanduser('~')
    return text.replace(home, '~') if len(home) > 1 else text


def _number(x):
    """A setting as JSON keeps it (None: not a plain number)."""
    if isinstance(x, (bool, np.bool_)):
        return bool(x)
    if isinstance(x, (int, np.integer)):
        return int(x)
    if isinstance(x, (float, np.floating)):
        return float(x)
    return None


def _train_parts(model, cfg, optimizer=False):
    """The training part's keys and tensors: what of the model a game leaves out."""
    import torch as th
    policy = model.policy
    shared = bool(getattr(policy, 'share_features_extractor', True))
    tensors = []
    if not shared:
        tensors += _features(policy.vf_features_extractor, 'train.vf.')[1]
    k = 0
    for m in policy.mlp_extractor.value_net:
        if isinstance(m, th.nn.Linear):
            tensors += [(f'train.vf.{k}.weight', m.weight.detach().cpu().numpy(), False),
                        (f'train.vf.{k}.bias', m.bias.detach().cpu().numpy(), False)]
            k += 1
    tensors += [('train.value.weight', policy.value_net.weight.detach().cpu().numpy(), False),
                ('train.value.bias', policy.value_net.bias.detach().cpu().numpy(), False)]
    sb3 = dict(policy=type(policy).__name__, share_features_extractor=shared,
               ortho_init=bool(getattr(policy, 'ortho_init', True)), vf_layers=k,
               num_timesteps=int(model.num_timesteps),
               optimizer=type(policy.optimizer).__name__,
               optimizer_kwargs={k: v for k, v in (policy.optimizer_kwargs or {}).items()
                                 if _number(v) is not None})
    for name in HYPER:
        v = _number(getattr(model, name, None))
        if v is not None:
            sb3[name] = v
    lr = _number(model.learning_rate)
    if lr is not None:
        sb3['learning_rate'] = lr
    try:
        sb3['clip_range'] = float(model.clip_range(1.0))
    except TypeError:
        if _number(model.clip_range) is not None:
            sb3['clip_range'] = _number(model.clip_range)
    if optimizer:
        if type(policy.optimizer).__name__ != 'Adam':
            raise ValueError(f"optimizer: the model's is {type(policy.optimizer).__name__}; "
                             'an agent file keeps Adam\'s')
        state = policy.optimizer.state_dict()['state']
        params = list(policy.parameters())
        if len(state) == len(params):  # (none before the first update)
            sb3['adam_step'] = int(max(float(v['step']) for v in state.values()))
            for j in range(len(params)):
                tensors += [(f'train.adam.{j}.m', state[j]['exp_avg'].cpu().numpy(), False),
                            (f'train.adam.{j}.v', state[j]['exp_avg_sq'].cpu().numpy(), False)]
    keys = {'train': TRAIN, 'train.config': _line(cfg), 'train.sb3': _line(sb3)}
    return keys, tensors


def read_agent(path):
    """An agent file whole: (its format, its header's keys, {tensor name: its array})."""
    with open(path, 'rb') as f:
        data = f.read()
    if data[:8] != MAGIC:
        raise ValueError(f'{path}: not an agent file')
    fmt, size = struct.unpack_from('<II', data, 8)
    keys = {}
    for line in data[16:16 + size].decode('utf-8', errors='replace').split('\n'):
        if '=' in line:
            k, v = line.split('=', 1)
            keys[k] = v
    at = 16 + size
    (count,) = struct.unpack_from('<I', data, at)
    at += 4
    tensors = {}
    for _ in range(count):
        (n,) = struct.unpack_from('<H', data, at)
        tname = data[at + 2:at + 2 + n].decode()
        at += 2 + n
        kind, ndim = struct.unpack_from('<BB', data, at)
        if kind > 2 or ndim > 4:
            raise ValueError(f'{path}: damaged (the tensor {tname})')
        at += 2
        dims = struct.unpack_from(f'<{ndim}I', data, at)
        at += 4 * ndim
        dtype = np.dtype(('<f4', '<i4', 'u1')[kind])
        total = int(np.prod(dims, dtype=np.int64)) * dtype.itemsize
        if at + total > len(data):
            raise ValueError(f'{path}: cut short (the tensor {tname})')
        tensors[tname] = np.frombuffer(data, dtype, total // dtype.itemsize, at).reshape(dims).copy()
        at += total
    return fmt, keys, tensors


def _modules(keys, fmt):
    """The modules a file's header names: {name: version}."""
    text = keys.get('modules') or ('policy:1,routes:1' if int(keys.get('routes', 0) or 0) > 0
                                   else 'policy:1')
    out = {}
    for item in filter(None, text.split(',')):
        name, _, version = item.partition(':')
        out[name] = int(version or 1)
    return out


def _carried(path, keep):
    """The parts of the agent file `path` another file takes as they are (keep: of
    'routes', 'chooser'): (modules, keys, tensors as _tensor takes them)."""
    fmt, keys, tensors = read_agent(path)
    has = _modules(keys, fmt)
    modules, out_keys, out_tensors = [], {}, []
    prefixes = {'routes': ('routes', 'route_', 'source.library', 'source.marks'),
                'chooser': ('chooser_', 'source.chooser')}
    for part in ('routes', 'chooser'):
        if part not in keep or part not in has:
            continue
        if part == 'chooser' and 'routes' not in modules:
            continue  # (it chooses among the routes)
        modules.append(part)
        for k, v in keys.items():
            if k == part or any(k.startswith(x) for x in prefixes[part]):
                out_keys[k] = v
        for name, a in tensors.items():
            if name.startswith(part + '.'):
                out_tensors.append((name, a, 'u8' if a.dtype == np.uint8 else
                                    a.dtype.kind == 'i'))
    return modules, out_keys, out_tensors


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


def sha256(path_or_bytes):
    h = hashlib.sha256()
    if isinstance(path_or_bytes, (bytes, bytearray)):
        h.update(path_or_bytes)
    else:
        with open(path_or_bytes, 'rb') as f:
            for block in iter(lambda: f.read(1 << 20), b''):
                h.update(block)
    return h.hexdigest()


def exporter():
    """This exporter and the revision of the checkout it is in (git describe), if it is in
    one."""
    repo = os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    try:
        rev = subprocess.run(['git', '-C', repo, 'describe', '--always', '--dirty'],
                             capture_output=True, text=True, timeout=10).stdout.strip()
    except (OSError, subprocess.SubprocessError):
        rev = ''
    return 'efz_env.export' + (f' {rev}' if rev else '')


def _one_line(v):
    return str(v).replace('\n', ' ').replace('\r', ' ')


def export_agent(model_path, out_path, name=None, character=None, check=True, library=None,
                 victims=None, replan=False, per_start=None, chooser=None,
                 margin=CHOOSER_MARGIN, version=None, sources=None, dropped=(), train=True,
                 optimizer=False, parts_from=None, keep=('routes', 'chooser')):
    """Writes model_path (a model.zip, with its config.json) as an agent file at out_path.
    name: what the game shows (default: the model's folder for avg.zip / model.zip, else
    its file name). character: the one it plays (a name or 0-24; default the first of
    config.json's chars, else any). library: a combo library (.npz, with its join points
    beside it if they are there; or load_routes's list) whose routes the game plays the
    agent's combos from, as play.py --assist does; victims: the characters it plans
    against (play.py --assist-victims; None all); replan: planned again at each new move's
    hit (round 15b's); per_start: the routes tried a plan (default 12, replanning 24).
    chooser: combo_net.py's chooser.pt for that agent and library, played when a combo's
    first plan is late; margin: what a route it picks must promise beyond the agent's own
    play (HP). version: what the game shows beside the name. sources: {part: (label,
    sha256)} where each part came from (default: the files given); dropped: what of its
    pack was left out, for the record.
    train: the file carries its training part too (the critic, config.json, PPO's
    settings), so that it can be unpacked and trained further (unpack_agent); optimizer:
    Adam's moments as well (three times the size: a fine-tune starts well without).
    parts_from: an agent file whose routes and chooser (keep: which) go into this one as
    they are, for a model without its library at hand: a packed agent trained further.
    check: run the file in the library and compare it with the model: {'policy': the
    largest difference of the log-probabilities, 'chooser': of the chooser's values (HP),
    None without one; 'routes', 'pool': the file's as the library reads them} (None if not
    check)."""
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
    if chooser is not None and library is None:
        raise ValueError('chooser: it chooses among the routes of a library')
    carried = ([], {}, [])
    if parts_from is not None:
        if library is not None or chooser is not None:
            raise ValueError('parts_from: the routes and chooser of that file, or a library '
                             'and chooser given, not both')
        carried = _carried(parts_from, keep)
    features, feature_tensors, activation, layers, out = _actor(policy)
    from .policy import OPP_ACTION, OPP_CHAR, SELF_ACTION, SELF_CHAR, ACTIONS, CHARACTERS
    modules = (['policy'] + ['routes'] * (library is not None) +
               ['chooser'] * (chooser is not None) + carried[0])
    keys = {
        'modules': ','.join(f'{m}:{MODULES[m]}' for m in modules),
        'name': _one_line(name),
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
    }
    if version:
        keys['version'] = _one_line(version)
    route_tensors, chooser_tensors, chooser_values = [], [], None
    routes = None
    if library is not None:
        routes = load_routes(library) if isinstance(library, (str, os.PathLike)) else library
        route_keys, route_tensors = _route_parts(routes, victims, keys['history'],
                                                 keys['delay'], keys['frame_skip'],
                                                 replan=replan, per_start=per_start)
        keys.update(route_keys)
        if isinstance(library, (str, os.PathLike)):
            keys['route_source'] = os.path.basename(os.fspath(library))
    if chooser is not None:
        chooser_keys, chooser_tensors, chooser_values = _chooser_parts(model, chooser, routes,
                                                                       margin)
        keys.update(chooser_keys)
    if carried[0]:
        if 'routes' in carried[0] and (keys['frame_skip'] != 1 or keys['delay'] <= 0 or
                                       keys['history'] <= 0):
            raise ValueError('parts_from: routes are for an agent deciding every frame, with '
                             'a delay and its input history')
        keys.update(carried[1])
        route_tensors = carried[2]
        keys['parts_from'] = _one_line(os.path.basename(os.fspath(parts_from)))
    train_tensors = []
    if train:
        train_keys, train_tensors = _train_parts(model, cfg, optimizer)
        keys.update(train_keys)
    # Where it came from.
    if sources is None:
        sources = {'model': (os.path.basename(model_path), sha256(model_path))}
        if isinstance(library, (str, os.PathLike)):
            sources['library'] = (os.path.basename(os.fspath(library)), sha256(library))
            if replan and os.path.exists(marks_path(library)):
                sources['marks'] = (os.path.basename(marks_path(library)),
                                    sha256(marks_path(library)))
        if chooser is not None:
            sources['chooser'] = (os.path.basename(os.fspath(chooser)), sha256(chooser))
    for part, (label, digest) in sources.items():
        keys.setdefault(f'source.{part}', _one_line(f'{label} sha256:{digest}'))
    keys['exporter'] = _one_line(exporter())
    keys['exported'] = datetime.datetime.now().isoformat(timespec='seconds')
    if dropped:
        keys['dropped'] = _one_line(', '.join(dropped))
    text = ''.join(f'{k}={v}\n' for k, v in keys.items()).encode()
    tensors = list(feature_tensors)
    for k, (w, b) in enumerate(layers):
        tensors += [(f'pi.{k}.weight', w, False), (f'pi.{k}.bias', b, False)]
    tensors += [('action.weight', out[0], False), ('action.bias', out[1], False)]
    tensors += route_tensors + chooser_tensors + train_tensors
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
        result = dict(policy=float(np.abs(native.log_probs(views) -
                                          torch_log_probs(policy, views)).max()),
                      chooser=None, routes=native.routes, pool=native.pool)
        if chooser_values is not None:
            mine = np.stack([native.choose(v, 0, 0)[1] for v in views])
            result['chooser'] = float(np.abs(mine - chooser_values(views)).max())
        want_routes = want_pool = 0
        if routes is not None:  # (no pool written: the routes themselves)
            want_routes, want_pool = len(routes), route_keys['route_pool'] or len(routes)
        elif 'routes' in carried[0]:
            want_routes = int(carried[1]['routes'])
            want_pool = int(carried[1].get('route_pool', 0) or 0) or want_routes
        if native.routes != want_routes or native.pool != want_pool:
            raise ValueError(f'{out_path}: the file has {native.routes} routes and a pool of '
                             f'{native.pool}; it was written with {want_routes} and '
                             f'{want_pool}')
        return result
    finally:
        native.close()


# A pack's files, by what they are to an agent file: carried in it, or not needed by the
# game (which plays its own code).
CARRIED = {'model': 'policy', 'config': 'policy', 'library': 'routes',
           'marks': 'routes (its join points)', 'chooser': 'chooser'}
NOT_NEEDED = {'code': "the pack's code: the game plays its own (port/agent)",
              'readme': 'notes for a person', 'launcher': "play.py's launcher",
              'chooser record': "the chooser's training record",
              'manifest': 'what the pack is made of (read)'}


def read_pack(path):
    """A pack (play.py's: a zip carrying an agent by hand) as an agent file takes it:
    {name in the zip: what it is}, one of CARRIED's, NOT_NEEDED's, or None (nothing an
    agent file knows). Its model is FOLDER/avg.zip (else the first .zip) with its
    config.json; what lies beside that folder is the agent's: a library (.npz), its join
    points (.marks.json), a chooser (chooser.pt, with its training record), a manifest
    (agent.json, runs/human-ayu's efz_env.modules); the code beside, files outside that
    folder. ValueError if it isn't a pack."""
    if not zipfile.is_zipfile(path):
        raise ValueError(f'{path}: not a zip')
    with zipfile.ZipFile(path) as z:
        names = [n for n in z.namelist() if not n.endswith('/')]
    models = sorted((n for n in names if n.endswith('.zip')),
                    key=lambda n: (not n.endswith('avg.zip'), n))
    if 'data' in names or not models:
        raise ValueError(f'{path}: not a pack (no FOLDER/avg.zip in it)')
    model = models[0]
    folder = os.path.dirname(model)
    choosers = {os.path.dirname(n) for n in names if os.path.basename(n) == 'chooser.pt'}
    out = {}
    for n in names:
        base, where = os.path.basename(n), os.path.dirname(n)
        if n == model:
            kind = 'model'
        elif where == folder and base == 'config.json':
            kind = 'config'
        elif base == 'agent.json':
            kind = 'manifest'
        elif base.endswith('.marks.json'):
            kind = 'marks'
        elif base.endswith('.npz'):
            kind = 'library'
        elif base == 'chooser.pt':
            kind = 'chooser'
        elif where in choosers and base in ('combo_net.json', 'config.json'):
            kind = 'chooser record'
        elif base.endswith('.py') or base == '.gitignore':
            kind = 'code'
        elif base.lower().startswith('readme'):
            kind = 'readme'
        elif base.endswith(('.sh', '.cmd', '.bat', '.ps1')):
            kind = 'launcher'
        else:
            kind = None
        out[n] = kind
    return out


def pack_name(path):
    """A pack's version, from its file's name: efz-round15b-pack.zip -> round15b."""
    stem = os.path.splitext(os.path.basename(path))[0]
    for prefix in ('efz-',):
        stem = stem[len(prefix):] if stem.startswith(prefix) else stem
    return stem[:-len('-pack')] if stem.endswith('-pack') else stem


def export_pack(path, out_path=None, name=None, version=None, character=None, drop=(),
                replan=None, per_start=None, check=True, log=print, train=True,
                optimizer=False):
    """Writes a pack (read_pack) as one agent file: its model, its library's routes with
    their join points, its chooser, as its play.py plays them (an agent.json says how;
    without one, round 15b's packs' way when the library has join points: planned again at
    each new move's hit, 24 routes a plan; else round 15's: once, 12). Each of the pack's
    files is carried or not needed; one the agent file can't carry stops the export, unless
    left out: drop, file names in the pack or parts ('routes', 'chooser', 'marks'). replan,
    per_start: as export_agent's (None: as the pack plays). version: default the pack's name
    (pack_name). out_path: default beside the pack, NAME-VERSION.efzagent. log: each file's
    fate, a line each. train, optimizer: export_agent's (the training part). Returns
    (out_path, export_agent's check, {file: its fate})."""
    kinds = read_pack(path)
    drop = set(drop)
    parts = {'routes', 'chooser', 'marks'}
    manifests = [n for n, k in kinds.items() if k == 'manifest']
    with zipfile.ZipFile(path) as z:  # (an agent.json's modules can be dropped by kind)
        for n in manifests:
            parts |= {spec.get('kind') for spec in json.loads(z.read(n)).get('modules', [])}
    unknown_drops = drop - parts - set(kinds)
    if unknown_drops:
        raise ValueError(f'drop: {sorted(unknown_drops)} is neither a part ({sorted(parts)}) '
                         f'nor a file of {os.path.basename(path)}')
    if 'routes' in drop:
        drop |= {'library', 'chooser', 'marks'}
    by_kind = {}
    for n, k in kinds.items():
        by_kind.setdefault(k, []).append(n)
    fate = {}
    with zipfile.ZipFile(path) as z, tempfile.TemporaryDirectory() as tmp:
        def take(n):
            dest = os.path.join(tmp, *n.split('/'))
            os.makedirs(os.path.dirname(dest), exist_ok=True)
            with z.open(n) as src, open(dest, 'wb') as f:
                f.write(src.read())
            return dest

        def digest(n):
            return sha256(z.read(n))

        def one(kind, among=None):
            names = [n for n in (among if among is not None else by_kind.get(kind, []))
                     if n not in drop and kind not in drop]
            if len(names) > 1:
                raise ValueError(f'{os.path.basename(path)} has {len(names)} {kind} files '
                                 f'({", ".join(names)}): drop all but one')
            return names[0] if names else None

        model = one('model')
        options = {}
        manifest = one('manifest')
        library = one('library')
        chooser = one('chooser')
        if manifest:  # efz_env.modules's agent.json: its model and modules decide
            m = json.loads(z.read(manifest))
            base = os.path.dirname(manifest)

            def inside(p):
                return os.path.normpath(os.path.join(base, p)).replace(os.sep, '/')
            model = inside(m['model'])
            library = chooser = None
            for spec in m.get('modules', []):
                kind = spec.get('kind')
                if kind != 'routes':
                    if kind in drop:  # (its files with it)
                        drop |= {inside(f) for f in spec.get('files', {}).values()}
                    else:
                        raise ValueError(f"{os.path.basename(path)}: its agent.json has a module "
                                         f"'{kind}', which an agent file can't carry yet: "
                                         f"drop {kind} to export without it")
                    continue
                if 'routes' in drop:
                    continue
                files, options = spec.get('files', {}), dict(spec.get('options', {}))
                if options.get('by', 'planner') != 'planner':
                    raise ValueError(f"{os.path.basename(path)}: its routes are chosen by the "
                                     f"chooser alone; the game plans them (by: planner)")
                library = inside(files['library']) if files.get('library') else None
                chooser = (inside(files['chooser']) if files.get('chooser') and
                           'chooser' not in drop else None)
                options.setdefault('replan', True)
                options.setdefault('per_start', PER_START_REPLAN)
        marks = None
        if library:
            want = marks_path(library).replace(os.sep, '/')
            marks = want if want in kinds and 'marks' not in drop and want not in drop else None
        if replan is None:
            replan = bool(options.get('replan', marks is not None)) if library else False
        if per_start is None:
            per_start = options.get('per_start')
        if model not in kinds:
            raise ValueError(f'{os.path.basename(path)}: its agent.json names the model {model}, '
                             f'which it hasn\'t got')
        config = os.path.join(os.path.dirname(model), 'config.json').replace(os.sep, '/')
        role = {n: what for n, what in ((model, 'policy'), (library, 'routes'),
                                         (marks, 'routes (its join points)'),
                                         (chooser, 'chooser')) if n}
        if config in kinds:
            role[config] = 'policy (its settings)'
        for n, k in sorted(kinds.items()):
            if n in role:
                fate[n] = 'in the file: ' + role[n]
            elif n in drop or k in drop or (k in CARRIED and k != 'config'):
                fate[n] = 'left out' + (' (dropped)' if n in drop or k in drop else
                                        ' (not the one the agent plays)')
            elif k in NOT_NEEDED:
                fate[n] = 'not needed: ' + NOT_NEEDED[k]
            else:
                fate[n] = None
        stuck = [n for n, f in fate.items() if f is None]
        if stuck:
            raise ValueError(f"{os.path.basename(path)} has {', '.join(stuck)}, which an agent "
                             f"file can't carry: drop it to export without it")
        if marks is None and library and replan:
            log('(the library has no join points: replanning tries the routes from their start '
                'and the rest of the route it is on)')
        model_file = take(model)
        if config in kinds:
            take(config)
        library_file = take(library) if library else None
        if marks:
            take(marks)  # (beside the library, where load_routes finds it)
        chooser_file = take(chooser) if chooser else None
        sources = {'pack': (os.path.basename(path), sha256(path)),
                   'model': (model, digest(model))}
        if library:
            sources['library'] = (library, digest(library))
        if marks:
            sources['marks'] = (marks, digest(marks))
        if chooser:
            sources['chooser'] = (chooser, digest(chooser))
        if version is None:
            version = pack_name(path)
        if name is None:
            stem = os.path.splitext(os.path.basename(model))[0]
            folder = os.path.basename(os.path.dirname(model))
            name = folder if stem in ('avg', 'model', 'best') and folder else stem
        if out_path is None:
            out_path = os.path.join(os.path.dirname(os.path.abspath(path)),
                                    f'{name}-{version}.efzagent' if version else f'{name}.efzagent')
        dropped = sorted(n for n, f in fate.items() if f.startswith('left out'))
        result = export_agent(model_file, out_path, name=name, character=character,
                              check=check, library=library_file,
                              victims=options.get('victims'), replan=replan,
                              per_start=per_start, chooser=chooser_file,
                              margin=float(options.get('margin', CHOOSER_MARGIN)),
                              version=version, sources=sources, dropped=dropped,
                              train=train, optimizer=optimizer)
    for n, f in fate.items():
        log(f'  {n}: {f}')
    return out_path, result, fate


class _Spaces:
    """Only the spaces, for making a model (unpack_agent)."""

    def __new__(cls, width, actions):
        import gymnasium

        class Spaces(gymnasium.Env):
            observation_space = gymnasium.spaces.Box(-np.inf, np.inf, (width,), np.float32)
            action_space = gymnasium.spaces.Discrete(actions)

            def reset(self, seed=None, options=None):
                return np.zeros((width,), np.float32), {}

            def step(self, action):
                return np.zeros((width,), np.float32), 0.0, True, False, {}

        return Spaces()


def _library(keys, tensors):
    """A file's routes as a combo library (combo_library.py's .npz as load_routes and
    macros.load_library read it: (its arrays, its join points)), or None if the file
    doesn't keep their damage (one written before the training part)."""
    from .vec import character_names
    if 'routes.damage' not in tensors:
        return None
    names = character_names()
    table = ActionTable()
    offsets, acts = tensors['routes.offset'], tensors['routes.actions']
    at = tensors.get('routes.marks.offset')
    meta, arrays, marks = [], {}, {}
    for k in range(len(tensors['routes.starter'])):
        opp = int(tensors['routes.opponent'][k])
        meta.append(dict(starter=int(tensors['routes.starter'][k]),
                         opponent=names[opp] if 0 <= opp < len(names) else None,
                         kept_for='victim' if tensors['routes.kept'][k] else 'overall',
                         damage=float(tensors['routes.damage'][k]), prev=0, id=f'route{k}'))
        arrays[f'inputs{k}'] = table.to_bytes(
            acts[offsets[k]:offsets[k + 1]].astype(np.int64)).astype(np.uint8)
        if at is not None and at[k + 1] > at[k]:
            # (the damage before a join point to a tenth of HP, as combo_library.py writes it)
            marks[str(k)] = [[int(a), int(b), round(float(c), 1), int(d)]
                             for a, b, c, d in tensors['routes.marks'][at[k]:at[k + 1]]]
    arrays['meta'] = np.array(json.dumps(meta))
    return arrays, marks


def unpack_agent(path, out_dir, check=True):
    """An agent file as the files it was made from, in out_dir: model.zip (a
    Stable-Baselines3 PPO model: finetune.py --start, evaluate.py, play.py) with its
    config.json, and, if the file has routes and keeps their damage, combo-library.npz
    with its join points (.marks.json) for the tools' --assist. The model is made anew
    from the file's numbers and its JSON, nothing of the file is run or unpickled: a file
    from anyone can be unpacked.

    A file with its training part (export_agent's train) gives the model whole, the critic
    too, and with optimizer=True Adam's moments. One without (written before 15 November,
    or with train=False) has only the actor: the critic is made new (its features the
    actor's), and training from it has to teach the value again first.

    Returns {'model', 'config', 'library' (None without), 'critic' ('file' or 'new'),
    'optimizer' (its moments were in the file), 'policy' (check: the largest difference
    between the model's log-probabilities and the file's as the library runs it)}."""
    import warnings
    import torch as th
    from stable_baselines3 import PPO
    from stable_baselines3.common.policies import ActorCriticPolicy
    from .policy import EfzFeatures, EfzPolicy
    fmt, keys, tensors = read_agent(path)
    width, actions = int(keys['width']), int(keys['actions'])
    sb3 = json.loads(keys['train.sb3']) if 'train.sb3' in keys else {}
    has_train = 'train.value.weight' in tensors
    activation = {'relu': th.nn.ReLU, 'tanh': th.nn.Tanh}[keys['activation']]
    pi = [int(tensors[f'pi.{k}.bias'].shape[0]) for k in range(int(keys['layers']))]
    vf = ([int(tensors[f'train.vf.{k}.bias'].shape[0]) for k in range(int(sb3['vf_layers']))]
          if has_train else list(pi))
    kwargs = dict(net_arch=dict(pi=pi, vf=vf), activation_fn=activation)
    efz = keys['features'] == 'efz'
    if efz:
        shared = bool(sb3.get('share_features_extractor', False))
        kwargs.update(features_extractor_class=EfzFeatures,
                      features_extractor_kwargs=dict(
                          action_embed=int(tensors['features.action'].shape[1]),
                          char_embed=int(tensors['features.char'].shape[1])),
                      share_features_extractor=shared,
                      ortho_init=bool(sb3.get('ortho_init', False)))
    elif keys['features'] != 'flat':
        raise ValueError(f"{path}: features {keys['features']!r}: efz or flat")
    else:
        shared = bool(sb3.get('share_features_extractor', True))
        kwargs.update(share_features_extractor=shared, ortho_init=bool(sb3.get('ortho_init', True)))
    if sb3.get('optimizer_kwargs'):
        kwargs['optimizer_kwargs'] = {k: float(v) for k, v in sb3['optimizer_kwargs'].items()}
    classes = {'EfzPolicy': EfzPolicy, 'ActorCriticPolicy': ActorCriticPolicy}
    policy_class = classes.get(sb3.get('policy'), EfzPolicy if efz else ActorCriticPolicy)
    hyper = {k: sb3[k] for k in HYPER + ('learning_rate', 'clip_range') if k in sb3}
    hyper.setdefault('n_steps', 64)
    hyper.setdefault('batch_size', 64)
    with warnings.catch_warnings():
        warnings.simplefilter('ignore')
        model = PPO(policy_class, _Spaces(width, actions), policy_kwargs=kwargs, device='cpu',
                    **hyper)
    policy = model.policy
    state = policy.state_dict()

    def put(name, array):
        if name not in state or tuple(state[name].shape) != tuple(array.shape):
            raise ValueError(f'{path}: {name} is {tuple(array.shape)}, the model\'s '
                             f'{tuple(state[name].shape) if name in state else "nothing"}')
        state[name] = th.as_tensor(np.asarray(array, np.float32))

    def put_features(prefix, source):
        if not efz:
            return
        cont = tensors[source + 'cont'].astype(np.int64)
        mine = getattr(policy, prefix).cont.cpu().numpy()
        if len(cont) != len(mine) or (cont != mine).any():
            raise ValueError(f"{path}: its features' columns are not this library's "
                             '(efz_env.policy.continuous_columns)')
        for a, b in (('mean', 'mean'), ('scale', 'scale'), ('action', 'action.weight'),
                     ('own_action', 'own_action.weight'), ('char', 'char.weight')):
            put(f'{prefix}.{b}', tensors[source + a])

    for prefix in ('features_extractor', 'pi_features_extractor'):
        put_features(prefix, 'features.')
    # (unshared: the critic's own, the file's or, without a training part, the actor's)
    if not shared:
        put_features('vf_features_extractor',
                     'train.vf.features.' if has_train else 'features.')
    linear = lambda net: [k for k, m in enumerate(net) if isinstance(m, th.nn.Linear)]
    for k, j in enumerate(linear(policy.mlp_extractor.policy_net)):
        put(f'mlp_extractor.policy_net.{j}.weight', tensors[f'pi.{k}.weight'])
        put(f'mlp_extractor.policy_net.{j}.bias', tensors[f'pi.{k}.bias'])
    put('action_net.weight', tensors['action.weight'])
    put('action_net.bias', tensors['action.bias'])
    if has_train:
        for k, j in enumerate(linear(policy.mlp_extractor.value_net)):
            put(f'mlp_extractor.value_net.{j}.weight', tensors[f'train.vf.{k}.weight'])
            put(f'mlp_extractor.value_net.{j}.bias', tensors[f'train.vf.{k}.bias'])
        put('value_net.weight', tensors['train.value.weight'])
        put('value_net.bias', tensors['train.value.bias'])
    policy.load_state_dict(state)
    model.num_timesteps = int(sb3.get('num_timesteps', 0))
    params = list(policy.parameters())
    adam = 'adam_step' in sb3 and all(f'train.adam.{j}.m' in tensors for j in range(len(params)))
    if adam:
        opt = policy.optimizer.state_dict()
        opt['state'] = {}
        for j, prm in enumerate(params):
            m, v = tensors[f'train.adam.{j}.m'], tensors[f'train.adam.{j}.v']
            if tuple(m.shape) != tuple(prm.shape):
                raise ValueError(f"{path}: the optimizer's moments don't fit the model")
            opt['state'][j] = dict(step=th.tensor(float(sb3['adam_step'])),
                                   exp_avg=th.as_tensor(m), exp_avg_sq=th.as_tensor(v))
        policy.optimizer.load_state_dict(opt)
    os.makedirs(out_dir, exist_ok=True)
    model_path = os.path.join(out_dir, 'model.zip')
    model.save(model_path)
    cfg = json.loads(keys['train.config']) if 'train.config' in keys else {}
    for k in ('frame_skip', 'history', 'delay'):
        cfg[k] = int(keys[k])
    if 'chars' not in cfg:
        from .vec import character_names
        c, names = int(keys.get('character', -1)), character_names()
        cfg['chars'] = [names[c] if 0 <= c < len(names) else None, None]
    config_path = os.path.join(out_dir, 'config.json')
    with open(config_path, 'w') as f:
        json.dump(cfg, f, indent=1)
    library_path = None
    lib = _library(keys, tensors) if 'routes.starter' in tensors else None
    if lib is not None:
        library_path = os.path.join(out_dir, 'combo-library.npz')
        np.savez_compressed(library_path, **lib[0])
        with open(marks_path(library_path), 'w') as f:
            json.dump(lib[1], f)
    with open(os.path.join(out_dir, 'packed.json'), 'w') as f:
        json.dump(dict(file=os.path.basename(os.fspath(path)), sha256=sha256(path),
                       format=fmt, modules=keys.get('modules', ''), name=keys.get('name', ''),
                       version=keys.get('version', ''), critic='file' if has_train else 'new',
                       optimizer=bool(adam),
                       routes=dict(per_start=int(keys.get('route_per_start', 0) or 0),
                                   replan=bool(int(keys.get('route_replan', 0) or 0)),
                                   victims=keys.get('route_victims', ''))
                       if 'routes.starter' in tensors else None), f, indent=1)
    result = dict(model=model_path, config=config_path, library=library_path,
                  critic='file' if has_train else 'new', optimizer=bool(adam), policy=None)
    if check:
        views = sample_views(width)
        native = NativeAgent(path)
        try:
            result['policy'] = float(np.abs(native.log_probs(views) -
                                            torch_log_probs(policy, views)).max())
        finally:
            native.close()
    return result


_UNPACKED = {}  # agent file (its path, size, time) -> its model, unpacked for this process


def unpacked_model(path):
    """The model.zip of the agent file `path`, unpacked (once a process, into a folder
    that goes with it): what efz_env.agent.Agent loads where it is given an agent file."""
    import atexit
    import shutil
    path = os.path.abspath(path)
    st = os.stat(path)
    key = (path, st.st_size, st.st_mtime_ns)
    if key not in _UNPACKED:
        folder = tempfile.mkdtemp(prefix='efzagent-')
        atexit.register(shutil.rmtree, folder, ignore_errors=True)
        _UNPACKED[key] = unpack_agent(path, folder, check=False)['model']
    return _UNPACKED[key]


def read_header(path):
    """An agent file's format and its header's keys (no machine learning needed), and its
    tensors' names and shapes."""
    with open(path, 'rb') as f:
        data = f.read()
    if data[:8] != MAGIC:
        raise ValueError(f'{path}: not an agent file')
    fmt, size = struct.unpack_from('<II', data, 8)
    text = data[16:16 + size].decode('utf-8', errors='replace')
    keys = {}
    for line in text.split('\n'):
        if '=' in line:
            k, v = line.split('=', 1)
            keys[k] = v
    at = 16 + size
    (count,) = struct.unpack_from('<I', data, at)
    at += 4
    tensors = {}
    for _ in range(count):
        (n,) = struct.unpack_from('<H', data, at)
        tname = data[at + 2:at + 2 + n].decode()
        at += 2 + n
        kind, ndim = struct.unpack_from('<BB', data, at)
        at += 2
        dims = struct.unpack_from(f'<{ndim}I', data, at)
        at += 4 * ndim
        at += int(np.prod(dims, dtype=np.int64)) * (1 if kind == 2 else 4)
        tensors[tname] = tuple(dims)
    return fmt, keys, tensors


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
        self.routes, self.pool = info.routes, info.pool
        self.replan, self.chooser = bool(info.replan), bool(info.chooser)
        self.format = info.format
        self.version = info.version.decode(errors='replace')
        self.modules = info.modules.decode(errors='replace')
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

    def plan(self, env, index, side, starter, actions, history, prev, deterministic=True,
             seed=0, late=0, extra=None):
        """One plan of its routes as the game makes it at its hit (port/agent/routes.h),
        on EfzVecEnv `env`'s game `index` as it is (left as it was): player `side` plays
        `actions` (its inputs until it sees the hit), the opponent holding back, then the
        routes of `starter` and its own play are tried on copies. history (history, 6) and
        prev: its input history after those actions. late: the steps since the hit (the
        routes played that much further in); extra: one more option, actions from where
        `actions` leave the game (the rest of the route being played, at a replan). A dict:
        outcome ('planned', 'own': not this opponent, 'apart'), tried (the options: (a
        route's index, the step it is joined at), then ('extra', 0) and ('own', 0)), chosen
        (an index into tried, or None for its own play), dealt (each one's most), expected
        (its view once it sees the hit), frames, ms."""
        env._finish()
        acts = np.ascontiguousarray(actions, np.int32)
        hist = np.ascontiguousarray(history, np.float32).reshape(-1)
        more = np.ascontiguousarray(extra if extra is not None else [], np.int32)
        out = _native.Plan()
        r = self._lib.efz_env_agent_plan(self._h, env._h, int(index), int(side), int(starter),
                                         acts.ctypes.data, len(acts), hist.ctypes.data,
                                         int(prev), int(bool(deterministic)), int(seed),
                                         int(late), more.ctypes.data, len(more),
                                         ctypes.byref(out))
        if r != 0:
            raise ValueError(f'efz_env_agent_plan: {self._lib.efz_env_error(env._h).decode()}')
        n = out.options
        names = {-1: 'own', -2: 'extra'}
        tried = [(names.get(r, int(r)), int(a)) for r, a in zip(out.route[:n], out.at[:n])]
        return dict(outcome={1: 'planned', 2: 'own', 3: 'apart'}.get(out.outcome, 'none'),
                    chosen=None if out.chosen < 0 else int(out.chosen), tried=tried,
                    dealt=np.array(out.dealt[:n], np.float32),
                    expected=np.array(out.expected, np.float32), frames=out.frames, ms=out.ms)

    def choose(self, view, starter, offset):
        """Its chooser's pick for `view` (its network's input: a view, then its input
        history; on the step it sees its hit of `starter`), its routes played from
        `offset`: (a route's index, or None for its own play; what it says each route and
        its own play, the last, would deal, in HP)."""
        if not self.chooser:
            raise ValueError(f'{self.path}: no chooser')
        v = np.ascontiguousarray(view, np.float32).reshape(-1)
        if len(v) != self.width:
            raise ValueError(f'choose: a view of {self.width} numbers, not {len(v)}')
        values = np.empty(self.routes + 1, np.float32)
        r = self._lib.efz_env_agent_choose(self._h, v.ctypes.data, int(starter), int(offset),
                                           values.ctypes.data)
        return (None if r < 0 else int(r)), values

    def close(self):
        if getattr(self, '_h', None):
            self._lib.efz_env_agent_free(self._h)
            self._h = None

    def __del__(self):
        self.close()
