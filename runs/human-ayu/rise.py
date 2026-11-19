"""The module 'rise' (python/efz_env/modules.py; evaluate.py --p1-module, play.py
--module): the agent's own wake-up, a move or a guard, by how each went in this match.

    rise[:prior=4,move=150,still=-165,super=-400,temperature=75,window=240,carry=false]

Why (the user's, 17 November: "risk management ... It should pay more attention when the
other side hit back"; docs/training-v2.md, "The league by the three measures"). Against
the user most of the agent's raw risky moves were wake-up reversals (23 of its 27 raw
236236A, 12 of 15 raw 641236A, 10 of 15 raw 623B), four in five whiffed or were guarded
and three in four of those were punished: about 1,100 HP a match. The league teaches the
habit: its opponents attack the agent's rising, and a reversal that is waited out is
rare there (the `crowd` profile guards 8% of them). People's own wake-up reversal pays
(Ayu players in the community's replays: 10% of their wake-ups, 527 HP ahead for it; a
guard, 56%, 168 behind) because it is used one rising in ten; the agent's, at one in
four and at every knockdown of a match alike, is read by anyone who looks. Training
does not make the policy use what it saw earlier in a match (the told-habits
experiment), so a module does: a person who is punished for the same wake-up move twice
stops, and starts again when the guard is what gets opened.

What it does. It keeps two accounts for the match, from what the agent sees: the HP
swing (the opponent's HP lost less its own, over `window` steps after it sees itself up,
or until it sees itself down again or the round ends) of the wake-ups it rose with a
move on (a move of its own seen within REVERSAL steps of rising), and of the others.
Each account's worth is its mean over a prior (`move`, `still` HP; `prior` wake-ups'
weight: people's and the league's numbers). When it sees itself knocked down it draws:
with the probability 1 / (1 + exp((worth of a move - worth of the others) /
temperature)) this rising is guarded through. A rising guarded through: while it sees
itself down, the policy's own action if that is a guard or a jump back (a back direction,
no button), else a guard, standing if it sees the opponent in the air and crouching
otherwise. The agent sees `delay` steps late, so this covers the first `delay` steps
after it is up, which is where a wake-up move would come out; then its own play again.

With the priors as they are nothing changes until something was punished: 1.5% of the
risings are guarded through at a match's start, 42% after one wake-up move that cost a
combo (1,300 HP), 90% after two; a guard that is opened as often brings the move back.

The one move. The class is not the leak: in the league a wake-up move pays as a class
(the module's own accounts against Ikumi's `exploiter18`: +174 a rising with a move, -77
without) and one move in it does not: the level-one super 236236A, 88 raw uses in 64
matches there, nine in ten of them wake-up ones, at -960 HP each; -166 to -494 against
the others measured, -625 against the user; people's wake-up supers are 641236A. So it
has an account of its own (`super`, the prior -400), and the module sees it coming: its
own play's inputs while it sees itself down are the module's to draw and play, and when
they hold two down-to-forward sweeps within RECENT steps and then press a button that
makes the level-one super (A, or any with one bar: the agent's is 236236C), this rising
is guarded through with the probability the super's account gives against the others'
(96% at a match's start; a super that hit brings it down).

Measured (Ikumi's `exploiter18`, 64 matches): with both the class's draw and the
super's, 93 of 103 supers seen coming were stopped (raw wake-up ones 79 to 13) and the
wins did not move (65.6% for 68.8%): the class's draw guarded another fifth of the
risings through and took the wake-up moves that pay (641236A halved) with it. So the
class's draw is off unless asked for (`moves=true`); the super's is what the module does.

The guard by sight (`guard=true`). The league's opponents leave the agent's rising
alone and a person does not (docs/training-v2.md, "The agent's own rising against an
attacker who is on it"): a move of the attacker's is out as the agent rises on 16-36% of
its knockdowns against eight of the eleven `exploiter18`s, 75% against the user, 56-58%
in the community's replays. Against the user's it lost 427 HP a knockdown (-65 where the
user was not on it): a move of its own into the meaty (a fifth of them, 697 lost each),
and a guard that is not one (of the 26 air attacks that hit it rising, 25 were in its
view, 14 steps late as it is, and it held a standing guard under 7). The strongest Ayu
player of the replays guards 53% of their risings and loses 13 HP a knockdown.
So, with `guard`: a rising on which it sees the attacker on it (while it sees itself
down: the attacker in a move of its own, or in the air within `fly` pixels; or merely
within `near`, which is off: measured with 130, an opponent that stands close to throw,
Ikumi's `exploiter18`, had every rising guarded and the wins went from 89% to 80%
through the game's code) is guarded through with a probability read from the match: the share of the risings it
has seen in it at which the attacker was in a move of its own as the agent saw itself up
(the measure above; what the agent did has no part in it), over a prior (`meaty`, 0.56,
the community's, counting as `met_prior` risings, 2); none are guarded at the rate `low`
(0.3), all at `high` (0.6), in a line between: 87% at a match's start, none after two
risings left alone, all against an attacker who is there each time. Two builds before
this one kept accounts of HP instead (such risings guarded through, against those left to
its own play): eleven risings a match at a thousand HP either way say nothing in time,
and "the attacker on it" is seen at nine knockdowns in ten (the move that knocked it down
is one), so the guard went on at two risings in three against everyone: level over the
eleven `exploiter18`s, and 10 points of its HP more lost against the three that leave its
rising alone (Ikumi's, which comes to throw: 51% to 61%). The guard is held by sight: standing while it sees the
attacker in the air, else its own play's guard, else crouching; no button and no jump.
`hold` (steps, 0: off): a rising guarded through goes on guarding by sight after it sees
itself up, for at most that many steps, while the attacker goes on (in a move of its own
or in the air within `fly`), until it has seen `gap` steps (8) without that, itself hit,
or the round over: against the user 97% of the hits it took 41-96 steps after a rising
came with a button of its own pressed in the 14 steps before.

`plain` (false): the guard alone. The module then never draws its own play's action (no
super seen coming, no class's draw): a rising it does not guard through is the next
module's or its own play's, as the game's rise:1 is; with the module risk after it the
super's account is that module's.

options: moves (false), guard (false), plain (false), prior (4), move (150), still (-165), super (-400),
meaty (0.56), low (0.3), high (0.6), met_prior (2), near (0), fly (200), hold (0), gap (8),
temperature (75),
window (240),
carry (false: a new match is another opponent; true: the same, the accounts kept and
scaled by `decay`, 0.7), seed.
"""

