// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct T8010EE60 { u32 f0; u32 *f4; };
struct B8010EE60 { u8 pad[16]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual u32 v5(u32); };
struct O8010EE60 : B8010EE60 { u8 pad20[12]; u32 f32; u32 count() { return f32; } };
struct P8010EE60 { u32 f0; O8010EE60 *f4; T8010EE60 *f8; u32 f12;
  bool has() { return f8 != 0; }
};
extern "C" {
u32 fn_8010EE60(P8010EE60 *p, u32 i) {
    u32 v;
    if (p->f8 != 0 && p->has()) v = p->f8->f4[p->f12 + i]; else v = p->f12 + i;
    if (p->f12 + i < p->f4->count()) return p->f4->v5(v);
    return 0;
}

} /* extern "C" */
