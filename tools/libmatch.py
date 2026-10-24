#!/usr/bin/env python3
"""Find the functions of prebuilt libraries in a binary.

Every function in the given .lib/.obj files (COFF, not /GL) is looked for in the
binary's .text, its relocated bytes masked out.  A function is found when all other
bytes agree at a 16-byte or unaligned start and the code is followed by padding or
another function.  This tells which library objects (and which build of a library)
the binary linked, and marks their code as not needing to be decompiled.

Usage: tools/libmatch.py BINARY LIB_OR_OBJ... [--list]
  prints, per object, how many of its functions were found; --list prints each one.
"""
import collections
import os
import struct
import sys

import pefile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from compid import members  # noqa: E402

MIN_SIZE = 6  # shorter functions (a ret, a jmp) match anywhere


def coff_functions(data):
    """Yield (name, code, mask) for each function in a COFF object; mask[i] marks bytes
    covered by a relocation."""
    machine, nsec, _ts, symptr, nsym, optsize, _ch = struct.unpack_from('<HHIIIHH', data, 0)
    if machine != 0x14C or not symptr:
        return
    secs = []
    for k in range(nsec):
        o = 20 + optsize + 40 * k
        size, rawptr, relptr, _ln, nrel, _nln, chars = struct.unpack_from('<IIIIHHI', data, o + 16)
        secs.append((size, rawptr, relptr, nrel, chars))
    strtab = symptr + 18 * nsym
    syms = collections.defaultdict(list)
    k = 0
    while k < nsym:
        o = symptr + 18 * k
        if data[o:o + 4] == b'\0\0\0\0':
            off = struct.unpack_from('<I', data, o + 4)[0]
            name = data[strtab + off:data.index(b'\0', strtab + off)].decode('latin-1')
        else:
            name = data[o:o + 8].rstrip(b'\0').decode('latin-1')
        value, secnum, typ, storage, naux = struct.unpack_from('<IhHBB', data, o + 8)
        if secnum > 0 and typ == 0x20 and storage in (2, 3):
            syms[secnum - 1].append((value, name))
        k += 1 + naux
    for idx, entries in syms.items():
        size, rawptr, relptr, nrel, chars = secs[idx]
        if not chars & 0x20 or not rawptr:  # IMAGE_SCN_CNT_CODE
            continue
        raw = data[rawptr:rawptr + size]
        mask = bytearray(size)
        for r in range(nrel):
            vaddr, _sym, typ = struct.unpack_from('<IIH', data, relptr + 10 * r)
            width = 4 if typ in (0x6, 0x7, 0x14, 0xA, 0xB) else 2
            for b in range(vaddr, min(vaddr + width, size)):
                mask[b] = 1
        entries.sort()
        for j, (value, name) in enumerate(entries):
            end = entries[j + 1][0] if j + 1 < len(entries) else size
            yield name, raw[value:end], mask[value:end]


def anchor(code, mask):
    """Longest run of unmasked bytes, as (offset, bytes)."""
    best, start = (0, b''), None
    for i in range(len(code) + 1):
        if i < len(code) and not mask[i]:
            if start is None:
                start = i
        elif start is not None:
            if i - start > len(best[1]):
                best = (start, code[start:i])
            start = None
    return best


def find(text, code, mask):
    off, key = anchor(code, mask)
    if len(key) < 4:
        return []
    hits, at = [], text.find(key)
    while at >= 0:
        start = at - off
        if start >= 0 and all(mask[i] or text[start + i] == code[i] for i in range(len(code))):
            hits.append(start)
        at = text.find(key, at + 1)
    return hits


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('--')]
    listing = '--list' in sys.argv
    pe = pefile.PE(args[0], fast_load=True)
    text = next(s for s in pe.sections if s.Name.startswith(b'.text'))
    base = pe.OPTIONAL_HEADER.ImageBase + text.VirtualAddress
    blob = text.get_data()[:text.Misc_VirtualSize]
    total = found = 0
    for path in args[1:]:
        data = open(path, 'rb').read()
        objs = members(data) if data[:8] == b'!<arch>\n' else [(path, data)]
        for objname, body in objs:
            funcs = [(n, c, m) for n, c, m in coff_functions(body) if len(c) >= MIN_SIZE]
            if not funcs:
                continue
            hits = []
            for name, code, mask in funcs:
                where = find(blob, code, mask)
                hits.append((name, len(code), where))
            n = sum(1 for h in hits if h[2])
            total += len(funcs)
            found += n
            short = objname.replace('\\', '/').rsplit('/', 1)[-1]
            print(f'{os.path.basename(path)}:{short}: {n}/{len(funcs)} functions found')
            if listing:
                for name, size, where in hits:
                    at = ' '.join(f'{base + w:#x}' for w in where[:4]) or '-'
                    print(f'    {at:24} {size:6} {name}')
    print(f'{found}/{total} functions found')


if __name__ == '__main__':
    main()
