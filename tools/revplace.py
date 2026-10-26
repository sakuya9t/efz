#!/usr/bin/env python3
"""Compare where a rebuilt EfzRevival binary puts each function with where the original has it.

The rebuild's addresses come from its link map; the original's from the annotations
(`// FUNCTION:`) and from tools/revmatch.py's placements (NAMES.json). Functions are listed
in the rebuild's order with the offset between the two; a byte-identical image has every
offset 0, and the first function whose offset changes is where the layouts part.

Usage: tools/revplace.py MAP NAMES.json SRC_DIR [LO HI] [--all]
  prints the runs of equal offsets (--all: every function).
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402
from revltcg import read_map  # noqa: E402


def main():
    args = [a for a in sys.argv[1:] if a != '--all']
    every = '--all' in sys.argv
    mapfile, names, src = args[:3]
    lo, hi = (int(args[3], 16), int(args[4], 16)) if len(args) > 4 else (0, 1 << 32)
    original = {n: int(a, 16) for n, a in json.load(open(names)).items()}
    for qual, (kind, addr) in funcdiff.read_annotations(src).items():
        if kind == 'FUNCTION':
            for n in funcdiff.mangled_prefixes(qual):
                if n.endswith('\0'):
                    original.setdefault(n[:-1], addr)
    syms, _byname = read_map(mapfile)
    rows = [(a, n, original[n]) for a, n in syms if n in original and lo <= original[n] < hi]
    run = None
    for a, n, o in rows:
        delta = a - o
        if every:
            print(f'{a:#x} {o:#x} {delta:+#x} {n[:100]}')
        elif run is None or run[0] != delta:
            if run:
                print(f'  {run[3]} functions, through {run[2][:80]}')
            print(f'{delta:+#x} from {a:#x} (original {o:#x}) {n[:90]}')
            run = [delta, a, n, 1]
        else:
            run[2], run[3] = n, run[3] + 1
    if run and not every:
        print(f'  {run[3]} functions, through {run[2][:80]}')


if __name__ == '__main__':
    main()
