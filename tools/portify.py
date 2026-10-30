#!/usr/bin/env python3
"""Mark the pointer traffic of recovered sources for the native 64-bit build.

The recovered code keeps pointers in ints and casts them back, which only works where
pointers are 32 bits wide. This rewrites those casts into src/efz.h's macros, which
expand back to the same casts for the matching build and to 32-bit handles for the
native one (port/guest.h):

    *(char**)(a)             PTRAT(a)            a pointer loaded from raw memory
    *(char**)(a) = p         PTRSET(a, p)
    (T*)v, v an integer      TOPTR(T*, v)        found by compiling for 64 bits
    (int)p, p a pointer      TOINT(int, p)       likewise
    IDirectDrawSurface**     PTR32(IDirectDrawSurface)*   a pointer to a pointer member
    CPlayer**                PTR32(CPlayer)*              (g_player1, g_player2)

A pointer member of a class in efz.h is declared PTR32(T) by hand; a cast of one to
another pointer type or to an integer needs no macro (port/guest.h's Ptr32 has them).

The casts are found by compiling each file with g++ for 64 bits (-DEFZ_NATIVE) and
reading its diagnostics, which give each cast's exact extent; the file is rewritten and
compiled again until none is left. Running it again on rewritten sources changes
nothing, so it can follow tools/lift.py and `tools/members.py rewrite` on new code.
`make check` must still give the original's bytes afterwards.

Usage: tools/portify.py [src/file.cpp ...]   (default: the sources the native build uses)
"""
import json
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SRC = os.path.join(REPO, 'src')
HEADER = os.path.join(SRC, 'efz.h')
# Compiled for Windows only: replaced in the native build by port/.
PLATFORM = {'main.cpp', 'graphics.cpp', 'input.cpp', 'sound.cpp'}

BASE_TYPES = {'char', 'short', 'int', 'long', 'unsigned', 'signed', 'float', 'double',
              'void', 'BYTE', 'WORD', 'DWORD', 'BOOL', 'UINT', 'LONG', 'HWND', 'HANDLE'}


def match_paren(t, i):
    """Index after the parenthesis that closes the one at t[i]."""
    depth = 0
    while True:
        c = t[i]
        if c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
            if depth == 0:
                return i + 1
        elif c == '"' or c == "'":
            i = skip_literal(t, i) - 1
        i += 1


def skip_literal(t, i):
    q = t[i]
    i += 1
    while t[i] != q:
        i += 2 if t[i] == '\\' else 1
    return i + 1


def is_type(s):
    s = s.strip()
    m = re.fullmatch(r'(?:const\s+)?([A-Za-z_]\w*)(?:\s+[A-Za-z_]\w*)*\s*(\**)', s)
    if not m:
        return False
    return bool(m.group(2)) or m.group(1) in BASE_TYPES


def skip_ws(t, i):
    while i < len(t) and t[i] in ' \t\n':
        i += 1
    return i


def operand_end(t, i):
    """End of the cast-expression (the operand of a cast or unary *) starting at t[i]."""
    i = skip_ws(t, i)
    c = t[i]
    if c == '(':
        j = match_paren(t, i)
        if is_type(t[i + 1:j - 1]):
            return operand_end(t, j)
        return postfix_end(t, j)
    if c in '*&!~-+':
        return operand_end(t, i + 1)
    m = re.compile(r'new\s+[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*').match(t, i)
    if m:
        return postfix_end(t, m.end())
    m = re.compile(r'operator\s+(?:new|delete)(?:\s*\[\])?|[A-Za-z_]\w*(?:::[A-Za-z_]\w*)*'
                   r'|0x[0-9a-fA-F]+|\d+').match(t, i)
    if not m:
        raise ValueError(f'no operand at {t[i:i + 40]!r}')
    return postfix_end(t, m.end())


def postfix_end(t, i):
    while True:
        j = skip_ws(t, i)
        if j < len(t) and t[j] == '(':
            i = match_paren(t, j)
        elif j < len(t) and t[j] == '[':
            depth, k = 0, j
            while True:
                depth += {'[': 1, ']': -1}.get(t[k], 0)
                k += 1
                if depth == 0:
                    break
            i = k
        elif t.startswith('->', j) or (j < len(t) and t[j] == '.' and not t[j + 1:j + 2].isdigit()):
            m = re.compile(r'(->|\.)\s*[A-Za-z_]\w*').match(t, j)
            i = m.end()
        else:
            return i


