"""The combo master: Ayu trained on combo trials, each started where one of people's
combos started (combo_starts.py), rewarded for the damage of the combo it makes.

    python runs/human-ayu/combo.py --starts D:/tasogare/efz-replays/combo-starts

Why: an agent learning from whole matches finds that pokes pay at once and combos only
when every input of them is right, so it settles for more and shorter combos (with
Instant Charge, 22C, in 4% of them against people's 16%). In a trial the reward is the
combo alone, from its first hit to the counter's reset: what it inputs while it can't
move (the cancel buffered for the moment a move connects, the IC) is what pays.

A trial loads a start (the game at the first hit), gives the agent the attacker with the
views and inputs the player had just before (its reaction --delay and input --history,
as the clone it starts from was trained with), and the defender guards, standing or
crouching at random, once it can: a combo that leaves a gap is guarded. It ends when the
combo counter goes back to 0, at a KO, or after --limit steps. --focus of the trials
start from the quarter of starts their players made the most of (most starts are a
poke with nothing to follow; those are where the long combos are: the corner, the
meter), the rest from any. In --rich of them the attacker's resources are drawn from
the 12 groups (evaluate.resources: the RF gauge blue under 500, no Instant Charge; red
500-999, one 22C cancel; cyan, full, whose Instant Charge also gives back five times the
gauge in proration, the way to 7,000 and more; and 0-3 bars of power), so that it learns to use what it
has; in the rest they are the player's. Each evaluation plays every held-out start as
its player had it, and with the resources of --eval-groups.

Two helpers (the user's) for long combos. The juggle: each hit sets the defender's
untech time (the bar under a juggled player: until it runs out it can't recover) to the
hit's own times the attacker's proration (the combo's power, which each hit cuts, and a
cyan Instant Charge gives back); --juggle w adds w * (gamma * phi' - phi) to each step's
reward, phi the defender's untech time left while it is juggled (in hitstun in the air),
so that a hit keeping the juggle up pays at once and not only through the hits it makes
possible. Being potential-based it changes how fast it is learnt, not which combo is
best. And --meter-cost c: minus c for each bar of power gauge spent (supers), so that the
long combos are found without them; the RF gauge (Instant Charge) is free. And
--leftover-cost l: minus l times the proration left when the combo ends (people's end
with 64% of it left, the agents' with 74-79%: the in-air bar costs nothing, so what is
left of it is damage not made; the user's). The reward is the damage
dealt (per 1000 HP); a small KL toward the clone (--prior-coef) keeps its inputs a
person's. Every --chunk steps the held-out starts (from replays bc.py holds out) are
played once each and compared with what their players did from there (the damage after
the first hit, which had landed already, and the combo's hits). --out gets
combo.zip (and its combo.config.json, for efz_env.agent), combo.json, chunks.
"""

import argparse
import csv
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np
from gymnasium import spaces
from stable_baselines3.common.vec_env.base_vec_env import VecEnv

from efz_env import ActionTable, EfzVecEnv
from efz_env.actions import BACK, DOWN
from efz_env.history import FEATURES, input_features

COMBO_HITS, COMBO_DAMAGE = 30, 38  # self_combo_hits (/ 30), self_combo_damage (/ 9999)
from evaluate import GROUPS  # noqa: E402  (runs/human-ayu is on the path)


def group_gauges(group, rng):
    """Gauges in a resource group ('red2': RF 500-999, 2,000-2,999 power), drawn."""
    state, bars = group[:-1], int(group[-1])
    power = 3000 if bars == 3 else int(bars * 1000 + rng.integers(0, 1000))
    if state == 'cyan':
        return power, 1000.0, True
    lo = 500 if state == 'red' else 0
    return power, float(lo + rng.integers(0, 500)), False
SELF_GAUGE = 9  # self_gauge (/ 3000)
SELF_PRORATION = 31  # self_proration (/ 10000)
OPP_HITSTUN, OPP_UNTECH, OPP_AIRBORNE = 52, 61, 71  # opp_untech: ticks / 100
ACTION = 18
INSTANT_CHARGE = (0xa7, 0xab)
SPECIALS = range(0xfa, 0x13e)


