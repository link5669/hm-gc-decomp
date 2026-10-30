// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct M { u8 b[16]; };
struct V { f32 x, y, z; };
struct L { u8 pad[12]; u32 n; };
struct S224 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12();
    virtual void get(M *, int, int, int, int); virtual void put(V *, int, int, int, int); };
struct S192 { u8 pad[4]; void *f4; };
struct T { u8 pad[192]; S192 *f192; u8 pad196[28]; S224 *f224; u8 pad228[80]; f32 *f308; u8 pad312[40]; L *f352; L *f356; u8 pad360[16]; V f376; };
extern f32 lbl_803596E0[];
extern char lbl_80361F10[8];
void *fn_80245F8C(L *, int);
f32 fn_80101590(M *, void *);
void fn_80257A4C(void *, V *);
void fn_80241DD0(T *, const char *, int, int, int, int);
void fn_800A77D0(T *t, int k) {
    M m;
    t->f224->get(&m, 0, 0, 0, 0);
    V *far = 0;
    V *near = 0;
    f32 dfar = lbl_803596E0[0];
    f32 dnear = dfar;
    L *l = t->f352;
    if (l && l->n) {
        for (u32 i = 0; i < t->f352->n; i++) {
            V *o = (V *)fn_80245F8C(t->f352, i);
            f32 d = fn_80101590(&m, o);
            if (d <= dnear && d <= *t->f308) {
                near = o;
                dnear = d;
            }
            if (d <= dfar) {
                far = o;
                dfar = d;
            }
        }
        if (near) {
            t->f376 = *near;
            fn_80257A4C(t->f192->f4, &t->f376);
            if (k) t->f224->put(&t->f376, 0, 0, 0, 0);
        } else if (k && far) {
            t->f376 = *far;
            fn_80257A4C(t->f192->f4, &t->f376);
            t->f224->put(&t->f376, 0, 0, 0, 0);
        } else if (t->f356 && t->f356->n) {
            fn_80241DD0(t, lbl_80361F10, 0, 0, 0, 0);
        }
    } else if (t->f356 && t->f356->n) {
        fn_80241DD0(t, lbl_80361F10, 0, 0, 0, 0);
    }
}

} /* extern "C" */
