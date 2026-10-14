#!/usr/bin/env python3
"""Compare recompiled functions in a COFF .obj against the original efz.exe.

Every function annotated `// FUNCTION: 0xADDR` in src/ is found in the object by its
mangled name and laid over the original at ADDR.  Each relocation must resolve to
what the original instruction points at:
  * annotated functions and globals must have the annotated address,
  * imports (__imp__X) must point at the IAT slot for X,
  * string literals and other local data must have identical bytes,
  * anything else is reported as a learned address you can annotate.
A function matches when every byte outside relocations is equal and every relocation
agrees.  Mismatches are shown as an instruction diff.

Usage: tools/funcdiff.py build/main.obj [name-filter]   (original: $EFZ_DIR/efz.exe)
"""
import difflib
import os
import re
import struct
import subprocess
import sys
import tempfile

import pefile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
IMAGE_REL_I386_DIR32 = 0x6
IMAGE_REL_I386_REL32 = 0x14


# --- annotations -------------------------------------------------------------

ANNOTATION = re.compile(r'//\s*(FUNCTION|GLOBAL):\s*(0x[0-9a-fA-F]+)(?:\s+(\S+))?')
CLASS = re.compile(r'^\s*(?:class|struct)\s+(\w+)[^;]*$')
MACRO_CLASS = re.compile(r'^\s*\w+\((\w+)\s*,')


def read_annotations(src_dir):
    """Return {qualified name: (kind, address)} from FUNCTION/GLOBAL comments."""
    found = {}
    for root, _, files in os.walk(src_dir):
        for fn in sorted(files):
            if fn.endswith(('.cpp', '.h')):
                parse_file(os.path.join(root, fn), found)
    return found


def parse_file(path, found):
    lines = open(path, encoding='utf-8').read().splitlines()
    scopes = []  # (class name, brace depth at which it opened)
    depth = 0
    pending_class = None
    for i, line in enumerate(lines):
        m = CLASS.match(line)
        if m:
            pending_class = m.group(1)
        code = line.split('//')[0]
        for ch in code:
            if ch == '{':
                depth += 1
                if pending_class:
                    scopes.append((pending_class, depth))
                    pending_class = None
            elif ch == '}':
                if scopes and scopes[-1][1] == depth:
                    scopes.pop()
                depth -= 1
        m = ANNOTATION.search(line)
        if not m:
            continue
        kind, addr, explicit = m.group(1), int(m.group(2), 16), m.group(3)
        name = explicit or infer_name(kind, lines, i + 1, scopes[-1][0] if scopes else None)
        if name:
            found[name] = (kind, addr)


def infer_name(kind, lines, start, cls):
    for line in lines[start:start + 12]:
        code = line.split('//')[0].strip()
        if not code:
            continue  # comments between the annotation and the code
        m = MACRO_CLASS.match(code)
        if m and kind == 'FUNCTION' and '(' in code and code.split('(')[0].isupper():
            return f'{m.group(1)}::{m.group(1)}'  # DECLARE_X(Class, ...) declares a constructor
        if kind == 'FUNCTION':
            m = re.search(r'([\w:~]+)\s*\(', code)
        else:
            m = re.search(r'([\w:]+)\s*(?:\[[^\]]*\]\s*)*(?:=|;)', code)
        if m:
            name = m.group(1)
            return f'{cls}::{name}' if cls and '::' not in name else name
    return None


def mangled_prefixes(name):
    """Possible MSVC decorated-name prefixes for a qualified C++ name.

    An annotation can also give the decorated name itself, for compiler-generated
    functions such as `??_GCGame@@QAEPAXI@Z` (a scalar deleting destructor) or `_$E1`
    (VC 7.1's name for a TU's first dynamic initializer), and for extern "C" inlines
    such as `_fabsf`.
    """
    if name.startswith(('?', '_')):
        return [name + '\0']
    parts = name.split('::')
    if len(parts) == 1:
        return ['?' + name + '@@', '_' + name + '@', '_' + name + '\0']
    cls, member = '@'.join(reversed(parts[:-1])), parts[-1]
    if member == parts[-2]:
        return ['??0' + cls + '@@']
    if member == '~' + parts[-2]:
        return ['??1' + cls + '@@']
    return ['?' + member + '@' + cls + '@@']


