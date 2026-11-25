#!/bin/bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build ../output_files
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j 8
cd build
./demo "$@"
