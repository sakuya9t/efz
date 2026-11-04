"""EfzVecEnv: a batch of two-player EFZ matches, stepped in parallel in C++.

    env = EfzVecEnv('/path/to/EFZ', num_envs=256)
    obs = env.reset()                         # (256, 2, obs_dim): each player's view
    obs, reward, terminated, truncated, info = env.step(actions)   # actions (256, 2) uint8

Everything returned is a numpy view of the library's buffers, written in place by the
next step or reset: copy what you keep. By default matches that end restart within the
same step (the returned obs is the new match's first view; final_obs holds the last view
of the match that ended, and info describes it); autoreset='next_step' restarts them at
the next step instead, and 'disabled' leaves them ended until reset(mask).
"""

import ctypes
import os

import numpy as np

from . import _native

STAGES = 23

AUTORESET = {
    'same_step': _native.AUTORESET_SAME_STEP,
    'next_step': _native.AUTORESET_NEXT_STEP,
    'disabled': _native.AUTORESET_DISABLED,
}


def character_names():
    lib = _native.library()
    return [lib.efz_env_character_name(i).decode() for i in range(25)]


def _character(c):
    if c is None:
        return -1
    if isinstance(c, str):
        names = character_names()
        if c.lower() not in names:
            raise ValueError(f'no character {c!r}; they are {names}')
        return names.index(c.lower())
    return int(c)


def _pool(items, size):
    if items is None:
        return 0
    mask = 0
    for i in items:
        i = _character(i) if size == 25 else int(i)
        if not 0 <= i < size:
            raise ValueError(f'{i} is out of range')
        mask |= 1 << i
    return mask


def _per_env(value, n, width=None):
    """A value for every environment: one shared, or one per env."""
    a = np.asarray(value, dtype=object)
    if width is None:
        return [value] * n if a.ndim == 0 else list(value)
    if a.ndim == 1 and len(a) == width:
        return [tuple(value)] * n
    return [tuple(v) for v in value]


