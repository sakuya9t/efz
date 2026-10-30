#!/usr/bin/env python3
"""The replay test (docs/compat.md): the native game against the original.

The original is build/trace/efz.exe (make trace): efz.exe's code with the harness of
src/trace.cpp, run under wine on a virtual display in the efz-revival-test image. The
native game is build/native/efz (tools/native.sh), run without a display; with
--windows, the native game's Windows build, build/windows/efz.exe, under 64-bit wine
(efz-wine64). Both log each player's status after every tick of the fight; the first
tick whose status differs is where a bug shows.

    tools/compat.py record N-M SPEC [--ticks T]  the original records replay\\dataN-M.rep,
                                                 SPEC = P1:P2:STAGE:PAL1:PAL2:SEED
    tools/compat.py play N-M [--runs R]          the original plays it R times (default
                                                 2, to see it is repeatable), the
                                                 native game once; compare
    tools/compat.py fuzz COUNT [--seed S] [--ticks T]
                                                 record COUNT matches of random
                                                 characters, stages and input, play
                                                 each, compare
    tools/compat.py check [N-M ...]              play the replays in the native game
                                                 only, against the original's traces
                                                 from play (default: every replay)
    tools/compat.py diff A B                     compare two trace files
    --native-records                             with record and fuzz: the native game
                                                 records, and the original plays it back

Everything happens in $EFZ_PLAY/compat (default ~/.local/share/efz-decomp/compat): the
game folder (links to $EFZ_DIR, with replays and traces), the wine prefix.
"""
import argparse
import os
import random
import shutil
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PLAY = os.path.join(os.environ.get('EFZ_PLAY', os.path.expanduser('~/.local/share/efz-decomp')),
                    'compat')
GAME = os.path.join(PLAY, 'game')
ORIGINAL = os.path.join(REPO, 'build', 'trace', 'efz.exe')
NATIVE = os.environ.get('EFZ_NATIVE', os.path.join(REPO, 'build', 'native', 'efz'))
WINDOWS = os.path.join(REPO, 'build', 'windows', 'efz.exe')
IMAGE = 'efz-revival-test'
IMAGE64 = 'efz-wine64'
# Set by --windows: run the native game's Windows build instead.
use_windows = False

FIELDS = ['action', 'frame', 'x', 'y', 'vx', 'vy', 'hp', 'combo start hp', 'combo damage',
          'hits', 'gauge', 'facing']
# Characters by replay number (CScene2::Unk76da20) and the stages a fight can use.
CHARACTERS = list(range(0x19))
STAGES = list(range(0x17))


def die(msg):
    sys.exit(f'tools/compat.py: {msg}')


def setup():
    efz = os.environ.get('EFZ_DIR')
    if not efz or not os.path.isfile(os.path.join(efz, 'efz.exe')):
        die('set EFZ_DIR to the folder containing the original efz.exe')
    efz = os.path.abspath(efz)
    os.makedirs(os.path.join(GAME, 'replay'), exist_ok=True)
    for name in os.listdir(efz):
        if name.lower() in ('efz.exe', 'key.ini', 'replay'):
            continue
        link = os.path.join(GAME, name)
        if not os.path.lexists(link):
            os.symlink(os.path.join(efz, name), link)
    # A fixed key.ini (docs/compat.md): the data folder's, written over each time.
    key = os.path.join(GAME, 'key.ini')
    if os.path.lexists(key):
        os.remove(key)
    if os.path.exists(os.path.join(efz, 'key.ini')):
        shutil.copyfile(os.path.join(efz, 'key.ini'), key)
    exe = os.path.join(GAME, 'efz.exe')
    if os.path.lexists(exe):
        os.remove(exe)
    if not os.path.isfile(ORIGINAL):
        die(f'no {ORIGINAL}: run make trace')
    shutil.copyfile(ORIGINAL, exe)
    os.makedirs(os.path.join(PLAY, 'wine'), exist_ok=True)
    return efz


