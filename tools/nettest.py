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
    tools/nettest.py idle               the host's --idle-timeout (8 s here), two native
                                        games: (play) the joiner presses keys at random
                                        into a fight, then nothing, and the host must end
                                        the match 8 s after, not before; (delay) the
                                        joiner connects from NET PLAY's screen and never
                                        confirms the input delay, and the host must end it
                                        8 s after it connected; both ends must say so
        --case play|delay               that one only
        --native PATH                   the build (default build/native/efz)
    tools/nettest.py internet           over the internet, with another machine (a
                                        server with a public address, reached by ssh):
                                        (public) it hosts and this one joins; (punch)
                                        this one hosts behind its router, nothing
                                        forwarded, and the other joins through the
                                        hole-punching server (tools/punchserver.py) run
                                        there; (control) the same without the server,
                                        which must not connect
        --remote USER@HOST              the other machine (Linux x64, with python3 and
                                        systemd-run); it must let UDP from this one in
        --ssh-key FILE                  ssh's key for it
        --case public|punch|control     that one only
        --port N, --punch-port N        its ports (default 10900, 10901); this one
        --local-port N                  hosts on 10800 (default)
        --frames N, --native PATH       as for native
      Both ends play on the compatibility pack (tools/compatpack.py) made from EFZ_DIR,
      which goes to the other machine with the build, in ~/efz-nettest; the game there
      runs in a systemd scope of at most 320 MB.
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
- Against Revival, the native end has EDIT COLOR palettes for every character, which only
  it has: each one its random keys picked (D on the colour), Revival must have found as
  sent (its logEfz.txt, "custom 1").

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
# Pressed at random: not C (B). In a network match B doesn't leave character select
# (Revival's patch at efz.exe 0x754c1a, src/scene1.cpp), but it takes a choice back, which
# keeps character select going long enough to miss the second fight; and on the NET PLAY
# screens before the match it cancels.
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


def native_ini(save):
    """The native game's EfzRevival.ini (port/revival/config.h) in its save folder, which it
    reads before the data folder's: no hole-punching server, whose default is Revival's
    server on the internet, and Revival's other settings as shipped."""
    with open(os.path.join(save, 'EfzRevival.ini'), 'w') as f:
        f.write('[Network]\nHolePunchingServer = None\n')


# Revival's folders of the characters (EfzPalettes.cpp's folderName), for EDIT COLOR's
# palettes.
PALETTE_FOLDERS = ['Nanase', 'Ayu', 'Mai', 'Makoto', 'Akane', 'Mayu', 'Nagamori', 'Misaki',
                   'Shiori', 'Sayuri', 'Nayuki', 'Mio', 'ExNanase', 'Kaori', 'Ikumi', 'Mishio',
                   'Akiko', 'NayukiB', 'MizukaB', 'Kanna', 'Kano', 'Minagi', 'NayukiA',
                   'Misuzu', 'Mizuka']


def custom_palettes(save):
    """EDIT COLOR palettes for every character in the native game's save folder (a byte,
    then 40 colours, blue, green, red: magenta), which only that end has: when its random
    keys pick one (D on the colour), the other end can show it only as sent."""
    for name in PALETTE_FOLDERS:
        os.makedirs(os.path.join(save, name), exist_ok=True)
        for i in range(1, 7):
            with open(os.path.join(save, name, f'{name}{i}.pal'), 'wb') as f:
                f.write(bytes([0]) + bytes([200, 30 * i % 256, 250]) * 40 + bytes(64))


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
        native_ini(os.path.join(folder, who, 'save'))
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



# --- The idle timeout (--idle-timeout)

IDLE = 8
# The joiner's random keys stop at this frame of its own: in the first fight (it connects
# in about 300 frames, and character select takes 300-400 of random keys).
IDLE_STOP = 2400
# On the title, down to NET PLAY and A (the test key.ini's X), then A on its screen's
# START: netplay.ini has it join, where and as whom.
NET_PLAY_KEYS = ('200:+Down,204:-Down,215:+Down,219:-Down,230:+Down,234:-Down,'
                 '260:+X,264:-X,330:+X,334:-X')
LOG_LINE = re.compile(r'^\S+ \S+ \+([\d.]+) f=(-?\d+) s=-?\d+ \w+\s+net: (.*)$')


