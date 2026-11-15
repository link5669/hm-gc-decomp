#!/bin/bash
# collect.sh LOG SHOTDIR SHEET [N]: stop the run (after a guest backtrace) and make a contact sheet of the last N shots
LOG=$1; SHOTS=$2; SHEET=$3; N=${4:-12}
kill -USR1 "$(cat "$LOG.pid")" 2>/dev/null; sleep 0.3; kill "$(cat "$LOG.pid")" 2>/dev/null
grep -v "Dolphin SDK\|fps" "$LOG" | tail -6; grep fps "$LOG" | tail -3 | tr '\n' ' '; echo
python3 - "$SHOTS" "$SHEET" "$N" <<'PY'
import sys, glob
from PIL import Image
fs = sorted(glob.glob(sys.argv[1] + '/f*.png'))[-int(sys.argv[3]):]
if not fs: print('no shots'); sys.exit()
ims = [Image.open(f).convert('RGB').resize((320, 240)) for f in fs]
cols = 4; rows = (len(ims) + cols - 1) // cols
sheet = Image.new('RGB', (320 * cols, 240 * rows))
for i, im in enumerate(ims): sheet.paste(im, (320 * (i % cols), 240 * (i // cols)))
sheet.save(sys.argv[2]); print(fs[0].split('/')[-1], fs[-1].split('/')[-1])
PY
