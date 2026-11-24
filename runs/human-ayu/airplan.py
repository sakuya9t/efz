"""The planned catch (python/efz_env/modules.py; the kind 'airplan' of an agent.json, of
evaluate.py --p1-module): when the agent sees its opponent recover in the air out of a
combo, people's catches from the library (air_library.py) are tried on copies of the
game, each against the ways a recovering player goes on, and one is chosen.

    airplan:library=~/data/efz-replays/air-library.npz[,per_plan=8,temperature=200,carry]

Why (docs/training-v2-log.md, "The air"): an opponent that presses out of a combo in the air
is free again beside the agent, and the agent then does what it does anywhere: it caught
the user again after 28% of the user's recoveries and was hit back after 28%; the user
caught it after 67% of its own, with air throws (0.29 a minute; the agent none). In the community's
replays an air throw catches half the recoveries it is tried on and everything else a
fifth. What to press and when is a planner's problem, as the okizeme's is.

- **The options.** The library's entries whose player was where the agent is now (the
  distance, the opponent's height over it, in the air or not) as many steps after the
  recovery began as have passed, and had not yet pressed its move: at most `per_class` of
  a kind (an air throw, a move in the air, a move from the ground, a jump, nothing) and
  `per_plan` in all; an air throw of its own timing (C with forward held after 0, 4 or 8
  steps in the air, or 7, 11 or 15 steps into a jump at the opponent from the ground);
  a wait (back held through the recovery and `wait` steps more: a
  guard, on the ground or in the air); and its own play.
- **The answers.** Each is played on copies against an opponent that, out of its
  recovery, does nothing (falls), holds a guard, presses a button, jumps again, or dashes
  back. What an option is worth against an answer: as okiplan.py's (the HP taken less the
  HP lost by `window` steps after the recovery's end, a first hit or throw of the agent's
  counted as at least `hit_worth`, one taken as at least `hurt_worth`).
- **The choice.** What the opponent did out of its recoveries so far this set, as the
  agent saw it, over a prior of the community's players (a move out of 0.38 of them,
  nothing 0.35, a dash 0.12, a jump 0.10, a guard 0.05), gives each answer a share; the
  draw is okiplan.py's (`temperature`, or `doubt`).

The decision is made from what the agent sees (the recovery, `delay` steps after it);
the copies are of the game as it is. It plans once a recovery and lets go when its inputs
end, when the agent sees itself hit, or when another module took a step.

options: per_plan (8), per_class (2), window (50), wait (20), tolerance (pixels of
distance, 40), tolerance_up (of height, 50), near (the most pixels apart it plans at,
320), temperature (200), doubt (0), hit_worth (1300), hurt_worth (1200), prior (6: the
recoveries the prior counts as), sure (true: an air throw that catches the opponent inside
its recovery is looked for first and played if there is one), matrix (true; false: without
such a throw its own play, nothing tried against answers), carry, fixed, after, skip, seed (okiplan.py's); think (0:
steps of back held before the plan's first input, the plan made for the game as it will
be then and dropped if it isn't: what a planner beside the game, which cannot have its
plan at once, would do).
"""

import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

from efz_env import ActionTable, modules
from efz_env.actions import encode
from efz_env.history import InputHistory, action_labels

import okiplan
import tactics
from okiplan import (DX, INDEX, OPP_ACT, OPP_CHAR, OPP_HITSTUN, OPP_X, ROUND_OVER, SELF_AIR,
                     SELF_HITSTUN, TABLE)

DY, OPP_AIR, SELF_X = 5, 71, 13
SELF_HITS, OPP_HP = 30, 40
ANSWERS = ('fall', 'guard', 'move', 'jump', 'dash')
# What the community's players did first out of an air recovery (air_library.py's count
# over 3,808 of them).
PRIOR = dict(fall=0.35, guard=0.05, move=0.38, jump=0.10, dash=0.12)
RECOVERY = np.array(tactics.AIR_RECOVERY)
DOWN = tuple(tactics.DOWN)
REACT = (0x32, 0x60)     # the hit reactions (src/efz.h)
THROWN = okiplan.THROWN
AIR_JUMP = (0xe, 0xf, 0x10)
AIRDASH = tuple(tactics.AIRDASH)
GUARDS = tuple(tactics.GUARDS)
BACK = INDEX[(4, '')]
FORWARD, UP_FORWARD, THROW = INDEX[(6, '')], INDEX[(9, '')], INDEX[(6, 'C')]
# The air throw (src/ayu.cpp: C with forward held, in the air within 100 pixels of an
# opponent in the air that is in no hit reaction and no guard: an air recovery can be
# thrown), as options of its own beside the library's: pressed after so many steps of
# holding forward (in the air), or of a jump toward the opponent (from the ground).
THROW_AFTER = (0, 4, 8)
JUMP_THROW_AFTER = (7, 11, 15)
NEUTRAL, UP = INDEX[(5, '')], INDEX[(8, '')]
SURE_SPAN = 24     # a sure throw is pressed at most this many steps from the plan's start
SURE_MIN_LEAD = 3  # ... and looked for only with this many steps of the recovery left
LOOK = 60       # the most steps the recovery's end is looked for
PRESS = 2       # an entry's move is pressed at least this many steps after the step it is played from
FRESH = 10      # steps after it saw the recovery in which it still plans
WATCH = 30      # steps after a recovery it saw end in which the opponent's choice is looked for


def load_library(path):
    """air_library.py's entries, their inputs as an agent's actions: dicts with actions,
    dist, up, air (per step), cls, move_at, lead, opponent, corner."""
    table = ActionTable()
    lib = np.load(os.path.expanduser(os.fspath(path)))
    meta = json.loads(str(lib['meta']))
    ends = np.cumsum(lib['lengths'])
    inputs, dist, up, air = lib['inputs'], lib['dist'], lib['up'], lib['air']
    out = []
    for k, m in enumerate(meta):
        s = slice(int(ends[k] - lib['lengths'][k]), int(ends[k]))
        acts = action_labels(np.concatenate([[m.get('prev', 0)], inputs[s]]).astype(np.uint8),
                             table)[1:]
        out.append(dict(m, actions=acts.astype(np.int64), dist=dist[s], up=up[s], air=air[s]))
    return out


def belief(counts, prior=6.0, answers=ANSWERS, base=PRIOR):
    """The shares of ANSWERS a recovering player is expected to give: what this one did
    out of its recoveries (counts, by answer) over the community's prior. (answers, base:
    another situation's: a jump's.)"""
    counts = np.asarray(counts, float)
    base = np.array([base[a] for a in answers])
    return (prior * base + counts) / (prior + counts.sum())


