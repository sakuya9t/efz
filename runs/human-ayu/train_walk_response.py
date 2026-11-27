"""Distill Ayu's response to Sayuri's walk into an ordinary policy:1 ReLU network."""
import argparse
import hashlib
import json
from pathlib import Path
import struct

import numpy as np

from sayuri_throws import DELAY, HOLD, Signals
from efz_env.actions import encode
from efz_env.export import MAGIC, NativeAgent, _tensor, read_agent, unpack_agent, export_agent
from efz_env.history import history_features
from efz_env.vec import character_names


def samples(games, model, index):
    """Teacher inputs and native reference probabilities on frames that the new unit can affect."""
    xs, probability, target, gates = [], [], [], []
    sayuri = character_names().index('sayuri')
    for path in games:
        with np.load(path) as game:
            if 'controls' in game:
                v, controls = game['obs'][:,0], game['controls'][:,0]
            else:
                v, controls = game['obs'].astype(np.float32), game['input']
        history = history_features(controls, model.history)
        sig = Signals()
        start = -HOLD
        batch, ys, weights = [], [], []
        for i in range(DELAY,len(v)):
            if v[i,1] != v[i-DELAY,1] or v[i,2] or v[i,3]:
                sig, start = Signals(), -HOLD
                continue
            seen = v[i-DELAY]
            if sig.event(i,seen) == 'walk':
                start = i
            if (int(seen[66]) != sayuri or seen[50] != 1
                    or int(seen[18]) not in (0,1,2,3,4,8) or np.any(seen[[2,3,20,39,52,71]])):
                continue
            gate = np.clip((44-abs(float(seen[4]))*640)/2, 0, 1)
            if gate:
                batch.append(np.r_[seen, history[i]])
                ys.append(i-start < HOLD)
                weights.append(gate)
        if batch:
            x = np.asarray(batch,np.float32)
            lp = model.log_probs(x)
            p = np.exp(lp[:,index]).astype(float)
            xs.extend(x)
            probability.extend(p)
            target.extend(np.where(ys,.98+.02*p,p))
            gates.extend(weights)
    if not xs:
        raise ValueError('No walk-in frames in these recordings')
    return np.array(xs), np.array(probability), np.array(target), np.array(gates)


def fit(p, y, gate):
    # The derivative of the cross-entropy is monotone in this one output weight.
    logits = np.log(p) - np.log1p(-p)
    lo, hi = 0., 24.
    for _ in range(48):
        gain = (lo+hi)/2
        pred = 1/(1+np.exp(-(logits+gate*gain)))
        if np.dot(gate, pred-y) > 0:
            hi = gain
        else:
            lo = gain
    return (lo+hi)/2


def expand(t):
    """Add a ReLU unit for the delayed approach cue. Preserve the native dot-product lanes."""
    cont = t['features.cont'].tolist()
    width = len(cont)
    embed = t['features.action'].shape[1]
    # Adding a multiple of 16 preserves the accumulation order in the game's Dot().
    added = 16
    sayuri = character_names().index('sayuri')
    ayu = character_names().index('ayu')
    for prefix, layer in [('features.', 'pi.0.weight'), ('train.vf.features.', 'train.vf.0.weight')]:
        for field in ('action','own_action'):
            t[prefix+field] = np.pad(t[prefix+field],((0,0),(0,added)))
        # Four embedding blocks (action, character-specific action for each player).
        old = t[layer]
        pieces = [old[:,:width]]
        for j in range(4):
            pieces.append(np.pad(old[:,width+j*embed:width+(j+1)*embed],((0,0),(0,added))))
        pieces.append(old[:,width+4*embed:])
        t[layer] = np.concatenate(pieces,axis=1)
    own = t['features.own_action']
    for action in (0,1,2,3,4,8):
        own[ayu*1024+action,embed] = 1
    own[sayuri*1024+1,embed+1] = 1
    n0,n1 = len(t['pi.0.bias']),len(t['pi.1.bias'])
    assert n0%16 == n1%16 == 0
    t['pi.0.weight'] = np.pad(t['pi.0.weight'],((0,added),(0,0)))
    t['pi.0.bias'] = np.pad(t['pi.0.bias'],(0,added))
    t['pi.1.weight'] = np.pad(t['pi.1.weight'],((0,added),(0,added)))
    t['pi.1.bias'] = np.pad(t['pi.1.bias'],(0,added))
    t['action.weight'] = np.pad(t['action.weight'],((0,0),(0,added)))
    w,b=t['pi.0.weight'],t['pi.0.bias']
    # Penalty outside the inner 42 pixels, 1 at 44 pixels.
    dx=cont.index(4)
    for offset,sign in enumerate((1,-1)):
        w[n0+offset,dx] = sign*320/t['features.scale'][dx]
        b[n0+offset] = sign*320*t['features.mean'][dx]-21
    # One violation turns the cue off. Indicators come from the characters' action embeddings.
    w[n0+2,width+(embed+added)+embed] = -1
    w[n0+2,width+3*(embed+added)+embed+1] = -1
    b[n0+2] = 2
    for col in (2,3,20,39,52,71):
        j=cont.index(col)
        zero,one=np.clip((np.array([0.,1.])-t['features.mean'][j])*t['features.scale'][j],-10,10)
        w[n0+2,j]=1/(one-zero)
        b[n0+2]-=zero/(one-zero)
    t['pi.1.weight'][n1,n0:n0+3] = [-1,-1,-2]
    t['pi.1.bias'][n1] = 1
    return n1


