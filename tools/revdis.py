#!/usr/bin/env python3
"""Disassemble part of an EfzRevival binary with its call targets and data labelled.

Labels come from tools/revnames.py's {address: name} (make revival-names writes
build/revival/<binary>.labels.json); imports and string literals are shown too.

Usage: tools/revdis.py LO HI [BINARY [LABELS.json]]
  BINARY defaults to $REVIVAL_DIR/EfzRevival.exe.
"""
import json
import os
import re
import subprocess
import sys

import pefile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def literal(img, base, a):
    o = a - base
    if not 0 <= o < len(img):
        return None
    b = img[o:o + 64]
    m = re.match(rb'([\x20-\x7e]{3,})\x00', b)
    if m:
        return '"' + m.group(1).decode()[:40] + '"'
    m = re.match(rb'((?:[\x20-\x7e]\x00){2,})\x00\x00', b)
    if m:
        return 'L"' + m.group(1).decode('utf-16le')[:40] + '"'
    return None


def main():
    lo, hi = sys.argv[1], sys.argv[2]
    rdir = os.environ.get('REVIVAL_DIR', os.path.expanduser('~/.local/share/efz-decomp/revival/1.02h'))
    binary = sys.argv[3] if len(sys.argv) > 3 else os.path.join(rdir, 'EfzRevival.exe')
    lpath = sys.argv[4] if len(sys.argv) > 4 else os.path.join(
        REPO, 'build', 'revival', os.path.basename(binary) + '.labels.json')
    labels = {int(k, 16): v for k, v in json.load(open(lpath)).items()} if os.path.exists(lpath) else {}
    pe = pefile.PE(binary)
    iat = {i.address: i.name.decode() for d in pe.DIRECTORY_ENTRY_IMPORT for i in d.imports if i.name}
    img = pe.get_memory_mapped_image()
    base = pe.OPTIONAL_HEADER.ImageBase
    out = subprocess.run(['objdump', '-d', '-M', 'intel', '--no-show-raw-insn',
                          f'--start-address={lo}', f'--stop-address={hi}', binary],
                         capture_output=True, text=True, check=True).stdout
    for line in out.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\t(.*)', line)
        if not m or m[2] == 'int3':
            continue
        a, ins = int(m[1], 16), m[2]
        if a in labels:
            print(f'--- {labels[a][:120]}')
        notes = []
        for v in re.findall(r'0x([0-9a-f]{6,8})\b', ins):
            v = int(v, 16)
            note = labels.get(v, '')[:90] or iat.get(v) or literal(img, base, v)
            if note:
                notes.append(note)
        print(f'{a:x}: {ins}' + ('   ; ' + ' | '.join(notes) if notes else ''))


if __name__ == '__main__':
    main()
