// One translation unit: fn_8008F16C .. fn_80090C68 (13 former units; lmw, readonly strings).
// They share the descriptor tables at 802C88A8 (fn_8008F16C walks them, fn_80090844 stores their addresses),
// the string pool at 802995A8 and consecutive jump tables (fn_80090C68's starts at 4 mod 8 right behind
// fn_8008F16C's), so they cannot link separately. fn_800904CC is schedule-equivalent, the rest exact.
// One namespace per former unit.
#include "common.h"

extern "C" {
void fn_80090C68(void);
void fn_8008F16C(void);
extern u8 lbl_803606D0[];
extern u8 lbl_803606D8[];
extern u8 lbl_803606E0[];
extern u8 lbl_803606E8[];
extern u8 lbl_803606F0[];
extern u8 lbl_803606F8[];
extern u8 lbl_80360700[];
extern u8 lbl_80360708[];
extern u8 lbl_80360710[];
extern u8 lbl_80360718[];
extern u8 lbl_80360720[];
extern u8 lbl_80360728[];
extern u8 lbl_80360730[];
extern u8 lbl_80360738[];
extern char lbl_80360740[4], lbl_803608EC[4], lbl_803608F4[4], lbl_8036090C[4];
extern u8 lbl_80360744[];
extern u8 lbl_8036074C[];
extern u8 lbl_80360754[];
extern u8 lbl_8036075C[];
extern u8 lbl_80360764[];
extern u8 lbl_8036076C[];
extern u8 lbl_80360774[];
extern u8 lbl_8036077C[];
extern u8 lbl_80360784[];
extern u8 lbl_8036078C[];
extern u8 lbl_80360794[];
extern u8 lbl_8036079C[];
extern u8 lbl_803607A4[];
extern u8 lbl_803607AC[];
extern u8 lbl_803607B4[];
extern u8 lbl_803607BC[];
extern u8 lbl_803607C4[];
extern u8 lbl_803607CC[];
extern u8 lbl_803607D4[];
extern u8 lbl_803607DC[];
extern u8 lbl_803607E4[];
extern u8 lbl_803607EC[];
extern u8 lbl_803607F4[];
extern u8 lbl_803607FC[];
extern u8 lbl_80360804[];
extern u8 lbl_8036080C[];
extern u8 lbl_80360814[];
extern u8 lbl_8036081C[];
extern u8 lbl_80360824[];
extern u8 lbl_8036082C[];
extern u8 lbl_80360830[];
extern u8 lbl_80360838[];
extern u8 lbl_80360840[];
extern u8 lbl_80360848[];
extern u8 lbl_80360850[];
extern u8 lbl_80360858[];
extern u8 lbl_80360860[];
extern u8 lbl_80360868[];
extern u8 lbl_80360870[];
extern u8 lbl_80360878[];
extern u8 lbl_80360880[];
extern u8 lbl_80360888[];
extern u8 lbl_80360890[];
extern u8 lbl_80360898[];
extern u8 lbl_803608A0[];
extern u8 lbl_803608A8[];
extern u8 lbl_803608B0[];
extern u8 lbl_803608B8[];
extern u8 lbl_803608C0[];
extern u8 lbl_803608C8[];
extern u8 lbl_803608D0[];
extern char lbl_803608D8[0x6];
extern char lbl_803608E0[0x7];
void fn_80090B0C(void);
void fn_80249AC4(void);
void fn_80090970(void);
void fn_800902FC(void);
void fn_800907D0(void);
void fn_8023D198(void);
void fn_80090C18(void);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_80090470(void);
void fn_80090358(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_800903E4(void);
// The TU string pool (.rodata 802995A8-8029975C) in its original order: the 19 table strings are globals (the
// tables and other objects name them), the strings the code uses are one static array each (statics are
// addressed relative to the pool start, like the original literals).
extern const char lbl_802995A8[];
const char lbl_802995A8[] = "MStation";
extern const char lbl_802995B4[];
const char lbl_802995B4[] = "BR_idle2";
extern const char lbl_802995C0[];
const char lbl_802995C0[] = "PlrShot4";
extern const char lbl_802995CC[];
const char lbl_802995CC[] = "PlrShot2";
extern const char lbl_802995D8[];
const char lbl_802995D8[] = "PlrShot5";
extern const char lbl_802995E4[];
const char lbl_802995E4[] = "PlrShot3";
extern const char lbl_802995F0[];
const char lbl_802995F0[] = "PlrShot6";
extern const char lbl_802995FC[];
const char lbl_802995FC[] = "FADEOVER";
extern const char lbl_80299608[];
const char lbl_80299608[] = "IDLEOVER";
extern const char lbl_80299614[];
const char lbl_80299614[] = "PSTATOVR";
extern const char lbl_80299620[];
const char lbl_80299620[] = "SENDEVNT";
extern const char lbl_8029962C[];
const char lbl_8029962C[] = "ANIMOVER";
extern const char lbl_80299638[];
const char lbl_80299638[] = "ANIMLOOP";
extern const char lbl_80299644[];
const char lbl_80299644[] = "STRT_COL";
extern const char lbl_80299650[];
const char lbl_80299650[] = "ATTARGET";
extern const char lbl_8029965C[];
const char lbl_8029965C[] = "PLYRDEAD";
extern const char lbl_80299668[];
const char lbl_80299668[] = "PLYRLIVE";
extern const char lbl_80299674[];
const char lbl_80299674[] = "HITINVLN";
extern const char lbl_80299680[];
const char lbl_80299680[] = "PATHOVER";
static const char s68C[] = "Banshee2";
static const char s698[] = "BansheeF";
static const char s6A4[] = "Banshe2F";
static const char s6B0[] = "BRingSht";
static const char s6BC[] = "BRingSh2";
static const char s6C8[] = "AttackDamage";
static const char s6D8[] = "WindStrength";
static const char s6E8[] = "WindupDelay";
static const char s6F4[] = "MaxPushDistance";
static const char s704[] = "SlowdownFactor";
static const char s714[] = "SlowdownTime";
static const char s724[] = "AttackDuration";
static const char s734[] = "PostAttackPause";
static const char s744[] = "aDeadEvent";
static const char s750[12] = "BansheeType";   // padded: the pool ends at 8029975C
}

// Global scope: the constructors / destructor of these classes are real symbols (a namespace would change
// the mangled names).
struct C8018E150 { C8018E150(); u8 pad_[0xa8]; };
struct C8024262C {
    C8024262C();
    ~C8024262C();
};

namespace n8008F16C {

extern "C" {

#include "common.h"
extern "C" {
struct VO { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void getPos(void *p, int a, int b, int c, int d); virtual void setPos(void *p, int a, int b, int c, int d); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void send(void *msg, u32 to, int a, void *d, void *e); };
struct VE { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void fire(u32 o, void *pos, char *grp, char *bone); };
// Descriptor tables of the TU (.data from 802C88A8), split where fn_80090844 takes their addresses.
__declspec(section ".data") u8 lbl_802C88A8[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *d540[5] = { (void *)lbl_802995A8, (void *)lbl_803606D0, (void *)lbl_803606D8, (void *)lbl_803606E0, (void *)lbl_803606E8 };
static __declspec(section ".data") void *d560[24] = { (void *)lbl_803606F0, (void *)lbl_803606F8, (void *)lbl_80360700, (void *)lbl_80360708, (void *)lbl_803606F8, (void *)lbl_80360710, (void *)lbl_80360718, (void *)lbl_803606F8, (void *)lbl_80360720, (void *)lbl_80360728, (void *)lbl_803606F8, (void *)lbl_802995B4, (void *)lbl_80360730, (void *)lbl_803606F8, (void *)lbl_80360738, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_80360744, (void *)lbl_803606F8, (void *)lbl_80360744, (void *)lbl_8036074C, (void *)lbl_803606F8, (void *)lbl_8036074C };
static __declspec(section ".data") void *d656[2] = { (void *)lbl_80360754, (void *)lbl_8036075C };
static __declspec(section ".data") u8 d656_8[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *d656_C[2] = { (void *)lbl_80360764, (void *)lbl_8036076C };
static __declspec(section ".data") u8 d656_14[4] = { 0, 0, 0, 1 };
static __declspec(section ".data") void *d656_18[2] = { (void *)lbl_80360774, (void *)lbl_8036077C };
static __declspec(section ".data") u8 d656_20[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *d692[36] = { (void *)lbl_80360784, (void *)lbl_80360784, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036078C, (void *)lbl_80360794, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036078C, (void *)lbl_802995C0, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036079C, (void *)lbl_802995CC, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036079C, (void *)lbl_802995D8, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036079C, (void *)lbl_803607A4, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036079C, (void *)lbl_802995E4, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_8036079C, (void *)lbl_802995F0, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_803607AC, (void *)lbl_80360740, (void *)lbl_80360740, (void *)lbl_80360740 };
static __declspec(section ".data") u8 d836[12] = { 0x3D, 0xCC, 0xCC, 0xCD, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_C[1] = { (void *)lbl_803607B4 };
static __declspec(section ".data") u8 d836_10[12] = { 0x40, 0x40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_1C[1] = { (void *)lbl_802995FC };
static __declspec(section ".data") u8 d836_20[12] = { 0x40, 0xA0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_2C[1] = { (void *)lbl_80299608 };
static __declspec(section ".data") u8 d836_30[12] = { 0x40, 0x40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_3C[1] = { (void *)lbl_803607BC };
static __declspec(section ".data") u8 d836_40[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_4C[1] = { (void *)lbl_80299614 };
static __declspec(section ".data") u8 d836_50[12] = { 0x3F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_5C[1] = { (void *)lbl_80360740 };
static __declspec(section ".data") u8 d836_60[12] = { 0x40, 0xA0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_6C[1] = { (void *)lbl_80299620 };
static __declspec(section ".data") u8 d836_70[12] = { 0x40, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d836_7C[1] = { (void *)lbl_803607C4 };
static __declspec(section ".data") void *d964[1] = { (void *)lbl_803607CC };
static __declspec(section ".data") u8 d964_4[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d964_14[1] = { (void *)lbl_803607D4 };
static __declspec(section ".data") u8 d964_18[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d964_28[1] = { (void *)lbl_803607DC };
static __declspec(section ".data") u8 d964_2C[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d964_3C[1] = { (void *)lbl_803607E4 };
static __declspec(section ".data") u8 d964_40[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d964_50[1] = { (void *)lbl_803607EC };
static __declspec(section ".data") u8 d964_54[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d964_64[1] = { (void *)lbl_803607F4 };
static __declspec(section ".data") u8 d964_68[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *d1084[13] = { (void *)lbl_803607FC, (void *)lbl_80360718, (void *)lbl_80360804, (void *)lbl_8036080C, (void *)lbl_80360814, (void *)lbl_8036081C, (void *)lbl_80360824, (void *)lbl_8036082C, (void *)lbl_80360830, (void *)lbl_80360764, (void *)lbl_80360838, (void *)lbl_80360840, (void *)lbl_80360848 };
static __declspec(section ".data") void *d1136[39] = { (void *)lbl_803607FC, (void *)lbl_80360850, (void *)lbl_8029962C, (void *)lbl_80299638, (void *)lbl_80299644, (void *)lbl_80299644, (void *)lbl_803607C4, (void *)lbl_80360858, (void *)lbl_80360860, (void *)lbl_8036081C, (void *)lbl_80299650, (void *)lbl_8029965C, (void *)lbl_80299668, (void *)lbl_80360868, (void *)lbl_803607B4, (void *)lbl_802995FC, (void *)lbl_80299608, (void *)lbl_80299674, (void *)lbl_803606F0, (void *)lbl_80360754, (void *)lbl_80360870, (void *)lbl_80299680, (void *)lbl_80360878, (void *)lbl_80360880, (void *)lbl_80360888, (void *)lbl_80360890, (void *)lbl_80360898, (void *)lbl_803608A0, (void *)lbl_803608A8, (void *)lbl_803608B0, (void *)lbl_803608B8, (void *)lbl_803608C0, (void *)lbl_803608C8, (void *)lbl_803607BC, (void *)lbl_80299614, (void *)lbl_803608D0, (void *)lbl_80299620, (void *)lbl_803608D8, (void *)lbl_803608E0 };
static __declspec(section ".data") void *d1292[1] = { (void *)lbl_803607FC };
static __declspec(section ".data") u8 d1292_4[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_C[1] = { (void *)lbl_80360850 };
static __declspec(section ".data") u8 d1292_10[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_18[1] = { (void *)lbl_8029962C };
static __declspec(section ".data") u8 d1292_1C[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_24[1] = { (void *)lbl_80299638 };
static __declspec(section ".data") u8 d1292_28[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_30[1] = { (void *)lbl_80299644 };
static __declspec(section ".data") u8 d1292_34[8] = { 0, 0, 0, 4, 0, 0, 0, 2 };
static __declspec(section ".data") void *d1292_3C[1] = { (void *)lbl_803607C4 };
static __declspec(section ".data") u8 d1292_40[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_48[1] = { (void *)lbl_80360858 };
static __declspec(section ".data") u8 d1292_4C[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_54[1] = { (void *)lbl_80360860 };
static __declspec(section ".data") u8 d1292_58[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_60[1] = { (void *)lbl_8036081C };
static __declspec(section ".data") u8 d1292_64[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_6C[1] = { (void *)lbl_80299650 };
static __declspec(section ".data") u8 d1292_70[8] = { 0, 0, 0, 0xA, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_78[1] = { (void *)lbl_8029965C };
static __declspec(section ".data") u8 d1292_7C[8] = { 0, 0, 0, 0xB, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_84[1] = { (void *)lbl_80299668 };
static __declspec(section ".data") u8 d1292_88[8] = { 0, 0, 0, 0xC, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_90[1] = { (void *)lbl_80360868 };
static __declspec(section ".data") u8 d1292_94[8] = { 0, 0, 0, 0xD, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_9C[1] = { (void *)lbl_803607B4 };
static __declspec(section ".data") u8 d1292_A0[8] = { 0, 0, 0, 0xE, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_A8[1] = { (void *)lbl_802995FC };
static __declspec(section ".data") u8 d1292_AC[8] = { 0, 0, 0, 0xF, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_B4[1] = { (void *)lbl_80299608 };
static __declspec(section ".data") u8 d1292_B8[8] = { 0, 0, 0, 0x10, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_C0[1] = { (void *)lbl_80299674 };
static __declspec(section ".data") u8 d1292_C4[8] = { 0, 0, 0, 0x11, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_CC[1] = { (void *)lbl_803606F0 };
static __declspec(section ".data") u8 d1292_D0[8] = { 0, 0, 0, 0x12, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_D8[1] = { (void *)lbl_80360754 };
static __declspec(section ".data") u8 d1292_DC[8] = { 0, 0, 0, 0x13, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_E4[1] = { (void *)lbl_80360870 };
static __declspec(section ".data") u8 d1292_E8[8] = { 0, 0, 0, 0x14, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_F0[1] = { (void *)lbl_80299680 };
static __declspec(section ".data") u8 d1292_F4[8] = { 0, 0, 0, 0x15, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_FC[1] = { (void *)lbl_80360878 };
static __declspec(section ".data") u8 d1292_100[8] = { 0, 0, 0, 0x16, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_108[1] = { (void *)lbl_80360880 };
static __declspec(section ".data") u8 d1292_10C[8] = { 0, 0, 0, 0x17, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_114[1] = { (void *)lbl_80360888 };
static __declspec(section ".data") u8 d1292_118[8] = { 0, 0, 0, 0x18, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_120[1] = { (void *)lbl_80360890 };
static __declspec(section ".data") u8 d1292_124[8] = { 0, 0, 0, 0x19, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_12C[1] = { (void *)lbl_80360898 };
static __declspec(section ".data") u8 d1292_130[8] = { 0, 0, 0, 0x1A, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_138[1] = { (void *)lbl_803608A0 };
static __declspec(section ".data") u8 d1292_13C[8] = { 0, 0, 0, 0x1B, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_144[1] = { (void *)lbl_803608A8 };
static __declspec(section ".data") u8 d1292_148[8] = { 0, 0, 0, 0x1C, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_150[1] = { (void *)lbl_803608B0 };
static __declspec(section ".data") u8 d1292_154[8] = { 0, 0, 0, 0x1D, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_15C[1] = { (void *)lbl_803608B8 };
static __declspec(section ".data") u8 d1292_160[8] = { 0, 0, 0, 0x1E, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_168[1] = { (void *)lbl_803608C0 };
static __declspec(section ".data") u8 d1292_16C[8] = { 0, 0, 0, 0x1F, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_174[1] = { (void *)lbl_803608C8 };
static __declspec(section ".data") u8 d1292_178[8] = { 0, 0, 0, 0x20, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_180[1] = { (void *)lbl_803607BC };
static __declspec(section ".data") u8 d1292_184[8] = { 0, 0, 0, 0x21, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_18C[1] = { (void *)lbl_80299614 };
static __declspec(section ".data") u8 d1292_190[8] = { 0, 0, 0, 0x22, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_198[1] = { (void *)lbl_803608D0 };
static __declspec(section ".data") u8 d1292_19C[8] = { 0, 0, 0, 0x23, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_1A4[1] = { (void *)lbl_80299620 };
static __declspec(section ".data") u8 d1292_1A8[8] = { 0, 0, 0, 0x24, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_1B0[1] = { (void *)lbl_803608D8 };
static __declspec(section ".data") u8 d1292_1B4[8] = { 0, 0, 0, 0x25, 0, 0, 0, 1 };
static __declspec(section ".data") void *d1292_1BC[1] = { (void *)lbl_803608E0 };
static __declspec(section ".data") u8 d1292_1C0[8] = { 0, 0, 0, 0x26, 0, 0, 0, 1 };
static __declspec(section ".data") u8 d1748[156] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 0, 0xA, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0xD, 0, 0, 0, 0xE, 0, 0, 0, 0xF, 0, 0, 0, 0x10, 0, 0, 0, 0x11, 0, 0, 0, 0x12, 0, 0, 0, 0x13, 0, 0, 0, 0x14, 0, 0, 0, 0x15, 0, 0, 0, 0x16, 0, 0, 0, 0x17, 0, 0, 0, 0x18, 0, 0, 0, 0x19, 0, 0, 0, 0x1A, 0, 0, 0, 0x1B, 0, 0, 0, 0x1C, 0, 0, 0, 0x1D, 0, 0, 0, 0x1E, 0, 0, 0, 0x1F, 0, 0, 0, 0x20, 0, 0, 0, 0x21, 0, 0, 0, 0x22, 0, 0, 0, 0x23, 0, 0, 0, 0x24, 0, 0, 0, 0x25, 0, 0, 0, 0x26 };
static __declspec(section ".data") s32 tA[39] = { 0, 0xD, 0x17, 0x1E, 0x21, 0x2A, 0x33, 0x34, 0x37, 0x3F, 0x45, 0x48, 0x4E, 0x56, 0x58, 0x5B, 0x63, 0x68, 0x69, 0x6C, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7F, 0x81, 0x84, 0x87, 0x8B };
static __declspec(section ".data") s32 tB[143] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 1, 1, 1, 5, 1, 1, 0xB, 1, 4, 1, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 2, 1, 1, 1, 0xD, 1, 1, 0xB, 1, 4, 1, 1, 3, 1, 1, 1, 1, 4, 1, 5, 1, 1, 2, 1, 0xA, 2, 3, 1, 2, 4, 1, 1, 1, 3, 1, 1, 1, 4, 1, 1, 0xC, 4, 1, 8, 5, 1, 1, 1, 1, 1, 1, 2, 2, 1, 6, 1, 3, 0xD, 0xB, 1, 1, 0xB, 1, 1, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 0xD, 4, 1, 8, 0xC, 1, 0xB, 1, 1, 5, 1, 7, 2, 9, 1, 1, 2, 9, 1, 1 };
static __declspec(section ".data") s32 tC[143] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF, 0x10, 0x11, 0x12, 0x13, 0x12, 0xD, 0x14, 0xD, 0x15, 0xD, 0x16, 0xD, 0x17, 0xD, 0xD, 0x18, 0xD, 0xD, 0x19, 0xD, 0x19, 0x1A, 0xD, 0x19, 0xD, 0x19, 0xD, 0x1B, 0xD, 0x1B, 0x1A, 0xD, 0x1B, 0xD, 0x1B, 0x1C, 0xD, 0x17, 0xD, 0xD, 0x1D, 0xD, 0x1D, 0xD, 0x1D, 0xD, 0x1D, 0xD, 0x1E, 0xD, 0x1E, 0xD, 0x1E, 0xD, 0x1F, 0xD, 0x20, 0x21, 0xD, 0x20, 0xD, 0x20, 0x22, 0x23, 0x22, 0xD, 0x24, 0x22, 0xD, 0x22, 0x25, 0xD, 0xD, 0x26, 0xD, 0xD, 0x27, 0x28, 0xD, 0x29, 0xD, 0x17, 0xD, 0xD, 0x1F, 0xD, 0x2A, 0xD, 0xD, 0xD, 0x2B, 0xD, 0xD, 0x2C, 0xD, 0x2D, 0x2D, 0x2E, 0x2F, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0xD, 0x39, 0xD, 0xD, 0x3A, 0xD, 0x3B, 0xD, 0xD, 0x3C, 0xD, 0xD, 0x3D, 0xD, 0x3D, 0xD, 0x3E, 0xD, 0x3E };
__declspec(section ".data") u8 lbl_802C952C[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802C9534[18] = { (void *)fn_80090B0C, (void *)fn_80249AC4, (void *)fn_80090970, (void *)fn_800902FC, (void *)fn_800907D0, (void *)fn_8023D198, (void *)fn_80090C18, (void *)fn_8008F16C, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_80090470, (void *)fn_80090358, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_80090C68, (void *)fn_800903E4 };
typedef struct { f32 x, y, z; } V3;
extern int lbl_8035B308;
extern int lbl_8035B460;
extern int lbl_8035B530;
extern int lbl_8035B65C;
extern int lbl_8035B374;
extern u32 lbl_803608E8;
extern f32 lbl_803608FC, lbl_80360900, lbl_80360904, lbl_80360908;
extern char lbl_80360740[4], lbl_803608EC[4], lbl_803608F4[4], lbl_8036090C[4];
extern char lbl_80360914[4], lbl_8036091C[4], lbl_80360924[4], lbl_8036092C[4], lbl_80360934[4], lbl_8036093C[4], lbl_80360944[4], lbl_8036094C[4], lbl_80360954[4], lbl_8036095C[4];
u32 rand(void);
int fn_800F6CD0(int, const char *);
u32 fn_800F8274(u32, const char *);
u32 fn_800F9398(int, const char *);
void fn_800F7EC0(int);
void fn_800F7E98(void);
void fn_800604C4(int, int, int, int);
void fn_8018DFAC(int, int, u32);
void fn_8019B7E8(int, int);
VE *fn_80233550(int, const char *);
void fn_8022BCD8(u32, const char *, char *);
void fn_8022BE28(u32, int);
void fn_8022BF30(u32, int, int, f32);
void fn_80236AC0(u32);
void fn_80236B14(u32);
int fn_8023F5E8(int, int);
void fn_8023F864(int, int);
void fn_8023F9C8(int, int);
int fn_802401A0(int);
int fn_802401D0(int);
int fn_802402E0(int);
int fn_802405B8(int);
void fn_80240274(int, int);
void fn_80240948(int, char *, int);
void fn_80240DBC(int, f32);
void fn_8024118C(int, int, int);
void fn_8024125C(int, int);
void fn_802413D8(int, int, f32, int, int, int);
void fn_80241588(int, int, int, f32);
int fn_80241628(int, int, int);
int fn_80242144(int, int);
void fn_80242BC0(int, const char *, int, int, int, int);
void fn_80249008(int, int);
int fn_80249058(int, int);
int fn_8024909C(int, int);
void fn_802490E0(int, int, f32);
int fn_802491DC(int, int);
int fn_802494A4(int, int);

#define E0 (*(u32 *)(p + 0xe0))
#define EO (*(VO **)(p + 0xe0))
#define I(o) (*(int *)(p + (o)))
#define PF(o) (**(f32 **)(p + (o)))
#define PI(o) (**(int **)(p + (o)))
#define PU(o) (**(u32 **)(p + (o)))
#define VP(o) (*(VO **)(p + (o)))

static inline void skA(int p) {
    int *s = *(int **)(p + 0x144);
    if (s == 0) fn_8022BE28(E0, 0);
    else switch (*s) {
    case 2: fn_8022BCD8(E0, ((char *)s68C), lbl_80360740); break;
    case 1: default: fn_8022BE28(E0, 0); break;
    }
}
static inline void skB(int p) {
    int *s = *(int **)(p + 0x144);
    if (s == 0) fn_8022BCD8(E0, ((char *)s698), lbl_80360740);
    else switch (*s) {
    case 2: fn_8022BCD8(E0, ((char *)s6A4), lbl_80360740); break;
    case 1: default: fn_8022BCD8(E0, ((char *)s698), lbl_80360740); break;
    }
}
static inline void path(int p, char *s) {
    fn_802494A4(p, 0xb);
    fn_80240274(p, 0);
    fn_80240948(p, s, 0);
}
static inline void offs(int p) {
    fn_8023F864(p, 0);
    fn_8023F864(p, 1);
    fn_8023F864(p, 2);
    fn_8023F864(p, 3);
    fn_8023F864(p, 4);
    fn_8023F864(p, 5);
}

void fn_8008F16C(int p, int st) {
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
        skA(p);
        fn_80241628(p, 0, 0);
        I(0x118) = *(int *)(lbl_8035B308 + 0x48);
        I(0x170) = fn_800F8274(*(u32 *)(*(int *)(E0 + 0xa0) + 0xa8), lbl_803608EC);
        if (*(void **)(p + 0x16c) == 0) {
            u32 r = fn_800F9398(*(int *)(lbl_8035B460 + 8) + 0x90, lbl_803608F4);
            if ((void *)lbl_8035B530 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B530);
            *(C8018E150 **)(p + 0x16c) = new C8018E150;
            fn_800F7E98();
            if (*(void **)(p + 0x16c) == 0) fn_800604C4(-4, 0, 0, 0);
            if (*(void **)(p + 0x16c) != 0) {
                fn_8018DFAC(I(0x16c), *(int *)(lbl_8035B460 + 8), r);
                PU(0x16c) &= ~0x800;
                fn_8019B7E8(*(int *)(lbl_8035B65C + 0xc), I(0x16c));
            }
        }
        if (*(int *)(E0 + 0x114) == 0) {
            EO->getPos((void *)(p + 0x160), 0, 0, 0, 0);
            fn_802494A4(p, 2);
        }
        break;
    case 1:
        *(f32 *)(E0 + 0x110) = lbl_803608FC;
        fn_80241628(p, 1, 0);
        fn_80241588(p, 2, 0, lbl_80360900);
        break;
    case 2:
        skA(p);
        if (I(0x14c) != 0) fn_802494A4(p, 6);
        else if (*(void **)(p + 300) != 0 && PI(300) != 0) {
            fn_8023F5E8(p, I(0x118));
            fn_80241628(p, 3, 0);
            fn_80241588(p, 2, 0, lbl_80360900);
            fn_802491DC(p, 2);
        } else {
            fn_8023F5E8(p, I(0x118));
            fn_80241628(p, 2, 0);
            fn_80241588(p, 7, 0, lbl_80360900);
        }
        break;
    case 3:
        fn_8023F5E8(p, I(0x118));
        fn_80241628(p, 3, 0);
        fn_80241588(p, 1, 0, lbl_80360900);
        break;
    case 4:
        fn_80241628(p, 3, 0);
        I(0x148) = 1;
        fn_80241588(p, 0, 0, lbl_80360900);
        fn_802491DC(p, 0);
        fn_802490E0(p, 3, PF(0x138));
        PU(0x16c) |= lbl_803608E8;
        break;
    case 5:
        *(f32 *)(E0 + 0x110) = lbl_803608FC;
        fn_80249008(p, 1);
        fn_80241628(p, 0, 0);
        fn_802401A0(p);
        fn_802491DC(p, 6);
        fn_80241588(p, 4, 0, lbl_80360900);
        break;
    case 6:
        fn_802401A0(p);
        fn_80241628(p, 3, 0);
        fn_80241588(p, 3, 0, lbl_80360900);
        I(0x15c) = 0;
        skB(p);
        fn_8022BF30(E0, 0, 1, lbl_80360904);
        fn_8023F9C8(p, 2);
        fn_802490E0(p, 1, lbl_80360908);
        break;
    case 7:
        fn_80241628(p, 0, 0);
        fn_80241588(p, 6, 0, lbl_80360900);
        break;
    case 8:
        fn_802401A0(p);
        fn_80241628(p, 3, 0);
        fn_80241588(p, 2, 0, lbl_80360900);
        skB(p);
        fn_8022BF30(E0, 0, 1, lbl_80360904);
        fn_8023F9C8(p, 2);
        fn_802490E0(p, 1, lbl_80360908);
        fn_8024125C(p, 0);
        break;
    case 9:
        fn_802401A0(p);
        fn_8022BCD8(E0, ((char *)s698), lbl_80360740);
        fn_8022BF30(E0, 0, 1, lbl_80360904);
        fn_80241628(p, 1, 0);
        fn_80241588(p, 2, 0, lbl_80360900);
        fn_802491DC(p, 2);
        fn_8024125C(p, 1);
        break;
    case 10:
        fn_802401D0(p);
        fn_80241628(p, 3, 0);
        fn_80241588(p, 3, 0, lbl_80360900);
        skB(p);
        skA(p);
        fn_8023F9C8(p, 5);
        fn_802490E0(p, 1, lbl_80360908);
        fn_8024125C(p, 0);
        break;
    case 11: {
        int i;
        *(f32 *)(E0 + 0x110) = lbl_803608FC;
        fn_80241628(p, 4, 0);
        fn_80241588(p, 2, 0, lbl_80360900);
        skB(p);
        skA(p);
        fn_8023F9C8(p, 5);
        fn_802490E0(p, 1, lbl_80360908);
        fn_802401D0(p);
        fn_80236AC0(E0);
        for (i = 0; i < I(0x5c); i++) fn_8024909C(p, i);
        offs(p);
        if (I(0x148) != 0) PU(0x16c) |= lbl_803608E8;
        break;
    }
    case 12:
        fn_80241628(p, 3, 0);
        fn_80241588(p, 2, 0, lbl_80360900);
        fn_802490E0(p, 4, PF(0x13c));
        break;
    case 13:
        return;
    case 14:
        fn_80249008(p, 0);
        fn_80249008(p, 3);
        I(0x148) = 0;
        PU(0x16c) &= ~0x800;
        break;
    case 15:
        fn_80249008(p, 6);
        break;
    case 16:
        I(0x15c) = 0;
        break;
    case 17:
        return;
    case 18:
        fn_802401D0(p);
        break;
    case 19:
        fn_802401D0(p);
        fn_80240DBC(p, lbl_80360908);
        break;
    case 20:
        fn_80249008(p, 4);
        break;
    case 21:
        fn_802494A4(p, 4);
        break;
    case 22:
        fn_8023F9C8(p, 1);
        fn_8023F9C8(p, 2);
        fn_8023F9C8(p, 3);
        fn_8023F9C8(p, 4);
        fn_8023F9C8(p, 5);
        fn_8022BCD8(E0, ((char *)s698), lbl_80360740);
        fn_8022BF30(E0, 0, 1, lbl_80360904);
        fn_802491DC(p, 1);
        fn_8024125C(p, 2);
        break;
    case 23:
        fn_802494A4(p, 2);
        break;
    case 24:
        if ((int)(rand() % 10) < 3) fn_802494A4(p, 6);
        break;
    case 25:
        I(0x150) = 0;
        fn_802405B8(p);
        break;
    case 26:
        fn_802405B8(p);
        break;
    case 27:
        I(0x150) = 1;
        fn_802405B8(p);
        break;
    case 28:
        *(f32 *)(E0 + 0x110) = lbl_803608FC;
        break;
    case 29:
        if (I(0x150) == 1) fn_802494A4(p, 7);
        break;
    case 30:
        fn_802494A4(p, 5);
        break;
    case 31:
        fn_802494A4(p, 3);
        break;
    case 32:
        I(0x14c) = 1;
        break;
    case 33:
        I(0x14c) = 1;
        fn_802494A4(p, 6);
        break;
    case 34:
        I(0x14c) = 0;
        break;
    case 35:
        I(0x14c) = 0;
        fn_802494A4(p, 2);
        break;
    case 36:
        fn_802401A0(p);
        I(0x14c) = 0;
        if (I(0x15c) == 1) {
            EO->setPos((void *)(p + 0x160), 0, 0, 0, 0);
            fn_802494A4(p, 10);
        }
        break;
    case 37:
        I(0x154) = I(0xe4);
        I(0x158) = I(0xec);
        EO->getPos((void *)(p + 0x160), 0, 0, 0, 0);
        fn_802494A4(p, 2);
        break;
    case 38: {
        V3 v;
        VE *e;
        VP(0x118)->getPos(&v, 0, 0, 0, 0);
        v.z = v.z + lbl_803608FC;
        { int *s = *(int **)(p + 0x144);
        if (s == 0) e = fn_80233550(lbl_8035B374, ((char *)s6B0));
        else switch (*s) {
        case 2: e = fn_80233550(lbl_8035B374, ((char *)s6BC)); break;
        case 1: default: e = fn_80233550(lbl_8035B374, ((char *)s6B0)); break;
        } }
        if (e != 0) e->fire(E0, &v, lbl_80360740, lbl_803608EC);
        fn_802491DC(p, 0);
        break;
    }
    case 39: {
        VO *o;
        fn_802402E0(p);
        o = VP(0x154);
        if (o != 0) o->send(lbl_8036090C, E0, 0, *(void **)(p + 0x158), 0);
        break;
    }
    case 40:
        fn_802401A0(p);
        I(0x15c) = 1;
        if (I(0x14c) == 0) {
            EO->setPos((void *)(p + 0x160), 0, 0, 0, 0);
            fn_802494A4(p, 10);
        }
        break;
    case 41:
        fn_802494A4(p, 9);
        break;
    case 42:
        fn_802494A4(p, 10);
        break;
    case 43:
        fn_80240274(p, 0);
        fn_802401D0(p);
        fn_8023F5E8(p, I(0x118));
        fn_802494A4(p, 2);
        break;
    case 44:
        fn_802494A4(p, 8);
        break;
    case 45:
        fn_802494A4(p, 0xb);
        fn_802402E0(p);
        break;
    case 46: path(p, lbl_80360914); break;
    case 47: path(p, lbl_8036091C); break;
    case 48: path(p, lbl_80360924); break;
    case 49: path(p, lbl_8036092C); break;
    case 50: path(p, lbl_80360934); break;
    case 51: path(p, lbl_8036093C); break;
    case 52: path(p, lbl_80360944); break;
    case 53: path(p, lbl_8036094C); break;
    case 54: path(p, lbl_80360954); break;
    case 55: path(p, lbl_8036095C); break;
    case 56:
        if (*(void **)(p + 0xf0) != 0) fn_802413D8(p, I(0xf0), lbl_80360900, 0, 1, I(0xec));
        break;
    case 57:
        fn_802494A4(p, 0xc);
        break;
    case 58:
        if (*(void **)(p + 300) != 0 && PI(300) != 0) fn_802494A4(p, 2);
        else fn_802494A4(p, 8);
        break;
    case 59:
        if (*(void **)(p + 0xf0) != 0 && *(int *)(*(int *)(*(int *)(lbl_8035B308 + 0x48) + 600) + 0x300) == 0)
            fn_8024118C(p, I(0xf0), 0);
        break;
    case 60:
        if (fn_800F6CD0(I(0x140), lbl_80360740) == 0) fn_80242BC0(fn_80242144(p, 3), *(const char **)(p + 0x140), 0, 0, 0, 0);
        break;
    case 61: {
        int i;
        fn_80236B14(E0);
        for (i = 0; i < I(0x5c); i++) fn_80249058(p, i);
        if (I(0x148) != 0) PU(0x16c) &= ~0x800;
        offs(p);
        break;
    }
    case 62: {
        int i;
        fn_80236AC0(E0);
        for (i = 0; i < I(0x5c); i++) fn_8024909C(p, i);
        offs(p);
        if (I(0x148) != 0) PU(0x16c) |= lbl_803608E8;
    }
    case 63:
        break;
    }
}
}

} /* extern "C" */
#undef E0
#undef EO
#undef I
#undef PF
#undef PI
#undef PU
#undef VP
} // namespace n8008F16C

namespace n800902FC {

extern "C" {



} /* extern "C" */

extern "C" {
void fn_80242210(int);
struct VCall_fn_800902FC_0 { char vptr_pad[0x68]; virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void m(int); };

void fn_800902FC(u32 param_1) {
    u32 iVar1;

    iVar1 = *(u32 *)(param_1 + 0x16c);
    if (iVar1 != 0) {
        if (iVar1 != 0) {
            ((VCall_fn_800902FC_0 *)(iVar1))->m((u32)(1));
        }
        *(u32 *)(param_1 + 0x16c) = 0;
    }
    fn_80242210((int)(param_1));
}
}
} // namespace n800902FC

namespace n80090358 {

extern "C" {

} /* extern "C" */

extern "C" {
extern char lbl_803608D8[0x6];
extern char lbl_803608E0[0x7];
struct VCall_fn_80090358_0 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void m(int); };
struct VCall_fn_80090358_1 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void m(int); };
struct VCall_fn_80090358_2 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void m(int); };
struct VCall_fn_80090358_3 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void m(int); };

void fn_80090358(s32 *param_1) {
    ((VCall_fn_80090358_0 *)(param_1))->m((s32)(((char *)lbl_80299668))); /* "PLYRLIVE" */
    ((VCall_fn_80090358_1 *)(param_1))->m((s32)(((char *)lbl_8029965C))); /* "PLYRDEAD" */
    ((VCall_fn_80090358_2 *)(param_1))->m((s32)(lbl_803608D8)); /* "CINON" */
    ((VCall_fn_80090358_3 *)(param_1))->m((s32)(lbl_803608E0)); /* "CINOFF" */
}
}
} // namespace n80090358

namespace n800903E4 {

extern "C" {

} /* extern "C" */

extern "C" {
extern char lbl_803608D8[0x6];
extern char lbl_803608E0[0x7];
struct VCall_fn_800903E4_0 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void m(int); };
struct VCall_fn_800903E4_1 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void m(int); };
struct VCall_fn_800903E4_2 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void m(int); };
struct VCall_fn_800903E4_3 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void m(int); };

void fn_800903E4(s32 *param_1) {
    ((VCall_fn_800903E4_0 *)(param_1))->m((s32)(((char *)lbl_80299668))); /* "PLYRLIVE" */
    ((VCall_fn_800903E4_1 *)(param_1))->m((s32)(((char *)lbl_8029965C))); /* "PLYRDEAD" */
    ((VCall_fn_800903E4_2 *)(param_1))->m((s32)(lbl_803608D8)); /* "CINON" */
    ((VCall_fn_800903E4_3 *)(param_1))->m((s32)(lbl_803608E0)); /* "CINOFF" */
}
}
} // namespace n800903E4

namespace n80090470 {
extern "C" {

typedef struct S { char pad[328]; int f148; } S;
extern f32 lbl_803608FC;
void fn_800904CC(S *s, f32 a, f32 b);
void fn_8023FE08(S *s, f32 a);
void fn_80090470(S *s, f32 a) {
    if (s->f148 != 0) fn_800904CC(s, a, lbl_803608FC);
    fn_8023FE08(s, a);
}
}
} // namespace n80090470

namespace n800904CC {

// fn_800904CC: NonMatching draft (wBX), DIFF 8: sc init K load and d copy stores scheduled 1 slot off.
extern "C" {

struct V3 { f32 x, y, z; };
struct G { u8 pad[16]; void *h; u8 pad20[12]; u32 fl; };
struct N {
    u8 pad0[48];
    G *g;
    u8 pad52[52];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void s11(f32);
    u8 pad108[12];
    void *m120;
};
struct OB {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void s13(V3 *, V3 *, V3 *, V3 *, int);
};
struct P {
    u8 pad0[224];
    OB *o224;
    u8 pad228[52];
    OB *o280;
    u8 pad284[80];
    N *n364;
    void *m368;
};
struct T { u8 pad12[12]; void (*f12)(void *, V3 *); u8 pad16[12]; void (*f28)(void *, V3 *, V3 *, V3 *); };
extern T lbl_803286D0;
extern f32 lbl_803608FC, lbl_80360904, lbl_80360908, lbl_80360968, lbl_8036096C;
extern u32 lbl_80360964;
void fn_80107244(void *, V3 *);
void fn_80100F24(V3 *, V3 *);
void fn_80101820(V3 *);
void fn_80101414(V3 *, V3 *, f32);
void fn_80107F3C(void *, V3 *);
void fn_80190C98(N *);

static inline f32 dot(V3 *a, V3 *b) { return a->x * b->x + a->y * b->y + a->z * b->z; }

static inline void h12(N *n, V3 *m) { G *g = n->g; if (g) { lbl_803286D0.f12(g->h, m); g->fl |= lbl_80360964; fn_80190C98(n); } }
static inline void h28(N *n, V3 *a, V3 *b, V3 *c) { G *g = n->g; if (g) { lbl_803286D0.f28(g->h, a, b, c); g->fl |= lbl_80360964; fn_80190C98(n); } }
static inline void cross(V3 *r, V3 *a, V3 *b) { r->x = a->y * b->z - a->z * b->y; r->y = a->z * b->x - a->x * b->z; r->z = a->x * b->y - a->y * b->x; }
static inline void neg(V3 *v) { v->x = -v->x; v->y = -v->y; v->z = -v->z; }
void fn_800904CC(P *p, f32 dt, f32 s) {
    G *g;
    N *n;
    V3 m, t, a, b, c, d, r, u, sc;
    if (p->n364) {
        fn_80107244(p->m368, &m);
        p->o224->s13(0, &a, &b, &c, 0);
        *(volatile f32 *)&sc.x = s;
        *(volatile f32 *)&sc.y = *(volatile f32 *)&lbl_803608FC;
        *(volatile f32 *)&sc.z = s;
        p->o280->s13(&t, 0, 0, 0, 0);
        t.z += lbl_803608FC;
        d.x = t.x - m.x;
        d.y = t.y - m.y;
        d.z = t.z - m.z;
        fn_80100F24(&d, &c);
        fn_80101820(&d);
        if (dot(&d, &a) < lbl_80360908) {
            f32 k = dot(&d, &b);
            d.x = a.x; d.y = a.y; ((f32 *)&r)[5] = a.z;
            if (k > lbl_80360904) fn_80101414(&d, &c, lbl_80360968);
            else fn_80101414(&d, &c, lbl_8036096C);
        }
        neg(&d);
        u = c;
        neg(&u);
        cross(&r, &u, &d);
        fn_80101820(&r);
        {
            n = p->n364;
            g = n->g;
            if (g) { lbl_803286D0.f28(g->h, &u, &d, &r); g->fl |= lbl_80360964; fn_80190C98(n); }
        }
        if (p->n364->m120) fn_80107F3C(p->n364->m120, &sc);
        {
            n = p->n364;
            g = n->g;
            if (g) { lbl_803286D0.f12(g->h, &m); g->fl |= lbl_80360964; fn_80190C98(n); }
        }
        p->n364->s11(dt);
    }
}

}
} // namespace n800904CC

namespace n800907D0 {

extern "C" {

extern f32 lbl_80360904;
void fn_80241E0C(void *);

void fn_800907D0(u8 *p) {
    *(s32 *)(p + 280) = 0;
    *(s32 *)(p + 284) = 0;
    *(s32 *)(p + 288) = 0;
    *(s32 *)(p + 292) = 0;
    *(s32 *)(p + 296) = 0;
    *(s32 *)(p + 300) = 0;
    *(s32 *)(p + 304) = 0;
    *(s32 *)(p + 308) = 0;
    *(s32 *)(p + 312) = 0;
    *(s32 *)(p + 316) = 0;
    *(s32 *)(p + 320) = 0;
    *(s32 *)(p + 324) = 0;
    *(s32 *)(p + 328) = 0;
    *(s32 *)(p + 332) = 0;
    *(s32 *)(p + 336) = 0;
    *(s32 *)(p + 340) = 0;
    *(s32 *)(p + 344) = 0;
    *(s32 *)(p + 348) = 0;
    *(f32 *)(p + 372) = lbl_80360904;
    fn_80241E0C(p);
}

} /* extern "C" */
} // namespace n800907D0

namespace n80090844 {
extern "C" {

// the tables are the TU statics defined with fn_8008F16C
#define d540 n8008F16C::d540
#define d560 n8008F16C::d560
#define d656 n8008F16C::d656
#define d692 n8008F16C::d692
#define d836 n8008F16C::d836
#define d964 n8008F16C::d964
#define d1084 n8008F16C::d1084
#define d1136 n8008F16C::d1136
#define d1292 n8008F16C::d1292
#define d1748 n8008F16C::d1748
extern f32 lbl_80360904;
typedef struct T {
    char p0[40]; void *f28; int f2C; void *f30; char p34[84-52]; int f54; void *f58; int f5C; char p60[104-96]; int f68; void *f6C;
    char p70[120-112]; void *f78; int f7C; int f80; int f84; int f88; int f8C; char p90[4]; int f94; char p98[196-152];
    void *fC4; void *fC8; void *fCC; char pD0[244-208]; void *fF4; char pF8[4]; int fFC; char p100[268-256]; void *f10C;
    char p110[280-272]; int a[18]; char p160[364-352]; int f16C; int f170; f32 f174;
} T;
void fn_80090844(T *t) {
    int i;
    t->f54 = 39;
    t->f2C = 38;
    t->f68 = 13;
    t->f5C = 8;
    t->f80 = 5;
    t->f7C = 8;
    t->f84 = 3;
    t->f88 = 9;
    t->f8C = 0;
    t->f94 = 6;
    t->f58 = d1136;
    t->f28 = d1292;
    t->f30 = d1748;
    t->f6C = d1084;
    t->f78 = d836;
    t->fC4 = d540;
    t->fC8 = d560;
    t->fCC = d656;
    t->fF4 = d692;
    t->fFC = 0;
    t->f10C = d964;
    for (i = 0; i < 18; i++) t->a[i] = 0;
    t->f16C = 0;
    t->f170 = 0;
    t->f174 = lbl_80360904;
}
}
#undef d540
#undef d560
#undef d656
#undef d692
#undef d836
#undef d964
#undef d1084
#undef d1136
#undef d1292
#undef d1748
} // namespace n80090844

namespace n80090970 {

extern "C" {

/* QV=2.0p1 */
typedef struct S80090970 {
    u8 pad[284];
    u32 f284;
    u32 f288;
    u32 f292;
    u32 f296;
    u32 f300;
    u32 f304;
    u32 f308;
    u32 f312;
    u32 f316;
    u32 f320;
    u32 f324;
} S80090970;

u32 fn_8023F52C(S80090970 *p, char *a, char *b, char *name, s32 c, s32 d);
void fn_8023F214(S80090970 *p);
extern char lbl_80360740[4];
extern char lbl_80360970[7];
extern char lbl_80360978[5];

#pragma opt_propagation off
void fn_80090970(S80090970 *p) {
    char *str = ((char *)lbl_802995A8);
    p->f284 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 288, 1, 0);
    p->f288 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 304, 1, 0);
    p->f292 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 320, 1, 0);
    p->f296 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 332, 1, 0);
    p->f300 = fn_8023F52C(p, lbl_80360740, lbl_80360740, lbl_80360970, 0, 0);
    p->f304 = fn_8023F52C(p, lbl_80360740, lbl_80360978, str + 348, 1, 0);
    p->f308 = fn_8023F52C(p, lbl_80360740, lbl_80360978, str + 364, 1, 0);
    p->f312 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 380, 1, 0);
    p->f316 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 396, 1, 0);
    p->f320 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 412, 1, 0);
    p->f324 = fn_8023F52C(p, lbl_80360740, lbl_80360740, str + 424, 0, 0);
    fn_8023F214(p);
}
#pragma opt_propagation reset

} /* extern "C" */
#pragma opt_propagation reset
} // namespace n80090970

namespace n80090B0C {

extern "C" {

} /* extern "C" */

extern "C" {
extern u8 lbl_802C952C[];
void __dl__FPv(int);
void __dt__9C8024262CFv(int, int);
struct VCall_fn_80090B0C_0 { virtual void p0(); virtual void p1(); virtual void p2(); virtual void m(); };

s32 * fn_80090B0C(s32 *param_1, s16 param_2) {
    if (param_1 != (s32 *)0x0) {
        *param_1 = (s32)lbl_802C952C;
        ((VCall_fn_80090B0C_0 *)(param_1))->m();
        __dt__9C8024262CFv((int)(param_1), (int)(0));
        if (0 < param_2) {
            __dl__FPv((int)(param_1));
        }
    }
    return param_1;
}
}
} // namespace n80090B0C

namespace n80090B80 {

#pragma optEH2 on

extern "C" {

extern void *lbl_8035B530;
extern u8 lbl_802C952C[];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_80090844(void *);

} /* extern "C" */


struct C80090B80 : C8024262C {
    u8 pad[0x178];
    C80090B80() {
        *(void **)this = lbl_802C952C;
        fn_80090844(this);
    }
};

extern "C" void *fn_80090B80(void) {
    C80090B80 *r;
    if (lbl_8035B530 == NULL) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035B530);
    r = new C80090B80;
    fn_800F7E98();
    if (r == NULL) {
        fn_800604C4(-4, 0, 0, 0);
    }
    return r;
}
#pragma optEH2 reset
} // namespace n80090B80

namespace n80090C18 {

extern "C" {

s32 fn_802421C0(void *, s32);

s32 fn_80090C18(void *p, s32 a) {
    switch (a) {
    case 4:
        return fn_802421C0(p, 1);
    case 5:
        return fn_802421C0(p, 2);
    }
    return 1;
}

} /* extern "C" */
} // namespace n80090C18

namespace n80090C68 {

extern "C" {

extern "C" {

}


extern "C" int fn_80090C68(void *arg0, u32 arg1) {
    void *p = *(void **)((u8 *)arg0 + 0x98);
    if (p != NULL) {
        return (*(int **)((u8 *)p + 0xC))[arg1];
    }
    switch (arg1) {
    case 0: return 1;
    case 1: return 0;
    case 2: return 1;
    case 3: return 0;
    case 4: return 0;
    case 5: return 0;
    case 6: return 0;
    case 7: return 1;
    default: return 1;
    }
}

} /* extern "C" */
} // namespace n80090C68
