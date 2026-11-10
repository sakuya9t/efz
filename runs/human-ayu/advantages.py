"""A red team's advantages (the user's, 9 November: "very high RG-invincible rate, so that
the agent learns not to keep inputting; 100%-250% damage; red team can abuse throwing, so
it won't keep guarding under pressure"), for any opponent, in training (finetune.py
--vs-rg, --vs-reversal, --vs-throw, --vs-damage) and in evaluations (evaluate.py
--p2-advantage):

- rg: the share of its guards the game makes recoil guards (efz_env_set_recoil_guard, as
  the game's CPU gets its own: the window opened as the hit lands), of the guards it holds
  the right way;
- reversal: of its recoil guards, the share after which, if the agent presses on (starts
  a move of its own within ARM steps: "an RG and an invincible during it", the user's
  read of a habit), it plays its fastest invincible move that comes out of a recoil guard
  and that its gauges allow (motions.json: the motion, as a person would input it);
- throw: the share of its chances to throw (both on the ground, within 28 pixels, the
  agent neither in a hit or guard reaction nor protected from throws, itself free to act)
  in which it throws (forward + C);
- damage: the scale on the damage the agent takes from its hits (efz_env_set_damage_scale);
- bait: of the agent's wake-up reversals (an invincible move within WAKE steps of rising)
  that it isn't committed against (free to act: standing, walking, crouching), the share
  it guards through (crouching: Ayu's invincible moves are all mid; seen as it starts, as
  the advantages see everything) and punishes with its fastest move that reaches and
  starts before the agent recovers (its own play sees the game late, too late for that).
  The user's games of 9 November: the agent rose with one on a third of its wake-ups and
  was hit back on half. Waiting on every wake-up instead gave up the opponent's okizeme
  for little: the agent rises with one on a fifth.

The opponent reads the game as it is, with no reaction time: an advantage too. Its own
policy plays every other step. People's play is the guide, human limits are the agent's
alone: these are the opponent's, to make a habit of the agent's cost what it would
against a strong player, more often.
"""

import json
import os

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))

# Columns of a player's own view (efz_env_obs_name).
DX, SELF_GAUGE, SELF_RF, SELF_BLUE = 4, 9, 10, 11
SELF_Y, SELF_ACT, OPP_Y, OPP_ACT = 14, 18, 46, 50
FIRST_OWN = 0xc8  # tactics.FIRST_OWN: a character's own moves
SELF_HITSTUN, SELF_GUARDING, OPP_HITSTUN, OPP_GUARDING, OPP_THROW_PROTECTED = 20, 21, 52, 53, 60
OPP_ACT_FRAME = 51
DOWN = (0x60, 0x61, 0x62, 0x63)  # tactics.DOWN: wake-up, the two knockdowns, lying
WAKE = 8  # focus.WAKE_WINDOW: steps after a knockdown's end in which a reversal is a wake-up one
OUTCOME = 60  # steps after a reversal starts in which its outcome is counted
RG = (0xa8, 0xa9, 0xaa)
FREE = (0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0x9, 0xe, 0xf, 0x10)  # tactics.FREE
THROW_REACH = 28 / 640  # the game's throws reach 30 pixels (src/ayu.cpp etc.)
ARM = 30  # steps after a recoil guard in which the agent's next move sets off the reversal
# The reversal's input: its motion once, from the step of the recoil guard motions.py found
# it comes out from (rg_delay: the game drops what comes before; START if not known), then,
# should a longer freeze have dropped it, its button again every other step with the last
# direction held (a person's mashing; a motion input again can read as another, 2 3 6C
# 2 3 6C as 623C) until the move starts.
START, MASH = 8, 12


def parse(spec):
    """'rg=0.5,reversal=0.8,throw=0.3,damage=2' -> dict (left out: none)."""
    out = dict(rg=0.0, reversal=0.0, throw=0.0, damage=1.0, bait=0.0)
    for part in filter(None, (spec or '').split(',')):
        k, v = part.split('=')
        if k not in out:
            raise ValueError(f'advantage {k}: rg, reversal, throw, damage or bait')
        out[k] = float(v)
    return out


