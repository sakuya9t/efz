"""Playing the game yourself, against an agent or the game's CPU, in a window.

    python python/examples/play.py --agent runs/ppo/model.zip      # play it; each match is recorded
    python python/examples/train.py --opponent human --load runs/ppo/model.zip   # it learns from your games

The window shows the game as the headless library draws it (no sound), at the game's
speed: 64 frames a second. The human plays one side with the keyboard (default: arrows,
Z X C V for A B C D) or the first gamepad (hat or left stick, buttons 0-3); Esc or
closing the window stops. The other side is an agent, a policy acting every frame_skip
frames as in its training, or the game's CPU. Every match is recorded to record_dir as
an .npz of every frame (both players' views and controls) and a .json describing it:
data to learn from (cloning the human's play, or the agent's own experience).

Needs pygame-ce (pip install pygame-ce).
"""

import datetime
import json
import os
import time

import numpy as np

from . import actions
from .actions import ActionTable
from .vec import EfzVecEnv

FPS = 64  # the game's frames a second

DEFAULT_KEYS = {'up': 'up', 'down': 'down', 'left': 'left', 'right': 'right',
                'A': 'z', 'B': 'x', 'C': 'c', 'D': 'v'}


class Quit(Exception):
    """The human closed the window or pressed Esc."""


def to_relative(screen_bits, facing):
    """A control byte with screen directions (RIGHT = screen right) as the library's
    relative one (RIGHT = forward) for a player facing `facing` (1 right, -1 left)."""
    bits = int(screen_bits)
    if facing < 0:
        bits = (bits & ~3) | (bits & 1) << 1 | (bits & 2) >> 1
    return bits


class Controls:
    """The human's controls: the keyboard (pygame key names) and the first gamepad."""

    def __init__(self, keys=None, pad_buttons=(0, 1, 2, 3)):
        import pygame
        self.pygame = pygame
        names = dict(DEFAULT_KEYS, **(keys or {}))
        self.codes = {k: pygame.key.key_code(v) for k, v in names.items()}
        pygame.joystick.init()
        self.pad = pygame.joystick.Joystick(0) if pygame.joystick.get_count() else None
        self.pad_buttons = pad_buttons

    def screen_bits(self):
        """What is held now: directions as on screen, and the buttons."""
        held = self.pygame.key.get_pressed()
        right, left = held[self.codes['right']], held[self.codes['left']]
        up, down = held[self.codes['up']], held[self.codes['down']]
        buttons = [held[self.codes[b]] for b in 'ABCD']
        if self.pad is not None:
            if self.pad.get_numhats():
                hx, hy = self.pad.get_hat(0)
                right, left, up, down = right or hx > 0, left or hx < 0, up or hy > 0, down or hy < 0
            if self.pad.get_numaxes() >= 2:
                ax, ay = self.pad.get_axis(0), self.pad.get_axis(1)
                right, left, up, down = right or ax > .5, left or ax < -.5, up or ay < -.5, down or ay > .5
            for k, b in enumerate(self.pad_buttons):
                if b < self.pad.get_numbuttons() and self.pad.get_button(b):
                    buttons[k] = True
        bits = 0
        if right != left:  # both or neither: no horizontal direction
            bits |= actions.RIGHT if right else actions.LEFT
        if up != down:
            bits |= actions.UP if up else actions.DOWN
        for flag, b in zip((actions.A, actions.B, actions.C, actions.D), buttons):
            if b:
                bits |= flag
        return bits


