"""Which inputs start each character's moves: every motion the game reads (src/efz.h's
kCmd*: 236, 623, 214, 22, 412, 236236...) with each button, played from the same saved
state (standing, at a round's start, full power and RF gauges) for every character; the
move each one starts, and for its invincible ones (framedata.json) the motion that does.
A red team's advantages (redteam_assist.py) play them: an invincible move after a recoil
guard, as a person's reversal.

    python runs/human-ayu/motions.py            # -> motions.json

motions.json: {char: {"moves": {pattern: motion}, "invincible": [{"pattern", "motion",
"startup", "level", "from_rg", "rg_delay"}...]}}, a motion a string of numpad steps and a
button ("623C"; "5252A" for 22A), each step one frame, the button with the last; from_rg:
whether it comes out of a recoil guard (the game drops the first few steps' inputs), and
rg_hits whether, so started, it hits an opponent pressing on (Ayu's 2A every 8 steps)
before it is hit itself (None: neither), rg_delay the first step after the guard's start
its motion can begin on (input once:
repeated, a motion can read as another, 2 3 6C 2 3 6C as 623C). Needs a library with
efz_env_set_recoil_guard.
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
HITSTUN_SELF, HITSTUN_OPP = 20, 52  # efz_env_obs_name: self_hitstun, opp_hitstun


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


def probe_rg(env, char, inv, own, most=40):
    """For each invincible move, whether its motion comes out of a recoil guard, input once,
    and the first step after the guard's start it can begin on (rg_delay: before it the
    game drops the inputs): P2 (Ayu) walks in pressing 2A into P1's crouching guard, every
    guard a recoil guard."""
    from efz_env.actions import encode
    env.set_matches(chars=(char, 'ayu'), stage=0)
    env.set_recoil_guard(0, 0, 1.0)
    env.reset()
    rg = None
    for t in range(4000):
        p2 = encode(2, 'A') if t % 8 == 0 else encode(6)
        obs = env.step(np.array([[encode(1), p2]], np.uint8))[0]
        if int(round(obs[0, 0, own])) in (0xa8, 0xa9, 0xaa):
            rg = env.save_state(0)
            break
    env.set_recoil_guard(0, 0, 0.0)
    if rg is None:
        return False
    for m in inv:
        motion, pattern = m['motion'], int(m['pattern'], 16)
        m['from_rg'], m['rg_delay'] = False, None
        for d in range(most):
            env.load_state(0, rg)
            env.set_gauges(0, 0, power=3000, rf=999, blue=False)
            seq = [encode(1)] * d + controls(motion[:-1], motion[-1]) + [0] * SETTLE
            for c in seq:
                obs = env.step(np.array([[c, 0]], np.uint8))[0]
                if int(round(obs[0, 0, own])) == pattern:
                    m['from_rg'], m['rg_delay'] = True, d
                    break
            if m['from_rg']:
                break
        if m['from_rg']:  # as a reversal: P2 presses on (2A every 8 steps), who is hit first
            env.load_state(0, rg)
            env.set_gauges(0, 0, power=3000, rf=999, blue=False)
            mine = [encode(1)] * m['rg_delay'] + controls(motion[:-1], motion[-1])
            m['rg_hits'] = None
            for t in range(m['rg_delay'] + 90):
                c1 = mine[t] if t < len(mine) else 0
                c2 = encode(2, 'A') if t % 8 == 0 else encode(6)
                obs = env.step(np.array([[c1, c2]], np.uint8))[0]
                if obs[0, 0, HITSTUN_OPP] > 0.5 or obs[0, 0, HITSTUN_SELF] > 0.5:
                    m['rg_hits'] = bool(obs[0, 0, HITSTUN_OPP] > 0.5)
                    break
    return True


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
        probe_rg(env, char, inv, own)
        out[char] = dict(moves={hex(k): v for k, v in sorted(found.items())}, invincible=inv)
        print(f"{char}: {len(found)} moves; invincible: "
              + (', '.join(f"{x['motion']} ({x['pattern']}, {x['startup']}f, from an RG "
                           f"{'from step ' + str(x['rg_delay']) + (', hits' if x.get('rg_hits') else ', hit back' if x.get('rg_hits') is False else ', neither') if x.get('from_rg') else 'no' if 'from_rg' in x else '?'})"
                           for x in inv) or 'none'),
              flush=True)
    env.close()
    with open(args.out, 'w') as f:
        json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
