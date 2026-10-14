#!/usr/bin/env python3
"""Derive a stand-in for the user32.lib efz.exe was linked with from the February 2003
Platform SDK's.

efz.exe's import hints for user32.dll match the February 2003 Platform SDK's
user32.lib up to PostQuitMessage and are one higher from RegisterClassA on, and its
Rich header shows two import objects from a library built by linker 7.10.2067. That fits
Visual Studio .NET 2003's own copy of user32.lib, which isn't freely available: it lists
one more user32.dll export somewhere between those two names. This script copies the
February 2003 library, raises the hint of every export after PostQuitMessage by one,
and restamps the library's objects as built by linker 2067. Nothing else changes.

Usage: user32lib.py FEB2003-User32.Lib OUT.lib
"""
import struct
import sys

LAST_UNCHANGED = 515                    # PostQuitMessage's hint in both libraries
IMPLIB_2179 = (0x5d << 16) | 2179       # Implib710, linker build 2179
IMPLIB_2067 = (0x5d << 16) | 2067


def main():
    data = bytearray(open(sys.argv[1], 'rb').read())
    assert data[:8] == b'!<arch>\n'
    off, hints, stamps = 8, 0, 0
    while off + 60 <= len(data):
        size = int(data[off + 48:off + 58])
        body = off + 60
        if data[body:body + 4] == b'\0\0\xff\xff':
            # short import object: sig1, sig2, version, machine, timestamp, size, hint
            hint = struct.unpack_from('<H', data, body + 16)[0]
            if hint > LAST_UNCHANGED:
                struct.pack_into('<H', data, body + 16, hint + 1)
                hints += 1
        elif struct.unpack_from('<H', data, body)[0] == 0x14c:
            symtab, nsyms = struct.unpack_from('<II', data, body + 8)
            for i in range(nsyms):
                sym = body + symtab + 18 * i
                if data[sym:sym + 8] == b'@comp.id':
                    assert struct.unpack_from('<I', data, sym + 8)[0] == IMPLIB_2179
                    struct.pack_into('<I', data, sym + 8, IMPLIB_2067)
                    stamps += 1
        off = body + size + (size & 1)
    assert hints and stamps == 3, (hints, stamps)
    open(sys.argv[2], 'wb').write(data)


if __name__ == '__main__':
    main()
