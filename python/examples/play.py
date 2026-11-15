"""Plays against an agent, or the game's CPU, in a window; every match is recorded.

    python python/examples/play.py --agent runs/self/model.zip
    python python/examples/play.py --cpu --cpu-level 4 --chars ayu mai

    python python/examples/play.py --agent runs/human-ayu/model.zip --assist combo-library.npz

Keys: arrows, Z X C V for A B C D (--keys to change them), or a gamepad; Esc stops.
You are player 2 unless --side 1. Matches go to --record (default recordings/) as
.npz + .json (efz_env.human). Needs pygame-ce; an --agent needs stable-baselines3.

--assist: the agent's combos from built-in routes (runs/human-ayu/combo_support.py's
LiveRoutes): once it sees its hit, as late as it sees everything, people's combos from the
library (runs/human-ayu/combo_library.py's) that begin with the move that hit are tried on
copies of the game and the most damaging is played, if it beats the agent's own play.
It plans again at each new move's hit it sees, the rest of the route it is on one of the
options and the library's combos joined where that move hit in them (the library's
.marks.json beside it), so a route that doesn't fit where the players are is left for one
that does; --assist-once for a plan at the first hit only.
With --chooser (runs/human-ayu/combo_net.py's chooser.pt, trained for that agent and
library) nothing is tried on copies: a network says from the agent's view which combo to
play (ChosenRoutes): no second process, a little less damage.

--agent also takes a pack: a zip made to carry an agent by hand, holding its model
(FOLDER/avg.zip with its config.json) and, for its combos, a library (.npz) and a chooser
(chooser.pt). It is unpacked once into the folder of its name beside it, and the agent
plays with the pack's routes unless --no-assist; --chooser alone means the pack's.

    python python/examples/play.py --agent tmp/efz-round15-pack.zip --chars ayu kano

The routes are a module of the agent (python/efz_env/modules.py): a part that takes its
inputs over in some situation. A pack says what its agent is made of in its agent.json
(the model, the modules in the order they are asked, their files); a pack without one is
its model and, if it holds a library, the routes. --module KIND:key=value,... adds a module
(or replaces the pack's of that kind; a value that is a file's path is one of its files),
--no-module KIND leaves one out; --assist, --chooser and --no-assist are the routes' own
words for the same. The kinds are runs/human-ayu/agent_modules.py's.
"""

import argparse
import json
import os
import shutil
import sys
import zipfile

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.dirname(HERE))

from efz_env.human import HumanMatch


def unpack(path):
    """A pack's model, combo library, chooser and agent.json (see above; None where it has
    none), unpacked into the folder of the pack's name beside it; None if `path` is not a
    pack (a model's zip has `data`)."""
    if not zipfile.is_zipfile(path):
        return None
    with zipfile.ZipFile(path) as z:
        names = [n for n in z.namelist() if not n.endswith('/') and '..' not in n.split('/')]
        models = sorted((n for n in names if n.endswith('.zip')),
                        key=lambda n: (not n.endswith('avg.zip'), n))
        if 'data' in names or not models:
            return None
        # What lies beside the model's folder; a pack may hold other things (code).
        root = '/'.join(models[0].split('/')[:-2])
        root += '/' * bool(root)
        out = os.path.splitext(path)[0]
        found = {}
        for n in names:
            if not n.startswith(root):
                continue
            dest = os.path.join(out, *n[len(root):].split('/'))
            if not (os.path.exists(dest) and os.path.getsize(dest) == z.getinfo(n).file_size):
                os.makedirs(os.path.dirname(dest), exist_ok=True)
                with z.open(n) as src, open(dest, 'wb') as f:
                    shutil.copyfileobj(src, f)
            kind = ('model' if n == models[0] else 'library' if n.endswith('.npz') else
                    'chooser' if n.endswith('chooser.pt') else
                    'manifest' if n == root + 'agent.json' else None)
            found.setdefault(kind, dest)
    return found['model'], found.get('library'), found.get('chooser'), found.get('manifest')


