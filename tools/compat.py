#!/usr/bin/env python3
"""The compatibility test (docs/compat.md): every change must play the original's game.

The suite is tests/compat/suite.txt: replays (tests/compat/replays/*.rep, both players
human) and CPU fights (a seed and who plays each side; the game's CPU never runs in a
replay). Each case runs in a build with the harness of src/trace.cpp, which logs the
whole game state, hashed, after every tick of the fight. The reference is the original:
efz.exe's code, byte for byte, as of the git tag `compat-reference`, plus the harness,
run under wine. tests/compat/reference.txt holds the digest of its log for every case,
so a check needs no logs of the original: only the game data and the build to test.

    tools/compat.py check [CASES]           every case (or those named, or matching a
                                            prefix such as fuzz1-) in both the native game
                                            and the headless runner (efz-headless, docs/
                                            headless.md, its game moved to a copy on a new
                                            thread every HOP frames, as the training
                                            library does): each log must be the reference's,
                                            byte for byte, and the two the same
        --mode game|headless                one of the two only
        --no-reference                      only that the two write the same logs: for a
                                            build that doesn't give the reference's (on a
                                            machine where the untouched source doesn't)
        --windows                           the native game's Windows builds, under 64-bit
                                            wine (build/windows/efz.exe, efz-headless.exe)
        --exe PATH                          a 32-bit Windows build of efz.exe with the
                                            harness (make trace), under wine; that only
        --native PATH                       another native build (default build/native/efz)
        --headless PATH                     its headless runner (default efz-headless next
                                            to the game)
    tools/compat.py explain CASE            where and how a build parts from the reference:
                                            the first tick, the status, the blocks of state
                                            and the members (needs libclang to name them);
                                            --mode headless: the headless runner's
    tools/compat.py reference [CASES]       the reference plays the cases: its logs are
                                            cached, and each digest must be the recorded
                                            one (--update records new or changed ones)
    tools/compat.py build-reference         build/reference/efz.exe from the tag (make trace)
    tools/compat.py add-fuzz COUNT PREFIX   the reference records COUNT replays of random
                                            characters, stages and scripted input
        [--seed S] [--ticks T] [--native]   (--native: the native game records them; the
                                            reference only has to play them back)
    tools/compat.py add-cpu NAME SPEC TICKS a fight: SPEC = P1:P2:STAGE:PAL1:PAL2:SEED:C1:C2,
                                            C = 1 for the game's CPU, 0 scripted input
    tools/compat.py coverage [CASES]        the suite in a native build with gcov: which
                                            lines of src/ it runs, file by file, and the
                                            actions each character reaches
    tools/compat.py diff A B                compare two logs
    -j N                                    run N cases at once (default: half the CPUs)

EFZ_DIR is the folder of the original game (its data). Work folders, the wine prefixes
and the reference's cached logs are in $EFZ_COMPAT (default ~/.local/share/efz-decomp/compat2).
Checking native builds needs neither docker nor wine, and works on Windows too (builds
in Visual Studio's configuration folders, build/native/RelWithDebInfo/efz.exe, are
found).
"""
import argparse
import concurrent.futures
import hashlib
import json
import os
import random
import re
import shutil
import struct
import subprocess
import sys
import threading

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
TESTS = os.path.join(REPO, 'tests', 'compat')
SUITE = os.path.join(TESTS, 'suite.txt')
DIGESTS = os.path.join(TESTS, 'reference.txt')
REPLAYS = os.path.join(TESTS, 'replays')
TAG = 'compat-reference'
REFERENCE_EXE = os.path.join(REPO, 'build', 'reference', 'efz.exe')
NATIVE = os.path.join(REPO, 'build', 'native', 'efz')
HEADLESS_NAME = 'efz-headless'
WINDOWS = os.path.join(REPO, 'build', 'windows', 'efz.exe')
# The headless runner moves its game into a copy on a new thread every HOP frames
# (efz-headless --hop): a prime, so that the moves fall on every phase of the game's
# frame-parity logic.
HOP = 97
# How reports name the builds under test.
LABELS = {'game': 'game', 'headless': 'headless runner'}
COVERAGE_DIR = os.path.join(REPO, 'build', 'coverage')
HOME = os.environ.get('EFZ_COMPAT', os.path.expanduser('~/.local/share/efz-decomp/compat2'))
CACHE = os.path.join(HOME, 'reference')
IMAGE = 'efz-revival-test'
IMAGE64 = 'efz-wine64'
NATIVE_IMAGE = 'efz-native'

FIELDS = ['action', 'frame', 'x', 'y', 'vx', 'vy', 'hp', 'combo start hp', 'combo damage',
          'hits', 'gauge', 'facing']
