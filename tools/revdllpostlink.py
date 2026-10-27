#!/usr/bin/env python3
"""Set the fields of the linked EfzRevival.dll that the build can't reproduce
(as tools/postlink.py does for efz.exe and tools/revpostlink.py for EfzRevival.exe).

- **The link timestamp**, in the file header and the debug directory, and **the PDB's
  GUID and age** in the RSDS record (link.exe makes up the GUID when it creates the PDB;
  the original's PDB had been updated by 128 links).
- **The Rich header's count of imported functions**: 156 in the original, 154 in the
  build. Its sources referred to two more that its code no longer calls (the imported
  functions are the same). The count changes the header's checksum key, and with it how
  much link.exe pads the block, so the PE header can move (tools/postlink.py).
- **The size of .reloc**, which link.exe reserves before it drops unreferenced code
  (/OPT:REF; see tools/revpostlink.py): the original's inputs had more relocations.
- **The anonymous-namespace names in boost's type names** (`?A0x...`): the developer
  linked their own build of the boost libraries, and the compiler draws those names
  afresh on every compile (docs/revival.md, "Libraries"); the official libraries the
  build uses have others, of the same length.

Usage: tools/revdllpostlink.py build/revival/dll/EfzRevival.dll
"""
import os
import struct
import sys

import pefile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from postlink import read_rich, set_rich  # noqa: E402

TIMESTAMP = 0x62929371                      # 2022-05-28 21:26:09 UTC
PDB_GUID = bytes.fromhex('9d98fbc9821d8344a310ec3a35d1b21b')
PDB_AGE = 128
COUNTS = {(0x01, 0): 156}                   # Import0, imported functions
RELOC_VSIZE = 0xE736
ANONYMOUS = {b'?A0x92439a12': b'?A0x0812ae90',     # boost.system's error categories
             b'?A0x4800ac1b': b'?A0x71bbbf5e'}     # boost.filesystem's codecvt_error_cat


def main():
    path = sys.argv[1]
    data = bytearray(open(path, 'rb').read())

    entries = [(c, COUNTS.get((c >> 16, c & 0xFFFF), n)) for c, n in read_rich(data)]
    set_rich(data, entries)

    pe = pefile.PE(data=bytes(data))
    struct.pack_into('<I', data, pe.FILE_HEADER.get_file_offset() + 4, TIMESTAMP)
    for entry in pe.DIRECTORY_ENTRY_DEBUG:
        struct.pack_into('<I', data, entry.struct.get_file_offset() + 4, TIMESTAMP)
        ptr = entry.struct.PointerToRawData
        if data[ptr:ptr + 4] == b'RSDS':
            data[ptr + 4:ptr + 20] = PDB_GUID
            struct.pack_into('<I', data, ptr + 20, PDB_AGE)

    # .reloc, the last section: the reserved size, padded with zeros.
    reloc = pe.sections[-1]
    assert reloc.Name.rstrip(b'\0') == b'.reloc'
    used = pe.OPTIONAL_HEADER.DATA_DIRECTORY[5].Size
    if used <= RELOC_VSIZE:
        falign = pe.OPTIONAL_HEADER.FileAlignment
        salign = pe.OPTIONAL_HEADER.SectionAlignment
        raw = (RELOC_VSIZE + falign - 1) // falign * falign
        grow = raw - reloc.SizeOfRawData
        hdr = reloc.get_file_offset()
        struct.pack_into('<I', data, hdr + 8, RELOC_VSIZE)          # VirtualSize
        struct.pack_into('<I', data, hdr + 16, raw)                 # SizeOfRawData
        end = reloc.PointerToRawData + reloc.SizeOfRawData
        if grow > 0:
            data[end:end] = bytes(grow)
        elif grow < 0:
            del data[end + grow:end]
        opt = pe.OPTIONAL_HEADER.get_file_offset()
        struct.pack_into('<I', data, opt + 56,                     # SizeOfImage
                         reloc.VirtualAddress + (RELOC_VSIZE + salign - 1) // salign * salign)
        struct.pack_into('<I', data, opt + 8,                      # SizeOfInitializedData
                         pe.OPTIONAL_HEADER.SizeOfInitializedData + grow)
    else:
        print('revdllpostlink: more relocations (%#x bytes) than the original reserved'
              % used, file=sys.stderr)

    for old, new in ANONYMOUS.items():
        data = bytearray(bytes(data).replace(old, new))

    open(path, 'wb').write(data)


if __name__ == '__main__':
    main()
