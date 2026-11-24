"""The planned okizeme (python/efz_env/modules.py; the kind 'okiplan' of an agent.json, of
evaluate.py --p1-module): when the agent sees its opponent knocked down, people's okizeme
from the library (oki_library.py) are tried on copies of the game, each against the ways a
riser answers, and one is chosen by what the match has shown of this opponent.

    okiplan:library=~/data/efz-replays/oki-library.npz[,per_plan=10,temperature=200,carry]

Why (docs/training-v2-log.md, "The whole result" of the told-habits experiment and "The
okizeme module, measured"): the agent's okizeme is one move whoever it plays, a policy
told its opponent's habits plays no differently, and people's clone has the mix but not
the timing. A set-up's timing is a planner's problem, and the choice between set-ups is a
count's.

- **The options.** The library's entries whose player stood where the agent stands now,
  as many steps before the rising as the agent has left (an entry is played with its
  recorded rising on the step this opponent rises: its timing is the knockdown's), at
  most `per_class` of a kind (how it came in, how it is guarded, the side) and `per_plan`
  in all; a wait (a crouching guard through the rising and `wait` steps more, then its
  own play); and its own play.
- **The answers.** Each option is played on copies against a riser that guards crouching,
  guards standing, reverses (its invincible move as it rises: advantages.py's, timed as
  the profiles' is), jumps away, or presses a button. After an option's inputs end the
  agent's own play goes on, seeing each copy as late as it sees the game. What an option
  is worth against an answer: the HP it took less the HP it lost by `window` steps after
  the rising, a first hit of the agent's counted as at least `hit_worth` (the combo its
  routes make of it) and one taken as at least `hurt_worth`.
- **The choice.** What the opponent has done on its wake-ups this set (efz_env.memory's
  counts, of the view the agent has: `delay` steps late), over a prior of the community's
  players (a reversal on 0.10 of the risings, another move on 0.19, a jump or backdash on
  0.04, the rest a guard, crouching in 0.8 of them), gives each answer a share; an option
  is drawn with the weight exp(its expected worth / temperature). So it varies, and it
  leans to what this opponent has shown itself open to. With `doubt` d the draw is
  instead the mix that does best if the shares are only (1 - d) right and the rest is
  whatever answer is worst for the mix (a matrix game, solved by regret matching): what
  beats the expected riser most of the time, and enough of the others that an opponent
  who answers the favourite gains little by it.

The decision is made from what the agent sees (the knockdown, `delay` steps after it);
the copies are of the game as it is, as the routes' are. It plans once a knockdown, when
no module before it (the routes) has the step, and lets go when its inputs end, when the
agent sees itself hit, or when another module took a step.

options: per_plan (10), per_class (2), window (70), wait (40), tolerance (pixels, 24),
after ('own'; 'guard': a crouching guard after an option's inputs on the copies, not its
own play: the game's planner), skip (0: an answer with a share under it isn't counted),
think (0: steps of crouching guard before the plan's first input, the game's planner's
working time), temperature (200), doubt (0), hit_worth (1300), hurt_worth (1200), bait
(0: the HP a riser's reversal that came out and did not hit is worth to the agent, on
the copies where neither hit first: the punish, which the copies do not play; without it
waiting a reversal out is worth nothing and is never drawn. The league's measure,
evaluate.py's faced_risks: a miss of the opponent's costs it 600), prior (6: the wake-ups
the prior counts as), sight (0: the riser's two guards are a crouching one and a standing
one, held whatever the agent does, in the shares its guards have shown; N: the riser
guards by sight, standing while it sees the agent in the air and crouching otherwise,
N steps late, and the standing guard held throughout is SIGHT_STAND of its guards.
People guard so: of their guards of an attack from the air 95% stand, of one from the
ground 92% crouch (the community's replays). Without it an overhead off a jump is worth
a hit four times in five on the copies and is what the planner draws most; in the
league it hits 23% of the time and is its worst okizeme), carry (false: a new match is another opponent; true: the same, evaluate.py
--sets), fixed (none: an answer to plan for whatever was seen, for a test), seed.
"""

import json
import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

from efz_env import ActionTable, EfzVecEnv, modules
from efz_env.actions import encode
from efz_env.history import InputHistory, action_labels
from efz_env.memory import K, Memory

import tactics

