// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct O;
struct H { virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4(); virtual void h5(); virtual void h6(); virtual void h7(); virtual void h8(); virtual void h9();
 virtual void h10(); virtual void h11(); virtual void h12(); virtual void h13(); virtual void h14(); virtual void h15(); virtual void h16(); virtual void h17(); virtual void h18(); virtual void h19();
 virtual void h20(); virtual void h21(); virtual void h22(); virtual void h23(); virtual void h24(); virtual void h25(); virtual void h26(); virtual void h27(); virtual void h28(); virtual void h29();
 virtual void h30(); virtual void h31(); virtual void h32(); virtual void h33(); virtual void h34(); virtual void h35(); virtual void h36(); virtual void h37(); virtual void h38(); virtual void h39();
 virtual void h40(); virtual void h41(); virtual void h42(); virtual void h43(); virtual void h44(); virtual void h45(); virtual void h46(); virtual void h47(); virtual void h48(); virtual void h49(); virtual void ev(O *, int); };
struct N { H *f0; u8 pad4[4]; N *f8; };
struct O { u8 pad[136]; N *f136; u8 pad140[184]; u32 f324; u32 f328; };
struct V2 { f32 x, y; };
struct T { u8 pad[4]; void *f4; u8 pad8[12]; O *f20; void *f24; u8 pad28[4]; void *f32; void *f36; void *f40; u8 pad44[4]; V2 f48; };
extern f32 lbl_80364FD0;
f32 fn_80100D18(V2 *, V2 *);
int fn_801DB1C0(void *, f32, f32);
int fn_801DB174(void *, void *, void *, f32, f32);
void fn_801C197C(T *, void *, void *, f32, f32);
static inline void notify(O *o, int e) {
    N *n;
    for (n = o->f136; n; n = n->f8) n->f0->ev(o, e);
    o->f328 = o->f324;
    o->f324 = (o->f324 & 0xFFFF0000) | e;
}
int fn_801C1774(T *t, void *x, f32 a, f32 b) {
    O *o;
    N *n;
    if (t->f24 && !t->f36) {
        V2 p;
        p.x = a;
        p.y = b;
        if (fn_80100D18(&p, &t->f48) > lbl_80364FD0 && fn_801DB1C0(t->f24, a, b)) {
            t->f36 = t->f24;
            notify(t->f20, 1024);
        }
    }
    if (t->f36 && t->f32) {
        if (fn_801DB174(t->f32, t->f36, x, a, b)) {
            t->f40 = t->f32;
            o = t->f20;
            for (n = o->f136; n; n = n->f8) n->f0->ev(o, 1024);
            o->f328 = o->f324;
            o->f324 = (o->f324 & 0xFFFF0000) | 1024;

        } else {
            t->f40 = 0;
            o = t->f20;
            for (n = o->f136; n; n = n->f8) n->f0->ev(o, 2048);
            o->f328 = o->f324;
            o->f324 = (o->f324 & 0xFFFF0000) | 2048;

        }
    }
    fn_801C197C(t, x, t->f4, a, b);
    return 0;
}

} /* extern "C" */
