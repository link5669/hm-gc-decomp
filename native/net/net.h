// Online co-op (host-authoritative remote play). The host runs the game and streams video+audio;
// a guest sends its controller, which drives player 2 (pad index 1). See native/README.md.
#pragma once
#include <stdint.h>

struct NetPad { uint16_t buttons; int8_t sx, sy, cx, cy; uint8_t tl, tr; };

// Parses and removes --host/--join/--relay/--room/--name from argv. Returns 0 = normal game,
// 1 = game + host, 2 = guest (thin client, no disc).
int net_parse_args(int *argc, char **argv);
int net_client_main();                       // guest mode: runs until the window closes

// host side (all no-ops unless net_parse_args returned 1)
void net_host_start();                       // after SDL/GL init
void net_capture_frame(int w, int h);        // game/GL thread, after gpu_present, before the swap
bool net_remote_pad(NetPad *out);            // true while a guest drives player 2
const char *net_status();                    // "" or e.g. "guest bob connected, 23 ms"
void net_audio_capture(const int16_t *lr, int frames, int rate);   // audio thread, mixed output

// provided by runtime/hle.cpp: poll host keyboard/controllers, return player 1's pad (for the guest)
bool pad_local_p1(NetPad *out);
