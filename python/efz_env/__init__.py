"""efz_env: headless EFZ for training agents.

Batches of matches of the recovered game (the same as the original's, tick for tick),
run in C++ on every core without a window or sound. See docs/headless.md.

    from efz_env import EfzVecEnv, actions
    env = EfzVecEnv('/path/to/EFZ', num_envs=256)
    table = actions.ActionTable()
    obs = env.reset()
    obs, reward, terminated, truncated, info = env.step(table.to_bytes(indices))

For the training frameworks (each imported on its own, needing only its framework):
efz_env.gym (Gymnasium: EfzVsCpu, EfzVsCpuEnv, registered as efz/VsCpu-v0),
efz_env.sb3 (Stable-Baselines3: against the CPU, in self-play or against a frozen
policy), efz_env.pettingzoo (one match, both players agents) and efz_env.human (playing
it yourself in a window, recorded; an agent can learn from those matches). Scripts:
python/examples/train.py and play.py.
"""

from . import actions
from .actions import ActionTable
from .vec import STAGES, EfzVecEnv, character_names

__all__ = ['EfzVecEnv', 'ActionTable', 'actions', 'character_names', 'STAGES']
