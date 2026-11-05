// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct A80262D38 { u8 pad[492]; virtual ~A80262D38(); };
struct B80262D38 { u8 pad[16]; virtual ~B80262D38(); };
struct V80262D38 {
    f32 x, y, z;
    void Zero();
    void Set(f32 a, f32 b, f32 c) { x = a; y = b; z = c; }
    void VSet(f32 a, f32 b, f32 c) volatile { x = a; y = b; z = c; }
};
extern "C" {
}
inline void V80262D38::Zero() { x = 0.0f; y = 0.0f; z = 0.0f; }
extern "C" {
typedef struct {
    u32 f0;
    u32 f4;
    B80262D38 *f8;
    A80262D38 *f12;
    B80262D38 *f16;
    u32 f20;
} S80262D38;
extern void *volatile lbl_8035B478;
void fn_8023E138(void *, A80262D38 *);
V80262D38 lbl_80357E78, lbl_80357E84, lbl_80357E90;
extern f32 lbl_80366AEC;
extern f32 lbl_80366AE8;
#pragma opt_propagation off
void fn_80262D38(S80262D38 *p) {
    f32 one, zero;
    { void *g = lbl_8035B478; if (g && p->f12) fn_8023E138(g, p->f12); }
    if (p->f12) delete p->f12;
    if (p->f8) delete p->f8;
    if (p->f16) delete p->f16;
    p->f12 = 0; p->f8 = 0; p->f4 = 0; p->f16 = 0; p->f20 = 0;
    zero = lbl_80366AE8;
    ((volatile V80262D38 *)&lbl_80357E78)->x = zero; ((volatile V80262D38 *)&lbl_80357E78)->y = zero; ((volatile V80262D38 *)&lbl_80357E78)->z = zero;
    one = *(volatile f32 *)&lbl_80366AEC;
    lbl_80357E78.x = one;
    lbl_80357E84.x = zero; lbl_80357E84.y = zero; lbl_80357E84.z = zero; lbl_80357E84.y = one;
    lbl_80357E90.x = zero; lbl_80357E90.y = zero; lbl_80357E90.z = zero; lbl_80357E90.z = one;
}
#pragma opt_propagation reset

} /* extern "C" */

extern "C" {
extern void *volatile lbl_8035B754;
void __dl__FPv(void *);
#pragma opt_propagation off
S80262D38 *fn_80262E58(S80262D38 *p, s16 f) {
    f32 one, zero;
    if (p) {
        lbl_8035B754 = 0;
        { void *g = lbl_8035B478; if (g && p->f12) fn_8023E138(g, p->f12); }
        if (p->f12) delete p->f12;
        if (p->f8) delete p->f8;
        if (p->f16) delete p->f16;
        p->f12 = 0; p->f8 = 0; p->f4 = 0; p->f16 = 0; p->f20 = 0;
        zero = lbl_80366AE8;
        ((volatile V80262D38 *)&lbl_80357E78)->x = zero; ((volatile V80262D38 *)&lbl_80357E78)->y = zero; ((volatile V80262D38 *)&lbl_80357E78)->z = zero;
        one = *(volatile f32 *)&lbl_80366AEC;
        lbl_80357E78.x = one;
        lbl_80357E84.x = zero; lbl_80357E84.y = zero; lbl_80357E84.z = zero; lbl_80357E84.y = one;
        lbl_80357E90.x = zero; lbl_80357E90.y = zero; lbl_80357E90.z = zero; lbl_80357E90.z = one;
        if (f > 0) __dl__FPv(p);
    }
    return p;
}
#pragma opt_propagation reset

} /* extern "C" */

extern "C" {

static inline void clear_row(f32 *p) {
    extern f32 lbl_80366AE8;
    p[0] = lbl_80366AE8;
    p[1] = lbl_80366AE8;
    p[2] = lbl_80366AE8;
}

/* QV=2.0p1 */
} /* extern "C" */
extern "C" {
void __ct__9C80262FA0Fv(u8 *p) {
    V80262D38 *a = &lbl_80357E78, *b = &lbl_80357E84, *c = &lbl_80357E90;
    f32 one, zero;
    *(void **)&lbl_8035B754 = p;
    *(s32 *)(p + 0xC) = 0;
    *(s32 *)(p + 0x8) = 0;
    *(s32 *)(p + 0x4) = 0;
    *(s32 *)(p + 0x10) = 0;
    *(s32 *)(p + 0x14) = 0;
    zero = *(volatile f32 *)&lbl_80366AE8;
    ((volatile V80262D38 *)a)->VSet(zero, zero, zero);
    one = *(volatile f32 *)&lbl_80366AEC;
    a->x = one;
    b->Set(zero, zero, zero);
    b->y = one;
    c->Set(zero, zero, zero);
    c->z = one;
}

} /* extern "C" */
