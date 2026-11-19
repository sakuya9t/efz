"""The module 'who' (python/efz_env/modules.py; evaluate.py --p1-module): a measure, not a
player: for the moves named, which module's steps the move's inputs were, and what the
opponent was doing as the agent sees the move start.

    who[:moves=0x104+0x105+0x106+0x107,delay=14,span=12]

It never acts. As it sees (the agent's view, `delay` steps late) one of `moves` start, it
looks at who played the steps `delay` to `delay + span` steps back (the motion and the
button): a module's name where one played any of them (the first in the stack's order to
have), else 'policy'; and at the opponent in that view: 'guarding', 'hit' (a combo's
piece) or 'free'. stats(): the count of each "move|opponent|who". Put it first among the
modules, so that it watches every step.
"""

import collections
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env import modules

import tactics

SELF_ACT, OPP_ACT, OPP_HITSTUN = 18, 50, 52
GUARDS = frozenset(tactics.GUARDS)


class Who(modules.Module):
    name = 'who'

    def __init__(self, moves, delay=14, span=12):
        self.moves, self.delay, self.span = frozenset(moves), int(delay), int(span)
        self.counts = collections.Counter()
        self.batch(0)

    def batch(self, n):
        self.owners = [collections.deque(maxlen=self.delay + self.span + 2) for _ in range(n)]
        self.prev = [0] * n

    def reset(self, mask=None):
        for i, d in enumerate(self.owners):
            if mask is None or mask[i]:
                d.clear()
                self.prev[i] = 0

    def watch(self, i, ctx):
        self.owners[i].append(ctx.last)  # (who played the step before this one)
        a = int(round(float(ctx.view[SELF_ACT])))
        if a in self.moves and a != self.prev[i]:
            past = list(self.owners[i])[:-self.delay] if self.delay else list(self.owners[i])
            names = [x for x in past[-self.span:] if x and x != self.name]
            o = int(round(float(ctx.view[OPP_ACT])))
            opp = 'guarding' if o in GUARDS else 'hit' if ctx.view[OPP_HITSTUN] > 0 else 'free'
            self.counts[f'{hex(a)}|{opp}|{names[0] if names else "policy"}'] += 1
        self.prev[i] = a

    def act(self, i, ctx):
        return None

    def stats(self):
        return dict(self.counts.most_common())


@modules.register('who')
def who(agent, where, files, options, data):
    """options: moves (hex numbers joined by +), delay (14), span (12)."""
    moves = [int(x, 16) for x in str(options.get('moves', '0x104+0x105+0x106+0x107')).split('+')]
    return Who(moves, delay=options.get('delay', 14), span=options.get('span', 12))
