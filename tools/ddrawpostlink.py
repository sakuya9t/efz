#!/usr/bin/env python3
"""Set the fields of the linked DDRAW.dll (EfzRevival 1.02h) that the build can't
reproduce (as tools/revdllpostlink.py does for EfzRevival.dll).

- **The link timestamp**, in the file header and the debug directory, and the export
  directory's, one second earlier (the import library's, made first).
- **The PDB's GUID and age** in the RSDS record (link.exe makes up the GUID when it
  creates the PDB; the original's had been updated by 4 links).
- **The anonymous-namespace name in boost.system's error category type names**
  (`?A0x...`): the developer linked their own build of the boost libraries, and the
  compiler draws those names afresh on every compile (docs/revival.md, "Libraries");
  the official libraries the build uses have another, of the same length.

Usage: tools/ddrawpostlink.py build/revival/ddraw/DDRAW.final.dll
"""
import struct
import sys

import pefile

TIMESTAMP = 0x625C3202                      # 2022-04-17 15:28:02 UTC
PDB_GUID = bytes.fromhex('d0b27e941ef1fb4e9779ec9d4b3c65e8')
PDB_AGE = 4
ANONYMOUS = {b'?A0x92439a12': b'?A0x0812ae90'}


def main():
    path = sys.argv[1]
    data = bytearray(open(path, 'rb').read())
    pe = pefile.PE(data=bytes(data))

    struct.pack_into('<I', data, pe.FILE_HEADER.get_file_offset() + 4, TIMESTAMP)
    struct.pack_into('<I', data, pe.DIRECTORY_ENTRY_EXPORT.struct.get_file_offset() + 4,
                     TIMESTAMP - 1)
    for entry in pe.DIRECTORY_ENTRY_DEBUG:
        struct.pack_into('<I', data, entry.struct.get_file_offset() + 4, TIMESTAMP)
        ptr = entry.struct.PointerToRawData
        if data[ptr:ptr + 4] == b'RSDS':
            data[ptr + 4:ptr + 20] = PDB_GUID
            struct.pack_into('<I', data, ptr + 20, PDB_AGE)

    for old, new in ANONYMOUS.items():
        data = bytearray(bytes(data).replace(old, new))

    open(path, 'wb').write(data)


if __name__ == '__main__':
    main()
