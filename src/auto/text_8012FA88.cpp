// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct R { u8 pad[0x124]; virtual void p0(); virtual void p1(); virtual void setup(void *, s32, s32); virtual void p3(); virtual void err(s32); virtual u32 next(); };
struct Nm { u8 d[8]; };
struct E;
struct P { u8 pad[0x10]; virtual void p0(); virtual void clr(); virtual void init(void *); virtual E *get(u32); u32 n; };
struct C80215F50 { C80215F50(); ~C80215F50(); u8 b[44]; R *rd; u8 c[8]; };
extern "C" {
extern char lbl_80363F70[4];
extern char lbl_80363F74[6];
extern u8 lbl_802E48B0[];
s32 fn_80215C84(C80215F50 *, const char *, const char *, s32, s32);
void fn_80060E30(s32, const char *, ...);
void fn_80215BFC(C80215F50 *);
u32 fn_800FADA8(R *); void fn_800FB064(R *, void *); void fn_800FB000(R *, s32); void fn_800FAEA0(R *);
void fn_800F8E38(P *, u32);
void fn_80135EE4(void *, P *, Nm *);
void fn_800F87F0(P *, void *, E *);
void fn_8012F7F8(E *, void *, P *, R *);

void fn_8012FA88(P *p, void *x, const char *name) {
    C80215F50 obj;
    Nm nm;
    Nm key;
    Nm *pn;
    u32 i;
    R *r;
    u32 k;
    s32 err;
    err = fn_80215C84(&obj, name, lbl_80363F70, 2, 0);
    if (err != 0) fn_80060E30(err, lbl_80363F74, name, lbl_80363F70);
    r = obj.rd;
    if (p->n != 0) p->clr();
    r->setup(lbl_802E48B0, 9, 0);
    k = r->next();
    pn = 0;
    if (k == 57) {
        fn_800FB064(r, &nm);
        fn_800FB000(r, 58);
        pn = &nm;
    } else if (k != 58) {
        r->err(30);
    }
    p->n = fn_800FADA8(r);
    fn_800F8E38(p, p->n);
    fn_80135EE4(x, p, pn);
    p->init(x);
    for (i = 0; i < p->n; i++) {
        fn_800FB000(r, 58);
        fn_800FB064(r, &key);
        pn = (Nm *)p->get(i);
        fn_800F87F0(p, &key, (E *)pn);
        fn_8012F7F8((E *)pn, x, p, r);
    }
    fn_800FAEA0(r);
    fn_80215BFC(&obj);
}

} /* extern "C" */
