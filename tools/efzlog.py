#!/usr/bin/env python3
"""The native game's logs and fight records (docs/logging.md).

    tools/efzlog.py sessions [LOGS]          the sessions in a logs folder, oldest first
    tools/efzlog.py show SESSION             a session: how it ended, its warnings and
                                             errors, its fights, its crash
    tools/efzlog.py fight FIGHT.jsonl        a fight: players, result, events, anomalies
    tools/efzlog.py export FIGHT.jsonl OUT   its ticks as a table, one row a tick:
                                             OUT.csv, or OUT.npz (needs numpy)
    tools/efzlog.py diff A.jsonl B.jsonl     the first tick at which two records of a
                                             fight part, and what differs there
    tools/efzlog.py state FILE.state         the blocks of a state file, their sizes and
                                             hashes

LOGS is $EFZ_LOG_DIR by default. SESSION is a session folder, or its id in LOGS.

As a module, for training and analysis:
    read_fight(path)     {'header', 'ticks', 'events', 'end', 'path'}
    ticks_table(fight)   the ticks as columns: {'t': [...], 'p1_hp': [...], ...}
    iter_fights(logs)    every fight record under a logs folder
    read_state(path)     {block name: bytes} of a .state file
    decode_input(bits)   a replay input word as {'up': bool, ..., 'A': bool, ...}
"""
import argparse
import csv
import glob
import json
import os
import re
import struct
import sys

BLOCKS = ['p1', 'p1obj', 'p1char', 'p2', 'p2obj', 'p2char', 'scene', 'game', 'fx']
SESSION = re.compile(r'^\d{8}-\d{6}-[0-9a-f]{4}$')
# The bits of an input word, as the replay files and the records' "in" have them.
INPUT_BITS = {'right': 0x1, 'left': 0x2, 'down': 0x4, 'up': 0x8,
              'A': 0x10, 'B': 0x20, 'C': 0x40, 'D': 0x80}


def die(message):
    sys.exit(f'efzlog: {message}')


def decode_input(bits):
    return {name: bool(bits & bit) for name, bit in INPUT_BITS.items()}


def read_jsonl(path):
    """The records of a JSON-lines file. A line that isn't JSON (the last line, when the
    game crashed while writing it) is left out with a warning."""
    records = []
    with open(path, encoding='utf-8') as f:
        for number, line in enumerate(f, 1):
            if not line.strip():
                continue
            try:
                records.append(json.loads(line))
            except json.JSONDecodeError:
                print(f'efzlog: {path}:{number} isn\'t JSON; left out', file=sys.stderr)
    return records


def read_fight(path):
    fight = {'path': path, 'header': None, 'ticks': [], 'events': [], 'end': None}
    for record in read_jsonl(path):
        kind = record.get('type')
        if kind == 'fight':
            fight['header'] = record
        elif kind == 'tick':
            fight['ticks'].append(record)
        elif kind == 'end':
            fight['end'] = record
        else:
            fight['events'].append(record)
    if fight['header'] is None:
        die(f'{path} has no header: not a fight record')
    if fight['header'].get('format') != 'efz-fight' or fight['header'].get('version') != 1:
        die(f'{path} isn\'t an efz-fight record of version 1')
    return fight


def ticks_table(fight):
    """The ticks as columns of equal length: t (the tick), f (the fight's frame), rng,
    in_p1 and in_p2 (input words), the game fields, and p1_<field>, p2_<field> for each
    of the header's player_fields. A position or velocity that wasn't a number is None."""
    header = fight['header']
    player_fields = header['player_fields']
    game_fields = header.get('game_fields', [])
    columns = {name: [] for name in ['t', 'f', 'rng', 'in_p1', 'in_p2'] + game_fields}
    for side in ('p1', 'p2'):
        for name in player_fields:
            columns[f'{side}_{name}'] = []
    for tick in fight['ticks']:
        columns['t'].append(tick['t'])
        columns['f'].append(tick['f'])
        columns['rng'].append(tick['rng'])
        columns['in_p1'].append(tick['in'][0])
        columns['in_p2'].append(tick['in'][1])
        for i, name in enumerate(game_fields):
            columns[name].append(tick['g'][i])
        for s, side in enumerate(('p1', 'p2')):
            for i, name in enumerate(player_fields):
                columns[f'{side}_{name}'].append(tick['p'][s][i])
    return columns


