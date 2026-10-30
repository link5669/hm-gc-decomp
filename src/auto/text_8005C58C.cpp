// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" char *strcat(char *, const char *);
struct V { f32 x, y, z; };
struct FT { u8 pad[12]; void (*f12)(void *, V *); u8 pad16[32]; void (*f48)(void *, void *, void *); };
extern FT lbl_803286D0;
extern u8 lbl_80357E84[];
extern f32 lbl_8035E438;
extern u32 lbl_8035E468, lbl_8035E46C, lbl_8035E470;
extern char lbl_8035E474[8], lbl_8035E478[8];
struct G334 { u8 pad[8]; void *f8; };
extern G334 *lbl_8035B334;
struct P { u8 pad[16]; void *f16; u8 pad20[12]; u32 f32; };
struct O { u32 f0; u8 pad4[44]; P *f48; u8 pad52[56]; int f108; u8 pad112[40]; u32 f152; f32 f156; u8 pad160[12]; f32 f172; };
struct T { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void pos(V *, int, int, int, int); virtual void b0(); virtual void b1(); virtual void b2(); virtual void b3(); virtual void b4(); virtual void b5(); virtual void b6(); virtual void b7(); virtual void b8(); virtual void b9(); virtual void b10(); virtual void b11(); virtual void b12(); virtual void b13(); virtual void b14(); virtual void b15(); virtual void b16(); virtual void b17(); virtual void b18(); virtual void say(const char *, void *, int, int, int);
    u8 pad4[716]; u8 f720[8]; O *f728[10]; int f768; u8 pad772[4]; O *f776; u8 pad780[36]; int f816; O *f820[8]; };
void fn_801907D8(O *);
void fn_80231408(T *, int, void *, void *);
void fn_800F6E40(char *, void *);
O *fn_8022ECB4(void *, char *);
void fn_80190C98(O *);
void fn_80196688(O *);
void fn_8005C58C(T *t, int a, void *b, void *c) {
    O *ob;
    P *q;
    int i;
    for (i = 0; i < t->f816; i++) {
        t->f820[i]->f152 &= ~1;
        t->f820[i]->f0 &= ~0x800;
        fn_801907D8(t->f820[i]);
    }
    fn_80231408(t, a, b, c);
    for (i = 0; i < t->f768; i++) {
        if (t->f728[i]) {
            t->f728[i]->f108 = 0;
            t->f728[i]->f0 &= ~0x800;
        }
    }
    if (t->f776) t->f776->f0 &= ~0x800;
    if (a) return;
    char nm[20];
    a = (int)lbl_8035B334->f8;
    fn_800F6E40(nm, t->f720);
    strcat(nm, lbl_8035E474);
    ob = fn_8022ECB4((void *)a, nm);
    if (ob) {
        V p;
        t->pos(&p, 0, 0, 0, 0);
        q = ob->f48;
        if (q) {
            lbl_803286D0.f12(q->f16, &p);
            q->f32 |= lbl_8035E468;
            fn_80190C98(ob);
        }
        if (b) {
            q = ob->f48;
            if (q) {
                lbl_803286D0.f48(q->f16, b, lbl_80357E84);
                q->f32 |= lbl_8035E468;
                fn_80190C98(ob);
            }
        }
        ob->f156 = lbl_8035E438;
        ob->f152 &= ~6;
        ob->f172 = lbl_8035E438;
        fn_80196688(ob);
        ob->f0 |= lbl_8035E46C;
        ob->f152 |= lbl_8035E470;
    }
    t->say(lbl_8035E478, c, 0, 0, 0);
}

} /* extern "C" */
