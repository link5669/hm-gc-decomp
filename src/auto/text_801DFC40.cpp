// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V801DFC40 { u32 f0; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(void *); };
struct E801DFC40 { u8 pad[12]; V801DFC40 *f12; u8 pad2[44]; };
struct O801DFC40 { u8 pad[172]; s32 f172; E801DFC40 *f176; };
struct P801DFC40 { u8 pad[24]; u8 f24[8]; void *f32; u32 f36; s32 f40; u32 f44; s32 f48; V801DFC40 f52; u8 pad4[20]; u32 f80; };
extern "C" {
void fn_801EB7B0(P801DFC40 *);
void fn_8017AD2C(V801DFC40 *);
O801DFC40 *fn_8019556C(void *);
void fn_801DFC40(P801DFC40 *p) {
    if (p->f44 != 0) {
        O801DFC40 *o; u32 end; u32 off; s32 i;
        o = fn_8019556C(p->f32);
        if (o != 0) {
            i = p->f40;
            if (i >= 0) { end = i; } else { i = 0; end = o->f172 - 1; }
            off = i * 60;
            for (; i <= end; i++) { V801DFC40 *q = *(V801DFC40 **)((u8 *)o->f176 + off + 12); if (q) q->v6(p->f24); else p->f52.v6(p->f24); off += 60; }
        }
    }
    fn_801EB7B0(p);
    fn_8017AD2C(&p->f52);
    p->f36 = 0;
    p->f32 = 0;
    p->f80 = 0;
    p->f44 = 0;
    p->f40 = -1;
    p->f48 = 32;
}

} /* extern "C" */
