// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern volatile f32 lbl_80363A7C;
extern volatile f32 lbl_80363A80;
extern volatile f32 lbl_80363A68;
typedef struct { u32 a; u32 b; } E8;
typedef struct { u32 f0; u32 f4; u32 f8; u32 f12; f32 f16; f32 f20; f32 f24; f32 f28; f32 f32_; } D36;
typedef struct { u8 pad[12]; f32 f12; f32 f16; u32 f20; u32 f24; u32 f28; } P176;
void fn_80118694(void *p, u32 n, u32 v);
s32 fn_8011F5C0(void *o, const P176 *p);
void fn_80118B5C(void *q, D36 *s);
void *memset(void *, int, u32);
} /* extern "C" */
struct O176 {
    u32 f0; u32 f4; u32 f8; u8 pad12[24 - 12]; u32 f24; u8 pad28[80 - 28]; E8 *f80; u8 pad84[168 - 84];
    u32 f168; u32 f172; u8 pad176[208 - 176];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual s32 v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual s32 v7();
    u8 *f212; u8 f216[4];
    void upd() { f168 = f0 + f4 + f8; }
    void upd2() { f168 = f0 + f4 + f8; f172 = f4 + f8; }
    void set0(u32 v) { f0 = v; upd(); }
    void set1(u32 v) { f4 = v; upd2(); }
    void set2(u32 v) { f8 = v; upd2(); }
};
extern "C" {
static inline s32 tail(O176 *o, const P176 *p) {
    s32 r;
    u32 i;
    f32 a;
    f32 b;
    r = fn_8011F5C0(o, p);
    if (r == 0) {
        r = o->v3();
        if (r == 0) {
            a = p->f12; b = p->f16;
            for (i = 0; i < o->f4; i++) {
                D36 s;
                memset(&s, 0, sizeof(s));
                s.f8 = o->f80[i].a;
                s.f4 = 1;
                s.f0 = o->f24;
                u32 t = i + o->f0;
                *(volatile f32 *)&s.f28 = a;
                *(volatile u32 *)&s.f12 = t;
                *(volatile f32 *)&s.f32_ = b;
                *(volatile f32 *)&s.f16 = lbl_80363A7C;
                *(volatile f32 *)&s.f20 = lbl_80363A80;
                *(volatile f32 *)&s.f24 = lbl_80363A68;
                fn_80118B5C(o->f212 + i * 64, &s);
            }
        }
    }
    return r;
}
s32 fn_801176A4(O176 *o, const P176 *p) {
    s32 r;
    r = o->v7();
    if (r != 0) return r;
    o->set0(p->f20);
    o->set1(p->f24);
    o->set2(p->f28);
    fn_80118694(o->f216, o->f168 * 2, 255);
    return tail(o, p);
}

} /* extern "C" */
