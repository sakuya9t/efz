"""Controls: the byte each player sends per step, and discrete action sets over them.

A control byte is the game's own input word: four directions and four buttons. With
the environment's relative_actions (the default), RIGHT and LEFT mean forward (toward
where the player faces) and back, so that one policy plays both sides.

    from efz_env import actions
    table = actions.ActionTable()            # 9 directions x (none, A, B, C, D) = 45
    bytes_ = table.to_bytes(indices)          # (num_envs, 2) ints -> (num_envs, 2) uint8
"""

import numpy as np

RIGHT = FORWARD = 0x01
LEFT = BACK = 0x02
DOWN = 0x04
UP = 0x08
A = 0x10
B = 0x20
C = 0x40
D = 0x80

# Numpad notation, for a player facing right (or any player, with relative_actions):
# 1 down-back, 2 down, 3 down-forward, 4 back, 5 neutral, 6 forward, 7 up-back, 8 up,
# 9 up-forward.
NUMPAD = {
    1: DOWN | BACK, 2: DOWN, 3: DOWN | FORWARD,
    4: BACK, 5: 0, 6: FORWARD,
    7: UP | BACK, 8: UP, 9: UP | FORWARD,
}

BUTTONS = {'': 0, 'A': A, 'B': B, 'C': C, 'D': D}


def encode(direction=5, buttons=''):
    """The control byte for a numpad direction and a string of buttons ('', 'A', 'BC')."""
    value = NUMPAD[direction]
    for b in buttons:
        value |= BUTTONS[b.upper()]
    return value


class ActionTable:
    """A discrete action set: every direction with every button set given.

    directions: numpad directions (default all nine).
    buttons: button strings pressed with each (default none, A, B, C, D).

    Holding a button down across steps is one press: the game reads a button going down.
    To press it again an agent lets go for a step (an action without it).
    """

    def __init__(self, directions=(1, 2, 3, 4, 5, 6, 7, 8, 9),
                 buttons=('', 'A', 'B', 'C', 'D')):
        self.actions = [(d, b) for b in buttons for d in directions]
        self.table = np.array([encode(d, b) for d, b in self.actions], dtype=np.uint8)

    def __len__(self):
        return len(self.table)

    def to_bytes(self, indices):
        """Indices into the table (any shape) -> control bytes (uint8, same shape)."""
        return self.table[np.asarray(indices)]

    def describe(self, index):
        d, b = self.actions[index]
        return f'{d}{b}'
