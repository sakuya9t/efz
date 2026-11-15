"""efz_env.modules: the modules of an agent, their order, and the manifest (no game, no
model: an agent that always plays 0)."""

import json
import os
import tempfile
import unittest

try:
    import numpy as np
except ImportError:  # the package needs numpy
    raise unittest.SkipTest('numpy is not installed')

from efz_env import modules
from efz_env.actions import ActionTable


class Still:
    """An agent as efz_env.agent.Agent is to its hosts, playing action 0 with no delay."""
    frame_skip, history, delay, hist, seen, deterministic, model = 1, 0, 0, None, None, False, None

    def __init__(self):
        self.table = ActionTable()
        self.resets = []

    def batch(self, n):
        self.n = n

    def reset(self, mask=None):
        self.resets.append(mask)

    def controls(self, obs, step):
        return self.table.to_bytes(np.zeros(len(obs), int))

    def observe(self, controls):
        pass


class When(modules.Module):
    """Plays `action` on the steps whose first observation is one of `values`."""

    def __init__(self, name, values, action):
        self.name, self.values, self.action = name, values, action
        self.watched, self.interrupted, self.matches = 0, 0, 0

    def reset(self, mask=None):
        self.matches += 1

    def watch(self, i, ctx):
        self.watched += 1
        if ctx.last not in (None, self.name):
            self.interrupted += 1

    def act(self, i, ctx):
        return self.action if int(ctx.view[0]) in self.values else None

    def stats(self):
        return dict(watched=self.watched)


class Hosts(unittest.TestCase):
    def play(self, firsts, mods):
        agent = modules.ModularAgent(Still(), mods)
        agent.attach(env=None, side=0)
        agent.batch(1)
        table = agent.table.table
        out = []
        for step, v in enumerate(firsts):
            c = agent.controls(np.array([[v, 0.0]], np.float32), step)
            agent.observe(c)
            out.append(int(np.flatnonzero((table == c[0]))[0]) if c[0] != table[0] else 0)
        return agent, out

    def test_the_first_module_that_wants_a_step_has_it(self):
        a, b = When('a', {1, 3}, 5), When('b', {2, 3}, 7)
        agent, out = self.play([0, 1, 2, 3, 0], [a, b])
        self.assertEqual(out, [0, 5, 7, 5, 0])
        self.assertEqual((a.watched, b.watched), (5, 5))  # each sees every step
        s = agent.stats()
        self.assertEqual(s['played'], dict(a=0.4, b=0.2))
        self.assertEqual(s['a'], dict(watched=5))

    def test_a_module_learns_it_was_interrupted(self):
        a, b = When('a', {3}, 5), When('b', {2, 3}, 7)
        self.play([2, 3, 2, 0], [a, b])
        # b played step 0, a took step 1: b sees a's name on step 2, a sees b's on 1 and 3
        self.assertEqual(b.interrupted, 1)
        self.assertEqual(a.interrupted, 2)

    def test_names_are_one_of_each(self):
        with self.assertRaises(ValueError):
            modules.Stack([When('a', set(), 1), When('a', set(), 2)])

    def test_reset_reaches_the_agent_and_its_modules(self):
        a = When('a', set(), 1)
        agent = modules.ModularAgent(Still(), [a])
        agent.batch(2)
        before = a.matches
        agent.reset(np.array([True, False]))
        self.assertEqual(a.matches, before + 1)
        self.assertEqual(len(agent.agent.resets), 1)


class Manifest(unittest.TestCase):
    def test_round_trip_and_build(self):
        with tempfile.TemporaryDirectory() as d:
            os.makedirs(os.path.join(d, 'agent'))
            model, lib = os.path.join(d, 'agent', 'avg.zip'), os.path.join(d, 'lib.npz')
            for p in (model, lib):
                open(p, 'w').close()
            path = os.path.join(d, modules.MANIFEST)
            modules.save_manifest(path, model, [dict(kind='when', code=None, files=dict(library=lib),
                                                     options=dict(action=4))])
            with open(path) as f:
                raw = json.load(f)
            self.assertEqual(raw['model'], 'agent/avg.zip')  # paths from its folder
            self.assertEqual(raw['modules'][0]['files'], dict(library='lib.npz'))
            made = modules.load_manifest(d)
            self.assertEqual(made['model'], model)
            self.assertEqual(made['modules'][0]['files']['library'], lib)
            seen = {}

            def factory(agent, where, files, options, data):
                seen.update(where=where, files=files, data=data)
                return When('when', {1}, options['action'])
            modules.register('when', factory)
            try:
                built = modules.build('agent', made['modules'], 'batch', data='game')
            finally:
                del modules.REGISTRY['when']
            self.assertEqual(built[0].action, 4)
            self.assertEqual(seen, dict(where='batch', files=dict(library=lib), data='game'))

    def test_an_unknown_kind_and_a_newer_format_say_so(self):
        with self.assertRaises(ValueError):
            modules.build(None, [dict(kind='no-such-kind')], 'play')
        with tempfile.TemporaryDirectory() as d:
            with open(os.path.join(d, modules.MANIFEST), 'w') as f:
                json.dump(dict(format=modules.FORMAT + 1, model='m.zip'), f)
            with self.assertRaises(ValueError):
                modules.load_manifest(d)
        self.assertIsNone(modules.load_manifest(os.path.join(d, 'nothing-here.json')))

    def test_a_command_line_spec(self):
        with tempfile.NamedTemporaryFile(suffix='.npz') as f:
            spec = modules.parse_spec(f'routes:library={f.name},per_start=24,replan=false,x')
        self.assertEqual(spec['kind'], 'routes')
        self.assertEqual(spec['files'], dict(library=os.path.abspath(f.name)))
        self.assertEqual(spec['options'], dict(per_start=24, replan=False, x=True))


if __name__ == '__main__':
    unittest.main()
