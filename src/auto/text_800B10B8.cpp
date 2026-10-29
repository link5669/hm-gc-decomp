// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct A { u8 pad[180]; u32 fl180; };
struct P {
    u8 pad0[96];
    s32 t96;
    u8 pad100[124];
    A *a224;
    u8 pad228[52];
    f32 *f280;
    f32 *f284;
    f32 *f288;
    f32 *f292;
    u32 u296;
    char *s300;
    char *s304;
    s32 *s308;
    s32 *s312;
    s32 i316;
    s32 i320;
};
static u8 sPad[828] = {1};
static s32 tA[9] = {1};
static s32 tB[22] = {1};
static s32 tC[34] = {1};
static const char sPad2[36] = {1};
static const char sS36[] = "C_FREEZE";
static const char sS48[] = "TELEPORT";
static const char sS60[] = "C_RESUME";
extern void *lbl_8035B65C;
extern void *lbl_8035A02C;
extern char lbl_80362E94[4], lbl_80362E28[4];
void fn_802494A4(P *, int);
void fn_802490E0(P *, int, f32);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
void *fn_80242144(P *, int);
void fn_80242BC0(void *, char *, int, int, u32, int);
void fn_80039E80(void *, int, f32);
void fn_800F6E88(char *, char *);
int fn_800F6CD0(char *, char *);

void fn_800B10B8(P *p, s32 n) {
    s32 *q;
    s32 i;
    s32 t;
    t = p->t96;
    i = tA[n];
    for (q = tB + i; t > 0; q++) {
        if (*q > t) break;
        t -= tB[i++];
    }
    switch (tC[i]) {
    case 0:
        p->a224->fl180 |= 4;
        p->i320 = *p->s312;
        fn_802494A4(p, 1);
        break;
    case 1:
        return;
    case 2:
        fn_802490E0(p, 0, *p->f280);
        __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)sS36, 0, 0, 0);
        if (*p->s308) fn_80242BC0(fn_80242144(p, 0), lbl_80362E94, 0, 0, 0, 0);
        break;
    case 3:
        fn_802490E0(p, 1, *p->f284);
        fn_80039E80(lbl_8035A02C, 1, *p->f284);
        break;
    case 4:
        fn_802490E0(p, 2, *p->f288);
        fn_80242BC0(fn_80242144(p, 0), (char *)sS48, 0, 0, p->u296, 0);
        __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)sS60, 0, 0, 0);
        break;
    case 5: {
        char buf[8];
        fn_80039E80(lbl_8035A02C, 0, *p->f292);
        fn_800F6E88(buf, p->i316 ? p->s304 : p->s300);
        if (fn_800F6CD0(buf, lbl_80362E28) == 0) fn_80242BC0(fn_80242144(p, 1), buf, 0, 0, 0, 0);
        fn_802494A4(p, 1);
        break;
    }
    case 6:
        if (p->i320) fn_802494A4(p, 2);
        break;
    case 7:
        fn_802494A4(p, 3);
        break;
    case 8:
        fn_802494A4(p, 5);
        break;
    case 9:
        fn_802494A4(p, 4);
        break;
    case 10:
        p->i316 = 0;
        break;
    case 11:
        p->i316 = 1;
        break;
    case 12:
        p->i320 = 1;
        break;
    case 13:
        p->i320 = 0;
        break;
    case 14:
        break;
    }
}

} /* extern "C" */
