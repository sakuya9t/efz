"""Unpacks an agent file (.efzagent) into the files it was made from, to train it further
or work on it with the tools here (docs/agents.md, "Working on from an agent file").

    python python/examples/unpack_agent.py agents/ayu.efzagent              # -> agents/ayu/
    python python/examples/unpack_agent.py agents/ayu.efzagent --out work/ayu

    work/ayu/model.zip            the model (Stable-Baselines3 PPO)
    work/ayu/config.json          its settings (frame_skip, history, delay, its training's)
    work/ayu/combo-library.npz    its routes as a combo library, with their join points
    work/ayu/combo-library.marks.json   (if the file has routes and keeps their damage)
    work/ayu/packed.json          what the file was: its name, version, modules, SHA-256

then, as with any model:

    python runs/human-ayu/finetune.py --start work/ayu/model.zip --out runs/mine ...
    python runs/human-ayu/evaluate.py --p1 work/ayu/model.zip --p1-assist work/ayu/combo-library.npz ...
    python python/examples/play.py --agent work/ayu/model.zip --assist work/ayu/combo-library.npz
    python python/examples/export_agent.py runs/mine/avg.zip --parts-from agents/ayu.efzagent

(the last: the model trained further, packed again with the file's routes and chooser as
they are). The tools also take the agent file itself where they take a model.zip, and
unpack it for themselves.

The model is made anew from the file's numbers: nothing in the file is run, so a file from
anyone can be unpacked. A file written with its training part (the exporter's default
since 15 November) gives the model whole: the same weights to the last bit, the critic
too. An older one has only the actor: the critic is made new, and training from it has to
teach the value again first (finetune.py's first chunks: a small learning rate).
Needs stable-baselines3, torch and the efz_env library.
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

from efz_env.export import unpack_agent

POLICY_MOST = 1e-3  # (log-probability)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('agent', help='an agent file (.efzagent)')
    p.add_argument('--out', help="the folder (default: beside the file, of its name)")
    args = p.parse_args()
    out = args.out or os.path.splitext(os.path.abspath(args.agent))[0]
    try:
        got = unpack_agent(args.agent, out)
    except (ValueError, KeyError) as e:
        sys.exit(f'{args.agent}: {e}')
    if got['policy'] is not None and got['policy'] > POLICY_MOST:
        sys.exit(f"{got['model']}: its log-probabilities differ from the file's by up to "
                 f"{got['policy']:.2g}")
    critic = ('the critic too' if got['critic'] == 'file' else
              'the actor only: the file has no training part, the critic is new')
    print(f"{got['model']}: the file's model, {critic}"
          + (", the optimizer's moments" if got['optimizer'] else '')
          + f" (log-probabilities within {got['policy']:.1g} of the file's)")
    print(f"{got['config']}: its settings")
    if got['library']:
        print(f"{got['library']}: its routes, as a combo library (--assist)")
    else:
        print('no combo library: the file has no routes, or (an older file) not their damage; '
              'pack again with export_agent.py --parts-from to keep them')


if __name__ == '__main__':
    main()
