// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct T20_8003C674 {
    u8 b[20];
};
struct S_8003C674 {
    u8 pad[740];
    T20_8003C674 a[31];
    u32 *ptr[31];
    s32 cnt[31];
};
struct V_8003C674 {
    u8 pad[0xC0];
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void m3(void *, s32);
    virtual void p4();
    virtual s32 m5(const void *);
};
extern V_8003C674 *lbl_8035B684;
extern const char lbl_8035C1D0[7];
u32 *fn_800F8274(void *, const char *);
void fn_800F87F0(void *, const char *, u32 *);

bool fn_8003C674(S_8003C674 *p, const char *key, u32 **out) {
    s32 k;
    bool found;
    T20_8003C674 *q;
    s32 t;
    u8 buf[8];
    t = lbl_8035B684->m5(lbl_8035C1D0);
    *out = 0;
    k = t;
    if (t == -1) {
        lbl_8035B684->m3(buf, -1);
        k = lbl_8035B684->m5(buf);
    }
    q = &p->a[k];
    *out = fn_800F8274(q, key);
    found = *out != 0;
    if (*out == 0) {
        *out = p->ptr[k] + p->cnt[k];
        fn_800F87F0(q, key, *out);
        p->cnt[k]++;
    }
    return found;
}

} /* extern "C" */
