// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

#pragma always_inline on
struct V3 { f32 x, y, z; };
struct Ent { u8 pad[0x30]; u8 b30; u8 pad31[3]; u8 b34; };
struct Lst { u32 n; Ent **p; };
struct Sub { u8 pad[0x10]; void *f10; u8 pad14[0xc]; u32 f20; };
struct Bse { u8 pad[0x30]; Sub *f30; u8 pad34[0x38]; Lst *f6c; u8 pad70[0x20]; u8 *f90; u8 pad94[4]; u32 f98; };
struct C801883E0 : Bse { C801883E0(); u8 padx[0xcc - 0x9c]; };
struct C8018E150 : Bse { C8018E150(); u8 padx[0xa8 - 0x9c]; };
struct C80197988 : Bse { C80197988(); u8 padx[0xe4 - 0x9c]; };
struct Nd { u32 f0; u16 type; };
struct ETab { u32 n; u32 *p; };
struct Gen { u8 pad[0x10]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void init(u32 h, s32 a, s32 b, s32 c, s32 d); virtual void v7(); virtual u32 create(); };
struct Fac { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual Gen *make(); };
struct Game { u8 pad[0x2c44]; Fac *f2c44; u8 pad2c48[4]; u32 f2c4c; };
struct Glob { u8 pad[0xc]; Game *fc; };
struct Mgr { u8 pad[0xc]; void *fc; };
struct FTab { void *f0; void *f4; void *f8; void (*fC)(void *, V3 *); };
struct Obj {
    u8 pad[0x9c]; u32 f9c; u8 padA0[0x2d0 - 0xa0];
    u32 f2d0; u32 f2d4; u8 pad2d8[0xc]; C8018E150 *f2e4; C801883E0 *f2e8; u8 pad2ec[4];
    C80197988 *f2f0[2]; C80197988 *f2f8[6]; u8 pad310[0x14]; ETab e[3]; u32 f33c; u32 f340; Gen *f344;
};
extern u8 **lbl_8035B684;
extern void *lbl_8035B320;
extern Mgr *lbl_8035B65C;
extern Glob *lbl_8035B460;
extern FTab lbl_803286D0;
extern const u32 lbl_8035E49C;
extern const f32 lbl_8035E4A8;
extern char lbl_8035E4E8[7];
extern char lbl_8035E4F0[8];
extern char lbl_80297160[];
extern char lbl_8029716C[];
void fn_800E8F6C(char *d, const char *fmt, ...);
void *fn_800F9398(void *o, char *n);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_80188144(C801883E0 *, u8 *, Nd *, s32);
void fn_8018DFAC(C8018E150 *, u8 *, Nd *);
void fn_8019777C(C80197988 *, u8 *, Nd *, Nd *);
void fn_80190C98(Bse *);
void fn_80190940(Bse *, u32);
void fn_8019B7E8(void *, Bse *);
void fn_8013EBAC(ETab *, u32, u32);
void fn_8012FE8C(u32, u32, Gen *, Ent *);

inline Lst *GetL(Bse *b) {
    Lst *l = b->f6c;
    if (l == 0) l = (Lst *)(b->f90 + 0x1c);
    return l;
}

inline void Fill(Obj *o, Bse *b, Lst *l) {
    u32 h = lbl_8035B460->fc->f2c4c;
    u32 i;
    fn_8013EBAC(&o->e[o->f340], h, l->n);
    for (i = 0; i < l->n; i++) {
        u32 x;
        Gen *g = o->f344;
        o->f33c++;
        x = g->create();
        fn_8012FE8C(x, h, o->f344, l->p[i]);
        o->e[o->f340].p[i] = x;
    }
    b->f6c = (Lst *)&o->e[o->f340];
    o->f340++;
}

inline void Hook(Bse *b, V3 *v) {
    Sub *s = b->f30;
    if (s != 0) {
        lbl_803286D0.fC(s->f10, v);
        s->f20 |= lbl_8035E49C;
        fn_80190C98(b);
    }
}

