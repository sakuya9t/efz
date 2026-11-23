"""A focus for an opponent: a shaping reward, on top of the game's, for what it is
meant to be good at, by tactics.py's definitions, for finetune.py --focus.

    env = Focus(EfzSB3VecEnv(...), 'setup', coef=0.02)

'setup': a move started in free time (the learner free, its opponent not: tactics'
    free time) that puts out an object of its own within SETUP_WINDOW steps (a trap, a
    projectile: Mizuka's, Misuzu's game);
'charge': a move that builds the character's own resource (tactics.CHARGE: Kano's 5D,
    236D) started in free time;
'reversal': an invincible attack of its own (framedata.json: invulnerable in its first
    steps; not a throw) started as it rises (within WAKE_WINDOW steps of a knockdown's
    end) or after a recoil guard (within RG_WINDOW steps), that hits the opponent within
    REVERSAL_WINDOW steps, before the learner is hit itself: the user's answer to an agent
    that presses the same thing at every wake-up and in every string ("a wake-up
    invincible, or an RG and an invincible during it");
'air': a hit of its own, made in the air, that begins the hit reaction of an opponent on
    the ground: a jump-in that lands (docs/training-v2.md, "Round 17": people's opponents
    jump in on Ayu 2.9 times a minute, the league's 1.1, and the agent walks into them).

'out': getting away: an air recovery of its own (out of a hit reaction, src/player.cpp's
    TryAirRecovery) after which it is not hit or thrown again within OUT_WINDOW steps;
    and leaving a corner it was held in (within CORNER_IN of a wall, the opponent on the
    open side within CORNER_NEAR pixels, for CORNER_LEAST steps in which it guarded or was
    hit) on its own feet or through the air, not in a hit reaction: an opponent that
    recovers whenever it is safe and escapes pressure whenever it can (the user's, 18
    November), which learns by the game's own reward what to do next. What a combo that
    lets its victim go and a pressure that does not hold cost the agent.

'press': pressure. A move of its own that the opponent guards (a guard of the opponent's
    touched; not a recoil guard) adds PRESS_CONTACT of `coef`, and a hit of its own that
    begins the opponent's hit reaction within PRESS_WINDOW steps of such a guard adds
    `coef`: a string that opens the guard, or catches what leaves it. Why (the user's
    games of 21 November against round 21's agent, "sucks under pressure"): against the
    league's opponents the agent guards 4 to 7 times a minute and against the user 13 to
    18; there a move pressed after a guard gets away a third of the time and is hit 14 to
    19%, against the user it is hit 42% and a jump out 27% (2% get away), and three
    quarters of the HP the agent loses under the user's pressure it loses by leaving its
    guard. Nothing in the league holds it in a guard, so nothing there teaches it one.

'corner': its own pressure, in the corners above all (the user's, 22 November: "in order
    to learn how to handle pressure, it needs to understand how to pressure properly,
    especially at corners"; against an opponent that jumps out of a corner when it is
    free there, four in five of the agent's corner stays end with that jump, people's two
    in five). press's two events, each CORNER_TIMES as much while the opponent is held in
    a corner (the opponent within CORNER_IN of a wall, or within CORNER_OUT once it was,
    the learner on the open side within CORNER_NEAR pixels); and a jump out caught: a
    hit of the learner's that begins the hit reaction of an opponent in the air there
    adds CORNER_TIMES of `coef`.

Each such event adds `coef` to the step's reward (the game's: damage dealt minus taken
in full bars, so 0.02 is 200 HP's worth). The learner is player 1; the events are read
from its current view (as the game is, not as it sees it late). `counts` keeps the
events and steps since the last `take()`, for the log.
"""

import numpy as np
from stable_baselines3.common.vec_env import VecEnvWrapper

import tactics

