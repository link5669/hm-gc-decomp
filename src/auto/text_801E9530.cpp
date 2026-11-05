// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct P801E9530 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); };
extern "C" {
typedef struct { u8 pad[20]; s32 f20; } D801E9530;
void fn_801E0628(P801E9530 *p, const D801E9530 *d);

void fn_801E9530(P801E9530 *p, const D801E9530 *d) {
    p->v4();
    fn_801E0628(p, d);
    { s32 v = d->f20; M2C_FIELD(p, s32 *, 60) = 0; M2C_FIELD(p, s32 *, 56) = 0; M2C_FIELD(p, s32 *, 56) = v; }
}

} /* extern "C" */