class Catches:
    """The library, as arrays to choose a recovery's entries from."""

    def __init__(self, library, per_plan=8, per_class=2, tolerance=40, tolerance_up=50):
        self.library, self.per_plan, self.per_class = library, per_plan, per_class
        self.tolerance, self.tolerance_up = tolerance, tolerance_up
        n = len(library)
        longest = max((len(m['actions']) for m in library), default=1)
        self.dist = np.full((n, longest), -10000, np.int32)
        self.up = np.full((n, longest), -10000, np.int32)
        self.air = np.zeros((n, longest), bool)
        for k, m in enumerate(library):
            self.dist[k, :len(m['dist'])] = m['dist']
            self.up[k, :len(m['up'])] = m['up']
            self.air[k, :len(m['air'])] = m['air']
        self.move_at = np.array([m['move_at'] for m in library], int)
        self.length = np.array([len(m['actions']) for m in library], int)
        # (a recovery's entry: how long the recovery held; a jump's: when the jumper landed)
        self.lead = np.array([m['lead'] if 'lead' in m else m['land'] if m['land'] >= 0 else 60
                              for m in library], int)
        self.corner = np.array([bool(m['corner']) for m in library])
        self.victim = np.array([m['opponent'] for m in library])
        self.cls = np.array([m['cls'] for m in library])

    def pick(self, since, lead, distance, up, air, victim, corner):
        """The entries to try `since` steps after the recovery began, `lead` before the
        opponent is out of it, the agent `distance` pixels from the opponent, which is
        `up` pixels over it, in the air or not: [(index, its actions from now)]. An entry
        is played from its step `since`, if its player was then within the tolerances of
        that place, in the air or not as the agent is, and pressed its move later (or
        none); the closest first (in place, then by how long its opponent's recovery
        held; the same character and corner a little closer), at most per_class of a
        kind, a kind's best before any kind's second, per_plan in all."""
        if not len(self.library) or since >= self.dist.shape[1]:
            return []
        off = np.abs(self.dist[:, since] - distance)
        off_up = np.abs(self.up[:, since] - up)
        ok = (since < self.length - 4) & ((self.move_at < 0) | (self.move_at >= since + PRESS))
        ok &= (off <= self.tolerance) & (off_up <= self.tolerance_up) & (self.air[:, since] == bool(air))
        score = (off + 0.5 * off_up + 2.0 * np.abs(self.lead - (since + lead)) +
                 6.0 * (self.victim != victim) + 10.0 * (self.corner != bool(corner)))
        by, seen = {}, set()
        for k in np.argsort(score, kind='stable'):
            if not ok[k]:
                continue
            key = self.library[k]['actions'][since:].tobytes()
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
        return [(int(k), self.library[k]['actions'][since:]) for k in picked]


