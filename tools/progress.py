#!/usr/bin/env python3
"""How much of efz.exe's game code matches.

Compares every compiled object in build/ (run `make` first) with the original, and the
matching functions with the function inventory of efz.exe:
  * functions and bytes matched, out of the game code's
  * how far from the start of .text everything matches, and what comes next
  * with --range LO HI, the functions in that range that do not match yet

Usage: tools/progress.py [--range 0xLO 0xHI]   (original: $EFZ_DIR/efz.exe)
"""
import glob
import json
import os
import subprocess
import sys

import funcdiff

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def inventory(exe):
    """Function list of efz.exe from tools/inventory.py, cached in build/."""
    cache = os.path.join(REPO, 'build', 'inventory.json')
    if not os.path.exists(cache) or os.path.getmtime(cache) < os.path.getmtime(exe):
        os.makedirs(os.path.dirname(cache), exist_ok=True)
        subprocess.run([sys.executable, os.path.join(REPO, 'tools', 'inventory.py'), exe, cache],
                       check=True, stdout=subprocess.DEVNULL)
    with open(cache) as f:
        return json.load(f)


def main():
    exe = os.path.join(os.environ.get('EFZ_DIR', '.'), 'efz.exe')
    original = funcdiff.Original(exe)
    known = funcdiff.read_annotations(os.path.join(REPO, 'src'))
    matched = {}
    for obj in sorted(glob.glob(os.path.join(REPO, 'build', '*.obj'))):
        for qual, addr, size, ok, _lines in funcdiff.check(obj, original, known):
            if ok:
                matched[addr] = (qual, size)
    inv = inventory(exe)
    game = [f for f in inv['functions'] if f['region'] == 'game']
    game_bytes = sum(f['size'] for f in game)
    done = [f for f in game if f['addr'] in matched]
    done_bytes = sum(matched[f['addr']][1] for f in done)
    print(f'functions: {len(done)}/{len(game)} ({100 * len(done) / len(game):.1f}%)')
    print(f'bytes:     {done_bytes}/{game_bytes} ({100 * done_bytes / game_bytes:.2f}%)')
    # Everything up to the first game function that does not match.
    first = next((f for f in game if f['addr'] not in matched), None)
    if first:
        print(f'all game code matches from {game[0]["addr"]:#x} up to {first["addr"]:#x}; '
              f'next: {first["addr"]:#x} ({first["size"]} bytes)')
    else:
        print('all game code matches')
    extra = sorted(a for a in matched if a >= inv['game_end'])
    if extra:
        print(f'also matching outside the game code range: {len(extra)} '
              f'({", ".join(hex(a) for a in extra)})')
    if len(sys.argv) == 4 and sys.argv[1] == '--range':
        lo, hi = int(sys.argv[2], 16), int(sys.argv[3], 16)
        for f in game:
            if lo <= f['addr'] < hi and f['addr'] not in matched:
                print(f'  unmatched {f["addr"]:#x} ({f["size"]} bytes)')


if __name__ == '__main__':
    main()
