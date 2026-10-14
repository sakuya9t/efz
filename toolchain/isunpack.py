#!/usr/bin/env python3
"""Unpack the files embedded in an InstallShield setup.exe overlay.

The overlay starts with 'InstallShield\\0', a file count and a 46-byte header, then
for each file a 312-byte entry (name, flags, size) followed by the data.  Flag 0x2
means the data is XOR-encoded with a key derived from the file name.

Usage: isunpack.py overlay.bin outdir
"""
import os
import struct
import sys

HEADER_SIZE = 46
ENTRY_SIZE = 312
KEY_SEED = (0x13, 0x35, 0x86, 0x07)


def decode(data, name):
    key = [c ^ KEY_SEED[i % 4] for i, c in enumerate(name.encode('latin-1'))]
    tables = [bytes((~(k ^ (((b << 4) & 0xFF) | (b >> 4)))) & 0xFF for b in range(256)) for k in key]
    out = bytearray(len(data))
    for i in range(len(key)):
        out[i::len(key)] = data[i::len(key)].translate(tables[i])
    return bytes(out)


def main():
    src, outdir = sys.argv[1:3]
    d = open(src, 'rb').read()
    if d[:14] != b'InstallShield\0':
        sys.exit(f'{src}: not an InstallShield overlay')
    count = struct.unpack_from('<H', d, 14)[0]
    off = HEADER_SIZE
    os.makedirs(outdir, exist_ok=True)
    for _ in range(count):
        name = d[off:off + 260].split(b'\0')[0].decode('latin-1')
        flags, _unk, size = struct.unpack_from('<III', d, off + 260)
        off += ENTRY_SIZE
        data = d[off:off + size]
        off += size
        if '/' in name or '\\' in name or name in ('', '.', '..'):
            sys.exit(f'refusing unsafe file name {name!r}')
        if flags & 0x2:
            data = decode(data, name)
        with open(os.path.join(outdir, name), 'wb') as f:
            f.write(data)
        print(f'{name:40} {size:10}')


if __name__ == '__main__':
    main()
