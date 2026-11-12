// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
extern u8 lbl_8035FB58[];
extern u8 lbl_8035FB5C[];
extern u8 lbl_8035FB64[];
extern u8 lbl_8035FB6C[];
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
extern u8 lbl_8035FB7C[];
extern u8 lbl_8035FB84[];
extern u8 lbl_8035FB8C[];
extern u8 lbl_8035FB94[];
extern u8 lbl_8035FB9C[];
extern u8 lbl_8035FBA4[];
extern u8 lbl_8035FBAC[];
extern u8 lbl_8035FBB4[];
extern u8 lbl_8035FBBC[];
extern const char lbl_80298A78[];
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
extern u8 lbl_8035FBD4[];
extern u8 lbl_8035FBDC[];
extern u8 lbl_8035FBE4[];
extern u8 lbl_8035FBEC[];
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
extern const char lbl_80298ACC[];
extern u8 lbl_8035FC04[];
extern u8 lbl_8035FC0C[];
void fn_80083BC4(void);
void fn_80249AC4(void);
void fn_80083908(void);
void fn_80081F84(void);
void fn_80083690(void);
void fn_8023D198(void);
void fn_80083CD0(void);
void fn_8008028C(int p, int st);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_800824C0(void);
void fn_80081988(void);
void fn_800835D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_80083CD8(void);
void fn_800819BC(void);

