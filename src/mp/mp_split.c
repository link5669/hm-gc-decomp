/* Multiplayer mod: vertical split screen (left = player 1, right = player 2).
   Game::Render is called twice per frame, once per camera, with every full-screen world pass
   (Gx BeginPass/SetViewport with a null rect) redirected to the current half. */
#include "mp.h"
#include "mp_state.h"
#include "mp_split.h"

typedef struct Rect { s32 x0, y0, x1, y1; f32 n, f; } Rect;

void fn_800326D0(void *game, void *gx);                      /* Game::Render */
void fn_801650F8(void *gx, void *cam, s32 flags, Rect *r);    /* Gx::BeginPass */
void fn_80163CB4(void *gx, Rect *r);                          /* Gx::SetViewport */
void fn_8002C34C(void *hud, void *gx);
void fn_801C3050(void *menus, void *gx);
void fn_80039F78(void *fade, void *gx);
void fn_80129938(void *cam, void *ctx);
void fn_8012962C(void *cam, f32 fov, f32 aspect, f32 n, f32 f);
void fn_80129710(void *cam, const f32 *eye, const f32 *at, const f32 *up);
f32 tanf(f32);
int fn_80264E0C(f32 *from, f32 *to, f32 *hit, f32 *normal, f32 *frac, int a, int b, int c, int d, int e, int f, int g,
                int h, int i, int mask);  /* segment vs. level (the game camera's wall test, mask 2) */

/* Pull a camera in front of walls: segment from the player's head to the wanted eye (plus a margin);
   returns the usable distance along the direction. */
static f32 wall_clip(const f32 *head, const f32 *dir, f32 len)
{
    f32 a[3], b[3], hit[3], n[3], t = 1.0f, margin = 0.4f, d;
    int i;
    for (i = 0; i < 3; i++) {
        a[i] = head[i];
        b[i] = head[i] + dir[i] * (len + margin);
    }
    if (!fn_80264E0C(a, b, hit, n, &t, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2))
        return len;
    d = t * (len + margin) - margin;
    return d < 0.8f ? 0.8f : d;
}
extern u8 lbl_803286D0[];                                     /* transform op table */

static Rect s_pane[2] = {{0, 0, 320, 480, 0.0f, 1.0f}, {320, 0, 640, 480, 0.0f, 1.0f}};
static int s_pane_idx = -1, s_inworld;
void *mp_main_cam;  /* camera of the current Render pass (Game+0x28); only its world pass is captured */
static void *s_cam2, *s_camA;  /* split-screen cameras for the right / left pane */

#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))
#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

void mp_cam_get_pos(void *cam, f32 *pos)
{
    ((void (*)(void *, f32 *))PTR(lbl_803286D0, 0x130))(PTR(cam, 0x10), pos);
}

void mp_cam_get_basis(void *cam, f32 *right, f32 *up, f32 *fwd)
{
    ((void (*)(void *, f32 *, f32 *, f32 *))PTR(lbl_803286D0, 0x134))(PTR(cam, 0x10), right, up, fwd);
}

static void *make_cam2(void *game, void *cam1)
{
    u8 *a4 = PTR(game, 0x04);
    void *mgr = PTR(a4, 0x10);
    void *cam = ((void *(*)(void *))PTR(*(void **)mgr, 0x6c))(mgr);
    if (!cam)
        return 0;
    fn_80129938(cam, PTR(a4, 0x18));
    fn_8012962C(cam, F32(cam1, 0x34), F32(cam1, 0x38), F32(cam1, 0x4c), F32(cam1, 0x50));
    OSReport("[mp] camera 2 created %p (fov %d mrad)\n", cam, (int)(F32(cam1, 0x34) * 1000.0f));
    return cam;
}

/* World-pass camera matrices captured per pane (0 = left/full, 1 = right) for name tags. */
f32 mp_view[2][16], mp_proj[2][16];
u8 mp_have_mtx[2];

