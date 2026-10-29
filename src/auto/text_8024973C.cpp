// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern char lbl_803662E4[8], lbl_803662EC[8];
struct B { u32 a, b; };
struct Rg { u32 f0; u32 f4; };
struct X;
struct T { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual int can(X *); virtual void go(X *);
    u8 pad4[16]; u8 f20[28]; X **f48; u8 pad52[44]; int f96; int f100; int f104; const char **f108; };
void fn_800F70A8(void *);
void fn_800F6FBC(const char *, B *);
int fn_800F6F00(void *, B *);
Rg *fn_800F8274(void *, const char *);
static inline void tryS(T *t, const char *s) {
    Rg *r = fn_800F8274(t->f20, s);
    if (r) {
        X **p = &t->f48[r->f0];
        for (u32 n = r->f4; n; n--, p++) {
            if (t->can(*p)) {
                t->go(*p);
                break;
            }
        }
    }
}
void fn_8024973C(T *t, void *nm) {
    X **p;
    u32 n;
    int i;
    for (i = 0; i < t->f104; i++) {
        fn_800F70A8(nm);
        B b;
        fn_800F6FBC(t->f108[i], &b);
        if (fn_800F6F00(nm, &b) == 0) {
            if (t->f96 != -1) tryS(t, lbl_803662E4);
            t->f100 = -1;
            t->f96 = i;
            {
                Rg *r = fn_800F8274(t->f20, lbl_803662EC);
                if (r) {
                    p = &t->f48[r->f0];
                    for (n = r->f4; n; n--, p++) {
                        if (t->can(*p)) {
                            t->go(*p);
                            break;
                        }
                    }
                }
            }
            return;
        }
    }
    t->f100 = -1;
    t->f96 = 0;
    tryS(t, lbl_803662EC);
}

} /* extern "C" */
