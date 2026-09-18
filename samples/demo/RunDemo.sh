#!/bin/bash
set -euo pipefail
here="$(cd "$(dirname "$0")" && pwd)"
root="$(cd "$here/../.." && pwd)"
cmake -S "$here" -B "$here/build" -DCMAKE_BUILD_TYPE=Release
cmake --build "$here/build" --parallel 4
if [[ $# -gt 0 ]]; then
    exec "$here/build/demo" "$@"
fi
mkdir -p "$root/samples/output_files"
exec "$here/build/demo" "$root/resource/license/license.xml" "$root/resource" \
    "$root/samples/input_files/word.pdf" "$root/samples/output_files/word-$(date +%Y%m%d-%H%M%S).docx"