def matches(symbol, prefixes):
    return any(symbol.startswith(p.rstrip('\0')) and (not p.endswith('\0') or symbol == p[:-1])
               for p in prefixes)


# --- COFF ----------------------------------------------------------------------

class Coff:
    def __init__(self, path):
        d = self.data = open(path, 'rb').read()
        _machine, nsec, _ts, symptr, nsym, optsize, _ch = struct.unpack_from('<HHIIIHH', d, 0)
        self.sections = []
        for k in range(nsec):
            o = 20 + optsize + 40 * k
            name = d[o:o + 8].rstrip(b'\0').decode()
            size, rawptr, relptr, _ln, nrel, _nln, chars = struct.unpack_from('<IIIIHHI', d, o + 16)
            relocs = [struct.unpack_from('<IIH', d, relptr + 10 * r) for r in range(nrel)]
            self.sections.append({'name': name, 'size': size, 'raw': d[rawptr:rawptr + size] if rawptr else b'',
                                  'relocs': relocs, 'chars': chars})
        strtab = symptr + 18 * nsym
        self.symbols = {}
        k = 0
        while k < nsym:
            o = symptr + 18 * k
            if d[o:o + 4] == b'\0\0\0\0':
                off = struct.unpack_from('<I', d, o + 4)[0]
                name = d[strtab + off:d.index(b'\0', strtab + off)].decode('latin-1')
            else:
                name = d[o:o + 8].rstrip(b'\0').decode('latin-1')
            value, secnum, typ, storage, naux = struct.unpack_from('<IhHBB', d, o + 8)
            self.symbols[k] = {'name': name, 'value': value, 'section': secnum, 'type': typ,
                               'storage': storage}
            k += 1 + naux

    def functions(self):
        """Yield (symbol, section index, offset, size) for every function defined here."""
        by_section = {}
        for s in self.symbols.values():
            if s['section'] > 0 and s['type'] == 0x20 and s['storage'] in (2, 3):
                by_section.setdefault(s['section'] - 1, []).append(s)
        for sec, syms in by_section.items():
            syms.sort(key=lambda s: s['value'])
            for j, s in enumerate(syms):
                end = syms[j + 1]['value'] if j + 1 < len(syms) else self.sections[sec]['size']
                yield s, sec, s['value'], end - s['value']


# --- comparison ------------------------------------------------------------------

def disasm(blob, vma):
    with tempfile.NamedTemporaryFile(suffix='.bin') as f:
        f.write(blob)
        f.flush()
        out = subprocess.run(['objdump', '-D', '-b', 'binary', '-m', 'i386', '-M', 'intel',
                              '--no-show-raw-insn', f'--adjust-vma={vma:#x}', f.name],
                             capture_output=True, text=True, check=True).stdout
    return [l.split(':', 1)[1].strip() for l in out.splitlines() if re.match(r'\s+[0-9a-f]+:', l)]


def compare(obj, sym, sec, off, size, addr, pe, image, iat, known, learned):
    base = pe.OPTIONAL_HEADER.ImageBase
    section = obj.sections[sec]
    mine = bytearray(section['raw'][off:off + size])
    orig = image[addr - base:addr - base + size]
    problems = []
    for vaddr, symidx, typ in section['relocs']:
        if not off <= vaddr < off + size:
            continue
        o = vaddr - off
        target = obj.symbols[symidx]
        addend = struct.unpack_from('<i', mine, o)[0]
        if typ == IMAGE_REL_I386_DIR32:
            actual = struct.unpack_from('<I', orig, o)[0] - addend
        elif typ == IMAGE_REL_I386_REL32:
            actual = addr + o + 4 + struct.unpack_from('<i', orig, o)[0] - addend
        else:
            problems.append(f'+{o:#x}: unsupported relocation type {typ:#x}')
            continue
        name = target['name']
        if target['section'] == sec + 1 and target['storage'] != 2:
            # A label in this function's own section (jump table, case target). Calls
            # to other functions of this object are external symbols and resolve below.
            expected = addr - off + target['value']
        else:
            expected = resolve(obj, target, actual, image, base, iat, known, learned)
        if expected is None:
            problems.append(f'+{o:#x}: {name} -> original has {actual:#x}, which does not match')
            expected = actual
        elif expected != actual:
            problems.append(f'+{o:#x}: {name} is {expected:#x}, original uses {actual:#x}')
        value = expected + addend if typ == IMAGE_REL_I386_DIR32 else expected + addend - (addr + o + 4)
        struct.pack_into('<I', mine, o, value & 0xFFFFFFFF)
    return bytes(mine), orig, problems


