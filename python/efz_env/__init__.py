"""efz_env: headless EFZ for training agents.

Batches of matches of the recovered game (the same as the original's, tick for tick),
run in C++ on every core without a window or sound. See docs/headless.md.

    from efz_env import EfzVecEnv, actions
    env = EfzVecEnv('/path/to/EFZ', num_envs=256)
    table = actions.ActionTable()
    obs = env.reset()
    obs, reward, terminated, truncated, info = env.step(table.to_bytes(indices))

efz_env.gym.EfzVsCpu is Gymnasium's vector API for one agent against the game's CPU.
"""

from . import actions
from .actions import ActionTable
from .vec import STAGES, EfzVecEnv, character_names

__all__ = ['EfzVecEnv', 'ActionTable', 'actions', 'character_names', 'STAGES']
