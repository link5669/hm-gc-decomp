// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V80138D34 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual u32 v6(); };
struct S80138D34 { u8 pad[184]; V80138D34 *f184; u32 f188[4]; u32 f204[4]; };
extern "C" {
void fn_80138D34(S80138D34 *p, u32 a, s32 i) {
    p->f204[i] = a;
    p->f188[i] = p->f184->v6();
}

} /* extern "C" */