TABLE = ActionTable()
INDEX = {a: k for k, a in enumerate(TABLE.actions)}
NEUTRAL, CROUCH_GUARD = INDEX[(5, '')], INDEX[(1, '')]
SELF_ACT, OPP_ACT, SELF_HITSTUN, OPP_HITSTUN = 18, 50, 20, 52
SELF_AIR, OPP_CHAR, DX, SELF_X, OPP_X = 39, 66, 4, 13, 45
ROUND_OVER = 3
DOWN = np.array(sorted(tactics.DOWN))
THROWN = np.arange(0x64, 0x79)
ANSWERS = ('crouch', 'stand', 'reversal', 'jump', 'mash')
# The community's players, the median (docs/training-v2-log.md, "What people's habits look
# like"): a wake-up's invincible move, another move, a jump or backdash; the crouching
# share of a guard is the profiles' (my estimate).
PRIOR = dict(reversal=0.10, mash=0.19, jump=0.04, crouch=0.8)
SIGHT_STAND = 0.08  # with `sight`: the share of a riser's guards that stand whatever comes
FIRST_OWN = 0xc8  # kFirstCharacterAction: a character's own moves from here
MIN_LEAD = 24   # steps to the rising below which nothing is planned (the rising itself is 20)
MOTION = 8      # an entry's move is pressed at most this many steps before it starts
LOOK = 110      # the most steps the rising is looked for
OUT_AGAIN = 14  # `out`: the step after its rising of a riser's second jump out of a corner


def load_library(path):
    """oki_library.py's entries, their inputs as an agent's actions: dicts with actions,
    dist, air (per step), rise, move_at, cls (efz_env.export.load_oki: what an agent file
    is written from)."""
    from efz_env.export import load_oki
    return load_oki(path)


def belief(counts, prior=6.0, crouch_prior=6.0, sight=False):
    """The shares of ANSWERS a riser is expected to give: efz_env.memory's counts (one
    environment's) over the community's prior. sight: the 'crouch' answer is the guard
    by sight (the planner's `sight`), the 'stand' one SIGHT_STAND of the guards."""
    n = float(counts[K['w_n']])
    inv = float(counts[K['w_inv']])
    move = max(0.0, float(counts[K['w_move']]) - inv)
    away = float(counts[K['w_jump']] + counts[K['w_back']])
    rev = (prior * PRIOR['reversal'] + inv) / (prior + n)
    mash = (prior * PRIOR['mash'] + move) / (prior + n)
    jump = (prior * PRIOR['jump'] + away) / (prior + n)
    guard = max(0.0, 1.0 - rev - mash - jump)
    g = float(counts[K['g_n']])
    crouch = (crouch_prior * PRIOR['crouch'] + float(counts[K['g_crouch']])) / (crouch_prior + g)
    if sight:
        crouch = 1 - SIGHT_STAND
    return np.array([guard * crouch, guard * (1 - crouch), rev, jump, mash])


def maximin(worth, rounds=2000):
    """The row player's mix of a matrix game (worth[option, answer], the row's gain) that
    makes the most of the column's best reply: regret matching on both sides, the rows'
    average. (Twelve options against five answers: a few milliseconds.)"""
    worth = np.asarray(worth, float)
    O, R = worth.shape
    regret_p, regret_q, total = np.zeros(O), np.zeros(R), np.zeros(O)
    for _ in range(rounds):
        p = np.maximum(regret_p, 0)
        p = p / p.sum() if p.sum() > 0 else np.full(O, 1 / O)
        q = np.maximum(regret_q, 0)
        q = q / q.sum() if q.sum() > 0 else np.full(R, 1 / R)
        total += p
        rows, cols = worth @ q, p @ worth
        regret_p += rows - p @ rows
        regret_q += q @ cols - cols  # (the column wants the row's gain small)
    return total / total.sum()


