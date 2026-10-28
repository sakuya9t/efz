#!/usr/bin/env python3
"""Compare a linked rebuild of an EfzRevival DLL with the original, function by function.

EfzRevival.dll and DDRAW.dll were built with /GL: their code is generated at link
time, so it can only be compared after linking. This lays each annotated function of
the rebuild (its address from the link map) over the original's (from its
`// FUNCTION: 0xADDR` annotation) and compares them instruction by instruction:
  * opcodes and non-address operands must be equal;
  * an address operand must name the same thing: through the map, the rebuild's
    address gives a symbol (plus an offset), and the symbol must be at the original's
    address. Annotated symbols have their annotated address; others are learned from
    their first use and must then stay consistent; string literals must have the same
    contents; imports must use the same IAT slot.
Functions end at the next symbol (rebuild) or the next function start (original,
from the Ghidra export), padding removed.

Usage: tools/revltcg.py ORIGINAL BUILT MAP SRC_DIR FUNCTIONS_JSON [-v] [--only F,...]
                        [NAME_FILTER]
  -v prints instruction diffs and the learned addresses; --only reports just the
  functions annotated in those source files (every annotation still names addresses).
"""
import bisect
import difflib
import json
import os
import re
import subprocess
import sys

import pefile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402

ADDR = re.compile(r'0x([0-9a-f]{6,8})\b')


class Image:
    def __init__(self, path):
        self.path = path
        self.pe = pefile.PE(path)
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        self.image = self.pe.get_memory_mapped_image()
        self.hi = self.base + self.pe.OPTIONAL_HEADER.SizeOfImage
        self.iat = {}
        for d in getattr(self.pe, 'DIRECTORY_ENTRY_IMPORT', []):
            for i in d.imports:
                self.iat[i.address] = (d.dll.decode().lower(),
                                       i.name.decode() if i.name else f'#{i.ordinal}')
        text = next(s for s in self.pe.sections if s.Name.startswith(b'.text'))
        self.tlo = self.base + text.VirtualAddress
        self.thi = self.tlo + text.Misc_VirtualSize
        self._dis = None

    def disasm(self):
        """{address: (next address, instruction text)} for all of .text, cached."""
        if self._dis is None:
            out = subprocess.run(['objdump', '-d', '-M', 'intel', '--no-show-raw-insn',
                                  f'--start-address={self.tlo:#x}', f'--stop-address={self.thi:#x}',
                                  self.path], capture_output=True, text=True, check=True).stdout
            rows = []
            for line in out.splitlines():
                m = re.match(r'\s*([0-9a-f]+):\t(.*)', line)
                if m:
                    rows.append((int(m[1], 16), m[2].strip()))
            self._dis = {}
            for (a, ins), nxt in zip(rows, rows[1:] + [(self.thi, '')]):
                self._dis[a] = (nxt[0], ins)
            self.addrs = sorted(self._dis)
        return self._dis

    def instructions(self, lo, hi):
        d = self.disasm()
        i = bisect.bisect_left(self.addrs, lo)
        out = []
        while i < len(self.addrs) and self.addrs[i] < hi:
            a = self.addrs[i]
            out.append((a, d[a][1]))
            i += 1
        # a switch's jump table follows its function; drop it.
        tables = [int(t, 16) for _, ins in out
                  for t in re.findall(r'jmp\s+DWORD PTR \[e\w\w\*4\+0x([0-9a-f]+)\]', ins)]
        tables = [t for t in tables if lo < t < hi]
        if tables:
            out = [(a, ins) for a, ins in out if a < min(tables)]
        while out and out[-1][1] in ('int3', 'nop', 'xchg   ax,ax', 'mov    edi,edi', 'lea    esi,[esi+0x0]', 'lea    ecx,[ecx+0x0]', 'lea    ebx,[ebx+0x0]', 'lea    esp,[esp+0x0]'):
            out.pop()
        return out

    def cstring(self, a, wide):
        o = a - self.base
        if not 0 <= o < len(self.image):
            return None
        b = self.image[o:o + 512]
        if wide:
            end = next((i for i in range(0, len(b) - 1, 2) if b[i:i + 2] == b'\0\0'), None)
            return None if end is None else b[:end + 2]
        end = b.find(b'\0')
        return None if end < 0 else b[:end + 1]


