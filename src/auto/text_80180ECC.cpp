// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800E1E88(void *p, void *dtor);
void __dt__9C8017D12CFv(void);
void __dt__9C801829F8Fv(void);
void __dt__9C8017ED58Fv(void);
void __dt__9C801850ACFv(void);
void __dt__9C8018AE9CFv(void);
void __dt__9C8018ED98Fv(void);
void __dt__9C80195170Fv(void);
void __dt__9C80215B8CFv(void);
void __dt__9C80187498Fv(void);
void __dt__9C8019E778Fv(void);
void __dt__9C8019CF04Fv(void);
} /* extern "C" */
struct V80180ECC { u8 pad[16]; virtual void v0(); virtual void v1(); };
extern "C" {
typedef struct S80180ECC {
    void *f0, *f4, *f8, *f12, *f16, *f20, *f24, *f28, *f32, *f36, *f40, *f44;
    u8 m48[20];
    u8 m68[20];
    s16 f88, f90, f92, f94, f96, f98, f100, f102, f104, f106, f108;
    u8 pad110[2];
    s32 f112;
} S80180ECC;

void fn_80180ECC(S80180ECC *p) {
    if (p->f24) fn_800E1E88(p->f24, (void *)__dt__9C8017D12CFv);
    if (p->f44) fn_800E1E88(p->f44, (void *)__dt__9C801829F8Fv);
    if (p->f28) fn_800E1E88(p->f28, (void *)__dt__9C8017ED58Fv);
    if (p->f12) fn_800E1E88(p->f12, (void *)__dt__9C801850ACFv);
    if (p->f16) fn_800E1E88(p->f16, (void *)__dt__9C8018AE9CFv);
    if (p->f8) fn_800E1E88(p->f8, (void *)__dt__9C8018ED98Fv);
    if (p->f4) fn_800E1E88(p->f4, (void *)__dt__9C80195170Fv);
    if (p->f32) fn_800E1E88(p->f32, (void *)__dt__9C80215B8CFv);
    if (p->f36) fn_800E1E88(p->f36, (void *)__dt__9C80187498Fv);
    if (p->f40) fn_800E1E88(p->f40, (void *)__dt__9C8019E778Fv);
    if (p->f20) fn_800E1E88(p->f20, (void *)__dt__9C8019CF04Fv);
    ((V80180ECC *)p->m68)->v1();
    ((V80180ECC *)p->m48)->v1();
    p->f0 = 0; p->f4 = 0; p->f8 = 0; p->f12 = 0; p->f16 = 0; p->f28 = 0; p->f20 = 0; p->f44 = 0;
    p->f24 = 0; p->f32 = 0; p->f36 = 0; p->f40 = 0; p->f112 = 0;
    p->f88 = 0; p->f90 = 0; p->f92 = 0; p->f94 = 0; p->f98 = 0; p->f108 = 0; p->f100 = 0;
    p->f102 = 0; p->f96 = 0; p->f104 = 0; p->f106 = 0;
}

} /* extern "C" */
