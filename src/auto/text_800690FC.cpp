// One translation unit: fn_800690FC .. fn_8006FEA4 (34 former units; GC/2.0p1, lmw, readonly strings).
// The functions share two compiler-made int->float constants (lbl_8035F1E0, lbl_8035F208), the string pool at
// 80297908, the descriptor tables at 802BD3F8 and TU-level .bss, so they cannot link separately.
// fn_8006BB24 is schedule-equivalent, fn_8006D124 schedule- and register-equivalent, fn_8006F808
// register-equivalent; everything else is exact. One namespace per former unit.
#include "common.h"

extern "C" {
extern u8 lbl_8035E810[];
extern u8 lbl_8035E818[];
extern u8 lbl_8035E820[];
extern u8 lbl_8035E828[];
extern u8 lbl_8035E830[];
extern u8 lbl_8035E838[];
extern u8 lbl_8035E840[];
extern u8 lbl_8035E848[];
extern u8 lbl_8035E850[];
extern u8 lbl_8035E858[];
extern u8 lbl_8035E860[];
extern u8 lbl_8035E868[];
extern u8 lbl_8035E870[];
extern u8 lbl_8035E878[];
extern u8 lbl_8035E880[];
extern u8 lbl_8035E888[];
extern u8 lbl_8035E890[];
extern u8 lbl_8035E898[];
extern u8 lbl_8035E8A0[];
extern u8 lbl_8035E8A8[];
extern u8 lbl_8035E8B0[];
extern u8 lbl_8035E8B8[];
extern u8 lbl_8035E8C0[];
extern u8 lbl_8035E8C4[];
extern u8 lbl_8035E8C8[];
extern u8 lbl_8035E8CC[];
extern u8 lbl_8035E8D0[];
extern u8 lbl_8035E8D8[];
extern u8 lbl_8035E8E0[];
extern u8 lbl_8035E8E8[];
extern u8 lbl_8035E8F0[];
extern u8 lbl_8035E8F8[];
extern u8 lbl_8035E900[];
extern u8 lbl_8035E908[];
extern u8 lbl_8035E910[];
extern u8 lbl_8035E918[];
extern u8 lbl_8035E920[];
extern u8 lbl_8035E924[];
extern u8 lbl_8035E928[];
extern u8 lbl_8035E92C[];
extern u8 lbl_8035E934[];
extern u8 lbl_8035E93C[];
extern u8 lbl_8035E944[];
extern u8 lbl_8035E94C[];
extern u8 lbl_8035E954[];
extern u8 lbl_8035E95C[];
extern u8 lbl_8035E964[];
extern u8 lbl_8035E96C[];
extern u8 lbl_8035E974[];
extern u8 lbl_8035E97C[];
extern u8 lbl_8035E984[];
extern u8 lbl_8035E98C[];
extern u8 lbl_8035E994[];
extern u8 lbl_8035E99C[];
extern u8 lbl_8035E9A0[];
extern u8 lbl_8035E9A4[];
extern u8 lbl_8035E9AC[];
extern u8 lbl_8035E9B4[];
extern u8 lbl_8035E9BC[];
extern u8 lbl_8035E9C4[];
extern u8 lbl_8035E9CC[];
extern u8 lbl_8035E9D4[];
extern u8 lbl_8035E9DC[];
extern u8 lbl_8035E9E4[];
extern u8 lbl_8035E9EC[];
extern u8 lbl_8035E9F4[];
extern u8 lbl_8035E9FC[];
extern u8 lbl_8035EA04[];
extern u8 lbl_8035EA08[];
extern u8 lbl_8035EA0C[];
extern u8 lbl_8035EA10[];
extern u8 lbl_8035EA18[];
extern u8 lbl_8035EA20[];
extern u8 lbl_8035EA28[];
extern u8 lbl_8035EA30[];
extern u8 lbl_8035EA38[];
extern u8 lbl_8035EA40[];
extern u8 lbl_8035EA48[];
extern u8 lbl_8035EA50[];
extern u8 lbl_8035EA58[];
extern u8 lbl_8035EA60[];
extern u8 lbl_8035EA68[];
extern u8 lbl_8035EA70[];
extern u8 lbl_8035EA78[];
extern u8 lbl_8035EA80[];
extern u8 lbl_8035EA88[];
extern u8 lbl_8035EA90[];
extern u8 lbl_8035EA98[];
extern u8 lbl_8035EAA0[];
extern u8 lbl_8035EAA8[];
extern u8 lbl_8035EAB0[];
extern u8 lbl_8035EAB8[];
extern u8 lbl_8035EAC0[];
extern u8 lbl_8035EAC8[];
extern u8 lbl_8035EAD0[];
extern u8 lbl_8035EAD8[];
extern u8 lbl_8035EAE0[];
extern u8 lbl_8035EAE8[];
extern u8 lbl_8035EAF0[];
extern u8 lbl_8035EAF8[];
extern u8 lbl_8035EB00[];
extern u8 lbl_8035EB08[];
extern u8 lbl_8035EB10[];
extern u8 lbl_8035EB18[];
extern u8 lbl_8035EB20[];
extern u8 lbl_8035EB28[];
extern u8 lbl_8035EB30[];
extern u8 lbl_8035EB38[];
extern u8 lbl_8035EB40[];
extern u8 lbl_8035EB48[];
extern u8 lbl_8035EB50[];
extern u8 lbl_8035EB58[];
extern u8 lbl_8035EB60[];
extern u8 lbl_8035EB68[];
extern u8 lbl_8035EB70[];
extern u8 lbl_8035EB78[];
extern u8 lbl_8035EB80[];
extern u8 lbl_8035EB88[];
extern u8 lbl_8035EB90[];
extern u8 lbl_8035EB98[];
extern u8 lbl_8035EBA0[];
extern u8 lbl_8035EBA8[];
extern u8 lbl_8035EBB0[];
extern u8 lbl_8035EBB8[];
extern u8 lbl_8035EBC0[];
extern u8 lbl_8035EBC8[];
extern u8 lbl_8035EBD0[];
extern u8 lbl_8035EBD8[];
extern u8 lbl_8035EBE0[];
extern u8 lbl_8035EBE8[];
extern u8 lbl_8035EBF0[];
extern u8 lbl_8035EBF8[];
extern u8 lbl_8035EC00[];
extern u8 lbl_8035EC08[];
extern u8 lbl_8035EC10[];
extern u8 lbl_8035EC18[];
extern u8 lbl_8035EC20[];
extern u8 lbl_8035EC28[];
extern u8 lbl_8035EC30[];
extern u8 lbl_8035EC38[];
extern u8 lbl_8035EC40[];
extern u8 lbl_8035EC48[];
extern u8 lbl_8035EC50[];
extern u8 lbl_8035EC58[];
extern u8 lbl_8035EC60[];
extern u8 lbl_8035EC68[];
extern u8 lbl_8035EC70[];
extern u8 lbl_8035EC78[];
extern u8 lbl_8035EC80[];
extern u8 lbl_8035EC88[];
extern u8 lbl_8035EC90[];
extern u8 lbl_8035EC98[];
extern u8 lbl_8035ECA0[];
extern u8 lbl_8035ECA8[];
extern u8 lbl_8035ECB0[];
extern u8 lbl_8035ECB8[];
extern u8 lbl_8035ECC0[];
extern u8 lbl_8035ECC8[];
extern u8 lbl_8035ECD0[];
extern u8 lbl_8035ECD8[];
extern char lbl_8035F09C[4], lbl_8035F0A4[4], lbl_8035F0AC[4], lbl_8035EE70[4], lbl_8035F0D0[4], lbl_8035F0D8[4], lbl_8035ED68[4], lbl_8035F0E4[4], lbl_8035EE18[4], lbl_8035ECE0[4], lbl_8035F1C0[8], lbl_8035F1CC[4], lbl_8035F1D4[4], lbl_8035EEA8[4];
extern u8 lbl_8035ECE8[];
extern u8 lbl_8035ECF0[];
extern u8 lbl_8035ECF8[];
extern u8 lbl_8035ED00[];
extern u8 lbl_8035ED08[];
extern u8 lbl_8035ED10[];
extern u8 lbl_8035ED18[];
extern u8 lbl_8035ED20[];
extern u8 lbl_8035ED28[];
extern u8 lbl_8035ED30[];
extern u8 lbl_8035ED38[];
extern u8 lbl_8035ED40[];
extern u8 lbl_8035ED48[];
extern u8 lbl_8035ED50[];
extern u8 lbl_8035ED58[];
extern u8 lbl_8035ED60[];
extern char lbl_8035F09C[4], lbl_8035F0A4[4], lbl_8035F0AC[4], lbl_8035EE70[4], lbl_8035F0D0[4], lbl_8035F0D8[4], lbl_8035ED68[4], lbl_8035F0E4[4], lbl_8035EE18[4], lbl_8035ECE0[4], lbl_8035F1C0[8], lbl_8035F1CC[4], lbl_8035F1D4[4], lbl_8035EEA8[4];
extern u8 lbl_8035ED6C[];
extern u8 lbl_8035ED74[];
extern u8 lbl_8035ED7C[];
extern u8 lbl_8035ED84[];
extern u8 lbl_8035ED8C[];
extern u8 lbl_8035ED94[];
extern const char lbl_8035ED9C[8];
extern u8 lbl_8035EDAC[];
extern u8 lbl_8035EDB4[];
extern u8 lbl_8035EDBC[];
extern u8 lbl_8035EDC4[];
extern u8 lbl_8035EDCC[];
extern u8 lbl_8035EDD4[];
extern u8 lbl_8035EDDC[];
extern u8 lbl_8035EDE4[];
extern u8 lbl_8035EDEC[];
extern u8 lbl_8035EDF4[];
extern u8 lbl_8035EDFC[];
extern u8 lbl_8035EE04[];
extern u8 lbl_8035EE0C[];
extern u8 lbl_8035EE14[];
extern char lbl_8035F09C[4], lbl_8035F0A4[4], lbl_8035F0AC[4], lbl_8035EE70[4], lbl_8035F0D0[4], lbl_8035F0D8[4], lbl_8035ED68[4], lbl_8035F0E4[4], lbl_8035EE18[4], lbl_8035ECE0[4], lbl_8035F1C0[8], lbl_8035F1CC[4], lbl_8035F1D4[4], lbl_8035EEA8[4];
extern u8 lbl_8035EE20[];
extern u8 lbl_8035EE28[];
extern u8 lbl_8035EE30[];
extern u8 lbl_8035EE38[];
extern u8 lbl_8035EE40[];
extern u8 lbl_8035EE48[];
extern u8 lbl_8035EE50[];
extern u8 lbl_8035EE58[];
extern u8 lbl_8035EE60[];
extern u8 lbl_8035EE68[];
extern char lbl_8035F09C[4], lbl_8035F0A4[4], lbl_8035F0AC[4], lbl_8035EE70[4], lbl_8035F0D0[4], lbl_8035F0D8[4], lbl_8035ED68[4], lbl_8035F0E4[4], lbl_8035EE18[4], lbl_8035ECE0[4], lbl_8035F1C0[8], lbl_8035F1CC[4], lbl_8035F1D4[4], lbl_8035EEA8[4];
extern u8 lbl_8035EE78[];
extern u8 lbl_8035EE80[];
extern u8 lbl_8035EE88[];
extern u8 lbl_8035EE90[];
extern char lbl_8035EE98[4];
extern const char lbl_8035EEA0[7];
extern char lbl_8035F09C[4], lbl_8035F0A4[4], lbl_8035F0AC[4], lbl_8035EE70[4], lbl_8035F0D0[4], lbl_8035F0D8[4], lbl_8035ED68[4], lbl_8035F0E4[4], lbl_8035EE18[4], lbl_8035ECE0[4], lbl_8035F1C0[8], lbl_8035F1CC[4], lbl_8035F1D4[4], lbl_8035EEA8[4];
extern u8 lbl_8035EEB0[];
extern u8 lbl_8035EEB8[];
extern u8 lbl_8035EEC0[];
extern u8 lbl_8035EEC8[];
extern u8 lbl_8035EED0[];
extern u8 lbl_8035EED8[];
extern u8 lbl_8035EEE0[];
extern u8 lbl_8035EEE8[];
extern u8 lbl_8035EEF0[];
extern u8 lbl_8035EEF8[];
extern u8 lbl_8035EF00[];
extern u8 lbl_8035EF08[];
extern u8 lbl_8035EF10[];
extern u8 lbl_8035EF18[];
extern u8 lbl_8035EF20[];
extern u8 lbl_8035EF28[];
extern u8 lbl_8035EF30[];
extern u8 lbl_8035EF38[];
extern u8 lbl_8035EF40[];
extern u8 lbl_8035EF48[];
extern const char lbl_8035EF50[8];
extern u8 lbl_8035EF58[];
extern u8 lbl_8035EF60[];
extern u8 lbl_8035EF68[];
extern u8 lbl_8035EF70[];
extern u8 lbl_8035EF78[];
extern char lbl_8035EF80[8];
extern u8 lbl_8035EF88[];
extern u8 lbl_8035EF90[];
extern u8 lbl_8035EF98[];
extern u8 lbl_8035EFA0[];
extern u8 lbl_8035EFA8[];
extern u8 lbl_8035EFB0[];
extern u8 lbl_8035EFB8[];
extern u8 lbl_8035EFC0[];
extern u8 lbl_8035EFC8[];
extern u8 lbl_8035EFD0[];
extern u8 lbl_8035EFD8[];
extern u8 lbl_8035EFE0[];
extern u8 lbl_8035EFE8[];
extern u8 lbl_8035EFF0[];
extern u8 lbl_8035EFF8[];
extern u8 lbl_8035F000[];
extern u8 lbl_8035F008[];
extern u8 lbl_8035F010[];
extern u8 lbl_8035F018[];
extern u8 lbl_8035F020[];
extern u8 lbl_8035F028[];
extern u8 lbl_8035F030[];
extern u8 lbl_8035F038[];
extern u8 lbl_8035F040[];
extern u8 lbl_8035F048[];
extern u8 lbl_8035F050[];
extern u8 lbl_8035F058[];
extern u8 lbl_8035F060[];
extern u8 lbl_8035F068[];
extern u8 lbl_8035F070[];
extern u8 lbl_8035F078[];
extern u8 lbl_8035F080[];
extern u8 lbl_8035F084[];
extern u8 lbl_8035F08C[];
extern u8 lbl_8035F094[];
void fn_80070A88(void);
void fn_80249AC4(void);
void fn_800706D8(void);
void fn_80070324(void);
void fn_8023D198(void);
void fn_80070C1C(void);
void fn_80241D80(void);
void fn_8003F140(void);
void fn_8003F18C(void);
void fn_8006DA44(void);
void fn_802416D4(void);
void fn_8003F1DC(void);
void fn_800712B0(void);
void fn_80070CC0(void);
void fn_8006DAD8(void);
void fn_8006C3CC(void);
void fn_8006FEA4(void);
void fn_8006D124(void);
void fn_800690FC(void);
// The TU string pool (.rodata 80297908-80297E10) in its original order. The 85 table strings are globals (the
// descriptor tables and jt_802BD300 name them). The strings the code uses are one static array each: statics
// are addressed relative to the pool start, like the original literals (a global gets its own lis/addi).
extern const char lbl_80297908[];
const char lbl_80297908[] = "MContact";
extern const char lbl_80297914[];
const char lbl_80297914[] = "MAirborn";
extern const char lbl_80297920[];
const char lbl_80297920[] = "MStation";
extern const char lbl_8029792C[];
const char lbl_8029792C[] = "MFalling";
extern const char lbl_80297938[];
const char lbl_80297938[] = "SNEAKLFT";
extern const char lbl_80297944[];
const char lbl_80297944[] = "SNEAKRGT";
extern const char lbl_80297950[];
const char lbl_80297950[] = "SNEAKBCK";
extern const char lbl_8029795C[];
const char lbl_8029795C[] = "JUMPLAND";
extern const char lbl_80297968[];
const char lbl_80297968[] = "JUMPSHOT";
extern const char lbl_80297974[];
const char lbl_80297974[] = "sprtfwd2";
extern const char lbl_80297980[];
const char lbl_80297980[] = "Cnothnks";
extern const char lbl_8029798C[];
const char lbl_8029798C[] = "activate";
extern const char lbl_80297998[];
const char lbl_80297998[] = "BALLROLL";
extern const char lbl_802979A4[];
const char lbl_802979A4[] = "DmFrShot";
extern const char lbl_802979B0[];
const char lbl_802979B0[] = "HmFrShot";
extern const char lbl_802979BC[];
const char lbl_802979BC[] = "WlgnShot";
extern const char lbl_802979C8[];
const char lbl_802979C8[] = "BRingSht";
extern const char lbl_802979D4[];
const char lbl_802979D4[] = "BRingSh2";
extern const char lbl_802979E0[];
const char lbl_802979E0[] = "AttFbll2";
extern const char lbl_802979EC[];
const char lbl_802979EC[] = "hazshots";
extern const char lbl_802979F8[];
const char lbl_802979F8[] = "BNS_OVER";
extern const char lbl_80297A04[];
const char lbl_80297A04[] = "IDLEBOR1";
extern const char lbl_80297A10[];
const char lbl_80297A10[] = "JMPSLACK";
extern const char lbl_80297A1C[];
const char lbl_80297A1C[] = "GAMEOVER";
extern const char lbl_80297A28[];
const char lbl_80297A28[] = "SUCKSHRV";
extern const char lbl_80297A34[];
const char lbl_80297A34[] = "BRAKBEAM";
extern const char lbl_80297A40[];
const char lbl_80297A40[] = "SolClcta";
extern const char lbl_80297A4C[];
const char lbl_80297A4C[] = "SolClctb";
extern const char lbl_80297A58[];
const char lbl_80297A58[] = "SolClctc";
extern const char lbl_80297A64[];
const char lbl_80297A64[] = "SolClctd";
extern const char lbl_80297A70[];
const char lbl_80297A70[] = "STANDCOM";
extern const char lbl_80297A7C[];
const char lbl_80297A7C[] = "BNS_SHRV";
extern const char lbl_80297A88[];
const char lbl_80297A88[] = "ACTV8ING";
extern const char lbl_80297A94[];
const char lbl_80297A94[] = "SPRT2HIT";
extern const char lbl_80297AA0[];
const char lbl_80297AA0[] = "ANIMOVER";
extern const char lbl_80297AAC[];
const char lbl_80297AAC[] = "ANIMLOOP";
extern const char lbl_80297AB8[];
const char lbl_80297AB8[] = "JUMP_PRS";
extern const char lbl_80297AC4[];
const char lbl_80297AC4[] = "FJMP_PRS";
extern const char lbl_80297AD0[];
const char lbl_80297AD0[] = "BEAM_PRS";
extern const char lbl_80297ADC[];
const char lbl_80297ADC[] = "BEAM_REL";
extern const char lbl_80297AE8[];
const char lbl_80297AE8[] = "STRT_COL";
extern const char lbl_80297AF4[];
const char lbl_80297AF4[] = "GDAMAGED";
extern const char lbl_80297B00[];
const char lbl_80297B00[] = "KDAMAGED";
extern const char lbl_80297B0C[];
const char lbl_80297B0C[] = "OBJKILLD";
extern const char lbl_80297B18[];
const char lbl_80297B18[] = "TRANSOVR";
extern const char lbl_80297B24[];
const char lbl_80297B24[] = "STRT_COM";
extern const char lbl_80297B30[];
const char lbl_80297B30[] = "CHRG_PRS";
extern const char lbl_80297B3C[];
const char lbl_80297B3C[] = "CHRG_REL";
extern const char lbl_80297B48[];
const char lbl_80297B48[] = "LIGHTOFF";
extern const char lbl_80297B54[];
const char lbl_80297B54[] = "TELEPORT";
extern const char lbl_80297B60[];
const char lbl_80297B60[] = "NSHRINKP";
extern const char lbl_80297B6C[];
const char lbl_80297B6C[] = "WATEROFF";
extern const char lbl_80297B78[];
const char lbl_80297B78[] = "STRTPATH";
extern const char lbl_80297B84[];
const char lbl_80297B84[] = "CHGPTH10";
extern const char lbl_80297B90[];
const char lbl_80297B90[] = "CHGPTH11";
extern const char lbl_80297B9C[];
const char lbl_80297B9C[] = "CHGPTH12";
extern const char lbl_80297BA8[];
const char lbl_80297BA8[] = "CHGPTH13";
extern const char lbl_80297BB4[];
const char lbl_80297BB4[] = "CHGPTH14";
extern const char lbl_80297BC0[];
const char lbl_80297BC0[] = "CHGPTH15";
extern const char lbl_80297BCC[];
const char lbl_80297BCC[] = "CHGPTH16";
extern const char lbl_80297BD8[];
const char lbl_80297BD8[] = "CHGPTH17";
extern const char lbl_80297BE4[];
const char lbl_80297BE4[] = "CHGPTH18";
extern const char lbl_80297BF0[];
const char lbl_80297BF0[] = "CHGPTH19";
extern const char lbl_80297BFC[];
const char lbl_80297BFC[] = "CHGPTH20";
extern const char lbl_80297C08[];
const char lbl_80297C08[] = "CHGPTH21";
extern const char lbl_80297C14[];
const char lbl_80297C14[] = "CHGPTH22";
extern const char lbl_80297C20[];
const char lbl_80297C20[] = "CHGPTH23";
extern const char lbl_80297C2C[];
const char lbl_80297C2C[] = "CHGPTH24";
extern const char lbl_80297C38[];
const char lbl_80297C38[] = "CHGPTH25";
extern const char lbl_80297C44[];
const char lbl_80297C44[] = "CINFUEGO";
extern const char lbl_80297C50[];
const char lbl_80297C50[] = "CINFUEG1";
extern const char lbl_80297C5C[];
const char lbl_80297C5C[] = "BACK2WRK";
extern const char lbl_80297C68[];
const char lbl_80297C68[] = "RAINOFFE";
extern const char lbl_80297C74[];
const char lbl_80297C74[] = "PRERESET";
extern const char lbl_80297C80[];
const char lbl_80297C80[] = "GGGLNTRN";
extern const char lbl_80297C8C[];
const char lbl_80297C8C[] = "NGGLNTRN";
extern const char lbl_80297C98[];
const char lbl_80297C98[] = "GIVEGEM2";
extern const char lbl_80297CA4[];
const char lbl_80297CA4[] = "GIVEGEM3";
extern const char lbl_80297CB0[];
const char lbl_80297CB0[] = "GIVEGEM4";
extern const char lbl_80297CBC[];
const char lbl_80297CBC[] = "GIVEGEM5";
extern const char lbl_80297CC8[];
const char lbl_80297CC8[] = "GIVEGEM6";
extern const char lbl_80297CD4[];
const char lbl_80297CD4[] = "GIVEGEML";
extern const char lbl_80297CE0[];
const char lbl_80297CE0[] = "BODYNODE";
extern const char lbl_80297CEC[];
const char lbl_80297CEC[] = "BODYANIM";
static const char sCF8[] = "PLYRDEAD";
static const char sD04[] = "C_NOSHKE";
static const char sD10[] = "PLYRLIVE";
static const char sD1C[] = "C_NSCARY";
static const char sD28[] = "LvSprFnd";
static const char sD34[] = "PLYRNACT";
static const char sD40[] = "PREMNGST";
static const char sD4C[] = "RUMBLE_M";
static const char sD58[] = "PlrShot2";
static const char sD64[] = "C_RESUME";
static const char sD70[] = "aaCertificateNames";
static const char sD84[] = "aaCertificateEvents";
static const char sD98[] = "SHRVPNTR";
static const char sDA4[] = "RUMBLE_L";
static const char sDB0[] = "RUMBLE_H";
static const char sDBC[] = "SENDDIST";
static const char sDC8[] = "Srchable";
static const char sDD4[] = "SENDDATA";
static const char sDE0[] = "SpwnShri";
static const char sDEC[] = "PICKEDUP";
static const char sDF8[] = "dethcert";
static const char sE04[12] = "leotcard";
}

