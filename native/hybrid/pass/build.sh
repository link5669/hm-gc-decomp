#!/bin/bash
# builds GuestMem.so (LLVM 18 pass plugin); arg: output path (default build/hybrid/GuestMem.so)
set -e
D=$(cd "$(dirname "$0")" && pwd)
O=$(realpath -m "${1:-$D/../../../build/hybrid/GuestMem.so}")
mkdir -p "$(dirname "$O")"
g++ -O2 -g -shared -fPIC $(/usr/lib/llvm-18/bin/llvm-config --cxxflags) -fexceptions -o "$O" "$D/GuestMem.cpp"
