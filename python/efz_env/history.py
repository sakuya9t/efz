"""Each player's own recent inputs, as features to append to its observation.

A policy that acts every frame (frame_skip=1) has to know what it has input already to
carry a motion through (2, 3, 6 and A for 236A): the game's state doesn't show it until
the move comes out. These features are, for each of the last `frames` steps (most
recent first): forward-back (1, 0, -1), up-down (1, 0, -1), and whether A, B, C and D
went down. They come from control bytes as the environment reports them (info['input'],
relative to facing), so they are the same for a player's own actions and for a replay
played back (EfzVecEnv.play).

    hist = InputHistory((num_envs, 2), frames=16)
    obs = env.reset(); hist.clear()
    ...  # each step:
    obs, _, term, trunc, info = env.step(controls)
    hist.push(info['input']); hist.clear(term | trunc)   # a new match: nothing input yet
    features = np.concatenate([obs, hist.features()], -1)

history_features() gives the same for a whole match at once.
"""

import numpy as np

from .actions import A, BACK, DOWN, FORWARD, UP

FEATURES = 6  # per step: forward-back, up-down, A, B, C, D pressed


def input_features(controls, previous):
    """Control bytes, and the step's before -> (..., 6) float32."""
    c = np.asarray(controls, dtype=np.uint8)
    p = np.asarray(previous, dtype=np.uint8)
    out = np.empty(c.shape + (FEATURES,), dtype=np.float32)
    out[..., 0] = ((c & FORWARD) > 0).astype(np.float32) - ((c & BACK) > 0)
    out[..., 1] = ((c & UP) > 0).astype(np.float32) - ((c & DOWN) > 0)
    pressed = (c & ~p) >> 4  # the buttons that went down
    for b in range(4):
        out[..., 2 + b] = (pressed >> b) & 1
    return out


class InputHistory:
    """The last `frames` steps' input features of each player in a batch (`shape`, e.g.
    (num_envs, 2)), most recent first."""

    def __init__(self, shape, frames=16):
        self.shape = tuple(shape)
        self.frames = frames
        self.buf = np.zeros(self.shape + (frames, FEATURES), dtype=np.float32)
        self.prev = np.zeros(self.shape, dtype=np.uint8)

    @property
    def size(self):
        return self.frames * FEATURES

    def push(self, controls):
        controls = np.asarray(controls, dtype=np.uint8)
        self.buf[..., 1:, :] = self.buf[..., :-1, :]
        self.buf[..., 0, :] = input_features(controls, self.prev)
        self.prev = controls.copy()

    def clear(self, mask=None):
        """Forgets the inputs (where `mask`, over the leading axes; all if None)."""
        if mask is None:
            self.buf[:] = 0
            self.prev[:] = 0
            return
        mask = np.asarray(mask, dtype=bool)
        self.buf[mask] = 0
        self.prev[mask] = 0

    def features(self):
        return self.buf.reshape(self.shape + (self.size,))


class Delay:
    """A reaction time: what a player sees is the observation of `steps` steps before
    (its own inputs, above, it knows at once). For a batch (`shape`, e.g. (num_envs, 2))
    of observations of `dim` features; a new match's first view fills it (so a player
    sees the start of the match for its first `steps` steps)."""

    def __init__(self, shape, steps, dim):
        self.shape = tuple(shape)
        self.steps = steps
        self.buf = np.zeros(self.shape + (steps + 1, dim), dtype=np.float32)
        self.fresh = np.ones(self.shape, dtype=bool)

    def clear(self, mask=None):
        """A new match (where mask): the next view pushed fills the buffer."""
        if mask is None:
            self.fresh[:] = True
        else:
            self.fresh[np.asarray(mask, dtype=bool)] = True

    def push(self, obs):
        """This step's observations -> what is seen: those of `steps` steps before."""
        obs = np.asarray(obs, dtype=np.float32)
        self.buf[..., 1:, :] = self.buf[..., :-1, :]
        self.buf[..., 0, :] = obs
        if self.fresh.any():
            self.buf[self.fresh] = obs[self.fresh][..., None, :]
            self.fresh[:] = False
        return self.buf[..., self.steps, :].copy()

    def peek(self, obs):
        """What push(obs) would return, without pushing it (a match's last view)."""
        obs = np.asarray(obs, dtype=np.float32)
        if self.steps == 0:
            return obs.copy()
        out = self.buf[..., self.steps - 1, :].copy()
        out[self.fresh] = obs[self.fresh]
        return out


def delayed(obs, steps):
    """For one player's observations over a match, (T, dim): what it sees at each step,
    those of `steps` steps before (the first, before that)."""
    obs = np.asarray(obs)
    idx = np.maximum(np.arange(len(obs)) - steps, 0)
    return obs[idx]


def history_features(controls, frames=16):
    """For one player's control bytes over a match, (T,), the features each step's
    observation is given: row t holds the inputs of steps t-1, t-2, ... t-frames."""
    controls = np.asarray(controls, dtype=np.uint8)
    T = len(controls)
    prev = np.concatenate([[0], controls[:-1]]).astype(np.uint8)
    per_step = input_features(controls, prev)  # (T, 6): step t's input
    out = np.zeros((T, frames, FEATURES), dtype=np.float32)
    for k in range(1, frames + 1):
        out[k:, k - 1] = per_step[:T - k]
    return out.reshape(T, frames * FEATURES)


def action_labels(controls, table=None):
    """The action of `table` (default ActionTable()) that plays each step's input as the
    game reads it: its direction, and a button that went down (the first of A-D, if
    more than one did; none if none did: a button held on presses nothing more)."""
    from .actions import ActionTable, NUMPAD
    table = table or ActionTable()
    c = np.asarray(controls, dtype=np.uint8)
    prev = np.concatenate([[0], c[:-1]]).astype(np.uint8)
    h = ((c & FORWARD) > 0).astype(int) - ((c & BACK) > 0)
    v = ((c & UP) > 0).astype(int) - ((c & DOWN) > 0)
    numpad = 5 + h + 3 * v
    pressed = (c & ~prev) >> 4
    button = np.zeros(len(c), dtype=int)  # 0 none, 1-4 A-D
    for b in (3, 2, 1, 0):  # the first that went down wins
        button = np.where((pressed >> b) & 1, b + 1, button)
    index = {(d, b): i for i, (d, b) in enumerate(table.actions)}
    names = ['', 'A', 'B', 'C', 'D']
    lookup = np.full((10, 5), -1, dtype=np.int64)
    for d in range(1, 10):
        for b in range(5):
            lookup[d, b] = index.get((d, names[b]), -1)
    out = lookup[numpad, button]
    if (out < 0).any():
        raise ValueError('the table has no action for some inputs')
    return out
