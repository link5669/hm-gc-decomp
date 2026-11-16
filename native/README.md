# Native Linux port (branch `native`)

The game (main.dol, including the co-op mod from branch `multiplayer`) runs as native x86-64 code.
Nothing is emulated at the instruction level.

```
main_mp.dol --(recomp/ppc2c.py)--> build/native/gen/*.c   one C function per guest function
                                         |
runtime/  (C++)  guest RAM, MMIO devices, fibers for guest threads, interrupts, DVD from the ISO,
                 pads (SDL), memory card files, boot (apploader/IPL HLE)
gpu/      (C++)  GX command-stream processor -> OpenGL 3.3 core (CP/XF/BP state, TEV shaders,
                 texture decode, EFB copies, XFB present)
audio/    (C++)  DSP AX-ucode HLE + ARAM + AI -> SDL audio
```

The game data is never in the repo. At run time the program reads the user's own disc image.

## Guest model
- Guest RAM is 24 MiB, `uint8_t *ram`, big-endian contents. For any guest address `a` with
  `(a & 0x3E000000) == 0` (0x80000000/0xC0000000 mirrors), the RAM byte is `ram[a & 0x01FFFFFF]`.
  Anything else is MMIO (0xCC000000 hardware registers, 0xCC008000 write-gather pipe,
  0xC8000000 EFB peek/poke, 0xE0000000 locked cache), handled by `runtime/mmio.cpp`.
- CPU state is in `struct CPU` (runtime/cpu.h): r[32], f[32] and ps1[32] (doubles), cr, lr, ctr,
  xer, msr, gqr[8], plus the time base and decrementer, derived from the host clock at 40.5 MHz.
- Each guest function becomes `void fn_XXXXXXXX(CPU *c)`. `bl` is a C call, `blr` is a return, and
  `bctrl`/`bctr` go through `rt_call(c, addr)`, which uses a dense address-to-function table.
- Guest threads are host fibers (ucontext) on one host thread. The guest OS scheduler is
  recompiled unchanged. Only `OSLoadContext` (replaced) and calls to `OSSaveContext` (each call
  site becomes an inline `setjmp`) switch fibers. Interrupts are delivered at checkpoints
  (loop back-edges, and `mtmsr` when it sets EE) by calling the guest's own exception handler
  from `__OSExceptionTable` with a fully saved context, exactly as the hardware stub would.

## GPU interface (gpu/gpu.h)
The runtime feeds the GP command stream (the bytes the CPU wrote to the gather pipe while the
CPU FIFO is linked to the GP FIFO) and services the GPU callbacks. Display lists are executed by
the GPU reading guest RAM (CALL_DL), and so are indexed vertex arrays, LOAD_INDX_*, textures and
TLUTs. See gpu/gpu.h.

## Building
1. Build the decomp + mod as usual: `ninja` then `tools/mp/build.sh` (gives build/GHYE6S/main.elf, mp/mp.elf, main_mp.dol).
2. `native/build.sh`: recompiles main_mp.dol to C in build/native/gen and builds build/native/cmake/hauntedmansion.
   Needs gcc/g++ 13, cmake, ninja, Python 3 and a static SDL2 (default /home/mi/Decomp/ref/sdl2, set SDL2_ROOT).
3. `native/tools/make_appimage.sh [out.AppImage]`: single-file AppImage (uses another type-2 AppImage's runtime).

The binary and the AppImage contain code translated from your copy of the game: keep them private.

## Running
`hauntedmansion [disc.iso]`. Without an argument it uses $HM_DISC or ~/.local/share/hauntedmansion/game.iso.
Player 1: keyboard (arrows move, X=A, Z=B, C=X, S=Y, D=Z, Enter=Start, Q/W=L/R, I/J/K/L C-stick, T/F/G/H D-pad)
plus the first game controller; player 2: the second game controller (HM_P2_PAD0=1: first controller is player 2).
F11 or Alt+Enter toggles fullscreen.

Environment: HM_SCALE (internal resolution, default 2), HM_FULLSCREEN, HM_FPS, HM_REPORT (game's OSReport output),
HM_LOG=2 (verbose), HM_SHOTDIR/HM_SHOTEVERY (screenshots), HM_SCRIPT (scripted pad input at VI frame numbers,
e.g. "300:S 900:A*8"), SIGUSR1 prints the guest call stack.

## Online co-op
Host-authoritative remote play (code in `net/`): the host runs the game and streams video (JPEG) and audio
(IMA-ADPCM, 32 kHz stereo) over TCP; the guest is a thin client (no disc needed) whose controller drives
player 2 (pad 2). While a guest is connected its input replaces controller 2; when it leaves, pad 2 goes
back to the local controller / unplugged (the mod then drops player 2). Player 2 joins by pressing Start in gameplay.

- Direct: host `hauntedmansion [disc.iso] --host [port]` (default 7777, forward that TCP port);
  guest `hauntedmansion --join HOST[:PORT]`. Optional shared code: `--room CODE` on both (or HM_NET_ROOM).
- Via a relay (no port forwarding): host `hauntedmansion --host --relay RELAY:7778 [--room CODE]`
  (prints the room code; random 6 characters if none given); guest `hauntedmansion --relay RELAY:7778 --room CODE`.
  (`--relay` with `--room` and without `--host` means guest.)
- Guest keys/controller: the player-1 mapping above. F11 / Alt+Enter fullscreen. `--name NAME` (or HM_NET_NAME).
- Status: host window title shows "guest connected (name, RTT)"; both sides log `[net]` stats every 5 s.
- Host tuning: HM_NET_W / HM_NET_H (stream size, default 960 x window aspect), HM_NET_QUALITY (JPEG, default 65),
  HM_NET_FPS (max stream fps, default 30), HM_NET_MAXQ (KB of unsent socket data before frames are dropped, default 192).
  Guest: HM_NET_AUDIO_MS (audio jitter buffer, default 60), HM_NET_SCRIPT (test input: "ms:BUTTONS*hold_ms ...",
  e.g. "95000:S*150").
- Bandwidth at defaults: about 4-7 Mbit/s video + 0.27 Mbit/s audio host->guest, ~10 kbit/s guest->host.

Protocol: u32 length + u8 type + payload; HELLO (magic, version, role, room, name), INPUT, VIDEO, AUDIO,
PING/PONG, BYE (see `net/proto.h`). The relay speaks a one-line preamble first (`HMRELAY HOST|JOIN CODE`).

### Relay server
`net/relay/hm_relay.py` (Python 3.7+, no dependencies) pairs hosts and guests by room code and pipes bytes.
On any VPS: `python3 hm_relay.py --port 7778` (open TCP 7778). Options: `--idle 120` (seconds without data
before a session is closed), `--wait 3600` (how long a host may wait for a guest). systemd unit example
(`/etc/systemd/system/hm-relay.service`, then `systemctl enable --now hm-relay`):

    [Unit]
    Description=Haunted Mansion co-op relay
    After=network-online.target
    [Service]
    ExecStart=/usr/bin/python3 /opt/hm/hm_relay.py --port 7778
    DynamicUser=yes
    Restart=always
    [Install]
    WantedBy=multi-user.target
