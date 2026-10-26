#!/usr/bin/env python3
"""Match a rebuilt EfzRevival binary's functions with the original's, wherever they are,
and write a link order file that puts them at the original's places.

Identical functions are folded by the link (/OPT:ICF), and which copy survives (so where
the code goes) depends on a qsort over every candidate in the link, dead code included
(docs/revival.md, "How the code is laid out"). The original's inputs had code that left
nothing in the image, so its choices can't be reproduced by matching the sources alone;
an order file (/ORDER) pins them.

Each function is the text of its instructions with addresses replaced by a placeholder
(as tools/revalign.py). Functions are paired by an alignment of the two sequences, then
by unique text, then, among functions of identical text, by the targets of their
address operands (calls, jumps, data) through the pairs found so far; pairs whose
operands disagree are dropped and redone, and an unpaired function takes over a
candidate its operands agree with better. It also reports how many of the original's
functions the build has at the same address with the same instructions.

Usage: tools/revorder.py ORIGINAL BUILT MAP FUNCTIONS_JSON LO HI [options]
  --order FILE   write the order file: every symbol of each paired function, in the
                 original's address order (symbols the linker can't order are skipped)
  --pairs FILE   write the pairs as JSON {original address: [built address, names]}
  --until ADDR   order only the functions before ADDR; the rest keep the link's order
  --libs A,B     libraries compiled with /Gy (all their functions can be ordered; of
                 other libraries only the inline functions are named)
  -v             list the unpaired functions on both sides
"""
import bisect
import difflib
import json
import os
import re
import subprocess
import sys
import tempfile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from revltcg import Image, read_map  # noqa: E402

ADDR = re.compile(r'0x[0-9a-f]{5,8}\b')


def resync(img, a, b):
    """Instructions of a-b disassembled on their own, for a function the linear sweep of
    the whole section ran into out of step (after a jump table)."""
    blob = img.image[a - img.base:b - img.base]
    with tempfile.NamedTemporaryFile(suffix='.bin') as f:
        f.write(blob)
        f.flush()
        out = subprocess.run(['objdump', '-D', '-b', 'binary', '-m', 'i386', '-M', 'intel',
                              '--no-show-raw-insn', f'--adjust-vma={a:#x}', f.name],
                             capture_output=True, text=True, check=True).stdout
    ins = []
    for line in out.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\t(.*)', line)
        if m:
            ins.append((int(m[1], 16), m[2].strip()))
    while ins and ins[-1][1] in ('int3', 'nop'):
        ins.pop()
    return ins


def functions(img, starts, lo, hi):
    """[(address, text, [operand addresses])] for each start in lo-hi."""
    img.disasm()
    out = []
    sel = [a for a in starts if lo <= a < hi]
    for a, b in zip(sel, sel[1:] + [hi]):
        ins = img.instructions(a, b) if a in img._dis else resync(img, a, b)
        text = '\n'.join(ADDR.sub('A', t) for _x, t in ins)
        ops = [int(h, 16) for _x, t in ins for h in ADDR.findall(t)]
        out.append((a, text, ops))
    return out


