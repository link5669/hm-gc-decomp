#include "common.h"
#pragma explicit_zero_data on
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {
__declspec(section ".sdata2") u32 lbl_80364A90 = 2;
__declspec(section ".sdata2") u32 lbl_80364A94 = 1;
__declspec(section ".sdata2") u32 lbl_80364A98 = 4;
__declspec(section ".sdata2") f32 lbl_80364A9C = 0.0f;
}

extern "C" {

struct R { u8 pad_[292]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void v4(int); virtual u32 v5(); };
struct Q { u8 pad_[4]; virtual void s0(); virtual void v1(void*); };
#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
void fn_800FB064(R *, char *);
void fn_800FB000(R *, int);
void fn_800FAEF8(R *);
u32 fn_800FB33C(R *);
f32 fn_800FB2E0(R *);
void *fn_800F9398(void *, char *);
void *fn_800F9788(void *, char *, char *);
void fn_8013E85C(void *, void *);
static inline void *find(u8 *m, char *g, char *n) { if ((u32)g == 0 || !g[0]) return fn_800F9398(m + 420, n); return fn_800F9788(m + 444, g, n); }
#pragma opt_loop_invariants off
void fn_8018CFA0(u8 *p, u8 *lib, R *r) {
    char b16[8];
    char b8[8];
    f32 v = lbl_80364A9C;
    int has = 0;
    u32 t;
    fn_800FB000(r, 112);
    fn_800FAEF8(r);
    while ((t = r->v5()) != 6) {
        switch (t) {
        case 113: {
            void *x;
            u32 n;
            fn_800FB064(r, b16);
            fn_800FB064(r, b8);
            x = find(lib, b8, b16);
            if (!x) r->v4(37);
            fn_8013E85C(p, x);
            F(p,0,u32) |= lbl_80364A90;
            if (F(p,12,Q*)) F(p,12,Q*)->v1(p);
            F(p,20,u32) |= lbl_80364A94;
            F(p,0,u32) |= lbl_80364A98;
            n = fn_800FB33C(r);
            if (F(p,20,u32) & 1) F(p,4,f32) = (int)(n % F(F(p,16,u8*),12,u32));
            break;
        }
        case 72:
            v = fn_800FB2E0(r);
            has = 1;
            break;
        case 83:
            F(p,24,u32) = fn_800FB33C(r);
            break;
        default:
            r->v4(30);
            break;
        }
    }
    if (has) F(p,8,f32) = v;
}
#pragma opt_loop_invariants reset

} /* extern "C" */

