#!/usr/bin/env python3
"""Line coverage of the game's sources from a gcov build (tools/native.sh coverage) that
has run: `tools/coverage_report.py build/coverage` writes build/coverage/gcov/*.gcov
(each line of src/ with its count) and build/coverage/report.json ({file: {lines, hit,
never: [functions never run]}}). Runs where the game was built (tools/compat.py runs it
in the efz-native image), so gcov is the compiler's own."""
import gzip
import json
import os
import subprocess
import sys


def main():
    build = os.path.abspath(sys.argv[1])
    objs = os.path.join(build, 'CMakeFiles', 'efz.dir', 'src')
    out = os.path.join(build, 'gcov')
    os.makedirs(out, exist_ok=True)
    for name in os.listdir(out):
        os.remove(os.path.join(out, name))
    sources = sorted(n[:-5] for n in os.listdir(objs) if n.endswith('.cpp.gcda'))
    report = {}
    for src in sources:
        obj = os.path.join(objs, src + '.o')
        for fmt in ([], ['--json-format']):
            subprocess.run(['gcov', *fmt, '-o', obj, os.path.join('src', src)], cwd=out,
                           capture_output=True, check=True)
        lines = hit = 0
        never = []
        for name in os.listdir(out):
            if not name.endswith('.gcov.json.gz'):
                continue
            path = os.path.join(out, name)
            with gzip.open(path) as f:
                data = json.load(f)
            os.remove(path)
            for f in data['files']:
                if os.path.basename(f['file']) != src:
                    continue
                for line in f['lines']:
                    lines += 1
                    hit += line['count'] > 0
                for fn in f['functions']:
                    if fn['execution_count'] == 0:
                        never.append(fn['demangled_name'])
        report[src] = {'lines': lines, 'hit': hit, 'never': sorted(set(never))}
    # Only the game's own sources' listings are kept.
    for name in os.listdir(out):
        if not any(name == s + '.gcov' for s in sources):
            os.remove(os.path.join(out, name))
    with open(os.path.join(build, 'report.json'), 'w') as f:
        json.dump(report, f, indent=1)


if __name__ == '__main__':
    main()
