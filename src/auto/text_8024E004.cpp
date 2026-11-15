// Code of main that had no source file yet: decomp.wtf gave it this one.
#include "common.h"
extern "C" {
#pragma opt_loop_invariants off
#include "common.h"

struct V_8024E3DC { u8 pad[0x10]; virtual void p0(); virtual void p1(); virtual void p2(); virtual s32 m(); };
struct C8023C7CC { C8023C7CC(); ~C8023C7CC(); u8 *own; u8 *blk; u8 *cur; u32 idx; s32 flag; u8 x[8]; };
class Ev { public: virtual void e0(); virtual void e1(); virtual void e2(); virtual void e3(); virtual void e4(); virtual void e5();
    virtual void e6(); virtual void e7(); virtual void e8(); virtual void e9(); virtual void set(char *, char *); virtual void stop(int); };
struct Nd { u8 p[28]; u32 f28; u8 p32[8]; s32 f40; u32 f44; u8 p48[60]; Nd **f108; s32 f112; };
struct Ent { char name[8]; char a[8]; char b[8]; u32 f24; u8 p[12]; };
struct Pb { u8 p[636]; u32 n; Ent e[5]; };
extern "C" {
void fn_8023C720(void *, void *);
void fn_8023C528(void *, char *);
void fn_8023C3F4(void *);
u8 *fn_8023A490(void *, u32);
extern char lbl_80366440[8];
extern char lbl_80366448[8];
void fn_800F6E88(void *, void *);
s32 fn_800F6F00(void *, void *);
s32 fn_800F6CD0(void *, void *);
void fn_802502BC(u8 *);
void fn_80250EBC(u8 *);
Nd *fn_8024E3DC(Pb *, char *, u32 *);
s32 fn_8024B710(void);
s32 fn_8024D814(Pb *, char *, u32 *);
}
static inline u8 *Get(C8023C7CC *it) {
    return it->cur != 0 ? fn_8023A490(it->cur, it->idx) : 0;
}
static inline u8 *Find(Pb *p, char *name, char *lbl) {
    char buf[8];
    C8023C7CC it;
    u32 i;
    u8 *o;
    for (i = 0; i < 2; i++) {
        if (i == 0 && ((V_8024E3DC *)p)->m() != 0) fn_8023C720(&it, p);
        else fn_8023C720(&it, (u8 *)p + 76);
        fn_8023C528(&it, lbl);
        while (it.cur != 0) {
            o = Get(&it);
            fn_800F6E88(buf, o + 20);
            if (fn_800F6F00(name, buf) == 0) return o;
            fn_8023C3F4(&it);
        }
    }
    return 0;
}
static inline Nd *Sub(Nd *x) { return x->f28 == 2 ? x->f108[x->f44] : 0; }
static inline Nd *Res(Nd *x) {
    return x->f40 == 0 ? x : Sub(x);
}
extern "C" void fn_8024E004(Pb *p, char *name, s32 mode, char *a, char *b) {
    C8023C7CC top;
    u32 u;
    char buf[8];
    switch (mode) {
    case 1:
        fn_802502BC(Find(p, name, lbl_80366440));
        break;
    case 2:
        fn_80250EBC(Find(p, name, lbl_80366448));
        break;
    case 3: {
        Ev *e = (Ev *)fn_8024E3DC(p, name, &u);
        if (fn_8024B710()) return;
        if (!fn_8024D814(p, buf, &u)) {
            e->set(a, b);
            break;
        }
        if (fn_800F6CD0(name, buf)) return;
        {
            Nd *y = Res(fn_8024E3DC(p, buf, &u));
            if (y->f112) ((Ev *)y)->stop(0);
        }
        {
            u8 *q = (u8 *)p;
            u32 i;
            s32 found = 0;
            for (i = 0; i < p->n; q += 40, i++)
                if (fn_800F6CD0(name, ((Pb *)q)->e[0].name)) found = 1;
            if (!found && p->n < 5) {
                fn_800F6E88(p->e[p->n].name, name);
                fn_800F6E88(p->e[p->n].b, b);
                fn_800F6E88(p->e[p->n].a, a);
                p->e[p->n].f24 = 3;
                p->n++;
            }
        }
        break;
    }
    }
}
}