def iter_fights(logs):
    """Every fight-NNN.jsonl under a logs folder, in session order."""
    for path in sorted(glob.glob(os.path.join(logs, '*', 'fight-*.jsonl'))):
        yield path


def fnv(data):
    h = 2166136261
    for b in data:
        h = ((h ^ b) * 16777619) & 0xffffffff
    return h


def read_state(path):
    """A .state file's blocks (the harness's dump format: [tick, block, size] and the
    bytes), by name. A file with several ticks keeps the last of each block."""
    blocks = {}
    with open(path, 'rb') as f:
        data = f.read()
    at = 0
    while at + 12 <= len(data):
        tick, block, size = struct.unpack_from('<III', data, at)
        at += 12
        if block >= len(BLOCKS) or at + size > len(data):
            die(f'{path} is cut short or isn\'t a state file')
        blocks[BLOCKS[block]] = data[at:at + size]
        at += size
    return blocks


def logs_dir(path):
    path = path or os.environ.get('EFZ_LOG_DIR')
    if not path:
        die('which logs folder? Name it, or set EFZ_LOG_DIR')
    return path


def session_dir(name, logs=None):
    if os.path.isdir(name):
        return name
    if logs or os.environ.get('EFZ_LOG_DIR'):
        path = os.path.join(logs_dir(logs), name)
        if os.path.isdir(path):
            return path
    die(f'no session {name}')


def read_session(path):
    try:
        with open(os.path.join(path, 'session.json'), encoding='utf-8') as f:
            return json.load(f)
    except (OSError, json.JSONDecodeError):
        return {}


def players(header):
    return ' vs '.join(f"{p['name']} ({'cpu' if p['cpu'] else 'human'})"
                       for p in header['players'])


def fight_line(fight):
    header, end = fight['header'], fight['end']
    result = 'no end recorded'
    if end:
        result = end['reason']
        if end.get('winner', -1) >= 0:
            result += f", P{end['winner'] + 1} won {end['rounds_won'][0]}-{end['rounds_won'][1]}"
    anomalies = sum(1 for e in fight['events'] if e.get('type') == 'anomaly')
    return (f"{os.path.basename(fight['path'])}: {players(header)}, stage {header['stage']}, "
            f"{header['mode_name']}; {len(fight['ticks'])} ticks, {result}"
            + (f'; {anomalies} anomalies' if anomalies else ''))


# --- The commands.

def cmd_sessions(args):
    logs = logs_dir(args.logs)
    for name in sorted(os.listdir(logs)):
        path = os.path.join(logs, name)
        if not SESSION.match(name) or not os.path.isdir(path):
            continue
        s = read_session(path)
        counts = s.get('counts', {})
        crash = ' crash.txt' if os.path.exists(os.path.join(path, 'crash.txt')) else ''
        print(f"{name}  {s.get('status', '?'):8} {s.get('seconds', 0):8.1f} s  "
              f"fights {counts.get('fights', 0):3}  anomalies {counts.get('anomalies', 0):3}  "
              f"warnings {counts.get('warnings', 0):3}  errors {counts.get('errors', 0):3}"
              f"{crash}")


def cmd_show(args):
    path = session_dir(args.session, args.logs)
    s = read_session(path)
    build = s.get('build', {})
    print(f"session {s.get('id', os.path.basename(path))}: {s.get('status', '?')}"
          + (f", exit code {s['exit_code']}" if 'exit_code' in s else '')
          + f", {s.get('seconds', 0):.1f} s")
    print(f"build {build.get('revision', '?')}{'+' if build.get('dirty') else ''} "
          f"({build.get('compiler', '?')}, {build.get('config', '?')}, {build.get('os', '?')} "
          f"{build.get('arch', '?')}), seed {s.get('seed', '?')}")
    crash = os.path.join(path, 'crash.txt')
    if os.path.exists(crash):
        with open(crash, encoding='utf-8', errors='replace') as f:
            report = f.read()
        print('\n' + report.split('\ngame:')[0].strip())
    log = os.path.join(path, 'efz.log')
    if os.path.exists(log):
        with open(log, encoding='utf-8', errors='replace') as f:
            problems = [line.rstrip() for line in f
                        if re.search(r' (WARN|ERROR|FATAL) ', line)]
        if problems:
            print(f'\nwarnings and errors ({len(problems)}):')
            for line in problems[:50]:
                print('  ' + line)
            if len(problems) > 50:
                print(f'  ... and {len(problems) - 50} more')
    fights = sorted(glob.glob(os.path.join(path, 'fight-*.jsonl')))
    if fights:
        print(f'\nfights ({len(fights)}):')
        for f in fights:
            print('  ' + fight_line(read_fight(f)))


