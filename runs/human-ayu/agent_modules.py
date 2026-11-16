"""The kinds of module (python/efz_env/modules.py) an agent of runs/human-ayu can be made
of, registered by importing this: what an agent.json's "code": "agent_modules" names, and
what play.py --module and evaluate.py --p1-module know.

    routes    combo_support.py: its combos from people's library, once it sees its hit
    oki       okizeme.py: people's okizeme (the clone's play) while it sees the opponent down
    okiplan   okiplan.py: people's okizeme tried on copies of the game from its knockdown,
              one chosen by what the opponent has shown
"""

import combo_support  # noqa: F401  (registers 'routes')
import okizeme  # noqa: F401  (registers 'oki')
import okiplan  # noqa: F401  (registers 'okiplan')
import pressplan  # noqa: F401  (registers 'pressplan')