def net_lines(log):
    """(seconds since the start, frame, message) of each of a log's net lines."""
    return [(float(m.group(1)), int(m.group(2)), m.group(3))
            for m in map(LOG_LINE.match, log.splitlines()) if m]


def first(lines, text):
    return next((line for line in lines if text in line[2]), None)


def idle_match(args, efz, exe, work, case, seed):
    name = f'idle-{case}'
    folder = os.path.join(work, name)
    shutil.rmtree(folder, ignore_errors=True)
    for who in ('host', 'join'):
        for sub in ('save', 'logs'):
            os.makedirs(os.path.join(folder, who, sub))
        key_ini(efz, os.path.join(folder, who, 'save', 'key.ini'))
        native_ini(os.path.join(folder, who, 'save'))
    env = dict(os.environ, SDL_VIDEO_DRIVER='offscreen', SDL_AUDIO_DRIVER='dummy')
    env.pop('EFZ_NET_LAG', None)
    rng = random.Random(seed)
    port = free_udp_port()
    # Long after the host should have ended the match: an end that waits for these is
    # the timeout not working.
    frames = IDLE_STOP + (IDLE + 30) * 64
    if case == 'play':
        join_keys = key_script(rng, IDLE_STOP)
        join_args = ['--join', f'127.0.0.1:{port}', '--name', 'Join']
    else:
        with open(os.path.join(folder, 'join', 'save', 'netplay.ini'), 'w') as f:
            f.write(f'mode=join\naddress=127.0.0.1\nport={port}\nname=Join\nagent=\n')
        join_keys = NET_PLAY_KEYS
        join_args = []
    procs = {}
    for who in ('host', 'join'):
        # The host presses keys too: its own input doesn't keep the match.
        keys = key_script(rng, frames) if who == 'host' else join_keys
        cmd = [exe, '--data', efz, '--save', os.path.join(folder, who, 'save'),
               '--log-dir', os.path.join(folder, who, 'logs'), '--frames', str(frames),
               '--keys', keys]
        cmd += (['--host', '--port', str(port), '--name', 'Host', '--idle-timeout', str(IDLE)]
                if who == 'host' else join_args)
        out = open(os.path.join(folder, who, 'out.txt'), 'w')
        procs[who] = subprocess.Popen(cmd, stdout=out, stderr=subprocess.STDOUT, env=env)
        if who == 'host':
            deadline = time.time() + 20
            while time.time() < deadline and 'hosting on UDP port' not in native_log(
                    os.path.join(folder, 'host', 'logs')):
                time.sleep(0.2)
    problems = []
    limit = time.time() + frames / 64 * 2 + 60
    for who, p in procs.items():
        try:
            p.wait(timeout=max(1, limit - time.time()))
        except subprocess.TimeoutExpired:
            p.kill()
            problems.append(f'{who}: still running after {int(limit)} s: killed')
    h = net_lines(native_log(os.path.join(folder, 'host', 'logs')))
    j = net_lines(native_log(os.path.join(folder, 'join', 'logs')))
    lines = [f'seed {seed}']
    end = first(h, 'the session ends: ')
    want = 'Join gave no input for' if case == 'play' else "Join didn't start the match in"
    if not end or want not in end[2]:
        problems.append(f'host: the match did not end as idle ({end[2] if end else "no end"})')
    jend = first(j, 'the session ends: ')
    if not jend or 'The game was closed' in jend[2]:
        problems.append(f'joiner: the host did not end its match '
                        f'({jend[2] if jend else "no end"})')
    if end:
        lines.append(f'host: {end[2]}')
    if jend:
        lines.append(f'joiner: {jend[2]}')
    if case == 'play':
        # It played into a fight, longer than the timeout, and the end came about IDLE
        # seconds after its last key (released at most 12 frames after the last press).
        start = first(j, 'the match starts: ')
        ran = first(h, 'the match ran ')
        if not first(h, 'fight at frame'):
            problems.append('host: no fight')
        if start and ran:
            stopped = IDLE_STOP + 12 - start[1]
            n = int(re.match(r'the match ran (\d+)', ran[2]).group(1))
            lines.append(f'the joiner stopped at match frame {stopped} at the latest, the host '
                         f'ended it at {n}')
            # (the timeout counts seconds; a slow machine runs fewer frames in them)
            if not IDLE * 64 * 0.5 <= n - stopped <= IDLE * 64 + 128:
                problems.append(f'host: ended {n - stopped} frames after the joiner stopped, '
                                f'not about {IDLE * 64}')
        else:
            problems.append('no match start or end in the logs')
    else:
        connected = first(h, 'hosting -> measuring')
        if first(h, '-> playing'):
            problems.append('host: the match started')
        if connected and end:
            waited = end[0] - connected[0]
            lines.append(f'host: ended {waited:.1f} s after the joiner connected')
            if not IDLE - 0.5 <= waited <= IDLE + 2:
                problems.append(f'host: ended {waited:.1f} s after the joiner connected, '
                                f'not {IDLE}')
        else:
            problems.append('host: no connection or end in the log')
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
    native_ini(os.path.join(folder, 'native', 'save'))
    custom_palettes(os.path.join(folder, 'native', 'save'))
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
    # The palettes, when the random keys picked EDIT COLOR (D on the colour): the native
    # game's own sent, Revival's log (Palettes::log, Debug = 1) has it found, "custom 1".
    sent = re.findall(r"P\d's palette: custom, this computer's, number (\d) of (\w+)", ours.log)
    came = re.findall(r"custom palette (\d) of (\w+) came", ours.log)
    found = set(re.findall(r'(\w+) id (\d) custom 1', read(os.path.join(game, 'logEfz.txt'))))
    for number, who in sorted(set(sent)):
        if (who, str(int(number) - 1)) in found:
            lines.append(f'the native game\'s custom palette {number} of {who}: Revival shows it')
        else:
            problems.append(f'the native game\'s custom palette {number} of {who}: Revival '
                            f'didn\'t find it (logEfz.txt)')
    for number, who in sorted(set(came)):
        lines.append(f"Revival's custom palette {number} of {who} came")
    if not sent:
        lines.append('(the native game picked no EDIT COLOR palette: not compared)')
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