static void capture(void *gx, int pane)
{
    u8 *dev = PTR(gx, 6452);
    f32 *v, *pr;
    int i;
    if (!dev || !(v = PTR(dev, 10888)) || !(pr = PTR(dev, 10880)))
        return;
    for (i = 0; i < 16; i++) {
        mp_view[pane][i] = v[i];
        mp_proj[pane][i] = pr[i];
    }
    mp_have_mtx[pane] = 1;
}

void mp_gx_beginpass(void *gx, void *cam, s32 flags, Rect *r)
{
    int world = (r == 0 && flags == 7);
    if (s_pane_idx >= 0) {
        if (r == 0 && flags == 7) {
            r = &s_pane[s_pane_idx];
            s_inworld = 1;
        } else if (flags != 7) {
            s_inworld = 0;
        }
    }
    fn_801650F8(gx, cam, flags, r);
    if (world && cam == mp_main_cam)
        capture(gx, s_pane_idx > 0 ? 1 : 0);
}

void mp_gx_setviewport(void *gx, Rect *r)
{
    if (s_pane_idx >= 0 && r == 0 && s_inworld)
        r = &s_pane[s_pane_idx];
    fn_80163CB4(gx, r);
}

/* HUD, menus and fades are drawn once (full screen) in the last pass only. */
u32 mp_hud_seen;  /* render frame in which the in-game HUD was last drawn (= real gameplay) */
void mp_hook_hud(void *a, void *gx)
{
    mp_hud_seen = mp_render_frame;
    if (s_pane_idx != 0)
        fn_8002C34C(a, gx);
}
void mp_hook_menu(void *a, void *gx) { if (s_pane_idx != 0) fn_801C3050(a, gx); }
void mp_hook_fade(void *a, void *gx) { if (s_pane_idx != 0) fn_80039F78(a, gx); }

static void set_aspect(void *cam, f32 aspect)
{
    fn_8012962C(cam, F32(cam, 0x34), aspect, F32(cam, 0x4c), F32(cam, 0x50));
}

/* Renders the frame split in two. cam2's pose is computed by the caller via eye/at. */
int mp_split_render(void *game, void *gx, const f32 *eye1, const f32 *at1, const f32 *eye2, const f32 *at2)
{
    void *cam1 = PTR(game, 0x28);
    f32 up[3] = {0.0f, 0.0f, -1.0f};  /* the world is Z-up; the look-at helper wants the negated up axis */
    f32 fov;

    if (!cam1)
        return 0;
    if (!s_cam2)
        s_cam2 = make_cam2(game, cam1);
    if (!s_camA)
        s_camA = make_cam2(game, cam1);
    if (!s_cam2 || !s_camA)
        return 0;
    /* half-width panes: a slightly wider vertical view keeps more of the room in sight */
    fov = F32(cam1, 0x34) * 1.15f;
    fn_8012962C(s_camA, fov, 320.0f / 448.0f, F32(cam1, 0x4c), F32(cam1, 0x50));
    fn_8012962C(s_cam2, fov, 320.0f / 448.0f, F32(cam1, 0x4c), F32(cam1, 0x50));
    fn_80129710(s_camA, eye1, at1, up);
    fn_80129710(s_cam2, eye2, at2, up);

    PTR(game, 0x28) = s_camA;
    s_pane_idx = 0;
    mp_main_cam = s_camA;
    fn_800326D0(game, gx);
    PTR(game, 0x28) = s_cam2;
    s_pane_idx = 1;
    mp_main_cam = s_cam2;
    fn_800326D0(game, gx);
    mp_main_cam = cam1;
    PTR(game, 0x28) = cam1;
    s_pane_idx = -1;
    s_inworld = 0;
    return 1;
}

void *mp_split_cam2(void) { return s_cam2; }

