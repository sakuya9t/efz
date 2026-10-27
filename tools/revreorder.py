#!/usr/bin/env python3
"""Reorder the annotated function definitions of an EfzRevival.dll source file.

Link-time code generation lays out an object's (non-COMDAT) functions in the reverse of
the order in which their symbols were created, and a function defined in the object gets
its symbol where it is defined (a call before the definition doesn't create it). So an
object whose functions are defined in the reverse of the original's address order comes
out in the original's order; functions an earlier object refers to are created there and
come last whatever their place (docs/revival.md, "How link-time code generation orders
functions").

This rewrites FILE with its annotated definitions (`// FUNCTION: 0xADDR` followed by a
definition) sorted by descending address (--ascending: ascending). Each definition moves
with the comment block right above it and with the text between it and the previous
definition (declarations, statics). Annotations without a definition stay where they are.

Usage: tools/revreorder.py [--ascending] [--dry-run] FILE...
"""
import re
import sys

ANNOTATION = re.compile(r'^\s*//\s*FUNCTION:\s*(0x[0-9a-fA-F]+)(\s+\S+)?')


def find_end(lines, i):
    """Index of the line after the definition starting at line i (matching braces)."""
    depth = 0
    seen = False
    in_block = False
    for j in range(i, len(lines)):
        line = lines[j]
        k = 0
        while k < len(line):
            c = line[k]
            if in_block:
                if line.startswith('*/', k):
                    in_block = False
                    k += 2
                    continue
                k += 1
                continue
            if line.startswith('//', k):
                break
            if line.startswith('/*', k):
                in_block = True
                k += 2
                continue
            if c in '"\'':
                q = c
                k += 1
                while k < len(line) and line[k] != q:
                    k += 2 if line[k] == '\\' else 1
                k += 1
                continue
            if c == '{':
                depth += 1
                seen = True
            elif c == '}':
                depth -= 1
                if seen and depth == 0:
                    return j + 1
            elif c == ';' and not seen and depth == 0:
                return None     # a declaration, not a definition
            k += 1
    raise ValueError('unbalanced braces from line %d' % (i + 1))


def chunks(lines):
    """[(address, start, end)] of the annotated definitions, in file order."""
    out = []
    i = 0
    while i < len(lines):
        m = ANNOTATION.match(lines[i])
        if not m:
            i += 1
            continue
        addr = int(m.group(1), 16)
        j = i + 1
        while j < len(lines) and lines[j].lstrip().startswith('//') and not ANNOTATION.match(lines[j]):
            j += 1
        if j >= len(lines) or not lines[j].strip() or ANNOTATION.match(lines[j]):
            i += 1
            continue
        end = find_end(lines, j)
        if end is None:
            i += 1
            continue
        start = i
        while start > 0 and lines[start - 1].lstrip().startswith('//') and \
                not ANNOTATION.match(lines[start - 1]) and (not out or start - 1 >= out[-1][2]):
            start -= 1
        if end < len(lines) and not lines[end].strip():
            end += 1
        out.append((addr, start, end))
        i = end
    return out


def reorder(text, descending=True):
    lines = text.split('\n')
    cs = chunks(lines)
    if not cs:
        return text
    pieces = []
    prev = cs[0][1]
    head = lines[:prev]
    for addr, start, end in cs:
        pieces.append((addr, lines[prev:end]))
        prev = end
    tail = lines[prev:]
    pieces.sort(key=lambda p: -p[0] if descending else p[0])
    body = [l for _a, ls in pieces for l in ls]
    # keep one blank line between definitions
    out = head + body + tail
    return '\n'.join(out)


def main():
    args = sys.argv[1:]
    descending = '--ascending' not in args
    dry = '--dry-run' in args
    for path in [a for a in args if not a.startswith('--')]:
        text = open(path, encoding='utf-8').read()
        new = reorder(text, descending)
        if dry:
            for addr, start, end in chunks(text.split('\n')):
                print('%s %#x lines %d-%d' % (path, addr, start + 1, end))
        elif new != text:
            with open(path, 'w', encoding='utf-8') as f:
                f.write(new)


if __name__ == '__main__':
    main()
