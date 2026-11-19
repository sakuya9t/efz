"""The module 'cancel' (python/efz_env/modules.py; evaluate.py --p1-module, play.py
--module): a risky move of the agent's that it sees guarded is cancelled with an Instant
Charge (22C) when it has the RF gauge for one.

    cancel[:moves=623A+623B,rg=true]

Why (the user's, 17 November: "risk management ... Ayu's 623 being RGed can make herself
in a dangerous situation"). People's Ayu in the community's replays, of their raw 623A and
623B (not a combo's piece) that were guarded with the gauge for a cancel (500 of the RF
gauge, or cyan): 69% and 81% cancelled, and the opponent then hit them first 29% and 23%
of the time, for 86% and 76% of those left uncancelled. They start these moves with the
gauge in hand (77-87% of the raw ones that touched). Half their cancels come within 13 steps of the
guard: pressed without waiting to see, as the same 22C goes on into a combo when the
move hits. The agent's routes take the hit's side (they are planned when it sees its
hit); nothing took the guard's, and against the user round 17's agent cancelled none of
its misses. This module does it on sight: the guard is seen `delay` steps late and 22C is
three steps, so its Instant Charge begins about 17 steps after the contact; people's
cancels that late still cut the punishment from 76-86% to 35-38%.

What it costs: the Instant Charge empties the RF gauge, which a combo would have used.
Measured by evaluate.py's risks (per move: ic, punished, lost, net).

options: moves (the names of tactics.RISKY joined by +; default 623A+623B: the ones
whose own cost leaves the gauge), rg (also when the guard was a recoil guard, default
true: people's cancels there cut less, 27-35% for 35-50%).
"""

import os
import sys

import numpy as np

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env import modules
from efz_env.actions import ActionTable

import tactics

TABLE = ActionTable()
INDEX = {a: k for k, a in enumerate(TABLE.actions)}
SELF_ACT, OPP_ACT, SELF_HITSTUN, OPP_HITSTUN = 18, 50, 20, 52
SELF_RF, SELF_RF_BLUE = 10, 11        # self_rf_gauge (/ 1000), self_rf_blue: cyan
RF_FOR_ONE = 500                      # the gauge an Instant Charge needs (evaluate.rf_state)
MOTION = (INDEX[(2, '')], INDEX[(5, '')], INDEX[(2, 'C')], INDEX[(2, 'C')])  # 22C
INSTANT_CHARGE = (0xa7, 0xab)
CAME = 12                             # steps after its 22C in which it must see the charge
GUARDS, RG = frozenset(tactics.GUARDS), frozenset(tactics.RG)


class Cancel(modules.Module):
    """moves: the actions it cancels. stats(): guarded (those it saw guarded), no_gauge,
    tried (22C pressed) and came (the Instant Charge seen after)."""
    name = 'cancel'

    def __init__(self, moves, rg=True):
        self.moves, self.rg = frozenset(moves), bool(rg)
        self.n_ = dict(guarded=0, no_gauge=0, tried=0, came=0)
        self.batch(0)

    def batch(self, n):
        self.n = n
        self.fired = np.zeros(n, bool)   # this move's guard was already answered
        self.playing = {}                # env -> the motion's next step
        self.waiting = np.zeros(n, int)  # steps left to see the charge it pressed

    def reset(self, mask=None):
        mask = np.ones(self.n, bool) if mask is None else np.asarray(mask, bool)
        self.fired[mask] = False
        self.waiting[mask] = 0
        for i in np.flatnonzero(mask):
            self.playing.pop(int(i), None)

    def stats(self):
        return dict(self.n_)

    def watch(self, i, ctx):
        a = int(round(float(ctx.view[SELF_ACT])))
        if self.waiting[i] > 0:
            self.waiting[i] -= 1
            if a in INSTANT_CHARGE:
                self.n_['came'] += 1
                self.waiting[i] = 0
        if a not in self.moves and i not in self.playing:
            self.fired[i] = False

    def act(self, i, ctx):
        v = ctx.view
        k = self.playing.get(i)
        if k is not None:
            if v[SELF_HITSTUN] > 0 or k >= len(MOTION):
                self.playing.pop(i)
            else:
                self.playing[i] = k + 1
                if k + 1 == len(MOTION):
                    self.waiting[i] = CAME + len(MOTION)
                return MOTION[k]
        if self.fired[i] or int(round(float(v[SELF_ACT]))) not in self.moves:
            return None
        o = int(round(float(v[OPP_ACT])))
        if o not in GUARDS or v[OPP_HITSTUN] > 0 or v[SELF_HITSTUN] > 0 or \
                (o in RG and not self.rg):
            return None
        self.fired[i] = True
        self.n_['guarded'] += 1
        if v[SELF_RF] * 1000 < RF_FOR_ONE and v[SELF_RF_BLUE] <= 0:
            self.n_['no_gauge'] += 1
            return None
        self.n_['tried'] += 1
        self.playing[i] = 1
        return MOTION[0]


@modules.register('cancel')
def cancel(agent, where, files, options, data):
    """options: moves ('623A+623B'), rg (true); the character's names: tactics.RISKY."""
    names = {v: k for k, v in tactics.RISKY['ayu'].items()}
    want = str(options.get('moves', '623A+623B')).split('+')
    unknown = [m for m in want if m not in names]
    if unknown:
        raise ValueError(f'cancel: moves {unknown}: one of {sorted(names)}')
    return Cancel([names[m] for m in want], rg=options.get('rg', True))
