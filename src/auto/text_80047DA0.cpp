// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

#include "common.h"

struct V3 { f32 x, y, z; };
struct C4 { f32 a, b, c, d; };
struct In { u8 p[20]; C4 f20; };
struct Y { u8 p[16]; In *f16; };
struct N16 { u8 p[16]; void *f16; };
struct H { u32 f0; u16 f4; u8 p6[42]; N16 *f48; u8 p52[12]; void *f64; u8 p68[40]; Y *f108; };
struct Cm { u8 p[156]; H *f156; u8 p160[412]; s32 f572; };
struct FT { u8 p[304]; void (*f304)(void *, V3 *); };
struct G116 { u8 p[484]; void *f484; };
struct GB { u8 p[12]; void *f12; u8 p16[100]; G116 *f116; };
class O { public: u8 p0[96]; s32 f96; u8 p100[124]; Cm *f224; u8 p228[56]; s32 *f284; s32 *f288; u8 p292[4]; s32 *f296; void *f300; void *f304; u8 p308[4];
    void *f312, *f316, *f320; f32 f324, f328, f332; u8 p336[4]; V3 f340; C4 f352; C4 *f368; s32 f372; C4 f376; Y *f392; H *f396; u8 p400[16]; f32 f416; s32 f420;
    void *f424, *f428; };
static u8 sPad[792] = {1};
static s32 tI[12] = {1};
static s32 tB[23] = {1};
static s32 tS[23] = {1};
const char *wG_strpool_80047DA0[] = { "LIGHTOFF", "FLASHOFF", "AMCYCOFF", "SOUNDOFF" };
extern "C" {
extern FT lbl_803286D0;
extern GB *lbl_8035B65C;
extern f32 lbl_8035D184, lbl_8035D194;
extern u32 lbl_8035D180;
extern char lbl_8035D188[8], lbl_8035D18C[8], lbl_8035D160[8], lbl_8035D168[8];
void *fn_8023F4A0(O *, char *, char *, char *, int);
void fn_8019AE40(void *, H *);
void fn_8024118C(O *, void *, int);
void fn_80240DBC(O *, f32);
void fn_802494A4(O *, int);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
void fn_800483EC(O *, int);
}
inline void On(O *o) {
    if (o->f396) o->f396->f0 |= lbl_8035D180;
    if (o->f300) fn_8024118C(o, o->f300, 0);
    if (o->f304) fn_8024118C(o, o->f304, 1);
}
inline void Off(O *o) {
    if (o->f396) o->f396->f0 &= ~0x800;
    fn_80240DBC(o, lbl_8035D194);
}
inline void Restore(O *o) {
    if (o->f392) o->f392->f16->f20 = o->f352;
    if (o->f392 && o->f296 && *o->f296) o->f396->f0 &= ~0x800;
}
extern "C" void fn_80047DA0(O *o, s32 idx) {
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
        o->f324 = lbl_8035D184;
        o->f328 = lbl_8035D184;
        o->f332 = lbl_8035D184;
        o->f312 = fn_8023F4A0(o, lbl_8035D188, lbl_8035D188, (char *)"AmbientFlashOn", 0);
        o->f316 = fn_8023F4A0(o, lbl_8035D188, lbl_8035D188, (char *)"AmbientFlashOff", 0);
        o->f320 = fn_8023F4A0(o, lbl_8035D188, lbl_8035D188, (char *)"LightStartColor", 0);
        o->f424 = fn_8023F4A0(o, lbl_8035D188, lbl_8035D18C, (char *)"AmbientCycleHigh", 0);
        o->f428 = fn_8023F4A0(o, lbl_8035D188, lbl_8035D18C, (char *)"AmbientCycleLow", 0);
        o->f368 = (C4 *)((u8 *)lbl_8035B65C + 88);
        if (!o->f312 && !o->f316) {
            H *h = o->f224->f156;
            if (h && h->f4 == 15) {
                N16 *y = h->f48;
                if (y) lbl_803286D0.f304(y->f16, &o->f340);
                else { o->f340.x = lbl_8035D184; o->f340.y = lbl_8035D184; o->f340.z = lbl_8035D184; }
                o->f396 = o->f224->f156;
                o->f392 = o->f396->f108;
                if (!o->f320) o->f352 = o->f392->f16->f20;
            }
        }
        if (o->f396 && !o->f396->f64) {
            fn_8019AE40(lbl_8035B65C->f12, o->f396);
            fn_8019AE40(lbl_8035B65C->f116->f484, o->f396);
        }
        break;
    case 1:
        if (o->f284 && *o->f284) On(o);
        else Off(o);
        break;
    case 2:
        if (o->f288 && *o->f288) On(o);
        else Off(o);
        break;
    case 3: return;
    case 4:
        if (o->f284 && *o->f284) Off(o);
        break;
    case 5:
        if (o->f288 && *o->f288) Off(o);
        break;
    case 6: fn_802494A4(o, 1); break;
    case 7: fn_802494A4(o, 2); break;
    case 8: __ct__9C80253F24Fiiii(lbl_8035B65C, lbl_8035D160, 0, 0, 0); break;
    case 9: __ct__9C80253F24Fiiii(lbl_8035B65C, lbl_8035D168, 0, 0, 0); break;
    case 10: fn_800483EC(o, 0); break;
    case 11: fn_800483EC(o, 1); break;
    case 12:
        if (o->f316) *o->f368 = o->f376;
        Restore(o);
        break;
    case 13:
        if (o->f312) *o->f368 = o->f376;
        Restore(o);
        break;
    case 14:
        o->f420 = 1;
        o->f416 = lbl_8035D184;
        break;
    case 15:
        o->f420 = 0;
        if (!o->f372) {
            o->f376 = *o->f368;
            o->f372 = 1;
        }
        *o->f368 = o->f376;
        break;
    case 16: o->f224->f572 = 1; break;
    case 17: o->f224->f572 = 0; break;
    case 18: break;
    }
}

} /* extern "C" */