def rewrite_loads(t):
    """*(char**)X -> PTRAT(X), and *(char**)X = v -> PTRSET(X, v), innermost first."""
    pat = '*(char**)'
    end = len(t)
    while True:
        k = t.rfind(pat, 0, end)
        if k < 0:
            return t
        line = t.rfind('\n', 0, k) + 1
        if t[line:k].lstrip().startswith('#'):
            end = k
            continue
        a = k + len(pat)
        e = operand_end(t, a)
        operand = t[a:e].strip()
        if operand.startswith('(') and match_paren(operand, 0) == len(operand):
            operand = operand[1:-1]
        rest = skip_ws(t, e)
        # A store only if nothing (such as a cast) applies to the load first.
        stmt = t[t.rfind('\n', 0, k) + 1:k].strip()
        if t[rest] == '=' and t[rest + 1] != '=' and stmt in ('', '{', '}', ';'):
            v0 = skip_ws(t, rest + 1)
            v1 = t.index(';', v0)
            t = t[:k] + f'PTRSET({operand}, {t[v0:v1].strip()})' + t[v1:]
        else:
            t = t[:k] + f'PTRAT({operand})' + t[e:]


def rewrite_text(name, t):
    t = rewrite_loads(t)
    t = t.replace('(IDirectDrawSurface**)', '(PTR32(IDirectDrawSurface)*)')
    t = re.sub(r'\bIDirectDrawSurface\*\* ', 'PTR32(IDirectDrawSurface)* ', t)
    t = re.sub(r'\bCPlayer\*\* ', 'PTR32(CPlayer)* ', t)
    return t


# --- The casts the 64-bit compiler finds.

CAST_ERR = re.compile(r"cast from .(.+?). to .(.+?). loses precision")
CAST_WARN = re.compile(r'cast to pointer from integer of different size')


DIAG = re.compile(r'^(.+?):(\d+):(\d+): (error|warning): (.*)$')


def compile_diagnostics(path):
    """(file, line, byte column, kind, message) of each diagnostic. The text output, as
    its locations are where a cast is written even inside a macro's arguments."""
    cmd = ['g++', '-std=c++17', '-fsyntax-only', '-fmax-errors=0', '-DEFZ_NATIVE',
           '-I', os.path.join(REPO, 'port'), '-I', SRC, '-fdiagnostics-plain-output',
           '-fdiagnostics-column-unit=byte', '-Wno-conversion-null', path]
    p = subprocess.run(cmd, capture_output=True, text=True, cwd=REPO)
    out = []
    for line in p.stderr.splitlines():
        m = DIAG.match(line)
        if m:
            out.append((os.path.join(REPO, m.group(1)), int(m.group(2)), int(m.group(3)),
                        m.group(4), m.group(5)))
    return out


def line_offsets(b):
    offs, pos = [0], 0
    for line in b.split(b'\n'):
        pos += len(line) + 1
        offs.append(pos)
    return offs


def rewrite_casts(path):
    """One round: wraps each innermost cast the compiler reports. Returns how many."""
    diags = compile_diagnostics(path)
    edits = {}
    others = []
    for f, line, col, kind, msg in diags:
        f = os.path.abspath(f)
        if not (CAST_ERR.search(msg) or CAST_WARN.search(msg)) \
                or f not in (os.path.abspath(path), HEADER):
            if kind == 'error':
                others.append((f, line, msg))
            continue
        edits.setdefault(f, set()).add((line, col))
    count = 0
    for f, locs in edits.items():
        t = open(f, encoding='utf-8').read()
        lines = t.split('\n')
        offs = [0]
        for line in lines:
            offs.append(offs[-1] + len(line) + 1)
        spans = set()
        for line, col in locs:
            s = offs[line - 1] + len(lines[line - 1].encode('utf-8')[:col - 1].decode('utf-8'))
            if t[s] != '(':
                raise ValueError(f'{f}:{line}: not a cast: {t[s:s + 60]!r}')
            # The diagnostic's end is unreliable when the operand is a macro call.
            spans.add((s, operand_end(t, match_paren(t, s))))
        # Only the innermost of nested casts this round; the rest come back next time.
        inner = [x for x in spans
                 if not any(y != x and x[0] <= y[0] and y[1] <= x[1] for y in spans)]
        for s, e in sorted(inner, reverse=True):
            k = match_paren(t, s)
            ty, operand = t[s + 1:k - 1].strip(), t[k:e].strip()
            if operand.startswith('(') and match_paren(operand, 0) == len(operand):
                operand = operand[1:-1]
            macro = 'TOPTR' if ty.endswith('*') else 'TOINT'
            t = t[:s] + f'{macro}({ty}, {operand})' + t[e:]
        open(f, 'w', encoding='utf-8').write(t)
        count += len(inner)
    return count, others


def main():
    files = sys.argv[1:] or [os.path.join(SRC, f) for f in sorted(os.listdir(SRC))
                             if f.endswith('.cpp') and f not in PLATFORM]
    for path in [HEADER] + files:
        t = open(path, encoding='utf-8').read()
        n = rewrite_text(os.path.basename(path), t)
        if n != t:
            open(path, 'w', encoding='utf-8').write(n)
    status = 0
    for path in files:
        total = 0
        while True:
            n, others = rewrite_casts(path)
            total += n
            if not n:
                break
        print(f'{os.path.relpath(path, REPO)}: {total} casts')
        for f, line, msg in others[:20]:
            print(f'  {os.path.relpath(f, REPO)}:{line}: {msg}')
        if others:
            status = 1
    return status


if __name__ == '__main__':
    sys.exit(main())
