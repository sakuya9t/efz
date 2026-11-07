"""Reinforcement learning from the clone of people's Ayu (bc.py), kept close to how they
play: PPO, every frame, with a KL penalty toward the clone (efz_env.policy).

    python runs/human-ayu/finetune.py --data "$EFZ_DIR" --out runs/human-ayu/agent   # continues it
    python runs/human-ayu/finetune.py --data "$EFZ_DIR" --out runs/mine --prior-coef 0

Ayu plays player 1. In --cpu-share of the matches player 2 is the game's CPU, from
--level up (a level higher once it wins --promote of its matches there), playing a
character drawn from all of them (people's Ayu met them all); in the rest it
is Ayu played by one of: a frozen copy of the policy (taken at each chunk's start), the
clone, the agent of runs/curriculum (every 4 frames, as it was trained), and the --team:
clones of single players (bc.py --players), each with its own habits, so that no one
way of winning works against all of them (a league, as against self-play's narrowing),
and the --combo master (combo.py): a red-team opponent, seeing the game as it is
(without the reaction time the others have), that lands the most damaging combo it can,
so that a hit taken costs what it can. With --combo-teacher it is also the target of the
pull while the agent's own combo runs (people's play elsewhere). The reward
is the damage dealt minus taken (full bars) and 1 for the match, as the clone's critic
learnt it from people's matches. Each chunk (--chunk steps) is followed by matches
played to the end against the CPU (at the level of the chunk) and the curriculum
agent, with how it played (evaluate.py's Events: people's are people.py's). --out gets
model.zip, chunkNNN.zip, finetune.json (the evaluations) and config.json.

Any character (--char, from its clone: bc.py --char), Ayu by default; the mirror
opponents above (a frozen copy, the clone, --old, --team, --combo) play the learner's
character. --vs MODEL:CHAR adds frozen opponents of their own characters (an agent of
another run), which play --vs-share of the matches against agents (1: only they). With
--focus the learner also gets focus.py's shaping reward for what it is meant to be good
at ('setup': objects put out in free time, Mizuka's and Misuzu's traps; 'charge': Kano's
charge moves in free time): an exploiter with a style, trained against a frozen agent
(--vs) and kept close to its people's clone. --stop-win ends it once it beats every --vs
opponent that often. best.zip is the chunk whose evaluation won most (the mean over the
--vs opponents and the CPU), to be checked on more matches: a league forgets what it
stops meeting. --pfsp-window shares the matches by the last few evaluations, not the
last one alone. --vs-assist plays the --vs opponents with built-in combos
(combo_support.FairAssistOpponent), in training and evaluations: an agent trained with
--assist, met as it plays.

    python runs/human-ayu/finetune.py --char kano --start runs/human-ayu/kano/bc-d14.zip \\
        --prior runs/human-ayu/kano/bc-d14.zip --delay 14 --out runs/human-ayu/kano/exploiter \\
        --vs runs/human-ayu/agent-red/model.zip:ayu --vs-share 1 --cpu-share 0.25 --focus charge
"""

import argparse
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np
import torch
from stable_baselines3 import PPO
from stable_baselines3.common.callbacks import BaseCallback

from efz_env import ActionTable
from efz_env.sb3 import EfzSB3VecEnv, frozen, held, mixture

import evaluate as ev

TABLE = ActionTable()