class Entries:
    """The library, as arrays to choose a knockdown's entries from."""

    def __init__(self, library, per_plan=10, per_class=2, tolerance=24):
        self.library, self.per_plan, self.per_class = library, per_plan, per_class
        self.tolerance = tolerance
        n = len(library)
        longest = max(len(m['actions']) for m in library)
        self.dist = np.full((n, longest), -10000, np.int32)
        self.air = np.zeros((n, longest), bool)
        for k, m in enumerate(library):
            self.dist[k, :len(m['dist'])] = m['dist']
            self.air[k, :len(m['air'])] = m['air']
        self.rise = np.array([m['rise'] for m in library])
        self.move_at = np.array([m['move_at'] for m in library])
        self.length = np.array([len(m['actions']) for m in library])
        self.corner = np.array([bool(m['corner']) for m in library])
        self.victim = np.array([m['opponent'] for m in library])
        self.cls = np.array([m['cls'] for m in library])

    def pick(self, lead, distance, air, victim, corner):
        """The entries to try with `lead` steps to the rising, the agent `distance`
        pixels from the opponent (in the air or not), against `victim`, in the corner or
        not: [(index, its actions from now)]. An entry is played from its step that is
        `lead` before its recorded rising, if its player was then within `tolerance`
        pixels of that distance, in the air or not as the agent is, and had not yet
        pressed the move that touched; the closest first (an entry on the same character
        and in the same place a little closer), at most per_class of a kind, a kind's
        best before any kind's second, per_plan in all."""
        j0 = self.rise - lead  # (each entry's step that is now)
        ok = (j0 >= 0) & (j0 <= self.move_at - MOTION) & (j0 < self.length)
        j = np.clip(j0, 0, self.dist.shape[1] - 1)
        rows = np.arange(len(j))
        off = np.abs(self.dist[rows, j] - distance)
        ok &= (off <= self.tolerance) & (self.air[rows, j] == bool(air))
        score = off + 6.0 * (self.victim != victim) + 10.0 * (self.corner != bool(corner))
        by, seen = {}, set()
        for k in np.argsort(score, kind='stable'):
            if not ok[k]:
                continue
            key = self.library[k]['actions'][j0[k]:].tobytes()
            if key in seen:  # (the same inputs from here on)
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
        return [(int(k), self.library[k]['actions'][j0[k]:]) for k in picked]


