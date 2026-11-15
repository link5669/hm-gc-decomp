/* Multiplayer mod: debug menu (Z + START on either controller, in gameplay).
   - PLAYER 2: AI / HUMAN
   - warp to any area: loads the level and sets the progress (spirits, lantern) for that point of the game */
#include <dolphin/pad.h>
#include "mp.h"
#include "mp_state.h"
#include "mp_draw.h"

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
extern char lbl_802AFFF8[];  /* level table: 8-byte keys */
void mp_apply_progress(const char *key8);
int mp_area_count(void);
const char *mp_area_label(int i);
void mp_area_key(int i, char *key8);
void mp_apply_area_progress(int i);
int mp_in_gameplay_now(void);
int mp_area_name(const char *key8, char *out, int n);

static int s_sel, s_top, s_nlevels;
static int s_owner;  /* controller that opened the menu */
#define VISIBLE 11

static int count_levels(void)
{
    int n = 0;
    while (n < 48 && lbl_802AFFF8[n * 8] >= 'A' && lbl_802AFFF8[n * 8] <= 'Z')
        n++;
    return n;
}

void mp_load_level_key(const char *key)
{
    u8 *fw = *(u8 **)0x8035B65C;
    char k[8];
    int i;
    for (i = 0; i < 8; i++)
        k[i] = key[i];
    if (fw && PTR(fw, 0x2f0))
        ((void (*)(void *, void *))PTR(PTR(fw, 0x2f0), 0x3c))(fw, k);
}

/* called once per frame from the UI update */
void mp_menu_update(void)
{
    int c, items;
    if (!mp.menu_open) {
        for (c = 0; c < 2; c++) {
            MpInput *in = &mp.in[c];
            if ((in->held & PAD_TRIGGER_Z) && (in->pressed & PAD_BUTTON_START) && mp_in_gameplay_now()) {
                mp.menu_open = 1;
                s_owner = c;
                s_nlevels = mp_area_count();
                in->pressed = 0;
                return;
            }
        }
        return;
    }
    items = 1 + s_nlevels;
    {
        MpInput *in = &mp.in[s_owner];
        if (in->pressed & PAD_BUTTON_UP)
            s_sel = (s_sel + items - 1) % items;
        if (in->pressed & PAD_BUTTON_DOWN)
            s_sel = (s_sel + 1) % items;
        if (s_sel < s_top)
            s_top = s_sel;
        if (s_sel >= s_top + VISIBLE)
            s_top = s_sel - VISIBLE + 1;
        if (in->pressed & (PAD_BUTTON_B | PAD_BUTTON_START)) {
            mp.menu_open = 0;
        } else if (in->pressed & PAD_BUTTON_A) {
            if (s_sel == 0) {
                mp.p2_ai ^= 1;
            } else {
                char key[8];
                mp_area_key(s_sel - 1, key);
                mp.menu_open = 0;
                OSReport("[mp] debug menu: warp to '%.8s'\n", key);
                mp_apply_area_progress(s_sel - 1);
                mp_load_level_key(key);
            }
        }
    }
}

void mp_menu_draw(void)
{
    int i;
    f32 x = 150.0f, y = 70.0f;
    char name[24];
    if (!mp.menu_open)
        return;
    mp_draw_box(x, y, 340.0f, 360.0f, 0x101028E8);
    mp_draw_box(x, y, 340.0f, 3.0f, 0xFFE070FF);
    mp_draw_text_centered(320.0f, y + 10.0f, "DEBUG MENU", 2.0f, 0xFFE070FF);
    for (i = 0; i < VISIBLE && s_top + i < 1 + s_nlevels; i++) {
        int it = s_top + i;
        f32 ly = y + 44.0f + i * 26.0f;
        u32 col = it == s_sel ? 0x000000FF : 0xE8E8F0FF;
        if (it == s_sel)
            mp_draw_box(x + 10.0f, ly - 4.0f, 320.0f, 24.0f, 0x60C0FFFF);
        if (it == 0) {
            mp_draw_text(x + 20.0f, ly, mp.p2_ai ? "PLAYER 2: AI" : "PLAYER 2: HUMAN", 1.5f, col);
        } else {
            const char *nm = mp_area_label(it - 1);
            char line[40];
            int n = 0, k;
            const char *w = "WARP: ";
            while (*w)
                line[n++] = *w++;
            for (k = 0; nm[k] && n < 38; k++)
                line[n++] = nm[k];
            line[n] = 0;
            mp_draw_text(x + 20.0f, ly, line, 1.5f, col);
        }
    }
    mp_draw_text_centered(320.0f, y + 336.0f, "D-PAD MOVE   A SELECT   B CLOSE", 1.0f, 0x9090A0FF);
}