# --- Over the internet

class Remote:
    """The other machine, by ssh."""

    def __init__(self, target, key, folder='efz-nettest'):
        self.target, self.key, self.folder = target, key, folder
        self.ssh = ['ssh', '-o', 'BatchMode=yes', '-o', 'ConnectTimeout=15']
        if key:
            self.ssh += ['-i', key]

    def run(self, command, timeout=120, check=True):
        r = subprocess.run(self.ssh + [self.target, command], capture_output=True, text=True,
                           timeout=timeout)
        if check and r.returncode != 0:
            raise SystemExit(f'tools/nettest.py: on {self.target}: {command}: {r.stderr.strip()}')
        return r.stdout

    def start(self, command):
        return subprocess.Popen(self.ssh + [self.target, command], stdout=subprocess.DEVNULL,
                                stderr=subprocess.DEVNULL)

    def put(self, local, remote):
        scp = ['scp', '-q', '-o', 'BatchMode=yes'] + (['-i', self.key] if self.key else [])
        subprocess.run(scp + ['-r', local, f'{self.target}:{remote}'], check=True, timeout=600)

    def get(self, remote, local):
        scp = ['scp', '-q', '-o', 'BatchMode=yes'] + (['-i', self.key] if self.key else [])
        subprocess.run(scp + ['-r', f'{self.target}:{remote}', local], check=True, timeout=600)


def deploy(remote, exe, pack, work):
    """The build, stripped, the pack and the hole-punching server, in ~/efz-nettest."""
    stage = os.path.join(work, 'deploy')
    shutil.rmtree(stage, ignore_errors=True)
    os.makedirs(stage)
    subprocess.run(['strip', '-o', os.path.join(stage, 'efz'), exe], check=True)
    shutil.copy(os.path.join(REPO, 'tools', 'punchserver.py'), stage)
    subprocess.run(['tar', '-C', os.path.dirname(pack), '-czf', os.path.join(stage, 'pack.tar.gz'),
                    os.path.basename(pack)], check=True)
    remote.run(f'rm -rf {remote.folder} && mkdir -p {remote.folder}')
    for f in ('efz', 'punchserver.py', 'pack.tar.gz'):
        remote.put(os.path.join(stage, f), f'{remote.folder}/{f}')
    name = os.path.basename(pack)
    remote.run(f'cd {remote.folder} && tar xzf pack.tar.gz && rm pack.tar.gz' +
               (f' && mv {name} pack' if name != 'pack' else ''))


