// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
template <int N> struct VA {
    u8 pad_[N];
    virtual void s0(); virtual void s1();
};
struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[12];
};
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void s11(int); };
struct VX { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void s6(void *); };
struct V28 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void s28(void *);
};
extern "C" {
struct G { u8 pad[11332]; V28 *v11332; u8 pad11336[764]; VX *x12100; };
struct P {
    u8 pad0[16];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual s32 s3();
    u8 pad20[52];
    s32 i72;
    u8 pad76[72];
    C8023C7CC *it;
    u8 pad152[4];
    void *a156;
    void *a160;
    VA<116> m164;
    VA<36> m284;
    void *a324;
    u8 pad328[288];
    u8 s616[20];
    s32 i636;
    u8 pad640[208];
    void *a848;
};
extern char lbl_80366440[8], lbl_80366448[8], lbl_80366450[8], lbl_80366458[8];
extern u8 *lbl_8035B460;
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, char *);
O *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);
void fn_802501D4(O *);
void fn_80250E80(O *);
void fn_80272DDC(void *, int);
void fn_8024FF04(u8 *);
void fn_8023CC40(P *);

static inline O *get(C8023C7CC *it) { return it->a ? fn_8023A490(it->a, it->b) : (O *)0; }

void fn_8024EECC(P *p) {
    VX *x;
    G *g;
    if (p->s3()) {
        fn_8023C720(p->it, p);
        for (fn_8023C528(p->it, lbl_80366440); p->it->a; fn_8023C3F4(p->it)) fn_802501D4(get(p->it));
        for (fn_8023C528(p->it, lbl_80366448); p->it->a; fn_8023C3F4(p->it)) fn_80250E80(get(p->it));
        for (fn_8023C528(p->it, lbl_80366450); p->it->a; fn_8023C3F4(p->it)) get(p->it)->s11(0);
        for (fn_8023C528(p->it, lbl_80366458); p->it->a; fn_8023C3F4(p->it)) get(p->it)->s11(0);
    }
    if (p->a848) fn_80272DDC(p->a848, 1);
    g = *(G **)(lbl_8035B460 + 12);
    x = g->x12100;
    if (p->a160) g->v11332->s28(p->a160);
    if (p->a156) g->v11332->s28(p->a156);
    p->m164.s1();
    p->m284.s1();
    if (p->a324) x->s6(p->a324);
    fn_8024FF04(p->s616);
    p->i72 = 0;
    p->a156 = 0;
    p->a160 = 0;
    p->a324 = 0;
    p->i636 = 0;
    p->a848 = 0;
    fn_8023CC40(p);
}

} /* extern "C" */
