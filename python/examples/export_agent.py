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

The file also carries what training needs beyond what a game plays (the critic, the
model's config.json, PPO's settings; --optimizer: Adam's moments too, three times the size),
so that anyone can unpack it and train it further (unpack_agent.py); --no-train leaves that
out (half the size, a file only to play). --parts-from FILE.efzagent: the routes and chooser
of that agent file, as they are, for a model without its library at hand (a packed agent
trained further and packed again; --keep routes: without its chooser).

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
            print(f'  {k} = {v if len(v) <= 200 else v[:200] + f"... ({len(v)} characters)"}')
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
    p.add_argument('--ending', type=int, metavar='HP',
                   help="what a knockdown at a combo's end is worth to the planner over any "
                        "other end (default: damage alone, or the pack's, or the "
                        "--parts-from file's)")
    p.add_argument('--confirm', type=int, metavar='STEPS',
                   help="its routes begin this many steps after its hit instead of its delay: "
                        "a combo confirmed before it has seen the hit. For the opponents an "
                        "agent trains and is measured against (their own play before a route "
                        "begins does not carry people's combos); never for an agent that is "
                        "to play within a person's limits")
    p.add_argument('--no-train', dest='train', action='store_false',
                   help="without the training part (the critic, config.json, PPO's settings): "
                        "a file to play, not to train further")
    p.add_argument('--optimizer', action='store_true',
                   help="the training part with Adam's moments too")
    p.add_argument('--parts-from', metavar='FILE.efzagent',
                   help="a model's routes and chooser from this agent file, as they are")
    p.add_argument('--okizeme', metavar='LIBRARY.npz',
                   help="its okizeme planned in the game from this library of people's "
                        "(runs/human-ayu/oki_library.py's, its .answers.json beside it: "
                        "oki_library.py --answers)")
    p.add_argument('--okizeme-option', action='append', default=[], metavar='KEY=VALUE',
                   help="the game's okizeme planner's settings (efz_env.export.OKI_OPTIONS: "
                        "per_plan, window, think, skip, doubt, ...)")
    p.add_argument('--pressure', metavar='LIBRARY.npz',
                   help="its pressure after a guarded move planned in the game from this "
                        "library of people's (runs/human-ayu/pressure_library.py's, its "
                        ".answers.json beside it: pressure_library.py --answers)")
    p.add_argument('--pressure-option', action='append', default=[], metavar='KEY=VALUE',
                   help="the game's pressure planner's settings (efz_env.export.PRESS_OPTIONS)")
    p.add_argument('--air-throw', action='store_true',
                   help="in the game it air-throws an opponent that recovers in the air out "
                        "of its combo, when a throw catches inside the recovery (the module "
                        "airthrow:1; runs/human-ayu/airplan.py's sure throw: no library)")
    p.add_argument('--rise', action='store_true',
                   help="in the game it guards its own rising by sight when it sees the "
                        "attacker on it, as often as guarding has paid in the match (the "
                        "module rise:1; runs/human-ayu/rise.py's guard)")
    p.add_argument('--rise-option', action='append', default=[], metavar='KEY=VALUE',
                   help="its settings (efz_env.export.RISE_OPTIONS)")
    p.add_argument('--risk', action='store_true',
                   help="in the game a raw special of its own play is let out or stopped at "
                        "its input by how that move has paid in the match (the module risk:1; "
                        "runs/human-ayu/risk.py, whose moves and priors it takes)")
    p.add_argument('--risk-option', action='append', default=[], metavar='KEY=VALUE',
                   help="its settings (efz_env.export.RISK_OPTIONS), or a move's name for its "
                        "prior (623B=-326)")
    p.add_argument('--keep', nargs='+',
                   choices=('routes', 'chooser', 'okiplan', 'pressplan', 'airthrow', 'rise', 'risk'),
                   default=['routes', 'chooser', 'okiplan', 'pressplan', 'airthrow', 'rise', 'risk'],
                   help='--parts-from: which of them')
    args = p.parse_args()
    if args.show:
        return show(args.model)

    try:
        read_pack(args.model)
        pack = True
    except ValueError:
        pack = False
    if pack:
        if args.library or args.chooser or args.victims or args.parts_from:
            sys.exit('--library, --chooser, --victims, --parts-from: a pack has its own '
                     '(--drop to leave them out)')
        print(f'{args.model}, a pack:')
        try:
            out, check, _ = export_pack(args.model, args.out, name=args.name,
                                        version=args.version, character=args.char,
                                        drop=args.drop, replan=args.replan,
                                        per_start=args.per_start, train=args.train,
                                        optimizer=args.optimizer, ending=args.ending)
        except ValueError as e:
            sys.exit(str(e))
    else:
        if args.drop:
            sys.exit('--drop: of a pack')
        if args.chooser and not args.library:
            sys.exit('--chooser: the chooser of a --library')
        if args.victims and not args.library:
            sys.exit('--victims: the routes of a --library')
        if args.parts_from and (args.library or args.chooser):
            sys.exit('--parts-from: the routes and chooser of that file, or --library and '
                     '--chooser, not both')
        model = args.model
        name = args.name
        if name is None:
            stem = os.path.splitext(os.path.basename(model))[0]
            folder = os.path.basename(os.path.dirname(os.path.abspath(model)))
            name = folder if stem in ('avg', 'model', 'best') and folder else stem
        file = f'{name}-{args.version}' if args.version else name
        out = args.out or os.path.join(os.path.dirname(os.path.abspath(model)), file + '.efzagent')
        rise = None
        if args.rise or args.rise_option:
            from efz_env.export import RISE_OPTIONS
            rise = {}
            for kv in args.rise_option:
                k, _, v = kv.partition('=')
                if k not in RISE_OPTIONS:
                    sys.exit(f"--rise-option {k}: one of {', '.join(RISE_OPTIONS)}")
                rise[k] = type(RISE_OPTIONS[k])(v)
        risk = None
        if args.risk or args.risk_option:
            from efz_env.export import RISK_OPTIONS
            sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(
                os.path.abspath(__file__)))), 'runs', 'human-ayu'))
            import risk as risk_module  # (the moves and their priors)
            priors = dict(risk_module.PRIORS)
            risk = {}
            for kv in args.risk_option:
                k, _, v = kv.partition('=')
                if k in risk_module.MOVES:
                    priors[k] = float(v)
                elif k == 'jump':  # (the jump's account: its starting worth, HP a jump)
                    risk[k] = float(v)
                elif k in RISK_OPTIONS:
                    risk[k] = type(RISK_OPTIONS[k])(v)
                else:
                    sys.exit(f"--risk-option {k}: one of {', '.join(RISK_OPTIONS)}, or a move "
                             f"({', '.join(risk_module.MOVES)})")
            risk['moves'] = {risk_module.MOVES[k]: w for k, w in priors.items()}
        okiplan = None
        if args.okizeme:
            from efz_env.export import OKI_OPTIONS
            okiplan = dict(library=args.okizeme)
            for kv in args.okizeme_option:
                k, _, v = kv.partition('=')
                if k not in OKI_OPTIONS:
                    sys.exit(f"--okizeme-option {k}: one of {', '.join(OKI_OPTIONS)}")
                okiplan[k] = type(OKI_OPTIONS[k])(v)
        elif args.okizeme_option:
            sys.exit('--okizeme-option: the planner of an --okizeme library')
        pressplan = None
        if args.pressure:
            from efz_env.export import PRESS_OPTIONS
            pressplan = dict(library=args.pressure)
            for kv in args.pressure_option:
                k, _, v = kv.partition('=')
                if k not in PRESS_OPTIONS:
                    sys.exit(f"--pressure-option {k}: one of {', '.join(PRESS_OPTIONS)}")
                pressplan[k] = type(PRESS_OPTIONS[k])(v)
        elif args.pressure_option:
            sys.exit('--pressure-option: the planner of a --pressure library')
        try:
            check = export_agent(model, out, name=name, character=args.char, library=args.library,
                                 victims=args.victims, replan=bool(args.replan),
                                 per_start=args.per_start, chooser=args.chooser,
                                 version=args.version, train=args.train,
                                 optimizer=args.optimizer, parts_from=args.parts_from,
                                 keep=tuple(args.keep), ending=args.ending,
                                 confirm=args.confirm,
                                 okiplan=okiplan, pressplan=pressplan,
                                 airthrow={} if args.air_throw else None, rise=rise,
                                 risk=risk)
        except ValueError as e:
            sys.exit(str(e))
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
    if agent.oki:
        combos += f"; its okizeme planned from {agent.oki} of people's"
    if agent.press:
        combos += f"; its pressure planned from {agent.press} of people's"
    if getattr(agent, 'airthrow', False):
        combos += "; an air throw of an air recovery when one catches inside it"
    if getattr(agent, 'rise', False):
        combos += "; its rising guarded by sight when the attacker is on it"
    if getattr(agent, 'risk', False):
        combos += "; its raw specials let out or stopped by how each has paid in the match"

    label = agent.name + (f' {agent.version}' if agent.version else '')
    sure = f"log-probabilities within {check['policy']:.1g}"
    if check['chooser'] is not None:
        sure += f", the chooser's values within {check['chooser']:.1g} HP"
    work = ('with its training part (unpack_agent.py: to train it further)' if args.train
            else 'without its training part (to play only)')
    print(f'{out} ({os.path.getsize(out) / 1e6:.1f} MB): "{label}", {agent.modules}, {work}; '
          f'{combos}. The same as the model ({sure}). Copy it into the game\'s agents folder.')
    agent.close()


if __name__ == '__main__':
    main()
