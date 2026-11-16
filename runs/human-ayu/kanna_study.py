"""Where an agent's HP goes against the level-4 CPU's Kanna, and how its invincible moves
fare: the user's way of beating her without throws is big combos and invincible moves
put out as she acts, overriding her slow, long moves and starting a combo.

    python runs/human-ayu/kanna_study.py --p1 runs/human-ayu/agent-league6/best.zip --matches 32

Plays P1 (Ayu) against the CPU (--char, --level) to the end and reports, per minute:
- her attacks, out of her combos (her own moves started, by move, with their startup
  from framedata.json; those that go on a combo of hers are only totalled): how many,
  the share that hit the agent, that it guarded, and that did neither: the agent hit her
  in it before it could hit (overridden) or after it missed (punished: her long moves
  leave time to see the miss and answer it), or nothing happened; and what the agent was
  doing when she started (free, in a move of its own, in the air, guarding);
- the HP she took, by the move that started each of her combos (her action on the step
  the combo counter starts: an object's hit is counted under the move she is in then)
  and whether the agent was in the air;
- the agent's invincible moves (reversals): what she was doing when it started one, and
  how it went: a counter-hit (it hit her in a move of hers), a hit, or no hit, and then
  whether she hit it within PUNISH steps;
- her attacks slow enough to be beaten on sight: startup of at least REACT steps (the
  14-step reaction, then a reversal invincible from its 2nd step), and how often the
  agent answered one with a reversal before it landed;
- her rhythm: her neutral attacks are off for 180 ticks after she was last hit, guarding
  or knocked down (kanna.cpp's m_cpuHitCooldown); the share of her attacks (out of her
  combos), and of the damage of her combos, that came after that lock had ended, how
  soon after it, and the agent's reversals in it and out of it;
- her RF gauge: the share of the time it is red or cyan (236C, her invincible beam,
  623C and 41236C are hers then), and the agent's moves started then and not: the
  share she hit within WINDOW steps (with one of those, when it was up).
"""

import argparse
import json
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))
sys.path.insert(0, HERE)

import numpy as np

from efz_env import EfzVecEnv
from efz_env.agent import Agent

import evaluate
import tactics

# Observation columns (env.observation_names).
DX, HP, ACT, FRAME, HITSTUN, AIR, COMBO, COMBO_DMG = 4, 8, 18, 19, 20, 39, 30, 38
O_ACT, O_FRAME, O_HITSTUN, O_OWN, O_COMBO, O_COMBO_DMG, O_AIR = 50, 51, 52, 67, 62, 70, 71
O_RF, O_RF_BLUE = 42, 43  # opp_rf_gauge (/ 1000), opp_rf_blue
COLS = [DX, HP, ACT, FRAME, HITSTUN, AIR, COMBO, COMBO_DMG, O_ACT, O_FRAME, O_HITSTUN, O_OWN, O_COMBO,
        O_COMBO_DMG, O_AIR, O_RF, O_RF_BLUE]
C = {c: k for k, c in enumerate(COLS)}

FIRST_OWN, FIRST_OBJECT = 0xc8, 0x190
NOT_STARTS = {0x103, 0x136}  # 623's landing, the LV4's miss: not a new move
WINDOW = 60   # steps after her move starts in which its hit or guard is looked for
PUNISH = 60   # steps after a reversal that whiffed in which her hit is looked for
REACT = 17    # her startup from which a reversal can beat a move on sight (14 + 2 + 1)
LOCK_FROM, LOCK_TO, LOCK = 0x32, 0xa1, 180  # hit reactions, knockdowns, guards: her neutral
#   attacks are off for 180 ticks after the last of them (kanna.cpp: m_cpuHitCooldown)
LIVE_BINS = (30, 60, 120)  # steps after the lock ends
KANNA = {  # src/efz.h's CKanna actions
    0xc8: '5A', 0xc9: '5B close', 0xca: '5B far', 0xcb: '5C', 0xcc: '2A', 0xcd: '2B',
    0xce: '2C', 0xcf: 'j.A', 0xd0: 'j.B', 0xd1: 'j.C', 0xfa: '236A/B', 0xfb: '236C',
    0xfd: 'j.236', 0x100: '623', 0x101: '623C', 0x103: '623 landing', 0x107: '214A',
    0x108: '214B', 0x109: '214C', 0x10a: '41236A/B', 0x10b: '41236C', 0x12c: '236236A',
    0x12f: '236236B', 0x132: 'j.236236B', 0x135: 'LV4', 0x136: 'LV4 miss'}
