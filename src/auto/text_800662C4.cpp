// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V800662C4 {
    u8 pad[8];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void *v5(s32);
};
extern "C" {

extern char lbl_80297760[];
extern char lbl_8035E740[5];
extern void *lbl_8035B5E4;
extern u8 *lbl_8035B65C;
void *fn_800F8274(void *, char *);
void *fn_80261114(u8 *, char *, s32);
void *fn_80110444(void *, char *, s32);
V800662C4 **fn_8010FEDC(void *, void *, char *, s32);
void fn_80261B18(u8 *, void *);

#pragma opt_propagation off
void fn_800662C4(u8 *p, void *a) {
    char *str;
    void *h;
    *(void **)(p + 252) = a;
    str = lbl_80297760;
    *(void **)(p + 356) = fn_800F8274(lbl_8035B5E4, lbl_8035E740);
    *(u8 **)(p + 360) = lbl_8035B65C + 1904;
    *(void **)(p + 212) = fn_80261114(p, str + 12, 1);
    *(void **)(p + 216) = fn_80261114(p, str + 28, 1);
    *(void **)(p + 220) = fn_80261114(p, str + 44, 1);
    *(void **)(p + 176) = fn_80261114(p, str + 60, 1);
    *(void **)(p + 180) = fn_80261114(p, str + 72, 1);
    *(void **)(p + 184) = fn_80261114(p, str + 84, 1);
    *(void **)(p + 188) = fn_80261114(p, str + 104, 1);
    *(void **)(p + 192) = fn_80261114(p, str + 124, 1);
    *(void **)(p + 196) = fn_80261114(p, str + 144, 1);
    *(void **)(p + 200) = fn_80261114(p, str + 164, 1);
    *(void **)(p + 204) = fn_80261114(p, str + 176, 1);
    *(void **)(p + 208) = fn_80261114(p, str + 192, 1);
    *(void **)(p + 224) = fn_80261114(p, str + 208, 1);
    *(void **)(p + 228) = fn_80261114(p, str + 224, 1);
    *(void **)(p + 244) = fn_80261114(p, str + 240, 1);
    h = fn_80110444(*(void **)(p + 12), str + 252, 0);
    *(void **)(p + 248) = (*fn_8010FEDC(*(void **)(p + 12), h, str + 264, 0))->v5(0);
    fn_80261B18(p, a);
}
#pragma opt_propagation reset

} /* extern "C" */
