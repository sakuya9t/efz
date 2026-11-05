"""People's matches as data: plays back every replay of the community's collection in
which a character (Ayu by default) plays, and keeps that side's view and inputs at each
step, as an agent playing it would have them.

    python runs/human-ayu/dataset.py --replays D:/tasogare/efz-replays --out D:/tasogare/efz-replays/datasets/ayu

--replays is the folder with the collection's index.csv (its replays, by path, and their
headers). Each replay is played with EfzVecEnv.play at frame_skip=1 (a step a frame;
the intros and KOs run through within a step, as in training), and for each side the
character plays, OUT/<id>-<side>.npz gets:

    obs      (T, obs_dim) float16  the side's view before each step
    input    (T,) uint8            its controls on the step (forward/back relative)
    opp_input (T,) uint8           the other side's
    reward   (T,) float32          its reward for the step (damage dealt minus taken)

and OUT/matches.csv a line per side: the replay's id in index.csv (no names: the
files' names, which carry the players', stay in --replays), the side, the opponent,
how it ended and whether it played in sync. A replay with EfzRevival's block says how
many frames the match had: played in sync, ours has the same (less the intro, a constant
measured on the first ones). One without ends in a KO if it played as recorded, or just
stops (a showcase, practice): kept, marked.
"""

import argparse
import collections
import csv
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))

import numpy as np

from efz_env import EfzVecEnv
from efz_env.vec import character_names


def parse():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    p.add_argument('--replays', required=True, help='the folder with index.csv')
    p.add_argument('--out', required=True)
    p.add_argument('--char', default='ayu')
    p.add_argument('--envs', type=int, default=48)
    p.add_argument('--limit', type=int, default=0, help='at most this many replays (0 all)')
    return p.parse_args()


def main():
    args = parse()
    os.makedirs(args.out, exist_ok=True)
    names = character_names()
    char = names.index(args.char)
    rows = [r for r in csv.DictReader(open(os.path.join(args.replays, 'index.csv'),
                                           encoding='utf-8'))
            if r['ok'] == '1' and char in (int(r['c1']), int(r['c2']))]
    if args.limit:
        rows = rows[:args.limit]
    done_path = os.path.join(args.out, 'matches.csv')
    done = set()
    if os.path.exists(done_path):  # continued
        done = {r['id'] for r in csv.DictReader(open(done_path, encoding='utf-8'))}
    rows = [r for r in rows if r['id'] not in done]
    print(f'{len(rows)} replays with {args.char} to play', flush=True)
    fields = ['id', 'side', 'opponent', 'steps', 'frames', 'ended', 'winner', 'extended',
              'revival_frames', 'frame_offset', 'in_sync']
    out_csv = open(done_path, 'a', newline='', encoding='utf-8')
    writer = csv.DictWriter(out_csv, fieldnames=fields)
    if not done:
        writer.writeheader()

    n = min(args.envs, len(rows))
    # Cut at 30 minutes, should a replay never end.
    env = EfzVecEnv(args.data, n, frame_skip=1, max_frames=64 * 60 * 30, rounds_to_win=2,
                    damage_level=2, autoreset='disabled')
    queue = collections.deque(rows)
    current = [None] * n
    bufs = [None] * n

    def start(i, reset=True):
        """Environment i plays the next replay that starts (one that ends within its
        intro doesn't)."""
        while queue:
            r = queue.popleft()
            try:
                env.play(i, os.path.join(args.replays, r['path']))
            except ValueError as e:
                print(f"replay {r['id']}: {e}", flush=True)
                continue
            if reset:
                env.reset(mask=np.arange(n) == i)
            if env.terminated[i] or not env.info['replay'][i]:
                print(f"replay {r['id']}: it doesn't start", flush=True)
                continue
            current[i] = r
            bufs[i] = dict(obs=[env.obs[i].astype(np.float16)], input=[], reward=[])
            return True
        current[i] = None
        return False

    for i in range(n):  # the first, all at once
        r = queue.popleft()
        env.play(i, os.path.join(args.replays, r['path']))
        current[i] = r
    env.reset()
    for i in range(n):
        if env.terminated[i] or not env.info['replay'][i]:
            print(f"replay {current[i]['id']}: it doesn't start", flush=True)
            start(i)
        else:
            bufs[i] = dict(obs=[env.obs[i].astype(np.float16)], input=[], reward=[])
    offsets = collections.Counter()
    t0, steps, finished = time.time(), 0, 0
    idle = np.zeros((n, 2), np.uint8)
    while any(c is not None for c in current):
        obs, reward, term, trunc, info = env.step(idle)
        steps += 1
        ended = term | trunc
        for i in range(n):
            if current[i] is None:
                continue
            b = bufs[i]
            b['input'].append(info['input'][i].copy())
            b['reward'].append(reward[i].copy())
            if not ended[i]:
                b['obs'].append(obs[i].astype(np.float16))
                continue
            r = current[i]
            frames = int(info['frame'][i])
            # The block's own count of the match's frames (none in older versions').
            extended = r['extended'] == '1' and int(r['revival_frames'] or 0) > 0
            offset = int(r['revival_frames']) - frames if extended else ''
            if extended:
                offsets[offset] += 1
            o = np.stack(b['obs'])
            inp = np.stack(b['input'])
            rew = np.stack(b['reward'])
            for side in range(2):
                if int(info['chars'][i][side]) != char:
                    continue
                np.savez(os.path.join(args.out, f"{r['id']}-{side}.npz"), obs=o[:, side],
                         input=inp[:, side], opp_input=inp[:, 1 - side],
                         reward=rew[:, side].astype(np.float32))
                writer.writerow(dict(
                    id=r['id'], side=side, opponent=names[int(info['chars'][i][1 - side])],
                    steps=len(o), frames=frames, ended='ko' if term[i] else 'cut',
                    winner=int(info['winner'][i]), extended=int(extended),
                    revival_frames=r['revival_frames'], frame_offset=offset, in_sync=''))
            finished += 1
            start(i)
        if steps % 20000 == 0:
            out_csv.flush()
            print(f'{finished} replays, {time.time() - t0:.0f}s; offsets {offsets.most_common(3)}',
                  flush=True)
    out_csv.close()
    env.close()
    # In sync: extended replays at the usual offset (the intro EfzRevival counts and we
    # don't), and the others ending in a KO.
    rows = list(csv.DictReader(open(done_path, encoding='utf-8')))
    usual = collections.Counter(r['frame_offset'] for r in rows if r['extended'] == '1')
    usual = usual.most_common(1)[0][0] if usual else None
    for r in rows:
        if r['extended'] == '1':
            r['in_sync'] = int(r['frame_offset'] == usual)
        else:
            r['in_sync'] = int(r['ended'] == 'ko')
    with open(done_path, 'w', newline='', encoding='utf-8') as f:
        w = csv.DictWriter(f, fieldnames=fields)
        w.writeheader()
        w.writerows(rows)
    sync = sum(int(r['in_sync']) for r in rows)
    print(f'{len(rows)} sides in {time.time() - t0:.0f}s: {sync} in sync '
          f'(offset {usual}); offsets {usual and collections.Counter(r["frame_offset"] for r in rows).most_common(5)}')


if __name__ == '__main__':
    main()
