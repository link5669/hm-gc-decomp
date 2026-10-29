// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct E40 { u8 pad[20]; void *f20; u8 pad24[16]; };
struct E52 { u8 pad[20]; void *f20; u8 pad24[28]; };
struct Mdl { u8 pad[28]; u32 n28; u32 n32; E40 *f36; E52 *f40; void *f44; };
struct X { u8 pad[20]; void *f20; };
struct R68 { u8 pad[6448]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void a33(); virtual void a34(); virtual void a35(); virtual void a36(); virtual void a37(); virtual void a38(); virtual void a39(); virtual void a40(); virtual void a41(); virtual void a42(); virtual void a43(); virtual void a44(); virtual void a45(); virtual void a46(); virtual void a47(); virtual void a48(); virtual void a49(); virtual void a50(); virtual void a51(); virtual void a52(); virtual void a53(); virtual void a54(); virtual void a55(); virtual void a56(); virtual void a57(); virtual void a58(); virtual void a59(); virtual void a60(); virtual void a61(); virtual void a62(); virtual void a63(); virtual void a64(); virtual void a65(); virtual void a66(); virtual void a67(); virtual void *mat(); };
struct R13 { u8 pad[48]; virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual R68 *rr(); };
struct S184;
struct C0 { R13 *f0; u8 pad4[180]; S184 *f184; };
struct S184 { virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void *get(int); };
struct C { C0 *f0; };
struct O { u32 f0; u8 pad4[100]; virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual X *def(); void *f108; u8 pad112[32]; void *f144; u8 f148[20]; Mdl *f168; };
void fn_8017A028(void *);
void fn_801044C4(X *, void *, void *);
void fn_80138DD8(C0 *, u32, void *);
void fn_801043E0(void *, void *, void *);
void fn_80138D8C(C0 *);
void fn_8019E7C8(C *, void *, void *, void *);
void fn_801874E8(O *o, C *c, X *x) {
    if (!(o->f0 & 0x4000)) return;
    if (o->f0 & 0x80000) fn_8017A028(&o->f168);
    if (!x) x = o->def();
    Mdl *m = o->f168;
    if (x) {
        fn_801044C4(x, c->f0->f184->get(0), c->f0->f0->rr()->mat());
        fn_80138DD8(c->f0, 0, x->f20);
        if (m && m->f44) fn_801043E0(m->f44, x->f20, c->f0->f0->rr()->mat());
    } else {
        fn_80138D8C(c->f0);
        if (m && m->f44) {
            fn_801043E0(m->f44, c->f0->f184->get(0), c->f0->f0->rr()->mat());
        }
    }
    u32 k = 1;
    u32 i;
    for (i = 0; i < m->n28; i++) fn_80138DD8(c->f0, k++, m->f36[i].f20);
    for (i = 0; i < m->n32; i++) fn_80138DD8(c->f0, k++, m->f40[i].f20);
    fn_8019E7C8(c, o->f144, o->f108, o->f148);
}

} /* extern "C" */
