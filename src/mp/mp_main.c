/* Multiplayer mod: entry points and hooks. Built by tools/mp/build_mp.py, not by configure.py. */
#include "mp.h"
#include "mp_draw.h"

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
    fn_800326D0(game, gx);
    mp_draw_begin();
    mp_draw_box(16.0f, 16.0f, 200.0f, 28.0f, 0x20104080);
    mp_draw_text(24.0f, 20.0f, "CO-OP MOD", 2.0f, 0xFFE070FF);
}
