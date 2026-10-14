#!/usr/bin/env python3
"""Stamp objects as built by Visual C++ .NET 2003 Standard Edition.

efz.exe was compiled by the Standard Edition, whose compiler stamps Utc1310_CPP_Std into
each object's @comp.id (and from there into the exe's Rich header). The Visual C++
Toolkit 2003 used here is the same build, 13.10.3077, and generates the same code at
/Od, but stamps Utc1310_CPP. This rewrites that stamp in place.

Usage: tools/stdstamp.py OBJ...
"""
import struct
import sys

UTC_CPP = (0x60 << 16) | 3077         # Utc1310_CPP, build 3077
UTC_CPP_STD = (0x62 << 16) | 3077     # Utc1310_CPP_Std, build 3077


def main():
    for path in sys.argv[1:]:
        data = bytearray(open(path, 'rb').read())
        symtab, nsyms = struct.unpack_from('<II', data, 8)
        for i in range(nsyms):
            sym = symtab + 18 * i
            if data[sym:sym + 8] == b'@comp.id':
                value = struct.unpack_from('<I', data, sym + 8)[0]
                if value == UTC_CPP:
                    struct.pack_into('<I', data, sym + 8, UTC_CPP_STD)
                    open(path, 'wb').write(data)
                elif value != UTC_CPP_STD:
                    sys.exit(f'{path}: unexpected @comp.id {value:#x}')
                break
        else:
            sys.exit(f'{path}: no @comp.id')


if __name__ == '__main__':
    main()
