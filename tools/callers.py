#!/usr/bin/env python3
"""Who calls (or points at) a function: callers.py 0xADDR [0xADDR ...]"""
import bisect
import json
import os
import re
import struct
import sys

import capstone
import pefile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def main():
    exe = os.path.join(os.environ['EFZ_DIR'], 'efz.exe')
    pe = pefile.PE(exe)
    img = pe.get_memory_mapped_image()
    inv = json.load(open(os.path.join(REPO, 'build', 'inventory.json')))
    funcs = sorted((f['addr'], f['size']) for f in inv['functions'])
    starts = [a for a, _ in funcs]
    targets = {int(a, 16) for a in sys.argv[1:]}
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    found = {t: [] for t in targets}
    for a, size in funcs:
        if a >= 0x777d46:
            continue
        code = img[a - 0x400000:a - 0x400000 + size]
        for i in md.disasm(code, a):
            if i.mnemonic in ('call', 'push', 'mov') and i.op_str:
                for m in re.finditer(r'0x[0-9a-f]+', i.op_str):
                    v = int(m.group(0), 16)
                    if v in targets:
                        found[v].append((i.address, a, i.mnemonic))
    for off in range(0x387000, 0x38f000, 4):
        v = struct.unpack_from('<I', img, off)[0]
        if v in targets:
            found[v].append((0x400000 + off, None, 'data'))
    for t in sorted(found):
        print(f'{t:#x}:', ', '.join(f'{k} @{s:#x} in {f:#x}' if f else f'{k} @{s:#x}' for s, f, k in found[t]) or 'none')


if __name__ == '__main__':
    main()
