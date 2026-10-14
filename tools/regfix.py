#!/usr/bin/env python3
"""Line up the compiler's register rotation with the original's.

The compiler hands out eax, ecx and edx in turn, statement after statement. Dead code
in the original source (unreachable statements after a `break`, empty `if`s) took its
turn without leaving any instructions, so in places the original's choice is one or two
steps further along than the lifted source gives. Where a function differs from the
original only in register names, this finds the first statement where the rotation
diverges, records the shift in tools/regpads.json (the lifter writes that many
`if (0) {}` before the statement), regenerates and compiles the object, and repeats.

Usage: tools/regfix.py OBJ [OBJ...]
"""
import json
import os
import re
import subprocess
import sys

import capstone

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402
import lift  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
PADS = os.path.join(REPO, 'tools', 'regpads.json')
ROT = ['eax', 'ecx', 'edx']
WIDE = {'al': 'eax', 'ax': 'eax', 'cl': 'ecx', 'cx': 'ecx', 'dl': 'edx', 'dx': 'edx'}
REG = re.compile(r'\b(e[acd]x|[acd][lx])\b')
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)


def disasm(blob, base):
    return [(i.address, f'{i.mnemonic} {i.op_str}') for i in md.disasm(blob, base)]


def norm(text):
    text = REG.sub('R', text)
    return re.sub(r'0x[4-7][0-9a-f]{5}\b', 'A', text)


def divergence(mine, orig, addr):
    """(original address, shift) of the first register-only difference, or None."""
    a, b = disasm(orig, addr), disasm(mine, addr)
    for (oa, ot), (_ma, mt) in zip(a, b):
        if ot == mt:
            continue
        if norm(ot) != norm(mt):
            return None          # something other than registers differs first
        if not re.match(r'mov e[acd]x, dword ptr \[ebp - 0x[0-9a-f]+\]$', ot):
            return None          # not where a statement starts: operand order, not rotation
        ro = [WIDE.get(r, r) for r in REG.findall(ot)]
        rm = [WIDE.get(r, r) for r in REG.findall(mt)]
        for x, y in zip(ro, rm):
            if x != y and x in ROT and y in ROT:
                return oa, (ROT.index(x) - ROT.index(y)) % 3
        # only an address differs (code moved by a size difference elsewhere)
    return None


def statement_start(img, syms, func, at):
    """The address where the statement containing `at` starts."""
    lf = lift.Lifter2(img, syms, func, lift.function_end(syms, func))
    items = lf.execute(None)
    starts = sorted({it[-1] for it in items if it[0] in ('stmt', 'cjump', 'jump') and it[-1]}
                    | {it[1] for it in items if it[0] == 'label'})
    best = None
    for s in starts:
        if s <= at:
            best = s
    return best


def main():
    exe = os.path.join(os.environ['EFZ_DIR'], 'efz.exe')
    original = funcdiff.Original(exe)
    img = lift.Image(exe)
    syms = lift.Symbols(img)
    pads = json.load(open(PADS)) if os.path.exists(PADS) else {}
    tried = {}
    for obj in sys.argv[1:]:
        for rnd in range(40):
            subprocess.run([os.path.join(REPO, 'tools', 'objcheck.sh'), obj], cwd=REPO,
                           capture_output=True)
            known = funcdiff.read_annotations(os.path.join(REPO, 'src'))
            coff = funcdiff.Coff(os.path.join(REPO, 'build', obj + '.obj'))
            changed = False
            for qual, (kind, addr) in known.items():
                if kind != 'FUNCTION':
                    continue
                hits = [f for f in coff.functions() if funcdiff.matches(f[0]['name'], funcdiff.mangled_prefixes(qual))]
                if not hits:
                    continue
                sym, sec, off, size = hits[0]
                mine, orig, _ = funcdiff.compare(coff, sym, sec, off, size, addr, original.pe,
                                                 original.image, original.iat, known, {})
                if mine == orig:
                    continue
                d = divergence(mine, orig, addr)
                if d is None:
                    continue
                at, shift = d
                start = at       # the first instruction of the statement that diverges
                f = pads.setdefault(f'{addr:#x}', {})
                key = f'{start:#x}'
                if key in tried.setdefault(addr, set()):
                    continue     # padding here didn't help: something else differs
                tried[addr].add(key)
                f[key] = (f.get(key, 0) + shift) % 3
                if not f[key]:
                    del f[key]
                print(f'{obj}: {qual} at {at:#x}: +{shift} before {key}')
                changed = True
            json.dump(pads, open(PADS, 'w'), indent=1, sort_keys=True)
            if not changed:
                break
        print(subprocess.run([os.path.join(REPO, 'tools', 'objcheck.sh'), obj], cwd=REPO,
                             capture_output=True, text=True).stdout.strip().split('\n')[-1])


if __name__ == '__main__':
    main()
