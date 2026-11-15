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
extern u8 lbl_803286D0[];                                     /* transform op table */

static Rect s_pane[2] = {{0, 0, 320, 480, 0.0f, 1.0f}, {320, 0, 640, 480, 0.0f, 1.0f}};
static int s_pane_idx = -1, s_inworld;
static void *s_cam2;

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
    if (world)
        capture(gx, s_pane_idx > 0 ? 1 : 0);
}

void mp_gx_setviewport(void *gx, Rect *r)
{
    if (s_pane_idx >= 0 && r == 0 && s_inworld)
        r = &s_pane[s_pane_idx];
    fn_80163CB4(gx, r);
}

/* HUD, menus and fades are drawn once (full screen) in the last pass only. */
void mp_hook_hud(void *a, void *gx) { if (s_pane_idx != 0) fn_8002C34C(a, gx); }
void mp_hook_menu(void *a, void *gx) { if (s_pane_idx != 0) fn_801C3050(a, gx); }
void mp_hook_fade(void *a, void *gx) { if (s_pane_idx != 0) fn_80039F78(a, gx); }

static void set_aspect(void *cam, f32 aspect)
{
    fn_8012962C(cam, F32(cam, 0x34), aspect, F32(cam, 0x4c), F32(cam, 0x50));
}

/* Renders the frame split in two. cam2's pose is computed by the caller via eye/at. */
int mp_split_render(void *game, void *gx, const f32 *eye2, const f32 *at2)
{
    void *cam1 = PTR(game, 0x28);
    f32 up[3] = {0.0f, 1.0f, 0.0f};
    f32 aspect1;

    if (!cam1)
        return 0;
    if (!s_cam2)
        s_cam2 = make_cam2(game, cam1);
    if (!s_cam2)
        return 0;
    aspect1 = F32(cam1, 0x38);
    fn_8012962C(s_cam2, F32(cam1, 0x34), aspect1 * 0.5f, F32(cam1, 0x4c), F32(cam1, 0x50));
    fn_80129710(s_cam2, eye2, at2, up);
    if ((mp.frame & 255) == 0) {
        f32 p1[3], p2[3];
        mp_cam_get_pos(cam1, p1);
        mp_cam_get_pos(s_cam2, p2);
        OSReport("[mp] cam1 %d %d %d cam2 %d %d %d\n", (int)p1[0], (int)p1[1], (int)p1[2], (int)p2[0], (int)p2[1], (int)p2[2]);
    }
    set_aspect(cam1, aspect1 * 0.5f);

    s_pane_idx = 0;
    fn_800326D0(game, gx);
    PTR(game, 0x28) = s_cam2;
    s_pane_idx = 1;
    fn_800326D0(game, gx);
    PTR(game, 0x28) = cam1;
    s_pane_idx = -1;
    s_inworld = 0;
    set_aspect(cam1, aspect1);
    return 1;
}

void *mp_split_cam2(void) { return s_cam2; }
