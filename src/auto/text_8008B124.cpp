// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C802449C4 {
    u8 pad[56];
    C802449C4();
    ~C802449C4();
};
extern "C" {
static u8 data_000[736] = { 0 };
static s32 data_2E0[7] = { 0, 2, 3, 5, 7, 9, 12 };
static s32 data_2FC[14] = { 1, 3, 4, 1, 3, 1, 3, 3, 1, 1, 2, 1, 1, 3 };
static s32 data_334[14] = { 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 1, 6 };
extern u8 *lbl_8035B308;
struct P8008B124 {
    u8 pad[96];
    s32 f96;
    u8 pad2[208];
    s32 *f308;
    s32 *f312;
    u8 pad3[4];
    s32 f320;
    s32 f324;
    s32 f328;
    s32 f332;
};
void fn_80241628(P8008B124 *, s32, s32);
void *fn_80242144(void *self, s32 n);
void fn_802448C8(C802449C4 *it, void *list);
void fn_80244750(C802449C4 *it, s32 n);
s32 fn_8024457C(C802449C4 *it);
s32 fn_80244584(C802449C4 *it);
void fn_802494A4(void *self, s32 n);

void fn_8008B124(P8008B124 *p, s32 n) {
    s32 *q;
    s32 j = data_2E0[n];
    s32 t = p->f96;
    for (q = &data_2FC[j]; t > 0; q++) {
        if (*q > t) break;
        t -= data_2FC[j++];
    }
    switch (data_334[j]) {
    case 0:
        fn_80241628(p, 0, 0);
        if (*p->f312 != 0) {
            p->f320 = *(s32 *)(lbl_8035B308 + 72);
        } else {
            C802449C4 it;
            fn_802448C8(&it, fn_80242144(p, 0));
            fn_80244750(&it, 0);
            if (fn_80244584(&it) == 0) p->f320 = fn_8024457C(&it);
        }
        p->f332 = 1;
        if (*p->f308 == 0) fn_802494A4(p, 3);
        break;
    case 1:
        return;
    case 2:
        p->f324 = 0;
        break;
    case 3:
        p->f324 = 1;
        break;
    case 4:
        if (p->f328 != 0) fn_802494A4(p, 1);
        else fn_802494A4(p, 2);
        break;
    case 5:
        fn_802494A4(p, 3);
        break;
    case 6:
        fn_802494A4(p, 0);
        break;
    case 7:
        break;
    }
}

} /* extern "C" */
