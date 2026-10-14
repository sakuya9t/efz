#!/usr/bin/env python3
"""Pick local-variable names that reproduce the original stack layout.

Visual C++ .NET 2003 doesn't place locals in declaration order. It keeps a function's
locals in a 16-bucket hash table keyed on the name and lays them out from the top of
the frame down, bucket by bucket in a fixed order. Within a bucket, the later
declaration sits higher. Context outside the function doesn't matter. The hash
function itself is unknown: none of the common string hashes fit.

This tool measures ranks directly: it compiles a probe function with every candidate
name as a local, once in each declaration order (to detect ties). It then picks one
name per variable so the variables come out in the required order.

  tools/stackorder.py rank NAME...
      print the names from the top of the frame down; [a b] marks a tie
  tools/stackorder.py solve 'src: hFile hSrc' 'dst: hFile2 hDst' ...
      each argument is one variable, top of the frame first, with candidate names in
      order of preference; prints the first assignment that gives that order. Declare
      the locals in the printed order (bottom of the frame first): that resolves any
      variables that share a bucket.

Arrays are not moved: with /GS the security cookie just goes directly above the first
char array (or struct containing one) in this order, so solve arrays and scalars
together as one ordering. Arrays and structs of about 100 bytes or more are 8-aligned
with their size rounded up to 8, which leaves gaps; adjacent char locals share a slot.
Variables declared inside a block (a `case`, an `if`) get their own slots below the
function-scope ones, block by block in code order; solve each block on its own.
Compiler temporaries (new/delete pointers, struct returns) go below everything.

When several assignments work, solve picks the one whose names come earliest in their
candidate lists overall, so list preferred names first.

Global variables without an initialiser follow the same kind of hash: an object's .bss
holds them in a fixed order of their names, and only names that tie fall back on
declaration order (the later declaration comes first). With --globals, rank and solve
work on .bss offsets instead, lowest address first:
  tools/stackorder.py --globals solve 'startTime: g_startTime g_baseTime' ...
"""
import os
import re
import struct
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


GLOBALS = False     # --globals: rank globals by .bss offset instead of locals


def compile_probe(source):
    """Compile `source` and return the object file's bytes."""
    os.makedirs(os.path.join(REPO, 'build'), exist_ok=True)
    with tempfile.TemporaryDirectory(dir=os.path.join(REPO, 'build')) as tmp:
        with open(os.path.join(tmp, 'probe.cpp'), 'w') as f:
            f.write(source)
        rel = os.path.relpath(tmp, REPO)
        subprocess.run([os.path.join(REPO, 'tools', 'msvc'), 'cl', '/nologo', '/c', '/Od',
                        f'/Fo{rel}/probe.obj', f'{rel}/probe.cpp'],
                       cwd=REPO, check=True, stdout=subprocess.DEVNULL)
        with open(os.path.join(tmp, 'probe.obj'), 'rb') as f:
            return f.read()


def measure(names):
    """Return {name: frame offset} for a probe declaring `names` in that order (with
    GLOBALS, {name: .bss offset} for globals)."""
    if GLOBALS:
        return measure_globals(names)
    body = ''.join(f'    int {n};\n' for n in names)
    body += ''.join(f'    {n} = {k};\n' for k, n in enumerate(names))
    data = compile_probe('void probe()\n{\n' + body + '}\n')
    with tempfile.NamedTemporaryFile(suffix='.obj') as obj:
        obj.write(data)
        obj.flush()
        dis = subprocess.run(['objdump', '-d', '-M', 'intel', obj.name],
                             capture_output=True, text=True, check=True).stdout
    found = re.findall(r'mov\s+DWORD PTR \[ebp-(0x[0-9a-f]+)\],(0x[0-9a-f]+)', dis)
    return {names[int(k, 16)]: int(off, 16) for off, k in found}


