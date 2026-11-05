// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct P801E7750 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); };
extern "C" {
typedef struct { u8 pad[8]; u8 f8[8]; u32 f16; f32 f20; f32 f24; f32 f28; } D801E7750;
void fn_801EF9A0(P801E7750 *p, const D801E7750 *d);
void fn_800F6E88(void *dst, const void *src);

void fn_801E7750(P801E7750 *p, const D801E7750 *d) {
    p->v4();
    fn_801EF9A0(p, d);
    {
        u32 v = d->f16;
        M2C_FIELD(p, u32 *, 52) = 0;
        M2C_FIELD(p, u32 *, 48) = 0;
        M2C_FIELD(p, u32 *, 48) = v;
    }
    M2C_FIELD(p, f32 *, 56) = d->f20;
    M2C_FIELD(p, f32 *, 60) = d->f24;
    M2C_FIELD(p, f32 *, 64) = d->f28;
    fn_800F6E88((u8 *)p + 40, d->f8);
}

} /* extern "C" */