class AirPlanner(okiplan.OkiPlanner):
    """Tries a recovery's catches on copies of the game and draws one."""

    ANSWERS = ANSWERS

    def __init__(self, data_dir, library, width, delay, history=16, per_plan=8, per_class=2,
                 window=50, wait=20, tolerance=40, tolerance_up=50, temperature=200.0,
                 hit_worth=1300.0, hurt_worth=1200.0, doubt=0.0, learner='ayu', seed=0,
                 after='own', skip=0.0, think=0, sure=True, matrix=True):
        # sure: before anything else, the air throws that catch the opponent while its
        # recovery still holds it are looked for (sure_throw), and the first is played.
        # matrix: without one, the options against the answers (False: its own play).
        self.sure, self.matrix = bool(sure), bool(matrix)
        super().__init__(data_dir, [], width, delay, history=history,
                         per_plan=per_plan + len(THROW_AFTER),  # (the copies: the throws' too)
                         per_class=per_class, window=window, wait=wait, temperature=temperature,
                         hit_worth=hit_worth, hurt_worth=hurt_worth, doubt=doubt,
                         learner=learner, seed=seed, entries=False, after=after, skip=skip)
        self.entries = Catches(library, per_plan, per_class, tolerance, tolerance_up)
        # think: the plan is for `think` steps from now, back held until then (the frames
        # a planner beside the game works in: there the plan cannot be had at once).
        self.think = int(think)

    def ahead(self, state, side, hist, prev, seen):
        """The game `think` steps on, the agent holding back and the opponent pressing
        nothing: (its state, the agent's input history, last controls and views then), or
        None if the round ended or the agent was hit on the way."""
        one = self.one
        one.load_state(0, state)
        seen = np.array(seen, np.float32)
        h = InputHistory((1,), self.H)
        h.buf[0], h.prev[0] = hist, prev
        controls = np.zeros((1, 2), np.uint8)
        controls[0, side], controls[0, 1 - side] = TABLE.table[BACK], encode(5)
        for _ in range(self.think):
            obs, _, term, trunc, info = one.step(controls)
            if term[0] or trunc[0] or obs[0, side, ROUND_OVER] != 0 or \
                    obs[0, side, SELF_HITSTUN] > 0:
                return None
            h.push(info['input'][:, side])
            seen[1:] = seen[:-1]
            seen[0] = obs[0, side]
        return one.save_state(0), h.buf[0].copy(), int(h.prev[0]), seen

    @staticmethod
    def throws(lead, air):
        """The air throws tried for a sure one, the agent's actions each: C with forward
        held after every second step (up to SURE_SPAN and the recovery's end) of holding
        forward in the air, of a second jump at the opponent, or of a dash at it; from
        the ground, that many steps into a jump at it, or straight up."""
        seqs = []
        for d in range(0, min(lead, SURE_SPAN), 2):
            if air:
                seqs.append([FORWARD] * d + [THROW] * 2)
                if d >= 4:
                    seqs.append([NEUTRAL, UP_FORWARD] + [FORWARD] * (d - 2) + [THROW] * 2)
                    seqs.append([FORWARD, NEUTRAL, FORWARD] + [FORWARD] * (d - 3) + [THROW] * 2)
            elif d >= 4:
                seqs.append([UP_FORWARD] * d + [THROW] * 2)
                seqs.append([UP] * d + [THROW] * 2)
        return seqs

    def sure_throw(self, state, side, lead, now):
        """An air throw that catches the opponent before its recovery is over: the agent's
        actions, or None. Until then the opponent can do nothing, so what a copy shows is
        what will happen. throws()'s are tried, each on a copy; the one that catches
        soonest (then the shortest, then the first). self.caught: the step it catches on."""
        self.caught = -1
        if lead < SURE_MIN_LEAD:
            return None
        sim = self.sim
        seqs = self.throws(lead, now[SELF_AIR] > 0)[:sim.num_envs]
        E = len(seqs)
        if not E:
            return None
        for e in range(E):
            sim.load_state(e, state)
        controls = np.zeros((sim.num_envs, 2), np.uint8)
        controls[:, 1 - side] = encode(5)
        caught = np.full(E, -1)
        for t in range(lead + 1):
            mine = np.array([q[t] if t < len(q) else NEUTRAL for q in seqs])
            controls[:E, side] = TABLE.table[mine]
            obs, *_ = sim.step(controls)
            thrown = np.isin(np.round(obs[:E, side, OPP_ACT]), THROWN) & (caught < 0)
            caught[thrown] = t
            if (caught >= 0).any():
                break
        if not (caught >= 0).any():
            return None
        best = min(np.flatnonzero(caught >= 0), key=lambda e: (caught[e], len(seqs[e]), e))
        self.caught = int(caught[best])
        return np.array(seqs[best])

    def finish(self, out, seen):
        """A plan's actions with its think steps before them; self.last['view']: the game
        as the plan has it when they are over (the module lets go if it isn't so)."""
        if not self.think or self.last is None:
            return out
        self.last['view'] = np.array(seen[0])
        ahead = np.full(self.think, BACK)
        return ahead if out is None else np.concatenate([ahead, out])

    def count_from(self, lead):
        return 0  # (the opponent is out of its hit reaction already)

    def their_controls(self, t, lead, answer, side, schedule, logic):
        theirs = np.full(len(answer), encode(5), np.uint8)       # fall
        theirs[answer == 1] = encode(4)                          # a guard
        if t >= lead - 1:                                        # a button, pressed again
            theirs[answer == 2] = encode(5, 'A') if t % 2 == 0 else encode(5)
        if t >= lead - 2:                                        # a jump, pressed again
            theirs[answer == 3] = encode(7) if t % 2 == 0 else encode(5)
        if t >= lead:                                            # a dash back: 4, 5, 4
            theirs[answer == 4] = encode(5) if t - lead == 1 else encode(4)
        return theirs

    def lead(self, state, side):
        """(the steps until the opponent is out of its recovery: 0 if it is; the game's
        view now) for a saved game; (None, the view) if the opponent is not in the air
        and free of a hit."""
        one = self.one
        one.load_state(0, state)
        now = one.obs[0, side].copy()
        if now[OPP_AIR] <= 0 or now[OPP_HITSTUN] > 0 or \
                int(round(float(now[OPP_ACT]))) in THROWN:
            return None, now
        controls = np.zeros((1, 2), np.uint8)
        controls[0, side], controls[0, 1 - side] = encode(5), encode(5)
        obs = one.obs
        for t in range(LOOK):
            if int(round(float(obs[0, side, OPP_ACT]))) not in RECOVERY:
                return t, now
            obs, _, term, trunc, _ = one.step(controls)
            if term[0] or trunc[0]:
                break
        return None, now

    def plan(self, state, side, hist, prev, seen, policy, shares, since=0):
        """state: the game now (the opponent recovering in the air, or just out of it);
        since: the steps since its recovery began. The rest as okiplan's."""
        self.last = None
        if self.think:
            got = self.ahead(state, side, hist, prev, seen)
            if got is None:
                return None
            state, hist, prev, seen = got
            since = int(since) + self.think
        lead, now = self.lead(state, side)
        if lead is None:
            return None
        if self.sure:
            throw = self.sure_throw(state, side, lead, now)
            if throw is not None or not self.matrix:
                self.last = dict(lead=int(lead), kinds=['sure throw' if throw is not None else 'none',
                                                        'own'],
                                 worth=np.zeros((2, self.R)), expected=np.zeros(2), chosen=0,
                                 mix=np.array([1.0, 0.0]), first=np.zeros((2, self.R), int),
                                 entries=[],
                                 # (where it was looked for: for the module's report)
                                 at=dict(air=bool(now[SELF_AIR] > 0),
                                         dx=abs(float(now[DX])) * 640, up=-float(now[DY]) * 240,
                                         busy=bool(now[okiplan.SELF_ACT] >= tactics.FIRST_OWN)))
                return self.finish(throw, seen)
        elif not self.matrix:
            return None
        victim = self.names[int(round(float(now[OPP_CHAR])))]
        cands = self.entries.pick(int(since), lead, abs(float(now[DX])) * 640,
                                  -float(now[DY]) * 240, now[SELF_AIR] > 0, victim,
                                  abs(float(now[OPP_X])) > 0.8)
        options = [a for _, a in cands]
        kinds = [str(self.entries.cls[k]) for k, _ in cands]
        if now[SELF_AIR] > 0:
            for d in THROW_AFTER:
                options.append(np.array([FORWARD] * d + [THROW] * 2))
                kinds.append(f'throw +{d}')
        else:
            for d in JUMP_THROW_AFTER:
                options.append(np.array([UP_FORWARD] * d + [THROW] * 2))
                kinds.append(f'jump throw +{d}')
        options += [np.full(lead + self.wait, BACK), np.zeros(0, int)]
        kinds += ['wait', 'own']
        return self.finish(self.tryout(state, side, lead, options, kinds,
                                       [k for k, _ in cands], hist, prev, seen, policy, shares,
                                       schedule=[]), seen)


JUMP_ANSWERS = ('attack', 'late', 'empty', 'low', 'again')
# What the community's jumpers did (air_library.py --kind jump, 6,207 forward jumps at an
# Ayu player): an attack in 0.72 of them (half within 24 steps of the jump's start), none
# in 0.14 (a move on landing after one in seven of those), another jump or a dash in 0.12.
JUMP_PRIOR = dict(attack=0.40, late=0.32, empty=0.12, low=0.04, again=0.12)
LATE = 10          # steps before landing at which the 'late' answer presses
EARLY = 16         # an attack seen within this many steps of the jump is an early one
JUMP_FORWARD = 0x5
JUMP_LOOK = 90