def run_container(args, timeout):
    """docker run ARGS; a container still running after `timeout` seconds (wine hangs
    now and then) is killed, which leaves its trace short."""
    name = f'efz-compat-{os.getpid()}'
    try:
        subprocess.run(['docker', 'run', '--name', name, *args], timeout=timeout, check=False)
    except subprocess.TimeoutExpired:
        print(f'  timed out after {timeout} s; killed', flush=True)
        subprocess.run(['docker', 'kill', name], capture_output=True, check=False)


def run_original(efz, env, timeout=900):
    """Runs the original under wine with the harness's variables `env`."""
    subprocess.run(['docker', 'image', 'inspect', IMAGE], capture_output=True, check=True)
    envs = []
    for k, v in env.items():
        envs += ['-e', f'{k}={v}']
    script = '''
Xvfb :99 -screen 0 1024x768x24 >/dev/null 2>&1 &
sleep 1
[ -e /wine/.compat-setup ] || { wineboot -i >/dev/null 2>&1; wineserver -w; touch /wine/.compat-setup; }
wine explorer /desktop=EFZ,640x480 efz.exe >/dev/null 2>&1
wineserver -w
'''
    run_container(['--rm', '--init', '--network', 'none',
                   '-v', f'{efz}:{efz}:ro', '-v', f'{GAME}:/run/game', '-v', f'{PLAY}/wine:/wine',
                   '-e', 'WINEPREFIX=/wine', '-e', 'WINEDEBUG=-all', '-e', 'DISPLAY=:99',
                   *envs, '-w', '/run/game', IMAGE, 'bash', '-c', script], timeout)


def run_native(efz, env, timeout=900):
    env = dict(env, SDL_VIDEO_DRIVER='offscreen', SDL_AUDIO_DRIVER='dummy')
    if use_windows:
        if not os.path.isfile(WINDOWS):
            die(f'no {WINDOWS}: run tools/native.sh windows')
        subprocess.run(['docker', 'image', 'inspect', IMAGE64], capture_output=True, check=True)
        os.makedirs(os.path.join(PLAY, 'wine64'), exist_ok=True)
        envs = []
        for k, v in env.items():
            envs += ['-e', f'{k}={v}']
        script = r'''
[ -e /wine/.compat-setup ] || { /usr/lib/wine/wine64 wineboot -i >/dev/null 2>&1; wineserver -w; touch /wine/.compat-setup; }
/usr/lib/wine/wine64 /bin64/efz.exe --data 'Z:\efz' --save 'Z:\run\game'
'''
        run_container(['--rm', '--init', '--network', 'none',
                       '-v', f'{efz}:/efz:ro', '-v', f'{GAME}:/run/game',
                       '-v', f'{PLAY}/wine64:/wine', '-v', f'{os.path.dirname(WINDOWS)}:/bin64:ro',
                       '-e', 'WINEPREFIX=/wine', '-e', 'WINEARCH=win64', '-e', 'WINEDEBUG=-all',
                       *envs, '-w', '/run/game', IMAGE64, 'bash', '-c', script], timeout)
        return
    if not os.path.isfile(NATIVE):
        die(f'no {NATIVE}: run tools/native.sh')
    subprocess.run([NATIVE, '--data', efz, '--save', GAME], env=dict(os.environ, **env), cwd=GAME,
                   timeout=timeout, check=False)


def read_trace(path, recording=False):
    """The trace's ticks: (tick and replay position, player 1, player 2). Fields the
    game hasn't set yet are left out: the combo's damage (+0x100) is uninitialised
    heap memory until a combo starts, different on every run of the original. A
    recording reads nothing from the replay, so its read position is left out too."""
    rows = []
    with open(path) as f:
        for line in f:
            parts = [p.split() for p in line.split('|')]
            if len(parts) != 3:
                continue
            for player in parts[1:]:
                if player[FIELDS.index('hits')] == '0':
                    player[FIELDS.index('combo damage')] = '-'
            if recording:
                parts[0][1] = '-'
            rows.append((parts[0], parts[1], parts[2]))
    return rows


