#!/usr/bin/env python3
"""A compatibility pack: what the compatibility suite's fights read of EFZ's data and
nothing more, made from an EFZ 4.02 install, so that the suite can run where the
install can't be (CI: docs/compat.md, "In CI").

    tools/compatpack.py build OUT [--efz DIR] [--archive FILE.tar.gz]
    tools/compatpack.py encrypt [--efz DIR] [--key-file FILE]
    tools/compatpack.py unpack OUT [--key-file FILE]

build makes OUT a folder EFZ_DIR can name for tools/compat.py check. encrypt makes the
pack and writes it encrypted to tests/compat/pack.tar.gz.enc, with the digest of what
it encrypted in tests/compat/pack.sha256 (an unchanged pack is left as it was);
unpack decrypts that file, checks the digest and extracts it into OUT. The key is the
EFZ_COMPAT_PACK_KEY environment variable's, or --key-file's contents; encryption is
openssl's AES-256 with a key derived by PBKDF2 (openssl must be on the PATH).

What the game's state depends on is kept; the pictures and the sounds are not:

- .pat (moves, frames, boxes, damage...), the characters' .pal and key.ini: copied.
- .dat (a byte counting palette entries, the palette, then images: width, height, and
  pixels raw or run-length coded): the palette copied; each image keeps its size and
  its first pixel (which the game reads as the colour key); its other pixels become the
  first one's colour (run-length coded) or 0 (raw, which keep their length).
- .wav: the chunks up to the data chunk's header (which decide whether the game takes a
  sound slot), then the file's last 0x140 bytes (where CSound::LoadLoop looks for loop
  points); the samples are dropped.

Every .dat, .pat and .wav goes in: a fight opens the characters', the effects', the
stages' and the sounds', and the game opens the menus' pictures as it starts (each
scene loads its own when WinMain makes it). The program, its libraries, texts, BMPs
(which the game's loaders never take) and the rest are left out.

The pack is still made of the game's data (its frame data and palettes): unencrypted,
it is for the owner's own tests, as the install is. Only the encrypted file goes in the
repository; the key stays with the owner and in the repository's CI secrets.
"""
import argparse
import gzip
import hashlib
import io
import os
import shutil
import subprocess
import sys
import tarfile
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ENCRYPTED = os.path.join(REPO, 'tests', 'compat', 'pack.tar.gz.enc')
DIGEST = os.path.join(REPO, 'tests', 'compat', 'pack.sha256')
KEY_VAR = 'EFZ_COMPAT_PACK_KEY'
# openssl enc: AES-256-CBC, the key derived from the passphrase by PBKDF2-SHA256.
CIPHER = ['-aes-256-cbc', '-pbkdf2', '-iter', '600000', '-md', 'sha256']
LOOP_TAIL = 0x140


def images(data, start, rle):
    """(start, end, width, height) of each image from `start` on, as the game's loader
    reads them (port/graphics.cpp, LoadDatImage), until the data ends or stops making
    sense."""
    pos = start
    while pos + 4 <= len(data):
        w = data[pos] | data[pos + 1] << 8
        h = data[pos + 2] | data[pos + 3] << 8
        p = pos + 4
        n = w * h
        if rle == 0:
            p += n
        else:
            covered = 0
            while covered < n and p < len(data):
                b = data[p]
                p += 1
                covered += 1 if b <= rle else b - rle
            if covered < n:
                return
        if p > len(data):
            return
        yield pos, p, w, h
        pos = p


def shrink_image(data, start, end, w, h, rle):
    """The image's size and first pixel; the rest of the same colour, or zeros."""
    n = w * h
    out = bytearray(data[start:start + 4])
    if n == 0:
        return bytes(out)
    pixels = data[start + 4:end]
    if rle == 0:
        # The pixel the loader puts first in memory: the bottom row's first.
        first = (h - 1) * w
        raw = bytearray(n)
        raw[first] = pixels[first]
        return bytes(out + raw)
    b = pixels[0]
    out.append(b if b <= rle else rle + 1)  # a pixel, or a run of one (colour 0)
    left = n - 1
    while left > 0:
        k = min(left, 255 - rle)
        out.append(rle + k)
        left -= k
    return bytes(out)


def shrink_dat(data, rle):
    """A .dat with its palette and every image shrunk; images past what the loader can
    read (if any) are kept as they are. Returns (bytes, images shrunk, verbatim tail)."""
    header = 1 + data[0] * 3
    out = bytearray(data[:header])
    pos = header
    count = 0
    for start, end, w, h in images(data, header, rle):
        out += shrink_image(data, start, end, w, h, rle)
        pos = end
        count += 1
    out += data[pos:]
    return bytes(out), count, len(data) - pos


