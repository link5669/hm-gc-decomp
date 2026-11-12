#include "common.h"
extern "C" {
extern u8 lbl_80295E70[];
extern u8 lbl_8035D3E8[];
extern u8 lbl_8035D3F0[];
extern u8 lbl_8035D3F8[];
extern u8 lbl_8035D400[];
extern u8 lbl_8035D408[];
extern u8 lbl_8035D410[];
extern u8 lbl_8035D418[];
extern u8 lbl_8035D41C[];
extern u8 lbl_80295E7C[];
extern u8 lbl_8035D424[];
extern u8 lbl_8035D42C[];
extern u8 lbl_8035D434[];
extern u8 lbl_8035D43C[];
extern u8 lbl_8035D444[];
extern u8 lbl_8035D44C[];
extern u8 lbl_8035D454[];
extern u8 lbl_8035D45C[];
extern u8 lbl_8035D464[];
extern u8 lbl_8035D46C[];
extern u8 lbl_8035D474[];
extern u8 lbl_8035D47C[];
extern u8 lbl_8035D484[];
extern s8 lbl_8035D48C[1];
extern u8 lbl_8035D490[];
extern u8 lbl_8035D498[];
extern u8 lbl_80295E88[];
extern u8 lbl_8035D4A0[];
extern u8 lbl_80295E94[];
extern u8 lbl_80295EA0[];
extern u8 lbl_8035D4A8[];
extern u8 lbl_8035D4B0[];
extern u8 lbl_80295EAC[];
extern u8 lbl_80295EB8[];
extern u8 lbl_8035D4B8[];
extern u8 lbl_80295EC4[];
extern u8 lbl_80295ED0[];
extern u8 lbl_80295EDC[];
extern u8 lbl_80295EE8[];
extern u8 lbl_8035D4C8[];
extern u8 lbl_8035D4D0[];
extern u8 lbl_8035D4D8[];
extern u8 lbl_8035D4E0[];
extern u8 lbl_8035D4E8[];
extern u8 lbl_8035D4F0[];
extern u8 lbl_8035D4F8[];
extern u8 lbl_8035D500[];
extern u8 lbl_8035D508[];
extern u8 lbl_8035D510[];
extern u8 lbl_8035D518[];
extern u8 lbl_8035D520[];
extern u8 lbl_80295EF4[];
extern u8 lbl_8035D528[];
extern u8 lbl_8035D530[];
extern u8 lbl_80295F00[];
extern u8 lbl_80295F0C[];
extern u8 lbl_80295F18[];
extern u8 lbl_8035D538[];
extern u8 lbl_8035D540[];
extern u8 lbl_80295F24[];
extern u8 lbl_80295F30[];
extern u8 lbl_80295F3C[];
extern u8 lbl_8035D548[];
extern u8 lbl_80295F48[];
extern u8 lbl_8035D550[];
extern u8 lbl_8035D558[];
extern u8 lbl_8035D560[];
extern u8 lbl_8035D568[];
extern u8 lbl_8035D570[];
extern u8 lbl_8035D578[];
extern u8 lbl_8035D580[];
extern u8 lbl_8035D588[];
extern u8 lbl_8035D590[];
extern u8 lbl_8035D598[];
extern u8 lbl_8035D5A0[];
extern u8 lbl_8035D5A8[];
extern u8 lbl_8035D5B0[];
extern u8 lbl_8035D5B8[];
extern u8 lbl_8035D5C0[];
void fn_8004DB2C(void);
void fn_80249AC4(void);
void fn_8004D9B0(void);
void fn_80242210(void);
void fn_8004D804(void);
void fn_8023D198(void);
void fn_8004DC38(void);
void fn_8004C4FC(int p, int st);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_8023FE08(void);
void fn_8004D6EC(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_8004DCC0(void);
void fn_8004D778(void);
struct VO { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void getPos(void *p, void *a, int b, int c, int d); virtual void setPos(void *a, void *b, void *c, void *d, int e); virtual void w15(); virtual void w16(); virtual void hideA(); virtual void w18(); virtual void showA(); virtual void vanish(); virtual void w21(); virtual void w22(); virtual void w23(); virtual void w24(); virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void send(void *msg, u32 to, int a, void *d, int b); };
__declspec(section ".data") u8 lbl_802B6D48[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[27] = { (void *)lbl_80295E70, (void *)lbl_8035D3E8, (void *)lbl_8035D3F0, (void *)lbl_8035D3F8, (void *)lbl_8035D400, (void *)lbl_8035D408, (void *)lbl_8035D410, (void *)lbl_8035D418, (void *)lbl_8035D408, (void *)lbl_8035D410, (void *)lbl_8035D41C, (void *)lbl_8035D408, (void *)lbl_80295E7C, (void *)lbl_8035D424, (void *)lbl_8035D408, (void *)lbl_8035D42C, (void *)lbl_8035D434, (void *)lbl_8035D408, (void *)lbl_8035D43C, (void *)lbl_8035D444, (void *)lbl_8035D408, (void *)lbl_8035D44C, (void *)lbl_8035D454, (void *)lbl_8035D408, (void *)lbl_8035D45C, (void *)lbl_8035D400, (void *)lbl_8035D410 };
static __declspec(section ".data") u8 sPad_288[4] = { 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_28C[2] = { (void *)lbl_8035D464, (void *)lbl_8035D46C };
static __declspec(section ".data") u8 sPad_294[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_298[2] = { (void *)lbl_8035D474, (void *)lbl_8035D47C };
static __declspec(section ".data") u8 sPad_2A0[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2A4[36] = { (void *)lbl_8035D484, (void *)lbl_8035D484, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D490, (void *)lbl_8035D498, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D490, (void *)lbl_80295E88, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D4A0, (void *)lbl_80295E94, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D4A0, (void *)lbl_80295EA0, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D4A8, (void *)lbl_8035D4B0, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D4A8, (void *)lbl_80295EAC, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D4A8, (void *)lbl_80295EB8, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D4B8, (void *)lbl_8035D48C, (void *)lbl_8035D48C, (void *)lbl_8035D48C };
static __declspec(section ".data") u8 sPad_334[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_340[1] = { (void *)lbl_80295EC4 };
static __declspec(section ".data") u8 sPad_344[12] = { 0x40, 0x40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_350[1] = { (void *)lbl_8035D464 };
static __declspec(section ".data") u8 sPad_354[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_360[1] = { (void *)lbl_80295ED0 };
static __declspec(section ".data") u8 sPad_364[12] = { 0x40, 0xA0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_370[1] = { (void *)lbl_80295EDC };
static __declspec(section ".data") u8 sPad_374[12] = { 0x3F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_380[1] = { (void *)lbl_80295EE8 };
static __declspec(section ".data") u8 sPad_384[12] = { 0x40, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_390[1] = { (void *)lbl_8035D4C8 };
static __declspec(section ".data") u8 sPad_394[12] = { 0x3C, 0x23, 0xD7, 0xA, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_3A0[2] = { (void *)lbl_8035D4D0, (void *)lbl_8035D4D8 };
static __declspec(section ".data") u8 sPad_3A8[16] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_3B8[53] = { (void *)lbl_8035D4E0, (void *)lbl_8035D4E8, (void *)lbl_8035D4F0, (void *)lbl_8035D4F8, (void *)lbl_8035D500, (void *)lbl_8035D48C, (void *)lbl_8035D508, (void *)lbl_8035D510, (void *)lbl_8035D41C, (void *)lbl_8035D518, (void *)lbl_8035D520, (void *)lbl_80295EF4, (void *)lbl_8035D528, (void *)lbl_8035D4E0, (void *)lbl_8035D530, (void *)lbl_80295F00, (void *)lbl_80295F0C, (void *)lbl_80295F18, (void *)lbl_8035D538, (void *)lbl_80295F18, (void *)lbl_80295F18, (void *)lbl_80295F18, (void *)lbl_8035D540, (void *)lbl_8035D508, (void *)lbl_8035D4C8, (void *)lbl_80295F24, (void *)lbl_8035D464, (void *)lbl_80295ED0, (void *)lbl_8035D4F8, (void *)lbl_80295EC4, (void *)lbl_80295EDC, (void *)lbl_80295EE8, (void *)lbl_8035D4D0, (void *)lbl_80295F30, (void *)lbl_80295F3C, (void *)lbl_8035D548, (void *)lbl_80295F48, (void *)lbl_8035D550, (void *)lbl_8035D558, (void *)lbl_8035D560, (void *)lbl_8035D568, (void *)lbl_8035D570, (void *)lbl_8035D578, (void *)lbl_8035D580, (void *)lbl_8035D588, (void *)lbl_8035D590, (void *)lbl_8035D598, (void *)lbl_8035D5A0, (void *)lbl_8035D5A8, (void *)lbl_8035D5B0, (void *)lbl_8035D5B8, (void *)lbl_8035D5C0, (void *)lbl_8035D4E0 };
static __declspec(section ".data") u8 sPad_48C[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_494[1] = { (void *)lbl_8035D530 };
static __declspec(section ".data") u8 sPad_498[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4A0[1] = { (void *)lbl_80295F00 };
static __declspec(section ".data") u8 sPad_4A4[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4AC[1] = { (void *)lbl_80295F0C };
static __declspec(section ".data") u8 sPad_4B0[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4B8[1] = { (void *)lbl_80295F18 };
static __declspec(section ".data") u8 sPad_4BC[8] = { 0, 0, 0, 4, 0, 0, 0, 4 };
static __declspec(section ".data") void *sPad_4C4[1] = { (void *)lbl_8035D538 };
static __declspec(section ".data") u8 sPad_4C8[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4D0[1] = { (void *)lbl_8035D540 };
static __declspec(section ".data") u8 sPad_4D4[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4DC[1] = { (void *)lbl_8035D508 };
static __declspec(section ".data") u8 sPad_4E0[8] = { 0, 0, 0, 0xA, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4E8[1] = { (void *)lbl_8035D4C8 };
static __declspec(section ".data") u8 sPad_4EC[8] = { 0, 0, 0, 0xB, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_4F4[1] = { (void *)lbl_80295F24 };
static __declspec(section ".data") u8 sPad_4F8[8] = { 0, 0, 0, 0xC, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_500[1] = { (void *)lbl_8035D464 };
static __declspec(section ".data") u8 sPad_504[8] = { 0, 0, 0, 0xD, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_50C[1] = { (void *)lbl_80295ED0 };
static __declspec(section ".data") u8 sPad_510[8] = { 0, 0, 0, 0xE, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_518[1] = { (void *)lbl_8035D4F8 };
static __declspec(section ".data") u8 sPad_51C[8] = { 0, 0, 0, 0xF, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_524[1] = { (void *)lbl_80295EC4 };
static __declspec(section ".data") u8 sPad_528[8] = { 0, 0, 0, 0x10, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_530[1] = { (void *)lbl_80295EDC };
static __declspec(section ".data") u8 sPad_534[8] = { 0, 0, 0, 0x11, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_53C[1] = { (void *)lbl_80295EE8 };
static __declspec(section ".data") u8 sPad_540[8] = { 0, 0, 0, 0x12, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_548[1] = { (void *)lbl_8035D4D0 };
static __declspec(section ".data") u8 sPad_54C[8] = { 0, 0, 0, 0x13, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_554[1] = { (void *)lbl_80295F30 };
static __declspec(section ".data") u8 sPad_558[8] = { 0, 0, 0, 0x14, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_560[1] = { (void *)lbl_80295F3C };
static __declspec(section ".data") u8 sPad_564[8] = { 0, 0, 0, 0x15, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_56C[1] = { (void *)lbl_8035D548 };
static __declspec(section ".data") u8 sPad_570[8] = { 0, 0, 0, 0x16, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_578[1] = { (void *)lbl_80295F48 };
static __declspec(section ".data") u8 sPad_57C[8] = { 0, 0, 0, 0x17, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_584[1] = { (void *)lbl_8035D550 };
static __declspec(section ".data") u8 sPad_588[8] = { 0, 0, 0, 0x18, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_590[1] = { (void *)lbl_8035D558 };
static __declspec(section ".data") u8 sPad_594[8] = { 0, 0, 0, 0x19, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_59C[1] = { (void *)lbl_8035D560 };
static __declspec(section ".data") u8 sPad_5A0[8] = { 0, 0, 0, 0x1A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5A8[1] = { (void *)lbl_8035D568 };
static __declspec(section ".data") u8 sPad_5AC[8] = { 0, 0, 0, 0x1B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5B4[1] = { (void *)lbl_8035D570 };
static __declspec(section ".data") u8 sPad_5B8[8] = { 0, 0, 0, 0x1C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5C0[1] = { (void *)lbl_8035D578 };
static __declspec(section ".data") u8 sPad_5C4[8] = { 0, 0, 0, 0x1D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5CC[1] = { (void *)lbl_8035D580 };
static __declspec(section ".data") u8 sPad_5D0[8] = { 0, 0, 0, 0x1E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5D8[1] = { (void *)lbl_8035D588 };
static __declspec(section ".data") u8 sPad_5DC[8] = { 0, 0, 0, 0x1F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5E4[1] = { (void *)lbl_8035D590 };
static __declspec(section ".data") u8 sPad_5E8[8] = { 0, 0, 0, 0x20, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5F0[1] = { (void *)lbl_8035D598 };
static __declspec(section ".data") u8 sPad_5F4[8] = { 0, 0, 0, 0x21, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_5FC[1] = { (void *)lbl_8035D5A0 };
static __declspec(section ".data") u8 sPad_600[8] = { 0, 0, 0, 0x22, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_608[1] = { (void *)lbl_8035D5A8 };
static __declspec(section ".data") u8 sPad_60C[8] = { 0, 0, 0, 0x23, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_614[1] = { (void *)lbl_8035D5B0 };
static __declspec(section ".data") u8 sPad_618[8] = { 0, 0, 0, 0x24, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_620[1] = { (void *)lbl_8035D5B8 };
static __declspec(section ".data") u8 sPad_624[8] = { 0, 0, 0, 0x25, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_62C[1] = { (void *)lbl_8035D5C0 };
static __declspec(section ".data") u8 sPad_630[164] = { 0, 0, 0, 0x26, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 5, 0, 0, 0, 9, 0, 0, 0, 0xA, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0xD, 0, 0, 0, 0xE, 0, 0, 0, 0xF, 0, 0, 0, 0x10, 0, 0, 0, 0x11, 0, 0, 0, 0x12, 0, 0, 0, 0x13, 0, 0, 0, 0x14, 0, 0, 0, 0x15, 0, 0, 0, 0x16, 0, 0, 0, 0x17, 0, 0, 0, 0x18, 0, 0, 0, 0x19, 0, 0, 0, 0x1A, 0, 0, 0, 0x1B, 0, 0, 0, 0x1C, 0, 0, 0, 0x1D, 0, 0, 0, 0x1E, 0, 0, 0, 0x1F, 0, 0, 0, 0x20, 0, 0, 0, 0x21, 0, 0, 0, 0x22, 0, 0, 0, 0x23, 0, 0, 0, 0x24, 0, 0, 0, 0x25, 0, 0, 0, 0x26 };
static __declspec(section ".data") s32 tA[39] = { 0, 0xD, 0x17, 0x21, 0x22, 0x27, 0x28, 0x31, 0x3A, 0x43, 0x49, 0x4F, 0x52, 0x55, 0x58, 0x61, 0x64, 0x67, 0x6A, 0x6B, 0x6D, 0x74, 0x78, 0x7B, 0x7E, 0x81, 0x84, 0x87, 0x8A, 0x8D, 0x90, 0x93, 0x96, 0x99, 0x9C, 0x9F, 0xA2, 0xA4, 0xAA };
static __declspec(section ".data") s32 tB[176] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 2, 1, 1, 1, 3, 1, 1, 1, 1, 2, 1, 0xD, 1, 1, 6, 1, 4, 0xD, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 2, 1, 2, 6, 1, 2, 1, 1, 4, 2, 3, 1, 2, 5, 1, 7, 2, 1, 0xA, 3, 1, 9, 3, 1, 1, 2, 1, 2, 1, 1, 1, 0xA, 1, 2, 1, 1, 0xB, 2, 1, 0xA, 0xD, 1, 0xC, 1, 2, 2, 2, 1, 1, 4, 5, 2, 1, 5, 5, 1, 7, 5, 1, 7, 0xA, 1, 2, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 5, 1, 7, 1, 0xC, 1, 4, 1, 4, 1, 2, 1, 4, 1, 4, 1, 2 };
static __declspec(section ".data") s32 tC[176] = { 0, 1, 2, 3, 4, 5, 6, 3, 7, 8, 9, 0xA, 0xB, 5, 0xC, 5, 0xD, 0xE, 5, 0xE, 5, 0xF, 0xE, 5, 0x10, 0x11, 5, 0x12, 5, 0x13, 0x14, 5, 0x15, 5, 5, 0x16, 5, 0x17, 5, 5, 5, 0x18, 5, 0x18, 5, 0x18, 0x19, 5, 0x18, 5, 0x1A, 5, 0x1A, 5, 0x1A, 0x19, 5, 0x1A, 5, 0x1B, 5, 0x1B, 5, 0x1B, 0x19, 5, 0x1B, 5, 0x1C, 5, 0x1C, 5, 0x1C, 5, 0x1D, 5, 0x1D, 5, 0x1D, 0x1E, 5, 0x1E, 5, 0x1F, 5, 5, 0x20, 5, 5, 0x21, 0x16, 5, 0xF, 5, 0xF, 0x16, 0x22, 5, 0x23, 5, 5, 0x16, 5, 5, 0x14, 5, 5, 0x24, 5, 0x25, 0x26, 0x25, 5, 0x25, 0x26, 0x25, 0x27, 5, 0x28, 0x27, 0x29, 5, 0x29, 0xF, 5, 0xF, 5, 0x2A, 5, 0x2B, 5, 0x2B, 0x2C, 5, 0x2C, 0x2D, 5, 0x2D, 0x2E, 5, 0x2E, 0x2F, 5, 0x2F, 0x30, 5, 0x30, 0x31, 5, 0x31, 0x32, 5, 0x32, 0x33, 5, 0x33, 0x34, 5, 0x34, 0x35, 5, 0x35, 0x36, 5, 5, 0x37, 5, 0x37, 5, 0x37, 5, 0x38, 5, 0x38, 5, 0x38 };
__declspec(section ".data") u8 lbl_802B7A38[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802B7A40[18] = { (void *)fn_8004DB2C, (void *)fn_80249AC4, (void *)fn_8004D9B0, (void *)fn_80242210, (void *)fn_8004D804, (void *)fn_8023D198, (void *)fn_8004DC38, (void *)fn_8004C4FC, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_8023FE08, (void *)fn_8004D6EC, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_8004DCC0, (void *)fn_8004D778 };
typedef struct { f32 x, y, z; } V3;
extern u32 lbl_8035B308;
extern u8 *lbl_8035B460;
extern s8 lbl_8035D48C[1];
extern f32 lbl_8035D5C8, lbl_8035D5D8, lbl_8035D5E4, lbl_8035D5E8, lbl_8035D5EC, lbl_8035D5F0;
extern char lbl_8035D5CC[4], lbl_8035D5D0[7], lbl_8035D5DC[8], lbl_8035D5F4[7], lbl_8035D5FC[7];
extern char lbl_8035D604[8], lbl_8035D60C[8], lbl_8035D614[8], lbl_8035D61C[8];
extern char lbl_8035D624[5], lbl_8035D62C[5], lbl_8035D634[5], lbl_8035D63C[5], lbl_8035D644[5], lbl_8035D64C[5];
void *fn_800F9398(void *, void *);
void *fn_800F9788(void *, void *, void *);
int fn_800F6CD0(void *, void *);
int fn_80237934(int, V3 *, int, int, void *);
void fn_80257A84(int, f32);
void fn_80240DBC(int, f32);
void fn_8022BCD8(int, void *, void *);
int fn_8022BE28(int, int);
void fn_8022BF30(int, int, int, f32);
int fn_80236AC0(int);
int fn_80236B14(int);
int fn_8023F5E8(int, int);
void fn_8023F864(int, int);
void fn_8023F9C8(int, int);
int fn_802401A0(int);
int fn_802401D0(int);
int fn_802402E0(int);
int fn_802405B8(int);
void fn_8024125C(int, int);
void fn_80240274(int, int);
void fn_80240948(int, char *, int);
void fn_802413D8(int, int, f32, int, int, int);
void fn_80241588(int, int, int, f32);
int fn_80241628(int, int, int);
void *fn_80242144(int, int);
void fn_80242BC0(void *, void *, u32, int, u32, int);
int fn_80249058(int, int);
int fn_8024909C(int, int);
void fn_802490E0(int, int, f32);
int fn_802494A4(int, int);

#define E0 (*(VO **)(p + 0xe0))

static inline void *FindRes(u8 *mgr, s8 *grp, void *name) {
    if (grp == 0 || grp[0] == 0) return fn_800F9398(mgr + 0x180, name);
    return fn_800F9788(mgr + 0x198, grp, name);
}
static inline void reaper(int p) {
    fn_8022BCD8(*(int *)(p + 0xe0), lbl_8035D5DC, lbl_8035D48C);
    fn_8024125C(p, 2);
    fn_8022BF30(*(int *)(p + 0xe0), 0, 1, lbl_8035D5E4);
    fn_8022BF30(*(int *)(p + 0xe0), 0x7f, 1, lbl_8035D5E8);
    fn_802490E0(p, 2, lbl_8035D5EC);
    fn_8023F9C8(p, 0);
}
static inline void hit(int p, int a) {
    fn_802401D0(p);
    E0->setPos((void *)(p + 0x11c), 0, 0, 0, 0);
    fn_8023F5E8(p, *(int *)(p + 0x118));
    fn_80241628(p, 2, 0);
    fn_80241588(p, a, 0, lbl_8035D5D8);
    reaper(p);
}
static inline void walkPlayer(int p, char *name) {
    fn_802494A4(p, 10);
    fn_80240274(p, 0);
    fn_80240948(p, name, 0);
    reaper(p);
}

void fn_8004C4FC(int p, int st) {
    s32 *q;
    s32 idx;
    s32 t;
    int i;
    V3 f;
    char buf[12];
    V3 b;
    V3 a;
    f32 dmg;

    idx = tA[st];
    t = *(s32 *)(p + 0x60);
    for (q = tB + idx; t > 0; q++) {
        if (*q > t) break;
        t -= tB[idx++];
    }
    switch (tC[idx]) {
    case 0: {
        VO *e;
        *(f32 *)((int)E0 + 0x110) = lbl_8035D5C8;
        fn_8022BE28(*(int *)(p + 0xe0), 0);
        *(u32 *)(p + 0x118) = *(u32 *)(lbl_8035B308 + 0x48);
        E0->getPos((void *)(p + 0x11c), 0, 0, 0, 0);
        *(void **)(p + 0x15c) = FindRes(*(u8 **)(lbl_8035B460 + 8), lbl_8035D48C, lbl_8035D5CC);
        *(void **)(p + 0x160) = FindRes(*(u8 **)(lbl_8035B460 + 8), lbl_8035D48C, lbl_8035D5D0);
        fn_80241628(p, 0, 0);
        *(f32 *)(p + 0x17c) = *(f32 *)((int)E0 + 0x1ac);
        e = E0;
        if (*(int *)((int)e + 0x114) == 0 && **(int **)(p + 0x150) != 0) e->vanish();
        else e->vanish();
        break;
    }
    case 1:
        if (*(int *)(p + 0x16c) != 0) {
            fn_802494A4(p, 7);
        } else {
            fn_8023F5E8(p, *(int *)(p + 0x118));
            fn_80241628(p, 2, 0);
            fn_80241588(p, 0, 0, lbl_8035D5D8);
            fn_8024125C(p, 0);
            fn_802490E0(p, 0, **(f32 **)(p + 0x13c));
        }
        break;
    case 2:
        if (*(int *)(p + 0x16c) != 0) {
            fn_802494A4(p, 7);
        } else {
            fn_8023F5E8(p, *(int *)(p + 0x118));
            fn_80241628(p, 1, 0);
            fn_80241588(p, 1, 0, lbl_8035D5D8);
            fn_80257A84(*(int *)(*(int *)(p + 0xc0) + 4), **(f32 **)(p + 0x12c));
            fn_802490E0(p, 3, **(f32 **)(p + 0x144));
        }
        break;
    case 3:
        fn_802401A0(p);
        fn_80241628(p, 0, 0);
        fn_80241588(p, 0, 0, lbl_8035D5D8);
        fn_8022BCD8(*(int *)(p + 0xe0), lbl_8035D5DC, lbl_8035D48C);
        fn_8024125C(p, 1);
        fn_8022BF30(*(int *)(p + 0xe0), 0x7f, 1, lbl_8035D5E4);
        fn_8022BF30(*(int *)(p + 0xe0), 0, 0, lbl_8035D5E8);
        fn_802490E0(p, 2, lbl_8035D5EC);
        fn_8023F9C8(p, 0);
        break;
    case 4:
        fn_802401D0(p);
        (*(VO **)(p + 0x118))->getPos(&a, &f, 0, 0, 0);
        *(volatile f32 *)&f.x = -f.x;
        *(volatile f32 *)&f.y = -f.y;
        *(volatile f32 *)&f.z = -f.z;
        { f32 k = *(volatile f32 *)&lbl_8035D5F0;
        f.x *= k;
        f.y *= k;
        f.z *= k; }
        b.x = a.x + f.x;
        b.y = a.y + f.y;
        b.z = a.z + f.z;
        if (fn_80237934(*(int *)(p + 0x118), &b, 0, 0, buf) != 0) E0->setPos(&b, 0, 0, 0, 0);
        else E0->setPos((void *)(p + 0x11c), 0, 0, 0, 0);
        fn_8023F5E8(p, *(int *)(p + 0x118));
        fn_80241628(p, 2, 0);
        fn_80241588(p, 0, 0, lbl_8035D5D8);
        reaper(p);
        break;
    case 5:
        return;
    case 6:
        *(f32 *)((int)E0 + 0x110) = lbl_8035D5C8;
        fn_802401A0(p);
        fn_80241628(p, 0, 0);
        fn_80241588(p, 5, 0, lbl_8035D5D8);
        fn_8023F9C8(p, 0);
        break;
    case 7:
        fn_8023F5E8(p, *(int *)(p + 0x118));
        fn_80241628(p, 2, 0);
        fn_80241588(p, 2, 0, lbl_8035D5D8);
        *(u32 *)(p + 0x170) = 0;
        break;
    case 8:
        fn_80241628(p, 0, 0);
        fn_80241588(p, 4, 0, lbl_8035D5D8);
        break;
    case 9:
        *(f32 *)((int)E0 + 0x110) = lbl_8035D5C8;
        fn_80241628(p, 3, 0);
        fn_80241588(p, 0, 0, lbl_8035D5D8);
        break;
    case 10:
        hit(p, 0);
        break;
    case 11:
        *(f32 *)((int)E0 + 0x110) = lbl_8035D5C8;
        hit(p, 6);
        *(u32 *)(p + 0x174) = 0;
        break;
    case 12:
        fn_80240DBC(p, lbl_8035D5E8);
        break;
    case 13:
        fn_802401D0(p);
        fn_8023F864(p, 0);
        break;
    case 14:
        fn_802401D0(p);
        break;
    case 15:
        fn_8023F864(p, 0);
        break;
    case 16:
        if (*(int *)(p + 0xdc) != 0) fn_80241588(p, 0, 0, lbl_8035D5D8);
        break;
    case 17:
        if (*(int *)(p + 0xdc) != 1) fn_80241588(p, 1, 0, lbl_8035D5D8);
        break;
    case 18: {
        VO *o;
        fn_8023F864(p, 0);
        fn_802402E0(p);
        o = *(VO **)(p + 0x164);
        if (o) o->send(lbl_8035D5F4, *(u32 *)(p + 0xe0), 0, *(void **)(p + 0x168), 0);
        if (fn_800F6CD0(*(void **)(p + 0x14c), lbl_8035D48C) == 0)
            fn_80242BC0(fn_80242144(p, 4), *(void **)(p + 0x14c), 0, 0, 0, 0);
        break;
    }
    case 19:
        if (*(int *)(p + 0x170) == 1) fn_802494A4(p, 1);
        else fn_802494A4(p, 3);
        break;
    case 20:
        fn_802494A4(p, 3);
        break;
    case 21:
        if (*(int *)(p + 0xdc) == 6) fn_80241588(p, 0, 0, lbl_8035D5D8);
        else if (*(int *)(p + 0x174) == 1) fn_802494A4(p, 1);
        break;
    case 22:
        fn_802494A4(p, 2);
        break;
    case 23:
        *(u32 *)(p + 0x170) = 1;
        dmg = -**(f32 **)(p + 0x128);
        (*(VO **)(p + 0x118))->send(lbl_8035D5FC, *(u32 *)(p + 0xe0), 0, &dmg, 0);
        break;
    case 24:
        *(u32 *)(p + 0x138) = 1;
        fn_802405B8(p);
        break;
    case 25:
        fn_802405B8(p);
        break;
    case 26:
        *(u32 *)(p + 0x138) = 2;
        fn_802405B8(p);
        break;
    case 27:
        *(u32 *)(p + 0x138) = 3;
        fn_802405B8(p);
        break;
    case 28: {
        f32 c;
        if (lbl_8035D5E4 == *(f32 *)(p + 0x17c)) *(f32 *)(p + 0x17c) = *(f32 *)((int)E0 + 0x1a8);
        c = *(f32 *)((int)E0 + 0x1ac);
        if (*(f32 *)(p + 0x17c) - c > **(f32 **)(p + 0x134)) {
            *(f32 *)(p + 0x17c) = c;
            fn_802494A4(p, 3);
        } else if (*(int *)(p + 0x60) == 1 || *(int *)(p + 0x60) == 2) {
            if (*(int *)(p + 0x138) == 2) fn_80241588(p, 3, 0, lbl_8035D5D8);
            else if (*(int *)(p + 0x138) == 3) fn_80241588(p, 3, 0, lbl_8035D5D8);
        }
        break;
    }
    case 29:
        fn_802494A4(p, 6);
        break;
    case 30:
        *(f32 *)((int)E0 + 0x110) = lbl_8035D5C8;
        break;
    case 31:
        fn_802494A4(p, 8);
        break;
    case 32:
        fn_802494A4(p, 4);
        break;
    case 33:
        fn_8023F864(p, 0);
        fn_802490E0(p, 1, **(f32 **)(p + 0x140));
        break;
    case 34:
        *(u32 *)(p + 0x174) = 1;
        if (*(int *)(p + 0xdc) == 0) fn_802494A4(p, 1);
        break;
    case 35:
        fn_802494A4(p, 7);
        break;
    case 36:
        fn_802494A4(p, 12);
        break;
    case 37:
        *(u32 *)(p + 0x16c) = 1;
        break;
    case 38:
        *(u32 *)(p + 0x16c) = 1;
        fn_802494A4(p, 7);
        break;
    case 39:
        *(u32 *)(p + 0x16c) = 0;
        break;
    case 40:
        *(u32 *)(p + 0x16c) = 0;
        fn_802494A4(p, 11);
        break;
    case 41:
        fn_802494A4(p, 10);
        fn_802402E0(p);
        fn_8023F864(p, 0);
        break;
    case 42:
        fn_802494A4(p, 1);
        break;
    case 43: walkPlayer(p, lbl_8035D604); break;
    case 44: walkPlayer(p, lbl_8035D60C); break;
    case 45: walkPlayer(p, lbl_8035D614); break;
    case 46: walkPlayer(p, lbl_8035D61C); break;
    case 47: walkPlayer(p, lbl_8035D624); break;
    case 48: walkPlayer(p, lbl_8035D62C); break;
    case 49: walkPlayer(p, lbl_8035D634); break;
    case 50: walkPlayer(p, lbl_8035D63C); break;
    case 51: walkPlayer(p, lbl_8035D644); break;
    case 52: walkPlayer(p, lbl_8035D64C); break;
    case 53:
        if (*(void **)(p + 0xf0) != 0) fn_802413D8(p, *(int *)(p + 0xf0), lbl_8035D5D8, 0, 1, *(int *)(p + 0xec));
        break;
    case 54:
        *(u32 *)(p + 0x164) = *(u32 *)(p + 0xe4);
        *(u32 *)(p + 0x168) = *(u32 *)(p + 0xec);
        E0->getPos((void *)(p + 0x11c), 0, 0, 0, 0);
        E0->showA();
        E0->hideA();
        fn_802494A4(p, 12);
        break;
    case 55:
        fn_80236B14(*(int *)(p + 0xe0));
        for (i = 0; i < *(int *)(p + 0x5c); i++) fn_80249058(p, i);
        fn_8023F864(p, 0);
        break;
    case 56:
        fn_80236AC0(*(int *)(p + 0xe0));
        for (i = 0; i < *(int *)(p + 0x5c); i++) fn_8024909C(p, i);
    case 57:
        break;
    }
}
}