def describe(player):
    """The player's fields, doubles decoded."""
    import struct
    out = []
    for name, value in zip(FIELDS, player):
        if name in ('x', 'y', 'vx', 'vy'):
            value = repr(struct.unpack('>d', bytes.fromhex(value))[0])
        out.append(f'{name}={value}')
    return ' '.join(out)


def compare(a_path, b_path, a_name='original', b_name='native', quiet=False):
    """Prints where two traces part; returns True if they agree."""
    recording = a_path.endswith('-record.txt') or b_path.endswith('-record.txt')
    a, b = read_trace(a_path, recording), read_trace(b_path, recording)
    n = min(len(a), len(b))
    for i in range(n):
        if a[i] == b[i]:
            continue
        print(f'  tick {a[i][0][0]}: first difference')
        for k in range(max(0, i - 3), min(n, i + 2)):
            for side in (1, 2):
                if a[k][side] != b[k][side]:
                    diff = [f'{FIELDS[j]} {x} != {y}'
                            for j, (x, y) in enumerate(zip(a[k][side], b[k][side])) if x != y]
                    print(f'    tick {a[k][0][0]} P{side}: ' + ', '.join(diff))
            if a[k][0] != b[k][0]:
                print(f'    tick {a[k][0][0]}: replay position {a[k][0][1]} != {b[k][0][1]}')
        print(f'    {a_name} P1: {describe(a[i][1])}')
        print(f'    {b_name} P1: {describe(b[i][1])}')
        print(f'    {a_name} P2: {describe(a[i][2])}')
        print(f'    {b_name} P2: {describe(b[i][2])}')
        return False
    # A recording stops at its tick limit, and its playback runs on to the end of the
    # file: only the ticks both have count then.
    if len(a) != len(b) and not recording:
        print(f'  {a_name} has {len(a)} ticks, {b_name} {len(b)}')
        return False
    if not quiet:
        print(f'  {n} ticks agree')
    return True


def trace_path(name):
    return os.path.join(GAME, name)


def record(efz, slot, spec, ticks, native=False):
    env = {'EFZ_TRACE': f'trace-{slot}-record.txt', 'EFZ_TRACE_RECORD': f'{slot}:{spec}',
           'EFZ_TRACE_FAST': '1'}
    if ticks:
        env['EFZ_TRACE_TICKS'] = str(ticks)
    rep = os.path.join(GAME, 'replay', f'data{slot}.rep')
    if os.path.exists(rep):
        os.remove(rep)
    (run_native if native else run_original)(efz, env)
    if not os.path.isfile(rep):
        die(f'the {"native game" if native else "original"} wrote no {rep}')
    print(f'recorded {rep}: {len(read_trace(trace_path(f"trace-{slot}-record.txt")))} ticks')


def same(a_path, b_path):
    a, b = read_trace(a_path), read_trace(b_path)
    return a[:min(len(a), len(b))] == b[:min(len(a), len(b))]


def play(efz, slot, runs):
    """Plays a replay in the original `runs` times and in the native game; True if all
    traces agree. If the native game parts from the original, the original plays it up
    to 4 more times: when one of those runs is the native game's, the original itself
    varies on this replay (uninitialised memory, docs/compat.md) and the native game
    took one of its ways; that is reported, and not counted as a failure."""
    ok = True
    names = []
    for r in range(runs):
        name = f'trace-{slot}-original{r}.txt'
        run_original(efz, {'EFZ_TRACE': name, 'EFZ_TRACE_PLAY': slot, 'EFZ_TRACE_FAST': '1'})
        names.append(name)
    run_native(efz, {'EFZ_TRACE': f'trace-{slot}-native.txt', 'EFZ_TRACE_PLAY': slot,
                     'EFZ_TRACE_FAST': '1'})
    first = trace_path(names[0])
    record_trace = trace_path(f'trace-{slot}-record.txt')
    if os.path.isfile(record_trace):
        print(f'data{slot}.rep: recording against the original playing it')
        ok &= compare(record_trace, first, 'recording', 'playback')
    for r in range(1, runs):
        print(f'data{slot}.rep: the original against itself (run {r + 1})')
        ok &= compare(first, trace_path(names[r]), 'run 1', f'run {r + 1}')
    print(f'data{slot}.rep: the original against the native game')
    native = trace_path(f'trace-{slot}-native.txt')
    if compare(first, native):
        return ok
    for r in range(runs, runs + 4):
        name = f'trace-{slot}-original{r}.txt'
        run_original(efz, {'EFZ_TRACE': name, 'EFZ_TRACE_PLAY': slot, 'EFZ_TRACE_FAST': '1'})
        if same(trace_path(name), native):
            print(f'  the original varies: its run {r + 1} is the native game\'s, tick for tick')
            return ok
    return False


