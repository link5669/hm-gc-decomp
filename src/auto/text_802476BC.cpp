// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void __dla__FPv(void *);
void *__nwa__FUl(u32);
void fn_80264840(void *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
extern void *lbl_8035B4F8;
extern f32 lbl_80366250;
extern u16 lbl_80366290;
typedef struct S802476BC {
    u32 f0;
    u16 f4;
    u16 f6;
    f32 f8;
    u32 f12, f16, f20;
    u8 *f24, *f28, *f32;
    void *f36, *f40, *f44, *f48, *f52, *f56, *f60;
    u32 f64;
    void *f68;
    u32 f72;
    u8 pad76[28];
    u32 f104;
} S802476BC;
void fn_802476BC(S802476BC *p) {
    if (p->f4 & 1) {
        if (p->f12 != 0) {
            if (p->f24 != 0) {
                __dla__FPv(p->f24 - 16);
            }
            __dla__FPv(p->f56);
            __dla__FPv(p->f60);
            if (p->f28 != 0) {
                if (p->f28 != 0) {
                    __dla__FPv(p->f28 - 16);
                }
            }
            if (p->f32 != 0) {
                if (p->f32 != 0) {
                    __dla__FPv(p->f32 - 16);
                }
            }
            if (p->f36 != 0) __dla__FPv(p->f36);
            if (p->f44 != 0) __dla__FPv(p->f44);
            if (p->f48 != 0) __dla__FPv(p->f48);
            if (p->f52 != 0) __dla__FPv(p->f52);
            if (p->f40 != 0) __dla__FPv(p->f40);
        }
        if (p->f68 != 0) __dla__FPv(p->f68);
        p->f0 = 1;
        p->f8 = lbl_80366250;
        p->f12 = 0;
        p->f16 = 0;
        p->f20 = 0;
        p->f24 = 0;
        p->f28 = 0;
        p->f32 = 0;
        p->f36 = 0;
        p->f44 = 0;
        p->f48 = 0;
        p->f40 = 0;
        p->f52 = 0;
        p->f64 = 0;
        p->f68 = 0;
        p->f56 = 0;
        p->f60 = 0;
        fn_80264840(&p->f72);
        p->f72 = 0;
        p->f4 = 0;
        p->f104 = 0;
    }
    if (p->f68 == 0) {
        if (lbl_8035B4F8 == 0) {
            fn_800604C4(-2, 0, 0, 0);
        }
        fn_800F7EC0(lbl_8035B4F8);
        p->f68 = __nwa__FUl(3360);
        fn_800F7E98();
        if (p->f68 == 0) {
            fn_800604C4(-4, 0, 0, 0);
        }
    }
    p->f4 |= lbl_80366290;
}

} /* extern "C" */
