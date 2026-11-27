"""Replay and full-match tests of Ayu's answers to Sayuri. See docs/sayuri-throws.md."""
import argparse
from collections import Counter, deque
import json
from pathlib import Path

import numpy as np

from neutral_trials import DELAY, HERE, env_for
from efz_env import EfzVecEnv
from efz_env.actions import encode
from efz_env.export import NativeAgent
from from_record import seed_for
import advantages

THROWN = set(range(0x64, 0x79))
GROUND = (0xdc, 0xdd)
AIR = (0xf8, 0xf9)
RUN = (0xfd, 0xfe, 0xff)
SUPER = (0x12c, 0x12d, 0x12e)
ACTIONS = ('retreat', 'jump', 'jab', 'guard')
HOLD = 8
COOLDOWN = 32
HORIZON = 120


def family(move):
    if move in GROUND:
        return 'ground'
    if move in AIR:
        return 'air'
    if move in RUN:
        return 'run'
    if move in SUPER:
        return 'super'
    if move == 0x12b:
        return 'parry'
    return 'other'


def cue(v):
    if v[2] or v[3] or int(v[18]) in THROWN:
        return None
    foe = int(v[50])
    if foe == 0x100:
        return 'stance'
    if foe in RUN + SUPER:
        return 'rush'
    if (foe == 1 and not v[39] and not v[71] and abs(float(v[4]))*640 <= 42
            and not v[20] and not v[52] and int(v[18]) in (0, 1, 2, 3, 4, 8)):
        return 'walk'
    return None


class Signals:
    def __init__(self):
        self.previous = None
        self.last = {}

    def event(self, tick, seen):
        current = cue(seen)
        entered = current and current != self.previous and tick-self.last.get(current, -COOLDOWN) >= COOLDOWN
        self.previous = current
        if entered:
            self.last[current] = tick
            return current
        return None


def response(action, age, original):
    if action is None or age >= HOLD:
        return original
    if action == 'release':
        return original & 15
    if action == 'jab':
        return encode(2, 'A') if age == 0 else encode(1)
    return encode({'guard': 1, 'jump': 7, 'retreat': 4}[action])


class WalkMix:
    """A defender that sometimes walks in for a throw, low jab or guard.

    Choose the finish on entry. All three finishes share their approach and
    use the same delayed view. The underlying policy plays between approaches.
    """
    def __init__(self, throw_share, rng):
        self.share = throw_share
        self.rng = rng
        self.finish = None
        self.ready = 0

    def step(self, tick, seen, counts):
        # The stored view faces Ayu. Indices 50 and 52 belong to Sayuri.
        if seen[2] or seen[3] or seen[39] or seen[71] or seen[52]:
            self.finish = None
            return None
        distance = abs(float(seen[4])) * 640
        if self.finish is None:
            if (tick < self.ready or not 40 <= distance <= 75
                    or int(seen[50]) not in (0, 1, 2, 3, 4, 8) or seen[20]):
                return None
            roll = self.rng.random()
            if roll < self.share:
                self.finish = 'throw'
            elif roll < (1 + self.share) / 2:
                self.finish = 'jab'
            else:
                self.finish = 'guard'
            self.start = tick
            self.ready = tick + 96
            counts['approach'] += 1
        if tick - self.start >= 32:
            self.finish = None
            return None
        if distance > 30 or tick - self.start < 5:
            return encode(6)
        finish = self.finish
        self.finish = None
        counts['approach_' + finish] += 1
        return {'throw': encode(6, 'C'), 'jab': encode(2, 'A'), 'guard': encode(1)}[finish]


