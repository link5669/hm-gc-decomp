#include "common.h"
extern "C" {
extern u8 lbl_80299A90[];
extern u8 lbl_80360DB0[];
extern u8 lbl_80360DB8[];
extern u8 lbl_80360DC0[];
extern char lbl_80360DC8[8], lbl_80360EC0[8], lbl_80360EC8[8], lbl_80360ED0[8], lbl_80360ED8[8], lbl_80360EE0[8], lbl_80360EE8[8], lbl_80360EF0[8], lbl_80360EF8[8], lbl_80360F00[8], lbl_80360F08[8];
extern u8 lbl_80360DCC[];
extern u8 lbl_80360DD4[];
extern u8 lbl_80360DDC[];
extern u8 lbl_80360DE4[];
extern u8 lbl_80360DEC[];
extern u8 lbl_80360DF4[];
extern u8 lbl_80360DFC[];
extern u8 lbl_80360E04[];
extern u8 lbl_80360E0C[];
extern u8 lbl_80360E14[];
extern u8 lbl_80299A9C[];
extern u8 lbl_80299AA8[];
extern u8 lbl_80299AB4[];
extern u8 lbl_80360E1C[];
extern u8 lbl_80360E24[];
extern u8 lbl_80299AC0[];
extern u8 lbl_80360E2C[];
extern u8 lbl_80360E34[];
extern u8 lbl_80360E3C[];
extern u8 lbl_80299ACC[];
extern u8 lbl_80299AD8[];
extern u8 lbl_80299AE4[];
extern u8 lbl_80299AF0[];
extern u8 lbl_80360E44[];
extern u8 lbl_80360E4C[];
extern u8 lbl_80360E54[];
extern u8 lbl_80299AFC[];
extern u8 lbl_80360E5C[];
extern u8 lbl_80360E64[];
extern u8 lbl_80360E6C[];
extern u8 lbl_80360E74[];
extern u8 lbl_80360E7C[];
extern u8 lbl_80360E84[];
extern u8 lbl_80360E8C[];
extern u8 lbl_80360E94[];
extern u8 lbl_80360E9C[];
extern u8 lbl_80360EA4[];
extern u8 lbl_80360EAC[];
void fn_8009479C(void);
void fn_80249AC4(void);
void fn_800945E0(void);
void fn_80094368(void);
void fn_80094418(void);
void fn_8023D198(void);
void fn_800948A8(void);
class O;
void fn_80093A70(O *o, s32 idx);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_800942C4(void);
void fn_8009417C(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_800948B0(void);
void fn_80094220(void);

struct G72 { u8 p[72]; void *f72; };
class O { public: u8 p0[96]; s32 f96; u8 p100[120]; s32 f220; void *f224; u8 p228[8]; s32 f236; void *f240; u8 p244[40]; s32 *f284; s32 *f288; u8 p292[12];
    char *f304; void *f308; u32 *f312; u32 f316; u32 f320; s32 f324; s32 *f328; s32 *f332; f32 *f336; f32 *f340; f32 *f344; s32 f348; u32 f352; f32 f356;
    s32 f360; s32 f364; s32 f368; s32 f372; };
__declspec(section ".data") u8 lbl_802CAF48[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[38] = { (void *)lbl_80299A90, (void *)lbl_80360DB0, (void *)lbl_80360DB8, (void *)lbl_80360DC0, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DCC, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DD4, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DDC, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DE4, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DEC, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DF4, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DFC, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360E04, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360E0C, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360E14, (void *)lbl_80360E14, (void *)lbl_80360DC8, (void *)lbl_80360DC8, (void *)lbl_80360DC8 };
static __declspec(section ".data") u8 sPad_2B4[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2C0[1] = { (void *)lbl_80299A9C };
static __declspec(section ".data") u8 sPad_2C4[12] = { 0x40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2D0[1] = { (void *)lbl_80299AA8 };
static __declspec(section ".data") u8 sPad_2D4[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2E0[31] = { (void *)lbl_80299AB4, (void *)lbl_80360E1C, (void *)lbl_80360E24, (void *)lbl_80299AC0, (void *)lbl_80360E2C, (void *)lbl_80360E34, (void *)lbl_80360E1C, (void *)lbl_80360E3C, (void *)lbl_80299ACC, (void *)lbl_80299AD8, (void *)lbl_80299AE4, (void *)lbl_80299AF0, (void *)lbl_80299AA8, (void *)lbl_80299AB4, (void *)lbl_80360E44, (void *)lbl_80360E4C, (void *)lbl_80360E54, (void *)lbl_80299AFC, (void *)lbl_80360E5C, (void *)lbl_80360E64, (void *)lbl_80360E6C, (void *)lbl_80360E74, (void *)lbl_80360E7C, (void *)lbl_80360E84, (void *)lbl_80360E8C, (void *)lbl_80360E94, (void *)lbl_80360E9C, (void *)lbl_80360EA4, (void *)lbl_80360EAC, (void *)lbl_80299A9C, (void *)lbl_80360E1C };
static __declspec(section ".data") u8 sPad_35C[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_364[1] = { (void *)lbl_80360E3C };
static __declspec(section ".data") u8 sPad_368[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_370[1] = { (void *)lbl_80299ACC };
static __declspec(section ".data") u8 sPad_374[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_37C[1] = { (void *)lbl_80299AD8 };
static __declspec(section ".data") u8 sPad_380[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_388[1] = { (void *)lbl_80299AE4 };
static __declspec(section ".data") u8 sPad_38C[8] = { 0, 0, 0, 4, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_394[1] = { (void *)lbl_80299AF0 };
static __declspec(section ".data") u8 sPad_398[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3A0[1] = { (void *)lbl_80299AA8 };
static __declspec(section ".data") u8 sPad_3A4[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3AC[1] = { (void *)lbl_80299AB4 };
static __declspec(section ".data") u8 sPad_3B0[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3B8[1] = { (void *)lbl_80360E44 };
static __declspec(section ".data") u8 sPad_3BC[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3C4[1] = { (void *)lbl_80360E4C };
static __declspec(section ".data") u8 sPad_3C8[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3D0[1] = { (void *)lbl_80360E54 };
static __declspec(section ".data") u8 sPad_3D4[8] = { 0, 0, 0, 0xA, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3DC[1] = { (void *)lbl_80299AFC };
static __declspec(section ".data") u8 sPad_3E0[8] = { 0, 0, 0, 0xB, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3E8[1] = { (void *)lbl_80360E5C };
static __declspec(section ".data") u8 sPad_3EC[8] = { 0, 0, 0, 0xC, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3F4[1] = { (void *)lbl_80360E64 };
static __declspec(section ".data") u8 sPad_3F8[8] = { 0, 0, 0, 0xD, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_400[1] = { (void *)lbl_80360E6C };
static __declspec(section ".data") u8 sPad_404[8] = { 0, 0, 0, 0xE, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_40C[1] = { (void *)lbl_80360E74 };
static __declspec(section ".data") u8 sPad_410[8] = { 0, 0, 0, 0xF, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_418[1] = { (void *)lbl_80360E7C };
static __declspec(section ".data") u8 sPad_41C[8] = { 0, 0, 0, 0x10, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_424[1] = { (void *)lbl_80360E84 };
static __declspec(section ".data") u8 sPad_428[8] = { 0, 0, 0, 0x11, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_430[1] = { (void *)lbl_80360E8C };
static __declspec(section ".data") u8 sPad_434[8] = { 0, 0, 0, 0x12, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_43C[1] = { (void *)lbl_80360E94 };
static __declspec(section ".data") u8 sPad_440[8] = { 0, 0, 0, 0x13, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_448[1] = { (void *)lbl_80360E9C };
static __declspec(section ".data") u8 sPad_44C[8] = { 0, 0, 0, 0x14, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_454[1] = { (void *)lbl_80360EA4 };
static __declspec(section ".data") u8 sPad_458[8] = { 0, 0, 0, 0x15, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_460[1] = { (void *)lbl_80360EAC };
static __declspec(section ".data") u8 sPad_464[8] = { 0, 0, 0, 0x16, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_46C[1] = { (void *)lbl_80299A9C };
static __declspec(section ".data") u8 sPad_470[104] = { 0, 0, 0, 0x17, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 0, 0xA, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0xD, 0, 0, 0, 0xE, 0, 0, 0, 0xF, 0, 0, 0, 0x10, 0, 0, 0, 0x11, 0, 0, 0, 0x12, 0, 0, 0, 0x13, 0, 0, 0, 0x14, 0, 0, 0, 0x15, 0, 0, 0, 0x16, 0, 0, 0, 0x17 };
static __declspec(section ".data") s32 tI[24] = { 0, 5, 8, 0xA, 0xD, 0x10, 0x11, 0x14, 0x17, 0x18, 0x19, 0x1B, 0x1E, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32, 0x34 };
static __declspec(section ".data") s32 tB[54] = { 1, 1, 1, 1, 1, 3, 1, 1, 4, 1, 1, 1, 3, 1, 1, 3, 5, 3, 1, 1, 3, 1, 1, 5, 5, 4, 1, 3, 1, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 4, 1, 2, 3 };
static __declspec(section ".data") s32 tS[54] = { 0, 1, 2, 3, 4, 5, 6, 5, 5, 7, 5, 8, 5, 5, 9, 5, 0xA, 5, 0xB, 5, 5, 0xC, 5, 0xD, 0xE, 0xF, 5, 0xF, 0x10, 5, 0x11, 5, 0x12, 5, 0x13, 5, 0x14, 5, 0x15, 5, 0x16, 5, 0x17, 5, 0x18, 5, 0x19, 5, 0x1A, 5, 0x1B, 5, 5, 0x1C };
__declspec(section ".data") u8 lbl_802CB630[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802CB638[18] = { (void *)fn_8009479C, (void *)fn_80249AC4, (void *)fn_800945E0, (void *)fn_80094368, (void *)fn_80094418, (void *)fn_8023D198, (void *)fn_800948A8, (void *)fn_80093A70, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_800942C4, (void *)fn_8009417C, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_800948B0, (void *)fn_80094220 };
extern "C" {
extern G72 *lbl_8035B308;
extern void *volatile lbl_8035A0A4;
extern void *lbl_8035B65C;
extern f32 lbl_80360EB4, lbl_80360EB8, lbl_80360EBC;
extern char lbl_80360DC8[8], lbl_80360EC0[8], lbl_80360EC8[8], lbl_80360ED0[8], lbl_80360ED8[8], lbl_80360EE0[8], lbl_80360EE8[8], lbl_80360EF0[8], lbl_80360EF8[8], lbl_80360F00[8], lbl_80360F08[8];
extern char lbl_80299B08[];
int rand(void);
void fn_80241628(O *, int, int);
void fn_8003C778(void *, void *, u32 **);
void fn_8022BF30(void *, s32, int, f32);
void fn_802494A4(O *, int);
void fn_802402E0(O *);
void fn_80072438(void *, s32);
void fn_8022D6FC(void *);
void fn_80241588(O *, int, int, f32);
int fn_800F6CD0(char *, char *);
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
void fn_80240274(O *, int);
int fn_8003C674(void *, char *, s32 **);
void fn_802490E0(O *, int, f32);
void fn_80240948(O *, char *, int);
void fn_802413D8(O *, void *, int, int, f32, s32);
}
inline void Ev(O *o, char *s) {
    fn_802494A4(o, 3);
    fn_80240274(o, 0);
    fn_80240948(o, s, 0);
}
extern "C" void fn_80093A70(O *o, s32 idx) {
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
        if (o->f328) o->f348 = *o->f328;
        if (o->f332) o->f352 = *o->f332;
        if (o->f336) o->f356 = *o->f336;
        o->f308 = lbl_8035B308->f72;
        fn_8003C778(lbl_8035A0A4, o->f224, &o->f312);
        fn_8022BF30(o->f224, o->f348, 0, lbl_80360EB4);
        if (!(*o->f312 & o->f316)) fn_802494A4(o, 1);
        else fn_802494A4(o, 4);
        break;
    case 1: fn_802402E0(o); break;
    case 2:
        *o->f312 |= o->f316;
        *o->f312 |= o->f320;
        fn_80072438(o->f308, *o->f284);
        o->f368 = 0;
        break;
    case 3:
        fn_80241628(o, 1, 0);
        o->f360 = 1;
        break;
    case 4:
        fn_80241628(o, 0, 0);
        fn_8022D6FC(o->f224);
        fn_80241588(o, 7, 0, lbl_80360EB8);
        if (o->f304 && !fn_800F6CD0(o->f304, lbl_80360DC8)) __ct__9C80253F24Fiiii(lbl_8035B65C, o->f304, 0, 0, 0);
        break;
    case 5: return;
    case 6:
        fn_8022BF30(o->f224, o->f348, 1, lbl_80360EB4);
        o->f360 = 0;
        break;
    case 7:
        if (o->f220 != 7) {
            fn_80241588(o, 7, 0, lbl_80360EB8);
        } else if ((s32)((u32)rand() % 10) < 3) {
            if (rand() & 1) fn_80241588(o, 8, 0, lbl_80360EB8);
            else fn_80241588(o, 9, 0, lbl_80360EB8);
        } else {
            fn_80241588(o, 7, 0, lbl_80360EB8);
        }
        break;
    case 8:
        o->f364 = o->f368 = 1;
        break;
    case 9:
        fn_80240274(o, 0);
        fn_802494A4(o, 2);
        break;
    case 10:
        if (o->f364) {
            s32 *volatile p = 0;
            if (!fn_8003C674(lbl_8035A0A4, lbl_80299B08, (s32 **)&p)) *p = 0;
            { s32 *q = p; *q = *q + *o->f288; }
            o->f364 = 0;
        }
        if (o->f368) {
            fn_80072438(o->f308, *o->f284);
            o->f368 = 0;
        }
        break;
    case 11: {
        f32 f = *o->f344;
        fn_8022BF30(o->f224, 0, 1, lbl_80360EB4);
        fn_8022BF30(o->f224, o->f348, 1, f);
        fn_802490E0(o, 2, *o->f344);
        break;
    }
    case 12: fn_802490E0(o, 0, lbl_80360EBC); break;
    case 13: o->f372 = 1; break;
    case 14: o->f372 = 0; break;
    case 15:
        fn_802494A4(o, 3);
        fn_802402E0(o);
        break;
    case 16:
        fn_8022BF30(o->f224, o->f348, 1, lbl_80360EB4);
        fn_802494A4(o, 4);
        break;
    case 17: Ev(o, lbl_80360EC0); break;
    case 18: Ev(o, lbl_80360EC8); break;
    case 19: Ev(o, lbl_80360ED0); break;
    case 20: Ev(o, lbl_80360ED8); break;
    case 21: Ev(o, lbl_80360EE0); break;
    case 22: Ev(o, lbl_80360EE8); break;
    case 23: Ev(o, lbl_80360EF0); break;
    case 24: Ev(o, lbl_80360EF8); break;
    case 25: Ev(o, lbl_80360F00); break;
    case 26: Ev(o, lbl_80360F08); break;
    case 27:
        if (o->f240) {
            fn_802413D8(o, o->f240, 0, 1, lbl_80360EB8, o->f236);
            if (o->f360) {
                o->f360 = 0;
                fn_8022BF30(o->f224, 0, 1, lbl_80360EB4);
                fn_802490E0(o, 1, *o->f340);
            }
        }
        break;
    case 28: {
        s32 s = 1;
        u32 r, n;
        if (o->f324 >= o->f348) s = -1;
        n = o->f352;
        r = 0;
        if (n) r = rand() % n;
        fn_8022BF30(o->f224, o->f324, 1, lbl_80360EB4);
        o->f324 = o->f348 + s * r;
        fn_8022BF30(o->f224, o->f324, 0, o->f356);
        fn_802490E0(o, 0, o->f356);
        break;
    }
    case 29: break;
    }
}
}