class JumpPlanner(AirPlanner):
    """Tries the answers to a jump at the agent on copies of the game and draws one: the
    library's (air_library.py --kind jump: what people did from where the agent stands,
    as many steps after the jump began), an air throw of its own timing, a standing
    guard held until the jumper is down and `wait` steps more, and its own play; against
    a jumper that attacks at once, attacks late (LATE steps before it lands), lands
    without attacking and guards, lands and presses a low, or jumps again."""

    ANSWERS = JUMP_ANSWERS

    def their_controls(self, t, lead, answer, side, schedule, logic):
        theirs = np.full(len(answer), encode(5), np.uint8)
        press = t % 2 == 0
        theirs[answer == 0] = encode(5, 'B') if press else encode(5)       # at once
        if t >= lead - LATE:
            theirs[answer == 1] = encode(5, 'B') if press else encode(5)   # late
        if t >= lead:
            theirs[answer == 2] = encode(1)                                # down, a guard
            theirs[answer == 3] = encode(2, 'A') if press else encode(2)   # down, a low
        theirs[answer == 4] = encode(7) if press else encode(5)            # another jump
        return theirs

    def lead(self, state, side):
        """(the steps until the jumper is down; the game's view now), or (None, the view)
        if the opponent is not in the air, or being hit."""
        one = self.one
        one.load_state(0, state)
        now = one.obs[0, side].copy()
        if now[OPP_AIR] <= 0 or now[OPP_HITSTUN] > 0 or \
                int(round(float(now[OPP_ACT]))) in THROWN:
            return None, now
        controls = np.zeros((1, 2), np.uint8)
        controls[0, side], controls[0, 1 - side] = encode(4), encode(5)
        obs = one.obs
        for t in range(JUMP_LOOK):
            if obs[0, side, OPP_AIR] <= 0:
                return t, now
            obs, _, term, trunc, _ = one.step(controls)
            if term[0] or trunc[0]:
                break
        return None, now

    def plan(self, state, side, hist, prev, seen, policy, shares, since=0):
        self.last = None
        if self.think:
            got = self.ahead(state, side, hist, prev, seen)
            if got is None:
                return None
            state, hist, prev, seen = got
            since = int(since) + self.think
        lead, now = self.lead(state, side)
        if lead is None or lead < 4 or now[SELF_AIR] > 0:
            return None
        victim = self.names[int(round(float(now[OPP_CHAR])))]
        cands = self.entries.pick(int(since), lead, abs(float(now[DX])) * 640,
                                  -float(now[DY]) * 240, False, victim,
                                  abs(float(now[SELF_X])) > 0.8)
        options = [a for _, a in cands]
        kinds = [str(self.entries.cls[k]) for k, _ in cands]
        for d in JUMP_THROW_AFTER:
            options.append(np.array([UP_FORWARD] * d + [THROW] * 2))
            kinds.append(f'jump throw +{d}')
        options += [np.full(lead + self.wait, BACK), np.zeros(0, int)]
        kinds += ['wait', 'own']
        return self.finish(self.tryout(state, side, lead, options, kinds,
                                       [k for k, _ in cands], hist, prev, seen, policy, shares,
                                       schedule=[]), seen)


def live_throw(planner, state, side, hist, prev, seen, policy, rest=(), near=320):
    """The sure throw as a planner beside the game makes it (port/agent/mix.h's
    BeginThrow: the module airthrow:1 of an agent file), for a game saved on the step its
    opponent's recovery begins: the agent's inputs for the `delay` steps until it sees the
    recovery are chosen at once (rest: inputs it is already to play; then its own play's
    from what it will see), played on a copy with the opponent pressing nothing, and the
    sure throw looked for from there. Returns None (the round over or the agent hit on
    the way, the opponent no longer in the air, out of `near` pixels, or no throw that
    catches inside the recovery), or (the agent's actions from now: those inputs, then
    the throw's; the step of them at which the game should be as `expected`; expected:
    its view then)."""
    one, delay, H = planner.one, planner.delay, planner.H
    one.load_state(0, state)
    seen = np.asarray(seen, np.float32)
    h = InputHistory((1,), H)
    h.buf[0], h.prev[0] = hist, prev
    controls = np.zeros((1, 2), np.uint8)
    actions = []
    for k in range(delay):
        if k < len(rest):
            a = int(rest[k])
        else:
            x = np.concatenate([seen[delay - k], h.features()[0].reshape(-1)])[:planner.width]
            a = int(np.asarray(policy(x[None])).reshape(-1)[0])
        actions.append(a)
        controls[0, side], controls[0, 1 - side] = TABLE.table[a], encode(5)
        obs, _, term, trunc, _ = one.step(controls)
        v = obs[0, side]
        if term[0] or trunc[0] or v[ROUND_OVER] != 0 or v[SELF_HITSTUN] > 0:
            return None
        h.push(np.array([TABLE.table[a]], np.uint8))
    expected = one.obs[0, side].copy()
    if abs(float(expected[DX])) * 640 > near:
        return None
    start = one.save_state(0)
    lead, now = planner.lead(start, side)
    if lead is None:
        return None
    throw = planner.sure_throw(start, side, lead, now)
    if throw is None:
        return None
    planner.last = dict(lead=int(lead), caught=planner.caught, tried=len(planner.throws(lead, now[SELF_AIR] > 0)))
    return np.concatenate([actions, throw]).astype(int), delay, expected


