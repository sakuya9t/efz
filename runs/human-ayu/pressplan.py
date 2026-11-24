"""The planned pressure (python/efz_env/modules.py; the kind 'pressplan' of an agent.json,
of evaluate.py --p1-module): when the agent has seen a move of its own guarded and can act
again next to its opponent, people's follow-ups from the library (pressure_library.py) are
tried on copies of the game, each against the ways a guarding player answers, and one is
chosen by what the match has shown of this opponent. okiplan.py's planner, from a guard
instead of a knockdown.

    pressplan:library=~/data/efz-replays/pressure-library.npz[,per_plan=10,doubt=0.3,carry]

Why (docs/training-v2-log.md, "The games of 15 November, evening"): the agent's pressure is a
low or nothing after each guard, with no throw and no overhead, so a guard held costs
nothing and a jump gets out; people's Ayu opens a guard with a throw (3.6% of its
follow-ups, 88% of them land) and an overhead after a dash (4.3%, 39%). PPO never kept
either: a throw's range and timing are a planner's problem.

- **When.** The agent has seen (its view, `delay` steps late) a contact on its
  opponent's guard within the last `fresh` steps, and the game as it is has the agent free
  on the ground within `near` pixels of an opponent on the ground that isn't being hit:
  the first such step after the contact, once (a guard seen again after a plan, the
  planned move's own, is another).
- **The options.** The library's entries taken at the same frame advantage (the steps of
  guard the opponent has left, or has been free for: within `slack`) and distance (within
  `tolerance` pixels), at most `per_class` of a kind (the next move's way in and height;
  a throw; no move: holding, backing off, jumping) and `per_plan` in all; a wait (a
  crouching guard for `wait` steps past the opponent's guard: the bait); and its own
  play.
- **The answers.** A guarding player that goes on guarding crouching, or standing,
  reverses (its fastest invincible move its gauges allow, the motion input so that the
  button lands on its first free step), jumps away, or presses a button. Worth and choice
  as okiplan's: the HP taken less the HP lost by `window` steps after the guard ends, a
  first hit either way counted as a combo; the shares of the answers from the memory's
  counts of what this opponent did after its guards (efz_env.memory's p_*), over a prior;
  the draw by `doubt` (the mix that holds up if the shares are wrong) or `temperature`.

It plans from what the agent sees; the copies are of the game as it is, as the routes'
are. It lets go when its inputs end, when the agent sees itself hit, or when another
module (the routes, at a hit seen) took a step.

**Live** (`live`: how a game can play it, port/agent). A plan takes time, and the game
has none between seeing a guard and acting on it. So on the step a move of the agent's
touches the opponent's guard (the game as it is), the agent's next `delay` inputs are
chosen at once, its own play's from the views it already has (what it would have pressed
anyway: it sees the guard only after them), and the plan is made for the game as those
inputs leave it, the opponent holding the guard it holds: then a crouching guard until
the agent is free (at most `max_wait` steps, else nothing is planned), then the option
drawn. If the game isn't where the plan expected once those inputs are played (the
opponent did something else), the rest is dropped. A contact while a planned move's own
inputs are being played plans again from it, the rest of those inputs the first of the
next `delay`.

options: live (false), max_wait (20), per_plan (10), per_class (2), window (60), wait (24), tolerance (pixels, 16),
slack (steps, 2), near (160), fresh (40), temperature (200), doubt (0.3), hit_worth (1300),
hurt_worth (1200), sight (0; N: the guard by sight, okiplan.py's), prior (8: the guards the prior counts as), carry, fixed, seed.
"""

import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

from efz_env import modules
from efz_env.actions import encode
from efz_env.history import InputHistory, action_labels
from efz_env.memory import K, Memory

import okiplan
import tactics
from okiplan import (ANSWERS, CROUCH_GUARD, DX, OPP_ACT, OPP_CHAR, OPP_HITSTUN, OPP_X,
                     SELF_ACT, SELF_AIR, SELF_HITSTUN, TABLE)

OPP_AIR, OPP_FRAME = 71, 51
GUARDS = np.array(sorted(tactics.GUARDS))
GUARDS_CROUCH = (0x99, 0x9a, 0x9b, 0xa9)
ROUND_OVER = okiplan.ROUND_OVER
FREE = np.array(sorted(tactics.FREE))
# What a guarding player does next, the community's (docs/training-v2-log.md, "What people's
# habits look like": a move out of pressure on 0.27-0.48 of the guards by player, few of
# them invincible; the jumps from pressure_library's and five.py's counts).
PRIOR = dict(reversal=0.05, mash=0.22, jump=0.15, crouch=0.8)
LOOK = 80  # the most steps the guard's end is looked for


