// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct S801E6918 {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
};
struct T801E6918 {
    u8 pad0[24];
    s32 *f24;
    u32 f28;
    u8 pad20[8];
    s32 f40;
    s32 f44;
    s32 f48;
    u32 f52;
    u8 pad38[4];
    f32 f60;
};
extern "C" {
extern u32 lbl_8035B0A0[2];
extern u32 lbl_80365324;
u32 fn_800FADA8(S801E6918 *s);
s32 fn_800FB33C(S801E6918 *s);
f32 fn_800FB2E0(S801E6918 *s);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(u32 heap);
void fn_800F7E98(void);
void *__nwa__FUl(u32 size);
void fn_801EB474(T801E6918 *self, S801E6918 *s, s32 id);

void fn_801E6918(T801E6918 *self, S801E6918 *s, s32 id) {
    u32 i;
    switch (id) {
    case 78:
        self->f28 = fn_800FADA8(s);
        if (lbl_8035B0A0[0] == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B0A0[0]);
        self->f24 = (s32 *)__nwa__FUl(self->f28 * 4);
        fn_800F7E98();
        if (self->f24 == 0) fn_800604C4(-4, 0, 0, 0);
        for (i = 0; i < self->f28; i++) {
            self->f24[i] = fn_800FB33C(s);
        }
        s->v5();
        break;
    case 73:
        self->f60 = fn_800FB2E0(s);
        break;
    case 74:
        self->f40 = fn_800FB33C(s);
        break;
    case 75:
        self->f44 = 1;
        if (self->f44 != 0) self->f52 |= lbl_80365324;
        else self->f52 &= ~4;
        break;
    case 76:
        self->f44 = 0;
        if (self->f44 != 0) self->f52 |= lbl_80365324;
        else self->f52 &= ~4;
        break;
    case 77:
        self->f48 = fn_800FB33C(s);
        break;
    default:
        fn_801EB474(self, s, id);
        break;
    }
}

} /* extern "C" */
