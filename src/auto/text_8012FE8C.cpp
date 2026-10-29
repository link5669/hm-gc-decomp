// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" void *memcpy(void *, const void *, unsigned long);
extern u32 lbl_80363F88;
struct C4 { u8 r, g, b, a; };
struct P { u8 pad[28]; u32 n28; u32 *b32; u8 pad36[4]; u32 n40; u32 *b44; };
struct T {
    C4 c0; C4 c4; C4 c8; C4 c12; u8 pad16[4]; u32 f20; u32 *f24; u32 *f28; u32 g32; u32 f36; f32 f40; u32 f44; u8 b48; u8 b49; u8 pad50[2]; u8 b52; u8 b53; u8 b54; u8 b55; C4 c56; u8 pad60[4]; P *f64;
    virtual void apply(void *); virtual void v1(); virtual void reset();
};
static inline u32 *alloc28(P *p, u32 n) { u32 *r = &p->b32[p->n28]; p->n28 += n; return r; }
static inline u32 *alloc40(P *p, u32 n) { u32 *r = &p->b44[p->n40]; p->n40 += n; return r; }
void fn_8012FE8C(T *t, void *a, P *p, T *s) {
    if (t->f44 & 1) t->reset();
    t->f64 = p;
    t->f44 = s->f44;
    t->c0 = s->c0;
    t->c4 = s->c4;
    t->c12 = s->c12;
    t->c8 = s->c8;
    t->f20 = s->f20;
    t->g32 = s->g32;
    t->f36 = s->f36;
    t->f40 = s->f40;
    t->b52 = s->b52;
    t->b48 = s->b48;
    t->b53 = s->b53;
    t->b54 = s->b54;
    t->b55 = s->b55;
    t->b49 = s->b49;
    t->c56 = s->c56;
    t->b52 = s->b52;
    if (s->f24) {
        t->f24 = alloc28(p, t->b52);
        if (s->f24) memcpy(t->f24, s->f24, t->b52 * 4);
    }
    t->b48 = s->b48;
    if (s->f28) {
        t->f28 = alloc40(p, t->b48);
        if (s->f28) memcpy(t->f28, s->f28, t->b48 * 4);
    }
    t->apply(a);
    t->f44 |= lbl_80363F88;
}

} /* extern "C" */
