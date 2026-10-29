// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[300] = {1};
static const char sS300[] = "AttackDamage";
static const char sS316[] = "AttackRange";
static const char sS328[] = "ShotDelay";
static const char sS340[] = "WebStrength";
static const char sS352[] = "SpeedScale";
static const char sS364[] = "PushRange";
static const char sS376[] = "PushSpeed";
static const char sS388[] = "NearRange";
static const char sS400[] = "FarRange";
static const char sS412[] = "DodgeRange";
static const char sS424[] = "SlowdownFactor";
static const char sS440[] = "SlowdownTime";
static const char sS456[] = "Unbreakable";
static const char sS468[] = "MissRecovery";
static const char sS484[] = "CanShoot";
static const char sS496[] = "ReleaseProbability";
extern char lbl_8035DE24[4];
extern char lbl_8035E024[4];
extern char lbl_8035E02C[4];
extern char lbl_8035E034[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void fn_800543B0(P *p) {
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS300, 1, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS316, 1, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS328, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS340, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS352, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, lbl_8035E024, 1, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS364, 1, 0);
    *(void **)((u8 *)p + 340) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS376, 1, 0);
    *(void **)((u8 *)p + 356) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS388, 1, 0);
    *(void **)((u8 *)p + 360) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS400, 1, 0);
    *(void **)((u8 *)p + 364) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS412, 1, 0);
    *(void **)((u8 *)p + 368) = fn_8023F52C(p, lbl_8035DE24, lbl_8035E02C, (char *)sS424, 1, 0);
    *(void **)((u8 *)p + 372) = fn_8023F52C(p, lbl_8035DE24, lbl_8035E02C, (char *)sS440, 1, 0);
    *(void **)((u8 *)p + 404) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS456, 0, 0);
    *(void **)((u8 *)p + 408) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS468, 1, 0);
    *(void **)((u8 *)p + 412) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, lbl_8035E034, 1, 0);
    *(void **)((u8 *)p + 416) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS484, 1, 0);
    *(void **)((u8 *)p + 420) = fn_8023F52C(p, lbl_8035DE24, lbl_8035DE24, (char *)sS496, 1, 0);
    fn_8023F214(p);
}

} /* extern "C" */
