#ifndef MP_STATE_H
#define MP_STATE_H
#include <dolphin/types.h>
#include <dolphin/pad.h>

#define MP_NAME_MAX 10

enum { MP_SOLO, MP_NAMING, MP_COOP };

typedef struct MpInput {
    u16 held, pressed;  /* PAD_BUTTON_* bits */
    s8 sx, sy;          /* main stick */
    u8 connected;
    u8 rep_timer;       /* menu auto-repeat */
    s8 rep_dx, rep_dy;
} MpInput;

typedef struct MpState {
    int mode;           /* MP_SOLO / MP_NAMING / MP_COOP */
    int naming_player;  /* 0 or 1 while MP_NAMING */
    char name[2][MP_NAME_MAX + 1];
    u8 named[2];
    MpInput in[2];
    u32 frame;
    u8 join_pending;    /* player 2 pressed START in a menu: start naming when gameplay begins */
    u8 want_spawn;
    u8 p2_rejoin;       /* player 2 (out of lives) pressed START */      /* player 2 asked to spawn (latched until the next player update) */
    u8 debug_split;
    u8 debug_hide;
    u8 debug_teleport, debug_kill, debug_level, debug_list, debug_tp, debug_p1tp;      /* debug: X on controller 2 cycles hiding P2's body / instance */     /* debug: Z on controller 2 toggles split screen */
} MpState;

extern MpState mp;
extern void *mp_player[2];
extern u32 mp_player_seen[2], mp_render_frame;
extern void *mp_game;

void mp_ui_update(void);
int mp_in_gameplay(void);
void mp_ui_draw(void);
#endif
