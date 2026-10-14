#!/bin/sh
# Regenerate src/<obj>.cpp with the lifter, compile it and summarise the diff.
#   tools/objcheck.sh player [playerobj ...]
set -e
cd "$(dirname "$0")/.."
for obj in "$@"; do
    python3 tools/lift.py write "$obj"
done
for obj in "$@"; do
    rm -f "build/$obj.obj"
    make -s "build/$obj.obj" 2>&1 | grep -E " error " | head -20 || true
    python3 tools/funcdiff.py "build/$obj.obj" 2>/dev/null | grep -E "^(MATCH|DIFF|MISSING)" | grep -v "^MATCH" || true
    python3 tools/funcdiff.py "build/$obj.obj" 2>/dev/null | tail -1
done
