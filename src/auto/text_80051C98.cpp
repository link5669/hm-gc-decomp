// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[276] = {1};
static const char sS276[] = "rStartNodeSpeed";
static const char sS292[] = "rMinSuckSpeed";
static const char sS308[] = "rMaxSuckSpeed";
static const char sS324[] = "rMinSuckAngle";
static const char sS340[] = "rMaxSuckAngle";
static const char sS356[] = "aPickupName";
static const char sS368[] = "rZOffset";
static const char sS380[] = "bHasDeathCertificate";
static const char sS404[] = "aDeathCertType";
static const char sS420[] = "nFleeVOPercent";
static const char sS436[] = "nIdleVOPercent";
static const char sS452[] = "nCaughtVOPercent";
static const char sS472[] = "rBonusSpawnRadius";
static const char sS492[] = "rBonusSpeed";
static const char sS504[] = "rSafetyTime";
extern char lbl_8035DB88[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_800A2AF0(P *);
void fn_80051C98(P *p) {
    *(void **)((u8 *)p + 532) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS276, 1, 0);
    *(void **)((u8 *)p + 536) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS292, 1, 0);
    *(void **)((u8 *)p + 540) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS308, 1, 0);
    *(void **)((u8 *)p + 544) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS324, 1, 0);
    *(void **)((u8 *)p + 548) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS340, 1, 0);
    *(void **)((u8 *)p + 552) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS356, 1, 0);
    *(void **)((u8 *)p + 556) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS368, 1, 0);
    *(void **)((u8 *)p + 560) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS380, 1, 0);
    *(void **)((u8 *)p + 564) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS404, 1, 0);
    *(void **)((u8 *)p + 568) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS420, 1, 0);
    *(void **)((u8 *)p + 572) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS436, 1, 0);
    *(void **)((u8 *)p + 576) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS452, 1, 0);
    *(void **)((u8 *)p + 580) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS472, 1, 0);
    *(void **)((u8 *)p + 584) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS492, 1, 0);
    *(void **)((u8 *)p + 588) = fn_8023F52C(p, lbl_8035DB88, lbl_8035DB88, (char *)sS504, 1, 0);
    fn_800A2AF0(p);
}

} /* extern "C" */
