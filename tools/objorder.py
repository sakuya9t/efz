#!/usr/bin/env python3
"""Show the order of functions in .obj files as the linker will lay them out.

Each object's sections are placed in section order: the main .text first, then each
COMDAT (an inline function) in its own section. A COMDAT already defined by an earlier
object in the list is dropped, as the linker keeps the first copy. Prints each function
with its original address from the src/ annotations and flags addresses that go
backwards.

Usage: tools/objorder.py build/a.obj build/b.obj ...
"""
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    known = funcdiff.read_annotations(os.path.join(REPO, 'src'))
    prefixes = [(qual, addr, funcdiff.mangled_prefixes(qual))
                for qual, (kind, addr) in known.items() if kind == 'FUNCTION']
    seen = set()
    last = 0
    bad = 0
    for obj in sys.argv[1:]:
        print(f'== {obj}')
        coff = funcdiff.Coff(obj)
        funcs = sorted(coff.functions(), key=lambda f: (f[1], f[2]))
        for sym, sec, off, size in funcs:
            if not coff.sections[sec]['name'].startswith('.text'):
                continue
            name = sym['name']
            if name in seen:
                continue
            seen.add(name)
            hit = [(q, a) for q, a, p in prefixes if funcdiff.matches(name, p)]
            addr = hit[0][1] if hit else None
            flag = ''
            if addr is not None:
                if addr < last:
                    flag = '  <-- out of order'
                    bad += 1
                last = addr
            print(f'  {addr:#x}  ' if addr else '  ?         ', name, flag)
    print(f'{bad} out of order')


if __name__ == '__main__':
    main()
