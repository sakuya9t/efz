#!/usr/bin/env python3
"""The sorts in link.exe's identical-function folding (IMAGE::ICFAnalysis), dumped and simulated.

link.exe sorts each group of candidates for /OPT:ICF with the C runtime's qsort
(ICFComparePcon), then folds each run of equal candidates into its first one. qsort isn't
stable, so which copy of identical library functions or data survives, and so where it
lands, depends on every candidate in the link. This tool makes a copy of the toolchain's
link.exe that writes the candidates before and after each of those sorts (the installed
toolchain is not changed), links the DLL with it, and replays the sorts:

  tools/icfsort.py patch            build/revival/linkhack/link.exe, the instrumented copy
  tools/icfsort.py run [OUT]        relink build/revival/dll's objects with it (the image is
                                    the same); the dump goes to OUT (build/revival/icfdump.bin)
  tools/icfsort.py check [DUMP]     replay every sort with the comparator and qsort below and
                                    compare with the dumped results
  tools/icfsort.py ties [DUMP]      the runs of equal candidates and which one comes first

The comparator (read from link.exe 11.00.61030): candidates whose section has
characteristics bit 0x2000 first, then the folding record's byte 0x11, the size (0 for
some modules), the size less padding, the record's checksum, the data checksum and last
the candidate's own id (CON+0: unique for link-time generated code, 0, read as
0xffffffff, for everything else). Equal ids are ties.
"""
import os
import struct
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LINKHACK = os.path.join(REPO, 'build', 'revival', 'linkhack')
DUMP = os.path.join(REPO, 'build', 'revival', 'icfdump.bin')

# The stub (tools/icfsort.py's own, assembled for 0x49c440, in .text's file padding):
# fopen(DUMP, "ab"); writes the count, the candidate pointers, then for each candidate its
# 0x40-byte CON, its 20-byte folding record, its module's CON base, flags and pointer and
# its module's name; calls qsort; writes the sorted pointers; fclose.
STUB = bytes.fromhex(
    '5589e583ec106068c5c5490068a3c54900ff1594f74a0083c40889c3536a016a048d450c50ff1524f7'
    '4a0083c41053ff750c6a04ff7508ff1524f74a0083c4108b75088b7d0c85ff0f84df0000008b0e536a'
    '016a4051ff1524f74a0083c4108b0e8b51108b829c00000039c1722c8b82b8000000c1e00603829c00'
    '000039c1771989c82b829c000000c1f8068d0480c1e002038294000000eb038d4140536a016a1450ff'
    '1524f74a0083c4108b0e8b51108955fc8b82ac0000008945f88b829c0000008945f4536a016a0c8d45'
    'f450ff1524f74a0083c4108b0e8b51108b520831c085d2740f66833c42007408403de803000072f189'
    '45f08955f4536a016a048d45f050ff1524f74a0083c4108b45f085c0741053506a02ff75f4ff1524f7'
    '4a0083c41083c6044fe919ffffffff7514ff7510ff750cff7508ff1584f64a0083c41053ff750c6a04'
    'ff7508ff1524f74a0083c41053ff15f0f64a0083c4046189ec5dc35a3a5c776f726b5c6275696c645c'
    '7265766976616c5c69636664756d702e62696e00616200')
CAVE = 0x49c440        # in .text's padding (its raw size runs to 0x49c600)
CALL = 0x420440        # ICFAnalysis's call dword ptr [__imp__qsort]
QSORT_CALL = bytes.fromhex('ff1584f64a00')


def patch():
    toolchain = os.environ.get('EFZ_TOOLCHAIN', os.path.expanduser('~/tools/efz-toolchain'))
    src = os.path.join(toolchain, 'vs2012', 'bin', 'link.exe')
    data = bytearray(open(src, 'rb').read())
    pe_off = struct.unpack_from('<I', data, 0x3c)[0]
    opt = pe_off + 24
    sections = opt + struct.unpack_from('<H', data, pe_off + 20)[0]
    vsize, va, rawsize, rawptr = struct.unpack_from('<IIII', data, sections + 8)
    base = struct.unpack_from('<I', data, opt + 28)[0]

    def off(addr):
        return rawptr + addr - base - va
    if data[off(CALL):off(CALL) + 6] != QSORT_CALL or any(data[off(CAVE):off(CAVE) + len(STUB)]):
        sys.exit('icfsort: not the link.exe this tool knows (11.00.61030)')
    data[off(CAVE):off(CAVE) + len(STUB)] = STUB
    data[off(CALL):off(CALL) + 6] = b'\xe8' + struct.pack('<i', CAVE - (CALL + 5)) + b'\x90'
    struct.pack_into('<I', data, sections + 8, rawsize)      # map the padding
    dllchar = opt + 0x46                                      # load at 0x400000
    struct.pack_into('<H', data, dllchar, struct.unpack_from('<H', data, dllchar)[0] & ~0x40)
    os.makedirs(LINKHACK, exist_ok=True)
    open(os.path.join(LINKHACK, 'link.exe'), 'wb').write(data)
    subprocess.run(['cp', '-r', os.path.join(toolchain, 'vs2012', 'bin', '1033'), LINKHACK],
                   check=True)


def run(out):
    if not os.path.exists(os.path.join(LINKHACK, 'link.exe')):
        patch()
    if os.path.exists(DUMP):
        os.remove(DUMP)
    dll = os.path.join(REPO, 'build', 'revival', 'dll', 'EfzRevival.dll')
    if os.path.exists(dll):
        os.remove(dll)
    env = dict(os.environ, MSVC11_LINK='/work/build/revival/linkhack/link.exe')
    subprocess.run(['make', '-s', 'build/revival/dll/EfzRevival.dll'], cwd=REPO, env=env,
                   check=True)
    if out != DUMP:
        os.replace(DUMP, out)


