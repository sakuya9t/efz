#!/usr/bin/env python3
"""Identify an efz.exe: hash check, build toolchain (Rich header), PDB record, sections, imports.

Works on any PE; EfzRevival's binaries (docs/revival.md) are read the same way.

Usage: tools/peinfo.py [path/to/efz.exe]   (default: $EFZ_DIR/efz.exe)
"""
import hashlib
import os
import struct
import sys

import pefile

# The 4.02 build every EfzRevival install expects; this is the decomp target.
TARGET_SHA256 = '3a1616d6c76d2eea08a95bb198d853e96cb6b9b3266e277ca1d167426dd66481'

# Rich header product IDs that occur in Visual Studio .NET 2003 builds, and in the
# Visual Studio 2012 builds of EfzRevival (with the Windows SDK 7.1A's import libraries,
# made by Visual Studio 2008's lib.exe).
PRODIDS = {
    0x0001: 'Import0 (imported functions)',
    0x000f: 'Masm710',
    0x005a: 'Linker710',
    0x005b: 'Cvtomf710',
    0x005c: 'Export710',
    0x005d: 'Implib710',
    0x005e: 'Cvtres710',
    0x005f: 'Utc1310_C',
    0x0060: 'Utc1310_CPP',
    0x0061: 'Utc1310_C_Std',
    0x0062: 'Utc1310_CPP_Std',
    0x0093: 'Implib900',
    0x00c7: 'AliasObj1100',
    0x00c9: 'Cvtres1100',
    0x00ca: 'Export1100',
    0x00cb: 'Implib1100',
    0x00cc: 'Linker1100',
    0x00cd: 'Masm1100',
    0x00ce: 'Utc1700_C',
    0x00cf: 'Utc1700_CPP',
    0x00d2: 'Utc1700_LTCG_C',
    0x00d3: 'Utc1700_LTCG_CPP',
}


def rich_entries(data, pe_offset):
    end = data.find(b'Rich', 0, pe_offset)
    if end < 0:
        return []
    key = struct.unpack_from('<I', data, end + 4)[0]
    start = data.find(struct.pack('<I', 0x536E6144 ^ key), 0, end)  # 'DanS'
    entries = []
    for off in range(start + 16, end, 8):
        compid, count = (v ^ key for v in struct.unpack_from('<II', data, off))
        entries.append((compid >> 16, compid & 0xFFFF, count))
    return entries


def main():
    path = sys.argv[1] if len(sys.argv) > 1 else os.path.join(os.environ.get('EFZ_DIR', '.'), 'efz.exe')
    data = open(path, 'rb').read()
    digest = hashlib.sha256(data).hexdigest()
    print(f'{path}\n  sha256 {digest} ({"matches 4.02 target" if digest == TARGET_SHA256 else "NOT the 4.02 target"})')

    pe = pefile.PE(data=data)
    fh, oh = pe.FILE_HEADER, pe.OPTIONAL_HEADER
    print(f'  timestamp {fh.TimeDateStamp:#x}  linker {oh.MajorLinkerVersion}.{oh.MinorLinkerVersion}'
          f'  image base {oh.ImageBase:#x}  entry {oh.ImageBase + oh.AddressOfEntryPoint:#x}'
          f'  file align {oh.FileAlignment:#x}  checksum {oh.CheckSum:#x}')

    print('Rich header (product, build, object count):')
    for prodid, build, count in rich_entries(data, pe.DOS_HEADER.e_lfanew):
        print(f'  {PRODIDS.get(prodid, f"prodid {prodid:#06x}"):30} {build:5}  x{count}')

    for entry in getattr(pe, 'DIRECTORY_ENTRY_DEBUG', []):
        ptr, size = entry.struct.PointerToRawData, entry.struct.SizeOfData
        record = data[ptr:ptr + size]
        if record[:4] == b'RSDS':
            guid, age = record[4:20].hex(), struct.unpack_from('<I', record, 20)[0]
            pdb = record[24:].split(b'\0')[0].decode()
            print(f'PDB: {pdb}  guid {guid}  age {age}  (file offset {ptr:#x})')

    print('Sections:')
    for s in pe.sections:
        name = s.Name.rstrip(b'\0').decode()
        print(f'  {name:8} va {oh.ImageBase + s.VirtualAddress:#x}'
              f'  vsize {s.Misc_VirtualSize:#9x}  raw {s.SizeOfRawData:#9x}')

    print('Imports:')
    for imp in pe.DIRECTORY_ENTRY_IMPORT:
        names = [i.name.decode() if i.name else f'#{i.ordinal}' for i in imp.imports]
        print(f'  {imp.dll.decode():13} {len(names):3}  {" ".join(names)}')


if __name__ == '__main__':
    main()
