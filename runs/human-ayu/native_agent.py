"""An agent file played by the game's own code (port/agent: its network, its routes, its
planned okizeme), in an evaluation's matches: what a person meets in the game, measured as
the Python agents are.

    python runs/human-ayu/evaluate.py --p1 AGENT.efzagent --p1-native --p2 ... --json out.json

Each match has its own player (efz_env.export.NativeAgent, attached to its environment:
its plans are made on copies of it, each worked to its end on the step that needs it, as
the game's fast-forward does). The file's own modules and options are what is played;
evaluate.py's --p1-assist and --p1-module are the Python agents'.

In training the same file is an opponent (NativeOpponent: finetune.py --vs FILE.efzagent
--vs-native), so that what learns to beat an agent meets it as the game plays it.
"""

import numpy as np

from efz_env.export import NativeAgent

INTRO, ROUND_OVER = 2, 3


class NativePlayers:
    """evaluate.py's P1 from an agent file: batch(n), attach(env, side), controls(obs,
    step), observe(inputs), reset(mask), stats()."""

    def __init__(self, path, deterministic=False, seed=0):
        self.path, self.deterministic, self.seed = path, deterministic, seed
        self.agents, self.total = [], {}
        self.env = self.side = None

    def batch(self, n):
        self.close()
        self.agents = [NativeAgent(self.path, deterministic=self.deterministic,
                                   seed=self.seed + i) for i in range(n)]

    def attach(self, env, side):
        self.env, self.side = env, side
        for i, a in enumerate(self.agents):
            a.attach(env, i, side, seed=self.seed + i)

    def _take(self, a):
        for k, v in a.stats().items():
            self.total[k] = self.total.get(k, 0) + v

    def reset(self, mask=None):
        for i, a in enumerate(self.agents):
            if mask is None or mask[i]:
                self._take(a)
                a.reset(self.seed + i)

    def controls(self, obs, step):
        out = np.zeros(len(self.agents), np.uint8)
        for i, a in enumerate(self.agents):
            out[i] = a.step(obs[i, :168], obs[i, INTRO] == 0 and obs[i, ROUND_OVER] == 0)
        return out

    def observe(self, inputs):
        pass

    def stats(self):
        """Its plans, all matches: the routes' and the okizeme's (NativeAgent.stats)."""
        for a in self.agents:
            self._take(a)
            a.reset(self.seed)
        t = dict(self.total)
        asked = max(1, t.get('oki_asked', 0) - t.get('oki_late', 0))
        t['oki_ms_a_plan'] = round(t.get('oki_ms', 0) / asked, 1)
        t['oki_frames_a_plan'] = round(t.get('oki_frames', 0) / asked)
        pressed = max(1, t.get('press_asked', 0) - t.get('press_late', 0))
        t['press_ms_a_plan'] = round(t.get('press_ms', 0) / pressed, 1)
        caught = max(1, t.get('air_asked', 0) - t.get('air_late', 0))
        t['air_ms_a_plan'] = round(t.get('air_ms', 0) / caught, 1)
        t['air_frames_a_plan'] = round(t.get('air_frames', 0) / caught)
        made = max(1, t.get('route_plans', 0) + t.get('route_dropped', 0))
        t['route_ms_a_plan'] = round(t.get('route_ms', 0) / made, 1)
        return t

    def close(self):
        for a in self.agents:
            a.close()
        self.agents = []


class NativeOpponent:
    """An agent file played by the game's own code as an EfzSB3VecEnv's opponent (player
    2): finetune.py --vs FILE.efzagent --vs-native. A member of sb3.mixture (its actions
    there are placeholders): attach(venv) gives each of its matches (`mine`: a mask, None
    for all) a player attached to that environment, and from then on the environment's
    opponent_controls hook writes their control bytes. The file's own reaction time is
    what it plays with (it is given the game as it is and delays it itself).

    threads: its players' steps (their plans are most of a step's time) on this many
    threads; each player has its own game copies and draws, so the bytes are the same as
    one after another."""
    takes_index = True

    def __init__(self, path, deterministic=False, seed=0, threads=1):
        self.path, self.deterministic, self.seed = path, deterministic, seed
        self.mine = self.venv = self.pool = None
        self.threads = max(1, int(threads))
        self.agents, self.total, self.matches, self.played = {}, {}, 0, {}

    def attach(self, venv):
        self.close()  # (the players of the environment before: it may be closed by now)
        self.venv = venv
        where = np.arange(venv.n) if self.mine is None else np.flatnonzero(self.mine)
        for i in where:
            i = int(i)
            a = NativeAgent(self.path, deterministic=self.deterministic, seed=self.seed + i)
            a.attach(venv.env, i, 1, seed=self.seed + i)
            self.agents[i] = a
        venv.opponent_controls.append(self.controls)
        if self.threads > 1 and self.pool is None:
            from concurrent.futures import ThreadPoolExecutor
            self.pool = ThreadPoolExecutor(self.threads)

    def __call__(self, obs, idx):
        return np.zeros(len(idx), np.int64)

    def controls(self, out):
        v = self.venv
        obs = v.env.obs
        for i, a in self.agents.items():
            if v._length[i] == 0:  # a new match
                for k, x in a.stats().items():
                    self.total[k] = self.total.get(k, 0) + x
                self.matches += 1
                self.played[i] = self.played.get(i, 0) + 1
                a.reset(self.seed + i + 7919 * self.played[i])

        def one(item):
            i, a = item
            o = obs[i, 1]
            out[i] = a.step(o[:168], o[INTRO] == 0 and o[ROUND_OVER] == 0)
        if self.pool is None:
            for item in self.agents.items():
                one(item)
        else:
            list(self.pool.map(one, self.agents.items()))

    def close(self):
        for a in self.agents.values():
            a.close()
        self.agents = {}
