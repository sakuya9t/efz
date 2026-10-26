#!/usr/bin/env python3
"""Place the functions of compiled objects in an original binary, following references.

For objects compiled without /GL, a function's code doesn't depend on where it is used
(the launcher is built with /Ob0, so nothing is even inlined), so compiling headers
with the original's options and finding the results names the library and template
code in the original.  This is how probe files name what the developer's code
instantiated, and how recovered sources are placed before they are annotated.

A function is placed when its bytes (relocations masked) occur at exactly one function
start of the original and the code that follows is padding or the next function.  From
every placed function, and from every placed table of pointers (vtables), each
relocation then gives the address of its target: when that target's own bytes are
found there, it is placed too, even if its bytes occur elsewhere as well (a `ret 4`
is placed from its caller).  Imports must use the same IAT slot and string literals
must have the same contents, or the placement is dropped.

Several names on one address are expected: the link folded identical functions
(/OPT:ICF).

Usage: tools/revmatch.py BINARY FUNCTIONS_JSON OBJ... [--out NAMES.json] [--range LO HI]
       [--uncovered] [-v]
  --out writes {decorated name: address}; --range limits the report of unplaced
  original functions (--uncovered lists them) to LO-HI; -v lists names placed twice.
  An object's names take precedence over later objects', so recovered objects go
  before probes.
"""
import collections
import json
import os
import struct
import sys

import pefile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from funcdiff import Coff  # noqa: E402
from libmatch import anchor  # noqa: E402
from rtti import vtables  # noqa: E402

MIN_SIZE = 6


class Binary:
    def __init__(self, path, fjson):
        self.pe = pefile.PE(path)
        self.image = self.pe.get_memory_mapped_image()
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        text = next(s for s in self.pe.sections if s.Name.startswith(b'.text'))
        self.tlo = self.base + text.VirtualAddress
        self.thi = self.tlo + text.Misc_VirtualSize
        self.text = self.image[text.VirtualAddress:text.VirtualAddress + text.Misc_VirtualSize]
        self.iat = {}
        for d in getattr(self.pe, 'DIRECTORY_ENTRY_IMPORT', []):
            for i in d.imports:
                self.iat[i.address] = i.name.decode() if i.name else f'#{i.ordinal}'
        funcs = [f for f in json.load(open(fjson)) if not f['external']]
        starts = {f['entry'] for f in funcs}
        # Ghidra misses some: code after int3 padding at a 16-byte boundary starts one
        # (two int3s: one can be a displacement, as in lea eax,[ebp-0x34])
        t = self.text
        for o in range(16 - self.tlo % 16, len(t), 16):
            if t[o - 2:o] == b'\xcc\xcc' and t[o] != 0xCC:
                starts.add(self.tlo + o)
        self.starts = sorted(starts)
        self.startset = set(self.starts)
        self.funcs = {f['entry']: f for f in funcs}

    def byte(self, addr, n):
        return self.image[addr - self.base:addr - self.base + n]

    def next_start(self, addr):
        import bisect
        i = bisect.bisect_right(self.starts, addr)
        return self.starts[i] if i < len(self.starts) else self.thi


