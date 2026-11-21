"""The module 'risk' (python/efz_env/modules.py; evaluate.py --p1-module, play.py
--module): a raw special of the agent's own play, let out or stopped at its input by how
that move has paid in this match.

    risk[:prior=4,temperature=75,window=180,carry=false,623B=-326,...]

Why (the user's, 17 and 18 November: "risk management", "When doing something, it seems
it's not calculating what'd be the outcome if that doesn't work"; docs/training-v2.md,
"The raw moves: the whole of the deficit"). Against the user round 18's agent lost about
1,450 HP a minute on five raw moves, which is all it was behind by: 623B (0.64 a minute,
644 lost each), the level-one 236236 super (1.13, 367), 236B thrown in the open (0.78,
402), 623C and 623A on rising. The strongest Ayu player of the community's replays uses
the same moves, the losing ones four to seven times less often (236B 0.14 a minute, 623B
0.17, that super 0.16), and all their raw specials together are worth +150 HP a minute.
The league pays for some of them and a person does not; nothing in the policy counts
what a move did earlier in the match.

What it does. It sits last among the modules: a step no planner took is its own play's,
which this module draws. When that action presses a button, and the agent does not see
its opponent in a hit reaction (a combo it has seen is not a risk), the press is tried on
a copy of the game as it is, the opponent pressing nothing: the press, then `look`
frames of nothing (the game keeps a press made during a move and plays it when the move
lets it: one frame shows the specials started from standing, not the buffered ones), or
`look_down` frames when the agent is down (a reversal's button is read while it rises):
what the agent knows of its own hands, not of the opponent. If the copy has it starting
(an action it was not in when it pressed) one of the moves
with an account (tactics.RISKY's and the supers), that move's account decides: its worth
is the mean HP swing (the opponent's HP lost less its own over `window` steps after the
press, as the agent sees it) of the times it let the move out in this match, over a prior
(the strongest player's HP a raw use, counting as `prior` uses); with the probability
1 / (1 + exp(worth / temperature)) the button is left out of the action (the same
direction, nothing pressed), once drawn for as long as the same press is being tried
(AGAIN steps).

At the priors (since 20 November the agent's own worths against opponents with combos,
below): 236B, 236A, 623C and the level-one super are stopped nearly every time, 623B 99
times in 100, 623A 92, 236236B 81, 236C one time in three, 641236A one in four, 641236B
almost never. A move that has been hitting in this match comes back, one that has been
punished goes: 236C after one that cost a combo (1,300 HP) is stopped 96 times in 100.
(With the strongest player's worths, until then: 236C was stopped 1 time in 100, half the
time after one that cost a combo, 94 in 100 after two.)

The jump at the opponent (`jump`: its starting worth in HP; none: no account). The user's
games of 20 November: "When it can't get advantage during air-to-air, it doesn't adjust
the strategy ... no in-game adjustment." A forward jump within 400 pixels was worth, over
the two seconds after it, +131 to +552 HP in each of the seven matches the agent won and
-239 to +12 in the four it lost, 19 to 35 of them a match, and against Kano it jumped
twice as often (78, at -115 each). So the jump has an account as a raw special has: its
own play's action up and forward, itself free on the ground, the opponent within
`jump_near` pixels and not in a hit reaction it has seen; the HP swing over `jump_window`
steps after one let out (as it sees it); its worth the mean over a prior (`jump`, counting
as `jump_prior` jumps); stopped with the probability 1 / (1 + exp(worth /
`jump_temperature`)), the action then the same without up (it walks or dashes in, and
what it does from the ground is its own play's and the planners'). A match in which the
air pays jumps as before; one in which it does not is played from the ground.

The first build looked one frame ahead and missed most of them: against Kano's
`exploiter18` it stopped 31 of 31 presses that would start 623B at once and the match's
record still had 21 raw 623B, buffered ones and wake-up ones.

options: look (10), look_down (50), prior (4), temperature (75), window (180), carry (false; true: the accounts
kept into the next match, scaled by `decay`, 0.7), seed, and a move's name for its prior
(236A, 236B, 236C, 623A, 623B, 623C, 641236A/B/C, 236236A/B/C: the level, not the button).
"""

import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env import EfzVecEnv, modules
from efz_env.actions import ActionTable