def sets(args):
    env = env_for(args.data)
    ayu = NativeAgent(args.agent)
    foe = NativeAgent(args.opponent or HERE / args.char / args.generation / 'combos.efzagent')
    assert ayu.delay == foe.delay == DELAY
    rules = json.loads(args.rules)
    if rules and args.char != 'sayuri':
        raise ValueError('The walk-in rules apply to Sayuri')
    if any(k not in ('walk', 'rush', 'stance') or v not in ACTIONS for k,v in rules.items()):
        raise ValueError('Invalid response rules')
    with args.out.open('x') as out:
        for seed in range(args.seed, args.seed+args.count):
            env.set_matches(chars=('ayu', args.char))
            env.seed(0, seed)
            env.reset()
            ayu.attach(env, 0, 0, seed=seed)
            foe.attach(env, 0, 1, seed=seed+1)
            habit = advantages.Advantages(args.char, 1, throw=args.throw, antiair=args.antiair, seed=seed+2)
            walk_rng = np.random.default_rng(seed + 3)
            legs = []
            saw_ground_throw = False
            for leg in range(3):
                if leg:
                    ayu.next_match()
                    foe.next_match()
                    habit.clear(0)
                    env.reset()
                recent = deque(maxlen=DELAY)
                counts = Counter()
                signals = Signals()
                tick = net = prev_input = presses = pressure = pressure_presses = 0
                was_thrown = False
                prior_round = -1
                active = None
                started = -HOLD
                while True:
                    me, op = env.obs[0]
                    if int(me[1]) != prior_round:
                        prior_round = int(me[1])
                        recent.clear()
                        signals = Signals()
                        active = None
                        walk_mix = WalkMix(args.walk_mix, walk_rng) if args.walk_mix is not None else None
                    live = not (me[2] or me[3])
                    a = ayu.step(me, live)
                    b = foe.step(op, live)
                    if args.throw or args.antiair:
                        extra = habit.step(0, op)
                        if extra is not None:
                            b = encode(*extra)
                    if args.char == 'sayuri' and len(recent) == DELAY:
                        seen = recent[0]
                        if walk_mix and live:
                            walk_input = walk_mix.step(tick, seen, counts)
                            if walk_input is not None:
                                b = walk_input
                        if int(seen[18]) in THROWN and int(seen[50]) in GROUND:
                            saw_ground_throw = True
                        label = signals.event(tick, seen)
                        if label:
                            counts['cue_'+label] += 1
                            if label in rules and (saw_ground_throw or not args.after_ground):
                                started, active = tick, rules[label]
                                counts['response_'+label] += 1
                    recent.append(me.copy())
                    a = response(active, tick-started, a)
                    ayu.played(a)
                    foe.played(b)
                    pressed = int((a & ~prev_input) >> 4).bit_count()
                    blocked = bool(me[20] or me[21])
                    presses += pressed
                    pressure += blocked
                    pressure_presses += blocked*pressed
                    prev_input = a
                    _, reward, term, cut, info = env.step(np.array([[a,b]], np.uint8))
                    net += round(float(reward[0,0])*9999)
                    nxt = env.obs[0,0]
                    thrown = int(nxt[18]) in THROWN
                    if args.char == 'sayuri' and thrown and not was_thrown:
                        counts[family(int(nxt[50]))] += 1
                    was_thrown = thrown
                    tick += 1
                    if term[0] or cut[0]:
                        assert term[0]
                        legs.append(dict(win=int(info['winner'][0] == 0), net=net, frames=tick,
                                         presses=presses, pressure=pressure, pressure_presses=pressure_presses,
                                         counts=dict(counts)))
                        break
            print(json.dumps(dict(seed=seed,char=args.char,generation=args.generation,
                                  opponent=args.opponent.name if args.opponent else None,throw=args.throw,
                                  antiair=args.antiair,walk_mix=args.walk_mix,rules=rules,
                                  after_ground=args.after_ground,legs=legs)),
                  file=out, flush=True)
    ayu.close()
    foe.close()
    env.close()


def entries(v):
    previous = False
    for t, frame in enumerate(v):
        thrown = int(frame[18]) in THROWN
        if thrown and not previous:
            yield t, family(int(frame[50]))
        previous = thrown


