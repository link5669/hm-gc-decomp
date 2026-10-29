// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#define F(p, T, off) (*(T *)((u8 *)(p) + (off)))
typedef struct { u32 v[3]; } T12;
} /* extern "C" */
struct V801DF3A0 {
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3();
    virtual void m4(void *);
};
extern "C" {
extern T12 lbl_802ED4D8;
extern T12 lbl_802ED4E4;
extern f32 lbl_80365274;
void fn_801EF9A0(V801DF3A0 *, void *);
void fn_80108B94(void *, V801DF3A0 *, T12 *, s32);

void fn_801DF3A0(V801DF3A0 *p, const u8 *s) {
    T12 t1;
    T12 t2;
    f32 f;
    p->m4((void *)s);
    fn_801EF9A0(p, (void *)s);
    F(p, u32, 40) = F(s, u32, 8);
    F(p, u32, 44) = F(s, u32, 12);
    f = F(s, f32, 16);
    F(p, void *, 56) = F(F(p, void *, 40), void *, 28);
    F(p, void *, 60) = F(F(p, void *, 44), void *, 28);
    if (f > lbl_80365274) {
        F(p, f32, 48) = f;
    }
    t1 = lbl_802ED4D8;
    fn_80108B94(F(p, void *, 56), p, &t1, -1);
    t2 = lbl_802ED4E4;
    fn_80108B94(F(p, void *, 60), p, &t2, -1);
}

} /* extern "C" */