BLOCKS = ['p1', 'p1obj', 'p1char', 'p2', 'p2obj', 'p2char', 'scene', 'game', 'fx']
# Characters by replay number (CScene2::CreateCharacter), the stages a fight can use.
CHARACTER_NAMES = ['nanase', 'ayu', 'mai', 'makoto', 'akane', 'mayu', 'nagamori', 'misaki',
                   'shiori', 'sayuri', 'nayuki', 'mio', 'exnanase', 'kaori', 'ikumi',
                   'mishio', 'akiko', 'nayukib', 'mizukab', 'kanna', 'kano', 'minagi',
                   'nayuki', 'misuzu', 'mizuka']
CHARACTERS = list(range(0x19))
STAGES = list(range(0x17))


def die(msg):
    sys.exit(f'tools/compat.py: {msg}')


# --- The suite.

class Case:
    """A line of suite.txt: `NAME replay [TICKS]` or `NAME cpu SPEC TICKS`."""

    def __init__(self, line):
        f = line.split()
        self.name, self.kind = f[0], f[1]
        if self.kind == 'replay':
            self.spec = None
            self.ticks = int(f[2]) if len(f) > 2 else None
        elif self.kind == 'cpu':
            self.spec, self.ticks = f[2], int(f[3])
        else:
            die(f'suite.txt: unknown kind {self.kind} for {self.name}')

    def characters(self):
        """The two characters' numbers."""
        if self.kind == 'cpu':
            return [int(x) for x in self.spec.split(':')[:2]]
        with open(os.path.join(REPLAYS, f'{self.name}.rep'), 'rb') as f:
            return list(struct.unpack('<hh', f.read(4)))

    def line(self):
        if self.kind == 'replay':
            return f'{self.name} replay' + (f' {self.ticks}' if self.ticks else '')
        return f'{self.name} cpu {self.spec} {self.ticks}'


def read_suite():
    cases = []
    with open(SUITE) as f:
        for line in f:
            line = line.split('#')[0].strip()
            if line:
                cases.append(Case(line))
    return cases


def select(cases, names):
    """The cases named, or whose names start with one of `names` ending in - or *."""
    if not names:
        return cases
    out = []
    for n in names:
        hit = [c for c in cases if c.name == n or (n.endswith(('-', '*')) and
                                                   c.name.startswith(n.rstrip('*')))]
        if not hit:
            die(f'no case {n} in suite.txt')
        out += [c for c in hit if c not in out]
    return out


def read_digests():
    """{case: (ticks, sha256)} from reference.txt."""
    out = {}
    if os.path.exists(DIGESTS):
        with open(DIGESTS) as f:
            for line in f:
                line = line.split('#')[0].split()
                if line:
                    out[line[0]] = (int(line[1]), line[2])
    return out


def write_digests(digests):
    with open(DIGESTS, 'w') as f:
        f.write('# The reference\'s log of each case of suite.txt: ticks and sha256.\n'
                '# Written by tools/compat.py reference --update; see docs/compat.md.\n')
        order = [c.name for c in read_suite()]
        for name in sorted(digests, key=lambda n: order.index(n) if n in order else 1 << 30):
            ticks, digest = digests[name]
            f.write(f'{name} {ticks} {digest}\n')


def digest(path):
    """(ticks, sha256) of a log."""
    h = hashlib.sha256()
    ticks = 0
    with open(path, 'rb') as f:
        for line in f:
            h.update(line)
            if not line.startswith(b'#'):
                ticks += 1
    return ticks, h.hexdigest()


# --- Running a build.

def efz_dir():
    """The game's data: an EFZ 4.02 install, or a pack of tools/compatpack.py (which
    has no efz.exe; only make check, for the reference, needs that)."""
    efz = os.environ.get('EFZ_DIR')
    if not efz or not os.path.isfile(os.path.join(efz, 'system', 'effect', 'effect.pat')):
        die('set EFZ_DIR to the folder of an EFZ 4.02 install, or a pack of '
            'tools/compatpack.py')
    return os.path.abspath(efz)


_setup_lock = threading.Lock()


def binary(path):
    """`path`, or where a build put it under another name: with .exe, or in a Visual
    Studio configuration folder next to it."""
    folder, name = os.path.split(path)
    configs = ('RelWithDebInfo', 'Release', 'Debug')
    for d in (folder, *(os.path.join(folder, c) for c in configs)):
        for n in (name, name + '.exe'):
            if os.path.isfile(os.path.join(d, n)):
                return os.path.join(d, n)
    return path


