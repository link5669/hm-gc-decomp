#!/bin/bash
# build_all.sh /path/to/game.iso [--appimage]
#
# Builds the native Linux version of The Haunted Mansion from a fresh checkout of the static-recomp branch:
#   1. extracts main.dol from your disc image (USA, GHYE6S) into orig/GHYE6S/sys/
#   2. configures and builds the decomp (build/GHYE6S/main.dol) and the co-op mod (main_mp.dol)
#   3. builds a static SDL2 if needed (build/sdl2; or set SDL2_ROOT to an existing static SDL2 install)
#   4. recompiles the DOL to C and builds build/native/cmake/hauntedmansion
#   5. with --appimage: packages build/native/HauntedMansion-x86_64.AppImage
# Everything built here contains code from your copy of the game: keep it to yourself.
#
# Needs: python3, ninja, cmake, gcc/g++ (13+), git, curl, mksquashfs (only for --appimage),
#        X11 + OpenGL development headers (libx11-dev libxext-dev libgl-dev), optionally libpulse-dev/libasound2-dev.
set -euo pipefail
R=$(cd "$(dirname "$0")/.." && pwd)
ISO=${1:-}
APPIMAGE=0; [ "${2:-}" = "--appimage" ] && APPIMAGE=1
[ -n "$ISO" ] && [ -r "$ISO" ] || { sed -n '2,15p' "$0"; exit 1; }
cd "$R"
J=${JOBS:-$(nproc)}

echo "== 1/5 extracting main.dol from $ISO"
mkdir -p orig/GHYE6S/sys
python3 - "$ISO" orig/GHYE6S/sys/main.dol <<'EOF'
import struct, sys
f = open(sys.argv[1], 'rb')
hdr = f.read(0x440)
if hdr[:6] != b'GHYE6S':
    sys.exit('not a Haunted Mansion (USA, GHYE6S) disc image: %r' % hdr[:6])
dol_off = struct.unpack('>I', hdr[0x420:0x424])[0]
f.seek(dol_off); h = f.read(0x100)
offs = struct.unpack('>18I', h[0:72]); sizes = struct.unpack('>18I', h[144:216])
size = max(o + s for o, s in zip(offs, sizes) if s)
f.seek(dol_off)
open(sys.argv[2], 'wb').write(f.read(size))
print('  main.dol: %d bytes' % size)
EOF

echo "== 2/5 decomp + co-op mod"
if [ ! -f build.ninja ]; then
    T=$HOME/.local/share/decompnet/toolchains
    if [ -d "$T" ] && [ -x "$HOME/.local/share/uv/tools/decompnet/bin/python" ]; then
        "$HOME/.local/share/uv/tools/decompnet/bin/python" configure.py --wrapper "$T/wibo/wibo" --compilers "$T/mwcc" \
            --binutils "$T/gc-wii-binutils" --dtk "$T/dtk/dtk" --objdiff "$T/objdiff-cli/objdiff-cli" --sjiswrap "$T/sjiswrap/sjiswrap.exe"
    else
        python3 configure.py
    fi
fi
[ -x "$HOME/.local/share/decompnet/toolchains/gc-wii-binutils/powerpc-eabi-nm" ] || ninja build/binutils
tools/mp/build.sh

echo "== 3/5 SDL2"
if [ -z "${SDL2_ROOT:-}" ]; then
    for d in /home/mi/Decomp/ref/sdl2 "$R/build/sdl2"; do [ -f "$d/lib/libSDL2.a" ] && SDL2_ROOT=$d && break; done
fi
if [ -z "${SDL2_ROOT:-}" ]; then
    SDL2_ROOT=$R/build/sdl2
    [ -d build/sdl2-src ] || git clone --depth 1 -b release-2.30.9 https://github.com/libsdl-org/SDL.git build/sdl2-src
    cmake -S build/sdl2-src -B build/sdl2-build -G Ninja -DCMAKE_BUILD_TYPE=Release -DSDL_SHARED=OFF -DSDL_STATIC=ON \
        -DSDL_TEST=OFF -DSDL_WAYLAND=OFF -DSDL_PULSEAUDIO_SHARED=ON -DSDL_ALSA_SHARED=ON \
        -DCMAKE_POSITION_INDEPENDENT_CODE=ON -DCMAKE_INSTALL_PREFIX="$SDL2_ROOT" > build/sdl2-build.log
    ninja -C build/sdl2-build -j "$J" install > /dev/null
fi
export SDL2_ROOT
echo "  using $SDL2_ROOT"

echo "== 4/5 recompiling and building the native game"
CMAKE_ARGS="-DHMAUDIO_TESTS=OFF ${CMAKE_ARGS:-}" NINJA_ARGS="-j $J" native/build.sh | tail -1

if [ $APPIMAGE = 1 ]; then
    echo "== 5/5 AppImage"
    RT=build/appimage-runtime-x86_64
    [ -f "$RT" ] || curl -sSL -o "$RT" https://github.com/AppImage/type2-runtime/releases/download/continuous/runtime-x86_64
    APPIMAGE_RUNTIME_RAW=$R/$RT native/tools/make_appimage.sh | tail -1
fi
echo "done: run  build/native/cmake/hauntedmansion  (it asks for your disc image on first launch)"