def shrink_wav(data):
    """The chunks up to the data chunk's header, then the last 0x140 bytes."""
    if len(data) < 12 or data[:4] != b'RIFF' or data[8:12] != b'WAVE':
        return data
    p = 12
    while p + 8 <= len(data):
        size = int.from_bytes(data[p + 4:p + 8], 'little')
        if data[p:p + 4] == b'data':
            head = p + 8
            if len(data) <= head + LOOP_TAIL:
                return data
            return data[:head] + data[-LOOP_TAIL:]
        p += 8 + size + (size & 1)
    return data


def plan(efz):
    """(relative path, how) of each file to pack: 'copy', 'wav', or the run-length
    threshold of a .dat's images (0 raw)."""
    out = []
    for root, dirs, files in os.walk(efz):
        dirs.sort()
        rel_root = os.path.relpath(root, efz).replace('\\', '/')
        parts = [] if rel_root == '.' else rel_root.lower().split('/')
        for name in sorted(files):
            rel = name if not parts else f'{rel_root}/{name}'
            low = name.lower()
            stem, ext = os.path.splitext(low)
            if not parts and low == 'key.ini':
                out.append((rel, 'copy'))
            elif ext == '.pat':
                out.append((rel, 'copy'))
            elif ext == '.wav':
                out.append((rel, 'wav'))
            elif ext == '.pal' and len(parts) == 1:
                out.append((rel, 'copy'))
            elif ext == '.dat':
                if len(parts) == 1 and parts[0] == stem:
                    out.append((rel, 128))           # a character's sprites
                elif parts == ['system', 'effect'] and stem == 'effect':
                    out.append((rel, 81))            # the effects' sprites
                else:
                    out.append((rel, 0))             # one picture (CGame::LoadDat)
    return out




def build(efz, out, verbose=False):
    """The pack of `efz` in the folder `out`."""
    if not efz or not os.path.isfile(os.path.join(efz, 'system', 'effect', 'effect.dat')):
        sys.exit('compatpack: name an EFZ 4.02 install with --efz or EFZ_DIR')
    if os.path.exists(out):
        shutil.rmtree(out)
    before = after = 0
    tails = []
    for rel, how in plan(efz):
        with open(os.path.join(efz, rel), 'rb') as f:
            data = f.read()
        if how == 'copy':
            packed = data
        elif how == 'wav':
            packed = shrink_wav(data)
        else:
            packed, count, tail = shrink_dat(data, how)
            if tail:
                tails.append(f'{rel}: {count} images, then {tail} bytes kept as they are')
        dest = os.path.join(out, rel)
        os.makedirs(os.path.dirname(dest) or out, exist_ok=True)
        with open(dest, 'wb') as f:
            f.write(packed)
        before += len(data)
        after += len(packed)
    with open(os.path.join(out, 'PACK.txt'), 'w', newline='\n') as f:
        f.write('A compatibility pack (tools/compatpack.py): what the compatibility suite\n'
                'reads of EFZ 4.02\'s data. Made from the game\'s data: for its owner\'s\n'
                'tests only, not to be published or passed on.\n')
    # The images the game reads are all before them (a stage, a loading screen: one).
    if verbose:
        for line in tails:
            print(line)
    elif tails:
        print(f'{len(tails)} files end in bytes after their images, kept as they are (-v)')
    print(f'{out}: {after / 1e6:.1f} MB from {before / 1e6:.1f} MB')


def archive(folder):
    """The folder as a .tar.gz, the same bytes for the same files: names sorted, times,
    owners and modes fixed."""
    def norm(info):
        info.mtime = 0
        info.uid = info.gid = 0
        info.uname = info.gname = ''
        info.mode = 0o755 if info.isdir() else 0o644
        return info

    raw = io.BytesIO()
    with gzip.GzipFile(filename='', mode='wb', fileobj=raw, mtime=0) as gz:
        with tarfile.open(fileobj=gz, mode='w', format=tarfile.GNU_FORMAT) as tar:
            for root, dirs, files in os.walk(folder):
                dirs.sort()
                for name in sorted(files):
                    path = os.path.join(root, name)
                    arcname = os.path.relpath(path, folder).replace('\\', '/')
                    tar.add(path, arcname=arcname, filter=norm)
    return raw.getvalue()


def key_env(args):
    """The environment for openssl, the key in KEY_VAR: never on a command line."""
    env = dict(os.environ)
    if args.key_file:
        with open(args.key_file) as f:
            env[KEY_VAR] = f.read()
    # A key pasted into a CI secret or saved by an editor may end in a newline.
    env[KEY_VAR] = env.get(KEY_VAR, '').strip()
    if not env[KEY_VAR]:
        sys.exit(f'compatpack: no key: set {KEY_VAR} or pass --key-file')
    if not shutil.which('openssl'):
        sys.exit('compatpack: openssl is not on the PATH')
    return env


