/* Multiplayer mod: entry points and hooks. Built by tools/mp/build_mp.py, not by configure.py. */
#include "mp.h"
#include "mp_draw.h"
#include "mp_state.h"
#include "mp_split.h"

s32 fn_800629DC(void *a, s32 b, s32 c);
void fn_800326D0(void *game, void *gx);
void mp_debug_mtx(void);
int mp_coop_render(void *game, void *gx);
void mp_draw_p2_hud(void);

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
    mp_game = game;
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
    mp_draw_p2_hud();
    mp_ui_draw();
}

void fn_800786B8(void *player);
void *mp_player[2];
u32 mp_player_seen[2];  /* render frame in which each player was last updated */
u32 mp_render_frame;
void *mp_game;  /* the Game object (from the Render hook) */

/* Hook: Player factory -> Player init. Records created players (debug: logs who created them). */
void mp_player_created(void *player)
{
    fn_800786B8(player);
    (void)player;
}

void fn_80074AF4(void *player, f32 dt);

int mp_spawn_p2(void);
static int s_p0_frames;
void mp_update_p2(f32 dt);

/* Hook: Player vtable slot "update" (per frame): tracks player 1, spawns and updates player 2. */
void mp_player_update(void *player, f32 dt)
{
    if (player == mp_player[1])  /* player 2 is updated only by mp_update_p2 (with its own input) */
        return;
    if (player != mp_player[0]) {
        mp_player[0] = player;     /* new level: the old player 2 died with the old pool */
        mp_player[1] = 0;
        s_p0_frames = 0;
    }
    mp_player_seen[0] = mp_render_frame;
#ifdef MP_DEBUG_INPUT
    {
        /* log every change of player 1's input struct, with the raw pad state */
        static u32 last[0x15];
        u32 *in = (u32 *)((u8 *)*(void **)0x8035B65C + 0x770);
        int k, ch = 0;
        for (k = 2; k < 0x15; k++)
            if (in[k] != last[k])
                ch = 1;
        if (ch) {
            OSReport("[mp] IN btn %04x st %d %d c %d %d:", mp.in[0].held, mp.in[0].sx, mp.in[0].sy, 0, 0);
            for (k = 2; k < 0x15; k++) {
                if (in[k] != last[k])
                    OSReport(" +%02x=%08x", k * 4, in[k]);
                last[k] = in[k];
            }
            OSReport("\n");
        }
    }
#endif
    fn_80074AF4(player, dt);
    /* player 2 appears once player 1 has been in control for a moment (after loads/intros) */
    if (mp.mode == MP_COOP && !mp_player[1]) {
        if (!mp_in_gameplay())
            s_p0_frames = 0;
        else if (++s_p0_frames > 90)
            mp_spawn_p2();
    } else {
        s_p0_frames = 0;
    }
    if (mp.mode == MP_COOP)
        mp_update_p2(dt);
}

void fn_80228A48(void *mgr, f32 dt);

/* Hook: per-frame actor update (players, enemies, objects). Paused while a player types a name. */
void mp_actor_update(void *mgr, f32 dt)
{
    if (mp.mode == MP_NAMING)
        return;
    fn_80228A48(mgr, dt);
}

extern u32 mp_hud_seen;
/* True while the in-game HUD is being drawn (= real gameplay, not menus, movies or loading). */
int mp_in_gameplay(void)
{
    /* HUD drawn + player 1 being updated + a room/spawn key set (front-end scenes have none) */
    u8 *lm = *(u8 **)0x8035B684;
    int hud = mp_render_frame - mp_hud_seen <= 3;
    int p0 = mp_player[0] && mp_render_frame - mp_player_seen[0] <= 3;
    /* cutscenes: the cinema letterbox (Game+0xb70, as Game::Render tests it) is active */
    u8 *cine = mp_game ? *(u8 **)((u8 *)mp_game + 0xb70) : 0;
    int cinema = cine && (*(s32 *)(cine + 0x284) != 0 || *(f32 *)(cine + 0x290) != 0.0f);
    static u32 since, last_frame;
    int ok = hud && p0 && lm && lm[0x1b8] != 0 && !cinema;
    /* must hold for 2 s of rendered frames (cinematics play outside Game::Render, freezing these signals) */
    if (!ok || mp_render_frame - last_frame > 2)
        since = mp_render_frame;
    last_frame = mp_render_frame;
    return ok && mp_render_frame - since >= 120;
}
