// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern void *volatile lbl_8035B7A8;
extern char lbl_802AA548[];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
struct C8026ED20 { C8026ED20(); virtual ~C8026ED20(); virtual void a0(); virtual void a1(); virtual void stop(); u8 pad[428]; };
struct C80269FD0 { C80269FD0(); virtual ~C80269FD0(); u8 pad[1468]; };
struct Y { u8 pad[48]; virtual void y0(); virtual void y1(); virtual void y2(); virtual void y3(); virtual void y4(); virtual void y5(); virtual void y6(); virtual void y7(); virtual void y8(); virtual void y9(); virtual void y10(); virtual void y11(); virtual void y12(); virtual void y13(); virtual void y14(); virtual void *get(); };
struct Z { u8 pad[28]; virtual void z0(); virtual void z1(); virtual void z2(); virtual void set(void *, int, int); };
struct G { u8 pad[11340]; Y *f11340; u8 pad11344[744]; Z z; u8 padz[12100 - 12088 - sizeof(Z)]; void *f12100; u8 pad12104[8]; void *f12112; };
struct G460 { u8 pad[12]; G *f12; };
extern G460 *lbl_8035B460;
struct P { u8 pad[4]; void *f4; void *f8; };
struct T { C8026ED20 *f0; C80269FD0 *f4; int f8; };
void fn_80268DCC(C80269FD0 *);
void fn_8026D3FC(C8026ED20 *);
void fn_8026EDCC(void *);
void fn_8026A11C(void *);
void fn_8026E4C4(C8026ED20 *, void *, void *, const char *, void *);
void fn_8026985C(C80269FD0 *);
void fn_8026A15C(T *t, P *p) {
    if (t->f8) {
        if (t->f4) {
            fn_80268DCC(t->f4);
            delete t->f4;
        }
        if (t->f0) {
            t->f0->stop();
            fn_8026D3FC(t->f0);
            delete t->f0;
        }
        t->f0 = 0;
        t->f4 = 0;
        t->f8 = 0;
    }
    t->f8 = 1;
    lbl_8035B7A8 = p->f8;
    fn_8026EDCC(lbl_8035B7A8);
    fn_8026A11C(lbl_8035B7A8);
    if (lbl_8035B7A8 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B7A8);
    t->f0 = new C8026ED20;
    fn_800F7E98();
    if (t->f0 == 0) fn_800604C4(-4, 0, 0, 0);
    if (lbl_8035B7A8 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B7A8);
    t->f4 = new C80269FD0;
    fn_800F7E98();
    if (t->f4 == 0) fn_800604C4(-4, 0, 0, 0);
    G *g = lbl_8035B460->f12;
    g->z.set(g->f11340->get(), 0, 0);
    fn_8026E4C4(t->f0, g->f12100, g->f12112, lbl_802AA548, p->f4);
    fn_8026985C(t->f4);
}

} /* extern "C" */