def read_map(path):
    """[(address, name)] of every symbol in a link map, sorted; and {name: address}."""
    syms = []
    for line in open(path, encoding='latin-1'):
        m = re.match(r'\s+[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s', line)
        if m:
            syms.append((int(m[2], 16), m[1]))
    syms.sort()
    byname = {}
    for a, n in syms:
        byname.setdefault(n, a)
    return syms, byname


class Matcher:
    def __init__(self, orig, built, syms, annotated):
        self.orig, self.built = orig, built
        self.syms = syms
        self.starts = [a for a, _ in syms]
        self.known = dict(annotated)   # symbol -> original address
        self.learned = {}
        # identical functions folded by /OPT:ICF share an address; any
        # of their names may be the one meant.
        self.names_at = {}
        for a, n in syms:
            self.names_at.setdefault(a, []).append(n)
        # static functions of one name in several objects (each its own copy): an
        # annotation names the first; the others are learned by address.
        self.first, addresses = {}, {}
        for a, n in syms:
            self.first.setdefault(n, a)
            addresses.setdefault(n, set()).add(a)
        self.copies = {n for n, s in addresses.items() if len(s) > 1}

    def key(self, name, a):
        """known/learned key of the symbol name at our address a"""
        if name in self.copies and a != self.first[name]:
            return f'{name}@{a:#x}'
        return name

    def symbol_at(self, a):
        i = bisect.bisect_right(self.starts, a) - 1
        if i < 0:
            return None, 0
        return self.syms[i][1], a - self.syms[i][0]

    def operand(self, ours, theirs):
        """Is our address operand `ours` the same thing as the original's `theirs`?"""
        b, o = self.built, self.orig
        if ours in b.iat or theirs in o.iat:
            return b.iat.get(ours) == o.iat.get(theirs) and ours in b.iat, 'import'
        name, off = self.symbol_at(ours)
        if name is None:
            return ours == theirs, 'absolute'
        if name.startswith('??_C@'):
            wide = name.startswith('??_C@_1')
            s = b.cstring(ours, wide)
            return s is not None and s == o.cstring(theirs, wide), name
        names = self.names_at.get(ours - off, [name])
        keys = [self.key(n, ours - off) for n in names]
        for n in keys:
            want = self.known.get(n, self.learned.get(n))
            if want is not None and want + off == theirs:
                return True, n
        for n in keys:
            if n not in self.known and n not in self.learned:
                self.learned[n] = theirs - off
                return True, n
        return False, name

    def compare(self, ours_lo, ours_hi, theirs_lo, theirs_hi):
        a = self.built.instructions(ours_lo, ours_hi)
        b = self.orig.instructions(theirs_lo, theirs_hi)
        ok = len(a) == len(b)
        lines_a, lines_b = [], []
        for i in range(max(len(a), len(b))):
            ia = a[i][1] if i < len(a) else ''
            ib = b[i][1] if i < len(b) else ''
            na, nb = ADDR.sub('<a>', ia), ADDR.sub('<a>', ib)
            same = na == nb
            if same:
                va = [int(x, 16) for x in ADDR.findall(ia)]
                vb = [int(x, 16) for x in ADDR.findall(ib)]
                for x, y in zip(va, vb):
                    inside_ours = self.built.base <= x < self.built.hi
                    inside_theirs = self.orig.base <= y < self.orig.hi
                    if inside_ours != inside_theirs:
                        same = False
                    elif inside_ours:
                        good, _what = self.operand(x, y)
                        if not good:
                            same = False
                            nb += f'   ; differs: {self.symbol_at(x)[0]}'
                    elif x != y:
                        same = False
            ok &= same
            lines_a.append(na if same else ia)
            lines_b.append(nb if same else ib)
        return ok, len(b), sum(1 for x, y in zip(lines_a, lines_b) if x == y), lines_b, lines_a


