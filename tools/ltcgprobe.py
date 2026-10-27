#!/usr/bin/env python3
"""Link probe sources with link-time code generation and report each object's function order.

Writes the given sources into build/revival/ltcgprobe/NAME/, compiles each with the DLL's
options (the Makefile's DLL_CFLAGS), links them in the given order into a DLL with /LTCG
and reads the map: for every object, its non-COMDAT functions in address order.

As a module:  probe(name, {'a.cpp': text, ...}, order=['a', 'b'], cflags=..., link=...)
              -> {object: [decorated names in address order]}
Usage:        tools/ltcgprobe.py NAME DIR [OBJ ...]   (DIR holds the .cpp files and headers)
"""
import os
import re
import shutil
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
DLL_CFLAGS = ('/nologo /c /O2 /Ob0 /Oy- /GS- /GL /Gy- /GF- /MT /EHsc /arch:SSE /fp:strict '
              '/W3 /Zc:wchar_t /Zc:forScope /D WIN32 /D NDEBUG /D _WINDOWS /D _USRDLL '
              '/D _UNICODE /D UNICODE').split()


def msvc(args, cwd):
    env = dict(os.environ, MSVC11_QUIET='1')
    r = subprocess.run([os.path.join(REPO, 'tools', 'msvc11')] + args, cwd=cwd, env=env,
                       stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    if r.returncode:
        raise RuntimeError(' '.join(args) + '\n' + r.stdout)
    return r.stdout


def read_map(path):
    """[(address, name, object)] for the map's non-COMDAT functions ('f' without 'i')."""
    rows = []
    for line in open(path, errors='replace'):
        m = re.match(r'\s*0001:[0-9a-f]+\s+(\S+)\s+([0-9a-f]{8})\s+f\s+(\S+)\s*$', line)
        if m:
            rows.append((int(m.group(2), 16), m.group(1), m.group(3)))
    return sorted(rows)


def probe(name, sources, order=None, cflags=None, link=(), libs=('kernel32.lib',), jobs=8, pch=None):
    """pch: a header name (say 'stdafx.h'); stdafx.cpp is then compiled first with /Yc and
    every other source with /Yu, as a Visual Studio project with precompiled headers."""
    d = os.path.join(REPO, 'build', 'revival', 'ltcgprobe', name)
    if os.path.isdir(d):
        shutil.rmtree(d)
    os.makedirs(d)
    for fn, text in sources.items():
        with open(os.path.join(d, fn), 'w', newline='\r\n') as f:
            f.write(text)
    order = order or sorted(os.path.splitext(f)[0] for f in sources if f.endswith('.cpp'))
    flags = cflags or DLL_CFLAGS
    procs = []
    pchstem = os.path.splitext(pch)[0] if pch else None
    if pch:
        msvc(['cl'] + flags + ['/Yc' + pch, pchstem + '.cpp'], d)
    for stem in order:
        if stem == pchstem:
            continue
        extra = ['/Yu' + pch] if pch else []
        procs.append(subprocess.Popen(
            [os.path.join(REPO, 'tools', 'msvc11'), 'cl'] + flags + extra + [stem + '.cpp'], cwd=d,
            env=dict(os.environ, MSVC11_QUIET='1'), stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT, text=True))
        if len(procs) >= jobs:
            for p in procs:
                out = p.communicate()[0]
                if p.returncode:
                    raise RuntimeError(out)
            procs = []
    for p in procs:
        out = p.communicate()[0]
        if p.returncode:
            raise RuntimeError(out)
    msvc(['link', '/nologo', '/DLL', '/LTCG', '/NOENTRY', '/MACHINE:X86', '/MAP:probe.map',
          '/OUT:probe.dll'] + list(link) + [s + '.obj' for s in order] + list(libs), d)
    result = {}
    for _a, n, obj in read_map(os.path.join(d, 'probe.map')):
        result.setdefault(obj, []).append(n)
    return result


def main():
    name, src = sys.argv[1:3]
    order = sys.argv[3:] or None
    sources = {f: open(os.path.join(src, f)).read() for f in os.listdir(src)
               if f.endswith(('.cpp', '.h', '.def'))}
    for obj, names in probe(name, sources, order).items():
        print(obj)
        for n in names:
            print('   ', n)


if __name__ == '__main__':
    main()
