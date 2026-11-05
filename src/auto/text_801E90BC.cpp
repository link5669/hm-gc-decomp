// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Q801E7D14 { u8 pad[8]; u32 f8; u32 fC; u32 f10; u32 f14; } Q801E7D14;
} /* extern "C" */
struct H801E7D14 { u32 a; u32 b; void Clear() { b = 0; a = 0; } };
struct V801E7D14 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    u8 pad[36];
    H801E7D14 h; u32 f30; u32 f34; u32 f38;
};

extern "C" {
void fn_801EF9A0(V801E7D14 *p, const Q801E7D14 *q);
void fn_801E90BC(V801E7D14 *p, const Q801E7D14 *q) {
    u32 d, c, b, a;
    p->v4();
    fn_801EF9A0(p, q);
    a = q->f8; b = q->fC; c = q->f10; d = q->f14;
    p->h.b = 0;
    p->h.a = 0;
    p->h.a = a;
    p->f30 = b;
    p->f34 = c;
    p->f38 = d;
}

} /* extern "C" */
