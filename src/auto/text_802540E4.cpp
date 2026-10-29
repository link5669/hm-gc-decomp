// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct FT { u8 pad0[4]; void (*f4)(void *); u8 pad8[36]; void (*f44)(void *, void *, void *); u8 pad48[140]; void (*f188)(void *, void *); u8 pad192[96]; void (*f288)(void *, int, int, f32); u8 pad292[64]; void (*f356)(void *, void *); };
extern FT lbl_803286D0;
struct R { u8 pad[6448]; virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void v15(); virtual void v16(); virtual void b17(); virtual void b18(); virtual void b19(); virtual void b20(); virtual void b21(); virtual void b22(); virtual void b23(); virtual void b24(); virtual void b25(); virtual void b26(); virtual void b27(); virtual void b28(); virtual void b29(); virtual void b30(); virtual void b31(); virtual void b32(); virtual void b33(); virtual void b34(); virtual void b35(); virtual void b36(); virtual void b37(); virtual void b38(); virtual void b39(); virtual void b40(); virtual void b41(); virtual void b42(); virtual void b43(); virtual void b44(); virtual void b45(); virtual void b46(); virtual void b47(); virtual void b48(); virtual void b49(); virtual void b50(); virtual void b51(); virtual void b52(); virtual void b53(); virtual void b54(); virtual void b55(); virtual void b56(); virtual void b57(); virtual void b58(); virtual void b59(); virtual void b60(); virtual void b61(); virtual void b62(); virtual void b63(); virtual void b64(); virtual void b65(); virtual void b66(); virtual void *v67(); virtual void v68(); virtual void v69(int, void *); };
struct Q { u8 pad[28]; R *f28; };
struct B { u8 pad[20]; virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11(); virtual void c12(); virtual void c13(); virtual void c14(); virtual void c15(); virtual void c16(); virtual void go(R *, void *, int, int); };
struct T { u8 pad[4]; Q *f4; u8 pad8[648]; void *f656; void *f660; void *f664; };
void fn_802540E4(T *t, B *b, void *c, void *d, void *e, f32 *f, void *g) {
    lbl_803286D0.f4(t->f656);
    lbl_803286D0.f4(t->f660);
    lbl_803286D0.f4(t->f664);
    if (f) {
        lbl_803286D0.f288(t->f660, 0, 0, f[0]);
        lbl_803286D0.f288(t->f660, 1, 1, f[1]);
        lbl_803286D0.f288(t->f660, 2, 2, f[2]);
    }
    lbl_803286D0.f356(t->f656, t->f660);
    if (d && e) lbl_803286D0.f44(t->f664, d, e);
    lbl_803286D0.f356(t->f656, t->f664);
    if (c) lbl_803286D0.f188(t->f656, c);
    lbl_803286D0.f356(t->f656, t->f4->f28->v67());
    t->f4->f28->v69(0, t->f656);
    t->f4->f28->v16();
    b->go(t->f4->f28, g, 0, 0);
    t->f4->f28->v15();
}

} /* extern "C" */
