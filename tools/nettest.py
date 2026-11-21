#!/usr/bin/env python3
"""The network test (docs/compat.md, "The network layer"): netplay matches on one
machine's loopback, each checked from both ends.

    tools/nettest.py native             two native games, one hosting and one joining,
                                        at the game's speed: once as they are and once
                                        with 60 +- 20 ms on every datagram each sends
                                        (EFZ_NET_LAG), so that the rollback runs deep
        --lag MS[:JITTER]               that one only, with this lag (0: none)
        --frames N                      how long the host runs (default 3200 frames,
                                        about 300 of them to connect); Esc on the
                                        host's end at frame 1800 leaves the first
                                        fight, and a second follows
        --native PATH                   the build (default build/native/efz)
    tools/nettest.py revival            the native game against the original: efz.exe
                                        4.02 with EfzRevival 1.02h, under wine in the
                                        efz-revival-test docker image, with no network
                                        but the container's loopback; once with Revival
                                        hosting, once with the native game hosting
        --host revival|native           that one only
        --lag MS[:JITTER]               EFZ_NET_LAG for the native game's datagrams
        --fight S                       seconds of the first fight, which Esc on
                                        Revival's end ends (default 20)
        --native PATH                   the build (default build/native/efz)
        --revival DIR                   Revival's files (default $REVIVAL_DIR, else
                                        ~/.local/share/efz-decomp/revival/1.02h); they
                                        must be 1.02h's, unchanged
    --seed S                            the random keys' seed (default: a new one, shown)
    --keep                              keep the run folders of the matches that passed

Each end plays with random presses of P1's controls (the arrows, X, V, Z of a key.ini
written for the test), through character select into a fight; Esc leaves it (random
presses never end a match), both are back at character select, and a second fight
starts, in which the test stops. What must hold:

- Both ends got into a fight (two for native), on opposite sides, with the same seed.
- The sync records (frame, scene, FPU control word, both players' actions, inputs and
  positions, the random state: Revival's SharedData.h SyncBlock) the native game asks
  the other end for agree with its own on every frame compared, and most frames were
  compared. Against Revival, Revival's own comparison too (Debug = 1: logNet.txt's
  "Checked" lines, and no "ERROR:"); and if Revival left the first fight on a predicted
  frame, after which EfzRevival.dll makes no records, the comparison must have gone up
  to there.
- Both ends' replays of each fight are the same, byte for byte, up to the frame where
  the end that stopped first stopped. Against Revival, the fight the test stops in is
  compared by its words only: Revival writes the rest of a replay as the fight ends.

EFZ_DIR is the original game's folder (its data; for the revival test also its efz.exe,
which must be 4.02's). The runs go to $EFZ_COMPAT/net (default
~/.local/share/efz-decomp/compat2/net), each in a folder named for it, kept when it
fails. Exit code 0: every match passed.
"""
import argparse
import hashlib
import os
import random
import re
import shutil
import socket
import struct
import subprocess
import sys
import time

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DRIVER = os.path.join(REPO, 'tools', 'nettest-revival.sh')
IMAGE = 'efz-revival-test'

# What the revival test plays against: what players have (docs/recon.md, docs/revival.md).
EFZ_SHA256 = '3a1616d6c76d2eea08a95bb198d853e96cb6b9b3266e277ca1d167426dd66481'
REVIVAL_SHA256 = {
    'EfzRevival.exe': 'e2c8b136a36f829f4178daf96655ee952ffa465776ae204219cafc24b74b488f',
    'EfzRevival.dll': '0687e74bb40a8aadc91b591284bc962a320078394bdf7d23b9741d54e937f8aa',
    'DDRAW.dll': '4d83369bd40fca915ba8bbe8b46afabdcd626a0e97c4a1135f97a292db0ca72c',
}

# P1's controls in the test's key.ini (src/input.cpp, CInput::LoadBindings: a device
# byte and a DIK_ code each, up, down, left, right, A, B, C, D): the arrows, X, C, V, Z.
P1_BINDINGS = bytes([0, 0xc8, 0, 0xd0, 0, 0xcb, 0, 0xcd, 0, 0x2d, 0, 0x2e, 0, 0x2f, 0, 0x2c])
# Pressed at random: not C (B), which backs out of character select to the title, which
# in netplay leaves the match.
KEYS = ['Up', 'Down', 'Left', 'Right', 'X', 'V', 'Z']
# The native test's Esc, in the host's frames (--keys).
ESC_FRAME = 1800
# Of the sync records made, at least this share must have been compared: the last
# second or so of a match is always unanswered.
COMPARED = 0.75


