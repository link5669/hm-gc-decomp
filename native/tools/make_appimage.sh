#!/bin/bash
# make_appimage.sh OUT.AppImage: package build/native/cmake/hauntedmansion as a single-file AppImage.
# The binary contains code recompiled from YOUR copy of the game: keep the AppImage private.
# The game disc image is not included; the program looks for ~/.local/share/hauntedmansion/game.iso
# (or a path given as the first argument / HM_DISC).
set -euo pipefail
N=$(cd "$(dirname "$0")/.." && pwd); R=$(dirname "$N")
OUT=${1:-$R/build/native/HauntedMansion-x86_64.AppImage}
RUNTIME_SRC=${APPIMAGE_RUNTIME:-$HOME/Downloads/dolphin-2609b-x64.AppImage}   # any type-2 AppImage: we reuse its runtime
W=$(mktemp -d); trap 'rm -r "$W"' EXIT
A=$W/AppDir
mkdir -p "$A/usr/bin"
cp "$R/build/native/cmake/hauntedmansion" "$A/usr/bin/"
strip "$A/usr/bin/hauntedmansion"
python3 "$N/tools/make_icon.py" "$A/hauntedmansion.png"
cat > "$A/hauntedmansion.desktop" <<'D'
[Desktop Entry]
Type=Application
Name=The Haunted Mansion (native)
Exec=hauntedmansion
Icon=hauntedmansion
Categories=Game;
Actions=Host;

[Desktop Action Host]
Name=Host online co-op (port 7777)
Exec=hauntedmansion --host
D
cat > "$A/AppRun" <<'R'
#!/bin/sh
HERE=$(dirname "$(readlink -f "$0")")
exec "$HERE/usr/bin/hauntedmansion" "$@"
R
chmod +x "$A/AppRun"
OFF=$("$RUNTIME_SRC" --appimage-offset)
head -c "$OFF" "$RUNTIME_SRC" > "$W/runtime"
mksquashfs "$A" "$W/fs.sqfs" -root-owned -noappend -comp zstd -quiet
cat "$W/runtime" "$W/fs.sqfs" > "$OUT"
chmod +x "$OUT"
ls -la "$OUT"
