// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

#include "common.h"

#define V(n) virtual void n();
struct K8 { u32 a, b; };
class Cam { public: V(c0) V(c1) V(c2) V(c3) V(c4) V(c5) V(c6) V(c7) V(c8) V(c9) V(c10) V(c11) V(c12) V(c13) V(c14) V(c15) V(c16) V(c17) V(c18) V(c19)
    V(c20) V(c21) V(c22) V(c23) V(c24) V(c25) V(c26) V(c27) V(c28) V(c29) V(c30) V(c31) V(c32)
    virtual void play(char *, struct Cm *, int, void *, int); };
struct C3 { u8 p[4]; void *f4; };
struct C2 { u8 p[8]; C3 *f8; };
struct Cm { u8 p[16]; C2 *f16; u8 p20[160]; u32 f180; };
struct GB { u8 p[8]; struct { u8 p[4]; u8 *f4; } *f8; };
class O { public: u8 p0[96]; s32 f96; u8 p100[124]; Cm *f224; Cam *f228; u8 p232[4]; void *f236; u8 p240[40]; void *f280;
    void *f284, *f288, *f292, *f296, *f300, *f304, *f308, *f312; s32 *f316; s32 *f320; s32 *f324; f32 *f328; char *f332;
    s32 f336; s32 f340; u32 f344; f32 f348; u8 p352[12]; s32 f364; s32 f368; s32 f372; s32 f376; };
static u8 sPad[872] = {1};
static s32 tI[12] = {1};
static s32 tB[36] = {1};
static s32 tS[36] = {1};
const char *wG_strpool_800A3688[] = { "MStation", "STRTBAND", "STRTHAUN", "CONVERSE", "STNDSTIL", "CONVERS2", "ANIMOVER", "SENDDIST" };
extern "C" {
extern GB *lbl_8035B460;
extern void *lbl_8035B65C;
extern void *lbl_8035B79C;
extern f32 lbl_80361CC4, lbl_80361CC8, lbl_80361CD4;
extern char lbl_80361C90[8], lbl_80361CCC[8];
int rand(void);
void fn_800F6FBC(void *, K8 *);
void *fn_800F9398(u8 *, K8 *);
void *fn_8023F52C(O *, char *, char *, char *, int, int);
void fn_802402E0(O *);
void fn_80241628(O *, int, int);
void fn_8022BF30(Cm *, s32, int, f32);
void fn_80240D70(O *, int);
void fn_80240D44(O *);
void fn_800A41DC(O *);
void fn_802680D8(void *);
int fn_800F6CD0(char *, char *);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
void fn_802490E0(O *, int, f32);
void fn_800A3E30(O *);
void fn_802494A4(O *, int);
void fn_80249008(O *, int);
void fn_80240274(O *, int);
}
inline void Stop(O *o) {
    fn_80240D70(o, -1);
    if (o->f316 && *o->f316) fn_80240D44(o);
}
extern "C" void fn_800A3688(O *o, s32 idx) {
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
    case 0: {
        K8 b;
        fn_800F6FBC(o->f224->f16->f8->f4, &b);
        o->f280 = fn_800F9398(lbl_8035B460->f8->f4 + 732, &b);
        o->f284 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaConversationAnimGroup1", 1, 1);
        o->f288 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaConversationAnimGroup2", 1, 1);
        o->f292 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaConversationAnimGroup3", 1, 1);
        o->f296 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaIdleAnimGroup1", 1, 1);
        o->f300 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaIdleAnimGroup2", 1, 1);
        o->f304 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaIdleAnimGroup3", 1, 1);
        o->f308 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaStandAnimGroup", 0, 1);
        o->f312 = fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"aaPrepareAnimGroup", 0, 1);
        o->f320 = (s32 *)fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"BaseTrans", 1, 0);
        o->f324 = (s32 *)fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"PulseAmount", 1, 0);
        o->f328 = (f32 *)fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"PulseInterval", 1, 0);
        o->f332 = (char *)fn_8023F52C(o, lbl_80361C90, lbl_80361C90, (char *)"StillEvent", 0, 0);
        fn_802402E0(o);
        fn_80241628(o, 0, 0);
        if (o->f320) o->f340 = *o->f320;
        if (o->f324) o->f344 = *o->f324;
        if (o->f328) o->f348 = *o->f328;
        o->f224->f180 |= 4;
        fn_8022BF30(o->f224, 0, 1, lbl_80361CC4);
        fn_802402E0(o);
        break;
    }
    case 1:
        o->f364 = 1;
        Stop(o);
        fn_800A41DC(o);
        break;
    case 2:
        o->f376 = 1;
        Stop(o);
        fn_802680D8(lbl_8035B79C);
        fn_800A41DC(o);
        break;
    case 3:
        o->f368 = 1;
        Stop(o);
        fn_800A41DC(o);
        if (o->f332 && !fn_800F6CD0(o->f332, lbl_80361C90)) __ct__9C80253F24Fiiii(lbl_8035B65C, o->f332, 0, 0, 0);
        break;
    case 4:
        o->f372 = 1;
        fn_800A41DC(o);
        break;
    case 5: return;
    case 6: o->f364 = 0; break;
    case 7: o->f376 = 0; break;
    case 8: o->f368 = 0; break;
    case 9: o->f372 = 0; break;
    case 10: {
        s32 s = 1;
        u32 n, r;
        if (o->f336 >= o->f340) s = -1;
        n = o->f344;
        r = 0;
        if (n) r = rand() % n;
        o->f336 = o->f340 + s * r;
        fn_8022BF30(o->f224, o->f336, 0, o->f348);
        fn_802490E0(o, 0, o->f348);
        break;
    }
    case 11:
        if (!o->f364 && !o->f368) fn_800A3E30(o);
        break;
    case 12: fn_802494A4(o, 1); break;
    case 13:
        __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)"STNDSTIL", 0, 0, 0);
        fn_802494A4(o, 2);
        break;
    case 14:
        if (o->f308) fn_802494A4(o, 3);
        break;
    case 15:
        Stop(o);
        if (o->f308) {
            fn_802494A4(o, 3);
            fn_80249008(o, 1);
        } else {
            fn_802494A4(o, 1);
        }
        break;
    case 16:
        if (o->f312) fn_802490E0(o, 1, lbl_80361CC8);
        break;
    case 17:
        __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)"STNDSTIL", 0, 0, 0);
        fn_802494A4(o, 4);
        break;
    case 18:
        if (o->f364 || o->f376 || o->f368 || o->f372) o->f228->play(lbl_80361CCC, o->f224, 0, o->f236, 0);
        break;
    case 19:
        __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)"STNDSTIL", 0, 0, 0);
        fn_802494A4(o, 5);
        break;
    case 20:
        fn_80240274(o, 0);
        fn_802494A4(o, 1);
        fn_8022BF30(o->f224, o->f340, 1, lbl_80361CD4);
        fn_802490E0(o, 0, lbl_80361CD4);
        break;
    case 21: break;
    }
}

} /* extern "C" */
