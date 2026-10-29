// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
extern f32 lbl_80366158, lbl_8036613C;
extern char lbl_802A8DE0[], lbl_802A8DEC[];
extern char lbl_8036615C[8], lbl_80366164[8], lbl_8036616C[8];
struct A { virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4(); virtual void q5(); virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9(); virtual void q10(); virtual void q11(); virtual void q12(); virtual void probe(int, V *, int, int, int); u8 pad[420]; f32 f424; f32 f428; u8 pad432[8]; int *f440; };
struct B { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void probe(int, V *, int, int, int); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void say(const char *, A *, int, int, int); u8 pad4[276]; V n; u8 pad292[188]; f32 *f480; };
struct T { u8 pad[184]; int f184; u8 pad188[36]; A *f224; B *f228; u32 f232; u32 f236; u32 f240; };
void fn_80249A18(T *, const char *);
static inline void go(T *t, B *b, const char *s) {
    if (t->f184) {
        t->f228 = b;
        t->f232 = 0;
        t->f236 = 0;
        t->f240 = 0;
        fn_80249A18(t, s);
    }
}
void fn_80240384(T *t) {
    A *a = t->f224;
    int n = a->f440 ? *a->f440 : 0;
    if (n < 0) return;
    f32 d = t->f228->f480 ? *t->f228->f480 : lbl_80366158;
    if (d <= lbl_8036613C) return;
    a->f428 = a->f428 - d;
    if (a->f428 > a->f424) a->f428 = a->f424;
    t->f228->say(lbl_802A8DE0, t->f224, 0, 0, 0);
    if (t->f224->f428 <= lbl_8036613C) {
        go(t, t->f228, lbl_8036615C);
        return;
    }
    V v;
    f32 nx = t->f228->n.x, ny = t->f228->n.y, nz = t->f228->n.z;
    t->f224->probe(0, &v, 0, 0, 0);
    if (v.x * nx + v.y * ny + v.z * nz <= lbl_8036613C) go(t, t->f228, lbl_802A8DEC);
    else go(t, t->f228, lbl_80366164);
    go(t, t->f228, lbl_8036616C);
}

} /* extern "C" */
