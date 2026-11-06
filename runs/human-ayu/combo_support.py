"""Built-in combo support for an agent (the user's, after Hisoutensoku's scripted AIs, whose
combos are written in rather than learnt): ways to play an agent whose combos come from
elsewhere, as evaluate.py's players (--p1-combo, --p1-lookahead).

    agent = ComboSwitch(Agent('agent.zip'), Agent('combo/combo.zip'))   # the combo master's
    agent = lookahead(data_dir, 'agent.zip', 'combo-library.npz')       # the best route, tried

ComboSwitch: while the agent's combo runs (its combo counter, as the agent sees the game:
`delay` steps late, a person's hit-confirm; confirm='now' for none), the combo player's
controls are played, else the agent's own. Both see every step and every input, so either
can take over at once. The combo master (combo.py) was trained as the agent was (the
reaction time, a pull toward people's play) on trials from people's combo starts.

lookahead: at each first hit (as the game is: an upper bound) people's library combos
with that starter and the agent's own play are tried on copies of the game and the most
damaging is played (redteam.py's planner, the red team's): "a player who knows the routes
and lands them", the defender guarding once it can.
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

import numpy as np

COMBO_HITS = 30  # self_combo_hits (/ 30)


class ComboSwitch:
    def __init__(self, base, combo, confirm='seen'):
        if confirm not in ('seen', 'now'):
            raise ValueError("confirm: 'seen' or 'now'")
        self.base, self.combo, self.confirm = base, combo, confirm
        self.frame_skip, self.history = 1, base.history
        self.steps = self.switched = 0

    def batch(self, n):
        self.base.batch(n)
        self.combo.batch(n)

    def reset(self, mask=None):
        self.base.reset(mask)
        self.combo.reset(mask)

    def controls(self, obs, step):
        own = self.base.controls(obs, step)
        alt = self.combo.controls(obs, step)
        if self.confirm == 'seen' and self.base.delay:
            view = self.base.seen.buf[:, self.base.delay]  # what the agent sees now
        else:
            view = obs
        use = np.round(view[:, COMBO_HITS] * 30) > 0
        self.steps += len(use)
        self.switched += int(use.sum())
        return np.where(use, alt, own)

    def observe(self, controls):
        self.base.observe(controls)
        self.combo.observe(controls)


def lookahead(data_dir, path, library, per_start=12):
    from stable_baselines3 import PPO
    import macros
    import redteam
    planner = redteam.Planner(data_dir, macros.load_library(library, 300),
                              PPO.load(path, device='cpu'), per_start=per_start)
    return redteam.RedTeamAgent(planner, path)
