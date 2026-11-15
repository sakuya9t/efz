"""Agent files (efz_env.export, port/agent/policy.h): a model written as one plays as the
model does, run by the library as the game runs it; its modules and where they came from
are in its header, and a module the library doesn't play is refused by name; a chooser in
it says what the chooser does; a pack goes in whole, each of its files accounted for; its
routes are planned as runs/human-ayu/redteam.py's planner plans them (port/agent/routes.h),
replanning as round 15b's does. Needs the efz_env library and stable-baselines3; the
matches played need the game's data ($EFZ_DATA) too."""

import json
import os
import sys
import tempfile
import unittest

try:
    import numpy as np
    import gymnasium
    import stable_baselines3  # noqa: F401
    import torch as th
except ImportError:
    raise unittest.SkipTest('needs numpy, gymnasium, stable-baselines3 and torch')

import struct
import zipfile

from efz_env.export import (NativeAgent, export_agent, export_pack, read_header, sample_views,
                            sha256, torch_log_probs)

DATA = os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
OBS_DIM = 168


class Spaces(gymnasium.Env):
    """Only the spaces, for making a model to export."""

    def __init__(self, width):
        self.observation_space = gymnasium.spaces.Box(-np.inf, np.inf, (width,), np.float32)
        self.action_space = gymnasium.spaces.Discrete(45)

    def reset(self, seed=None, options=None):
        return np.zeros(self.observation_space.shape, np.float32), {}

    def step(self, action):
        return np.zeros(self.observation_space.shape, np.float32), 0.0, True, False, {}


def make_model(folder, efz=True, history=2, delay=3, frame_skip=1, seed=0):
    """A model of random weights, saved with its config.json; its path."""
    from stable_baselines3 import PPO
    from efz_env.policy import EfzPolicy, policy_kwargs
    th.manual_seed(seed)
    width = OBS_DIM + 6 * history
    if efz:
        model = PPO(EfzPolicy, Spaces(width), policy_kwargs=policy_kwargs(width=64), device='cpu',
                    n_steps=64, batch_size=64)
        rng = np.random.default_rng(seed)
        model.policy.set_scale(rng.normal(size=width), rng.uniform(0.5, 2, width))
        with th.no_grad():  # embeddings that matter
            for p in model.policy.parameters():
                p.add_(th.randn_like(p) * 0.3)
    else:  # SB3's MlpPolicy: tanh, no embeddings
        model = PPO('MlpPolicy', Spaces(width), device='cpu', n_steps=64, batch_size=64,
                    policy_kwargs=dict(net_arch=dict(pi=[32, 32], vf=[32, 32])))
    path = os.path.join(folder, 'model.zip')
    model.save(path)
    with open(os.path.join(folder, 'config.json'), 'w') as f:
        json.dump(dict(frame_skip=frame_skip, history=history, delay=delay,
                       chars=['ayu', None]), f)
    return path, model


class Export(unittest.TestCase):
    def check(self, efz):
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder, efz=efz)
            out = os.path.join(folder, 'agent.efzagent')
            check = export_agent(path, out)
            self.assertLess(check['policy'], 1e-4)
            self.assertIsNone(check['chooser'])
            agent = NativeAgent(out)
            self.assertEqual((agent.format, agent.modules), (2, 'policy:1'))
            self.assertEqual((agent.width, agent.actions), (OBS_DIM + 12, 45))
            self.assertEqual((agent.frame_skip, agent.history, agent.delay), (1, 2, 3))
            self.assertEqual(agent.character, 1)  # ayu
            self.assertEqual(agent.name, os.path.basename(folder))
            views = sample_views(agent.width, 64, seed=5)
            np.testing.assert_allclose(agent.log_probs(views), torch_log_probs(model.policy, views),
                                       atol=1e-4)
            agent.close()

    def test_efz_policy(self):
        self.check(True)

    def test_mlp_policy(self):
        self.check(False)

    def test_refuses_what_isnt_one(self):
        with tempfile.TemporaryDirectory() as folder:
            path = os.path.join(folder, 'x.efzagent')
            with open(path, 'wb') as f:
                f.write(b'not an agent')
            with self.assertRaisesRegex(RuntimeError, 'not an agent file'):
                NativeAgent(path)


