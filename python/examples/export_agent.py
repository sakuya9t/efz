"""Writes a trained agent as an agent file (.efzagent) for the game, which plays it on
character select and in netplay (docs/agents.md).

    python python/examples/export_agent.py tmp/efz-round15-pack.zip      # with the pack's routes
    python python/examples/export_agent.py tmp/round15/agent-league15-s1/avg.zip \
        --library tmp/round15/combo-library-victims.npz --out agents/ayu15.efzagent

The model is a model.zip from train.py or finetune.py, with its config.json beside it
(frame_skip, history, delay), or a pack (play.py's). --library: its combos from that
library's routes, as play.py --assist plays them (a pack's library, unless --no-routes);
--victims: only against those characters (play.py --assist-victims). The file goes to
--out, by default beside the model as <name>.efzagent; copy it into the `agents` folder
of the game's folder (or of its save folder). The file is checked: run in the library,
its log-probabilities must be the model's. Needs stable-baselines3 and the efz_env
library.
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))
sys.path.insert(0, HERE)

from efz_env.export import export_agent


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('model', help='a model.zip (with its config.json), or a pack')
    p.add_argument('--out', help='the agent file (default: beside the model, <name>.efzagent)')
    p.add_argument('--name', help="what the game shows (default: the model's folder)")
    p.add_argument('--char', help="the character it plays (default: its training's first)")
    p.add_argument('--library', metavar='LIBRARY.npz',
                   help="its combos from this library's routes (play.py --assist's)")
    p.add_argument('--victims', nargs='+', metavar='CHAR',
                   help='the routes only against these characters (play.py --assist-victims)')
    p.add_argument('--no-routes', action='store_true',
                   help="a pack's agent with its own combos, not the pack's routes")
    args = p.parse_args()
    model, library = args.model, args.library
    if os.path.isfile(model):
        from play import unpack
        pack = unpack(model)
        if pack:
            model = pack[0]
            library = library or pack[1]
            print(f'pack: its model {model}' + (f', its library {pack[1]}' if pack[1] else ''))
    if args.no_routes:
        library = None
    if args.victims and not library:
        sys.exit('--victims: the routes of a --library')
    name = args.name
    if name is None:
        stem = os.path.splitext(os.path.basename(model))[0]
        folder = os.path.basename(os.path.dirname(os.path.abspath(model)))
        name = folder if stem in ('avg', 'model', 'best') and folder else stem
    out = args.out or os.path.join(os.path.dirname(os.path.abspath(model)), name + '.efzagent')
    diff = export_agent(model, out, name=name, character=args.char, library=library,
                        victims=args.victims)
    if diff > 1e-3:
        sys.exit(f'{out}: its log-probabilities differ from the model\'s by up to {diff:.2g}')
    from efz_env.export import NativeAgent
    agent = NativeAgent(out)
    combos = (f'its combos from {agent.routes} routes of {os.path.basename(library)}'
              if agent.routes else 'its own combos')
    agent.close()
    print(f'{out} ({os.path.getsize(out) / 1e6:.1f} MB): "{name}", {combos}; the same as the '
          f'model (log-probabilities within {diff:.1g}). Copy it into the game\'s agents folder.')


if __name__ == '__main__':
    main()