def load_starts(folder, split, limit, rng):
    """The starts of a split, without their states (restore() makes them)."""
    rows = [r for r in csv.DictReader(open(os.path.join(folder, 'starts.csv'), encoding='utf-8'))
            if r['split'] == split]
    rng.shuffle(rows)
    out = []
    for r in rows[:limit]:
        with np.load(os.path.join(folder, r['file'])) as z:
            seen = z['seen'].astype(np.float32)
            # The player's combo after the start: its first hit had landed already.
            first = float(seen[-1][COMBO_DAMAGE]) * 9999
            out.append(dict(id=r['id'], step=int(r['file'].rsplit('-', 1)[1].split('.')[0]),
                            side=int(z['side']), seen=seen,
                            inputs=z['inputs'].astype(np.uint8), hits=int(z['hits']),
                            damage=max(0.0, float(z['damage']) - first), file=r['file']))
    return out


def restore(data_dir, replays, starts, envs=32):
    """Each start's state, made again in this process: its replay played back to the
    step it was taken at (as combo_starts.py played it). A save state holds the library's
    addresses, so the one kept on disk is good only where the library loads at the same
    place; the replay and the step are good anywhere. Checks that the view there is the
    one kept. Returns how many matched."""
    import collections
    index = {r['id']: r['path'] for r in csv.DictReader(open(os.path.join(replays, 'index.csv'),
                                                             encoding='utf-8'))}
    by_replay = collections.defaultdict(list)
    for st in starts:
        by_replay[st['id']].append(st)
    queue = collections.deque(by_replay.items())
    n = min(envs, len(queue))
    env = EfzVecEnv(data_dir, n, frame_skip=1, rounds_to_win=2, max_frames=64 * 60 * 30,
                    autoreset='disabled')
    jobs = [None] * n  # per environment: [replay id, its starts by step, step]

    def next_job(i):
        while queue:
            rid, sts = queue.popleft()
            env.play(i, os.path.join(replays, index[rid]))
            env.reset(mask=np.arange(n) == i)
            steps = collections.defaultdict(list)
            for st in sts:
                steps[st['step']].append(st)
            jobs[i] = [rid, steps, 0]
            return
        jobs[i] = None

    for i in range(n):
        next_job(i)
    matched = 0
    idle = np.zeros((n, 2), np.uint8)
    while any(j is not None for j in jobs):
        obs, _, term, trunc, _ = env.step(idle)
        for i in range(n):
            j = jobs[i]
            if j is None:
                continue
            j[2] += 1
            if j[2] in j[1]:
                state = env.save_state(i)
                for st in j[1].pop(j[2]):
                    st['state'] = state
                    matched += int(np.array_equal(obs[i, st['side']], st['seen'][-1]))
            if not j[1] or term[i] or trunc[i]:
                next_job(i)
    env.close()
    return matched


