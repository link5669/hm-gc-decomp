// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"
extern "C" {

typedef struct Msg { u32 a, b, c, code, down, f, g; } Msg;
typedef struct Obj { u8 pad[4]; void *o4; } Obj;
typedef struct Cfg { u8 pad[20]; f32 k; } Cfg;
typedef struct Pad {
    u8 pad0[8]; f32 x; f32 y; u8 pad1[40 - 16];
    s32 sx; s32 cx; s32 sy; s32 cy; s32 lim; void *o;
} Pad;
extern Obj *lbl_8035B7E4;
extern Cfg *lbl_8035B488;
extern f32 lbl_8035BFDC, lbl_8035BFE0, lbl_8035BFE4, lbl_8035BFE8;
void fn_801C30E8(void *, Msg *);
void fn_80038078(Pad *p) {
    Msg m;
    void *o;
    f32 k;
    m.down = 1;
    o = p->o;
    if (!o) o = lbl_8035B7E4->o4;
    k = lbl_8035B488->k;
    if (p->x < lbl_8035BFDC) {
        if (p->sx != 0 || p->cx == 0) {
            if (p->sx != 0) p->lim = 50000;
            p->sx = 0;
            m.code = 66;
            if (o) fn_801C30E8(o, &m);
            p->cx = (s32)(lbl_8035BFE0 * (p->x * k));
        } else {
            p->cx += (s32)(lbl_8035BFE0 * (p->x * k));
            if (p->cx > p->lim) { p->cx = 0; p->lim = 25000; }
        }
    } else if (p->x > lbl_8035BFE4) {
        if (p->sx != 1 || p->cx == 0) {
            if (p->sx != 1) p->lim = 50000;
            p->sx = 1;
            m.code = 67;
            if (o) fn_801C30E8(o, &m);
            p->cx = (s32)(lbl_8035BFE8 * (p->x * k));
        } else {
            p->cx += (s32)(lbl_8035BFE8 * (p->x * k));
            if (p->cx > p->lim) { p->cx = 0; p->lim = 25000; }
        }
    } else {
        if (p->sx != 4) {
            Msg r;
            r.down = 0;
            r.code = 66;
            if (o) fn_801C30E8(o, &r);
        }
        p->sx = 4;
        p->cx = 0;
    }
    if (p->y > lbl_8035BFE4) {
        if (p->sy != 2 || p->cy == 0) {
            if (p->sy != 2) p->lim = 50000;
            p->sy = 2;
            m.code = 69;
            if (o) fn_801C30E8(o, &m);
            p->cy = (s32)(lbl_8035BFE8 * (p->y * k));
        } else {
            p->cy += (s32)(lbl_8035BFE8 * (p->y * k));
            if (p->cy > p->lim) { p->cy = 0; p->lim = 25000; }
        }
    } else if (p->y < lbl_8035BFDC) {
        if (p->sy != 3 || p->cy == 0) {
            if (p->sy != 3) p->lim = 50000;
            p->sy = 3;
            m.code = 70;
            if (o) fn_801C30E8(o, &m);
            p->cy = (s32)(lbl_8035BFE0 * (p->y * k));
        } else {
            p->cy += (s32)(lbl_8035BFE0 * (p->y * k));
            if (p->cy > p->lim) { p->cy = 0; p->lim = 25000; }
        }
    } else {
        if (p->sy != 4) {
            Msg r;
            r.down = 0;
            r.code = 69;
            if (o) fn_801C30E8(o, &r);
        }
        p->cy = 0;
        p->sy = 4;
    }
}

}
