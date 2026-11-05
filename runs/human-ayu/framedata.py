"""The characters' frame data, from the game's <name>/<name>.pat (as CPlayer::LoadPatterns
reads them, src/player.cpp): per character and move, the steps before it is active
(startup), how far its attack boxes reach, and whether it is invulnerable in its first
steps (a frame with flagsB0 0x20, kStateInvulnerable: an invincible move, a reversal).

    python runs/human-ayu/framedata.py --data D:/tasogare/EFZ    # -> framedata.json

evaluate.py reads framedata.json: an escape is an invincible move by it (or by the
player's invulnerability timer, which some moves set in code), and a minus guard is
punishable when the defender has a move as fast as its disadvantage that reaches.
These are the frames as the data has them; a move's code can change its course (a
follow-up, a hold), so they are the move's plain course.
"""

import argparse
import json
import os
import struct

HERE = os.path.dirname(os.path.abspath(__file__))
INVULNERABLE = 0x20  # flagsB0: kStateInvulnerable
FIRST_OWN = 0xc8
FRAME_BYTES = 240    # 6 ints of sprite, 8 ints, 4 shorts, 4 ints, 10 rects of 16 bytes


def read_pat(path):
    """{pattern: [(steps, flagsB0, damage, attack boxes [(l, t, r, b)]), ...]}"""
    data = open(path, 'rb').read()
    off = 0

    def ints(n):
        nonlocal off
        v = struct.unpack_from(f'<{n}i', data, off)
        off += 4 * n
        return v
    count, = ints(1)
    out = {}
    for _ in range(count):
        action, level, cancel, frames = ints(4)
        seq = []
        for _ in range(frames):
            start = off
            duration, surface, w, h, x, y = ints(6)
            damage, flags_aa, air_hit, flags_b0, untech, chip, on_hit, on_guard = ints(8)
            off += 8  # hitVy, hitVx, sound, effect (shorts)
            ints(4)   # hitstops, proration, ground hit pattern
            rects = [struct.unpack_from('<4i', data, off + 16 * k) for k in range(10)]
            off = start + FRAME_BYTES
            # Read order: push box, boxes 0-1, attack box 0, boxes 2-4, attack boxes 1-3.
            attack = [rects[3]] + rects[7:10]
            attack = [r for r in attack if r[2] > r[0] and r[3] > r[1]]
            seq.append((duration & 0xffff, flags_b0 & 0xffff,  # frames: a step each
                        damage, attack))
        out[action] = dict(level=level, cancel=cancel, frames=seq)
    if off != len(data):
        raise ValueError(f'{path}: read {off} of {len(data)} bytes')
    return out


def summarize(patterns, invincible_steps=8):
    """Per move of the character's own: startup (steps before the first frame with an
    attack box), reach (the farthest attack box edge ahead, pixels), invincible (a frame
    in its first `invincible_steps` steps is invulnerable), total steps."""
    out = {}
    for action, p in patterns.items():
        if action < FIRST_OWN:
            continue
        t, startup, reach, inv = 0, None, 0, False
        for steps, flags, damage, attack in p['frames']:
            if t < invincible_steps and flags & INVULNERABLE:
                inv = True
            if attack and startup is None:
                startup = t
            for r in attack:
                reach = max(reach, r[2])
            t += max(steps, 1)
        out[action] = dict(startup=startup, reach=reach, invincible=inv, steps=t,
                           level=p['level'])
    return out


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default=os.path.join(HERE, 'framedata.json'))
    args = p.parse_args()
    out = {}
    for name in sorted(os.listdir(args.data)):
        path = os.path.join(args.data, name, name + '.pat')
        if os.path.isfile(path):
            out[name] = {hex(k): v for k, v in summarize(read_pat(path)).items()}
            moves = out[name].values()
            fast = min((m['startup'] for m in moves if m['startup'] is not None), default=None)
            inv = sum(m['invincible'] and m['startup'] is not None for m in moves)
            print(f'{name:10s} {len(out[name]):3d} moves, fastest startup {fast}, '
                  f'{inv} invincible attacks')
    with open(args.out, 'w') as f:
        json.dump(out, f, indent=0)


if __name__ == '__main__':
    main()