OLD = os.path.join(REPO, 'runs', 'curriculum', 'model.zip')


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default=os.path.join(HERE, 'agent'))
    p.add_argument('--char', default='ayu', help="the learner's character")
    p.add_argument('--vs', nargs='*', default=[],
                   help='frozen opponents of other runs, MODEL.zip:CHAR (CHAR: ayu if left out)')
    p.add_argument('--vs-share', type=float, default=0.5,
                   help='share of the matches against agents that the --vs opponents play')
    p.add_argument('--focus', choices=('setup', 'charge'), help="a shaping reward (focus.py)")
    p.add_argument('--focus-coef', type=float, default=0.02)
    p.add_argument('--pfsp', type=float, default=0,
                   help='share out the --vs matches by (1 - the last evaluation\'s win) ** PFSP: '
                        'more against what it loses to (prioritized fictitious self-play; 0: evenly)')
    p.add_argument('--pfsp-window', type=int, default=1,
                   help='--pfsp by the average win of the last this many evaluations (a 16-match '
                        'evaluation swings by about 12%%)')
    p.add_argument('--stop-win', type=float, default=0,
                   help='stop once winning this share against every --vs opponent (0: never)')
    p.add_argument('--start', default=os.path.join(HERE, 'bc.zip'))
    p.add_argument('--prior', default=os.path.join(HERE, 'bc.zip'),
                   help='the policy to stay close to')
    p.add_argument('--prior-coef', type=float, default=0.1)
    p.add_argument('--old', default=OLD,
                   help='an agent of frame_skip 4 among the opponents')
    p.add_argument('--team', nargs='*', default=[], help="players' clones among the opponents")
    p.add_argument('--combo', help="combo.py's combo master: a red-team opponent")
    p.add_argument('--combo-teacher', action='store_true',
                   help="the combo master as the pull's target in the agent's own combos")
    p.add_argument('--combo-delay', type=int, default=0, help="the combo master's reaction time")
    p.add_argument('--lookahead', help="combo_library.py's library: the combo master tries its "
                   "options at each hit on copies of the game and plays the best (redteam.py)")
    p.add_argument('--combo-share', type=float, default=0.25,
                   help='share of the matches against agents that the combo master plays')
    p.add_argument('--level', type=int, default=2, help="the CPU's level to start at")
    p.add_argument('--promote', type=float, default=0.6,
                   help='share of wins against the CPU to move up a level')
    p.add_argument('--envs', type=int, default=64)
    p.add_argument('--practice', type=int, default=0,
                   help='of --envs, the environments of combo practice (practice.py): trials '
                        'from a hit, resources preset, against a dummy')
    p.add_argument('--practice-starts', default='own',
                   help="'own' (the learner's first hits against agents) or combo_starts.py's "
                        "folder (people's)")
    p.add_argument('--practice-replays',
                   help="the folder with index.csv for people's starts (default: the starts' parent)")
    p.add_argument('--practice-rich', type=float, default=0.5,
                   help='share of trials with resources drawn from the 12 groups')
    p.add_argument('--practice-pool', type=int, default=400, help='starts held at once')
    p.add_argument('--practice-limit', type=int, default=600, help='steps a trial lasts at most')
    p.add_argument('--assist', help="built-in combos (combo_support.ComboAssist): once the learner "
                                    "sees its hit, routes from this library (combo_library.py's) and "
                                    "its own play are tried on copies and the best played; those "
                                    "steps are kept out of the policy's loss")
    p.add_argument('--assist-score', default='damage', choices=('damage', 'value'),
                   help="--assist's and --vs-assist's choice of route: the most damaging, or the "
                        "most worth to the player (damage plus its critic's value of the game it "
                        "left: redteam.Planner)")
    p.add_argument('--vs-assist', help="the --vs opponents play with built-in combos, routes from "
                                       "this library (combo_support.FairAssistOpponent): agents "
                                       "trained with --assist, met as they play")
    p.add_argument('--practice-scale', type=float, default=1.0,
                   help="practice's reward per HP dealt, as a multiple of the match's (1/9999): "
                        "combo.py's is about 10")
    p.add_argument('--cpu-share', type=float, default=0.5)
    p.add_argument('--cpu-focus', nargs='*', default=[], metavar='CHAR:SHARE',
                   help="of the CPU's matches, SHARE with CHAR (the rest drawn from all 23): "
                        "kanna:0.25 for more of level-4 Kanna, whom it meets once in 23 "
                        "otherwise")
    p.add_argument('--history', type=int, default=16)
    p.add_argument('--delay', type=int, default=0,
                   help='steps late every player sees the game (the prior must be trained '
                        'with the same: bc.py --delay)')
    p.add_argument('--chunk', type=float, default=3e6)
    p.add_argument('--budget', type=float, default=6e7)
    p.add_argument('--minutes', type=float, default=5)
    p.add_argument('--eval', type=int, default=48)
    p.add_argument('--eval-every', type=int, default=1,
                   help='evaluate after every this many chunks (and the last): --assist plans in '
                        'every match evaluated, which is slow')
    p.add_argument('--cpu-chars', default='tiers', choices=('tiers', 'random'),
                   help="the level-4 CPU's characters in evaluations: a third per tier "
                        "(evaluate.TIERS) or drawn")
    p.add_argument('--lr', type=float, default=1e-4)
    p.add_argument('--ent-coef', type=float, default=0.005)
    p.add_argument('--torch-threads', type=int, default=8)
    args = p.parse_args()
    if args.char != 'ayu' and args.old == OLD:  # the curriculum agent plays Ayu only
        args.old = ''
    args.vs = [tuple(v.rsplit(':', 1)) if ':' in os.path.basename(v) else (v, 'ayu')
               for v in args.vs]
    return args


