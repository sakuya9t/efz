#!/usr/bin/env python3
"""Predict where a recompiled object's functions land in an EfzRevival binary, and
compare that with the original's layout.

Visual C++ 2012 emits an object's functions (each a COMDAT under /Gy) sorted by
decorated name, and the linker keeps that order. Functions nothing references are
dropped (/OPT:REF), and of several identical functions only the last survives
(/OPT:ICF). docs/revival.md has the experiments.

The prediction takes the object's functions in section order, keeps those whose
masked bytes occur in the given range of the original, and of identical ones keeps the
last. It is then aligned with the original's functions in the range (from the Ghidra
export), so that a misplaced name shows up as a function at the wrong position.

Usage: tools/revlayout.py BINARY FUNCTIONS_JSON OBJ LO HI
"""
import difflib
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import pefile  # noqa: E402

from libmatch import coff_functions, find  # noqa: E402


def section_order(data):
    """Functions of a COFF object as (name, code, mask), in the order the linker lays
    them out: by section number, then offset."""
    import struct
    _m, nsec, _ts, symptr, nsym, optsize, _ch = struct.unpack_from('<HHIIIHH', data, 0)
    strtab = symptr + 18 * nsym
    where = {}
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
            where[name] = (secnum, value)
        k += 1 + naux
    funcs = list(coff_functions(data))
    return sorted(funcs, key=lambda f: where.get(f[0], (1 << 30, 0)))


def main():
    exe, fjson, obj, lo, hi = sys.argv[1], sys.argv[2], sys.argv[3], int(sys.argv[4], 16), int(sys.argv[5], 16)
    pe = pefile.PE(exe, fast_load=True)
    text = next(s for s in pe.sections if s.Name.startswith(b'.text'))
    base = pe.OPTIONAL_HEADER.ImageBase + text.VirtualAddress
    blob = text.get_data()[:text.Misc_VirtualSize]
    orig = sorted(x['entry'] for x in json.load(open(fjson)) if lo <= x['entry'] < hi)

    # predicted: object functions found in the range, identical bodies keep the last
    found = []
    for name, code, mask in section_order(open(obj, 'rb').read()):
        if name.startswith(('__unwindfunclet', '__ehhandler', '__catch')):
            continue
        hits = [base + h for h in find(blob, code, mask) if lo <= base + h < hi] if len(code) >= 3 else []
        if hits:
            found.append((name, hits))
    by_addr = {}
    for name, hits in found:
        for h in hits:
            by_addr[h] = name  # later names overwrite earlier: the last copy survives
    predicted = []
    for name, hits in found:
        if any(by_addr[h] == name for h in hits):
            predicted.append((name, [h for h in hits if by_addr[h] == name]))

    pred_addrs = [hits[0] for _n, hits in predicted]
    names = {hits[0]: n for n, hits in predicted}
    sm = difflib.SequenceMatcher(a=orig, b=pred_addrs, autojunk=False)
    same = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == 'equal':
            same += i2 - i1
            continue
        for a in orig[i1:i2]:
            print(f'  original {a:#x} {"(" + names[a][:80] + ")" if a in names else ""}')
        for a in pred_addrs[j1:j2]:
            print(f'  predicted {a:#x} {names[a][:90]}')
        print('  --')
    print(f'{same} of {len(orig)} original functions in place; {len(predicted)} predicted')


if __name__ == '__main__':
    main()
