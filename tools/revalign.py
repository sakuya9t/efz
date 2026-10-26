#!/usr/bin/env python3
"""Align a rebuilt EfzRevival binary's functions with the original's, range by range.

Per-function comparison can't see layout: which template instantiations an object
emits, which copy of identical functions the linker keeps, which order they come in.
This compares the two images' code directly. Each function (the rebuild's from its link
map, the original's from the Ghidra export plus starts after int3 padding) becomes the
text of its instructions with every address replaced by a placeholder, and the two
sequences are aligned (difflib). Equal runs are summarised; the rest is printed with the
rebuild's names, so missing, extra or moved functions show.

Usage: tools/revalign.py ORIGINAL BUILT MAP FUNCTIONS_JSON LO HI [BUILT_LO]
  LO-HI is the original's range; the rebuild's starts at BUILT_LO (default LO) and
  covers as many functions as its map places from there up to the end of the object
  that holds HI's last function.
"""
import bisect
import difflib
import json
import os
import re
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from revltcg import Image, read_map  # noqa: E402

ADDR = re.compile(r'0x[0-9a-f]{5,8}\b')


def shapes(img, starts, lo, hi):
    """[(address, normalised instruction text)] for each function start in lo-hi."""
    img.disasm()
    out = []
    sel = [a for a in starts if lo <= a < hi]
    for a, b in zip(sel, sel[1:] + [hi]):
        ins = img.instructions(a, b)
        out.append((a, '\n'.join(ADDR.sub('A', t) for _x, t in ins)))
    return out


def main():
    orig_path, built_path, mapfile, fjson = sys.argv[1:5]
    lo, hi = int(sys.argv[5], 16), int(sys.argv[6], 16)
    blo = int(sys.argv[7], 16) if len(sys.argv) > 7 else lo
    orig, built = Image(orig_path), Image(built_path)
    starts = {f['entry'] for f in json.load(open(fjson)) if not f['external']}
    t = orig.image[orig.tlo - orig.base:orig.thi - orig.base]
    for o in range(16 - orig.tlo % 16, len(t), 16):
        if t[o - 2:o] == b'\xcc\xcc' and t[o] != 0xCC:
            starts.add(orig.tlo + o)
    starts = sorted(starts)
    syms, _ = read_map(mapfile)
    names = {}
    for a, n in syms:
        if built.tlo <= a < built.thi:
            names.setdefault(a, []).append(n)
    bstarts = sorted(names)
    bhi = blo + (hi - lo) + 0x1000
    i = bisect.bisect_left(bstarts, bhi)
    bhi = bstarts[i] if i < len(bstarts) else built.thi
    a_rows = shapes(orig, starts, lo, hi)
    b_rows = shapes(built, bstarts, blo, bhi)
    sm = difflib.SequenceMatcher(None, [s for _a, s in a_rows], [s for _a, s in b_rows],
                                 autojunk=False)
    same = 0
    for op, i1, i2, j1, j2 in sm.get_opcodes():
        if op == 'equal':
            same += i2 - i1
            print(f'= {i2 - i1} functions: original {a_rows[i1][0]:#x}, rebuilt {b_rows[j1][0]:#x}')
            continue
        for k in range(i1, i2):
            print(f'- original {a_rows[k][0]:#x} ({a_rows[k][1].count(chr(10)) + 1} instructions)')
        for k in range(j1, j2):
            n = names.get(b_rows[k][0], ['?'])
            print(f'+ rebuilt  {b_rows[k][0]:#x} {n[0][:110]}' + (f' (+{len(n) - 1} folded)' if len(n) > 1 else ''))
    print(f'{same} of {len(a_rows)} original functions in place')


if __name__ == '__main__':
    main()
