"""How fast efz_env runs from Python, with a policy in the loop.

    python python/examples/bench.py --data /path/to/EFZ [--envs 256] [--steps 1000]
                                    [--policy none|numpy|torch] [--device cuda]

Two loops, each with the same random-weight policy choosing every player's action:

- sync:  step the batch, run the policy on its observations, step again...
- async: two half batches, double-buffered: while one steps (in C++, on the worker
         threads) the policy runs on the other's observations. With the policy on a
         GPU, the simulation and the network overlap; with torch on CUDA the
         observations are written into page-locked memory (EfzVecEnv.pin_memory), so
         their copy to the GPU is a DMA.

The simulation itself is branchy integer C++ that runs on the CPU cores; the GPU is for
the networks.
"""

import argparse
import os
import sys
import time

import numpy as np

sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
from efz_env import ActionTable, EfzVecEnv  # noqa: E402


class NumpyPolicy:
    """A two-layer MLP with random weights, on the CPU."""

    def __init__(self, obs_dim, actions, seed=0):
        r = np.random.default_rng(seed)
        self.w1 = r.standard_normal((obs_dim, 256)).astype(np.float32) * 0.05
        self.w2 = r.standard_normal((256, actions)).astype(np.float32) * 0.05

    def __call__(self, obs):
        h = np.maximum(obs @ self.w1, 0)
        return np.argmax(h @ self.w2, axis=-1)


class TorchPolicy:
    """A three-layer MLP with random weights, on `device`."""

    def __init__(self, obs_dim, actions, device):
        import torch
        self.torch = torch
        self.device = device
        self.net = torch.nn.Sequential(
            torch.nn.Linear(obs_dim, 256), torch.nn.ReLU(), torch.nn.Linear(256, 256),
            torch.nn.ReLU(), torch.nn.Linear(256, actions)).to(device)

    def __call__(self, obs):
        with self.torch.no_grad():
            x = self.torch.from_numpy(obs).to(self.device, non_blocking=True)
            return self.net(x).argmax(-1).cpu().numpy()


def main():
    p = argparse.ArgumentParser(description=__doc__,
                                formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument('--data', default=os.environ.get('EFZ_DATA'))
    p.add_argument('--envs', type=int, default=256)
    p.add_argument('--threads', type=int, default=0)
    p.add_argument('--steps', type=int, default=1000)
    p.add_argument('--frame-skip', type=int, default=1)
    p.add_argument('--chars', help='a pool of characters, e.g. ayu,mai')
    p.add_argument('--policy', default='numpy',
                   help='none, numpy, torch, or sleep:MS (stands for a policy on an '
                        'accelerator: the CPU waits MS milliseconds per batch)')
    p.add_argument('--device', help='torch device (default cuda if there is one)')
    args = p.parse_args()

    table = ActionTable()
    pin = False

    def make(n, seed):
        env = EfzVecEnv(args.data, n, num_threads=args.threads, frame_skip=args.frame_skip,
                        max_frames=64 * 120, seed=seed)
        env.set_matches(char_pool=args.chars.split(',') if args.chars else None)
        if pin:
            import torch
            env.pin_memory(torch)
        return env

    obs_dim = make(1, 0).obs_dim
    if args.policy == 'torch':
        import torch
        device = args.device or ('cuda' if torch.cuda.is_available() else 'cpu')
        policy = TorchPolicy(obs_dim, len(table), device)
        pin = device.startswith('cuda')
    elif args.policy == 'numpy':
        policy = NumpyPolicy(obs_dim, len(table))
    elif args.policy.startswith('sleep:'):
        # MS per 256 environments' observations, as a network's time grows with its
        # batch; waited out on the clock (sleep is too coarse), on this thread only.
        per_row = float(args.policy[6:]) / 1000 / 512

        def policy(obs):
            end = time.perf_counter() + per_row * len(obs)
            while time.perf_counter() < end:
                pass
            return np.zeros(len(obs), dtype=np.int64)
    else:
        policy = None
    rng = np.random.default_rng(0)

    def act(obs):
        n = obs.shape[0]
        if policy is None:
            return table.to_bytes(rng.integers(0, len(table), (n, 2)))
        return table.to_bytes(policy(obs.reshape(n * 2, obs_dim)).reshape(n, 2))

    # Sync: one batch.
    env = make(args.envs, 1)
    obs = env.reset()
    for _ in range(20):
        obs = env.step(act(obs))[0]
    ticks, t = env.ticks, time.perf_counter()
    for _ in range(args.steps):
        obs = env.step(act(obs))[0]
    dt = time.perf_counter() - t
    print(f'sync:  {args.envs * args.steps / dt:9.0f} env steps/s, '
          f'{(env.ticks - ticks) / dt / 1e6:.2f}M ticks/s ({args.envs} envs, '
          f'policy {args.policy})')
    env.close()

    # Async: A steps while the policy runs on B, then B steps while it runs on A.
    half = args.envs // 2
    a, b = make(half, 2), make(half, 3)
    a.reset()
    b.reset()
    a.step_async(act(a.obs))
    t = time.perf_counter()
    for _ in range(args.steps):
        actions_b = act(b.obs)  # while A steps
        a.step_wait()
        b.step_async(actions_b)
        actions_a = act(a.obs)  # while B steps
        b.step_wait()
        a.step_async(actions_a)
    a.step_wait()
    dt = time.perf_counter() - t
    print(f'async: {2 * half * args.steps / dt:9.0f} env steps/s '
          f'(2 x {half} envs, policy {args.policy})')
    a.close()
    b.close()


if __name__ == '__main__':
    main()