def load_library(path):
    """pressure_library.py's entries, their inputs as an agent's actions: dicts with
    actions, cls, adv, distance, corner, opponent (efz_env.export.load_press: what an
    agent file is written from)."""
    from efz_env.export import load_press
    return load_press(path)


def belief(counts, prior=8.0, sight=False):
    """The shares of ANSWERS a player is expected to give after guarding: efz_env.memory's
    counts (one environment's: its answers after its guards ended, its guards' height)
    over the community's prior. sight: as okiplan.belief's (the guard by sight)."""
    n = float(counts[K['p_n']])
    inv = float(counts[K['p_inv']])
    move = max(0.0, float(counts[K['p_move']]) - inv)
    away = float(counts[K['p_jump']] + counts[K['p_back']])
    rev = (prior * PRIOR['reversal'] + inv) / (prior + n)
    mash = (prior * PRIOR['mash'] + move) / (prior + n)
    jump = (prior * PRIOR['jump'] + away) / (prior + n)
    guard = max(0.0, 1.0 - rev - mash - jump)
    g = float(counts[K['g_n']])
    crouch = (prior * PRIOR['crouch'] + float(counts[K['g_crouch']])) / (prior + g)
    if sight:
        crouch = 1 - okiplan.SIGHT_STAND
    return np.array([guard * crouch, guard * (1 - crouch), rev, jump, mash])


class Followups:
    """The library, as arrays to choose a guarded move's follow-ups from."""

    def __init__(self, library, per_plan=10, per_class=2, tolerance=16, slack=2):
        self.library, self.per_plan, self.per_class = library, per_plan, per_class
        self.tolerance, self.slack = tolerance, slack
        self.adv = np.array([m['adv'] for m in library])
        self.distance = np.array([m['distance'] for m in library], float)
        self.corner = np.array([bool(m['corner']) for m in library])
        self.victim = np.array([m['opponent'] for m in library])
        self.cls = np.array([m['cls'] for m in library])

    def pick(self, adv, distance, victim, corner):
        """The entries to try at the frame advantage `adv`, `distance` pixels from the
        opponent `victim`, in the corner or not: [(index, its actions)], the closest first
        (in distance, then advantage; the same character and place a little closer), at
        most per_class of a kind, a kind's best before any kind's second, per_plan in
        all."""
        off, late = np.abs(self.distance - distance), np.abs(self.adv - adv)
        ok = (off <= self.tolerance) & (late <= self.slack)
        score = off + 4.0 * late + 6.0 * (self.victim != victim) + 10.0 * (self.corner != bool(corner))
        by, seen = {}, set()
        for k in np.argsort(score, kind='stable'):
            if not ok[k]:
                continue
            key = self.library[k]['actions'].tobytes()
            if key in seen:
                continue
            seen.add(key)
            c = by.setdefault(self.cls[k], [])
            if len(c) < self.per_class:
                c.append(k)
        picked = []
        for rank in range(self.per_class):
            for c in sorted(by, key=lambda c: score[by[c][0]]):
                if rank < len(by[c]) and len(picked) < self.per_plan:
                    picked.append(by[c][rank])
        return [(int(k), self.library[k]['actions']) for k in picked]