def binary(path):
    """`path`, or where a build put it under another name (as tools/compat.py's)."""
    folder, name = os.path.split(path)
    for d in (folder, *(os.path.join(folder, c) for c in ('RelWithDebInfo', 'Release', 'Debug'))):
        for n in (name, name + '.exe'):
            if os.path.isfile(os.path.join(d, n)):
                return os.path.join(d, n)
    return path


def sha256(path):
    with open(path, 'rb') as f:
        return hashlib.sha256(f.read()).hexdigest()


def key_ini(efz, out):
    """The data folder's key.ini (its settings) with P1's controls the test's."""
    src = os.path.join(efz, 'key.ini')
    data = bytearray(open(src, 'rb').read()) if os.path.isfile(src) else bytearray()
    # (the game reads settings up to 0x26 and wants at least 0x20 bytes)
    data += bytes(max(0, 0x30 - len(data)))
    data[0:16] = P1_BINDINGS
    with open(out, 'wb') as f:
        f.write(data)


def key_script(rng, frames):
    """--keys: random presses of P1's controls from frame 30 on, 2-12 frames each."""
    events = []
    frame = 30
    while frame < frames:
        key = rng.choice(KEYS)
        events.append((frame, '+' + key))
        events.append((frame + rng.randint(2, 12), '-' + key))
        frame += rng.randint(3, 10)
    events.sort(key=lambda e: e[0])
    return ','.join(f'{f}:{k}' for f, k in events)


def free_udp_port():
    with socket.socket(socket.AF_INET, socket.SOCK_DGRAM) as s:
        s.bind(('127.0.0.1', 0))
        return s.getsockname()[1]


def read(path):
    try:
        with open(path, encoding='utf-8', errors='replace') as f:
            return f.read()
    except OSError:
        return ''


def native_log(logs):
    """The native game's efz.log in its --log-dir (one session)."""
    if not os.path.isdir(logs):
        return ''
    for session in sorted(os.listdir(logs)):
        text = read(os.path.join(logs, session, 'efz.log'))
        if text:
            return text
    return ''


class End:
    """What one end's log says of the match."""

    def __init__(self, name, log, save):
        self.note = None
        self.name = name
        self.log = log
        self.save = save
        m = re.search(r'the match starts: P(\d) here, delay (\d+), rollback (\d+), seed (\d+)', log)
        self.side = int(m.group(1)) if m else None
        self.seed = m.group(4) if m else None
        self.fights = len(re.findall(r'match \d+, fight at frame \d+', log))
        m = re.search(r'sync records: (\d+) made here(?: \((\d+) frames without\))?, (\d+) '
                      r'from \S+, compared to frame (-?\d+), (.*)', log)
        self.made, self.holes, self.got, self.compared, self.sync = (
            (int(m.group(1)), int(m.group(2) or 0), int(m.group(3)), int(m.group(4)),
             m.group(5).strip()) if m else (0, 0, 0, -1, None))
        self.desync = re.search(r'desync at frame (\d+)', log)
        m = re.search(r'the match ran (\d+) frames; (\d+) rollbacks ran (\d+) frames again, '
                      r'at most (\d+) at once', log)
        self.frames, self.rollbacks, self.deepest = (
            (int(m.group(1)), int(m.group(2)), int(m.group(4))) if m else (0, 0, 0))
        self.replays = [os.path.join(save, p) for p in
                        re.findall(r'replay saved: (.*?) \(\d+ frames\)', log)]
        # The frames a fight was left at (Esc, back to character select).
        self.left = [int(f) for f in re.findall(r'net: frame (\d+): scene 1 after \d+ frames of '
                                                r'scene 3', log)]

    def check(self, problems, revival=False):
        if self.side is None:
            problems.append(f'{self.name}: the match never started')
            return
        if self.fights == 0:
            problems.append(f'{self.name}: never got into a fight')
        if self.sync is None:
            problems.append(f'{self.name}: no summary of the sync records (did it end?)')
        elif self.sync != 'all the same':
            problems.append(f'{self.name}: sync records {self.sync}')
        if self.desync:
            problems.append(f'{self.name}: desync at frame {self.desync.group(1)}')
        if self.sync is not None and self.compared + 1 < COMPARED * (self.made + self.holes):
            # EfzRevival.dll makes no record after a frame it ran before this end's input
            # for it came and never ran again: a fight left on a predicted frame. Then
            # nothing can be compared after it, which is Revival's, not a failure, if the
            # comparison went that far.
            stop = self.left[0] if self.left else None
            if (revival and stop is not None and stop - 16 <= self.got <= stop + 16
                    and self.compared >= self.got - 16):
                self.note = (f'Revival made no sync records after frame {self.got - 1}, where '
                             f'it left fight 1 on a predicted frame (EfzRevival.dll\'s runFrame): '
                             f'after it only the replays are compared')
            else:
                problems.append(f'{self.name}: sync records compared to frame {self.compared} '
                                f'only, of {self.made + self.holes}')

    def summary(self):
        text = (f'{self.name}: P{self.side}, {self.frames} frames, {self.fights} fight(s), '
                f'{self.rollbacks} rollbacks (at most {self.deepest} frames), sync records '
                f'compared to frame {self.compared} of {self.made + self.holes}: {self.sync}')
        if self.holes:
            # A fight left on a frame run before the other end's input for it came (Esc
            # held, predicted): no rollback runs it again, so it has no record
            # (port/netplay/session.cpp, Session::RunFrame).
            text += f' ({self.holes} frame(s) without one: a fight left on a predicted frame)'
        if self.note:
            text += f'; {self.note}'
        return text


