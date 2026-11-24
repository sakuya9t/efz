"""The league's opponents with their characters' combos: a combo library for every
character from the community's replays, and each trained opponent as an agent file that
plays its model with those combos through the game's route planner.

Why (the user's, 20 November: "we need to build standard big planner combos for all the
league we used to train. Only our agent has combo while the opponent not creates an
advantage"). The agent plans its combos from people's routes; its opponents played their
models alone: 560-780 HP a combo for the agent's 1,750, so a hit cost the agent a third
of what it cost them, in training and in every benchmark.

    # a library for each character (its dataset of dataset.py; 15 s each)
    python runs/human-ayu/league_combos.py libraries --datasets ~/data/efz-replays/datasets \\
        --out ~/data/efz-replays/combos
    # the opponents' files (beside each model: combos.efzagent)
    python runs/human-ayu/league_combos.py files --libraries ~/data/efz-replays/combos \\
        runs/human-ayu/kano/exploiter18/model.zip:kano ...

    # the game's CPU with combos (OPTIONS' CPU COMBO, docs/agents.md): a file a character,
    # the newest exploiter's, as the game's agents/cpu folder wants them
    python runs/human-ayu/league_combos.py cpu --out ~/dev/efz/tmp/cpu-combos

libraries: combo_library.py's, --keep most damaging overall and --per-victim on each
character they were landed on, with the join points (--marks), as the agent's own. With
--kind oki or press, each character's people's okizeme (oki_library.py) or pressure
(pressure_library.py) instead, with the answers beside it: for the planners of files'
--oki and --press.

Planners for the league (docs/training-v2-log.md, "Playing to the opponent's weak areas": the
league varied a third as much as people do in the okizeme on the agent and in the
opponent's pressure, where people differ most): files --oki DIR and --press DIR give each
file its character's planned okizeme and pressure (the modules okiplan and pressplan,
port/agent/mix.h), with the agent's own settings (OKI, PRESS); --oki-skip and --press-skip
are the shares of its chances it leaves to its model, an opponent's strength there.

    python runs/human-ayu/league_combos.py libraries --kind oki --datasets ~/data/efz-replays/datasets \
        --out ~/data/efz-replays/oki
    python runs/human-ayu/league_combos.py files --libraries ~/data/efz-replays/combos \
        --oki ~/data/efz-replays/oki --press ~/data/efz-replays/press --name planners.efzagent \
        runs/human-ayu/kano/exploiter18/model.zip:kano ...

files: export_agent's file of the model with its character's library, planned again at
each new move's hit, without its training part. Two settings are an opponent's and not an
agent's:

- --confirm (1): its route begins this many steps after its hit, not after its delay. An
  opponent's own play in the steps before a route begins does not carry people's combos
  (trained without them): with its 14 steps a route was usable at a third of Kano's
  `exploiter18`'s hits (1,084 HP a combo, 860 without routes), with 8 at 46% (1,220), 4
  at 61% (1,319), 1 at 64% (1,413; the 90th percentile 3,308 for 1,976). It is a combo
  confirmed before the hit is seen: what a person gets from a string pressed ahead, and
  never a setting for an agent that is to play within a person's limits.
- --delay (11): the steps late its model sees the game, instead of its config's (14): an
  11-step agent is not to be measured by out-reacting its opponents.
"""

import argparse
import json
import os
import shutil
import subprocess
import sys
import tempfile

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
# The planners' settings, the agent's own (its round 21 file's, where they differ from
# efz_env.export's defaults).
OKI = dict(per_plan=5, window=40, think=14, sight=14)
PRESS = dict(doubt=0.3)


def libraries(args):
    os.makedirs(args.out, exist_ok=True)
    chars = args.chars or sorted(d for d in os.listdir(args.datasets)
                                 if os.path.exists(os.path.join(args.datasets, d, 'matches.csv')))
    tool = os.path.join(HERE, dict(combo='combo_library.py', oki='oki_library.py',
                                   press='pressure_library.py')[args.kind])
    for c in chars:
        data, out = os.path.join(args.datasets, c), os.path.join(args.out, c + '.npz')
        if os.path.exists(out) and not args.again:
            print(f'{c}: {out} is there')
            continue
        if args.kind != 'combo':
            log = subprocess.run([sys.executable, tool, '--dataset', data, '--out', out],
                                 capture_output=True, text=True, check=True).stdout
            subprocess.run([sys.executable, tool, '--answers', out], capture_output=True, text=True,
                           check=True)
            print(f'{c}: {log.splitlines()[0]}')
            continue
        log = subprocess.run([sys.executable, tool, '--dataset', data, '--keep', str(args.keep),
                              '--per-victim', str(args.per_victim), '--show', '0', '--out', out],
                             capture_output=True, text=True, check=True).stdout
        marks = subprocess.run([sys.executable, tool, '--dataset', data, '--marks', out],
                               capture_output=True, text=True, check=True).stdout
        print(f'{c}: {log.splitlines()[0]}; {log.splitlines()[-1]}; {marks.strip().split(": ")[-1]}')


def one_file(model, char, library, out, delay, confirm, per_start, version, okiplan=None,
             pressplan=None):
    """model (a model.zip with its config.json beside it) as an agent file at out; okiplan,
    pressplan: its planners (export_agent's), or None."""
    from efz_env.export import export_agent
    with tempfile.TemporaryDirectory() as folder:
        cfg = json.load(open(os.path.join(os.path.dirname(model), 'config.json')))
        if delay is not None:
            cfg['delay'] = int(delay)
        json.dump(cfg, open(os.path.join(folder, 'config.json'), 'w'))
        shutil.copy(model, os.path.join(folder, 'model.zip'))
        name = os.path.basename(os.path.dirname(os.path.abspath(model)))
        export_agent(os.path.join(folder, 'model.zip'), out, name=f'{char}-{name}', library=library,
                     replan=True, per_start=per_start, train=False, version=version,
                     confirm=confirm or None, okiplan=okiplan, pressplan=pressplan)