def measure_globals(names):
    """{name: offset in .bss} for a probe defining `names` as int globals in that order."""
    data = compile_probe(''.join(f'int {n};\n' for n in names))
    _machine, _nsec, _ts, symtab, nsyms = struct.unpack_from('<HHIII', data, 0)
    strtab = symtab + nsyms * 18
    found = {}
    i = 0
    while i < nsyms:
        off = symtab + i * 18
        name = data[off:off + 8]
        if name[:4] == b'\0\0\0\0':
            k = strtab + struct.unpack_from('<I', name, 4)[0]
            name = data[k:data.index(b'\0', k)]
        value, section, _type, storage, naux = struct.unpack_from('<IhHBB', data, off + 8)
        m = re.match(rb'\?(\w+)@@3', name)
        if storage == 2 and section > 0 and m:
            found[m.group(1).decode()] = value
        i += 1 + naux
    return found


def rank(names):
    """Return groups of names from the top of the frame down; a group is a tie."""
    names = list(dict.fromkeys(names))
    fwd = measure(names)
    rev = measure(names[::-1])
    order = sorted(names, key=lambda n: fwd[n])
    groups = [[order[0]]]
    for n in order[1:]:
        prev = groups[-1][-1]
        # Same bucket: their relative order flips when the declaration order does.
        if (fwd[n] > fwd[prev]) != (rev[n] > rev[prev]):
            groups[-1].append(n)
        else:
            groups.append([n])
    return groups


def solve(variables, ranks=None):
    """variables: [(label, [candidates])] from the top of the frame down.

    Returns the assignment whose candidates are earliest in their lists overall (the
    sum of their positions is minimal), so that preferred names win where they can.
    `ranks` marks variables declared later in the body than the others (1, 2, ... in
    code order; 0 for the ones declared at the top, whose order is free): a variable
    declared later sits above the others in its bucket.
    """
    ranks = ranks or [0] * len(variables)
    groups = rank([c for _, cands in variables for c in cands])
    level = {n: i for i, g in enumerate(groups) for n in g}
    # best[k][lv]: (cost, names) of the cheapest assignment of variables k.. whose
    # first name has a level of at least lv. Same bucket as the variable above is
    # fine: declaring bottom-up puts the upper one later, and later declarations sit
    # higher.
    nlevels = len(groups)
    best = [[None] * (nlevels + 1) for _ in range(len(variables) + 1)]
    for lv in range(nlevels + 1):
        best[len(variables)][lv] = (0, [])
    for k in range(len(variables) - 1, -1, -1):
        for lv in range(nlevels - 1, -1, -1):
            options = [best[k][lv + 1]] if lv + 1 <= nlevels else []
            for cost, cand in enumerate(variables[k][1]):
                below = ranks[k + 1] if k + 1 < len(variables) else 0
                # sharing a bucket with the variable below needs this one declared later
                share = ranks[k] > below or ranks[k] == below == 0
                nxt = level[cand] if share else level[cand] + 1
                rest = best[k + 1][nxt] if nxt <= nlevels else None
                if level[cand] == lv and rest is not None and cand not in rest[1]:
                    options.append((cost + rest[0], [cand] + rest[1]))
            options = [o for o in options if o is not None]
            best[k][lv] = min(options, key=lambda o: o[0]) if options else None
    result = best[0][0]
    return (result[1] if result else None), groups


def main():
    global GLOBALS
    if sys.argv[1:2] == ['--globals']:
        GLOBALS = True
        del sys.argv[1]
    if len(sys.argv) < 3 or sys.argv[1] not in ('rank', 'solve'):
        sys.exit(__doc__)
    if sys.argv[1] == 'rank':
        print(' '.join(g[0] if len(g) == 1 else '[' + ' '.join(g) + ']' for g in rank(sys.argv[2:])))
        return
    variables = []
    for arg in sys.argv[2:]:
        label, _, cands = arg.partition(':')
        variables.append((label.strip(), cands.split()))
    choice, groups = solve(variables)
    if choice is None:
        print('no assignment works; add more candidates. Ranking of the candidates:')
        print(' '.join(g[0] if len(g) == 1 else '[' + ' '.join(g) + ']' for g in groups))
        sys.exit(1)
    for (label, _), name in zip(variables, choice):
        print(f'{label}: {name}')
    print('declare in this order:', ', '.join(reversed(choice)))


if __name__ == '__main__':
    main()
