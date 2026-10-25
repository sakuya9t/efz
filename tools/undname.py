#!/usr/bin/env python3
"""Demangle MSVC decorated names with VS2012's undname.exe (through tools/msvc11), cached.

    from undname import undname; undname(['?f@@YAXXZ'])  -> {'?f@@YAXXZ': 'void __cdecl f(void)'}
The cache is build/revival/undname.json.
"""
import json
import os
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CACHE = os.path.join(REPO, 'build', 'revival', 'undname.json')


def undname(names):
    cache = json.load(open(CACHE)) if os.path.exists(CACHE) else {}
    todo = sorted({n for n in names if n not in cache and n.startswith('?')})
    if todo:
        tmp = os.path.join(REPO, 'build', 'revival', f'undname.{os.getpid()}.in')
        os.makedirs(os.path.dirname(tmp), exist_ok=True)
        open(tmp, 'w').write('\n'.join(todo) + '\n')
        out = subprocess.run([os.path.join(REPO, 'tools', 'msvc11'), 'undname', os.path.basename(tmp)],
                             cwd=os.path.dirname(tmp), capture_output=True, text=True,
                             check=True).stdout.splitlines()
        out = [l.rstrip() for l in out if l.strip()]
        os.remove(tmp)
        if len(out) == len(todo):
            cache.update(zip(todo, out))
            part = f'{CACHE}.{os.getpid()}'
            json.dump(cache, open(part, 'w'))
            os.replace(part, CACHE)  # atomic: several processes may share the cache
        else:
            for n in todo:
                cache[n] = n
    return {n: cache.get(n, n) for n in names}


if __name__ == '__main__':
    for n, d in undname(sys.argv[1:]).items():
        print(d)