def ppo_settings(args):
    return dict(learning_rate=args.lr, n_steps=256, batch_size=8192, n_epochs=3,
                gamma=0.999, gae_lambda=0.98, ent_coef=args.ent_coef, clip_range=0.1,
                vf_coef=0.5, max_grad_norm=0.5)


def recent_wins(history, k, window=1):
    """The learner's win against each of the k --vs opponents, averaged over the last
    `window` evaluations that played it (None where none did)."""
    evals = [h['eval'] for h in history if h.get('eval')]
    out = []
    for j in range(k):
        w = [e[f'vs{j}']['win'] for e in evals if f'vs{j}' in e][-window:]
        out.append(float(np.mean(w)) if w else None)
    return out


def score(results, k):
    """An evaluation's worth, for best.zip: the mean win against the --vs opponents and the
    CPU, each counted once."""
    wins = [results[f'vs{j}']['win'] for j in range(k)] + [results['cpu']['win']]
    return float(np.mean(wins))


def vs_counts(n, wins, power):
    """n matches shared out among the --vs opponents: by (1 - win) ** power (PFSP), at
    least one each, by largest remainder; evenly without wins or power."""
    k = len(wins)
    if not power or any(w is None for w in wins):
        return [n // k + (j < n % k) for j in range(k)]
    w = np.array([(1 - x) ** power + 0.02 for x in wins])
    share = (n - k) * w / w.sum()
    counts = 1 + np.floor(share).astype(int)
    for j in np.argsort(-(share - np.floor(share)))[:n - counts.sum()]:
        counts[j] += 1
    return [int(c) for c in counts]


def make_env(args, opponents, vs, seed, level, wins=None, pool=None):
    """opponents: the mirror ones (the learner's character); vs: [(opponent, char)];
    wins: the learner's last wins against each of vs (for --pfsp); pool: --practice's
    starts (practice.StartPool), whose trials take the last --practice environments."""
    n = args.envs - args.practice
    n_cpu = int(round(n * args.cpu_share))
    cpu_envs = np.arange(n) >= n - n_cpu
    agents = np.flatnonzero(~cpu_envs)
    k_vs = int(round(len(agents) * args.vs_share)) if vs else 0
    vs_envs, mirror = agents[:k_vs], agents[k_vs:]
    # The mirror matches, shared out among the mirror opponents; the combo master (the
    # last of them) plays --combo-share of them. Then the --vs opponents' (after them).
    assignment = np.full(n, -1)
    assignment[mirror] = np.arange(len(mirror)) % max(1, len(opponents))
    red = len(opponents) - 1 if args.combo else -2
    if args.combo:
        k = int(round(len(mirror) * args.combo_share))
        others = len(opponents) - 1
        assignment[mirror] = [red if j < k else j % others for j in range(len(mirror))]
    if len(vs_envs):
        counts = vs_counts(len(vs_envs), wins or [None] * len(vs), args.pfsp)
        which = np.repeat(np.arange(len(vs)), counts)
        assignment[vs_envs] = len(opponents) + which
        print('--vs matches:', ', '.join(f'{c}' for c in counts), flush=True)
    chars = [(args.char, None)] * n
    for i in mirror:
        chars[i] = (args.char, args.char)
    for i in vs_envs:
        chars[i] = (args.char, vs[assignment[i] - len(opponents)][1])
    cpu_idx = list(np.flatnonzero(cpu_envs))
    for focus in args.cpu_focus:  # these CPU matches with one character
        name, share = focus.rsplit(':', 1)
        k = min(len(cpu_idx), int(round(np.sum(cpu_envs) * float(share))))
        for _ in range(k):
            chars[cpu_idx.pop()] = (args.char, name)
        print(f'--cpu-focus: {k} of the {int(np.sum(cpu_envs))} CPU matches with {name}', flush=True)
    opponents = list(opponents) + [o for o, _ in vs]
    # The combo master has a reaction time of its own.
    opponent_delay = np.where(assignment == red, min(args.combo_delay, args.delay), args.delay)
    env = EfzSB3VecEnv(args.data, n, opponent=mixture(opponents, assignment),
                        cpu_envs=cpu_envs, chars=chars, frame_skip=1, history=args.history,
                        delay=args.delay, opponent_delay=opponent_delay if args.delay else None,
                        max_frames=int(args.minutes * 3840), cpu_level=level,
                        reward_round=0.0, reward_match=1.0, seed=seed)
    for o in opponents:  # the lookahead red team saves this environment's games
        if hasattr(o, 'attach'):
            o.attach(env)
    if args.assist:
        import combo_support
        env = combo_support.ComboAssist(env, ASSIST['planner'], ASSIST['policy'],
                                        ASSIST.get('value'))
    if args.focus:
        import focus
        env = focus.Focus(env, args.focus, args.focus_coef, args.char)
    if args.practice:
        import practice
        from combo import ComboTrials
        trials = ComboTrials(args.data, [], args.practice, args.delay, args.history,
                             args.practice_limit, seed=seed, rich=args.practice_rich,
                             sample=pool.sample, reward_scale=args.practice_scale / 9999,
                             bootstrap=True)
        env = practice.Practice(env, trials, pool, harvest=~cpu_envs)
    return env


class AssistMask(BaseCallback):
    """--assist: the steps a route played (infos[i]['assisted']) out of the policy's loss:
    their advantages 0, the rest normalised (PPO's own normalisation is off). The critic
    learns from every step, so it learns what a hit is worth with the routes."""

    def _on_rollout_start(self):
        buf = self.model.rollout_buffer
        self.mask = np.zeros((buf.buffer_size, buf.n_envs), bool)

    def _on_step(self):
        pos = self.model.rollout_buffer.pos
        for e, info in enumerate(self.locals['infos']):
            if info.get('assisted'):
                self.mask[pos, e] = True
        return True

    def _on_rollout_end(self):
        adv, m = self.model.rollout_buffer.advantages, self.mask
        keep = adv[~m]
        adv[~m] = (keep - keep.mean()) / (keep.std() + 1e-8)
        adv[m] = 0.0
        ASSIST['steps'] = ASSIST.get('steps', 0) + m.size
        ASSIST['assisted'] = ASSIST.get('assisted', 0) + int(m.sum())


class KLLog(BaseCallback):
    def _on_rollout_end(self):
        self.logger.record('train/prior_kl', self.model.policy.prior_kl)

    def _on_step(self):
        return True


def evaluate(args, model_path, level):
    class A:
        pass
    a = A()
    a.data, a.minutes = args.data, args.minutes
    me = ev.Agent(model_path)
    if args.assist:  # it plays with its built-in combos
        import combo_support
        me = combo_support.FairComboAgent(me, ASSIST['planner'])
    out = {}
    a.chars = (args.char, args.cpu_chars if level == 4 else 'random')  # tiers: level 4's
    out['cpu'] = ev.play(a, me, 'cpu', args.eval, level)
    out['cpu']['level'] = level
    if args.old and os.path.exists(args.old):
        a.chars = (args.char, 'ayu')
        out['old'] = ev.play(a, me, ev.Agent(args.old), args.eval)
    for j, (path, char) in enumerate(args.vs):
        a.chars = (args.char, char)
        them = ev.Agent(path)
        if args.vs_assist:  # as it plays: with its built-in combos
            import combo_support
            them = combo_support.FairComboAgent(them, VS_ASSIST[j])
        out[f'vs{j}'] = ev.play(a, me, them, args.eval)
    if args.combo:
        a.chars = (args.char, args.char)
        red = RED['agent'] if RED else ev.Agent(args.combo)
        n = len(red.plans) if RED else 0
        out['red'] = ev.play(a, me, red, args.eval)
        if RED:  # what the hits the agent took were worth to the red team
            plans = red.plans[n:]
            out['red']['plans'] = dict(
                n=len(plans), potential=float(np.mean([p[0] for p in plans])) if plans else None,
                own=float(np.mean([p[1] for p in plans])) if plans else None,
                library=float(np.mean([p[2] for p in plans])) if plans else None,
                big=float(np.mean([p[0] >= 3000 for p in plans])) if plans else None)
    return out


RED = {}  # the lookahead red team: its planner, opponent and agent
ASSIST = {}  # --assist: its planner, the learner's own play on the copies, counts
VS_ASSIST = []  # --vs-assist: each --vs opponent's planner


def show(results):
    parts = []
    for k, r in results.items():
        s = r['sides'][0]
        parts.append(f"{k}: win {r['win']:.0%} loss {r['loss']:.0%} cut {r['cut']:.0%}, "
                     f"{s['presses_per_second']} presses/s, per min {s['jumps_per_min']} jumps "
                     f"{s['guard_ground_per_min']} guards {s['hit_ground_per_min']}+"
                     f"{s['hit_air_per_min']} hits, RG {s['rg_ground']}/{s['rg_air']} "
                     f"RC {s['rc']}, after RG move/hit {s['rg_move']}/{s['rg_punish']}, "
                     f"combo avg/p90/max {s.get('combo_damage')}/{s.get('combo_damage_p90')}/"
                     f"{s.get('combo_damage_max')} IC {s.get('combo_ic')}"
                     + (f", taken {r['sides'][1].get('combo_damage_per_min')}/min" if k == 'red' else '')
                     + (' [' + ', '.join(f"{t} {v['win']:.0%}" + (
                         f" (HP {v['opp_hp_taken']:.0%})" if t == 'hardest' and
                         v.get('opp_hp_taken') is not None else '')
                         for t, v in r['by_tier'].items()) + ']'
                        if k == 'cpu' and r.get('by_tier') else ''))
    return ' | '.join(parts)


def main():
    args = parse()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    torch.set_num_threads(args.torch_threads)
    os.makedirs(args.out, exist_ok=True)
    state_path = os.path.join(args.out, 'finetune.json')
    history, start, level = [], args.start, args.level
    if os.path.exists(state_path):
        with open(state_path) as f:
            saved = json.load(f)
        history, level = saved['history'], saved['level']
        start = os.path.join(args.out, 'model.zip')
        print(f'continuing {args.out} after chunk {len(history)}', flush=True)
    settings = ppo_settings(args)
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(dict(frame_skip=1, history=args.history, delay=args.delay, chars=[args.char, None],
                       vs=[[os.path.relpath(p, REPO), c] for p, c in args.vs], vs_share=args.vs_share,
                       pfsp=args.pfsp, pfsp_window=args.pfsp_window, cpu_focus=args.cpu_focus,
                       focus=args.focus, focus_coef=args.focus_coef,
                       prior=os.path.relpath(args.prior, REPO), prior_coef=args.prior_coef,
                       team=[os.path.relpath(t, REPO) for t in args.team],
                       combo=args.combo and os.path.relpath(args.combo, REPO),
                       combo_teacher=args.combo_teacher, combo_delay=args.combo_delay,
                       lookahead=args.lookahead, assist=args.assist, vs_assist=args.vs_assist,
                       assist_score=args.assist_score,
                       practice=args.practice, practice_starts=args.practice_starts,
                       practice_rich=args.practice_rich, practice_pool=args.practice_pool,
                       practice_limit=args.practice_limit, practice_scale=args.practice_scale,
                       level=args.level, ppo=settings,
                       actions=[TABLE.describe(i) for i in range(len(TABLE))]), f, indent=1)
    prior = PPO.load(args.prior, device='cpu')
    clone = frozen(prior)
    old = held(frozen(PPO.load(args.old, device='cpu')), 4) if args.old else None
    team = [frozen(PPO.load(t, device='cpu')) for t in args.team]
    master = PPO.load(args.combo, device='cpu') if args.combo else None
    if master is not None and args.lookahead:
        import macros
        import redteam
        planner = redteam.Planner(args.data, macros.load_library(args.lookahead, 300), master)
        RED.update(opponent=redteam.RedTeamOpponent(planner, master),
                   agent=redteam.RedTeamAgent(planner, args.combo))
        team.append(RED['opponent'])
    elif master is not None:
        team.append(frozen(master))
    opponents = lambda snapshot: [o for o in (snapshot, clone, old) if o is not None] + team
    if args.vs_assist:
        import combo_support
        import macros
        import redteam
        library = macros.load_library(args.vs_assist, 300)
        vs = []
        for p, c in args.vs:
            m = PPO.load(p, device='cpu')
            VS_ASSIST.append(redteam.Planner(args.data, library, m, score=args.assist_score))
            vs.append((combo_support.FairAssistOpponent(VS_ASSIST[-1], m), c))
    else:
        vs = [(frozen(PPO.load(p, device='cpu')), c) for p, c in args.vs]
    if args.assist:
        import macros
        import redteam
        ASSIST['planner'] = redteam.Planner(args.data, macros.load_library(args.assist, 300),
                                            PPO.load(start, device='cpu'), score=args.assist_score)
        ASSIST['policy'] = None  # (set to each chunk's learner before its environment)
    pool = None
    if args.practice:
        import practice
        if args.practice_starts == 'own':
            pool = practice.StartPool(args.practice_pool, seed=len(history))
        else:
            replays = args.practice_replays or os.path.dirname(os.path.abspath(args.practice_starts))
            pool = practice.StartPool.people(args.data, args.practice_starts, replays,
                                             limit=args.practice_pool)
            print(f"practice: {len(pool.starts)} of people's starts {pool.kinds()}", flush=True)
    env = make_env(args, opponents(clone), vs, len(history), level, pool=pool)
    model = PPO.load(start, env=env, device='cpu', **settings)
    if args.assist:
        model.normalize_advantage = False  # AssistMask normalises, the routes' steps left out
    if args.prior_coef > 0:
        teacher = master.policy if master is not None and args.combo_teacher else None
        model.policy.set_prior(prior.policy, args.prior_coef, args.ent_coef, combo=teacher)
    print('starting from', start, flush=True)
    if not history:
        before = evaluate(args, start, level)
        print('before:', show(before), flush=True)
        worth = score(before, len(args.vs)) if args.vs else None
        if worth is not None:  # the start is the best so far
            import shutil
            shutil.copyfile(start, os.path.join(args.out, 'best.zip'))
        history.append(dict(steps=0, level=level, score=worth, eval=before))
    while model.num_timesteps < args.budget:
        env.close()
        wins = recent_wins(history, len(vs), args.pfsp_window)
        if args.assist:
            ASSIST['policy'] = frozen(model)
            if args.assist_score == 'value':
                import redteam
                ASSIST['value'] = redteam.critic(model)
        env = make_env(args, opponents(frozen(model)), vs, len(history) + 1, level, wins, pool)
        model.set_env(env)
        if pool is not None and pool.growing and len(pool.starts) < 48:
            n = practice.fill(pool, env.matches, model, mask=env.mask)
            print(f'practice: {n} starts of its own to begin with {pool.kinds()}', flush=True)
        t = time.time()
        callbacks = [KLLog()] + ([AssistMask()] if args.assist else [])
        model.learn(int(args.chunk), reset_num_timesteps=False, callback=callbacks)
        seconds = time.time() - t
        path = os.path.join(args.out, 'model.zip')
        model.save(path)
        model.save(os.path.join(args.out, f'chunk{len(history):03d}.zip'))
        due = len(history) % args.eval_every == 0 or model.num_timesteps >= args.budget
        results = evaluate(args, path, level) if due else None
        returns = [e['r'] for e in model.ep_info_buffer]
        focus = env.take() if args.focus else None  # the focus' events, a minute of play
        focus_rate = focus['events'] / max(1, focus['steps']) * 3840 if focus else None
        assist = None
        if args.assist:  # the chunk's built-in combos: plans made, steps they played
            assist = dict(env.assist.take_plans() if hasattr(env, 'assist') else {},
                          assisted=round(ASSIST.pop('assisted', 0) / max(1, ASSIST.pop('steps', 1)), 4))
        vs_plans = None
        if args.vs_assist:  # the --vs opponents' built-in combos in the chunk's matches
            vs_plans = [o.assist.take_plans() for o, _ in vs]
        trials = None
        if pool is not None:  # the practice of the chunk, and the pool it drew from
            trials = dict(env.take_trials(), pool=len(pool.starts), kinds=pool.kinds())
        if results and args.vs:  # the best evaluated so far (best.zip; the 64-match check is after)
            worth = score(results, len(args.vs))
            best = max((h.get('score', -1) for h in history), default=-1)
            if worth > best:
                model.save(os.path.join(args.out, 'best.zip'))
                print(f'best so far ({worth:.3f}): best.zip', flush=True)
        else:
            worth = None
        history.append(dict(steps=model.num_timesteps, level=level, train_seconds=seconds,
                            score=worth,
                            prior_kl=model.policy.prior_kl,
                            ep_return=float(np.mean(returns)) if returns else None,
                            focus_per_min=focus_rate, practice=trials, assist=assist,
                            vs_assist=vs_plans, eval=results))
        print(f'[{model.num_timesteps / 1e6:.1f}M steps, {seconds:.0f}s, L{level}, '
              f'KL {model.policy.prior_kl:.3f}'
              + (f', {args.focus} {focus_rate:.2f}/min' if focus else '') + '] '
              + (show(results) if results else 'not evaluated (--eval-every)'), flush=True)
        if assist and assist.get('plans'):
            print(f"  assist: {assist['plans']} plans, a route in {assist['route']:.0%}, best "
                  f"{assist['best']} (own play {assist['own']}); {assist['assisted']:.1%} of steps",
                  flush=True)
        for j, v in enumerate(vs_plans or []):
            if v.get('plans'):
                print(f"  vs{j} assist: {v['plans']} plans, a route in {v['route']:.0%}, best "
                      f"{v['best']} (own play {v['own']})", flush=True)
        if trials and trials.get('trials'):
            print(f"  practice: {trials['trials']} trials, combo {trials['damage']}/"
                  f"{trials['damage_p90']}/{trials['damage_max']}, {trials['hits']} hits, IC "
                  f"{trials['ic']:.0%}, special {trials['special']:.0%}; pool {trials['pool']}",
                  flush=True)
        if results and results['cpu']['win'] >= args.promote and level < 4:
            level += 1
            print(f'promoted to level {level}', flush=True)
        with open(state_path, 'w') as f:
            json.dump(dict(level=level, history=history), f, indent=1)
        if results and args.stop_win and args.vs and all(results[f'vs{j}']['win'] >= args.stop_win
                                             for j in range(len(args.vs))):
            print(f'beats every --vs opponent {args.stop_win:.0%} of the time: stopping', flush=True)
            break
    env.close()
    print('done', flush=True)


if __name__ == '__main__':
    main()