class ComboTrials(VecEnv):
    """Combo trials as SB3's VecEnv: num_envs trials at once, each restarting from a start
    drawn at random (or, with order, the starts in turn, each once; or with sample, a
    function of the rng giving one).

    A start: state (a save state at the attacker's first hit), side (the attacker's),
    seen (its views up to the start, oldest first, at least delay + 1) and either inputs
    (its controls before) or hist and prev (its input features, newest first, and last
    control, as efz_env.history.InputHistory keeps them); damage, hits and file, its
    player's combo from there, where known. reward_scale: the reward per HP dealt
    (combo.py's 1/1000; a match's is 1/9999 a bar). bootstrap: a trial's end is a time
    limit to SB3 (it values the state the combo left), for trials among matches
    (practice.py), where what follows a combo is the match."""

    def __init__(self, data_dir, starts, num_envs, delay=14, history=16, limit=1200, seed=0,
                 order=False, focus=0.0, rich=0.0, gauges=None, juggle=0.0, meter_cost=0.0,
                 gamma=0.99, leftover_cost=0.0, reward_scale=1 / 1000.0, bootstrap=False,
                 sample=None):
        self.env = EfzVecEnv(data_dir, num_envs, frame_skip=1, rounds_to_win=2,
                             max_frames=0, autoreset='disabled', reward_round=0.0,
                             reward_match=0.0)
        self.env.reset()  # a game in each, for the starts to load into
        self.starts, self.n, self.delay, self.H = starts, num_envs, delay, history
        self.limit, self.order, self.next = limit, order, 0
        self.focus = focus
        self.juggle, self.meter_cost, self.gamma = juggle, meter_cost, gamma
        self.leftover_cost = leftover_cost
        self.reward_scale, self.bootstrap, self.sample = reward_scale, bootstrap, sample
        self.recent = []  # the last trials' results, for a log (take_recent)
        self.proration = np.ones(num_envs)  # the attacker's, at its combo's last hit
        self.phi = np.zeros(num_envs)    # the juggle's potential now
        self.gauge = np.zeros(num_envs)  # the attacker's power gauge, last step
        self.rich = rich      # share of trials with resources drawn from the groups
        self.gauges = gauges  # a group ('cyan3'...): every trial with its resources
        by_damage = np.argsort([st.get('damage', 0.0) for st in starts])
        self.best = by_damage[-max(1, len(starts) // 4):]  # the top quarter
        self.rng = np.random.default_rng(seed)
        self.table = ActionTable()
        d = self.env.obs_dim
        self.seen = np.zeros((num_envs, delay + 1, d), np.float32)  # newest first
        self.hist = np.zeros((num_envs, history, FEATURES), np.float32)  # newest first
        self.prev = np.zeros(num_envs, np.uint8)
        self.side = np.zeros(num_envs, int)
        self.guard = np.zeros(num_envs, np.uint8)
        self.t = np.zeros(num_envs, int)
        self.dealt = np.zeros(num_envs)
        self.hp = np.zeros(num_envs)
        self.max_hits = np.zeros(num_envs, int)
        self.ic = np.zeros(num_envs, bool)
        self.special = np.zeros(num_envs, bool)
        self.current = [None] * num_envs
        self.active = np.ones(num_envs, bool)  # with order: false once the starts run out
        self.results = []  # with order: each start's trial, as it ends
        self._controls = np.zeros((num_envs, 2), np.uint8)
        space = spaces.Box(-np.inf, np.inf, (d + history * FEATURES,), np.float32)
        super().__init__(num_envs, space, spaces.Discrete(len(self.table)))

    def _load(self, i):
        if self.order:
            if self.next >= len(self.starts):
                self.active[i] = False
                return
            st = self.starts[self.next]
            self.next += 1
        elif self.sample is not None:
            st = self.sample(self.rng)
        elif self.rng.random() < self.focus:
            st = self.starts[self.best[self.rng.integers(len(self.best))]]
        else:
            st = self.starts[self.rng.integers(len(self.starts))]
        self.current[i] = st
        self.env.load_state(i, st['state'])
        s = st['side']
        self.side[i] = s
        group = st.get('group', self.gauges)  # a start's own, or the trials'
        if group is None and self.rich and self.rng.random() < self.rich:
            group = GROUPS[self.rng.integers(len(GROUPS))]
        if group is not None:
            power, rf, blue = group_gauges(group, self.rng)
            self.env.set_gauges(i, s, power=power, rf=rf, blue=blue)
        self.guard[i] = BACK | (DOWN if self.rng.random() < 0.5 else 0)
        if 'hist' in st:
            self.hist[i] = st['hist'][:self.H]
            self.prev[i] = st['prev']
        else:
            inputs = st['inputs']
            prev = np.concatenate([[0], inputs[:-1]]).astype(np.uint8)
            self.hist[i] = input_features(inputs, prev)[::-1][:self.H]
            self.prev[i] = inputs[-1]
        self.seen[i] = st['seen'][::-1][:self.delay + 1]
        self.seen[i, 0] = self.env.obs[i, s]  # the start, with its gauges as set
        self.t[i] = 0
        self.dealt[i] = 0.0
        self.hp[i] = float(self.env.info['hp'][i, 1 - s])
        self.phi[i] = self._phi(self.env.obs[i, s])
        self.proration[i] = min(1.0, float(self.env.obs[i, s, SELF_PRORATION]))
        self.gauge[i] = float(self.env.obs[i, s, SELF_GAUGE]) * 3000
        self.max_hits[i] = round(float(self.env.obs[i, s, COMBO_HITS]) * 30)
        self.ic[i] = self.special[i] = False

    def _phi(self, o):
        """The juggle's potential: the defender's untech time left, while juggled."""
        juggled = o[OPP_HITSTUN] > 0 and o[OPP_AIRBORNE] > 0
        return self.juggle * float(o[OPP_UNTECH]) if juggled else 0.0

    def _view(self, i):
        return np.concatenate([self.seen[i, self.delay], self.hist[i].ravel()])

    def reset(self):
        for i in range(self.n):
            self._load(i)
        return np.stack([self._view(i) for i in range(self.n)])

    def step_async(self, actions):
        b = self.table.to_bytes(np.asarray(actions))
        rows = np.arange(self.n)
        self._controls[rows, self.side] = b
        self._controls[rows, 1 - self.side] = self.guard
        self.env.step_async(self._controls)

    def step_wait(self):
        obs, _, term, trunc, info = self.env.step_wait()
        rewards = np.zeros(self.n, np.float32)
        dones = np.zeros(self.n, bool)
        infos = [{} for _ in range(self.n)]
        views = []
        for i in range(self.n):
            if not self.active[i]:
                views.append(self._view(i))
                continue
            s = self.side[i]
            c = info['input'][i, s]
            f = input_features(np.array([c]), np.array([self.prev[i]]))[0]
            self.hist[i, 1:] = self.hist[i, :-1]
            self.hist[i, 0] = f
            self.prev[i] = c
            self.seen[i, 1:] = self.seen[i, :-1]
            self.seen[i, 0] = obs[i, s]
            hp = float(info['hp'][i, 1 - s])
            dealt = max(0.0, self.hp[i] - hp)
            self.hp[i] = hp
            self.dealt[i] += dealt
            rewards[i] = dealt * self.reward_scale
            gauge = float(obs[i, s, SELF_GAUGE]) * 3000
            if self.meter_cost:
                rewards[i] -= self.meter_cost * max(0.0, self.gauge[i] - gauge) * self.reward_scale
            self.gauge[i] = gauge
            self.t[i] += 1
            hits = round(float(obs[i, s, COMBO_HITS]) * 30)
            self.max_hits[i] = max(self.max_hits[i], hits)
            act = round(float(obs[i, s, ACTION]))
            self.ic[i] |= act in INSTANT_CHARGE
            self.special[i] |= act in SPECIALS
            ended = hits == 0 or term[i] or trunc[i] or self.t[i] >= self.limit
            if hits > 0:
                self.proration[i] = min(1.0, float(obs[i, s, SELF_PRORATION]))
            if ended and self.leftover_cost and not term[i]:  # a KO wastes nothing
                rewards[i] -= self.leftover_cost * self.proration[i]
            if self.juggle:  # the potential is 0 once the trial ends
                phi = 0.0 if ended else self._phi(obs[i, s])
                rewards[i] += self.gamma * phi - self.phi[i]
                self.phi[i] = phi
            if ended:
                dones[i] = True
                st = self.current[i]
                result = dict(damage=self.dealt[i], hits=int(self.max_hits[i]), ic=bool(self.ic[i]),
                              special=bool(self.special[i]), human_damage=st.get('damage'),
                              human_hits=st.get('hits'), file=st.get('file'), job=st.get('job'),
                              kind=st.get('kind'))
                infos[i] = dict(terminal_observation=self._view(i), combo=result,
                                **{'TimeLimit.truncated': bool(self.bootstrap or
                                                               self.t[i] >= self.limit)})
                if not self.bootstrap:  # (among matches, SB3's episodes are the matches)
                    infos[i]['episode'] = {'r': float(self.dealt[i] * self.reward_scale),
                                           'l': int(self.t[i]), 't': 0.0}
                if self.order:
                    self.results.append(result)
                self.recent.append(result)
                del self.recent[:-2000]
                self._load(i)
            views.append(self._view(i))
        return np.stack(views), rewards, dones, infos

    def close(self):
        self.env.close()

    def get_attr(self, attr_name, indices=None):
        return [getattr(self, attr_name)] * len(self._get_indices(indices))

    def set_attr(self, attr_name, value, indices=None):
        setattr(self, attr_name, value)

    def env_method(self, method_name, *args, indices=None, **kwargs):
        result = getattr(self, method_name)(*args, **kwargs)
        return [result] * len(self._get_indices(indices))

    def env_is_wrapped(self, wrapper_class, indices=None):
        return [False] * len(self._get_indices(indices))


def evaluate(args, model, starts, gauges=None):
    """Each held-out start once: the damage made from it, against its player's (with
    gauges, from each start with the resources of that group)."""
    trials = ComboTrials(args.data, starts, min(64, len(starts)), args.delay, args.history,
                         args.limit, order=True, gauges=gauges)
    obs = trials.reset()
    while trials.active.any():
        actions = model.predict(obs, deterministic=False)[0]
        obs, _, _, _ = trials.step(actions)
    trials.close()
    r = trials.results
    mean = lambda k: float(np.mean([x[k] for x in r]))
    top = lambda k, q: float(np.percentile([x[k] for x in r], q))
    out = dict(starts=len(r), damage=mean('damage'), damage_p90=top('damage', 90),
               damage_max=top('damage', 100), hits=mean('hits'), hits_max=top('hits', 100),
               ic=mean('ic'), special=mean('special'))
    if all(x['human_damage'] is not None for x in r):  # people's starts: their players' combos
        out.update(human_damage=mean('human_damage'), human_damage_p90=top('human_damage', 90),
                   human_damage_max=top('human_damage', 100), human_hits=mean('human_hits'),
                   human_hits_max=top('human_hits', 100),
                   better=float(np.mean([x['damage'] > x['human_damage'] for x in r])))
    return out


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--starts', required=True, help="combo_starts.py's folder")
    p.add_argument('--replays', help='the folder with index.csv (default: --starts\'s parent)')
    p.add_argument('--out', default=os.path.join(HERE, 'combo'))
    p.add_argument('--start', default=os.path.join(HERE, 'bc-d14.zip'))
    p.add_argument('--prior', default=os.path.join(HERE, 'bc-d14.zip'), help='the clone to stay near')
    p.add_argument('--prior-coef', type=float, default=0.02)
    p.add_argument('--delay', type=int, default=14)
    p.add_argument('--history', type=int, default=16)
    p.add_argument('--limit', type=int, default=1200, help='steps a trial lasts at most')
    p.add_argument('--focus', type=float, default=0.5,
                   help="share of trials from the top quarter of starts by their player's damage")
    p.add_argument('--resume', action='store_true', help="continue --out's combo.zip")
    p.add_argument('--rich', type=float, default=0.5,
                   help='share of trials with resources drawn from the 12 groups')
    p.add_argument('--eval-groups', nargs='*', default=['blue0', 'red0', 'cyan0', 'cyan3'])
    p.add_argument('--juggle', type=float, default=0.0,
                   help="weight of the juggle helper (the defender's untech time, shaped)")
    p.add_argument('--meter-cost', type=float, default=0.0,
                   help='reward taken off per bar of power gauge spent')
    p.add_argument('--leftover-cost', type=float, default=0.0,
                   help="reward taken off per the proration left at the combo's end")
    p.add_argument('--pool', type=int, default=500, help='training starts held in memory')
    p.add_argument('--envs', type=int, default=48)
    p.add_argument('--chunk', type=float, default=1e6)
    p.add_argument('--budget', type=float, default=8e6)
    p.add_argument('--lr', type=float, default=1e-4)
    p.add_argument('--ent-coef', type=float, default=0.005)
    p.add_argument('--torch-threads', type=int, default=6)
    return p.parse_args()


def main():
    import torch
    from stable_baselines3 import PPO
    args = parse()
    torch.set_num_threads(args.torch_threads)
    os.makedirs(args.out, exist_ok=True)
    rng = np.random.default_rng(0)
    train = load_starts(args.starts, 'train', args.pool, rng)
    test = load_starts(args.starts, 'test', 1000, rng)
    replays = args.replays or os.path.dirname(os.path.abspath(args.starts))
    t = time.time()
    matched = restore(args.data, replays, train + test)
    train = [st for st in train if 'state' in st]
    test = [st for st in test if 'state' in st]
    print(f'states made again from the replays in {time.time() - t:.0f}s: {matched} of '
          f'{len(train) + len(test)} at the view kept', flush=True)
    print(f'{len(train)} training starts, {len(test)} held out', flush=True)
    settings = dict(learning_rate=args.lr, n_steps=128, batch_size=3072, n_epochs=4,
                    gamma=0.99, gae_lambda=0.95, ent_coef=args.ent_coef, clip_range=0.2)
    trials = ComboTrials(args.data, train, args.envs, args.delay, args.history, args.limit,
                         seed=1, focus=args.focus, rich=args.rich, juggle=args.juggle,
                         meter_cost=args.meter_cost, gamma=settings['gamma'],
                         leftover_cost=args.leftover_cost)
    state = os.path.join(args.out, 'combo.json')
    history = []
    if args.resume:
        history = json.load(open(state))['history']
        args.start = os.path.join(args.out, 'combo.zip')
    model = PPO.load(args.start, env=trials, device='cpu', **settings)
    if args.prior_coef > 0:
        model.policy.set_prior(PPO.load(args.prior, device='cpu').policy, args.prior_coef,
                               args.ent_coef)
    with open(os.path.join(args.out, 'combo.config.json'), 'w') as f:
        json.dump(dict(frame_skip=1, history=args.history, delay=args.delay, chars=['ayu', None],
                       start=os.path.relpath(args.start, REPO),
                       prior=os.path.relpath(args.prior, REPO), prior_coef=args.prior_coef,
                       limit=args.limit, focus=args.focus, rich=args.rich,
                       juggle=args.juggle, meter_cost=args.meter_cost,
                       leftover_cost=args.leftover_cost,
                       ppo=settings), f, indent=1)
    def both(m):
        return evaluate(args, m, test), {g: evaluate(args, m, test, gauges=g)
                                         for g in args.eval_groups}

    def show(groups):
        return ' | '.join(f"{g} {r['damage']:.0f}/{r['damage_p90']:.0f}/{r['damage_max']:.0f}"
                          f" IC {r['ic']:.0%}" for g, r in groups.items())

    if not history:
        ev, groups = both(model)
        history = [dict(steps=model.num_timesteps, eval=ev, groups=groups)]
        print('before:', json.dumps(ev), flush=True)
        print('  by resources (average/90th percentile/most):', show(groups), flush=True)
    while model.num_timesteps < args.budget:
        t = time.time()
        model.learn(int(args.chunk), reset_num_timesteps=False)
        seconds = time.time() - t
        model.save(os.path.join(args.out, 'combo.zip'))
        ev, groups = both(model)
        history.append(dict(steps=model.num_timesteps, seconds=seconds,
                            prior_kl=model.policy.prior_kl, eval=ev, groups=groups))
        print(f'[{model.num_timesteps / 1e6:.1f}M steps, {seconds:.0f}s, KL '
              f'{model.policy.prior_kl:.3f}] ' + json.dumps(ev), flush=True)
        print('  by resources (average/90th percentile/most):', show(groups), flush=True)
        with open(os.path.join(args.out, 'combo.json'), 'w') as f:
            json.dump(dict(args=vars(args), history=history), f, indent=1)
    trials.close()
    print('done', flush=True)


if __name__ == '__main__':
    main()
