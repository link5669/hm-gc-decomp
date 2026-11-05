// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {
extern u8 lbl_80362AE8[];
extern u8 lbl_80362AF0[];
extern u8 lbl_80362AF4[];
extern u8 lbl_80362AFC[];
extern u8 lbl_80362B04[];
extern u8 lbl_80362B0C[];
extern u8 lbl_80362B14[];
extern u8 lbl_80362B1C[];
extern u8 lbl_80362B24[];
void fn_800AF998(void);
void fn_80249AC4(void);
void fn_800AF978(void);
void fn_80242210(void);
void fn_800AF958(void);
void fn_8023D198(void);
void fn_800AFB2C(void);
void fn_800AF76C(u8 *p, s32 n);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_8023FE08(void);
void fn_800AF880(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_8023F5F4(void);
void fn_800AF8EC(void);

/* QV=2.0p1 */
__declspec(section ".data") u8 lbl_802D55C8[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[5] = { (void *)lbl_80362AE8, (void *)lbl_80362AE8, (void *)lbl_80362AF0, (void *)lbl_80362AF0, (void *)lbl_80362AF0 };
static __declspec(section ".data") u8 sPad_230[12] = { 0x40, 0xA0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_23C[1] = { (void *)lbl_80362AF4 };
static __declspec(section ".data") u8 sPad_240[12] = { 0x40, 0xA0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_24C[1] = { (void *)lbl_80362AFC };
static __declspec(section ".data") u8 sPad_250[12] = { 0x40, 0x40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_25C[9] = { (void *)lbl_80362B04, (void *)lbl_80362B0C, (void *)lbl_80362B14, (void *)lbl_80362AF4, (void *)lbl_80362B1C, (void *)lbl_80362AFC, (void *)lbl_80362B24, (void *)lbl_80362B04, (void *)lbl_80362B0C };
static __declspec(section ".data") u8 sPad_280[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_288[1] = { (void *)lbl_80362B14 };
static __declspec(section ".data") u8 sPad_28C[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_294[1] = { (void *)lbl_80362AF4 };
static __declspec(section ".data") u8 sPad_298[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2A0[1] = { (void *)lbl_80362B1C };
static __declspec(section ".data") u8 sPad_2A4[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2AC[1] = { (void *)lbl_80362AFC };
static __declspec(section ".data") u8 sPad_2B0[8] = { 0, 0, 0, 4, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2B8[1] = { (void *)lbl_80362B24 };
static __declspec(section ".data") u8 sPad_2BC[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2C4[1] = { (void *)lbl_80362B04 };
static __declspec(section ".data") u8 sPad_2C8[36] = { 0, 0, 0, 6, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6 };
static __declspec(section ".data") s32 tA[7] = { 0, 1, 2, 3, 4, 5, 6 };
static __declspec(section ".data") s32 tB[7] = { 1, 1, 1, 1, 1, 1, 1 };
static __declspec(section ".data") s32 tC[7] = { 0, 1, 2, 3, 4, 5, 6 };
__declspec(section ".data") u8 lbl_802D5908[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802D5910[18] = { (void *)fn_800AF998, (void *)fn_80249AC4, (void *)fn_800AF978, (void *)fn_80242210, (void *)fn_800AF958, (void *)fn_8023D198, (void *)fn_800AFB2C, (void *)fn_800AF76C, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_8023FE08, (void *)fn_800AF880, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_8023F5F4, (void *)fn_800AF8EC };
extern void *lbl_8035B79C;
void fn_80241628(u8 *p, s32 a, s32 b);
void fn_802491DC(u8 *p, s32 a);
void fn_8026820C(void *a, s32 b);
void fn_80268178(void *a, s32 b);

void fn_800AF76C(u8 *p, s32 n) {
    s32 *q;
    s32 i;
    s32 t;
    t = *(s32 *)(p + 96);
    i = tA[n];
    for (q = tB + i; t > 0; q++) {
        if (*q > t) break;
        t -= tB[i++];
    }
    switch (tC[i]) {
    case 0:
        fn_80241628(p, 0, 0);
        break;
    case 1:
        fn_802491DC(p, 0);
        break;
    case 2:
        fn_8026820C(lbl_8035B79C, 7);
        break;
    case 3:
        fn_802491DC(p, 1);
        fn_80268178(lbl_8035B79C, 7);
        break;
    case 4:
        fn_8026820C(lbl_8035B79C, 8);
        break;
    case 5:
        fn_802491DC(p, 2);
        fn_80268178(lbl_8035B79C, 8);
        break;
    case 6:
        fn_8026820C(lbl_8035B79C, 9);
        break;
    case 7:
        break;
    }
}

} /* extern "C" */
