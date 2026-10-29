// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct M { u8 b[16]; };
struct L { u8 pad[12]; u32 n; };
struct S224 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12();
    virtual void get(M *, int, int, int, int); virtual void put(void *, int, int, int, int); u8 pad4[272]; int f276; };
struct T { u8 pad[224]; S224 *f224; u8 pad228[80]; f32 *f308; u8 pad312[44]; L *f356; int f360; u8 pad364[4]; int f368; };
extern f32 lbl_803596E0[];
extern "C" int rand(void);
void *fn_80245F8C(L *, int);
f32 fn_80101590(M *, void *);
void fn_800A7A1C(T *t, int k) {
    u32 n = 0;
    if (t->f356) n = t->f356->n;
    if (n == 0) return;
    M m;
    int best;
    f32 bd;

    u32 cnt;
    int i;
    u32 r;
    int old;

    best = t->f360;
    bd = lbl_803596E0[0];
    t->f224->get(&m, 0, 0, 0, 0);
    cnt = 0;
    for (i = 0; i < n; i++) {
        void *o = fn_80245F8C(t->f356, i);
        f32 d = fn_80101590(&m, o);
        if (d <= *t->f308 && i != t->f360) cnt++;
        if (d < bd) { best = i; bd = d; }
    }
    if (cnt == 0) {
        if (k || (t->f368 && t->f224->f276)) t->f360 = best;
    } else {
        u32 q = 0;
        if (cnt) q = rand() % cnt;
        old = t->f360;
        t->f360 = -1;
        r = q + 1;
        while (r >= 1 && t->f360 + 1 < (int)t->f356->n) {
            t->f360++;
            void *o = fn_80245F8C(t->f356, t->f360);
            f32 d = fn_80101590(&m, o);
            if (d <= *t->f308 && t->f360 != old) r--;
        }
    }
    if (k) {
        void *o = fn_80245F8C(t->f356, t->f360);
        t->f224->put(o, 0, 0, 0, 0);
    }
}

} /* extern "C" */