def map_objects(mapfile):
    """{address: [(name, object, is_comdat)]} from a link map's publics and statics."""
    out = {}
    for line in open(mapfile, encoding='latin-1'):
        m = re.match(r'\s+0001:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+(f?)\s*(i?)\s*(\S+)\s*$', line)
        if m:
            out.setdefault(int(m[2], 16), []).append((m[1], m[5], bool(m[4])))
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    opts = sys.argv[1:]

    def opt(name):
        return opts[opts.index(name) + 1] if name in opts else None
    for flag in ('--order', '--pairs', '--until', '--libs'):
        if flag in opts:
            args.remove(opt(flag))
    orig_path, built_path, mapfile, fjson = args[:4]
    lo, hi = int(args[4], 16), int(args[5], 16)
    orig, built = Image(orig_path), Image(built_path)

    starts = {f['entry'] for f in json.load(open(fjson)) if not f['external']}
    t = orig.image[orig.tlo - orig.base:orig.thi - orig.base]
    dis = orig.disasm()
    for o in range(16 - orig.tlo % 16, len(t), 16):
        # A function follows padding: int3s up to a 16-byte boundary (one is enough when
        # the sweep decodes it as an instruction of its own, as after a tail jump).
        if t[o] != 0xCC and (t[o - 2:o] == b'\xcc\xcc' or (
                t[o - 1] == 0xCC and dis.get(orig.tlo + o - 1, (0, ''))[1] == 'int3')):
            starts.add(orig.tlo + o)
    starts = sorted(starts)
    syms = map_objects(mapfile)
    bstarts = sorted(a for a in syms if built.tlo <= a < built.thi)

    A = functions(orig, starts, lo, hi)
    B = functions(built, bstarts, built.tlo, built.thi)
    pairs = {}      # original index -> built index
    used = set()

    # 1. Sequence alignment (the bulk: whole runs in place).
    sm = difflib.SequenceMatcher(None, [x[1] for x in A], [x[1] for x in B], autojunk=False)
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == 'equal':
            for k in range(i2 - i1):
                pairs[i1 + k] = j1 + k
                used.add(j1 + k)

    by_text = {}
    for j, (_a, text, _o) in enumerate(B):
        by_text.setdefault(text, []).append(j)

    def known_map():
        """original address -> built address: paired functions, and every address
        operand of paired functions (data, labels) by majority."""
        votes = {}
        for i, j in pairs.items():
            if A[i][1] != B[j][1]:
                continue
            for x, y in zip(A[i][2], B[j][2]):
                v = votes.setdefault(x, {})
                v[y] = v.get(y, 0) + 1
        known = {x: max(v, key=v.get) for x, v in votes.items()}
        known.update({A[i][0]: B[j][0] for i, j in pairs.items()})
        return known

    def score(i, j, fmap):
        sc = 0
        for x, y in zip(A[i][2], B[j][2]):
            if x in fmap and x != A[i][0]:
                sc += 1 if fmap[x] == y else -1
        return sc

    for _round in range(6):
        # Alignment pairs identical-looking small functions blindly: drop the pairs
        # whose operands disagree with what the other pairs say.
        fmap = known_map()
        bad = [i for i, j in pairs.items() if score(i, j, fmap) < 0]
        for i in bad:
            used.discard(pairs.pop(i))

        # 2./3. The rest: unique text, then operand agreement, repeated while it helps.
        changed = True
        while changed:
            changed = False
            fmap = known_map()
            for i, (a, text, ops) in enumerate(A):
                if i in pairs:
                    continue
                cands = [j for j in by_text.get(text, []) if j not in used]
                if not cands:
                    continue
                if len(cands) > 1:
                    # Operand agreement first; then the developer's objects over the
                    # libraries'; then nearness to where the paired neighbours put it.
                    prev = max((k for k in pairs if k < i), default=None)
                    guess = B[pairs[prev]][0] + (a - A[prev][0]) if prev is not None else a
                    scored = []
                    for j in cands:
                        own = int(any(':' not in obj for _n, obj, _i in syms.get(B[j][0], [])))
                        scored.append((score(i, j, fmap), own, -abs(B[j][0] - guess), j))
                    scored.sort(reverse=True)
                    if scored[0][0] < 0 or (len(scored) > 1 and scored[1][:3] == scored[0][:3]):
                        continue
                    cands = [scored[0][3]]
                pairs[i] = cands[0]
                used.add(cands[0])
                changed = True

        # A function still unpaired takes a candidate whose operands agree better
        # with it than with the one it was paired with.
        fmap = known_map()
        owner = {j: k for k, j in pairs.items()}
        stolen = 0
        for i, (a, text, ops) in enumerate(A):
            if i in pairs:
                continue
            best = None
            for j in by_text.get(text, []):
                k = owner.get(j)
                if k is None or k in (i,):
                    continue
                gain = score(i, j, fmap) - score(k, j, fmap)
                if gain > 0 and (best is None or gain > best[0]):
                    best = (gain, j, k)
            if best:
                _g, j, k = best
                del pairs[k]
                pairs[i] = j
                owner[j] = i
                stolen += 1
        if not bad and not stolen:
            break

    # 4. Gaps: unpaired functions between two pairs whose rebuilt counterparts are as
    # many unpaired functions apart (a function that still differs, in its place).
    order = sorted(pairs)
    for i0, i1 in zip(order, order[1:]):
        j0, j1 = pairs[i0], pairs[i1]
        if i1 - i0 > 1 and j1 - j0 == i1 - i0 and all(j not in used for j in range(j0 + 1, j1)):
            for k in range(1, i1 - i0):
                pairs[i0 + k] = j0 + k
                used.add(j0 + k)

    paired = len(pairs)
    # In place: the rebuild has the same instructions at the original function's address.
    same = []
    for i, (a, text, _o) in enumerate(A):
        nxt = A[i + 1][0] if i + 1 < len(A) else hi
        ins = resync(built, a, nxt)
        if '\n'.join(ADDR.sub('A', t) for _x, t in ins) == text:
            same.append(i)
    same_set = set(same)
    first = next((A[i][0] for i in range(len(A)) if i not in same_set), None)
    print(f'{paired} of {len(A)} original functions paired, {len(same)} in place and identical'
          + (f', the first other at {first:#x}' if first is not None else ''), file=sys.stderr)
    if '-v' in opts:
        inv = {j: i for i, j in pairs.items()}
        for i, (a, text, _o) in enumerate(A):
            if i not in pairs:
                cands = by_text.get(text, [])
                note = ', '.join(f'{B[j][0]:#x}' + (f'=orig {A[inv[j]][0]:#x}' if j in inv else '')
                                 for j in cands[:4])
                print(f'- original {a:#x} ({text.count(chr(10)) + 1} instructions) same text: {note or "none"}')
        bl = min(B[j][0] for j in pairs.values()) if pairs else lo
        bh = max(B[j][0] for j in pairs.values()) if pairs else hi
        for j, (b, text, _o) in enumerate(B):
            if j not in used and bl <= b <= bh:
                n = syms.get(b, [('?', '?', False)])
                print(f'+ rebuilt  {b:#x} {n[0][1]} {n[0][0][:100]}' + (f' (+{len(n) - 1})' if len(n) > 1 else ''))

    if opt('--pairs'):
        json.dump({f'{A[i][0]:#x}': [f'{B[j][0]:#x}', [n for n, _o, _c in syms.get(B[j][0], [])]]
                   for i, j in sorted(pairs.items())}, open(opt('--pairs'), 'w'), indent=0)
    if opt('--order'):
        # The rebuild's functions in the original's order: each paired one at its
        # original's place, and one that isn't paired (it still differs, or the two
        # sides split it differently) right after the paired function before it in the
        # rebuild, so that it keeps its neighbourhood.
        inv = {j: i for i, j in pairs.items()}
        libs = set(opt('--libs').split(',')) if opt('--libs') else set()

        def orderable(obj, inline):
            return inline or ':' not in obj or obj.split(':')[0] in libs
        until = int(opt('--until'), 16) if opt('--until') else hi
        bmax = max(B[j][0] for j in pairs.values())
        keyed = []
        anchor = (-1, 0)
        for j in range(len(B)):
            if j in inv:
                anchor = (A[inv[j]][0], 0)
                keyed.append((anchor, j))
            elif lo <= B[j][0] <= bmax and any(orderable(o, i) for _n, o, i in syms.get(B[j][0], [])):
                anchor = (anchor[0], anchor[1] + 1)
                keyed.append((anchor, j))
        # The functions from UNTIL on keep the link's own order (a static function, which
        # an order file can't name, can only be in its place when everything after it is
        # left unordered too).
        keyed = [(k, j) for k, j in keyed if k[0] < until]
        seen = set()
        with open(opt('--order'), 'w') as f:
            for _k, j in sorted(keyed):
                for name, obj, inline in syms.get(B[j][0], []):
                    # Only COMDATs can be ordered: every function of an object compiled
                    # with /Gy, a library's only when inline (or the library is in
                    # --libs). Local labels and catch blocks (part of their function's
                    # section) can't be named; C names go without their leading underscore.
                    if not orderable(obj, inline) or name in seen:
                        continue
                    if name.startswith(('$', '__catch$', '__unwindfunclet$', '__ehhandler$')):
                        continue
                    seen.add(name)
                    f.write((name if name.startswith('?') else name[1:]) + '\n')

if __name__ == '__main__':
    main()
