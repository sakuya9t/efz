#!/usr/bin/env python3
"""Check tools/lift.py against functions that already match.

For each matching function in src/, replaces its body with the lifted one in a copy of
the source tree, compiles the copy and compares the function with the original.

Usage: tools/lifttest.py [name-filter] [-v]
"""
import os
import re
import shutil
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import funcdiff  # noqa: E402
import lift  # noqa: E402

REPO = lift.REPO
WORK = os.path.join(REPO, 'build', 'lifttest')


def find_definition(text, qual):
    """(start of body '{', end after '}', parameter names) of a function definition."""
    parts = qual.split('::')
    pat = r'::'.join(re.escape(p) for p in parts)
    for m in re.finditer(r'^[^\n;{}()]*\b' + pat + r'\s*\(', text, re.M):
        # parameter list
        depth, k = 1, m.end()
        while depth:
            depth += {'(': 1, ')': -1}.get(text[k], 0)
            k += 1
        params = text[m.end():k - 1]
        rest = text[k:]
        brace = re.match(r'\s*\{', rest)
        if not brace:
            continue
        start = k + brace.end() - 1
        depth, j = 0, start
        while True:
            depth += {'{': 1, '}': -1}.get(text[j], 0)
            j += 1
            if depth == 0:
                break
        names = []
        for p in split_params(params):
            p = p.strip()
            if not p or p == 'void' or p == '...':
                continue
            names.append(re.findall(r'\w+', p)[-1])
        return start, j, names
    return None


def split_params(s):
    out, depth, cur = [], 0, ''
    for ch in s:
        if ch == ',' and depth == 0:
            out.append(cur)
            cur = ''
            continue
        depth += {'(': 1, ')': -1}.get(ch, 0)
        cur += ch
    out.append(cur)
    return out


def main():
    flt = sys.argv[1] if len(sys.argv) > 1 and not sys.argv[1].startswith('-') else ''
    verbose = '-v' in sys.argv
    img = lift.Image(os.path.join(os.environ['EFZ_DIR'], 'efz.exe'))
    syms = lift.Symbols(img)
    original = funcdiff.Original(os.path.join(os.environ['EFZ_DIR'], 'efz.exe'))
    known = funcdiff.read_annotations(os.path.join(REPO, 'src'))
    results = {'match': 0, 'diff': 0, 'lift': 0, 'compile': 0, 'skip': 0}
    for fn in sorted(os.listdir(os.path.join(REPO, 'src'))):
        if not fn.endswith('.cpp'):
            continue
        text = open(os.path.join(REPO, 'src', fn), encoding='utf-8').read()
        for qual, (kind, addr) in sorted(known.items(), key=lambda kv: kv[1][1]):
            if kind != 'FUNCTION' or flt not in qual or addr >= 0x77697e:
                continue
            d = find_definition(text, qual)
            if d is None:
                continue
            start, end, names = d
            try:
                lf, body, st = lift.lift(img, syms, addr)
                code = lift.body_text(lf, body, st)
            except (lift.LiftError, KeyError, IndexError, TypeError, AttributeError) as e:
                results['lift'] += 1
                print(f'LIFT    {qual} {addr:#x}: {type(e).__name__}: {e}')
                continue
            for n, name in enumerate(names):
                code = re.sub(rf'\bp{n + 1}\b', name, code)
            variant = text[:start] + code + text[end:]
            ok, report = compile_and_compare(fn, variant, qual, original, known)
            if ok is None:
                results['compile'] += 1
                print(f'COMPILE {qual} {addr:#x}')
                if verbose:
                    print(report)
                    print(code)
            elif ok:
                results['match'] += 1
                print(f'MATCH   {qual} {addr:#x}')
            else:
                results['diff'] += 1
                print(f'DIFF    {qual} {addr:#x}')
                if verbose:
                    print(report)
                    print(code)
    print(results)


def compile_and_compare(fn, variant, qual, original, known):
    if os.path.exists(WORK):
        shutil.rmtree(WORK)
    os.makedirs(os.path.join(WORK, 'src'))
    for f in os.listdir(os.path.join(REPO, 'src')):
        data = open(os.path.join(REPO, 'src', f), encoding='utf-8').read()
        if f == fn:
            data = variant
        open(os.path.join(WORK, 'src', f), 'wb').write(data.encode('cp932'))
    rel = os.path.relpath(WORK, REPO)
    r = subprocess.run([os.path.join(REPO, 'tools', 'msvc'), 'cl', '/nologo', '/c', '/Od', '/GS',
                        '/W3', '/D', 'WIN32', '/D', 'NDEBUG', '/D', '_WINDOWS', '/D', '_MBCS',
                        f'/Fo{rel}/out.obj', f'{rel}/src/{fn}'], cwd=REPO, capture_output=True,
                       text=True, encoding='latin-1')
    if r.returncode != 0:
        return None, r.stdout[-3000:]
    lines = []
    ok = False
    for q, addr, size, good, rep in funcdiff.check(os.path.join(WORK, 'out.obj'), original, known, qual):
        if q == qual:
            ok = good
            lines = rep
    return ok, '\n'.join(lines)


if __name__ == '__main__':
    main()
