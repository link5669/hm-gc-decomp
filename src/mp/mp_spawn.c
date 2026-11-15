/* Multiplayer mod: spawning player 2 (a second Player actor from the game's own Player pool,
   initialised from the same level data as player 1). See hm-work/mp/spawn_p2.md. */
#include "mp.h"
#include "mp_state.h"

void *fn_8023CA4C(void *mgr, void *classKey);                       /* pool: first free item of class */
void fn_80076FF0(void *pl, void *q, void *mgr, void *node, void *c);  /* Player: bind data + world node */
int fn_80077010(void *pl);                                           /* Player: Start */
void fn_80076E94(void *pl);
void fn_80078980(void *pl);  /* Player: stop */                                          /* Player: post-load link */
void fn_80074AF4(void *pl, f32 dt);                                  /* Player: update */

void *__nw__FUl(u32 size);
void *__ct__9C801883E0Fv(void *self);
void fn_80188144(void *dst, void *world, void *src, int flags);  /* world node clone (model + body) */
void fn_8019B7E8(void *scene, void *node);                       /* add node to the scene draw list */
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
void fn_80190C98(void *node);
extern u8 lbl_803286D0[];
extern void *lbl_8035B320, *lbl_8035B460, *lbl_8035B65C;

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))

/* The input listener every gameplay object reads: *(lbl_8035B65C) + 0x770, 0x54 bytes. */
#define INPUT_STRUCT() ((u8 *)*(void **)0x8035B65C + 0x770)
static u8 s_p2_input[0x54];
static int s_p2_statics_init;
static int s_place_p2;  /* put player 2 next to player 1 before its next update */
static void give_p2_lantern(void *p0, void *p1);
static void give_p2_camera(void *p0, void *p1);
static void give_p2_nodes(void *p0, void *p1);
void mp_teleport_p2_to_p1(void);
void mp_split_reset(void);
/* Runtime-cloned world nodes are not in the world's update list (fn_80192488), so their animation
   would never advance: tick them ourselves each frame. */
void fn_80187EE0(void *node, f32 dt);
static void *s_cloned[24];
static int s_ncloned;
static void *clone_node(void *d);
void fn_80190940(void *child, void *parent);
void fn_8019B6B8(void *scene, void *node);

/* Zeke's visible meshes are child nodes of the body node that share its model (flag 0x40000): clone them
   under player 2's body so they take player 2's pose. */
static void clone_kids(void *d, void *d2)
{
    void *k, *k2;
    int n = 0;
    for (k = PTR(d, 0x58); k && n < 16; k = PTR(k, 0x54), n++) {
        OSReport("[mp] kid %p type %d fl %08x a8 %p (parent a8 %p) 88 %p\n", k, *(u16 *)((u8 *)k + 4), U32(k, 0),
                 PTR(k, 0xa8), PTR(d, 0xa8), PTR(k, 0x88));
        if (*(u16 *)((u8 *)k + 4) != 3)
            continue;
        fn_800F7EC0(lbl_8035B320);
        k2 = __nw__FUl(0xcc);
        if (k2)
            __ct__9C801883E0Fv(k2);
        fn_800F7E98();
        if (!k2)
            continue;
        fn_80188144(k2, PTR(lbl_8035B460, 8), k, (int)((U32(k, 0) & 0x40000) ? d2 : 0));
        U32(k2, 0) &= ~0x800u;
        PTR(k2, 0x3c) = 0;
        fn_80190940(k2, d2);
        if (PTR(k2, 0x88) == 0)
            fn_8019B7E8(PTR(lbl_8035B65C, 0xc), k2);
        OSReport("[mp]   -> %p a8 %p (d2 a8 %p)\n", k2, PTR(k2, 0xa8), PTR(d2, 0xa8));
    }
}
s32 mp_p2_lives, mp_p2_hp, mp_p2_maxhp, mp_p2_respawns;
void fn_8006B6C8(void *pl);  /* Player: full heal */

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
    /* player 2 gets its own copy of the "zeke" world node (model instance + physics body) */
    s_ncloned = 0;
    mp_split_reset();
    {
        void *d0 = d;
        d = clone_node(d0);
        if (!d)
            return 0;
        clone_kids(d0, d);
        {
            u8 *m1 = PTR(d0, 0xa8), *m2 = PTR(d, 0xa8);
            OSReport("[mp] mdl d %p d2 %p | 24: %p %p | 90: %p %p\n", m1, m2, m1 ? PTR(m1, 0x24) : 0, m2 ? PTR(m2, 0x24) : 0,
                     PTR(d0, 0x90), PTR(d, 0x90));
            if (m1 && m2 && PTR(m1, 0x24) && PTR(m2, 0x24))
                OSReport("[mp] elem0 10/14: %p %p | %p %p\n", PTR(PTR(m1, 0x24), 0x10), PTR(PTR(m1, 0x24), 0x14),
                         PTR(PTR(m2, 0x24), 0x10), PTR(PTR(m2, 0x24), 0x14));
        }
    }
