#!/usr/bin/env python3
"""Turn tools/revmatch.py's {decorated name: address} into {address: readable name}.

The readable name is the demangled qualified name without return type and
parameters, with the standard library's string types shortened, for labelling a
disassembler's database (tools/ghidra/ExportDecomp.java).  When identical functions
were folded into one address, the first name in decorated order is used.

Usage: tools/revnames.py NAMES.json... > LABELS.json
"""
import json
import re
import sys

from undname import undname

SHORT = [
    ('std::basic_string<char,std::char_traits<char>,std::allocator<char> >', 'std::string'),
    ('std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t> >', 'std::wstring'),
    (',std::char_traits<char>', ''), (',std::char_traits<wchar_t>', ''),
]


def qualified(dem):
    """`std::vector<int>::push_back` from a full demangled signature."""
    d = re.sub(r'\b(class|struct|union|enum) ', '', dem)
    d = re.sub(r'^(public|private|protected): ', '', d)
    d = re.sub(r'\b(virtual|static) ', '', d)
    for a, b in SHORT:
        d = d.replace(a, b)
    depth, cut = 0, None
    for i, ch in enumerate(d):
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == '(' and depth == 0:
            if d[max(0, i - 8):i].endswith('operator') or d[i - 1:i + 1] == ')(' and d[i - 9:i - 1].endswith('operator'):
                continue
            cut = i
            break
    head = d[:cut] if cut is not None else d
    depth, start = 0, 0
    for i, ch in enumerate(head):
        if ch == '<':
            depth += 1
        elif ch == '>':
            depth -= 1
        elif ch == ' ' and depth == 0:
            start = i + 1
    name = head[start:]
    name = re.sub(r'(?<=\w) (?=\w)', '_', name)
    return re.sub(r'\s+', '', name) or dem


def main():
    names = {}
    for path in sys.argv[1:]:
        for n, a in json.load(open(path)).items():
            names.setdefault(n, a)
    dem = undname(list(names))
    out = {}
    for n in sorted(names):
        a = names[n]
        if a in out:
            continue
        q = qualified(dem[n]) if dem[n] != n else n
        out[a] = q
    json.dump(dict(sorted(out.items(), key=lambda kv: int(kv[0], 16))), sys.stdout, indent=0)


if __name__ == '__main__':
    main()