/* Split-screen policy: split as soon as either player is not visible in player 1's (full-screen) view;
   merge again once both have been comfortably on screen for half a second. Camera 2 follows player 2 with the
   same offset and direction camera 1 has from player 1. */
extern f32 mp_view[2][16], mp_proj[2][16];
extern u8 mp_have_mtx[2];
static int s_split_on, s_visible_frames, s_offscreen_frames;
u32 mp_cam_toggles;
extern void *mp_gamecam2;

/* NDC of world point w in camera 1's view as a full-screen (4:3) projection; returns 0 if behind. */
static int ndc_full(const f32 *w, f32 *nx, f32 *ny)
{
    const f32 *v = mp_view[0], *p = mp_proj[0];
    f32 e[3], cx, cy, cw;
    int i;
    for (i = 0; i < 3; i++)
        e[i] = v[i * 4] * w[0] + v[i * 4 + 1] * w[1] + v[i * 4 + 2] * w[2] + v[i * 4 + 3];
    cx = p[0] * e[0] + p[1] * e[1] + p[2] * e[2] + p[3];
    cy = p[4] * e[0] + p[5] * e[1] + p[6] * e[2] + p[7];
    cw = p[12] * e[0] + p[13] * e[1] + p[14] * e[2] + p[15];
    if (cw < 0.1f)
        return 0;
    *nx = cx / cw;
    *ny = cy / cw;
    if (s_split_on)
        *nx *= 0.5f;  /* captured while split: the pane projection is half as wide */
    return 1;
}

/* The shared (single-screen) view = the game camera (Game+0x28), computed from its pose every frame so the
   split/merge decision doesn't depend on what was rendered last. */
static f32 s_gv[12], s_gp00, s_gp11;
static int s_gv_ok;
static void game_view(void *game)
{
    /* GameCam actor (o76): view rows right +0x20, up +0x2C, -forward +0x14 (3x3), eye +0x44 */
    u8 *gc = *(u8 **)((u8 *)*(void **)0x8035B308 + 0x4c);
    void *cam = PTR(game, 0x28);
    f32 t;
    int i;
    s_gv_ok = 0;
    if (!gc || !cam)
        return;
    for (i = 0; i < 3; i++) {
        s_gv[i] = *(f32 *)(gc + 0x20 + 4 * i);
        s_gv[4 + i] = *(f32 *)(gc + 0x2c + 4 * i);
        s_gv[8 + i] = -*(f32 *)(gc + 0x14 + 4 * i);
    }
    for (i = 0; i < 3; i++)
        s_gv[i * 4 + 3] = -(s_gv[i * 4] * *(f32 *)(gc + 0x44) + s_gv[i * 4 + 1] * *(f32 *)(gc + 0x48) +
                            s_gv[i * 4 + 2] * *(f32 *)(gc + 0x4c));
    t = tanf(F32(cam, 0x34) * 0.5f);
    if (t < 0.01f)
        return;
    s_gp11 = 1.0f / t;
    s_gp00 = s_gp11 / 1.3333334f;
    s_gv_ok = 1;
}

static int ndc_game(const f32 *w, f32 *nx, f32 *ny)
{
    f32 e[3];
    int i;
    for (i = 0; i < 3; i++)
        e[i] = s_gv[i * 4] * w[0] + s_gv[i * 4 + 1] * w[1] + s_gv[i * 4 + 2] * w[2] + s_gv[i * 4 + 3];
    if (-e[2] < 0.1f)
        return 0;
    *nx = s_gp00 * e[0] / -e[2];
    *ny = s_gp11 * e[1] / -e[2];
    return 1;
}

/* Is the player's whole body (feet and head) inside the screen, with the given NDC margin? */
static int on_screen(const f32 *pos, f32 lim)
{
    f32 w[3], x, y;
    int k;
    for (k = 0; k < 2; k++) {
        w[0] = pos[0]; w[1] = pos[1]; w[2] = pos[2] + (k ? 1.8f : 0.1f);
        if (!(s_gv_ok ? ndc_game(w, &x, &y) : ndc_full(w, &x, &y)) || x < -lim || x > lim || y < -lim || y > lim)
            return 0;
    }
    return 1;
}

