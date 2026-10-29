// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[36] = {1};
static const char sS36[] = "aIndoorPath";
static const char sS48[] = "aOutdoorPath";
static const char sS64[] = "aHangPath";
static const char sS76[] = "rAttackRange";
static const char sS92[] = "rReturnRange";
static const char sS108[] = "rWanderRange";
static const char sS124[] = "rNodeDist";
static const char sS136[] = "nHangTime";
static const char sS148[] = "nWanderTime";
static const char sS160[] = "nNodeTime";
static const char sS172[] = "nAttackTime";
static const char sS184[] = "rWanderSpeed";
static const char sS200[] = "rAttackSpeed";
static const char sS216[] = "rPlayerHeight";
static const char sS232[] = "CloseEnoughDist";
extern char lbl_80361EC0[4];
extern char lbl_80361F50[4];
extern char lbl_80361F78[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void fn_800A7DE0(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, lbl_80361F78, 1, 0);
    *(void **)((u8 *)p + 284) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS36, 1, 0);
    *(void **)((u8 *)p + 288) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS48, 1, 0);
    *(void **)((u8 *)p + 292) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS64, 1, 0);
    *(void **)((u8 *)p + 296) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS76, 1, 0);
    *(void **)((u8 *)p + 300) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS92, 1, 0);
    *(void **)((u8 *)p + 304) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS108, 1, 0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS124, 1, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS136, 1, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS148, 1, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS160, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS172, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS184, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS200, 1, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_80361F50, lbl_80361F50, (char *)sS216, 1, 0);
    *(void **)((u8 *)p + 340) = fn_8023F52C(p, lbl_80361F50, lbl_80361EC0, (char *)sS232, 1, 0);
    fn_8023F214(p);
}

} /* extern "C" */