def main():
    sys.stdout.reconfigure(line_buffering=True)
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--windows', action='store_true',
                    help="test the native game's Windows build, under 64-bit wine")
    sub = ap.add_subparsers(dest='cmd', required=True)
    r = sub.add_parser('record')
    r.add_argument('slot')
    r.add_argument('spec')
    r.add_argument('--ticks', type=int)
    p = sub.add_parser('play')
    p.add_argument('slot')
    p.add_argument('--runs', type=int, default=2)
    f = sub.add_parser('fuzz')
    f.add_argument('count', type=int)
    f.add_argument('--seed', type=int, default=1)
    f.add_argument('--ticks', type=int, default=3000)
    f.add_argument('--runs', type=int, default=1)
    c = sub.add_parser('check')
    c.add_argument('slots', nargs='*')
    d = sub.add_parser('diff')
    d.add_argument('a')
    d.add_argument('b')
    ap.add_argument('--native-records', action='store_true',
                    help='the native game records (record, fuzz); the original plays back')
    args = ap.parse_args()
    global use_windows
    use_windows = args.windows

    if args.cmd == 'diff':
        sys.exit(0 if compare(args.a, args.b, 'A', 'B') else 1)
    efz = setup()
    if args.cmd == 'record':
        record(efz, args.slot, args.spec, args.ticks, args.native_records)
    elif args.cmd == 'play':
        sys.exit(0 if play(efz, args.slot, args.runs) else 1)
    elif args.cmd == 'check':
        slots = args.slots or sorted(n[4:-4] for n in os.listdir(os.path.join(GAME, 'replay'))
                                     if n.startswith('data') and n.endswith('.rep'))
        failed = []
        for slot in slots:
            original = trace_path(f'trace-{slot}-original0.txt')
            if not os.path.isfile(original):
                print(f'data{slot}.rep: no trace of the original playing it; run play first')
                failed.append(slot)
                continue
            run_native(efz, {'EFZ_TRACE': f'trace-{slot}-native.txt', 'EFZ_TRACE_PLAY': slot,
                             'EFZ_TRACE_FAST': '1'})
            print(f'data{slot}.rep: the original against the native game')
            if not compare(original, trace_path(f'trace-{slot}-native.txt')):
                failed.append(slot)
        print(f'{len(slots) - len(failed)} of {len(slots)} replays agree')
        sys.exit(1 if failed else 0)
    elif args.cmd == 'fuzz':
        rng = random.Random(args.seed)
        failed = []
        for i in range(args.count):
            slot = f'{1 + i // 9 % 9}-{1 + i % 9}'
            spec = ':'.join(str(x) for x in (rng.choice(CHARACTERS), rng.choice(CHARACTERS),
                                             rng.choice(STAGES), rng.randrange(6),
                                             rng.randrange(6), rng.randrange(1, 1 << 30)))
            print(f'== {slot}: {spec}')
            record(efz, slot, spec, args.ticks, args.native_records)
            if not play(efz, slot, args.runs):
                failed.append((slot, spec))
        print(f'{args.count - len(failed)} of {args.count} replays agree')
        for slot, spec in failed:
            print(f'  differs: data{slot}.rep ({spec})')
        sys.exit(1 if failed else 0)


if __name__ == '__main__':
    main()
