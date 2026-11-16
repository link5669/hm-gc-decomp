#!/bin/bash
# Build the native port. Needs the decomp + mod build (main.elf, mp/mp.elf, main_mp.dol): tools/mp/build.sh.
# HM_BUILD (default: <repo>/build/GHYE6S) points at that build directory.
set -euo pipefail
N=$(cd "$(dirname "$0")" && pwd)
R=$(dirname "$N")
B=${HM_BUILD:-$R/build/GHYE6S}
O=${HM_OUT:-$R/build/native}
BU=${BINUTILS:-$HOME/.local/share/decompnet/toolchains/gc-wii-binutils/powerpc-eabi-}
[ -x "${BU}nm" ] || BU=$R/build/binutils/powerpc-eabi-   # tools downloaded by configure.py
mkdir -p "$O"
"${BU}nm" -S --defined-only "$B/main.elf" > "$O/main.nm"
"${BU}nm" -S --defined-only "$B/mp/mp.elf" > "$O/mp.nm"
MPDATA=$("${BU}objdump" -h "$B/mp/mp.elf" | awk '$2==".mpdata"{print $4}')
MPBSS_END=$("${BU}nm" "$B/mp/mp.elf" | awk '$3=="mp_end"{print $1}')
python3 "$N/recomp/ppc2c.py" --dol "$B/main_mp.dol" --syms "$O/main.nm" --syms "$O/mp.nm" \
    --hle "$N/recomp/hle.txt" --out "$O/gen" --nocode "$MPDATA-$MPBSS_END" \
    --export IdleContext
cmake -S "$N" -B "$O/cmake" -G Ninja -DHM_GEN_DIR="$O/gen" -DHM_DOL="$B/main_mp.dol" ${SDL2_ROOT:+-DSDL2_ROOT="$SDL2_ROOT"} ${CMAKE_ARGS:-} > "$O/cmake.log"
ninja -C "$O/cmake" ${NINJA_ARGS:-}
ls -la "$O/cmake/hauntedmansion"