/* Camera quality metrics (debug build): visibility of each player in his view, split toggles,
   camera-2 turn rate and distance. Logged every 300 frames. */
static f32 sqrtf(f32 x)
{
    f32 g;
    int i;
    if (x <= 0.0f)
        return 0.0f;
    g = x > 1.0f ? x * 0.5f : 1.0f;
    for (i = 0; i < 12; i++)
        g = 0.5f * (g + x / g);
    return g;
}
static void mp_cam_metrics(const f32 *p1, const f32 *p2, const f32 *eye2, const f32 *at2, int split)
{
#ifdef MP_DEBUG_CAM
    static u32 n, nsplit, v1, v2, toggles0, maxturn100, dmin100 = 99999, dmax100;
    static f32 lastdir[3];
    static u32 maxviewerr;
    f32 w[3], x, y;
    int vis1, vis2;
    /* player 1: in pane 0 (split: half projection) / full screen */
    w[0] = p1[0]; w[1] = p1[1]; w[2] = p1[2] + 1.0f;
    vis1 = ndc_full(w, &x, &y) && x > -1.0f && x < 1.0f && y > -1.0f && y < 1.0f;
    if (split)  /* in its own pane (the pane projection is not halved) */
        vis1 = ndc_full(w, &x, &y) && x * 2.0f > -1.0f && x * 2.0f < 1.0f && y > -1.0f && y < 1.0f;
    w[0] = p2[0]; w[1] = p2[1]; w[2] = p2[2] + 1.0f;
    if (split) {
        f32 d[3], len, dot;
        int i;
        for (i = 0; i < 3; i++)
            d[i] = at2[i] - eye2[i];
        len = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
        if (len > 0.001f) {
            for (i = 0; i < 3; i++)
                d[i] /= len;
            dot = d[0] * lastdir[0] + d[1] * lastdir[1] + d[2] * lastdir[2];
            if (n && dot < 1.0f && (u32)((1.0f - dot) * 100000.0f) > maxturn100)
                maxturn100 = (u32)((1.0f - dot) * 100000.0f);
            for (i = 0; i < 3; i++)
                lastdir[i] = d[i];
        }
        {
            f32 e0 = eye2[0] - p2[0], e1 = eye2[1] - p2[1], e2 = eye2[2] - p2[2];
            u32 dd = (u32)(sqrtf(e0 * e0 + e1 * e1 + e2 * e2) * 100.0f);
            if (dd < dmin100) dmin100 = dd;
            if (dd > dmax100) dmax100 = dd;
        }
        vis2 = 1;  /* camera 2 always looks at player 2 */
        nsplit++;
    } else {
        f32 gx_, gy_;
        vis2 = ndc_full(w, &x, &y) && x > -1.0f && x < 1.0f && y > -1.0f && y < 1.0f;
        /* self-check: computed shared view vs what was rendered */
        if (s_gv_ok && ndc_full(w, &x, &y) && ndc_game(w, &gx_, &gy_)) {
            u32 err = (u32)(((x - gx_) * (x - gx_) + (y - gy_) * (y - gy_)) * 10000.0f);
            if (err > maxviewerr)
                maxviewerr = err;
        }
    }
    n++;
    v1 += vis1;
    v2 += vis2;
    if (n >= 300) {
        OSReport("[mp] CAMSTAT frames %d split %d%% p1vis %d%% p2vis %d%% toggles %d maxturn(1-cos)x1e5 %d cam2dist %d..%d cm viewerr %d\n", n,
                 nsplit * 100 / n, v1 * 100 / n, v2 * 100 / n, mp_cam_toggles - toggles0, maxturn100, dmin100 == 99999 ? 0 : dmin100,
                 dmax100, maxviewerr);
        maxviewerr = 0;
        n = nsplit = v1 = v2 = 0;
        toggles0 = mp_cam_toggles;
        maxturn100 = dmax100 = 0;
        dmin100 = 99999;
    }
#endif
}

