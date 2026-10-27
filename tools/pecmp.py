#!/usr/bin/env python3
"""Compare two PE images byte for byte and say where they differ.

Prints the headers' differing fields, then for each section the size difference, the
number of differing bytes and the first differing runs (with the data directory or the
symbol of the second image's map a run falls in, when one is given). Exits 0 only when
the files are identical.

Usage: tools/pecmp.py ORIGINAL BUILT [MAP] [-n RUNS]
"""
import bisect
import re
import sys

import pefile


def read_map(path):
    syms = []
    for line in open(path, encoding='latin-1'):
        m = re.match(r'\s+[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s', line)
        if m:
            syms.append((int(m[2], 16), m[1]))
    syms.sort()
    return syms


def fields(pe):
    out = {}
    for name, s in (('file', pe.FILE_HEADER), ('opt', pe.OPTIONAL_HEADER)):
        for k in s.__keys__:
            k = k[0]
            out[f'{name}.{k}'] = getattr(s, k)
    for i, d in enumerate(pe.OPTIONAL_HEADER.DATA_DIRECTORY):
        out[f'dir{i}.{d.name}'] = (d.VirtualAddress, d.Size)
    for s in pe.sections:
        n = s.Name.rstrip(b'\0').decode()
        out[f'section {n}'] = (s.VirtualAddress, s.Misc_VirtualSize, s.PointerToRawData, s.SizeOfRawData)
    return out


def main():
    args = [a for a in sys.argv[1:] if not a.startswith('-')]
    nruns = 8
    if '-n' in sys.argv:
        nruns = int(sys.argv[sys.argv.index('-n') + 1])
        args = [a for a in args if a != str(nruns)]
    a_path, b_path = args[0], args[1]
    syms = read_map(args[2]) if len(args) > 2 else []
    addrs = [s[0] for s in syms]
    da, db = open(a_path, 'rb').read(), open(b_path, 'rb').read()
    if da == db:
        print('identical', len(da), 'bytes')
        return 0
    pa, pb = pefile.PE(data=da), pefile.PE(data=db)
    fa, fb = fields(pa), fields(pb)
    for k in fa:
        if fa.get(k) != fb.get(k):
            va, vb = fa.get(k), fb.get(k)
            fmt = lambda v: tuple(hex(x) for x in v) if isinstance(v, tuple) else (hex(v) if isinstance(v, int) else v)
            print(f'  {k}: {fmt(va)} != {fmt(vb)}')
    hdr = pa.OPTIONAL_HEADER.SizeOfHeaders
    nh = sum(1 for i in range(min(hdr, len(db))) if da[i] != db[i])
    print(f'headers: {nh} differing bytes in the first {hdr:#x}')
    base = pa.OPTIONAL_HEADER.ImageBase
    for sa in pa.sections:
        name = sa.Name.rstrip(b'\0').decode()
        sb = next((s for s in pb.sections if s.Name == sa.Name), None)
        if sb is None:
            print(f'{name}: missing')
            continue
        xa = da[sa.PointerToRawData:sa.PointerToRawData + sa.SizeOfRawData]
        xb = db[sb.PointerToRawData:sb.PointerToRawData + sb.SizeOfRawData]
        n = min(len(xa), len(xb))
        runs = []
        for i in range(n):
            if xa[i] != xb[i]:
                if runs and i - runs[-1][1] <= 16:
                    runs[-1][1] = i
                else:
                    runs.append([i, i])
        ndiff = sum(1 for i in range(n) if xa[i] != xb[i])
        dv = sb.Misc_VirtualSize - sa.Misc_VirtualSize
        print(f'{name}: size {sa.Misc_VirtualSize:#x} vs {sb.Misc_VirtualSize:#x} ({dv:+#x}), '
              f'{ndiff} differing bytes in {len(runs)} runs')
        for lo, hi in runs[:nruns]:
            va = base + sa.VirtualAddress + lo
            where = ''
            if syms:
                j = bisect.bisect_right(addrs, base + sb.VirtualAddress + lo) - 1
                if j >= 0:
                    where = f'  [{syms[j][1][:70]}+{base + sb.VirtualAddress + lo - syms[j][0]:#x}]'
            print(f'  {va:#x}-{base + sa.VirtualAddress + hi:#x}{where}')
    return 1


if __name__ == '__main__':
    sys.exit(main())
