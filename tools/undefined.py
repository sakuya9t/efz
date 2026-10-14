#!/usr/bin/env python3
"""List C++ symbols that some object references and none defines: these would make
the final link fail although every object compiles and diffs clean.

Usage: tools/undefined.py [build/*.obj]
"""
import glob
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    objs = sys.argv[1:] or sorted(glob.glob(os.path.join(REPO, 'build', '*.obj')))
    defined, used = set(), {}
    for path in objs:
        coff = funcdiff.Coff(path)
        for s in coff.symbols.values():
            if s['storage'] != 2:
                continue
            if s['section'] > 0:
                defined.add(s['name'])
            elif s['section'] == 0 and s['value'] == 0:
                used.setdefault(s['name'], set()).add(os.path.basename(path))
    missing = 0
    for name in sorted(used):
        # game code only: C++ names of our classes (the CRT and imports come from libs)
        if name in defined or not name.startswith('?') or '@std@@' in name:
            continue
        if any(x in name for x in ('@@YAPAXI@Z', '??2@', '??3@', '_purecall')):
            continue
        print(f'{name}  (used by {", ".join(sorted(used[name]))})')
        missing += 1
    print(f'{missing} undefined')
    sys.exit(1 if missing else 0)


if __name__ == '__main__':
    main()