def rewrite(path, fmt=None, keys=None):
    """An agent file's format and header keys changed (keys: {key: value, None to drop})."""
    with open(path, 'rb') as f:
        data = f.read()
    old_fmt, size = struct.unpack_from('<II', data, 8)
    lines = [l for l in data[16:16 + size].decode().split('\n') if l]
    kv = dict(l.split('=', 1) for l in lines)
    for k, v in (keys or {}).items():
        if v is None:
            kv.pop(k, None)
        else:
            kv[k] = v
    text = ''.join(f'{k}={v}\n' for k, v in kv.items()).encode()
    with open(path, 'wb') as f:
        f.write(data[:8] + struct.pack('<II', old_fmt if fmt is None else fmt, len(text)) + text +
                data[16 + size:])


def random_routes(rng, starters, per=16, delay=5, victims=('mai', 'akane'), marks_to=()):
    """Routes of random actions for the starters (and some for none of them), each with a
    damage and join points (at random steps, of the moves in marks_to); half landed on
    the first victim, kept for it, half on the second."""
    library = []
    for starter in list(starters) + [9999]:
        for k in range(per):
            n = int(rng.integers(delay + 1, 160))
            acts = np.where(rng.random(n) < 0.6, rng.integers(0, 45, n), 0)
            marks = [[0, int(starter), 0.0, 0]]
            for move in marks_to:
                if rng.random() < 0.5 and n > 8:
                    marks.append([int(rng.integers(2, n - 1)), int(move),
                                  float(rng.integers(0, 2000)) / 10, int(rng.integers(1, 5))])
            marks = [marks[0]] + sorted(marks[1:])
            library.append(dict(starter=starter, actions=acts.astype(np.int64),
                                opponent=victims[k % 2], damage=float(rng.integers(100, 4000)),
                                kept_for='victim' if k % 3 else 'overall', marks=marks))
    return library


def fake_chooser(model, routes, path, seed=0, hidden=16):
    """A chooser.pt as combo_net.py train-chooser saves one: a copy of the agent's features
    (changed a little) and a head of random weights, for `routes` combos."""
    import copy
    th.manual_seed(seed)
    ext = copy.deepcopy(model.policy.pi_features_extractor)
    with th.no_grad():
        for p in ext.parameters():
            p.add_(th.randn_like(p) * 0.1)
    dim = ext.features_dim
    head = th.nn.Sequential(th.nn.Linear(dim, hidden), th.nn.ReLU(), th.nn.Linear(hidden, hidden),
                            th.nn.ReLU(), th.nn.Linear(hidden, len(routes) + 1))
    with th.no_grad():
        head[4].weight.mul_(3)
    state = {f'features.{k}': v for k, v in ext.state_dict().items()}
    state.update({f'head.{k}': v for k, v in head.state_dict().items()})
    th.save(dict(routes=len(routes), hidden=hidden, state=state), path)

    def values(views):
        with th.no_grad():
            return head(ext(th.as_tensor(np.asarray(views, np.float32)))).numpy() * 1000
    return values


class FileFormat(unittest.TestCase):
    def test_header(self):
        # What it is made of and where it came from.
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, version='v7', check=False)
            fmt, keys, tensors = read_header(out)
            self.assertEqual(fmt, 2)
            self.assertEqual(keys['modules'], 'policy:1')
            self.assertEqual(keys['version'], 'v7')
            self.assertEqual(keys['source.model'], f'model.zip sha256:{sha256(path)}')
            self.assertTrue(keys['exporter'].startswith('efz_env.export'))
            self.assertIn('action.weight', tensors)
            agent = NativeAgent(out)
            self.assertEqual(agent.version, 'v7')
            agent.close()

    def test_format_1_read_and_modules_checked(self):
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            rewrite(out, fmt=1, keys={'modules': None})
            agent = NativeAgent(out)
            self.assertEqual((agent.format, agent.modules), (1, 'policy:1'))
            agent.close()
            rewrite(out, fmt=2, keys={'modules': 'policy:1,oki:1'})
            with self.assertRaisesRegex(RuntimeError, 'oki:1.*a newer game'):
                NativeAgent(out)
            rewrite(out, keys={'modules': 'policy:2'})
            with self.assertRaisesRegex(RuntimeError, 'policy:2'):
                NativeAgent(out)
            rewrite(out, fmt=3, keys={'modules': 'policy:1'})
            with self.assertRaisesRegex(RuntimeError, 'format 3'):
                NativeAgent(out)


