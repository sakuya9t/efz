"""An agent file as a release to work on from (efz_env.export: the training part,
unpack_agent, parts_from): what is unpacked is what was packed, and the tools take the
file where they take a model. Needs stable-baselines3 and torch; no game data."""

import json
import os
import tempfile
import unittest

import numpy as np

try:
    import torch as th
    from stable_baselines3 import PPO
    from efz_env.agent import Agent, load_config
    from efz_env.export import (NativeAgent, export_agent, load_routes, read_agent,
                                read_header, sample_views, torch_log_probs, unpack_agent)
    from tests.test_agents import fake_chooser, make_model, random_routes
    MISSING = None
except ImportError as e:  # pragma: no cover
    MISSING = str(e)


def same_state(a, b):
    sa, sb = a.policy.state_dict(), b.policy.state_dict()
    return sa.keys() == sb.keys() and all(th.equal(sa[k], sb[k]) for k in sa)


def trained_a_step(path):
    """The model at `path` after one update (so that its optimizer has moments), saved."""
    model = PPO.load(path, device='cpu')
    loss = sum((p ** 2).sum() for p in model.policy.parameters())
    model.policy.optimizer.zero_grad()
    loss.backward()
    model.policy.optimizer.step()
    model.num_timesteps = 12345
    model.save(path)
    return model