#ifdef MP_DEBUG_AUTOJOIN
/* debug: find where the GameCam actor keeps its view axes (rows of the rendered view matrix, +/-) */
static void search_axes(void)
{
    static int done;
    const f32 *v = mp_view[0];
    u8 *o76 = *(u8 **)((u8 *)*(void **)0x8035B308 + 0x4c);
    u32 k;
    int r, sg;
    if (done || !mp_have_mtx[0] || !o76 || (mp_render_frame % 60) != 30)
        return;
    done = 1;
    for (r = 0; r < 3; r++)
        for (sg = -1; sg <= 1; sg += 2) {
            OSReport("[mp] row%d*%d (%d %d %d):", r, sg, (int)(v[r * 4] * 100), (int)(v[r * 4 + 1] * 100), (int)(v[r * 4 + 2] * 100));
            for (k = 0; k + 12 <= 0x330; k += 4) {
                f32 *f = (f32 *)(o76 + k), a0 = f[0] - sg * v[r * 4], a1 = f[1] - sg * v[r * 4 + 1], a2 = f[2] - sg * v[r * 4 + 2];
                if (a0 * a0 + a1 * a1 + a2 * a2 < 0.01f)
                    OSReport(" +%03x", k);
            }
            OSReport("\n");
        }
}
#endif

