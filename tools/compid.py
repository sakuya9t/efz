#!/usr/bin/env python3
"""Print the @comp.id (tool product ID and build) of every COFF object in .lib/.obj files.

The linker builds the Rich header from these stamps, so they identify which SDK or CRT
release supplied each object that ended up in efz.exe.

Usage: tools/compid.py file.lib [file.obj ...]
"""
import struct
import sys

from peinfo import PRODIDS


def coff_compid(data):
    """Return (prodid, build) from a COFF object's @comp.id symbol, or None."""
    if len(data) < 20:
        return None
    if data[:4] == b'\0\0\xff\xff':
        # A /GL object holds compiler IL, not COFF; its stamp is the front end's
        # (Utc1700_CPP), which the linker records as the LTCG product (Utc1700_LTCG_CPP).
        at = data.find(b'@comp.id')
        if at < 0:
            return None
        value = struct.unpack_from('<I', data, at + 8)[0]
        return value >> 16, value & 0xFFFF
    machine, _nsec, _ts, symtab, nsyms = struct.unpack_from('<HHIII', data, 0)
    if machine != 0x14C or not symtab:
        return None
    for i in range(nsyms):
        off = symtab + i * 18
        if off + 18 > len(data):
            break
        if data[off:off + 8] == b'@comp.id':
            value = struct.unpack_from('<I', data, off + 8)[0]
            return value >> 16, value & 0xFFFF
    return None


def members(data):
    """Yield (name, bytes) for each member of an ar-format .lib."""
    off = 8
    longnames = b''
    while off + 60 <= len(data):
        header = data[off:off + 60]
        name = header[:16].decode('latin-1').rstrip()
        size = int(header[48:58])
        body = data[off + 60:off + 60 + size]
        if name == '//':
            longnames = body
        elif name.startswith('/') and name[1:].isdigit():
            start = int(name[1:])
            name = longnames[start:longnames.index(b'\0', start)].decode('latin-1')
        if name not in ('/', '//'):
            yield name, body
        off += 60 + size + (size & 1)


def main():
    for path in sys.argv[1:]:
        data = open(path, 'rb').read()
        items = members(data) if data[:8] == b'!<arch>\n' else [(path, data)]
        for name, body in items:
            stamp = coff_compid(body)
            if stamp:
                prodid, build = stamp
                print(f'{path}: {name:50} {PRODIDS.get(prodid, f"prodid {prodid:#06x}"):18} {build}')


if __name__ == '__main__':
    main()
