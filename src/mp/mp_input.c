/* Multiplayer mod: controller input. Hooks the game's only PADRead call (controller manager update). */
#include "sdk_names.h"
#include <dolphin/pad.h>
#include "mp_state.h"
#include "mp.h"

MpState mp;

static void track(MpInput *in, const PADStatus *st)
{
    u16 b = 0;
    in->connected = (st->err == PAD_ERR_NONE || st->err == PAD_ERR_NOT_READY || st->err == PAD_ERR_TRANSFER);
    if (st->err == PAD_ERR_NONE) {
        b = st->button;
        in->sx = st->stickX;
        in->sy = st->stickY;
    } else if (!in->connected) {
        in->sx = in->sy = 0;
    }
    if (st->err == PAD_ERR_NONE || !in->connected) {
        in->pressed = b & ~in->held;
        in->held = b;
    } else {
        in->pressed = 0;  /* keep last held state across transient errors */
    }
}

static void blank(PADStatus *st)
{
    st->button = 0;
    st->stickX = st->stickY = st->substickX = st->substickY = 0;
    st->triggerLeft = st->triggerRight = st->analogA = st->analogB = 0;
}

u32 mp_pad_read(PADStatus *st)
{
    u32 r = PADRead(st);
    mp.frame++;
    track(&mp.in[0], &st[0]);
    track(&mp.in[1], &st[1]);
    mp_ui_update();
    {
        static s8 last0 = 99, last1 = 99;
        if (st[0].err != last0 || st[1].err != last1)
            OSReport("[mp] pad err %d,%d (call %d)\n", st[0].err, st[1].err, mp.frame);
        last0 = st[0].err; last1 = st[1].err;
    }
    /* The game must not see menu input while a player types a name, and port 2 never drives Zeke 1. */
    if (mp.mode == MP_NAMING && st[0].err == PAD_ERR_NONE)
        blank(&st[0]);
    if (st[1].err == PAD_ERR_NONE)
        blank(&st[1]);
    return r;
}
