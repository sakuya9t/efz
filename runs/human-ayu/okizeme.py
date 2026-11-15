"""The okizeme module (python/efz_env/modules.py; the kind 'oki' of an agent.json, of
play.py --module and evaluate.py --p1-module): while the agent sees its opponent knocked
down, another player's play in its place.

    oki:model=runs/human-ayu/bc-d14.zip[,after=4]

Why: the agent's okizeme is one move (round 15's: a low in 72-84% of its okizeme, a high
in 3-12%, an object out in 1-7%; people's Ayu 40% / 38% / 30%), and against opponents who
reverse as they rise it loses HP (docs/training-v2.md, "Round 16"). People's clone
(bc-d14.zip), in the same situations, has people's mix. The module is efz_env.modules's
Switch: from the step the agent sees the opponent down (its action one of tactics.DOWN:
lying, the knockdowns, rising; seen `delay` steps late, so it lasts until `delay` steps
after the opponent is up: the okizeme's contact is inside) and `after` steps more, the
clone's actions are played, the clone seeing every step and every input as late as it was
trained to. It ends at once when the agent sees itself hit, and (unless through_combo)
while it sees its own combo counted: its combo is its own, or the routes', asked before
it. What it sees is `delay` steps old, so with that the okizeme begins `delay` steps
after the combo's count is gone; through_combo begins it as soon as the opponent is seen
down, the routes still first while they play.
"""

import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))

from efz_env import modules

import tactics

OPP_ACTION, SELF_HITSTUN, SELF_COMBO_HITS = 50, 20, 30
DOWN = frozenset(tactics.DOWN)


def down(view):
    """The player sees its opponent knocked down (or rising)."""
    return int(round(float(view[OPP_ACTION]))) in DOWN


def over(view):
    """The player sees its own combo counted, or itself hit: not the okizeme's step."""
    return view[SELF_COMBO_HITS] > 0 or view[SELF_HITSTUN] > 0


def hit(view):
    """The player sees itself hit."""
    return view[SELF_HITSTUN] > 0


@modules.register('oki')
def okizeme(agent, where, files, options, data):
    """files: model (the player whose okizeme it is: people's clone). options: after (the
    steps it goes on once the opponent is seen up, default 4), through_combo (above;
    default false), deterministic."""
    from efz_env.agent import Agent
    player = Agent(files['model'], deterministic=bool(options.get('deterministic', False)))
    if player.delay != agent.delay:
        raise ValueError(f"oki: {files['model']} sees the game {player.delay} steps late, the "
                         f'agent {agent.delay}')
    return modules.Switch('oki', player, down, after=int(options.get('after', 4)),
                          until=hit if options.get('through_combo') else over)