class Chooser(unittest.TestCase):
    """A chooser in the file: what it says is the chooser's, and its pick combo_net.py's
    NetPlanner's (the routes of the starter, those long enough from the offset, the first
    per_start; the one it says deals the most, if 200 HP more than its own play)."""

    def test_same_values_and_picks(self):
        rng = np.random.default_rng(3)
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder, history=4, delay=5, seed=1)
            routes = random_routes(rng, [3, 7, 11], per=20)
            chooser = os.path.join(folder, 'chooser.pt')
            values = fake_chooser(model, routes, chooser)
            out = os.path.join(folder, 'agent.efzagent')
            check = export_agent(path, out, library=routes, chooser=chooser)
            self.assertLess(check['chooser'], 0.05)
            agent = NativeAgent(out)
            self.assertTrue(agent.chooser)
            self.assertEqual(agent.modules, 'policy:1,routes:1,chooser:1')
            from efz_env.vec import character_names
            names = character_names()
            views = sample_views(agent.width, 200, seed=8)
            views[:, 66] = rng.choice([names.index('mai'), names.index('akane'), 3], len(views))
            theirs = values(views)
            picks = 0
            for v, want in zip(views, theirs):
                starter = int(rng.choice([3, 7, 11, 5]))
                offset = int(rng.integers(0, 40))
                got, said = agent.choose(v, starter, offset)
                np.testing.assert_allclose(said, want, atol=0.05)
                # (kept per victim: those landed on the opponent it sees first)
                victim = names[int(round(float(v[66])))]
                order = [k for k, m in enumerate(routes) if m['starter'] == starter]
                order = ([k for k in order if routes[k]['opponent'] == victim] +
                         [k for k in order if routes[k]['opponent'] != victim])
                pool = [k for k in order if len(routes[k]['actions']) > offset][:12]
                best = max(pool, key=lambda k: (said[k], -k)) if pool else None
                expect = best if best is not None and said[best] > said[-1] + 200 else None
                self.assertEqual(got, expect)
                picks += got is not None
            self.assertGreater(picks, 10)
            agent.close()

    def test_refuses_another_librarys(self):
        rng = np.random.default_rng(4)
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder, history=4, delay=5, seed=1)
            routes = random_routes(rng, [3], per=8)
            chooser = os.path.join(folder, 'chooser.pt')
            fake_chooser(model, routes[:-1], chooser)
            with self.assertRaisesRegex(ValueError, 'library'):
                export_agent(path, os.path.join(folder, 'a.efzagent'), library=routes,
                             chooser=chooser)


def write_library(path, rng, starters, per=10):
    """A combo library as combo_library.py writes one (meta, inputs{k}: control bytes),
    with its join points beside it; the combos as load_routes reads them."""
    from efz_env.export import load_routes
    meta, arrays, marks = [], {}, {}
    k = 0
    for starter in starters:
        for j in range(per):
            n = int(rng.integers(10, 90))
            arrays[f'inputs{k}'] = rng.choice([0, 0x01, 0x02, 0x10, 0x20, 0x40], n).astype(np.uint8)
            meta.append(dict(starter=int(starter), damage=float(rng.integers(100, 3000)), prev=0,
                             opponent='mai' if j % 2 else 'akane', kept_for='overall',
                             id=k, side=0, start=0, end=n))
            marks[str(k)] = [[0, int(starter), 0.0, 0]] + (
                [[int(rng.integers(3, n - 1)), int(rng.choice(starters)), 150.0, 2]] if j % 2 else [])
            k += 1
    np.savez(path, meta=json.dumps(meta), **arrays)
    with open(os.path.splitext(path)[0] + '.marks.json', 'w') as f:
        json.dump(marks, f)
    return load_routes(path)


