/* Multiplayer mod: computer-controlled player 2 (debug menu: "PLAYER 2: AI").
   Fills player 2's input struct directly: follows player 1, fights the nearest enemy (lock on with L, fire with
   R in bursts, soul collector X when close). Runs inside player 2's update window, so it may scan actors. */
#include "mp.h"
#include "mp_state.h"

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))

void fn_8023C528(void *it, char *x);
void *fn_8023A490(void *a, void *b);
void fn_8023C3F4(void *it);
extern int mp_is_enemy_actor(u8 *o);
extern int mp_player_pos(void *player, f32 *pos);
static f32 sq(f32 x) { return x * x; }

static u8 *nearest_enemy(const f32 *from, f32 maxd, f32 *epos)
{
    u8 *mgr = *(u8 **)0x8035B308, *it, *o, *best = 0;
    f32 bd = maxd * maxd, d;
    int n = 0;
    if (!mgr || !(it = PTR(mgr, 0x50)))
        return 0;
    for (fn_8023C528(it, 0); PTR(it, 8) && n < 500; fn_8023C3F4(it), n++) {
        o = fn_8023A490(PTR(it, 8), PTR(it, 12));
        if (!o || !mp_is_enemy_actor(o))
            continue;
        d = sq(F32(o, 0x44) - from[0]) + sq(F32(o, 0x48) - from[1]) + sq(F32(o, 0x4c) - from[2]);
        if (d < bd) {
            bd = d;
            best = o;
            epos[0] = F32(o, 0x44); epos[1] = F32(o, 0x48); epos[2] = F32(o, 0x4c);
        }
    }
    return best;
}

/* Objects that hide ghosts (throbbing chests, baskets...: behaviour BSearch): walk up and press B (Activate). */
#define BSEARCH_VT 0x802b8068
static u8 *s_visited[64];
static int s_nvisited;
static int visited(u8 *o)
{
    int i;
    for (i = 0; i < s_nvisited; i++)
        if (s_visited[i] == o)
            return 1;
    return 0;
}
static u8 *nearest_hider(const f32 *from, const f32 *p1, f32 maxd, f32 *pos)
{
    u8 *mgr = *(u8 **)0x8035B308, *it, *o, *beh, *best = 0;
    f32 bd = maxd * maxd, d;
    int n = 0;
    if (!mgr || !(it = PTR(mgr, 0x50)))
        return 0;
    for (fn_8023C528(it, 0); PTR(it, 8) && n < 500; fn_8023C3F4(it), n++) {
        o = fn_8023A490(PTR(it, 8), PTR(it, 12));
        if (!o)
            continue;
        beh = PTR(o, MP_BEHAVIOUR_OFS);
#ifdef MP_DEBUG_AUTOJOIN
        {
            static int logged;
            if (logged < 12 && ((char *)o)[0x8c] == 'G' && ((char *)o)[0x8d] == 'H') {
                logged++;
                OSReport("[mp] AI scan: '%.8s' beh %p vt %08x\n", (char *)o + 0x8c, beh,
                         ((u32)beh & 0xFE000000) == 0x80000000 ? *(u32 *)beh : 0);
            }
        }
#endif
        if (((u32)beh & 0xFE000000) != 0x80000000 || *(u32 *)beh != BSEARCH_VT || visited(o))
            continue;
        d = sq(F32(o, 0x44) - from[0]) + sq(F32(o, 0x48) - from[1]);
        /* stay with player 1: only objects reasonably close to both */
        if (d < bd && sq(F32(o, 0x44) - p1[0]) + sq(F32(o, 0x48) - p1[1]) < sq(18.0f)) {
            bd = d;
            best = o;
            pos[0] = F32(o, 0x44); pos[1] = F32(o, 0x48); pos[2] = F32(o, 0x4c);
        }
    }
    return best;
}

void mp_ai_reset(void) { s_nvisited = 0; }

/* world direction (x, y on the ground; Z-up) -> stick, relative to the camera player 2 moves by:
   his own (split screen) or the game camera (o76: right +0x20, fwd +0x14) */
