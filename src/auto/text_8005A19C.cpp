// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

#include "common.h"

struct Hd { u8 p[1068]; s32 f1068; u8 p1072[4]; s32 f1076; };
struct Pf { u8 p[12]; f32 *f12; };
class O { public: u8 p0[96]; s32 f96; u8 p100[180]; s32 f280; s32 f284; s32 f288; s32 f292; u8 p296[8]; Hd *f304; u8 p308[4]; f32 f312; char *f316; u8 p320[4];
    Pf *f324; f32 f328; f32 f332; };
static u8 sPad[984] = {1};
static s32 tI[16] = {1};
static s32 tB[37] = {1};
static s32 tS[37] = {1};
extern "C" {
extern f32 lbl_8035E354, lbl_8035E358;
extern char lbl_8035E304[8], lbl_8035E32C[8], lbl_8035E33C[8], lbl_8035E334[8];
extern void *lbl_8035B65C;
void fn_80241628(O *, int, int);
void fn_8005ABE8(O *);
void fn_802494A4(O *, int);
void fn_8005A874(O *);
void fn_802490E0(O *, int, f32);
void fn_802495F0(O *, int);
void fn_80241DD0(O *, char *, int, int, int, int);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
void fn_80249008(O *, int);
f32 fn_802492CC(O *, int);
void fn_80233F7C(Hd *);
}
extern "C" void fn_8005A19C(O *o, s32 idx) {
    s32 *q;
    s32 i;
    s32 t;
    i = tI[idx];
    t = o->f96;
    q = &tB[i];
    while (t > 0) {
        if (*q > t) break;
        t -= tB[i++];
        q++;
    }
    switch (tS[i]) {
    case 0:
        fn_80241628(o, 0, 0);
        fn_8005ABE8(o);
        break;
    case 1:
        if (o->f288 == 1) fn_802494A4(o, 3);
        else fn_8005A874(o);
        break;
    case 2: o->f304->f1076 = 1; break;
    case 3: return;
    case 4: o->f304->f1068 = 1; break;
    case 5: o->f304->f1068 = 0; break;
    case 6:
        o->f292 = 0;
        if (o->f284 == 1) o->f328 = lbl_8035E354 + *o->f324->f12;
        else fn_802490E0(o, 0, lbl_8035E354 + *o->f324->f12);
        break;
    case 7:
        o->f292 = 0;
        if (o->f284 == 1) o->f328 = lbl_8035E354 + *o->f324->f12;
        else fn_802490E0(o, 0, lbl_8035E354 + *o->f324->f12);
        break;
    case 8:
        o->f292 = 0;
        if (o->f284 == 1) o->f328 = lbl_8035E354 + *o->f324->f12;
        else fn_802490E0(o, 0, lbl_8035E354 + *o->f324->f12);
        break;
    case 9: fn_802494A4(o, 1); break;
    case 10: fn_802495F0(o, 1); break;
    case 11: fn_802494A4(o, 1); break;
    case 12: fn_80241DD0(o, lbl_8035E304, 0, 0, 0, 0); break;
    case 13: {
        if (o->f316) __ct__9C80253F24Fiiii(lbl_8035B65C, o->f316, 0, 0, 0);
        if (lbl_8035E358 == o->f312) fn_802494A4(o, 3);
        else if (o->f284 == 0) fn_802490E0(o, 1, o->f312);
        else o->f332 = o->f312;
        break;
    }
    case 14:
        fn_80249008(o, 0);
        fn_80249008(o, 1);
        fn_802494A4(o, 3);
        break;
    case 15:
        o->f328 = fn_802492CC(o, 0);
        if (o->f328 > lbl_8035E358) fn_80249008(o, 0);
        o->f284 = 1;
        break;
    case 16:
        o->f328 = fn_802492CC(o, 0);
        if (o->f328 > lbl_8035E358) fn_80249008(o, 0);
        o->f332 = fn_802492CC(o, 1);
        if (o->f332 > lbl_8035E358) fn_80249008(o, 1);
        o->f284 = 1;
        break;
    case 17:
        o->f328 = fn_802492CC(o, 0);
        if (o->f328 > lbl_8035E358) fn_80249008(o, 0);
        o->f284 = 1;
        break;
    case 18:
        o->f284 = 0;
        if (o->f328 > lbl_8035E358) fn_802490E0(o, 0, o->f328);
        break;
    case 19:
        o->f284 = 0;
        if (o->f328 > lbl_8035E358) fn_802490E0(o, 0, o->f328);
        else if (o->f332 > lbl_8035E358) fn_802490E0(o, 1, o->f332);
        break;
    case 20:
        o->f284 = 0;
        if (o->f328 > lbl_8035E358) fn_802490E0(o, 0, o->f328);
        break;
    case 21:
        o->f288 = 1;
        fn_80241DD0(o, lbl_8035E32C, 0, 0, 0, 0);
        break;
    case 22: o->f288 = 0; break;
    case 23:
        fn_80241DD0(o, lbl_8035E33C, 0, 0, 0, 0);
        o->f280 = 1;
        break;
    case 24:
        fn_80241DD0(o, lbl_8035E334, 0, 0, 0, 0);
        o->f280 = 0;
        break;
    case 25:
        fn_80233F7C(o->f304);
        fn_80241DD0(o, lbl_8035E32C, 0, 0, 0, 0);
        break;
    case 26: break;
    }
}

} /* extern "C" */