class AirPlan(modules.Module):
    """The module 'airplan' (see the file's head)."""
    name = 'airplan'
    ANSWERS, PRIOR = ANSWERS, PRIOR

    def __init__(self, planner, delay, carry=False, prior=6.0, fixed=None, near=320):
        if delay <= 0:
            raise ValueError('airplan plans when the player sees the recovery: delay > 0')
        self.planner, self.delay, self.carry, self.prior = planner, delay, bool(carry), prior
        self.near = near
        self.fixed = None if fixed is None else \
            np.eye(len(self.ANSWERS))[self.ANSWERS.index(fixed)]
        self.host = None
        self.batch(0)
        self.plans = []
        self.elsewhere = 0

    def attach(self, host):
        self.host = host

    def batch(self, n):
        self.n = n
        self.counts = np.zeros((n, len(self.ANSWERS)))  # what the opponent did out of its recoveries
        self.playing = {}                     # env -> [actions, step]
        self.was = np.zeros(n, int)           # the opponent's action it saw last
        self.pending = np.zeros(n, int)       # steps left to plan for a recovery it saw
        self.since = np.full(n, 10 ** 6)      # steps since the recovery began, as the game is
        self.now_rec = np.zeros(n, bool)
        self.watching = np.zeros(n, int)      # steps left to see what the opponent does out of one

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        if self.carry:  # the same opponent again: what it showed is kept, older
            self.counts[mask] *= 0.7
        else:
            self.counts[mask] = 0
        for i in np.flatnonzero(mask):
            self.playing.pop(int(i), None)
        self.was[mask] = 0
        self.pending[mask] = self.watching[mask] = 0
        self.since[mask] = 10 ** 6
        self.now_rec[mask] = False

    def watch(self, i, ctx):
        # The game as it is: how long ago the recovery began (the entries' clock).
        rec = int(round(float(ctx.now[OPP_ACT]))) in RECOVERY
        self.since[i] = 0 if rec and not self.now_rec[i] else min(self.since[i] + 1, 10 ** 6)
        self.now_rec[i] = rec
        # What it sees: a recovery out of a hit of its own begins; and, a recovery over,
        # what the opponent does first (the count its belief is made of).
        act, was = int(round(float(ctx.view[OPP_ACT]))), int(self.was[i])
        self.was[i] = act
        if act in RECOVERY and REACT[0] <= was < REACT[1]:
            self.pending[i] = FRESH
        elif self.pending[i] > 0:
            self.pending[i] -= 1
        if was in RECOVERY and act not in RECOVERY:
            self.watching[i] = WATCH
        if self.watching[i] > 0:
            self.watching[i] -= 1
            what = None
            if ctx.view[OPP_HITSTUN] > 0 or act in THROWN:
                self.watching[i] = 0       # caught before it chose
            elif act >= tactics.FIRST_OWN:
                what = 'move'
            elif act in AIRDASH:
                what = 'dash'
            elif act in AIR_JUMP and act != was:
                what = 'jump'
            elif act in GUARDS:
                what = 'guard'
            elif ctx.view[OPP_AIR] <= 0 or self.watching[i] == 0:
                what = 'fall'
            if what is not None:
                self.counts[i, self.ANSWERS.index(what)] += 1
                self.watching[i] = 0

    def act(self, i, ctx):
        p = self.playing.get(i)
        if p is not None:
            interrupted = p[1] > 0 and ctx.last != self.name
            if interrupted or p[1] >= len(p[0]) or ctx.view[SELF_HITSTUN] > 0:
                self.playing.pop(i)
            elif p[2] and p[1] == p[2] and not np.array_equal(ctx.now[1:168], p[3][1:168]):
                self.playing.pop(i)  # the game isn't where the plan was made for
                self.elsewhere += 1
            else:
                p[1] += 1
                return int(p[0][p[1] - 1])
        if self.pending[i] <= 0:
            return None
        self.pending[i] = 0  # once a recovery
        now = ctx.now
        if (now[SELF_HITSTUN] > 0 or ctx.view[SELF_HITSTUN] > 0 or self.since[i] > 60
                or abs(float(now[DX])) * 640 > self.near):
            return None
        shares = self.fixed if self.fixed is not None else \
            belief(self.counts[i], self.prior, self.ANSWERS, self.PRIOR)
        chosen = self.planner.plan(ctx.save(), ctx.side, ctx.hist, ctx.prev, ctx.seen,
                                   ctx.policy, shares, since=int(self.since[i]))
        last = self.planner.last
        if last is None:
            return None
        c = last['chosen']
        own = last['kinds'].index('own')
        self.plans.append(dict(kind=last['kinds'][c], options=len(last['kinds']) - 2,
                               spread=float(-(last['mix'] * np.log(last['mix'] + 1e-12)).sum()),
                               expected=float(last['expected'][c]),
                               own=float(last['expected'][own]), shares=shares,
                               lead=last['lead'], worth=last['worth'], kinds=last['kinds'],
                               at=last.get('at')))
        if chosen is None or not len(chosen):
            return None
        self.playing[i] = [chosen, 1, self.planner.think if 'view' in last else 0,
                           last.get('view')]
        return int(chosen[0])

    def stats(self):
        p = self.plans
        if not p:
            return dict(plans=0)
        kinds = {}
        for x in p:
            kinds[x['kind']] = kinds.get(x['kind'], 0) + 1
        # What each kind of option was worth where it was tried, by the opponent's answer.
        by = {}
        for x in p:
            for k, row in zip(x['kinds'], x['worth']):
                by.setdefault(k, []).append(row)
        sure = {}
        for name in ('sure throw', 'none'):  # where a sure throw was found, and where not
            at = [x['at'] for x in p if x.get('at') and x['kind'] == name]
            if at:
                sure[name] = dict(n=len(at), air=round(float(np.mean([a['air'] for a in at])), 2),
                                  busy=round(float(np.mean([a['busy'] for a in at])), 2),
                                  lead=round(float(np.mean([x['lead'] for x in p if x.get('at') and x['kind'] == name])), 1),
                                  dx=[round(float(v)) for v in np.percentile([a['dx'] for a in at], [10, 50, 90])],
                                  up=[round(float(v)) for v in np.percentile([a['up'] for a in at], [10, 50, 90])])
        return dict(plans=len(p), elsewhere=self.elsewhere, sure=sure,
                    options=round(float(np.mean([x['options'] for x in p])), 2),
                    lead=round(float(np.mean([x['lead'] for x in p])), 1),
                    expected=round(float(np.mean([x['expected'] for x in p]))),
                    own=round(float(np.mean([x['own'] for x in p]))),
                    between=round(float(np.exp(np.mean([x['spread'] for x in p]))), 2),
                    chosen={k: round(v / len(p), 3) for k, v in
                            sorted(kinds.items(), key=lambda kv: -kv[1])},
                    shares={a: round(float(np.mean([x['shares'][j] for x in p])), 3)
                            for j, a in enumerate(self.ANSWERS)},
                    worth={k: dict(n=len(v), **{a: round(float(np.mean([r[j] for r in v])))
                                                for j, a in enumerate(self.ANSWERS)})
                           for k, v in sorted(by.items(), key=lambda kv: -len(kv[1]))})

    def close(self):
        for env in (self.planner.one, self.planner.sim):
            env.close()


class JumpPlan(AirPlan):
    """The module 'jumpplan': when the agent, on the ground, sees its opponent jump at it
    within `near` pixels, JumpPlanner's plan. Its belief: what this opponent did on the
    jumps the agent saw (an attack within EARLY steps, a later one, none and a guard,
    none and a move on landing, another jump or a dash) over the community's prior.

        jumpplan:library=~/data/efz-replays/jump-library.npz[,near=260,...]

    options: airplan's (near 260)."""
    name = 'jumpplan'
    ANSWERS, PRIOR = JUMP_ANSWERS, JUMP_PRIOR

    def batch(self, n):
        super().batch(n)
        self.jump_seen = np.zeros(n, int)   # steps since it saw a jump begin (0: none watched)
        self.landed = np.zeros(n, int)      # steps since it saw that jumper land (0: in the air)

    def reset(self, mask=None):
        super().reset(mask)
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        self.jump_seen[mask] = self.landed[mask] = 0

    def watch(self, i, ctx):
        # The game as it is: how long ago the jump began.
        jump = int(round(float(ctx.now[OPP_ACT]))) == JUMP_FORWARD
        self.since[i] = 0 if jump and not self.now_rec[i] else min(self.since[i] + 1, 10 ** 6)
        self.now_rec[i] = jump
        # What it sees: a jump begins; and what the jumper does (the belief's count).
        act, was = int(round(float(ctx.view[OPP_ACT]))), int(self.was[i])
        self.was[i] = act
        if act == JUMP_FORWARD and was != JUMP_FORWARD:
            self.pending[i] = FRESH
            self.jump_seen[i], self.landed[i] = 1, 0
            return
        if self.pending[i] > 0:
            self.pending[i] -= 1
        if self.jump_seen[i] == 0:
            return
        self.jump_seen[i] += 1
        what = None
        if ctx.view[OPP_HITSTUN] > 0 or act in THROWN:
            self.jump_seen[i] = 0           # hit out of it before it chose
        elif self.landed[i] == 0:
            if act >= tactics.FIRST_OWN:
                what = 'attack' if self.jump_seen[i] <= EARLY else 'late'
            elif act in AIRDASH or (act in AIR_JUMP and act != was):
                what = 'again'
            elif ctx.view[OPP_AIR] <= 0 and self.jump_seen[i] > 8:
                self.landed[i] = 1
        else:
            self.landed[i] += 1
            if act >= tactics.FIRST_OWN:
                what = 'low'
            elif self.landed[i] > 12:
                what = 'empty'
        if what is not None:
            self.counts[i, self.ANSWERS.index(what)] += 1
            self.jump_seen[i] = 0

    def act(self, i, ctx):
        if self.pending[i] > 0 and i not in self.playing and \
                (ctx.now[SELF_AIR] > 0 or int(round(float(ctx.now[okiplan.SELF_ACT]))) in DOWN):
            self.pending[i] = 0  # (in the air itself, or down: nothing to plan from the ground)
        return super().act(i, ctx)