#ifdef MP_TEST_HIDE_BODY
    U32(d, 0) |= 0x800u;
#endif
    saved48 = PTR(mgr, 0x48);
    saved_owner = PTR(PTR(p0, 0x9c), 0x3c);
    p1 = fn_8023CA4C(mgr, (void *)cls);
    OSReport("[mp] spawn: p0 %p -> pool gave %p (owner %p)\n", p0, p1, saved_owner);
    if (!p1 || p1 == p0)
        return 0;
    fn_80076FF0(p1, q, mgr, d, c);
    U32(mgr, 0x54)++;
    PTR(mgr, 0x48) = saved48;
    PTR(PTR(p0, 0x9c), 0x3c) = saved_owner;
    for (i = 0; i < 8; i++)
        ((char *)p1 + 0x8c)[i] = name2[i];
    fn_80076E94(p1);
    give_p2_lantern(p0, p1);
    give_p2_camera(p0, p1);
    OSReport("[mp] spawn: linked, +434 %p +424 %p\n", PTR(p1, 0x434), PTR(p1, 0x424));
    {
        s32 *v540 = PTR(p0, 0x540), *v544 = PTR(p0, 0x544), *v548 = PTR(p0, 0x548);
        s32 l = v540 ? *v540 : 0, h = v544 ? *v544 : 0, m = v548 ? *v548 : 0;

        fn_80077010(p1);
        if (v540) *v540 = l;
        if (v544) *v544 = h;
        if (v548) *v548 = m;
        /* player 2 keeps its own lives and HP mirrors (health floats +0x1AC/+0x1A8 are per Player already) */
        mp_p2_lives = PTR(p1, 0x53c) ? *(s32 *)PTR(p1, 0x53c) : 3;
        if (mp_p2_lives <= 0 || mp_p2_lives > 9)
            mp_p2_lives = l > 0 ? l : 3;
        mp_p2_hp = (s32)*(f32 *)((u8 *)p1 + 0x1ac);
        mp_p2_maxhp = (s32)*(f32 *)((u8 *)p1 + 0x1a8);
        PTR(p1, 0x540) = &mp_p2_lives;
        PTR(p1, 0x544) = &mp_p2_hp;
        PTR(p1, 0x548) = &mp_p2_maxhp;
    }
    give_p2_nodes(p0, p1);
    PTR(mgr, 0x48) = saved48;
    PTR(PTR(p0, 0x9c), 0x3c) = saved_owner;
    mp_player[1] = p1;
    mp_player_seen[1] = mp_render_frame;
    s_p2_statics_init = 0;
    /* player 2 starts next to player 1 (positioned on its first update, see mp_update_p2) */
    s_place_p2 = 1;
    for (i = 0; i < 0x54; i++)
        s_p2_input[i] = INPUT_STRUCT()[i];
    {
        u8 *pl1 = PTR(p0, 0xb8), *pl2 = PTR(p1, 0xb8);
        OSReport("[mp] anim link P1 b8 %p idx %d own %p | P2 b8 %p idx %d own %p | P2 b0 %d\n", pl1, pl1 ? U32(pl1, 8) : -1,
                 pl1 ? PTR(pl1, 0xc) : 0, pl2, pl2 ? U32(pl2, 8) : -1, pl2 ? PTR(pl2, 0xc) : 0, U32(p1, 0xb0));
    }
    {
        u8 *b2 = PTR(p1, 0x20c), *b1 = PTR(p0, 0x20c);
        u32 i2;
        OSReport("[mp] BPlayer2 e0 %p 118 %p | BPlayer1 e0 %p 118 %p\n", b2 ? PTR(b2, 0xe0) : 0, b2 ? PTR(b2, 0x118) : 0,
                 b1 ? PTR(b1, 0xe0) : 0, b1 ? PTR(b1, 0x118) : 0);
        if (b2)
            for (i2 = 0; i2 < 0x2a0; i2 += 4) {
                u8 *o = PTR(b2, i2);
                if ((u32)o >= 0x80400000 && (u32)o < 0x81800000 && ((u32)o & 3) == 0 && PTR(o, 0xe0) == p0)
                    OSReport("[mp] BPlayer2 +%03x -> %p whose owner(+e0) is P1 (vt %p)\n", i2, o, *(void **)o);
            }
    }
    OSReport("[mp] bplayer P1 %p vt %p | P2 %p vt %p\n", PTR(p0, 0x20c), PTR(p0, 0x20c) ? *(void **)PTR(p0, 0x20c) : 0,
             PTR(p1, 0x20c), PTR(p1, 0x20c) ? *(void **)PTR(p1, 0x20c) : 0);
    OSReport("[mp] spawn: player 2 is %p  9c %p a0 %p 424 %p | P1 9c %p a0 %p 424 %p\n", p1, PTR(p1, 0x9c), PTR(p1, 0xa0),
             PTR(p1, 0x424), PTR(p0, 0x9c), PTR(p0, 0xa0), PTR(p0, 0x424));
    return 1;
}