namespace n800690FC {

extern "C" {

#include "common.h"
extern "C" {
struct VO { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12f(f32 k); virtual void getPos(void *p, void *a, void *b, int c, int d); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void send(void *msg, u32 to, int a, void *d, void *e); virtual void s34(); virtual void s35(); virtual void s36(); };
struct VE { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39(); virtual void shot(u32 o, int a, char *grp, char *bone, int b, f32 k, f32 m); };
struct VB80 { u8 pad_[0x80]; };
struct VQ : VB80 { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void tog(int a); };
struct VB2F0 { u8 pad_[0x2f0]; };
struct VG : VB2F0 { virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void go0(); virtual void go(void *s); virtual void s14(); };
__declspec(section ".data") u8 lbl_802BD3F8[540] = { 0, 0, 0, 0, 0, 0, 0, 0xFA, 0, 0, 1, 0xF4, 0, 0, 2, 0xEE, 0x55, 0x49, 0x5C, 0x4D, 0x45, 0x4D, 0x43, 0x41, 0x52, 0x44, 0x5C, 0, 0x41, 0x54, 0x54, 0x49, 0x43, 0, 0, 0, 0x42, 0x41, 0x4C, 0x4C, 0x52, 0x4F, 0x4F, 0x4D, 0x43, 0x48, 0x49, 0x4C, 0x44, 0x52, 0x45, 0x4E, 0x43, 0x4F, 0x4E, 0x53, 0x45, 0x52, 0x56, 0, 0x44, 0x49, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x46, 0x4F, 0x59, 0x45, 0x52, 0, 0, 0, 0x47, 0x41, 0x4C, 0x4C, 0x45, 0x52, 0x59, 0, 0x47, 0x52, 0x41, 0x56, 0x45, 0x59, 0x44, 0, 0x47, 0x52, 0x4F, 0x4F, 0x4D, 0, 0, 0, 0x47, 0x52, 0x54, 0x48, 0x41, 0x4C, 0x4C, 0, 0x47, 0x55, 0x45, 0x53, 0x54, 0, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x41, 0x42, 0, 0, 0x48, 0x41, 0x4C, 0x4C, 0x43, 0x44, 0, 0, 0x4B, 0x49, 0x54, 0x43, 0x48, 0x45, 0x4E, 0, 0x4C, 0x41, 0x42, 0, 0, 0, 0, 0, 0x4D, 0x55, 0x53, 0x45, 0x55, 0x4D, 0, 0, 0x4D, 0x41, 0x49, 0x44, 0, 0, 0, 0, 0x4D, 0x41, 0x53, 0x54, 0x52, 0x42, 0x45, 0x44, 0x4D, 0x41, 0x55, 0x53, 0x4F, 0x4C, 0x4D, 0, 0x4D, 0x45, 0x41, 0x53, 0x55, 0x52, 0x45, 0, 0x54, 0x4F, 0x59, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x4F, 0x42, 0x53, 0x45, 0x52, 0x56, 0, 0, 0x50, 0x41, 0x4E, 0x54, 0x52, 0x59, 0, 0, 0x50, 0x41, 0x52, 0x4C, 0x4F, 0x52, 0, 0, 0x53, 0x49, 0x54, 0x54, 0x49, 0x4E, 0x47, 0, 0x53, 0x54, 0x52, 0x45, 0x54, 0x43, 0x48, 0, 0x53, 0x55, 0x4E, 0x52, 0x4F, 0x4F, 0x4D, 0, 0x57, 0x49, 0x4E, 0x54, 0x45, 0x52, 0, 0, 0x54, 0x49, 0x54, 0x4C, 0x45, 0, 0, 0, 0x53, 0x50, 0x49, 0x52, 0x49, 0x54, 0, 0, 0x47, 0x4C, 0x4F, 0x42, 0x41, 0x4C, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x28, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x40, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0xBF, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0x3F, 0x80, 0, 0, 0xBF, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 9, 0, 0, 0, 0xC, 0, 0, 0, 0xF, 0, 0, 0, 0x12, 0, 0, 0, 0x15, 0, 0, 0, 0x18, 0, 0, 0, 0x1B, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0x40, 0, 0, 0, 0x43, 0, 0, 0, 0x46, 0, 0, 0, 0x49, 0, 0, 0, 0x4C, 0, 0, 0, 0x4F, 0, 0, 0, 0x52, 0, 0, 0, 0x55, 0, 0, 0, 0x1E, 0, 0, 0, 0x21, 0, 0, 0, 0x24, 0, 0, 0, 0x27, 0, 0, 0, 0x2A, 0, 0, 0, 0x2D, 0, 0, 0, 0x30, 0, 0, 0, 0x33 };
static __declspec(section ".data") void *sPad_21C[365] = { (void *)lbl_80297908, (void *)lbl_80297914, (void *)lbl_80297920, (void *)lbl_8029792C, (void *)lbl_8035E810, (void *)lbl_8035E818, (void *)lbl_8035E820, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E838, (void *)lbl_8035E828, (void *)lbl_8035E840, (void *)lbl_8035E848, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E850, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E858, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E860, (void *)lbl_8035E828, (void *)lbl_8035E868, (void *)lbl_8035E870, (void *)lbl_8035E828, (void *)lbl_8035E878, (void *)lbl_8035E880, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E888, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E890, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E898, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E8A0, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E8A8, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E8B0, (void *)lbl_8035E828, (void *)lbl_8035E8B8, (void *)lbl_8035E8C0, (void *)lbl_8035E828, (void *)lbl_8035E8C4, (void *)lbl_8035E8C8, (void *)lbl_8035E828, (void *)lbl_8035E8CC, (void *)lbl_8035E8D0, (void *)lbl_8035E828, (void *)lbl_8035E8D8, (void *)lbl_8035E8E0, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E8E8, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E8F0, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E8F8, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E900, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E908, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E910, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E918, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E920, (void *)lbl_8035E828, (void *)lbl_8035E924, (void *)lbl_8035E920, (void *)lbl_8035E828, (void *)lbl_8035E928, (void *)lbl_8035E92C, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E934, (void *)lbl_8035E828, (void *)lbl_8035E830, (void *)lbl_8035E93C, (void *)lbl_8035E828, (void *)lbl_8035E944, (void *)lbl_8035E94C, (void *)lbl_8035E828, (void *)lbl_8035E954, (void *)lbl_8035E95C, (void *)lbl_8035E828, (void *)lbl_8035E964, (void *)lbl_8035E96C, (void *)lbl_8035E828, (void *)lbl_8035E974, (void *)lbl_8035E97C, (void *)lbl_8035E828, (void *)lbl_8035E984, (void *)lbl_8035E98C, (void *)lbl_8035E828, (void *)lbl_8035E994, (void *)lbl_8035E99C, (void *)lbl_8035E828, (void *)lbl_8035E9A0, (void *)lbl_8035E9A4, (void *)lbl_8035E828, (void *)lbl_8035E9AC, (void *)lbl_8035E9B4, (void *)lbl_8035E828, (void *)lbl_8035E9BC, (void *)lbl_8035E9C4, (void *)lbl_8035E828, (void *)lbl_8035E9CC, (void *)lbl_8035E9D4, (void *)lbl_8035E828, (void *)lbl_8035E9DC, (void *)lbl_8035E9E4, (void *)lbl_8035E828, (void *)lbl_8035E9EC, (void *)lbl_8035E9F4, (void *)lbl_8035E828, (void *)lbl_8035E9FC, (void *)lbl_80297938, (void *)lbl_8035E828, (void *)lbl_8035EA04, (void *)lbl_80297944, (void *)lbl_8035E828, (void *)lbl_8035EA08, (void *)lbl_80297950, (void *)lbl_8035E828, (void *)lbl_8035EA0C, (void *)lbl_8035EA10, (void *)lbl_8035E828, (void *)lbl_8035EA18, (void *)lbl_8035EA20, (void *)lbl_8035E828, (void *)lbl_8035EA28, (void *)lbl_8029795C, (void *)lbl_8035E828, (void *)lbl_8035EA30, (void *)lbl_80297968, (void *)lbl_8035E828, (void *)lbl_8035EA38, (void *)lbl_8035EA40, (void *)lbl_8035E828, (void *)lbl_8035EA48, (void *)lbl_8035EA50, (void *)lbl_8035E828, (void *)lbl_8035EA58, (void *)lbl_8035EA60, (void *)lbl_8035E828, (void *)lbl_8035EA68, (void *)lbl_8035EA70, (void *)lbl_8035E828, (void *)lbl_8035EA78, (void *)lbl_8035EA80, (void *)lbl_8035E828, (void *)lbl_8035E9AC, (void *)lbl_8035EA88, (void *)lbl_8035E828, (void *)lbl_8035EA90, (void *)lbl_8035EA98, (void *)lbl_8035E828, (void *)lbl_8035EAA0, (void *)lbl_8035EAA8, (void *)lbl_8035E828, (void *)lbl_8035EAB0, (void *)lbl_8035EAB8, (void *)lbl_8035E828, (void *)lbl_8035E964, (void *)lbl_8035EAC0, (void *)lbl_8035E828, (void *)lbl_8035EAC8, (void *)lbl_8035EAD0, (void *)lbl_8035E828, (void *)lbl_8035EAD8, (void *)lbl_8035EAE0, (void *)lbl_8035E828, (void *)lbl_8035EAE8, (void *)lbl_8035EAF0, (void *)lbl_8035E828, (void *)lbl_8035E9BC, (void *)lbl_8035EAF8, (void *)lbl_8035E828, (void *)lbl_8035EB00, (void *)lbl_8035EB08, (void *)lbl_8035E828, (void *)lbl_8035EB10, (void *)lbl_8035EB18, (void *)lbl_8035E828, (void *)lbl_8035EB20, (void *)lbl_8035EB28, (void *)lbl_8035E828, (void *)lbl_8035EB30, (void *)lbl_8035EB38, (void *)lbl_8035E828, (void *)lbl_8035EB40, (void *)lbl_8035EB48, (void *)lbl_8035E828, (void *)lbl_8035EB50, (void *)lbl_8035EB58, (void *)lbl_8035E828, (void *)lbl_8035EB60, (void *)lbl_8035EB68, (void *)lbl_8035E828, (void *)lbl_8035EB68, (void *)lbl_8035EB70, (void *)lbl_8035E828, (void *)lbl_8035EB70, (void *)lbl_8035EB78, (void *)lbl_8035E828, (void *)lbl_8035EB78, (void *)lbl_8035EB80, (void *)lbl_8035E828, (void *)lbl_8035EB80, (void *)lbl_8035EB88, (void *)lbl_8035E828, (void *)lbl_8035EB88, (void *)lbl_8035EB90, (void *)lbl_8035E828, (void *)lbl_8035EB90, (void *)lbl_8035EB98, (void *)lbl_8035E828, (void *)lbl_8035EB98, (void *)lbl_8035EBA0, (void *)lbl_8035E828, (void *)lbl_8035EBA0, (void *)lbl_8035EBA8, (void *)lbl_8035E828, (void *)lbl_8035EBA8, (void *)lbl_8035EBB0, (void *)lbl_8035E828, (void *)lbl_8035EBB0, (void *)lbl_8035EBB8, (void *)lbl_8035E828, (void *)lbl_8035EBB8, (void *)lbl_8035EA48, (void *)lbl_8035E828, (void *)lbl_8035EA48, (void *)lbl_8035EA58, (void *)lbl_8035E828, (void *)lbl_8035EA58, (void *)lbl_8035EA68, (void *)lbl_8035E828, (void *)lbl_8035EA68, (void *)lbl_8035EBC0, (void *)lbl_8035E828, (void *)lbl_8035EBC0, (void *)lbl_8035EBC8, (void *)lbl_8035E828, (void *)lbl_8035EBC8, (void *)lbl_8035EBD0, (void *)lbl_8035E828, (void *)lbl_8035EBD0, (void *)lbl_8035EBD8, (void *)lbl_8035E828, (void *)lbl_8035EBD8, (void *)lbl_8035EBE0, (void *)lbl_8035E828, (void *)lbl_8035EBE0, (void *)lbl_8035EBE8, (void *)lbl_8035E828, (void *)lbl_8035EBE8, (void *)lbl_8035EBF0, (void *)lbl_8035E828, (void *)lbl_8035EBF0, (void *)lbl_8035EBF8, (void *)lbl_8035E828, (void *)lbl_8035EBF8, (void *)lbl_8035EC00, (void *)lbl_8035E828, (void *)lbl_8035EC00, (void *)lbl_8035EC08, (void *)lbl_8035E828, (void *)lbl_8035EC08, (void *)lbl_8035EC10, (void *)lbl_8035E828, (void *)lbl_8035EC10, (void *)lbl_8035EC18, (void *)lbl_8035E828, (void *)lbl_8035EC18, (void *)lbl_8035EC20, (void *)lbl_8035E828, (void *)lbl_8035EC20, (void *)lbl_8035EC28, (void *)lbl_8035E828, (void *)lbl_8035EC28, (void *)lbl_8035EC30, (void *)lbl_8035E828, (void *)lbl_8035EC30, (void *)lbl_8035EB68, (void *)lbl_8035E828, (void *)lbl_8035EB68, (void *)lbl_8035EC38, (void *)lbl_8035E828, (void *)lbl_8035EC38, (void *)lbl_8035EC40, (void *)lbl_8035E828, (void *)lbl_8035EC40, (void *)lbl_8035EC48, (void *)lbl_8035E828, (void *)lbl_8035EC48, (void *)lbl_80297974, (void *)lbl_8035E828, (void *)lbl_80297974, (void *)lbl_8035EC50, (void *)lbl_8035E828, (void *)lbl_8035EC50, (void *)lbl_8035EC58, (void *)lbl_8035E828, (void *)lbl_8035EC58, (void *)lbl_8035EC60, (void *)lbl_8035E828, (void *)lbl_8035EC60, (void *)lbl_8035EC68, (void *)lbl_8035E828, (void *)lbl_8035EC68, (void *)lbl_8035EC70, (void *)lbl_8035E828, (void *)lbl_8035EC70, (void *)lbl_8035EC78, (void *)lbl_8035E828, (void *)lbl_8035EC78, (void *)lbl_8035EC80, (void *)lbl_8035E828, (void *)lbl_8035EC80, (void *)lbl_8035EC88, (void *)lbl_8035E828, (void *)lbl_8035EC88, (void *)lbl_8035EC90, (void *)lbl_8035E828, (void *)lbl_8035EC90, (void *)lbl_80297980, (void *)lbl_8035E828, (void *)lbl_80297980, (void *)lbl_8035EC98, (void *)lbl_8035E828, (void *)lbl_8035EC98, (void *)lbl_8035ECA0, (void *)lbl_8035E828, (void *)lbl_8035ECA0, (void *)lbl_8035ECA8, (void *)lbl_8035E828, (void *)lbl_8035ECA8, (void *)lbl_8035ECB0, (void *)lbl_8035E828, (void *)lbl_8035ECB0, (void *)lbl_8029798C, (void *)lbl_8035E828, (void *)lbl_8029798C, (void *)lbl_8035ECB8, (void *)lbl_8035E828, (void *)lbl_8035ECB8, (void *)lbl_8035ECC0, (void *)lbl_8035ECC8 };
static __declspec(section ".data") u8 sPad_7D0[4] = { 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_7D4[2] = { (void *)lbl_8035ECD0, (void *)lbl_8035ECD8 };
static __declspec(section ".data") u8 sPad_7DC[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_7E0[2] = { (void *)lbl_8035ECE0, (void *)lbl_8035ECE8 };
static __declspec(section ".data") u8 sPad_7E8[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_7EC[2] = { (void *)lbl_8035ECF0, (void *)lbl_8035ECF8 };
static __declspec(section ".data") u8 sPad_7F4[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_7F8[2] = { (void *)lbl_8035ED00, (void *)lbl_8035ED08 };
static __declspec(section ".data") u8 sPad_800[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_804[2] = { (void *)lbl_8035ED10, (void *)lbl_8035ED18 };
static __declspec(section ".data") u8 sPad_80C[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_810[2] = { (void *)lbl_8035ED20, (void *)lbl_8035ED28 };
static __declspec(section ".data") u8 sPad_818[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_81C[2] = { (void *)lbl_80297998, (void *)lbl_8035ED30 };
static __declspec(section ".data") u8 sPad_824[4] = { 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_828[2] = { (void *)lbl_8035ED38, (void *)lbl_8035ED40 };
static __declspec(section ".data") u8 sPad_830[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_834[2] = { (void *)lbl_8035ED48, (void *)lbl_8035ED50 };
static __declspec(section ".data") u8 sPad_83C[4] = { 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_840[57] = { (void *)lbl_8035ED58, (void *)lbl_8035ED60, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_8035ED6C, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_802979A4, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_802979B0, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_8035ED74, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_8035ED7C, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_802979BC, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_802979C8, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_802979D4, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_8035ED84, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_8035ED8C, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_8035ED94, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED58, (void *)lbl_802979E0, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_802979EC, (void *)lbl_8035ED9C, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED68 };
static __declspec(section ".data") u8 sPad_924[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_930[1] = { (void *)lbl_802979F8 };
static __declspec(section ".data") u8 sPad_934[12] = { 0x3F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_940[1] = { (void *)lbl_8035EDAC };
static __declspec(section ".data") u8 sPad_944[12] = { 0x40, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_950[1] = { (void *)lbl_80297A04 };
static __declspec(section ".data") u8 sPad_954[12] = { 0x3F, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_960[1] = { (void *)lbl_80297A10 };
static __declspec(section ".data") u8 sPad_964[12] = { 0x40, 0xC0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_970[1] = { (void *)lbl_80297A1C };
static __declspec(section ".data") u8 sPad_974[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_980[1] = { (void *)lbl_8035ED68 };
static __declspec(section ".data") u8 sPad_984[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_990[1] = { (void *)lbl_8035ED68 };
static __declspec(section ".data") u8 sPad_994[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_9A0[1] = { (void *)lbl_8035ED68 };
static __declspec(section ".data") u8 sPad_9A4[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_9B0[1] = { (void *)lbl_8035ED68 };
static __declspec(section ".data") u8 sPad_9B4[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_9C0[1] = { (void *)lbl_8035ED68 };
static __declspec(section ".data") u8 sPad_9C4[12] = { 0x3F, 0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_9D0[1] = { (void *)lbl_8035EDB4 };
static __declspec(section ".data") u8 sPad_9D4[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_9E0[1] = { (void *)lbl_8035EDBC };
static __declspec(section ".data") u8 sPad_9E4[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_9F0[1] = { (void *)lbl_8035EDC4 };
static __declspec(section ".data") u8 sPad_9F4[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A00[1] = { (void *)lbl_80297A28 };
static __declspec(section ".data") u8 sPad_A04[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A10[1] = { (void *)lbl_80297A34 };
static __declspec(section ".data") u8 sPad_A14[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A20[1] = { (void *)lbl_80297A34 };
static __declspec(section ".data") u8 sPad_A24[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A30[2] = { (void *)lbl_8035EDCC, (void *)lbl_8035EDD4 };
static __declspec(section ".data") u8 sPad_A38[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A48[1] = { (void *)lbl_8035EDDC };
static __declspec(section ".data") u8 sPad_A4C[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A5C[1] = { (void *)lbl_8035EDE4 };
static __declspec(section ".data") u8 sPad_A60[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A70[1] = { (void *)lbl_8035EDEC };
static __declspec(section ".data") u8 sPad_A74[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A84[1] = { (void *)lbl_8035EDF4 };
static __declspec(section ".data") u8 sPad_A88[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_A98[1] = { (void *)lbl_8035EDFC };
static __declspec(section ".data") u8 sPad_A9C[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_AAC[1] = { (void *)lbl_80297A40 };
static __declspec(section ".data") u8 sPad_AB0[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_AC0[1] = { (void *)lbl_80297A4C };
static __declspec(section ".data") u8 sPad_AC4[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_AD4[1] = { (void *)lbl_80297A58 };
static __declspec(section ".data") u8 sPad_AD8[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_AE8[1] = { (void *)lbl_80297A64 };
static __declspec(section ".data") u8 sPad_AEC[16] = { 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *sPad_AFC[181] = { (void *)lbl_8035E858, (void *)lbl_80297A04, (void *)lbl_8035EE04, (void *)lbl_8035EE0C, (void *)lbl_8035EE14, (void *)lbl_8035ED68, (void *)lbl_8035EE18, (void *)lbl_8035E9C4, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035EE20, (void *)lbl_8035EE28, (void *)lbl_8035EE30, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035EE38, (void *)lbl_8035EE40, (void *)lbl_80297A70, (void *)lbl_8035EE48, (void *)lbl_8035ED68, (void *)lbl_8035EE50, (void *)lbl_8035ED68, (void *)lbl_8035ED68, (void *)lbl_8035EE58, (void *)lbl_8035E8B0, (void *)lbl_8035EE60, (void *)lbl_80297A7C, (void *)lbl_8035EE68, (void *)lbl_8035EE70, (void *)lbl_8035EE78, (void *)lbl_8035EE80, (void *)lbl_80297A88, (void *)lbl_8035EE88, (void *)lbl_8035EE90, (void *)lbl_80297A94, (void *)lbl_8035EE98, (void *)lbl_8035EEA0, (void *)lbl_8035ECE0, (void *)lbl_8035EEA8, (void *)lbl_8035EEB0, (void *)lbl_8035EEB8, (void *)lbl_8035EEC0, (void *)lbl_80297AA0, (void *)lbl_80297AAC, (void *)lbl_80297AB8, (void *)lbl_80297AC4, (void *)lbl_8035EEC8, (void *)lbl_8035EED0, (void *)lbl_8035EE38, (void *)lbl_80297A10, (void *)lbl_8035EED8, (void *)lbl_8035EEE0, (void *)lbl_80297AD0, (void *)lbl_80297ADC, (void *)lbl_8035EEE8, (void *)lbl_80297A34, (void *)lbl_80297A28, (void *)lbl_8035EDCC, (void *)lbl_80297AE8, (void *)lbl_80297AE8, (void *)lbl_8035E858, (void *)lbl_8035EEF0, (void *)lbl_8035EEF8, (void *)lbl_8035EE0C, (void *)lbl_8035EF00, (void *)lbl_8035EF08, (void *)lbl_8035EF10, (void *)lbl_8035EE14, (void *)lbl_8035EF18, (void *)lbl_8035EA50, (void *)lbl_8035EA60, (void *)lbl_8035EF20, (void *)lbl_8035EA70, (void *)lbl_8035EF28, (void *)lbl_8035EF30, (void *)lbl_8035EF38, (void *)lbl_8035EF40, (void *)lbl_8035EF48, (void *)lbl_80297AF4, (void *)lbl_80297B00, (void *)lbl_8035EF50, (void *)lbl_8035EE48, (void *)lbl_80297A04, (void *)lbl_8035EE30, (void *)lbl_8035EF58, (void *)lbl_80297B0C, (void *)lbl_8035EF60, (void *)lbl_80297B18, (void *)lbl_8035EDB4, (void *)lbl_80297B24, (void *)lbl_8035EF68, (void *)lbl_8035EF70, (void *)lbl_8035EF78, (void *)lbl_80297B30, (void *)lbl_80297B3C, (void *)lbl_8035EDBC, (void *)lbl_8035EDC4, (void *)lbl_8035EF80, (void *)lbl_80297B48, (void *)lbl_80297B54, (void *)lbl_8035EF88, (void *)lbl_8035EF90, (void *)lbl_8035ECD0, (void *)lbl_8035EF98, (void *)lbl_8035EFA0, (void *)lbl_80297B60, (void *)lbl_8035ED48, (void *)lbl_8035EFA8, (void *)lbl_8035EFB0, (void *)lbl_8035EFB8, (void *)lbl_8035EFC0, (void *)lbl_80297B6C, (void *)lbl_80297B78, (void *)lbl_8035EFC8, (void *)lbl_8035EFD0, (void *)lbl_8035EFD8, (void *)lbl_8035EFE0, (void *)lbl_8035EFE8, (void *)lbl_8035EFF0, (void *)lbl_8035EFF8, (void *)lbl_8035F000, (void *)lbl_8035F008, (void *)lbl_8035F010, (void *)lbl_8035F018, (void *)lbl_80297B84, (void *)lbl_80297B90, (void *)lbl_80297B9C, (void *)lbl_80297BA8, (void *)lbl_80297BB4, (void *)lbl_80297BC0, (void *)lbl_80297BCC, (void *)lbl_80297BD8, (void *)lbl_80297BE4, (void *)lbl_80297BF0, (void *)lbl_80297BFC, (void *)lbl_80297C08, (void *)lbl_80297C14, (void *)lbl_80297C20, (void *)lbl_80297C2C, (void *)lbl_80297C38, (void *)lbl_8035F020, (void *)lbl_8035F028, (void *)lbl_8035F030, (void *)lbl_8035F038, (void *)lbl_8035F040, (void *)lbl_8035F048, (void *)lbl_8035F050, (void *)lbl_8035F058, (void *)lbl_8035F060, (void *)lbl_8035F068, (void *)lbl_8035EE90, (void *)lbl_8035EE78, (void *)lbl_8035EE70, (void *)lbl_8035EE80, (void *)lbl_80297C44, (void *)lbl_80297C50, (void *)lbl_80297C5C, (void *)lbl_8035F070, (void *)lbl_8035EEA8, (void *)lbl_8035F078, (void *)lbl_8035F080, (void *)lbl_8035F084, (void *)lbl_8035F08C, (void *)lbl_8035F094, (void *)lbl_80297C68, (void *)lbl_80297A7C, (void *)lbl_802979F8, (void *)lbl_80297C74, (void *)lbl_80297C80, (void *)lbl_80297C8C, (void *)lbl_80297C98, (void *)lbl_80297CA4, (void *)lbl_80297CB0, (void *)lbl_80297CBC, (void *)lbl_80297CC8, (void *)lbl_80297CD4, (void *)lbl_80297CE0, (void *)lbl_80297CEC, (void *)lbl_80297A1C, (void *)lbl_8035EEB8 };
static __declspec(section ".data") u8 sPad_DD0[8] = { 0, 0, 0, 0, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_DD8[1] = { (void *)lbl_8035EEC0 };
static __declspec(section ".data") u8 sPad_DDC[8] = { 0, 0, 0, 1, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_DE4[1] = { (void *)lbl_80297AA0 };
static __declspec(section ".data") u8 sPad_DE8[8] = { 0, 0, 0, 2, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_DF0[1] = { (void *)lbl_80297AAC };
static __declspec(section ".data") u8 sPad_DF4[8] = { 0, 0, 0, 3, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_DFC[1] = { (void *)lbl_80297AB8 };
static __declspec(section ".data") u8 sPad_E00[8] = { 0, 0, 0, 4, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E08[1] = { (void *)lbl_80297AC4 };
static __declspec(section ".data") u8 sPad_E0C[8] = { 0, 0, 0, 5, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E14[1] = { (void *)lbl_8035EEC8 };
static __declspec(section ".data") u8 sPad_E18[8] = { 0, 0, 0, 6, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E20[1] = { (void *)lbl_8035EED0 };
static __declspec(section ".data") u8 sPad_E24[8] = { 0, 0, 0, 7, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E2C[1] = { (void *)lbl_8035EE38 };
static __declspec(section ".data") u8 sPad_E30[8] = { 0, 0, 0, 8, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E38[1] = { (void *)lbl_80297A10 };
static __declspec(section ".data") u8 sPad_E3C[8] = { 0, 0, 0, 9, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E44[1] = { (void *)lbl_8035EED8 };
static __declspec(section ".data") u8 sPad_E48[8] = { 0, 0, 0, 0xA, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E50[1] = { (void *)lbl_8035EEE0 };
static __declspec(section ".data") u8 sPad_E54[8] = { 0, 0, 0, 0xB, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E5C[1] = { (void *)lbl_80297AD0 };
static __declspec(section ".data") u8 sPad_E60[8] = { 0, 0, 0, 0xC, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E68[1] = { (void *)lbl_80297ADC };
static __declspec(section ".data") u8 sPad_E6C[8] = { 0, 0, 0, 0xD, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E74[1] = { (void *)lbl_8035EEE8 };
static __declspec(section ".data") u8 sPad_E78[8] = { 0, 0, 0, 0xE, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E80[1] = { (void *)lbl_80297A34 };
static __declspec(section ".data") u8 sPad_E84[8] = { 0, 0, 0, 0xF, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E8C[1] = { (void *)lbl_80297A28 };
static __declspec(section ".data") u8 sPad_E90[8] = { 0, 0, 0, 0x10, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_E98[1] = { (void *)lbl_8035EDCC };
static __declspec(section ".data") u8 sPad_E9C[8] = { 0, 0, 0, 0x11, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_EA4[1] = { (void *)lbl_80297AE8 };
static __declspec(section ".data") u8 sPad_EA8[8] = { 0, 0, 0, 0x12, 0, 0, 0, 2 };
static __declspec(section ".data") void *sPad_EB0[1] = { (void *)lbl_8035E858 };
static __declspec(section ".data") u8 sPad_EB4[8] = { 0, 0, 0, 0x14, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_EBC[1] = { (void *)lbl_8035EEF0 };
static __declspec(section ".data") u8 sPad_EC0[8] = { 0, 0, 0, 0x15, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_EC8[1] = { (void *)lbl_8035EEF8 };
static __declspec(section ".data") u8 sPad_ECC[8] = { 0, 0, 0, 0x16, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_ED4[1] = { (void *)lbl_8035EE0C };
static __declspec(section ".data") u8 sPad_ED8[8] = { 0, 0, 0, 0x17, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_EE0[1] = { (void *)lbl_8035EF00 };
static __declspec(section ".data") u8 sPad_EE4[8] = { 0, 0, 0, 0x18, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_EEC[1] = { (void *)lbl_8035EF08 };
static __declspec(section ".data") u8 sPad_EF0[8] = { 0, 0, 0, 0x19, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_EF8[1] = { (void *)lbl_8035EF10 };
static __declspec(section ".data") u8 sPad_EFC[8] = { 0, 0, 0, 0x1A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F04[1] = { (void *)lbl_8035EE14 };
static __declspec(section ".data") u8 sPad_F08[8] = { 0, 0, 0, 0x1B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F10[1] = { (void *)lbl_8035EF18 };
static __declspec(section ".data") u8 sPad_F14[8] = { 0, 0, 0, 0x1C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F1C[1] = { (void *)lbl_8035EA50 };
static __declspec(section ".data") u8 sPad_F20[8] = { 0, 0, 0, 0x1D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F28[1] = { (void *)lbl_8035EA60 };
static __declspec(section ".data") u8 sPad_F2C[8] = { 0, 0, 0, 0x1E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F34[1] = { (void *)lbl_8035EF20 };
static __declspec(section ".data") u8 sPad_F38[8] = { 0, 0, 0, 0x1F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F40[1] = { (void *)lbl_8035EA70 };
static __declspec(section ".data") u8 sPad_F44[8] = { 0, 0, 0, 0x20, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F4C[1] = { (void *)lbl_8035EF28 };
static __declspec(section ".data") u8 sPad_F50[8] = { 0, 0, 0, 0x21, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F58[1] = { (void *)lbl_8035EF30 };
static __declspec(section ".data") u8 sPad_F5C[8] = { 0, 0, 0, 0x22, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F64[1] = { (void *)lbl_8035EF38 };
static __declspec(section ".data") u8 sPad_F68[8] = { 0, 0, 0, 0x23, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F70[1] = { (void *)lbl_8035EF40 };
static __declspec(section ".data") u8 sPad_F74[8] = { 0, 0, 0, 0x24, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F7C[1] = { (void *)lbl_8035EF48 };
static __declspec(section ".data") u8 sPad_F80[8] = { 0, 0, 0, 0x25, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F88[1] = { (void *)lbl_80297AF4 };
static __declspec(section ".data") u8 sPad_F8C[8] = { 0, 0, 0, 0x26, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_F94[1] = { (void *)lbl_80297B00 };
static __declspec(section ".data") u8 sPad_F98[8] = { 0, 0, 0, 0x27, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FA0[1] = { (void *)lbl_8035EF50 };
static __declspec(section ".data") u8 sPad_FA4[8] = { 0, 0, 0, 0x28, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FAC[1] = { (void *)lbl_8035EE48 };
static __declspec(section ".data") u8 sPad_FB0[8] = { 0, 0, 0, 0x29, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FB8[1] = { (void *)lbl_80297A04 };
static __declspec(section ".data") u8 sPad_FBC[8] = { 0, 0, 0, 0x2A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FC4[1] = { (void *)lbl_8035EE30 };
static __declspec(section ".data") u8 sPad_FC8[8] = { 0, 0, 0, 0x2B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FD0[1] = { (void *)lbl_8035EF58 };
static __declspec(section ".data") u8 sPad_FD4[8] = { 0, 0, 0, 0x2C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FDC[1] = { (void *)lbl_80297B0C };
static __declspec(section ".data") u8 sPad_FE0[8] = { 0, 0, 0, 0x2D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FE8[1] = { (void *)lbl_8035EF60 };
static __declspec(section ".data") u8 sPad_FEC[8] = { 0, 0, 0, 0x2E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_FF4[1] = { (void *)lbl_80297B18 };
static __declspec(section ".data") u8 sPad_FF8[8] = { 0, 0, 0, 0x2F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1000[1] = { (void *)lbl_8035EDB4 };
static __declspec(section ".data") u8 sPad_1004[8] = { 0, 0, 0, 0x30, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_100C[1] = { (void *)lbl_80297B24 };
static __declspec(section ".data") u8 sPad_1010[8] = { 0, 0, 0, 0x31, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1018[1] = { (void *)lbl_8035EF68 };
static __declspec(section ".data") u8 sPad_101C[8] = { 0, 0, 0, 0x32, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1024[1] = { (void *)lbl_8035EF70 };
static __declspec(section ".data") u8 sPad_1028[8] = { 0, 0, 0, 0x33, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1030[1] = { (void *)lbl_8035EF78 };
static __declspec(section ".data") u8 sPad_1034[8] = { 0, 0, 0, 0x34, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_103C[1] = { (void *)lbl_80297B30 };
static __declspec(section ".data") u8 sPad_1040[8] = { 0, 0, 0, 0x35, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1048[1] = { (void *)lbl_80297B3C };
static __declspec(section ".data") u8 sPad_104C[8] = { 0, 0, 0, 0x36, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1054[1] = { (void *)lbl_8035EDBC };
static __declspec(section ".data") u8 sPad_1058[8] = { 0, 0, 0, 0x37, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1060[1] = { (void *)lbl_8035EDC4 };
static __declspec(section ".data") u8 sPad_1064[8] = { 0, 0, 0, 0x38, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_106C[1] = { (void *)lbl_8035EF80 };
static __declspec(section ".data") u8 sPad_1070[8] = { 0, 0, 0, 0x39, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1078[1] = { (void *)lbl_80297B48 };
static __declspec(section ".data") u8 sPad_107C[8] = { 0, 0, 0, 0x3A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1084[1] = { (void *)lbl_80297B54 };
static __declspec(section ".data") u8 sPad_1088[8] = { 0, 0, 0, 0x3B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1090[1] = { (void *)lbl_8035EF88 };
static __declspec(section ".data") u8 sPad_1094[8] = { 0, 0, 0, 0x3C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_109C[1] = { (void *)lbl_8035EF90 };
static __declspec(section ".data") u8 sPad_10A0[8] = { 0, 0, 0, 0x3D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10A8[1] = { (void *)lbl_8035ECD0 };
static __declspec(section ".data") u8 sPad_10AC[8] = { 0, 0, 0, 0x3E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10B4[1] = { (void *)lbl_8035EF98 };
static __declspec(section ".data") u8 sPad_10B8[8] = { 0, 0, 0, 0x3F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10C0[1] = { (void *)lbl_8035EFA0 };
static __declspec(section ".data") u8 sPad_10C4[8] = { 0, 0, 0, 0x40, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10CC[1] = { (void *)lbl_80297B60 };
static __declspec(section ".data") u8 sPad_10D0[8] = { 0, 0, 0, 0x41, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10D8[1] = { (void *)lbl_8035ED48 };
static __declspec(section ".data") u8 sPad_10DC[8] = { 0, 0, 0, 0x42, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10E4[1] = { (void *)lbl_8035EFA8 };
static __declspec(section ".data") u8 sPad_10E8[8] = { 0, 0, 0, 0x43, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10F0[1] = { (void *)lbl_8035EFB0 };
static __declspec(section ".data") u8 sPad_10F4[8] = { 0, 0, 0, 0x44, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_10FC[1] = { (void *)lbl_8035EFB8 };
static __declspec(section ".data") u8 sPad_1100[8] = { 0, 0, 0, 0x45, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1108[1] = { (void *)lbl_8035EFC0 };
static __declspec(section ".data") u8 sPad_110C[8] = { 0, 0, 0, 0x46, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1114[1] = { (void *)lbl_80297B6C };
static __declspec(section ".data") u8 sPad_1118[8] = { 0, 0, 0, 0x47, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1120[1] = { (void *)lbl_80297B78 };
static __declspec(section ".data") u8 sPad_1124[8] = { 0, 0, 0, 0x48, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_112C[1] = { (void *)lbl_8035EFC8 };
static __declspec(section ".data") u8 sPad_1130[8] = { 0, 0, 0, 0x49, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1138[1] = { (void *)lbl_8035EFD0 };
static __declspec(section ".data") u8 sPad_113C[8] = { 0, 0, 0, 0x4A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1144[1] = { (void *)lbl_8035EFD8 };
static __declspec(section ".data") u8 sPad_1148[8] = { 0, 0, 0, 0x4B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1150[1] = { (void *)lbl_8035EFE0 };
static __declspec(section ".data") u8 sPad_1154[8] = { 0, 0, 0, 0x4C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_115C[1] = { (void *)lbl_8035EFE8 };
static __declspec(section ".data") u8 sPad_1160[8] = { 0, 0, 0, 0x4D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1168[1] = { (void *)lbl_8035EFF0 };
static __declspec(section ".data") u8 sPad_116C[8] = { 0, 0, 0, 0x4E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1174[1] = { (void *)lbl_8035EFF8 };
static __declspec(section ".data") u8 sPad_1178[8] = { 0, 0, 0, 0x4F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1180[1] = { (void *)lbl_8035F000 };
static __declspec(section ".data") u8 sPad_1184[8] = { 0, 0, 0, 0x50, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_118C[1] = { (void *)lbl_8035F008 };
static __declspec(section ".data") u8 sPad_1190[8] = { 0, 0, 0, 0x51, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1198[1] = { (void *)lbl_8035F010 };
static __declspec(section ".data") u8 sPad_119C[8] = { 0, 0, 0, 0x52, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11A4[1] = { (void *)lbl_8035F018 };
static __declspec(section ".data") u8 sPad_11A8[8] = { 0, 0, 0, 0x53, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11B0[1] = { (void *)lbl_80297B84 };
static __declspec(section ".data") u8 sPad_11B4[8] = { 0, 0, 0, 0x54, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11BC[1] = { (void *)lbl_80297B90 };
static __declspec(section ".data") u8 sPad_11C0[8] = { 0, 0, 0, 0x55, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11C8[1] = { (void *)lbl_80297B9C };
static __declspec(section ".data") u8 sPad_11CC[8] = { 0, 0, 0, 0x56, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11D4[1] = { (void *)lbl_80297BA8 };
static __declspec(section ".data") u8 sPad_11D8[8] = { 0, 0, 0, 0x57, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11E0[1] = { (void *)lbl_80297BB4 };
static __declspec(section ".data") u8 sPad_11E4[8] = { 0, 0, 0, 0x58, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11EC[1] = { (void *)lbl_80297BC0 };
static __declspec(section ".data") u8 sPad_11F0[8] = { 0, 0, 0, 0x59, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_11F8[1] = { (void *)lbl_80297BCC };
static __declspec(section ".data") u8 sPad_11FC[8] = { 0, 0, 0, 0x5A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1204[1] = { (void *)lbl_80297BD8 };
static __declspec(section ".data") u8 sPad_1208[8] = { 0, 0, 0, 0x5B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1210[1] = { (void *)lbl_80297BE4 };
static __declspec(section ".data") u8 sPad_1214[8] = { 0, 0, 0, 0x5C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_121C[1] = { (void *)lbl_80297BF0 };
static __declspec(section ".data") u8 sPad_1220[8] = { 0, 0, 0, 0x5D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1228[1] = { (void *)lbl_80297BFC };
static __declspec(section ".data") u8 sPad_122C[8] = { 0, 0, 0, 0x5E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1234[1] = { (void *)lbl_80297C08 };
static __declspec(section ".data") u8 sPad_1238[8] = { 0, 0, 0, 0x5F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1240[1] = { (void *)lbl_80297C14 };
static __declspec(section ".data") u8 sPad_1244[8] = { 0, 0, 0, 0x60, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_124C[1] = { (void *)lbl_80297C20 };
static __declspec(section ".data") u8 sPad_1250[8] = { 0, 0, 0, 0x61, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1258[1] = { (void *)lbl_80297C2C };
static __declspec(section ".data") u8 sPad_125C[8] = { 0, 0, 0, 0x62, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1264[1] = { (void *)lbl_80297C38 };
static __declspec(section ".data") u8 sPad_1268[8] = { 0, 0, 0, 0x63, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1270[1] = { (void *)lbl_8035F020 };
static __declspec(section ".data") u8 sPad_1274[8] = { 0, 0, 0, 0x64, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_127C[1] = { (void *)lbl_8035F028 };
static __declspec(section ".data") u8 sPad_1280[8] = { 0, 0, 0, 0x65, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1288[1] = { (void *)lbl_8035F030 };
static __declspec(section ".data") u8 sPad_128C[8] = { 0, 0, 0, 0x66, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1294[1] = { (void *)lbl_8035F038 };
static __declspec(section ".data") u8 sPad_1298[8] = { 0, 0, 0, 0x67, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12A0[1] = { (void *)lbl_8035F040 };
static __declspec(section ".data") u8 sPad_12A4[8] = { 0, 0, 0, 0x68, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12AC[1] = { (void *)lbl_8035F048 };
static __declspec(section ".data") u8 sPad_12B0[8] = { 0, 0, 0, 0x69, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12B8[1] = { (void *)lbl_8035F050 };
static __declspec(section ".data") u8 sPad_12BC[8] = { 0, 0, 0, 0x6A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12C4[1] = { (void *)lbl_8035F058 };
static __declspec(section ".data") u8 sPad_12C8[8] = { 0, 0, 0, 0x6B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12D0[1] = { (void *)lbl_8035F060 };
static __declspec(section ".data") u8 sPad_12D4[8] = { 0, 0, 0, 0x6C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12DC[1] = { (void *)lbl_8035F068 };
static __declspec(section ".data") u8 sPad_12E0[8] = { 0, 0, 0, 0x6D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12E8[1] = { (void *)lbl_8035EE90 };
static __declspec(section ".data") u8 sPad_12EC[8] = { 0, 0, 0, 0x6E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_12F4[1] = { (void *)lbl_8035EE78 };
static __declspec(section ".data") u8 sPad_12F8[8] = { 0, 0, 0, 0x6F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1300[1] = { (void *)lbl_8035EE70 };
static __declspec(section ".data") u8 sPad_1304[8] = { 0, 0, 0, 0x70, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_130C[1] = { (void *)lbl_8035EE80 };
static __declspec(section ".data") u8 sPad_1310[8] = { 0, 0, 0, 0x71, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1318[1] = { (void *)lbl_80297C44 };
static __declspec(section ".data") u8 sPad_131C[8] = { 0, 0, 0, 0x72, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1324[1] = { (void *)lbl_80297C50 };
static __declspec(section ".data") u8 sPad_1328[8] = { 0, 0, 0, 0x73, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1330[1] = { (void *)lbl_80297C5C };
static __declspec(section ".data") u8 sPad_1334[8] = { 0, 0, 0, 0x74, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_133C[1] = { (void *)lbl_8035F070 };
static __declspec(section ".data") u8 sPad_1340[8] = { 0, 0, 0, 0x75, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1348[1] = { (void *)lbl_8035EEA8 };
static __declspec(section ".data") u8 sPad_134C[8] = { 0, 0, 0, 0x76, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1354[1] = { (void *)lbl_8035F078 };
static __declspec(section ".data") u8 sPad_1358[8] = { 0, 0, 0, 0x77, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1360[1] = { (void *)lbl_8035F080 };
static __declspec(section ".data") u8 sPad_1364[8] = { 0, 0, 0, 0x78, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_136C[1] = { (void *)lbl_8035F084 };
static __declspec(section ".data") u8 sPad_1370[8] = { 0, 0, 0, 0x79, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1378[1] = { (void *)lbl_8035F08C };
static __declspec(section ".data") u8 sPad_137C[8] = { 0, 0, 0, 0x7A, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1384[1] = { (void *)lbl_8035F094 };
static __declspec(section ".data") u8 sPad_1388[8] = { 0, 0, 0, 0x7B, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1390[1] = { (void *)lbl_80297C68 };
static __declspec(section ".data") u8 sPad_1394[8] = { 0, 0, 0, 0x7C, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_139C[1] = { (void *)lbl_80297A7C };
static __declspec(section ".data") u8 sPad_13A0[8] = { 0, 0, 0, 0x7D, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13A8[1] = { (void *)lbl_802979F8 };
static __declspec(section ".data") u8 sPad_13AC[8] = { 0, 0, 0, 0x7E, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13B4[1] = { (void *)lbl_80297C74 };
static __declspec(section ".data") u8 sPad_13B8[8] = { 0, 0, 0, 0x7F, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13C0[1] = { (void *)lbl_80297C80 };
static __declspec(section ".data") u8 sPad_13C4[8] = { 0, 0, 0, 0x80, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13CC[1] = { (void *)lbl_80297C8C };
static __declspec(section ".data") u8 sPad_13D0[8] = { 0, 0, 0, 0x81, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13D8[1] = { (void *)lbl_80297C98 };
static __declspec(section ".data") u8 sPad_13DC[8] = { 0, 0, 0, 0x82, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13E4[1] = { (void *)lbl_80297CA4 };
static __declspec(section ".data") u8 sPad_13E8[8] = { 0, 0, 0, 0x83, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13F0[1] = { (void *)lbl_80297CB0 };
static __declspec(section ".data") u8 sPad_13F4[8] = { 0, 0, 0, 0x84, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_13FC[1] = { (void *)lbl_80297CBC };
static __declspec(section ".data") u8 sPad_1400[8] = { 0, 0, 0, 0x85, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1408[1] = { (void *)lbl_80297CC8 };
static __declspec(section ".data") u8 sPad_140C[8] = { 0, 0, 0, 0x86, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1414[1] = { (void *)lbl_80297CD4 };
static __declspec(section ".data") u8 sPad_1418[8] = { 0, 0, 0, 0x87, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1420[1] = { (void *)lbl_80297CE0 };
static __declspec(section ".data") u8 sPad_1424[8] = { 0, 0, 0, 0x88, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_142C[1] = { (void *)lbl_80297CEC };
static __declspec(section ".data") u8 sPad_1430[8] = { 0, 0, 0, 0x89, 0, 0, 0, 1 };
static __declspec(section ".data") void *sPad_1438[1] = { (void *)lbl_80297A1C };
static __declspec(section ".data") u8 sPad_143C[564] = { 0, 0, 0, 0x8A, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 5, 0, 0, 0, 6, 0, 0, 0, 7, 0, 0, 0, 8, 0, 0, 0, 9, 0, 0, 0, 0xA, 0, 0, 0, 0xB, 0, 0, 0, 0xC, 0, 0, 0, 0xD, 0, 0, 0, 0xE, 0, 0, 0, 0xF, 0, 0, 0, 0x10, 0, 0, 0, 0x11, 0, 0, 0, 0x12, 0, 0, 0, 0x13, 0, 0, 0, 0x14, 0, 0, 0, 0x15, 0, 0, 0, 0x16, 0, 0, 0, 0x17, 0, 0, 0, 0x18, 0, 0, 0, 0x19, 0, 0, 0, 0x1A, 0, 0, 0, 0x1B, 0, 0, 0, 0x1C, 0, 0, 0, 0x1D, 0, 0, 0, 0x1E, 0, 0, 0, 0x1F, 0, 0, 0, 0x20, 0, 0, 0, 0x21, 0, 0, 0, 0x22, 0, 0, 0, 0x23, 0, 0, 0, 0x24, 0, 0, 0, 0x25, 0, 0, 0, 0x26, 0, 0, 0, 0x27, 0, 0, 0, 0x28, 0, 0, 0, 0x29, 0, 0, 0, 0x2A, 0, 0, 0, 0x2B, 0, 0, 0, 0x2C, 0, 0, 0, 0x2D, 0, 0, 0, 0x2E, 0, 0, 0, 0x2F, 0, 0, 0, 0x30, 0, 0, 0, 0x31, 0, 0, 0, 0x32, 0, 0, 0, 0x33, 0, 0, 0, 0x34, 0, 0, 0, 0x35, 0, 0, 0, 0x36, 0, 0, 0, 0x37, 0, 0, 0, 0x38, 0, 0, 0, 0x39, 0, 0, 0, 0x3A, 0, 0, 0, 0x3B, 0, 0, 0, 0x3C, 0, 0, 0, 0x3D, 0, 0, 0, 0x3E, 0, 0, 0, 0x3F, 0, 0, 0, 0x40, 0, 0, 0, 0x41, 0, 0, 0, 0x42, 0, 0, 0, 0x43, 0, 0, 0, 0x44, 0, 0, 0, 0x45, 0, 0, 0, 0x46, 0, 0, 0, 0x47, 0, 0, 0, 0x48, 0, 0, 0, 0x49, 0, 0, 0, 0x4A, 0, 0, 0, 0x4B, 0, 0, 0, 0x4C, 0, 0, 0, 0x4D, 0, 0, 0, 0x4E, 0, 0, 0, 0x4F, 0, 0, 0, 0x50, 0, 0, 0, 0x51, 0, 0, 0, 0x52, 0, 0, 0, 0x53, 0, 0, 0, 0x54, 0, 0, 0, 0x55, 0, 0, 0, 0x56, 0, 0, 0, 0x57, 0, 0, 0, 0x58, 0, 0, 0, 0x59, 0, 0, 0, 0x5A, 0, 0, 0, 0x5B, 0, 0, 0, 0x5C, 0, 0, 0, 0x5D, 0, 0, 0, 0x5E, 0, 0, 0, 0x5F, 0, 0, 0, 0x60, 0, 0, 0, 0x61, 0, 0, 0, 0x62, 0, 0, 0, 0x63, 0, 0, 0, 0x64, 0, 0, 0, 0x65, 0, 0, 0, 0x66, 0, 0, 0, 0x67, 0, 0, 0, 0x68, 0, 0, 0, 0x69, 0, 0, 0, 0x6A, 0, 0, 0, 0x6B, 0, 0, 0, 0x6C, 0, 0, 0, 0x6D, 0, 0, 0, 0x6E, 0, 0, 0, 0x6F, 0, 0, 0, 0x70, 0, 0, 0, 0x71, 0, 0, 0, 0x72, 0, 0, 0, 0x73, 0, 0, 0, 0x74, 0, 0, 0, 0x75, 0, 0, 0, 0x76, 0, 0, 0, 0x77, 0, 0, 0, 0x78, 0, 0, 0, 0x79, 0, 0, 0, 0x7A, 0, 0, 0, 0x7B, 0, 0, 0, 0x7C, 0, 0, 0, 0x7D, 0, 0, 0, 0x7E, 0, 0, 0, 0x7F, 0, 0, 0, 0x80, 0, 0, 0, 0x81, 0, 0, 0, 0x82, 0, 0, 0, 0x83, 0, 0, 0, 0x84, 0, 0, 0, 0x85, 0, 0, 0, 0x86, 0, 0, 0, 0x87, 0, 0, 0, 0x88, 0, 0, 0, 0x89, 0, 0, 0, 0x8A };
static __declspec(section ".data") s32 tA[139] = { 0, 0x25, 0x44, 0x5E, 0x66, 0x72, 0x7E, 0x8B, 0x8E, 0x9A, 0x9D, 0xA8, 0xAB, 0xB6, 0xB9, 0xBC, 0xBF, 0xC2, 0xD1, 0xE0, 0xEF, 0xFD, 0x105, 0x10D, 0x11C, 0x12B, 0x139, 0x147, 0x155, 0x163, 0x16F, 0x17B, 0x187, 0x193, 0x1A2, 0x1B2, 0x1C2, 0x1D2, 0x1E1, 0x1EC, 0x1F9, 0x204, 0x215, 0x21B, 0x22A, 0x239, 0x248, 0x255, 0x25A, 0x269, 0x278, 0x27B, 0x28A, 0x297, 0x2A2, 0x2AC, 0x2AE, 0x2B4, 0x2C3, 0x2D2, 0x2E1, 0x2F0, 0x2FF, 0x30E, 0x31D, 0x32C, 0x33B, 0x34A, 0x359, 0x368, 0x377, 0x389, 0x398, 0x3A7, 0x3AA, 0x3B9, 0x3C8, 0x3D7, 0x3E6, 0x3F5, 0x404, 0x413, 0x422, 0x431, 0x440, 0x44F, 0x45E, 0x46D, 0x47C, 0x48B, 0x49A, 0x4A9, 0x4B8, 0x4C7, 0x4D6, 0x4E5, 0x4F4, 0x503, 0x512, 0x521, 0x530, 0x533, 0x536, 0x547, 0x558, 0x569, 0x57A, 0x589, 0x598, 0x5A7, 0x5B6, 0x5C5, 0x5D4, 0x5E5, 0x5F6, 0x5F9, 0x5FC, 0x5FF, 0x602, 0x611, 0x614, 0x617, 0x618, 0x619, 0x61A, 0x61B, 0x620, 0x623, 0x626, 0x627, 0x628, 0x629, 0x62A, 0x62B, 0x62C, 0x62D, 0x62E, 0x62F, 0x630 };
static __declspec(section ".data") s32 tB[1585] = { 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1, 1, 4, 1, 3, 1, 1, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 3, 1, 1, 2, 2, 1, 3, 1, 2, 1, 1, 1, 3, 2, 2, 2, 1, 1, 1, 1, 1, 4, 1, 1, 0xB, 1, 0xD, 1, 5, 1, 8, 5, 1, 1, 1, 3, 1, 4, 1, 0x13, 3, 1, 1, 5, 1, 1, 1, 3, 1, 4, 1, 0x13, 3, 1, 1, 5, 1, 1, 4, 1, 4, 1, 9, 1, 9, 3, 1, 1, 7, 1, 0x21, 7, 1, 2, 2, 7, 1, 0xC, 2, 2, 3, 1, 1, 7, 1, 0x21, 1, 2, 2, 1, 1, 1, 8, 1, 9, 1, 0xE, 0x20, 1, 8, 3, 2, 1, 2, 8, 1, 9, 1, 9, 1, 4, 0x24, 1, 4, 0x24, 1, 4, 0x24, 1, 4, 0x24, 1, 4, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 2, 4, 1, 9, 1, 5, 2, 2, 3, 1, 1, 5, 1, 2, 2, 2, 4, 1, 9, 1, 5, 2, 2, 3, 1, 1, 1, 1, 1, 2, 1, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 3, 1, 0x1D, 3, 2, 1, 1, 1, 3, 1, 0x1D, 3, 2, 1, 1, 1, 1, 1, 1, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 2, 3, 1, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 6, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 6, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 6, 1, 1, 1, 1, 1, 2, 1, 3, 2, 0x14, 2, 6, 1, 5, 1, 2, 2, 2, 4, 1, 9, 1, 5, 2, 2, 3, 1, 1, 5, 1, 2, 2, 3, 3, 3, 7, 1, 5, 1, 2, 1, 3, 1, 1, 5, 1, 2, 2, 3, 3, 3, 7, 1, 5, 1, 2, 1, 3, 1, 1, 5, 1, 2, 2, 3, 3, 3, 7, 1, 5, 1, 2, 1, 3, 1, 1, 5, 1, 2, 2, 3, 3, 3, 7, 1, 6, 2, 1, 3, 1, 1, 5, 1, 1, 1, 8, 1, 9, 1, 5, 1, 8, 5, 1, 1, 1, 3, 1, 4, 1, 8, 2, 5, 2, 7, 5, 1, 1, 1, 8, 1, 0xF, 1, 1, 1, 6, 5, 1, 2, 2, 2, 4, 1, 1, 1, 7, 1, 5, 2, 2, 3, 1, 1, 1, 5, 1, 0x13, 1, 0xE, 5, 1, 2, 2, 3, 3, 3, 7, 1, 5, 2, 2, 3, 1, 1, 5, 1, 2, 2, 3, 3, 2, 8, 1, 5, 2, 2, 3, 1, 1, 5, 1, 2, 2, 3, 3, 2, 8, 1, 5, 2, 2, 3, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xD, 0xC, 1, 4, 2, 0x16, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 1, 3, 2, 6, 1, 7, 1, 5, 2, 2, 3, 1, 1, 0x12, 1, 0x16, 5, 1, 2, 2, 3, 3, 3, 7, 1, 5, 2, 2, 3, 1, 1, 5, 2, 1, 2, 3, 3, 3, 7, 1, 5, 2, 6, 1, 1, 4, 2, 1, 2, 2, 4, 1, 9, 1, 0xE, 5, 2, 1, 2, 2, 4, 1, 9, 1, 0xE, 1, 0x28, 5, 2, 1, 0x12, 1, 0xE, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 2, 1, 2, 1, 1, 1, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 2, 0xA, 1, 1, 0x1C, 1, 0xC, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 0x1C, 4, 9, 0x1C, 4, 9, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 2, 1, 8, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 1, 3, 7, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 1, 3, 7, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 1, 3, 7, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 2, 1, 8, 1, 1, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 3, 1, 7, 1, 1, 0x1C, 1, 0xC, 0x1C, 1, 0xC, 0x22, 2, 5, 0x20, 1, 8, 5, 1, 2, 2, 3, 3, 4, 1, 1, 2, 3, 1, 0xB, 1, 1, 0x20, 1, 8, 0x20, 1, 8, 0x29, 0x29, 0x29, 0x29, 0x1B, 1, 0xB, 1, 1, 0x1B, 1, 0xD, 0x1B, 1, 0xD, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29, 0x29 };
static __declspec(section ".data") s32 tC[1585] = { 0, 1, 2, 3, 4, 5, 6, 7, 5, 8, 9, 0xA, 5, 0xB, 0xC, 0xD, 0xE, 5, 0xF, 5, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 5, 0x22, 5, 0x22, 0x23, 5, 0x24, 5, 0x25, 0x26, 0x27, 5, 0x28, 5, 0x29, 5, 0x2A, 0x2B, 0x2C, 5, 0x2A, 0x2D, 0x2E, 5, 0x2F, 5, 0x30, 5, 0x31, 5, 0x32, 0x33, 0x32, 5, 0x1D, 0x34, 5, 0x32, 0x35, 5, 0x1D, 5, 0x36, 5, 0x1D, 5, 0x1D, 5, 0x1D, 0x37, 0x38, 0x1D, 0x39, 0x3A, 5, 0x1D, 0x3B, 5, 0x3C, 5, 0x1D, 5, 0x3D, 5, 0x3E, 5, 0x3E, 0x3F, 5, 0x3E, 5, 0x3E, 5, 0x3E, 5, 0x3E, 0x40, 5, 0x40, 0x3F, 5, 0x40, 5, 0x40, 5, 0x40, 5, 0x40, 0x41, 5, 0x41, 5, 0x42, 5, 0x43, 5, 0x43, 5, 0x41, 5, 0x44, 5, 0x45, 5, 5, 0x46, 5, 0x47, 5, 0x48, 5, 0x48, 5, 0x48, 5, 0x48, 5, 0x49, 5, 0x4A, 0x4B, 0x4C, 5, 0x4A, 0x4B, 5, 0x4B, 5, 0x4A, 5, 5, 0x4D, 5, 0x4E, 0x4F, 5, 0x4E, 5, 0x4E, 5, 0x4E, 5, 0x50, 5, 5, 0x51, 5, 5, 0x52, 5, 5, 0x53, 5, 5, 0x54, 5, 0x55, 5, 0x55, 5, 0x55, 5, 0x55, 5, 0x55, 5, 0x55, 5, 0x55, 5, 0x55, 0x56, 5, 0x56, 5, 0x56, 5, 0x56, 5, 0x56, 5, 0x56, 5, 0x56, 5, 0x56, 0x57, 5, 0x57, 5, 0x57, 5, 0x57, 5, 0x57, 5, 0x57, 5, 0x57, 5, 0x57, 0x58, 0x59, 0x5A, 0x5B, 5, 0x58, 5, 0x5B, 5, 0x5B, 5, 0x58, 5, 0x5C, 0x5D, 0x5E, 0x5F, 5, 0x5D, 5, 0x5F, 5, 0x60, 0x5E, 0x61, 5, 0x62, 5, 0x63, 5, 0x64, 0x5E, 0x65, 5, 0x66, 5, 0x64, 5, 0x1D, 5, 0x1D, 5, 0x67, 5, 0x68, 0x69, 0x5E, 0x6A, 5, 0x66, 5, 0x69, 5, 0x1D, 5, 0x1D, 5, 0x6B, 5, 0x68, 0x6C, 0x5E, 0x6D, 0x6E, 5, 0x6C, 5, 0x1D, 5, 0x1D, 5, 0x6F, 5, 0x68, 0x70, 0x71, 0x72, 0x6E, 5, 0x70, 5, 0x1D, 5, 0x1D, 5, 0x73, 5, 0x68, 0x74, 0x5E, 0x75, 0x6E, 5, 0x74, 5, 0x1D, 5, 0x1D, 5, 0x76, 5, 0x68, 0x77, 0x5E, 0x78, 0x6E, 5, 0x77, 5, 0x1D, 5, 0x1D, 5, 0x79, 5, 0x68, 0x7A, 0x5E, 0x7B, 0x6E, 5, 0x7A, 5, 0x1D, 5, 0x1D, 5, 0x68, 0x7C, 0x71, 0x7D, 0x6E, 5, 0x7C, 5, 0x1D, 5, 0x1D, 5, 0x68, 0x7E, 0x5E, 0x7F, 0x6E, 5, 0x7E, 5, 0x1D, 5, 0x1D, 5, 0x68, 0x80, 0x5E, 0x81, 0x6E, 5, 0x80, 5, 0x1D, 5, 0x1D, 5, 0x68, 0x82, 5, 0x82, 5, 0x82, 5, 0x82, 5, 0x82, 5, 0x82, 5, 0x82, 5, 0x82, 0x83, 5, 0x83, 5, 0x83, 5, 0x83, 5, 0x83, 5, 0x84, 0x83, 5, 0x83, 5, 0x83, 0x85, 5, 0x85, 5, 0x85, 5, 0x85, 5, 0x85, 5, 0x86, 0x85, 5, 0x85, 5, 0x85, 0x87, 5, 0x87, 5, 0x87, 5, 0x87, 5, 0x87, 5, 0x88, 0x87, 5, 0x87, 5, 0x87, 0x89, 5, 0x89, 5, 0x89, 5, 0x89, 5, 0x89, 5, 0x89, 5, 0x89, 5, 0x89, 0x8A, 5, 0x8A, 0x8B, 5, 0x8A, 5, 0x8A, 5, 0x8A, 5, 0x8C, 5, 0x8C, 0x8D, 5, 0x8C, 5, 0x8C, 5, 0x8C, 5, 0x8C, 5, 0x8E, 5, 0x8E, 0x8F, 5, 0x8E, 5, 0x8E, 5, 0x90, 5, 0x91, 5, 0x91, 5, 0x91, 5, 0x91, 5, 0x91, 5, 0x91, 5, 0x91, 5, 0x91, 5, 0x91, 0x92, 5, 0x92, 5, 0x92, 5, 0x93, 5, 0x93, 5, 0x93, 5, 0x93, 5, 0x93, 5, 0x93, 5, 0x93, 5, 0x93, 0x94, 5, 0x94, 5, 0x94, 5, 0x94, 5, 0x94, 5, 0x94, 5, 0x94, 5, 0x94, 0x95, 5, 0x95, 5, 0x95, 5, 0x95, 5, 0x95, 5, 0x95, 5, 0x95, 5, 0x95, 0x96, 5, 0x96, 5, 0x96, 5, 0x96, 5, 0x96, 5, 0x96, 5, 0x96, 5, 0x97, 5, 0x97, 5, 0x98, 5, 0x98, 5, 0x98, 5, 0x98, 5, 0x98, 5, 0x98, 5, 0x98, 5, 0x98, 0x99, 5, 0x99, 5, 0x99, 5, 0x9A, 5, 0x99, 5, 0x99, 5, 0x99, 5, 0x99, 5, 0x1D, 5, 0x9B, 5, 0x9B, 5, 0x9B, 5, 0x9B, 5, 0x9B, 5, 0x9B, 5, 0x9B, 5, 0x9B, 0x9C, 5, 0x9C, 5, 0x9C, 5, 0x9C, 5, 0x9C, 5, 0x9C, 5, 0x9C, 0x9D, 0x9E, 5, 0x9E, 5, 0x9E, 5, 0x9E, 5, 0x9E, 5, 0x9F, 5, 0x9F, 5, 0x9F, 5, 0xA0, 5, 0x9F, 5, 0xA1, 5, 0xA2, 5, 0xA2, 5, 0xA2, 5, 0xA3, 5, 0xA3, 5, 0xA3, 5, 0xA3, 5, 0xA3, 5, 0xA3, 5, 0xA3, 5, 0xA3, 0xA4, 5, 0xA4, 5, 0xA4, 5, 0xA4, 5, 0xA4, 5, 0xA4, 5, 0xA4, 5, 0xA4, 0xA5, 5, 0xA5, 5, 0xA5, 5, 0xA5, 5, 0xA5, 5, 0xA5, 5, 0xA5, 5, 0xA5, 0xA6, 5, 0xA6, 5, 0xA6, 5, 0xA6, 5, 0xA6, 5, 0xA6, 5, 0xA6, 5, 0xA6, 0xA7, 5, 0xA7, 5, 0xA7, 5, 0xA7, 5, 0xA7, 5, 0xA7, 5, 0xA7, 5, 0xA7, 0xA8, 5, 0xA8, 5, 0xA8, 5, 0xA8, 5, 0xA8, 5, 0xA8, 5, 0xA8, 5, 0xA8, 0xA9, 5, 0xA9, 5, 0xA9, 5, 0xA9, 5, 0xA9, 5, 0xA9, 5, 0xA9, 5, 0xA9, 0xAA, 5, 0xAA, 5, 0xAA, 5, 0xAA, 5, 0xAA, 5, 0xAA, 5, 0xAA, 5, 0xAA, 0xAB, 5, 0xAB, 5, 0xAB, 5, 0xAB, 5, 0xAB, 5, 0xAB, 5, 0xAB, 5, 0xAB, 0xAC, 5, 0xAC, 5, 0xAC, 5, 0xAC, 5, 0xAC, 5, 0xAC, 5, 0xAC, 5, 0xAC, 0xAD, 5, 0xAD, 5, 0xAD, 5, 0xAD, 5, 0xAD, 5, 0xAD, 5, 0xAD, 5, 0xAD, 0xAE, 5, 0xAE, 5, 0xAE, 5, 0xAE, 5, 0xAE, 5, 0xAE, 5, 0xAE, 5, 0xAE, 0xAF, 5, 0xAF, 5, 0xAF, 5, 0xAF, 5, 0xAF, 5, 0xAF, 5, 0xAF, 5, 0xAF, 0xB0, 0xB1, 0xB0, 5, 0xB0, 0xB2, 5, 0xB0, 5, 0xB0, 5, 0xB0, 5, 0xB0, 5, 0xB0, 5, 0xB0, 0xB3, 5, 0xB3, 5, 0xB3, 5, 0xB3, 5, 0xB3, 5, 0xB3, 5, 0xB3, 5, 0xB3, 0x1D, 5, 0x1D, 5, 0x1D, 5, 0x1D, 5, 0x1D, 5, 0x1D, 5, 0x1D, 5, 0x1D, 5, 0xB4, 5, 0xB5, 5, 0xB5, 5, 0xB5, 5, 0xB5, 5, 0xB5, 5, 0xB5, 5, 0xB5, 5, 0xB5, 0xB6, 5, 0xB6, 5, 0xB6, 5, 0xB6, 5, 0xB6, 5, 0xB6, 5, 0xB6, 5, 0xB6, 0xB7, 5, 0xB7, 5, 0xB7, 5, 0xB7, 5, 0xB7, 5, 0xB7, 5, 0xB7, 5, 0xB7, 0xB8, 5, 0xB8, 5, 0xB8, 5, 0xB8, 5, 0xB8, 5, 0xB8, 5, 0xB8, 5, 0xB8, 0xB9, 5, 0xB9, 5, 0xB9, 5, 0xB9, 5, 0xB9, 5, 0xB9, 5, 0xB9, 5, 0xB9, 0xBA, 5, 0xBA, 5, 0xBA, 5, 0xBA, 5, 0xBA, 5, 0xBA, 5, 0xBA, 5, 0xBA, 0xBB, 5, 0xBB, 5, 0xBB, 5, 0xBB, 5, 0xBB, 5, 0xBB, 5, 0xBB, 5, 0xBB, 0xBC, 5, 0xBC, 5, 0xBC, 5, 0xBC, 5, 0xBC, 5, 0xBC, 5, 0xBC, 5, 0xBC, 0xBD, 5, 0xBD, 5, 0xBD, 5, 0xBD, 5, 0xBD, 5, 0xBD, 5, 0xBD, 5, 0xBD, 0xBE, 5, 0xBE, 5, 0xBE, 5, 0xBE, 5, 0xBE, 5, 0xBE, 5, 0xBE, 5, 0xBE, 0xBF, 5, 0xBF, 5, 0xBF, 5, 0xBF, 5, 0xBF, 5, 0xBF, 5, 0xBF, 5, 0xBF, 0xC0, 5, 0xC0, 5, 0xC0, 5, 0xC0, 5, 0xC0, 5, 0xC0, 5, 0xC0, 5, 0xC0, 0xC1, 5, 0xC1, 5, 0xC1, 5, 0xC1, 5, 0xC1, 5, 0xC1, 5, 0xC1, 5, 0xC1, 0xC2, 5, 0xC2, 5, 0xC2, 5, 0xC2, 5, 0xC2, 5, 0xC2, 5, 0xC2, 5, 0xC2, 0xC3, 5, 0xC3, 5, 0xC3, 5, 0xC3, 5, 0xC3, 5, 0xC3, 5, 0xC3, 5, 0xC3, 0xC4, 5, 0xC4, 5, 0xC4, 5, 0xC4, 5, 0xC4, 5, 0xC4, 5, 0xC4, 5, 0xC4, 0xC5, 5, 0xC5, 5, 0xC5, 5, 0xC5, 5, 0xC5, 5, 0xC5, 5, 0xC5, 5, 0xC5, 0xC6, 5, 0xC6, 5, 0xC6, 5, 0xC6, 5, 0xC6, 5, 0xC6, 5, 0xC6, 5, 0xC6, 0xC7, 5, 0xC7, 5, 0xC7, 5, 0xC7, 5, 0xC7, 5, 0xC7, 5, 0xC7, 5, 0xC7, 0xC8, 5, 0xC8, 5, 0xC8, 5, 0xC8, 5, 0xC8, 5, 0xC8, 5, 0xC8, 5, 0xC8, 0xC9, 5, 0xC9, 5, 0xC9, 5, 0xC9, 5, 0xC9, 5, 0xC9, 5, 0xC9, 5, 0xC9, 0xCA, 5, 0xCA, 5, 0xCA, 5, 0xCA, 5, 0xCA, 5, 0xCA, 5, 0xCA, 5, 0xCA, 0xCB, 5, 0xCB, 5, 0xCB, 5, 0xCB, 5, 0xCB, 5, 0xCB, 5, 0xCB, 5, 0xCB, 0xCC, 5, 0xCC, 5, 0xCC, 5, 0xCC, 5, 0xCC, 5, 0xCC, 5, 0xCC, 5, 0xCC, 0xCD, 5, 0xCD, 5, 0xCD, 5, 0xCD, 5, 0xCD, 5, 0xCD, 5, 0xCD, 5, 0xCD, 0xCE, 5, 0xCE, 5, 0xCE, 5, 0xCE, 5, 0xCE, 5, 0xCE, 5, 0xCE, 5, 0xCE, 5, 0xCF, 5, 5, 0xD0, 5, 0xD1, 5, 0xD1, 5, 0xD1, 5, 0xD1, 5, 0xD1, 5, 0xD1, 5, 0xD1, 5, 0xD1, 5, 0xD1, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD2, 5, 0xD3, 5, 0xD3, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 5, 0xD2, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 5, 0xD3, 0xD4, 5, 0xD4, 5, 0xD4, 5, 0xD4, 5, 0xD4, 5, 0xD4, 5, 0xD4, 5, 0xD4, 0xD5, 5, 0xD5, 5, 0xD5, 5, 0xD5, 5, 0xD5, 5, 0xD5, 5, 0xD5, 5, 0xD5, 0xD6, 5, 0xD6, 5, 0xD6, 5, 0xD6, 5, 0xD6, 5, 0xD6, 5, 0xD6, 5, 0xD6, 0xD7, 5, 0xD7, 5, 0xD7, 5, 0xD7, 5, 0xD7, 5, 0xD7, 5, 0xD7, 5, 0xD7, 0xD8, 5, 0xD8, 5, 0xD8, 5, 0xD8, 5, 0xD8, 5, 0xD8, 5, 0xD8, 5, 0xD8, 0xD9, 5, 0xD9, 5, 0xD9, 5, 0xD9, 5, 0xD9, 5, 0xD9, 5, 0xD9, 5, 0xD9, 5, 0xD9, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDA, 5, 0xDB, 5, 5, 0xDC, 5, 5, 0xDD, 5, 5, 0x4D, 5, 0xDE, 5, 0xDE, 5, 0xDE, 5, 0xDE, 5, 0xDE, 5, 0xDE, 5, 0xDE, 5, 0xDE, 5, 0xDF, 5, 5, 0xDF, 5, 0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 5, 0xE4, 5, 0xE4, 5, 0x1D, 5, 5, 0xE5, 5, 0xE6, 0xE7, 0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF, 0xF0 };
__declspec(section ".data") u8 lbl_802C1E1C[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
static __declspec(section ".data") void *fill_802C1E24[19] = { (void *)fn_80070A88, (void *)fn_80249AC4, (void *)fn_800706D8, (void *)fn_8006FEA4, (void *)fn_80070324, (void *)fn_8023D198, (void *)fn_80070C1C, (void *)fn_800690FC, (void *)fn_80241D80, (void *)fn_8003F140, (void *)fn_8003F18C, (void *)fn_8006D124, (void *)fn_8006DA44, (void *)fn_802416D4, (void *)fn_8003F1DC, (void *)fn_800712B0, (void *)fn_80070CC0, (void *)fn_8006DAD8, (void *)fn_8006C3CC };

extern int lbl_8035B308;
extern int lbl_8035B65C;
#define GV ((VG *)lbl_8035B65C)
extern int lbl_80359F2C;
extern int lbl_8035B5E4;
extern int lbl_8035B374;
extern int lbl_8035A0A4;
extern int lbl_8035B684;
extern int lbl_8035B6E4;
extern f32 lbl_8035F0B4, lbl_8035F0B8, lbl_8035F0BC, lbl_8035F0C0, lbl_8035F0C4, lbl_8035F0C8, lbl_8035F0CC, lbl_8035F0E0, lbl_8035F0EC, lbl_8035F0F0, lbl_8035F1BC, lbl_8035F1C8;
extern char lbl_8035F09C[4], lbl_8035F0A4[4], lbl_8035F0AC[4], lbl_8035EE70[4], lbl_8035F0D0[4], lbl_8035F0D8[4], lbl_8035ED68[4], lbl_8035F0E4[4], lbl_8035EE18[4], lbl_8035ECE0[4], lbl_8035F1C0[8], lbl_8035F1CC[4], lbl_8035F1D4[4], lbl_8035EEA8[4];
extern char lbl_8035F0F4[4], lbl_8035F0FC[4], lbl_8035F104[4], lbl_8035F10C[4], lbl_8035F114[4], lbl_8035F11C[4], lbl_8035F124[4], lbl_8035F12C[4], lbl_8035F134[4], lbl_8035F13C[4], lbl_8035F144[4], lbl_8035F14C[4], lbl_8035F154[4], lbl_8035F15C[4], lbl_8035F164[4], lbl_8035F16C[4], lbl_8035F174[4], lbl_8035F17C[4], lbl_8035F184[4], lbl_8035F18C[4], lbl_8035F194[4], lbl_8035F19C[4], lbl_8035F1A4[4], lbl_8035F1AC[4], lbl_8035F1B4[4];
void __ct__9C80253F24Fiiii(void *, const char *, int, int, int);
int fn_800F6CD0(int, const char *);
void fn_800F6E88(int, int);
int fn_802288FC(int, const char *);
VE *fn_80233550(int, const char *);
int fn_8003C674(int, const char *, int **);
void fn_8002FD10(int, void *);
void fn_8019B6B8(int, int);
void fn_80253304(int, int, f32);
void fn_80253250(int);
void fn_8023F864(int, int);
void fn_802405B8(int);
void fn_80240384(int);
void fn_80240948(int, char *, int);
void fn_80240F24(int, int, int);
void fn_80241028(int, int, int);
void fn_802410CC(int, int, int);
void fn_8024125C(int, int);
void fn_802413D8(int, int, f32, int, int, int);
int fn_80241628(int, int, int);
void fn_80242168(f32, int);
void fn_80242174(f32, int);
void fn_80249008(int, int);
void fn_802490E0(int, int, f32);
int fn_802491DC(int, int);
void fn_802493D0(int, int);
int fn_802494A4(int, int);
void fn_8006B5A4(int);
void fn_8006B6F4(int);
void fn_8006B908(int);
void fn_8006BA1C(int);
void fn_8006BE6C(int);
void fn_8006BFE4(int);
int fn_8006C128(int);
void fn_8006C418(int);
void fn_8006C748(int, int, f32);
void fn_8006CD00(int, int, int, int);
void fn_8006DB6C(int);
void fn_8006DC14(int);
void fn_8006DD74(int);
void fn_8006E2F8(int);
void fn_8006E994(int, int, int);
void fn_8006EAD0(int, int, int, f32);
void fn_8006EB9C(int, int, f32);
void fn_8006EC5C(int, int);
void fn_8006ED08(int);
void fn_8006F1DC(int);
void fn_8006F26C(int);
void fn_8006F2FC(int);
void fn_8006F3CC(int);
void fn_8006F808(int);
void fn_8006FC88(int);
void fn_8006FD64(int);
void fn_80070054(int);
void fn_8007115C(int);
void fn_800716F0(int, int);
void fn_80071E68(int);
void fn_80071EE0(int);
void fn_80071F54(int, int, f32);
void fn_80072040(int, int);
void fn_8007225C(int, f32);
int fn_8007239C(int);
void fn_80072438(int, int);
void fn_8007249C(int, int);
void fn_80072BA8(int);
void fn_80072C54(int);
void fn_80072D94(int, int, f32);
void fn_800739F8(int, f32);
void fn_80076D50(int, int);
void fn_80076DFC(int, int);

#define I(o) (*(int *)(p + (o)))
#define F(o) (*(f32 *)(p + (o)))
#define PF(o) (**(f32 **)(p + (o)))
#define PI(o) (**(int **)(p + (o)))
#define VP(o) (*(VO **)(p + (o)))
#define T(o) (*(int *)(I(0x118) + (o)))
#define CT(s) __ct__9C80253F24Fiiii((void *)lbl_8035B65C, s, 0, 0, 0)
#define LIGHT (*(int *)(*(int *)(I(0x118) + 0x20c) + 0xd8))

#define walk(p, n, k) do { fn_8006EC5C(p, n); fn_80242168(k, p); fn_80241628(p, 0, 0); CT(lbl_8035F0A4); } while (0)
static inline void dead(int p) {
    int e = I(0xe0);
    *(int *)(e + 0x118) = I(0x1ac);
    *(int *)(e + 0x11c) = I(0x1b0);
    *(int *)(e + 0x120) = I(0x1b4);
    *(int *)(e + 0x154) = 0;
}
static inline void cam(int p) {
    int g = lbl_80359F2C;
    *(int *)(g + 0x16c) = 5;
    *(f32 *)(g + 0x168) = lbl_8035F0CC;
}
static inline void tog(int v) {
    VQ *q = *(VQ **)(lbl_80359F2C + 0x1c4);
    if (q != 0) q->tog(v);
}
static inline void gems(int p) {
    int n = I(0x268);
    int *volatile r = 0;
    if (fn_8003C674(*(volatile int *)&lbl_8035A0A4, ((char *)sD28), (int **)&r) == 0) { int *t = r; *t = 0; }
    { int *t = r; *t = *t + n; }
    I(0x268) = I(0x268) - n;
}
#define ld(p, a, b, k, st) do { fn_8006E994(p, a, b); fn_80242168(k, p); fn_80249008(p, 2); if (st) fn_802494A4(p, 2); } while (0)
#define lc(p, a, k, st) do { fn_8006EC5C(p, a); fn_80242168(k, p); fn_80249008(p, 2); if (st) fn_802494A4(p, 2); } while (0)
static inline int chk(int p) {
    if (T(0x4cc) == 1) {
        fn_8006ED08(p);
        return 0;
    }
    return 1;
}
static inline void notify(int p) {
    int o;
    u32 i;
    for (i = 0, o = 0; i < (u32)I(0x200); i++) {
        (*(VO **)(I(0x228) + o))->send(lbl_8035ECE0, 0, 0, 0, 0);
        o += 4;
    }
}
static inline void path(int p, char *s) {
    fn_802494A4(p, 0x1c);
    fn_80241628(p, 5, 0);
    fn_80240948(p, s, 0);
}
static inline void shot(int p, const char *n) {
    VE *e = fn_80233550(lbl_8035B374, n);
    if (e != 0) e->shot(I(0x118), 1, lbl_8035ED68, lbl_8035F1C0, 0, lbl_8035F0C0, lbl_8035F1C8);
}

void fn_800690FC(int p, int st) {
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
        T(0x4c0) = 1;
        fn_80241628(p, 0, 0);
        CT(lbl_8035F09C);
        CT(lbl_8035F0A4);
        I(0x1f0) = fn_802288FC(lbl_8035B308, lbl_8035F0AC);
        fn_80070054(p);
        I(0x298) = 0;
        break;
    case 1:
        fn_80241628(p, 0, 0);
        CT(lbl_8035F0A4);
        break;
    case 2:
        if (I(0x1ec) == 1) T(0x5e8) = 0;
        break;
    case 3:
        walk(p, 0x23, lbl_8035F0B4);
        break;
    case 4:
        walk(p, 0xe, lbl_8035F0B8);
        break;
    case 5:
        return;
    case 6:
        fn_80241628(p, 2, 0);
        fn_8006EC5C(p, 0x5e);
        break;
    case 7:
        if (I(0x1ec) == 1) T(0x5e8) = 1;
        fn_80241628(p, 1, 0);
        T(0x4c4) = 1;
        fn_8006EB9C(p, 0x26, lbl_8035F0BC);
        I(0x14c) = 0;
        fn_802491DC(p, 3);
        break;
    case 8:
        fn_8006EC5C(p, 0);
        fn_80240F24(p, 3, 6);
        fn_80241628(p, 1, 0);
        fn_800716F0(p, -1);
        break;
    case 9:
        fn_8006DB6C(p);
        fn_80241628(p, 1, 0);
        fn_800716F0(p, -1);
        break;
    case 10:
        fn_80241628(p, 2, 0);
        lbl_8035B6E4 = 1;
        break;
    case 11:
        fn_8006FD64(p);
        fn_80241628(p, 0, 0);
        CT(lbl_8035F0A4);
        I(0x14c) = 0;
        break;
    case 12:
        fn_80241628(p, 3, 0);
        *(volatile int *)&lbl_8035B6E4 = 1;
        (*(VG *volatile *)&lbl_8035B65C)->go0();
        break;
    case 13:
        T(0x33c) = 1;
        fn_80241628(p, 2, 0);
        fn_80242174(lbl_8035F0C0, p);
        break;
    case 14:
        fn_8006BA1C(p);
        break;
    case 15:
        fn_8006EC5C(p, 0x48);
        break;
    case 16:
        fn_80241628(p, 3, 0);
        T(0x68c) = 0;
        { int e = I(0xe0);
        *(f32 *)(e + 0x118) = F(0x1ac);
        *(f32 *)(e + 0x11c) = F(0x1b0);
        *(f32 *)(e + 0x120) = F(0x1b4);
        *(f32 *)(e + 0x154) = lbl_8035F0C0; }
        CT(((char *)sCF8));
        break;
    case 17:
        if (LIGHT != 1) fn_80241628(p, 2, 0);
        fn_8006EC5C(p, 0xd);
        break;
    case 18:
        fn_8006EC5C(p, 0x2d);
        fn_80242174(lbl_8035F0C4, p);
        T(0x68c) = 0;
        break;
    case 19:
        fn_8024125C(p, 8);
        fn_80241628(p, 3, 0);
        fn_8006EC5C(p, 0x74);
        fn_8006B908(p);
        I(0x274) = 1;
        T(0x68c) = 0;
        CT(((char *)sCF8));
        fn_80253304(*(int *)(lbl_8035B5E4 + 0x70) + *(int *)(lbl_8035B5E4 + 0x68) * 0x34, 2000, lbl_8035F0C8);
        break;
    case 20:
        fn_8006EC5C(p, 4);
        T(0x68c) = 0;
        fn_80076D50(I(0x118), 0);
        break;
    case 21:
        I(0xec) = (int)lbl_8035EE70;
        fn_8006C418(p);
        fn_8006EC5C(p, 0x55);
        fn_80241628(p, 2, 0);
        cam(p);
        break;
    case 22:
        T(0x68c) = 0;
        break;
    case 23:
        fn_8006EC5C(p, 0x5f);
        fn_80241628(p, 2, 0);
        tog(1);
        cam(p);
        CT(((char *)sCF8));
        break;
    case 24:
        fn_80241628(p, 2, 0);
        I(0x184) = 1;
        fn_80076D50(I(0x118), 0);
        break;
    case 25:
        fn_8006EC5C(p, 0x45);
        fn_80241628(p, 1, 0);
        fn_800716F0(p, -1);
        fn_80076D50(I(0x118), 0);
        break;
    case 26:
        fn_80240948(p, lbl_8035F0D0, 0);
        fn_80241628(p, 5, 0);
        fn_8006EC5C(p, 0x66);
        I(0x1fc) = 1;
        fn_80072C54(I(0x118));
        fn_80076D50(I(0x118), 0);
        break;
    case 27:
        I(0x1fc) = 1;
        break;
    case 28: {
        int k;
        I(0x200) = 0;
        I(0x234) = 0;
        I(0x230) = 1;
        fn_802490E0(p, 0xd, PF(0x204));
        k = fn_8007239C(I(0x118));
        fn_802490E0(p, 0xf, PF(0x208) * (f32)*(u32 *)(*(int *)(I(0x20c) + 0xc) + (k - 1) * 4));
        if (fn_8006C128(p) == 0) fn_802494A4(p, 0);
        fn_80076D50(I(0x118), 0);
        break;
    }
    case 29:
        fn_802494A4(p, 0);
        break;
    case 30:
        return;
    case 31:
        fn_80241628(p, 2, 0);
        T(0x68c) = 0;
        break;
    case 32:
        fn_8006EC5C(p, 99);
        fn_80241628(p, 0, 0);
        break;
    case 33:
        fn_80249008(p, 2);
        I(0x298) = 0;
        break;
    case 34:
        fn_80249008(p, 2);
        break;
    case 35: {
        u8 *o;
        T(0x4c4) = 0;
        I(0x154) = 0;
        o = *(u8 **)(I(0x118) + 0x234);
        if (o != 0) {
            *(int *)(o + 0x234) = 0;
            T(0x234) = 0;
        }
        fn_80249008(p, 3);
        break;
    }
    case 36:
        CT(((char *)sD04));
        break;
    case 37:
        return;
    case 38:
        CT(((char *)sD04));
        VP(0x118)->s36();
        break;
    case 39:
        T(0x33c) = 0;
        break;
    case 40:
        CT(((char *)sD10));
        VP(0x118)->s36();
        CT(lbl_8035F0A4);
        I(0x15c) = 1;
        T(0x68c) = 1;
        T(0x73c) = 0;
        break;
    case 41:
        fn_8006C748(p, 1, lbl_8035F0C0);
        VP(0x118)->s12f(lbl_8035F0C0);
        CT(((char *)sD10));
        CT(((char *)sD1C));
        T(0x68c) = 1;
        break;
    case 42:
        T(0x68c) = 1;
        break;
    case 43:
        I(0x274) = 0;
        gems(p);
        T(0x68c) = 1;
        CT(((char *)sD10));
        CT(lbl_8035F0D8);
        fn_8023F864(p, 6);
        fn_8023F864(p, 7);
        fn_8023F864(p, 8);
        fn_8023F864(p, 9);
        break;
    case 44:
        fn_80241628(p, 2, 0);
        fn_8006EC5C(p, 4);
        T(0x68c) = 1;
        T(0x240) = 0;
        break;
    case 45:
        tog(0);
        CT(((char *)sD10));
        break;
    case 46: {
        VO *o;
        fn_80241628(p, 0, 0);
        I(0x184) = 0;
        o = VP(0x180);
        if (o != 0) {
            o->send((void *)((char *)sD34), I(0x118), 0, 0, 0);
            I(0x180) = 0;
        }
        CT(((char *)sD10));
        break;
    }
    case 47:
        I(0x1fc) = 0;
        break;
    case 48:
        if (I(0x234) == 0) fn_8006BE6C(p);
        break;
    case 49:
        fn_8006BE6C(p);
        break;
    case 50:
        T(0x4c0) = 1;
        break;
    case 51:
        T(0x4c0) = 1;
        fn_80249008(p, 2);
        fn_802491DC(p, 2);
        break;
    case 52:
        fn_8006EB9C(p, 0x29, lbl_8035F0E0);
        break;
    case 53:
        VP(0x118)->s36();
        GV->go0();
        T(0x5e8) = 1;
        break;
    case 54:
        fn_8006FC88(p);
        break;
    case 55:
        fn_802494A4(p, 0);
        if (*(void **)(p + 0x240) != 0 && fn_800F6CD0(I(0x240), lbl_8035ED68) == 0) {
            CT(((char *)sD40));
            CT((const char *)I(0x240));
        }
        break;
    case 56:
        if (fn_800F6CD0(p + 0x178, lbl_8035F0E4) == 0) fn_802494A4(p, 0);
        break;
    case 57:
        fn_8006EC5C(p, 0x66);
        break;
    case 58:
        fn_802493D0(p, 0x22);
        fn_8006EC5C(p, 0x66);
        break;
    case 59:
        fn_8006B6F4(p);
        break;
    case 60:
        VP(0x118)->s36();
        GV->go0();
        break;
    case 61:
        if (fn_800F6CD0(p + 0x178, lbl_8035EE18) != 0) fn_802494A4(p, 0);
        break;
    case 62:
        fn_800739F8(I(0x118), lbl_8035F0C0);
        fn_802494A4(p, 7);
        I(0x164) = 0;
        break;
    case 63:
        if (I(0x164) != 0) {
            fn_800739F8(I(0x118), lbl_8035F0C0);
            I(0x164) = 0;
        }
        break;
    case 64:
        fn_800739F8(I(0x118), lbl_8035F0C0);
        fn_802494A4(p, 7);
        I(0x164) = 0;
        fn_8006EC5C(p, 1);
        break;
    case 65:
        fn_802494A4(p, 7);
        I(0x164) = 1;
        break;
    case 66:
        fn_802494A4(p, 7);
        I(0x164) = 0;
        break;
    case 67:
        fn_802494A4(p, 7);
        break;
    case 68:
        fn_802494A4(p, 7);
        I(0x164) = 0;
        break;
    case 69:
        fn_8006FD64(p);
        I(0x14c) = 1;
        break;
    case 70:
        fn_800716F0(p, -1);
        fn_80241628(p, 0, 0);
        fn_802494A4(p, 0x10);
        break;
    case 71:
        CT(((char *)sD4C));
        fn_80241628(p, 0, 0);
        break;
    case 72:
        fn_80241628(p, 0, 0);
        break;
    case 73:
        I(0x164) = 0;
        break;
    case 74:
        if (LIGHT != 1) fn_8006F3CC(p);
        fn_80249008(p, 2);
        break;
    case 75:
        if (LIGHT != 1) fn_8006F3CC(p);
        break;
    case 76:
        if (LIGHT != 1) fn_8006F3CC(p);
        fn_80242168(lbl_8035F0B8, p);
        break;
    case 77:
        if (fn_800F6CD0(p + 0x178, lbl_8035F0E4) != 0) fn_802494A4(p, 0);
        break;
    case 78:
        if (LIGHT != 1) fn_802494A4(p, 0x24);
        break;
    case 79:
        if (LIGHT != 1) fn_802494A4(p, 0x24);
        fn_80242168(lbl_8035F0B8, p);
        break;
    case 80:
        fn_8006C128(p);
        fn_80249008(p, 0xe);
        fn_802490E0(p, 0xd, PF(0x204));
        break;
    case 81:
        fn_80249008(p, 0xd);
        fn_802490E0(p, 0xe, PF(0x208));
        break;
    case 82:
        fn_8006BFE4(p);
        break;
    case 83:
        fn_802494A4(p, 0x25);
        break;
    case 84: {
        I(0x234) = 1;
        notify(p);
        fn_802494A4(p, 0x26);
        break;
    }
    case 85:
        PI(0x22c) &= ~0x800;
        fn_80249008(p, 0x10);
        if (*(void **)(I(0x22c) + 0x88) == 0) fn_8019B6B8(*(int *)(lbl_8035B65C + 0xc), I(0x22c));
        break;
    case 86:
        fn_802405B8(p);
        fn_80072D94(I(0x118), 1, PF(0x158));
        break;
    case 87:
        fn_802405B8(p);
        break;
    case 88:
        if (chk(p)) {
            fn_8006EB9C(p, 4, lbl_8035F0EC);
            fn_80249008(p, 2);
            fn_802491DC(p, 2);
        }
        break;
    case 89:
        if (chk(p)) fn_8006EB9C(p, 4, lbl_8035F0EC);
        break;
    case 90:
        if (chk(p)) {
            fn_8006EB9C(p, 4, lbl_8035F0EC);
            fn_80249008(p, 2);
            fn_802491DC(p, 2);
            fn_802494A4(p, 0);
        }
        break;
    case 91:
        if (chk(p)) fn_802494A4(p, 0);
        break;
    case 92:
        return;
    case 93: ld(p, 0x2a, 0x3c, lbl_8035F0F0, 1); break;
    case 94:
        fn_802494A4(p, 0);
        fn_80249008(p, 2);
        break;
    case 95: ld(p, 0x2a, 0x3c, lbl_8035F0F0, 0); break;
    case 96: ld(p, 0x2b, 0x3b, lbl_8035F0F0, 1); break;
    case 97: ld(p, 0x2b, 0x3b, lbl_8035F0F0, 0); break;
    case 98: ld(p, 0x2b, 0x3b, lbl_8035F0F0, 1); break;
    case 99: ld(p, 0x2b, 0x3b, lbl_8035F0F0, 0); break;
    case 100: ld(p, 0x23, 0x39, lbl_8035F0B4, 1); break;
    case 101: ld(p, 0x23, 0x39, lbl_8035F0B4, 0); break;
    case 102:
        fn_802494A4(p, 3);
        break;
    case 103: ld(p, 0x23, 0x39, lbl_8035F0B4, 0); break;
    case 104:
        return;
    case 105: ld(p, 0x2c, 0x3a, lbl_8035F0B4, 1); break;
    case 106: ld(p, 0x2c, 0x3a, lbl_8035F0B4, 0); break;
    case 107: ld(p, 0x2c, 0x3a, lbl_8035F0B4, 0); break;
    case 108: ld(p, 0x19, 0x38, lbl_8035F0B8, 1); break;
    case 109: ld(p, 0x19, 0x38, lbl_8035F0B8, 0); break;
    case 110:
        fn_802494A4(p, 4);
        break;
    case 111: ld(p, 0x19, 0x38, lbl_8035F0B8, 0); break;
    case 112: ld(p, 0x1a, 0x37, lbl_8035F0B8, 1); break;
    case 113:
        fn_802494A4(p, 0);
        fn_80249008(p, 2);
        break;
    case 114: ld(p, 0x1a, 0x37, lbl_8035F0B8, 0); break;
    case 115: ld(p, 0x1a, 0x37, lbl_8035F0B8, 0); break;
    case 116: ld(p, 0xe, 0x35, lbl_8035F0B8, 1); break;
    case 117: ld(p, 0xe, 0x35, lbl_8035F0B8, 0); break;
    case 118: ld(p, 0xe, 0x35, lbl_8035F0B8, 0); break;
    case 119: ld(p, 0xf, 0x36, lbl_8035F0B8, 1); break;
    case 120: ld(p, 0xf, 0x36, lbl_8035F0B8, 0); break;
    case 121: ld(p, 0xf, 0x36, lbl_8035F0B8, 0); break;
    case 122: lc(p, 0x32, lbl_8035F0B8, 1); break;
    case 123: lc(p, 0x32, lbl_8035F0B8, 0); break;
    case 124: lc(p, 0x33, lbl_8035F0B8, 1); break;
    case 125: lc(p, 0x33, lbl_8035F0B8, 0); break;
    case 126: lc(p, 0x31, lbl_8035F0B8, 1); break;
    case 127: lc(p, 0x31, lbl_8035F0B8, 0); break;
    case 128: lc(p, 0x34, lbl_8035F0B8, 1); break;
    case 129: lc(p, 0x34, lbl_8035F0B8, 0); break;
    case 130:
        fn_80240384(p);
        break;
    case 131:
        fn_8006F26C(p);
        break;
    case 132:
        if (fn_800F6CD0(p + 0x178, lbl_8035F0E4) != 0) fn_8006F26C(p);
        break;
    case 133:
        fn_8006F1DC(p);
        break;
    case 134:
        if (fn_800F6CD0(p + 0x178, lbl_8035F0E4) != 0) fn_8006F1DC(p);
        break;
    case 135:
        fn_8006F2FC(p);
        break;
    case 136:
        if (fn_800F6CD0(p + 0x178, lbl_8035F0E4) != 0) fn_8006F2FC(p);
        break;
    case 137:
        fn_8007225C(I(0x118), PF(0x1e8));
        fn_802494A4(p, 10);
        break;
    case 138:
        fn_802494A4(p, 0x21);
        break;
    case 139:
        fn_8006EC5C(p, 0x45);
        break;
    case 140:
        fn_802494A4(p, 0x28);
        break;
    case 141:
        fn_8006EC5C(p, 99);
        break;
    case 142:
        fn_802494A4(p, 0xb);
        break;
    case 143:
        fn_8006DB6C(p);
        break;
    case 144:
        fn_8006EC5C(p, 0x67);
        fn_802494A4(p, 0x23);
        break;
    case 145:
        fn_802494A4(p, 0x13);
        break;
    case 146:
        return;
    case 147:
        fn_802494A4(p, 0xc);
        fn_8006DC14(p);
        break;
    case 148:
        I(0x150) = 1;
        break;
    case 149:
        fn_8007225C(I(0x118), *(f32 *)(I(0xe4) + 0x1a8) * PF(500));
        break;
    case 150:
        fn_80253250(*(int *)(lbl_8035B5E4 + 0x70) + *(int *)(lbl_8035B5E4 + 0x68) * 0x34);
        break;
    case 151:
        fn_8006B5A4(I(0x118));
        fn_8006EAD0(p, 0x17, 1, lbl_8035F0C0);
        fn_802494A4(p, 0);
        break;
    case 152:
        I(0x15c) = 1;
        break;
    case 153:
        fn_802494A4(p, 0x12);
        break;
    case 154:
        fn_8006EC5C(p, 4);
        break;
    case 155:
        fn_802494A4(p, 0x11);
        break;
    case 156:
        if (PF(0xec) < F(0x174)) {
            I(0x180) = I(0xe4);
            F(0x174) = PF(0xec);
            fn_800F6E88(p + 0x178, I(0xf0));
        }
        break;
    case 157:
        fn_802490E0(p, 0xb, PF(0x144));
        break;
    case 158:
        fn_8006ED08(p);
        break;
    case 159:
        fn_8006E2F8(p);
        break;
    case 160:
        fn_802494A4(p, 0);
        fn_8006E2F8(p);
        break;
    case 161:
        if (T(0x4cc) != 0) fn_8006ED08(p);
        break;
    case 162:
        fn_8006DD74(p);
        break;
    case 163: {
        int o = I(0x118);
        *(int *)(o + 0x6c4) = 1;
        if (*(int *)(o + 0x6cc) != 0) *(int *)(o + 0x6c8) = 1;
        break;
    }
    case 164:
        T(0x6c4) = 0;
        break;
    case 165:
        fn_8006C418(p);
        break;
    case 166:
        fn_8006F808(p);
        break;
    case 167:
        return;
    case 168: fn_8006CD00(p, 0, 0, 0); break;
    case 169: fn_8006CD00(p, 0, 0, 1); break;
    case 170: fn_8006CD00(p, 1, 1, 0); break;
    case 171: fn_8006CD00(p, 1, 1, 1); break;
    case 172: fn_8006CD00(p, 1, 2, 0); break;
    case 173: fn_8006CD00(p, 1, 2, 1); break;
    case 174: fn_8006CD00(p, 0, 1, 0); break;
    case 175: fn_8006CD00(p, 0, 1, 1); break;
    case 176:
        I(0x1ec) = 1;
        T(0x5e8) = 0;
        break;
    case 177:
        I(0x1ec) = 1;
        T(0x5e8) = 0;
        break;
    case 178:
        if (I(0x1ec) == 0) {
            I(0x1ec) = 1;
            T(0x5e8) = 0;
        } else {
            I(0x1ec) = 0;
            T(0x5e8) = 1;
        }
        break;
    case 179:
        if (*(void **)(p + 0xec) != 0 && PI(0xec) == 0) {
            I(0x1ec) = 0;
            T(0x5e8) = 1;
        }
        break;
    case 180:
        fn_8006EC5C(p, 4);
        fn_802494A4(p, 0);
        break;
    case 181: path(p, lbl_8035F0D0); break;
    case 182: path(p, lbl_8035F0F4); break;
    case 183: path(p, lbl_8035F0FC); break;
    case 184: path(p, lbl_8035F104); break;
    case 185: path(p, lbl_8035F10C); break;
    case 186: path(p, lbl_8035F114); break;
    case 187: path(p, lbl_8035F11C); break;
    case 188: path(p, lbl_8035F124); break;
    case 189: path(p, lbl_8035F12C); break;
    case 190: path(p, lbl_8035F134); break;
    case 191: path(p, lbl_8035F13C); break;
    case 192: path(p, lbl_8035F144); break;
    case 193: path(p, lbl_8035F14C); break;
    case 194: path(p, lbl_8035F154); break;
    case 195: path(p, lbl_8035F15C); break;
    case 196: path(p, lbl_8035F164); break;
    case 197: path(p, lbl_8035F16C); break;
    case 198: path(p, lbl_8035F174); break;
    case 199: path(p, lbl_8035F17C); break;
    case 200: path(p, lbl_8035F184); break;
    case 201: path(p, lbl_8035F18C); break;
    case 202: path(p, lbl_8035F194); break;
    case 203: path(p, lbl_8035F19C); break;
    case 204: path(p, lbl_8035F1A4); break;
    case 205: path(p, lbl_8035F1AC); break;
    case 206: path(p, lbl_8035F1B4); break;
    case 207:
        if (*(void **)(p + 0xf0) != 0 && *(int *)(T(600) + 0x300) == 0) fn_802410CC(p, I(0xf0), 0);
        break;
    case 208:
        if (*(void **)(p + 0xf0) != 0 && *(int *)(T(600) + 0x300) == 0) fn_80241028(p, I(0xf0), 0);
        break;
    case 209:
        if (*(void **)(p + 0xf0) != 0) fn_802413D8(p, I(0xf0), lbl_8035F1BC, 0, 1, I(0xec));
        break;
    case 210:
        fn_800716F0(p, 0);
        break;
    case 211:
        fn_800716F0(p, 1);
        break;
    case 212:
        fn_8007249C(I(0x118), 1);
        break;
    case 213:
        fn_8007249C(I(0x118), 0);
        fn_8007115C(p);
        break;
    case 214:
        fn_80076DFC(I(0x118), I(0xe4));
        break;
    case 215:
        fn_802494A4(p, 0x22);
        break;
    case 216:
        if (*(void **)(p + 0xf0) != 0) fn_802413D8(p, I(0xf0), lbl_8035F1BC, 0, 1, I(0xec));
        { int e = I(0xe0);
        *(f32 *)(e + 0x118) = F(0x1ac);
        *(f32 *)(e + 0x11c) = F(0x1b0);
        *(f32 *)(e + 0x120) = F(0x1b4);
        *(f32 *)(e + 0x154) = lbl_8035F0C0; }
        fn_802494A4(p, 0x1e);
        break;
    case 217:
        fn_802494A4(p, 0x1d);
        break;
    case 218:
        fn_802494A4(p, 0x1f);
        break;
    case 219:
        shot(p, ((char *)sD58));
        break;
    case 220:
        shot(p, lbl_8035F1CC);
        break;
    case 221: {
        u8 buf[8];
        fn_8002FD10(lbl_8035B684, buf);
        GV->go(buf);
        fn_80072BA8(I(0x118));
        fn_802494A4(p, 0);
        break;
    }
    case 222:
        fn_802494A4(p, 0x27);
        break;
    case 223:
        VP(0x180)->send(lbl_8035F1D4, I(0x118), 0, 0, 0);
        break;
    case 224:
        I(600) = 1;
        break;
    case 225:
        I(600) = 0;
        break;
    case 226:
        I(0x25c) = 1;
        break;
    case 227:
        I(0x25c) = 0;
        break;
    case 228:
        fn_802494A4(p, 0x1b);
        break;
    case 229:
        gems(p);
        break;
    case 230:
        fn_80071EE0(I(0x118));
        break;
    case 231:
        fn_80071E68(I(0x118));
        break;
    case 232: fn_80072438(I(0x118), 2); break;
    case 233: fn_80072438(I(0x118), 4); break;
    case 234: fn_80072438(I(0x118), 8); break;
    case 235: fn_80072438(I(0x118), 0x10); break;
    case 236: fn_80072438(I(0x118), 0x20); break;
    case 237: fn_80072438(I(0x118), 0x40); break;
    case 238:
        fn_80072040(I(0x118), I(0xf0));
        break;
    case 239:
        fn_80071F54(I(0x118), I(0xf0), PF(0xec));
        break;
    case 240:
        GV->go(lbl_8035EEA8);
    case 241:
        break;
    }
}
}

} /* extern "C" */
#undef GV
#undef I
#undef F
#undef PF
#undef PI
#undef VP
#undef T
#undef CT
#undef LIGHT
#undef walk
#undef ld
#undef lc
} // namespace n800690FC

extern "C" {
// .sdata2 8035F1E8-8035F208, between the two int->float constants (the unit owns 8035F1E0-8035F210): defined here
// so that they are emitted after the first constant (fn_800690FC) and before the second (fn_8006B908).
__declspec(section ".sdata2") char lbl_8035F1E8[8] = "Enemy";
__declspec(section ".sdata2") char lbl_8035F1F0[8] = "BONUS";
__declspec(section ".sdata2") char lbl_8035F1F8[8] = "SPAWN";
__declspec(section ".sdata2") u32 lbl_8035F200 = 0x2B;
}

namespace n8006B5A4 {

extern "C" {

struct V5A { f32 x, y, z; };
struct B5A {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void Place(V5A *, f32 *, f32 *, f32 *, int);
};
extern void *lbl_8035B65C;
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F1C8;
extern f32 lbl_8035F1BC;
void __ct__9C80253F24Fiiii(void *, char *, int, int, int);
#define F(o) (*(f32 *)(p + (o)))
#define I(o) (*(s32 *)(p + (o)))
void fn_8006B5A4(u8 *p) {
    V5A v;
    __ct__9C80253F24Fiiii(lbl_8035B65C, ((char *)sD64), 0, 0, 0);
    I(0x5b0) = 0;
    F(0x5b4) = lbl_8035F0C0; F(0x5b8) = lbl_8035F0C0; F(0x5bc) = lbl_8035F0C0;
    F(0x5c0) = lbl_8035F0C0; F(0x5c4) = lbl_8035F0C0; F(0x5c8) = lbl_8035F0C0;
    F(0x5cc) = lbl_8035F1C8;
    F(0x5d0) = lbl_8035F0C0; F(0x5d4) = lbl_8035F0C0; F(0x5d8) = lbl_8035F0C0;
    I(0x338) = 0; I(0x5dc) = 0; I(0x5e0) = 0;
    F(0x500) = lbl_8035F0C0; F(0x504) = lbl_8035F0C0;
    *(volatile f32 *)&v.x = *(volatile f32 *)&F(0x57c);
    *(volatile f32 *)&v.y = *(volatile f32 *)&F(0x580);
    f32 z = *(volatile f32 *)&F(0x584);
    *(volatile f32 *)&v.z = z;
    v.z = z + *(volatile f32 *)&lbl_8035F1BC;
    ((B5A *)p)->Place(&v, &F(0x588), &F(0x594), &F(0x5a0), 0);
    F(0x118) = lbl_8035F0C0; F(0x11c) = lbl_8035F0C0; F(0x120) = lbl_8035F0C0;
    F(0x154) = lbl_8035F0C0;
}

} /* extern "C" */
#undef F
#undef I
} // namespace n8006B5A4

namespace n8006B6C8 {

extern "C" {

void fn_8006B6C8(u8 *p) {
    *(f32 *)(p + 0x1AC) = *(f32 *)(p + 0x1A8);
    **(s32 **)(p + 0x544) = (s32)*(f32 *)(p + 0x1AC);
}

} /* extern "C" */
} // namespace n8006B6C8

namespace n8006B6F4 {

extern "C" {

extern "C" int rand(void);
struct T { u8 pad[220]; int f220; u8 pad224[56]; void *f280; u8 pad284[380]; int f664; };
int fn_800724A4(void *);
void fn_8007115C(T *);
void fn_80241588(T *, int, int, f32);
extern f32 lbl_8035F1BC;
static inline void Set(T *p, int id) {
    if (p->f220 == 14 && !fn_800724A4(p->f280)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}
void fn_8006B6F4(T *t) {
    switch (t->f220) {
    case 29:
        break;
    case 4:
        t->f664++;
        if (t->f664 > 5) {
            t->f664 = 0;
            switch ((int)((u32)rand() % 5)) {
            case 0: Set(t, 110); break;
            case 1: Set(t, 6); break;
            case 2: Set(t, 88); break;
            case 3: Set(t, 97); break;
            case 4: Set(t, 89); break;
            }
        }
        break;
    default:
        Set(t, 4);
        t->f664 = 0;
        break;
    }
}

} /* extern "C" */
} // namespace n8006B6F4

namespace n8006B908 {

extern "C" {

struct V9 { f32 x, y, z; };
struct E9 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void Set(void *, int, int, int, int);
};
struct Q9 { u8 pad[0x10]; void *f10; u8 pad14[0x20 - 0x14]; u32 f20; };
struct O9 { u8 pad[0x30]; Q9 *f30; };
struct P9 {
    u8 pad[0xe0]; E9 *fe0; u8 pade4[0xec - 0xe4]; s32 *fec;
    u8 padf0[0x110 - 0xf0]; O9 **f110; u8 pad114[0x118 - 0x114]; void *f118;
    u8 pad11c[0x260 - 0x11c]; f32 *f260; u8 pad264[4]; s32 f268; f32 f26c; f32 f270;
    u8 pad274[0x288 - 0x274]; u8 f288[4];
};
struct T9 { void *a, *b, *c; void (*fn)(void *, V9 *); };
extern T9 lbl_803286D0;
extern f32 lbl_8035F0C0;
extern u32 lbl_8035F200;
void fn_80072AC8(void *, V9 *);
void fn_8023F9C8(P9 *, s32);
void fn_80190C98(O9 *);
void fn_8006B908(P9 *p) {
    V9 v;
    Q9 *q; u32 i; O9 *o;
    p->f268 = *p->fec;
    p->f26c = *p->f260 / (f32)p->f268;
    p->f270 = lbl_8035F0C0;
    p->fe0->Set(p->f288, 0, 0, 0, 0);
    fn_80072AC8(p->f118, &v);
    for (i = 6; i <= 9; i++) {
        fn_8023F9C8(p, i);
        o = p->f110[i];
        if (o && (q = o->f30)) {
            lbl_803286D0.fn(q->f10, &v);
            q->f20 |= lbl_8035F200;
            fn_80190C98(o);
        }
    }
}

} /* extern "C" */
} // namespace n8006B908

namespace n8006BA1C {

extern "C" {

extern void *lbl_8035B65C;
extern f32 lbl_8035F210;
extern f32 lbl_8035F214;
void __ct__9C80253F24Fiiii(void *, void *, s32, s32, s32);
void fn_80076D50(void *, s32);
s32 fn_800724A4(void *);
void fn_8007115C(void *);
void fn_80241588(void *, s32, void *, f32);
void fn_80242174(void *, f32);

void fn_8006BA1C(u8 *p) {
    *(s32 *)(p + 0x1EC) = 0;
    __ct__9C80253F24Fiiii(lbl_8035B65C, ((u8 *)sCF8), 0, 0, 0);
    fn_80076D50(*(void **)(p + 0x118), 0);
    *(s32 *)(*(u8 **)(p + 0x118) + 0x4C8) = 0;
    *(s32 *)(*(u8 **)(p + 0x118) + 0x73C) = 1;
    if (**(s32 **)(*(u8 **)(p + 0x118) + 0x540) <= 0) {
        if (*(s32 *)(p + 0xDC) == 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
            fn_8007115C(p);
        }
        fn_80241588(p, 106, 0, lbl_8035F210);
    } else {
        if (*(s32 *)(p + 0xDC) == 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
            fn_8007115C(p);
        }
        fn_80241588(p, 39, 0, lbl_8035F210);
        fn_80242174(p, lbl_8035F214);
    }
    *(s32 *)(*(u8 **)(p + 0x118) + 0x68C) = 0;
}

} /* extern "C" */
} // namespace n8006BA1C

namespace n8006BB24 {

extern "C" {

}
struct V3 { f32 x, y, z; };
struct H { u8 pad[16]; void *h; u8 pad2[12]; u32 f32; };
struct A { u8 pad[48]; H *f48; u8 pad2[52];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void f(f32);
    u8 pad3[12]; void *f120; };
struct B36 { u8 pad[36]; void *f36; };
struct B168 { u8 pad[168]; B36 *f168; };
struct B { u8 pad[156]; B168 *f156; };
struct Tb { u8 pad[12]; void (*f12)(void *, V3 *); u8 pad2[12]; void (*f28)(void *, V3 *, V3 *, V3 *); };
struct L12 { u8 pad[12]; u32 *f12; };
struct T { u8 pad[280]; void *f280; u8 pad2[240]; L12 *f524; u8 pad3[20]; A **f548; B **f552; u8 pad4[12]; f32 *f568; };
extern "C" {
extern Tb lbl_803286D0;
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F1C8;
extern f64 lbl_8035F220;
extern f32 lbl_8035F228;
extern f32 lbl_8035F210;
extern u32 lbl_8035F200;
void fn_80107244(void *, V3 *);
void fn_80072AC8(void *, V3 *);
void fn_80101820(V3 *);
f32 fn_80101590(V3 *, V3 *);
int rand(void);
void fn_80190C98(A *);
void fn_80107F3C(void *, V3 *);
u32 fn_8007239C(void *);
static inline void cross(V3 &r, const V3 &a, const V3 &b) {
    r.x = a.y * b.z - a.z * b.y;
    r.y = a.z * b.x - a.x * b.z;
    r.z = a.x * b.y - a.y * b.x;
}
static inline f32 rnd() { s32 i = rand() % 3000u; f32 r = lbl_8035F228 * (f32)i; r = lbl_8035F210 + r; return r; }
void fn_8006BB24(T *t, f32 dt) {
    u32 i;
    for (i = 0; i < t->f524->f12[(u32)(fn_8007239C(t->f280) - 1)]; i++) {
        V3 p, q, r, u, d, s, w;
        A *a = t->f548[i];
        B *b;
        f32 sc, r1, k;
        H *h;
        if (a == 0) continue;
        b = t->f552[i];
        if (b == 0) continue;
        fn_80107244(b->f156->f168->f36, &p);
        fn_80072AC8(t->f280, &q);
        d.x = q.x - p.x; d.y = q.y - p.y; d.z = q.z - p.z;
        fn_80101820(&d);
        {
            f32 dz, dy, dx, o, ux, uy;
            ux = *(f32 *)&lbl_8035F0C0;
            uy = lbl_8035F0C0;
            dy = d.y;
            *(volatile f32 *)&u.x = ux;
            dz = d.z;
            *(volatile f32 *)&u.y = uy;
            dx = *(volatile f32 *)&d.x;
            o = *(f32 *)&lbl_8035F1C8;
            u.z = o;
            r.x = dy * o - dz * uy;
            r.y = dz * ux - dx * o;
            r.z = dx * uy - dy * ux;
        }
        fn_80101820(&r);
        cross(u, r, d);
        fn_80101820(&u);
        sc = fn_80101590(&p, &q) / (lbl_8035F220 * *t->f568);
        r1 = rnd();
        {
            f32 r2 = rnd();
            s.y = r1;
            s.z = sc;
            s.x = r2;
        }
        k = -*t->f568 * sc;
        w.x = k * d.x + q.x; w.y = k * d.y + q.y; w.z = k * d.z + q.z;
        h = a->f48;
        if (h) { lbl_803286D0.f12(h->h, &w); h->f32 |= lbl_8035F200; fn_80190C98(a); }
        h = a->f48;
        if (h) { lbl_803286D0.f28(h->h, &r, &u, &d); h->f32 |= lbl_8035F200; fn_80190C98(a); }
        if (a->f120) fn_80107F3C(a->f120, &s);
        a->f(dt);
    }
}

} /* extern "C" */
} // namespace n8006BB24

namespace n8006BE6C {

extern "C" {

/* QV=2.0p1 */
extern const char lbl_8035EEA0[7];
extern u8 *lbl_8035B65C;
s32 fn_8007239C(void *);
void fn_800746A4(void *, void *);
void fn_8019B6B8(void *, void *);
} /* extern "C" */

struct O8006BE6C {
    u8 pad[140 - 8];
    virtual void v0();
};

struct V8006BE6C {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33(const char *, s32, s32, s32, s32);
};

struct Q8006BE6C {
    u32 f0;
    u8 pad[132];
    u32 f136;
};

struct T8006BE6C {
    u8 pad[12];
    u32 *f12;
};

struct C8006BE6C {
    u8 pad[224];
    void *f224;
    u8 pad2[52];
    void *f280;
    u8 pad3[240];
    T8006BE6C *f524;
    u8 pad4[20];
    Q8006BE6C **f548;
    V8006BE6C **f552;
    u8 pad5[4];
    u32 f560;
    u8 pad6[16];
    u8 f580[16];
    s32 f596;
};

static inline s32 Cur(C8006BE6C *p) {
    return fn_8007239C(p->f280) - 1;
}
static inline u32 Count(C8006BE6C *p) {
    return p->f524->f12[Cur(p)];
}

static inline void Remove(C8006BE6C *p, V8006BE6C *cur) {
    s32 found;
    u32 j;
    Q8006BE6C *q;

    found = -1;
    for (j = 0; j < Count(p); j++) {
        if (p->f552[j] == cur) {
            found = j;
            j = Count(p);
            p->f552[j] = 0;
        }
    }
    q = p->f548[found];
    if (q != 0) {
        q->f0 &= ~0x800;
        if (q->f136 == 0) {
            fn_8019B6B8(*(void **)(lbl_8035B65C + 12), q);
        }
    }
}

extern "C" {

void fn_8006BE6C(C8006BE6C *p) {
    u32 i;

    if (p->f596 != 0) {
        fn_800746A4(p->f224, p->f580);
    }
    for (i = 0; i < Count(p); i++) {
        if (p->f552[i] != 0) {
            p->f552[i]->v33(lbl_8035EEA0, 0, 0, 0, 0);
            Remove(p, p->f552[i]);
            p->f552[i] = 0;
        }
    }
    p->f560 = 0;
}

} /* extern "C" */
} // namespace n8006BE6C

namespace n8006BFE4 {

extern "C" {

/* QV=2.0p1 */
typedef struct Vec8006BFE4 {
    f32 x, y, z;
} Vec8006BFE4;
} /* extern "C" */
struct V8006BFE4 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13(Vec8006BFE4 *, Vec8006BFE4 *, Vec8006BFE4 *, void *, void *);
};
extern "C" {
typedef struct S8006BFE4 {
    u8 pad[224];
    V8006BFE4 *f224;
    V8006BFE4 *f228;
    u8 pad2[48];
    void *f280;
    u8 pad3[88];
    f32 f372;
    u8 pad4[8];
    V8006BFE4 *f384;
    u8 pad5[148];
    f32 *f536;
} S8006BFE4;
extern f32 lbl_8035F0C0;
extern volatile f64 lbl_8035F230;
extern f32 lbl_8035F238;
extern f32 lbl_8035F23C;
extern f32 lbl_8035F240;
void fn_80072AC8(void *, Vec8006BFE4 *);
f32 fn_80101590(Vec8006BFE4 *, Vec8006BFE4 *);
f64 fn_800F045C(f64);

static inline f32 sacos(f32 x) {
    if ((f32)__fabs(x) <= lbl_8035F230) return (f32)fn_800F045C(x);
    if (x > lbl_8035F0C0) return lbl_8035F0C0;
    return lbl_8035F238;
}

void fn_8006BFE4(S8006BFE4 *p) {
    Vec8006BFE4 v32;
    Vec8006BFE4 v20;
    Vec8006BFE4 v8;
    Vec8006BFE4 d;
    f32 dist;
    f32 ang;
    fn_80072AC8(p->f280, &v32);
    p->f228->v13(&v20, 0, 0, 0, 0);
    dist = fn_80101590(&v32, &v20);
    if (dist < p->f372) {
        p->f224->v13(0, &v8, 0, 0, 0);
        d.z = lbl_8035F0C0;
        *(volatile f32 *)&v8.z = d.z;
        d.x = v20.x - v32.x;
        d.y = v20.y - v32.y;
        ang = sacos(v8.x * d.x + v8.y * d.y + d.z * d.z);
        if (ang < lbl_8035F23C * (*p->f536 * lbl_8035F240)) {
            p->f372 = dist;
            p->f384 = p->f228;
        }
    }
}

} /* extern "C" */
} // namespace n8006BFE4

namespace n8006C128 {
extern "C" {
}
struct V4 { f32 a, b, c, d; };
struct Vo { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31(); virtual void v32(); virtual void play(const char *, s32, s32, s32, s32); };
struct Y { u32 f0; f32 f4; u8 pad[40]; u32 f48; };
struct Z { u8 pad[8]; Y *y; };
struct Sh { u8 pad[4]; f32 len; u8 pad2[44]; u16 n; };
struct M { u8 pad[16]; Sh *sh; };
struct M2 { u32 f0; f32 f4; };
struct E { u32 f0; u8 pad[128]; Z *z; u32 f136; u8 pad2[176 - 140]; M *m; };
struct Tb { u8 pad[12]; u32 *u; };
struct Tf { u8 pad[12]; f32 *f; };
struct G { u8 pad[12]; void *f12; };
struct O { u8 pad[224]; void *f224; u8 pad2[280 - 228]; void *f280; u8 pad3[372 - 284]; f32 f372; u8 pad4[384 - 376]; Vo *f384; u8 pad5[496 - 388]; Vo *f496; u8 pad6[512 - 500]; u32 cnt; u8 pad7[524 - 516]; Tb *f524; Tf *f528; u8 pad8[548 - 532]; E **f548; Vo **f552; E *f556; u8 pad9[580 - 560]; u8 f580[16]; s32 f596; };
extern "C" {
extern G *lbl_8035B65C;
extern char lbl_8035F248[4];
extern char lbl_8035EE98[4];
extern u32 lbl_8035F218;
extern f32 lbl_8035F0C0; extern volatile f32 lbl_8035F244, lbl_8035F1C8;
u32 fn_8007239C(void *p);
void __ct__9C80253F24Fiiii(G *, const char *, void *, s32, s32);
void fn_8019B7E8(void *, E *);
void fn_80074660(void *, void *);
void fn_800746A4(void *, V4 *);
void fn_802490E0(O *, s32, f32);

static inline Y *getY(Z *z) { if (z == 0) return 0; else return z->y; }


static inline u32 mx(O *o) { u32 i = fn_8007239C(o->f280) - 1; return o->f524->u[i]; }
static inline f32 tm(O *o) { u32 i = fn_8007239C(o->f280); Tf *t = o->f528; i--; return t->f[i]; }
s32 fn_8006C128(O *o) {
    s32 r = 0;
    if (o->cnt < mx(o)) {
        o->f372 = tm(o);
        o->f384 = 0;
        __ct__9C80253F24Fiiii(lbl_8035B65C, ((char *)sD98), o->f224, 0, 0);
        if (o->f384) {
            E *e;
            o->f552[o->cnt] = o->f384;
            e = o->f548[o->cnt];
            e->f0 |= lbl_8035F218;
            if (!e->f136) fn_8019B7E8(lbl_8035B65C->f12, e);
            {
                Z *z = e->z;
                if (getY(z)) {
                    Y *y = getY(z);
                    if (y->f48 & 1) {
                        y->f4 = lbl_8035F0C0;
                        y->f0 &= ~0x18;
                    }
                }
            }
            if (o->cnt == 0) {
                if (!o->f596) { o->f596 = 1; fn_80074660(o->f224, o->f580); }
                { V4 c; void *q = o->f224; *(volatile f32 *)&c.a = lbl_8035F0C0; *(volatile f32 *)&c.b = lbl_8035F244; *(volatile f32 *)&c.c = lbl_8035F0C0; *(volatile f32 *)&c.d = lbl_8035F1C8; fn_800746A4(q, &c); }
            }
            o->f496->play(lbl_8035F248, 0, 0, 0, 0);
            o->f552[o->cnt]->play(lbl_8035EE98, 0, 0, 0, 0);
            o->cnt++;
            r = 1;
        }
    }
    if (!r) {
        f32 v;
        o->f556->f0 |= lbl_8035F218;
        ((M2 *)o->f556->m)->f4 = lbl_8035F0C0;
        v = (f32)o->f556->m->sh->n / o->f556->m->sh->len;
        if (!o->f556->f136) fn_8019B7E8(lbl_8035B65C->f12, o->f556);
        fn_802490E0(o, 16, v);
    }
    return r;
}

}
} // namespace n8006C128

namespace n8006C3CC {

extern "C" {

extern f32 lbl_8035F1C8;
extern u8 *lbl_8035B488;
void fn_800746A4(void *, void *);

void fn_8006C3CC(u8 *p) {
    *(f32 *)(lbl_8035B488 + 0x27EC) = lbl_8035F1C8;
    if (*(void **)(p + 0xE0) != NULL && *(s32 *)(p + 0x254) != 0) {
        fn_800746A4(*(void **)(p + 0xE0), p + 0x244);
    }
}

} /* extern "C" */
} // namespace n8006C3CC

namespace n8006C418 {
extern "C" {
}
struct V3 { f32 x, y, z; };
struct O { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void get(V3 *, int, V3 *, V3 *, int); virtual void put(V3 *, V3 *, V3 *, V3 *, int); };
struct O11 { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void f(); };
struct H48 { u8 pad[16]; void *h; };
struct Res { u8 pad[48]; H48 *f48; };
struct X { u8 pad[280]; V3 a; u8 pad2[48]; f32 f340; u8 pad3[1112]; Res *f1456; f32 m[7]; };
struct Tb { u8 pad[304]; void (*f304)(void *, V3 *); void (*f308)(void *, V3 *, V3 *, V3 *); };
struct D { u8 pad[4]; O11 *o; };
struct G { u8 pad[8]; u8 *db; };
struct T { u8 pad[192]; D *f192; u8 pad2[20]; s32 f216; u8 pad3[4]; X *f224; u8 pad4[8]; void *f236; u8 pad5[40]; O *f280; u8 pad6[144]; V3 f428; };
extern "C" {
extern f32 lbl_8035F0C0;
extern void *volatile lbl_8035B308;
extern G *lbl_8035B460;
extern Tb lbl_803286D0;
extern s32 lbl_8035B6E8;
O *fn_802288FC(void *, void *);
Res *fn_800F9398(void *, void *);
void fn_80107244(H48 *, f32 *);
void fn_801075B8(H48 *, f32 *);
static inline void negcross(V3 &v, V3 &u, V3 &c) {
    v.x = -v.x; v.y = -v.y; v.z = -v.z;
    c.x = v.y * u.z - v.z * u.y; c.y = v.z * u.x - v.x * u.z; c.z = v.x * u.y - v.y * u.x;
}
struct PQ { V3 p; f32 q[4]; };
void fn_8006C418(T *t) {
    V3 pos, v, u, c;
    f32 mq[4];
    V3 mp;
    Res *key = (Res *)t->f236;
    X *x;
    Res *r;
    O *o;
    { f32 k = lbl_8035F0C0; *(volatile f32 *)&v.x = k; *(volatile f32 *)&v.y = k; *(volatile f32 *)&v.z = k; }
    o = fn_802288FC(lbl_8035B308, key);
    r = 0;
    if (o) {
        o->get(&pos, 0, &u, &v, 0);
        negcross(v, u, c);
    } else {
        key = fn_800F9398(lbl_8035B460->db + 144, key);
        r = key;
        if (key) {
            Res *q = key;
            if (q->f48) lbl_803286D0.f304(q->f48->h, &pos);
            else pos.z = pos.y = pos.x = lbl_8035F0C0;
            if (q->f48) lbl_803286D0.f308(q->f48->h, &v, &c, &u);
            negcross(v, u, c);
        }
    }
    if (o == 0 && r == 0) return;
    {
        X *x = t->f224;
        x->a = t->f428;
        x->f340 = lbl_8035F0C0;
    }
    t->f280->put(&pos, &v, &u, &c, 0);
    lbl_8035B6E8 = 1;
    if (t->f216 == 1) {
        {
        x = (X *)t->f280;
        x->f1456 = 0;
        if (x->f1456) {
            mq[3] = mq[2] = mq[1] = mq[0] = mp.z = mp.y = mp.x = lbl_8035F0C0;
            if (x->f1456->f48) fn_80107244(x->f1456->f48, &mp.x);
            else mp.z = mp.y = mp.x = lbl_8035F0C0;
            if (x->f1456->f48) fn_801075B8(x->f1456->f48, mq);
            x->m[0] = mp.x; x->m[1] = mp.y; x->m[2] = mp.z; x->m[3] = mq[0];
            x->m[4] = mq[1]; x->m[5] = mq[2]; x->m[6] = mq[3];
        }
        }
        { X *x = (X *)t->f280; x->m[0] = pos.x; x->m[1] = pos.y; x->m[2] = pos.z; }
        t->f192->o->f();
    }
}

}
} // namespace n8006C418

namespace n8006C748 {

extern "C" {

struct V6C { f32 x; f32 y; f32 z; };
struct M6C { u8 pad[0x28]; f32 f28; f32 f2c; f32 f30; };
struct HB6C { u32 f0; u8 pad4[0x20]; f32 f24; u8 pad28[0x68 - 0x28]; };
struct H6C : HB6C {
    virtual void v0(); virtual void v1(); virtual void Update();
    u8 pad6c[0x78 - 0x6c]; M6C *f78;
};
struct G6C {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void GetPos(V6C *, s32, s32, s32, s32);
    virtual void SetPos(V6C *, s32, s32, s32, s32);
    u8 pad4[0x9c - 4]; H6C *f9c;
};
struct O6C { u8 pad[0x428]; H6C *f428; u8 pad42c[0x6dc - 0x42c]; f32 f6dc; f32 f6e0; f32 f6e4; u8 pad6e8[0xc]; f32 f6f4; f32 f6f8; f32 f6fc; };
struct P6C { u8 pad[0xe0]; G6C *fe0; u8 pade4[0x118 - 0xe4]; O6C *f118; u8 pad11c[0x19c - 0x11c]; f32 *f19c; f32 *f1a0; f32 *f1a4; s32 f1a8; u8 pad1ac[0x1c4 - 0x1ac]; s32 f1c4; s32 f1c8; s32 f1cc; V6C v1d0; V6C v1dc; };
void fn_80107F3C(M6C *, V6C *);
void fn_80241140(P6C *, s32);
void fn_802494A4(P6C *, s32);
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F1C8;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;

inline f32 Sqrt6C(f32 x) {
    if (x > lbl_8035F0C0) {
        const f64 _half = lbl_8035F250;
        const f64 _three = lbl_8035F258;
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

inline f32 MagF6C(f32 x, f32 y, f32 z) {
    return Sqrt6C(__fmadds(z, z, __fmadds(x, x, y * y)));
}

inline f32 Mag6C(V6C *v) {
    f32 x = v->x, y = v->y, z = v->z;
    f32 xx = x * x, yy = y * y, zz = z * z;
    return Sqrt6C(xx + yy + zz);
}

inline f32 MagB6C(V6C *v) {
    return Sqrt6C(v->x * v->x + v->y * v->y + v->z * v->z);
}

inline void Apply6C(P6C *p, V6C t) {
    M6C *m2 = p->fe0->f9c->f78;
    if (m2) fn_80107F3C(m2, &t);
    {
        V6C u;
        O6C *o = p->f118;
        f32 rz = o->f6e4 / o->f6fc;
        f32 ry = o->f6e0 / o->f6f8;
        f32 rx = o->f6dc / o->f6f4;
        u.x = t.x / rx;
        u.y = t.y / ry;
        u.z = t.z / rz;
        if (o->f428->f78) fn_80107F3C(o->f428->f78, &u);
    }
}

void fn_8006C748(P6C *p, f32 dt, s32 b) {
    V6C s;
    f32 dy;
    f32 dx;
    f32 dz;
    f32 k;
    f32 y0;
    H6C *h = p->fe0->f9c;
    M6C *m = h->f78;
    if (m) {
        s.x = m->f28;
        s.y = m->f2c;
        s.z = m->f30;
    } else {
        f32 c = lbl_8035F1C8;
        s.x = c;
        s.y = c;
        s.z = c;
    }
    if (h->f0 & 4) h->Update();
    k = dt / *p->f19c;
    y0 = h->f24;
    dx = k;
    dy = k;
    dz = k;
    if (p->f1c4) {
        dx = -k;
        dy = dx;
        dz = dx;
    }
    s.x -= dx;
    s.y -= dy;
    s.z -= dz;
    if (b || (!p->f1c4 && Mag6C(&s) <= Mag6C(&p->v1d0)) || (p->f1c4 && MagB6C(&s) >= Mag6C(&p->v1d0))) {
        p->f1a8 = 0;
        if (p->f1c8 && !p->f1cc) {
            Apply6C(p, p->v1dc);
        } else if (!p->f1c8) {
            Apply6C(p, p->v1d0);
        }
        if (!b) fn_802494A4(p, 0);
    } else {
        f32 y1;
        V6C w;
        Apply6C(p, s);
        h = p->fe0->f9c;
        if (h->f0 & 4) h->Update();
        y1 = h->f24;
        p->fe0->GetPos(&w, 0, 0, 0, 0);
        w.z -= y0 - y1;
        p->fe0->SetPos(&w, 0, 0, 0, 0);
    }
}
}
} // namespace n8006C748

namespace n8006CD00 {

extern "C" {

struct V6C { f32 x; f32 y; f32 z; };
struct M6C { u8 pad[0x28]; f32 f28; f32 f2c; f32 f30; };
struct H6C { u8 pad[0x78]; M6C *f78; };
struct G6C { u8 pad[0x9c]; H6C *f9c; };
struct O6C { u8 pad[0x428]; H6C *f428; u8 pad42c[0x6dc - 0x42c]; f32 f6dc; f32 f6e0; f32 f6e4; u8 pad6e8[0xc]; f32 f6f4; f32 f6f8; f32 f6fc; };
struct P6C { u8 pad[0xe0]; G6C *fe0; u8 pade4[0x118 - 0xe4]; O6C *f118; u8 pad11c[0x1a0 - 0x11c]; f32 *f1a0; f32 *f1a4; s32 f1a8; u8 pad1ac[0x1c4 - 0x1ac]; s32 f1c4; s32 f1c8; s32 f1cc; V6C v1d0; V6C v1dc; };
void fn_80107F3C(M6C *, V6C *);
void fn_80241140(P6C *, s32);
void fn_802494A4(P6C *, s32);
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F1C8;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;

inline f32 Sqrt6C(f32 x) {
    if (x > lbl_8035F0C0) {
        const f64 _half = lbl_8035F250;
        const f64 _three = lbl_8035F258;
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

inline f32 MagF6C(f32 x, f32 y, f32 z) {
    return Sqrt6C(__fmadds(z, z, __fmadds(x, x, y * y)));
}

inline f32 Mag6C(V6C *v) {
    return Sqrt6C(v->x * v->x + v->y * v->y + v->z * v->z);
}

void fn_8006CD00(P6C *p, s32 a, s32 mode, s32 b) {
    M6C *m;
    f32 sx, sy, sz;
    f32 px, py, pz;
    p->f1c4 = a;
    p->f1c8 = b;
    p->f1cc = 0;
    m = p->fe0->f9c->f78;
    if (m) {
        sx = m->f28;
        sy = m->f2c;
        sz = m->f30;
    } else {
        sz = sy = sx = lbl_8035F1C8;
    }
    px = p->f118->f6dc;
    py = p->f118->f6e0;
    pz = p->f118->f6e4;
    switch (mode) {
    case 0:
        {
            f32 c = *p->f1a0;
            p->v1d0.x = c; p->v1d0.y = c; p->v1d0.z = c;
        }
        p->v1dc.x = px; p->v1dc.y = py; p->v1dc.z = pz;
        break;
    case 1:
        p->v1d0.x = px; p->v1d0.y = py; p->v1d0.z = pz;
        if (p->f1c4) {
            p->f1cc = p->f1c8;
            {
                f32 c = *p->f1a0;
                p->v1dc.x = c; p->v1dc.y = c; p->v1dc.z = c;
            }
        } else {
            p->f1cc = p->f1c8;
            {
                f32 c = *p->f1a4;
                p->v1dc.x = c; p->v1dc.y = c; p->v1dc.z = c;
            }
        }
        break;
    case 2:
        {
            f32 c = *p->f1a4;
            p->v1d0.x = c; p->v1d0.y = c; p->v1d0.z = c;
        }
        p->v1dc.x = px; p->v1dc.y = py; p->v1dc.z = pz;
        break;
    }
    if (p->f1cc == 0 && ((p->f1c4 && MagF6C(sx, sy, sz) >= Mag6C(&p->v1d0)) || (!p->f1c4 && MagF6C(sx, sy, sz) <= Mag6C(&p->v1d0)))) return;
    p->f1a8 = 1;
    if (p->f1c8 && p->f1cc) {
        V6C t = p->v1dc;
        V6C u;
        M6C *m2 = p->fe0->f9c->f78;
        if (m2) fn_80107F3C(m2, &t);
        {
            O6C *o = p->f118;
            f32 rz = o->f6e4 / o->f6fc;
            f32 ry = o->f6e0 / o->f6f8;
            f32 rx = o->f6dc / o->f6f4;
            u.x = t.x / rx;
            u.y = t.y / ry;
            u.z = t.z / rz;
            if (o->f428->f78) fn_80107F3C(o->f428->f78, &u);
        }
    }
    if (a) {
        fn_80241140(p, 9);
    } else {
        fn_80241140(p, 1);
    }
    fn_802494A4(p, 0x18);
}

}
} // namespace n8006CD00

namespace n8006D124 {

extern "C" {

struct V3 { f32 x; f32 y; f32 z; };
struct HB { u32 f0; u8 pad4[0x18 - 4]; f32 f18; f32 f1c; f32 f20; u8 pad24[0x30 - 0x24]; void *f30; u8 pad34[0x68 - 0x34]; };
struct H : HB {
    virtual void v0(); virtual void v1(); virtual void Update(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void Tick(f32);
};
struct G {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void GetPos(V3 *, V3 *, V3 *, V3 *, s32);
    virtual void SetPos(V3 *, V3 *, V3 *, V3 *, s32);
    u8 pad4[0x9c - 4]; H *f9c; u8 padA0[0x118 - 0xa0]; V3 v118; u8 pad124[0x154 - 0x124]; f32 f154;
};
struct E {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32();
    virtual void Say(char *, s32, s32, char *, s32);
    u8 pad4[0x40c - 4]; char f40c[8]; char f414[8];
};
struct G1 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual void GetPos(s32, V3 *, V3 *, V3 *, s32);
};
struct S { u8 pad[0x10]; f32 f10; u8 pad14[4]; f32 f18; u8 pad1c[0x2c - 0x1c]; void Set(f32 a, f32 b) { f10 = a; f18 = b; } };
struct P {
    u8 pad[0xd8]; s32 fd8; u8 paddc[4]; G *fe0; u8 pade4[0x118 - 0xe4]; void *f118;
    u8 pad11c[0x178 - 0x11c]; char f178[8]; G *f180; s32 f184; u8 pad188[0x1a8 - 0x188]; s32 f1a8; V3 v1ac;
    u8 pad1b8[0x1f0 - 0x1b8]; G1 *f1f0; u8 pad1f4[0x1fc - 0x1f4]; s32 f1fc; u8 pad200[0x22c - 0x200]; H *f22c; s32 f230;
    u8 pad234[0x258 - 0x234]; s32 f258; s32 f25c; u8 pad260[4]; f32 *f264; s32 f268; f32 f26c; f32 f270; s32 f274;
    s32 f278; char *f27c; u8 pad280[0x288 - 0x280]; V3 v288; s32 f294;
};
s32 fn_800724A4(void *);
void fn_800711D0(P *, s32, f32);
void fn_8007112C(P *, f32);
void fn_8007115C(P *);
void fn_8006BB24(P *, f32);
void fn_80072AC8(void *, V3 *);
void fn_801078CC(void *, V3 *, V3 *, V3 *, V3 *, s32);
void fn_80190C98(H *);
void fn_8006C748(P *, f32, s32);
s32 fn_8003C674(void *, char *, u32 **);
E *fn_802288FC(void *, s32);
void fn_800F6E88(char *, char *);
void fn_802490E0(P *, s32, f32);
void fn_8023F864(P *, s32);
s32 fn_800F6CD0(char *, char *);
f32 fn_80101664(V3 *);
void fn_80101820(V3 *);
void fn_800713AC(P *, f32);
double fn_800F049C(double);
f32 fn_8023D494(S *, f32, f32);
void fn_80076D44(G *);
void fn_80076C6C(G *);
void *__ct__9C8023D65CFv(void *);
void __dt__9C8023D65CFv(void *, s32);
void __register_global_object(void *, void *, void *);
extern void *volatile lbl_8035A0A4;
extern void *lbl_8035B308;
extern char lbl_8035F1E8[8], lbl_8035F1F0[8], lbl_8035F1F8[8], lbl_8035F264[8], lbl_8035F0E4[4], lbl_8035F26C[8];
extern volatile f32 lbl_8035A210, lbl_8035A218;
extern volatile f32 lbl_8035A27C, lbl_8035A280;
extern s32 lbl_8035A220;
extern volatile s8 lbl_8035A214, lbl_8035A21C, lbl_8035A21D, lbl_8035A21E, lbl_8035A224;
extern volatile f32 lbl_8035F0C0;
extern f32 lbl_8035F0C8, lbl_8035F1C8, lbl_8035F240, lbl_8035F260, lbl_8035F274, lbl_8035F278, lbl_8035F27C;
extern f32 lbl_8035F280, lbl_8035F284, lbl_8035F288;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;

inline f32 Sqrt6D(f32 x) {
    volatile f32 y;
    f64 g = __frsqrte(x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    y = x * g;
    return y;
}

inline f32 Dot6D(V3 *v) {
    f32 m = v->y * v->y;
    m = __fmadds(v->x, v->x, m);
    m = __fmadds(v->z, v->z, m);
    return m;
}

inline f32 Len6D(f32 m) {
    return m > lbl_8035F0C0 ? Sqrt6D(m) : m;
}

// TU .bss 80306798-80306838: a global object and its registration record (the sinit fn_800710BC and
// fn_800629DC use them by label), then this function's own statics.
u8 lbl_80306798[0xC]; u8 lbl_803067A4[0x24]; static u8 c1[0xC]; static S s1o; static u8 c2[0xC]; static S s2o;
void fn_8006D124(P *p, f32 dt) {
    V3 xd0, xc4, xb8, xac, xa0, x94, x88, x7c;
    V3 g70, g64, g58, g4c;
    V3 d, c, b;
    V3 a;
    if (fn_800724A4(p->f118) && !p->fd8) {
        f32 s;
        f32 m = Dot6D(&p->fe0->v118);
        if (Len6D(m) < lbl_8035F260)
            s = Len6D(m) / lbl_8035F260;
        else
            s = lbl_8035F1C8;
        if (p->f294 == 0) {
            p->f294 = 1;
            fn_800711D0(p, 7, s);
        } else {
            fn_8007112C(p, s);
        }
    } else if (p->f294 == 1) {
        p->f294 = 0;
        fn_8007115C(p);
    }
    if (p->f230) fn_8006BB24(p, dt);
    if (p->f22c->f0 & 0x800) {
        fn_80072AC8(p->f118, &a);
        p->f1f0->GetPos(0, &b, &c, &d, 0);
        {
            H *h = p->f22c;
            if (h->f30) {
                fn_801078CC(h->f30, &b, &c, &d, &a, 0);
                fn_80190C98(h);
            }
        }
        p->f22c->Tick(dt);
    }
    if (p->f1a8) fn_8006C748(p, dt, 0);
    if (p->f274) {
        if (p->f268 > 0) {
            p->f270 += dt;
            while (p->f270 >= p->f26c && p->f268 > 0) {
                u32 *r;
                E *o;
                p->f270 -= p->f26c;
                *(u32 *volatile *)&r = 0;
                if (!fn_8003C674(lbl_8035A0A4, ((char *)sD28), &r)) *r = 0;
                (*r)++;
                p->f268--;
                o = fn_802288FC(lbl_8035B308, p->f278);
                if (o) {
                    char buf[8];
                    fn_800F6E88(o->f414, lbl_8035F1E8);
                    fn_800F6E88(o->f40c, p->f27c);
                    fn_800F6E88(buf, lbl_8035F1F0);
                    o->Say(lbl_8035F1F8, 0, 0, buf, 0);
                }
            }
            if (p->f268 == 0) {
                fn_802490E0(p, 0, *p->f264);
                fn_8023F864(p, 6);
                fn_8023F864(p, 7);
                fn_8023F864(p, 8);
                fn_8023F864(p, 9);
            }
        }
        p->fe0->SetPos(&p->v288, 0, 0, 0, 0);
        {
            G *e = p->fe0;
            e->v118.x = p->v1ac.x;
            e->v118.y = p->v1ac.y;
            e->v118.z = p->v1ac.z;
            e->f154 = lbl_8035F0C0;
        }
    }
    if (p->f184 && (fn_800F6CD0(p->f178, lbl_8035F264) || fn_800F6CD0(p->f178, lbl_8035F0E4) || fn_800F6CD0(p->f178, lbl_8035F26C))) {
        G *o = p->f180;
        if (o) {
            H *h;
            f32 k;
            o->GetPos(&xd0, &xb8, &xc4, 0, 0);
            h = p->f180->f9c;
            if (h->f0 & 4) h->Update();
            xd0.x = h->f18;
            xd0.y = h->f1c;
            xd0.z = h->f20;
            p->fe0->GetPos(&xac, &x94, &x88, &x7c, 0);
            k = lbl_8035F0C8;
            if (fn_800F6CD0(p->f178, lbl_8035F0E4)) {
                k = lbl_8035F274;
            } else if (fn_800F6CD0(p->f178, lbl_8035F264)) {
                f32 t = lbl_8035F278 * dt;
                *(volatile f32 *)&xac.x = __fmadds(t, xc4.x, xac.x);
                *(volatile f32 *)&xac.y = __fmadds(t, xc4.y, xac.y);
                *(volatile f32 *)&xac.z = __fmadds(t, lbl_8035F0C0, xac.z);
                k = *(volatile f32 *)&lbl_8035F240;
            } else if (fn_800F6CD0(p->f178, lbl_8035F26C)) {
                k = lbl_8035F240;
            }
            {
                f32 len;
                *(volatile f32 *)&xa0.x = xd0.x - xac.x;
                *(volatile f32 *)&xa0.y = xd0.y - xac.y;
                *(volatile f32 *)&xa0.z = xd0.z - xac.z;
                xa0.z = lbl_8035F0C0;
                len = fn_80101664(&xa0);
                if (len < lbl_8035F27C) {
                    f32 ax, ay, az, bz, bx, by;
                    ax = xa0.x; ay = xa0.y; az = xa0.z; bz = x88.z; by = x88.y; bx = x88.x;
                    xac.x = __fmadds(lbl_8035F240 * (len - k), ax, xac.x);
                    xac.y = __fmadds(lbl_8035F240 * (len - k), ay, xac.y);
                    xac.z = __fmadds(lbl_8035F240 * (len - k), az, xac.z);
                    x94.x = ax; x94.y = ay; x94.z = az;
                    x7c.x = __fmsubs(ay, bz, az * by);
                    x7c.y = __fmsubs(az, bx, ax * bz);
                    x7c.z = __fmsubs(ax, by, ay * bx);
                    fn_80101820(&x7c);
                    p->fe0->SetPos(&xac, &x94, &x88, &x7c, 0);
                }
            }
        }
    }
    fn_800713AC(p, dt);
    if (p->f1fc) {
        f32 diff;
        f32 bb;
        if (!lbl_8035A214) { lbl_8035A210 = lbl_8035F0C0; lbl_8035A214 = 1; }
        if (!lbl_8035A21C) { lbl_8035A218 = lbl_8035F0C0; lbl_8035A21C = 1; }
        if (!lbl_8035A21D) {
            __register_global_object(__ct__9C8023D65CFv((u8 *)&s1o), (void *)__dt__9C8023D65CFv, c1);
            lbl_8035A21D = 1;
        }
        if (!lbl_8035A21E) {
            __register_global_object(__ct__9C8023D65CFv((u8 *)&s2o), (void *)__dt__9C8023D65CFv, c2);
            lbl_8035A21E = 1;
        }
        if (!lbl_8035A224) { lbl_8035A220 = 1; lbl_8035A224 = 1; }
        if (lbl_8035A220) {
            S *s2 = (S *)((u8 *)&s2o);
            S *s1 = (S *)((u8 *)&s1o);
            {
            f32 a = lbl_8035F280, b;
            *(volatile f32 *)&s1->f10 = a;
            b = *(volatile f32 *)&lbl_8035F284;
            *(volatile f32 *)&s1->f18 = b;
            *(volatile f32 *)&s2->f10 = a;
            *(volatile f32 *)&s2->f18 = b;
            }
            *(volatile s32 *)&lbl_8035A220 = 0;
        }
        diff = lbl_8035A280 - lbl_8035A210;
        if ((f32)__fabs(diff) > lbl_8035F0C0)
            lbl_8035A210 = __fmadds(lbl_8035F1C8 - (f32)fn_800F049C(lbl_8035F288 * dt), diff, lbl_8035A210);
        diff = lbl_8035A27C - lbl_8035A218;
        if ((f32)__fabs(diff) > lbl_8035F0C0)
            lbl_8035A218 = __fmadds(lbl_8035F1C8 - (f32)fn_800F049C(lbl_8035F288 * dt), diff, lbl_8035A218);
        diff = fn_8023D494((S *)((u8 *)&s1o), dt, lbl_8035A218);
        bb = fn_8023D494((S *)((u8 *)&s2o), dt, lbl_8035A210);
        p->fe0->GetPos(&g70, &g64, &g58, &g4c, 0);
        {
            f32 t = lbl_8035F27C * -bb;
            *(volatile f32 *)&g70.x = __fmadds(t, g58.x, g70.x);
            *(volatile f32 *)&g70.y = __fmadds(t, g58.y, g70.y);
            *(volatile f32 *)&g70.z = __fmadds(t, g58.z, g70.z);
        }
        {
            f32 t = *(volatile f32 *)&lbl_8035F278 * diff;
            g70.x = __fmadds(t, g4c.x, g70.x);
            g70.y = __fmadds(t, g4c.y, g70.y);
            g70.z = __fmadds(t, g4c.z, g70.z);
        }
        p->fe0->SetPos(&g70, &g64, &g58, &g4c, 0);
    }
    {
        s32 a258 = p->f258;
        if (a258 && !p->f25c) fn_80076D44(p->fe0);
        else if (p->f25c && !a258) fn_80076C6C(p->fe0);
    }
}

}
} // namespace n8006D124

namespace n8006DA44 {

extern "C" {

extern char lbl_8035EF80[8];

struct V80043278 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void send(char *s);
};

#pragma opt_propagation off
void fn_8006DA44(V80043278 *p) {
    char *str = ((char *)lbl_80297908);
    p->send(str + 528);
    p->send(lbl_8035EF80);
    p->send(str + 576);
    p->send(str + 876);
}

} /* extern "C" */
#pragma opt_propagation reset
} // namespace n8006DA44

namespace n8006DAD8 {

extern "C" {

extern char lbl_8035EF80[8];
struct V8004330C {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void m(char *);
};
#pragma opt_propagation off
void fn_8006DAD8(V8004330C *p) {
    char *str = ((char *)lbl_80297908);
    p->m(str + 528);
    p->m(lbl_8035EF80);
    p->m(str + 576);
    p->m(str + 876);
}

} /* extern "C" */
#pragma opt_propagation reset
} // namespace n8006DAD8

namespace n8006DB6C {

extern "C" {

extern f32 lbl_8035F1C8;
extern f32 lbl_8035F1BC;
s32 fn_800724A4(void *);
void fn_8007115C(void *);
void fn_80241588(void *, s32, void *, f32);
void fn_802490E0(void *, s32, f32);

void fn_8006DB6C(u8 *p) {
    if (*(s32 *)(p + 0x15C) != 0) {
        f32 v = lbl_8035F1C8;
        if (*(f32 **)(p + 0x160) != NULL) {
            v = **(f32 **)(p + 0x160);
        }
        if (*(s32 *)(p + 0xDC) == 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
            fn_8007115C(p);
        }
        fn_80241588(p, 40, 0, lbl_8035F1BC);
        *(s32 *)(p + 0x15C) = 0;
        fn_802490E0(p, 10, v);
    }
}

} /* extern "C" */
} // namespace n8006DB6C

namespace n8006DC14 {

extern "C" {

extern f32 lbl_8035F1BC;
s32 fn_800724A4(void *);
void fn_8007115C(void *);
void fn_80241588(void *, s32, s32, f32);

static inline void setstate_8006DC14(u8 *p, s32 st) {
    if (*(s32 *)(p + 0xDC) == 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
        fn_8007115C(p);
    }
    fn_80241588(p, st, 0, lbl_8035F1BC);
}

void fn_8006DC14(u8 *p) {
    u8 *q;
    s32 v;
    u8 *x;
    x = *(u8 **)(p + 0x118);
    q = *(u8 **)(x + 0x5E4);
    *(s32 *)(x + 0x5E8) = 0;
    if (q != 0) {
        s32 *r = *(s32 **)(q + 0x94);
        v = r ? *r : 0;
        switch (v) {
        case 0:
            setstate_8006DC14(p, 1);
            break;
        case 1:
            setstate_8006DC14(p, 22);
            break;
        case 2:
            setstate_8006DC14(p, 21);
            break;
        }
    } else {
        setstate_8006DC14(p, 1);
    }
}

} /* extern "C" */
} // namespace n8006DC14

namespace n8006DD74 {

extern "C" {

struct Vec6E { f32 x; f32 y; f32 z; };
struct Q6E { u8 pad[0xd8]; s32 fd8; };
struct R6E { u32 f0; };
struct Z6E { u8 pad[4]; f32 f4; };
struct O6E { u8 pad[0x118]; Vec6E pos; u8 pad124[0x20c - 0x124]; Q6E *f20c; u8 pad210[0x500 - 0x210]; f32 f500; f32 f504; u8 pad508[4]; R6E *f50c; };
struct P6E { u8 pad[0xdc]; s32 fdc; u8 pade0[0x118 - 0xe0]; O6E *f118; u8 pad11c[0x130 - 0x11c]; f32 *f130; u8 pad134[4]; f32 *f138; };
void fn_80249008(P6E *, s32);
Z6E *fn_8022D694(O6E *);
s32 fn_80072988(O6E *, Vec6E);
s32 fn_800724A4(O6E *);
void fn_8007115C(P6E *);
void fn_800711D0(P6E *, s32, f32);
extern f32 lbl_8035F1C8;
void fn_80241588(P6E *, s32, s32, f32);
void fn_80242168(P6E *, f32);
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F0B8;
extern f32 lbl_8035F0B4;
extern f32 lbl_8035F1BC;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;
extern f64 lbl_8035F290;

inline f32 Sqrt6E(f32 x) {
    volatile f32 y;
    f64 g = __frsqrte(x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    y = x * g;
    return y;
}

inline void Set6E(P6E *p, s32 id) {
    if (p->fdc == 0xe && !fn_800724A4(p->f118)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}

inline void Set2_6D(P6E *p, s32 id) {
    if (p->fdc != 0xe && !fn_800724A4(p->f118)) fn_800711D0(p, 0, lbl_8035F1C8);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}

void fn_8006DD74(P6E *p) {
    f32 d;
    f32 z;
    Vec6E v;
    z = fn_8022D694(p->f118)->f4;
    v = p->f118->pos;
    d = p->f118->f500 * p->f118->f500 + p->f118->f504 * p->f118->f504;
    if (d > lbl_8035F0C0) d = Sqrt6E(d);
    if (p->f118->f20c->fd8 == 1) return;
    if (d > *p->f138) {
        switch (fn_80072988(p->f118, v)) {
        case 1: Set2_6D(p, 0xe); break;
        case 2: Set6E(p, 0xf); break;
        case 3: Set6E(p, 0x1a); break;
        case 4: Set6E(p, 0x19); break;
        default: Set2_6D(p, 0xe); break;
        }
        fn_80242168(p, lbl_8035F0B8);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
    } else if (d > *p->f130) {
        switch (fn_80072988(p->f118, v)) {
        case 1: Set6E(p, 0x23); break;
        case 2: Set6E(p, 0x2c); break;
        case 3: Set6E(p, 0x2b); break;
        case 4: Set6E(p, 0x2a); break;
        default: Set6E(p, 0x23); break;
        }
        fn_80242168(p, lbl_8035F0B4);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
    } else if (fn_800724A4(p->f118)) {
        Vec6E *q = &p->f118->pos;
        f32 len = __fmadds(q->z, q->z, __fmadds(q->x, q->x, q->y * q->y));
        if (len > lbl_8035F0C0) len = Sqrt6E(len);
        if (len < lbl_8035F1C8) {
            Set6E(p, 4);
        } else {
            Set2_6D(p, 0xe);
        }
    } else {
        Set6E(p, 4);
    }
}

} /* extern "C" */
} // namespace n8006DD74

namespace n8006E2F8 {

extern "C" {

struct Vec6E { f32 x; f32 y; f32 z; };
struct Q6E { u8 pad[0xd8]; s32 fd8; };
struct R6E { u32 f0; };
struct Z6E { u8 pad[4]; f32 f4; };
struct O6E { u8 pad[0x118]; Vec6E pos; u8 pad124[0x20c - 0x124]; Q6E *f20c; u8 pad210[0x4cc - 0x210]; s32 f4cc; u8 pad4d0[0x500 - 0x4d0]; f32 f500; f32 f504; u8 pad508[4]; R6E *f50c; u8 pad510[0x6b0 - 0x510]; f32 f6b0; u8 f6b4; };
struct M6E {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void play(char *, s32, s32, s32, s32);
};
struct P6E { u8 pad[0xdc]; s32 fdc; u8 pade0[0x118 - 0xe0]; O6E *f118; u8 pad11c[0x130 - 0x11c]; f32 *f130; u8 pad134[4]; f32 *f138; u8 pad13c[4]; f32 *f140; u8 pad144[4]; f32 *f148; u8 pad14c[0x1f0 - 0x14c]; M6E *f1f0; };
void fn_80249008(P6E *, s32);
Z6E *fn_8022D694(O6E *);
s32 fn_80072988(O6E *, Vec6E);
s32 fn_800724A4(O6E *);
void fn_8007115C(P6E *);
void fn_800711D0(P6E *, s32, f32);
extern f32 lbl_8035F1C8;
void fn_80241588(P6E *, s32, s32, f32);
void fn_80242168(P6E *, f32);
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F0B8;
extern f32 lbl_8035F0B4;
extern f32 lbl_8035F1BC;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;
extern f64 lbl_8035F290;

inline f32 Sqrt6E(f32 x) {
    volatile f32 y;
    f64 g = __frsqrte(x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    y = x * g;
    return y;
}

inline void Set6E(P6E *p, s32 id) {
    if (p->fdc == 0xe && !fn_800724A4(p->f118)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}

inline void Set2_6D(P6E *p, s32 id) {
    if (p->fdc != 0xe && !fn_800724A4(p->f118)) fn_800711D0(p, 0, lbl_8035F1C8);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}

void fn_80073E4C(O6E *, s32);
void fn_80076D50(O6E *, s32);
void fn_802490E0(P6E *, s32, f32);
void fn_802494A4(P6E *, s32);
extern f32 lbl_8035F2C8;
extern f32 lbl_8035F0E0;
extern char lbl_8035F298[8];
extern char lbl_8035F2A0[8];
extern char lbl_8035F2A8[8];
extern char lbl_8035F2B0[8];
extern char lbl_8035F2B8[8];
extern char lbl_8035F2C0[8];

inline void SetF6E(P6E *p, s32 id) {
    if (p->fdc == 0xe && !fn_800724A4(p->f118)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F0E0);
}

void fn_8006E2F8(P6E *p) {
    f32 d;
    f32 z;
    Vec6E v;
    if (p->f118->f4cc == 0) return;
    fn_80073E4C(p->f118, 0);
    fn_80076D50(p->f118, 0);
    switch (p->f118->f6b4) {
    case 0: p->f1f0->play(lbl_8035F298, 0, 0, 0, 0); break;
    case 1: p->f1f0->play(lbl_8035F2A0, 0, 0, 0, 0); break;
    case 2: p->f1f0->play(lbl_8035F2A8, 0, 0, 0, 0); break;
    case 3: p->f1f0->play(lbl_8035F2B0, 0, 0, 0, 0); break;
    case 4: p->f1f0->play(lbl_8035F2B8, 0, 0, 0, 0); break;
    case 5: p->f1f0->play(lbl_8035F2C0, 0, 0, 0, 0); break;
    default: p->f1f0->play(lbl_8035F298, 0, 0, 0, 0); break;
    }
    fn_802490E0(p, 1, *p->f148);
    fn_802490E0(p, 0xc, *p->f140);
    z = fn_8022D694(p->f118)->f4;
    v = p->f118->pos;
    if (p->f118->f6b0 >= lbl_8035F2C8) {
        fn_802494A4(p, 0x19);
        return;
    }
    d = p->f118->f500 * p->f118->f500 + p->f118->f504 * p->f118->f504;
    if (d > lbl_8035F0C0) d = Sqrt6E(d);
    if (p->f118->f20c->fd8 == 1) {
        z = fn_8022D694(p->f118)->f4;
        SetF6E(p, 0x30);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
        return;
    }
    if (d > *p->f138) {
        switch (fn_80072988(p->f118, v)) {
        case 1: SetF6E(p, 0x3d); break;
        case 2: SetF6E(p, 0x3e); break;
        case 3: SetF6E(p, 0x37); break;
        case 4: SetF6E(p, 0x38); break;
        default: SetF6E(p, 0x3d); break;
        }
        fn_80242168(p, lbl_8035F0B8);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
    } else if (d > *p->f130) {
        switch (fn_80072988(p->f118, v)) {
        case 1: SetF6E(p, 0x41); break;
        case 2: SetF6E(p, 0x42); break;
        case 3: SetF6E(p, 0x43); break;
        case 4: SetF6E(p, 0x44); break;
        default: SetF6E(p, 0x41); break;
        }
        fn_80242168(p, lbl_8035F0B4);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
    } else {
        SetF6E(p, 0x20);
    }
}

} /* extern "C" */
} // namespace n8006E2F8

namespace n8006E994 {

extern "C" {

extern f32 lbl_8035F1C8;
extern f32 lbl_8035F0E0;
s32 fn_800724A4(void *);
void fn_800711D0(void *, s32, f32);
void fn_8007115C(void *);
void fn_80241588(void *, s32, s32, f32);

void fn_8006E994(u8 *p, s32 a, s32 b) {
    if (*(s32 *)(*(u8 **)(p + 280) + 1228) == 0) {
        if (*(s32 *)(p + 220) != 14 && a == 14 && fn_800724A4(*(void **)(p + 280)) == 0) {
            fn_800711D0(p, 0, lbl_8035F1C8);
        } else if (*(s32 *)(p + 220) == 14 && a != 14 && fn_800724A4(*(void **)(p + 280)) == 0) {
            fn_8007115C(p);
        }
        fn_80241588(p, a, 0, lbl_8035F0E0);
    } else {
        if (*(s32 *)(p + 220) != 14 && b == 14 && fn_800724A4(*(void **)(p + 280)) == 0) {
            fn_800711D0(p, 0, lbl_8035F1C8);
        } else if (*(s32 *)(p + 220) == 14 && b != 14 && fn_800724A4(*(void **)(p + 280)) == 0) {
            fn_8007115C(p);
        }
        fn_80241588(p, b, 0, lbl_8035F0E0);
    }
}

} /* extern "C" */
} // namespace n8006E994

namespace n8006EAD0 {

extern "C" {

extern f32 lbl_8035F1C8;
s32 fn_800724A4(void *);
void fn_800711D0(void *, s32, f32);
void fn_8007115C(void *);
void fn_80241588(void *, s32, void *, f32);

void fn_8006EAD0(u8 *p, s32 a, void *b, f32 f) {
    if (*(s32 *)(p + 0xDC) != 14 && a == 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
        fn_800711D0(p, 0, lbl_8035F1C8);
    } else if (*(s32 *)(p + 0xDC) == 14 && a != 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
        fn_8007115C(p);
    }
    fn_80241588(p, a, b, f);
}

} /* extern "C" */
} // namespace n8006EAD0

namespace n8006EB9C {

extern "C" {

extern f32 lbl_8035F1C8;
s32 fn_800724A4(void *);
void fn_800711D0(void *, s32, f32);
void fn_8007115C(void *);
void fn_80241588(void *, s32, void *, f32);

void fn_8006EB9C(u8 *p, s32 a, f32 f) {
    if (*(s32 *)(p + 0xDC) != 14 && a == 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
        fn_800711D0(p, 0, lbl_8035F1C8);
    } else if (*(s32 *)(p + 0xDC) == 14 && a != 14 && fn_800724A4(*(void **)(p + 0x118)) == 0) {
        fn_8007115C(p);
    }
    fn_80241588(p, a, 0, f);
}

} /* extern "C" */
} // namespace n8006EB9C

namespace n8006EC5C {

extern "C" {

extern f32 lbl_8035F1C8;
extern f32 lbl_8035F1BC;
s32 fn_800724A4(void *);
void fn_800711D0(void *, s32, f32);
void fn_8007115C(void *);
void fn_80241588(void *, s32, s32, f32);

void fn_8006EC5C(u8 *p, s32 a) {
    if (*(s32 *)(p + 220) != 14 && a == 14 && fn_800724A4(*(void **)(p + 280)) == 0) {
        fn_800711D0(p, 0, lbl_8035F1C8);
    } else if (*(s32 *)(p + 220) == 14 && a != 14 && fn_800724A4(*(void **)(p + 280)) == 0) {
        fn_8007115C(p);
    }
    fn_80241588(p, a, 0, lbl_8035F1BC);
}

} /* extern "C" */
} // namespace n8006EC5C

namespace n8006ED08 {

extern "C" {

struct Vec6E { f32 x; f32 y; f32 z; };
struct Q6E { u8 pad[0xd8]; s32 fd8; };
struct R6E { u32 f0; };
struct Z6E { u8 pad[4]; f32 f4; };
struct O6E { u8 pad[0x118]; Vec6E pos; u8 pad124[0x20c - 0x124]; Q6E *f20c; u8 pad210[0x500 - 0x210]; f32 f500; f32 f504; u8 pad508[4]; R6E *f50c; };
struct P6E { u8 pad[0xdc]; s32 fdc; u8 pade0[0x118 - 0xe0]; O6E *f118; u8 pad11c[0x130 - 0x11c]; f32 *f130; u8 pad134[4]; f32 *f138; };
void fn_80249008(P6E *, s32);
Z6E *fn_8022D694(O6E *);
s32 fn_80072988(O6E *, Vec6E);
s32 fn_800724A4(O6E *);
void fn_8007115C(P6E *);
void fn_80241588(P6E *, s32, s32, f32);
void fn_80242168(P6E *, f32);
extern f32 lbl_8035F0C0;
extern f32 lbl_8035F0B8;
extern f32 lbl_8035F0B4;
extern f32 lbl_8035F1BC;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;
extern f64 lbl_8035F290;

inline f32 Sqrt6E(f32 x) {
    volatile f32 y;
    f64 g = __frsqrte(x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    g = lbl_8035F250 * g * (lbl_8035F258 - g * g * x);
    y = x * g;
    return y;
}

inline void Set6E(P6E *p, s32 id) {
    if (p->fdc == 0xe && !fn_800724A4(p->f118)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}

void fn_8006ED08(P6E *p) {
    f32 d;
    f32 z;
    Vec6E v;
    fn_80249008(p, 2);
    d = p->f118->f500 * p->f118->f500 + p->f118->f504 * p->f118->f504;
    if (d > lbl_8035F0C0) d = Sqrt6E(d);
    z = fn_8022D694(p->f118)->f4;
    v = p->f118->pos;
    if (p->f118->f20c->fd8 == 1) return;
    if (d > *p->f138) {
        switch (fn_80072988(p->f118, v)) {
        case 1: Set6E(p, 0x35); break;
        case 2: Set6E(p, 0x36); break;
        case 3: Set6E(p, 0x37); break;
        case 4: Set6E(p, 0x38); break;
        default: Set6E(p, 0x35); break;
        }
        fn_80242168(p, lbl_8035F0B8);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
    } else if (d > *p->f130) {
        switch (fn_80072988(p->f118, v)) {
        case 1: Set6E(p, 0x39); break;
        case 2: Set6E(p, 0x3a); break;
        case 3: Set6E(p, 0x3b); break;
        case 4: Set6E(p, 0x3c); break;
        default: Set6E(p, 0x39); break;
        }
        fn_80242168(p, lbl_8035F0B4);
        {
            Z6E *zz = fn_8022D694(p->f118);
            zz->f4 = lbl_8035F290 + z;
        }
    } else if (p->f118->f50c->f0 == 1) {
        Set6E(p, 0);
    } else {
        Set6E(p, 0x1d);
    }
}

} /* extern "C" */
} // namespace n8006ED08

namespace n8006F1DC {

extern "C" {

extern f32 lbl_8035F0C0;
extern f32 lbl_8035F2CC;
extern u8 *lbl_80359F2C;
void fn_8007225C(void *, f32);
void fn_80241DD0(void *, const char *, void *, s32, s32, s32);
void fn_80072D94(void *, s32, f32);

void fn_8006F1DC(u8 *p) {
    u8 *g;
    if (*(f32 *)(*(u8 **)(p + 280) + 1648) > lbl_8035F0C0) {
        return;
    }
    fn_8007225C(*(void **)(p + 280), **(f32 **)(p + 236));
    fn_80241DD0(p, ((char *)lbl_80297B00), *(void **)(p + 228), 0, 0, 0);
    g = lbl_80359F2C;
    *(s32 *)(g + 364) = 4;
    *(f32 *)(g + 360) = lbl_8035F2CC;
    fn_80072D94(*(void **)(p + 280), 1, **(f32 **)(p + 344));
}

} /* extern "C" */
} // namespace n8006F1DC

namespace n8006F26C {

extern "C" {

extern f32 lbl_8035F0C0;
extern f32 lbl_8035F2CC;
extern u8 *lbl_80359F2C;
void fn_8007225C(void *, f32);
void fn_80241DD0(void *, const char *, void *, s32, s32, s32);
void fn_80072D94(void *, s32, f32);

void fn_8006F26C(u8 *p) {
    u8 *g;
    if (*(f32 *)(*(u8 **)(p + 280) + 1648) > lbl_8035F0C0) {
        return;
    }
    fn_8007225C(*(void **)(p + 280), **(f32 **)(p + 236));
    fn_80241DD0(p, ((char *)lbl_80297AF4), *(void **)(p + 228), 0, 0, 0);
    g = lbl_80359F2C;
    *(s32 *)(g + 364) = 4;
    *(f32 *)(g + 360) = lbl_8035F2CC;
    fn_80072D94(*(void **)(p + 280), 1, **(f32 **)(p + 344));
}

} /* extern "C" */
} // namespace n8006F26C

namespace n8006F2FC {

extern "C" {

extern f32 lbl_8035F0C0;
extern f32 lbl_8035F2CC;
extern const char lbl_8035EF50[8];
extern const char lbl_8035ED9C[8];
extern u8 *lbl_80359F2C;
void fn_8007225C(void *obj, f32 v);
void fn_80241DD0(void *obj, const char *name, void *a, s32 b, s32 c, s32 d);
void fn_80072D94(void *obj, s32 n, f32 v);
void fn_800F6E88(u8 *dst, u8 *src);
s32 fn_800F6CD0(const char *a, u8 *b);

void fn_8006F2FC(u8 *self) {
    u8 buf[16];
    u8 *g;
    if (!(*(f32 *)(*(u8 **)(self + 280) + 1648) > lbl_8035F0C0)) {
        fn_8007225C(*(void **)(self + 280), **(f32 **)(self + 236));
        fn_80241DD0(self, lbl_8035EF50, *(void **)(self + 228), 0, 0, 0);
        g = lbl_80359F2C;
        *(s32 *)(g + 364) = 4;
        *(f32 *)(g + 360) = lbl_8035F2CC;
        if (*(u8 **)(self + 228) == 0) {
            fn_80072D94(*(void **)(self + 280), 1, **(f32 **)(self + 344));
        } else {
            fn_800F6E88(buf, *(u8 **)(self + 228) + 140);
            if (fn_800F6CD0(lbl_8035ED9C, buf) == 0) {
                fn_80072D94(*(void **)(self + 280), 1, **(f32 **)(self + 344));
            }
        }
    }
}

} /* extern "C" */
} // namespace n8006F2FC

namespace n8006F3CC {

extern "C" {

struct O6F { u8 pad[0x68c]; s32 f68c; };
struct M6F {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void play(char *, O6F *, s32, s32, s32);
};
struct P6F { u8 pad[0xdc]; s32 fdc; u8 pade0[0x118 - 0xe0]; O6F *f118; u8 pad11c[0x16c - 0x11c]; f32 *f16c; f32 *f170; f32 f174; char f178[8]; M6F *f180; };
void fn_80228144(void *, const char *, f32, f32, O6F *, s32, const char *, s32, s32, f32);
void fn_802494A4(P6F *, s32);
void fn_80242174(P6F *, f32);
s32 fn_800724A4(O6F *);
void fn_8007115C(P6F *);
void fn_80241588(P6F *, s32, s32, f32);
s32 fn_800F6CD0(void *, char *);
void __ct__9C80253F24Fiiii(void *, const char *, s32, s32, s32);
extern void *lbl_8035B308;
extern void *lbl_8035B65C;
extern f32 lbl_803596E0[];
extern f32 lbl_8035F2D0;
extern f32 lbl_8035F1BC;
extern f32 lbl_8035F2E4;
extern char lbl_8035F2D4[8];
extern char lbl_8035F2DC[8];
extern char lbl_8035EE18[8];
extern char lbl_8035F264[8];
extern char lbl_8035F26C[8];
extern char lbl_8035F0E4[8];
extern char lbl_8035F2E8[8];
extern char lbl_8035F1D4[8];


inline void Set6F(P6F *p, s32 id) {
    if (p->fdc == 0xe && !fn_800724A4(p->f118)) fn_8007115C(p);
    fn_80241588(p, id, 0, lbl_8035F1BC);
}

void fn_8006F3CC(P6F *p) {
    p->f174 = lbl_803596E0[0];
    p->f180 = 0;
    fn_80228144(lbl_8035B308, ((char *)sDBC), *p->f16c, *p->f170, p->f118, 0, lbl_8035F2D4, 0, 1, lbl_8035F2D0);
    fn_80228144(lbl_8035B308, ((char *)sDBC), *p->f16c, *p->f170, p->f118, 0, lbl_8035F2DC, 0, 1, lbl_8035F2D0);
    if (p->f180 == 0) {
        p->f174 = lbl_803596E0[0];
        p->f180 = 0;
        fn_80228144(lbl_8035B308, ((char *)sDBC), *p->f16c, *p->f170, p->f118, 0, ((char *)sDC8), 0, 1, lbl_8035F2D0);
        if (p->f180) {
            fn_802494A4(p, 6);
            p->f180->play(lbl_8035EE18, p->f118, 0, 0, 0);
        }
    }
    if (p->f118->f68c != 0 && p->f180) {
        if (fn_800F6CD0(p->f178, lbl_8035F264)) {
            p->f180->play(lbl_8035F1D4, p->f118, 0, 0, 0);
            __ct__9C80253F24Fiiii(lbl_8035B65C, ((char *)sCF8), 0, 0, 0);
            Set6F(p, 0x5e);
            fn_802494A4(p, 0x20);
        } else if (fn_800F6CD0(p->f178, lbl_8035F26C)) {
            __ct__9C80253F24Fiiii(lbl_8035B65C, ((char *)sCF8), 0, 0, 0);
            Set6F(p, 0x5a);
            fn_802494A4(p, 0x20);
        } else if (fn_800F6CD0(p->f178, lbl_8035F0E4)) {
            p->f180->play(lbl_8035F1D4, p->f118, 0, 0, 0);
            Set6F(p, 0x47);
            fn_802494A4(p, 0x20);
        } else if (fn_800F6CD0(p->f178, lbl_8035EE18)) {
            p->f180->play(lbl_8035F1D4, p->f118, 0, 0, 0);
            __ct__9C80253F24Fiiii(lbl_8035B65C, ((char *)sCF8), 0, 0, 0);
            Set6F(p, 0x57);
            fn_80242174(p, lbl_8035F2E4);
            fn_802494A4(p, 0x20);
        } else if (fn_800F6CD0(p->f178, lbl_8035F2E8)) {
            p->f180->play(lbl_8035F1D4, p->f118, 0, 0, 0);
        } else {
            __ct__9C80253F24Fiiii(lbl_8035B65C, ((char *)sCF8), 0, 0, 0);
            Set6F(p, 0x75);
            fn_802494A4(p, 0x20);
        }
    }
}

}
} // namespace n8006F3CC

namespace n8006F808 {

extern "C" {
}
#define F(o, off, t) (*(t *)((u8 *)(o) + (off)))
struct K8 { u32 a, b; };
struct V { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28(); virtual void v29();
    virtual void v30(); virtual void v31(); virtual void v32(); virtual void Say(char *, void *, int, int, int); };
struct Nd { u32 fl; u8 p4[0x88 - 4]; u32 x88; };
struct L0 { u8 p[0x10]; u32 n; };
struct Tb { L0 *l; u8 p4[8]; u8 *xc; };
extern "C" {
extern char lbl_8035ED68[4], lbl_8035F2F0[4], lbl_8035F2F8[4], lbl_8035F300[4];
extern f32 lbl_8035F1C8;
extern u8 *lbl_8035B65C;
extern void *volatile lbl_8035A0A4;
int fn_800F6CD0(void *, void *);
void fn_800F6E88(void *, void *);
Tb *fn_8023F4A0(void *, char *, char *, char *, int);
u32 fn_8007239C(void *);
void fn_8007222C(void *, f32);
void fn_8007225C(void *, f32);
void fn_800746A4(void *, void *);
void fn_802494A4(void *, int);
void fn_8019B6B8(void *, Nd *);
void fn_8003C674(void *, void *, u32 **);
void __ct__9C80253F24Fiiii(void *, void *, int, int, int);
static inline u32 Last(u8 *o) { u32 n = fn_8007239C(F(o, 0x118, void *)) - 1; return ((u32 *)F(o, 0x20c, Tb *)->xc)[n]; }
static inline void clr(u8 *o, u32 i) { F(o, 0x228, V **)[i] = 0; }
static inline u32 FindK(u8 *o, Tb *t1, K8 *a, K8 *b) {
    u32 k = 0, i;
    for (i = 0; i < t1->l->n; i++) {
        k = i / *F(o, 0x280, u32 *);
        fn_800F6E88(b, t1->xc + i * 8);
        if (fn_800F6CD0(a, b)) i = t1->l->n;
    }
    return k;
}
void fn_8006F808(u8 *o) {
    char *s = ((char *)lbl_80297908);
    void *cmd = F(o, 0xec, void *);
    F(o, 0xec, void *) = 0;
    if (fn_800F6CD0(cmd, lbl_8035ED68) == 0) {
        F(o, 0xe4, V *)->Say(s + 0x4cc, F(o, 0xe0, void *), 0, 0, 0);
        if (fn_800F6CD0(cmd, s + 0x4d8)) {
            V *me;
            int found;
            u32 i;
            F(o, 0x200, u32)--;
            found = -1;
            me = F(o, 0xe4, V *);
            for (i = 0; i < Last(o); i++) {
                if (F(o, 0x228, V **)[i] == me) {
                    found = i;
                    clr(o, i = Last(o));
                }
            }
            {
                Nd *d = F(o, 0x224, Nd **)[found];
                if (d) {
                    d->fl &= ~0x800;
                    if (d->x88 == 0) fn_8019B6B8(*(void **)(lbl_8035B65C + 12), d);
                }
            }
            if (F(o, 0xe4, V *)) F(o, 0xe4, V *)->Say(s + 0x4e4, 0, 0, 0, 0);
            if (F(o, 0x200, u32) == 0) {
                if (F(o, 0x254, int)) fn_800746A4(F(o, 0xe0, void *), o + 0x244);
                fn_802494A4(o, 0);
            }
            F(o, 0x1f0, V *)->Say(lbl_8035F2F0, 0, 0, 0, 0);
            F(o, 0xe4, V *) = 0;
        } else if (fn_800F6CD0(cmd, s + 0x4f0)) {
            K8 a, d, c, b;
            u32 *r;
            Tb *t1, *t2;
            u32 k, i;
            int ok;
            u32 off;
            u32 j;
            fn_800F6E88(&a, (u8 *)F(o, 0xe4, V *) + 0x8c);
            t1 = fn_8023F4A0(o, lbl_8035ED68, lbl_8035ED68, s + 0x468, 1);
            t2 = fn_8023F4A0(o, lbl_8035ED68, lbl_8035ED68, s + 0x47c, 1);
            k = FindK(o, t1, &a, &b);
            ok = 1;
            j = k * *F(o, 0x280, u32 *);
            for (off = j * 8; j < (k + 1) * *F(o, 0x280, u32 *); off += 8, j++) {
                fn_800F6E88(&c, t1->xc + off);
                if (!fn_800F6CD0(&c, lbl_8035ED68)) {
                    *(u32 *volatile *)&r = 0;
                    fn_8003C674(lbl_8035A0A4, &c, &r);
                    if (!(*r & *F(o, 0x284, u32 *))) ok = 0;
                }
            }
            if (ok) {
                fn_800F6E88(&d, t2->xc + k * 8);
                __ct__9C80253F24Fiiii(lbl_8035B65C, &d, 0, 0, 0);
            }
        } else if (fn_800F6CD0(cmd, lbl_8035F2F8)) {
            fn_8007222C(F(o, 0x118, void *), (s32)*F(o, 0xec, f32 *));
            fn_8007225C(F(o, 0x118, void *), F(F(o, 0xe0, u8 *), 0x1a8, f32) * lbl_8035F1C8);
        } else if (fn_800F6CD0(cmd, lbl_8035F300)) {
            u8 *q = F(o, 0x118, u8 *);
            f32 cu, mx;
            mx = *(volatile f32 *)(q + 0x1a8);
            cu = *(volatile f32 *)(q + 0x1ac);
            if (cu < mx)
                fn_8007225C(q, F(F(o, 0xe0, u8 *), 0x1a8, f32) * *F(o, 0xec, f32 *));
            else
                F(o, 0xe4, V *) = 0;
        } else if (fn_800F6CD0(cmd, s + 0x4fc)) {
            *F(o, 0x1f8, s32 *) += (s32)*F(o, 0xec, f32 *);
        }
    }
    if (F(o, 0xe4, V *)) F(o, 0xe4, V *)->Say(s + 0x4e4, 0, 0, 0, 0);
}
}
#undef F
} // namespace n8006F808

namespace n8006FC88 {

extern "C" {

} /* extern "C" */
struct V8006FC88 {
    u8 pad[128];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20(s32 a);
};
struct D8006FC88 {
    u8 pad[1344];
    s32 *m1344;
};
struct S8006FC88 {
    u8 pad[280];
    D8006FC88 *m280;
};
extern "C" {
extern u8 *lbl_8035A1DC;
extern u8 *lbl_80359F2C;
void fn_802491DC(S8006FC88 *s, s32 a);
void fn_802494A4(S8006FC88 *s, s32 a);

void fn_8006FC88(S8006FC88 *s) {
    s32 *p;
    s32 v;
    D8006FC88 *d;
    d = s->m280;
    p = d->m1344;
    v = *p;
    if (v <= 0) {
        if (*(s32 *)(lbl_8035A1DC + 13992) != 0) {
            V8006FC88 *vv = *(V8006FC88 **)(lbl_80359F2C + 456);
            if (vv) {
                vv->v20(1);
            }
            fn_802491DC(s, 4);
            return;
        }
        *p = v + 5;
        if (*d->m1344 < 0) {
            *d->m1344 = 0;
        }
        fn_802494A4(s, 21);
    } else {
        *p = v - 1;
        if (*d->m1344 < 0) {
            *d->m1344 = 0;
        }
        fn_802494A4(s, 21);
    }
}

} /* extern "C" */
} // namespace n8006FC88

namespace n8006FD64 {

extern "C" {

extern f32 lbl_8035F308;
extern f32 lbl_8035F0C0;
extern f64 lbl_8035F250;
extern f64 lbl_8035F258;
extern f32 lbl_8035F30C;
extern f32 lbl_8035F210;
extern s32 fn_800724A4(u8 *q);
extern void fn_8007115C(u8 *p);
extern void fn_80241588(u8 *p, s32 a, s32 b, f32 t);
extern void fn_802494A4(u8 *p, s32 a);

void fn_8006FD64(u8 *p) {
    u8 *q;
    f32 d;
    volatile f32 y;
    f64 guess;
    if (*(s32 *)(p + 332) == 0) {
        q = *(u8 **)(p + 280);
        if (*(f32 *)(q + 288) < lbl_8035F308) {
            d = *(f32 *)(q + 1280) * *(f32 *)(q + 1280) + *(f32 *)(q + 1284) * *(f32 *)(q + 1284);
            if (d > lbl_8035F0C0) {
                guess = __frsqrte((f64)d);
                guess = lbl_8035F250 * guess * (lbl_8035F258 - guess * guess * d);
                guess = lbl_8035F250 * guess * (lbl_8035F258 - guess * guess * d);
                guess = lbl_8035F250 * guess * (lbl_8035F258 - guess * guess * d);
                y = (f32)(d * guess);
                d = y;
            }
            if (d > lbl_8035F30C) {
                if (*(s32 *)(p + 220) == 14 && fn_800724A4(*(u8 **)(p + 280)) == 0) {
                    fn_8007115C(p);
                }
                fn_80241588(p, 46, 0, lbl_8035F210);
            } else {
                if (*(s32 *)(p + 220) == 14 && fn_800724A4(*(u8 **)(p + 280)) == 0) {
                    fn_8007115C(p);
                }
                fn_80241588(p, 47, 0, lbl_8035F210);
            }
        } else {
            fn_802494A4(p, 0);
        }
    }
}

} /* extern "C" */
} // namespace n8006FD64

namespace n8006FEA4 {

extern "C" {

/* QV=2.0p1 */
extern void *volatile lbl_8035A0A4;
s32 fn_8003C674(void *, char *, s32 *volatile *);
void fn_800746A4(void *, void *);
void fn_80242210(void *);
} /* extern "C" */

struct E_8006FEA4 {
    u8 pad[104];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual ~E_8006FEA4();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
};

struct S_8006FEA4 {
    u8 pad0[224];
    void *f224;
    u8 pad1[304];
    u32 n532;
    u8 pad2[12];
    E_8006FEA4 **a548;
    s32 *a552;
    E_8006FEA4 *p556;
    u8 pad3[20];
    u8 f580[16];
    s32 f596;
    u8 pad4[16];
    s32 f616;
};

extern "C" {

void fn_8006FEA4(S_8006FEA4 *self) {
    s32 amt = self->f616;
    s32 *volatile ptr = 0;
    u32 i;
    s32 *q;
    u32 j;
    if (fn_8003C674(lbl_8035A0A4, ((char *)sD28), &ptr) == 0) {
        *ptr = 0;
    }
    q = ptr;
    *q += amt;
    self->f616 -= amt;
    if (self->f224 != 0 && self->f596 != 0) {
        fn_800746A4(self->f224, self->f580);
    }
    if (self->a548 != 0) {
        for (i = 0; i < self->n532; i++) {
            if (self->a548[i] != 0) {
                self->a548[i]->v10();
                delete self->a548[i];
            }
            self->a548[i] = 0;
        }
        delete[] self->a548;
        self->a548 = 0;
    }
    if (self->a552 != 0) {
        for (j = 0; j < self->n532; j++) {
            self->a552[j] = 0;
        }
        delete[] self->a552;
        self->a552 = 0;
    }
    if (self->p556 != 0) {
        delete self->p556;
        self->p556 = 0;
    }
    fn_80242210(self);
}

} /* extern "C" */
} // namespace n8006FEA4
