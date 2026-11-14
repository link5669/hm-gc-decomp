#include "common.h"

extern "C" {

}
struct Lod { u8 pad[32]; virtual void v0(); virtual void v1(); virtual u32 v2(); u8 pad2[40]; s32 f76; };
struct Tex { u8 pad[16]; u32 w; u32 h; u8 pad2[4]; u16 f28; u8 pad3[1310];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); u8 pad4[4]; u32 f1348; };
struct Str { u8 b[8]; u8 f8; u8 pad[7]; };
struct Loc { u8 b[20]; };
struct S { u8 pad[8]; u32 f8; u16 f12; u8 pad2; u8 f15; u8 f16; u8 pad3[39]; u32 f56; Lod *f60; };
extern "C" {
extern Tex lbl_8032E7B4;
extern char lbl_80364594[4];
extern u16 lbl_80364590;
void fn_80148310(Loc *);
Lod *fn_80171438(Tex *, u8);
void fn_800F6E40(Str *, void *);
void fn_801488B4(Tex *, Str *);
void fn_80134848(u32);
Tex *fn_801348E8(void);
void fn_801482DC(Loc *, u16 *);
void fn_8015569C(S *, void *, u32 *, u32 *, Loc *, u8, u32 *);
void fn_80155124(Lod *, void *, u32, u32, u32, void *, Tex *, u32, Lod *);
void fn_801551F8(Lod *, u32, u32, u32, Loc *, u32, Lod *);
void fn_800E8F6C(char *, const char *, ...);
char *strcat(char *, const char *);
void fn_80155AE4(S *a, void *b, Tex *tex, void *d) {
    Loc l;
    u32 buf[9];
    u32 w, h;
    u8 *sp;
    s32 i;
    fn_80148310(&l);
    i = (s32)b;
    a->f60 = fn_80171438(tex, a->f16);
    if ((a->f8 & 0x1C00) == 0x1C00) {
        Str s;
        sp = (u8 *)(tex = &lbl_8032E7B4);
        fn_800F6E40(&s, d);
        s.f8 = 0;
        fn_801488B4(tex, &s);
        a->f16 = a->f15 = ((Tex *)sp)->f1348;
    } else {
        Str s;
        fn_80134848(a->f8);
        tex = fn_801348E8();
        fn_800F6E40(&s, d);
        s.f8 = 0;
        fn_801488B4(tex, &s);
        sp = 0;
    }
    w = *(volatile u32 *)&tex->w;
    h = *(volatile u32 *)&tex->h;
    fn_801482DC(&l, &tex->f28);
    fn_8015569C(a, b, &w, &h, &l, a->f16, buf);
    if (sp) {
        a->f60->f76 = 1;
        fn_80155124(a->f60, (void *)i, a->f56, ((Tex *)sp)->w, ((Tex *)sp)->h, &((Tex *)sp)->f28, (Tex *)sp, a->f8, 0);
        ((Tex *)sp)->v4();
    } else {
        u32 hh = h;
        u32 ww = w;
        if (!(a->f12 & 4) && a->f15 > 1) {
            int chain;
            Lod *prev;
            Lod *cur;
            tex->v4();
            chain = 0;
            i = a->f15 - 1;
            sp = (u8 *)&buf[i];
            prev = 0;
            cur = &a->f60[i];
            ww >>= i;
            hh >>= i;
            for (; i >= 0; i--) {
                if (i == 0 || !(a->f12 & 4)) {
                    if (tex->f28 == 0) {
                        Str s;
                        char nb[4];
                        fn_800F6E40(&s, d);
                        s.f8 = 0;
                        if ((u32)i != 0 && (u32)i < 100) {
                            fn_800E8F6C(nb, lbl_80364594, i);
                            strcat((char *)&s, nb);
                        }
                        fn_801488B4(tex, &s);
                    }
                    fn_80155124(cur, b, a->f56 + *(u32 *)sp, ww, hh, &l, tex, a->f8, prev);
                    tex->v4();
                } else {
                    fn_801551F8(cur, a->f56 + *(u32 *)sp, ww, hh, &l, a->f8, prev);
                }
                if (chain) prev = cur;
                chain = 0;
                ww <<= 1;
                hh <<= 1;
                cur--;
                sp -= 4;
            }
        }
    }
    if (a->f60->v2()) a->f12 |= lbl_80364590;
    else a->f12 &= ~0x20;
}

} /* extern "C" */