int mp_coop_render(void *game, void *gx)
{
    f32 p1[3], p2[3], eye[3], fwd[3], eye2[3], at2[3];
    const f32 *v = mp_view[0];
    int i;

    if (!mp_player_pos(mp_player[0], p1) || !mp_player_pos(mp_player[1], p2) || !mp_have_mtx[0])
        return 0;
    game_view(game);
    if (mp.debug_split) {
        s_split_on = 1;
    } else if (!s_split_on) {
        /* split once a player has been off the shared screen for a third of a second */
        if (!on_screen(p1, 0.92f) || !on_screen(p2, 0.92f)) {
            if (++s_offscreen_frames > 20)
                s_split_on = 1, s_visible_frames = 0, s_offscreen_frames = 0, mp_cam_toggles++;
        } else {
            s_offscreen_frames = 0;
        }
    } else {
        /* merge once both have been well inside player 1's view for 0.75 s */
        if (on_screen(p1, 0.7f) && on_screen(p2, 0.7f)) {
            if (++s_visible_frames > 45)
                s_split_on = 0, s_offscreen_frames = 0, mp_cam_toggles++;
        } else {
            s_visible_frames = 0;
        }
    }
    if (!s_split_on) {
#ifdef MP_DEBUG_AUTOJOIN
        search_axes();
#endif
        mp_cam_metrics(p1, p2, 0, 0, 0);
        return 0;
    }
    {
        /* Each pane: start from that player's game camera position (the game's own follow camera with its
           collision handling), keep a minimum distance and height, always look at the player's head, smooth. */
        static f32 se[2][3], sa[2][3];
        static u32 last_frame;
        f32 eyes[2][3], ats[2][3];
        void *gc[2];
        const f32 *pp[2];
        int k;
        gc[0] = *(void **)((u8 *)*(void **)0x8035B308 + 0x4c);  /* player 1's GameCam (o76) */
        gc[1] = 0;
        pp[0] = p1;
        pp[1] = p2;
        for (k = 0; k < 2; k++) {
            f32 head[3], d[3], len;
            head[0] = pp[k][0]; head[1] = pp[k][1]; head[2] = pp[k][2] + 1.3f;
            {
                /* chase camera: behind the player's walking direction (kept while standing still) */
                static f32 hd[2][2] = {{1.0f, 0.0f}, {1.0f, 0.0f}};
                f32 vx = *(f32 *)((u8 *)mp_player[k] + 0x118), vy = *(f32 *)((u8 *)mp_player[k] + 0x11c);
                f32 sp = sqrtf(vx * vx + vy * vy);
                if (sp > 0.5f) {
                    hd[k][0] += (vx / sp - hd[k][0]) * 0.06f;
                    hd[k][1] += (vy / sp - hd[k][1]) * 0.06f;
                    sp = sqrtf(hd[k][0] * hd[k][0] + hd[k][1] * hd[k][1]);
                    if (sp > 0.01f) {
                        hd[k][0] /= sp;
                        hd[k][1] /= sp;
                    }
                }
                eyes[k][0] = head[0] - hd[k][0] * 3.6f;
                eyes[k][1] = head[1] - hd[k][1] * 3.6f;
                eyes[k][2] = head[2] + 1.4f;
            }
            {
                /* chase camera: keep 3.2..7 m, a bit above the head, and in front of walls; if a wall is close
                   behind the player, rise to an over-the-shoulder / overhead view rather than a close-up */
                f32 best = -1.0f, cand[3][3], bestv[3];
                int c;
                for (i = 0; i < 3; i++)
                    d[i] = eyes[k][i] - head[i];
                len = sqrtf(d[0] * d[0] + d[1] * d[1] + d[2] * d[2]);
                if (len < 0.01f) {
                    d[0] = 1.0f; d[1] = 0.0f; d[2] = 0.0f; len = 1.0f;
                }
                for (i = 0; i < 3; i++)
                    d[i] /= len;
                /* candidates: behind, behind+higher, nearly overhead */
                for (i = 0; i < 3; i++) {
                    cand[0][i] = d[i] * 3.6f;
                    cand[1][i] = d[i] * 2.4f;
                    cand[2][i] = d[i] * 0.9f;
                }
                cand[0][2] = 1.4f; cand[1][2] = 2.6f; cand[2][2] = 3.4f;
                for (c = 0; c < 3; c++) {
                    f32 cl = sqrtf(cand[c][0] * cand[c][0] + cand[c][1] * cand[c][1] + cand[c][2] * cand[c][2]), dn[3], got;
                    for (i = 0; i < 3; i++)
                        dn[i] = cand[c][i] / cl;
                    got = wall_clip(head, dn, cl);
                    if (got > best + 0.25f) {  /* prefer earlier (lower) candidates unless clearly better */
                        best = got;
                        for (i = 0; i < 3; i++)
                            bestv[i] = head[i] + dn[i] * got;
                    }
                    if (got >= cl - 0.01f && got >= 2.5f)
                        break;  /* unobstructed and far enough */
                }
                for (i = 0; i < 3; i++)
                    eyes[k][i] = bestv[i];
            }
            for (i = 0; i < 3; i++)
                ats[k][i] = head[i];
        }
        {
            f32 ke = (mp_render_frame - last_frame > 2) ? 1.0f : 0.12f, ka = (ke < 1.0f) ? 0.25f : 1.0f;
            for (k = 0; k < 2; k++)
                for (i = 0; i < 3; i++) {
                    se[k][i] += (eyes[k][i] - se[k][i]) * ke;
                    sa[k][i] += (ats[k][i] - sa[k][i]) * ka;
                }
            last_frame = mp_render_frame;
        }
        mp_cam_metrics(p1, p2, se[1], sa[1], 1);
        return mp_split_render(game, gx, se[0], sa[0], se[1], sa[1]);
    }
}

/* A new level frees the old camera objects: make camera 2 again on the next split. */
void mp_split_reset(void)
{
    s_cam2 = 0;
    s_camA = 0;
    s_split_on = 0;
    mp_have_mtx[0] = mp_have_mtx[1] = 0;
}
