// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct R80190120 { u8 pad[0x124]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void err(s32); virtual u32 n(); };
struct Obj80190120;
struct Cb80190120 { u32 pad; virtual void f0(); virtual void f1(Obj80190120 *); };
struct Inner80190120 { u8 pad[20]; u32 f20; };
struct Obj80190120 { u32 flags; f32 f4; f32 f8; Cb80190120 *cb; Inner80190120 *f16; u32 f20; };

extern f32 lbl_80364B2C;
extern u32 lbl_80364B20;
extern u32 lbl_80364B24;
extern u32 lbl_80364B28;
void fn_800FB000(void *, s32);
void fn_800FAEF8(void *);
void fn_800FB064(void *, void *);
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, void *, void *);
void fn_8014094C(Obj80190120 *, void *);
u32 fn_800FB33C(void *);
f32 fn_800FB2E0(void *);

void fn_80190120(Obj80190120 *o, u8 *ctx, R80190120 *r) {
    u8 b16[8];
    char b8[8];
    s32 have;
    f32 f;
    u32 t;

    have = 0;
    f = lbl_80364B2C;
    fn_800FB000(r, 131);
    fn_800FAEF8(r);
    while ((t = r->n()) != 6) {
        switch ((s32)t) {
        case 132: {
            void *res;
            u32 v;
            fn_800FB064(r, b16);
            fn_800FB064(r, b8);
            if (b8 == 0 || b8[0] == 0) {
                res = fn_800F9398(ctx + 480, b16);
            } else {
                res = fn_800F9788(ctx + 504, b8, b16);
            }
            if (res == 0) {
                r->err(37);
            }
            fn_8014094C(o, res);
            o->flags |= lbl_80364B20;
            if (o->cb != 0) {
                o->cb->f1(o);
            }
            o->f20 |= lbl_80364B24;
            o->flags |= lbl_80364B28;
            v = fn_800FB33C(r);
            if (o->f20 & 1) {
                o->f4 = (s32)(v % o->f16->f20);
            }
            break;
        }
        case 72:
            f = fn_800FB2E0(r);
            have = 1;
            break;
        default:
            r->err(30);
            break;
        }
    }
    if (have) {
        o->f8 = f;
    }
}

} /* extern "C" */
