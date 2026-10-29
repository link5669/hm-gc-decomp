// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[40] = {1};
static const char sS40[] = "aShotSound";
static const char sS52[] = "aBounceSound";
static const char sS68[] = "aDamageSound";
static const char sS84[] = "aCollideSound";
static const char sS100[] = "aSinkSound";
static const char sS112[] = "aRollingSound";
static const char sS128[] = "rDropHeight";
static const char sS140[] = "rDropElasticity";
static const char sS156[] = "rMaxDamage";
static const char sS168[] = "rMinDamageSpeed";
static const char sS184[] = "rMaxDamageSpeed";
static const char sS200[] = "rMaxShadowHeight";
static const char sS220[] = "rMaxAltitudeChange";
static const char sS240[] = "aaEffects";
static const char sS252[] = "Elasticity";
extern char lbl_8035C2F8[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void *fn_8023F4A0(P *, char *, char *, char *, int);
void fn_8023F214(P *);
void fn_80040CD8(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS40, 0, 0);
    *(void **)((u8 *)p + 284) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS52, 0, 0);
    *(void **)((u8 *)p + 288) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS68, 0, 0);
    *(void **)((u8 *)p + 292) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS84, 0, 0);
    *(void **)((u8 *)p + 296) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS100, 0, 0);
    *(void **)((u8 *)p + 300) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS112, 0, 0);
    *(void **)((u8 *)p + 304) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS128, 1, 0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS140, 1, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS156, 1, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS168, 1, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS184, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS200, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS220, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F4A0(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS240, 1);
    *(f32 *)((u8 *)p + 344) = *(f32 *)fn_8023F52C(p, lbl_8035C2F8, lbl_8035C2F8, (char *)sS252, 1, 0);
    fn_8023F214(p);
}

} /* extern "C" */