def internet_match(args, remote, exe, pack, work, case, seed, public, server):
    """One case: who hosts, with which hole-punching server, and whether it must connect."""
    folder = os.path.join(work, f'internet-{case}')
    shutil.rmtree(folder, ignore_errors=True)
    for sub in ('save', 'logs'):
        os.makedirs(os.path.join(folder, 'here', sub))
    key_ini(pack, os.path.join(folder, 'here', 'save', 'key.ini'))
    punch = f'{remote.target.split("@")[-1]}:{args.punch_port}' if case == 'punch' else 'None'
    with open(os.path.join(folder, 'here', 'save', 'EfzRevival.ini'), 'w') as f:
        f.write(f'[Network]\nHolePunchingServer = {punch}\n')
    there = f'{remote.folder}/run-{case}'
    shutil.copy(os.path.join(folder, 'here', 'save', 'key.ini'), os.path.join(folder, 'key.ini'))
    remote.run(f'rm -rf {there} && mkdir -p {there}/save {there}/logs && '
               f'printf "[Network]\\nHolePunchingServer = {punch}\\n" > {there}/save/EfzRevival.ini')
    remote.put(os.path.join(folder, 'key.ini'), f'{there}/save/key.ini')
    rng = random.Random(seed)
    frames = args.frames if case != 'control' else 64 * 15
    remote_hosts = case == 'public'
    host_keys = key_script(rng, frames) + f',{ESC_FRAME}:+Escape,{ESC_FRAME + 10}:-Escape'
    join_keys = key_script(rng, frames + 600)
    env = dict(os.environ, SDL_VIDEO_DRIVER='offscreen', SDL_AUDIO_DRIVER='dummy')
    env.pop('EFZ_NET_LAG', None)
    sdl = 'SDL_VIDEO_DRIVER=offscreen SDL_RENDER_DRIVER=software SDL_AUDIO_DRIVER=dummy'

    def remote_cmd(role, keys, n):
        return (f'cd {remote.folder} && systemd-run --scope -q -p MemoryMax=320M env {sdl} '
                f'./efz --data pack --save run-{case}/save --log-dir run-{case}/logs '
                f'--frames {n} --keys "{keys}" --name Remote {role} > run-{case}/out.txt 2>&1')

    def local_cmd(role, keys, n):
        return [exe, '--data', pack, '--save', os.path.join(folder, 'here', 'save'), '--log-dir',
                os.path.join(folder, 'here', 'logs'), '--frames', str(n), '--keys', keys,
                '--name', 'Here'] + role

    problems = []
    if remote_hosts:
        far = remote.start(remote_cmd(f'--host --port {args.port}', host_keys, frames))
        deadline = time.time() + 30
        while time.time() < deadline and 'hosting on UDP port' not in remote.run(
                f'cat {there}/logs/*/efz.log 2>/dev/null', check=False):
            time.sleep(1)
        near = subprocess.Popen(local_cmd(['--join', f'{remote.target.split("@")[-1]}:{args.port}'],
                                          join_keys, frames + 600),
                                stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT, env=env)
    else:
        near = subprocess.Popen(local_cmd(['--host', '--port', str(args.local_port)], host_keys,
                                          frames),
                                stdout=subprocess.DEVNULL, stderr=subprocess.STDOUT, env=env)
        deadline = time.time() + 20
        while time.time() < deadline and 'hosting on UDP port' not in native_log(
                os.path.join(folder, 'here', 'logs')):
            time.sleep(0.2)
        far = remote.start(remote_cmd(f'--join {public}:{args.local_port}', join_keys,
                                      frames + 600))
    limit = time.time() + (frames + 600) / 64 * 2 + 120
    for who, p in (('here', near), ('remote', far)):
        try:
            p.wait(timeout=max(1, limit - time.time()))
        except subprocess.TimeoutExpired:
            p.kill()
            problems.append(f'{who}: still running: killed')
    os.makedirs(os.path.join(folder, 'remote'), exist_ok=True)
    remote.get(f'{there}/logs', os.path.join(folder, 'remote'))
    remote.get(f'{there}/save', os.path.join(folder, 'remote'))
    here = End('here', native_log(os.path.join(folder, 'here', 'logs')),
               os.path.join(folder, 'here', 'save'))
    far_end = End('remote', native_log(os.path.join(folder, 'remote', 'logs')),
                  os.path.join(folder, 'remote', 'save'))
    host, joiner = (far_end, here) if remote_hosts else (here, far_end)
    lines = [f'{case}: {"the remote" if remote_hosts else "this machine"} hosts'
             f'{", hole-punching server " + punch if case == "punch" else ""}, seed {seed}']
    punches = re.findall(r'the hole-punching server points to (\S+)', host.log + joiner.log)
    if case == 'control':
        if joiner.side is not None:
            problems.append('connected without the hole-punching server: is the port '
                            'forwarded to this machine, so that this shows nothing?')
        else:
            lines.append('no connection, as it must be: '
                         + (re.findall(r'the session ends: (.*)', joiner.log) or ['?'])[-1])
        return report(f'internet-{case}', problems, lines, folder, args.keep)
    for end in (host, joiner):
        end.check(problems)
    if host.side and joiner.side and host.side == joiner.side:
        problems.append(f'both ends are P{host.side}')
    if host.seed and joiner.seed and host.seed != joiner.seed:
        problems.append(f'the seeds differ: {host.seed} and {joiner.seed}')
    if case == 'punch' and not punches:
        problems.append('no punch from the server was logged')
    m = re.search(r'ping average (\d+), min (\d+), max (\d+)', joiner.log)
    if m:
        lines.append(f'ping {m.group(1)} ms (min {m.group(2)}, max {m.group(3)})')
    if punches:
        lines.append('the server pointed to ' + ', '.join(sorted(set(punches))))
    lines += [host.summary(), joiner.summary()]
    for i, (a, b) in enumerate(zip(host.replays, joiner.replays)):
        same = same_replays(a, b, problems, f'fight {i + 1}')
        if same:
            lines.append(f"fight {i + 1}'s replays: {same}")
    return report(f'internet-{case}', problems, lines, folder, args.keep)