def resolve(obj, target, actual, image, base, iat, known, learned):
    """Address the recompiled relocation refers to, or None if it is provably different."""
    name = target['name']
    if name.startswith('__imp__'):
        want = name[7:].split('@')[0]
        return actual if iat.get(actual) == want else None
    for qual, (_kind, addr) in known.items():
        if matches(name, mangled_prefixes(qual)):
            return addr
    if target['section'] > 0 and target['storage'] == 3 or name.startswith('??_C@'):
        # Data defined in this object (string literals etc.): compare contents.
        sec = obj.sections[target['section'] - 1] if target['section'] > 0 else None
        if sec is not None:
            blob = sec['raw'][target['value']:]
            if name.startswith('??_C@'):
                blob = blob[:blob.index(b'\0') + 1]
            start = actual - base
            return actual if image[start:start + len(blob)] == blob else None
    learned.setdefault(name, set()).add(actual)
    return actual


class Original:
    """The original efz.exe, loaded once for any number of objects."""

    def __init__(self, path):
        self.pe = pefile.PE(path)
        self.image = self.pe.get_memory_mapped_image()
        self.base = self.pe.OPTIONAL_HEADER.ImageBase
        text = next(s for s in self.pe.sections if s.Name.startswith(b'.text'))
        self.text_end = self.base + text.VirtualAddress + text.Misc_VirtualSize
        self.iat = {i.address: (i.name.decode() if i.name else f'#{i.ordinal}')
                    for d in self.pe.DIRECTORY_ENTRY_IMPORT for i in d.imports}


def check(obj_path, original, known, flt=''):
    """Compare every annotated function in an object with the original.

    Yields (qualified name, address, size, ok, report lines); `learned` collects the
    addresses of symbols that are not annotated.
    """
    obj = Coff(obj_path)
    learned = {}
    for qual, (kind, addr) in sorted(known.items(), key=lambda kv: kv[1][1]):
        if kind != 'FUNCTION' or flt not in qual:
            continue
        hits = [f for f in obj.functions() if matches(f[0]['name'], mangled_prefixes(qual))]
        if not hits:
            continue
        sym, sec, off, size = hits[0]
        mine, orig, problems = compare(obj, sym, sec, off, size, addr, original.pe,
                                       original.image, original.iat, known, learned)
        image, base = original.image, original.base
        same = sum(a == b for a, b in zip(mine, orig))
        after = image[addr - base + size:addr - base + size + 3]
        ends = after[:1] == b'\xcc' or after == b'\x55\x8b\xec' or addr + size == original.text_end
        ok = mine == orig and not problems and ends
        lines = [f'{"MATCH" if ok else "DIFF "} {qual} {addr:#x}: {same}/{size} bytes'
                 f'{"" if ends else ", original function continues past the recompiled end"}']
        lines += ['   reloc ' + p for p in problems]
        if mine != orig:
            a, b = disasm(orig, addr), disasm(mine, addr)
            if os.environ.get('FUNCDIFF_MASK'):
                # hide code addresses, which all shift once the size differs
                mask = lambda l: re.sub(r'0x4[0-9a-f]{5}\b|0x[5-7][0-9a-f]{5}\b', '<code>', l)
                a, b = [mask(l) for l in a], [mask(l) for l in b]
            lines += ['   ' + l for l in difflib.unified_diff(a, b, 'original', 'recompiled', n=2,
                                                            lineterm='')]
        yield qual, addr, size, ok, lines
    check.learned = learned


def main():
    obj_path = sys.argv[1]
    flt = sys.argv[2] if len(sys.argv) > 2 else ''
    original = Original(os.path.join(os.environ.get('EFZ_DIR', '.'), 'efz.exe'))
    known = read_annotations(os.path.join(REPO, 'src'))
    total = matched = 0
    for _qual, _addr, _size, ok, lines in check(obj_path, original, known, flt):
        total += 1
        matched += ok
        print('\n'.join(lines))
    for name, addrs in sorted(check.learned.items()):
        print(f'learned: {name} -> {", ".join(hex(a) for a in sorted(addrs))}')
    print(f'{matched}/{total} functions match')
    sys.exit(0 if matched == total else 1)


if __name__ == '__main__':
    main()
