"""Population-based training with a league, over Stable-Baselines3's PPO.

    from efz_env.pbt import Population
    pop = Population('runs/pbt', '/path/to/EFZ', size=6, steps_per_generation=200_000)
    pop.run(generations=20)          # resumes from runs/pbt/state.json if it is there

Each generation:

1. Train. Each member in turn learns with PPO for steps_per_generation steps against a
   mix of opponents: the game's CPU in cpu_share of the matches; in the rest, other
   members as they were when the generation began, itself, and older versions from the
   archive. Opponents a member scored badly against are picked more often (prioritized
   fictitious self-play: weight (1 - score)^2).
2. Rate. Every pair of members, and each member against the CPU, play eval_matches
   matches, half on each side. A Bradley-Terry fit of the results gives Elo ratings,
   the CPU fixed at 1000. A match that runs out of time counts for whoever dealt more
   damage.
3. Select. The bottom `truncation` of the members by rating copy the weights and
   settings of a random member of the top `truncation` (Jaderberg et al., 2017).
4. Vary. Those copied settings are perturbed: each multiplied by 0.8 or 1.25 and kept in
   bounds, or now and then drawn again.

The settings evolved (SEARCH_SPACE) are PPO's learning rate and entropy bonus and the
reward's weights for rounds and the match (damage stays 1). The run's folder holds
state.json (everything needed to resume), members/<id>.zip, archive/ (older versions,
opponents for later generations), best.zip (the top-rated member) with config.json for
examples/play.py, and log.jsonl (a line per generation).
"""

import json
import math
import os
import shutil
import time

import numpy as np
from stable_baselines3 import PPO

from .actions import ActionTable
from .sb3 import EfzSB3VecEnv, frozen, mixture
from .vec import EfzVecEnv

# name: (low, high, scale). Names in ENV_SETTINGS go to the environment, the rest to PPO.
SEARCH_SPACE = {
    'learning_rate': (1e-4, 1e-3, 'log'),
    'ent_coef': (1e-3, 3e-2, 'log'),
    'reward_round': (0.0, 0.5, 'linear'),
    'reward_match': (0.5, 2.0, 'linear'),
}
ENV_SETTINGS = ('reward_round', 'reward_match')

PPO_DEFAULTS = dict(n_steps=128, batch_size=2048, n_epochs=4, gamma=0.99, gae_lambda=0.95,
                    clip_range=0.2, policy_kwargs=dict(net_arch=[256, 256]))

CPU = 'cpu'


def sample(rng, space=SEARCH_SPACE):
    out = {}
    for name, (lo, hi, scale) in space.items():
        if scale == 'log':
            out[name] = float(math.exp(rng.uniform(math.log(lo), math.log(hi))))
        else:
            out[name] = float(rng.uniform(lo, hi))
    return out


def perturb(rng, settings, space=SEARCH_SPACE, resample=0.2):
    """Each setting multiplied by 0.8 or 1.25 and kept in bounds, or drawn again."""
    out = dict(settings)
    fresh = sample(rng, space)
    for name, (lo, hi, scale) in space.items():
        if rng.random() < resample:
            out[name] = fresh[name]
        else:
            value = out.get(name, fresh[name])
            if scale == 'linear' and value == 0:
                value = (hi - lo) * 0.05
            out[name] = float(min(hi, max(lo, value * (0.8 if rng.random() < 0.5 else 1.25))))
    return out


def bradley_terry(results, players, anchor=CPU, anchor_elo=1000.0, iterations=500):
    """Elo ratings from (a, b, score of a) results (1 win, 0.5 draw, 0 loss) by a
    Bradley-Terry fit (minorization-maximization), `anchor` fixed at anchor_elo. Each
    player gets one virtual draw against the anchor, so no rating is infinite."""
    index = {p: i for i, p in enumerate(players)}
    n = len(players)
    wins = np.zeros(n)
    games = np.zeros((n, n))
    for a, b, s in results:
        i, j = index[a], index[b]
        wins[i] += s
        wins[j] += 1 - s
        games[i, j] += 1
        games[j, i] += 1
    k = index[anchor]
    for i in range(n):
        if i != k:
            wins[i] += 0.5
            wins[k] += 0.5
            games[i, k] += 1
            games[k, i] += 1
    strength = np.ones(n)
    for _ in range(iterations):
        for i in range(n):
            denom = np.sum(games[i] / (strength[i] + strength))
            if denom > 0:
                strength[i] = max(wins[i], 1e-9) / denom
        strength /= strength[k]
    return {p: float(anchor_elo + 400 * math.log10(strength[index[p]])) for p in players}