def internet(args, efz, exe, work, seed):
    remote = Remote(args.remote, args.ssh_key)
    pack = os.path.join(work, 'pack')
    if not os.path.isfile(os.path.join(pack, 'PACK.txt')):
        subprocess.run([sys.executable, os.path.join(REPO, 'tools', 'compatpack.py'), 'build',
                        pack, '--efz', efz], check=True, stdout=subprocess.DEVNULL)
    deploy(remote, exe, pack, work)
    public = remote.run('echo $SSH_CLIENT').split()[0]
    print(f'this machine is {public} to {args.remote}')
    cases = [args.case] if args.case else ['public', 'punch', 'control']
    results = []
    server = None
    try:
        if 'punch' in cases:
            remote.run(f'systemctl stop efz-nettest-punch 2>/dev/null; systemd-run '
                       f'--unit=efz-nettest-punch --collect -p MemoryMax=64M /usr/bin/python3 '
                       f'$HOME/{remote.folder}/punchserver.py --port {args.punch_port}',
                       check=False)
        for i, case in enumerate(cases):
            results.append(internet_match(args, remote, exe, pack, work, case, seed + i, public,
                                          server))
    finally:
        if 'punch' in cases:
            print('the hole-punching server said:')
            print(remote.run('journalctl -u efz-nettest-punch --no-pager -o cat | tail -20',
                             check=False))
            remote.run('systemctl stop efz-nettest-punch', check=False)
    return results


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    for name in ('native', 'revival', 'internet', 'idle'):
        p = sub.add_parser(name)
        p.add_argument('--native', default=os.path.join(REPO, 'build', 'native', 'efz'))
        p.add_argument('--lag')
        p.add_argument('--seed', type=int)
        p.add_argument('--keep', action='store_true')
        if name in ('native', 'internet'):
            p.add_argument('--frames', type=int, default=3200)
        if name == 'internet':
            p.add_argument('--remote', required=True)
            p.add_argument('--ssh-key')
            p.add_argument('--case', choices=('public', 'punch', 'control'))
            p.add_argument('--port', type=int, default=10900)
            p.add_argument('--punch-port', type=int, default=10901)
            p.add_argument('--local-port', type=int, default=10800)
        elif name == 'idle':
            p.add_argument('--case', choices=('play', 'delay'))
        elif name == 'revival':
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
    if args.cmd == 'internet':
        results = internet(args, efz, exe, work, seed)
    elif args.cmd == 'idle':
        for i, case in enumerate([args.case] if args.case else ['play', 'delay']):
            results.append(idle_match(args, efz, exe, work, case, seed + i))
    elif args.cmd == 'native':
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
