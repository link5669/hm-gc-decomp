/* Multiplayer mod: name tags above the players' heads. */
#include "mp.h"
#include "mp_state.h"
#include "mp_split.h"
#include "mp_draw.h"

f32 tanf(f32);
extern u8 lbl_803286D0[];


#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))


int mp_player_pos(void *player, f32 *pos)
{
    /* same as the follow camera: target->vtbl[13](&pos, 0, 0, 0, 0) */
    void (*getpos)(void *, f32 *, int, int, int, int);
    if (!player || !*(void **)player)
        return 0;
    getpos = (void (*)(void *, f32 *, int, int, int, int))PTR(*(void **)player, 0x3c);
    getpos(player, pos, 0, 0, 0, 0);
    return 1;
}


/* Project world point w with the captured world-pass matrices of pane into screen rect (x0,y0,sw,sh). */
extern f32 mp_view[2][16], mp_proj[2][16];
extern u8 mp_have_mtx[2];
static int project(int pane, const f32 *w, f32 x0, f32 y0, f32 sw, f32 sh, f32 *sx, f32 *sy)
{
    const f32 *v = mp_view[pane], *p = mp_proj[pane];
    f32 e[3], cx, cy, cw;
    int i;
    if (!mp_have_mtx[pane])
        return 0;
    for (i = 0; i < 3; i++)
        e[i] = v[i * 4 + 0] * w[0] + v[i * 4 + 1] * w[1] + v[i * 4 + 2] * w[2] + v[i * 4 + 3];
    cx = p[0] * e[0] + p[1] * e[1] + p[2] * e[2] + p[3];
    cy = p[4] * e[0] + p[5] * e[1] + p[6] * e[2] + p[7];
    cw = p[12] * e[0] + p[13] * e[1] + p[14] * e[2] + p[15];
    if (cw < 0.05f)
        return 0;
    *sx = x0 + (cx / cw + 1.0f) * 0.5f * sw;
    *sy = y0 + (1.0f - cy / cw) * 0.5f * sh;
    return 1;
}

static const u32 tag_col[2] = {0xFFB070FF, 0x80D0FFFF};

/* Draw every player's tag as seen by camera cam in screen rect; panes: call once per pane. */
void mp_draw_tags(void *cam, f32 x0, f32 y0, f32 sw, f32 sh)
{
    int i;
    f32 p[3], sx, sy;
    if (!cam)
        return;
    for (i = 0; i < 2; i++) {
        if (!mp.named[i] || mp_render_frame - mp_player_seen[i] > 2 || !mp_player_pos(mp_player[i], p))
            continue;
        p[2] += 1.7f;  /* world is Z-up: above the head */
        if (!project(x0 > 0.0f ? 1 : 0, p, x0, y0, sw, sh, &sx, &sy))
            continue;
        if (sx < x0 - 40.0f || sx > x0 + sw + 40.0f || sy < y0 || sy > y0 + sh)
            continue;
        mp_draw_text_centered(sx, sy - 12.0f, mp.name[i], 1.0f, tag_col[i]);
    }
}

extern f32 mp_view[2][16], mp_proj[2][16];
extern u8 mp_have_mtx[2];

void mp_debug_mtx(void) {}

/* Player 2's own health bar and lives, bottom right (player 1 keeps the game's HUD). */
extern s32 mp_p2_lives;
void mp_draw_p2_hud(void)
{
    void *p2 = mp_player[1];
    f32 hp, max, frac, x = 452.0f, y = 400.0f;
    char buf[16];
    int n;
    {
        extern int mp_in_title;
        if (!p2 || mp.mode != MP_COOP || mp_in_title || mp_render_frame - mp_player_seen[1] > 2)
            return;
    }
    hp = *(f32 *)((u8 *)p2 + 0x1ac);
    max = *(f32 *)((u8 *)p2 + 0x1a8);
    frac = max > 0.0f ? hp / max : 0.0f;
    if (frac < 0.0f) frac = 0.0f;
    if (frac > 1.0f) frac = 1.0f;
    mp_draw_text(x, y - 18.0f, mp.name[1], 1.0f, tag_col[1]);
    mp_draw_box(x - 2.0f, y - 2.0f, 124.0f, 14.0f, 0x000000C0);
    mp_draw_box(x, y, 120.0f * frac, 10.0f, frac > 0.3f ? 0x3070E0FF : 0xE04040FF);
    n = mp_p2_lives;
    buf[0] = 'x'; buf[1] = (char)('0' + (n > 9 ? 9 : n < 0 ? 0 : n)); buf[2] = 0;
    mp_draw_text(x + 128.0f, y - 2.0f, buf, 1.0f, 0xFFFFFFFF);
    if (n <= 0 && hp <= 0.0f)
        mp_draw_text_centered(x + 60.0f, y + 16.0f, "OUT OF LIVES - START TO REJOIN", 1.0f, 0xE04040FF);
}
