// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V801DFA10 { u32 f0; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(void *); };
struct E801DFA10 { u8 pad[12]; V801DFA10 *f12; u8 pad2[44]; };
struct O801DFA10 { u8 pad[172]; s32 f172; E801DFA10 *f176; };
struct P801DFA10 { u8 pad[24]; u8 f24[8]; void *f32; u8 pad2[4]; s32 f40; u8 pad3[8]; V801DFA10 f52; };
extern "C" {
void fn_801EB728(P801DFA10 *);
O801DFA10 *fn_8019556C(void *);
void fn_801DFA10(P801DFA10 *p) {
    O801DFA10 *o; u32 end; u32 off; s32 i;
    fn_801EB728(p);
    o = fn_8019556C(p->f32);
    if (o == 0) return;
    i = p->f40;
    if (i >= 0) { end = i; } else { i = 0; end = o->f172 - 1; }
    off = i * 60;
    for (; i <= end; i++) { V801DFA10 *q = *(V801DFA10 **)((u8 *)o->f176 + off + 12); if (q) q->v6(p->f24); else p->f52.v6(p->f24); off += 60; }
}

} /* extern "C" */