class PressPlanner(okiplan.OkiPlanner):
    """Tries a guarded move's follow-ups on copies of the game and draws one."""

    def __init__(self, data_dir, library, width, delay, history=16, per_plan=10, per_class=2,
                 window=60, wait=24, tolerance=16, slack=2, temperature=200.0,
                 hit_worth=1300.0, hurt_worth=1200.0, doubt=0.3, learner='ayu', seed=0,
                 after='own', skip=0.0, sight=0):
        super().__init__(data_dir, [], width, delay, history=history, per_plan=per_plan,
                         per_class=per_class, window=window, wait=wait, temperature=temperature,
                         hit_worth=hit_worth, hurt_worth=hurt_worth, doubt=doubt,
                         learner=learner, seed=seed, entries=False, after=after, skip=skip,
                         sight=sight)
        self.entries = Followups(library, per_plan, per_class, tolerance, slack)

    def reversal(self, victim):
        if victim not in self.reversals:
            import advantages
            try:
                logic = advantages.Advantages(victim, 1, reversal=1.0, seed=0, learner=self.learner)
                logic = logic if logic.moves else None
            except (ValueError, KeyError):
                logic = None
            self.reversals[victim] = logic
        return self.reversals[victim]

    def lead(self, state, side):
        """(the steps until the opponent's guard is over: 0 if it isn't guarding; the game's
        view now; the opponent's view) for a saved game."""
        one = self.one
        one.load_state(0, state)
        now, theirs = one.obs[0, side].copy(), one.obs[0, 1 - side].copy()
        controls = np.zeros((1, 2), np.uint8)
        controls[0, side], controls[0, 1 - side] = encode(1), encode(1)
        obs = one.obs
        for t in range(LOOK):
            if int(round(float(obs[0, side, OPP_ACT]))) not in GUARDS:
                return t, now, theirs
            obs, _, term, trunc, _ = one.step(controls)
            if term[0] or trunc[0]:
                break
        return None, now, theirs

    def plan(self, state, side, hist, prev, seen, policy, shares, free_for=0):
        """state: the game now (the agent free beside an opponent that guarded); free_for:
        the steps the opponent has been out of its guard (0: still in it). The rest as
        okiplan's."""
        self.last = None
        lead, now, theirs = self.lead(state, side)
        if lead is None:
            return None
        adv = lead if lead > 0 else 1 - max(1, int(free_for))  # (0: its first free step)
        victim = self.names[int(round(float(now[OPP_CHAR])))]
        cands = self.entries.pick(adv, abs(float(now[DX])) * 640, victim,
                                  abs(float(now[OPP_X])) > 0.8)
        options = [a for _, a in cands] + [np.full(lead + self.wait, CROUCH_GUARD), np.zeros(0, int)]
        kinds = [str(self.entries.cls[k]) for k, _ in cands] + ['wait', 'own']
        schedule = None
        logic = self.reversal(victim)
        picked = logic.pick(theirs) if logic is not None else None
        if picked:  # the motion, its button on the first step the guard is over
            seq = [encode(d, b) for d, b in picked[0]]
            press = next(j for j, (_, b) in enumerate(picked[0]) if b)
            schedule = [encode(1)] * max(0, lead - press) + seq
        out = self.tryout(state, side, lead, options, kinds, [k for k, _ in cands], hist, prev,
                          seen, policy, shares, schedule=schedule or [])
        if self.last is not None:
            self.last['adv'] = adv
        return out


def live_plan(planner, state, side, hist, prev, seen, policy, shares, rest=(), near=160,
              max_wait=20):
    """The live plan (the file's head) for a game saved on the step of a contact on the
    opponent's guard. rest: inputs the agent is already to play (a planned move's own).
    Returns None (nothing to plan), or (the agent's actions from now: the `delay` chosen
    at once, the wait, the option drawn; the step of them at which the game should be as
    `expected`; expected: its view then)."""
    one, delay, H = planner.one, planner.delay, planner.H
    one.load_state(0, state)
    seen = np.asarray(seen, np.float32)
    theirs = int(round(float(one.obs[0, side, OPP_ACT])))
    hold = encode(1) if theirs in GUARDS_CROUCH else encode(4)
    h = InputHistory((1,), H)
    h.buf[0], h.prev[0] = hist, prev
    views = seen.copy()
    controls = np.zeros((1, 2), np.uint8)
    free_for = 0

    def step(action):
        nonlocal free_for
        controls[0, side], controls[0, 1 - side] = TABLE.table[action], hold
        obs, _, term, trunc, _ = one.step(controls)
        v = obs[0, side]
        if term[0] or trunc[0] or v[ROUND_OVER] != 0 or v[SELF_HITSTUN] > 0 or v[OPP_HITSTUN] > 0:
            return None  # the round over, or a hit either way: no pressure to plan
        h.push(np.array([TABLE.table[action]], np.uint8))
        views[1:] = views[:-1]
        views[0] = v
        free_for = 0 if int(round(float(v[OPP_ACT]))) in GUARDS else free_for + 1
        return v

    actions = []
    for k in range(delay):  # what it presses until it sees the guard
        if k < len(rest):
            a = int(rest[k])
        else:
            x = np.concatenate([seen[delay - k], h.features()[0].reshape(-1)])[:planner.width]
            a = int(np.asarray(policy(x[None])).reshape(-1)[0])
        actions.append(a)
        if step(a) is None:
            return None
    expected = one.obs[0, side].copy()
    v, waited = expected, 0
    while int(round(float(v[SELF_ACT]))) not in FREE or v[SELF_AIR] > 0:
        if waited >= max_wait:
            return None
        actions.append(CROUCH_GUARD)
        waited += 1
        v = step(CROUCH_GUARD)
        if v is None:
            return None
    if (v[OPP_AIR] > 0 or abs(float(v[DX])) * 640 > near or free_for > 30
            or int(round(float(v[OPP_ACT]))) in okiplan.DOWN):
        return None
    out = planner.plan(one.save_state(0), side, h.buf[0].copy(), int(h.prev[0]), views, policy,
                       shares, free_for=free_for)
    if planner.last is None:
        return None
    return np.concatenate([actions, out if out is not None else []]).astype(int), delay, expected


