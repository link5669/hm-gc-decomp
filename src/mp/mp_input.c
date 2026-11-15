/* Multiplayer mod: controller input. Hooks the game's only PADRead call (controller manager update). */
#include "sdk_names.h"
#include <dolphin/pad.h>
#include "mp_state.h"
#include "mp.h"

MpState mp;
void mp_fill_p2_input(const PADStatus *st);

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
        in->pressed |= b & ~in->held;  /* accumulated until the once-per-frame UI update consumes it */
        in->held = b;
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
    int was_naming = (mp.mode == MP_NAMING);
    mp.frame++;
    track(&mp.in[0], &st[0]);
    track(&mp.in[1], &st[1]);
    {
        /* the game polls several times per frame: run the UI once per rendered frame */
        static u32 last_frame = 0xFFFFFFFF;
        if (mp_render_frame != last_frame) {
            last_frame = mp_render_frame;
            mp_ui_update();
            mp.in[0].pressed = mp.in[1].pressed = 0;
        }
    }
    /* The game must not see menu input while a player types a name, and port 2 never drives Zeke 1. */
    if ((was_naming || mp.mode == MP_NAMING || mp.menu_open) && st[0].err == PAD_ERR_NONE)
        blank(&st[0]);
    if (st[1].err == PAD_ERR_NONE) {
        if (!mp.menu_open)
            mp_fill_p2_input(&st[1]);
        blank(&st[1]);
    }
    return r;
}