import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env import modules
from efz_env.actions import ActionTable

TABLE = ActionTable()
INDEX = {a: k for k, a in enumerate(TABLE.actions)}
ROUND_OVER = 3
SELF_HP, OPP_HP, SELF_ACT, OPP_ACT, OPP_AIR, DX, SELF_HITSTUN = 8, 40, 18, 50, 71, 4, 20
PIXELS = 640.0                              # dx's scale
DOWN = frozenset((0x60, 0x61, 0x62, 0x63))  # rising, the two knockdowns, lying
FIRST_OWN = 0xc8                            # the character's own moves from here
REVERSAL = 10                               # steps after rising in which a move is a wake-up one
HP = 9999.0
CROUCH_GUARD, STAND_GUARD = INDEX[(1, '')], INDEX[(4, '')]
BACK = (1, 4, 7)                            # a guard's directions, and the jump back
MOVE, STILL, SUPER = 0, 1, 2
ACCOUNTS = ('move', 'still', 'super')
SUPER_MOVE = 0x13b   # Ayu's 236236 super at level one (236236A, or B or C with one bar)
SUPER_LEVEL = dict(A=1, B=2, C=3)  # the level a button asks for; the bars cap it
SELF_GAUGE = 9       # self_gauge: the power gauge, 1.0 three bars
RECENT = 24          # steps in which its own inputs make a motion


def sweeps(dirs):
    """How many times the directions go from down to forward (2 ... 6): two is 236236's
    motion and nothing else's (641236 has one, 623 none)."""
    n, want = 0, 2
    for d in dirs:
        if d == want:
            n, want = (n, 6) if want == 2 else (n + 1, 2)
    return n