class PressPlan(modules.Module):
    """The module 'pressplan' (see the file's head)."""
    name = 'pressplan'

    def __init__(self, planner, delay, carry=False, prior=8.0, fixed=None, near=160, fresh=40,
                 live=False, max_wait=20):
        if delay <= 0:
            raise ValueError('pressplan plans when the player sees its move guarded: delay > 0')
        self.planner, self.delay, self.carry, self.prior = planner, delay, bool(carry), prior
        self.near, self.fresh, self.live, self.max_wait = near, fresh, bool(live), max_wait
        self.elsewhere = 0
        self.fixed = None if fixed is None else np.eye(len(ANSWERS))[ANSWERS.index(fixed)]
        inv = {str(c): sorted(v[0]) for c, v in tactics.frame_data().items()}
        self.invincible = inv or None
        self.host = None
        self.batch(0)
        self.plans = []

    def attach(self, host):
        self.host = host

    def batch(self, n):
        self.n = n
        self.memory = Memory(n, invincible=self.invincible) if n else None
        self.playing = {}                     # env -> [actions, step]
        self.seen_guard = np.zeros(n, int)    # steps since it last saw the opponent guard (capped)
        self.seen_guard[:] = 10 ** 6
        self.armed = np.zeros(n, bool)        # a guard's contact seen, not planned for yet
        self.was = np.full((n, 2), -1)        # the opponent's action and frame it saw last
        self.free_for = np.zeros(n, int)      # steps the opponent has been out of its guard, now
        self.now_was = np.full((n, 2), -1)    # the opponent's action and frame as the game was
        self.contact = np.zeros(n, bool)      # a contact on its guard on this step, as the game is

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        if self.memory is not None:
            if self.carry:
                self.memory.end(mask, new_set=np.zeros(self.n, bool))
            else:
                self.memory.clear(mask)
        for i in np.flatnonzero(mask):
            self.playing.pop(int(i), None)
        self.seen_guard[mask] = 10 ** 6
        self.armed[mask] = False
        self.was[mask] = -1
        self.now_was[mask] = -1
        self.contact[mask] = False
        self.free_for[mask] = 0

    def see(self, obs, step):
        a = self.host.agent
        views = a.seen.buf[:, a.delay] if a.delay else obs  # what it sees, late
        self.memory.update(np.asarray(views)[:, :168])

    def watch(self, i, ctx):
        act, frame = int(round(float(ctx.view[OPP_ACT]))), int(round(float(ctx.view[OPP_FRAME])))
        was_act, was_frame = self.was[i]
        self.was[i] = act, frame
        if act in GUARDS:
            self.seen_guard[i] = 0
            # (a contact: the guard starts, or starts again: tactics.Side.contact)
            if was_act not in GUARDS or act != was_act or frame < was_frame:
                self.armed[i] = True
        else:
            self.seen_guard[i] = min(self.seen_guard[i] + 1, 10 ** 6)
            if self.seen_guard[i] > self.fresh:
                self.armed[i] = False
        guarding = int(round(float(ctx.now[OPP_ACT]))) in GUARDS
        self.free_for[i] = 0 if guarding else min(self.free_for[i] + 1, 10 ** 6)
        act, frame = int(round(float(ctx.now[OPP_ACT]))), int(round(float(ctx.now[OPP_FRAME])))
        was_act, was_frame = self.now_was[i]
        self.now_was[i] = act, frame
        self.contact[i] = guarding and (was_act not in GUARDS or act != was_act or frame < was_frame)

    def act_live(self, i, ctx):
        p = self.playing.get(i)  # [actions, step, the step to check at, the view expected]
        rest = ()
        if p is not None:
            interrupted = p[1] > 0 and ctx.last != self.name
            if interrupted or p[1] >= len(p[0]) or ctx.view[SELF_HITSTUN] > 0:
                self.playing.pop(i)
            elif p[1] == p[2] and not np.array_equal(ctx.now[1:168], p[3][1:168]):
                self.playing.pop(i)  # the game isn't where the plan was made for
                self.elsewhere += 1
            elif self.contact[i] and p[1] > p[2]:  # its planned move guarded: from it, again
                rest = p[0][p[1]:]
                self.playing.pop(i)
            else:
                p[1] += 1
                return int(p[0][p[1] - 1])
        if not self.contact[i] or i in self.playing or ctx.view[SELF_HITSTUN] > 0:
            return None
        shares = self.fixed if self.fixed is not None else belief(
            self.memory.c[i], self.prior, sight=bool(getattr(self.planner, 'sight', 0)))
        got = live_plan(self.planner, ctx.save(), ctx.side, ctx.hist, ctx.prev, ctx.seen,
                        ctx.policy, shares, rest=rest, near=self.near, max_wait=self.max_wait)
        if got is None:
            if len(rest):  # (nothing planned: on with what it was playing)
                self.playing[i] = [np.asarray(rest), 1, -1, None]
                return int(rest[0])
            return None
        self.record(shares)
        self.playing[i] = [got[0], 1, got[1], got[2]]
        return int(got[0][0])

    def record(self, shares):
        last = self.planner.last
        c = last['chosen']
        own = last['kinds'].index('own')
        self.plans.append(dict(kind=last['kinds'][c], options=len(last['kinds']) - 2,
                               spread=float(-(last['mix'] * np.log(last['mix'] + 1e-12)).sum()),
                               expected=float(last['expected'][c]),
                               own=float(last['expected'][own]), shares=shares,
                               lead=last['adv']))

    def act(self, i, ctx):
        if self.live:
            return self.act_live(i, ctx)
        p = self.playing.get(i)
        if p is not None:
            interrupted = p[1] > 0 and ctx.last != self.name
            if interrupted or p[1] >= len(p[0]) or ctx.view[SELF_HITSTUN] > 0:
                self.playing.pop(i)
            else:
                p[1] += 1
                return int(p[0][p[1] - 1])
        if not self.armed[i]:
            return None
        now = ctx.now
        if (int(round(float(now[SELF_ACT]))) not in FREE or now[SELF_AIR] > 0 or now[OPP_AIR] > 0
                or now[OPP_HITSTUN] > 0 or now[SELF_HITSTUN] > 0 or ctx.view[SELF_HITSTUN] > 0
                or abs(float(now[DX])) * 640 > self.near):
            return None
        if int(round(float(now[OPP_ACT]))) in okiplan.DOWN or self.free_for[i] > 30:
            self.armed[i] = False
            return None
        self.armed[i] = False  # once a guarded string
        shares = self.fixed if self.fixed is not None else belief(
            self.memory.c[i], self.prior, sight=bool(getattr(self.planner, 'sight', 0)))
        chosen = self.planner.plan(ctx.save(), ctx.side, ctx.hist, ctx.prev, ctx.seen,
                                   ctx.policy, shares, free_for=self.free_for[i])
        last = self.planner.last
        if last is None:
            return None
        c = last['chosen']
        own = last['kinds'].index('own')
        self.plans.append(dict(kind=last['kinds'][c], options=len(last['kinds']) - 2,
                               spread=float(-(last['mix'] * np.log(last['mix'] + 1e-12)).sum()),
                               expected=float(last['expected'][c]),
                               own=float(last['expected'][own]), shares=shares,
                               lead=last['adv']))
        if chosen is None or not len(chosen):
            return None
        self.playing[i] = [chosen, 1]
        return int(chosen[0])

    def stats(self):
        return dict(okiplan.OkiPlan.stats(self), elsewhere=self.elsewhere)

    close = okiplan.OkiPlan.close