TABLE = ActionTable()
INDEX = {a: k for k, a in enumerate(TABLE.actions)}
ROUND_OVER = 3
SELF_HP, OPP_HP, SELF_ACT, OPP_ACT, OPP_HITSTUN = 8, 40, 18, 50, 52
DOWN = frozenset((0x60, 0x61, 0x62, 0x63))  # rising, the two knockdowns, lying
HP = 9999.0
GUARDS = frozenset(list(range(0x96, 0x9d)) + [0xa8, 0xa9, 0xaa])  # tactics.GUARDS
FREE = frozenset((0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xe, 0xf, 0x10))  # free to do anything (tactics.FREE)
SELF_AIR, DX, PIXELS = 39, 4, 640.0
# Ayu's moves with an account, and what a raw use of each starts at. Until 20 November
# the strongest Ayu player's HP a use (community replays, 487 matches: 236C +333, 623C
# +580, 236A -130, 236B -131, 641236A +195, 641236B +290, 236236A -232, 236236B +90). Now,
# for the moves used 50 times or more there, the agent's own HP a use against the league's
# opponents with their characters' combos (bench.py's `combos` drill, round 20's file, 704
# matches): a miss costs a combo there as it does against a person, which the league as
# it was (and the player's opponents, to that player) did not charge. The user's games of
# 20 November: the raw 236C 32 times, guarded 38%, -251 HP a use, its account starting at
# +333 and three uses a match too few to turn it.
MOVES = {'236A': 0x104, '236B': 0x105, '236C': 0x106, '623A': 0xfa, '623B': 0xfc, '623C': 0xfb,
         '641236A': 0x132, '641236B': 0x133, '641236C': 0x134,
         '236236A': 0x13b, '236236B': 0x13c, '236236C': 0x13d}
PRIORS = {'236A': -650, '236B': -1010, '236C': 50, '623A': -180, '623B': -326, '623C': -460,
          '641236A': 80, '641236B': 670, '641236C': 987,
          '236236A': -1500, '236236B': -110, '236236C': 1216}
AGAIN = 12   # steps in which the same move tried again is the same press
CAME = 24    # steps after the agent could see the move in which it must (else: not followed)


