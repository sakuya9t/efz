#!/usr/bin/env python3
"""List the vtables of an MSVC binary through its RTTI.

Each class with RTTI has a type descriptor (`.?AV<name>@@`); a complete object locator
points at it, and the word before each of the class's vtables points at the locator.
Prints every vtable with its class (and its offset in the complete object, for
secondary bases) and the functions in it.

Usage: tools/rtti.py BINARY [class-filter]
"""
import struct
import sys

import pefile


def main():
    pe = pefile.PE(sys.argv[1])
    flt = sys.argv[2] if len(sys.argv) > 2 else ''
    base = pe.OPTIONAL_HEADER.ImageBase
    image = pe.get_memory_mapped_image()
    text = next(s for s in pe.sections if s.Name.startswith(b'.text'))
    tlo, thi = base + text.VirtualAddress, base + text.VirtualAddress + text.Misc_VirtualSize
    data = [(base + s.VirtualAddress, base + s.VirtualAddress + s.Misc_VirtualSize)
            for s in pe.sections if s.Name.startswith((b'.rdata', b'.data'))]

    def u32(va):
        return struct.unpack_from('<I', image, va - base)[0]

    def in_data(va):
        return any(lo <= va < hi for lo, hi in data)

    # type descriptors: vftable ptr, spare, then the name
    tds = {}
    at = image.find(b'.?A')
    while at >= 0:
        end = image.index(b'\0', at)
        tds[base + at - 8] = image[at:end].decode('latin-1')
        at = image.find(b'.?A', end)
    # complete object locators: signature 0, offset, cd offset, pTypeDescriptor, pClassDescriptor
    cols = {}
    for lo, hi in data:
        for va in range(lo, hi - 20, 4):
            if u32(va) == 0 and u32(va + 12) in tds and in_data(u32(va + 16)):
                cols[va] = (tds[u32(va + 12)], u32(va + 4))
    rows = []
    for lo, hi in data:
        for va in range(lo, hi - 4, 4):
            col = u32(va)
            if col in cols:
                funcs, p = [], va + 4
                while p < hi and tlo <= u32(p) < thi:
                    funcs.append(u32(p))
                    p += 4
                if funcs:
                    rows.append((cols[col][0], cols[col][1], va + 4, funcs))
    for name, offset, vt, funcs in sorted(rows, key=lambda r: r[2]):
        if flt in name:
            off = f' (at +{offset:#x})' if offset else ''
            print(f'{vt:#x} {name}{off}: {" ".join(f"{f:#x}" for f in funcs)}')


if __name__ == '__main__':
    main()