class Window:
    def __init__(self, scale=3, title='EFZ'):
        import pygame
        self.pygame = pygame
        pygame.init()
        self.scale = scale
        self.screen = pygame.display.set_mode((320 * scale, 240 * scale))
        pygame.display.set_caption(title)
        self.font = pygame.font.Font(None, 12 * scale)
        self.last = None

    def pump(self):
        for e in self.pygame.event.get():
            if e.type == self.pygame.QUIT or (e.type == self.pygame.KEYDOWN and
                                              e.key == self.pygame.K_ESCAPE):
                raise Quit()

    def show(self, rgb, lines=()):
        pg = self.pygame
        if rgb is not None:
            surface = pg.surfarray.make_surface(np.ascontiguousarray(rgb.swapaxes(0, 1)))
            self.last = pg.transform.scale(surface, self.screen.get_size())
        if self.last is not None:
            self.screen.blit(self.last, (0, 0))
        y = 4
        for line in lines:
            text = self.font.render(line, True, (255, 255, 255), (0, 0, 0))
            self.screen.blit(text, ((self.screen.get_width() - text.get_width()) // 2, y))
            y += text.get_height() + 2
        pg.display.flip()

    def message(self, *lines):
        """Text over the last frame, shown at once (e.g. while the agent learns)."""
        self.pump()
        self.show(None, lines)


class Clock:
    """Paces frames at FPS; falls back in step when far behind (a pause to learn)."""

    def __init__(self, fps=FPS):
        self.period = 1.0 / fps
        self.next = time.perf_counter()

    def tick(self):
        self.next += self.period
        now = time.perf_counter()
        if self.next - now < -0.25:
            self.next = now
            return
        while True:
            left = self.next - time.perf_counter()
            if left <= 0:
                return
            if left > 0.002:
                time.sleep(left - 0.0015)


class HumanMatch:
    """Matches in a window: the human plays player `human` (0 or 1), the other side is
    an agent (agent_step's action every frame_skip frames) or the game's CPU
    (opponent='cpu'). Steps through intros and KOs as training's skip_noninteractive
    does, frame by frame, in real time.

    controls: anything with screen_bits() (default: Controls(keys)); window: a Window,
    or None to run without one (tests, or a program that draws itself).
    """

    def __init__(self, data_dir=None, *, human=1, opponent='agent', chars=(None, None),
                 stage=None, char_pool=None, stage_pool=None, frame_skip=4,
                 action_table=None, record_dir='recordings', agent_name='', keys=None,
                 scale=3, window=True, controls=None, realtime=True, result_seconds=2.0,
                 **config):
        if human not in (0, 1):
            raise ValueError('human: 0 (player 1) or 1 (player 2)')
        if opponent not in ('agent', 'cpu'):
            raise ValueError("opponent: 'agent' or 'cpu'")
        self.human, self.side = human, 1 - human
        self.opponent = opponent
        self.frame_skip = max(1, int(frame_skip))
        self.table = action_table or ActionTable()
        self.record_dir = record_dir
        self.agent_name = agent_name
        self.realtime = realtime
        self.result_seconds = result_seconds
        for key in ('frame_skip', 'skip_noninteractive', 'drawing', 'autoreset', 'num_envs'):
            config.pop(key, None)
        config.setdefault('num_threads', 1)
        self.env = EfzVecEnv(data_dir, 1, frame_skip=1, skip_noninteractive=False,
                             drawing=True, autoreset='disabled', **config)
        cpu = [False, False]
        cpu[self.side] = opponent == 'cpu'
        self.env.set_matches(chars=chars, stage=stage, cpu=tuple(cpu), char_pool=char_pool,
                             stage_pool=stage_pool)
        names = self.env.observation_names
        self._facing = names.index('self_facing')
        self._intro = names.index('intro')
        self._round_over = names.index('round_over')
        self.window = Window(scale) if window is True else (window or None)
        self.controls = controls or Controls(keys)
        self.clock = Clock()
        self._controls = np.zeros((1, 2), dtype=np.uint8)
        self._frames = []
        self.matches = 0
        self.results = []  # per match: the winner from the agent's side (1 won, -1 lost, 0)

    # --- Frames.

    def _actionable(self):
        o = self.env.obs[0, 0]
        return o[self._intro] == 0 and o[self._round_over] == 0

    def _frame(self, agent_bits, decision):
        if self.window is not None:
            self.window.pump()
        obs = self.env.obs[0]
        human_screen = self.controls.screen_bits()
        self._controls[0, self.human] = to_relative(human_screen, obs[self.human, self._facing])
        self._controls[0, self.side] = agent_bits
        before = obs.copy()
        _, reward, terminated, truncated, _ = self.env.step(self._controls)
        self._frames.append((before, self._controls[0].copy(), human_screen, decision,
                             reward[0].copy()))
        if self.window is not None:
            self.window.show(self.env.render(0))
        if self.realtime:
            self.clock.tick()
        return float(reward[0, self.side]), bool(terminated[0]), bool(truncated[0])

    # --- The agent's side.

    def reset(self, seed=None):
        """Starts a match; returns the agent's view (obs_dim floats)."""
        self._frames = []
        self.env.reset(seed=seed)
        self.clock = Clock()
        total, ended = 0.0, False
        while not ended and not self._actionable():  # the intro, in real time
            r, term, trunc = self._frame(0, -1)
            total += r
            ended = term or trunc
        return self.env.obs[0, self.side].copy()

    def agent_step(self, action):
        """The agent's action held for frame_skip frames, then on through any intro or KO.
        Returns (obs, reward, terminated, truncated, info) from the agent's side."""
        bits = int(self.table.table[int(action)])
        total, term, trunc = 0.0, False, False
        for k in range(self.frame_skip):
            r, term, trunc = self._frame(bits, int(action) if k == 0 else -1)
            total += r
            if term or trunc:
                break
        while not (term or trunc) and not self._actionable():
            r, term, trunc = self._frame(0, -1)
            total += r
        info = self._info()
        if term or trunc:
            self._match_ended(info)
        return self.env.obs[0, self.side].copy(), total, term, trunc, info

    def _info(self):
        i = self.env.info[0]
        return {'frame': int(i['frame']), 'winner': int(i['winner']),
                'rounds_won': [int(x) for x in i['rounds_won']],
                'episode_return': float(i['episode_return'][self.side]),
                'chars': [int(x) for x in i['chars']], 'stage': int(i['stage'])}

    # --- Matches.

    def _match_ended(self, info):
        self.matches += 1
        won = 0 if info['winner'] < 0 else (1 if info['winner'] == self.side else -1)
        self.results.append(won)
        self.save(info)
        if self.window is not None and self.result_seconds > 0:
            you = {1: 'You lose', -1: 'You win', 0: 'Time'}[won]
            agent_wins = sum(r == 1 for r in self.results)
            human_wins = sum(r == -1 for r in self.results)
            end = time.perf_counter() + self.result_seconds
            while time.perf_counter() < end:
                self.window.message(you, f'You {human_wins} - {agent_wins} agent')
                time.sleep(1 / 30)

    def save(self, info):
        """Writes the match just played: <record_dir>/<time>.npz and .json."""
        if not self.record_dir or not self._frames:
            return None
        os.makedirs(self.record_dir, exist_ok=True)
        stamp = datetime.datetime.now().strftime('%Y%m%d-%H%M%S')
        path = os.path.join(self.record_dir, f'{stamp}-{self.matches:03d}')
        obs, controls, screen, decision, reward = zip(*self._frames)
        np.savez_compressed(
            path + '.npz',
            obs=np.stack(obs).astype(np.float32),          # (T, 2, obs_dim): each player's view before the frame
            controls=np.stack(controls).astype(np.uint8),  # (T, 2): the bytes the library got (relative)
            human_screen=np.asarray(screen, np.uint8),     # (T,): the human's, as on screen
            agent_action=np.asarray(decision, np.int16),   # (T,): the agent's action index where it chose, else -1
            reward=np.stack(reward).astype(np.float32),    # (T, 2)
            final_obs=self.env.obs[0].copy())
        meta = dict(info, human=self.human, agent=self.side, opponent=self.opponent,
                    agent_name=self.agent_name, frame_skip=self.frame_skip,
                    frames=len(self._frames), fps=FPS,
                    actions=[self.table.describe(i) for i in range(len(self.table))],
                    observation_names=self.env.observation_names,
                    date=datetime.datetime.now().isoformat(timespec='seconds'))
        with open(path + '.json', 'w', encoding='utf-8') as f:
            json.dump(meta, f, indent=1)
        self._frames = []
        return path

    def play(self, policy=None, matches=None):
        """Plays matches until Esc (or `matches` of them): policy(obs) -> action index for
        the agent's side (None: it stands still; ignored against the CPU). A policy with a
        reset() (efz_env.agent.Agent) is told of each new match."""
        try:
            while matches is None or self.matches < matches:
                obs = self.reset()
                if hasattr(policy, 'reset'):
                    policy.reset()
                while True:
                    action = 0 if policy is None or self.opponent == 'cpu' else policy(obs)
                    obs, _, term, trunc, _ = self.agent_step(action)
                    if term or trunc:
                        break
        except Quit:
            pass
        return self.results

    def close(self):
        self.env.close()
        if self.window is not None:
            self.window.pygame.quit()


try:
    from gymnasium import spaces
    from stable_baselines3.common.callbacks import BaseCallback
    from stable_baselines3.common.vec_env.base_vec_env import VecEnv
except ImportError:  # learning from human games needs stable-baselines3
    VecEnv = None

if VecEnv is not None:
    class HumanVecEnv(VecEnv):
        """SB3's VecEnv of one HumanMatch: the agent learns (PPO, ...) from matches
        against the human, in real time. Esc ends training (Quit from learn())."""

        def __init__(self, match):
            self.match = match
            obs_space = spaces.Box(-np.inf, np.inf, (match.env.obs_dim,), np.float32)
            super().__init__(1, obs_space, spaces.Discrete(len(match.table)))
            self._action = 0
            self._length = 0

        def reset(self):
            self._length = 0
            return self.match.reset()[None]

        def step_async(self, actions):
            self._action = int(np.asarray(actions).reshape(-1)[0])

        def step_wait(self):
            obs, reward, term, trunc, info = self.match.agent_step(self._action)
            self._length += 1
            info = dict(info)
            done = term or trunc
            if done:
                info['terminal_observation'] = obs
                info['TimeLimit.truncated'] = trunc and not term
                info['episode'] = {'r': info['episode_return'], 'l': self._length, 't': 0.0}
                obs = self.reset()[0]
            return obs[None], np.array([reward], np.float32), np.array([done]), [info]

        def close(self):
            self.match.close()

        def get_attr(self, attr_name, indices=None):
            return [getattr(self, attr_name)]

        def set_attr(self, attr_name, value, indices=None):
            setattr(self, attr_name, value)

        def env_method(self, method_name, *args, indices=None, **kwargs):
            return [getattr(self, method_name)(*args, **kwargs)]

        def env_is_wrapped(self, wrapper_class, indices=None):
            return [False]

    class LearningNotice(BaseCallback):
        """Says in the window that the agent is learning while SB3 updates it."""

        def __init__(self, match):
            super().__init__()
            self.match = match

        def _on_rollout_end(self):
            if self.match.window is not None:
                self.match.window.message('Learning from your games...')

        def _on_step(self):
            return True
