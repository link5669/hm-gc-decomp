#!/bin/bash
# run_bg.sh LOG [args...]: start the native game in the background, write its pid to LOG.pid
LOG=$1; shift
D=$(cd "$(dirname "$0")/../.." && pwd)
"${HM_BIN:-$D/build/native/cmake/hauntedmansion}" "$@" > "$LOG" 2>&1 &
echo $! > "$LOG.pid"
