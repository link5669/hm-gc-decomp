// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[108] = {1};
static const char sS108[] = "bCollisionWhileMoving";
static const char sS132[] = "bCollisionWhileStopped";
static const char sS156[] = "aForwardEvent";
static const char sS172[] = "aBackwardEvent";
static const char sS188[] = "bMoveNode";
static const char sS200[] = "nNodeToMove";
static const char sS212[] = "bIgnoreZ";
static const char sS224[] = "bStopForward";
static const char sS240[] = "bStopBackward";
static const char sS256[] = "NearRange";
static const char sS268[] = "aNearEvent";
static const char sS280[] = "aNearData";
static const char sS292[] = "aMoveSound";
static const char sS304[] = "aStartMoveForwardSound";
static const char sS328[] = "aStopMoveForwardSound";
extern char lbl_8035E3A8[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void fn_8005BF98(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS108, 0, 0);
    *(void **)((u8 *)p + 284) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS132, 0, 0);
    *(void **)((u8 *)p + 288) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS156, 0, 0);
    *(void **)((u8 *)p + 292) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS172, 0, 0);
    *(void **)((u8 *)p + 296) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS188, 0, 0);
    *(void **)((u8 *)p + 300) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS200, 0, 0);
    *(void **)((u8 *)p + 304) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS212, 0, 0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS224, 0, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS240, 0, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS256, 0, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS268, 0, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS280, 0, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS292, 0, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS304, 0, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_8035E3A8, lbl_8035E3A8, (char *)sS328, 0, 0);
    fn_8023F214(p);
}

} /* extern "C" */