def invincible_moves(char):
    """The character's invincible moves (motions.json), fastest first: (directions,
    button, startup, needs) with needs 'bar' (a super: a level of power), 'rf' (a
    C-button special: half the RF gauge, or blue) or None."""
    data = json.load(open(os.path.join(HERE, 'motions.json'))).get(char, {})
    out = []
    for m in data.get('invincible', []):
        # Only those that come out of a recoil guard and win against pressure (motions.py)
        if not m.get('from_rg', True) or m.get('rg_hits', True) is not True:
            continue
        motion = m['motion']
        dirs, button = [int(d) for d in motion[:-1]], motion[-1]
        needs = 'bar' if len(dirs) >= 6 else 'rf' if button == 'C' else None
        out.append((dirs, button, m['startup'], needs, int(m['pattern'], 16),
                    m.get('rg_delay', START)))
    return sorted(out, key=lambda m: m[2])


def learner_reversals(char):
    """The learner's invincible attacks (framedata.json, throws left out): {pattern:
    (startup, steps)}."""
    data = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    return {int(k, 16): (m['startup'], m['steps']) for k, m in data.items()
            if m['invincible'] and m['startup'] is not None and m['level'] >= 10
            and int(k, 16) < 0x190}


def punishers(char):
    """The character's moves to punish with, fastest first: its invincible ones from
    neutral (motions.json, an attack that starts and hits fast), as (directions, button,
    startup, needs, reach in pixels)."""
    data = json.load(open(os.path.join(HERE, 'motions.json'))).get(char, {})
    fd = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    out = []
    for m in data.get('invincible', []):
        motion = m['motion']
        dirs, button = [int(d) for d in motion[:-1]], motion[-1]
        needs = 'bar' if len(dirs) >= 6 else 'rf' if button == 'C' else None
        reach = fd.get(m['pattern'], {}).get('reach') or 0
        out.append((dirs, button, m['startup'] + len(dirs) - 1, needs, reach))
    return sorted(out, key=lambda m: m[2])


