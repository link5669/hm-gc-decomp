// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct A { u8 pad_[128]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void v39(int,int); virtual void v40(int,int); virtual void v41(int,int); virtual void v42(int,int); virtual void v43(int); virtual void v44(int); virtual void s45(); virtual void s46(); virtual void s47(); virtual void v48(int); virtual void v49(int); virtual void s50(); virtual void s51(); virtual void s52(); virtual void v53(int); virtual void s54(); virtual void s55(); virtual void s56(); virtual void s57(); virtual void v58(int,int); };
struct B { u8 pad_[16]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void v4(); };
struct C { u8 pad_[256]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void v3(void*,f32); };
#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
extern f32 lbl_80364FD4;
extern f32 lbl_80364FD8;
extern f32 lbl_80364FDC;
void fn_801C2BB0(void *, void *, f32);
static inline void clr(u8 *p) { if (F(p,100,void**)) for (u32 i = 0; i < F(p,104,u32); i++) { if (!F(p,100,void**)[i]) break; F(p,100,void**)[i] = 0; } }
void __dt__9C801C3FD0Fv(void);
void fn_801C3DD8(void);
void fn_801C3ECC(void);
void *lbl_802EBD10[5] = { 0, 0, (void *)__dt__9C801C3FD0Fv, (void *)fn_801C3DD8, (void *)fn_801C3ECC };
void fn_801C28C0(u8 *p, f32 dt) {
    u32 i;
    if (F(p,100,B**)) for (i = 0; i < F(p,104,u32); i++) if (F(p,100,B**)[i]) F(p,100,B**)[i]->v4();
    fn_801C2BB0(p, F(p,4,void*), dt);
    if (F(p,0,u8*) && F(F(p,0,u8*),20,C*) && F(F(p,0,u8*),24,void*))
        F(F(p,0,u8*),20,C*)->v3(F(F(p,0,u8*),24,void*), dt / lbl_80364FD4);
    F(p,88,f32) += dt;
    if (F(p,44,u32)) {
        F(p,72,f32) -= dt;
        if (F(p,72,f32) <= lbl_80364FD8) { F(p,72,f32) = lbl_80364FDC; F(p,44,int) = 0; }
    }
    if (F(p,12,A*) && F(p,84,u32) && F(p,88,f32) >= F(p,92,f32)) {
        F(p,88,f32) = lbl_80364FD8;
        switch (F(p,84,u32)) {
        case 66: F(p,12,A*)->v39(F(p,80,int), 1); break;
        case 67: F(p,12,A*)->v40(F(p,80,int), 1); break;
        case 69: F(p,12,A*)->v41(F(p,80,int), 1); break;
        case 70: F(p,12,A*)->v42(F(p,80,int), 1); break;
        case 72: F(p,12,A*)->v43(F(p,80,int)); break;
        case 73: F(p,12,A*)->v44(F(p,80,int)); break;
        case 77: F(p,12,A*)->v48(F(p,80,int)); break;
        case 78: F(p,12,A*)->v49(F(p,80,int)); break;
        case 81: F(p,12,A*)->v53(F(p,80,int)); break;
        default: F(p,12,A*)->v58(F(p,84,u32), F(p,80,int)); break;
        }
    }
    clr(p);
}

} /* extern "C" */
