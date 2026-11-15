/* Multiplayer mod: entry points and hooks. Built by tools/mp/build_mp.py, not by configure.py. */
#include "mp.h"
#include "mp_draw.h"
#include "mp_state.h"
#include "mp_split.h"

s32 fn_800629DC(void *a, s32 b, s32 c);
void fn_800326D0(void *game, void *gx);

/* Hook: first call in main(), before the game sets up its heaps. */
s32 mp_hook_main_init(void *a, s32 b, s32 c)
{
    OSReport("[mp] multiplayer mod loaded\n");
    return fn_800629DC(a, b, c);
}

/* Hook: Game::Render (vtable slot). Draw the game, then our overlay on top. */
void mp_game_render(void *game, void *gx)
{
    int split = 0;
    if (mp.mode == MP_COOP && mp.debug_split) {
        /* debug: second view = player 1's camera moved 400 units to its right */
        void *cam1 = *(void **)((u8 *)game + 0x28);
        if (cam1) {
            f32 eye[3], r[3], u[3], f[3], at[3];
            int i;
            mp_cam_get_pos(cam1, eye);
            mp_cam_get_basis(cam1, r, u, f);
            for (i = 0; i < 3; i++) {
                eye[i] += r[i] * (mp.debug_split == 2 ? 400.0f : 0.0f);
                at[i] = eye[i] + f[i] * 100.0f;
            }
            split = mp_split_render(game, gx, eye, at);
        }
    }
    if (!split)
        fn_800326D0(game, gx);
    mp_draw_begin();
    mp_ui_draw();
}

void fn_800786B8(void *player);
void *mp_player[2];

/* Hook: Player factory -> Player init. Records created players (debug: logs who created them). */
void mp_player_created(void *player)
{
    fn_800786B8(player);
    mp_backtrace("Player created", (u32)player, 0);
    if (!mp_player[0])
        mp_player[0] = player;
}

void fn_80074AF4(void *player, f32 dt);

static void mp_dump_players(void *p0)
{
    int k, off;
    for (k = 0; k < 4; k++) {
        u32 *w = (u32 *)((u8 *)p0 + k * 0x744);
        for (off = 0; off < 0x744 / 4; off += 8)
            OSReport("[mp] D%d %03x %08x %08x %08x %08x %08x %08x %08x %08x\n", k, off * 4, w[off], w[off + 1], w[off + 2],
                     w[off + 3], w[off + 4], w[off + 5], w[off + 6], w[off + 7]);
    }
}
static void *s_updated[8];
static int s_nupdated;

/* Hook: Player vtable slot "update" (per frame). Debug: log which Player instances are updated. */
void mp_player_update(void *player, f32 dt)
{
    int i;
    for (i = 0; i < s_nupdated; i++)
        if (s_updated[i] == player)
            break;
    if (i == s_nupdated && s_nupdated < 8) {
        s_updated[s_nupdated++] = player;
        mp_backtrace("Player update", (u32)player, (u32)s_nupdated);
        if (s_nupdated == 1)
            mp_dump_players(player);
    }
    fn_80074AF4(player, dt);
}