def opening_points(v):
    """Diagnostic starts before the hit that led to a running grab or super."""
    points = {}
    casts = set()
    for caught, kind in entries(v):
        if kind not in ('run','super'):
            continue
        cast = caught
        while cast and v[cast-1,50] == v[caught,50]:
            cast -= 1
        if cast in casts or not v[cast,20]:
            continue
        casts.add(cast)
        hit = cast
        while hit and v[hit-1,20]:
            hit -= 1
        for lead in (4,8,16):
            points.setdefault(hit-lead, []).append(dict(opening=kind, hit=hit, target=caught, lead=lead))
        # Intervene before the input that began Ayu's last action preceding the opening hit.
        start = hit-1
        while start and v[start-1,18] == v[hit-1,18]:
            start -= 1
        if start and v[start,18] == 0x107 and v[start-1,18] in (0x104,0x105,0x106):
            start -= 1
            while start and v[start-1,18] == v[start,18]:
                start -= 1
        if start > 0:
            points.setdefault(start-1, []).append(dict(commit=int(v[start,18]), hit=hit, target=caught,
                                                        opening=kind))
    return points


def replay(args):
    fight = args.session / f'fight-{args.fight:03}.jsonl'
    with fight.open() as f:
        head = json.loads(f.readline())
    chars = tuple(x['name'] for x in head['players'])
    assert chars[0] == 'ayu' and head['mode_name'] == 'vs human'
    if not args.risk_casts:
        assert chars[1] == 'sayuri'
    path = args.recordings / f"{head['session']}-{args.fight:03}.npz"
    with np.load(path) as record:
        obs = record['obs']
        inputs = record['controls']
        final = record['final_obs']
    def world():
        w = EfzVecEnv(args.data, 1, num_threads=1, skip_noninteractive=False,
                      rounds_to_win=head['rounds_to_win'], reward_match=0, autoreset='disabled')
        w.set_matches(chars=chars, stage=head['stage'], palettes=tuple(x['palette'] for x in head['players']))
        w.seed(0, seed_for(head['rng']))
        w.reset()
        for side in (0,1):
            w.set_gauges(0,side,rf=0)
        return w
    env, branch = world(), world()
    play_branches(args, env, branch, obs, inputs, final, side=0, diagnostic=True)


def validate_rep(args):
    env, branch = env_for(args.data), env_for(args.data)
    env.play(0, args.rep)
    env.reset()
    obs, controls = [], []
    idle = np.zeros((1,2), np.uint8)
    while True:
        obs.append(env.obs[0].copy())
        _, _, end, cut, info = env.step(idle)
        controls.append(info['input'][0].copy())
        if end[0] or cut[0]:
            assert end[0] and info['frame'][0] == args.frames and info['winner'][0] == args.winner
            break
    final = env.obs[0].copy()
    env.play(0, args.rep)
    env.reset()
    play_branches(args, env, branch, np.stack(obs), np.stack(controls), final, args.side, False)