def portable(value):
    if isinstance(value,list):
        return [portable(v) for v in value]
    if isinstance(value,dict):
        return {k:portable(v) for k,v in value.items()}
    if isinstance(value,str) and '/runs/human-ayu/' in value:
        return value.split('/runs/human-ayu/')[-1]
    if isinstance(value,str) and value.startswith('~/data/efz-replays/'):
        return Path(value).name
    return value


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base', type=Path, required=True)
    parser.add_argument('--out', type=Path, required=True)
    parser.add_argument('--games', type=Path, nargs='+', required=True)
    args = parser.parse_args()
    args.out.mkdir(parents=True, exist_ok=False)
    fmt, keys, tensors = read_agent(args.base)
    if keys['activation'] != 'relu' or any(n.startswith('train.adam.') for n in tensors):
        raise ValueError('Expected a round 25 ReLU checkpoint without optimizer moments')

    original = NativeAgent(args.base)
    chosen = bytes.fromhex(keys['table']).index(encode(7))
    inputs, probability, targets, gate = samples(args.games, original, chosen)
    gain = fit(probability, targets, gate)
    feature = expand(tensors)
    tensors['action.weight'][chosen, feature] = gain

    config = portable(json.loads(keys['train.config']))
    keys['train.config'] = json.dumps(config, separators=(',', ':'))
    header = ''.join(f'{k}={v}\n' for k, v in keys.items()).encode()
    staging = args.out / 'initial.efzagent'
    with staging.open('xb') as f:
        f.write(MAGIC + struct.pack('<II', fmt, len(header)) + header + struct.pack('<I', len(tensors)))
        for name, arr in tensors.items():
            kind = 'u8' if arr.dtype == np.uint8 else arr.dtype.kind == 'i'
            f.write(_tensor(name, arr, kind))
    checkpoint = args.out / 'checkpoint'
    unpack_agent(staging, checkpoint)
    result = args.out / 'ayu-round28.efzagent'
    check = export_agent(checkpoint / 'model.zip', result, name='Ayu', version='round28', parts_from=args.base)
    staging.unlink()

    native = NativeAgent(result)
    predicted = original.log_probs(inputs).copy()
    predicted[:, chosen] += gate * gain
    predicted -= np.logaddexp.reduce(predicted, axis=1)[:, None]
    error = float(np.max(abs(native.log_probs(inputs) - predicted)))
    assert error < 2e-4, error
    outside = inputs.copy()
    outside[:, 66] = character_names().index('kano')
    assert np.array_equal(original.log_probs(outside), native.log_probs(outside))
    stats = dict(games=len(args.games), frames=len(inputs), base_probability=float(probability.mean()),
                 target=float(targets.mean()), gain=gain, export=check, gate_error=error,
                 sha256=hashlib.sha256(result.read_bytes()).hexdigest())
    print(json.dumps(stats, indent=2))
    (args.out / 'fit.json').write_text(json.dumps(stats, indent=2) + '\n')
    original.close()
    native.close()


if __name__ == '__main__':
    main()