def parse(path):
    """[(candidates in their original order, sorted pointers)], one per sort."""
    d = open(path, 'rb').read()
    p = 0
    sorts = []
    while p < len(d):
        n = struct.unpack_from('<I', d, p)[0]
        p += 4
        ptrs = struct.unpack_from('<%dI' % n, d, p)
        p += 4 * n
        cands = []
        for ptr in ptrs:
            con, rec = d[p:p + 0x40], d[p + 0x40:p + 0x54]
            mbase, mflags, _mod = struct.unpack_from('<III', d, p + 0x54)
            length = struct.unpack_from('<I', d, p + 0x60)[0]
            name = d[p + 0x64:p + 0x64 + 2 * length].decode('utf-16-le')
            p += 0x64 + 2 * length
            cands.append(dict(ptr=ptr, con=con, rec=rec, mflags=mflags, module=name,
                              section=(ptr - mbase) // 0x40 + 1 if ptr >= mbase else None))
        sorted_ = list(struct.unpack_from('<%dI' % n, d, p))
        p += 4 * n
        sorts.append((cands, sorted_))
    return sorts


def u32(b, o):
    return struct.unpack_from('<I', b, o)[0]


def key(c):
    con, rec = c['con'], c['rec']
    return (0 if u32(con, 4) & 0x2000 else 1, rec[0x11] != 0,
            0 if c['mflags'] & 0x400 else u32(con, 0x24),
            (u32(con, 8) - u32(con, 0x20)) & 0xffffffff, u32(rec, 8), u32(con, 0x2c),
            u32(con, 0) or 0xffffffff)


def compare(a, b):
    ka, kb = a['key'], b['key']
    if ka[0] != kb[0]:
        return 1 if ka[0] else -1
    if ka[1] != kb[1]:
        return 1 if not kb[1] else -1
    for x, y in zip(ka[2:], kb[2:]):
        if x != y:
            return -1 if x < y else 1
    return 0


def qsort(a, cmp):
    """The C runtime's qsort (msvcr110): median of three, then partitioning; eight or
    fewer elements by selection."""
    def shortsort(lo, hi):
        while hi > lo:
            mx = lo
            for p in range(lo + 1, hi + 1):
                if cmp(a[p], a[mx]) > 0:
                    mx = p
            a[mx], a[hi] = a[hi], a[mx]
            hi -= 1
    if len(a) < 2:
        return
    stack = []
    lo, hi = 0, len(a) - 1
    while True:
        size = hi - lo + 1
        if size <= 8:
            shortsort(lo, hi)
        else:
            mid = lo + size // 2
            if cmp(a[lo], a[mid]) > 0:
                a[lo], a[mid] = a[mid], a[lo]
            if cmp(a[lo], a[hi]) > 0:
                a[lo], a[hi] = a[hi], a[lo]
            if cmp(a[mid], a[hi]) > 0:
                a[mid], a[hi] = a[hi], a[mid]
            loguy, higuy = lo, hi
            while True:
                if mid > loguy:
                    loguy += 1
                    while loguy < mid and cmp(a[loguy], a[mid]) <= 0:
                        loguy += 1
                if mid <= loguy:
                    loguy += 1
                    while loguy <= hi and cmp(a[loguy], a[mid]) <= 0:
                        loguy += 1
                higuy -= 1
                while higuy > mid and cmp(a[higuy], a[mid]) > 0:
                    higuy -= 1
                if higuy < loguy:
                    break
                a[loguy], a[higuy] = a[higuy], a[loguy]
                if mid == higuy:
                    mid = loguy
            higuy += 1
            if mid < higuy:
                higuy -= 1
                while higuy > mid and cmp(a[higuy], a[mid]) == 0:
                    higuy -= 1
            if mid >= higuy:
                higuy -= 1
                while higuy > lo and cmp(a[higuy], a[mid]) == 0:
                    higuy -= 1
            if higuy - lo >= hi - loguy:
                if lo < higuy:
                    stack.append((lo, higuy))
                if loguy < hi:
                    lo = loguy
                    continue
            else:
                if loguy < hi:
                    stack.append((loguy, hi))
                if lo < higuy:
                    hi = higuy
                    continue
        if not stack:
            return
        lo, hi = stack.pop()


def simulate(cands):
    for c in cands:
        c['key'] = key(c)
    a = list(cands)
    qsort(a, compare)
    return a


def main():
    cmd = sys.argv[1] if len(sys.argv) > 1 else 'check'
    arg = sys.argv[2] if len(sys.argv) > 2 else DUMP
    if cmd == 'patch':
        patch()
    elif cmd == 'run':
        run(arg)
    elif cmd == 'check':
        for i, (cands, sorted_) in enumerate(parse(arg)):
            same = [c['ptr'] for c in simulate(cands)] == sorted_
            print('sort %d: %d candidates, %s' % (i, len(cands), 'same' if same else 'DIFFERENT'))
    elif cmd == 'ties':
        for i, (cands, sorted_) in enumerate(parse(arg)):
            byptr = {c['ptr']: c for c in simulate(cands)}
            seq = [byptr[p] for p in sorted_]
            j = 0
            while j < len(seq):
                k = j
                while k + 1 < len(seq) and seq[k + 1]['key'] == seq[j]['key']:
                    k += 1
                if k > j:
                    print('sort %d size %d: %s' % (i, seq[j]['key'][3], ', '.join(
                        '%s#%s' % (c['module'].split('\\')[-1], c['section'])
                        for c in seq[j:k + 1])))
                j = k + 1
    else:
        sys.exit(__doc__)


if __name__ == '__main__':
    main()