class Unit:
    """A compiled object's functions and data, with their relocations."""

    def __init__(self, path):
        self.path = path
        self.coff = c = Coff(path)
        self.items = {}  # name -> (kind, section index, offset, size)
        bysec = collections.defaultdict(list)
        for s in c.symbols.values():
            if s['section'] > 0 and s['storage'] in (2, 3) and not s['name'].startswith('$'):
                bysec[s['section'] - 1].append(s)
        for sec, syms in bysec.items():
            info = c.sections[sec]
            code = bool(info['chars'] & 0x20)
            if not info['raw']:
                continue
            syms.sort(key=lambda s: s['value'])
            for j, s in enumerate(syms):
                end = syms[j + 1]['value'] if j + 1 < len(syms) else info['size']
                if code and s['type'] != 0x20:
                    continue
                if not code and s['storage'] != 2 and not s['name'].startswith('??_'):
                    continue
                self.items.setdefault(s['name'], ('code' if code else 'data', sec, s['value'],
                                                  end - s['value']))
        # weak externals (a vtable's ??_E vector deleting destructor is an alias of ??_G)
        self.alias = {}
        d = c.data
        _m, _n, _t, symptr, nsym, _o, _c = struct.unpack_from('<HHIIIHH', d, 0)
        for k, sym in c.symbols.items():
            if sym['storage'] == 105:
                tag = struct.unpack_from('<I', d, symptr + 18 * (k + 1))[0]
                if tag in c.symbols:
                    self.alias[sym['name']] = c.symbols[tag]['name']

    def vtable_key(self, name):
        """(type descriptor name, offset) of a vtable item, from its complete object locator,
        the relocation in the word before it."""
        _kind, sec, off, _size = self.items[name]
        info = self.coff.sections[sec]
        col = next((self.coff.symbols[si] for v, si, _t in info['relocs'] if v == off - 4), None)
        if not col or not col['name'].startswith('??_R4') or col['section'] <= 0:
            return None
        cinfo = self.coff.sections[col['section'] - 1]
        offset = struct.unpack_from('<I', cinfo['raw'], col['value'] + 4)[0]
        td = next((self.coff.symbols[si]['name'] for v, si, _t in cinfo['relocs']
                   if v == col['value'] + 12), '')
        if not td.startswith('??_R0'):
            return None
        return '.' + td[5:-2], offset

    def body(self, name):
        kind, sec, off, size = self.items[name]
        info = self.coff.sections[sec]
        code = info['raw'][off:off + size]
        relocs = [(v - off, self.coff.symbols[si], t) for v, si, t in info['relocs']
                  if off <= v < off + size]
        mask = bytearray(size)
        for o, _s, _t in relocs:
            for b in range(o, min(o + 4, size)):
                mask[b] = 1
        return kind, code, mask, relocs


def masked_equal(binary, addr, code, mask):
    orig = binary.byte(addr, len(code))
    return len(orig) == len(code) and all(mask[i] or orig[i] == code[i] for i in range(len(code)))


def fits(binary, addr, size, kind):
    """The function at addr ends where the recompiled one does: padding follows it up to
    the next 16-byte boundary (a function at the boundary may be one Ghidra missed)."""
    if kind != 'code':
        return True
    end = addr + size
    if end in binary.startset or end >= binary.thi:
        return True
    return binary.byte(end, -end % 16).strip(b'\xcc') == b''


class Matcher:
    def __init__(self, binary, units):
        self.b = binary
        self.units = units
        self.placed = {}   # name -> address
        self.where = {}    # name -> unit (first defining)
        for u in units:
            for name in u.items:
                self.where.setdefault(name, u)
        self.cache = {}
        self.alias = {}
        for u in units:
            for k, v in u.alias.items():
                self.alias.setdefault(k, v)

    def get(self, name):
        if name not in self.cache:
            self.cache[name] = self.where[name].body(name)
        return self.cache[name]

    def targets(self, name, addr):
        """(target name, target address) for each relocation of a placed item; None for a
        relocation that contradicts the original (wrong import, other string)."""
        kind, code, mask, relocs = self.get(name)
        out = []
        b = self.b
        for o, sym, typ in relocs:
            raw = b.byte(addr + o, 4)
            if len(raw) < 4:
                return None
            addend = struct.unpack_from('<i', code, o)[0]
            v = struct.unpack_from('<I', raw)[0]
            if typ == 0x6:
                actual = v - addend
            elif typ == 0x14:
                actual = (addr + o + 4 + struct.unpack_from('<i', raw)[0] - addend) & 0xffffffff
            else:
                continue
            tname = sym['name']
            tname = self.alias.get(tname, tname)
            if tname.startswith('__imp_'):
                want = tname[6:].lstrip('_').split('@')[0]
                got = b.iat.get(actual)
                if got is None or (got != want and got.lstrip('_') != want):
                    return None
                continue
            if tname.startswith('??_C@'):
                u = self.where.get(tname)
                if u:
                    _k, s, _m, _r = self.get(tname)
                    s = s[:s.index(b'\0') + 1] if b'\0' in s else s
                    if tname.startswith('??_C@_1'):
                        s = self.get(tname)[1]
                    if b.byte(actual, len(s)) != s:
                        return None
                continue
            out.append((tname, actual))
        return out

    def accept(self, name, addr):
        kind, code, mask, _r = self.get(name)
        if not masked_equal(self.b, addr, code, mask) or not fits(self.b, addr, len(code), kind):
            return False
        targets = self.targets(name, addr)
        if targets is None:
            return False
        # what is placed already must agree
        return all(self.placed.get(t, a) == a for t, a in targets)

    def candidates(self, name):
        """Function starts where a function's bytes occur, at most 16."""
        _k, code, mask, _r = self.get(name)
        off, key = anchor(code, mask)
        if len(key) < 6:
            return None
        b, hits = self.b, []
        at = b.text.find(key)
        while at >= 0 and len(hits) < 16:
            a = b.tlo + at - off
            if a in b.startset and self.accept(name, a):
                hits.append(a)
            at = b.text.find(key, at + 1)
        return hits

    def propagate(self, queue):
        while queue:
            name, addr = queue.popleft()
            if name in self.placed:
                if self.placed[name] != addr:
                    self.conflicts[name].update({self.placed[name], addr})
                continue
            self.placed[name] = addr
            for tname, taddr in self.targets(name, addr) or []:
                if tname in self.placed or tname not in self.where:
                    continue
                if self.accept(tname, taddr):
                    queue.append((tname, taddr))

    def run(self):
        b = self.b
        self.conflicts = collections.defaultdict(set)
        queue = collections.deque()
        # vtables, through the RTTI both sides have
        rows = collections.defaultdict(list)
        for td, offset, vt, _slots in vtables(b.pe):
            rows[td, offset].append(vt)
        for name, u in self.where.items():
            if name.startswith('??_7') and u.items[name][0] == 'data':
                key = u.vtable_key(name)
                if key and len(rows.get(key, ())) == 1:
                    queue.append((name, rows[key][0]))
        # functions whose bytes occur at one function start only
        cands = {}
        for name, u in self.where.items():
            kind, _sec, _off, size = u.items[name]
            if kind != 'code' or size < MIN_SIZE:
                continue
            if name.startswith(('__unwindfunclet$', '__ehhandler$', '__catch$', '__tryend$')):
                continue
            hits = self.candidates(name)
            if hits is not None:
                cands[name] = hits
            if hits and len(hits) == 1:
                queue.append((name, hits[0]))
        self.propagate(queue)
        # then repeatedly, with what is placed constraining the rest: a function with one
        # candidate left, or one that no other name took
        while True:
            taken = set(self.placed.values())
            for name in cands:
                if name in self.placed:
                    continue
                hits = self.candidates(name)
                free = [a for a in hits if a not in taken]
                if len(hits) == 1:
                    queue.append((name, hits[0]))
                elif len(free) == 1:
                    queue.append((name, free[0]))
            if not queue:
                break
            self.propagate(queue)
        return self.placed


