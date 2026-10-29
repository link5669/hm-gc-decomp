// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct C8023C7CC {
    u8 pad[8];
    void *a;
    void *b;
    u8 pad2[12];
    C8023C7CC();
    ~C8023C7CC();
};
void fn_8023C720(C8023C7CC *, void *);
void fn_8023C528(C8023C7CC *, s32);
u8 *fn_8023A490(void *, void *);
void fn_8023C3F4(C8023C7CC *);
void fn_800F6E88(void *, void *);
s32 fn_800F6CD0(void *, void *);
extern char lbl_80365CC8[8], lbl_80365CD0[8];
extern char lbl_802A8510[];
struct X { virtual void a0(); virtual void a1(); virtual void reset(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void stop(); };
struct Y { u8 pad[12]; void *f12; void *f16; };
struct Z8 { u8 pad[8]; virtual void z0(); virtual void z1(); virtual void z2(); virtual void z3(); virtual void z4(); virtual void *get(int); };
struct R { Z8 *f0; };
struct T { u8 pad[76]; Y *f76; u8 pad80[12]; void *f92; };
R *fn_8010FEDC(void *, void *, const char *, int);
static inline u8 *find(void *a, char *name) {
    C8023C7CC it;
    char buf[8];
    fn_8023C720(&it, a);
    fn_8023C528(&it, 0);
    while (it.a != 0) {
        u8 *o = it.a != 0 ? fn_8023A490(it.a, it.b) : (u8 *)0;
        fn_800F6E88(buf, o + 140);
        if (fn_800F6CD0(name, buf) != 0) return o;
        fn_8023C3F4(&it);
    }
    return 0;
}
void fn_802286C4(T *t) {
    C8023C7CC it;
    fn_8023C720(&it, t);
    fn_8023C528(&it, 0);
    while (it.a != 0) {
        X *x = (X *)(it.a != 0 ? fn_8023A490(it.a, it.b) : (u8 *)0);
        x->stop();
        x->reset();
        fn_8023C3F4(&it);
    }
    t->f76 = (Y *)find(t, lbl_80365CC8);
    t->f92 = 0;
    Y *y = (Y *)find(t, lbl_80365CD0);
    if (y && y->f12) {
        R *r = fn_8010FEDC(y->f12, y->f16, lbl_802A8510, 0);
        if (r) t->f92 = r->f0->get(0);
    }
}

} /* extern "C" */
