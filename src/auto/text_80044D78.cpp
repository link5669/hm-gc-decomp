// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V_44D78 {
    u8 pad[192];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void m8(char *);
};
extern "C" {
typedef struct { u8 d[52]; } E_44D78;
typedef struct { u8 pad[104]; s32 idx; u8 pad2[4]; E_44D78 *arr; } G_44D78;
#pragma opt_propagation off
static u8 tab_000_44D78[832] = { 1 };
static s32 tabA_44D78[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
static s32 tabB_44D78[9] = { 28, 28, 28, 28, 28, 28, 28, 28, 28 };
static s32 tabC_44D78[9] = { 0, 0, 1, 2, 3, 4, 5, 6, 7 };
extern char lbl_8035CC0C[4];
extern f32 lbl_8035CC10;
extern f32 lbl_8035CC14;
extern f32 lbl_8035CC18;
extern V_44D78 *lbl_8035B684;
extern char lbl_802956D0[];
extern G_44D78 *lbl_8035B5E4;
extern void *lbl_8035A0A4;
extern void *lbl_8035B79C;
s32 fn_800F6CD0(char *, char *);
void fn_80242B58(u8 *, char *);
void fn_80253304(E_44D78 *, s32, f32);
void fn_80253250(E_44D78 *);
s32 fn_8003CC3C(void *);
s32 fn_8003CDA4(void *);
void fn_8026820C(void *, s32);

void fn_80044D78(u8 *p, s32 n) {
    s32 *q;
    s32 i;
    s32 t;
    i = tabA_44D78[n];
    t = *(s32 *)(p + 96);
    q = &tabB_44D78[i];
    while (t > 0) {
        if (*q > t) break;
        t -= tabB_44D78[i++];
        q++;
    }
    switch (tabC_44D78[i]) {
    case 0:
        return;
    case 1:
        if (*(char **)(p + 124) != 0 && fn_800F6CD0(*(char **)(p + 124), lbl_8035CC0C) == 0)
            fn_80242B58(p, *(char **)(p + 124));
        break;
    case 2:
        lbl_8035B684->m8(lbl_802956D0);
        break;
    case 3:
        fn_80253304(&lbl_8035B5E4->arr[lbl_8035B5E4->idx], 500, lbl_8035CC10);
        break;
    case 4:
        fn_80253304(&lbl_8035B5E4->arr[lbl_8035B5E4->idx], 500, lbl_8035CC14);
        break;
    case 5:
        fn_80253304(&lbl_8035B5E4->arr[lbl_8035B5E4->idx], 500, lbl_8035CC18);
        break;
    case 6:
        fn_80253250(&lbl_8035B5E4->arr[lbl_8035B5E4->idx]);
        break;
    case 7: {
        void *o = lbl_8035A0A4;
        s32 a = fn_8003CC3C(o);
        if (a - fn_8003CDA4(o) > 0) {
            fn_8026820C(lbl_8035B79C, 1);
            fn_8026820C(lbl_8035B79C, 4);
        } else {
            fn_8026820C(lbl_8035B79C, 6);
        }
        break;
    }
    case 8:
        break;
    }
}
#pragma opt_propagation reset

} /* extern "C" */
