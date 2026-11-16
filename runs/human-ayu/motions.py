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


RISING = 0x60                     # tactics.DOWN's wake-up: the last of a knockdown
DOWN = (0x60, 0x61, 0x62, 0x63)   # tactics.DOWN
DX, X, AIRBORNE, GUARDING = 4, 13, 39, 21  # efz_env_obs_name: dx, self_x, self_airborne, self_guarding


def _step(env, c1, c2):
    return env.step(np.array([[c1, c2]], np.uint8))[0]


def knockdown(env, own, victim=0, most=2000):
    """From a round's start: the other player walks in and throws the victim (forward + C,
    as advantages.py's throw), who stands still. Returns the saved state at the victim's
    first rising step (RISING) and the steps of each part of its knockdown
    [(action, steps)], or (None, None)."""
    from efz_env.actions import encode
    env.reset()
    other = 1 - victim
    parts, prev, rising = [], None, None
    for t in range(most):
        dx = abs(env_obs(env)[0, other, DX]) * 640 if t else 999
        go = encode(6, 'C') if dx < 24 and t % 2 == 0 else encode(6)
        if parts:  # thrown: both idle
            go = 0
        c = [0, 0]
        c[other] = go
        obs = _step(env, *c)
        a = int(round(obs[0, victim, own]))
        if a in DOWN:
            if a != prev:
                parts.append([a, 0])
            parts[-1][1] += 1
            if a == RISING and prev != RISING:
                rising = env.save_state(0)
        elif parts:
            return rising, [tuple(p) for p in parts]
        prev = a
    return None, None


def env_obs(env):
    return env.obs


def probe_wake(env, char, inv, own):
    """For each invincible move, the step after the first rising step its input begins on
    (wake_delay: its motion, one step each, the button with the last) that starts it the
    soonest after the knockdown, and that step (wake_start: the steps from the first rising
    one to the move's first); and the character's rising length (the steps of RISING)."""
    from efz_env.actions import encode
    env.set_matches(chars=(char, 'ayu'), stage=0)
    state, parts = knockdown(env, own, victim=0)
    if state is None:
        return None
    rise = dict(parts).get(RISING)
    for m in inv:
        motion, pattern = m['motion'], int(m['pattern'], 16)
        best = None
        for d in range(rise + 3):
            env.load_state(0, state)
            env.set_gauges(0, 0, power=3000, rf=999, blue=False)
            seq = [0] * d + controls(motion[:-1], motion[-1]) + [0] * SETTLE
            for t, c in enumerate(seq):
                obs = _step(env, c, 0)
                if int(round(obs[0, 0, own])) == pattern:
                    if best is None or t + 1 <= best[1]:
                        best = (d, t + 1)  # the latest input of the soonest start
                    break
        m['wake_delay'], m['wake_start'] = (best if best else (None, None))
    return dict(rise=rise, knockdown=parts)


def probe_meaty(env, char, inv, own, button_at=2, hold=3, offsets=range(-8, 4)):
    """Each invincible move as a wake-up reversal against Ayu's meaty 2A: the character
    knocked down by Ayu's 2C (no side crossed: after a throw that crosses, the game reads a
    motion made while rising the wrong way), its motion input while rising and its
    button `button_at` steps before its first free one (held `hold`), Ayu's 2A pressed
    at each of `offsets` steps from that first free step. wake_wins: the share of them
    in which Ayu is hit first (the move's own invulnerability, not its speed, decides it:
    the user's Mishio rose with 623B and won 5 of 5, its 623A is the faster)."""
    from efz_env.actions import encode
    env.set_matches(chars=('ayu', char), stage=0)
    env.reset()
    rising, rise, parts, prev = None, None, [], None
    for t in range(1500):  # Ayu walks in and sweeps (2C), then stands
        dx = abs(env_obs(env)[0, 0, DX]) * 640
        c1 = 0 if parts else encode(2, 'C') if dx < 60 and t % 3 == 0 else encode(6)
        obs = _step(env, c1, 0)
        a = int(round(obs[0, 1, own]))
        if a in DOWN:
            if a != prev:
                parts.append([a, 0])
            parts[-1][1] += 1
            if a == RISING and prev != RISING:
                rising = env.save_state(0)
        elif parts:
            rise = dict(parts)[RISING]
            break
        prev = a
    if rising is None:
        return None
    for m in inv:
        dirs, button = [int(d) for d in m['motion'][:-1]], m['motion'][-1]
        start = max(0, rise - button_at - (len(dirs) - 1))
        mine = [0] * start + [encode(d) for d in dirs[:-1]] + [encode(dirs[-1], button)] * hold
        wins = 0
        for off in offsets:
            env.load_state(0, rising)
            env.set_gauges(0, 1, power=3000, rf=999, blue=False)
            press = rise + off
            for t in range(rise + 60):
                d = abs(env_obs(env)[0, 0, DX]) * 640
                c1 = encode(2, 'A') if t == press else (encode(6) if t < press and d > 30 else 0)
                obs = _step(env, c1, mine[t] if t < len(mine) else 0)
                if obs[0, 0, 20] > 0.5 and int(round(obs[0, 0, own])) not in DOWN:
                    wins += 1  # Ayu hit first
                    break
                if t > rise and obs[0, 1, 20] > 0.5:
                    break  # the riser hit first
        m['wake_wins'] = round(wins / len(offsets), 3)
    return dict(meaty_rise=rise)