def cmd_fight(args):
    fight = read_fight(args.fight)
    header = fight['header']
    print(fight_line(fight))
    print(f"session {header['session']}, fight {header['fight']}, started {header['started']}, "
          f"build {header['build'].get('revision', '?')}")
    for event in fight['events']:
        kind = event.get('type')
        if kind == 'anomaly':
            print(f"  tick {event['t']}: anomaly {event['check']}, "
                  f"{['P1', 'P2'][event['player']] if event['player'] >= 0 else 'game'}: "
                  f"{event['detail']}" + (f" (state {event['state']})" if 'state' in event else ''))
        elif kind == 'event':
            extra = {k: v for k, v in event.items() if k not in ('type', 't', 'f', 'event')}
            print(f"  tick {event['t']}: {event['event']} {extra if extra else ''}".rstrip())
    end = fight['end']
    if end and end.get('anomalies'):
        print('  anomalies in all: ' + ', '.join(f'{k} on {v} ticks'
                                                for k, v in end['anomalies'].items()))


def cmd_export(args):
    columns = ticks_table(read_fight(args.fight))
    out = args.out
    if out.endswith('.npz'):
        try:
            import numpy as np
        except ImportError:
            die('.npz needs numpy; or write a .csv')

        def array(values):
            if all(isinstance(v, int) and not isinstance(v, bool) for v in values):
                return np.asarray(values, dtype=np.int64)
            return np.asarray([float('nan') if v is None else v for v in values],
                              dtype=np.float64)
        np.savez_compressed(out, **{name: array(values) for name, values in columns.items()})
    else:
        if not out.endswith('.csv'):
            out += '.csv'
        names = list(columns)
        with open(out, 'w', newline='', encoding='utf-8') as f:
            w = csv.writer(f)
            w.writerow(names)
            for row in zip(*(columns[n] for n in names)):
                w.writerow(['' if v is None else repr(v) if isinstance(v, float) else v
                            for v in row])
    print(f"{out}: {len(columns['t'])} ticks, {len(columns)} columns")


def cmd_diff(args):
    a, b = read_fight(args.a), read_fight(args.b)
    fields = a['header']['player_fields']
    count = min(len(a['ticks']), len(b['ticks']))
    for i in range(count):
        ta, tb = a['ticks'][i], b['ticks'][i]
        what = []
        ha, hb = ta.get('h', ''), tb.get('h', '')
        if ha and hb:
            what += [name for k, name in enumerate(BLOCKS) if ha[8 * k:8 * k + 8] != hb[8 * k:8 * k + 8]]
        for key in ('f', 'rng', 'in'):
            if ta.get(key) != tb.get(key):
                what.append(key)
        if what:
            print(f"tick {i} differs: {', '.join(what)}")
            for s in range(2):
                for k, name in enumerate(fields):
                    va, vb = ta['p'][s][k], tb['p'][s][k]
                    if va != vb:
                        print(f'  P{s + 1} {name}: {va!r} / {vb!r}')
            return 1
    if len(a['ticks']) != len(b['ticks']):
        print(f"the same for {count} ticks; then one has {len(a['ticks'])}, the other "
              f"{len(b['ticks'])}")
        return 1
    print(f'the same, all {count} ticks')
    return 0


def cmd_state(args):
    for name, data in read_state(args.state).items():
        print(f'{name:7} {len(data):7} bytes  fnv {fnv(data):08x}')


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = p.add_subparsers(dest='command', required=True)
    s = sub.add_parser('sessions')
    s.add_argument('logs', nargs='?')
    s = sub.add_parser('show')
    s.add_argument('session')
    s.add_argument('--logs')
    s = sub.add_parser('fight')
    s.add_argument('fight')
    s = sub.add_parser('export')
    s.add_argument('fight')
    s.add_argument('out')
    s = sub.add_parser('diff')
    s.add_argument('a')
    s.add_argument('b')
    s = sub.add_parser('state')
    s.add_argument('state')
    args = p.parse_args()
    return globals()['cmd_' + args.command](args) or 0


if __name__ == '__main__':
    sys.exit(main())
