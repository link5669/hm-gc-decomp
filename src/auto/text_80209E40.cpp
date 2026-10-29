// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" { unsigned long strlen(const char *); char *strcpy(char *, const char *); }
extern void *lbl_8035B1D4;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
extern char lbl_802A6938[], lbl_802A6978[];
extern u32 lbl_803657D4;
struct T;
struct H16 { u8 pad[16]; void *f16; };
struct S { H16 *f0; virtual void init(void *, T *); virtual void x1(); virtual void set(void *); u8 pad8[68]; };
struct P { u8 b[268]; };
struct I { u8 pad[52]; u32 f52; u32 f56; };
struct T { void *f0; u32 f4; u32 f8; char *f12; virtual void v0(); virtual void v1(); virtual void v2(); virtual void close(); int f20; u8 pad24[4]; S s28; S s104; };
void fn_80210CFC(P *, const char *);
int fn_800BD044(P *);
int fn_800BD338(int, I *);
int fn_800BD474(I *);
void *fn_8021141C(T *);
void fn_80060568(const char *, int, int, int);
int fn_80209E40(T *t, const char *path, const char *name, u32 flags) {
    t->close();
    t->f8 = flags;
    if (flags & 45) return 9;
    P p;
    I inf;
    fn_80210CFC(&p, path);
    t->f20 = fn_800BD044(&p);
    if (t->f20 >= 0 && fn_800BD338(t->f20, &inf)) {
        t->f4 = inf.f52;
        if (fn_800BD474(&inf)) {
            void *b = fn_8021141C(t);
            if (!b) fn_80060568(lbl_802A6938, 0, 0, 0);
            t->s28.init(b, t);
            t->s28.set(0);
            if (t->f8 & 0x40) {
                b = fn_8021141C(t);
                if (!b) fn_80060568(lbl_802A6978, 0, 0, 0);
                t->s104.init(b, t);
                t->s104.set(t->s28.f0->f16);
            }
            t->f8 |= lbl_803657D4;
            t->f0 = 0;
            u32 len = strlen(name);
            if (lbl_8035B1D4 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B1D4);
            t->f12 = new char[len + 1];
            fn_800F7E98();
            if (t->f12 == 0) fn_800604C4(-4, 0, 0, 0);
            strcpy(t->f12, name);
            return 0;
        }
    }
    return 3;
}

} /* extern "C" */