def probe_jump(env, char, own, buttons='ABC'):
    """The character's jump-in on a rising opponent: its forward jump (9: the steps before
    it leaves the ground, airborne, the pixels it travels) and, of its air attacks pressed
    on each step of it from each distance, the one that hits Ayu crouch-guarding (a high:
    air attacks are guarded standing) where a standing guard holds it, the contact as late
    in the jump as there is one: {'button', 'press' (steps after the 9), 'contact' (steps
    after the 9 to the hit), 'distance' (pixels apart at the 9)}, or None."""
    from efz_env.actions import encode
    env.set_matches(chars=('ayu', char), stage=0)
    env.reset()
    for _ in range(30):
        _step(env, 0, 0)
    start = env.save_state(0)
    x0 = env_obs(env)[0, 1, X] * 640
    pre = air = 0
    for t in range(200):
        obs = _step(env, 0, encode(9) if not air else 0)
        if obs[0, 1, AIRBORNE] > 0.5:
            air += 1
        elif air:
            break
        else:
            pre += 1
    travel = abs(env_obs(env)[0, 1, X] * 640 - x0)
    jump = dict(prejump=pre, air=air, travel=round(float(travel), 1))
    best = None

    def run(distance, button, press, guard, way=9):
        """Ayu holding `guard` (1 crouching, 4 standing) from far: 'hit', 'guard' or None,
        and the step of the contact after the jump's input (way: 9 forward, 8 straight up)."""
        env.load_state(0, start)
        for _ in range(300):  # walk in to the distance, Ayu guarding
            d = abs(env_obs(env)[0, 1, DX]) * 640
            if d <= distance:
                break
            _step(env, encode(guard), encode(6))
        else:
            return None, None
        if abs(abs(env_obs(env)[0, 1, DX]) * 640 - distance) > 8:
            return None, None  # (as close as the two can stand: no nearer)
        for t in range(pre + air + 4):
            c2 = encode(way) if t < pre else encode(5, button) if t == press else 0
            obs = _step(env, encode(guard), c2)
            if obs[0, 0, 20] > 0.5:  # self_hitstun
                return 'hit', t + 1
            if obs[0, 0, GUARDING] > 0.5:
                return 'guard', t + 1
        return None, None

    # The latest-contact plan from each distance, every 8 pixels: forward jumps from a
    # third of their travel on, straight-up ones from close (a forward one from there
    # crosses over: a standing guard the other way no longer holds it).
    plans = []
    grid = [(9, x) for x in np.arange(0.35 * travel, 1.1 * travel, 8.0)] + \
        [(8, x) for x in np.arange(16.0, 0.5 * travel, 8.0)]
    for way, distance in grid:
        here = None
        for button in buttons:
            for press in range(pre, pre + air):
                got, contact = run(distance, button, press, 1, way)
                if got != 'hit':
                    continue
                stood, _ = run(distance, button, press, 4, way)
                if stood != 'guard':
                    continue
                if here is None or contact > here['contact']:
                    here = dict(way=way, button=button, press=press, contact=contact,
                                distance=round(float(distance), 1))
        if here:
            plans.append(here)
            if best is None or here['contact'] > best['contact']:
                best = here
    jump['jumpin'] = best
    jump['plans'] = plans
    return jump


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--out', default=os.path.join(HERE, 'motions.json'))
    p.add_argument('--chars', nargs='*')
    p.add_argument('--add', nargs='*', choices=('wake', 'jump', 'meaty'), default=None,
                   help="only these probes, added to --out's characters as they are: wake "
                        "(the rising length, each invincible move's wake_delay), jump (the "
                        "jump-in)")
    args = p.parse_args()
    if args.add is not None:
        return add(args)
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


def add(args):
    """--add: the wake and jump probes over an existing motions.json."""
    from efz_env import EfzVecEnv
    from efz_env._native import library
    lib = library()
    obs_names = [lib.efz_env_obs_name(i).decode() for i in range(lib.efz_env_obs_dim())]
    own = obs_names.index('self_action')
    out = json.load(open(args.out))
    env = EfzVecEnv(args.data, 1, num_threads=1, seed=1, autoreset='disabled')
    for char in args.chars or list(out):
        c = out[char]
        if 'wake' in args.add:
            got = probe_wake(env, char, c['invincible'], own)
            if got:
                c.update(got)
            print(f"{char}: rising {c.get('rise')} steps (knockdown {c.get('knockdown')}); "
                  + ', '.join(f"{m['motion']} from step {m.get('wake_delay')} -> starts at "
                              f"{m.get('wake_start')}" for m in c['invincible']), flush=True)
        if 'jump' in args.add:
            c['jump'] = probe_jump(env, char, own)
            print(f"{char}: jump {c['jump']}", flush=True)
        if 'meaty' in args.add:
            got = probe_meaty(env, char, c['invincible'], own)
            if got:
                c.update(got)
            print(f"{char}: against a meaty 2A, " + ', '.join(
                f"{m['motion']} {m.get('wake_wins')}" for m in c['invincible']), flush=True)
    env.close()
    with open(args.out, 'w') as f:
        json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
