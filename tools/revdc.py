#!/usr/bin/env python3
"""Print the decompiled functions of an address range from a Ghidra export.

make revival-decomp writes build/revival/<binary>.c with tools/ghidra/ExportDecomp.java
(functions named from revmatch's placements). Blank lines are dropped.

Usage: tools/revdc.py LO HI [EXPORT.c]   (default build/revival/EfzRevival.exe.c)
"""
import os
import re
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
    path = sys.argv[3] if len(sys.argv) > 3 else os.path.join(REPO, 'build', 'revival', 'EfzRevival.exe.c')
    for block in re.split(r'^(?=// FUNCTION )', open(path).read(), flags=re.M):
        m = re.match(r'// FUNCTION (0x[0-9a-f]+)', block)
        if m and lo <= int(m.group(1), 16) < hi:
            print(re.sub(r'\n\s*\n', '\n', block).rstrip())


if __name__ == '__main__':
    main()