inline void Build(Obj *o) {
    u32 i;
    if (o->f2d0 != 3) {
        s32 a, c;
        a = c = 0;
        u32 h;
        Lst *l;
        if (o->f2e8 != 0) {
            l = GetL(o->f2e8);
            if (l != 0) { u32 j; for (j = 0; j < l->n; j++) { a += l->p[j]->b30; c += l->p[j]->b34; } }
        }
        if (o->f2e4 != 0) {
            l = GetL(o->f2e4);
            if (l != 0) { u32 j; for (j = 0; j < l->n; j++) { a += l->p[j]->b30; c += l->p[j]->b34; } }
        }
        for (i = 0; i < 2; i++) {
            if (o->f2f0[i] != 0) {
                l = o->f2f0[i]->f6c;
                if (l != 0) { u32 j; for (j = 0; j < l->n; j++) { a += l->p[j]->b30; c += l->p[j]->b34; } }
            }
        }
        h = lbl_8035B460->fc->f2c4c;
        o->f344 = lbl_8035B460->fc->f2c44->make();
        o->f344->init(h, c, a, 5, 0);
        if (o->f2e8 != 0) {
            Bse *b = o->f2e8;
            l = GetL(b);
            if (l != 0) Fill(o, b, l);
        }
        if (o->f2e4 != 0) {
            Bse *b = o->f2e4;
            l = GetL(b);
            if (l != 0) Fill(o, b, l);
        }
        for (i = 0; i < 2; i++) {
            Bse *b = o->f2f0[i];
            if (b != 0) {
                l = b->f6c;
                if (l != 0) Fill(o, b, l);
            }
        }
    }
}

#pragma push
#pragma opt_lifetimes off
void fn_8005E77C(Obj *o) {
    u8 *w;
    void *t;
    void *mgr;
    u32 i;
    char buf[8];
    V3 v;
    w = *lbl_8035B684 + 0x3040;
    fn_800E8F6C(buf, lbl_8035E4E8, o->f2d0, o->f2d4);
    t = fn_800F9398(w + 0x90, buf);
    if (t != 0) {
        f32 z = lbl_8035E4A8;
        v.x = z; v.y = z; v.z = z;
        switch (((Nd *)t)->type) {
        case 3:
            {
            Nd *n = (Nd *)t;
            n->f0 &= ~0x800;
            if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B320);
            o->f2e8 = new C801883E0;
            fn_800F7E98();
            if (o->f2e8 == 0) fn_800604C4(-4, 0, 0, 0);
            fn_80188144(o->f2e8, w, n, 0);
            Hook(o->f2e8, &v);
            fn_80190940(o->f2e8, o->f9c);
            fn_8019B7E8(lbl_8035B65C->fc, o->f2e8);
            }
            break;
        case 2:
            {
            Nd *n = (Nd *)t;
            n->f0 &= ~0x800;
            if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B320);
            o->f2e4 = new C8018E150;
            fn_800F7E98();
            if (o->f2e4 == 0) fn_800604C4(-4, 0, 0, 0);
            fn_8018DFAC(o->f2e4, w, n);
            Hook(o->f2e4, &v);
            fn_80190940(o->f2e4, o->f9c);
            fn_8019B7E8(lbl_8035B65C->fc, o->f2e4);
            }
            break;
        }
    }
    fn_800E8F6C(buf, lbl_8035E4F0, o->f2d0, o->f2d4);
    t = fn_800F9398(w + 0x90, buf);
    if (t != 0) {
        f32 z = lbl_8035E4A8;
        v.x = z; v.y = z; v.z = z;
        switch (((Nd *)t)->type) {
        case 3:
            ((Nd *)t)->f0 &= ~0x800;
            break;
        case 2:
            ((Nd *)t)->f0 &= ~0x800;
            break;
        }
    }
    mgr = lbl_8035B65C->fc;
    for (i = 0; i < 2; i++) {
        fn_800E8F6C(buf, lbl_80297160, o->f2d0, o->f2d4, i);
        t = fn_800F9398(w + 0x90, buf);
        if (t != 0) {
            Nd *n = (Nd *)t;
            if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B320);
            o->f2f0[i] = new C80197988;
            fn_800F7E98();
            if (o->f2f0[i] == 0) fn_800604C4(-4, 0, 0, 0);
            n->f0 &= ~0x800;
            fn_8019777C(o->f2f0[i], w, n, n);
            Hook(o->f2f0[i], &v);
            fn_80190940(o->f2f0[i], o->f9c);
            fn_8019B7E8(mgr, o->f2f0[i]);
        }
    }
    for (i = 0; i < 6; i++) {
        fn_800E8F6C(buf, lbl_8029716C, o->f2d0, o->f2d4, i);
        t = fn_800F9398(w + 0x90, buf);
        if (t != 0) {
            Nd *n = (Nd *)t;
            if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B320);
            o->f2f8[i] = new C80197988;
            fn_800F7E98();
            if (o->f2f8[i] == 0) fn_800604C4(-4, 0, 0, 0);
            n->f0 &= ~0x800;
            fn_8019777C(o->f2f8[i], w, n, n);
            Hook(o->f2f8[i], &v);
            o->f2f8[i]->f98 &= ~1;
            fn_8019B7E8(mgr, o->f2f8[i]);
        }
    }
    Build(o);
}
#pragma pop

} /* extern "C" */
