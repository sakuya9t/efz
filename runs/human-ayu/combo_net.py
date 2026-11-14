"""The agent's combos learnt apart from its own network: the built-in routes
(combo_support's FairAssist: people's library combos, tried on copies of the game once the
agent sees its hit, the best played) without the copies. The agent's network isn't
trained and plays everything else as before, so what the routes do (jump cancels, long
strings) can't spread to its neutral, as it did the three times routes were trained into
the one network (rounds 5, 7, 8).

    python runs/human-ayu/combo_net.py collect --agent AGENT.zip --library LIBRARY.npz \
        --p2 OPPONENT.zip --chars ayu kano [--p2-advantage SPEC] --seed 102 --plans-only \
        --out DATA/kano.npz
    python runs/human-ayu/combo_net.py train-chooser --agent AGENT.zip --data DATA \
        --out combo-chooser
    python runs/human-ayu/evaluate.py --p1 AGENT.zip --p1-assist LIBRARY.npz \
        --assist-chooser combo-chooser/chooser.pt ...
    python python/examples/play.py --agent AGENT.zip --assist LIBRARY.npz \
        --chooser combo-chooser/chooser.pt

**The chooser** (what works: README, "Round 15"). collect: the agent with the routes
plays matches (evaluate.py's, with another seed than its evaluations'); every plan is
kept: the agent's view on the step it sees its hit (the game as it saw it, its own last
inputs), the library combos tried from there, what each dealt on its copy and what its
own play dealt. train-chooser: a network (the agent's features, copied and trained on)
learns from that view what each of the library's combos would deal and what its own play
would; --data may hold other agents' files too (what a combo deals is the game's; only
the agent's own files teach its own play). Matches are held out to measure it: what its
choices dealt, as the planner measured them, beside the planner's choices and its own
play always. NetPlanner then stands where the planner did: the most promising combo is
played from memory (the recording, as the planner's is), if it promises more than its own
play by a margin. No copies of the game, no second process.

**Two networks that play the combo step by step** (what doesn't: kept for the
measurements). collect without --plans-only keeps every step on which the agent sees its
combo running (its combo counter above 0 in its view, `delay` steps late): its view, the
action played, whether a route played it, its own probabilities. `train`: a copy of the
agent's network learns the route's action where a route played (cross-entropy) and its
own probabilities elsewhere (KL); played by evaluate.py --p1-combo. `train-clock`: a
network that adds to the agent's own log-probabilities, from its view, the count of steps
since it saw the combo and the actions it played on them; played by `play --combo`. Both
choose a route without knowing whether it connects from here, and miss its timing.
"""

import argparse
import glob
import json
import os
import sys
import time

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, 'python'))
sys.path.insert(0, HERE)

import numpy as np

FRAME, INTRO, ROUND_OVER, COMBO_HITS, OPP_CHARACTER = 0, 2, 3, 30, 66  # efz_env's observation


def load_routes(path):
    """macros.load_library's combos, each with its place in the list as 'index' (the
    chooser's name for it: the library's ids aren't one a combo)."""
    import macros
    library = macros.load_library(path)
    for k, m in enumerate(library):
        m['index'] = k
    return library


