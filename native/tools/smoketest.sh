#!/bin/bash
# smoketest.sh [disc.iso]: boots the native game hidden, drives it with a scripted controller into gameplay,
# joins player 2, names both players, switches player 2 to AI and warps to the Graveyard via the co-op
# debug menu. Checks log markers and that screenshots aren't blank. ~5 minutes. Exit 0 = pass.
set -u
D=$(cd "$(dirname "$0")/../.." && pwd)
ISO=${1:-/home/mi/Decomp/hm-emu/HauntedMansion_coop.iso}
O=$(mktemp -d /tmp/hm-smoke.XXXXXX)
WARP=""; for i in $(seq 0 9); do WARP="$WARP +$((1150 + i * 40)):D*4"; done
export HM_SCRIPT="300:S 600:S 900:S 1200:S 1600:A*8 2400:A*8 2600:U*6 2700:A*8 3000:S 3300:S 3600:S 3900:S 4200:S \
4500:A*6 4650:A*6 4800:A*6 4950:A*6 @GRTHALL +400:p2:S*6 @name_entry_for_player_1 +200:A*6 +320:S*6 \
@name_entry_for_player_2 +200:p2:A*6 +320:p2:S*6 +600:A*6 +800:ZS*8 +1000:A*6 $WARP +1700:A*6 @GRAVEYD +900:>*200"
export HM_HIDDEN=1 HM_REPORT=1 HM_FPS=1 HM_SCRIPT_LOG=1 HM_SHOTDIR=$O HM_SHOTEVERY=120 HM_SCALE=${HM_SCALE:-1}
"$D/native/tools/run_bg.sh" "$O/log" "$ISO"
PID=$(cat "$O/log.pid")
deadline=$((SECONDS + ${SMOKE_TIMEOUT:-420}))
while kill -0 "$PID" 2>/dev/null && [ $SECONDS -lt $deadline ]; do
    grep -q "level change to 'GRAVEYD'" "$O/log" && { sleep 25; break; }
    sleep 5
done
kill "$PID" 2>/dev/null; sleep 1
fail=0
check() { if grep -q "$1" "$O/log"; then echo "PASS  $2"; else echo "FAIL  $2"; fail=1; fi; }
check "multiplayer mod loaded" "boot + co-op mod loaded"
check "level change to 'GRTHALL'" "new game reaches gameplay (Great Hall)"
check "name entry for player 2" "player 2 joined (controller 2 Start) and named"
check "warp to 'GRAVEYD'" "debug menu warp"
check "level change to 'GRAVEYD'" "level load after warp (player 2 carried)"
if grep -q "FATAL" "$O/log"; then echo "FAIL  no fatal errors"; grep FATAL "$O/log" | head -3; fail=1; else echo "PASS  no fatal errors"; fi
python3 - "$O" <<'EOF' || fail=1
import sys, glob
from PIL import Image, ImageStat
fs = sorted(glob.glob(sys.argv[1] + '/f*.png'))
bright = [f for f in fs if sum(ImageStat.Stat(Image.open(f).convert('L')).mean) > 8]
print(('PASS' if len(bright) >= len(fs) // 2 and fs else 'FAIL') + '  screenshots not blank (%d/%d)' % (len(bright), len(fs)))
sys.exit(0 if fs and len(bright) >= len(fs) // 2 else 1)
EOF
grep "fps" "$O/log" | tail -3 | sed 's/^/      /'
echo "artifacts: $O"
exit $fail
