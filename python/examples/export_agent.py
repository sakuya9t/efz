"""Writes a trained agent as an agent file (.efzagent) for the game, which plays it on
character select and in netplay (docs/agents.md): everything the agent plays with, in the
one file.

    python python/examples/export_agent.py tmp/efz-round15b-pack.zip      # a pack, all of it
    python python/examples/export_agent.py tmp/round15/agent-league15-s1/avg.zip \
        --library tmp/round15/combo-library-victims.npz --out agents/ayu15.efzagent
    python python/examples/export_agent.py --show agents/ayu15.efzagent    # what one holds

A pack (play.py's zip carrying an agent by hand) goes in whole: its model, its combo
library's routes, the library's join points and its chooser, played as the pack's play.py
plays them (an agent.json in it says how; else with join points planned again at each new
move's hit, 24 routes a plan, as round 15b's; without, once at the first hit, 12, as round
15's). Each of its files is listed with what became of it; one an agent file can't carry
stops the export, unless --drop names it (or a part: routes, chooser, marks). The version
the game shows beside the name is the pack's (efz-round15b-pack.zip: round15b) unless
--version.

A model is a model.zip from train.py or finetune.py, with its config.json beside it
(frame_skip, history, delay): --library its combos from that library's routes (its join
points beside it), --chooser that library's chooser, --replan planned again at each new
move's hit.

The file goes to --out (default beside the model or pack, as NAME-VERSION.efzagent); copy it
into the `agents` folder of the game's folder (or of its save folder). It is checked: run in
the library, its log-probabilities must be the model's, its chooser's values the chooser's.
Needs stable-baselines3, torch and the efz_env library.
"""

import argparse
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

from efz_env.export import export_agent, export_pack, read_header, read_pack

POLICY_MOST, CHOOSER_MOST = 1e-3, 1.0  # (log-probability; HP)


def show(path):
    fmt, keys, tensors = read_header(path)
    print(f'{path}: an agent file of format {fmt}, {os.path.getsize(path) / 1e6:.1f} MB')
    skip = {'table'}
    for k, v in keys.items():
        if k not in skip:
            print(f'  {k} = {v}')
    print(f'  {len(tensors)} tensors: ' +
          ', '.join(f'{n} {"x".join(map(str, d))}' for n, d in tensors.items()))


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('model', help='a pack, or a model.zip (with its config.json); with --show '
                                 'an agent file')
    p.add_argument('--show', action='store_true', help="print an agent file's header and stop")
    p.add_argument('--out', help='the agent file (default: beside the model, '
                                 'NAME-VERSION.efzagent)')
    p.add_argument('--name', help="what the game shows (default: the model's folder)")
    p.add_argument('--version', help="shown beside the name (default: a pack's name)")
    p.add_argument('--char', help="the character it plays (default: its training's first)")
    p.add_argument('--drop', nargs='+', default=[], metavar='PART',
                   help="of a pack, leave these out: files in it, or parts (routes, chooser, "
                        "marks)")
    p.add_argument('--library', metavar='LIBRARY.npz',
                   help="a model's combos from this library's routes (play.py --assist's)")
    p.add_argument('--victims', nargs='+', metavar='CHAR',
                   help='the routes only against these characters (play.py --assist-victims)')
    p.add_argument('--chooser', metavar='CHOOSER.pt',
                   help="the library's chooser (combo_net.py's), played when a plan is late")
    plan = p.add_mutually_exclusive_group()
    plan.add_argument('--replan', action='store_true', default=None,
                      help="planned again at each new move's hit (round 15b's)")
    plan.add_argument('--once', dest='replan', action='store_false',
                      help='planned once, at the first hit (round 15\'s)')
    p.add_argument('--per-start', type=int, help='routes tried a plan (default 12, '
                                                 'replanning 24)')
    args = p.parse_args()
    if args.show:
        return show(args.model)

    try:
        read_pack(args.model)
        pack = True
    except ValueError:
        pack = False
    if pack:
        if args.library or args.chooser or args.victims:
            sys.exit('--library, --chooser, --victims: a pack has its own (--drop to leave '
                     'them out)')
        print(f'{args.model}, a pack:')
        try:
            out, check, _ = export_pack(args.model, args.out, name=args.name,
                                        version=args.version, character=args.char,
                                        drop=args.drop, replan=args.replan,
                                        per_start=args.per_start)
        except ValueError as e:
            sys.exit(str(e))
    else:
        if args.drop:
            sys.exit('--drop: of a pack')
        if args.chooser and not args.library:
            sys.exit('--chooser: the chooser of a --library')
        if args.victims and not args.library:
            sys.exit('--victims: the routes of a --library')
        model = args.model
        name = args.name
        if name is None:
            stem = os.path.splitext(os.path.basename(model))[0]
            folder = os.path.basename(os.path.dirname(os.path.abspath(model)))
            name = folder if stem in ('avg', 'model', 'best') and folder else stem
        file = f'{name}-{args.version}' if args.version else name
        out = args.out or os.path.join(os.path.dirname(os.path.abspath(model)), file + '.efzagent')
        check = export_agent(model, out, name=name, character=args.char, library=args.library,
                             victims=args.victims, replan=bool(args.replan),
                             per_start=args.per_start, chooser=args.chooser,
                             version=args.version)
    bad = []
    if check['policy'] > POLICY_MOST:
        bad.append(f"its log-probabilities differ from the model's by up to {check['policy']:.2g}")
    if check['chooser'] is not None and check['chooser'] > CHOOSER_MOST:
        bad.append(f"its chooser's values differ from the chooser's by up to "
                   f"{check['chooser']:.2g} HP")
    if bad:
        sys.exit(f'{out}: ' + '; '.join(bad))
    from efz_env.export import NativeAgent
    agent = NativeAgent(out)
    combos = 'its own combos'
    if agent.routes:
        combos = (f'its combos from {agent.routes} routes, planned '
                  + ('again at each new move\'s hit' if agent.replan else 'at the first hit')
                  + (f' ({agent.pool - agent.routes} joined at a later move)'
                     if agent.pool > agent.routes else '')
                  + ('; the chooser\'s when a plan is late' if agent.chooser else ''))
    label = agent.name + (f' {agent.version}' if agent.version else '')
    sure = f"log-probabilities within {check['policy']:.1g}"
    if check['chooser'] is not None:
        sure += f", the chooser's values within {check['chooser']:.1g} HP"
    print(f'{out} ({os.path.getsize(out) / 1e6:.1f} MB): "{label}", {agent.modules}; {combos}. '
          f'The same as the model ({sure}). Copy it into the game\'s agents folder.')
    agent.close()


if __name__ == '__main__':
    main()
