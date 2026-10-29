// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 *data;
    s32 stride;
    u8 pad[112];
} LockInfo_FA0;

} /* extern "C" */
struct V80139FA0 { char vptr_pad[12]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void unlock(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void lock(LockInfo_FA0 *, s32); };
extern "C" {

void fn_80139FA0(V80139FA0 *p, s32 idx, f32 *out) {
    LockInfo_FA0 info;
    f32 *src;
    p->lock(&info, 4);
    src = (f32 *)(info.data + idx * info.stride);
    out[0] = src[0];
    out[1] = src[1];
    out[2] = src[2];
    p->unlock();
}

} /* extern "C" */