class Pack(unittest.TestCase):
    """A pack in one file: its model, library, join points and chooser carried; its code,
    notes, launcher and the chooser's training record not needed; anything else stops the
    export unless dropped; where each part came from recorded."""

    def make(self, folder, extra=()):
        rng = np.random.default_rng(6)
        root = os.path.join(folder, 'src', 'tmp', 'round9')
        os.makedirs(os.path.join(root, 'agent-x'))
        path, model = make_model(os.path.join(root, 'agent-x'), history=4, delay=5, seed=2)
        os.rename(path, os.path.join(root, 'agent-x', 'avg.zip'))
        routes = write_library(os.path.join(root, 'lib.npz'), rng, [3, 7])
        os.makedirs(os.path.join(root, 'chooser9'))
        fake_chooser(model, routes, os.path.join(root, 'chooser9', 'chooser.pt'))
        files = {'tmp/round9/chooser9/combo_net.json': '{}', 'tmp/round9/README.md': 'notes',
                 'tmp/round9/play.sh': '#!/bin/sh', 'runs/human-ayu/combo_support.py': '#'}
        files.update(extra)
        pack = os.path.join(folder, 'efz-round9-pack.zip')
        with zipfile.ZipFile(pack, 'w') as z:
            for base, _, names in os.walk(os.path.join(folder, 'src')):
                for n in names:
                    full = os.path.join(base, n)
                    z.write(full, os.path.relpath(full, os.path.join(folder, 'src')).replace(os.sep, '/'))
            for n, text in files.items():
                z.writestr(n, text)
        return pack, routes

    def test_all_of_it(self):
        with tempfile.TemporaryDirectory() as folder:
            pack, routes = self.make(folder)
            out, check, fate = export_pack(pack, log=lambda *a: None)
            self.assertEqual(os.path.basename(out), 'agent-x-round9.efzagent')
            self.assertLess(check['policy'], 1e-4)
            self.assertLess(check['chooser'], 0.05)
            self.assertEqual(check['routes'], len(routes))
            self.assertGreater(check['pool'], len(routes))  # joined at their marks
            self.assertTrue(fate['tmp/round9/lib.marks.json'].startswith('in the file'))
            self.assertTrue(fate['tmp/round9/chooser9/chooser.pt'].startswith('in the file'))
            self.assertTrue(fate['runs/human-ayu/combo_support.py'].startswith('not needed'))
            _, keys, _ = read_header(out)
            self.assertEqual(keys['modules'], 'policy:1,routes:1,chooser:1')
            self.assertEqual(keys['version'], 'round9')
            self.assertEqual((keys['route_replan'], keys['route_per_start']), ('1', '24'))
            self.assertEqual(keys['source.pack'], f'efz-round9-pack.zip sha256:{sha256(pack)}')
            with zipfile.ZipFile(pack) as z:
                self.assertEqual(keys['source.chooser'], 'tmp/round9/chooser9/chooser.pt sha256:' +
                                 sha256(z.read('tmp/round9/chooser9/chooser.pt')))
            agent = NativeAgent(out)
            self.assertEqual((agent.replan, agent.chooser, agent.version), (True, True, 'round9'))
            agent.close()
            # Without its join points: planned once, as round 15's packs.
            out, _, _ = export_pack(pack, os.path.join(folder, 'once.efzagent'), drop=['marks'],
                                    check=False, log=lambda *a: None)
            _, keys, _ = read_header(out)
            self.assertEqual((keys['route_replan'], keys['route_per_start']), ('0', '12'))
            self.assertIn('marks', keys['dropped'])
            out, _, _ = export_pack(pack, os.path.join(folder, 'plain.efzagent'), drop=['routes'],
                                    check=False, log=lambda *a: None)
            self.assertEqual(read_header(out)[1]['modules'], 'policy:1')

    def test_its_manifest(self):
        # An agent.json (efz_env.modules's) says how it plays; a module of another kind
        # stops the export unless dropped, its files with it.
        with tempfile.TemporaryDirectory() as folder:
            manifest = dict(format=1, model='agent-x/avg.zip', modules=[
                dict(kind='routes', code='combo_support',
                     files=dict(library='lib.npz', chooser='chooser9/chooser.pt'),
                     options=dict(replan=False, per_start=10)),
                dict(kind='oki', code='okizeme', files=dict(model='bc.zip'), options={})])
            pack, _ = self.make(folder, extra={'tmp/round9/agent.json': json.dumps(manifest),
                                               'tmp/round9/bc.zip': 'x'})
            with self.assertRaisesRegex(ValueError, "'oki'"):
                export_pack(pack, check=False, log=lambda *a: None)
            out, _, fate = export_pack(pack, drop=['oki'], check=False, log=lambda *a: None)
            self.assertEqual(fate['tmp/round9/bc.zip'], 'left out (dropped)')
            self.assertTrue(fate['tmp/round9/agent.json'].startswith('not needed'))
            _, keys, _ = read_header(out)
            self.assertEqual(keys['modules'], 'policy:1,routes:1,chooser:1')
            self.assertEqual((keys['route_replan'], keys['route_per_start']), ('0', '10'))

    def test_what_it_cant_carry(self):
        with tempfile.TemporaryDirectory() as folder:
            pack, _ = self.make(folder, extra={'tmp/round9/okizeme.bin': 'x'})
            with self.assertRaisesRegex(ValueError, 'okizeme.bin'):
                export_pack(pack, check=False, log=lambda *a: None)
            out, _, fate = export_pack(pack, drop=['tmp/round9/okizeme.bin'], check=False,
                                       log=lambda *a: None)
            self.assertEqual(fate['tmp/round9/okizeme.bin'], 'left out (dropped)')
            self.assertIn('okizeme.bin', read_header(out)[1]['dropped'])


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class PlaysAsTheModel(unittest.TestCase):
    def play(self, frame_skip):
        # The exported agent beside efz_env.agent.Agent, both choosing their likeliest
        # action, on the views of a match against the CPU that the exported one plays,
        # stepped as play.py's HumanMatch steps an agent: the same decisions.
        from efz_env import EfzVecEnv
        from efz_env.agent import Agent
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=4, delay=5, frame_skip=frame_skip, seed=2)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            native = NativeAgent(out, deterministic=True)
            agent = Agent(path, deterministic=True)
            env = EfzVecEnv(DATA, 1, num_threads=1, frame_skip=1, skip_noninteractive=False,
                            autoreset='disabled', max_frames=0)
            env.set_matches(chars=('ayu', 'mai'), stage=0, cpu=(False, True))
            names = env.observation_names
            intro, over = names.index('intro'), names.index('round_over')
            env.reset(seed=1)
            native.reset()
            agent.reset()
            controls = np.zeros((1, 2), np.uint8)
            held, decisions = 0, 0
            for _ in range(1500):
                obs = env.obs[0, 0].copy()
                actionable = obs[intro] == 0 and obs[over] == 0
                controls[0, 0] = native.step(obs, actionable)
                if held == 0 and actionable:
                    self.assertEqual(native.last_action, agent(obs))
                    held, decisions = frame_skip, decisions + 1
                held = max(0, held - 1)
                _, _, term, trunc, _ = env.step(controls)
                if term[0] or trunc[0]:
                    break
            self.assertGreater(decisions, 1500 // frame_skip // 2)
            env.close()
            native.close()

    def test_every_frame(self):
        self.play(1)

    def test_frame_skip(self):
        self.play(3)


RUNS = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__)))),
                    'runs', 'human-ayu')


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class PlansAsRedteam(unittest.TestCase):
    """At each hit of a match, the game's planner (efz_env_agent_plan) and redteam.py's, as
    combo_support.py's _live_worker runs it for play.py --assist, on the same game: the
    same routes tried, the same damage from each, the same choice, the same view expected;
    and the game left as it was."""

    HISTORY, DELAY = 4, 5

    def script(self, f):
        return 0x10 if f % 7 == 0 else 0x01  # forward, and A now and then

    def hits(self, env, frames=2400, again=False):
        """The match played by the script: at each of player 1's hits (its combo counter
        from 0; again: also each new move's hit in a combo), the frame, the state, the
        starter, its input history and whether it is a combo's first."""
        from efz_env.history import InputHistory
        env.reset(seed=4)
        hist = InputHistory((1,), self.HISTORY)
        controls = np.zeros((1, 2), np.uint8)
        out, prev_hits, planned = [], 0, None
        for f in range(frames):
            obs = env.obs[0, 0].copy()
            hits = int(round(float(obs[30]) * 30))
            move = int(round(float(obs[18])))
            if hits == 0:
                planned = None
            if (hits > 0 and prev_hits == 0) or (again and hits > prev_hits and move != planned):
                out.append(dict(frame=f, state=env.save_state(0), starter=move,
                                hist=hist.buf[0].copy(), prev=int(hist.prev[0]), obs=obs,
                                first=prev_hits == 0))
                planned = move
            prev_hits = hits
            controls[0, 0] = self.script(f)
            hist.push(controls[:, 0])
            _, _, term, trunc, _ = env.step(controls)
            if term[0] or trunc[0]:
                break
        return out

    def test_same_plans(self):
        sys.path.insert(0, RUNS)
        try:
            import redteam
            from combo_support import sampler
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        from stable_baselines3 import PPO
        from efz_env import ActionTable, EfzVecEnv
        from efz_env.actions import BACK
        from efz_env.history import InputHistory
        table = ActionTable().table
        env = EfzVecEnv(DATA, 1, num_threads=1, frame_skip=1, skip_noninteractive=False,
                        autoreset='disabled', max_frames=0)
        env.set_matches(chars=('ayu', 'mai'), stage=0, cpu=(False, False))
        hits = self.hits(env)
        self.assertGreater(len(hits), 2)
        # A library of random routes for the starters seen, and some for none of them; half
        # landed on mai, kept for that victim (theirs first), half on akane.
        rng = np.random.default_rng(9)
        library = []
        for starter in sorted({h['starter'] for h in hits}) + [9999]:
            for k in range(16):
                n = int(rng.integers(self.DELAY + 1, 160))
                acts = np.where(rng.random(n) < 0.6, rng.integers(0, 45, n), 0)
                library.append(dict(starter=starter, actions=acts.astype(np.int64),
                                    opponent='mai' if k % 2 else 'akane',
                                    kept_for='victim' if k % 3 else 'overall'))
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False, library=library)
            native = NativeAgent(out, deterministic=True)
            self.assertEqual(native.routes, len(library))
            model = PPO.load(path, device='cpu')
            planner = redteam.Planner(DATA, library, model, per_start=12, history=self.HISTORY)
            policy = sampler(model, deterministic=True)
            sim = planner.sim
            pre = np.zeros((sim.num_envs, 2), np.uint8)
            index = {id(m): i for i, m in enumerate(library)}
            compared = routes_chosen = 0
            for h in hits[:8]:
                env.load_state(0, h['state'])
                actions = rng.integers(0, 45, self.DELAY)
                hist = InputHistory((1,), self.HISTORY)
                hist.buf[0], hist.prev[0] = h['hist'], h['prev']
                for a in actions:
                    hist.push(table[np.array([a])])
                mine = native.plan(env, 0, 0, h['starter'], actions, hist.buf[0], int(hist.prev[0]))
                self.assertEqual(env.save_state(0), h['state'])  # the game as it was
                # _live_worker's steps, then the planner's.
                sim.load_state(0, h['state'])
                seen = [sim.obs[0, 0].copy()]
                for a in actions:
                    pre[0, 0], pre[0, 1] = table[a], BACK
                    seen.insert(0, sim.step(pre)[0][0, 0].copy())
                chosen, best, own = planner.plan(sim.save_state(0), 0, h['starter'],
                                                 hist.buf[0].copy(), int(hist.prev[0]),
                                                 offset=self.DELAY, seen=np.stack(seen),
                                                 policy=policy)
                theirs = planner.last
                self.assertEqual(mine['outcome'], 'planned')
                self.assertEqual(mine['tried'],
                                 [(index[id(m)], 0) for m in theirs['picked']] + [('own', 0)])
                np.testing.assert_array_equal(mine['dealt'], theirs['dealt'].astype(np.float32))
                np.testing.assert_array_equal(mine['expected'][1:], seen[0][1:])
                want = None if chosen is None else next(
                    j for j, m in enumerate(theirs['picked'])
                    if np.array_equal(m['actions'][self.DELAY:], chosen))
                self.assertEqual(mine['chosen'], want)
                compared += 1
                routes_chosen += want is not None
            self.assertGreater(compared, 2)
            native.close()
        env.close()

    def test_same_replans(self):
        """Round 15b's planner, planning again at each new move's hit: the routes joined
        where that move hit in them (their marks), the rest of the route it is on one more
        option (extra), a plan made late (the routes that much further in)."""
        import inspect
        sys.path.insert(0, RUNS)
        try:
            import redteam
            from combo_support import sampler
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        if 'replan' not in inspect.signature(redteam.Planner).parameters:
            self.skipTest("runs/human-ayu's redteam.py plans once (round 15b's replanning isn't "
                          "in this checkout)")
        from stable_baselines3 import PPO
        from efz_env import ActionTable, EfzVecEnv
        from efz_env.actions import BACK
        from efz_env.export import replan_pool
        from efz_env.history import InputHistory
        table = ActionTable().table
        env = EfzVecEnv(DATA, 1, num_threads=1, frame_skip=1, skip_noninteractive=False,
                        autoreset='disabled', max_frames=0)
        env.set_matches(chars=('ayu', 'mai'), stage=0, cpu=(False, False))
        hits = self.hits(env, again=True)
        starters = sorted({h['starter'] for h in hits})
        rng = np.random.default_rng(11)
        library = random_routes(rng, starters, per=12, delay=self.DELAY, marks_to=starters)
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False, library=library, replan=True)
            native = NativeAgent(out, deterministic=True)
            model = PPO.load(path, device='cpu')
            planner = redteam.Planner(DATA, library, model, per_start=24, history=self.HISTORY,
                                      replan=True)
            mine_pool = replan_pool(library)
            self.assertEqual(native.pool, sum(len(v) for v in mine_pool.values()))
            for starter, entries in planner.by_starter.items():
                self.assertEqual([(m['actions'].tobytes(), m.get('joined', 0)) for m in entries],
                                 [(library[k]['actions'][at:].tobytes(), at)
                                  for k, at, _ in mine_pool[starter]])
            policy = sampler(model, deterministic=True)
            sim = planner.sim
            pre = np.zeros((sim.num_envs, 2), np.uint8)
            compared = 0
            for n, h in enumerate(hits[:12]):
                late = 2 if n % 3 == 2 else 0
                extra = None if h['first'] else rng.integers(0, 45, int(rng.integers(10, 80)))
                env.load_state(0, h['state'])
                actions = rng.integers(0, 45, self.DELAY)
                hist = InputHistory((1,), self.HISTORY)
                hist.buf[0], hist.prev[0] = h['hist'], h['prev']
                for a in actions:
                    hist.push(table[np.array([a])])
                mine = native.plan(env, 0, 0, h['starter'], actions, hist.buf[0],
                                   int(hist.prev[0]), late=late, extra=extra)
                sim.load_state(0, h['state'])
                seen = [sim.obs[0, 0].copy()]
                for a in actions:
                    pre[0, 0], pre[0, 1] = table[a], BACK
                    seen.insert(0, sim.step(pre)[0][0, 0].copy())
                offset = self.DELAY + late
                chosen, _, _ = planner.plan(sim.save_state(0), 0, h['starter'],
                                            hist.buf[0].copy(), int(hist.prev[0]),
                                            offset=offset, seen=np.stack(seen), policy=policy,
                                            extra=extra)
                theirs = planner.last
                self.assertEqual(mine['outcome'], 'planned')
                got = [library[k]['actions'][at:].tobytes() for k, at in mine['tried']
                       if k not in ('own', 'extra')]
                self.assertEqual(got, [m['actions'].tobytes() for m in theirs['picked']])
                dealt = list(theirs['dealt'][:-1]) + ([theirs['kept']] if extra is not None else [])
                np.testing.assert_array_equal(mine['dealt'],
                                              np.array(dealt + [theirs['dealt'][-1]], np.float32))
                if chosen is None:
                    self.assertIsNone(mine['chosen'])
                else:
                    k, at = mine['tried'][mine['chosen']]
                    np.testing.assert_array_equal(
                        extra if k == 'extra' else library[k]['actions'][at + offset:], chosen)
                compared += 1
            self.assertGreater(compared, 4)
            native.close()
        env.close()


if __name__ == '__main__':
    unittest.main()
