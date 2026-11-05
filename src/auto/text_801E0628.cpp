// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Q801E0628 { u8 pad[8]; char s[8]; u32 f16; } Q801E0628;
struct V801E0628 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); };
void fn_801EF9A0(V801E0628 *p, const Q801E0628 *q);
void fn_800F6E88(char *d, const char *s);
void fn_801E0628(V801E0628 *p, const Q801E0628 *q) {
    p->v4();
    fn_801EF9A0(p, q);
    {
        u32 v = q->f16;
        M2C_FIELD(p, u32 *, 52) = 0;
        M2C_FIELD(p, u32 *, 48) = 0;
        M2C_FIELD(p, u32 *, 48) = v;
    }
    fn_800F6E88((char *)p + 40, q->s);
}

} /* extern "C" */