ACT_SELF, ACT_OPP = 18, 50
FRAME_OPP = 51
HITSTUN_SELF, HITSTUN_OPP = 20, 52
OBJECTS = [72 + 6 * k for k in range(8)]  # self_obj<k>_active
SETUP_WINDOW = 30
WAKE_WINDOW = 8       # steps after a knockdown's end in which a reversal is a wake-up one
RG_WINDOW = 20        # ... after a recoil guard
REVERSAL_WINDOW = 40  # steps in which a reversal must hit
FOCUSES = ('setup', 'charge', 'reversal', 'air', 'out', 'press', 'corner')
AIR_SELF, AIR_OPP = 39, 71  # self_airborne, opp_airborne
DX, X_SELF, X_OPP, GUARDING_SELF = 4, 13, 45, 21
OUT_WINDOW = 40       # steps after its air recovery begins in which it must not be caught
RECOVERY = (0x9d, 0x9e)
PRESS_WINDOW = 60     # steps after the opponent's guard in which a hit is the pressure's
PRESS_CONTACT = 0.2   # a guard touched, as a share of coef
CORNER_TIMES = 2.0    # corner: press's events, and a jump out caught, this many times coef in a corner
PLAIN_GUARDS = [g for g in tactics.GUARDS if g not in tactics.RG]
CORNER_IN, CORNER_OUT, CORNER_NEAR, CORNER_LEAST = 0.80, 0.68, 220, 20  # evaluate.corner()'s


def reversal_moves(char):
    """A character's invincible attacks (framedata.json), throws left out (level 0)."""
    import json
    import os
    path = os.path.join(tactics.HERE, 'framedata.json')
    data = json.load(open(path)).get(char, {}) if os.path.exists(path) else {}
    return {int(k, 16) for k, m in data.items()
            if m['invincible'] and m['startup'] is not None and m['level'] >= 10
            and int(k, 16) < tactics.FIRST_OBJECT}