/* Single-player statics the Player update (and its movement/behaviour code) reads and writes: processed sticks,
   aim/look modes, camera push flags... Player 2 gets its own copy, swapped in only around its update. */
#define ST_A_BEGIN 0x8035A238
#define ST_A_SIZE (0x8035A2B0 - 0x8035A238)
typedef struct Statics { u8 a[ST_A_SIZE]; u32 b6e8, b6ec, s9748; } Statics;
static Statics s_p2_statics, s_p1_statics;

static void statics_save(Statics *t)
{
    int i;
    for (i = 0; i < ST_A_SIZE; i++)
        t->a[i] = ((u8 *)ST_A_BEGIN)[i];
    t->b6e8 = *(u32 *)0x8035B6E8;
    t->b6ec = *(u32 *)0x8035B6EC;
    t->s9748 = *(u32 *)0x80359748;
}

static void statics_load(const Statics *t)
{
    int i;
    for (i = 0; i < ST_A_SIZE; i++)
        ((u8 *)ST_A_BEGIN)[i] = t->a[i];
    *(u32 *)0x8035B6E8 = t->b6e8;
    *(u32 *)0x8035B6EC = t->b6ec;
    *(u32 *)0x80359748 = t->s9748;
}

/* Clone a level-loaded actor (same data record, new pool item), the way the level loader builds one
   (fn_802297E4) followed by what fn_802286C4 does after loading. Its world node is cloned too. */
void *fn_8010FEDC(void *q, void *c, const char *name, int one);
void fn_800F6E88(void *dst, const void *src);
extern char lbl_80365CEC[];  /* "TYPE" */
#define VT(o, off) (*(void **)((u8 *)*(void **)(o) + (off)))

static void *clone_node(void *d)
{
    void *d2;
    fn_800F7EC0(lbl_8035B320);
    d2 = __nw__FUl(0xcc);
    if (d2)
        __ct__9C801883E0Fv(d2);
    fn_800F7E98();
    if (!d2)
        return 0;
    fn_80188144(d2, PTR(lbl_8035B460, 8), d, 0);
    U32(d2, 0) &= ~0x800u;
    PTR(d2, 0x3c) = 0;
    if (s_ncloned < (int)(sizeof(s_cloned) / sizeof(s_cloned[0])))
        s_cloned[s_ncloned++] = d2;
    return d2;
}

