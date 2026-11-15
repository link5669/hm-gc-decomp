#!/bin/bash
# stack.sh LOG: print host backtraces of the running game (pid from LOG.pid)
gdb -p "$(cat "$1.pid")" -batch -ex "thread apply all bt ${2:-12}" 2>&1 | grep -E "^#|^Thread"
