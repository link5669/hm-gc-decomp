/* Multiplayer mod: entry points and hooks. Built by tools/mp/build_mp.py, not by configure.py. */
#include "mp.h"
#include "mp_draw.h"
#include "mp_state.h"
#include "mp_split.h"

s32 fn_800629DC(void *a, s32 b, s32 c);
void fn_800326D0(void *game, void *gx);
void mp_debug_mtx(void);
int mp_coop_render(void *game, void *gx);

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
    extern void *mp_main_cam;
    mp_render_frame++;
    mp_main_cam = *(void **)((u8 *)game + 0x28);
    if (mp.mode == MP_COOP && mp_player[1] && mp_render_frame - mp_player_seen[1] <= 2)
        split = mp_coop_render(game, gx);
    if (!split)
        fn_800326D0(game, gx);
    mp_debug_mtx();
    mp_draw_begin();
    if (mp.mode == MP_COOP) {
        if (split) {
            mp_draw_tags(*(void **)((u8 *)game + 0x28), 0.0f, 0.0f, 320.0f, 480.0f);
            mp_draw_tags(mp_split_cam2(), 320.0f, 0.0f, 320.0f, 480.0f);
            mp_draw_box(319.0f, 0.0f, 2.0f, 480.0f, 0x000000FF);
        } else {
            mp_draw_tags(*(void **)((u8 *)game + 0x28), 0.0f, 0.0f, 640.0f, 480.0f);
        }
    }
    mp_ui_draw();
}

void fn_800786B8(void *player);
void *mp_player[2];
u32 mp_player_seen[2];  /* render frame in which each player was last updated */
u32 mp_render_frame;

/* Hook: Player factory -> Player init. Records created players (debug: logs who created them). */
void mp_player_created(void *player)
{
    fn_800786B8(player);
    (void)player;
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
int mp_spawn_p2(void);
void mp_update_p2(f32 dt);
void *fn_800F9398(void *table, const char *name);
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
        if (s_nupdated == 1) {
            u8 *d = *(u8 **)((u8 *)player + 0x9c);
            u8 *w = *(u8 **)(*(u8 **)0x8035B460 + 8);
            void *t = fn_800F9398(w + 0x90, (char *)player + 0x8c);
            OSReport("[mp] P0 %p d %p type %d d[0] %08x d+4 %08x name '%.8s' tmpl %p q %p c %p\n", player, d,
                     d ? *(u16 *)(d + 4) : -1, d ? *(u32 *)d : 0, d ? *(u32 *)(d + 4) : 0, (char *)player + 0x8c, t,
                     *(void **)((u8 *)player + 0xc), *(void **)((u8 *)player + 0x10));
        }
    }
    if (player == mp_player[1]) {  /* normally unreachable: player 2 is updated by mp_update_p2 */
        fn_80074AF4(player, dt);
        return;
    }
    if (player != mp_player[0]) {
        mp_player[0] = player;     /* new level: the old player 2 died with the old pool */
        mp_player[1] = 0;
    }
    mp_player_seen[0] = mp_render_frame;
    fn_80074AF4(player, dt);
    if (mp.want_spawn) {
        mp.want_spawn = 0;
        OSReport("[mp] spawn request: mode %d p1 %p\n", mp.mode, mp_player[1]);
        if (mp.mode == MP_COOP && !mp_player[1])
            mp_spawn_p2();
    }
    mp_update_p2(dt);
}
