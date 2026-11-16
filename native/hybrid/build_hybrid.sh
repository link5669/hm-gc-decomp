#!/bin/bash
# Hybrid native build: decomp units compiled natively (GuestMem pass) + recompiled code for everything else.
# Output: ${HM_OUT:-build/native-hybrid}/cmake/hauntedmansion. See build_hybrid.py for options.
#   1. python3 native/hybrid/hmcc.py --all     (front end: decomp units -> build/hybrid/ir/*.ll)
#   2. native/hybrid/build_hybrid.sh [-j N]    (back end + link)
set -euo pipefail
exec python3 "$(dirname "$0")/build_hybrid.py" "$@"