def main():
    args = sys.argv[1:]
    out = rng = None
    uncovered = '--uncovered' in args
    args = [a for a in args if a not in ('--uncovered', '-v')]
    if '--out' in args:
        i = args.index('--out')
        out = args[i + 1]
        del args[i:i + 2]
    if '--range' in args:
        i = args.index('--range')
        rng = int(args[i + 1], 16), int(args[i + 2], 16)
        del args[i:i + 3]
    binary = Binary(args[0], args[1])
    units = [Unit(p) for p in args[2:]]
    m = Matcher(binary, units)
    placed = m.run()
    for u in units:
        names = [n for n, it in u.items.items() if it[0] == 'code' and m.where[n] is u]
        n = sum(1 for x in names if x in placed)
        print(f'{os.path.basename(u.path)}: {n}/{len(names)} functions placed')
    for name, addrs in sorted(m.conflicts.items()):
        if '-v' in sys.argv:
            print(f'conflict: {name} at {", ".join(hex(a) for a in sorted(addrs))}')
    if m.conflicts:
        print(f'{len(m.conflicts)} names placed at two addresses (-v lists them)')
    if rng:
        lo, hi = rng
        # a placed function covers every start inside it (Ghidra makes catch blocks and
        # the code after them functions of their own)
        def span(n, a):
            kind, sec, off, _size = m.where[n].items[n]
            return a, a + m.where[n].coff.sections[sec]['size'] - off  # to its section's end
        spans = sorted(span(n, a) for n, a in placed.items() if m.where[n].items[n][0] == 'code')
        import bisect
        ends = [s for s, _e in spans]
        def inside(a):
            i = bisect.bisect_right(ends, a) - 1
            return i >= 0 and spans[i][0] <= a < spans[i][1]
        todo = [a for a in binary.starts if lo <= a < hi and not inside(a)]
        size = lambda a: binary.next_start(a) - a
        print(f'{len(todo)} original functions in {lo:#x}-{hi:#x} not placed, '
              f'{sum(size(a) for a in todo)} bytes')
        if uncovered:
            for a in todo:
                print(f'  {a:#x} {size(a)}')
    if out:
        json.dump({k: hex(v) for k, v in sorted(placed.items(), key=lambda kv: kv[1])},
                  open(out, 'w'), indent=0)


if __name__ == '__main__':
    main()