@modules.register('pressplan')
def pressplan(agent, where, files, options, data):
    """files: library (pressure_library.py's). options: the file's head."""
    if where != 'batch':
        raise ValueError('pressplan: evaluations only so far (a match in real time needs its '
                         'plans made beside the game, as the live routes are)')
    o = dict(options)
    keys = ('per_plan', 'per_class', 'window', 'wait', 'tolerance', 'slack', 'temperature',
            'hit_worth', 'hurt_worth', 'doubt', 'seed', 'after', 'skip', 'sight')
    unknown = sorted(set(o) - set(keys) - {'carry', 'prior', 'fixed', 'near', 'fresh', 'live',
                                           'max_wait'})
    if unknown:
        raise ValueError(f"pressplan: no option {', '.join(unknown)}")
    planner = PressPlanner(data, load_library(files['library']),
                           agent.model.observation_space.shape[0], agent.delay,
                           history=agent.history, **{k: o[k] for k in keys if k in o})
    return PressPlan(planner, agent.delay, carry=o.get('carry', False),
                     prior=float(o.get('prior', 8.0)), fixed=o.get('fixed'),
                     near=float(o.get('near', 160)), fresh=int(o.get('fresh', 40)),
                     live=bool(o.get('live', False)), max_wait=int(o.get('max_wait', 20)))
