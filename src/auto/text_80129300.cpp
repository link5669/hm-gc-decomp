// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_80134848(u32);
} /* extern "C" */
struct R80129300 {
    u8 pad[16];
    s32 f16;
    s32 f20;
    u8 pad2[4];
    u8 f28[1340 - 28];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void v5(s32 a, void *self, u32 c);
};
struct S80129300 {
    u8 pad[26];
    u16 f26;
    u8 pad2[4];
    virtual void v0();
    virtual void v1();
    virtual void v2(); virtual void v3();
    virtual void v4(void *d);
    virtual void v5();
    virtual void v6();
    virtual s32 v7(s32 a, s32 b, s32 c, u8 *d, u32 e);
};
extern "C" {
R80129300 *fn_801348E8(void);
void fn_801488B4(R80129300 *, s32);
void fn_800604C4(s32, s32, s32, s32);
void fn_80129300(S80129300 *self, s32 a, s32 b, u32 c, void *d) {
    R80129300 *r;
    if (self->f26 & 1) {
        self->v1();
    }
    fn_80134848(c);
    r = fn_801348E8();
    fn_801488B4(r, b);
    if (self->v7(a, r->f16, r->f20, r->f28, c) == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    if (d != 0) {
        self->v4(d);
    }
    r->v5(a, self, c & 0x80);
    r->v4();
}

} /* extern "C" */
