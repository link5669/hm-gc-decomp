// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#pragma optimization_level 2
} /* extern "C" */
struct Rd {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void open(void *name, s32 a, s32 b);
    virtual void v3();
    virtual void v4();
    virtual u32 next();
};
struct C80215F50 {
    C80215F50();
    ~C80215F50();
    u8 pad[44];
    Rd *f44;
    u8 pad2[4];
};
struct A {
    u8 pad[16];
    virtual void v0();
    virtual void reset();
    u8 *f20;
};
struct Buf { u32 a, b; };
extern "C" {
extern char lbl_80363930[4];
extern char lbl_80363934[6];
extern char lbl_802E2538[];
s32 fn_80215C84(C80215F50 *r, u32 name, char *s, s32 a, s32 b);
void fn_80060E30(s32 e, char *fmt, ...);
void fn_800FB064(Rd *r, Buf *b);
void fn_800FAFA8(Rd *r);
u32 fn_800FB33C(Rd *r);
void fn_800FAF50(Rd *r);
void fn_800FAEF8(Rd *r);
void fn_800FAEA0(Rd *r);
void fn_800F8E38(A *a, u32 n);
void fn_801087AC(void *b, A *a, Buf *p);
void fn_80108D14(u8 **p, u32 n);
void fn_800F87F0(A *a, Buf *b, u8 *d);
void fn_80215BFC(C80215F50 *r);

static inline void rdall(A *a, Rd *r, u32 n, Buf *v, u32 i) {
    u32 off;
    for (off = i; i < n; off += 12, i++) {
        fn_800FB064(r, v);
        fn_800F87F0(a, v, a->f20 + off);
    }
}

static inline void rd58(A *a, void *b, Rd *r, Buf *ph, Buf *v, u32 &off) {
    u32 n;
    u32 i;
    fn_800FAFA8(r);
    n = fn_800FB33C(r);
    fn_800FAF50(r);
    fn_800FAEF8(r);
    fn_800F8E38(a, n);
    fn_801087AC(b, a, ph);
    fn_80108D14(&a->f20, n);
    for (off = i = 0; i < n; off += 12, i++) {
        fn_800FB064(r, v);
        fn_800F87F0(a, v, a->f20 + off);
    }
    fn_800FAEA0(r);
}
void fn_8010917C(A *a, void *b, u32 name) {
    s32 e;
    u32 t;
    Buf *ph;
    Rd *r;
    Buf v;
    Buf hd;
    C80215F50 rd;
    if ((e = fn_80215C84(&rd, name, lbl_80363930, 2, 0)) != 0) fn_80060E30(e, lbl_80363934, name, lbl_80363930);
    r = rd.f44;
    if (a->f20) a->reset();
    r->open(lbl_802E2538, 2, 0);
    t = r->next();
    ph = 0;
    if (t == 57) {
        fn_800FB064(r, &hd);
        ph = &hd;
        t = r->next();
    }
    while (t != 0) {
        switch (t) {
        case 58:
            rd58(a, b, r, ph, &v, name);
        }
        t = r->next();
    }
    fn_80215BFC(&rd);
}

#pragma optimization_level reset

} /* extern "C" */