static void *clone_actor(void *x0, const char *name8)
{
    void *mgr = *(void **)0x8035B308, *q = PTR(x0, 0x0c), *c = PTR(x0, 0x10), *d = PTR(x0, 0x9c), *d2 = d;
    void *saved48, *saved4c, *own = 0, *x2, **t;
    char key[8];
    int i;
    if (!q || !c || !(t = fn_8010FEDC(q, c, lbl_80365CEC, 1)) || !*t)
        return 0;
    fn_800F6E88(key, (u8 *)*t + 12);
    if (d && *(u16 *)((u8 *)d + 4) == 3)
        d2 = clone_node(d);
    saved48 = PTR(mgr, 0x48);
    saved4c = PTR(mgr, 0x4c);
    if (d)
        own = PTR(d, 0x3c);
    x2 = fn_8023CA4C(mgr, key);
    if (!x2 || x2 == x0)
        return 0;
    ((void (*)(void *, void *, void *, void *, void *))VT(x2, 0x24))(x2, q, mgr, d2, c);
    PTR(mgr, 0x48) = saved48;
    PTR(mgr, 0x4c) = saved4c;
    if (d)
        PTR(d, 0x3c) = own;
    U32(mgr, 0x54)++;
    for (i = 0; i < 8; i++)
        ((char *)x2 + 0x8c)[i] = name8[i];
    ((void (*)(void *))VT(x2, 0x34))(x2);
    /* (no stop() here: for a Camera it unbinds the actor completely) */
    ((void (*)(void *))VT(x2, 0x10))(x2);
    PTR(mgr, 0x48) = saved48;
    PTR(mgr, 0x4c) = saved4c;
    OSReport("[mp] cloned actor '%.8s' (%.8s) %p -> %p node %p\n", (char *)x0 + 0x8c, key, x0, x2, d2);
    return x2;
}

/* Replace pointers to player 1 (or its actors) inside an object with player 2's. */
static void repoint(void *obj, u32 size, void *from, void *to)
{
    u32 i;
    if (!obj)
        return;
    for (i = 0; i + 4 <= size; i += 4)
        if (*(void **)((u8 *)obj + i) == from)
            *(void **)((u8 *)obj + i) = to;
}

static void *s_lantern2;
void *mp_gamecam2;  /* player 2's own follow camera actor (clone of "GameCam") */
void fn_80223A50(void *cam, f32 dt);  /* Camera actor update */

static void give_p2_camera(void *p0, void *p1)
{
    void *c0 = PTR(p0, 0x258), *c2;
    static const char nm[8] = "gamcam2";
    mp_gamecam2 = 0;
    if (!c0)
        return;
    c2 = clone_actor(c0, nm);
    if (!c2)
        return;
    repoint(c2, 0x330, p0, p1);
    PTR(c2, 0x18c) = p1;
    PTR(p1, 0x258) = c2;
    mp_gamecam2 = c2;
}

/* Player 2's own lantern: separate beam, separate ghost catching (shared totals live in global vars). */
static void give_p2_lantern(void *p0, void *p1)
{
    void *l0 = PTR(p0, 0x434), *l2;
    static const char nm[8] = "lantrn2";
    s_lantern2 = 0;
    if (!l0)
        return;
    l2 = clone_actor(l0, nm);
    if (!l2)
        return;
    repoint(l2, 0x270, p0, p1);
    if (PTR(l2, 0x20c))
        repoint(PTR(l2, 0x20c), 0x2a0, p0, p1);
    PTR(p1, 0x434) = l2;
    s_lantern2 = l2;
}

/* World nodes the Player finds by name (lantern beam/reticle/charge effects, rings...): give player 2 copies
   so both players don't move the same effect nodes. */
static const u16 s_node_fields[] = {0x428, 0x42c, 0x430, 0x438, 0x43c, 0x440, 0x444, 0x448, 0x44c, 0x450,
                                    0x5f0, 0x62c, 0x718, 0x720, 0x740};

static void give_p2_nodes(void *p0, void *p1)
{
    int i;
    for (i = 0; i < (int)(sizeof(s_node_fields) / sizeof(s_node_fields[0])); i++) {
        u16 off = s_node_fields[i];
        void *n = PTR(p1, off), *n2;
        if (!n || n != PTR(p0, off) || *(u16 *)((u8 *)n + 4) != 3)
            continue;
        n2 = clone_node(n);
        if (!n2)
            continue;
        U32(n2, 0) |= U32(n, 0) & 0x800u;  /* keep hidden effects hidden until the player shows them */
        if (PTR(n, 0x48) && !PTR(n2, 0x48))
            fn_8019B7E8(PTR(lbl_8035B65C, 0xc), n2);
        PTR(p1, off) = n2;
        OSReport("[mp] p2 node +%03x %p -> %p\n", off, n, n2);
    }
}

