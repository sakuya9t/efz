"""A run's checkpoints averaged: the mean of their policies' weights (docs/training-v2.md:
rounds 8-13 wandered around a point and best.zip was the luckiest chunk; the mean of
agent-league11-r7's ten chunks wins 90% over the 39 where its best.zip wins 86%).

    python runs/human-ayu/average.py runs/human-ayu/agent-league11-r7 --out runs/human-ayu/agent-league11-avg
    python runs/human-ayu/average.py RUN --chunks 4-7 --out OUT

Writes OUT/model.zip (the last chunk's file with the mean weights: its optimiser's state
and step count are the last chunk's) and OUT/config.json (RUN's). The policies must be of
one architecture; integer entries (none in EfzPolicy) are taken from the last chunk.
"""

import argparse
import glob
import json
import os
import re
import shutil
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(HERE)), 'python'))


def chunks_of(run, spec=None):
    """RUN's chunkNNN.zip paths, all of them or those of spec ('4-7', '1,3,5')."""
    have = sorted(glob.glob(os.path.join(run, 'chunk[0-9][0-9][0-9].zip')))
    if not spec:
        return have
    want = set()
    for part in spec.split(','):
        lo, _, hi = part.partition('-')
        want.update(range(int(lo), int(hi or lo) + 1))
    return [p for p in have if int(re.findall(r'\d+', os.path.basename(p))[0]) in want]


def mean_state(states):
    import torch
    return {k: (torch.stack([s[k].float() for s in states]).mean(0).to(v.dtype)
                if v.is_floating_point() else states[-1][k])
            for k, v in states[0].items()}


def average(paths, out_path):
    """The mean of the policies of `paths` (SB3 model zips), saved at out_path."""
    from stable_baselines3 import PPO
    models = [PPO.load(p, device='cpu') for p in paths]
    states = [{k: v.clone() for k, v in m.policy.state_dict().items()} for m in models]
    base = models[-1]
    base.policy.load_state_dict(mean_state(states))
    base.save(out_path)
    return len(models)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    p.add_argument('run', help="a finetune.py run's folder (its chunkNNN.zip, config.json)")
    p.add_argument('--chunks', help="which chunks ('4-7', '1,3,5'; default: all)")
    p.add_argument('--out', required=True)
    args = p.parse_args()
    paths = chunks_of(args.run, args.chunks)
    if not paths:
        sys.exit(f'no chunkNNN.zip in {args.run}' + (f' for {args.chunks}' if args.chunks else ''))
    os.makedirs(args.out, exist_ok=True)
    n = average(paths, os.path.join(args.out, 'model.zip'))
    shutil.copyfile(os.path.join(args.run, 'config.json'), os.path.join(args.out, 'config.json'))
    with open(os.path.join(args.out, 'average.json'), 'w') as f:
        json.dump(dict(run=os.path.relpath(args.run, os.path.dirname(os.path.dirname(HERE))),
                       chunks=[os.path.basename(x) for x in paths]), f, indent=1)
    print(f'{args.out}/model.zip: the mean of {n} chunks of {args.run}')


if __name__ == '__main__':
    main()
