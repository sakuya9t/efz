"""The kinds of module (python/efz_env/modules.py) an agent of runs/human-ayu can be made
of, registered by importing this: what an agent.json's "code": "agent_modules" names, and
what play.py --module and evaluate.py --p1-module know.

    routes    combo_support.py: its combos from people's library, once it sees its hit
"""

import combo_support  # noqa: F401  (registers 'routes')