def parse_replay(data):
    """A netplay replay (Revival's writeExtendedReplay, port/netplay/session.cpp): the
    game's words, 30 blank records, then the random seed, the count of input words, both
    players' inputs of every confirmed frame, where the seed is, and -1. (words, seed,
    inputs), or None."""
    if len(data) < 8 or struct.unpack_from('<i', data, len(data) - 4)[0] != -1:
        return None
    offset = struct.unpack_from('<i', data, len(data) - 8)[0]
    if not 30 * 16 <= offset <= len(data) - 16:
        return None
    seed, count = struct.unpack_from('<Ii', data, offset)
    inputs = data[offset + 8:offset + 8 + 2 * count]
    if len(inputs) != 2 * count or offset + 8 + 2 * count != len(data) - 8:
        return None
    return data[:offset - 30 * 16], seed, inputs


def same_replays(a, b, problems, what, cut=False):
    """Both ends' replays of a fight: the same, up to where the end that stopped first
    stopped (the words and the inputs of the shorter one begin the longer one's). With
    `cut`, `a` may be a replay cut off as its game was closed in the fight (EfzRevival
    adds what follows the words only when the fight ends): then its words alone."""
    for path in (a, b):
        if not (path and os.path.isfile(path)):
            problems.append(f'{what}: no replay at {path}')
            return None
    raw = open(a, 'rb').read()
    x, y = parse_replay(raw), parse_replay(open(b, 'rb').read())
    if x is None and cut and y is not None:
        n = min(len(raw), len(y[0]))
        if n < 1024 or raw[:n] != y[0][:n]:
            problems.append(f'{what}: the cut-off replay\'s words differ: {a}, {b}')
            return None
        return f'the same words ({n} bytes; {os.path.basename(a)} was cut off as the match stopped)'
    if x is None or y is None:
        problems.append(f'{what}: not a netplay replay: {a if x is None else b}')
        return None
    if x[1] != y[1]:
        problems.append(f'{what}: the replays\' seeds differ ({x[1]}, {y[1]}): {a}, {b}')
        return None
    for part, (p, q) in (('words', (x[0], y[0])), ('inputs', (x[2], y[2]))):
        n = min(len(p), len(q))
        if p[:n] != q[:n]:
            at = next(i for i in range(n) if p[i] != q[i])
            problems.append(f'{what}: the replays\' {part} differ from byte {at}: {a}, {b}')
            return None
    frames = (len(x[2]) // 4, len(y[2]) // 4)
    return 'the same' if frames[0] == frames[1] else (
        f'the same up to frame {min(frames)} (the ends stopped {abs(frames[0] - frames[1])} '
        f'frame(s) apart)')


def report(name, problems, lines, folder, keep):
    ok = not problems
    print(f'{"PASS" if ok else "FAIL"} {name}')
    for line in lines:
        print(f'    {line}')
    for p in problems:
        print(f'    ! {p}')
    if ok and not keep:
        shutil.rmtree(folder, ignore_errors=True)
    else:
        print(f'    (the run is in {folder})')
    return ok


# --- Two native games

def native_match(args, efz, exe, work, lag, seed):
    name = f'native-lag{lag.replace(":", "+")}' if lag else 'native'
    folder = os.path.join(work, name)
    shutil.rmtree(folder, ignore_errors=True)
    ends = {}
    for who in ('host', 'join'):
        for sub in ('save', 'logs'):
            os.makedirs(os.path.join(folder, who, sub))
        key_ini(efz, os.path.join(folder, who, 'save', 'key.ini'))
    env = dict(os.environ, SDL_VIDEO_DRIVER='offscreen', SDL_AUDIO_DRIVER='dummy')
    env.pop('EFZ_NET_LAG', None)
    if lag:
        env['EFZ_NET_LAG'] = lag
    rng = random.Random(seed)
    port = free_udp_port()
    procs = {}
    for who in ('host', 'join'):
        frames = args.frames if who == 'host' else args.frames + 600
        keys = key_script(rng, frames)
        if who == 'host':
            # Esc in the first fight (character select takes 300-400 frames of random
            # keys, after about 300 to connect): both back to character select, both
            # write the fight's replay, then a second fight.
            keys += f',{ESC_FRAME}:+Escape,{ESC_FRAME + 10}:-Escape'
        cmd = [exe, '--data', efz, '--save', os.path.join(folder, who, 'save'),
               '--log-dir', os.path.join(folder, who, 'logs'), '--frames', str(frames),
               '--keys', keys, '--name', who.capitalize()]
        cmd += ['--host', '--port', str(port)] if who == 'host' else ['--join', f'127.0.0.1:{port}']
        out = open(os.path.join(folder, who, 'out.txt'), 'w')
        procs[who] = subprocess.Popen(cmd, stdout=out, stderr=subprocess.STDOUT, env=env)
        if who == 'host':
            # The joiner gives up after five seconds without an answer.
            deadline = time.time() + 20
            while time.time() < deadline and 'hosting on UDP port' not in native_log(
                    os.path.join(folder, 'host', 'logs')):
                time.sleep(0.2)
    problems = []
    limit = time.time() + args.frames / 64 * 2 + 120
    for who, p in procs.items():
        try:
            p.wait(timeout=max(1, limit - time.time()))
        except subprocess.TimeoutExpired:
            p.kill()
            problems.append(f'{who}: still running after {int(limit)} s: killed')
    for who in ('host', 'join'):
        ends[who] = End(who, native_log(os.path.join(folder, who, 'logs')),
                        os.path.join(folder, who, 'save'))
        ends[who].check(problems)
    h, j = ends['host'], ends['join']
    if h.side and min(h.fights, j.fights) < 2:
        problems.append(f'no second fight (Esc at frame {ESC_FRAME} of the host\'s: was it '
                        f'in the first?)')
    if h.side and j.side and h.side == j.side:
        problems.append(f'both ends are P{h.side}')
    if h.seed and j.seed and h.seed != j.seed:
        problems.append(f'the seeds differ: {h.seed} and {j.seed}')
    if len(h.replays) != len(j.replays):
        problems.append(f'host saved {len(h.replays)} replays, the joiner {len(j.replays)}')
    lines = [f'lag {lag or "none"}, seed {seed}', h.summary(), j.summary()]
    for i, (a, b) in enumerate(zip(h.replays, j.replays)):
        same = same_replays(a, b, problems, f'fight {i + 1}')
        if same:
            lines.append(f"fight {i + 1}'s replays: {same}")
    return report(name, problems, lines, folder, args.keep)


# --- Against EfzRevival 1.02h

def revival_ini(src, out, port):
    """Revival's EfzRevival.ini (UTF-16) with the test's settings: Debug on (logNet.txt
    compares the sync records), no hole-punching server, its name, the port, no music."""
    text = open(src, 'rb').read().decode('utf-16')
    settings = {'Debug': '1', 'HolePunchingServer': 'None', 'Name': 'Revival',
                'Port': str(port), 'MuteBGM': '1'}
    for key, value in settings.items():
        text, n = re.subn(r'(?m)^(%s\s*=).*?(\r?)$' % key, r'\g<1> %s\g<2>' % value, text)
        if n != 1:
            raise SystemExit(f'tools/nettest.py: {key} is in {src} {n} times, not once')
    with open(out, 'wb') as f:
        f.write(text.encode('utf-16'))


def revival_match(args, efz, exe, work, host, lag, seed, revival):
    name = f'revival-{host}-hosts' + (f'-lag{lag.replace(":", "+")}' if lag else '')
    folder = os.path.join(work, name)
    shutil.rmtree(folder, ignore_errors=True)
    game = os.path.join(folder, 'game')
    os.makedirs(game)
    # The game's folder: links to the data, copies of what is run or written (a link
    # would be written through, into EFZ_DIR).
    own = {'efz.exe', 'key.ini', 'replay', 'EfzRevival.exe', 'EfzRevival.dll', 'DDRAW.dll',
           'EfzRevival.ini'}
    for entry in os.listdir(efz):
        if entry not in own and not entry.lower().startswith(('log', 'battlelog')):
            os.symlink(os.path.join(efz, entry), os.path.join(game, entry))
    shutil.copyfile(os.path.join(efz, 'efz.exe'), os.path.join(game, 'efz.exe'))
    for f in REVIVAL_SHA256:
        shutil.copyfile(os.path.join(revival, f), os.path.join(game, f))
    # The host's port. Revival binds its Port when joining too (Network::init), so as
    # the joiner on the host's machine it takes another.
    port = 10800
    revival_ini(os.path.join(revival, 'EfzRevival.ini'), os.path.join(game, 'EfzRevival.ini'),
                port if host == 'revival' else port + 1)
    key_ini(efz, os.path.join(game, 'key.ini'))
    os.makedirs(os.path.join(game, 'replay', 'netplay'))
    for sub in ('save', 'logs'):
        os.makedirs(os.path.join(folder, 'native', sub))
    key_ini(efz, os.path.join(folder, 'native', 'save', 'key.ini'))
    wine = os.path.join(work, 'wine')
    os.makedirs(wine, exist_ok=True)
    rng = random.Random(seed)
    frames = 64 * 600
    env = {'WINEPREFIX': '/wine', 'WINEDEBUG': '-all', 'DISPLAY': ':99',
           'WINEDLLOVERRIDES': 'ddraw=n,b', 'EFZ_DIR': efz, 'HOST': host, 'PORT': str(port),
           'SEED': str(seed % 32768), 'KEYS': key_script(rng, frames), 'FRAMES': str(frames),
           'FIGHT': str(args.fight), 'LAG': lag or ''}
    container = f'efz-nettest-{os.getpid()}-{host}'
    cmd = ['docker', 'run', '--rm', '--init', '--name', container, '--network', 'none',
           '--ipc', 'host',
           '-v', f'{efz}:{efz}:ro', '-v', f'{folder}:/run', '-v', f'{wine}:/wine',
           '-v', f'{exe}:/native/efz:ro', '-v', f'{DRIVER}:/driver.sh:ro']
    for k, v in env.items():
        cmd += ['-e', f'{k}={v}']
    cmd += [IMAGE, 'bash', '/driver.sh']
    problems = []
    try:
        r = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True,
                           timeout=900)
        if r.returncode != 0:
            problems.append(f'the driver failed ({r.returncode}): '
                            + (r.stdout.strip().splitlines() or ['?'])[-1])
    except subprocess.TimeoutExpired:
        problems.append('the driver ran 15 minutes: stopped')
        subprocess.run(['docker', 'kill', container], stdout=subprocess.DEVNULL,
                       stderr=subprocess.DEVNULL)
    driver = read(os.path.join(folder, 'driver.log'))
    ours = End('native', native_log(os.path.join(folder, 'native', 'logs')),
               os.path.join(folder, 'native', 'save'))
    ours.check(problems, revival=True)
    if 'Esc on Revival' not in driver:
        problems.append('the first fight never ended (no Esc sent)')
    # Revival's own comparison of the sync records (ProtocolContext::checkSync).
    net = read(os.path.join(game, 'logNet.txt'))
    checked = [int(n) for n in re.findall(r'Checked (\d+)', net)]
    if 'ERROR:' in net:
        problems.append("Revival's logNet.txt has ERROR: (a desync, by its records)")
    if not checked:
        problems.append("Revival's logNet.txt checked no frames")
    # Fight 1's replays: Revival's (replay/netplay, written as Esc left the fight) and the
    # native game's first.
    theirs = sorted(os.path.join(game, 'replay', 'netplay', f)
                    for f in os.listdir(os.path.join(game, 'replay', 'netplay')))
    lines = [f'{host} hosts, lag {lag or "none"}, seed {seed}', ours.summary(),
             f'Revival: P{3 - ours.side if ours.side else "?"}, checked {len(checked)} times, '
             f'frames up to {max(checked) if checked else "-"}, '
             f'{"ERROR" if "ERROR:" in net else "no errors"}; {len(theirs)} replay(s)']
    # Each fight's replays: fight 1's written as Esc left it, fight 2's as the match
    # ended. A replay starts with the fight's random state, so fight 2's show the two
    # games went on alike, even where the sync records stopped at the Esc.
    if 'Esc on Revival' in driver:
        if not theirs or not ours.replays:
            problems.append(f"fight 1's replay: Revival saved {len(theirs)}, the native game "
                            f"{len(ours.replays)}")
        for i, (a, b) in enumerate(zip(theirs, ours.replays)):
            same = same_replays(a, b, problems, f"fight {i + 1}'s replay",
                                cut=i == len(theirs) - 1)
            if same:
                lines.append(f"fight {i + 1}'s replays: {same}")
    return report(name, problems, lines, folder, args.keep)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('native', 'revival'):
        p = sub.add_parser(name)
        p.add_argument('--native', default=os.path.join(REPO, 'build', 'native', 'efz'))
        p.add_argument('--lag')
        p.add_argument('--seed', type=int)
        p.add_argument('--keep', action='store_true')
        if name == 'native':
            p.add_argument('--frames', type=int, default=3200)
        else:
            p.add_argument('--host', choices=('revival', 'native'))
            p.add_argument('--fight', type=int, default=20)
            p.add_argument('--revival', default=os.environ.get('REVIVAL_DIR') or os.path.expanduser(
                '~/.local/share/efz-decomp/revival/1.02h'))
    args = ap.parse_args()
    efz = os.environ.get('EFZ_DIR')
    if not efz or not os.path.isdir(efz):
        sys.exit('tools/nettest.py: set EFZ_DIR to the game folder')
    efz = os.path.abspath(efz)
    exe = os.path.abspath(binary(args.native))
    if not os.path.isfile(exe):
        sys.exit(f'tools/nettest.py: no {args.native}: build it first (tools/native.sh)')
    work = os.path.join(os.environ.get('EFZ_COMPAT') or os.path.expanduser(
        '~/.local/share/efz-decomp/compat2'), 'net')
    os.makedirs(work, exist_ok=True)
    seed = args.seed if args.seed is not None else random.randrange(1 << 31)
    results = []
    if args.cmd == 'native':
        lags = [args.lag if args.lag != '0' else None] if args.lag is not None else [None, '60:20']
        for i, lag in enumerate(lags):
            results.append(native_match(args, efz, exe, work, lag, seed + i))
    else:
        if sha256(os.path.join(efz, 'efz.exe')) != EFZ_SHA256:
            sys.exit(f'tools/nettest.py: {efz}/efz.exe is not efz.exe 4.02')
        for f, digest in REVIVAL_SHA256.items():
            path = os.path.join(args.revival, f)
            if not os.path.isfile(path) or sha256(path) != digest:
                sys.exit(f'tools/nettest.py: {path} is not EfzRevival 1.02h\'s')
        if subprocess.run(['docker', 'image', 'inspect', IMAGE], stdout=subprocess.DEVNULL,
                          stderr=subprocess.DEVNULL).returncode != 0:
            subprocess.run(['docker', 'build', '-q', '-t', IMAGE, '-f',
                            os.path.join(REPO, 'toolchain', 'revival-test.Dockerfile'),
                            os.path.join(REPO, 'toolchain')], check=True)
        hosts = [args.host] if args.host else ['revival', 'native']
        for i, host in enumerate(hosts):
            results.append(revival_match(args, efz, exe, work, host, args.lag, seed + i,
                                         os.path.abspath(args.revival)))
    print(f'{sum(results)} of {len(results)} matches passed')
    sys.exit(0 if all(results) else 1)


if __name__ == '__main__':
    main()
