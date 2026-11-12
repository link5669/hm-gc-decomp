// One translation unit: fn_800B1844, fn_800B1D58, fn_800B21A0 (they share the int->float constant
// lbl_80362F98, which this unit owns as its compiler literal; the other pool constants stay extern).
// fn_800B1D58 is schedule-equivalent (one stfs in the e *= s length block sits one slot early).
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {
extern u8 lbl_80362EA8[];
extern u8 lbl_80362EB0[];
extern u8 lbl_80362EB4[];
extern u8 lbl_80362EBC[];
extern u8 lbl_80362EC4[];
extern u8 lbl_80362ECC[];
extern u8 lbl_80362ED4[];
extern u8 lbl_80362EDC[];
extern u8 lbl_80362EE4[];
extern u8 lbl_80362EEC[];
extern u8 lbl_80362EF4[];
extern u8 lbl_80362EFC[];
extern u8 lbl_80362F04[];
extern u8 lbl_8029BBD0[];
extern u8 lbl_8029BBDC[];
extern u8 lbl_80362F0C[];
extern u8 lbl_80362F14[];
extern u8 lbl_80362F1C[];
extern u8 lbl_80362F24[];
extern u8 lbl_80362F2C[];
extern u8 lbl_80362F34[];
extern u8 lbl_8029BBE8[];
extern u8 lbl_8029BBF4[];
extern u8 lbl_80362F3C[];
extern u8 lbl_80362F44[];
extern u8 lbl_80362F4C[];
extern u8 lbl_80362F54[];
extern u8 lbl_80362F5C[];
extern u8 lbl_80362F64[];
extern u8 lbl_80362F6C[];
extern u8 lbl_80362F74[];
extern u8 lbl_8029BC00[];
extern u8 lbl_8029BC0C[];
void fn_800B2928(void);
void fn_80249AC4(void);
void fn_800B266C(void);
void fn_80242210(void);
void fn_800B24A8(void);
void fn_8023D198(void);
void fn_800B2A34(void);
typedef struct T T;
void fn_800B1844(T *p, s32 n);
void fn_800B21A0(T *p, f32 dt);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_8003FB68(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_800B2A3C(void);
void fn_8003FB6C(void);

} /* extern "C" */
typedef struct V3 { f32 x, y, z; } V3;
struct VO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13(V3 *a, V3 *b, V3 *c, V3 *d, s32 e);
    virtual void v14(V3 *a, V3 *b, V3 *c, V3 *d, s32 e);
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23();
    virtual void v24();
    u8 pad4[276];
    V3 f280;
    u8 pad292[48];
    f32 f340;
};
extern "C" {
__declspec(section ".data") u8 lbl_802D6D40[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[5] = { (void *)lbl_80362EA8, (void *)lbl_80362EB0, (void *)lbl_80362EB4, (void *)lbl_80362EBC, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_230[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_234[2] = { (void *)lbl_80362EC4, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_23C[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_240[2] = { (void *)lbl_80362ECC, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_248[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_24C[2] = { (void *)lbl_80362ED4, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_254[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_258[2] = { (void *)lbl_80362EDC, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_260[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_264[2] = { (void *)lbl_80362EE4, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_26C[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_270[2] = { (void *)lbl_80362EEC, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_278[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_27C[2] = { (void *)lbl_80362EF4, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_284[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_288[2] = { (void *)lbl_80362EFC, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_290[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_294[2] = { (void *)lbl_80362F04, (void *)lbl_80362EB0 };
static __declspec(section ".data") u8 sPad_29C[16] = { 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2AC[1] = { (void *)lbl_8029BBD0 };
static __declspec(section ".data") u8 sPad_2B0[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2BC[2] = { (void *)lbl_8029BBDC, (void *)lbl_80362F0C };
static __declspec(section ".data") u8 sPad_2C4[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2D4[1] = { (void *)lbl_80362F14 };
static __declspec(section ".data") u8 sPad_2D8[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2E8[1] = { (void *)lbl_80362F1C };
static __declspec(section ".data") u8 sPad_2EC[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2FC[18] = { (void *)lbl_80362F24, (void *)lbl_80362F2C, (void *)lbl_80362F34, (void *)lbl_8029BBE8, (void *)lbl_8029BBF4, (void *)lbl_80362F3C, (void *)lbl_80362F44, (void *)lbl_80362F4C, (void *)lbl_80362F54, (void *)lbl_80362F5C, (void *)lbl_80362F64, (void *)lbl_80362F6C, (void *)lbl_80362F74, (void *)lbl_8029BC00, (void *)lbl_8029BC0C, (void *)lbl_8029BBD0, (void *)lbl_8029BBDC, (void *)lbl_80362F44 };
static __declspec(section ".data") u8 sPad_344[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_34C[1] = { (void *)lbl_80362F4C };
static __declspec(section ".data") u8 sPad_350[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_358[1] = { (void *)lbl_80362F54 };
static __declspec(section ".data") u8 sPad_35C[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_364[1] = { (void *)lbl_80362F5C };
static __declspec(section ".data") u8 sPad_368[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_370[1] = { (void *)lbl_80362F64 };
static __declspec(section ".data") u8 sPad_374[8] = { 0, 0, 0, 4, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_37C[1] = { (void *)lbl_80362F6C };
static __declspec(section ".data") u8 sPad_380[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_388[1] = { (void *)lbl_80362F74 };
static __declspec(section ".data") u8 sPad_38C[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_394[1] = { (void *)lbl_8029BC00 };
static __declspec(section ".data") u8 sPad_398[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3A0[1] = { (void *)lbl_8029BC0C };
static __declspec(section ".data") u8 sPad_3A4[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3AC[1] = { (void *)lbl_8029BBD0 };
static __declspec(section ".data") u8 sPad_3B0[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3B8[1] = { (void *)lbl_8029BBDC };
static __declspec(section ".data") u8 sPad_3BC[52] = { 0, 0, 0, 0xA, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 0, 0xA };
static __declspec(section ".data") s32 sA[11] = { 0, 6, 9, 0xB, 0xE, 0x11, 0x13, 0x16, 0x18, 0x1B, 0x1C };
static __declspec(section ".data") s32 sB[31] = { 1, 1, 1, 1, 1, 1, 2, 1, 3, 1, 5, 2, 1, 3, 2, 1, 3, 3, 3, 1, 4, 1, 3, 3, 1, 4, 1, 6, 1, 1, 4 };
static __declspec(section ".data") s32 sC[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 6, 6, 8, 6, 9, 6, 6, 0xA, 6, 6 };
static __declspec(section ".data") u8 fill_802D7220[52] = { 0, 0, 0, 8, 0, 0, 0, 6, 0, 0, 0, 0xB, 0, 0, 0, 6, 0, 0, 0, 6, 0, 0, 0, 8, 0, 0, 0, 6, 0, 0, 0, 0xB, 0, 0, 0, 6, 0, 0, 0, 0xC, 0, 0, 0, 6, 0, 0, 0, 0xD, 0, 0, 0, 6 };
__declspec(section ".data") u8 lbl_802D7254[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802D725C[18] = { (void *)fn_800B2928, (void *)fn_80249AC4, (void *)fn_800B266C, (void *)fn_80242210, (void *)fn_800B24A8, (void *)fn_8023D198, (void *)fn_800B2A34, (void *)fn_800B1844, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_800B21A0, (void *)fn_8003FB68, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_800B2A3C, (void *)fn_8003FB6C };
struct FT { u8 pad[12]; void (*f12)(void *, V3 *); };
extern FT lbl_803286D0;
extern u32 lbl_80362F7C;
extern f32 lbl_80362F80;
extern f32 lbl_80362F84;
extern f32 lbl_80362F88;
extern f32 lbl_80362F8C;
extern f32 lbl_80362F90;
typedef struct Q { u8 pad[16]; void *f16; u8 pad2[12]; u32 f32_; } Q;
typedef struct O { u8 pad[48]; Q *f48; } O;
typedef struct A276 { O *f0; u8 pad[8]; s32 f12; s32 f16; f32 f20; f32 f24; f32 f28; } A276;
typedef struct X { u32 f0; u8 pad[44]; u32 f48; } X;
typedef struct T {
    u8 pad0[96]; s32 f96; u8 p1[224 - 100]; VO *f224; u8 p2[276 - 228]; A276 *f276; s32 *f280; f32 *f284;
    s32 *f288; f32 *f292; f32 *f296; f32 *f300; f32 *f304; f32 *f308; f32 *f312; f32 *f316; f32 *f320;
    s32 *f324; s32 *f328; s32 f332; f32 *f336; f32 *f340; f32 *f344; f32 *f348; f32 *f352; f32 *f356;
    V3 f360; s32 f372; f32 f376; s32 f380; f32 f384; s32 f388;
} T;
int rand(void);
void fn_80241628(T *p, s32 a, s32 b);
void fn_802494A4(T *p, s32 a);
void fn_802490E0(T *p, s32 a, f32 v);
void fn_80241588(T *p, s32 a, s32 b, f32 v);
void fn_8024017C(T *p);
void fn_80240F24(T *p, s32 a, s32 b);
void fn_8023F9C8(T *p, s32 a);
void fn_8023F5FC(T *p, s32 a, f32 v);
void fn_80190C98(O *o);
X *fn_8022D694(VO *o);

inline f32 frnd();

void fn_800B1844(T *p, s32 n) {
    s32 *q;
    s32 idx;
    s32 t;
    idx = sA[n];
    t = p->f96;
    for (q = sB + idx; t > 0; q++) {
        if (*q > t) break;
        t -= sB[idx++];
    }
    switch (sC[idx]) {
    case 0:
        fn_80241628(p, 0, 0);
        p->f224->v23();
        if (p->f372 != 0) {
            p->f224->v13(&p->f360, 0, 0, 0, 0);
            p->f372 = 0;
        } else {
            p->f224->v14(&p->f360, 0, 0, 0, 0);
        }
        fn_802494A4(p, 1);
        break;
    case 1:
        fn_80241628(p, 0, 0);
        if (*p->f324 != 0 && (*p->f328 == 0 || p->f388 != 0)) {
            { s32 i = rand() % 10000u; f32 r = lbl_80362F80 * (f32)i; f32 d = *p->f356 - *p->f352; r = d * r + *p->f352; fn_802490E0(p, 1, r); }
        }
        break;
    case 2:
        fn_80241628(p, 1, 0);
        fn_80241588(p, 0, 0, lbl_80362F84);
        break;
    case 3:
        fn_80241628(p, 0, 0);
        fn_8024017C(p);
        fn_802494A4(p, 5);
        fn_80240F24(p, 4, 7);
        break;
    case 4:
        fn_80241628(p, 0, 0);
        fn_8023F9C8(p, 0);
        fn_8023F9C8(p, 1);
        fn_8023F9C8(p, 2);
        fn_80240F24(p, 0, 3);
        fn_8023F5FC(p, p->f332, *p->f336);
        if (p->f276 != 0) {
            V3 v;
            p->f224->v13(&v, 0, 0, 0, 0);
            {
                O *o = p->f276->f0;
                Q *qq = o->f48;
                if (qq) {
                    lbl_803286D0.f12(qq->f16, &v);
                    qq->f32_ |= lbl_80362F7C;
                    fn_80190C98(o);
                }
            }
            p->f276->f12 = 1;
            p->f276->f16 = 1;
            p->f276->f24 = lbl_80362F88;
            p->f276->f20 = lbl_80362F8C;
            {
                A276 *a = p->f276;
                f32 d = a->f24 - a->f20;
                a->f28 = d * lbl_80362F90;
            }
        }
        fn_802494A4(p, 5);
        fn_80240F24(p, 8, 9);
        break;
    case 5:
        fn_80241628(p, 0, 0);
        p->f224->v24();
        break;
    case 6:
        return;
    case 7:
        if (fn_8022D694(p->f224) != 0) {
            X *x = fn_8022D694(p->f224);
            if (x->f48 & 1) x->f0 &= ~2;
        }
        break;
    case 8:
        fn_802494A4(p, 0);
        break;
    case 9:
        if (*p->f280 != 0) {
            V3 v;
            p->f224->v13(&v, 0, 0, 0, 0);
            if (p->f360.z - v.z >= *p->f284) fn_802494A4(p, 3);
        }
        break;
    case 10:
        if (*p->f280 != 0) {
            V3 v;
            p->f224->v13(&v, 0, 0, 0, 0);
            if (p->f360.z - v.z >= *p->f284) {
                fn_802494A4(p, 3);
                break;
            }
        }
        fn_802494A4(p, 1);
        break;
    case 11:
        fn_802494A4(p, 5);
        break;
    case 12:
        p->f380 = 1;
        break;
    case 13:
        p->f376 = lbl_80362F88;
        fn_802494A4(p, 2);
        break;
    case 14:
        break;
    }
}

} /* extern "C" */

extern "C" {
extern FT lbl_803286D0;
extern u32 lbl_80362F7C;
extern f32 lbl_80362F80;
extern f32 lbl_80362F84;
extern f32 lbl_80362F88;
extern f32 lbl_80362F8C;
extern f32 lbl_80362F90;
extern f32 lbl_80362FA0;
extern f32 lbl_80362FA4;
extern f64 lbl_80362FA8;
extern f64 lbl_80362FB0;
typedef struct G72 { u8 pad[72]; VO *f72; } G72;
extern G72 *lbl_8035B308;
void fn_80241628(T *p, s32 a, s32 b);
void fn_80101820(V3 *v);
void fn_80101414(V3 *v, V3 *axis, f32 a);

static inline f32 Sq(f32 x) {
    if (x > *(volatile f32 *)&lbl_80362F88) {
        const f64 _half = lbl_80362FA8;
        const f64 _three = lbl_80362FB0;
        volatile f32 y;
        f64 g = __frsqrte((f64)x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        g = _half * g * (_three - g * g * x);
        y = x * g;
        return y;
    }
    return x;
}

static inline void Set(V3 *o, const V3 *a) {
    o->x = a->x;
    o->y = a->y;
    o->z = a->z;
}

static inline void SetV(V3 *o, const V3 *a) {
    *(volatile f32 *)&o->x = a->x;
    *(volatile f32 *)&o->y = a->y;
    *(volatile f32 *)&o->z = a->z;
}



static inline f32 MagS(f32 x, f32 y, f32 z) {
    f32 xx = x * x, yy = y * y, zz = z * z;
    return Sq(zz + (xx + yy));
}
static inline f32 SubM(V3 *o, const V3 *a, const V3 *b) {
    f32 x = a->x - b->x;
    f32 y = a->y - b->y;
    f32 z = a->z - b->z;
    *(volatile f32 *)&o->x = x;
    *(volatile f32 *)&o->y = y;
    *(volatile f32 *)&o->z = z;
    f32 xx = x * x, yy = y * y, zz = z * z;
    return Sq(zz + (xx + yy));
}
static inline f32 Mag(const V3 *v) {
    f32 x = v->x, y = v->y, z = v->z;
    f32 xx = x * x, yy = y * y, zz = z * z;
    return Sq(zz + (xx + yy));
}

s32 fn_800B1D58(T *p) {
    V3 a;
    V3 b;
    V3 d;
    V3 c;
    V3 e;
    V3 h;
    V3 g;
    f32 dz;
    f32 s;
    lbl_8035B308->f72->v13(&a, 0, 0, 0, 0);
    p->f224->v13(&b, 0, 0, 0, 0);
    dz = b.z - a.z;
    if (dz >= *p->f304 && dz <= *p->f304 + *p->f300) {
        {
        a.z = b.z;
        f32 m = SubM(&d, &b, &a);
        if (m <= *p->f296) {

            VO *o = lbl_8035B308->f72;
            SetV(&c, &o->f280);
            {
            f32 spd = Mag(&c);
            s = spd * *p->f308;
            }
            if (s > *p->f312) s = *p->f312;
            if (s > lbl_80362F88) {
                Set(&e, &d);
                e.z = lbl_80362F88;
                fn_80101820(&e);
                {
                f32 ux, uy, vz, vy, vx, k;
                ux = *(f32 *)&lbl_80362F88;
                uy = lbl_80362F88;
                vy = e.y;
                *(volatile f32 *)&h.x = ux;
                vz = e.z;
                *(volatile f32 *)&h.y = uy;
                vx = *(volatile f32 *)&e.x;
                k = lbl_80362FA4;
                h.z = k;
                g.x = vy * k - vz * uy;
                g.y = vz * ux - vx * k;
                g.z = vx * uy - vy * ux;
                }
                fn_80101820(&g);
                h.x = g.y * e.z - g.z * e.y;
                h.y = g.z * e.x - g.x * e.z;
                h.z = g.x * e.y - g.y * e.x;
                fn_80101820(&h);
                fn_80101414(&e, &g, -(lbl_80362FA0 * *p->f316));
                fn_80241628(p, 1, 0);
                {
                    f32 l;
                    {
                    f32 x0 = *(volatile f32 *)&e.x;
                    f32 y0 = *(volatile f32 *)&e.y;
                    f32 z0 = *(volatile f32 *)&e.z;
                    f32 xxs = x0 * s;
                    f32 zzs = z0 * s;
                    f32 yys = y0 * s;
                    *(volatile f32 *)&e.x = xxs;
                    *(volatile f32 *)&e.y = yys;
                    *(volatile f32 *)&e.z = zzs;
                    l = MagS(xxs, yys, zzs);
                    }

                    VO *m = p->f224;
                    Set(&m->f280, &e);
                    m->f340 = l;
                }
                c.z = lbl_80362F88;
                fn_80101820(&c);
                d.z = lbl_80362F88;
                fn_80101820(&d);
                p->f376 = (c.x * d.y - c.y * d.x >= lbl_80362F88) ? 1 : -1;
                p->f376 *= s;
                return 1;
            }
        }
        }
    }
    return 0;
}

} /* extern "C" */

extern "C" {

struct A {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void s13(V3 *, V3 *, int, int, int);
    virtual void s14(int, V3 *, V3 *, V3 *, int);
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void s24();
    u8 pad4[336];
    f32 f340;
};
void fn_8010117C(V3 *, f32);
void fn_8023FE08(T *, f32);

void fn_800B21A0(T *p, f32 dt) {
    s32 st = p->f96;
    if (st == 1 || (st == 2 && p->f384 >= *p->f348)) {
        if (fn_800B1D58(p)) {
            p->f388 = 1;
            p->f384 = lbl_80362F88;
            f32 h = ((A *)p->f224)->f340;
            if (p->f380 && h > lbl_80362F88) {
                p->f380 = 0;
                {
                    s32 i = rand() % 10000u;
                    f32 r = lbl_80362F80 * (f32)i;
                    f32 d = *p->f344 - *p->f340;
                    r = d * r + *p->f340;
                    fn_802490E0(p, 0, r);
                }
                fn_80240F24(p, 0, 3);
            }
            fn_802494A4(p, 2);
            goto end;
        }
    }
    st = p->f96;
    if (st == 1 && *p->f324) {
        if (((A *)p->f224)->f340 > lbl_80362F88) fn_802494A4(p, 2);
    } else if (st == 2) {
        V3 w, u, v, t;
        ((A *)p->f224)->s13(0, &v, 0, 0, 0);
        { f32 m = lbl_80362FA0 * *p->f320; fn_8010117C(&v, p->f376 * (m * dt)); }
        {
        f32 ux, uy, vz, vy, vx, o;
        ux = *(f32 *)&lbl_80362F88;
        uy = lbl_80362F88;
        vy = v.y;
        *(volatile f32 *)&u.x = ux;
        vz = v.z;
        *(volatile f32 *)&u.y = uy;
        vx = *(volatile f32 *)&v.x;
        o = lbl_80362FA4;
        u.z = o;
        w.x = vy * o - vz * uy;
        w.y = vz * ux - vx * o;
        w.z = vx * uy - vy * ux;
        }
        fn_80101820(&w);
        u.x = w.y * v.z - w.z * v.y;
        u.y = w.z * v.x - w.x * v.z;
        u.z = w.x * v.y - w.y * v.x;
        fn_80101820(&u);
        ((A *)p->f224)->s14(0, &v, &u, &w, 0);
        if (*p->f288) {

            ((A *)p->f224)->s13(&t, 0, 0, 0, 0);
            if (t.z <= *p->f292) fn_802494A4(p, 4);
        }
    } else if (st == 5) {
        ((A *)p->f224)->s24();
    }
end:
    fn_8023FE08(p, dt);
}

} /* extern "C" */
