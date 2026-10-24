#!/usr/bin/env python3
"""Compare a recompiled EfzRevival object with the original binary, function by function.

tools/funcdiff.py does the comparison (every byte, every relocation); this supplies
the addresses. A function's address comes from a `// FUNCTION: 0xADDR` annotation in
revival/ or, for generated code such as EfzPackets.pb.cc, from the one place in the
range where its bytes (relocations masked) occur. Relocations then have to resolve to
those addresses, to the addresses of library functions found the same way in the
given library objects, or to identical data.

Exception-handling code (`__ehhandler$`, unwind funclets) sits apart from its function,
in `.text$x`; a relocation to it matches when the code there is the same with
relocations masked. A function also ends where the Ghidra export (FUNCTIONS_JSON)
starts the next one, since optimised functions need not be followed by padding.

Usage: tools/revdiff.py BINARY FUNCTIONS_JSON OBJ LO HI [LIB_OBJ...] [-v]
  LO-HI is the range the object's code lies in. -v prints the diffs.
"""
import json
import os
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402
from libmatch import coff_functions, find  # noqa: E402

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def placed(blob, base, path, lo, hi, starts, original):
    """{decorated name: address} for functions of an object found exactly once in lo-hi:
    at a function start, filling the function up to padding, with its imports, strings
    and data references agreeing (calls to other functions aren't checked here)."""
    ends = sorted(starts)
    obj = funcdiff.Coff(path)
    out = {}
    for sym, sec, off, size in obj.functions():
        name = sym['name']
        if size < 3 or name.startswith(('__unwindfunclet', '__ehhandler', '__catch')):
            continue
        code = obj.sections[sec]['raw'][off:off + size]
        mask = bytearray(size)
        for vaddr, _s, _t in obj.sections[sec]['relocs']:
            for b in range(vaddr - off, vaddr - off + 4):
                if 0 <= b < size:
                    mask[b] = 1
        hits = []
        for h in find(blob, code, mask):
            a = base + h
            if not lo <= a < hi or a not in starts:
                continue
            nxt = next((e for e in ends if e > a), base + len(blob))
            tail = blob[h + size:nxt - base]
            if a + size > nxt or tail.strip(b'\xcc') != b'':
                continue
            _m, _o, problems = funcdiff.compare(obj, sym, sec, off, size, a, original.pe,
                                                original.image, original.iat, {}, {})
            if not problems:
                hits.append(a)
        if len(hits) == 1:
            out[name] = hits[0]
    return out


def data_size(coff, target):
    """Bytes from a data symbol to the next symbol in its section (or the section end)."""
    sec = target['section']
    after = sorted(s['value'] for s in coff.symbols.values()
                   if s['section'] == sec and s['value'] > target['value'])
    return (after[0] if after else coff.sections[sec - 1]['size']) - target['value']


def code_resolver(obj, blob, base):
    """Wrap funcdiff.resolve so that relocations to this object's own code (EH handlers
    and funclets) are checked by comparing code, and relocations to its data (tables of
    pointers, vtables) by comparing contents, relocations masked in both."""
    bodies = {name: (code, mask) for name, code, mask in coff_functions(open(obj, 'rb').read())}
    plain = funcdiff.resolve

    def resolve(coff, target, actual, image, imgbase, iat, known, learned):
        body = bodies.get(target['name'])
        if body and target['name'].startswith(('__ehhandler$', '__unwindfunclet$', '__catch$')):
            code, mask = body
            at = actual - base
            ok = 0 <= at and all(mask[i] or blob[at + i] == code[i] for i in range(len(code)))
            return actual if ok else None
        sec = coff.sections[target['section'] - 1] if target['section'] > 0 else None
        if (sec is not None and target['storage'] in (2, 3) and sec['relocs']
                and not sec['chars'] & 0x20 and not target['name'].startswith('??_C@')):
            n = data_size(coff, target)
            mine = sec['raw'][target['value']:target['value'] + n] if sec['raw'] else bytes(n)
            masked = {v - target['value'] + i for v, _s, _t in sec['relocs'] for i in range(4)}
            theirs = image[actual - imgbase:actual - imgbase + n]
            ok = all(i in masked or mine[i] == theirs[i] for i in range(n))
            return actual if ok else None
        return plain(coff, target, actual, image, imgbase, iat, known, learned)
    return resolve


def main():
    args = [a for a in sys.argv[1:] if a != '-v']
    verbose = '-v' in sys.argv
    exe, fjson, obj, lo, hi = args[0], args[1], args[2], int(args[3], 16), int(args[4], 16)
    libs = args[5:]
    original = funcdiff.Original(exe)
    text = next(s for s in original.pe.sections if s.Name.startswith(b'.text'))
    base = original.base + text.VirtualAddress
    blob = text.get_data()[:text.Misc_VirtualSize]
    starts = {x['entry'] for x in json.load(open(fjson))}
    funcdiff.resolve = code_resolver(obj, blob, base)

    # The object's own copies of inline functions come first: a library compiled with
    # other options (inlining) has different code under the same names.
    known = funcdiff.read_annotations(os.path.join(REPO, 'revival'))
    for name, addr in placed(blob, base, obj, lo, hi, starts, original).items():
        known.setdefault(name, ('FUNCTION', addr))
    own = {name for name, _c, _m in coff_functions(open(obj, 'rb').read())}
    for lib in libs:
        for name, addr in placed(blob, base, lib, base, base + len(blob), starts, original).items():
            if name not in own:
                known.setdefault(name, ('FUNCTION', addr))

    total = matched = 0
    for qual, addr, size, ok, lines in funcdiff.check(obj, original, known):
        if not lo <= addr < hi:
            continue
        if not ok and lines[0].endswith('continues past the recompiled end') and addr + size in starts:
            # followed directly by the next function rather than by padding
            lines[0] = lines[0].rsplit(',', 1)[0]
            ok = len(lines) == 1
            if ok:
                lines[0] = 'MATCH' + lines[0][5:]
        total += 1
        matched += ok
        if verbose or not ok:
            print('\n'.join(lines if verbose else lines[:1] + [l for l in lines[1:] if l.startswith('   reloc')]))
    for name, addrs in sorted(funcdiff.check.learned.items()):
        if verbose:
            print(f'learned: {name} -> {", ".join(hex(a) for a in sorted(addrs))}')
    print(f'{os.path.basename(obj)}: {matched}/{total} functions match')


if __name__ == '__main__':
    main()
