// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct F80247B04 {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2(void *tab, s32 n, s32 z);
};
struct C80215F50 {
    u8 pad[44];
    F80247B04 *f44;
    u8 pad2[8];
    C80215F50();
    ~C80215F50();
};
struct C80247A00 {
    u8 pad[108];
    C80247A00();
    ~C80247A00();
};
struct S80247B04 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    s32 f20;
    C80247A00 *f24;
    s32 f28;
};
extern "C" {
extern char lbl_803662A0[4];
extern u8 lbl_802F1B00[];
extern void *lbl_8035B508;
s32 fn_80215C84(C80215F50 *f, char *name, char *mode, s32 a, s32 b);
void fn_800FB000(F80247B04 *f, s32 c);
void fn_800FAFA8(F80247B04 *f);
s32 fn_800FB33C(F80247B04 *f);
void fn_800FAF50(F80247B04 *f);
void fn_800F8E38(S80247B04 *self, s32 n);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
void fn_800FB064(F80247B04 *f, u32 *out);
void fn_80246C68(C80247A00 *e, F80247B04 *f);
void fn_800F87F0(S80247B04 *self, u32 *key, C80247A00 *e);

s32 fn_80247B04(S80247B04 *self, char *name) {
    C80215F50 file;
    u32 key[2];
    F80247B04 *f;
    s32 n;
    s32 i;
    if (self->f20 != 0) {
        self->v1();
    }
    if (fn_80215C84(&file, name, lbl_803662A0, 2, 0) != 0) {
        return -1;
    }
    f = file.f44;
    f->v2(lbl_802F1B00, 29, 0);
    fn_800FB000(f, 58);
    fn_800FAFA8(f);
    n = fn_800FB33C(f);
    fn_800FAF50(f);
    self->f20 = 1;
    self->f28 = n;
    fn_800F8E38(self, self->f28);
    if (lbl_8035B508 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B508);
    self->f24 = new C80247A00[self->f28];
    fn_800F7E98();
    if (self->f24 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    for (i = 0; i < self->f28; i++) {
        fn_800FB000(f, 58);
        fn_800FB064(f, key);
        fn_80246C68(&self->f24[i], f);
        fn_800F87F0(self, key, &self->f24[i]);
    }
    return 0;
}

} /* extern "C" */
