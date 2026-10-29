// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct R { u8 pad_[292]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual u32 v5(); };
#define F(p,o,t) (*(t*)((u8*)(p)+(o)))
extern void *lbl_8035B080;
void fn_800FB064(R *, char *);
u32 fn_800FADA8(R *);
int fn_800FB33C(R *);
f32 fn_800FB2E0(R *);
void *fn_800F9398(void *, char *);
void *fn_800F9788(void *, char *, char *);
void fn_801EB474(void *, R *);
void fn_800604C4(int, int, int, int);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
static inline void *find(u8 *m, char *g, char *n) { if ((u32)g == 0 || !g[0]) return fn_800F9398(m + 4, n); return fn_800F9788(m + 52, g, n); }
void __dt__9C801E4C2CFv(void);
void fn_801E47DC(u8 *p, R *r, int tok);
void fn_801E4A94(void);
void fn_801E4B2C(void);
void fn_801EB698(void);
void fn_801EB724(void);
void fn_801EB728(void);
void fn_801EB738(void);
void fn_801EB764(void);
void *__vt__9C801E4C2C[11] = { 0, 0, (void *)fn_801E47DC, (void *)fn_801EB698, (void *)__dt__9C801E4C2CFv, (void *)fn_801E4B2C, (void *)fn_801E4A94, (void *)fn_801EB724, (void *)fn_801EB764, (void *)fn_801EB738, (void *)fn_801EB728 };
void fn_801E47DC(u8 *p, R *r, int tok) {
    char b16[8];
    char b8[8];
    u32 i;
    switch (tok) {
    case 116:
        fn_800FB064(r, b16); fn_800FB064(r, b8);
        F(p,24,void*) = find(F(F(p,16,u8*),180,u8*), b8, b16);
        break;
    case 117: F(p,120,u32) = r->v5(); break;
    case 118: F(p,116,int) = 2; break;
    case 119: F(p,116,int) = 1; F(p,124,int) = 1; break;
    case 120: F(p,116,int) = 1; F(p,124,int) = 0; break;
    case 123: F(p,116,int) = 1; F(p,124,int) = 3; break;
    case 124: F(p,116,int) = 1; F(p,124,int) = 2; break;
    case 125:
        F(p,116,int) = 1;
        F(p,124,int) = fn_800FB33C(r);
        F(p,124,int) += 4096;
        break;
    case 96: F(p,128,int) = 1; F(p,132,f32) = fn_800FB2E0(r); break;
    case 97: F(p,128,int) = 4; F(p,132,f32) = fn_800FB2E0(r); break;
    case 98: F(p,128,int) = 6; F(p,132,f32) = fn_800FB2E0(r); break;
    case 99: F(p,128,int) = 3; F(p,132,f32) = fn_800FB2E0(r); break;
    case 100: F(p,128,int) = 5; F(p,132,f32) = fn_800FB2E0(r); break;
    case 101: F(p,128,int) = 2; F(p,132,f32) = fn_800FB2E0(r); break;
    case 102: F(p,128,int) = 7; break;
    case 121:
        F(p,140,u32) = fn_800FADA8(r) * 2;
        if (!lbl_8035B080) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B080);
        F(p,136,f32*) = new f32[F(p,140,u32)];
        fn_800F7E98();
        if (!F(p,136,f32*)) fn_800604C4(-4, 0, 0, 0);
        for (i = 0; i < F(p,140,u32); i++) F(p,136,f32*)[i] = fn_800FB2E0(r);
        r->v5();
        break;
    default: fn_801EB474(p, r); break;
    }
}

} /* extern "C" */