class Focus(VecEnvWrapper):
    def __init__(self, venv, focus, coef=0.02, char=None):
        if focus not in FOCUSES:
            raise ValueError(f'focus: one of {FOCUSES}')
        super().__init__(venv)
        self.focus, self.coef = focus, coef
        self.charge = set(tactics.CHARGE.get(char, []))
        if focus == 'charge' and not self.charge:
            raise ValueError(f"{char} has no charge moves (tactics.CHARGE)")
        self.reversals = reversal_moves(char) if focus == 'reversal' else set()
        if focus == 'reversal' and not self.reversals:
            raise ValueError(f'{char} has no invincible attacks (framedata.json)')
        n = venv.num_envs
        self.prev = None
        self.pending = np.full(n, -1)          # steps left for a setup's object to appear
        self.pending_objects = np.zeros(n, int)
        self.since_down = np.full(n, 999)      # steps since it rose from a knockdown
        self.since_rg = np.full(n, 999)        # ... since a recoil guard
        self.held = np.zeros(n, int)           # steps it has been held in a corner
        self.pressed = np.zeros(n, bool)       # ... and guarded or was hit there
        self.since_guard = np.full(n, 999)     # ... since the opponent's guard was touched
        self.kinds = self._kinds()
        self.counts = dict(events=0, steps=0)

    def _kinds(self):
        if self.focus == 'corner':
            return dict(contacts=0, opened=0, caught=0, cornered=0)
        return dict(contacts=0, opened=0) if self.focus == 'press' else dict(recoveries=0, corners=0)

    def _raw(self):
        return self.venv.env.obs[:, 0]  # EfzSB3VecEnv's game: player 1's current view

    def reset(self):
        obs = self.venv.reset()
        self.prev = self._raw().copy()
        self.pending[:] = -1
        self.since_down[:] = 999
        self.since_rg[:] = 999
        self.since_guard[:] = 999
        self.held[:] = 0
        self.pressed[:] = False
        return obs

    def take(self):
        c = dict(self.counts)
        if self.focus in ('out', 'press', 'corner'):
            c.update(self.kinds)
            self.kinds = self._kinds()
        self.counts = dict(events=0, steps=0)
        return c

    def step_wait(self):
        obs, reward, done, infos = self.venv.step_wait()
        raw = self._raw()
        now = np.where(done[:, None], self.venv.env.final_obs[:, 0], raw)  # before a reset
        prev = self.prev
        a0, o0 = np.round(prev[:, ACT_SELF]).astype(int), np.round(prev[:, ACT_OPP]).astype(int)
        a = np.round(now[:, ACT_SELF]).astype(int)
        free = np.isin(a0, tactics.FREE) & ~np.isin(o0, tactics.FREE)
        started = (a != a0) & (a >= tactics.FIRST_OWN) & free
        bonus = np.zeros(len(a))
        if self.focus == 'setup':
            objects_before = (prev[:, OBJECTS] > 0).sum(1)
            objects = (now[:, OBJECTS] > 0).sum(1)
            new = started & (self.pending < 0)
            self.pending[new] = SETUP_WINDOW
            self.pending_objects[new] = objects_before[new]
            live = self.pending > 0
            hit = live & (objects > self.pending_objects)
            bonus[hit] = self.coef
            self.pending[hit] = -1
            self.pending[live & ~hit] -= 1
            self.pending[self.pending == 0] = -1
        elif self.focus == 'charge':
            bonus[started & np.isin(a, list(self.charge))] = self.coef
        elif self.focus == 'air':
            hit_opp = (now[:, HITSTUN_OPP] > 0) & ~(prev[:, HITSTUN_OPP] > 0)
            bonus[hit_opp & (now[:, AIR_SELF] > 0) & ~(prev[:, AIR_OPP] > 0)] = self.coef
        elif self.focus in ('press', 'corner'):
            o = np.round(now[:, ACT_OPP]).astype(int)
            guard, guard0 = np.isin(o, PLAIN_GUARDS), np.isin(o0, PLAIN_GUARDS)
            contact = guard & (~guard0 | (o != o0) | (now[:, FRAME_OPP] < prev[:, FRAME_OPP])) & ~done
            # (its hit reaction, or a throw's pose: the stun column is up in a guard too)
            react = ((o >= 0x32) & (o < 0x60)) | np.isin(o, tactics.THROWN)
            react0 = ((o0 >= 0x32) & (o0 < 0x60)) | np.isin(o0, tactics.THROWN)
            opened = react & ~react0 & (self.since_guard <= PRESS_WINDOW) & ~done
            times = np.ones(len(a))
            if self.focus == 'corner':  # the opponent held in a corner: the events count for more
                mx, ox = np.abs(now[:, X_SELF]), np.abs(now[:, X_OPP])
                inside = (mx < ox) & (np.abs(now[:, DX]) * 640 <= CORNER_NEAR)
                hold = (ox > CORNER_OUT) & inside
                before = self.held.copy()
                self.held = np.where(hold & ((ox > CORNER_IN) | (before > 0)) & ~done, before + 1, 0)
                times[before > 0] = CORNER_TIMES
                caught = (before > 0) & react & ~react0 & (prev[:, AIR_OPP] > 0) & ~done
                bonus[caught] += self.coef * CORNER_TIMES
                self.kinds['caught'] += int(caught.sum())
                self.kinds['cornered'] += int((self.held > 0).sum())
                opened &= ~caught  # (one event)
            bonus[contact] += self.coef * PRESS_CONTACT * times[contact]
            bonus[opened] += self.coef * times[opened]
            self.kinds['contacts'] += int(contact.sum())
            self.kinds['opened'] += int(opened.sum())
            self.since_guard = np.where(contact, 0, np.minimum(self.since_guard + 1, 999))
            self.since_guard[opened | done] = 999
        elif self.focus == 'out':
            react = ((a >= 0x32) & (a < 0x60)) | np.isin(a, tactics.THROWN)
            react0 = (a0 >= 0x32) & (a0 < 0x60)
            # A recovery that got away.
            new = np.isin(a, RECOVERY) & react0
            live = (self.pending > 0) & ~new
            caught = live & react
            away = live & ~caught & (self.pending == 1)
            bonus[away] += self.coef
            self.kinds['recoveries'] += int(away.sum())
            self.pending[live] -= 1
            self.pending[caught | (self.pending == 0)] = -1
            self.pending[new] = OUT_WINDOW
            # A corner left.
            mx, ox = np.abs(now[:, X_SELF]), np.abs(now[:, X_OPP])
            inside = (ox < mx) & (np.abs(now[:, DX]) * 640 <= CORNER_NEAR)
            hold = (mx > CORNER_OUT) & inside
            before = self.held.copy()
            self.held = np.where(hold & ((mx > CORNER_IN) | (before > 0)), before + 1, 0)
            self.pressed |= hold & ((now[:, GUARDING_SELF] > 0) | (now[:, HITSTUN_SELF] > 0))
            left = ((before >= CORNER_LEAST) & self.pressed & ~hold & ~react &
                    ~np.isin(a, tactics.DOWN) & ~done)
            bonus[left] += self.coef
            self.kinds['corners'] += int(left.sum())
            self.pressed[~hold] = False
            self.held[done] = 0
            self.pressed[done] = False
        else:
            rose = np.isin(a0, tactics.DOWN) & ~np.isin(a, tactics.DOWN)
            self.since_down = np.where(rose, 0, np.minimum(self.since_down + 1, 999))
            self.since_rg = np.where(np.isin(a, tactics.RG), 0, np.minimum(self.since_rg + 1, 999))
            new = (a != a0) & np.isin(a, list(self.reversals)) & (self.pending < 0) & (
                (self.since_down <= WAKE_WINDOW) | (self.since_rg <= RG_WINDOW))
            self.pending[new] = REVERSAL_WINDOW
            live = self.pending > 0
            hit_opp = (now[:, HITSTUN_OPP] > 0) & ~(prev[:, HITSTUN_OPP] > 0)
            hit_me = (now[:, HITSTUN_SELF] > 0) & ~(prev[:, HITSTUN_SELF] > 0)
            landed = live & hit_opp & ~hit_me
            bonus[landed] = self.coef
            self.pending[landed | (live & hit_me)] = -1
            self.pending[live & ~landed & ~hit_me] -= 1
            self.pending[self.pending == 0] = -1
            self.since_down[done] = 999
            self.since_rg[done] = 999
        self.pending[done] = -1
        self.prev = raw.copy()
        self.counts['events'] += int((bonus > 0).sum())
        self.counts['steps'] += len(a)
        return obs, reward + bonus.astype(reward.dtype), done, infos