class Risk(modules.Module):
    """stats(): per move, seen (presses that would start it, drawn for), stopped, let
    (let out), came (of those, the move seen), and the account: n, swing (their mean)."""
    name = 'risk'

    def __init__(self, data_dir, width, delay, priors=None, prior=4.0, temperature=75.0,
                 window=180, carry=False, decay=0.7, seed=0, sim=None, look=10, look_down=50,
                 jump=None, jump_prior=6.0, jump_temperature=100.0, jump_window=130,
                 jump_near=400.0):
        self.width, self.delay = width, int(delay)
        self.priors = dict(PRIORS, **(priors or {}))
        self.names = {MOVES[k]: k for k in self.priors}
        self.prior, self.temperature, self.window = float(prior), float(temperature), int(window)
        self.carry, self.decay = bool(carry), float(decay)
        self.look, self.look_down = max(1, int(look)), max(1, int(look_down))
        self.rng = np.random.default_rng(seed)
        # the jump at the opponent: its account's starting worth (None: no account)
        self.jump = None if jump is None else float(jump)
        self.jump_prior, self.jump_temperature = float(jump_prior), float(jump_temperature)
        self.jump_window, self.jump_near = int(float(jump_window)), float(jump_near)
        self.jumps = dict(seen=0, stopped=0, let=0, came=0)
        self.jumps_all = [0, 0.0]
        # (a frame a step; a copy is played one frame)
        self.sim = sim if sim is not None else EfzVecEnv(
            data_dir, 1, frame_skip=1, rounds_to_win=2, max_frames=0, autoreset='disabled',
            skip_noninteractive=False)
        if sim is None:
            self.sim.reset()
        self.n_ = {k: dict(seen=0, stopped=0, let=0, came=0) for k in self.priors}
        self.all = {k: [0, 0.0] for k in self.priors}  # every match's: uses, swing's sum
        self.batch(0)

    def batch(self, n):
        self.n = n
        self.count = [dict.fromkeys(self.priors, 0.0) for _ in range(n)]
        self.total = [dict.fromkeys(self.priors, 0.0) for _ in range(n)]
        self.t = np.zeros(n, int)
        self.drawn = [None] * n   # the press being tried: (move, step, stopped)
        self.open = [None] * n    # the use being followed: [move, age, own HP, its HP, came]
        self.jcount, self.jtotal = np.zeros(n), np.zeros(n)  # the jump's account
        self.jdrawn = [None] * n  # the jump being tried: (step, stopped)
        self.jopen = [None] * n   # the jump being followed: [age, own HP, its HP, came]

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        scale = self.decay if self.carry else 0.0
        for i in np.flatnonzero(mask):
            self.open[i] = self.drawn[i] = None
            self.jopen[i] = self.jdrawn[i] = None
            self.jcount[i] *= scale
            self.jtotal[i] *= scale
            for k in self.priors:
                self.count[i][k] *= scale
                self.total[i][k] *= scale

    def worth(self, i, move):
        return ((self.prior * self.priors[move] + self.total[i][move]) /
                (self.prior + self.count[i][move]))

    def chance(self, i, move):
        """The probability that a press that would start `move` is stopped."""
        return 1.0 / (1.0 + np.exp(np.clip(self.worth(i, move) / self.temperature, -50, 50)))

    def jump_worth(self, i):
        return (self.jump_prior * self.jump + self.jtotal[i]) / (self.jump_prior + self.jcount[i])

    def jump_chance(self, i):
        """The probability that a jump at the opponent is stopped."""
        return float(1.0 / (1.0 + np.exp(np.clip(self.jump_worth(i) / self.jump_temperature, -50, 50))))

    def jump_settle(self, i, view):
        """The followed jump's swing into the jump's account (if it saw itself in the air)."""
        rec, self.jopen[i] = self.jopen[i], None
        if rec is None or view is None or not rec[3]:
            return
        mine = max(0.0, rec[1] - float(view[SELF_HP]) * HP)
        theirs = max(0.0, rec[2] - float(view[OPP_HP]) * HP)
        self.jcount[i] += 1
        self.jtotal[i] += theirs - mine
        self.jumps_all[0] += 1
        self.jumps_all[1] += theirs - mine

    def settle(self, i, view):
        """The followed use's swing into its move's account (if the move was seen)."""
        rec, self.open[i] = self.open[i], None
        if rec is None or view is None or not rec[4]:
            return
        mine = max(0.0, rec[2] - float(view[SELF_HP]) * HP)
        theirs = max(0.0, rec[3] - float(view[OPP_HP]) * HP)
        self.count[i][rec[0]] += 1
        self.total[i][rec[0]] += theirs - mine
        self.all[rec[0]][0] += 1
        self.all[rec[0]][1] += theirs - mine

    def watch(self, i, ctx):
        self.t[i] += 1
        v = ctx.view
        jump = self.jopen[i]
        if jump is not None:
            jump[0] += 1
            if not jump[3] and v[SELF_AIR] > 0:
                jump[3] = True
                self.jumps['came'] += 1
            if not jump[3] and jump[0] > self.delay + CAME:
                self.jopen[i] = None  # (the press started no jump it saw)
            elif v[ROUND_OVER] != 0 or jump[0] >= self.jump_window:
                self.jump_settle(i, v)
        rec = self.open[i]
        if rec is None:
            return
        rec[1] += 1
        if not rec[4] and int(round(float(v[SELF_ACT]))) == MOVES[rec[0]]:
            rec[4] = True
            self.n_[rec[0]]['came'] += 1
        if not rec[4] and rec[1] > self.delay + CAME:
            self.open[i] = None  # (the press started nothing it saw)
        elif v[ROUND_OVER] != 0 or rec[1] >= self.window:
            self.settle(i, v)

    def starts(self, ctx, action):
        """The move with an account that `action` starts on a copy of the game as it is
        (the press, then nothing: an action the agent was not in already), or None."""
        state = ctx.save()
        if state is None:
            return None
        sim = self.sim
        sim.load_state(0, state)
        was = int(round(float(ctx.now[SELF_ACT]))) if ctx.now is not None else -1
        controls = np.zeros((1, 2), np.uint8)
        controls[0, ctx.side] = TABLE.table[action]
        for _ in range(self.look_down if was in DOWN else self.look):
            obs = sim.step(controls)[0]
            controls[0, ctx.side] = 0
            a = int(round(float(obs[0, ctx.side, SELF_ACT])))
            if a != was and a in self.names:
                return self.names[a]
        return None

    def act(self, i, ctx):
        if ctx.policy is None or ctx.hist is None or ctx.save is None:
            return None
        v = ctx.view
        x = np.concatenate([np.asarray(v, np.float32).reshape(-1),
                            np.asarray(ctx.hist, np.float32).reshape(-1)])
        own = int(np.asarray(ctx.policy(x[None, :self.width or len(x)])).reshape(-1)[0])
        direction, buttons = TABLE.actions[own]
        if self.jump is not None and direction == 9 and v[ROUND_OVER] == 0:
            own = self.jumping(i, ctx, own)
            direction, buttons = TABLE.actions[own]
        if not buttons or v[ROUND_OVER] != 0:
            return own
        if v[OPP_HITSTUN] > 0 and int(round(float(v[OPP_ACT]))) not in GUARDS:
            return own  # (a combo it has seen)
        move = self.starts(ctx, own)
        if move is None:
            return own
        was = self.drawn[i]
        again = was is not None and was[0] == move and self.t[i] - was[1] <= AGAIN
        if again:
            stop = was[2]
        else:
            stop = bool(self.rng.random() < self.chance(i, move))
            self.n_[move]['seen'] += 1
            self.n_[move]['stopped' if stop else 'let'] += 1
        self.drawn[i] = (move, int(self.t[i]), stop)
        if stop:
            return INDEX[(direction, '')]
        if not again:  # followed from its first press (a use still followed ends here)
            self.settle(i, v)
            self.open[i] = [move, 0, float(v[SELF_HP]) * HP, float(v[OPP_HP]) * HP, False]
        return own

    def jumping(self, i, ctx, own):
        """Its own play's jump at the opponent (up and forward): the action, or stopped by
        the jump's account the same without up."""
        v = ctx.view
        now = ctx.now if ctx.now is not None else v
        if (now[SELF_AIR] > 0 or int(round(float(now[SELF_ACT]))) not in FREE
                or abs(float(v[DX])) * PIXELS > self.jump_near
                or (v[OPP_HITSTUN] > 0 and int(round(float(v[OPP_ACT]))) not in GUARDS)):
            return own
        was = self.jdrawn[i]
        again = was is not None and self.t[i] - was[0] <= AGAIN
        if again:
            stop = was[1]
        else:
            stop = bool(self.rng.random() < self.jump_chance(i))
            self.jumps['seen'] += 1
            self.jumps['stopped' if stop else 'let'] += 1
        self.jdrawn[i] = (int(self.t[i]), stop)
        if stop:
            return INDEX[(6, TABLE.actions[own][1])]
        if not again:
            self.jump_settle(i, v)
            self.jopen[i] = [0, float(v[SELF_HP]) * HP, float(v[OPP_HP]) * HP, False]
        return own

    def stats(self):
        out = {}
        for k in self.priors:
            n, total = self.all[k]
            if self.n_[k]['seen'] or n:
                out[k] = dict(self.n_[k], n=int(n), swing=round(total / n) if n else None)
        if self.jump is not None:
            n, total = self.jumps_all
            out['jump'] = dict(self.jumps, n=int(n), swing=round(total / n) if n else None)
        return out

    def close(self):
        self.sim.close()


@modules.register('risk')
def risk(agent, where, files, options, data):
    """options: the file's head."""
    o = dict(options)
    if where != 'batch':
        raise ValueError('risk: with copies of the game (evaluate.py, play.py)')
    priors = {k: float(o.pop(k)) for k in list(o) if k in MOVES}
    keys = ('prior', 'temperature', 'window', 'carry', 'decay', 'seed', 'look', 'look_down',
            'jump', 'jump_prior', 'jump_temperature', 'jump_window', 'jump_near')
    unknown = sorted(set(o) - set(keys))
    if unknown:
        raise ValueError(f"risk: no option {', '.join(unknown)}")
    return Risk(data, agent.model.observation_space.shape[0], agent.delay, priors=priors,
                **{k: o[k] for k in keys if k in o})