END_ANSWERS = ('down', 'fall', 'guard', 'move', 'jump', 'dash')
# What the victims of the community's Ayu players did at the end of a combo on them in the
# air (air_library.py --kind ending, 10,253 of them): no recovery in 0.82; out of a
# recovery, nothing in 0.39, a move 0.33, a dash 0.14, a jump 0.10, a guard 0.04.
END_PRIOR = dict(down=0.82, fall=0.07, guard=0.01, move=0.06, jump=0.02, dash=0.02)
END_LOOK = 110      # the most steps the victim's recovery (and its end) is looked for
RECOVER = encode(4) | encode(5, 'A')  # back and a button: the air recovery (redteam.BACK_PRESS)
BACK_AIR, DOWN_BACK_A = INDEX[(4, '')], INDEX[(4, 'A')]
TRAP_AFTER = (2, 8, 14)   # steps of the flight back before 214A


class EndPlanner(AirPlanner):
    """Tries the ends of a combo on copies of the game and draws one: from the step after
    the last hit of the route being played, on an opponent in the air: the library's
    (air_library.py --kind ending: what people did from there), Ayu's trap of its own
    timing (a flight back, then 214A), the rest of the route, a wait and its own play;
    against a victim that does not recover (it comes down), and one that recovers at the
    first chance and then falls, guards, presses a button, jumps or dashes back."""

    ANSWERS = END_ANSWERS
    from_lead = True   # (okiplan's tryout: a recovering victim's HP counted from its recovery's end)
    ways = 2           # a sure throw catches this many of the two ways of recovering (1: either)

    def __init__(self, *args, **kwargs):
        # sure (default): an air throw timed into the recovery of a victim that presses
        # out at its first chance is looked for (sure_end) and played if there is one.
        # matrix (default off): without one, the options against the answers; measured,
        # the copies' answers did not tell which end catches (docs/training-v2-log.md).
        kwargs.setdefault('sure', True)
        kwargs.setdefault('matrix', False)
        super().__init__(*args, **kwargs)

    def sure_end(self, state, side, begun, lead, now):
        """An air throw that catches a victim pressing out at its first chance while its
        recovery holds it, whether it recovers backward or forward: the agent's actions,
        or None. Tried: C with forward held after every second step from a little before
        the recovery can begin to its end, of holding forward in the air, of a second jump
        or a dash at the opponent; from the ground, that many steps into a jump at it or
        straight up. The one that catches both ways first, then the soonest.
        self.caught: how many of the two ways it catches."""
        self.caught = 0
        sim = self.sim
        air = now[SELF_AIR] > 0
        seqs = []
        for d in range(max(0, begun - 6), lead, 2):
            if air:
                seqs.append([FORWARD] * d + [THROW] * 2)
                if d >= 4:
                    seqs.append([NEUTRAL, UP_FORWARD] + [FORWARD] * (d - 2) + [THROW] * 2)
                    seqs.append([FORWARD, NEUTRAL, FORWARD] + [FORWARD] * (d - 3) + [THROW] * 2)
            elif d >= 4:
                seqs.append([UP_FORWARD] * d + [THROW] * 2)
                seqs.append([UP] * d + [THROW] * 2)
        seqs = seqs[:sim.num_envs // 2]
        E = len(seqs)
        if not E:
            return None
        for e in range(2 * E):
            sim.load_state(e, state)
        controls = np.zeros((sim.num_envs, 2), np.uint8)
        caught = np.full(2 * E, -1)
        way = np.repeat([4, 6], E)   # the victim's direction: back, forward
        for t in range(lead + 2):
            mine = np.array([q[t] if t < len(q) else NEUTRAL for q in seqs] * 2)
            controls[:2 * E, side] = TABLE.table[mine]
            stunned = sim.obs[:2 * E, side, OPP_HITSTUN] > 0
            press = t % 2 == 0
            theirs = np.full(2 * E, encode(5), np.uint8)
            for w in (4, 6):
                theirs[stunned & (way == w)] = encode(w, 'A') if press else encode(w)
            controls[:2 * E, 1 - side] = theirs
            obs, *_ = sim.step(controls)
            thrown = np.isin(np.round(obs[:2 * E, side, OPP_ACT]), THROWN) & (caught < 0)
            caught[thrown] = t
        got = (caught[:E] >= 0).astype(int) + (caught[E:] >= 0).astype(int)
        if got.max() < self.ways:
            return None
        when = np.where(caught[:E] >= 0, caught[:E], caught[E:])
        best = min(np.flatnonzero(got > 0), key=lambda e: (-got[e], when[e], len(seqs[e]), e))
        self.caught = int(got[best])
        return np.array(seqs[best])

    def count_from(self, lead):
        return lead  # (hits before the victim is out are the combo's own)

    def their_controls(self, t, lead, answer, side, schedule, logic):
        E = len(answer)
        obs = self.sim.obs[:E, side]
        stunned = obs[:, OPP_HITSTUN] > 0
        rec = np.isin(np.round(obs[:, OPP_ACT]).astype(int), RECOVERY)
        press = t % 2 == 0
        theirs = np.full(E, encode(4), np.uint8)                       # down: back held
        up = answer > 0
        theirs[up & stunned] = RECOVER if press else encode(4)         # out at the first chance
        free = up & ~stunned & ~rec
        theirs[free & (answer == 1)] = encode(5)                       # then: falls
        theirs[free & (answer == 2)] = encode(4)                       # a guard
        theirs[free & (answer == 3)] = encode(5, 'A') if press else encode(5)
        theirs[free & (answer == 4)] = encode(7) if press else encode(5)
        theirs[free & (answer == 5)] = encode(5) if t % 3 == 1 else encode(4)
        return theirs

    def lead(self, state, side, rest=None, horizon=END_LOOK):
        """(the steps until a victim that recovers at the first chance is in its recovery,
        the agent playing `rest` (its route's actions from now; none: pressing nothing),
        and until it is out of it; the game's view now), or (None, None, the view) if the
        opponent is not being hit in the air, cannot recover before it is down, or not
        within `horizon` steps."""
        one = self.one
        one.load_state(0, state)
        now = one.obs[0, side].copy()
        if now[OPP_AIR] <= 0 or now[OPP_HITSTUN] <= 0 or \
                int(round(float(now[OPP_ACT]))) in THROWN:
            return None, None, now
        controls = np.zeros((1, 2), np.uint8)
        obs, begun = one.obs, None
        for t in range(END_LOOK):
            act = int(round(float(obs[0, side, OPP_ACT])))
            if begun is None and act in RECOVERY:
                begun = t
            elif begun is not None and act not in RECOVERY:
                return begun, t, now
            elif begun is None and (t > horizon or act in DOWN or
                                    (t > 0 and obs[0, side, OPP_HITSTUN] <= 0)):
                break  # not soon; or down, or on its feet: nothing to recover from
            controls[0, side] = TABLE.table[int(rest[t])] if rest is not None and t < len(rest) \
                else encode(5)
            controls[0, 1 - side] = RECOVER if t % 2 == 0 else encode(4)
            obs, _, term, trunc, _ = one.step(controls)
            if term[0] or trunc[0]:
                break
        return None, None, now

    def plan(self, state, side, hist, prev, seen, policy, shares, since=0, rest=None,
             horizon=30):
        """state: the game now (the opponent hit in the air, `since` steps after the last
        hit); rest: the actions of the route being played from now on. A plan is made only
        if a victim pressing out would be in its recovery within `horizon` steps, the
        route going on: until then the combo holds it. The rest as okiplan's."""
        self.last = None
        begun, lead, now = self.lead(state, side, rest, horizon)
        if lead is None:
            return None
        if self.sure:
            throw = self.sure_end(state, side, begun, lead, now)
            if throw is not None or not self.matrix:
                self.last = dict(lead=int(lead), begun=int(begun), caught=self.caught,
                                 kinds=['sure throw' if throw is not None else 'none', 'own'],
                                 worth=np.zeros((2, self.R)), expected=np.zeros(2), chosen=0,
                                 mix=np.array([1.0, 0.0]), first=np.zeros((2, self.R), int),
                                 entries=[])
                return throw
        elif not self.matrix:
            return None
        victim = self.names[int(round(float(now[OPP_CHAR])))]
        air = now[SELF_AIR] > 0
        cands = self.entries.pick(int(since), begun, abs(float(now[DX])) * 640,
                                  -float(now[DY]) * 240, air, victim,
                                  abs(float(now[OPP_X])) > 0.8)
        cands = cands[:self.entries.per_plan - 1]  # (the copies: the route's rest too)
        options = [a for _, a in cands]
        kinds = [str(self.entries.cls[k]) for k, _ in cands]
        if air:
            for d in TRAP_AFTER:
                options.append(np.array([BACK_AIR, NEUTRAL, BACK_AIR] + [NEUTRAL] * d +
                                        [INDEX[(2, '')], INDEX[(1, '')], DOWN_BACK_A, DOWN_BACK_A]))
                kinds.append(f'trap +{d}')
        if rest is not None and len(rest):
            options.append(np.asarray(rest))
            kinds.append('route')
        options += [np.full(lead + self.wait, BACK), np.zeros(0, int)]
        kinds += ['wait', 'own']
        out = self.tryout(state, side, lead, options, kinds, [k for k, _ in cands], hist, prev,
                          seen, policy, shares, schedule=[])
        if self.last is not None:
            self.last['begun'] = int(begun)
        return out


class EndPlan(AirPlan):
    """The module 'endplan': when the agent sees a hit of its own on an opponent in the air
    and that opponent, pressing out at its first chance, would be in its recovery within
    `horizon` steps (30) with the route going on (looked for on a copy), EndPlanner's
    plan. It goes before 'routes' in the stack and takes the route's place when it chooses
    anything but the route's own rest. Its belief: what this opponent did
    at the end of the combos on it in the air that the agent saw (came down, or recovered
    and then fell, guarded, pressed, jumped, dashed) over the community's prior.

        endplan:library=~/data/efz-replays/end-library.npz[,least=0.3,ways=2,horizon=30,...]

    options: airplan's (sure true, matrix false by default); least, ways, horizon."""
    name = 'endplan'
    ANSWERS, PRIOR = END_ANSWERS, END_PRIOR
    horizon = 30
    # least: it plans only against an opponent expected to recover at least this often
    # where it can: of the ends of combos at which a copy showed it could press out
    # (its chances), the share at which it did, over a prior of CHANCE_PRIOR chances at
    # CHANCE_SHARE: off until it has seen this opponent recover once. A throw at one
    # that stays down whiffs and gives up the route and the okizeme.
    least = 0.34
    CHANCE_PRIOR, CHANCE_SHARE = 3.0, 0.3

    def stats(self):
        return dict(super().stats(), asked=dict(self.asked),
                    came={k: dict(v) for k, v in sorted(self.came.items())})

    def batch(self, n):
        super().batch(n)
        self.react_air = np.zeros(n, bool)   # it saw the opponent hit in the air, not out yet
        self.hits_seen = np.zeros(n, int)    # its combo's hits as it saw them last step
        self.new_hit = np.zeros(n, bool)     # it sees a new hit of its own this step
        self.hp_now = np.zeros(n)            # the opponent's HP as the game is
        self.since_hit = np.full(n, 10 ** 6)  # steps since its last hit, as the game is
        if not hasattr(self, 'asked'):       # hits seen on an opponent in the air; and of them
            self.asked = dict(seen=0, held=0, planned=0)
            self.came = {}                   # kind chosen -> how its plans went in the game
        self.track = {}                      # env -> [kind, steps left, the opponent recovered]
        self.chances = np.zeros(n)           # the ends at which it could press out
        self.recovered = np.zeros(n)         # ... and did

    def reset(self, mask=None):
        super().reset(mask)
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        self.react_air[mask] = False
        self.hits_seen[mask] = 0
        self.new_hit[mask] = False
        self.hp_now[mask] = 0
        self.since_hit[mask] = 10 ** 6
        for i in np.flatnonzero(mask):
            self.track.pop(int(i), None)
        keep = 0.7 if self.carry else 0.0
        self.chances[mask] *= keep
        self.recovered[mask] *= keep

    def watch(self, i, ctx):
        # The game as it is: how long since its last hit (the entries' clock). What it
        # sees: a new hit of its combo.
        hp = float(ctx.now[OPP_HP])
        self.since_hit[i] = 0 if hp < self.hp_now[i] - 1e-6 else min(self.since_hit[i] + 1, 10 ** 6)
        self.hp_now[i] = hp
        hits = int(round(float(ctx.view[SELF_HITS]) * 30))
        self.new_hit[i] = hits > self.hits_seen[i]
        self.hits_seen[i] = hits
        # How a plan went, as the game is: the opponent came down, or recovered and was
        # then caught (hit or thrown again), hit the agent back, or neither.
        tr = self.track.get(i)
        if tr is not None:
            a_now = int(round(float(ctx.now[OPP_ACT])))
            tr[1] -= 1
            went = None
            if not tr[2]:
                if a_now in RECOVERY:
                    tr[2], tr[3] = True, hp
                elif a_now in DOWN or tr[1] <= 0:
                    went = 'down'
            elif a_now not in RECOVERY or tr[1] <= 0:
                if hp < tr[3] - 1e-6 or a_now in THROWN:
                    went = 'caught'
                elif ctx.now[SELF_HITSTUN] > 0:
                    went = 'hit back'
                elif tr[1] <= 0:
                    went = 'neither'
            if went is not None:
                c = self.came.setdefault(tr[0], {})
                c[went] = c.get(went, 0) + 1
                self.chances[i] += 1
                self.recovered[i] += went != 'down'
                self.track.pop(i)
        # What it sees: the opponent leaves a hit reaction it was in off the ground, down
        # or into a recovery; and, a recovery over, what it does first.
        act, was = int(round(float(ctx.view[OPP_ACT]))), int(self.was[i])
        self.was[i] = act
        reacting = REACT[0] <= act < REACT[1]
        if reacting and ctx.view[OPP_AIR] > 0:
            self.react_air[i] = True
        elif self.react_air[i] and not reacting:
            self.react_air[i] = False
            if act in RECOVERY:
                self.watching[i] = WATCH + 40   # (the recovery itself, then its choice)
            elif act in DOWN:
                self.counts[i, 0] += 1
        if self.watching[i] > 0 and act not in RECOVERY:
            self.watching[i] -= 1
            what = None
            if ctx.view[OPP_HITSTUN] > 0 or act in THROWN:
                self.watching[i] = 0       # caught before it chose
            elif act >= tactics.FIRST_OWN:
                what = 'move'
            elif act in AIRDASH:
                what = 'dash'
            elif act in AIR_JUMP and act != was:
                what = 'jump'
            elif act in GUARDS:
                what = 'guard'
            elif ctx.view[OPP_AIR] <= 0 or self.watching[i] == 0:
                what = 'fall'
            if what is not None:
                self.counts[i, self.ANSWERS.index(what)] += 1
                self.watching[i] = 0

    def act(self, i, ctx):
        p = self.playing.get(i)
        if p is not None:
            interrupted = p[1] > 0 and ctx.last != self.name
            if interrupted or p[1] >= len(p[0]) or ctx.view[SELF_HITSTUN] > 0:
                self.playing.pop(i)
            else:
                p[1] += 1
                return int(p[0][p[1] - 1])
        if not self.new_hit[i]:
            return None
        now = ctx.now
        if now[OPP_HITSTUN] <= 0 or now[OPP_AIR] <= 0 or now[SELF_HITSTUN] > 0 or \
                self.since_hit[i] > 60 or abs(float(now[DX])) * 640 > self.near:
            return None
        self.asked['seen'] += 1
        shares = self.fixed if self.fixed is not None else \
            belief(self.counts[i], self.prior, self.ANSWERS, self.PRIOR)
        routes = self.host.stack.get('routes') if self.host is not None else None
        r = routes.playing.get(i) if routes is not None else None
        rest = r[0][r[1]:] if r is not None else None
        state = ctx.save()
        if self.planner.lead(state, ctx.side, rest, self.horizon)[1] is None:
            self.asked['held'] += 1   # (the combo holds it, or it cannot recover at all)
            return None
        if i not in self.track:       # a chance to press out: what it does with it is counted
            self.track[i] = ['chance', 150, False, 0.0]
        expects = (self.CHANCE_PRIOR * self.CHANCE_SHARE + self.recovered[i]) / \
            (self.CHANCE_PRIOR + self.chances[i])
        if self.fixed is None and expects < self.least:
            self.asked['unlikely'] = self.asked.get('unlikely', 0) + 1
            return None
        chosen = self.planner.plan(state, ctx.side, ctx.hist, ctx.prev, ctx.seen,
                                   ctx.policy, shares, since=int(self.since_hit[i]), rest=rest,
                                   horizon=self.horizon)
        last = self.planner.last
        if last is None:
            return None
        self.asked['planned'] += 1
        c = last['chosen']
        kind = last['kinds'][c]
        own = last['kinds'].index('own')
        self.plans.append(dict(kind=kind, options=len(last['kinds']) - 2,
                               spread=float(-(last['mix'] * np.log(last['mix'] + 1e-12)).sum()),
                               expected=float(last['expected'][c]),
                               own=float(last['expected'][own]), shares=shares,
                               lead=last['lead'], worth=last['worth'], kinds=last['kinds'],
                               at=None))
        if kind == 'sure throw':
            kind = f"sure throw ({last.get('caught', 0)} ways)"
        self.track[i][0] = kind
        if kind in ('route', 'none'):
            return None                     # the route goes on
        if r is not None:
            routes.playing[i] = None        # its end is this plan's (or its own play's)
        if chosen is None or not len(chosen):
            return None
        self.playing[i] = [chosen, 1, 0, None]
        return int(chosen[0])


def _build(agent, where, files, options, data, name, planner, module, near):
    if where != 'batch':
        raise ValueError(f'{name}: evaluations only so far (a match in real time needs its '
                         'plans made beside the game, as the live routes are)')
    o = dict(options)
    keys = ('per_plan', 'per_class', 'window', 'wait', 'tolerance', 'tolerance_up',
            'temperature', 'hit_worth', 'hurt_worth', 'doubt', 'seed', 'after', 'skip', 'think',
            'sure', 'matrix')
    extra = {k: o.pop(k) for k in ('least', 'ways', 'horizon') if k in o and name == 'endplan'}
    unknown = sorted(set(o) - set(keys) - {'carry', 'prior', 'fixed', 'near'})
    if unknown:
        raise ValueError(f"{name}: no option {', '.join(unknown)}")
    made = planner(data, load_library(files['library']),
                   agent.model.observation_space.shape[0], agent.delay,
                   history=agent.history, **{k: o[k] for k in keys if k in o})
    mod = module(made, agent.delay, carry=o.get('carry', False),
                 prior=float(o.get('prior', 6.0)), fixed=o.get('fixed'),
                 near=float(o.get('near', near)))
    if 'least' in extra:
        mod.least = float(extra['least'])
    if 'horizon' in extra:
        mod.horizon = int(extra['horizon'])
    if 'ways' in extra:
        made.ways = int(extra['ways'])
    return mod


@modules.register('airplan')
def airplan(agent, where, files, options, data):
    """files: library (air_library.py's). options: the file's head."""
    return _build(agent, where, files, options, data, 'airplan', AirPlanner, AirPlan, 320)


@modules.register('jumpplan')
def jumpplan(agent, where, files, options, data):
    """files: library (air_library.py --kind jump's). options: airplan's."""
    return _build(agent, where, files, options, data, 'jumpplan', JumpPlanner, JumpPlan, 260)


@modules.register('endplan')
def endplan(agent, where, files, options, data):
    """files: library (air_library.py --kind ending's). options: airplan's."""
    return _build(agent, where, files, options, data, 'endplan', EndPlanner, EndPlan, 320)
