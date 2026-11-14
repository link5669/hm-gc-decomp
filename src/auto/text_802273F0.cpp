#include "common.h"
namespace N802273F0 {

// NonMatching draft (wA_80247CF0): DIFF 18 - only loop-body scheduling (target copies r before the u32->f32 temp stores; lwz lbl_8035B374 before last two w stores).
extern "C" {
struct V { f32 x, y, z; };
extern u8 lbl_80357E90[];
struct G374 { };
extern void *lbl_8035B374;
struct E { u32 f0; u8 pad4[16]; E *f20; };
struct O { u32 f0; u8 pad4[20]; V pos; u8 pad36[20]; E *f56; u8 pad60[44]; virtual void a0(); virtual void a1(); virtual void upd(); };
struct S396 { u8 pad[156]; O *f156; };
struct H { virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7(); virtual void h8(); virtual void h9();
    virtual void h10(); virtual void h11(); virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15(); virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
    virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23(); virtual void h24(); virtual void h25(); virtual void h26(); virtual void h27(); virtual void h28(); virtual void h29(); virtual void h30(); virtual void h31(); virtual void h32(); virtual void h33(); virtual void h34(); virtual void h35(); virtual void h36(); virtual void h37();
    virtual void spawn(void *, V *, void *, void *); };
struct T { virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10(); virtual void t11(); virtual void t12(); virtual void get(V *, int, int, int, int);
    u8 pad4[392]; S396 *f396; };
void fn_8017BB84(E *, O *, V *);
void fn_80100E24(V *, void *, V *);
void fn_80101414(V *, V *, f32);
H *fn_80233550(void *, void *);
void fn_802273F0(T *t, void *name, void *a, void *b, u32 n, f32 ang) {
    S396 *s = t->f396;
    if (!s) return;
    V p;
    t->get(&p, 0, 0, 0, 0);
    O *o = s->f156;
    E *e = o->f56;
    while (e && e->f0) e = e->f20;
    V q;
    if (e && e->f0 == 0) {
        fn_8017BB84(e, o, &q);
    } else {
        if (o->f0 & 4) o->upd();
        q.x = o->pos.x;
        q.y = o->pos.y;
        q.z = o->pos.z;
    }
    V d;
    d.x = q.x - p.x;
    d.y = q.y - p.y;
    d.z = q.z - p.z;
    V ax;
    fn_80100E24(&ax, lbl_80357E90, &d);
    f32 step;
    f32 base;
    step = base = 0.0f;
    if (n > 1) {
        base = 0.017453292f * -(ang / 2.0f);
        step = 0.017453292f * (ang / (f32)(n - 1));
    }
    for (u32 i = 0; i < n; i++) {
        V r; r.x = d.x; r.y = d.y; r.z = d.z;
        fn_80101414(&r, &ax, __fmadds((f32)i, step, base));
        V w;
        w.x = p.x + r.x;
        w.y = p.y + r.y;
        w.z = p.z + r.z;
        H *h = fn_80233550(lbl_8035B374, name);
        if (h) h->spawn(t, &w, a, b);
    }
}
}
}

namespace N80227650 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

struct V_80227650 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void p10(); virtual void p11(); virtual void p12(); virtual void p13(); virtual void p14(); virtual void p15(); virtual void p16(); virtual void p17(); virtual void p18(); virtual void p19(); virtual void p20(); virtual void p21(); virtual void p22(); virtual void p23(); virtual void p24(); virtual void p25(); virtual void p26(); virtual void p27(); virtual void p28(); virtual void p29(); virtual void p30(); virtual void p31(); virtual void p32(); virtual void p33(); virtual void p34(); virtual void p35(); virtual void p36(); virtual void p37(); virtual void p38(); virtual void m(void *, void *, void *, void *, f32); };
extern void *lbl_8035B374;
V_80227650 *fn_80233550(void *);

void fn_80227650(u8 *p, void *x, void *a, void *b, void *c) {
    V_80227650 *g = fn_80233550(lbl_8035B374);
    if (g != NULL) {
        if (*(f32 **)(p + 0x1D0) != NULL) {
            g->m(p, c, a, b, **(f32 **)(p + 0x1D0));
        } else {
            g->m(p, c, a, b, 0.0f);
        }
    }
}

} /* extern "C" */
}
