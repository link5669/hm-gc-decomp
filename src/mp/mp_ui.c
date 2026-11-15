/* Multiplayer mod: join flow and on-screen keyboard for player names. */
#include <dolphin/pad.h>
#include "mp_state.h"
#include "mp.h"
#include "mp_draw.h"

#define KB_COLS 10
#define KB_ROWS 5
static const char kb_chars[4][KB_COLS + 1] = {
    "ABCDEFGHIJ", "KLMNOPQRST", "UVWXYZ-.!?", "0123456789",
};
/* row 4: SPACE (cols 0-3), DEL (4-6), DONE (7-9) */
enum { KEY_SPACE = 1000, KEY_DEL, KEY_DONE };

static int kb_x, kb_y, name_len;

static int key_at(int x, int y)
{
    if (y < 4)
        return kb_chars[y][x];
    if (x < 4)
        return KEY_SPACE;
    if (x < 7)
        return KEY_DEL;
    return KEY_DONE;
}

static int slen(const char *s)
{
    int n = 0;
    while (s[n])
        n++;
    return n;
}

static void start_naming(int p)
{
    mp.mode = MP_NAMING;
    mp.naming_player = p;
    kb_x = kb_y = 0;
    name_len = slen(mp.name[p]);
}

/* Stick/D-pad navigation with auto-repeat. */
static void nav(MpInput *in, int *dx, int *dy)
{
    int x = 0, y = 0;
    if ((in->held & PAD_BUTTON_LEFT) || in->sx < -48) x = -1;
    if ((in->held & PAD_BUTTON_RIGHT) || in->sx > 48) x = 1;
    if ((in->held & PAD_BUTTON_UP) || in->sy > 48) y = -1;
    if ((in->held & PAD_BUTTON_DOWN) || in->sy < -48) y = 1;
    *dx = *dy = 0;
    if (x == 0 && y == 0) {
        in->rep_timer = 0;
        in->rep_dx = in->rep_dy = 0;
        return;
    }
    if (x != in->rep_dx || y != in->rep_dy || in->rep_timer == 0) {
        *dx = x; *dy = y;
        in->rep_timer = 14;
    } else if (--in->rep_timer == 0) {
        *dx = x; *dy = y;
        in->rep_timer = 5;
    }
    in->rep_dx = x; in->rep_dy = y;
}

static void finish_naming(void)
{
    int p = mp.naming_player;
    if (name_len == 0) {
        const char *def = p ? "PLAYER 2" : "PLAYER 1";
        for (name_len = 0; def[name_len]; name_len++)
            mp.name[p][name_len] = def[name_len];
        mp.name[p][name_len] = 0;
    }
    mp.named[p] = 1;
    if (p == 0 && mp.in[1].connected)
        start_naming(1);
    else
        mp.mode = mp.in[1].connected ? MP_COOP : MP_SOLO;
}

static void type_key(int k)
{
    char *nm = mp.name[mp.naming_player];
    if (k == KEY_DONE) {
        finish_naming();
    } else if (k == KEY_DEL) {
        if (name_len > 0)
            nm[--name_len] = 0;
    } else if (name_len < MP_NAME_MAX) {
        nm[name_len++] = (k == KEY_SPACE) ? ' ' : (char)k;
        nm[name_len] = 0;
    }
}

void mp_ui_update(void)
{
    MpInput *in;
    int dx, dy;

    switch (mp.mode) {
    case MP_SOLO:
#ifdef MP_DEBUG_AUTOJOIN
        if (mp.in[1].connected && !mp.named[1]) {
            int k;
            for (k = 0; k < 2; k++) {
                const char *d = k ? "GHOST" : "ZEKE";
                int n = 0;
                while (d[n]) { mp.name[k][n] = d[n]; n++; }
                mp.name[k][n] = 0;
                mp.named[k] = 1;
            }
            mp.mode = MP_COOP;
        }
#endif
        /* Player 2 joins by pressing START on controller 2. Player 1 names themself first if not named yet. */
        if (mp.in[1].connected && (mp.in[1].pressed & PAD_BUTTON_START))
            start_naming(mp.named[0] ? 1 : 0);
        break;
    case MP_NAMING:
        in = &mp.in[mp.naming_player];
        if (!mp.in[1].connected && mp.naming_player == 1) {
            mp.mode = MP_SOLO;
            break;
        }
        nav(in, &dx, &dy);
        kb_x = (kb_x + dx + KB_COLS) % KB_COLS;
        kb_y = (kb_y + dy + KB_ROWS) % KB_ROWS;
        if (in->pressed & PAD_BUTTON_A)
            type_key(key_at(kb_x, kb_y));
        else if (in->pressed & PAD_BUTTON_B)
            type_key(KEY_DEL);
        else if (in->pressed & PAD_BUTTON_START)
            type_key(KEY_DONE);
        break;
    case MP_COOP:
        if (!mp.in[1].connected)
            mp.mode = MP_SOLO;  /* player 2 left (controller unplugged) */
        if (mp.in[1].pressed & PAD_BUTTON_Y) {
            mp.want_spawn = 1;
            OSReport("[mp] P2 pressed Y: spawn requested\n");
        }
        if (mp.in[1].pressed & PAD_TRIGGER_Z)
            mp.debug_split = (mp.debug_split + 1) % 3;
        break;
    }
}