class Population:
    def __init__(self, out, data_dir=None, *, size=6, steps_per_generation=200_000,
                 num_envs=32, num_threads=0, frame_skip=4, max_frames=64 * 240,
                 chars=(None, None), char_pool=None, stage=None, stage_pool=None,
                 cpu_level=2, cpu_share=0.25, opponents_per_member=3, archive_size=12,
                 eval_matches=32, eval_envs=128, eval_max_frames=None,
                 truncation=0.25, seed=0, device='cpu', ppo=None, verbose=1):
        self.out = out
        self.data_dir = data_dir or os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
        self.size = size
        self.steps = int(steps_per_generation)
        self.num_envs = num_envs
        self.match_config = dict(frame_skip=frame_skip, cpu_level=cpu_level,
                                 num_threads=num_threads)
        self.max_frames = max_frames
        self.matches = dict(chars=chars, char_pool=char_pool, stage=stage,
                            stage_pool=stage_pool)
        self.cpu_share = cpu_share
        self.opponents_per_member = opponents_per_member
        self.archive_size = archive_size
        self.eval_matches = max(2, eval_matches - eval_matches % 2)
        self.eval_envs = eval_envs
        self.eval_max_frames = eval_max_frames or max_frames
        # A member's turn restarts its matches: unless each sees a whole match or more,
        # no match ends in training and the reward for winning one is never seen.
        per_match = max_frames / frame_skip if max_frames else float('inf')
        per_turn = self.steps / num_envs
        if verbose and per_turn < 1.5 * per_match:
            print(f'warning: a turn gives each match {per_turn:.0f} steps and a match can '
                  f'take {per_match:.0f}: few matches will end in training, so the reward '
                  'for winning is rarely seen. Raise steps_per_generation, or lower '
                  'num_envs or max_frames.')
        self.truncation = truncation
        self.seed = seed
        self.device = device
        self.ppo = dict(PPO_DEFAULTS, **(ppo or {}))
        self.verbose = verbose
        self.table = ActionTable()
        os.makedirs(os.path.join(out, 'members'), exist_ok=True)
        os.makedirs(os.path.join(out, 'archive'), exist_ok=True)
        self.state_path = os.path.join(out, 'state.json')
        if os.path.exists(self.state_path):
            with open(self.state_path) as f:
                self.state = json.load(f)
            if verbose:
                print(f"resuming {out} at generation {self.state['generation']}")
        else:
            rng = np.random.default_rng(seed)
            self.state = {
                'generation': 0, 'archive': [], 'scores': {},
                'members': [{'id': f'm{i:02d}', 'settings': sample(rng), 'parent': None,
                             'born': 0, 'steps': 0, 'elo': [], 'vs_cpu': []}
                            for i in range(size)],
            }

    # --- Files.

    def _path(self, relative):
        return os.path.join(self.out, relative)

    def _model(self, member):
        return os.path.join('members', member['id'] + '.zip')

    def _save_state(self):
        tmp = self.state_path + '.tmp'
        with open(tmp, 'w') as f:
            json.dump(self.state, f, indent=1)
        os.replace(tmp, self.state_path)

    def _log(self, text):
        if self.verbose:
            print(text, flush=True)

    # --- Policies.

    def _policy(self, relative, cache):
        if relative not in cache:
            cache[relative] = frozen(PPO.load(self._path(relative), device=self.device))
        return cache[relative]

    # --- 1. Training.

    def _opponents(self, member, rng):
        """K opponents (model paths) for `member`, by prioritized fictitious self-play."""
        members = [m for m in self.state['members'] if os.path.exists(self._path(self._model(m)))]
        scores = self.state['scores'].get(member['id'], {})
        candidates, weights = [], []
        for m in members:
            p = scores.get(m['id'], 0.5)
            candidates.append(self._model(m))
            weights.append((1 - p) ** 2 + 0.05)
        for path in self.state['archive']:
            candidates.append(path)
            weights.append(0.1)
        if not candidates:
            return []
        k = min(self.opponents_per_member, len(candidates))
        weights = np.asarray(weights) / np.sum(weights)
        picks = rng.choice(len(candidates), size=k, replace=False, p=weights)
        return [candidates[i] for i in picks]

    def _train(self, member, generation, rng, cache):
        opponents = self._opponents(member, rng)
        n = self.num_envs
        n_cpu = n if not opponents else int(round(self.cpu_share * n))
        assignment = np.full(n, -1)
        if opponents:
            assignment[n_cpu:] = np.arange(n - n_cpu) % len(opponents)
        policies = [self._policy(o, cache) for o in opponents]
        cpu_envs = assignment < 0
        opponent = mixture(policies, assignment) if policies else (lambda obs: np.zeros(len(obs), np.int64))
        settings = member['settings']
        venv = EfzSB3VecEnv(self.data_dir, n, opponent=opponent, cpu_envs=cpu_envs,
                            action_table=self.table, max_frames=self.max_frames,
                            seed=self.seed * 100_003 + generation * 1009 + int(member['id'][1:]),
                            reward_round=settings['reward_round'],
                            reward_match=settings['reward_match'],
                            **self.match_config, **self.matches)
        ppo = {k: v for k, v in settings.items() if k not in ENV_SETTINGS}
        path = self._path(self._model(member))
        batch = min(self.ppo['batch_size'], self.ppo['n_steps'] * n)
        start = time.time()
        if os.path.exists(path):
            model = PPO.load(path, env=venv, device=self.device, batch_size=batch, **ppo)
        else:
            model = PPO('MlpPolicy', venv, device=self.device, verbose=0,
                        seed=self.seed + int(member['id'][1:]),
                        **dict(self.ppo, batch_size=batch), **ppo)
        model.learn(self.steps, reset_num_timesteps=False)
        model.save(path)
        venv.close()
        member['steps'] += self.steps
        returns = [e['r'] for e in model.ep_info_buffer]
        ended = (f'{len(returns)} matches ended, mean return {np.mean(returns):+.2f}'
                 if returns else 'no match ended')
        self._log(f"  {member['id']}: {self.steps:,} steps in {time.time() - start:.0f}s against "
                  f"CPU x{n_cpu}, {[os.path.basename(o)[:-4] for o in opponents]}; {ended}")

    # --- 2. Rating.

    def _play(self, pairs, cache, seed):
        """Plays the matchups `pairs` ((player 1, player 2) as model paths or CPU, one match
        each); returns player 1's score in each."""
        scores = []
        for start in range(0, len(pairs), self.eval_envs):
            chunk = pairs[start:start + self.eval_envs]
            n = len(chunk)
            env = EfzVecEnv(self.data_dir, n, autoreset='disabled', seed=seed + start,
                            max_frames=self.eval_max_frames, **self.match_config)
            env.set_matches(cpu=[(a == CPU, b == CPU) for a, b in chunk], **self.matches)
            obs = env.reset()
            players = sorted({p for pair in chunk for p in pair if p != CPU})
            sides = [[np.array([i for i, pair in enumerate(chunk) if pair[s] == p], int)
                      for p in players] for s in (0, 1)]
            controls = np.zeros((n, 2), np.uint8)
            done = np.zeros(n, bool)
            result = np.full(n, 0.5)
            while not done.all():
                for s in (0, 1):
                    for p, idx in zip(players, sides[s]):
                        idx = idx[~done[idx]]
                        if len(idx):
                            controls[idx, s] = self.table.to_bytes(
                                self._policy(p, cache)(obs[idx, s]))
                obs, _, terminated, truncated, info = env.step(controls)
                new = (terminated | truncated) & ~done
                if new.any():
                    winner = info['winner'][new]
                    margin = info['episode_return'][new, 0]
                    result[new] = np.where(winner == 0, 1.0, np.where(
                        winner == 1, 0.0, np.where(margin > 0, 1.0, np.where(margin < 0, 0.0, 0.5))))
                    done |= new
            env.close()
            scores.extend(result.tolist())
        return scores

    def _rate(self, generation, cache):
        ids = [m['id'] for m in self.state['members']]
        models = {m['id']: self._model(m) for m in self.state['members']}
        half = self.eval_matches // 2
        pairs, labels = [], []
        for i, a in enumerate(ids):
            for b in ids[i + 1:] + [CPU]:
                pb = models.get(b, CPU)
                for _ in range(half):
                    pairs.append((models[a], pb))
                    labels.append((a, b, False))
                    pairs.append((pb, models[a]))
                    labels.append((a, b, True))
        scores = self._play(pairs, cache, seed=self.seed * 7919 + generation * 104729)
        results = []
        table = {a: {} for a in ids}
        for (a, b, swapped), s in zip(labels, scores):
            s_a = 1 - s if swapped else s
            results.append((a, b, s_a))
            table[a].setdefault(b, []).append(s_a)
            if b != CPU:
                table[b].setdefault(a, []).append(1 - s_a)
        elo = bradley_terry(results, ids + [CPU])
        means = {a: {b: float(np.mean(v)) for b, v in row.items()} for a, row in table.items()}
        return elo, means

    # --- 3, 4. Selection and variation.

    def _exploit_explore(self, ranked, generation, rng):
        n = len(ranked)
        if n < 2:
            return []
        cut = max(1, int(round(n * self.truncation)))
        cut = min(cut, n // 2)
        top, bottom = ranked[:cut], ranked[-cut:]
        changes = []
        for loser in bottom:
            winner = top[rng.integers(len(top))]
            shutil.copyfile(self._path(self._model(winner)), self._path(self._model(loser)))
            loser['settings'] = perturb(rng, winner['settings'])
            loser['parent'] = winner['id']
            loser['born'] = generation
            loser['steps'] = winner['steps']
            changes.append((loser['id'], winner['id']))
        return changes

    # --- A generation.

    def generation(self):
        g = self.state['generation'] + 1
        rng = np.random.default_rng(self.seed * 1_000_003 + g)
        self._log(f'generation {g}: training')
        cache = {}  # the opponents' policies as the generation began
        for m in self.state['members']:
            if os.path.exists(self._path(self._model(m))):
                self._policy(self._model(m), cache)
        for m in self.state['members']:
            self._train(m, g, rng, cache)
        self._log(f'generation {g}: rating')
        rate_cache = {}  # the members as trained
        start = time.time()
        elo, scores = self._rate(g, rate_cache)
        for m in self.state['members']:
            m['elo'].append(round(elo[m['id']], 1))
            m['vs_cpu'].append(round(scores[m['id']].get(CPU, float('nan')), 3))
        ranked = sorted(self.state['members'], key=lambda m: -m['elo'][-1])
        self._report(g, ranked, time.time() - start)
        best = ranked[0]
        shutil.copyfile(self._path(self._model(best)), self._path('best.zip'))
        for m in self.state['members']:
            name = os.path.join('archive', f"g{g:03d}-{m['id']}.zip")
            shutil.copyfile(self._path(self._model(m)), self._path(name))
            self.state['archive'].append(name)
        while len(self.state['archive']) > self.archive_size:
            old = self.state['archive'].pop(0)
            if os.path.exists(self._path(old)):
                os.remove(self._path(old))
        changes = self._exploit_explore(ranked, g, rng)
        for loser, winner in changes:
            self._log(f'  {loser} <- {winner} (weights and settings, perturbed)')
        self.state['scores'] = scores
        self.state['generation'] = g
        with open(self._path('log.jsonl'), 'a') as f:
            f.write(json.dumps({'generation': g, 'elo': elo, 'scores': scores,
                                'members': self.state['members'], 'replaced': changes}) + '\n')
        with open(self._path('config.json'), 'w') as f:
            json.dump({'frame_skip': self.match_config['frame_skip'], 'best': best['id'],
                       'generation': g, 'elo': best['elo'][-1],
                       'actions': [self.table.describe(i) for i in range(len(self.table))]},
                      f, indent=1)
        self._save_state()
        return elo

    def _report(self, g, ranked, seconds):
        self._log(f'generation {g}: ratings ({seconds:.0f}s; the CPU at level '
                  f"{self.match_config['cpu_level']} is 1000)")
        self._log('  member   Elo   vs CPU   lr        entropy  round  match  parent  steps')
        for m in ranked:
            s = m['settings']
            self._log(f"  {m['id']}  {m['elo'][-1]:6.0f}  {m['vs_cpu'][-1]:5.0%}   "
                      f"{s['learning_rate']:.2e}  {s['ent_coef']:.4f}   {s['reward_round']:.2f}   "
                      f"{s['reward_match']:.2f}   {m['parent'] or '-':6}  {m['steps']:,}")

    def run(self, generations):
        """Runs until `generations` generations have been done (resuming)."""
        while self.state['generation'] < generations:
            self.generation()
        return self.state
