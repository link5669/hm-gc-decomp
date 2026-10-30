// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct C4 { u8 r, g, b, a; };
struct FT { u8 pad[392]; void (*f392)(void *, V *, V *); u8 pad396[8]; void (*f404)(void *, V *, V *); };
extern FT lbl_803286D0;
extern u32 lbl_802A0BE0[];
struct L { u8 b[4]; };
struct X { u8 pad[1132]; u8 f1132; C4 c; u8 pad1137[7]; u32 f1144; u32 f1148; int f1152; int f1156; };
struct S { u8 pad[76]; f32 f76; f32 f80; };
struct P { u8 pad[10888]; void *f10888; u8 pad2[0x20000 + 31212 - 10892]; f32 fa; f32 fb; };
struct T { u8 pad[12]; u32 f12; u8 pad16[40]; u8 f56[4]; u8 pad60[6392]; P *f6452; X *f6456; S *f6460; u8 pad6464[104]; int f6568; int f6572; u8 c6576, c6577, c6578; u8 pad6579; V f6580[8]; V f6676[8]; u8 pad6772[32]; u32 f6804; L *f6808[8]; };
void fn_8014CC80(void *);
void fn_8016C684(P *, S *);
void fn_800D7A88(int, C4);
void fn_800D7CA4(int, u8, int, u32, u32, int, int);
void fn_800D79B0(L *, f32, f32, f32);
void fn_800D7984(L *, f32, f32, f32);
void fn_800D7A0C(L *, u32);
static inline void mode(X *x, u32 a, int b, int c) {
    if (x->f1148 != a || x->f1152 != b || x->f1156 != c) {
        x->f1148 = a;
        x->f1152 = b;
        x->f1156 = c;
        fn_800D7CA4(0, x->f1132, 0, x->f1144, x->f1148, x->f1152, x->f1156);
    }
}
void fn_80163F28(T *t, S *s) {
    fn_8014CC80(t->f56);
    t->f6460 = s;
    fn_8016C684(t->f6452, t->f6460);
    t->f6452->fa = t->f6460->f76;
    t->f6452->fb = t->f6460->f80;
    if (t->f12 & 2 && t->f12 & 2) {
    if (t->f12 & 8) {
        X *x = t->f6456;
        if (x->c.r != t->c6576 || x->c.g != t->c6577 || x->c.b != t->c6578) {
            x->c.r = t->c6576;
            x->c.g = t->c6577;
            x->c.b = t->c6578;
            x->c.a = 255;
            fn_800D7A88(0, x->c);
        }
    } else {
        X *x = t->f6456;
        if (x->c.r || x->c.g || x->c.b) {
            x->c.r = 0;
            x->c.g = 0;
            x->c.b = 0;
            x->c.a = 255;
            fn_800D7A88(0, x->c);
        }
    }
    mode(t->f6456, lbl_802A0BE0[t->f6804], t->f6568, t->f6572);
    u32 i = 0;
    T *p12 = t;
    T *p4 = t;
    for (; i < t->f6804; i++) {
        V o;
        lbl_803286D0.f404(t->f6452->f10888, p12->f6676, &o);
        fn_800D79B0(p4->f6808[0], o.x, o.y, o.z);
        lbl_803286D0.f392(t->f6452->f10888, p12->f6580, &o);
        fn_800D7984(p4->f6808[0], o.x, o.y, o.z);
        fn_800D7A0C(p4->f6808[0], 1 << i);
        p12 = (T *)((u8 *)p12 + 12);
        p4 = (T *)((u8 *)p4 + 4);
    }
    }
}

} /* extern "C" */