/* Animation requests (fn_8022CC44) made while player 2 updates must go to player 2: its movement modules
   resolve their owner the single-player way and would animate player 1. */
static int s_in_p2;
void fn_8022CC44(void *o, void *anim, f32 a, s32 u, s32 b, s32 c, s32 q, f32 d);
void mp_anim_request(void *o, void *anim, f32 a, s32 u, s32 b, s32 c, s32 q, f32 d)
{
    static int logged;
    if (s_in_p2 && o == mp_player[0] && mp_player[1]) {
        if (logged < 3) {
            OSReport("[mp] anim request for P1 during P2 update -> P2 (anim %p)\n", anim);
            logged++;
        }
        o = mp_player[1];
    }
    fn_8022CC44(o, anim, a, u, b, c, q, d);
}

/* Move player 2 next to player 1 (spawn, respawn, debug). */
void mp_teleport_p2_to_p1(void)
{
    f32 pos[3];
    extern int mp_player_pos(void *player, f32 *pos);
    u8 *p2 = mp_player[1];
    if (!p2 || !mp_player_pos(mp_player[0], pos))
        return;
    pos[0] += 1.0f;
    pos[1] += 0.5f;
    *(f32 *)(p2 + 0x44) = pos[0];
    *(f32 *)(p2 + 0x48) = pos[1];
    *(f32 *)(p2 + 0x4c) = pos[2];
}