class Advantages:
    """The per-environment logic: step(i, view) gives the controls that override the
    opponent's own on this step, as (numpad direction, buttons), or None."""

    def __init__(self, char, n, reversal=0.0, throw=0.0, seed=0, bait=0.0, learner='ayu'):
        self.moves = invincible_moves(char) if reversal > 0 else []
        self.patterns = {m[4] for m in self.moves}
        self.reversal, self.throw, self.bait = reversal, throw, bait
        self.theirs = learner_reversals(learner) if bait > 0 else {}
        self.punish_moves = punishers(char) if bait > 0 else []
        self.rng = np.random.default_rng(seed)
        self.resize(n)
        self.counts = dict(rg=0, armed=0, reversals=0, reversals_started=0, reversal_hit=0,
                           reversal_hit_back=0, throw_chances=0, throws=0,
                           wake_reversals=0, baited=0, baited_hit_us=0, bait_punishes=0,
                           bait_punished=0)

    def resize(self, n):
        self.queue = [[] for _ in range(n)]
        self.prev = np.full(n, -1)
        self.prev_opp = np.full(n, -1)
        self.was_close = np.zeros(n, bool)
        self.armed = np.zeros(n, int)  # steps left in which the agent's move sets one off
        self.trying = np.zeros(n, int)  # steps left to start a reversal in
        self.watch = np.zeros(n, int)  # steps left to see a started reversal's outcome
        self.hit_prev = np.zeros((n, 2), bool)
        self.baiting = np.zeros(n, int)  # 2: guarding its reversal
        self.since_up = np.full(n, 999)  # steps since the agent rose from a knockdown
        self.blocked = np.zeros(n, bool)  # it guarded the reversal
        self.free_steps = np.zeros(n, int)  # steps out of guard since
        self.punish = np.zeros(n, int)  # steps left to see the baited reversal punished

    def clear(self, i):
        self.queue[i] = []
        self.prev[i] = self.prev_opp[i] = -1
        self.was_close[i] = False
        self.armed[i] = self.trying[i] = self.watch[i] = 0
        self.baiting[i] = self.punish[i] = 0
        self.since_up[i] = 999

    def pick(self, v):
        """The fastest invincible move its gauges allow, as its input: the motion, then the
        button mashed with the last direction held."""
        for dirs, button, _, needs, pattern, delay in self.moves:
            if needs == 'bar' and v[SELF_GAUGE] < 1 / 3:
                continue
            if needs == 'rf' and v[SELF_RF] < 0.5 and v[SELF_BLUE] < 0.5:
                continue
            last = dirs[-1]
            return ([(d, '') for d in dirs[:-1]] + [(last, button)]
                    + [(last, ''), (last, button)] * MASH), delay
        return None

    def step(self, i, v):
        a, o = int(round(v[SELF_ACT])), int(round(v[OPP_ACT]))
        hit = np.array([v[OPP_HITSTUN] > 0.5, v[SELF_HITSTUN] > 0.5])
        rose = hit & ~self.hit_prev[i]
        self.hit_prev[i] = hit
        if self.watch[i] > 0:  # who is hit first after its reversal
            self.watch[i] -= 1
            if rose[0] or rose[1]:
                self.counts['reversal_hit' if rose[0] else 'reversal_hit_back'] += 1
                self.watch[i] = 0
        if self.trying[i] and a in self.patterns:  # it came out: let it play
            self.counts['reversals_started'] += 1
            self.trying[i] = 0
            self.queue[i] = []
            self.watch[i] = OUTCOME
        if self.trying[i] and not self.queue[i]:
            self.trying[i] = 0  # it didn't come out
        if self.armed[i] > 0:
            self.armed[i] -= 1
            plan = self.pick(v) if o != self.prev_opp[i] and o >= FIRST_OWN else None
            if plan:  # the agent presses on: from the step of the recoil guard it comes out on
                seq, delay = plan
                self.counts['reversals'] += 1
                since = ARM - 1 - self.armed[i]
                self.armed[i] = 0
                self.trying[i] = 1
                self.queue[i] = [(5, '')] * max(0, delay - since) + seq
        out = self.step_bait(i, v, a, o, rose)
        if out is not None:
            self.prev[i], self.prev_opp[i] = a, o
            return out
        if a in RG and self.prev[i] not in RG:
            self.counts['rg'] += 1
            if self.moves and self.rng.random() < self.reversal:
                self.counts['armed'] += 1
                self.armed[i] = ARM
        if self.queue[i]:
            out = self.queue[i].pop(0)
        if out is None and self.throw > 0:
            close = (abs(v[DX]) < THROW_REACH and v[SELF_Y] >= 0 and v[OPP_Y] >= 0
                     and v[OPP_HITSTUN] < 0.5 and v[OPP_GUARDING] < 0.5
                     and v[OPP_THROW_PROTECTED] < 0.5 and a in FREE)
            if close and not self.was_close[i]:
                self.counts['throw_chances'] += 1
                if self.rng.random() < self.throw:
                    self.counts['throws'] += 1
                    self.queue[i] = [(6, 'C')]  # a fresh press: forward + C
                    out = (6, '')
            self.was_close[i] = close
        self.prev[i], self.prev_opp[i] = a, o
        return out

    def punish_with(self, v, left):
        """The input of the fastest punisher that reaches and starts within `left` steps: a
        throw within its reach (both on the ground), else a move."""
        dist = abs(v[DX]) * 640
        if abs(v[DX]) < THROW_REACH and v[SELF_Y] >= 0 and v[OPP_Y] >= 0 and left > 2:
            return [(6, ''), (6, 'C')]
        for dirs, button, startup, needs, reach in self.punish_moves:
            if startup >= left or reach < dist:
                continue
            if needs == 'bar' and v[SELF_GAUGE] < 1 / 3:
                continue
            if needs == 'rf' and v[SELF_RF] < 0.5 and v[SELF_BLUE] < 0.5:
                continue
            return [(d, '') for d in dirs[:-1]] + [(dirs[-1], button)]
        return None

    def step_bait(self, i, v, a, o, rose):
        """The bait's control for this step (a guard), or None."""
        if self.punish[i] > 0:  # after a baited reversal: is it punished?
            self.punish[i] -= 1
            if rose[0]:
                self.counts['bait_punished'] += 1
                self.punish[i] = 0
        if self.bait <= 0:
            return None
        if o in DOWN:
            self.since_up[i] = 0
        elif self.since_up[i] < 999:
            self.since_up[i] += 1
        if (self.baiting[i] == 0 and o in self.theirs and o != self.prev_opp[i]
                and self.since_up[i] <= WAKE):  # a wake-up reversal
            self.counts['wake_reversals'] += 1
            if a in FREE and self.rng.random() < self.bait:  # not committed: guard it through
                self.counts['baited'] += 1
                self.baiting[i], self.blocked[i], self.free_steps[i] = 2, False, 0
                self.queue[i], self.armed[i], self.trying[i] = [], 0, 0
        if self.baiting[i] == 2:
            if rose[1]:
                self.counts['baited_hit_us'] += 1
            guarding = v[SELF_GUARDING] > 0.5
            self.blocked[i] |= guarding
            self.free_steps[i] = 0 if guarding else self.free_steps[i] + 1
            done = (o not in self.theirs  # its move ended
                    or (self.blocked[i] and self.free_steps[i] >= 2)  # its hits are over
                    or (not self.blocked[i] and v[OPP_ACT_FRAME] > self.theirs[o][0] + 10))
            if done:
                self.baiting[i] = 0
                self.punish[i] = 45
                left = self.theirs[o][1] - v[OPP_ACT_FRAME] if o in self.theirs else 0
                seq = self.punish_with(v, left)
                if seq:  # its fastest move that reaches and starts before the agent recovers
                    self.counts['bait_punishes'] += 1
                    self.queue[i] = seq
                    return self.queue[i].pop(0)
                return None
            return (1, '')
        return None

    def take(self):
        c = dict(self.counts)
        for k in self.counts:
            self.counts[k] = 0
        return c


