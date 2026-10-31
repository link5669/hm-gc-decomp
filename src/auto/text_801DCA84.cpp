// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct R;
struct A { u8 pad[40]; void *f40; };
struct T;
struct Obj { virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void v50(struct T *, u32); };
struct Node { Obj *obj; u32 f4; Node *next; };
struct S12 { u8 pad[12]; void *f12; };
struct T {
    u8 pad[120];
    u32 f120;
    u8 pad2[4];
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7(); virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18(); virtual void d19(); virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23(); virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27(); virtual void d28(); virtual void d29(); virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33(); virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37(); virtual void d38(); virtual void d39(); virtual void d40(); virtual void d41(); virtual void d42(); virtual void d43(); virtual void d44(); virtual void d45(); virtual void d46(); virtual void d47(); virtual void d48(); virtual void d49(); virtual void d50(); virtual void d51(); virtual void d52(); virtual void d53(); virtual void d54(); virtual void d55(); virtual void d56(); virtual void d57(); virtual void d58(); virtual void v59(int, int); virtual void d60(); virtual void d61(); virtual void d62(); virtual void d63(); virtual void d64(); virtual void d65(); virtual void d66(); virtual void d67(); virtual void d68(); virtual void d69(); virtual void d70(); virtual void d71(); virtual void v72(int);
    u32 f132;
    Node *f136;
    u8 pad3[8];
    u8 f148[8];
    u8 f156[12];
    u8 f168[8];
    u8 f176[12];
    u8 f188[8];
    u8 f196[12];
    u8 f208[8];
    u8 f216[12];
    u8 f228[8];
    u8 f236[12];
    u8 f248[8];
    u8 f256[12];
    u8 f268[8];
    u8 f276[8];
    u8 f284[8];
    u8 f292[8];
    u8 f300[16];
    u8 f316[8];
    u32 f324;
    u32 f328;
    u8 pad4[20];
    S12 *f352;
};
void fn_800F6E88(void *, void *);
void fn_800FB064(R *, void *);
void fn_801C068C(T *, A *, void *, void *);
void fn_801C30E0(void *, T *);
void fn_801BDDFC(T *, s32, A *, R *);
static inline void bc(T *t, u32 m, Node *n) {
    for (n = t->f136; n; n = n->next) n->obj->v50(t, m);
    t->f328 = t->f324;
    t->f324 = (t->f324 & 0xFFFF0000) | m;
}
void fn_801DCA84(T *t, s32 tok, A *a, R *r) {
    u8 nm[8];
    u8 buf[8];
    if (t->f352->f12) fn_800F6E88(buf, t->f352->f12);
    switch (tok) {
    case 71:
        fn_800FB064(r, t->f292);
        fn_800FB064(r, t->f300);
        fn_801C068C(t, a, t->f284, t->f292);
        break;
    case 229: t->f120 = 1; break;
    case 72: fn_801C30E0(a->f40, t); break;
    case 63: fn_800FB064(r, t->f148); fn_800FB064(r, t->f156); break;
    case 64: fn_800FB064(r, t->f168); fn_800FB064(r, t->f176); break;
    case 65: fn_800FB064(r, t->f188); fn_800FB064(r, t->f196); break;
    case 66: fn_800FB064(r, t->f208); fn_800FB064(r, t->f216); break;
    case 68: fn_800FB064(r, t->f248); fn_800FB064(r, t->f256); break;
    case 69: fn_800FB064(r, t->f268); fn_800FB064(r, t->f276); break;
    case 70: fn_800FB064(r, t->f228); fn_800FB064(r, t->f236); break;
    case 110:
        fn_800FB064(r, nm);
        fn_801C068C(t, a, t->f316, nm);
        break;
    case 187: bc(t, 1, (Node *)r); break;
    case 188: bc(t, 2, (Node *)r); break;
    case 189: t->v72(0); bc(t, 4, (Node *)r); break;
    case 190: t->v72(0); bc(t, 8, (Node *)r); break;
    case 191: t->v59(0, 0); bc(t, 16, (Node *)r); break;
    case 192: t->v59(0, 0); t->v72(0); bc(t, 32, (Node *)r); break;
    case 193: t->v59(0, 0); bc(t, 64, (Node *)r); break;
    case 194: t->v59(0, 0); t->v72(0); bc(t, 128, (Node *)r); break;
    case 195: bc(t, 256, (Node *)r); break;
    case 196: bc(t, 512, (Node *)r); break;
    case 197: bc(t, 1024, (Node *)r); break;
    case 198: bc(t, 2048, (Node *)r); break;
    case 199: bc(t, 4096, (Node *)r); break;
    case 200: bc(t, 8192, (Node *)r); break;
    case 201: bc(t, 1, (Node *)r); break;
    case 202: bc(t, 2, (Node *)r); break;
    case 203: bc(t, 4, (Node *)r); break;
    case 204: bc(t, 8, (Node *)r); break;
    case 205: bc(t, 16, (Node *)r); break;
    case 206: bc(t, 32, (Node *)r); break;
    case 207: bc(t, 64, (Node *)r); break;
    case 208: bc(t, 128, (Node *)r); break;
    case 209: bc(t, 256, (Node *)r); break;
    case 210: bc(t, 512, (Node *)r); break;
    case 67:
    default:
        fn_801BDDFC(t, tok, a, r);
        break;
    }
}

} /* extern "C" */
