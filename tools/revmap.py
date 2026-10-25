#!/usr/bin/env python3
"""List the functions of part of an EfzRevival binary with what is known about them.

One line per function start (Ghidra's, plus those after int3 padding): address, size
up to the next start, the names tools/revmatch.py placed there (demangled; several
when identical functions were folded) or `?`, and the string literals it uses.

Usage: tools/revmap.py LO HI [BINARY]
  reads build/revival/<binary>.names.json and .functions.json (make revival-names).
"""
import json
import os
import re
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from revdis import literal  # noqa: E402
from revmatch import Binary  # noqa: E402
from undname import undname  # noqa: E402
from revnames import SHORT  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def short(d):
    d = re.sub(r'\b(class|struct|enum|union) |__thiscall |__cdecl |__stdcall |'
               r'(public|private|protected): |virtual |static ', '', d)
    for a, b in SHORT:
        d = d.replace(a, b)
    return d


def main():
    lo, hi = int(sys.argv[1], 16), int(sys.argv[2], 16)
    rdir = os.environ.get('REVIVAL_DIR', os.path.expanduser('~/.local/share/efz-decomp/revival/1.02h'))
    binary = sys.argv[3] if len(sys.argv) > 3 else os.path.join(rdir, 'EfzRevival.exe')
    stem = os.path.join(REPO, 'build', 'revival', os.path.basename(binary))
    b = Binary(binary, stem + '.functions.json')
    names = json.load(open(stem + '.names.json')) if os.path.exists(stem + '.names.json') else {}
    at = {}
    for n, a in names.items():
        a = int(a, 16)
        if lo <= a < hi:
            at.setdefault(a, []).append(n)
    dem = undname([n for v in at.values() for n in v])
    out = subprocess.run(['objdump', '-d', '-M', 'intel', '--no-show-raw-insn',
                          f'--start-address={lo:#x}', f'--stop-address={hi:#x}', binary],
                         capture_output=True, text=True, check=True).stdout
    strs = {}
    import bisect
    for line in out.splitlines():
        m = re.match(r'\s+([0-9a-f]+):\t(.*)', line)
        if not m:
            continue
        for v in re.findall(r'0x([0-9a-f]{6,8})\b', m[2]):
            s = literal(b.image, b.base, int(v, 16))
            if s:
                f = b.starts[bisect.bisect_right(b.starts, int(m[1], 16)) - 1]
                strs.setdefault(f, []).append(s)
    for a in b.starts:
        if lo <= a < hi:
            ns = at.get(a)
            text = ' | '.join(short(dem[n])[:110] for n in sorted(ns)[:2]) if ns else '?'
            s = ' '.join(sorted(set(strs.get(a, [])))[:4])
            print(f'{a:#x} {b.next_start(a) - a:5d} {text}' + (f'   {s[:100]}' if s else ''))


if __name__ == '__main__':
    main()
