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
        self.same_plans()

    def test_same_plans_by_ending(self):
        """The same with a knockdown at a combo's end worth HP (redteam.Planner's ending,
        the file's route_ending): the copies' victim recovering in the air when it can."""
        import inspect
        sys.path.insert(0, RUNS)
        try:
            import redteam
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        if 'ending' not in inspect.signature(redteam.Planner).parameters:
            self.skipTest("runs/human-ayu's redteam.py plans by damage alone")
        self.same_plans(ending=3000)

    def same_plans(self, ending=0):
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
            export_agent(path, out, check=False, library=library, ending=ending)
            native = NativeAgent(out, deterministic=True)
            self.assertEqual(native.routes, len(library))
            model = PPO.load(path, device='cpu')
            planner = redteam.Planner(DATA, library, model, per_start=12, history=self.HISTORY,
                                      **(dict(ending=ending) if ending else {}))
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
            if ending:  # the endings told apart, and a choice of them made by it somewhere
                self.assertEqual(planner.endings['plans'], compared)
                self.assertGreater(planner.endings['changed'], 0, planner.endings)
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


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class OkizemeAsOkiplan(unittest.TestCase):
    """The game's planned okizeme (port/agent/mix.h: the module okiplan:1) against
    runs/human-ayu/okiplan.py: the same counts of the opponent from the same views, and at
    a knockdown the same options, worth against each answer, and mix."""

    HISTORY, DELAY = 4, 5

    def setUp(self):
        sys.path.insert(0, RUNS)
        if not os.path.exists(os.path.join(RUNS, 'motions.json')):  # (made on each machine)
            self.skipTest('no runs/human-ayu/motions.json: python runs/human-ayu/motions.py '
                          'makes it')
        try:
            import okiplan
            import oki_library
            self.okiplan, self.answers = okiplan, oki_library.answers()
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        if not hasattr(okiplan.OkiPlanner, 'wake_schedule'):
            self.skipTest("runs/human-ayu's okiplan.py has no scheduled reversal")

    def match(self, steps, seed=0, envs=8):
        """Random play, ayu against mai: yields (the environment, its views) a step."""
        from efz_env import ActionTable, EfzVecEnv
        table = ActionTable()
        env = EfzVecEnv(DATA, envs, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                        autoreset='disabled', skip_noninteractive=False)
        env.set_matches(chars=('ayu', 'mai'))
        obs = env.reset()
        rng = np.random.default_rng(seed)
        a = np.zeros((envs, 2), np.uint8)
        try:
            for _ in range(steps):
                a[:, 0] = table.table[rng.integers(len(table), size=envs)]
                a[:, 1] = table.table[rng.integers(len(table), size=envs)]
                obs, _, term, trunc, _ = env.step(a)
                yield env, obs, term | trunc
        finally:
            env.close()

    def library(self, air, rng):
        """Entries of every kind that can be played from a knockdown wherever it is."""
        lib = []
        for k, cls in enumerate(['ground low', 'jump high', 'fly high', 'throw', 'ground mid',
                                 'dash high', 'ground low', 'jump high']):
            n = 110 + 3 * k
            lib.append(dict(actions=rng.integers(0, 45, n).astype(np.int64),
                            dist=np.full(n, 20 * k, np.int16), air=np.full(n, air), rise=85 + k,
                            move_at=84, cls=cls, opponent='mai' if k % 2 else 'akane',
                            corner=bool(k % 3 == 0)))
        lib.append(dict(lib[0], opponent='mai'))  # (the same inputs: tried once)
        return lib

    def test_the_same_counts(self):
        from efz_env.memory import K, Memory
        names = ['w_n', 'w_move', 'w_inv', 'w_jump', 'w_back', 'p_n', 'p_move', 'p_inv',
                 'p_jump', 'p_back', 'g_n', 'g_crouch']
        from efz_env.vec import character_names
        chars = character_names()
        inv = {str(chars.index(c)): acts for c, acts in self.answers['invincible'].items()}
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            lib = self.library(False, np.random.default_rng(1))
            export_agent(path, out, check=False, okiplan=dict(library=lib, answers=self.answers))
            native = NativeAgent(out)
            self.assertEqual(native.oki, len(lib))
            self.assertIn('okiplan:1', native.modules)
            memory = Memory(1, invincible=inv)
            native.counts(mode=1)
            seen = 0
            for step, (env, obs, over) in enumerate(self.match(9000, envs=1)):
                view = obs[0, 0]
                memory.update(view[None])
                mine, shares = native.counts(view)
                if step % 250 == 0 or over[0]:
                    theirs = np.array([memory.c[0, K[n]] for n in names])
                    np.testing.assert_array_equal(mine, theirs, err_msg=f'step {step}')
                    np.testing.assert_allclose(shares, self.okiplan.belief(memory.c[0], 6.0, 6.0),
                                               rtol=1e-12)
                    seen = max(seen, int((theirs > 0).sum()))
                if over[0]:
                    break
            self.assertGreaterEqual(seen, 6, 'too little happened in the match to tell')
            memory.end(np.array([True]), new_set=np.array([False]))  # the same opponent again
            mine, _ = native.counts(mode=2)
            np.testing.assert_allclose(mine, [memory.c[0, K[n]] for n in names], rtol=1e-6)
            native.close()

    def test_played_in_a_match(self):
        """The game's player with its planner, in a match (NativeAgent.attach): at its
        opponent's knockdowns plans are asked for and made from where the game then is
        (none elsewhere), and what is drawn is played."""
        from efz_env import ActionTable, EfzVecEnv
        table = ActionTable()
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            lib = self.library(False, np.random.default_rng(2)) + \
                self.library(True, np.random.default_rng(3))
            export_agent(path, out, check=False,
                         okiplan=dict(library=lib, answers=self.answers, per_plan=3, window=20,
                                      tolerance=400, think=4, skip=0.05))
            native = NativeAgent(out, seed=5)
            env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                            autoreset='disabled')
            rng = np.random.default_rng(0)
            a = np.zeros((1, 2), np.uint8)
            total = {}
            for match in range(6):
                env.set_matches(chars=('ayu', 'mai'))
                obs = env.reset()
                native.attach(env, 0, 0, seed=match) if match == 0 else native.reset(match)
                for _ in range(20000):
                    live = obs[0, 0, 2] == 0 and obs[0, 0, 3] == 0
                    a[0, 0] = native.step(obs[0, 0], live)
                    a[0, 1] = table.table[rng.integers(9)]  # (it only moves)
                    obs, _, term, trunc, _ = env.step(a)
                    if term[0] or trunc[0]:
                        break
                for k, v in native.stats().items():
                    total[k] = total.get(k, 0) + v
                if total['oki_plans'] >= 3:
                    break
            self.assertGreaterEqual(total['oki_plans'], 1, total)
            self.assertEqual(total['oki_elsewhere'], 0, total)
            self.assertEqual(total['oki_late'], 0, total)
            self.assertEqual(total['oki_asked'], total['oki_plans'] + total['oki_nothing'] +
                             total['oki_apart'], total)
            self.assertGreater(total['oki_frames'], 0)
            native.attach(None)
            native.close()
            env.close()

    def test_the_same_plans(self):
        from efz_env.modules import sampler
        okiplan = self.okiplan
        found = []
        was = np.zeros(8, bool)
        for env, obs, over in self.match(30000):
            down = np.isin(np.round(obs[:, 0, okiplan.OPP_ACT]), [0x62]) & ~over
            for e in np.flatnonzero(down & ~was):
                found.append((env.save_state(int(e)), obs[e, 0].copy()))
            was = down
            if len(found) >= 6 or over.all():
                break
        self.assertGreaterEqual(len(found), 3, 'too few knockdowns in the random play')
        rng = np.random.default_rng(5)
        compared = 0
        skipped = 0
        from efz_env.memory import K
        # (doubt, skip, and okiplan:2's: sight, the riser's guard by what it saw that many
        # steps ago; bait, a reversal that came out and missed counted as its punish)
        for doubt, skip, sight, bait in ((0.0, 0.0, 0, 0.0), (0.3, 0.0, 0, 0.0),
                                         (0.3, 0.12, 0, 0.0), (0.0, 0.12, 0, 0.0),
                                         (0.0, 0.0, 6, 0.0), (0.0, 0.0, 0, 500.0),
                                         (0.3, 0.12, 3, 700.0)):
            with tempfile.TemporaryDirectory() as folder:
                path, model = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
                out = os.path.join(folder, 'agent.efzagent')
                policy = sampler(model, deterministic=True)
                for state, view in found:
                    air = bool(view[okiplan.SELF_AIR] > 0)
                    lib = self.library(air, np.random.default_rng(compared))
                    options = dict(per_plan=5, per_class=2, window=40, wait=30, tolerance=400,
                                   doubt=doubt, skip=skip, sight=sight, bait=bait)
                    export_agent(path, out, check=False,
                                 okiplan=dict(library=lib, answers=self.answers, **options))
                    native = NativeAgent(out, deterministic=True)
                    # (a file that uses neither is one the first version's game loads)
                    self.assertIn('okiplan:2' if sight or bait else 'okiplan:1', native.modules)
                    np.testing.assert_allclose(
                        native.counts(mode=1)[1],
                        okiplan.belief(np.zeros(len(K)), 6.0, 6.0, sight=bool(sight)), rtol=1e-12)
                    planner = okiplan.OkiPlanner(DATA, lib, OBS_DIM + 6 * self.HISTORY, self.DELAY,
                                                 history=self.HISTORY, after='guard', **options)
                    seen = np.repeat(view[None], self.DELAY + 1, 0) + \
                        rng.normal(0, 0.01, (self.DELAY + 1, len(view))).astype(np.float32)
                    hist = rng.integers(0, 2, (self.HISTORY, 6)).astype(np.float32)
                    shares = rng.dirichlet(np.ones(5))
                    env = planner.one
                    env.load_state(0, state)
                    mine = native.oki_plan(env, 0, 0, hist, 0x10, shares, seen=seen)
                    self.assertEqual(env.save_state(0), state)  # the game as it was
                    planner.plan(state, 0, hist, 0x10, seen, policy, shares)
                    theirs = planner.last
                    if theirs is None:
                        self.assertEqual(mine['outcome'], 'nothing')
                    else:
                        self.assertEqual(mine['outcome'], 'planned')
                        self.assertEqual(mine['lead'], theirs['lead'])
                        self.assertEqual(mine['entries'], theirs['entries'])
                        kinds = [lib[k]['cls'] for k in theirs['entries']] + ['wait', 'own']
                        self.assertEqual(theirs['kinds'], kinds)
                        self.assertEqual(len(mine['kinds']), len(kinds))
                        self.assertEqual(mine['kinds'][-2:], ['wait', 'own'])
                        # (an answer with a share under skip: not played here, not counted there)
                        counted = shares >= skip
                        skipped += int((~counted).sum())
                        np.testing.assert_array_equal(mine['worth'][:, counted],
                                                      theirs['worth'][:, counted])
                        np.testing.assert_array_equal(mine['first'][:, counted],
                                                      theirs['first'][:, counted])
                        self.assertFalse(mine['worth'][:, ~counted].any())
                        np.testing.assert_allclose(mine['expected'], theirs['expected'], rtol=1e-9,
                                                   atol=1e-6)
                        np.testing.assert_allclose(mine['mix'], theirs['mix'], atol=1e-4)  # (2,000 rounds' sums)
                        self.assertEqual(len(theirs['entries']), 5)
                        # (something happened on the copies: not every worth is 0)
                        self.assertGreater(float(np.abs(theirs['worth']).max()), 0)
                        compared += 1
                    native.close()
                    for e in (planner.one, planner.sim):
                        e.close()
        self.assertGreaterEqual(compared, 4)
        self.assertGreater(skipped, 0)


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class PressureAsPressplan(unittest.TestCase):
    """The game's planned pressure (mix.h's BeginPress: the module pressplan:1) against
    runs/human-ayu/pressplan.py's live plan: from the step a move touches a guard, the
    same wait, the same view expected, the same options, worth and mix."""

    HISTORY, DELAY = 4, 5

    def setUp(self):
        sys.path.insert(0, RUNS)
        if not os.path.exists(os.path.join(RUNS, 'motions.json')):  # (made on each machine)
            self.skipTest('no runs/human-ayu/motions.json: python runs/human-ayu/motions.py '
                          'makes it')
        try:
            import okiplan
            import pressplan
            import pressure_library
            self.okiplan, self.pressplan = okiplan, pressplan
            self.answers = pressure_library.answers()
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        if not hasattr(pressplan, 'live_plan'):
            self.skipTest("runs/human-ayu's pressplan.py has no live plan")

    def contacts(self, want=6):
        """States on the step a move of player 1's touches player 2's guard: ayu walks in
        and presses, mai holds a crouching guard."""
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        okiplan = self.okiplan
        env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                        autoreset='disabled', skip_noninteractive=False)
        env.set_matches(chars=('ayu', 'mai'))
        obs = env.reset()
        a = np.zeros((1, 2), np.uint8)
        guards = set(self.pressplan.GUARDS.tolist())
        found, was = [], (-1, 0)
        for t in range(6000):
            close = abs(float(obs[0, 0, okiplan.DX])) * 640 < 36
            button = 'AB'[(t // 60) % 2]
            a[0, 0] = encode(2, button) if close and t % 14 == 0 else encode(5) if close else encode(6)
            a[0, 1] = encode(1)
            obs, _, term, trunc, _ = env.step(a)
            if term[0] or trunc[0]:
                break
            act, frame = int(round(float(obs[0, 0, 50]))), int(round(float(obs[0, 0, 51])))
            if act in guards and (was[0] not in guards or act != was[0] or frame < was[1]):
                found.append((env.save_state(0), obs[0, 0].copy()))
                if len(found) >= want:
                    break
            was = (act, frame)
        env.close()
        return found

    def library(self, rng):
        lib = []
        for k, cls in enumerate(['ground low', 'throw', 'dash high', 'none: hold', 'ground mid',
                                 'jump high', 'ground low', 'throw']):
            lib.append(dict(actions=rng.integers(0, 45, 30 + k).astype(np.int64), cls=cls,
                            adv=int(rng.integers(-6, 8)), distance=20 + 6 * k,
                            opponent='mai' if k % 2 else 'akane', corner=bool(k % 3 == 0)))
        lib.append(dict(lib[0], opponent='mai'))
        return lib

    def test_played_in_a_match(self):
        """The game's player with its planner, in a match against a guarding opponent
        (NativeAgent.attach): plans asked for at its guarded moves, made from where the
        game then is or dropped for a reason, and counted."""
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False,
                         pressplan=dict(library=self.library(np.random.default_rng(2)),
                                        answers=self.answers, per_plan=3, window=20,
                                        tolerance=400, slack=40))
            native = NativeAgent(out, seed=5)
            env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                            autoreset='disabled')
            a = np.zeros((1, 2), np.uint8)
            total = {}
            for match in range(4):
                env.set_matches(chars=('ayu', 'mai'))
                obs = env.reset()
                native.attach(env, 0, 0, seed=match) if match == 0 else native.reset(match)
                for t in range(20000):
                    live = obs[0, 0, 2] == 0 and obs[0, 0, 3] == 0
                    a[0, 0] = native.step(obs[0, 0], live)
                    # (it walks in and holds a crouching guard)
                    a[0, 1] = encode(6) if abs(float(obs[0, 0, 4])) * 640 > 60 else encode(1)
                    obs, _, term, trunc, _ = env.step(a)
                    if term[0] or trunc[0]:
                        break
                for k, v in native.stats().items():
                    total[k] = total.get(k, 0) + v
                if total['press_plans'] >= 3:
                    break
            self.assertGreaterEqual(total['press_asked'], 3, total)
            self.assertGreaterEqual(total['press_plans'], 1, total)
            self.assertEqual(total['press_late'], 0, total)
            self.assertEqual(total['press_asked'], total['press_plans'] + total['press_nothing'] +
                             total['press_apart'] + total['press_elsewhere'], total)
            native.attach(None)
            native.close()
            env.close()

    def test_the_same_plans(self):
        from efz_env.modules import sampler
        okiplan, pressplan = self.okiplan, self.pressplan
        found = self.contacts()
        self.assertGreaterEqual(len(found), 3, 'too few guarded moves in the script')
        rng = np.random.default_rng(7)
        compared = nothing = 0
        # (doubt, skip, and pressplan:2's sight: the guard by sight, okiplan's)
        for doubt, skip, sight in ((0.3, 0.05, 0), (0.0, 0.0, 0), (0.3, 0.12, 0), (0.0, 0.0, 5),
                                   (0.3, 0.05, 2)):
            with tempfile.TemporaryDirectory() as folder:
                path, model = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
                out = os.path.join(folder, 'agent.efzagent')
                policy = sampler(model, deterministic=True)
                for n, (state, view) in enumerate(found):
                    lib = self.library(np.random.default_rng(n))
                    options = dict(per_plan=4, per_class=2, window=30, wait=10, tolerance=400,
                                   slack=40, doubt=doubt, skip=skip, sight=sight)
                    export_agent(path, out, check=False,
                                 pressplan=dict(library=lib, answers=self.answers, **options))
                    native = NativeAgent(out, deterministic=True)
                    self.assertEqual(native.press, len(lib))
                    self.assertIn('pressplan:2' if sight else 'pressplan:1', native.modules)
                    planner = pressplan.PressPlanner(DATA, lib, OBS_DIM + 6 * self.HISTORY,
                                                     self.DELAY, history=self.HISTORY,
                                                     after='guard', **options)
                    actions = rng.integers(0, 45, self.DELAY) if n % 2 else \
                        np.full(self.DELAY, okiplan.NEUTRAL)
                    hist = rng.integers(0, 2, (self.HISTORY, 6)).astype(np.float32)
                    shares = rng.dirichlet(np.ones(5))
                    hold = 0x06  # (it holds a crouching guard: encode(1))
                    env = planner.one
                    env.load_state(0, state)
                    seen = np.repeat(env.obs[0, 0][None], self.DELAY + 1, 0)
                    mine = native.press_plan(env, 0, 0, actions, hist, 0x10, shares, hold)
                    self.assertEqual(env.save_state(0), state)  # the game as it was
                    got = pressplan.live_plan(planner, state, 0, hist, 0x10, seen, policy, shares,
                                              rest=actions)
                    if got is None:
                        self.assertEqual(mine['outcome'], 'nothing')
                        nothing += 1
                    else:
                        theirs = planner.last
                        self.assertEqual(mine['outcome'], 'planned')
                        waited = len(got[0]) - self.DELAY
                        counted = shares >= skip
                        self.assertEqual(mine['adv'], theirs['adv'])
                        self.assertEqual(mine['lead'], theirs['lead'])
                        np.testing.assert_array_equal(mine['view'][1:], got[2][1:])
                        self.assertEqual(mine['entries'], theirs['entries'])
                        np.testing.assert_array_equal(mine['worth'][:, counted],
                                                      theirs['worth'][:, counted])
                        np.testing.assert_allclose(mine['mix'], theirs['mix'], atol=1e-4)  # (2,000 rounds' sums)
                        # What it drew: the wait until it is free, then that option's inputs.
                        c, k = mine['chosen'], len(theirs['entries'])
                        want = (lib[theirs['entries'][c]]['actions'] if c < k else
                                np.full(theirs['lead'] + options['wait'], okiplan.CROUCH_GUARD)
                                if c == k else np.zeros(0, int))
                        self.assertEqual(mine['waited'], mine['option'].size - len(want))
                        np.testing.assert_array_equal(mine['option'][mine['waited']:], want)
                        self.assertTrue((mine['option'][:mine['waited']] == okiplan.CROUCH_GUARD).all())
                        # (the Python plan's own draw: the same wait before whatever it drew)
                        self.assertGreaterEqual(waited, mine['waited'])
                        compared += 1
                    native.close()
                    for e in (planner.one, planner.sim):
                        e.close()
        self.assertGreaterEqual(compared, 4, (compared, nothing))


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class CatchAsAirplan(unittest.TestCase):
    """The game's catch (mix.h's BeginThrow: the module airthrow:1) against
    runs/human-ayu/airplan.py's live_throw: from the step an opponent's air recovery
    begins, the same view expected, the same steps of the recovery left, and the same air
    throw that catches inside it (or none)."""

    HISTORY, DELAY = 4, 5

    def setUp(self):
        sys.path.insert(0, RUNS)
        try:
            import airplan
            import okiplan
            self.airplan, self.okiplan = airplan, okiplan
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        if not hasattr(airplan, 'live_throw'):
            self.skipTest("runs/human-ayu's airplan.py has no live throw")

    def recoveries(self, want=12, steps=6000):
        """States on the step player 2 recovers in the air out of a hit of player 1's:
        ayu presses and jumps at random, mai jumps about pressing a button every other
        step (which is also how a recovery is pressed)."""
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        okiplan = self.okiplan
        n = 8
        env = EfzVecEnv(DATA, n, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                        autoreset='disabled', skip_noninteractive=False)
        env.set_matches(chars=('ayu', 'mai'))
        obs = env.reset()
        rng = np.random.default_rng(5)
        table = okiplan.TABLE.table
        mine = [okiplan.INDEX[x] for x in ((5, 'A'), (5, 'B'), (9, ''), (9, 'A'), (9, 'B'),
                                           (8, 'B'), (6, ''), (5, 'C'), (2, 'B'), (6, ''))]
        a = np.zeros((n, 2), np.uint8)
        was, hold, cur = np.zeros(n, int), np.zeros(n, int), np.zeros(n, int)
        found = []
        for t in range(steps):
            for i in range(n):
                if hold[i] <= 0:
                    cur[i], hold[i] = mine[rng.integers(0, len(mine))], rng.integers(2, 10)
                hold[i] -= 1
            a[:, 0] = table[cur]
            d = (7, 8, 9, 9)[(t // 40) % 4]
            a[:, 1] = encode(d, 'A') if t % 2 == 0 else encode(d)
            obs, _, term, trunc, _ = env.step(a)
            act = np.round(obs[:, 0, 50]).astype(int)
            for i in range(n):
                if act[i] in (0x9d, 0x9e) and 0x32 <= was[i] < 0x60 and not (term[i] or trunc[i]):
                    found.append((env.save_state(i), obs[i, 0].copy()))
            was = act
            if len(found) >= want or (term | trunc).all():
                break
        env.close()
        return found

    def test_the_same_throws(self):
        from efz_env.modules import sampler
        airplan, okiplan = self.airplan, self.okiplan
        found = self.recoveries()
        self.assertGreaterEqual(len(found), 6, 'too few air recoveries in the script')
        rng = np.random.default_rng(7)
        caught = none = 0
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False, airthrow={})
            native = NativeAgent(out, deterministic=True)
            self.assertIn('airthrow:1', native.modules)
            self.assertTrue(native.airthrow)
            policy = sampler(model, deterministic=True)
            planner = airplan.AirPlanner(DATA, [], OBS_DIM + 6 * self.HISTORY, self.DELAY,
                                         history=self.HISTORY)
            env = planner.one
            for n, (state, view) in enumerate(found):
                actions = rng.integers(0, 45, self.DELAY) if n % 3 == 2 else \
                    np.full(self.DELAY, okiplan.NEUTRAL if n % 3 else airplan.FORWARD)
                hist = rng.integers(0, 2, (self.HISTORY, 6)).astype(np.float32)
                env.load_state(0, state)
                seen = np.repeat(env.obs[0, 0][None], self.DELAY + 1, 0)
                mine = native.throw_plan(env, 0, 0, actions, hist, 0x10)
                self.assertEqual(env.save_state(0), state)  # the game as it was
                got = airplan.live_throw(planner, state, 0, hist, 0x10, seen, policy, rest=actions)
                if got is None:
                    self.assertEqual(mine['outcome'], 2, mine)
                    self.assertEqual(mine['option'].size, 0)
                    none += 1
                else:
                    self.assertEqual(mine['outcome'], 1, mine)
                    self.assertEqual(got[1], self.DELAY)
                    np.testing.assert_array_equal(mine['view'][1:], got[2][1:])
                    np.testing.assert_array_equal(mine['option'], got[0][self.DELAY:])
                    self.assertEqual(mine['lead'], planner.last['lead'])
                    self.assertEqual(mine['caught'], planner.last['caught'])
                    self.assertEqual(mine['tried'], planner.last['tried'])
                    caught += 1
            native.close()
            for e in (planner.one, planner.sim):
                e.close()
        self.assertGreaterEqual(caught, 2, (caught, none))
        self.assertGreaterEqual(none, 1, (caught, none))

    def test_out_of_reach_nothing_is_planned(self):
        airplan = self.airplan
        found = self.recoveries(want=2)
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False, airthrow=dict(near=1))
            native = NativeAgent(out, deterministic=True)
            planner = airplan.AirPlanner(DATA, [], OBS_DIM + 6 * self.HISTORY, self.DELAY,
                                         history=self.HISTORY)
            env = planner.one
            state, view = found[0]
            env.load_state(0, state)
            hist = np.zeros((self.HISTORY, 6), np.float32)
            actions = np.full(self.DELAY, self.okiplan.NEUTRAL)
            if abs(float(view[4])) * 640 > 1:
                self.assertEqual(native.throw_plan(env, 0, 0, actions, hist, 0, near=1)['outcome'], 2)
            native.close()
            for e in (planner.one, planner.sim):
                e.close()

    def test_played_in_a_match(self):
        """The game's player with the catch, in matches against an opponent that jumps
        about and recovers (NativeAgent.attach): each recovery out of its hits is planned
        from or dropped for a reason, and counted."""
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False, airthrow={})
            native = NativeAgent(out, seed=5)
            env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                            autoreset='disabled')
            a = np.zeros((1, 2), np.uint8)
            total = {}
            for match in range(6):
                env.set_matches(chars=('ayu', 'mai'))
                obs = env.reset()
                native.attach(env, 0, 0, seed=match) if match == 0 else native.reset(match)
                for t in range(20000):
                    live = obs[0, 0, 2] == 0 and obs[0, 0, 3] == 0
                    a[0, 0] = native.step(obs[0, 0], live)
                    d = (7, 8, 9, 9)[(t // 40) % 4]
                    a[0, 1] = encode(d, 'A') if t % 2 == 0 else encode(d)
                    obs, _, term, trunc, _ = env.step(a)
                    if term[0] or trunc[0]:
                        break
                for k, v in native.stats().items():
                    total[k] = total.get(k, 0) + v
                if total['air_asked'] >= 3:
                    break
            self.assertGreaterEqual(total['air_asked'], 1, total)
            self.assertEqual(total['air_late'], 0, total)
            self.assertEqual(total['air_asked'], total['air_plans'] + total['air_nothing'] +
                             total['air_apart'] + total['air_elsewhere'], total)
            self.assertEqual(total['air_plans'], total['air_played'], total)
            native.attach(None)
            native.close()
            env.close()


@unittest.skipUnless(DATA, 'the game data (EFZ_DATA)')
class NativeAsOpponent(unittest.TestCase):
    """An agent file played by the game's code as a training environment's opponent
    (runs/human-ayu/native_agent.py's NativeOpponent, finetune.py --vs-native): player 2
    of its matches is the file's player, attached to each of them."""

    HISTORY, DELAY = 4, 5

    def setUp(self):
        sys.path.insert(0, RUNS)
        try:
            import native_agent
            self.native_agent = native_agent
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')
        if not hasattr(native_agent, 'NativeOpponent'):
            self.skipTest("runs/human-ayu's native_agent.py has no opponent")

    def played(self, path, threads, steps=400, n=3):
        """Player 2's control bytes over `steps` steps of n matches, of which the file
        plays the first two; and the file's own steps for them, asked again."""
        from efz_env.sb3 import EfzSB3VecEnv, mixture
        opp = self.native_agent.NativeOpponent(path, deterministic=True, seed=4, threads=threads)
        idle = lambda obs: np.zeros(len(obs), np.int64)
        assignment = np.array([0, 0, 1])
        env = EfzSB3VecEnv(DATA, n, opponent=mixture([opp, idle], assignment),
                           chars=[('ayu', 'mai')] * n, frame_skip=1, history=self.HISTORY,
                           delay=self.DELAY, max_frames=0, seed=3)
        opp.mine = assignment == 0
        opp.attach(env)
        self.assertEqual(sorted(opp.agents), [0, 1])
        rng = np.random.default_rng(1)
        env.reset()
        out = []
        for _ in range(steps):
            env.step_async(rng.integers(0, env.action_space.n, n))
            out.append(env._controls[:, 1].copy())
            env.step_wait()
        env.close()
        opp.close()
        return np.array(out)

    def test_the_file_plays_its_matches(self):
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            a = self.played(out, 1)
            # Its own matches: bytes of its own, more than one kind; the other match is
            # the mixture's other member's (action 0: nothing pressed).
            self.assertGreater(len(np.unique(a[:, :2])), 3)
            self.assertTrue((a[:, 2] == a[0, 2]).all())
            # The same play again, and on threads.
            np.testing.assert_array_equal(a, self.played(out, 1))
            np.testing.assert_array_equal(a, self.played(out, 3))

    def test_as_a_free_player(self):
        """Without planners in the file, the attached player's bytes are the ones the
        file's player gives for the same views (the game as it is, delayed by itself)."""
        from efz_env import EfzVecEnv
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            from efz_env.sb3 import EfzSB3VecEnv, mixture
            opp = self.native_agent.NativeOpponent(out, deterministic=True, seed=4)
            env = EfzSB3VecEnv(DATA, 1, opponent=mixture([opp], np.zeros(1, int)),
                               chars=[('ayu', 'mai')], frame_skip=1, history=self.HISTORY,
                               delay=self.DELAY, max_frames=0, seed=3)
            opp.attach(env)
            twin = NativeAgent(out, deterministic=True, seed=4)
            rng = np.random.default_rng(1)
            env.reset()
            for t in range(300):
                o = env.env.obs[0, 1].copy()
                want = twin.step(o[:OBS_DIM], o[2] == 0 and o[3] == 0)
                env.step_async(rng.integers(0, env.action_space.n, 1))
                self.assertEqual(int(env._controls[0, 1]), want, t)
                env.step_wait()
            env.close()
            opp.close()
            twin.close()


class RiseAsRisePy(unittest.TestCase):
    """The game's guard on rising (policy.h's Rise: the module rise:1) against
    runs/human-ayu/rise.py's with guard=true, carry=true: from the same views, the guard
    held by sight on the same steps, and the same read of the match's attacker."""

    HISTORY, DELAY = 4, 5
    LYING, HIT = 0x62, 0x3b

    def setUp(self):
        sys.path.insert(0, RUNS)
        try:
            import rise
            from efz_env import modules
            self.rise, self.modules = rise, modules
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')

    def views(self, script):
        """script: (steps, its own action, the attacker's distance in pixels, the attacker
        in the air, the attacker's action, its own HP lost on the first of them)."""
        rise, out, hp = self.rise, [], 1.0
        for steps, act, dx, air, opp, lost in script:
            for k in range(steps):
                hp -= (lost if k == 0 else 0) / rise.HP
                v = np.zeros(OBS_DIM, np.float32)
                v[rise.SELF_ACT], v[rise.DX], v[rise.OPP_AIR] = act, dx / rise.PIXELS, float(air)
                v[rise.OPP_ACT], v[rise.SELF_HP], v[rise.OPP_HP] = opp, hp, 1.0
                out.append(v)
        return out

    def played(self, native, views):
        return [native.step(v) for v in views]

    def twin(self, views, **options):
        """rise.py's module over the views as the agent sees them (DELAY late)."""
        m = self.modules.REGISTRY['rise'](None, 'batch', {}, dict(guard=True, carry=True, **options),
                                          None)
        m.batch(1)
        self.feed(m, views)
        return m

    def feed(self, m, views):
        for t in range(len(views)):
            v = views[max(0, t - self.DELAY)]
            ctx = self.modules.Context(v, v, hist=np.zeros((self.HISTORY, 6), np.float32), policy=None)
            m.watch(0, ctx)
            m.act(0, ctx)

    def test_the_guard_held_by_sight(self):
        rise = self.rise
        # Up; down with the attacker far; then near on the ground, then in the air; up.
        script = [(8, 0, 400, False, 0, 0), (6, self.LYING, 400, False, 0, 0),
                  (6, self.LYING, 100, False, 0, 0), (7, self.LYING, 100, True, 0, 0),
                  (5, self.LYING, 100, False, 0, 0), (30, 0, 100, False, 0, 0)]
        views = self.views(script)
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            plain, out = os.path.join(folder, 'plain.efzagent'), os.path.join(folder, 'rise.efzagent')
            export_agent(path, plain, check=False)
            export_agent(path, out, check=False, rise=dict(low=-1.0, high=0.0, near=130))  # (always guarded)
            self.assertNotIn('rise', read_header(plain)[1]['modules'])
            with self.assertRaises(ValueError):
                export_agent(path, out + '.bad', check=False, rise=dict(nothing=1))
            native, base = NativeAgent(out, deterministic=True), NativeAgent(plain, deterministic=True)
            self.assertIn('rise:1', native.modules)
            self.assertTrue(native.rise)
            got, own = self.played(native, views), self.played(base, views)
            stats = native.stats()
            native.close()
            base.close()
        # What it sees is DELAY steps late: down from step 8 + DELAY, the attacker on it
        # from 14 + DELAY, in the air from 20 + DELAY to 27 + DELAY, up at 32 + DELAY.
        d = self.DELAY
        self.assertEqual(got[:14 + d], own[:14 + d])  # its own play until the attacker is on it
        for t in range(14 + d, 32 + d):
            air = 20 + d <= t < 27 + d
            self.assertIn(got[t], (0x02,) if air else (0x02, 0x06), t)
        self.assertTrue(any(got[t] == 0x06 for t in range(14 + d, 20 + d)))
        self.assertEqual((stats['rise_knockdowns'], stats['rise_met'], stats['rise_guarded'],
                          stats['rise_steps'], stats['rise_stood']), (1, 1, 1, 18, 7))
        # The attacker far and not in a move: its own play throughout.
        far = self.views([(8, 0, 400, False, 0, 0), (20, self.LYING, 400, False, 0, 0),
                          (20, 0, 400, False, 0, 0)])
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            plain, out = os.path.join(folder, 'plain.efzagent'), os.path.join(folder, 'rise.efzagent')
            export_agent(path, plain, check=False)
            export_agent(path, out, check=False, rise=dict(low=-1.0, high=0.0, near=130))
            native, base = NativeAgent(out, deterministic=True), NativeAgent(plain, deterministic=True)
            self.assertEqual(self.played(native, far), self.played(base, far))
            self.assertEqual(native.stats()['rise_met'], 0)
            native.close()
            base.close()

    def test_the_same_read_of_the_attacker(self):
        # A rising the attacker leaves alone (no move of its own as the agent sees itself
        # up), and one it is in a move at.
        alone = [(6, 0, 300, False, 0, 0), (12, self.LYING, 300, False, 0, 0), (40, 0, 300, False, 0, 0)]
        there = [(12, self.LYING, 90, False, 0xd0, 0), (3, 0, 90, False, 0xd0, 0),
                 (4, self.HIT, 90, False, 0, 1300), (40, 0, 300, False, 0, 0)]
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'rise.efzagent')
            export_agent(path, out, check=False, rise={})
            native = NativeAgent(out, deterministic=True)
            m = self.twin([])
            # At the prior: the same probability.
            self.assertAlmostEqual(m.guard_chance(0), 0.867, delta=0.001)
            self.assertEqual(native.stats()['rise_chance'], 867)
            # The same risings counted, and the same probability after each.
            for script, seen, on, chance in ((alone, 1, 0, 244), (alone, 2, 0, 0), (there, 3, 1, 413)):
                views = self.views(script)
                self.played(native, views)
                self.feed(m, views)
                got = native.stats()
                self.assertEqual((got['rise_seen'], got['rise_on']), (100 * seen, 100 * on))
                self.assertEqual((m.seen[0], m.on[0]), (seen, on))
                self.assertAlmostEqual(got['rise_chance'], chance, delta=1)
                self.assertAlmostEqual(got['rise_chance'] / 1000, m.guard_chance(0), delta=0.001)
            native.next_match()                            # the same opponent next: older,
            native.next_match()                            # (once a match, as the game
            m.reset()                                      # resets at both its ends)
            got = native.stats()
            self.assertEqual((got['rise_seen'], got['rise_on']), (210, 70))
            self.assertAlmostEqual(m.seen[0], 2.1)
            self.assertAlmostEqual(m.on[0], 0.7)
            native.reset(1)                                # afresh: nothing kept
            self.assertEqual(native.stats()['rise_seen'], 0)
            native.close()


@unittest.skipIf(not DATA or not os.path.isdir(DATA or ''), 'no game data: set EFZ_DATA')
class RiskAsRiskPy(unittest.TestCase):
    """The game's look at a press (policy.h's Risk, Player::RiskStarts: the module risk:1)
    against runs/human-ayu/risk.py's: from the same game, the same move started (or none)
    by the same press, at once or kept by the game and played later; and the same
    probability of stopping it at the priors."""

    HISTORY, DELAY = 4, 5

    def setUp(self):
        sys.path.insert(0, RUNS)
        try:
            import risk
            from efz_env import modules
            self.risk, self.modules = risk, modules
        except ImportError as e:
            self.skipTest(f'runs/human-ayu: {e}')

    def test_the_same_moves_started(self):
        from efz_env import EfzVecEnv
        from efz_env.actions import encode
        risk = self.risk
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=self.HISTORY, delay=self.DELAY, seed=3)
            out = os.path.join(folder, 'risk.efzagent')
            moves = {risk.MOVES[k]: w for k, w in risk.PRIORS.items()}
            with self.assertRaises(ValueError):
                export_agent(path, out + '.bad', check=False, risk={})
            export_agent(path, out, check=False, risk=dict(moves=moves, ahead=1))
            self.assertEqual(read_header(out)[1]['risk_ahead'], '1')  # (the inputs chosen ahead too)
            export_agent(path, out, check=False, risk=dict(moves=moves))
            self.assertEqual(read_header(out)[1]['risk_ahead'], '0')
            native = NativeAgent(out, deterministic=True)
            self.assertIn('risk:1', native.modules)
            env = EfzVecEnv(DATA, 1, frame_skip=1, rounds_to_win=2, max_frames=0, seed=3,
                            autoreset='disabled')
            env.set_matches(chars=('ayu', 'ayu'))
            obs = env.reset()
            twin = risk.Risk(DATA, None, self.DELAY)
            twin.batch(1)

            def step(byte):
                a = np.zeros((1, 2), np.uint8)
                a[0, 0] = byte
                return env.step(a)[0]

            def both(action):
                state = env.save_state(0)
                ctx = self.modules.Context(obs[0, 0], obs[0, 0], save=lambda: state, side=0)
                mine = twin.starts(ctx, action)
                got, chance = native.risk_starts(env, 0, 0, action)
                self.assertEqual(env.save_state(0), state)  # the game as it was
                self.assertEqual(got, None if mine is None else risk.MOVES[mine], (action, mine))
                if mine is not None:
                    self.assertAlmostEqual(chance, twin.chance(0, mine), delta=1e-6)
                return mine

            for _ in range(150):
                obs = step(0)
            seen = set()
            presses = [risk.INDEX[a] for a in ((6, 'A'), (6, 'B'), (6, 'C'), (3, 'B'), (5, 'A'),
                                               (2, 'C'), (5, ''))]
            for motion in ('236', '623', '236236', '641236', '5'):
                for _ in range(90):
                    obs = step(0)
                for d in motion[:-1]:
                    obs = step(encode(int(d)))
                    for a in presses:
                        seen.add(both(a))
                for a in presses:
                    seen.add(both(a))
            self.assertTrue({'236A', '236B', '236C', '623A', '623B', '623C'} <= seen, seen)
            # A press made during a normal, which the game keeps: 5A, then 2 3 6 inside it.
            for _ in range(90):
                obs = step(0)
            obs = step(encode(5, 'A'))
            kept = set()
            for d in '236':
                obs = step(encode(int(d)))
            for _ in range(6):
                kept.add(both(risk.INDEX[(6, 'B')]))
                obs = step(encode(6))
            self.assertIn('236B', kept, kept)
            native.close()
            twin.close()
            env.close()


if __name__ == '__main__':
    unittest.main()