def collect(args):
    import torch
    import advantages
    import combo_support
    import evaluate as ev
    import redteam

    class Recorder(combo_support.FairComboAgent):
        """FairComboAgent, keeping the steps on which the agent sees its combo running
        (rounds being played: not their intros, their ends, or a match that is over)."""

        def __init__(self, agent, planner):
            super().__init__(agent, planner)
            self.kept = dict(view=[], action=[], route=[], probs=[], match=[], step=[])
            self.tried = dict(view=[], match=[], routes=[], dealt=[], own=[])
            self.routed = {}
            inner = self.assist.action

            def action(i, hits):  # (which steps a route played)
                self.routed[i] = inner(i, hits)
                return self.routed[i]
            self.assist.action = action
            update = self.assist.update

            def updated(i, seen_view, now_view, save, seen, hist, *rest):
                made = len(self.assist.plans)
                update(i, seen_view, now_view, save, seen, hist, *rest)
                if len(self.assist.plans) > made:  # a plan: the view it was made on, its options
                    last, k = planner.last, self.tried
                    routes = np.full(planner.per_start, -1, np.int16)
                    dealt = np.zeros(planner.per_start, np.float32)
                    n = len(last['picked'])
                    routes[:n] = [m['index'] for m in last['picked']]
                    dealt[:n] = last['dealt'][:n]
                    k['view'].append(np.concatenate([seen_view, hist.reshape(-1)])
                                     [:self.agent.width].astype(np.float32))
                    k['match'].append(i)
                    k['routes'].append(routes)
                    k['dealt'].append(dealt)
                    k['own'].append(float(last['dealt'][n]))
            self.assist.update = updated
            self.frame = None

        def controls(self, obs, step):
            out = super().controls(obs, step)
            a = self.agent
            seen = a.seen.buf[:, a.delay]
            live = (obs[:, INTRO] == 0) & (obs[:, ROUND_OVER] == 0)
            if self.frame is not None:
                live &= obs[:, FRAME] != self.frame  # (an ended match's game stands still)
            self.frame = obs[:, FRAME].copy()
            on = np.flatnonzero((np.round(seen[:, COMBO_HITS] * 30) > 0) & live)
            if len(on) and not args.plans_only:
                view = np.concatenate([seen[on], a.hist.features()[on]], 1)[:, :a.width]
                route = np.array([self.routed.get(int(i)) is not None for i in on])
                action = np.array([self.routed[int(i)] if r else a.last[i]
                                   for i, r in zip(on, route)], np.int16)
                with torch.no_grad():
                    probs = a.model.policy.logits(torch.as_tensor(view)).exp().numpy()
                k = self.kept
                k['view'].append(view.astype(np.float32))
                k['action'].append(action)
                k['route'].append(route)
                k['probs'].append(probs.astype(np.float16))
                k['match'].append(on.astype(np.int16))
                k['step'].append(np.full(len(on), step, np.int32))
            return out

    agent = ev.make_agent(args.agent)
    planner = redteam.Planner(args.data, load_routes(args.library), agent.model)
    p1 = Recorder(agent, planner)
    p2 = 'cpu' if args.p2 == 'cpu' else ev.make_agent(args.p2)
    if args.p2_advantage:
        p2 = advantages.AdvantagedAgent(p2, args.chars[1], advantages.parse(args.p2_advantage),
                                        learner=args.chars[0])
    t0 = time.time()
    r = ev.play(args, p1, p2, args.matches, args.level, seed=args.seed)
    k = {name: np.concatenate(v) if v else np.zeros(0) for name, v in p1.kept.items()}
    k.update({'plan_' + name: np.array(v) for name, v in p1.tried.items()})
    plans = p1.assist.take_plans()
    os.makedirs(os.path.dirname(os.path.abspath(args.out)), exist_ok=True)
    np.savez_compressed(args.out, **k, meta=json.dumps(dict(
        agent=args.agent, p2=args.p2, chars=list(args.chars), advantage=args.p2_advantage,
        seed=args.seed, matches=args.matches, win=r['win'], plans=plans,
        library=args.library, routes=len(planner.library))))
    print(f"{args.out}: {len(k['action'])} steps, {int(k['route'].sum())} a route's, "
          f"{plans.get('plans', 0)} plans (a route in {plans.get('route', 0):.0%}), "
          f"won {r['win']:.0%}, {time.time() - t0:.0f}s", flush=True)


def load(paths):
    """The shards as one set, each step's match numbered over all of them."""
    out, base = {}, 0
    for p in paths:
        z = np.load(p)
        for name in ('view', 'action', 'route', 'probs', 'step'):
            out.setdefault(name, []).append(z[name])
        out.setdefault('match', []).append(z['match'].astype(np.int64) + base)
        base += int(json.loads(str(z['meta']))['matches'])
    return {name: np.concatenate(v) for name, v in out.items()}


