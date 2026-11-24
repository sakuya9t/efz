"""The kinds of module (python/efz_env/modules.py) an agent of runs/human-ayu can be made
of, registered by importing this: what an agent.json's "code": "agent_modules" names, and
what play.py --module and evaluate.py --p1-module know.

    routes    combo_support.py: its combos from people's library, once it sees its hit
    oki       okizeme.py: people's okizeme (the clone's play) while it sees the opponent down
    okiplan   okiplan.py: people's okizeme tried on copies of the game from its knockdown,
              one chosen by what the opponent has shown
    pressplan pressplan.py: people's follow-ups to a guarded move, tried and chosen the same way
    airplan   airplan.py: people's catches of an opponent that recovers in the air out of a
              combo, tried and chosen the same way
    jumpplan  airplan.py: people's answers to a jump at the agent, tried and chosen the same way
    endplan   airplan.py: the end of a combo on an opponent that can recover in the air (off
              unless named; measured without a gain, docs/training-v2-log.md)
    cancel    cancel.py: a risky move it sees guarded, cancelled with an Instant Charge
    rise      rise.py: its own wake-up guarded through once its wake-up moves have cost it
              in this match
    risk      risk.py: a raw special of its own play, let out or stopped at its input by how
              that move has paid in this match (the last of the modules)
    who       who.py: a measure: which module's steps a named move's inputs were
"""

import combo_support  # noqa: F401  (registers 'routes')
import okizeme  # noqa: F401  (registers 'oki')
import okiplan  # noqa: F401  (registers 'okiplan')
import pressplan  # noqa: F401  (registers 'pressplan')
import airplan  # noqa: F401  (registers 'airplan', 'jumpplan', 'endplan')
import cancel  # noqa: F401  (registers 'cancel')
import rise  # noqa: F401  (registers 'rise')
import risk  # noqa: F401  (registers 'risk')
import who  # noqa: F401  (registers 'who')
