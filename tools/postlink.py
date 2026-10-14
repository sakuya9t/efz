#!/usr/bin/env python3
"""Set the few header fields of the linked efz.exe that the build can't reproduce.

- **The Rich header's object count.** The original counts 152 objects from the Standard
  Edition compiler; the recovered source is 71. Whatever the other 81 held adds nothing
  to the image (no code, data or constants), so nothing shows where they went. The
  count also feeds the header's checksum key, and link.exe pads the block by
  `(key >> 5) % 3` entries, so the new count moves the PE header too.
- **The link timestamp**, in the file header and the debug directory.
- **The PDB's GUID** in the debug directory's RSDS record, which link.exe makes up when it
  creates the PDB.

Everything else, including the PDB path and age, comes out of the link as it is.

Usage: tools/postlink.py build/efz.exe
"""
import struct
import sys

import pefile

TIMESTAMP = 0x4386998f                  # 2005-11-25 04:56:47 UTC
PDB_GUID = bytes.fromhex('1c282773e2de5c49bb17c3b43b19b436')
COUNTS = {(0x62, 3077): 152}            # Utc1310_CPP_Std, build 3077

DANS, RICH = 0x536E6144, 0x68636952
STUB = 0x80                             # DOS header and stub, where the Rich block starts


def rol(value, n):
    n &= 31
    return ((value << n) | (value >> (32 - n))) & 0xFFFFFFFF if n else value


def rich_key(stub, entries):
    """The checksum link.exe XORs the Rich block with: the stub's bytes (with e_lfanew
    zeroed) and each entry, rotated."""
    key = len(stub)
    for i, b in enumerate(stub):
        key = (key + rol(0 if 0x3C <= i < 0x40 else b, i)) & 0xFFFFFFFF
    for compid, count in entries:
        key = (key + rol(compid, count)) & 0xFFFFFFFF
    return key


def read_rich(data):
    end = data.index(b'Rich', STUB)
    key = struct.unpack_from('<I', data, end + 4)[0]
    assert struct.unpack_from('<I', data, STUB)[0] ^ key == DANS
    return [tuple(v ^ key for v in struct.unpack_from('<II', data, off))
            for off in range(STUB + 16, end, 8)]


def set_rich(data, entries):
    """Rewrite the Rich block and move the NT headers to where link.exe would put them."""
    old = struct.unpack_from('<I', data, 0x3C)[0]
    nsec, optsize = struct.unpack_from('<H', data, old + 6)[0], struct.unpack_from('<H', data, old + 20)[0]
    headers = bytes(data[old:old + 24 + optsize + 40 * nsec])
    key = rich_key(data[:STUB], entries)
    block = struct.pack('<4I', DANS ^ key, key, key, key)
    block += b''.join(struct.pack('<II', c ^ key, n ^ key) for c, n in entries)
    block += struct.pack('<II', RICH, key)
    # link.exe reserves 0x20 bytes plus 8 per entry, plus (key >> 5) % 3 more entries.
    new = STUB + 0x20 + 8 * (len(entries) + (key >> 5) % 3)
    data[STUB:old + len(headers)] = bytes(old + len(headers) - STUB)
    data[STUB:STUB + len(block)] = block
    data[new:new + len(headers)] = headers
    struct.pack_into('<I', data, 0x3C, new)


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

    open(path, 'wb').write(data)


if __name__ == '__main__':
    main()