def files(args):
    for spec in args.models:
        model, _, char = spec.rpartition(':')
        if not model:
            sys.exit(f'{spec}: MODEL.zip:CHAR')
        library = os.path.join(args.libraries, char + '.npz')
        if not os.path.exists(library):
            sys.exit(f'{char}: no library at {library} (league_combos.py libraries)')
        out = os.path.join(os.path.dirname(os.path.abspath(model)), args.name)
        if os.path.exists(out) and not args.again:
            print(f'{out} is there')
            continue
        plans = {}
        for kind, folder, skip, opts in (('okiplan', args.oki, args.oki_skip, OKI),
                                         ('pressplan', args.press, args.press_skip, PRESS)):
            if folder and skip < 1:
                lib = os.path.join(folder, char + '.npz')
                if not os.path.exists(lib):
                    sys.exit(f'{char}: no library at {lib} (league_combos.py libraries --kind)')
                plans[kind] = dict(opts, library=lib, skip=skip)
        one_file(model, char, library, out, args.delay, args.confirm, args.per_start, args.version,
                 **plans)
        print(f'{out}: {os.path.getsize(out) / 1e6:.1f} MB')


def newest(char_dir):
    """Of a character's trained opponents with a file (combos.efzagent), the newest
    exploiter's (exploiterN, the highest N; else `exploiter`), else the first by name."""
    have = sorted(d for d in os.listdir(char_dir)
                  if os.path.exists(os.path.join(char_dir, d, 'combos.efzagent')))
    def rank(d):
        n = d[len('exploiter'):]
        return (2, int(n)) if d.startswith('exploiter') and n.isdigit() else \
               (1, 0) if d == 'exploiter' else (0, 0)
    best = max(have, key=rank, default=None)
    return best if best is None or rank(best)[0] > 0 else have[0]


def cpu(args):
    """The game's CPU with combos: a file a character, CHAR.efzagent in --out, for the
    game's agents/cpu folder (port/agent/play.cpp takes the first by name of each
    character there). The game begins their routes later than the file says (its plans
    are made between frames)."""
    os.makedirs(args.out, exist_ok=True)
    runs = args.runs
    chars = args.chars or sorted(c for c in os.listdir(runs)
                                 if os.path.isdir(os.path.join(runs, c)) and newest(os.path.join(runs, c)))
    for c in chars:
        d = newest(os.path.join(runs, c)) if os.path.isdir(os.path.join(runs, c)) else None
        if d is None:
            print(f'{c}: no trained opponent with a file (league_combos.py files)')
            continue
        out = os.path.join(args.out, c + '.efzagent')
        shutil.copyfile(os.path.join(runs, c, d, 'combos.efzagent'), out)
        print(f'{c}: {c}/{d}/combos.efzagent -> {out} ({os.path.getsize(out) / 1e6:.1f} MB)')


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = p.add_subparsers(dest='what', required=True)
    a = sub.add_parser('libraries', help="a combo library for each character's dataset")
    a.add_argument('--datasets', required=True, help="the folder of dataset.py's datasets, one a character")
    a.add_argument('--out', required=True, help='CHAR.npz and CHAR.marks.json here')
    a.add_argument('--chars', nargs='*', help='only these (default: every dataset there)')
    a.add_argument('--keep', type=int, default=300)
    a.add_argument('--per-victim', type=int, default=40)
    a.add_argument('--again', action='store_true', help='also those already there')
    a.add_argument('--kind', default='combo', choices=('combo', 'oki', 'press'),
                   help="combos (combo_library.py), or people's okizeme or pressure")
    b = sub.add_parser('files', help="trained opponents as agent files with their characters' combos")
    b.add_argument('models', nargs='+', metavar='MODEL.zip:CHAR')
    b.add_argument('--libraries', required=True)
    b.add_argument('--name', default='combos.efzagent', help="the file's name, beside each model")
    b.add_argument('--delay', type=int, default=11,
                   help="the steps late the model sees the game (its config's: --delay -1)")
    b.add_argument('--confirm', type=int, default=1,
                   help='the steps after its hit at which a route begins (0: its delay)')
    b.add_argument('--per-start', type=int, default=None)
    b.add_argument('--version', default='combos')
    b.add_argument('--again', action='store_true')
    b.add_argument('--oki', help='planned okizeme from CHAR.npz here (libraries --kind oki)')
    b.add_argument('--press', help='planned pressure from CHAR.npz here (libraries --kind press)')
    b.add_argument('--oki-skip', type=float, default=0.05,
                   help='the share of its knockdowns left to its model (1: no planner)')
    b.add_argument('--press-skip', type=float, default=0.05,
                   help='the share of its guarded moves left to its model (1: no planner)')
    c = sub.add_parser('cpu', help="a file a character for the game's CPU with combos (agents/cpu)")
    c.add_argument('--out', required=True, help='CHAR.efzagent here')
    c.add_argument('--chars', nargs='*', help="only these (default: every character with a file)")
    c.add_argument('--runs', default=HERE, help='the trained opponents, CHAR/NAME/ (default: beside this script)')
    args = p.parse_args()
    if args.what == 'files' and args.delay is not None and args.delay < 0:
        args.delay = None
    {'libraries': libraries, 'files': files, 'cpu': cpu}[args.what](args)


if __name__ == '__main__':
    main()