def train(args):
    import shutil
    import torch
    from stable_baselines3 import PPO
    from efz_env.agent import load_config
    torch.manual_seed(args.seed)
    torch.set_num_threads(args.torch_threads)
    paths = sorted(glob.glob(os.path.join(args.data, '*.npz')))
    d = load(paths)
    n = len(d['action'])
    held = (d['match'] % args.hold) == 0  # whole matches held out
    print(f"{len(paths)} files, {n} steps ({d['route'].mean():.0%} a route's), "
          f"{held.mean():.0%} held out", flush=True)
    model = PPO.load(args.agent, device='cpu')
    policy = model.policy
    policy.set_training_mode(False)  # (no dropout or batch norm in it: its mode is all one)
    actor = [p for name, p in policy.named_parameters()
             if not name.startswith(('vf_features_extractor', 'mlp_extractor.value_net',
                                     'value_net'))]
    opt = torch.optim.Adam(actor, lr=args.lr)
    T = {k: torch.as_tensor(v) for k, v in
         dict(view=d['view'], action=d['action'].astype(np.int64), route=d['route'],
              probs=d['probs'].astype(np.float32)).items()}
    tr, te = torch.as_tensor(np.flatnonzero(~held)), torch.as_tensor(np.flatnonzero(held))
    device = torch.device(args.device)
    policy.to(device)

    def loss_of(idx):
        logp = policy.logits(T['view'][idx].to(device))
        route = T['route'][idx].to(device)
        ce = torch.nn.functional.nll_loss(logp, T['action'][idx].to(device), reduction='none')
        own = T['probs'][idx].to(device).clamp_min(1e-6)
        own = own / own.sum(1, keepdim=True)
        kl = (own * (own.log() - logp)).sum(1)
        return torch.where(route, ce * args.route_weight, kl), logp, route

    def measure(idx):
        out = dict(loss=0.0, n=0, route_n=0, route_hit=0, route_p=0.0, kl=0.0, own_n=0)
        with torch.no_grad():
            for i in range(0, len(idx), 65536):
                b = idx[i:i + 65536]
                loss, logp, route = loss_of(b)
                act = T['action'][b].to(device)
                out['loss'] += float(loss.sum())
                out['n'] += len(b)
                out['route_n'] += int(route.sum())
                out['route_hit'] += int((logp.argmax(1) == act)[route].sum())
                out['route_p'] += float(logp.gather(1, act[:, None])[:, 0].exp()[route].sum())
                out['kl'] += float(loss[~route].sum())
                out['own_n'] += int((~route).sum())
        return dict(loss=out['loss'] / max(1, out['n']),
                    route_top1=out['route_hit'] / max(1, out['route_n']),
                    route_prob=out['route_p'] / max(1, out['route_n']),
                    own_kl=out['kl'] / max(1, out['own_n']))

    history = [dict(epoch=0, train=measure(tr[:200000]), held=measure(te))]
    print('before:', json.dumps(history[0]), flush=True)
    steps = args.epochs * (len(tr) // args.batch)
    sched = torch.optim.lr_scheduler.OneCycleLR(opt, max_lr=args.lr, total_steps=max(1, steps),
                                                pct_start=0.05)
    t0 = time.time()
    for epoch in range(1, args.epochs + 1):
        perm = tr[torch.randperm(len(tr))]
        for i in range(0, len(perm) - args.batch + 1, args.batch):
            loss, _, _ = loss_of(perm[i:i + args.batch])
            opt.zero_grad()
            loss.mean().backward()
            torch.nn.utils.clip_grad_norm_(actor, 1.0)
            opt.step()
            sched.step()
        history.append(dict(epoch=epoch, train=measure(tr[:200000]), held=measure(te),
                            seconds=round(time.time() - t0)))
        print(f'epoch {epoch}:', json.dumps(history[-1]), flush=True)
    policy.to('cpu')
    os.makedirs(args.out, exist_ok=True)
    model.save(os.path.join(args.out, 'combo.zip'))
    cfg = dict(load_config(args.agent), combo_net=dict(
        agent=args.agent, data=args.data, files=len(paths), steps=int(n),
        route_share=float(d['route'].mean()), epochs=args.epochs, lr=args.lr,
        route_weight=args.route_weight, seed=args.seed))
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(cfg, f, indent=1)
    with open(os.path.join(args.out, 'combo_net.json'), 'w') as f:
        json.dump(dict(args=vars(args), history=history), f, indent=1)
    print('saved', os.path.join(args.out, 'combo.zip'), flush=True)


PAD = 45  # in a step's memory of actions: before the combo was seen


def clock_memory(match, step, action, memory):
    """For steps sorted by (match, step): each step's place in its run of consecutive
    steps (the clock: 0 on the step the combo is first seen), and the run's actions before
    it, the most recent first (PAD before the run)."""
    n = len(step)
    new = np.r_[True, (match[1:] != match[:-1]) | (step[1:] != step[:-1] + 1)]
    t = np.arange(n) - np.maximum.accumulate(np.where(new, np.arange(n), 0))
    mem = np.full((n, memory), PAD, np.int8)
    for k in range(1, memory + 1):
        ok = np.flatnonzero(t >= k)
        mem[ok, k - 1] = action[ok - k]
    return t, mem


def route_net(spec):
    import torch
    from torch import nn

    class RouteNet(nn.Module):
        """The agent's own log-probabilities of the actions, plus what this network adds
        to them from the agent's view, the clock and the memory of the combo's actions
        (nothing, before it is trained)."""

        def __init__(self, width, actions=45, memory=64, clock=1024, hidden=768):
            super().__init__()
            self.clock = clock
            self.acts = nn.Embedding(actions + 1, 8)
            self.time = nn.Embedding(clock, 32)
            layers, n = [], width + actions + memory * 8 + 32
            for _ in range(3):
                layers += [nn.Linear(n, hidden), nn.ReLU()]
                n = hidden
            self.body = nn.Sequential(*layers)
            self.out = nn.Linear(hidden, actions)
            nn.init.zeros_(self.out.weight)
            nn.init.zeros_(self.out.bias)

        def forward(self, view, own, mem, t):
            own = own.clamp_min(-10.0)
            x = torch.cat([view, own, self.acts(mem.long()).flatten(1),
                           self.time(t.clamp(max=self.clock - 1))], 1)
            return torch.log_softmax(own + self.out(self.body(x)), 1)

    return RouteNet(**spec)


def train_clock(args):
    import torch
    from stable_baselines3 import PPO
    from efz_env.agent import load_config
    torch.manual_seed(args.seed)
    torch.set_num_threads(args.torch_threads)
    paths = sorted(glob.glob(os.path.join(args.data, '*.npz')))
    d = load(paths)
    order = np.lexsort((d['step'], d['match']))
    d = {k: v[order] for k, v in d.items()}
    n = len(d['action'])
    t, mem = clock_memory(d['match'], d['step'], d['action'], args.memory)
    first = d['route'] & ~np.r_[False, d['route'][:-1] & (t[1:] > 0)]  # a route's first step
    run = np.cumsum(first) * d['route']                               # its number (0: none)
    change = d['route'] & (first | np.r_[True, d['action'][1:] != d['action'][:-1]])
    held = (d['match'] % args.hold) == 0  # whole matches held out
    print(f"{len(paths)} files, {n} steps ({d['route'].mean():.0%} a route's, "
          f"{int(first.sum())} routes), {held.mean():.0%} held out", flush=True)
    own_policy = PPO.load(args.agent, device='cpu').policy
    own_policy.set_training_mode(False)
    view = torch.as_tensor(d['view'])
    own = torch.empty((n, own_policy.action_space.n))
    with torch.no_grad():
        for i in range(0, n, 65536):
            own[i:i + 65536] = own_policy.logits(view[i:i + 65536])
    spec = dict(width=view.shape[1], actions=own.shape[1], memory=args.memory,
                hidden=args.hidden)
    net = route_net(spec)
    T = dict(view=view, own=own, mem=torch.as_tensor(mem), t=torch.as_tensor(t),
             action=torch.as_tensor(d['action'].astype(np.int64)),
             route=torch.as_tensor(d['route']))
    tr, te = torch.as_tensor(np.flatnonzero(~held)), torch.as_tensor(np.flatnonzero(held))
    opt = torch.optim.Adam(net.parameters(), lr=args.lr)

    def loss_of(idx):
        own = T['own'][idx]
        logp = net(T['view'][idx], own, T['mem'][idx], T['t'][idx])
        ce = torch.nn.functional.nll_loss(logp, T['action'][idx], reduction='none')
        kl = (own.exp() * (own - logp)).sum(1)
        return torch.where(T['route'][idx], ce * args.route_weight, kl), logp

    def measure(idx):
        """Over idx: how often the network's likeliest action is the route's (on all of a
        route's steps, on its first, on the steps it changes its action), the share of
        routes with every step right, and its distance from the agent's own play on the
        steps no route played."""
        right = np.zeros(n, bool)
        kl = 0.0
        with torch.no_grad():
            for i in range(0, len(idx), 65536):
                b = idx[i:i + 65536]
                loss, logp = loss_of(b)
                right[b.numpy()] = (logp.argmax(1) == T['action'][b]).numpy()
                kl += float(loss[~T['route'][b]].sum())
        on = np.zeros(n, bool)
        on[idx.numpy()] = True
        r = on & d['route']
        runs = np.unique(run[r])
        wrong = np.unique(run[r & ~right])
        return dict(route_top1=float(right[r].mean()), first=float(right[on & first].mean()),
                    changes=float(right[on & change].mean()),
                    held_action=float(right[r & ~change].mean()),
                    routes_whole=1 - len(wrong) / max(1, len(runs)),
                    own_kl=kl / max(1, int((on & ~d['route']).sum())))

    history = [dict(epoch=0, held=measure(te))]
    print('before:', json.dumps(history[0]), flush=True)
    steps = args.epochs * (len(tr) // args.batch)
    sched = torch.optim.lr_scheduler.OneCycleLR(opt, max_lr=args.lr, total_steps=max(1, steps),
                                                pct_start=0.05)
    t0 = time.time()
    for epoch in range(1, args.epochs + 1):
        perm = tr[torch.randperm(len(tr))]
        for i in range(0, len(perm) - args.batch + 1, args.batch):
            loss, _ = loss_of(perm[i:i + args.batch])
            opt.zero_grad()
            loss.mean().backward()
            torch.nn.utils.clip_grad_norm_(net.parameters(), 1.0)
            opt.step()
            sched.step()
        history.append(dict(epoch=epoch, held=measure(te), seconds=round(time.time() - t0)))
        print(f'epoch {epoch}:', json.dumps(history[-1]), flush=True)
    os.makedirs(args.out, exist_ok=True)
    torch.save(dict(spec=spec, state=net.state_dict()), os.path.join(args.out, 'combo.pt'))
    cfg = dict(load_config(args.agent), combo_net=dict(
        agent=args.agent, data=args.data, files=len(paths), steps=int(n),
        route_share=float(d['route'].mean()), epochs=args.epochs, lr=args.lr,
        route_weight=args.route_weight, seed=args.seed, **spec))
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(cfg, f, indent=1)
    with open(os.path.join(args.out, 'combo_net.json'), 'w') as f:
        json.dump(dict(args=vars(args), history=history), f, indent=1)
    print('saved', os.path.join(args.out, 'combo.pt'), flush=True)


def chooser_net(extractor, routes, hidden=512):
    from torch import nn

    class Chooser(nn.Module):
        """From the agent's view on the step it sees its hit: what each library combo
        would deal from there and (the last output) what its own play would, in 1000s of
        HP. Its features are a copy of the agent's (its embeddings of moves and
        characters), trained on."""

        def __init__(self):
            super().__init__()
            self.features = extractor
            self.head = nn.Sequential(nn.Linear(extractor.features_dim, hidden), nn.ReLU(),
                                      nn.Linear(hidden, hidden), nn.ReLU(),
                                      nn.Linear(hidden, routes + 1))

        def forward(self, view):
            return self.head(self.features(view))

    return Chooser()


def load_plans(paths, agent):
    """The files' plans as one set. mine: the plans of `agent`'s matches (what a combo
    deals is the game's; what its own play would have dealt is the agent's)."""
    out, base = {}, 0
    for p in paths:
        z = np.load(p)
        if 'plan_view' not in z.files or not len(z['plan_view']):
            continue
        for name in ('view', 'routes', 'dealt', 'own'):
            out.setdefault(name, []).append(z['plan_' + name])
        out.setdefault('match', []).append(z['plan_match'].astype(np.int64) + base)
        meta = json.loads(str(z['meta']))
        out.setdefault('count', []).append(np.full(len(z['plan_own']), meta['routes']))
        out.setdefault('mine', []).append(np.full(
            len(z['plan_own']), os.path.abspath(meta['agent']) == os.path.abspath(agent)))
        base += int(meta['matches'])
    return {name: np.concatenate(v) for name, v in out.items()}


def train_chooser(args):
    import copy
    import torch
    from stable_baselines3 import PPO
    from efz_env.agent import load_config
    torch.manual_seed(args.seed)
    torch.set_num_threads(args.torch_threads)
    paths = sorted(p for folder in args.data for p in glob.glob(os.path.join(folder, '*.npz')))
    d = load_plans(paths, args.agent)
    n = len(d['own'])
    if not d['mine'].any():
        sys.exit(f'no plans of {args.agent} in {args.data}')
    routes = int(d['count'][0])
    if (d['count'] != routes).any():
        sys.exit('the files are of different libraries')
    held = (d['match'] % args.hold) == 0  # whole matches held out
    valid = d['routes'] >= 0
    best = np.where(valid, d['dealt'], -1).max(1)
    print(f"{len(paths)} files, {n} plans ({int(d['mine'].sum())} the agent's), {routes} "
          f"combos in the library, a route better than its own play in "
          f"{(best > d['own']).mean():.0%}, {held.mean():.0%} held out", flush=True)
    policy = PPO.load(args.agent, device='cpu').policy
    net = chooser_net(copy.deepcopy(policy.pi_features_extractor), routes, args.hidden)
    T = dict(view=torch.as_tensor(d['view']),
             routes=torch.as_tensor(np.where(valid, d['routes'], 0).astype(np.int64)),
             valid=torch.as_tensor(valid),
             dealt=torch.as_tensor(d['dealt'] / 1000), own=torch.as_tensor(d['own'] / 1000).float(),
             mine=torch.as_tensor(d['mine']))
    tr = torch.as_tensor(np.flatnonzero(~held))
    te = torch.as_tensor(np.flatnonzero(held & d['mine']))  # (measured on the agent's own)
    opt = torch.optim.AdamW(net.parameters(), lr=args.lr, weight_decay=args.weight_decay)

    def predict(idx):
        out = net(T['view'][idx])
        return out.gather(1, T['routes'][idx]), out[:, -1]

    def loss_of(idx):
        pred, own = predict(idx)
        huber = torch.nn.functional.smooth_l1_loss
        valid, mine = T['valid'][idx], T['mine'][idx]
        k = valid.float().mean() * valid.shape[1]  # (combos a plan: each weighs as its own play)
        mine_loss = huber(own[mine], T['own'][idx][mine]) if mine.any() else 0.0
        return (huber(pred[valid], T['dealt'][idx][valid]) * k + mine_loss) / (1 + k)

    def measure(idx, margin=0.0):
        """Over idx: what the chooser's choice dealt (as the planner measured it) beside
        the planner's choice and its own play always, how often it takes a route, and how
        often the route it takes dealt less than its own play would have."""
        with torch.no_grad():
            pred, own = predict(idx)
            pred = torch.where(T['valid'][idx], pred, torch.full_like(pred, -1e9))
            pick = pred.argmax(1)
            take = pred.max(1).values > own + margin
            got = torch.where(take, T['dealt'][idx].gather(1, pick[:, None])[:, 0], T['own'][idx])
            dealt = torch.where(T['valid'][idx], T['dealt'][idx], torch.full_like(pred, -1.0))
            top = torch.maximum(dealt.max(1).values, T['own'][idx])
            err = (torch.where(T['valid'][idx], (pred - T['dealt'][idx]).abs(),
                               torch.zeros_like(pred)).sum() / T['valid'][idx].sum())
        return dict(chooser=round(float(got.mean()) * 1000), planner=round(float(top.mean()) * 1000),
                    own=round(float(T['own'][idx].mean()) * 1000),
                    takes_route=round(float(take.float().mean()), 3),
                    planner_takes=round(float((dealt.max(1).values > T['own'][idx]).float().mean()), 3),
                    worse_than_own=round(float((take & (got < T['own'][idx])).float().mean()), 3),
                    error=round(float(err) * 1000))

    history = [dict(epoch=0, held=measure(te))]
    print('before:', json.dumps(history[0]), flush=True)
    steps = args.epochs * max(1, len(tr) // args.batch)
    sched = torch.optim.lr_scheduler.OneCycleLR(opt, max_lr=args.lr, total_steps=steps,
                                                pct_start=0.1)
    for epoch in range(1, args.epochs + 1):
        perm = tr[torch.randperm(len(tr))]
        for i in range(0, len(perm) - args.batch + 1, args.batch):
            loss = loss_of(perm[i:i + args.batch])
            opt.zero_grad()
            loss.backward()
            opt.step()
            sched.step()
        if epoch % max(1, args.epochs // 10) == 0 or epoch == args.epochs:
            history.append(dict(epoch=epoch, train=measure(tr[:20000]), held=measure(te)))
            print(f'epoch {epoch}:', json.dumps(history[-1]), flush=True)
    margins = {m: measure(te, m / 1000) for m in (0, 100, 200, 300, 500)}
    print('held out, by the margin a route must promise over its own play:')
    for m, r in margins.items():
        print(f'  {m}: {json.dumps(r)}', flush=True)
    os.makedirs(args.out, exist_ok=True)
    meta = json.loads(str(np.load(paths[0])['meta']))
    torch.save(dict(routes=routes, hidden=args.hidden, state=net.state_dict(),
                    library=meta.get('library')), os.path.join(args.out, 'chooser.pt'))
    cfg = dict(load_config(args.agent), combo_net=dict(
        agent=args.agent, data=args.data, files=len(paths), plans=int(n), routes=routes,
        library=meta.get('library'), epochs=args.epochs, lr=args.lr, seed=args.seed))
    with open(os.path.join(args.out, 'config.json'), 'w') as f:
        json.dump(cfg, f, indent=1)
    with open(os.path.join(args.out, 'combo_net.json'), 'w') as f:
        json.dump(dict(args=vars(args), history=history, margins=margins), f, indent=1)
    print('saved', os.path.join(args.out, 'chooser.pt'), flush=True)


class NetPlanner:
    """redteam.Planner's place in combo_support's FairAssist (and so FairComboAgent's),
    with no copies of the game: train_chooser's network says from the agent's view what
    each library combo would deal and what its own play would, and the most promising
    combo is played from memory, as the planner's is, if it promises more than its own
    play by `margin` HP."""
    score = 'damage'
    changed = 0

    def __init__(self, library, model, path, per_start=12, margin=200.0):
        import copy
        import torch
        from efz_env.vec import character_names
        saved = torch.load(path, map_location='cpu', weights_only=False)
        if saved['routes'] != len(library):
            raise ValueError(f"{path} is of a library of {saved['routes']} combos, not "
                             f"{len(library)}")
        self.net = chooser_net(copy.deepcopy(model.policy.pi_features_extractor),
                               saved['routes'], saved['hidden'])
        self.net.load_state_dict(saved['state'])
        self.net.eval()
        self.library, self.per_start, self.margin = library, per_start, margin
        self.width = model.observation_space.shape[0]
        self.by_starter = {}
        for m in library:
            self.by_starter.setdefault(m['starter'], []).append(m)
        self.by_victim = any(m.get('kept_for') == 'victim' for m in library)
        self.names = character_names()

    def plans_against(self, view):
        return True

    def plan(self, state, side, starter, hist, prev, offset=0, seen=None, policy=None,
             value=None):
        import torch
        import redteam
        view = np.concatenate([seen[-1], np.asarray(hist).reshape(-1)])[:self.width]
        victim = (self.names[int(round(float(view[OPP_CHARACTER])))] if self.by_victim
                  else None)
        picked = redteam.route_pool(self.by_starter, starter, victim, offset, self.per_start)
        with torch.no_grad():
            out = self.net(torch.as_tensor(view[None].astype(np.float32)))[0].numpy() * 1000
        own = float(out[-1])
        if not picked:
            return None, own, own
        pred = out[[m['index'] for m in picked]]
        best = int(pred.argmax())
        chosen = picked[best]['actions'][offset:] if pred[best] > own + self.margin else None
        return chosen, float(max(pred[best], own)), own


class NetCombo:
    """An efz_env Agent (evaluate.py's players) whose combos train_clock's network plays:
    on every step the agent sees its own combo running, the network's action (drawn from
    its probabilities, or the likeliest), from the agent's view, the count of such steps
    so far and the actions played on them. Everything else is the agent's own play."""

    def __init__(self, agent, path, deterministic=False, temperature=1.0):
        import torch
        from efz_env import ActionTable
        saved = torch.load(path, map_location='cpu', weights_only=False)
        self.net = route_net(saved['spec'])
        self.net.load_state_dict(saved['state'])
        self.net.eval()
        self.memory = saved['spec']['memory']
        self.agent, self.deterministic, self.temperature = agent, deterministic, temperature
        self.frame_skip, self.history = 1, agent.history
        self.table = ActionTable()
        self.frame = None
        self.steps = self.played = 0

    def _clear(self, n=None, mask=None):
        if n is not None:
            self.t = np.zeros(n, np.int64)
            self.mem = np.full((n, self.memory), PAD, np.int64)
        else:
            self.t[mask] = 0
            self.mem[mask] = PAD

    def batch(self, n):
        self.agent.batch(n)
        self._clear(n)
        self.frame = None

    def reset(self, mask=None):
        self.agent.reset(mask)
        self._clear(mask=slice(None) if mask is None else np.asarray(mask, bool))

    def controls(self, obs, step):
        import torch
        a = self.agent
        out = a.controls(obs, step).copy()  # (it pushes obs into its view)
        seen = a.seen.buf[:, a.delay]
        live = (obs[:, INTRO] == 0) & (obs[:, ROUND_OVER] == 0)
        if self.frame is not None:
            live &= obs[:, FRAME] != self.frame
        self.frame = obs[:, FRAME].copy()
        gate = (np.round(seen[:, COMBO_HITS] * 30) > 0) & live
        self._clear(mask=~gate)
        on = np.flatnonzero(gate)
        self.steps += len(gate)
        self.played += len(on)
        if len(on):
            view = torch.as_tensor(np.concatenate([seen[on], a.hist.features()[on]], 1)
                                   [:, :a.width].astype(np.float32))
            with torch.no_grad():
                logp = self.net(view, a.model.policy.logits(view),
                                torch.as_tensor(self.mem[on]), torch.as_tensor(self.t[on]))
                if self.deterministic:
                    act = logp.argmax(1).numpy()
                else:
                    act = torch.distributions.Categorical(
                        logits=logp / self.temperature).sample().numpy()
            out[on] = self.table.table[act]
            self.mem[on, 1:] = self.mem[on, :-1]
            self.mem[on, 0] = act
            self.t[on] += 1
        return out

    def observe(self, controls):
        self.agent.observe(controls)


def play(args):
    import advantages
    import evaluate as ev
    agent = ev.make_agent(args.agent)
    if args.chooser:
        import combo_support
        p1 = combo_support.FairComboAgent(agent, NetPlanner(
            load_routes(args.library), agent.model, args.chooser, margin=args.margin))
    else:
        p1 = NetCombo(agent, args.combo, args.deterministic, args.temperature)
    p2 = 'cpu' if args.p2 == 'cpu' else ev.make_agent(args.p2)
    if args.p2_advantage:
        p2 = advantages.AdvantagedAgent(p2, args.chars[1], advantages.parse(args.p2_advantage),
                                        learner=args.chars[0])
    r = ev.play(args, p1, p2, args.matches, args.level, seed=args.seed)
    if args.chooser:
        how = dict(net=args.chooser, margin=args.margin, **p1.assist.take_plans())
    else:
        how = dict(net=args.combo, deterministic=args.deterministic,
                   temperature=args.temperature,
                   steps_played=round(p1.played / max(1, p1.steps), 4))
    out = {'cpu%d' % args.level if p2 == 'cpu' else 'vs': r, 'combo': how}
    print(json.dumps({k: v for k, v in r.items()
                      if k not in ('by_opponent', 'hp_by_opponent', 'sides', 'by_tier')}),
          json.dumps(out['combo']), flush=True)
    if args.json:
        with open(args.json, 'w') as f:
            json.dump(out, f, indent=1)


def main():
    p = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = p.add_subparsers(dest='cmd', required=True)
    c = sub.add_parser('collect')
    c.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    c.add_argument('--agent', required=True)
    c.add_argument('--library', required=True, help="combo_library.py's")
    c.add_argument('--p2', default='cpu')
    c.add_argument('--chars', nargs=2, default=('ayu', 'random'))
    c.add_argument('--p2-advantage')
    c.add_argument('--level', type=int, default=4)
    c.add_argument('--matches', type=int, default=64)
    c.add_argument('--minutes', type=float, default=5)
    c.add_argument('--seed', type=int, default=101, help="not evaluate.py's 7")
    c.add_argument('--out', required=True)
    c.add_argument('--plans-only', action='store_true',
                   help="keep the plans (train-chooser's), not the steps")
    t = sub.add_parser('train')
    t.add_argument('--agent', required=True)
    t.add_argument('--data', required=True, help="the folder of collect's files")
    t.add_argument('--out', required=True)
    t.add_argument('--epochs', type=int, default=30)
    t.add_argument('--batch', type=int, default=4096)
    t.add_argument('--lr', type=float, default=3e-4)
    t.add_argument('--route-weight', type=float, default=1.0)
    t.add_argument('--hold', type=int, default=10, help='one match in this many held out')
    t.add_argument('--seed', type=int, default=0)
    t.add_argument('--device', default='cpu')
    t.add_argument('--torch-threads', type=int, default=8)
    k = sub.add_parser('train-clock')
    k.add_argument('--agent', required=True)
    k.add_argument('--data', required=True, help="the folder of collect's files")
    k.add_argument('--out', required=True)
    k.add_argument('--epochs', type=int, default=8)
    k.add_argument('--batch', type=int, default=4096)
    k.add_argument('--lr', type=float, default=1e-3)
    k.add_argument('--route-weight', type=float, default=1.0)
    k.add_argument('--memory', type=int, default=64, help='the actions of the combo kept')
    k.add_argument('--hidden', type=int, default=768)
    k.add_argument('--hold', type=int, default=10, help='one match in this many held out')
    k.add_argument('--seed', type=int, default=0)
    k.add_argument('--torch-threads', type=int, default=8)
    h = sub.add_parser('train-chooser')
    h.add_argument('--agent', required=True)
    h.add_argument('--data', required=True, nargs='+',
                   help="folders of collect's files; other agents' count for the combos only")
    h.add_argument('--out', required=True)
    h.add_argument('--epochs', type=int, default=60)
    h.add_argument('--batch', type=int, default=512)
    h.add_argument('--lr', type=float, default=1e-3)
    h.add_argument('--weight-decay', type=float, default=1e-2)
    h.add_argument('--hidden', type=int, default=512)
    h.add_argument('--hold', type=int, default=10, help='one match in this many held out')
    h.add_argument('--seed', type=int, default=0)
    h.add_argument('--torch-threads', type=int, default=8)
    g = sub.add_parser('play')
    g.add_argument('--data', default=os.environ.get('EFZ_DATA') or os.environ.get('EFZ_DIR'))
    g.add_argument('--agent', required=True)
    g.add_argument('--combo', help="train-clock's combo.pt")
    g.add_argument('--chooser', help="train-chooser's chooser.pt (with --library)")
    g.add_argument('--library', help="--chooser's combos (combo_library.py's)")
    g.add_argument('--margin', type=float, default=200.0,
                   help='--chooser: the HP a combo must promise over its own play')
    g.add_argument('--deterministic', action='store_true', help="the network's likeliest action")
    g.add_argument('--temperature', type=float, default=1.0)
    g.add_argument('--p2', default='cpu')
    g.add_argument('--chars', nargs=2, default=('ayu', 'random'))
    g.add_argument('--p2-advantage')
    g.add_argument('--level', type=int, default=4)
    g.add_argument('--matches', type=int, default=64)
    g.add_argument('--minutes', type=float, default=5)
    g.add_argument('--seed', type=int, default=7)
    g.add_argument('--json')
    args = p.parse_args()
    if args.cmd in ('collect', 'play') and not args.data:
        sys.exit('pass --data, the folder of an EFZ 4.02 install (or set EFZ_DATA)')
    if args.cmd == 'play' and bool(args.combo) == bool(args.chooser):
        sys.exit('play: one of --combo, --chooser (with --library)')
    {'collect': collect, 'train': train, 'train-clock': train_clock,
     'train-chooser': train_chooser, 'play': play}[args.cmd](args)


if __name__ == '__main__':
    main()