def routes_spec(specs):
    """The routes' spec among `specs` (None if they have none)."""
    return next((s for s in specs if s['kind'] == 'routes'), None)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--agent', help='a model.zip from train.py, or a pack')
    p.add_argument('--cpu', action='store_true', help="play the game's CPU instead")
    p.add_argument('--cpu-level', type=int, default=2)
    p.add_argument('--side', type=int, choices=[1, 2], default=2, help='the side you play')
    p.add_argument('--chars', nargs=2, default=None, metavar=('P1', 'P2'))
    p.add_argument('--stage', type=int, default=None)
    p.add_argument('--rounds', type=int, default=2)
    p.add_argument('--frame-skip', type=int, default=None,
                   help="the agent's frames per decision (default: its training's)")
    p.add_argument('--deterministic', action='store_true', help="the agent's likeliest action")
    p.add_argument('--matches', type=int, default=None)
    p.add_argument('--record', default='recordings')
    p.add_argument('--keys', help='JSON of key names: {"A": "a", "up": "w", ...}')
    p.add_argument('--scale', type=int, default=3)
    p.add_argument('--volume', type=float, default=1.0, help='sounds and music, 0-1')
    p.add_argument('--no-sound', action='store_true')
    p.add_argument('--assist', metavar='LIBRARY',
                   help="the agent's combos from the built-in routes of this library")
    p.add_argument('--assist-victims', nargs='+', metavar='CHAR',
                   help='--assist only against these characters')
    p.add_argument('--assist-routes', type=int, default=None, metavar='N',
                   help='the combos tried at a plan (more: better combos, a slower plan; '
                        "default: the pack's, or 24)")
    p.add_argument('--assist-once', action='store_true',
                   help='a plan at the first hit only, not again at each new move')
    p.add_argument('--chooser', metavar='CHOOSER.pt', nargs='?', const=True,
                   help="--assist's combo chosen by this network, not on copies of the game "
                        "(alone: a pack's chooser)")
    p.add_argument('--no-assist', action='store_true',
                   help="a pack's agent with its own combos, not the pack's routes")
    p.add_argument('--module', action='append', default=[], metavar='KIND:key=value,...',
                   help='a module of the agent (in place of the pack\'s of that kind)')
    p.add_argument('--no-module', action='append', default=[], metavar='KIND',
                   help="the pack's agent without this module")
    args = p.parse_args()
    if not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    if not args.agent and not args.cpu:
        sys.exit('pass --agent model.zip, or --cpu')
    if args.assist and not args.agent:
        sys.exit('--assist: the combos of an --agent')
    from efz_env import modules
    # What the agent is made of: the pack's agent.json (or its library: the routes), then
    # this command line's words.
    specs, chooser = [], None
    pack = unpack(args.agent) if args.agent and os.path.isfile(args.agent) else None
    if pack:
        args.agent, library, chooser, manifest = pack
        if manifest:
            made = modules.load_manifest(manifest)
            args.agent, specs = made['model'], made['modules']
            chooser = (routes_spec(specs) or {}).get('files', {}).get('chooser', chooser)
        elif library:
            specs = [dict(kind='routes', code='agent_modules', options={},
                          files=dict(library=library, **({'chooser': chooser} if chooser else {})))]
    if args.assist:  # this library's routes, not the pack's
        spec = routes_spec(specs) or dict(kind='routes', code='agent_modules', files={}, options={})
        spec['files']['library'] = args.assist
        specs = [s for s in specs if s['kind'] != 'routes'] + [spec]
    if args.no_assist:
        specs = [s for s in specs if s['kind'] != 'routes']
    spec = routes_spec(specs)
    if args.chooser:
        if spec is None:
            sys.exit("--chooser: with --assist LIBRARY (the chooser's library)")
        if args.chooser is True and not chooser:
            sys.exit('--chooser: ' + ('the pack has no chooser.pt' if pack else
                                      "name a chooser.pt (alone it means a pack's)"))
        spec['files']['chooser'] = chooser if args.chooser is True else args.chooser
        spec['options']['by'] = 'chooser'
    if spec is not None:
        if args.assist_once:
            spec['options']['replan'] = False
        if args.assist_routes:
            spec['options']['per_start'] = args.assist_routes
        spec['options'].setdefault('per_start', 24)
        if args.assist_victims:
            spec['options']['victims'] = args.assist_victims
    for text in args.module:
        new = modules.parse_spec(text)
        new['code'] = new['options'].pop('code', 'agent_modules')
        specs = [s for s in specs if s['kind'] != new['kind']] + [new]
    specs = [s for s in specs if s['kind'] not in args.no_module]
    if pack or specs:
        print(f'agent: {args.agent}' + ''.join(
            f"\n  {s['kind']}: " + ', '.join(
                [f'{k} {v}' for k, v in s['files'].items()
                 if k != 'chooser' or s['options'].get('by') == 'chooser'] +
                [f'{k}={v}' for k, v in s['options'].items()]) for s in specs))
    policy, agent, frame_skip = None, None, args.frame_skip
    if args.agent:
        # As trained: deciding every frame_skip frames, with its input history.
        from efz_env.agent import Agent
        policy = Agent(args.agent, deterministic=args.deterministic, frame_skip=frame_skip)
        frame_skip = policy.frame_skip
        if specs:
            sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'runs',
                                            'human-ayu'))
            agent = modules.ModularAgent(policy, modules.build(policy, specs, 'play',
                                                               data=args.data))
    chars = tuple(None if c == 'any' else c for c in args.chars) if args.chars else (None, None)
    match = HumanMatch(args.data, human=args.side - 1,
                       opponent='cpu' if args.cpu else 'agent', chars=chars, stage=args.stage,
                       frame_skip=frame_skip or 4, record_dir=args.record,
                       agent_name=args.agent + ''.join(' +' + s['kind'] for s in specs) +
                       ' (chooser)' * any(s['options'].get('by') == 'chooser' for s in specs)
                       if args.agent
                       else f'cpu-{args.cpu_level}', scale=args.scale,
                       keys=json.loads(args.keys) if args.keys else None,
                       cpu_level=args.cpu_level, rounds_to_win=args.rounds,
                       sound=not args.no_sound, volume=args.volume)
    if agent:  # (the routes' planner follows the match: what set_matches was given)
        agent.attach_match(match, chars=chars, stage=args.stage, cpu=(False, False))
        policy = agent
    results = match.play(policy, matches=args.matches)
    match.close()
    if agent:
        agent.close()
        for name, what in agent.stats().items():
            print(f'{name}:', json.dumps(what))
    print(f'matches: {len(results)}, you won {sum(r == -1 for r in results)}, '
          f'lost {sum(r == 1 for r in results)}; recorded in {args.record}')


if __name__ == '__main__':
    main()