def main():
    argv = sys.argv[1:]
    only = None
    if '--only' in argv:
        i = argv.index('--only')
        only = {os.path.basename(f) for f in argv[i + 1].split(',') if f}
        del argv[i:i + 2]
    args = [a for a in argv if a != '-v']
    verbose = '-v' in argv
    orig_path, built_path, map_path, src_dir, fjson = args[:5]
    flt = args[5] if len(args) > 5 else ''
    orig, built = Image(orig_path), Image(built_path)
    syms, byname = read_map(map_path)
    starts = {f['entry'] for f in json.load(open(fjson)) if not f['external']}
    # Ghidra misses functions only reached through vtables: code after int3 padding at a
    # 16-byte boundary starts one too (two int3s: one can be a displacement)
    t = orig.image[orig.tlo - orig.base:orig.thi - orig.base]
    for o in range(16 - orig.tlo % 16, len(t), 16):
        if t[o - 2:o] == b'\xcc\xcc' and t[o] != 0xCC:
            starts.add(orig.tlo + o)
    starts = sorted(starts)

    annotated = {}
    want = []  # (qualified name, decorated name, original address)
    reported = None
    if only is not None:
        reported = {}
        for root, _, files in os.walk(src_dir):
            for fn in files:
                if fn in only:
                    funcdiff.parse_file(os.path.join(root, fn), reported)
    for qual, (kind, addr) in funcdiff.read_annotations(src_dir).items():
        prefixes = funcdiff.mangled_prefixes(qual)
        hits = [n for n in byname if funcdiff.matches(n, prefixes)]
        for n in hits:
            annotated[n] = addr
        if kind == 'FUNCTION' and (reported is None or qual in reported):
            want.append((qual, hits, addr))

    # annotated addresses also end the original's previous function
    # (Ghidra misses functions only reached through vtables).
    starts = sorted(set(starts) | {a for _, (k, a) in funcdiff.read_annotations(src_dir).items() if k == 'FUNCTION'})
    # Ghidra also splits a function at a block it reaches only by a jump (a merged tail):
    # when the original's range is shorter than ours, the comparison is tried again over
    # our length, up to the next annotated function at most.
    annotated_starts = sorted({a for _, (k, a) in funcdiff.read_annotations(src_dir).items()
                               if k == 'FUNCTION'})

    def compare_split(matcher, ours, ours_end, addr, theirs_end):
        result = matcher.compare(ours, ours_end, addr, theirs_end)
        longer = addr + (ours_end - ours)
        if result[0] or longer <= theirs_end:
            return result
        k = bisect.bisect_right(annotated_starts, addr)
        if k < len(annotated_starts) and annotated_starts[k] < longer:
            return result
        saved = dict(matcher.learned)
        retry = matcher.compare(ours, ours_end, addr, longer)
        if retry[0]:
            return retry
        matcher.learned.clear()
        matcher.learned.update(saved)
        return result

    text_syms = [(a, n) for a, n in syms if built.tlo <= a < built.thi]
    tstarts = [a for a, _ in text_syms]
    # a first pass over every annotated function learns addresses only
    # from the functions that match, so that a misaligned diff can't teach a wrong one.
    every = []
    for qual, (kind, addr) in funcdiff.read_annotations(src_dir).items():
        if kind == 'FUNCTION':
            hits = [n for n in byname if funcdiff.matches(n, funcdiff.mangled_prefixes(qual))]
            if hits:
                every.append((hits, addr))
    trusted = dict(annotated)
    for _round in range(3):
        for hits, addr in sorted(every, key=lambda w: w[1]):
            probe = Matcher(orig, built, syms, trusted)
            ours = byname[hits[0]]
            i = bisect.bisect_right(tstarts, ours)
            ours_end = tstarts[i] if i < len(tstarts) else built.thi
            j = bisect.bisect_right(starts, addr)
            theirs_end = starts[j] if j < len(starts) else orig.thi
            if compare_split(probe, ours, ours_end, addr, theirs_end)[0]:
                trusted.update(probe.learned)
    m = Matcher(orig, built, syms, trusted)
    total = matched = 0
    for qual, hits, addr in sorted(want, key=lambda w: w[2]):
        if flt not in qual:
            continue
        total += 1
        if not hits:
            print(f'MISSING {qual} {addr:#x}: not in the map (inlined everywhere, or not compiled)')
            continue
        ours = byname[hits[0]]
        i = bisect.bisect_right(tstarts, ours)
        ours_end = tstarts[i] if i < len(tstarts) else built.thi
        j = bisect.bisect_right(starts, addr)
        theirs_end = starts[j] if j < len(starts) else orig.thi
        ok, n, same, lb, la = compare_split(m, ours, ours_end, addr, theirs_end)
        matched += ok
        print(f'{"MATCH" if ok else "DIFF "} {qual} {addr:#x}: {same}/{n} instructions')
        if verbose and not ok:
            for line in difflib.unified_diff(lb, la, 'original', 'rebuilt', n=2, lineterm=''):
                print('   ' + line)
    if verbose:
        for name, a in sorted(m.learned.items(), key=lambda kv: kv[1]):
            print(f'learned: {name} -> {a:#x}')
    print(f'{matched}/{total} functions match')
    sys.exit(0 if matched == total else 1)


if __name__ == '__main__':
    main()