class EfzVecEnv:
    """A batch of EFZ matches. Parameters are efz_env.h's EfzEnvConfig:

    data_dir: an EFZ 4.02 install (default $EFZ_DATA or $EFZ_DIR).
    num_envs, num_threads: the threads stepping games, one pool for the whole process
        that every batch shares (0: one per hardware thread).
    frame_skip: game frames per step, the controls held (the game runs 64 frames a
        second, three simulation ticks each).
    max_frames: frames after which a match is cut short (truncated); 0 never.
    rounds_to_win, cpu_level (1-4), damage_level (1-3: 50/100/200%).
    skip_noninteractive: run through intros and KOs within a step.
    relative_actions: RIGHT/LEFT are forward/back for each player.
    drawing: draw the frames (render()); slower, the game is the same.
    cache_size: matches kept ready to start (5.5 MB each, 61 MB drawing).
    reward_damage, reward_round, reward_match: the reward is reward_damage per full HP
        bar dealt minus taken, plus reward_round per round won minus lost, plus
        reward_match for winning the match minus for losing it.
    seed: draws random characters and stages and seeds the game's CPU.
    autoreset: what a step does when a match ends: 'same_step' (the next match starts
        in the step; final_obs is the last view), 'next_step' (obs is the last view;
        the next step starts the next match, ignoring its actions, with no reward) or
        'disabled' (the environment stays ended until reset(mask) starts it again).
    """

    def __init__(self, data_dir=None, num_envs=64, *, num_threads=0, frame_skip=1,
                 max_frames=0, rounds_to_win=2, cpu_level=2, damage_level=2,
                 skip_noninteractive=True, relative_actions=True, drawing=False,
                 cache_size=64, reward_damage=1.0, reward_round=0.0, reward_match=1.0,
                 seed=0, autoreset='same_step'):
        if autoreset not in AUTORESET:
            raise ValueError(f'autoreset must be one of {sorted(AUTORESET)}')
        data_dir = data_dir or os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR')
        if not data_dir:
            raise ValueError('pass data_dir, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
        self._lib = lib = _native.library()
        cfg = _native.Config()
        lib.efz_env_default_config(ctypes.byref(cfg))
        for name, value in dict(num_envs=num_envs, num_threads=num_threads,
                                frame_skip=frame_skip, max_frames=max_frames,
                                rounds_to_win=rounds_to_win, cpu_level=cpu_level,
                                damage_level=damage_level,
                                skip_noninteractive=int(skip_noninteractive),
                                relative_actions=int(relative_actions), drawing=int(drawing),
                                cache_size=cache_size, reward_damage=reward_damage,
                                reward_round=reward_round, reward_match=reward_match,
                                seed=seed, autoreset=AUTORESET[autoreset]).items():
            setattr(cfg, name, value)
        self.config = cfg
        error = ctypes.create_string_buffer(512)
        self._h = lib.efz_env_create(os.fsencode(data_dir), ctypes.byref(cfg), error, 512)
        if not self._h:
            raise RuntimeError(f'efz_env: {error.value.decode(errors="replace")}')
        self.num_envs = num_envs
        self.obs_dim = lib.efz_env_obs_dim()
        self.observation_names = [lib.efz_env_obs_name(i).decode() for i in range(self.obs_dim)]
        self.drawing = bool(drawing)
        self.autoreset = autoreset
        self._actions = np.zeros((num_envs, 2), dtype=np.uint8)
        self._pending = False
        self._keep = None
        self._bind()

    # --- Buffers.

    def _bind(self):
        b = _native.Buffers()
        self._lib.efz_env_buffers(self._h, ctypes.byref(b))
        n, d = self.num_envs, self.obs_dim
        self.obs = np.ctypeslib.as_array(b.obs, shape=(n, 2, d))
        self.final_obs = np.ctypeslib.as_array(b.final_obs, shape=(n, 2, d))
        self.reward = np.ctypeslib.as_array(b.reward, shape=(n, 2))
        self.terminated = np.ctypeslib.as_array(b.terminated, shape=(n,)).view(np.bool_)
        self.truncated = np.ctypeslib.as_array(b.truncated, shape=(n,)).view(np.bool_)
        self.info = np.ctypeslib.as_array(b.info, shape=(n,))

    def set_obs_buffers(self, obs, final_obs, keep=None):
        """Has the library write observations straight into memory of the program's:
        two writable, C-contiguous float32 buffers of shape (num_envs, 2, obs_dim), as
        numpy arrays or as their addresses (with `keep` holding their owners alive)."""
        self._finish()
        n, d = self.num_envs, self.obs_dim

        def address(a):
            if isinstance(a, int):
                return a
            a = np.asarray(a)
            if a.dtype != np.float32 or a.shape != (n, 2, d) or not a.flags.c_contiguous \
                    or not a.flags.writeable:
                raise ValueError(f'need a writable C-contiguous float32 ({n}, 2, {d}) array')
            return a.ctypes.data

        self._lib.efz_env_set_obs_buffers(self._h, address(obs), address(final_obs))
        self._keep = (obs, final_obs, keep)
        self._bind()
        if not isinstance(obs, int):
            self.obs, self.final_obs = np.asarray(obs), np.asarray(final_obs)

    def pin_memory(self, torch):
        """Observations go straight into page-locked torch tensors, so that
        `obs.to('cuda', non_blocking=True)` copies them to the GPU by DMA, overlapping
        what comes next. Returns (obs, final_obs) as tensors; env.obs and env.final_obs
        are numpy views of them."""
        shape = (self.num_envs, 2, self.obs_dim)
        obs = torch.empty(shape, dtype=torch.float32, pin_memory=True)
        final = torch.empty(shape, dtype=torch.float32, pin_memory=True)
        self.set_obs_buffers(obs.data_ptr(), final.data_ptr(), keep=(obs, final))
        self.obs, self.final_obs = obs.numpy(), final.numpy()
        return obs, final

    # --- What the environments play.

    def set_matches(self, chars=(None, None), stage=None, cpu=(False, False),
                    palettes=(None, None), char_pool=None, stage_pool=None):
        """What each environment plays from its next match on. Each argument is one value
        for all environments or a sequence of one per environment:

        chars: (p1, p2), numbers 0-24 or names ('ayu'); None: drawn from char_pool.
        stage: 0-22; None: drawn from stage_pool.
        cpu: (p1, p2): True for the game's CPU (at cpu_level) on that side.
        palettes: (p1, p2) colour numbers; None: 0, and 1 for P2 in a mirror match.
        char_pool: characters random ones are drawn from (default: all 23 playable), or
            a pair of such lists, one per side.
        stage_pool: stages random ones are drawn from (default: all).
        """
        n = self.num_envs
        chars = _per_env(chars, n, 2)
        stages = _per_env(stage, n)
        cpus = _per_env(cpu, n, 2)
        pals = _per_env(palettes, n, 2)
        if char_pool is None or (len(char_pool) == 2 and all(
                isinstance(p, (list, tuple, set)) or p is None for p in char_pool)):
            pools = char_pool if char_pool is not None else (None, None)
        else:
            pools = (char_pool, char_pool)
        pool = (_pool(pools[0], 25), _pool(pools[1], 25))
        stage_mask = _pool(stage_pool, STAGES)
        matches = (_native.Match * n)()
        for i, m in enumerate(matches):
            for p in range(2):
                m.chars[p] = _character(chars[i][p])
                m.palettes[p] = -1 if pals[i][p] is None else int(pals[i][p])
                m.cpu[p] = 1 if cpus[i][p] else 0
                m.char_pool[p] = pool[p]
            m.stage = -1 if stages[i] is None else int(stages[i])
            m.stage_pool = stage_mask
        self._finish()
        if self._lib.efz_env_set_matches(self._h, matches, n) != 0:
            raise RuntimeError('efz_env_set_matches failed')

    # --- Running.

    def _finish(self):
        if self._pending:
            self._lib.efz_env_step_wait(self._h)
            self._pending = False

    def seed(self, index, seed):
        """Seeds environment `index`: its following matches (characters and stages drawn
        from pools, the game's rand) follow from `seed` alone, from its next match on."""
        self._finish()
        if self._lib.efz_env_seed(self._h, int(index), int(seed) & (2**64 - 1)) != 0:
            raise IndexError(f'no environment {index}')

    def reset(self, mask=None, seed=None):
        """Starts new matches (in every environment, or where mask is true). Returns obs;
        info is in self.info. seed: an int seeds environment i with seed + i (as
        Gymnasium's vector environments do), or a sequence gives each its own (None
        leaves one as it is); only the environments reset are seeded."""
        self._finish()
        if seed is not None:
            which = range(self.num_envs) if mask is None else np.flatnonzero(mask)
            for i in which:
                s = seed + int(i) if isinstance(seed, (int, np.integer)) else seed[i]
                if s is not None:
                    self.seed(i, s)
        if mask is None:
            self._lib.efz_env_reset(self._h, None)
        else:
            m = np.ascontiguousarray(mask, dtype=np.uint8)
            self._lib.efz_env_reset(self._h, m.ctypes.data)
        return self.obs

    def _actions_pointer(self, actions):
        a = np.asarray(actions)
        if a.dtype != np.uint8 or not a.flags.c_contiguous:
            np.copyto(self._actions, a, casting='unsafe')
            a = self._actions
        if a.shape != (self.num_envs, 2):
            raise ValueError(f'actions must be ({self.num_envs}, 2) control bytes')
        return a.ctypes.data

    def step(self, actions):
        """One step of every environment. actions: (num_envs, 2) control bytes
        (efz_env.actions). Returns (obs, reward, terminated, truncated, info)."""
        self._finish()
        self._lib.efz_env_step(self._h, self._actions_pointer(actions))
        return self.obs, self.reward, self.terminated, self.truncated, self.info

    def step_async(self, actions):
        """Starts a step and returns at once; step_wait finishes it. Meanwhile the batch's
        buffers are being written: don't read them. With two batches, one steps while
        the program works on the other's observations (e.g. on the GPU)."""
        self._finish()
        self._lib.efz_env_step_async(self._h, self._actions_pointer(actions))
        self._pending = True

    def step_wait(self):
        self._finish()
        return self.obs, self.reward, self.terminated, self.truncated, self.info

    # --- Save states and pictures.

    def save_state(self, index):
        """The whole game of environment `index`, as bytes. It loads into any
        environment of any batch of this process (not another process)."""
        self._finish()
        size = self._lib.efz_env_state_size(self._h, index)
        buf = ctypes.create_string_buffer(size)
        if self._lib.efz_env_save_state(self._h, index, buf, size) != size:
            raise RuntimeError('efz_env_save_state failed')
        return buf.raw

    def load_state(self, index, state):
        self._finish()
        if self._lib.efz_env_load_state(self._h, index, state, len(state)) != 0:
            raise ValueError('not a save state of this library')

    def render(self, index=0):
        """The last frame environment `index` drew, (240, 320, 3) uint8 RGB. Needs
        drawing=True."""
        if not self.drawing:
            raise RuntimeError('render needs EfzVecEnv(..., drawing=True)')
        self._finish()
        frame = np.empty((240, 320, 3), dtype=np.uint8)
        if not self._lib.efz_env_render(self._h, index, frame.ctypes.data):
            raise RuntimeError('no frame drawn yet')
        return frame

    @property
    def ticks(self):
        """Simulation ticks run so far (three per game frame)."""
        return self._lib.efz_env_ticks(self._h)

    def close(self):
        if getattr(self, '_h', None):
            self._finish()
            self._lib.efz_env_destroy(self._h)
            self._h = None

    def __enter__(self):
        return self

    def __exit__(self, *exc):
        self.close()

    def __del__(self):
        self.close()
