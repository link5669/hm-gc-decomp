#include "common.h"
extern "C" {
extern const char lbl_8029984C[];
extern u8 lbl_80360B60[];
extern u8 lbl_80360B68[];
extern char lbl_80360B70[8], lbl_80360BD8[8], lbl_80360BF4[8], lbl_80360BD0[8], lbl_80360BFC[8], lbl_80360C04[8], lbl_80360C0C[8], lbl_80360C14[8];
extern u8 lbl_80360B74[];
extern u8 lbl_80360B7C[];
extern u8 lbl_80360B80[];
extern u8 lbl_80360B88[];
extern u8 lbl_80360B90[];
extern u8 lbl_80360B98[];
extern u8 lbl_80360BA0[];
extern u8 lbl_80360BA8[];
extern const char lbl_80299858[];
extern u8 lbl_80360BB0[];
extern u8 lbl_80360BB8[];
extern u8 lbl_80360BC0[];
extern const char lbl_80299864[];
extern u8 lbl_80360BC8[];
extern const char lbl_80299870[];
extern const char lbl_8029987C[];
extern char lbl_80360B70[8], lbl_80360BD8[8], lbl_80360BF4[8], lbl_80360BD0[8], lbl_80360BFC[8], lbl_80360C04[8], lbl_80360C0C[8], lbl_80360C14[8];
extern char lbl_80360B70[8], lbl_80360BD8[8], lbl_80360BF4[8], lbl_80360BD0[8], lbl_80360BFC[8], lbl_80360C04[8], lbl_80360C0C[8], lbl_80360C14[8];
extern const char lbl_80299888[];
extern const char lbl_80299894[];
extern const char lbl_802998A0[];
extern u8 lbl_80360BE0[];
extern const char lbl_802998AC[];
extern u8 lbl_80360BE8[];
void fn_80092E78(void);
void fn_80249AC4(void);
void fn_80092CF4(void);
void fn_80242210(void);
void fn_80092B54(void);
void fn_8023D198(void);
void fn_80092F84(void);
class O;
void fn_80091A9C(O *o, s32 idx);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_800922CC(void);
void fn_800921A4(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_80240054(void);
void fn_8023F5F4(void);
void fn_80092238(void);
#include "common.h"

#define V(n) virtual void n();
struct K8 { u32 a, b; };
class Cam { public: V(c0) V(c1) V(c2) V(c3) V(c4) V(c5) V(c6) V(c7) V(c8) V(c9) V(c10) V(c11) V(c12) V(c13) V(c14) V(c15) V(c16) V(c17) V(c18) V(c19)
    V(c20) V(c21) V(c22) virtual void v100(); virtual void v104(); V(c25) V(c26) V(c27) V(c28) V(c29) V(c30) V(c31) V(c32)
    virtual void play(char *, Cam *, int, s32 *, int);
    u8 pad[176]; u32 f180; };
class Lt { public: u8 p[128]; V(l0) V(l1) V(l2) V(l3) V(l4) V(l5) V(l6) V(l7) V(l8) V(l9) V(l10) V(l11) V(l12) V(l13) V(l14) V(l15) V(l16) V(l17) V(l18) V(l19)
    virtual void off(int); };
struct GG { u8 p[448]; Lt *f448; u8 p452[36]; Lt *f488; Lt *f492; };
struct St;
class O { public: u8 p0[96]; s32 f96; u8 p100[124]; Cam *f224; Cam *f228; u8 p232[4]; s32 *f236; u8 p240[40]; char *f280; s32 *f284; f32 *f288; f32 *f292; char *f296;
    f32 *f300; s32 *f304; u8 p308[16]; s32 f324; s32 f328; s32 f332; u8 p336[12]; s32 f348; s32 f352; u32 *f356; u32 f360; s32 f364; s32 f368; };
__declspec(section ".data") u8 lbl_802CA050[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[2] = { (void *)lbl_8029984C, (void *)lbl_80360B60 };
static __declspec(section ".data") u8 sPad_224[4] = { 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_228[14] = { (void *)lbl_80360B68, (void *)lbl_80360B70, (void *)lbl_80360B70, (void *)lbl_80360B74, (void *)lbl_80360B74, (void *)lbl_80360B70, (void *)lbl_80360B70, (void *)lbl_80360B7C, (void *)lbl_80360B70, (void *)lbl_80360B70, (void *)lbl_80360B80, (void *)lbl_80360B70, (void *)lbl_80360B70, (void *)lbl_80360B70 };
static __declspec(section ".data") u8 sPad_260[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_26C[1] = { (void *)lbl_80360B88 };
static __declspec(section ".data") u8 sPad_270[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_27C[2] = { (void *)lbl_80360B90, (void *)lbl_80360B98 };
static __declspec(section ".data") u8 sPad_284[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_294[1] = { (void *)lbl_80360BA0 };
static __declspec(section ".data") u8 sPad_298[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_2A8[20] = { (void *)lbl_80360BA8, (void *)lbl_80299858, (void *)lbl_80360BB0, (void *)lbl_80360BB8, (void *)lbl_80360BC0, (void *)lbl_80299864, (void *)lbl_80360BC8, (void *)lbl_80299870, (void *)lbl_80360B88, (void *)lbl_80360B90, (void *)lbl_8029987C, (void *)lbl_80360BD0, (void *)lbl_80360BD8, (void *)lbl_80299888, (void *)lbl_80299894, (void *)lbl_802998A0, (void *)lbl_80360BE0, (void *)lbl_802998AC, (void *)lbl_80360BE8, (void *)lbl_80360BC0 };
static __declspec(section ".data") u8 sPad_2F8[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_300[1] = { (void *)lbl_80299864 };
static __declspec(section ".data") u8 sPad_304[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_30C[1] = { (void *)lbl_80360BC8 };
static __declspec(section ".data") u8 sPad_310[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_318[1] = { (void *)lbl_80299870 };
static __declspec(section ".data") u8 sPad_31C[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_324[1] = { (void *)lbl_80360B88 };
static __declspec(section ".data") u8 sPad_328[8] = { 0, 0, 0, 4, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_330[1] = { (void *)lbl_80360B90 };
static __declspec(section ".data") u8 sPad_334[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_33C[1] = { (void *)lbl_8029987C };
static __declspec(section ".data") u8 sPad_340[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_348[1] = { (void *)lbl_80360BD0 };
static __declspec(section ".data") u8 sPad_34C[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_354[1] = { (void *)lbl_80360BD8 };
static __declspec(section ".data") u8 sPad_358[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_360[1] = { (void *)lbl_80299888 };
static __declspec(section ".data") u8 sPad_364[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_36C[1] = { (void *)lbl_80299894 };
static __declspec(section ".data") u8 sPad_370[8] = { 0, 0, 0, 0xA, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_378[1] = { (void *)lbl_802998A0 };
static __declspec(section ".data") u8 sPad_37C[8] = { 0, 0, 0, 0xB, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_384[1] = { (void *)lbl_80360BE0 };
static __declspec(section ".data") u8 sPad_388[8] = { 0, 0, 0, 0xC, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_390[1] = { (void *)lbl_802998AC };
static __declspec(section ".data") u8 sPad_394[8] = { 0, 0, 0, 0xD, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_39C[1] = { (void *)lbl_80360BE8 };
static __declspec(section ".data") u8 sPad_3A0[68] = { 0, 0, 0, 0xE, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 0, 0xA, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0xD, 0, 0, 0, 0xE };
static __declspec(section ".data") s32 tI[15] = { 0, 4, 7, 0xA, 0xB, 0xE, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x18, 0x1B, 0x1E };
static __declspec(section ".data") s32 tB[34] = { 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 4, 2, 1, 1, 2, 2, 4, 4, 4, 4, 4, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1 };
static __declspec(section ".data") s32 tS[34] = { 0, 1, 2, 3, 4, 5, 4, 4, 6, 4, 4, 4, 7, 4, 4, 8, 9, 0xA, 0xB, 0xC, 0xD, 4, 0xE, 4, 4, 0xF, 4, 4, 0x10, 4, 4, 0x11, 4, 0x11 };
__declspec(section ".data") u8 lbl_802CA580[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802CA588[18] = { (void *)fn_80092E78, (void *)fn_80249AC4, (void *)fn_80092CF4, (void *)fn_80242210, (void *)fn_80092B54, (void *)fn_8023D198, (void *)fn_80092F84, (void *)fn_80091A9C, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_800922CC, (void *)fn_800921A4, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_80240054, (void *)fn_8023F5F4, (void *)fn_80092238 };
// The TU string pool (.rodata 80299840-80299984) in its original order: strings that tables or other units name are
// globals, the strings the code uses are one static array each (statics are addressed relative to the pool
// start, like the original literals).
extern const char lbl_80299840[];
const char lbl_80299840[] = "MStation";
extern const char lbl_8029984C[];
const char lbl_8029984C[] = "FRCFIELD";
extern const char lbl_80299858[];
const char lbl_80299858[] = "UNBROKEN";
extern const char lbl_80299864[];
const char lbl_80299864[] = "SENDDIST";
extern const char lbl_80299870[];
const char lbl_80299870[] = "ANIMOVER";
extern const char lbl_8029987C[];
const char lbl_8029987C[] = "SDORFREE";
extern const char lbl_80299888[];
const char lbl_80299888[] = "ACTIVATE";
extern const char lbl_80299894[];
const char lbl_80299894[] = "DEACTIV8";
extern const char lbl_802998A0[];
const char lbl_802998A0[] = "SDORFOUT";
extern const char lbl_802998AC[];
const char lbl_802998AC[] = "SDORFADE";
static const char s8B8[] = "GRAVEYDL";
static const char s8C4[] = "SOULCOLL";
static const char s8D0[] = "SOULBLNK";
static const char s8DC[] = "%d/%d %s";
static const char s8E8[] = "SOULNEED";
static const char s8F4[] = "aLevelName";
static const char s900[] = "nSpiritsRequired";
static const char s914[] = "rAttackTime";
static const char s920[] = "rFXStartTime";
static const char s930[] = "aLockedSound";
static const char s940[] = "rFadeTime";
static const char s94C[] = "nColorMax";
static const char s958[] = "rTextRange";
static const char s964[] = "rForceFieldRange";
static const char s978[12] = "DOORNEED";   // padded: the pool ends at 80299984
extern "C" {
extern void *lbl_8035A0A4;
extern void *volatile lbl_8035B65C;
extern GG *lbl_80359F2C;
extern f32 lbl_80360BF0;
extern char lbl_80360B70[8], lbl_80360BD8[8], lbl_80360BF4[8], lbl_80360BD0[8], lbl_80360BFC[8], lbl_80360C04[8], lbl_80360C0C[8], lbl_80360C14[8];
void fn_80241628(O *, int, int);
int fn_8003C778(void *, Cam *, u32 **);
int fn_8003CF0C(void *, char *);
int fn_800F6CD0(char *, char *);
s32 fn_8003CD00(void *, char *);
s32 fn_8003CE68(void *, char *);
void *fn_8022C3F4(Cam *);
void fn_8022C128(Cam *, s32, s32, s32, int, f32);
void fn_802494A4(O *, int);
void fn_8022AD0C(Cam *);
void fn_802490E0(O *, int, f32);
void fn_8022A7A8(Cam *);
St *fn_80242144(O *, int);
void fn_80242BC0(St *, char *, Cam *, int, void *, void *);
u32 fn_8003C930(void *);
void fn_80240B50(O *, char *, int);
void fn_8023F9C8(O *, int);
void __ct__9C80253F24Fiiii(void *, char *, Cam *, int, s32 *);
void fn_800F6E88(K8 *, char *);
}
inline void Ld(O *o, char *x) { if (x && !fn_800F6CD0(x, lbl_80360B70)) fn_80240B50(o, x, 0); }
extern "C" void fn_80091A9C(O *o, s32 idx) {
    s32 *q;
    s32 i;
    s32 t;
    f32 v2;
    volatile f32 v;
    volatile s32 a;
    K8 b2;
    K8 b;
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
        if (!fn_8003C778(lbl_8035A0A4, o->f224, &o->f356)) {
            u32 m = o->f360;
            if (*o->f284 <= 0) *o->f356 |= m;
            else *o->f356 &= ~m;
        }
        if (fn_8003CF0C(lbl_8035A0A4, o->f280)) *o->f356 |= o->f360;
        if (!fn_800F6CD0(o->f280, lbl_80360B70)) {
            o->f324 = fn_8003CD00(lbl_8035A0A4, o->f280);
            o->f328 = fn_8003CE68(lbl_8035A0A4, o->f280);
        } else {
            o->f324 = 0;
            o->f328 = 0;
        }
        o->f332 = o->f324 - o->f328;
        o->f224->f180 |= 4;
        if (fn_8022C3F4(o->f224)) fn_8022C128(o->f224, 0, 0, 0, 1, lbl_80360BF0);
        if (*o->f356 & o->f360) fn_802494A4(o, 3);
        else fn_802494A4(o, 1);
        break;
    case 1:
        o->f224->v100();
        fn_8022AD0C(o->f224);
        break;
    case 2:
        fn_802490E0(o, 0, *o->f288);
        fn_802490E0(o, 1, *o->f292);
        break;
    case 3:
        o->f224->v104();
        fn_8022A7A8(o->f224);
        fn_80242BC0(fn_80242144(o, 2), lbl_80360BD8, 0, 0, 0, 0);
        *o->f356 |= o->f360;
        break;
    case 4:
        return;
    case 5:
        if (o->f352) {
            if (o->f348 || fn_8003C930(lbl_8035A0A4) >= (u32)*o->f284)
                o->f228->play(lbl_80360BF4, o->f224, 0, o->f236, 0);
            else
                Ld(o, o->f296);
        }
        break;
    case 6: fn_802494A4(o, 2); break;
    case 7:
        fn_80242BC0(fn_80242144(o, 3), lbl_80360BD0, 0, 0, 0, 0);
        fn_80242BC0(fn_80242144(o, 0), lbl_80360BFC, o->f224, 0, 0, 0);
        fn_80242BC0(fn_80242144(o, 0), (char *)((char *)lbl_80299888), o->f224, 0, 0, 0);
        fn_802494A4(o, 3);
        break;
    case 8:
        fn_8023F9C8(o, 0);
        fn_8023F9C8(o, 1);
        __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)((char *)lbl_802998A0), o->f224, 0, 0);
        if (!o->f368) {
            s32 w;
            a = 0;
            v = *o->f300;
            __ct__9C80253F24Fiiii(lbl_8035B65C, (char *)((char *)lbl_802998AC), o->f224, 0, (s32 *)&a);
            w = a ? *o->f304 : 0;
            fn_8022C128(o->f224, w, w, w, 0, v);
            if (o->f96 == 1) {
                if (a) fn_800F6E88(&b, lbl_80360C04);
                else fn_800F6E88(&b, lbl_80360C0C);
                fn_80242BC0(fn_80242144(o, 2), (char *)&b, 0, 0, o->f304, (f32 *)&v);
            }
        } else {
            o->f224->v104();
        }
        fn_80242BC0(fn_80242144(o, 2), lbl_80360C14, 0, 0, 0, 0);
        break;
    case 9: o->f348 = 1; break;
    case 10:
        o->f352 = 1;
        o->f224->v100();
        fn_8022AD0C(o->f224);
        fn_80242BC0(fn_80242144(o, 2), lbl_80360BD0, 0, 0, 0, 0);
        break;
    case 11:
        o->f352 = 0;
        o->f224->v104();
        fn_8022A7A8(o->f224);
        fn_80242BC0(fn_80242144(o, 2), lbl_80360BD8, 0, 0, 0, 0);
        break;
    case 12: o->f364 = 1; break;
    case 13: o->f364 = 0; break;
    case 14: if (o->f228 != o->f224) o->f368 = 0; break;
    case 15: if (o->f228 != o->f224) o->f368 = 1; break;
    case 16:
        if (o->f228 != o->f224) {
            s32 a = *o->f236;
            s32 w;
            v2 = *o->f300;
            w = a ? *o->f304 : 0;
            fn_8022C128(o->f224, w, w, w, 0, v2);
            if (o->f96 == 1) {
                                if (a) fn_800F6E88(&b2, lbl_80360C04);
                else fn_800F6E88(&b2, lbl_80360C0C);
                fn_80242BC0(fn_80242144(o, 2), (char *)&b2, 0, 0, o->f304, &v2);
            }
        }
        break;
    case 17: {
        if (lbl_80359F2C->f448) lbl_80359F2C->f448->off(0);
        if (lbl_80359F2C->f488) lbl_80359F2C->f488->off(0);
        if (lbl_80359F2C->f492) lbl_80359F2C->f492->off(0);
        break;
    }
    case 18: break;
    }
}
}