def openssl(data, env, decrypt, fail=True):
    """openssl enc on `data`; on a failure exits, or with fail=False returns None (a
    wrong key makes decryption fail, nearly always)."""
    mode = ['-d'] if decrypt else ['-salt']
    r = subprocess.run(['openssl', 'enc', *mode, *CIPHER, '-pass', f'env:{KEY_VAR}'],
                       input=data, capture_output=True, env=env)
    if r.returncode:
        if not fail:
            return None
        sys.exit('compatpack: openssl failed' + (' (the wrong key?)' if decrypt else '') +
                 f': {r.stderr.decode(errors="replace").strip()}')
    return r.stdout


def opens(env, digest):
    """Whether the encrypted file opens with the key in `env` into a pack of `digest`."""
    if not os.path.isfile(ENCRYPTED):
        return False
    with open(ENCRYPTED, 'rb') as f:
        data = openssl(f.read(), env, decrypt=True, fail=False)
    return data is not None and hashlib.sha256(data).hexdigest() == digest


def cmd_build(args):
    build(args.efz, args.out, args.verbose)
    if args.archive:
        with open(args.archive, 'wb') as f:
            f.write(archive(args.out))
        print(f'{args.archive}: {os.path.getsize(args.archive) / 1e6:.1f} MB')


def cmd_encrypt(args):
    env = key_env(args)
    with tempfile.TemporaryDirectory() as tmp:
        folder = os.path.join(tmp, 'pack')
        build(args.efz, folder, args.verbose)
        data = archive(folder)
    digest = hashlib.sha256(data).hexdigest()
    # Left as it is only if it holds this pack under this key: a new key (rotated, see
    # docs/compat.md) encrypts it again, so that the file and the CI secret agree.
    if opens(env, digest):
        print(f'{os.path.relpath(ENCRYPTED, REPO)}: unchanged ({digest[:16]})')
        return
    if os.path.isfile(ENCRYPTED):
        print('the pack or the key changed: encrypting again')
    with open(ENCRYPTED, 'wb') as f:
        f.write(openssl(data, env, decrypt=False))
    with open(DIGEST, 'w', newline='\n') as f:
        f.write(f'{digest}  pack.tar.gz\n')
    print(f'{os.path.relpath(ENCRYPTED, REPO)}: {os.path.getsize(ENCRYPTED) / 1e6:.1f} MB, '
          f'holding a pack of sha256 {digest[:16]}')


def cmd_unpack(args):
    env = key_env(args)
    if not os.path.isfile(ENCRYPTED):
        sys.exit(f'compatpack: no {ENCRYPTED}: tools/compatpack.py encrypt makes it')
    with open(ENCRYPTED, 'rb') as f:
        data = openssl(f.read(), env, decrypt=True)
    with open(DIGEST) as f:
        want = f.read().split()[0]
    if hashlib.sha256(data).hexdigest() != want:
        sys.exit('compatpack: what was decrypted is not the pack (the wrong key?)')
    os.makedirs(args.out, exist_ok=True)
    with tarfile.open(fileobj=io.BytesIO(data), mode='r:gz') as tar:
        for member in tar.getmembers():
            name = member.name
            if not (member.isfile() or member.isdir()) or name.startswith('/') or \
                    '..' in name.split('/'):
                sys.exit(f'compatpack: an unexpected entry in the pack: {name}')
        if hasattr(tarfile, 'data_filter'):  # Python 3.12, and fixes of 3.8-3.11
            tar.extractall(args.out, filter='data')
        else:
            tar.extractall(args.out)
    print(f'{args.out}: the compatibility pack, sha256 {want[:16]}')


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    sub = ap.add_subparsers(dest='cmd', required=True)
    efz = os.environ.get('EFZ_DIR')
    b = sub.add_parser('build', help='the pack, as a folder (and a .tar.gz)')
    b.add_argument('out')
    b.add_argument('--efz', default=efz, help='the EFZ 4.02 install (default $EFZ_DIR)')
    b.add_argument('--archive', help='also write the pack as this .tar.gz')
    b.add_argument('-v', '--verbose', action='store_true',
                   help='name the files whose last bytes were kept as they are')
    e = sub.add_parser('encrypt', help='the pack, encrypted, into tests/compat/')
    e.add_argument('--efz', default=efz, help='the EFZ 4.02 install (default $EFZ_DIR)')
    e.add_argument('--key-file')
    e.add_argument('-v', '--verbose', action='store_true')
    u = sub.add_parser('unpack', help="tests/compat/'s pack, decrypted, into a folder")
    u.add_argument('out')
    u.add_argument('--key-file')
    args = ap.parse_args()
    {'build': cmd_build, 'encrypt': cmd_encrypt, 'unpack': cmd_unpack}[args.cmd](args)


if __name__ == '__main__':
    main()
