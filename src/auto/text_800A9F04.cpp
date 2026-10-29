// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct VB {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24();
};
extern "C" {
typedef struct Tabs {
    u8 pad[744];
    s32 a[7];
    s32 b[18];
    s32 c[18];
} Tabs;
typedef struct Self {
    u8 pad[96];
    s32 f96;
    u8 pad2[224 - 100];
    VB *f224;
    u8 pad3[8];
    s32 *f236;
    f32 *f240;
} Self;
static u8 tab_000[744] = { 1 };
static s32 tabA[7] = { 0, 3, 5, 8, 11, 14, 17 };
static s32 tabB[18] = { 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3 };
static s32 tabC[18] = { 0, 1, 2, 3, 4, 4, 5, 4, 4, 6, 4, 4, 7, 4, 4, 8, 4, 4 };
extern f32 lbl_803621E0;
void fn_80241628(Self *self, s32 a, s32 b);
void fn_8022C128(VB *o, s32 a, s32 b, s32 c, s32 d, f32 f);
void fn_8024017C(Self *self);
void fn_8024125C(Self *self, s32 a);
void fn_802494A4(Self *self, s32 a);

void fn_800A9F04(Self *self, s32 n) {
    s32 *q;
    s32 j;
    s32 t;
    j = tabA[n];
    t = self->f96;
    for (q = tabB + j; t > 0; q++) {
        if (*q > t) break;
        t -= tabB[j++];
    }
    switch (tabC[j]) {
    case 0:
        fn_80241628(self, 0, 0);
        self->f224->v24();
        fn_8022C128(self->f224, 0, 0, 0, 0, lbl_803621E0);
        break;
    case 1:
        self->f224->v23();
        break;
    case 2:
        self->f224->v24();
        fn_8024017C(self);
        fn_8024125C(self, 0);
        break;
    case 3:
        fn_802494A4(self, 1);
        break;
    case 4:
        return;
    case 5:
        fn_802494A4(self, 0);
        break;
    case 6:
        fn_802494A4(self, 2);
        break;
    case 7: {
        s32 v = *self->f236;
        fn_8022C128(self->f224, v, v, v, 0, *self->f240);
        break;
    }
    case 8:
        fn_8022C128(self->f224, 0, 0, 0, 0, *self->f240);
        break;
    case 9:
        break;
    }
}

} /* extern "C" */
