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
array in this order, so solve arrays and scalars together as one ordering. Variables
declared inside a block (a `case`, an `if`) get their own slots below the
function-scope ones, block by block in code order; solve each block on its own.
"""
import os
import re
import subprocess
import sys
import tempfile

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))


def measure(names):
    """Return {name: frame offset} for a probe declaring `names` in that order."""
    body = ''.join(f'    int {n};\n' for n in names)
    body += ''.join(f'    {n} = {k};\n' for k, n in enumerate(names))
    os.makedirs(os.path.join(REPO, 'build'), exist_ok=True)
    with tempfile.TemporaryDirectory(dir=os.path.join(REPO, 'build')) as tmp:
        src = os.path.join(tmp, 'probe.cpp')
        obj = os.path.join(tmp, 'probe.obj')
        with open(src, 'w') as f:
            f.write('void probe()\n{\n' + body + '}\n')
        rel = os.path.relpath(tmp, REPO)
        subprocess.run([os.path.join(REPO, 'tools', 'msvc'), 'cl', '/nologo', '/c', '/Od',
                        f'/Fo{rel}/probe.obj', f'{rel}/probe.cpp'],
                       cwd=REPO, check=True, stdout=subprocess.DEVNULL)
        dis = subprocess.run(['objdump', '-d', '-M', 'intel', obj],
                             capture_output=True, text=True, check=True).stdout
    found = re.findall(r'mov\s+DWORD PTR \[ebp-(0x[0-9a-f]+)\],(0x[0-9a-f]+)', dis)
    return {names[int(k, 16)]: int(off, 16) for off, k in found}


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


def solve(variables):
    """variables: [(label, [candidates])] from the top of the frame down."""
    groups = rank([c for _, cands in variables for c in cands])
    level = {n: i for i, g in enumerate(groups) for n in g}

    def search(k, floor, used):
        if k == len(variables):
            return []
        for cand in variables[k][1]:
            # Same bucket as the variable above is fine: declaring bottom-up puts
            # the upper one later, and later declarations sit higher.
            if cand not in used and level[cand] >= floor:
                rest = search(k + 1, level[cand], used | {cand})
                if rest is not None:
                    return [cand] + rest
        return None

    return search(0, 0, frozenset()), groups


def main():
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