def play_branches(args, env, branch, obs, inputs, final, side, diagnostic):
    v = obs[:,side]
    points = {}
    for t, kind in entries(v) if diagnostic else ():
        for lead in (12, 24, 48, 64):
            if t > lead:
                points.setdefault(t-lead, []).append(dict(event=kind, target=t, lead=lead))
    signals = Signals()
    for t in range(DELAY, len(v)):
        if v[t-DELAY,1] != v[t,1]:
            signals = Signals()
            continue
        key = signals.event(t, v[t-DELAY])
        if key and (diagnostic or key == 'walk'):
            points.setdefault(t, []).append(dict(cue=key))
    if args.openings:
        points = opening_points(v)
    if args.all_commits:
        points = {t: [dict(commit=int(v[t+1,18]))] for t in range(len(v)-1)
                  if v[t+1,18] in (0x106,0x101,0x132) and v[t,18] != v[t+1,18]}
    if args.risk_casts:
        points = {t: [dict(commit=int(v[t+1,18]), char=int(v[t,66]))] for t in range(DELAY,len(v)-1)
                  if v[t+1,18] in (0x100,0x101,0x102,0x106,0x132) and v[t,18] != v[t+1,18]
                  and not v[t-DELAY,62] and not v[t-DELAY,52]}
    if args.players:
        native_walk_trials(args,env,branch,obs,inputs,side)
        env.close()
        branch.close()
        return

    with args.out.open('x') as out:
        for t, original in enumerate(inputs):
            if not np.allclose(env.obs[0], obs[t], atol=1e-6, rtol=0):
                raise ValueError(f'Original tape diverged at {t}')
            if t in points:
                state = env.save_state(0)
                options = {}
                horizon = max(HORIZON, max(z.get('target',t)-t+32 for z in points[t])) if args.openings else HORIZON
                actions = (None, *ACTIONS) if diagnostic else (None, 'jump')
                if args.all_commits:
                    horizon, actions = 240, (None, 'retreat')
                if args.risk_casts:
                    horizon, actions = 240, (None, 'release')
                for action in actions:
                    branch.load_state(0, state)
                    net = 0
                    catches = []
                    was_thrown = int(v[t,18]) in THROWN
                    for i in range(t, min(t+horizon,len(v))):
                        ctl = inputs[i:i+1].copy()
                        ctl[0,side] = response(action, i-t, ctl[0,side])
                        _, reward, end, cut, _ = branch.step(ctl)
                        now = branch.obs[0,side]
                        if action is None:
                            expected = obs[i+1] if i+1 < len(v) else final
                            if not np.allclose(branch.obs[0], expected, atol=1e-6, rtol=0):
                                raise ValueError(f'Unmodified branch diverged at {i} from {t}')
                        net += round(float(reward[0,side])*9999)
                        thrown = int(now[18]) in THROWN
                        if thrown and not was_thrown:
                            catches.append([i+1-t,family(int(now[50]))])
                        was_thrown = thrown
                        if end[0] or cut[0] or now[1] != v[t,1]:
                            break
                    options[action or 'base'] = dict(net=net, catches=catches)
                print(json.dumps(dict(fight=args.fight if diagnostic else args.rep.name, frame=t, labels=points[t], options=options)),
                      file=out, flush=True)
            env.step(original[None,:])
    assert np.allclose(env.obs[0], final, rtol=0, atol=1e-6)
    env.close()
    branch.close()


