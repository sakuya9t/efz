#!/usr/bin/env bash
# Sets up a Linux machine with an NVIDIA GPU for the language-model agent (README.md):
# builds the headless library, makes a Python environment with CUDA torch and the
# packages, writes the frame data the measures read, and checks it all runs.
#
#   runs/llm-ayu/setup-linux.sh --efz /data/EFZ [--dataset /data/efz-replays/datasets/ayu] [--venv DIR]
#
# --efz: EFZ 4.02's install, or a compatibility pack made from it (tools/compatpack.py
# build OUT --efz DIR: what the game's state reads, about 1 MB); --dataset: the replays'
# dataset (runs/human-ayu/dataset.py's, copied from where it was made) to check.
# Needs: cmake (3.20+), a C++ compiler (g++ or clang), python3 (3.10+) with venv, an
# NVIDIA driver.
set -euo pipefail

REPO=$(cd "$(dirname "$0")/../.." && pwd)
VENV="$REPO/.venv-llm"
EFZ=""
DATASET=""
while [ $# -gt 0 ]; do
    case "$1" in
        --efz) EFZ=$2; shift 2 ;;
        --dataset) DATASET=$2; shift 2 ;;
        --venv) VENV=$2; shift 2 ;;
        *) echo "unknown argument: $1" >&2; exit 2 ;;
    esac
done
[ -n "$EFZ" ] || { echo "--efz: the EFZ install or pack" >&2; exit 2; }
[ -f "$EFZ/ayu/ayu.pat" ] || { echo "$EFZ has no ayu/ayu.pat: not EFZ's data" >&2; exit 1; }

echo "== GPU"
nvidia-smi --query-gpu=name,memory.total,driver_version --format=csv,noheader || {
    echo "no NVIDIA GPU or driver (nvidia-smi)" >&2; exit 1; }

echo "== the headless library (build/headless)"
cmake -S "$REPO" -B "$REPO/build/headless" -DEFZ_GAME=OFF -DCMAKE_BUILD_TYPE=Release
cmake --build "$REPO/build/headless" --parallel "$(nproc)"
LIB=$(find "$REPO/build/headless" -name 'libefz_env.so' | head -n 1)
[ -n "$LIB" ] || { echo "no libefz_env.so built" >&2; exit 1; }
echo "built $LIB"

echo "== Python ($VENV)"
[ -d "$VENV" ] || python3 -m venv "$VENV"
"$VENV/bin/pip" install --upgrade pip
"$VENV/bin/pip" install -r "$REPO/runs/llm-ayu/requirements.txt"
"$VENV/bin/pip" install -e "$REPO/python"

PY="$VENV/bin/python"
export EFZ_ENV_LIBRARY="$LIB" EFZ_DIR="$EFZ"
echo "== checks"
"$PY" - <<'EOF'
import os, torch
assert torch.cuda.is_available(), 'torch sees no CUDA device'
print('torch', torch.__version__, 'on', torch.cuda.get_device_name(0),
      f'({torch.cuda.get_device_properties(0).total_memory / 2**30:.0f} GB), bf16:',
      torch.cuda.is_bf16_supported())
import numpy as np
from efz_env import ActionTable, EfzVecEnv
env = EfzVecEnv(os.environ['EFZ_DIR'], 8, frame_skip=1)
obs = env.reset()
t = ActionTable()
for _ in range(300):
    obs, *_ = env.step(t.to_bytes(np.random.randint(len(t), size=(8, 2))))
env.close()
print('efz_env: 8 matches stepped, observations', obs.shape)
import transformers
print('transformers', transformers.__version__)
EOF
"$PY" "$REPO/runs/human-ayu/framedata.py" --data "$EFZ" | tail -n 3

if [ -n "$DATASET" ]; then
    [ -f "$DATASET/matches.csv" ] || { echo "$DATASET has no matches.csv" >&2; exit 1; }
    n=$(ls "$DATASET" | grep -c '\.npz$' || true)
    echo "dataset: $n matches' sides in $DATASET"
    [ -f "$(dirname "$(dirname "$DATASET")")/players.csv" ] ||
        echo "note: no players.csv beside the replays' folder: prompts name no players (--players)"
fi

cat <<EOF

Ready. In each shell:
    source $VENV/bin/activate
    export EFZ_ENV_LIBRARY=$LIB EFZ_DIR=$EFZ
A smoke test (a few minutes):
    python runs/llm-ayu/train.py --dataset ${DATASET:-DATASET} --out runs/llm-ayu/smoke --limit 20 --max-steps 50 --eval-every 50 --val-steps 2000
    python runs/human-ayu/evaluate.py --p1 runs/llm-ayu/smoke --p2 cpu --level 1 --matches 4 --minutes 0.5
EOF
