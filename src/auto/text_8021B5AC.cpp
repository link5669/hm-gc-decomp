// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O1 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual s32 v4(u32 a);
};
struct O2 { u8 pad[1764]; O1 *f1764; };
struct O3 { u8 pad[28]; O2 *f28; };
struct SB {
    u32 f0;
    u32 f4;
    u32 f8;
    char *f12;
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
};
struct S : SB {
    O3 *f20;
    u32 f24;
};
extern "C" {
s32 fn_8021A4C0(O3 *a, void *b, u32 *c, u32 *d);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
unsigned long strlen(const char *);
char *strcpy(char *, const char *);
extern u32 lbl_803658FC;
extern void *lbl_8035B1D4;

s32 fn_8021B5AC(S *self, void *a, char *str, u32 flags) {
    u32 len;
    self->v3();
    self->f8 = flags;
    if ((self->f8 & 1) || (self->f8 & 0x20)) {
        self->f8 &= ~1;
        self->f8 &= ~0x20;
    }
    if ((self->f8 & 8) || (self->f8 & 4)) {
        self->f8 = 0;
        return 9;
    }
    if (self->f8 & 0x40) self->f8 &= ~0x40;
    if (fn_8021A4C0(self->f20, a, &self->f24, &self->f4) == 0) return 2;
    if (self->f20->f28->f1764->v4(self->f24) != 0) return 3;
    self->f8 |= lbl_803658FC;
    self->f0 = 0;
    len = strlen(str);
    if (lbl_8035B1D4 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B1D4);
    self->f12 = new char[len + 1];
    fn_800F7E98();
    if (self->f12 == 0) fn_800604C4(-4, 0, 0, 0);
    strcpy(self->f12, str);
    return 0;
}

} /* extern "C" */