class Calm(VecEnvWrapper):
    """A cost on the learner's presses while it is hit or guarding (finetune.py
    --press-cost): each button pressed on a step that began with it in a hit reaction or
    a guard takes `cost` off the step's reward (0.002: 20 HP's worth). A human limit kept
    by the reward: people's Ayu players press 1.0 times a second there (0.6-2.2 by
    player; evaluate.py's presses_where), round 15's agent 2.8-3.8, and a press there
    does nothing but the one that is buffered for the first step it can act, which is
    worth far more than its cost."""

    def __init__(self, venv, cost):
        super().__init__(venv)
        self.cost, self.prev = cost, None

    def _raw(self):
        return self.venv.env.obs[:, 0]

    def reset(self):
        obs = self.venv.reset()
        self.prev = self._raw().copy()
        return obs

    def step_wait(self):
        obs, reward, done, infos = self.venv.step_wait()
        prev = self.prev
        defending = (prev[:, HITSTUN_SELF] > 0) | np.isin(np.round(prev[:, ACT_SELF]).astype(int),
                                                          tactics.GUARDS)
        # (the step's input, newest in the history; a match that ended: cleared, none)
        pressed = self.venv.history.buf[:, 0, 0, 2:].sum(-1)
        self.prev = self._raw().copy()
        return obs, reward - (self.cost * pressed * defending).astype(reward.dtype), done, infos