def game_dir(worker, links):
    """A game folder of the worker's own: a fixed key.ini (the data folder's, written
    over each time), an empty replay folder, and with `links` links to EFZ_DIR's files
    (for efz.exe, which reads its data from its folder; the native builds take
    --data)."""
    efz = efz_dir()
    game = os.path.join(HOME, 'work', f'game{worker}')
    os.makedirs(os.path.join(game, 'replay'), exist_ok=True)
    for name in os.listdir(efz) if links else ():
        if name.lower() in ('efz.exe', 'key.ini', 'replay'):
            continue
        link = os.path.join(game, name)
        if not os.path.lexists(link):
            os.symlink(os.path.join(efz, name), link)
    key = os.path.join(game, 'key.ini')
    if os.path.lexists(key):
        os.remove(key)
    if os.path.exists(os.path.join(efz, 'key.ini')):
        shutil.copyfile(os.path.join(efz, 'key.ini'), key)
    for name in os.listdir(os.path.join(game, 'replay')):
        os.remove(os.path.join(game, 'replay', name))
    return game


def run_container(args, timeout):
    """docker run ARGS; a container still running after `timeout` seconds (wine hangs
    now and then) is killed."""
    name = f'efz-compat-{os.getpid()}-{threading.get_ident()}'
    try:
        subprocess.run(['docker', 'run', '--name', name] + args, timeout=timeout,
                       stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except subprocess.TimeoutExpired:
        subprocess.run(['docker', 'kill', name], capture_output=True)
    subprocess.run(['docker', 'rm', '-f', name], capture_output=True)


def wine_prefix(name, image, boot):
    """The worker's wine prefix: a copy of one booted once (wineboot is slow)."""
    prefix = os.path.join(HOME, 'work', name)
    if os.path.isfile(os.path.join(prefix, '.compat-setup')):
        return prefix
    template = os.path.join(HOME, 'work', f'{image}-template')
    with _setup_lock:
        if not os.path.isfile(os.path.join(template, '.compat-setup')):
            os.makedirs(template, exist_ok=True)
            run_container(['--rm', '--init', '--network', 'none', '-v', f'{template}:/wine',
                           '-e', 'WINEPREFIX=/wine', '-e', 'WINEDEBUG=-all', *boot[0], image,
                           'bash', '-c', f'{boot[1]} >/dev/null 2>&1; wineserver -w; '
                           'touch /wine/.compat-setup'], 600)
        if os.path.exists(prefix):
            shutil.rmtree(prefix)
        shutil.copytree(template, prefix, symlinks=True)
    return prefix


def run_wine(exe, game, env, worker, timeout):
    """A 32-bit Windows efz.exe under wine on a virtual display."""
    shutil.copyfile(exe, os.path.join(game, 'efz.exe'))
    prefix = wine_prefix(f'wine{worker}', IMAGE, ([], 'wineboot -i'))
    envs = [x for k, v in env.items() for x in ('-e', f'{k}={v}')]
    script = '''
Xvfb :99 -screen 0 1024x768x24 >/dev/null 2>&1 &
sleep 1
wine explorer /desktop=EFZ,640x480 efz.exe >/dev/null 2>&1
wineserver -w
'''
    efz = efz_dir()
    run_container(['--rm', '--init', '--network', 'none',
                   '-v', f'{efz}:{efz}:ro', '-v', f'{game}:/run/game', '-v', f'{prefix}:/wine',
                   '-e', 'WINEPREFIX=/wine', '-e', 'WINEDEBUG=-all', '-e', 'DISPLAY=:99',
                   *envs, '-w', '/run/game', IMAGE, 'bash', '-c', script], timeout)


def run_windows(exe, args, game, env, worker, timeout):
    """One of the native game's 64-bit Windows builds (efz.exe, efz-headless.exe) under
    wine."""
    prefix = wine_prefix(f'wine64-{worker}', IMAGE64, (['-e', 'WINEARCH=win64'],
                                                       '/usr/lib/wine/wine64 wineboot -i'))
    envs = [x for k, v in env.items() for x in ('-e', f'{k}={v}')]
    script = (f'/usr/lib/wine/wine64 /bin64/{os.path.basename(exe)} '
              r"--data 'Z:\efz' --save 'Z:\run\game' " + ' '.join(args))
    run_container(['--rm', '--init', '--network', 'none',
                   '-v', f'{efz_dir()}:/efz:ro', '-v', f'{game}:/run/game',
                   '-v', f'{prefix}:/wine', '-v', f'{os.path.dirname(exe)}:/bin64:ro',
                   '-e', 'WINEPREFIX=/wine', '-e', 'WINEARCH=win64', '-e', 'WINEDEBUG=-all',
                   *envs, '-w', '/run/game', IMAGE64, 'bash', '-c', script], timeout)


class Build:
    """What runs a case: 'native' (a host binary: the game or the headless runner),
    'windows' (one of those built for Windows, under wine), or 'exe' (efz.exe under
    wine; the reference is one). `name` is what reports call it, `args` what it runs
    with besides --data and --save."""

    def __init__(self, kind, path=None, env=None, name='game', args=()):
        self.kind, self.path, self.env = kind, path, env or {}
        self.name, self.args = name, list(args)
        if kind in ('native', 'windows'):
            self.path = path = binary(path or WINDOWS)
        if kind in ('native', 'exe') and not os.path.isfile(path):
            hint = ''
            if kind == 'native' and name == 'headless':
                hint = (': build it (cmake --build ... --target efz-headless), or check the '
                        'game alone with --mode game')
            elif kind == 'native':
                hint = ': run tools/native.sh'
            die(f'no {path}{hint}')
        if kind == 'windows' and not os.path.isfile(path):
            die(f'no {path}: run tools/native.sh windows')

    def run(self, case, worker, out, extra=None, timeout=1200, record_to=None):
        """Runs `case`; its log goes to `out`. A recording's replay is copied to
        `record_to`. Returns True if a log was written."""
        game = game_dir(worker, links=self.kind == 'exe')
        env = {'EFZ_TRACE': 'trace.txt', 'EFZ_TRACE_FAST': '1'}
        if case.kind == 'replay' and record_to is None:
            shutil.copyfile(os.path.join(REPLAYS, f'{case.name}.rep'),
                            os.path.join(game, 'replay', 'data1-1.rep'))
            env['EFZ_TRACE_PLAY'] = '1-1'
        else:
            env['EFZ_TRACE_RECORD'] = f'1-1:{case.spec}'
        if case.ticks:
            env['EFZ_TRACE_TICKS'] = str(case.ticks)
        env.update(extra or {})
        trace = os.path.join(game, 'trace.txt')
        if os.path.exists(trace):
            os.remove(trace)
        if self.kind in ('native', 'windows'):  # SDL3, without a display or sound
            env.update(SDL_VIDEO_DRIVER='offscreen', SDL_AUDIO_DRIVER='dummy')
        if self.kind == 'native':
            subprocess.run([self.path, '--data', efz_dir(), '--save', game, *self.args],
                           env=dict(os.environ, **self.env, **env), cwd=game, timeout=timeout,
                           stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, check=False)
        elif self.kind == 'windows':
            run_windows(self.path, self.args, game, env, worker, timeout)
        else:
            run_wine(self.path, game, env, worker, timeout)
        if not os.path.isfile(trace):
            return False
        shutil.move(trace, out)
        for name in os.listdir(game):
            if name.startswith('trace') and name != 'trace.txt':
                shutil.move(os.path.join(game, name), out + name[5:])
        if record_to:
            rep = os.path.join(game, 'replay', 'data1-1.rep')
            if not os.path.isfile(rep):
                return False
            shutil.copyfile(rep, record_to)
        return True


def parallel(jobs, items, fn):
    """fn(item, worker) for each item, `jobs` at a time; results in order."""
    free = list(range(jobs))
    lock = threading.Lock()

    def one(item):
        with lock:
            w = free.pop()
        try:
            return fn(item, w)
        finally:
            with lock:
                free.append(w)

    with concurrent.futures.ThreadPoolExecutor(jobs) as ex:
        yield from ex.map(one, items)


# --- Logs.

def read_trace(path):
    """The log's ticks: (tick, replay position, player 1, player 2, block hashes)."""
    rows = []
    with open(path) as f:
        for line in f:
            if line.startswith('#'):
                continue
            body, _, hashes = line.partition('#')
            parts = [p.split() for p in body.split('|')]
            if len(parts) != 3:
                continue
            rows.append((parts[0], parts[1], parts[2], hashes.split()))
    return rows


def describe(player):
    """The player's fields, doubles decoded."""
    out = []
    for name, value in zip(FIELDS, player):
        if name in ('x', 'y', 'vx', 'vy'):
            value = repr(struct.unpack('>d', bytes.fromhex(value))[0])
        out.append(f'{name}={value}')
    return ' '.join(out)


def first_difference(a, b):
    """The index of the first tick two logs disagree on, len if one ends early, None if
    they are the same."""
    n = min(len(a), len(b))
    for i in range(n):
        if a[i] != b[i]:
            return i
    return None if len(a) == len(b) else n


def compare(a_path, b_path, a_name='reference', b_name='build'):
    """Prints where two logs part; returns the index of that tick, or None."""
    a, b = read_trace(a_path), read_trace(b_path)
    i = first_difference(a, b)
    if i is None:
        print(f'  {len(a)} ticks agree')
        return None
    if i == min(len(a), len(b)):
        print(f'  {a_name} has {len(a)} ticks, {b_name} {len(b)}')
        return i
    print(f'  tick {a[i][0][0]}: first difference')
    for k in range(max(0, i - 2), min(len(a), len(b), i + 3)):
        notes = []
        if a[k][0][1] != b[k][0][1]:
            notes.append(f'replay position {a[k][0][1]} != {b[k][0][1]}')
        for side in (1, 2):
            diff = [f'{FIELDS[j]} {x} != {y}'
                    for j, (x, y) in enumerate(zip(a[k][side], b[k][side])) if x != y]
            if diff:
                notes.append(f'P{side} ' + ', '.join(diff))
        blocks = [BLOCKS[j] for j, (x, y) in enumerate(zip(a[k][3], b[k][3])) if x != y]
        if blocks:
            notes.append('state differs in ' + ' '.join(blocks))
        if notes:
            print(f'    tick {a[k][0][0]}: ' + '; '.join(notes))
    for side in (1, 2):
        print(f'    {a_name} P{side}: {describe(a[i][side])}')
        print(f'    {b_name} P{side}: {describe(b[i][side])}')
    return i


# --- Commands.

def ensure_reference():
    if not os.path.isfile(REFERENCE_EXE):
        die(f'no {REFERENCE_EXE}: run tools/compat.py build-reference')
    return Build('exe', REFERENCE_EXE)


def cached(case):
    return os.path.join(CACHE, f'{case.name}.txt')


def cmd_build_reference(args):
    """The tag's sources, built with the harness (make trace) in build/reference."""
    tree = os.path.join(REPO, 'build', 'reference', 'tree')
    if os.path.exists(tree):
        shutil.rmtree(tree)
    os.makedirs(tree)
    archive = subprocess.run(['git', '-C', REPO, 'archive', TAG], capture_output=True,
                             check=True).stdout
    subprocess.run(['tar', '-x', '-C', tree], input=archive, check=True)
    subprocess.run(['make', '-C', tree, f'-j{os.cpu_count()}', 'trace', 'check',
                    f'EFZ_DIR={efz_dir()}'], check=True)
    shutil.copyfile(os.path.join(tree, 'build', 'trace', 'efz.exe'), REFERENCE_EXE)
    print(f'built {REFERENCE_EXE} from {TAG}')


def cmd_reference(args):
    """The reference plays the cases into the cache; digests are checked or recorded."""
    build = ensure_reference()
    cases = select(read_suite(), args.cases)
    digests = read_digests()
    os.makedirs(CACHE, exist_ok=True)
    bad = []

    def one(case, worker):
        out = cached(case)
        for attempt in range(2):
            if build.run(case, worker, out):
                return case, digest(out)
        return case, None

    for case, d in parallel(args.jobs, cases, one):
        if d is None:
            print(f'{case.name}: the reference wrote no log')
            bad.append(case.name)
        elif case.name not in digests or digests[case.name] != d:
            if args.update:
                note = 'new' if case.name not in digests else 'CHANGED'
                print(f'{case.name}: {d[0]} ticks, {note}')
                digests[case.name] = d
            else:
                print(f'{case.name}: the reference\'s log is not the recorded one')
                bad.append(case.name)
        else:
            print(f'{case.name}: {d[0]} ticks, as recorded')
    if args.update:
        write_digests(digests)
    print(f'{len(cases) - len(bad)} of {len(cases)} cases as recorded')
    return 1 if bad else 0


def test_builds(args, modes=('game', 'headless')):
    """The builds under test: the game and its headless runner (efz-headless next to it,
    moving its game every HOP frames), or those of `modes`; with --exe that build only."""
    if args.exe:
        return [Build('exe', os.path.abspath(args.exe), name='efz.exe')]
    hop = ['--hop', str(HOP)]
    if args.windows:
        game = WINDOWS
        headless = os.path.join(os.path.dirname(WINDOWS), HEADLESS_NAME + '.exe')
        kind = 'windows'
    else:
        game = os.path.abspath(args.native or NATIVE)
        headless = os.path.abspath(getattr(args, 'headless', None) or
                                   os.path.join(os.path.dirname(game), HEADLESS_NAME))
        kind = 'native'
    builds = []
    if 'game' in modes:
        builds.append(Build(kind, game, name='game'))
    if 'headless' in modes:
        builds.append(Build(kind, headless, name='headless', args=hop))
    return builds


def cmd_check(args):
    modes = ('game', 'headless') if args.mode == 'both' else (args.mode,)
    builds = test_builds(args, modes)
    if args.no_reference and len(builds) < 2:
        die('--no-reference compares the game with the headless runner: it needs both')
    cases = select(read_suite(), args.cases)
    digests = read_digests()
    for b in builds:
        os.makedirs(os.path.join(HOME, 'logs', b.name), exist_ok=True)

    def one(job, worker):
        case, b = job
        out = os.path.join(HOME, 'logs', b.name, f'{case.name}.txt')
        if os.path.exists(out):
            os.remove(out)
        ok = b.run(case, worker, out)
        return case, b, out if ok else None

    failed = {b.name: [] for b in builds}
    apart = []
    same = 0
    outs = {}
    # Results come in the jobs' order, so a case's builds come together: each case is
    # reported once all of its are in.
    for case, b, out in parallel(args.jobs, [(c, b) for c in cases for b in builds], one):
        outs[b.name] = out
        if len(outs) < len(builds):
            continue
        for name, out in outs.items():
            label = LABELS.get(name, name)
            if out is None:
                print(f'{case.name}: FAILED in the {label}, no log (it crashed or never '
                      'reached the fight)')
                failed[name].append(case.name)
                continue
            if args.no_reference:
                continue
            if case.name not in digests:
                print(f'{case.name}: no reference digest; run tools/compat.py reference --update')
                failed[name].append(case.name)
                continue
            if digest(out) == digests[case.name]:
                if args.verbose:
                    print(f'{case.name}: ok in the {label}, {digests[case.name][0]} ticks')
                continue
            failed[name].append(case.name)
            print(f'{case.name}: FAILED in the {label}')
            if os.path.isfile(cached(case)) and digest(cached(case)) == digests[case.name]:
                compare(cached(case), out)
            else:
                print(f'  (no cached reference log: tools/compat.py reference {case.name}, '
                      f'then tools/compat.py explain {case.name} --mode {name})')
        if len(outs) == 2 and None not in outs.values():
            game, headless = outs['game'], outs['headless']
            if digest(game) != digest(headless):
                apart.append(case.name)
                print(f'{case.name}: FAILED, the game and the headless runner part')
                compare(game, headless, 'game', 'headless')
            else:
                same += 1
                if args.verbose and args.no_reference:
                    print(f'{case.name}: the same in the game and the headless runner')
        outs = {}
    for b in builds:
        if not args.no_reference:
            print(f'{len(cases) - len(failed[b.name])} of {len(cases)} cases agree with the '
                  f'reference in the {LABELS.get(b.name, b.name)}' +
                  (f' ({b.path})' if b.kind != 'exe' else ''))
    if len(builds) == 2:
        # Only cases with both logs count: a case neither could play isn't "the same".
        print(f'{same} of {len(cases)} cases are the same in the game and the headless '
              'runner')
    bad = sorted(set(apart).union(*failed.values()))
    if bad:
        print('failed: ' + ' '.join(bad))
    return 1 if bad else 0


def read_dump(path):
    out = {}
    with open(path, 'rb') as f:
        while True:
            h = f.read(12)
            if len(h) < 12:
                break
            tick, block, size = struct.unpack('<III', h)
            out[(tick, block)] = f.read(size)
    return out


def layout_names():
    """{class: [(offset, size, name)]} for the classes the blocks hold, from
    tools/members.py's clang layout; None without libclang."""
    try:
        out = subprocess.run([sys.executable, os.path.join(REPO, 'tools', 'members.py'),
                              'fields'], capture_output=True, text=True, check=True).stdout
        return json.loads(out)
    except (subprocess.CalledProcessError, json.JSONDecodeError, FileNotFoundError):
        return None


def name_offset(layout, cls, offset, base=0):
    """The member of `cls` holding byte `offset` (block offset + base)."""
    if not layout or cls not in layout:
        return ''
    at = offset + base
    best = ''
    for off, size, name in layout[cls]:
        if off <= at < off + max(size, 1):
            best = f'{name}' + (f'+{at - off:#x}' if at != off else '')
    return best


# The fx block: m_effectHead and m_effectTail, m_effectActive, m_effectUnk1d84,
# m_effectUnk2784, 4 bytes, then the 640 effects of 0x70 bytes (src/efz.h).
FX_ACTIVE = 4
FX_EFFECTS = 4 + 0x280 * 4 * 2 + 0x280 + 4


def describe_effect(block, i):
    o = FX_EFFECTS + i * 0x70
    active = struct.unpack_from('<i', block, FX_ACTIVE + i * 4)[0]
    kind, frame, timer = struct.unpack_from('<HHH', block, o)
    x, y, vx, vy = struct.unpack_from('<dddd', block, o + 0x18)
    return (f'active {active} type {kind:#x} frame {frame} timer {timer} x {x!r} y {y!r} '
            f'vx {vx!r} vy {vy!r}')


def cmd_explain(args):
    case = select(read_suite(), [args.case])[0]
    build = test_builds(args, (args.mode,))[0]
    ref = ensure_reference()
    out_dir = os.path.join(HOME, 'explain')
    os.makedirs(out_dir, exist_ok=True)
    ref_log = cached(case)
    if not os.path.isfile(ref_log):
        ref.run(case, 0, ref_log)
    log = os.path.join(out_dir, f'{case.name}.txt')
    build.run(case, 1, log)
    a, b = read_trace(ref_log), read_trace(log)
    i = compare(ref_log, log)
    if i is None:
        return 0
    tick = int(a[min(i, len(a) - 1)][0][0])
    window = {'EFZ_TRACE_DUMP': 'trace-dump.bin', 'EFZ_TRACE_DUMP_FROM': str(max(0, tick - 1)),
              'EFZ_TRACE_DUMP_TO': str(tick)}
    ref.run(case, 0, os.path.join(out_dir, 'ref.txt'), window)
    build.run(case, 1, os.path.join(out_dir, 'build.txt'), window)
    da = read_dump(os.path.join(out_dir, 'ref.txt-dump.bin'))
    db = read_dump(os.path.join(out_dir, 'build.txt-dump.bin'))
    layout = layout_names()
    chars = case.characters()
    classes = {'p1': 'CPlayer', 'p2': 'CPlayer', 'p1obj': 'PlayerObject',
               'p2obj': 'PlayerObject', 'scene': None, 'game': 'CGame', 'fx': 'CGame'}
    for key in sorted(da):
        if key not in db or da[key] == db[key]:
            continue
        t, block = key
        x, y = da[key], db[key]
        name = BLOCKS[block]
        offs = [k for k in range(min(len(x), len(y))) if x[k] != y[k]]
        print(f'  tick {t}, block {name}: {len(offs)} bytes differ')
        shown = set()
        shown_effects = set()
        for o in offs:
            if name.endswith('char'):
                cls = 'C' + CHARACTER_NAMES[chars[int(name[1]) - 1]]
                where = name_offset(layout, cls.lower(), o, 0x3138) or f'+{0x3138 + o:#x}'
            elif name.endswith('obj'):
                where = f'm_objects[{o // 0x98}].' + (name_offset(layout, 'playerobject',
                                                                  o % 0x98) or f'+{o % 0x98:#x}')
            elif name == 'fx':
                effects = FX_EFFECTS
                if o >= effects:
                    i = (o - effects) // 0x70
                    where = f'm_effects[{i}]+{(o - effects) % 0x70:#x}'
                    if i not in shown_effects:
                        shown_effects.add(i)
                        print(f'    effect {i}: reference {describe_effect(x, i)}')
                        print(f'    effect {i}: build     {describe_effect(y, i)}')
                    continue
                base = layout and next((off for off, _, n in layout.get('cgame', [])
                                        if n == 'm_effectHead'), 0) or 0
                where = name_offset(layout, 'cgame', o, base) or f'+{o:#x}'
            elif classes.get(name):
                where = name_offset(layout, classes[name].lower(), o) or f'+{o:#x}'
            else:
                where = f'byte {o:#x} of the scene block'
            field = where.split('+')[0]
            if field in shown:
                continue
            shown.add(field)
            print(f'    {where}: {x[o:o + 8].hex()} != {y[o:o + 8].hex()}')
            if len(shown) >= 40:
                print('    ...')
                break
    return 1


def cmd_add_fuzz(args):
    """The reference (or the native game) records random fights into the suite."""
    build = Build('native', NATIVE) if args.native else ensure_reference()
    rng = random.Random(args.seed)
    specs = []
    for i in range(args.count):
        spec = ':'.join(str(x) for x in (rng.choice(CHARACTERS), rng.choice(CHARACTERS),
                                         rng.choice(STAGES), rng.randrange(6),
                                         rng.randrange(6), rng.randrange(1, 1 << 30)))
        specs.append((f'{args.prefix}{i + 1:03d}', spec))
    existing = {c.name for c in read_suite()}
    specs = [s for s in specs if s[0] not in existing]

    def one(item, worker):
        name, spec = item
        tmp = Case(f'{name} cpu {spec}:0:0 {args.ticks}')
        rep = os.path.join(REPLAYS, f'{name}.rep')
        ok = build.run(tmp, worker, os.path.join(HOME, 'work', f'record-{name}.txt'),
                       record_to=rep)
        return name, spec, ok

    added = []
    for name, spec, ok in parallel(args.jobs, specs, one):
        print(f'{name}: {spec}: ' + ('recorded' if ok else 'FAILED'))
        if ok:
            added.append(name)
    with open(SUITE, 'a') as f:
        for name in added:
            f.write(f'{name} replay\n')
    print(f'added {len(added)} replays; now tools/compat.py reference --update {args.prefix}')


def cmd_add_cpu(args):
    if len(args.spec.split(':')) != 8:
        die('SPEC is P1:P2:STAGE:PAL1:PAL2:SEED:C1:C2')
    if any(c.name == args.name for c in read_suite()):
        die(f'{args.name} is in the suite already')
    with open(SUITE, 'a') as f:
        f.write(f'{args.name} cpu {args.spec} {args.ticks}\n')
    print(f'added {args.name}; now tools/compat.py reference --update {args.name}')


def cmd_coverage(args):
    """The suite in a coverage build; a summary of what it runs."""
    subprocess.run([os.path.join(REPO, 'tools', 'native.sh'), 'coverage'], check=True)
    for root, _, files in os.walk(COVERAGE_DIR):
        for name in files:
            if name.endswith('.gcda'):
                os.remove(os.path.join(root, name))
    cases = select(read_suite(), args.cases)
    # The objects record /work/build/coverage/...: strip /work, prefix the repo.
    build = Build('native', os.path.join(COVERAGE_DIR, 'efz'),
                  {'GCOV_PREFIX': REPO, 'GCOV_PREFIX_STRIP': '1'})
    reached = {}
    logs = os.path.join(HOME, 'coverage-logs')
    os.makedirs(logs, exist_ok=True)

    def one(case, worker):
        out = os.path.join(logs, f'{case.name}.txt')
        return case, build.run(case, worker, out, timeout=3600) and out

    for case, out in parallel(args.jobs, cases, one):
        if not out:
            print(f'{case.name}: no log')
            continue
        chars = case.characters()
        for row in read_trace(out):
            for side in (1, 2):
                reached.setdefault(chars[side - 1], set()).add(int(row[side][0], 16))
    subprocess.run(['docker', 'run', '--rm', '-u', f'{os.getuid()}:{os.getgid()}',
                    '-v', f'{REPO}:/work', '-w', '/work', NATIVE_IMAGE, 'python3',
                    'tools/coverage_report.py', 'build/coverage'], check=True)
    report = os.path.join(COVERAGE_DIR, 'report.json')
    with open(report) as f:
        files = json.load(f)
    total = [0, 0]
    print(f'{"file":24} {"lines":>7} {"run":>7}    functions never run')
    for name in sorted(files):
        lines, hit, never = files[name]['lines'], files[name]['hit'], files[name]['never']
        total[0] += lines
        total[1] += hit
        print(f'{name:24} {lines:7} {100.0 * hit / max(lines, 1):6.1f}%    {len(never)}')
    print(f'{"all of src/":24} {total[0]:7} {100.0 * total[1] / max(total[0], 1):6.1f}%')
    print()
    print('actions reached, by character:')
    for c in sorted(reached):
        print(f'  {CHARACTER_NAMES[c]:9} {len(reached[c]):4}  ' +
              ' '.join(f'{p:x}' for p in sorted(reached[c])))
    with open(os.path.join(COVERAGE_DIR, 'actions.json'), 'w') as f:
        json.dump({CHARACTER_NAMES[c] + f'#{c}': sorted(v) for c, v in reached.items()}, f)
    print(f'\nper line: {COVERAGE_DIR}/gcov/*.gcov; never-run functions: {report}')


def main():
    sys.stdout.reconfigure(line_buffering=True)
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('-j', '--jobs', type=int, default=max(1, (os.cpu_count() or 2) // 2))
    sub = ap.add_subparsers(dest='cmd', required=True)

    def build_args(p):
        p.add_argument('--windows', action='store_true')
        p.add_argument('--exe')
        p.add_argument('--native')
        p.add_argument('--headless')

    c = sub.add_parser('check')
    c.add_argument('cases', nargs='*')
    c.add_argument('-v', '--verbose', action='store_true')
    c.add_argument('--mode', choices=['both', 'game', 'headless'], default='both')
    c.add_argument('--no-reference', action='store_true')
    build_args(c)
    e = sub.add_parser('explain')
    e.add_argument('case')
    e.add_argument('--mode', choices=['game', 'headless'], default='game')
    build_args(e)
    r = sub.add_parser('reference')
    r.add_argument('cases', nargs='*')
    r.add_argument('--update', action='store_true')
    sub.add_parser('build-reference')
    f = sub.add_parser('add-fuzz')
    f.add_argument('count', type=int)
    f.add_argument('prefix')
    f.add_argument('--seed', type=int, default=1)
    f.add_argument('--ticks', type=int, default=3000)
    f.add_argument('--native', action='store_true')
    a = sub.add_parser('add-cpu')
    a.add_argument('name')
    a.add_argument('spec')
    a.add_argument('ticks', type=int)
    v = sub.add_parser('coverage')
    v.add_argument('cases', nargs='*')
    d = sub.add_parser('diff')
    d.add_argument('a')
    d.add_argument('b')
    args = ap.parse_args()

    if args.cmd == 'diff':
        return 0 if compare(args.a, args.b, 'A', 'B') is None else 1
    return {'check': cmd_check, 'explain': cmd_explain, 'reference': cmd_reference,
            'build-reference': cmd_build_reference, 'add-fuzz': cmd_add_fuzz,
            'add-cpu': cmd_add_cpu, 'coverage': cmd_coverage}[args.cmd](args) or 0


if __name__ == '__main__':
    sys.exit(main())