@unittest.skipIf(MISSING, f'needs stable-baselines3 and torch: {MISSING}')
class Unpacked(unittest.TestCase):
    def round_trip(self, efz):
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, efz=efz)
            model = trained_a_step(path)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out)
            got = unpack_agent(out, os.path.join(folder, 'unpacked'))
            self.assertEqual((got['critic'], got['optimizer'], got['library']),
                             ('file', False, None))
            self.assertLess(got['policy'], 1e-4)
            again = PPO.load(got['model'], device='cpu')
            self.assertTrue(same_state(model, again))
            self.assertEqual(again.num_timesteps, 12345)
            for k in ('n_steps', 'batch_size', 'n_epochs', 'gamma', 'gae_lambda', 'ent_coef'):
                self.assertEqual(getattr(again, k), getattr(model, k), k)
            views = th.as_tensor(sample_views(model.observation_space.shape[0], 32, seed=3))
            with th.no_grad():
                self.assertTrue(th.equal(model.policy.predict_values(views),
                                         again.policy.predict_values(views)))
            cfg = json.load(open(got['config']))
            self.assertEqual((cfg['frame_skip'], cfg['history'], cfg['delay'], cfg['chars']),
                             (1, 2, 3, ['ayu', None]))
            # A game plays the file as before: the training part is of no module.
            agent = NativeAgent(out)
            self.assertEqual(agent.modules, 'policy:1')
            agent.close()

    def test_efz_policy(self):
        self.round_trip(True)

    def test_mlp_policy(self):
        self.round_trip(False)

    def test_the_optimizer(self):
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder)
            model = trained_a_step(path)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, optimizer=True)
            got = unpack_agent(out, os.path.join(folder, 'unpacked'))
            self.assertTrue(got['optimizer'])
            a = model.policy.optimizer.state_dict()['state']
            b = PPO.load(got['model'], device='cpu').policy.optimizer.state_dict()['state']
            self.assertEqual(len(a), len(b))
            for j in a:
                self.assertEqual(float(a[j]['step']), float(b[j]['step']))
                self.assertTrue(th.equal(a[j]['exp_avg'], b[j]['exp_avg']))
                self.assertTrue(th.equal(a[j]['exp_avg_sq'], b[j]['exp_avg_sq']))

    def test_a_file_to_play_only(self):
        # Without its training part (and the files from before it): the actor, a new critic.
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, train=False)
            _, keys, tensors = read_header(out)
            self.assertFalse(any(k.startswith('train') for k in list(keys) + list(tensors)))
            got = unpack_agent(out, os.path.join(folder, 'unpacked'))
            self.assertEqual(got['critic'], 'new')
            again = PPO.load(got['model'], device='cpu')
            views = sample_views(model.observation_space.shape[0], 32, seed=3)
            np.testing.assert_array_equal(torch_log_probs(model.policy, views),
                                          torch_log_probs(again.policy, views))
            sa = again.policy.state_dict()
            self.assertTrue(th.equal(sa['vf_features_extractor.scale'],
                                     sa['pi_features_extractor.scale']))
            self.assertEqual(json.load(open(got['config']))['chars'], ['ayu', None])

    def test_its_settings_without_the_home_folder(self):
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder)
            home = os.path.expanduser('~')
            cfg = json.load(open(os.path.join(folder, 'config.json')))
            cfg.update(vs=[[os.path.join(home, 'runs', 'x.zip'), 'mai']], memory={'decay': 0.5})
            json.dump(cfg, open(os.path.join(folder, 'config.json'), 'w'))
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            self.assertNotIn(home.encode(), open(out, 'rb').read())
            got = unpack_agent(out, os.path.join(folder, 'unpacked'), check=False)
            again = json.load(open(got['config']))
            self.assertEqual(again['vs'], [['~/runs/x.zip', 'mai']])
            self.assertEqual(again['memory'], {'decay': 0.5})

    def test_routes_and_chooser(self):
        with tempfile.TemporaryDirectory() as folder:
            path, model = make_model(folder, history=4, delay=5)
            routes = random_routes(np.random.default_rng(2), (200, 210), marks_to=(210, 215))
            # As a library's are: the actions its inputs read as (a button held is no press).
            from efz_env.actions import ActionTable
            from efz_env.history import action_labels
            table = ActionTable()
            read = lambda acts: action_labels(np.concatenate(
                [[0], table.to_bytes(np.asarray(acts))]).astype(np.uint8), table)[1:]
            for m in routes:
                m['actions'] = read(m['actions']).astype(np.int64)
                np.testing.assert_array_equal(read(m['actions']), m['actions'])
            chooser = os.path.join(folder, 'chooser.pt')
            fake_chooser(model, routes, chooser)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, library=routes, replan=True, chooser=chooser)
            got = unpack_agent(out, os.path.join(folder, 'unpacked'))
            # The routes as a combo library: what the planner in Python reads.
            back = load_routes(got['library'])
            self.assertEqual(len(back), len(routes))
            for a, b in zip(routes, back):
                self.assertEqual((a['starter'], a['opponent'], a['kept_for'], a['damage']),
                                 (b['starter'], b['opponent'], b['kept_for'], b['damage']))
                np.testing.assert_array_equal(a['actions'], b['actions'])
                self.assertEqual(a['marks'], b['marks'])
            # Packed again from the unpacked files: the same routes and pool.
            _, _, first = read_agent(out)
            second_path = os.path.join(folder, 'second.efzagent')
            export_agent(got['model'], second_path, library=got['library'], replan=True)
            _, _, second = read_agent(second_path)
            for name in first:
                if name.startswith('routes.') or name.startswith('train.') or \
                        name.startswith('pi.'):
                    np.testing.assert_array_equal(first[name], second[name], err_msg=name)
            # And with the first file's parts as they are: its chooser too.
            third_path = os.path.join(folder, 'third.efzagent')
            check = export_agent(got['model'], third_path, parts_from=out)
            _, keys, third = read_agent(third_path)
            self.assertEqual(sorted(first), sorted(third))
            for name in first:
                np.testing.assert_array_equal(first[name], third[name], err_msg=name)
            self.assertEqual(keys['modules'], 'policy:1,routes:1,chooser:1')
            self.assertEqual((check['routes'], check['pool']),
                             (len(routes), int(keys['route_pool'])))
            # Only its routes.
            fourth = os.path.join(folder, 'fourth.efzagent')
            export_agent(got['model'], fourth, parts_from=out, keep=('routes',))
            self.assertEqual(read_agent(fourth)[1]['modules'], 'policy:1,routes:1')
            # The planner's ending is a setting: the file's unless one is given.
            self.assertEqual(int(read_agent(fourth)[1]['route_ending']),
                             int(read_agent(out)[1]['route_ending']))
            fifth = os.path.join(folder, 'fifth.efzagent')
            export_agent(got['model'], fifth, parts_from=out, ending=400)
            self.assertEqual(int(read_agent(fifth)[1]['route_ending']), 400)
            sixth = os.path.join(folder, 'sixth.efzagent')
            export_agent(got['model'], sixth, parts_from=fifth)
            self.assertEqual(int(read_agent(sixth)[1]['route_ending']), 400)

    def test_the_tools_take_the_file(self):
        with tempfile.TemporaryDirectory() as folder:
            path, _ = make_model(folder, history=4, delay=5)
            out = os.path.join(folder, 'agent.efzagent')
            export_agent(path, out, check=False)
            self.assertEqual(load_config(out)['delay'], 5)
            a, b = Agent(path, n=3, deterministic=True), Agent(out, n=3, deterministic=True)
            self.assertEqual((b.frame_skip, b.history, b.delay), (1, 4, 5))
            rng = np.random.default_rng(0)
            for step in range(40):
                obs = rng.normal(size=(3, 168)).astype(np.float32)
                obs[:, [18, 50]] = rng.integers(0, 300, (3, 2))
                obs[:, [34, 66]] = rng.integers(0, 20, (3, 2))
                ca, cb = a.controls(obs, step), b.controls(obs, step)
                np.testing.assert_array_equal(ca, cb)
                a.observe(ca)
                b.observe(cb)

    def test_what_isnt_one(self):
        with tempfile.TemporaryDirectory() as folder:
            path = os.path.join(folder, 'x.efzagent')
            with open(path, 'wb') as f:
                f.write(b'not an agent')
            with self.assertRaisesRegex(ValueError, 'not an agent file'):
                unpack_agent(path, os.path.join(folder, 'out'))


if __name__ == '__main__':
    unittest.main()
