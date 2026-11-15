/* Multiplayer mod: spawning player 2 (a second Player actor from the game's own Player pool,
   initialised from the same level data as player 1). See hm-work/mp/spawn_p2.md. */
#include "mp.h"
#include "mp_state.h"

void *fn_8023CA4C(void *mgr, void *classKey);                       /* pool: first free item of class */
void fn_80076FF0(void *pl, void *q, void *mgr, void *node, void *c);  /* Player: bind data + world node */
int fn_80077010(void *pl);                                           /* Player: Start */
void fn_80076E94(void *pl);                                          /* Player: post-load link */
void fn_80074AF4(void *pl, f32 dt);                                  /* Player: update */

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

/* The input listener every gameplay object reads: *(lbl_8035B65C) + 0x770, 0x54 bytes. */
#define INPUT_STRUCT() ((u8 *)*(void **)0x8035B65C + 0x770)
static u8 s_p2_input[0x54];

int mp_spawn_p2(void)
{
    void *p0 = mp_player[0], *p1, *mgr = *(void **)0x8035B308;
    void *q, *c, *d, *saved48, *saved_owner;
    static const char cls[8] = "Player";
    static const char name2[8] = "zeke2";
    int i;

    if (!p0 || !mgr || mp_player[1])
        return 0;
    q = PTR(p0, 0x0c);
    c = PTR(p0, 0x10);
    d = PTR(p0, 0x9c);
    if (!q || !c || !d)
        return 0;
    saved48 = PTR(mgr, 0x48);
    saved_owner = PTR(d, 0x3c);
    p1 = fn_8023CA4C(mgr, (void *)cls);
    OSReport("[mp] spawn: p0 %p -> pool gave %p (owner %p)\n", p0, p1, saved_owner);
    if (!p1 || p1 == p0)
        return 0;
    fn_80076FF0(p1, q, mgr, d, c);
    U32(mgr, 0x54)++;
    PTR(mgr, 0x48) = saved48;
    PTR(d, 0x3c) = saved_owner;
    for (i = 0; i < 8; i++)
        ((char *)p1 + 0x8c)[i] = name2[i];
    fn_80076E94(p1);
    OSReport("[mp] spawn: linked, +434 %p +424 %p\n", PTR(p1, 0x434), PTR(p1, 0x424));
    fn_80077010(p1);
    PTR(mgr, 0x48) = saved48;
    PTR(d, 0x3c) = saved_owner;
    mp_player[1] = p1;
    mp_player_seen[1] = mp_render_frame;
    for (i = 0; i < 0x54; i++)
        s_p2_input[i] = INPUT_STRUCT()[i];
    OSReport("[mp] spawn: player 2 is %p\n", p1);
    return 1;
}

/* Called right after player 1's update each frame. */
void mp_update_p2(f32 dt)
{
    u8 *in = INPUT_STRUCT(), saved[0x54];
    int i;
    if (!mp_player[1])
        return;
    for (i = 0; i < 0x54; i++) {
        saved[i] = in[i];
        in[i] = s_p2_input[i];
    }
    fn_80074AF4(mp_player[1], dt);
    for (i = 0; i < 0x54; i++) {
        s_p2_input[i] = in[i];
        in[i] = saved[i];
    }
    mp_player_seen[1] = mp_render_frame;
}

/* Fill player 2's input struct from controller 2 (layout observed for player 1). */
void mp_fill_p2_input(const PADStatus *st)
{
    u8 *s = s_p2_input;
    u16 b = st->button;
#define AX(o) (*(f32 *)(s + (o)))
#define BT(o) (*(u32 *)(s + (o)))
    AX(0x08) = st->stickY / 127.0f;   /* forward */
    AX(0x0c) = st->stickX / 127.0f;   /* turning */
    AX(0x10) = st->substickX / 127.0f;
    AX(0x14) = st->substickY / 127.0f;
    BT(0x28) = (b & PAD_BUTTON_X) != 0;
    BT(0x34) = (b & PAD_TRIGGER_R) != 0;
    BT(0x38) = (b & PAD_BUTTON_B) != 0;
    BT(0x3c) = (b & PAD_BUTTON_Y) != 0;
    BT(0x40) = (b & PAD_TRIGGER_L) != 0;
    BT(0x2c) = (b & PAD_BUTTON_A) != 0;
#undef AX
#undef BT
}
