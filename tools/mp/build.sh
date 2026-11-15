#!/bin/bash
# Build the game DOL (no sha check: this branch changes it on purpose) and inject the multiplayer mod.
set -e
cd "$(dirname "$0")/../.."
ninja build/GHYE6S/main.dol | grep -v '^\[' || true
python3 tools/mp/build_mp.py "$@"