def native_walk_trials(args, env, branch, obs, inputs, side):
    """Play each native model at the same walk-in, against the recorded defender."""
    warm = 48
    v = obs[:,side]
    signals = Signals()
    points = set()
    for t in range(warm,len(v)):
        if v[t-warm,1] != v[t,1]:
            signals = Signals()
            continue
        if signals.event(t,v[t-DELAY]) == 'walk':
            points.add(t)
    players = {path.stem:NativeAgent(path) for path in args.players}
    if len(players) != len(args.players):
        raise ValueError('Native trial model filenames must be distinct')
    snapshots = {}
    with args.out.open('x') as out:
        for t, original in enumerate(inputs):
            if t+warm in points:
                snapshots[t+warm] = env.save_state(0)
            if t in points:
                source = snapshots.pop(t)
                original_ground = any(j > 0 and kind == 'ground' and v[t+j, 1] == v[t, 1]
                                      for j, kind in entries(v[t:t+33]))
                for draw in range(args.draws):
                    outcomes={}
                    for name, agent in players.items():
                        branch.load_state(0,source)
                        agent.attach(branch,0,side,seed=t*41+draw*1033)
                        for j in range(t-warm,t):
                            view=branch.obs[0,side]
                            agent.step(view,not (view[2] or view[3]))
                            agent.played(int(inputs[j,side]))
                            branch.step(inputs[j:j+1])
                        np.testing.assert_allclose(branch.obs[0],obs[t],atol=1e-6,rtol=0)
                        net=ground=0
                        first=None
                        was_thrown=int(v[t,18]) in THROWN
                        for j in range(t,min(t+HORIZON,len(v))):
                            view=branch.obs[0,side]
                            a=agent.step(view,not (view[2] or view[3]))
                            if first is None:
                                first=int(a)
                            ctl=inputs[j:j+1].copy()
                            ctl[0,side]=a
                            _,reward,end,cut,_=branch.step(ctl)
                            net+=round(float(reward[0,side])*9999)
                            view=branch.obs[0,side]
                            thrown=int(view[18]) in THROWN
                            if j-t<32 and thrown and not was_thrown and int(view[50]) in GROUND:
                                ground+=1
                            was_thrown=thrown
                            if end[0] or cut[0] or view[1] != v[t,1]:
                                break
                        outcomes[name]=dict(net=net,ground=ground,first=first)
                    print(json.dumps(dict(frame=t, draw=draw, original_ground=original_ground,
                                          outcomes=outcomes)), file=out, flush=True)
            env.step(original[None,:])
    for player in players.values():
        player.close()


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('mode', choices=['replay','sets','validate'])
    p.add_argument('--data', type=Path, required=True)
    p.add_argument('--agent', type=Path)
    p.add_argument('--session', type=Path)
    p.add_argument('--recordings', type=Path)
    p.add_argument('--fight', type=int)
    p.add_argument('--openings', action='store_true', help='diagnose the opening hits of recorded carries')
    p.add_argument('--all-commits', action='store_true', help='test retreat at every 236C, 214B or level-one 641236A start')
    p.add_argument('--risk-casts', action='store_true', help='replay raw specials with their buttons released')
    p.add_argument('--players', nargs='+', type=Path, help='compare native files from the actual walk-in cues')
    p.add_argument('--draws', type=int, default=8)
    p.add_argument('--rep', type=Path)
    p.add_argument('--side', type=int, choices=[0,1], default=0)
    p.add_argument('--frames', type=int)
    p.add_argument('--winner', type=int)
    p.add_argument('--out', type=Path, required=True)
    p.add_argument('--generation', default='exploiter19')
    p.add_argument('--char', default='sayuri', help='opposing character in full sets')
    p.add_argument('--opponent', type=Path, help='specific opponent agent file in full sets')
    p.add_argument('--throw', type=float, default=0)
    p.add_argument('--antiair', type=float, default=0)
    p.add_argument('--walk-mix', type=float, help='throw share after a delayed walk-in; other finishes are jab or guard')
    p.add_argument('--seed', type=int, default=240)
    p.add_argument('--count', type=int, default=1)
    p.add_argument('--rules', default='{}')
    p.add_argument('--after-ground', action='store_true', help='require an observed ground throw in this set')
    args = p.parse_args()
    if args.walk_mix is not None and (args.mode != 'sets' or args.char != 'sayuri' or not 0 <= args.walk_mix <= 1):
        p.error('--walk-mix requires Sayuri sets and a throw share between 0 and 1')
    studies = (args.openings, args.all_commits, args.risk_casts, bool(args.players))
    if sum(studies) > 1 or (args.mode == 'sets' and any(studies)):
        p.error('choose a single replay diagnosis when replaying or validating a recording')
    if (args.openings or args.risk_casts) and args.mode != 'replay':
        p.error('opening and raw-special diagnoses require tester fight records')
    if args.players and args.draws < 1:
        p.error('--players requires a positive number of draws')
    if args.mode == 'replay' and None in (args.fight, args.session, args.recordings):
        p.error('replay needs --session, --recordings and --fight')
    if args.mode == 'validate' and None in (args.rep, args.frames, args.winner):
        p.error('validate needs --rep, --frames and --winner')
    if args.mode == 'sets' and not args.agent:
        p.error('sets needs --agent')
    if args.mode == 'sets':
        sets(args)
    elif args.mode == 'validate':
        validate_rep(args)
    else:
        replay(args)


if __name__ == '__main__':
    main()