#include "common.h"
extern "C" {
struct VO { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void getPos(void *p, void *a, void *b, void *c, int d); virtual void setPos(void *a, void *b, void *c, void *d, int e); virtual void w15(); virtual void w16(); virtual void hideA(); virtual void w18(); virtual void showA(); virtual void w20(); virtual void w21(); virtual void w22(); virtual void show(); virtual void hide(); virtual void w25(); virtual void w26(); virtual void w27(); virtual void w28(); virtual void w29(); virtual void w30(); virtual void w31(); virtual void w32(); virtual void send(void *msg, void *to, int a, void *d, int b); };
// The TU string pool (.rodata 80298A60-80298AE4) in its original order: strings that tables or other units name are
// globals, the strings the code uses are one static array each (statics are addressed relative to the pool
// start, like the original literals).
extern const char lbl_80298A60[];
const char lbl_80298A60[] = "MStation";
static const char lbl_80298A6C[] = "BACKWARD";
extern const char lbl_80298A78[];
const char lbl_80298A78[] = "ANIMOVER";
static const char lbl_80298A84[] = "PLYRNACT";
static const char lbl_80298A90[] = "CHANNACT";
static const char lbl_80298A9C[] = "ACTIVATE";
static const char lbl_80298AA8[] = "DEACTIV8";
static const char lbl_80298AB4[] = "WAITONME";
static const char lbl_80298AC0[] = "SENDDIST";
extern const char lbl_80298ACC[];
const char lbl_80298ACC[] = "PLYRDEAD";
static const char lbl_80298AD8[12] = "SETGRATE";   // padded: the pool ends at 80298AE4
__declspec(section ".data") u8 lbl_802C4398[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[16] = { (void *)lbl_8035FB50, (void *)lbl_8035FB58, (void *)lbl_8035FB5C, (void *)lbl_8035FB64, (void *)lbl_8035FB58, (void *)lbl_8035FB6C, (void *)lbl_8035FB74, (void *)lbl_8035FB58, (void *)lbl_8035FB7C, (void *)lbl_8035FB84, (void *)lbl_8035FB58, (void *)lbl_8035FB58, (void *)lbl_8035FB8C, (void *)lbl_8035FB58, (void *)lbl_8035FB58, (void *)lbl_8035FB58 };
static __declspec(section ".data") u8 sPad_25C[12] = { 0x40, 0xA0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_268[30] = { (void *)lbl_8035FB94, (void *)lbl_8035FB9C, (void *)lbl_8035FBA4, (void *)lbl_8035FBAC, (void *)lbl_8035FBB4, (void *)lbl_80298A6C, (void *)lbl_8035FBBC, (void *)lbl_80298A78, (void *)lbl_8035FBC4, (void *)lbl_8035FBCC, (void *)lbl_8035FBD4, (void *)lbl_8035FBDC, (void *)lbl_8035FBE4, (void *)lbl_8035FBEC, (void *)lbl_8035FBF4, (void *)lbl_80298A84, (void *)lbl_80298A90, (void *)lbl_80298A9C, (void *)lbl_80298AA8, (void *)lbl_8035FB94, (void *)lbl_80298AB4, (void *)lbl_8035FBFC, (void *)lbl_80298AC0, (void *)lbl_80298ACC, (void *)lbl_8035FB50, (void *)lbl_8035FB74, (void *)lbl_8035FC04, (void *)lbl_8035FC0C, (void *)lbl_80298AD8, (void *)lbl_8035FBBC };
static __declspec(section ".data") u8 sPad_2E0[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2E8[1] = { (void *)lbl_80298A78 };
static __declspec(section ".data") u8 sPad_2EC[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_2F4[1] = { (void *)lbl_8035FBC4 };
static __declspec(section ".data") u8 sPad_2F8[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_300[1] = { (void *)lbl_8035FBCC };
static __declspec(section ".data") u8 sPad_304[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_30C[1] = { (void *)lbl_8035FBD4 };
static __declspec(section ".data") u8 sPad_310[8] = { 0, 0, 0, 4, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_318[1] = { (void *)lbl_8035FBDC };
static __declspec(section ".data") u8 sPad_31C[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_324[1] = { (void *)lbl_8035FBE4 };
static __declspec(section ".data") u8 sPad_328[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_330[1] = { (void *)lbl_8035FBEC };
static __declspec(section ".data") u8 sPad_334[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_33C[1] = { (void *)lbl_8035FBF4 };
static __declspec(section ".data") u8 sPad_340[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_348[1] = { (void *)lbl_80298A84 };
static __declspec(section ".data") u8 sPad_34C[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_354[1] = { (void *)lbl_80298A90 };
static __declspec(section ".data") u8 sPad_358[8] = { 0, 0, 0, 0xA, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_360[1] = { (void *)lbl_80298A9C };
static __declspec(section ".data") u8 sPad_364[8] = { 0, 0, 0, 0xB, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_36C[1] = { (void *)lbl_80298AA8 };
static __declspec(section ".data") u8 sPad_370[8] = { 0, 0, 0, 0xC, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_378[1] = { (void *)lbl_8035FB94 };
static __declspec(section ".data") u8 sPad_37C[8] = { 0, 0, 0, 0xD, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_384[1] = { (void *)lbl_80298AB4 };
static __declspec(section ".data") u8 sPad_388[8] = { 0, 0, 0, 0xE, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_390[1] = { (void *)lbl_8035FBFC };
static __declspec(section ".data") u8 sPad_394[8] = { 0, 0, 0, 0xF, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_39C[1] = { (void *)lbl_80298AC0 };
static __declspec(section ".data") u8 sPad_3A0[8] = { 0, 0, 0, 0x10, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3A8[1] = { (void *)lbl_80298ACC };
static __declspec(section ".data") u8 sPad_3AC[8] = { 0, 0, 0, 0x11, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3B4[1] = { (void *)lbl_8035FB50 };
static __declspec(section ".data") u8 sPad_3B8[8] = { 0, 0, 0, 0x12, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3C0[1] = { (void *)lbl_8035FB74 };
static __declspec(section ".data") u8 sPad_3C4[8] = { 0, 0, 0, 0x13, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3CC[1] = { (void *)lbl_8035FC04 };
static __declspec(section ".data") u8 sPad_3D0[8] = { 0, 0, 0, 0x14, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3D8[1] = { (void *)lbl_8035FC0C };
static __declspec(section ".data") u8 sPad_3DC[8] = { 0, 0, 0, 0x15, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_3E4[1] = { (void *)lbl_80298AD8 };
static __declspec(section ".data") u8 sPad_3E8[100] = { 0, 0, 0, 0x16, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 0, 0xA, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0xD, 0, 0, 0, 0xE, 0, 0, 0, 0xF, 0, 0, 0, 0x10, 0, 0, 0, 0x11, 0, 0, 0, 0x12, 0, 0, 0, 0x13, 0, 0, 0, 0x14, 0, 0, 0, 0x15, 0, 0, 0, 0x16 };
static __declspec(section ".data") s32 tA[23] = { 0, 5, 9, 0xC, 0x10, 0x12, 0x14, 0x16, 0x1B, 0x20, 0x25, 0x2A, 0x2E, 0x32, 0x35, 0x37, 0x39, 0x3B, 0x40, 0x43, 0x46, 0x48, 0x4B };
static __declspec(section ".data") s32 tB[76] = { 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 3, 1, 1, 1, 1, 2, 1, 4, 1, 4, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 2, 1, 1, 1, 3, 1, 1, 1, 4, 1, 4, 1, 4, 1, 1, 1, 1, 1, 1, 1, 3, 3, 1, 1, 1, 4, 3, 1, 1, 5 };
static __declspec(section ".data") s32 tC[76] = { 0, 1, 2, 3, 4, 5, 6, 5, 7, 5, 8, 9, 5, 0xA, 0xB, 0xA, 5, 0xC, 5, 0xD, 5, 0xE, 5, 0xF, 0x10, 0x11, 0x12, 5, 0x13, 0x14, 0x15, 0x16, 5, 0x17, 0x18, 0x19, 0x1A, 5, 0x1B, 0x1C, 0x1D, 0x1E, 5, 0x1F, 5, 0x20, 5, 0x21, 0x22, 5, 5, 0x23, 5, 5, 0x24, 5, 0x25, 5, 0x26, 5, 0x27, 0x28, 0x29, 0x27, 0x2A, 5, 0x2A, 0x2B, 5, 0x2B, 5, 0x2C, 5, 0x2D, 5, 0x2E };
__declspec(section ".data") u8 lbl_802C4AA0[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802C4AA8[18] = { (void *)fn_80083BC4, (void *)fn_80249AC4, (void *)fn_80083908, (void *)fn_80081F84, (void *)fn_80083690, (void *)fn_8023D198, (void *)fn_80083CD0, (void *)fn_8008028C, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_800824C0, (void *)fn_80081988, (void *)fn_800835D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_80083CD8, (void *)fn_800819BC };
extern f32 lbl_8035FC14;
extern char lbl_8035FB50[4], lbl_8035FB74[4], lbl_8035FBC4[4], lbl_8035FBCC[4], lbl_8035FBF4[4], lbl_8035FBFC[4], lbl_8035FC18[4];
void fn_800819F0(int, const char *);
void fn_800820C4(int);
void fn_80083120(int, int);
void fn_8022A7A8(VO *);
void fn_8022AD0C(VO *);
void fn_80240DBC(int, f32);
void fn_80241628(int, int, int);
void *fn_80242144(int, int);
void fn_80242BC0(void *, void *, int, int, int, int);
void fn_80249008(int, int);
void fn_802490E0(int, int, f32);
int fn_802494A4(int, int);

#define E0 (*(VO **)(p + 0xe0))
#define I(o) (*(int *)(p + (o)))
#define PV(o) (*(void **)(p + (o)))
#define PI(o) (**(int **)(p + (o)))
#define FLG (**(u32 **)(p + 0x1b8))

#define isOn(p) ((FLG & I(0x1bc)) != 0 && (FLG & I(0x1c0)) == 0)
static inline void grab(int p) {
    if (PV(0xe4) != 0 && I(0x198) == 0) {
        PV(0x180) = PV(0xe4);
        (*(VO **)(p + 0x180))->send((void *)((char *)lbl_80298AB4), 0, 0, 0, 0);
        I(0x198) = 1;
        I(0x19c) = 0;
    }
}
static inline void release(int p) {
    if (PV(0x180) != 0 && PV(0x180) != PV(0xe0) && I(0x19c) == 0) (*(VO **)(p + 0x180))->send(lbl_8035FBFC, 0, 0, 0, 0);
    I(0x198) = 0;
    I(0x19c) = 1;
    PV(0x180) = 0;
}
static inline void say(int p, char *s) { fn_80242BC0(fn_80242144(p, 1), s, 0, 0, 0, 0); }
static inline void unact(int p) {
    I(0x1a0) = 0;
    if (I(0x1a4) != 0) {
        fn_80240DBC(p, lbl_8035FC14);
        I(0x1a4) = 0;
    }
}
static inline void go4(int p) {
    I(0x1a0) = 1;
    I(0x18c) = 0;
    grab(p);
    fn_802494A4(p, 4);
}
static inline void go2(int p) {
    I(0x1a0) = 1;
    grab(p);
    fn_802494A4(p, 2);
}
static inline void tryA(int p) {
    if (PI(0x128) == 0) {
        if (isOn(p) && PI(0x124) == 0 && (PI(0x128) != 0 || I(0x188) == 0 || I(0x18c) == 0)) go4(p);
    } else {
        unact(p);
    }
}
static inline void tryB(int p) {
    if (isOn(p) && PI(0x124) == 0 && (PI(0x128) != 0 || I(0x188) == 0)) go4(p);
}

void fn_8008028C(int p, int st) {
    s32 *q;
    s32 idx;
    s32 t;

    t = *(s32 *)(p + 0x60);
    idx = tA[st];
    for (q = tB + idx; t > 0; q++) {
        if (*q > t) break;
        t -= tB[idx++];
    }
    switch (tC[idx]) {
    case 0:
        fn_80241628(p, 0, 0);
        fn_800820C4(p);
        break;
    case 1:
        fn_80083120(p, 0);
        fn_80241628(p, 0, 0);
        break;
    case 2:
        fn_80083120(p, 1);
        break;
    case 3:
        fn_80083120(p, 2);
        break;
    case 4:
        fn_80083120(p, 3);
        break;
    case 5:
        return;
    case 6:
        fn_802494A4(p, 3);
        release(p);
        say(p, lbl_8035FB74);
        break;
    case 7:
        fn_802494A4(p, 1);
        release(p);
        say(p, lbl_8035FB50);
        break;
    case 8:
        FLG &= ~I(0x1c0);
        say(p, lbl_8035FBC4);
        break;
    case 9:
        FLG &= ~I(0x1c0);
        say(p, lbl_8035FBC4);
        if (I(0x188) != 0 && isOn(p)) go2(p);
        break;
    case 10:
        FLG |= I(0x1c0);
        unact(p);
        say(p, lbl_8035FBCC);
        break;
    case 11:
        if (PI(0x128) == 0 && I(0x188) != 0 && isOn(p) && PI(0x124) == 0 && (PI(0x128) != 0 || I(0x188) == 0 || I(0x18c) == 0)) go4(p);
        FLG |= I(0x1c0);
        unact(p);
        say(p, lbl_8035FBCC);
        break;
    case 12:
        FLG |= I(0x1c0);
        say(p, lbl_8035FBCC);
        break;
    case 13: {
        if ((FLG & I(0x1c0)) == 0) {
            FLG |= I(0x1bc);
            E0->show();
            fn_8022AD0C(E0);
        }
        break;
    }
    case 14: {
        if ((FLG & I(0x1c0)) == 0) {
            FLG &= ~I(0x1bc);
            E0->hide();
            fn_8022A7A8(E0);
        }
        break;
    }
    case 15:
        I(0x1a8) = 0;
        I(0x188) = 1;
        if (PI(0x138) != 0) {
            if (isOn(p)) go2(p);
            fn_800819F0(p, lbl_8035FBF4);
        }
        break;
    case 16:
        I(0x1a8) = 0;
        if (PI(0x128) != 0 && PI(0x13c) != 0) tryB(p);
        I(0x188) = 1;
        fn_800819F0(p, lbl_8035FBF4);
        break;
    case 17:
        I(0x1a8) = 0;
        if (PI(0x128) != 0 && PI(0x13c) != 0) {
            tryB(p);
            I(0x188) = 1;
            fn_800819F0(p, lbl_8035FBF4);
        } else if (PI(0x13c) != 0) {
            tryB(p);
            fn_800819F0(p, lbl_8035FBF4);
        }
        break;
    case 18:
        I(0x1a8) = 0;
        I(0x188) = 1;
        if (PI(0x138) != 0) {
            if (isOn(p)) go2(p);
            fn_800819F0(p, lbl_8035FBF4);
        }
        break;
    case 19:
        I(0x1a8) = 1;
        if (isOn(p)) go2(p);
        fn_800819F0(p, lbl_8035FBF4);
        break;
    case 20:
        I(0x1a8) = 1;
        if (PI(0x128) != 0) tryB(p);
        fn_800819F0(p, lbl_8035FBF4);
        break;
    case 21:
        I(0x1a8) = 1;
        tryB(p);
        fn_800819F0(p, lbl_8035FBF4);
        break;
    case 22:
        I(0x1a8) = 1;
        if (isOn(p)) go2(p);
        fn_800819F0(p, lbl_8035FBF4);
        break;
    case 23:
        I(0x188) = 0;
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 24:
        tryA(p);
        I(0x188) = 0;
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 25:
        I(0x188) = 0;
        if (PI(0x130) != 0 && PI(0x128) == 0) fn_802490E0(p, 0, **(f32 **)(p + 0x134));
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 26:
        tryA(p);
        I(0x188) = 0;
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 27:
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 28:
        tryA(p);
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 29:
        if (PI(0x130) != 0 && PI(0x128) == 0) fn_802490E0(p, 0, **(f32 **)(p + 0x134));
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 30:
        tryA(p);
        fn_800819F0(p, ((char *)lbl_80298A90));
        break;
    case 31:
        I(0x1a8) = 0;
        if (isOn(p)) go2(p);
        I(0x18c) = 1;
        break;
    case 32:
        I(0x1a8) = 0;
        if (isOn(p)) go2(p);
        I(0x18c) = 1;
        break;
    case 33:
        I(0x1a8) = 0;
        tryB(p);
        break;
    case 34:
        I(0x1a8) = 0;
        tryB(p);
        break;
    case 35:
        I(0x17c) = 1;
        break;
    case 36:
        I(0x184)++;
        break;
    case 37:
        I(0x184)--;
        break;
    case 38:
        if (isOn(p)) {
            s32 s = *(s32 *)(p + 0x60);
            if ((PI(0x138) != 0 && (s == 1 || s == 4)) || (PI(0x13c) != 0 && (s == 2 || s == 3)))
                (*(VO **)(p + 0xe4))->send(lbl_8035FC18, E0, 0, PV(0xec), I(0x160));
        }
        break;
    case 39:
        I(0x188) = 0;
        break;
    case 40:
        if (I(0x188) != 0 && isOn(p) && PI(0x124) == 0 && (PI(0x128) != 0 || I(0x188) == 0 || I(0x18c) == 0)) go4(p);
        break;
    case 41:
        if (I(0x188) != 0 && PI(0x130) != 0 && PI(0x128) == 0) {
            I(0x188) = 0;
            fn_802490E0(p, 0, **(f32 **)(p + 0x134));
        } else {
            I(0x188) = 0;
        }
        break;
    case 42:
        fn_802494A4(p, 1);
        break;
    case 43:
        fn_802494A4(p, 3);
        break;
    case 44:
        fn_802494A4(p, 0);
        break;
    case 45:
        fn_80249008(p, 0);
        I(0x17c) = 0;
        break;
    case 46:
        if (PV(0xec) != 0) {
            *(f32 *)(p + 0x1d0) = *(f32 *)PV(0xec);
            if (PV(0x1ac) != 0) (*(VO **)(p + 0x1ac))->send((void *)((char *)lbl_80298AD8), 0, 0, PV(0xec), 0);
        }
        break;
    case 47:
        break;
    }
}
}

} /* extern "C" */