class OkiPlanner:
    """Tries a knockdown's okizeme on copies of the game and draws one."""

    ANSWERS = ANSWERS  # (a planner of another situation has its own: airplan.py)

    def __init__(self, data_dir, library, width, delay, history=16, per_plan=10, per_class=2,
                 window=70, wait=40, tolerance=24, temperature=200.0, hit_worth=1300.0,
                 hurt_worth=1200.0, doubt=0.0, learner='ayu', seed=0, entries=True,
                 scheduled=True, after='own', skip=0.0, think=0, bait=0.0, sight=0, out=0):
        # skip: an answer whose share is under this isn't counted (the game's planner
        # doesn't play it at all: a fifth of a plan's frames for an answer seen one time in
        # thirty). think: the plan is for `think` steps from now, a crouching guard held
        # until then (the frames the game's planner works in beyond the agent's delay).
        self.skip, self.think = float(skip), int(think)
        # bait: a reversal that came out and missed is the agent's punish (the file's head)
        self.bait = float(bait)
        # sight: the riser's 'crouch' answer guards by what it saw of the agent `sight`
        # steps ago (standing against one in the air); 0: it crouches whatever comes
        self.sight, self.seen_air = int(sight), None
        # out: a riser with its back to a wall, the agent on the open side, jumps forward
        # over the agent in its 'jump' answer (without: up-back, which in a corner goes
        # nowhere, and a jump-in okizeme scores against a riser that would have left),
        # with a second jump at the top and forward held after (advantages.py's escape)
        self.out, self.cornered = bool(out), False
        # after: what follows an option's inputs on the copies: 'own', the agent's own play
        # (the network on every copy, every step); 'guard', a crouching guard (what a
        # planner with a frame's spare time can afford: the game's). Its own play as an
        # option is the network's either way.
        if after not in ('own', 'guard'):
            raise ValueError("after: 'own' or 'guard'")
        self.after = after
        self.width, self.delay, self.H = width, delay, history
        # scheduled: the reversal answer from wake_schedule (False: advantages.py's logic a
        # step at a time, the first build's: the two are compared in tests)
        self.scheduled = bool(scheduled)
        # (entries=False: a planner of another library, pressplan.py's, sets its own)
        self.entries = Entries(library, per_plan, per_class, tolerance) if entries else None
        self.window, self.wait, self.temperature = window, wait, float(temperature)
        self.doubt = float(doubt)
        self.hit_worth, self.hurt_worth, self.learner = hit_worth, hurt_worth, learner
        from efz_env.vec import character_names
        self.names = character_names()
        self.R = len(self.ANSWERS)
        # (a frame a step, a KO's too: a copy is played to the round's end and no further)
        make = lambda envs: EfzVecEnv(data_dir, envs, frame_skip=1, rounds_to_win=2,
                                      max_frames=0, autoreset='disabled',
                                      skip_noninteractive=False)
        self.one = make(1)
        self.one.reset()
        self.sim = make((per_plan + 2) * self.R)
        self.sim.reset()
        self.reversals = {}  # victim -> advantages.Advantages (or None: it has no reversal)
        self.rng = np.random.default_rng(seed)
        self.last = None

    def reversal(self, victim):
        if victim not in self.reversals:
            import advantages
            try:
                logic = advantages.Advantages(victim, self.sim.num_envs, seed=0,
                                              learner=self.learner, wake=1.0, blind=1.0)
                logic = logic if logic.wake > 0 else None
            except (ValueError, KeyError):
                logic = None
            self.reversals[victim] = logic
        return self.reversals[victim]

    def wake_schedule(self, victim, theirs, lead):
        """The riser's reversal as its control bytes by step from now: its best invincible
        move on rising that its gauges allow (advantages.py's wake_moves, by its view
        `theirs`), the motion's directions and then its button with the last of them held
        WAKE_HOLD steps, the first of those WAKE_BUTTON steps before it is up (the game
        keeps a button pressed while rising); a crouching guard before. [] if it has no
        such move now (it guards). What advantages.py's `wake` does when it always
        reverses, as a list: the game's planner (port/agent) plays the same."""
        import advantages
        logic = self.reversal(victim)
        plan = logic.pick_wake(theirs) if logic is not None else None
        if not plan:
            return []
        dirs, button = plan
        start = max(0, lead - advantages.WAKE_BUTTON - (len(dirs) - 1))
        return ([encode(1)] * start + [encode(d) for d in dirs[:-1]] +
                [encode(dirs[-1], button)] * advantages.WAKE_HOLD)

    def lead(self, state, side):
        """(the steps until the opponent is up, the game's view now) for a saved game."""
        one = self.one
        one.load_state(0, state)
        now = one.obs[0, side].copy()
        self.theirs = one.obs[0, 1 - side].copy()  # the opponent's own view now
        controls = np.zeros((1, 2), np.uint8)
        controls[0, side], controls[0, 1 - side] = encode(1), encode(1)
        obs = one.obs
        for t in range(LOOK):
            if int(round(float(obs[0, side, OPP_ACT]))) not in DOWN:
                return t, now
            obs, _, term, trunc, _ = one.step(controls)
            if term[0] or trunc[0]:
                break
        return None, now

    def candidates(self, lead, now):
        """Entries.pick for the game's view now."""
        return self.entries.pick(lead, abs(float(now[DX])) * 640, now[SELF_AIR] > 0,
                                 self.names[int(round(float(now[OPP_CHAR])))],
                                 abs(float(now[OPP_X])) > 0.8)

    def plan(self, state, side, hist, prev, seen, policy, shares):
        """state: the game now (the opponent down); side: the agent's; hist (H, 6), prev:
        its input history; seen: its views, newest first ((delay + 1, dim)); policy: its
        own play's (views -> actions); shares: of ANSWERS. Returns (the chosen option's
        actions, or None: its own play; what was tried: self.last)."""
        self.last = None
        ahead = np.full(self.think, CROUCH_GUARD)
        if self.think:  # the game as it will be then, and what the agent will have seen
            one = self.one
            one.load_state(0, state)
            seen = np.array(seen, np.float32)
            h = InputHistory((1,), self.H)
            h.buf[0], h.prev[0] = hist, prev
            controls = np.zeros((1, 2), np.uint8)
            controls[0, side], controls[0, 1 - side] = encode(1), encode(4)
            for _ in range(self.think):
                obs, _, term, trunc, info = one.step(controls)
                if term[0] or trunc[0] or obs[0, side, ROUND_OVER] != 0:
                    return None
                h.push(info['input'][:, side])
                seen[1:] = seen[:-1]
                seen[0] = obs[0, side]
            state, hist, prev = one.save_state(0), h.buf[0].copy(), int(h.prev[0])
        lead, now = self.lead(state, side)
        if lead is None or lead < MIN_LEAD:
            return None
        self.cornered = bool(abs(float(now[OPP_X])) > 0.8 and
                             abs(float(now[SELF_X])) < abs(float(now[OPP_X])))
        cands = self.candidates(lead, now)
        options = [a for _, a in cands] + [np.full(lead + self.wait, CROUCH_GUARD), np.zeros(0, int)]
        kinds = [str(self.entries.cls[k]) for k, _ in cands] + ['wait', 'own']
        victim = self.names[int(round(float(now[OPP_CHAR])))]
        if self.scheduled:
            out = self.tryout(state, side, lead, options, kinds, [k for k, _ in cands], hist,
                              prev, seen, policy, shares,
                              schedule=self.wake_schedule(victim, self.theirs, lead))
        else:
            out = self.tryout(state, side, lead, options, kinds, [k for k, _ in cands], hist,
                              prev, seen, policy, shares, logic=self.reversal(victim))
        if not self.think or self.last is None:
            return out
        return ahead if out is None else np.concatenate([ahead, out])

    def count_from(self, lead):
        """The step of the copies from which a first hit counts (before: the knockdown's
        own reactions)."""
        return lead - 2

    def their_controls(self, t, lead, answer, side, schedule, logic):
        """The opponent's control bytes on step t of the copies, by each copy's answer
        (answer: its index in ANSWERS, a copy each)."""
        guard, stand, jump = encode(1), encode(4), encode(7)
        if self.out and self.cornered:  # out of the corner: a second jump at the top, then forward
            k = t - lead
            jump = encode(9 if k < OUT_AGAIN else 5 if k == OUT_AGAIN else
                          9 if k < OUT_AGAIN + 4 else 6)
        theirs = np.full(len(answer), guard, np.uint8)
        theirs[answer == 1] = stand
        if self.sight and self.seen_air is not None:  # the guard by sight, late
            theirs[(answer == 0) & self.seen_air[max(0, len(self.seen_air) - 1 - self.sight)]] = stand
        if t >= lead - 2:
            theirs[answer == 3] = jump
        if t >= lead - 1:
            theirs[answer == 4] = encode(2, 'A') if t % 2 == 0 else encode(2)
        if schedule is not None:
            if t < len(schedule):
                theirs[answer == 2] = schedule[t]
        elif logic is not None:
            for e in np.flatnonzero(answer == 2):
                out = logic.step(int(e), self.sim.obs[e, 1 - side])
                if out is not None:
                    theirs[e] = encode(out[0], out[1])
        return theirs

    def tryout(self, state, side, lead, options, kinds, entries, hist, prev, seen, policy,
               shares, logic=None, schedule=None):
        """The options (actions each; the last two a wait and its own play) against the
        answers, the opponent able to act `lead` steps from now, and one drawn. The
        reversal answer: logic (advantages.py's, a riser's) or schedule (its control
        bytes by step, from now); with neither it guards. Returns the chosen option's
        actions or None (its own play); self.last: what was tried."""
        O, R, sim = len(options), self.R, self.sim
        E = O * R
        hp0 = np.zeros((E, 2))
        for e in range(E):
            sim.load_state(e, state)
            hp0[e] = sim.info['hp'][e]
            if logic is not None:
                logic.clear(e)
        views = np.repeat(np.asarray(seen, np.float32)[None], E, 0)
        hists = InputHistory((E,), self.H)
        hists.buf[:] = hist
        hists.prev[:] = prev
        answer = np.tile(np.arange(R), O)
        option = np.repeat(np.arange(O), R)
        length = np.array([len(options[o]) for o in option])
        first = np.zeros(E, int)   # 1: the agent's hit came first; -1: the opponent's
        hp = hp0.copy()
        over = np.zeros(E, bool)
        stun = np.zeros((E, 2), bool)
        stun[:, 0] = sim.obs[:E, side, SELF_HITSTUN] > 0
        stun[:, 1] = sim.obs[:E, side, OPP_HITSTUN] > 0
        thrown = np.zeros((E, 2), bool)
        thrown[:, 0] = np.isin(np.round(sim.obs[:E, side, SELF_ACT]), THROWN)
        thrown[:, 1] = np.isin(np.round(sim.obs[:E, side, OPP_ACT]), THROWN)
        moved = np.zeros(E, bool)  # the riser started a move of its own (its reversal)
        # (what the riser has seen of the agent, a step each: in the air or not)
        self.seen_air = [sim.obs[:E, side, SELF_AIR] > 0] if self.sight else None
        controls = np.zeros((sim.num_envs, 2), np.uint8)
        for t in range(lead + self.window):
            mine = np.full(E, CROUCH_GUARD)
            own = t >= length
            for e in np.flatnonzero(~own):
                mine[e] = options[option[e]][t]
            if self.after == 'guard':  # (only the option that is its own play)
                own = own & (length == 0)
            if own.any():
                view = np.concatenate([views[own, -1], hists.features()[own].reshape(
                    int(own.sum()), -1)], 1)[:, :self.width]
                mine[own] = np.asarray(policy(view)).reshape(-1)
            controls[:E, side] = TABLE.table[mine]
            controls[:E, 1 - side] = self.their_controls(t, lead, answer, side, schedule, logic)
            obs, _, term, trunc, info = sim.step(controls)
            hists.push(info['input'][:E, side])
            views[:, 1:] = views[:, :-1]
            views[:, 0] = obs[:E, side]
            if self.sight:
                self.seen_air.append(obs[:E, side, SELF_AIR] > 0)
            s = np.stack([obs[:E, side, SELF_HITSTUN] > 0, obs[:E, side, OPP_HITSTUN] > 0], 1)
            th = np.stack([np.isin(np.round(obs[:E, side, SELF_ACT]), THROWN),
                           np.isin(np.round(obs[:E, side, OPP_ACT]), THROWN)], 1)
            began = (s & ~stun) | (th & ~thrown)
            stun, thrown = s, th
            if t >= self.count_from(lead):
                moved |= (np.round(obs[:E, side, OPP_ACT]) >= FIRST_OWN) & ~over
                undecided = (first == 0) & ~over
                first[undecided & began[:, 1]] = 1
                first[undecided & began[:, 0] & ~began[:, 1]] = -1
            live = ~over
            hp[live] = info['hp'][:E][live]
            if t + 1 == lead and getattr(self, 'from_lead', False):
                # (endplan: against a victim that recovers, only what follows its
                # recovery counts: the combo's own last hits are every option's)
                hp0[answer > 0] = hp[answer > 0]
            over |= term[:E] | trunc[:E] | (obs[:E, side, ROUND_OVER] != 0)
            if over.all():
                break
        dealt = np.maximum(hp0[:, 1 - side] - hp[:, 1 - side], 0)
        taken = np.maximum(hp0[:, side] - hp[:, side], 0)
        worth = (np.where(first > 0, np.maximum(dealt, self.hit_worth), dealt) -
                 np.where(first < 0, np.maximum(taken, self.hurt_worth), taken)).reshape(O, R)
        baited = np.zeros((O, R), bool)
        if self.bait > 0 and 'reversal' in self.ANSWERS:
            r = self.ANSWERS.index('reversal')
            baited[:, r] = (moved & (first == 0)).reshape(O, R)[:, r]
            worth = worth + self.bait * baited
        shares = np.asarray(shares, float)
        counted = shares >= self.skip
        if not counted.any():
            counted[:] = True
        expected = worth[:, counted] @ (shares[counted] / shares[counted].sum())
        if self.doubt > 0:  # the shares may be wrong by `doubt`, the worst way for the mix
            mix = maximin((1 - self.doubt) * expected[:, None] + self.doubt * worth[:, counted])
        else:
            w = np.exp((expected - expected.max()) / self.temperature)
            mix = w / w.sum()
        chosen = int(self.rng.choice(O, p=mix / mix.sum()))
        self.last = dict(lead=int(lead), kinds=kinds, worth=worth, expected=expected,
                         chosen=chosen, mix=mix, first=first.reshape(O, R),
                         entries=list(entries), baited=baited)
        return None if kinds[chosen] == 'own' else np.asarray(options[chosen])