RF_MOVES = {0xfb, 0x101, 0x10b}  # 236C, 623C, 41236C: need her RF gauge red or cyan


def name(char, a):
    if a < FIRST_OWN:
        return 'common'
    return (KANNA.get(a) if char == 'kanna' else None) or hex(a)


def startups(char):
    d = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    return {int(k, 16): v.get('startup') for k, v in d.items()}


def lengths(char):
    d = json.load(open(os.path.join(HERE, 'framedata.json'))).get(char, {})
    return {int(k, 16): v.get('steps') or 0 for k, v in d.items()}


def play(data, path, matches, char, level, minutes, seed):
    env = EfzVecEnv(data, matches, frame_skip=1, max_frames=int(minutes * 3840),
                    cpu_level=level, autoreset='disabled', seed=seed,
                    reward_round=0.0, reward_match=1.0)
    env.set_matches(chars=('ayu', char), cpu=(False, True))
    agent = Agent(path)
    agent.batch(matches)
    obs = env.reset()
    done = np.zeros(matches, bool)
    rec = [[] for _ in range(matches)]
    step = 0
    while not done.all():
        controls = np.zeros((matches, 2), np.uint8)
        controls[:, 0] = agent.controls(obs[:, 0], step)
        view = obs[:, 0, COLS].copy()
        obs, _, term, trunc, info = env.step(controls)
        agent.observe(info['input'][:, 0])
        step += 1
        for i in np.flatnonzero(~done):
            rec[i].append(view[i])
        done |= term | trunc
    env.close()
    return [np.array(r, np.float32) for r in rec]


def _prev(x, fill):
    return np.concatenate([[fill], x[:-1]])


