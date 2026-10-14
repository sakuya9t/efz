#!/bin/sh
# Lift, compile and diff several objects; one summary line each.
#   tools/batch.sh obj1 obj2 ...     (log per object in build/batch/<obj>.log)
cd "$(dirname "$0")/.."
mkdir -p build/batch
for obj in "$@"; do
    tools/objcheck.sh "$obj" > "build/batch/$obj.log" 2>&1
    errs=$(grep -c " error " "build/batch/$obj.log")
    lift=$(grep -c "Error\|LIFT FAILED" "build/batch/$obj.log")
    echo "$obj: $(tail -1 "build/batch/$obj.log") (compile errors: $errs, lift errors: $lift)"
done