def set_env(env, indices, side, adv):
    """The game's part of the advantages, on environments `indices` of an EfzVecEnv:
    the recoil-guard share of player `side` and the damage the other takes."""
    for i in indices:
        if adv['rg'] > 0:
            env.set_recoil_guard(int(i), side, adv['rg'])
        if adv['damage'] != 1:
            env.set_damage_scale(int(i), 1 - side, adv['damage'])


class AdvantagedOpponent:
    """finetune.py's: an EfzSB3VecEnv opponent (player 2) with the advantages' inputs.
    attach(venv) first. The game's part (rg, damage) is finetune.make_env's."""
    takes_index = True

    def __init__(self, inner, char, adv, seed=0, learner='ayu'):
        from efz_env.actions import ActionTable
        self.inner, self.adv = inner, adv
        self.table = ActionTable()
        self.index = {a: k for k, a in enumerate(self.table.actions)}
        self.logic = Advantages(char, 0, adv['reversal'], adv['throw'], seed,
                                adv.get('bait', 0.0), learner)
        self.venv = None
        self.only = None  # the environments that play with the advantages (None: all)

    def attach(self, venv):
        self.venv = venv
        self.logic.resize(venv.env.num_envs)

    def __call__(self, obs, idx):
        actions = np.asarray(self.inner(obs)).copy()
        v = self.venv
        for k, i in enumerate(idx):
            i = int(i)
            if self.only is not None and not self.only[i]:
                continue
            if v._length[i] == 0:  # a new match
                self.logic.clear(i)
            o = self.logic.step(i, v.env.obs[i, 1])
            if o is not None:
                actions[k] = self.index[o]
        return actions


class AdvantagedAgent:
    """evaluate.py's: an efz_env.agent.Agent with the advantages, its game's part set on
    the evaluation's environment as it attaches."""

    def __init__(self, agent, char, adv, seed=0, learner='ayu'):
        from efz_env.actions import encode
        self.agent, self.adv, self.encode = agent, adv, encode
        self.logic = Advantages(char, 0, adv['reversal'], adv['throw'], seed,
                                adv.get('bait', 0.0), learner)
        self.env = self.side = None

    def __getattr__(self, name):  # the rest is the agent's
        return getattr(self.agent, name)

    def attach(self, env, side):
        self.env, self.side = env, side
        set_env(env, range(env.num_envs), side, self.adv)
        if hasattr(self.agent, 'attach'):
            self.agent.attach(env, side)

    def batch(self, n):
        self.agent.batch(n)
        self.logic.resize(n)

    def reset(self, mask=None):
        self.agent.reset(mask)
        for i in (range(len(self.logic.queue)) if mask is None else np.flatnonzero(mask)):
            self.logic.clear(int(i))

    def controls(self, obs, step):
        own = np.asarray(self.agent.controls(obs, step)).copy()
        now = self.env.obs[:, self.side]  # the game as it is, not as the agent sees it
        for i in range(len(own)):
            o = self.logic.step(i, now[i])
            if o is not None:
                own[i] = self.encode(*o)
        return own