def study(recs, char):
    inv = evaluate.invincible_moves('ayu')
    up = startups(char)
    length = lengths(char)
    guards = set(tactics.GUARDS)
    frames = 0
    attacks = {}       # her move -> [starts, hit, guarded, neither, overridden, punished]
    state_at = {}      # her move -> the agent's state when she starts it -> count
    combo_moves = 0    # her moves started in a combo of hers (or on the agent down)
    rf = dict(up=0, own_up=0, own_up_hit=0, own_up_beam=0, own_down=0, own_down_hit=0)
    taken = {}         # (her starter, agent in the air) -> [combos, damage]
    rev_vs = {}        # what she was doing when the agent's reversal started -> [n, counter, hit, punished]
    rev = dict(n=0, counter=0, hit=0, missed_punished=0, missed_safe=0, damage_after_miss=0.0,
               combo_after_counter=0.0)
    countered = {}     # her move a counter-hit overrode -> count
    slow = dict(n=0, answered=0, answered_counter=0, hit_agent=0)
    hp_lost = 0.0
    rhythm = dict(attacks_locked=0, attacks_live=0, live_after=[0] * (len(LIVE_BINS) + 1),
                  damage_locked=0.0, damage_live=0.0, rev_locked=[0, 0], rev_live=[0, 0])
    for r in recs:
        T = len(r)
        if T < 2:
            continue
        frames += T
        a = np.round(r[:, C[ACT]]).astype(int)
        oa = np.round(r[:, C[O_ACT]]).astype(int)
        hp = r[:, C[HP]] * 9999
        hp_lost += float(np.clip(hp[:-1] - hp[1:], 0, None).sum())
        hit = (r[:, C[HITSTUN]] > 0) & ~_prev(r[:, C[HITSTUN]] > 0, False)
        ohit = (r[:, C[O_HITSTUN]] > 0) & ~_prev(r[:, C[O_HITSTUN]] > 0, False)
        air = r[:, C[AIR]] > 0
        oown = r[:, C[O_OWN]] > 0
        enter, oenter = a != _prev(a, -1), oa != _prev(oa, -1)
        guard_in = enter & np.isin(a, list(guards))
        # Steps since she was last in a hit reaction, a knockdown or a guard (as the game is).
        locked_state = (oa >= LOCK_FROM) & (oa < LOCK_TO)
        since = np.zeros(T, int)
        last = -10 ** 6
        for t in range(T):
            if locked_state[t]:
                last = t
            since[t] = t - last
        # Her attacks: those started in a combo of hers go on it; the others by what the
        # agent was doing then.
        in_combo = np.round(r[:, C[O_COMBO]] * 30) > 0
        for t in np.flatnonzero(oenter & (oa >= FIRST_OWN) & (oa < FIRST_OBJECT)):
            m = int(oa[t])
            if m in NOT_STARTS:
                continue
            if in_combo[t] or r[t, C[HITSTUN]] > 0 or a[t] in tactics.DOWN:
                combo_moves += 1
                continue
            k = name(char, m)
            row = attacks.setdefault(k, [0, 0, 0, 0, 0, 0])
            row[0] += 1
            if since[t] <= LOCK:
                rhythm['attacks_locked'] += 1
            else:
                rhythm['attacks_live'] += 1
                rhythm['live_after'][int(np.searchsorted(LIVE_BINS, since[t] - LOCK))] += 1
            w = slice(t, min(T, t + WINDOW))
            h, g = np.flatnonzero(hit[w]), np.flatnonzero(guard_in[w])
            if len(h) and (not len(g) or h[0] <= g[0]):
                row[1] += 1
            elif len(g):
                row[2] += 1
            else:
                row[3] += 1
                # the agent hit her while she was still in it: before it could hit
                # (overridden) or after (a miss punished)
                end = min(T, t + max(length.get(m, 0), 1) + 4)
                oh = np.flatnonzero(ohit[t:end])
                if len(oh) and oown[max(0, t + int(oh[0]) - 1)]:
                    row[4 if int(oh[0]) <= (up.get(m) or 0) else 5] += 1
            s = ('air' if air[t] else 'guarding' if a[t] in guards else
                 'own move' if a[t] >= FIRST_OWN else 'free')
            st = state_at.setdefault(k, {})
            st[s] = st.get(s, 0) + 1
            st = state_at.setdefault('all', {})
            st[s] = st.get(s, 0) + 1
            su = up.get(m)
            if su is not None and su >= REACT and r[t, C[HITSTUN]] == 0:
                slow['n'] += 1
                w2 = slice(t, min(T, t + su))
                ans = np.flatnonzero(enter[w2] & np.isin(a[w2], list(inv)))
                if len(ans):
                    slow['answered'] += 1
                    t2 = t + int(ans[0])
                    oh = np.flatnonzero(ohit[t2:min(T, t2 + evaluate.HIT_WINDOW)])
                    slow['answered_counter'] += int(len(oh) > 0)
                slow['hit_agent'] += int(len(h) > 0 and (not len(g) or h[0] <= g[0]))
        # Her combos on the agent, by the move that started them.
        on = np.round(r[:, C[O_COMBO]] * 30) > 0
        starts = np.flatnonzero(on & ~_prev(on, False))
        ends = np.flatnonzero(~on & _prev(on, False))
        for b in starts:
            later = ends[ends > b]
            e = later[0] if len(later) else T
            key = (name(char, int(oa[b])), bool(air[b - 1] if b > 0 else air[b]))
            row = taken.setdefault(key, [0, 0.0])
            row[0] += 1
            dmg = float(r[b:e, C[O_COMBO_DMG]].max() * 9999)
            row[1] += dmg
            rhythm['damage_locked' if since[b] <= LOCK else 'damage_live'] += dmg
        # The agent's reversals.
        for t in np.flatnonzero(enter & np.isin(a, list(inv))):
            rev['n'] += 1
            her = ('hit' if r[t, C[O_HITSTUN]] > 0 else name(char, int(oa[t])) if oa[t] >= FIRST_OWN
                   else 'guarding' if oa[t] in guards else 'down' if oa[t] in tactics.DOWN
                   else 'free')
            row = rev_vs.setdefault(her, [0, 0, 0, 0])
            row[0] += 1
            oh = np.flatnonzero(ohit[t:min(T, t + evaluate.HIT_WINDOW)])
            rl = rhythm['rev_locked' if since[t] <= LOCK else 'rev_live']
            rl[0] += 1
            rl[1] += int(len(oh) > 0 and oown[max(0, t + int(oh[0]) - 1)])
            if len(oh):
                th = t + int(oh[0])
                if oown[max(0, th - 1)]:
                    rev['counter'] += 1
                    row[1] += 1
                    m = name(char, int(oa[max(0, th - 1)]))
                    countered[m] = countered.get(m, 0) + 1
                    # the combo it started: its combo counter's run from the hit
                    run = np.round(r[th:min(T, th + 480), C[COMBO]] * 30) > 0
                    stop = np.flatnonzero(~run[1:])
                    e = th + 1 + (int(stop[0]) if len(stop) else len(run) - 1)
                    rev['combo_after_counter'] += float(r[th:e, C[COMBO_DMG]].max() * 9999)
                else:
                    rev['hit'] += 1
                    row[2] += 1
            else:
                h = np.flatnonzero(hit[t:min(T, t + PUNISH)])
                if len(h):
                    rev['missed_punished'] += 1
                    row[3] += 1
                    rev['damage_after_miss'] += float(hp[t] - hp[min(T - 1, t + PUNISH + 60)])
                else:
                    rev['missed_safe'] += 1
        # Her RF gauge (red or cyan: 236C, the invincible beam, and 623C, 41236C, are
        # hers) and the agent's own moves started then or not: hit within WINDOW steps.
        up_rf = (r[:, C[O_RF]] * 1000 >= 500) | (r[:, C[O_RF_BLUE]] > 0)
        rf['up'] += int(up_rf.sum())
        for t in np.flatnonzero(enter & (a >= FIRST_OWN) & (a < FIRST_OBJECT) & ~in_combo):
            h = np.flatnonzero(hit[t:min(T, t + WINDOW)])
            if up_rf[t]:
                rf['own_up'] += 1
                rf['own_up_hit'] += int(len(h) > 0)
                rf['own_up_beam'] += int(len(h) > 0 and oa[t + int(h[0])] in RF_MOVES)
            else:
                rf['own_down'] += 1
                rf['own_down_hit'] += int(len(h) > 0)
    per_min = 64 * 60 / max(1, frames)

    def table(d, n_cols):
        return {k: [round(v[0] * per_min, 2)] + [round(x / v[0], 3) if v[0] else None
                                                 for x in v[1:n_cols]]
                for k, v in sorted(d.items(), key=lambda kv: -kv[1][0])}
    total_combo = sum(v[1] for v in taken.values())
    out = dict(
        minutes=round(frames / 3840, 1),
        hp_lost_per_min=round(hp_lost * per_min),
        her_attacks={k: dict(per_min=round(v[0] * per_min, 2), startup=None,
                             hit=round(v[1] / v[0], 3), guarded=round(v[2] / v[0], 3),
                             neither=round(v[3] / v[0], 3),
                             overridden=round(v[4] / v[0], 3),
                             missed_punished=round(v[5] / v[0], 3))
                     for k, v in sorted(attacks.items(), key=lambda kv: -kv[1][0])},
        her_combo_moves_per_min=round(combo_moves * per_min, 2),
        agent_when_she_attacks={m: {k: round(v / max(1, sum(st.values())), 3)
                                    for k, v in sorted(st.items(), key=lambda kv: -kv[1])}
                                for m, st in state_at.items()},
        her_rf=dict(up_share=round(rf['up'] / max(1, frames), 3),
                    agent_moves_per_min_up=round(rf['own_up'] * per_min, 2),
                    hit_after_up=round(rf['own_up_hit'] / max(1, rf['own_up']), 3),
                    by_rf_move_after_up=round(rf['own_up_beam'] / max(1, rf['own_up']), 3),
                    agent_moves_per_min_down=round(rf['own_down'] * per_min, 2),
                    hit_after_down=round(rf['own_down_hit'] / max(1, rf['own_down']), 3)),
        taken_by_starter={f"{k[0]}{' (agent in the air)' if k[1] else ''}":
                          dict(combos_per_min=round(v[0] * per_min, 2),
                               damage_per_min=round(v[1] * per_min),
                               share=round(v[1] / total_combo, 3) if total_combo else None,
                               avg=round(v[1] / v[0]))
                          for k, v in sorted(taken.items(), key=lambda kv: -kv[1][1])},
        reversals=dict(per_min=round(rev['n'] * per_min, 2),
                       counter=round(rev['counter'] / rev['n'], 3) if rev['n'] else None,
                       hit=round(rev['hit'] / rev['n'], 3) if rev['n'] else None,
                       missed_punished=round(rev['missed_punished'] / rev['n'], 3) if rev['n'] else None,
                       missed_safe=round(rev['missed_safe'] / rev['n'], 3) if rev['n'] else None,
                       combo_after_counter=round(rev['combo_after_counter'] / max(1, rev['counter'])),
                       hp_lost_after_punished_miss=round(rev['damage_after_miss'] /
                                                         max(1, rev['missed_punished']))),
        reversals_by_her_state={k: dict(per_min=v[0], counter=v[1], hit=v[2], punished=v[3])
                                for k, v in table(rev_vs, 4).items()},
        counter_hit_her_move={k: v for k, v in sorted(countered.items(), key=lambda kv: -kv[1])},
        rhythm=dict(
            attacks_live_share=round(rhythm['attacks_live'] / max(1, rhythm['attacks_live'] + rhythm['attacks_locked']), 3),
            live_attacks_within=dict(zip([f'{b}' for b in LIVE_BINS] + ['more'],
                                         [round(x / max(1, rhythm['attacks_live']), 3)
                                          for x in rhythm['live_after']])),
            damage_live_share=round(rhythm['damage_live'] / max(1.0, rhythm['damage_live'] + rhythm['damage_locked']), 3),
            reversals_locked_per_min=round(rhythm['rev_locked'][0] * per_min, 2),
            reversals_locked_counter=round(rhythm['rev_locked'][1] / max(1, rhythm['rev_locked'][0]), 3),
            reversals_live_per_min=round(rhythm['rev_live'][0] * per_min, 2),
            reversals_live_counter=round(rhythm['rev_live'][1] / max(1, rhythm['rev_live'][0]), 3)),
        slow_attacks=dict(per_min=round(slow['n'] * per_min, 2),
                          answered=round(slow['answered'] / slow['n'], 3) if slow['n'] else None,
                          answered_counter=round(slow['answered_counter'] / max(1, slow['answered']), 3),
                          hit_agent=round(slow['hit_agent'] / slow['n'], 3) if slow['n'] else None),
    )
    for k, v in out['her_attacks'].items():
        m = next((a for a, nm in KANNA.items() if nm == k), None) if char == 'kanna' else None
        v['startup'] = up.get(m) if m is not None else None
    return out


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n\n')[0])
    p.add_argument('--p1', required=True)
    p.add_argument('--char', default='kanna')
    p.add_argument('--level', type=int, default=4)
    p.add_argument('--matches', type=int, default=32)
    p.add_argument('--minutes', type=float, default=10)
    p.add_argument('--seed', type=int, default=7)
    p.add_argument('--json')
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    args = p.parse_args()
    recs = play(args.data, args.p1, args.matches, args.char, args.level, args.minutes, args.seed)
    out = study(recs, args.char)
    print(json.dumps(out, indent=1))
    if args.json:
        os.makedirs(os.path.dirname(os.path.abspath(args.json)), exist_ok=True)
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


if __name__ == '__main__':
    main()
