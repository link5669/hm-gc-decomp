// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

void fn_800604C4(s32, s32, s32, s32); void fn_800F7EC0(void *); void fn_800F7E98(void); extern void *lbl_8035B560;
}
struct C8024AC90 { u8 d[108]; C8024AC90(); ~C8024AC90(); };
struct C8002FAE0 { u8 d[12]; C8002FAE0(); };
struct C80226CEC { u8 d[8]; C80226CEC(); };
struct Sub { u8 pad[160]; virtual void load(void *x, char *name, void *p); virtual void def(void *x); };
struct M { u32 n; C8024AC90 *a; C8002FAE0 *b; u16 *c; C80226CEC *d; u32 f20; u8 pad[4]; Sub sub; };
struct G2 { u8 pad[11344]; void *x; };
struct G { G2 *g; };
extern "C" {
extern G *lbl_8035B684;
extern char lbl_80366388[8];
s32 fn_800F6CD0(char *a, char *b);

void fn_8024B2D8(M *m, u32 n, char *name, void *p) {
    void *x;
    m->f20 = 1;
    m->n = n;
    if (!lbl_8035B560) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B560);
    m->a = new C8024AC90[n];
    fn_800F7E98();
    if (!m->a) fn_800604C4(-4, 0, 0, 0);
    x = lbl_8035B684->g->x;
    if (!lbl_8035B560) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B560);
    m->b = new C8002FAE0[m->n * 3];
    fn_800F7E98();
    if (!m->b) fn_800604C4(-4, 0, 0, 0);
    if (!lbl_8035B560) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B560);
    m->c = new u16[m->n * 3];
    fn_800F7E98();
    if (!m->c) fn_800604C4(-4, 0, 0, 0);
    if (!lbl_8035B560) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B560);
    m->d = new C80226CEC[m->n * 3];
    fn_800F7E98();
    if (!m->d) fn_800604C4(-4, 0, 0, 0);
    if (fn_800F6CD0(name, lbl_80366388)) m->sub.def(x);
    else m->sub.load(x, name, p);
}

} /* extern "C" */