static void dir_to_stick(f32 dx, f32 dy, f32 *sx, f32 *sy)
{
    u8 *gc = PTR(*(void **)0x8035B308, 0x4c);
    f32 rx = 1.0f, ry = 0.0f, fx = 0.0f, fy = 1.0f, a, b, m;
    f32 eye[3], fwd[3], side[3], up[3];
    extern int mp_cam2_basis(f32 *eye, f32 *fwd, f32 *side, f32 *up);
    if (mp_cam2_basis(eye, fwd, side, up)) {
        /* player 2's own camera (split screen): his stick is relative to it */
        rx = side[0]; ry = side[1];
        /* forward on the ground = side rotated a quarter turn */
        fx = -side[1]; fy = side[0];
    } else if (gc) {
        rx = F32(gc, 0x20); ry = F32(gc, 0x24);
        fx = F32(gc, 0x14); fy = F32(gc, 0x18);
    }
    a = dx * rx + dy * ry;
    b = dx * fx + dy * fy;
    m = (a < 0 ? -a : a) > (b < 0 ? -b : b) ? (a < 0 ? -a : a) : (b < 0 ? -b : b);
    if (m < 0.0001f) {
        *sx = *sy = 0.0f;
        return;
    }
    *sx = a / m;
    *sy = b / m;
}

void mp_ai_fill(u8 *in)
{
    static u32 t;
    f32 p1[3], p2[3], e[3], sx = 0.0f, sy = 0.0f, d1;
    u8 *enemy;
    int fire = 0, lock = 0, collect = 0, activate = 0;
    static u8 *s_hider;
    static u32 s_hider_frames;
    f32 h[3];
    u8 *hider;
    t++;
    if (!mp_player[0] || !mp_player[1] || !mp_player_pos(mp_player[0], p1) || !mp_player_pos(mp_player[1], p2))
        return;
    d1 = sq(p1[0] - p2[0]) + sq(p1[1] - p2[1]);
    enemy = nearest_enemy(p2, 7.0f, e);
    if (enemy && d1 < sq(16.0f)) {
        f32 de = sq(e[0] - p2[0]) + sq(e[1] - p2[1]);
        lock = 1;
        if (de > sq(4.5f))
            dir_to_stick(e[0] - p2[0], e[1] - p2[1], &sx, &sy);   /* close in */
        else if (de < sq(2.0f))
            dir_to_stick(p2[0] - e[0], p2[1] - e[1], &sx, &sy);   /* back off a little */
        fire = (t % 40) < 6;                                      /* bursts of fire */
        collect = de < sq(3.5f) && (t % 90) < 30;                 /* soul collector up close */
    } else if ((hider = nearest_hider(p2, p1, 12.0f, h)) != 0) {
        f32 dh = sq(h[0] - p2[0]) + sq(h[1] - p2[1]);
        if (hider != s_hider) {
            s_hider = hider;
            s_hider_frames = 0;
            OSReport("[mp] AI: going to '%.8s' to release its ghost\n", (char *)hider + 0x8c);
        }
        if (dh > sq(1.4f)) {
            dir_to_stick(h[0] - p2[0], h[1] - p2[1], &sx, &sy);
        } else {
            activate = (t % 20) < 5;  /* touch it with B */
            if (++s_hider_frames > 90 && s_nvisited < 64)
                s_visited[s_nvisited++] = hider;  /* done with this one */
        }
        if (++s_hider_frames > 900 && s_nvisited < 64)
            s_visited[s_nvisited++] = hider;  /* could not reach it: give up */
    } else if (d1 > sq(3.0f)) {
        dir_to_stick(p1[0] - p2[0], p1[1] - p2[1], &sx, &sy);     /* follow player 1 */
        if (d1 < sq(5.0f)) {
            sx *= 0.6f;
            sy *= 0.6f;
        }
    }
    {
        int k;
        for (k = 0x08; k < 0x54; k += 4)  /* nothing left held from the human player */
            *(u32 *)(in + k) = 0;
    }
    *(f32 *)(in + 0x08) = sy;
    *(f32 *)(in + 0x0c) = sx;
    *(u32 *)(in + 0x40) = lock;      /* L: lock on */
    *(u32 *)(in + 0x34) = fire;      /* R: fire */
    *(u32 *)(in + 0x28) = collect;   /* X: soul collector */
    *(u32 *)(in + 0x38) = activate;  /* B: activate */
}
