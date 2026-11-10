"""Which inputs start each character's moves: every motion the game reads (src/efz.h's
kCmd*: 236, 623, 214, 22, 412, 236236...) with each button, played from the same saved
state (standing, at a round's start, full power and RF gauges) for every character; the
move each one starts, and for its invincible ones (framedata.json) the motion that does.
A red team's advantages (redteam_assist.py) play them: an invincible move after a recoil
guard, as a person's reversal.

    python runs/human-ayu/motions.py            # -> motions.json

motions.json: {char: {"moves": {pattern: motion}, "invincible": [{"pattern", "motion",
"startup", "level"}...]}}, a motion a string of numpad steps and a button ("623C"; "5252A"
for 22A), each step one frame, the button with the last.
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))

import numpy as np

# Each the frames' numpad directions; the button goes with the last. Doubles (22, 222)
# pass through neutral as the game reads them (5 2 5 2).
MOTIONS = ['236', '623', '214', '5252', '525252', '412', '421', '263', '4136', '21436',
           '23614', '41236', '641236', '4631', '66', '666', '236236', '214214', '631631',
           '413413', '63146314', '23693', '236236236', '4123641236']
BUTTONS = 'ABCD'
SETTLE = 6  # frames after the press in which the move must have started


def controls(motion, button):
    from efz_env.actions import encode
    return [encode(int(d)) for d in motion[:-1]] + [encode(int(motion[-1]), button)]


def probe(env, char, own, first_own):
    """{pattern: motion} for one character (environment 0, player 1)."""
    env.set_matches(chars=(char, 'ayu'), stage=0)
    env.reset()
    env.set_gauges(0, 0, power=3000, rf=999, blue=False)
    start = env.save_state(0)
    found = {}
    idle = np.zeros((1, 2), np.uint8)
    for motion in MOTIONS:
        for b in BUTTONS:
            env.load_state(0, start)
            seq = controls(motion, b) + [0] * SETTLE
            entered = None
            for c in seq:
                act = idle.copy()
                act[0, 0] = c
                obs = env.step(act)[0]
                a = int(round(obs[0, 0, own]))
                if a >= first_own and entered is None:
                    entered = a
            if entered is not None:
                found.setdefault(entered, motion + b)  # the first, shortest, motion
    return found


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default=os.path.join(HERE, 'motions.json'))
    p.add_argument('--chars', nargs='*')
    args = p.parse_args()
    from efz_env import EfzVecEnv
    from efz_env.vec import character_names
    import tactics
    names = character_names()
    data = json.load(open(os.path.join(HERE, 'framedata.json')))
    env = EfzVecEnv(args.data, 1, num_threads=1, seed=1, autoreset='disabled')
    from efz_env._native import library
    lib = library()
    obs_names = [lib.efz_env_obs_name(i).decode() for i in range(lib.efz_env_obs_dim())]
    own = obs_names.index('self_action')
    chars = args.chars or [c for c in data if c in names]
    out = {}
    for char in chars:
        found = probe(env, char, own, tactics.FIRST_OWN)
        fd = data.get(char, {})
        inv = []
        for pat, motion in sorted(found.items()):
            m = fd.get(hex(pat))
            if m and m['invincible'] and m['startup'] is not None and m['level'] >= 10:
                inv.append(dict(pattern=hex(pat), motion=motion, startup=m['startup'],
                                level=m['level']))
        out[char] = dict(moves={hex(k): v for k, v in sorted(found.items())}, invincible=inv)
        print(f"{char}: {len(found)} moves; invincible: "
              + (', '.join(f"{x['motion']} ({x['pattern']}, {x['startup']}f)" for x in inv) or 'none'),
              flush=True)
    env.close()
    with open(args.out, 'w') as f:
        json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