/* Called right after player 1's update each frame. */
void mp_update_p2(f32 dt)
{
    u8 *in = INPUT_STRUCT(), saved[0x54];
    void *mgr = *(void **)0x8035B308, *o72;
    int i;
    if (!mp_player[1])
        return;
    if (*(f32 *)((u8 *)mp_player[1] + 0x1ac) <= 0.0f) {
        /* player 2 was knocked out: lose a life and come back at full health (no global death event).
           Out of lives: player 2 sits out (see HUD). */
        if (mp_p2_lives > 0) {
            mp_p2_lives--;
            fn_8006B6C8(mp_player[1]);
            mp_p2_respawns++;
            s_place_p2 = 1;
        } else if (mp.p2_rejoin) {
            /* out of lives: player 2 pressed START to come back in with fresh lives */
            mp.p2_rejoin = 0;
            mp_p2_lives = 3;
            fn_8006B6C8(mp_player[1]);
            s_place_p2 = 1;
        } else {
            mp_player_seen[1] = mp_render_frame;
            return;
        }
    }
    if (s_place_p2) {
        s_place_p2 = 0;
        mp_teleport_p2_to_p1();
    }
    statics_save(&s_p1_statics);
    if (!s_p2_statics_init) {
        s_p2_statics = s_p1_statics;
        repoint(s_p2_statics.a, ST_A_SIZE, mp_player[0], mp_player[1]);
        s_p2_statics_init = 1;
    }
    statics_load(&s_p2_statics);
    if (s_lantern2) {
        void *bp = PTR(mp_player[1], 0x20c);  /* BPlayer re-looks up "lantern" when it starts */
        PTR(mp_player[1], 0x434) = s_lantern2;
        if (bp && PTR(bp, 0x1f0) && PTR(bp, 0x1f0) != s_lantern2)
            PTR(bp, 0x1f0) = s_lantern2;
    }
    for (i = 0; i < 0x54; i++) {
        saved[i] = in[i];
        in[i] = s_p2_input[i];
    }
    o72 = PTR(mgr, 0x48);
    /* o72 stays player 1 (swapping it routed player 2 input to player 1) */
    s_in_p2 = 1;
    fn_80074AF4(mp_player[1], dt);
    s_in_p2 = 0;
    PTR(mgr, 0x48) = o72;
    for (i = 0; i < 0x54; i++) {
        s_p2_input[i] = in[i];
        in[i] = saved[i];
    }
    for (i = 0; i < s_ncloned; i++)
        if (s_cloned[i] && PTR(s_cloned[i], 0x88) == 0)
            fn_80187EE0(s_cloned[i], dt);
    {
        /* the model actually drawn for a Player is its own instance at +0x424 (made at bind time) */
        void *inst = PTR(mp_player[1], 0x424);
        if (inst && PTR(inst, 0x88) == 0)
            fn_80187EE0(inst, dt);
    }
    if (0) {
        u8 *d2 = PTR(mp_player[1], 0xa0), *d1 = PTR(mp_player[0], 0xa0);
        OSReport("[mp] anim d2 %p 88 %p a8 %p b0 %p t %d | d1 88 %p b0 %p t %d | dt %d n %d\n", d2, PTR(d2, 0x88), PTR(d2, 0xa8),
                 PTR(d2, 0xb0), (int)(*(f32 *)((u8 *)PTR(d2, 0xb0) + 4) * 100), PTR(d1, 0x88), PTR(d1, 0xb0), (int)(*(f32 *)((u8 *)PTR(d1, 0xb0) + 4) * 100),
                 (int)(dt * 1000), s_ncloned);
    }
#ifdef MP_DEBUG_AUTOJOIN
    if (0 && (mp_render_frame % 20) == 0) {
        int k;
        for (k = 0; k < 2; k++) {
            u8 *P = mp_player[k], *pl = PTR(P, 0xb8), *tb = PTR(PTR(P, 0xa0), 0xb0), *t, *beh = PTR(P, 0x20c);
            u32 ix = pl ? U32(pl, 8) : 0;
            t = tb + ix * 0x3c;
            OSReport("[mp] P%d ix %d clip %p t %d spd %d fl %x w %d | vel %d %d %d k1a0 %d | stick %d %d | st %d\n", k + 1, ix,
                     PTR(t, 0x10), (int)(*(f32 *)(t + 4) * 100), (int)(*(f32 *)(t + 8) * 100), U32(t, 0),
                     (int)(*(f32 *)(t + 0x28) * 100), (int)(*(f32 *)(P + 0x118) * 100), (int)(*(f32 *)(P + 0x11c) * 100),
                     (int)(*(f32 *)(P + 0x120) * 100), (int)(*(f32 *)(P + 0x1a0) * 100), (int)(*(f32 *)(P + 0x500) * 100),
                     (int)(*(f32 *)(P + 0x504) * 100), beh ? U32(beh, 0xdc) : -1);
        }
    }
    if (mp.debug_kill) {
        mp.debug_kill = 0;
        *(f32 *)((u8 *)mp_player[1] + 0x1ac) = 0.0f;
        OSReport("[mp] debug: player 2 knocked out (lives %d)\n", mp_p2_lives);
    }
    if (mp.debug_teleport) {
        f32 a[3], b[3];
        extern int mp_player_pos(void *player, f32 *pos);
        mp.debug_teleport = 0;
        mp_player_pos(mp_player[0], a);
        mp_player_pos(mp_player[1], b);
        OSReport("[mp] debug: p1 %d %d %d p2 %d %d %d | P2+44 %d %d %d +458 %p P1+458 %p\n", (int)(a[0] * 10), (int)(a[1] * 10),
                 (int)(a[2] * 10), (int)(b[0] * 10), (int)(b[1] * 10), (int)(b[2] * 10),
                 (int)(*(f32 *)((u8 *)mp_player[1] + 0x44) * 10), (int)(*(f32 *)((u8 *)mp_player[1] + 0x48) * 10),
                 (int)(*(f32 *)((u8 *)mp_player[1] + 0x4c) * 10), PTR(mp_player[1], 0x458), PTR(mp_player[0], 0x458));
        mp_teleport_p2_to_p1();
    }
    if (mp.debug_hide) {
        void *hn = mp.debug_hide == 1 ? PTR(mp_player[1], 0xa0) : PTR(mp_player[1], 0x424);
        if (hn) {
            U32(hn, 0) &= ~0x4000u;
            fn_8019B6B8(PTR(lbl_8035B65C, 0xc), hn);
        }
    }
#endif
    statics_save(&s_p2_statics);
    statics_load(&s_p1_statics);
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
    {
        /* A is a one-shot for the game (it clears the flag once used): set it on the press only */
        static u16 prev;
        if ((b & PAD_BUTTON_A) && !(prev & PAD_BUTTON_A))
            BT(0x2c) = 1;
        prev = b;
    }
#undef AX
#undef BT
}
