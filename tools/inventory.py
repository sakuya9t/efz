#!/usr/bin/env python3
"""Rough function and vtable inventory of efz.exe, used to size and split the decomp.

Function starts are direct call targets, code pointers stored in .rdata/.data, and
`push ebp; mov ebp,esp` frames that follow a ret/jmp/int3.  The game code was built
without optimisation, so every game function has that frame and this is reliable for
it; the optimised CRT at the end of .text is only approximated.  Disassembly comes
from GNU objdump.  A disassembler database (Ghidra/IDA) supersedes this list.

Usage: tools/inventory.py [path/to/efz.exe] [out.json]   (default: $EFZ_DIR/efz.exe)
"""
import collections
import json
import os
import re
import struct
import subprocess
import sys

import pefile

# Link-order boundaries in .text.  Game objects end where the import-call thunks
# (`jmp [IAT]`) start; DirectInput's c_dfDIKeyboard/c_dfDIJoystick tables from
# dinput.lib follow, then the static CRT from operator new onwards.
GAME_END = 0x77697E
CRT_START = 0x777D46

LINE = re.compile(r'^\s*([0-9a-f]+):\t(\S+)\s*(.*)$')
HEX = re.compile(r'0x[0-9a-f]+')


def disassemble(path):
    out = subprocess.run(['objdump', '-d', '-M', 'intel', '--no-show-raw-insn', '-j', '.text', path],
                         check=True, capture_output=True, text=True).stdout
    return [(int(m[1], 16), m[2], m[3]) for m in map(LINE.match, out.splitlines()) if m]


def main():
    exe = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.environ.get('EFZ_DIR', '.'), 'efz.exe')
    out_path = sys.argv[2] if len(sys.argv) > 2 else None
    pe = pefile.PE(exe)
    base = pe.OPTIONAL_HEADER.ImageBase
    text = next(s for s in pe.sections if s.Name.startswith(b'.text'))
    t0 = base + text.VirtualAddress
    t1 = t0 + text.Misc_VirtualSize

    insns = disassemble(exe)
    index = {a: i for i, (a, _, _) in enumerate(insns)}

    def is_frame(i):
        return insns[i][1:] == ('push', 'ebp') and i + 1 < len(insns) and insns[i + 1][1:] == ('mov', 'ebp,esp')

    reasons = collections.defaultdict(set)
    jump_tables = 0
    for i, (a, mn, ops) in enumerate(insns):
        if mn == 'call' and HEX.fullmatch(ops):
            reasons[int(ops, 16)].add('call')
        if mn == 'jmp' and '*4+0x' in ops:
            jump_tables += 1
        if is_frame(i) and (i == 0 or insns[i - 1][1].startswith(('ret', 'jmp', 'int3'))):
            reasons[a].add('frame')

    # Code pointers in data: vtables and callback tables.  A pointer only counts if it
    # lands on a frame or an already-known start, which drops coincidental values.
    data_ptrs = []
    for s in pe.sections:
        if not s.Name.startswith((b'.rdata', b'.data')):
            continue
        d = s.get_data()
        for off in range(0, len(d) - 3, 4):
            v = struct.unpack_from('<I', d, off)[0]
            if v in index and (v in reasons or is_frame(index[v])):
                reasons[v].add('data')
                data_ptrs.append((base + s.VirtualAddress + off, v))

    starts = sorted(a for a in reasons if t0 <= a < t1 and a in index)
    starts = sorted(set(starts) | {GAME_END})
    funcs = [{'addr': a, 'size': (starts[k + 1] if k + 1 < len(starts) else t1) - a,
              'region': 'game' if a < GAME_END else 'lib' if a < CRT_START else 'crt', 'refs': sorted(reasons[a])}
             for k, a in enumerate(starts)]

    # Runs of consecutive code pointers in .rdata are vtables.
    vtables, run, prev = [], [], None
    for loc, v in data_ptrs:
        if prev is not None and loc == prev + 4 and loc < base + 0x38F000:
            run.append(v)
        else:
            if len(run) >= 2:
                vtables.append({'addr': run_start, 'slots': run})
            run, run_start = [v], loc
        prev = loc
    if len(run) >= 2:
        vtables.append({'addr': run_start, 'slots': run})

    game = [f for f in funcs if f['region'] == 'game']
    crt = [f for f in funcs if f['region'] == 'crt']
    sizes = sorted(f['size'] for f in game)
    print(f'.text {t0:#x}-{t1:#x}, {len(insns)} instructions, {jump_tables} switch jump tables')
    print(f'game: {len(game)} functions, {sum(sizes)} bytes, median {sizes[len(sizes) // 2]}, largest {sizes[-1]}')
    lib = [f for f in funcs if f['region'] == 'lib']
    print(f'lib:  {sum(f["size"] for f in lib)} bytes of import thunks and DirectInput data formats')
    print(f'crt:  {len(crt)} functions, {sum(f["size"] for f in crt)} bytes (link the original static CRT, do not decompile)')
    shape = collections.Counter(len(v['slots']) for v in vtables)
    print('vtables by slot count: ' + ', '.join(f'{n} slots x{c}' for n, c in sorted(shape.items())))
    print('largest game functions:')
    for f in sorted(game, key=lambda f: -f['size'])[:10]:
        print(f'  {f["addr"]:#x} {f["size"]:6}  {",".join(f["refs"])}')

    if out_path:
        with open(out_path, 'w') as fp:
            json.dump({'text': [t0, t1], 'game_end': GAME_END, 'crt_start': CRT_START,
                       'functions': funcs, 'vtables': vtables}, fp, indent=1)


if __name__ == '__main__':
    main()