class OkiPlan(modules.Module):
    """The module 'okiplan' (see the file's head)."""
    name = 'okiplan'

    def __init__(self, planner, delay, carry=False, prior=6.0, fixed=None):
        if delay <= 0:
            raise ValueError('okiplan plans when the player sees the knockdown: delay > 0')
        self.planner, self.delay, self.carry, self.prior = planner, delay, bool(carry), prior
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
        self.playing = {}                  # env -> [actions, step]
        self.was_down = np.zeros(n, bool)  # it saw the opponent down on the step before
        self.pending = np.zeros(n, bool)   # a knockdown seen, not planned for yet

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        if self.memory is not None:
            if self.carry:  # the same opponent again: what it showed is kept, older
                self.memory.end(mask, new_set=np.zeros(self.n, bool))
            else:
                self.memory.clear(mask)
        for i in np.flatnonzero(mask):
            self.playing.pop(int(i), None)
        self.was_down[mask] = self.pending[mask] = False

    def see(self, obs, step):
        a = self.host.agent
        views = a.seen.buf[:, a.delay] if a.delay else obs  # what it sees, late
        self.memory.update(np.asarray(views)[:, :168])

    def watch(self, i, ctx):
        down = int(round(float(ctx.view[OPP_ACT]))) in DOWN
        if down and not self.was_down[i]:
            self.pending[i] = True
        elif not down:
            self.pending[i] = False
        self.was_down[i] = down

    def act(self, i, ctx):
        p = self.playing.get(i)
        if p is not None:
            interrupted = p[1] > 0 and ctx.last != self.name
            if interrupted or p[1] >= len(p[0]) or ctx.view[SELF_HITSTUN] > 0:
                self.playing.pop(i)
            else:
                p[1] += 1
                return int(p[0][p[1] - 1])
        if not self.pending[i]:
            return None
        self.pending[i] = False  # once a knockdown
        if int(round(float(ctx.now[OPP_ACT]))) not in DOWN or ctx.view[SELF_HITSTUN] > 0:
            return None
        shares = self.fixed if self.fixed is not None else \
            belief(self.memory.c[i], self.prior, self.prior, sight=bool(getattr(self.planner, 'sight', 0)))
        chosen = self.planner.plan(ctx.save(), ctx.side, ctx.hist, ctx.prev, ctx.seen,
                                   ctx.policy, shares)
        last = self.planner.last
        if last is None:
            return None
        c = last['chosen']
        own = last['kinds'].index('own')
        self.plans.append(dict(kind=last['kinds'][c], options=len(last['kinds']) - 2,
                               spread=float(-(last['mix'] * np.log(last['mix'] + 1e-12)).sum()),
                               expected=float(last['expected'][c]),
                               own=float(last['expected'][own]), shares=shares,
                               lead=last['lead'],
                               baited='baited' in last and bool(last['baited'][c].any())))
        if chosen is None or not len(chosen):
            return None
        self.playing[i] = [chosen, 1]
        return int(chosen[0])

    def stats(self):
        p = self.plans
        if not p:
            return dict(plans=0)
        kinds = {}
        for x in p:
            kinds[x['kind']] = kinds.get(x['kind'], 0) + 1
        return dict(plans=len(p),
                    options=round(float(np.mean([x['options'] for x in p])), 2),
                    lead=round(float(np.mean([x['lead'] for x in p])), 1),
                    expected=round(float(np.mean([x['expected'] for x in p]))),
                    own=round(float(np.mean([x['own'] for x in p]))),
                    # (how many options a draw is between: exp of the mix's entropy)
                    between=round(float(np.exp(np.mean([x['spread'] for x in p]))), 2),
                    chosen={k: round(v / len(p), 3) for k, v in
                            sorted(kinds.items(), key=lambda kv: -kv[1])},
                    # (the chosen option one that waits the riser's reversal out)
                    baits=round(float(np.mean([x.get('baited', False) for x in p])), 3),
                    shares={a: round(float(np.mean([x['shares'][j] for x in p])), 3)
                            for j, a in enumerate(ANSWERS)})

    def close(self):
        for env in (self.planner.one, self.planner.sim):
            env.close()


@modules.register('okiplan')
def okiplan(agent, where, files, options, data):
    """files: library (oki_library.py's). options: the file's head."""
    if where != 'batch':
        raise ValueError('okiplan: evaluations only so far (a match in real time needs its '
                         'plans made beside the game, as the live routes are)')
    o = dict(options)
    keys = ('per_plan', 'per_class', 'window', 'wait', 'tolerance', 'temperature', 'hit_worth',
            'hurt_worth', 'doubt', 'seed', 'after', 'skip', 'think', 'bait', 'sight', 'out')
    unknown = sorted(set(o) - set(keys) - {'carry', 'prior', 'fixed'})
    if unknown:
        raise ValueError(f"okiplan: no option {', '.join(unknown)}")
    planner = OkiPlanner(data, load_library(files['library']),
                         agent.model.observation_space.shape[0], agent.delay,
                         history=agent.history, **{k: o[k] for k in keys if k in o})
    return OkiPlan(planner, agent.delay, carry=o.get('carry', False),
                   prior=float(o.get('prior', 6.0)), fixed=o.get('fixed'))
