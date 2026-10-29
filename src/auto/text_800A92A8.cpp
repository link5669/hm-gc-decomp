// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[36] = {1};
static const char sS36[] = "nDamageLow";
static const char sS48[] = "nDamageHigh";
static const char sS60[] = "nLivesLow";
static const char sS72[] = "nLivesHigh";
static const char sS84[] = "nHealthLow";
static const char sS96[] = "nHealthHigh";
static const char sS108[] = "nCardsLow";
static const char sS120[] = "nCardsHigh";
static const char sS132[] = "nContinueLow";
static const char sS148[] = "nContinueHigh";
static const char sS164[] = "rSpeedLow";
static const char sS176[] = "rSpeedHigh";
static const char sS188[] = "rOmegaLow";
static const char sS200[] = "rOmegaHigh";
static const char sS212[] = "rSpringLow";
static const char sS224[] = "rSpringHigh";
static const char sS236[] = "rViscosityLow";
static const char sS252[] = "rViscosityHigh";
static const char sS268[] = "NUMCARDS";
extern char lbl_80362058[4];
extern char lbl_803620F8[4];
extern char lbl_80362100[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void *fn_80248EAC(char *, char *, const char *);
void fn_800A92A8(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_80362058, lbl_80362058, lbl_803620F8, 1, 0);
    *(void **)((u8 *)p + 284) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS36, 1, 0);
    *(void **)((u8 *)p + 288) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS48, 1, 0);
    *(void **)((u8 *)p + 292) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS60, 1, 0);
    *(void **)((u8 *)p + 296) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS72, 1, 0);
    *(void **)((u8 *)p + 300) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS84, 1, 0);
    *(void **)((u8 *)p + 304) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS96, 1, 0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS108, 0, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS120, 0, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS132, 1, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS148, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS164, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS176, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS188, 1, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS200, 1, 0);
    *(void **)((u8 *)p + 340) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS212, 1, 0);
    *(void **)((u8 *)p + 344) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS224, 1, 0);
    *(void **)((u8 *)p + 348) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS236, 1, 0);
    *(void **)((u8 *)p + 352) = fn_8023F52C(p, lbl_80362058, lbl_80362058, (char *)sS252, 1, 0);
    *(void **)((u8 *)p + 504) = fn_80248EAC(lbl_80362100, lbl_80362058, (char *)sS268);
    fn_8023F214(p);
}

} /* extern "C" */
