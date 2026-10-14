#!/usr/bin/env python3
"""Write efz.exe's program icon (its only resource) as an .ico file for src/efz.rc.

The icon is part of the original game, so it isn't in the repository; the build takes it
from $EFZ_DIR/efz.exe.

Usage: tools/icon.py OUT.ico   (original: $EFZ_DIR/efz.exe)
"""
import os
import struct
import sys

import pefile

RT_ICON, RT_GROUP_ICON = 3, 14


def resources(pe, rtype):
    """{id: bytes} of the resources of one type (first language of each)."""
    out = {}
    for t in pe.DIRECTORY_ENTRY_RESOURCE.entries:
        if t.id != rtype:
            continue
        for e in t.directory.entries:
            d = e.directory.entries[0].data.struct
            out[e.id] = pe.get_data(d.OffsetToData, d.Size)
    return out


def main():
    pe = pefile.PE(os.path.join(os.environ['EFZ_DIR'], 'efz.exe'))
    groups, icons = resources(pe, RT_GROUP_ICON), resources(pe, RT_ICON)
    group = groups[min(groups)]
    _reserved, kind, count = struct.unpack_from('<HHH', group, 0)
    entries = [struct.unpack_from('<BBBBHHIH', group, 6 + 14 * k) for k in range(count)]
    # An .ico has the same directory, with file offsets in place of resource IDs.
    offset = 6 + 16 * count
    head, data = struct.pack('<HHH', 0, kind, count), b''
    for w, h, colors, res, planes, bits, size, rid in entries:
        head += struct.pack('<BBBBHHII', w, h, colors, res, planes, bits, size, offset + len(data))
        data += icons[rid]
    with open(sys.argv[1], 'wb') as f:
        f.write(head + data)


if __name__ == '__main__':
    main()
