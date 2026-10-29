// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[96] = {1};
static const char sS96[] = "bShatter";
static const char sS108[] = "rShatterHeightDiff";
static const char sS128[] = "rSplashZ";
static const char sS140[] = "rCollisionRadius";
static const char sS160[] = "rCollisionHeight";
static const char sS180[] = "rPlayerBaseZOffset";
static const char sS200[] = "rSpeedMultiplier";
static const char sS220[] = "rMaxSpeed";
static const char sS232[] = "rArcAngle";
static const char sS244[] = "rRotationSpeed";
static const char sS260[] = "bAffectedByGravity";
static const char sS280[] = "bKickBeforeGravity";
static const char sS300[] = "aRippleEffect";
static const char sS316[] = "rRippleEffectTime";
static const char sS336[] = "rMinSoundGap";
static const char sS352[] = "rMaxSoundGap";
static const char sS368[] = "rTimeBetweenCollisionTests";
static const char sS396[] = "rMinTimeBetweenDropTests";
static const char sS424[] = "rMaxTimeBetweenDropTests";
extern char lbl_80362EB0[4];
extern char lbl_80362FB8[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void fn_800B266C(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS96, 1, 0);
    *(void **)((u8 *)p + 284) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS108, 1, 0);
    *(void **)((u8 *)p + 288) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, lbl_80362FB8, 1, 0);
    *(void **)((u8 *)p + 292) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS128, 1, 0);
    *(void **)((u8 *)p + 296) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS140, 1, 0);
    *(void **)((u8 *)p + 300) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS160, 1, 0);
    *(void **)((u8 *)p + 304) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS180, 1, 0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS200, 1, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS220, 1, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS232, 1, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS244, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS260, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS280, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS300, 1, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS316, 1, 0);
    *(void **)((u8 *)p + 340) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS336, 1, 0);
    *(void **)((u8 *)p + 344) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS352, 1, 0);
    *(void **)((u8 *)p + 348) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS368, 1, 0);
    *(void **)((u8 *)p + 352) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS396, 1, 0);
    *(void **)((u8 *)p + 356) = fn_8023F52C(p, lbl_80362EB0, lbl_80362EB0, (char *)sS424, 1, 0);
    fn_8023F214(p);
}

} /* extern "C" */
