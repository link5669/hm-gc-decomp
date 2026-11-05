// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct P801F0470 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); };
extern "C" {
typedef struct { u8 pad[8]; s32 f8; s32 f12; s32 f16; s32 f20; } D801F0470;
void fn_801EF9A0(P801F0470 *p, const D801F0470 *d);

void fn_801F0470(P801F0470 *p, const D801F0470 *d) {
    p->v4();
    fn_801EF9A0(p, d);
    { s32 v = d->f8; M2C_FIELD(p, s32 *, 44) = 0; M2C_FIELD(p, s32 *, 40) = 0; M2C_FIELD(p, s32 *, 40) = v; }
    M2C_FIELD(p, s32 *, 52) = d->f16;
    M2C_FIELD(p, s32 *, 48) = d->f12;
    M2C_FIELD(p, s32 *, 56) = d->f20;
}

} /* extern "C" */