#define COL_TITLE 0xFFE070FF
#define COL_TEXT 0xE8E8F0FF
#define COL_DIM 0x9090A0FF
#define COL_SEL 0x60C0FFFF

static void draw_keyboard(void)
{
    static const char *wide[3] = {"SPACE", "DEL", "DONE"};
    static const int wide_x[3] = {0, 4, 7}, wide_w[3] = {4, 3, 3};
    int p = mp.naming_player, x, y, i;
    f32 px = 130.0f, py = 96.0f, cw = 38.0f, ch = 34.0f, gx0 = px + 10.0f, gy0 = py + 112.0f;
    char buf[MP_NAME_MAX + 2];
    char cs[2];

    mp_draw_box(px, py, 380.0f, 300.0f, 0x101028E0);
    mp_draw_box(px, py, 380.0f, 3.0f, p ? 0x60C0FFFF : 0xFF9040FF);
    mp_draw_text_centered(320.0f, py + 12.0f, p ? "PLAYER 2" : "PLAYER 1", 2.0f, p ? 0x60C0FFFF : 0xFF9040FF);
    mp_draw_text_centered(320.0f, py + 42.0f, "ENTER YOUR NAME", 1.0f, COL_DIM);

    for (i = 0; i < name_len; i++)
        buf[i] = mp.name[p][i];
    buf[i++] = ((mp.frame >> 4) & 1) && name_len < MP_NAME_MAX ? '_' : ' ';
    buf[i] = 0;
    mp_draw_box(px + 60.0f, py + 62.0f, 260.0f, 32.0f, 0x000000A0);
    mp_draw_text(px + 70.0f, py + 66.0f, buf, 2.0f, COL_TEXT);

    cs[1] = 0;
    for (y = 0; y < 4; y++) {
        for (x = 0; x < KB_COLS; x++) {
            int sel = (x == kb_x && y == kb_y);
            if (sel)
                mp_draw_box(gx0 + x * ch - 2.0f + (cw - ch) * 0.0f, gy0 + y * ch - 3.0f, 30.0f, 30.0f, COL_SEL);
            cs[0] = kb_chars[y][x];
            mp_draw_text_centered(gx0 + x * ch + 13.0f, gy0 + y * ch, cs, 2.0f, sel ? 0x000000FF : COL_TEXT);
        }
    }
    for (i = 0; i < 3; i++) {
        int sel = (kb_y == 4 && kb_x >= wide_x[i] && kb_x < wide_x[i] + wide_w[i]);
        f32 bx = gx0 + wide_x[i] * ch - 2.0f, bw = wide_w[i] * ch - 8.0f;
        mp_draw_box(bx, gy0 + 4 * ch - 3.0f, bw, 30.0f, sel ? COL_SEL : 0x30304880);
        mp_draw_text_centered(bx + bw * 0.5f, gy0 + 4 * ch + 3.0f, wide[i], 1.5f, sel ? 0x000000FF : COL_TEXT);
    }
    mp_draw_text_centered(320.0f, py + 280.0f, "A TYPE   B DELETE   START DONE", 1.0f, COL_DIM);
}

void mp_ui_draw(void)
{
    switch (mp.mode) {
    case MP_SOLO:
        if (mp.in[1].connected)
            mp_draw_text_centered(320.0f, 440.0f, "PLAYER 2: PRESS START TO JOIN", 1.5f,
                                  ((mp.frame >> 5) & 1) ? 0x60C0FFFF : 0x60C0FF90);
        break;
    case MP_NAMING:
        draw_keyboard();
        break;
    case MP_COOP:
        break;
    }
}
