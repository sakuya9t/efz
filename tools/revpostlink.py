#!/usr/bin/env python3
"""Set the fields of the linked EfzRevival.exe that the build can't reproduce
(as tools/postlink.py does for efz.exe).

- **The link timestamp**, in the file header and the debug directory, and **the PDB's
  GUID and age** in the RSDS record (link.exe makes up the GUID when it creates the PDB;
  the original's PDB had been updated by 12 links).
- **The Rich header's counts of objects that left nothing in the image.** The original
  counts 30 objects from the launcher's compiler (the build has 29, Unused.obj
  included), 134 C++ objects of the static CRT (one more) and 202 imported functions
  (four more): its sources had code no longer in the image, which pulled them in. The
  new counts change the header's checksum key, and with it how much link.exe pads the
  block, so the PE header can move (tools/postlink.py).
- **The anonymous-namespace names in boost's type names** (`?A0x...`, as
  tools/revdllpostlink.py for EfzRevival.dll): the developer linked their own build of
  the boost libraries, and the compiler draws those names afresh on every compile; the
  official libraries the build uses have others, of the same length.
- **The size of .reloc.** link.exe reserves .reloc before it drops unreferenced code
  (/OPT:REF), at 2 bytes per DIR32 relocation of every section it took in plus 10 per page
  (IMAGE::CalculatePtrs), and pads the unused rest with zeros. The original's inputs had
  65,626 such relocations (the build's 22,000 or so): the same code no longer in the
  sources. The section keeps its relocations; only its virtual and file sizes grow.

Usage: tools/revpostlink.py build/revival/launcher/EfzRevival.exe
"""
import os
import struct
import sys

import pefile

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
from postlink import read_rich, set_rich  # noqa: E402

TIMESTAMP = 0x6292935e                      # 2022-05-28 21:25:50 UTC
PDB_GUID = bytes.fromhex('d9ea1d9035da1f42b5d58d31cfcfd8a8')
PDB_AGE = 12
COUNTS = {(0xCF, 61219): 30,                # Utc1700_CPP, Update 5's compiler
          (0xCF, 50929): 134,               # Utc1700_CPP, the static CRT
          (0x01, 0): 202}                   # Import0, imported functions
RELOC_VSIZE = 0x2094C
ANONYMOUS = {b'?A0x92439a12': b'?A0x0812ae90'}    # boost.system's error categories


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
    assert used <= RELOC_VSIZE, 'more relocations than the original reserved'
    falign = pe.OPTIONAL_HEADER.FileAlignment
    salign = pe.OPTIONAL_HEADER.SectionAlignment
    raw = (RELOC_VSIZE + falign - 1) // falign * falign
    grow = raw - reloc.SizeOfRawData
    hdr = reloc.get_file_offset()
    struct.pack_into('<I', data, hdr + 8, RELOC_VSIZE)          # VirtualSize
    struct.pack_into('<I', data, hdr + 16, raw)                 # SizeOfRawData
    end = reloc.PointerToRawData + reloc.SizeOfRawData
    data[end:end] = bytes(grow)
    opt = pe.OPTIONAL_HEADER.get_file_offset()
    struct.pack_into('<I', data, opt + 56,                     # SizeOfImage
                     reloc.VirtualAddress + (RELOC_VSIZE + salign - 1) // salign * salign)
    struct.pack_into('<I', data, opt + 8,                      # SizeOfInitializedData
                     pe.OPTIONAL_HEADER.SizeOfInitializedData + grow)

    for built, original in ANONYMOUS.items():
        data[:] = data.replace(built, original)

    open(path, 'wb').write(data)


if __name__ == '__main__':
    main()
