// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct V80116630 { u8 pad[0x8]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void m(void *, s32, s32); };
V80116630 **fn_80110444(u32, u32, s32);
void fn_800FA5D8(void *, void *);

void fn_80116630(u32 a, u32 b, void *out) {
    V80116630 **pp;
    V80116630 *p;
    void *buf;

    pp = fn_80110444(a, b, 0);
    if (pp != 0 && (p = *pp) != 0) {
        buf = *(s32 *)((u8 *)p + 52) != 0 ? (void *)((u8 *)p + 32) : (void *)((u8 *)p + 12);
        p->m(buf, 0, 1);
        fn_800FA5D8(buf, out);
    }
}

} /* extern "C" */
