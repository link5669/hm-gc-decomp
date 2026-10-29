// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[60] = {1};
static const char sS60[] = "bStartEnabled";
static const char sS76[] = "StandingJumpHeight";
static const char sS96[] = "WalkingJumpHeight";
static const char sS116[] = "RunningJumpHeight";
static const char sS136[] = "MAirborn";
static const char sS148[] = "AirControl";
static const char sS160[] = "MaxAirDownSpeed";
static const char sS176[] = "rNewStandingJumpHeight";
static const char sS200[] = "rNewWalkingJumpHeight";
static const char sS224[] = "rNewRunningJumpHeight";
static const char sS248[] = "rNewAirControl";
static const char sS264[] = "rNewMaxAirDownSpeed";
static const char sS284[] = "rNewGravity";
static const char sS296[] = "rSmoothActivateTime";
static const char sS316[] = "rSmoothDeactivateTime";
static const char sS340[] = "rRevertTime";
extern char lbl_803610A4[4];
extern char lbl_803610A8[4];
extern char lbl_803610B0[4];
extern char lbl_803610B8[4];
extern char lbl_803610C0[4];
extern char lbl_803610C8[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void *fn_80248EAC(char *, char *, const char *);
void fn_80096710(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS60, 1, 0);
    *(void **)((u8 *)p + 284) = fn_80248EAC(lbl_803610A8, lbl_803610B0, (char *)sS76);
    *(void **)((u8 *)p + 288) = fn_80248EAC(lbl_803610A8, lbl_803610B0, (char *)sS96);
    *(void **)((u8 *)p + 292) = fn_80248EAC(lbl_803610A8, lbl_803610B0, (char *)sS116);
    *(void **)((u8 *)p + 296) = fn_80248EAC(lbl_803610A8, (char *)sS136, (char *)sS148);
    *(void **)((u8 *)p + 300) = fn_80248EAC(lbl_803610A8, (char *)sS136, (char *)sS160);
    *(void **)((u8 *)p + 304) = fn_80248EAC(lbl_803610A8, lbl_803610B8, lbl_803610C0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS176, 1, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS200, 1, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS224, 1, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS248, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS264, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS284, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS296, 1, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS316, 1, 0);
    *(void **)((u8 *)p + 340) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, lbl_803610C8, 1, 0);
    *(void **)((u8 *)p + 344) = fn_8023F52C(p, lbl_803610A4, lbl_803610A4, (char *)sS340, 1, 0);
    fn_8023F214(p);
}

} /* extern "C" */
