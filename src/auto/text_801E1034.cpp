// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct VC801E1034 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void m(); };
struct S801E1034 { u8 pad[8]; u32 f8; f32 a[3]; f32 b[4]; };
struct D801E1034 { u8 pad[40]; u32 f40; f32 b[4]; f32 a[3]; };
extern "C" {
void fn_801EF9A0(void *, void *);
void fn_801E1034(D801E1034 *o, const S801E1034 *p) {
    ((VC801E1034 *)o)->m();
    fn_801EF9A0(o, (void *)p);
    o->f40 = p->f8;
    o->a[0] = p->a[0];
    o->a[1] = p->a[1];
    o->a[2] = p->a[2];
    o->b[0] = p->b[0];
    o->b[1] = p->b[1];
    o->b[2] = p->b[2];
    o->b[3] = p->b[3];
}

} /* extern "C" */