class Rise(modules.Module):
    """stats(): knockdowns (it saw), guarded (the risings it guarded through by the
    accounts), supers (the wake-up 236236A it saw coming in its own inputs), stopped (of
    those, guarded instead), kept (of the guarded steps, the policy's own guard), and per
    account its wake-ups and mean swing."""
    name = 'rise'

    def __init__(self, prior=4.0, move=150.0, still=-165.0, super=-400.0, temperature=75.0,
                 window=240, carry=False, decay=0.7, seed=0, width=None, moves=False,
                 guard=False, meaty=0.56, low=0.3, high=0.6, met_prior=2.0, near=0.0,
                 fly=200.0, hold=0, gap=8, plain=False):
        # moves: also guard a rising through by the class account (any wake-up move's);
        # measured without a gain, and it takes the wake-up moves that pay with it
        self.moves = moves in (True, 1, 'true', 'True', '1')
        # guard: a rising the attacker is seen on is guarded through, by sight
        self.guard = guard in (True, 1, 'true', 'True', '1')
        self.near, self.fly = float(near), float(fly)
        self.hold, self.gap = int(hold), int(gap)
        self.plain = plain in (True, 1, 'true', 'True', '1')
        self.prior = float(prior)
        self.priors = (float(move), float(still), float(super))
        # the guard's read: how often an attacker is in a move as the agent rises (the
        # prior, counting as met_prior risings), and the rates between which the guard
        # goes from never to always
        self.meaty, self.met_prior = float(meaty), float(met_prior)
        self.low, self.high = float(low), max(float(high), float(low) + 1e-6)
        self.temperature, self.window = float(temperature), int(window)
        self.carry, self.decay, self.width = bool(carry), float(decay), width
        self.rng = np.random.default_rng(seed)
        self.n_ = dict(knockdowns=0, guarded=0, supers=0, stopped=0, steps=0, kept=0, met=0,
                       met_guarded=0, stood=0, held=0, risings=0, attacked=0)
        self.all = np.zeros((len(ACCOUNTS), 2))  # every match's: [account] -> (wake-ups, swing's sum)
        self.batch(0)

    def batch(self, n):
        self.n = n
        self.count = np.zeros((n, len(ACCOUNTS)))  # this match's (or set's) wake-ups by account
        self.total = np.zeros((n, len(ACCOUNTS)))  # ... and their swings' sum
        self.seen = np.zeros(n)         # this match's risings it saw
        self.on = np.zeros(n)           # ... and of them, the attacker in a move as it rose
        self.met = np.zeros(n, bool)    # this rising: the attacker was seen on it
        self.drawn = np.zeros(n, bool)  # ... and its guard was drawn for
        self.holding = np.zeros(n, int)  # steps its guard may go on for, now that it is up
        self.quiet = np.zeros(n, int)    # ... and the steps the attacker has not gone on
        self.was_down = np.zeros(n, bool)
        self.veto = np.zeros(n, bool)   # this rising is guarded through
        self.asked = np.zeros(n, bool)  # this rising's super was drawn for already
        self.dirs = [[] for _ in range(n)]  # its inputs' directions since the knockdown: (step, direction)
        self.step = np.zeros(n, int)
        # the wake-up being followed: [age, moved, own HP, its HP, the move it rose with]
        self.open = [None] * n

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        for i in np.flatnonzero(mask):
            self.close(int(i), None)
            self.dirs[int(i)] = []
        scale = self.decay if self.carry else 0.0
        self.count[mask] *= scale
        self.total[mask] *= scale
        self.seen[mask] *= scale
        self.on[mask] *= scale
        self.was_down[mask] = self.veto[mask] = self.asked[mask] = False
        self.met[mask] = self.drawn[mask] = False
        self.holding[mask] = self.quiet[mask] = 0

    def worth(self, i):
        """(a wake-up move's, the others', the wake-up 236236A's) expected swing for
        environment i."""
        return tuple((self.prior * self.priors[k] + self.total[i, k]) /
                     (self.prior + self.count[i, k]) for k in range(len(ACCOUNTS)))

    def chance(self, i, account=MOVE):
        """The probability that a rising with a move of `account` is guarded through
        (against the risings without a move)."""
        worth = self.worth(i)
        return 1.0 / (1.0 + np.exp(np.clip((worth[account] - worth[STILL]) / self.temperature,
                                           -50, 50)))

    def rate(self, i):
        """How often this match's attacker has been in a move as the agent rose, over
        the prior."""
        return (self.met_prior * self.meaty + self.on[i]) / (self.met_prior + self.seen[i])

    def guard_chance(self, i):
        """The probability that a rising the attacker is on is guarded through by sight:
        none at the rate `low`, all at `high`."""
        return float(np.clip((self.rate(i) - self.low) / (self.high - self.low), 0.0, 1.0))

    def on_it(self, v):
        """The attacker as the agent sees it: in a move of its own, or near, or in the
        air within reach."""
        d = abs(float(v[DX])) * PIXELS
        return bool(int(round(float(v[OPP_ACT]))) >= FIRST_OWN or d < self.near
                    or (v[OPP_AIR] > 0 and d <= self.fly))

    def close(self, i, view):
        """The followed wake-up's swing into its account (view None: dropped)."""
        rec, self.open[i] = self.open[i], None
        if rec is None or view is None:
            return
        mine = max(0.0, rec[2] - float(view[SELF_HP]) * HP)
        theirs = max(0.0, rec[3] - float(view[OPP_HP]) * HP)
        k = SUPER if rec[4] == SUPER_MOVE else MOVE if rec[1] else STILL
        self.count[i, k] += 1
        self.total[i, k] += theirs - mine
        self.all[k] += (1, theirs - mine)

    def watch(self, i, ctx):
        v = ctx.view
        a = int(round(float(v[SELF_ACT])))
        down = a in DOWN
        self.step[i] += 1
        rec = self.open[i]
        if rec is not None:
            rec[0] += 1
            if rec[0] <= REVERSAL and a >= FIRST_OWN and not rec[1]:
                rec[1], rec[4] = True, a
            # (until it sees the round over, itself down again, or `window` steps on)
            if v[ROUND_OVER] != 0 or down or rec[0] >= self.window:
                self.close(i, v)
        if down and not self.was_down[i]:
            self.n_['knockdowns'] += 1
            self.veto[i] = self.moves and self.rng.random() < self.chance(i)
            self.n_['guarded'] += int(self.veto[i])
            self.asked[i], self.dirs[i] = False, []
            self.met[i] = self.drawn[i] = False
        if down and self.guard and self.on_it(v):
            self.met[i] = True
        if self.holding[i] > 0:  # up and guarding on: until the attacker has let up
            self.holding[i] -= 1
            going = bool(int(round(float(v[OPP_ACT]))) >= FIRST_OWN or
                         (v[OPP_AIR] > 0 and abs(float(v[DX])) * PIXELS <= self.fly))
            self.quiet[i] = 0 if going else self.quiet[i] + 1
            if (down or v[ROUND_OVER] != 0 or v[SELF_HITSTUN] > 0 or 0x32 <= a < 0x60
                    or self.quiet[i] >= self.gap):
                self.holding[i] = 0
        if self.was_down[i] and not down:
            if v[ROUND_OVER] == 0:  # the guard's read: was the attacker in a move as it rose
                self.seen[i] += 1
                self.n_['risings'] += 1
                if int(round(float(v[OPP_ACT]))) >= FIRST_OWN:
                    self.on[i] += 1
                    self.n_['attacked'] += 1
            if (self.veto[i] and self.met[i] and self.guard and v[ROUND_OVER] == 0
                    and (a < 0x32 or a >= 0x96)):
                self.holding[i], self.quiet[i] = self.hold, 0
            self.veto[i] = False
            if v[ROUND_OVER] == 0 and (a < 0x32 or a >= 0x96):  # up, not hit as it lay
                moved = a >= FIRST_OWN
                self.open[i] = [0, moved, float(v[SELF_HP]) * HP, float(v[OPP_HP]) * HP,
                                a if moved else None]
        self.was_down[i] = down

    def act(self, i, ctx):
        v = ctx.view
        if not self.was_down[i]:
            if self.holding[i] > 0:  # (its guard going on, by sight)
                self.n_['held'] += 1
                return STAND_GUARD if v[OPP_AIR] > 0 else CROUCH_GUARD
            return None
        own = None
        if self.plain:  # the guard alone: drawn once, held by sight, else not its step
            if not (self.guard and self.met[i]):
                return None
            if not self.drawn[i]:
                self.drawn[i] = True
                self.n_['met'] += 1
                if self.rng.random() < self.guard_chance(i):
                    self.veto[i] = True
                    self.n_['met_guarded'] += 1
            if not self.veto[i]:
                return None
            self.n_['steps'] += 1
            self.n_['stood'] += int(v[OPP_AIR] > 0)
            return STAND_GUARD if v[OPP_AIR] > 0 else CROUCH_GUARD
        if ctx.policy is not None and ctx.hist is not None:  # its own play's action now
            x = np.concatenate([np.asarray(v, np.float32).reshape(-1),
                                np.asarray(ctx.hist, np.float32).reshape(-1)])
            own = int(np.asarray(ctx.policy(x[None, :self.width or len(x)])).reshape(-1)[0])
            direction, buttons = TABLE.actions[own]
            dirs = self.dirs[i]
            if not dirs or dirs[-1][1] != direction:
                dirs.append((int(self.step[i]), direction))
            recent = [d for t, d in dirs if t > self.step[i] - RECENT]
            bars = int(float(v[SELF_GAUGE]) * 3 + 1e-4)
            level = min(max([SUPER_LEVEL.get(b, 0) for b in buttons] or [0]), bars)
            if (not self.veto[i] and not self.asked[i] and level == 1
                    and sweeps(recent) >= 2):
                # 236236 and a button that makes it the level-one super, while it sees
                # itself down: the wake-up super is coming
                self.asked[i] = True
                self.n_['supers'] += 1
                if self.rng.random() < self.chance(i, SUPER):
                    self.veto[i] = True
                    self.n_['stopped'] += 1
        sight = False
        if self.guard and self.met[i]:
            if not self.drawn[i]:  # the attacker is on it: this rising's guard, drawn once
                self.drawn[i] = True
                self.n_['met'] += 1
                if not self.veto[i] and self.rng.random() < self.guard_chance(i):
                    self.veto[i] = True
                    self.n_['met_guarded'] += 1
            sight = bool(self.veto[i])
        if not self.veto[i]:
            return own  # (its own play, as this module drew it: what it read is what is played)
        self.n_['steps'] += 1
        if sight:  # held by sight: standing under an attacker in the air, no jump, no button
            if v[OPP_AIR] > 0:
                self.n_['stood'] += 1
                return STAND_GUARD
            if own in (CROUCH_GUARD, STAND_GUARD):
                self.n_['kept'] += 1
                return own
            return CROUCH_GUARD
        if own is not None:
            direction, buttons = TABLE.actions[own]
            if not buttons and direction in BACK:
                self.n_['kept'] += 1
                return own
        return STAND_GUARD if v[OPP_AIR] > 0 else CROUCH_GUARD

    def stats(self):
        out = dict(self.n_)
        for k, name in enumerate(ACCOUNTS):
            n = self.all[k, 0]
            out[name] = dict(n=int(n), swing=round(float(self.all[k, 1] / n)) if n else None)
        return out


@modules.register('rise')
def rise(agent, where, files, options, data):
    """options: the file's head."""
    o = dict(options)
    keys = ('prior', 'move', 'still', 'super', 'temperature', 'window', 'carry', 'decay', 'seed',
            'moves', 'guard', 'meaty', 'low', 'high', 'met_prior', 'near', 'fly', 'hold', 'gap',
            'plain')
    unknown = sorted(set(o) - set(keys))
    if unknown:
        raise ValueError(f"rise: no option {', '.join(unknown)}")
    width = agent.model.observation_space.shape[0] if agent is not None else None
    return Rise(width=width, **{k: o[k] for k in keys if k in o})
