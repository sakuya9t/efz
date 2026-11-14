"""Writes a trained agent as an agent file (.efzagent) for the game, which plays it on
character select and in netplay (docs/agents.md).

    python python/examples/export_agent.py tmp/round15/agent-league15-s1/avg.zip
    python python/examples/export_agent.py tmp/efz-round15-pack.zip --out agents/ayu15.efzagent

The model is a model.zip from train.py or finetune.py, with its config.json beside it
(frame_skip, history, delay), or a pack (play.py's). The file goes to --out, by default
beside the model as <name>.efzagent; copy it into the `agents` folder of the game's
folder (or of its save folder). The file is checked: run in the library, its
log-probabilities must be the model's. Needs stable-baselines3 and the efz_env library.
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
    args = p.parse_args()
    model = args.model
    if os.path.isfile(model):
        from play import unpack
        pack = unpack(model)
        if pack:
            model = pack[0]
            print(f'pack: its model {model}')
    name = args.name
    if name is None:
        stem = os.path.splitext(os.path.basename(model))[0]
        folder = os.path.basename(os.path.dirname(os.path.abspath(model)))
        name = folder if stem in ('avg', 'model', 'best') and folder else stem
    out = args.out or os.path.join(os.path.dirname(os.path.abspath(model)), name + '.efzagent')
    diff = export_agent(model, out, name=name, character=args.char)
    if diff > 1e-3:
        sys.exit(f'{out}: its log-probabilities differ from the model\'s by up to {diff:.2g}')
    print(f'{out} ({os.path.getsize(out) / 1e6:.1f} MB): "{name}"; the same as the model '
          f'(log-probabilities within {diff:.1g}). Copy it into the game\'s agents folder.')


if __name__ == '__main__':
    main()
