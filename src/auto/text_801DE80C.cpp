// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#define F(p, T, off) (*(T *)((u8 *)(p) + (off)))
} /* extern "C" */
struct V801DE80C {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void m4(void *);
};
extern "C" {
void fn_801EF9A0(V801DE80C *, void *);

void fn_801DE80C(V801DE80C *p, const u8 *s) {
    if (F(p, s32, 8) != 0) {
        p->m4((void *)s);
    }
    fn_801EF9A0(p, (void *)s);
    {
        u32 val = F(s, u32, 8);
        F(p, u32, 44) = 0;
        F(p, u32, 40) = 0;
        F(p, u32, 40) = val;
    }
    F(p, u32, 48) = F(s, u32, 12);
}

} /* extern "C" */
