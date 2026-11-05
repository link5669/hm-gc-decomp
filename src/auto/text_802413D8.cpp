// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct B802413D8 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual u32 Get(s32);
};
struct I802413D8 { char *name; u32 x4; u32 x8; };
struct O802413D8 { u8 pad[52]; u16 f52; };
struct P802413D8 { u8 pad[416]; f32 f416; };
struct R802413D8 { u32 f0; f32 f4; };
struct S802413D8 : B802413D8 {
    u8 pad4[120];
    s32 f124;
    u8 pad128[72];
    I802413D8 *f200;
    u32 f204;
    O802413D8 **f208;
    u8 pad212[8];
    s32 f220;
    P802413D8 *f224;
};
struct G3 { u8 pad[768]; s32 f768; };
struct G2 { u8 pad[600]; G3 *f600; };
struct G1 { u8 pad[72]; G2 *f72; };
extern "C" {
extern G1 *lbl_8035B308;
extern f32 lbl_8036613C;
void fn_800F6E40(char *, void *);
char *strcpy(char *, const char *);
int stricmp(const char *, const char *);
void fn_8022CC44(P802413D8 *, O802413D8 *, s32, u32, s32, s32, f32, f32);
R802413D8 *fn_8022D694(P802413D8 *);

#pragma optimization_level 1
void fn_802413D8(S802413D8 *self, void *unused, s32 a, s32 b, f32 *pf, f32 f) {
    char buf20[12];
    char buf8[12];
    s32 flag;
    O802413D8 *item;
    s32 cnt;
    s32 off;
    s32 i;
    R802413D8 *r;
    flag = lbl_8035B308->f72->f600->f768;
    if (flag != 0) {
        a = 1;
        f = lbl_8036613C;
    }
    fn_800F6E40(buf20, unused);
    for (i = 0, off = 0; i < self->f124; off += 12, i++) {
        strcpy(buf8, *(char **)((u8 *)self->f200 + off));
        if (stricmp(buf8, buf20) == 0) {
            self->f220 = i;
            self->f224->f416 = lbl_8036613C;
            if (pf != 0 && flag == 0) {
                item = self->f208[i];
                fn_8022CC44(self->f224, item, 1, self->Get(i), a, b, f, *pf);
            } else {
                item = self->f208[i];
                fn_8022CC44(self->f224, item, 1, self->Get(i), a, b, f, lbl_8036613C);
            }
            if (flag != 0) {
                cnt = self->f208[i]->f52;
                r = fn_8022D694(self->f224);
                r->f4 = cnt - 1;
            }
            return;
        }
    }
}
#pragma optimization_level reset

} /* extern "C" */
