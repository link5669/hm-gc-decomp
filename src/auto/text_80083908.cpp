// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 b[1]; };
static const char sPad[232] = {1};
static const char sS232[] = "bSaveState";
static const char sS244[] = "bStartEnabled";
static const char sS260[] = "bStartInInitialState";
static const char sS284[] = "bOneShot";
static const char sS296[] = "bSyncOnInit";
static const char sS308[] = "rRevertTime";
static const char sS320[] = "bPlayerCanActivate";
static const char sS340[] = "bPlayerCanDeactivate";
static const char sS364[] = "aActivateEvent";
static const char sS380[] = "aActivateData";
static const char sS396[] = "aDeactivateEvent";
static const char sS416[] = "aDeactivateData";
static const char sS432[] = "bSendActivateGameEvent";
static const char sS456[] = "bSendDeactivateGameEvent";
static const char sS484[] = "rForwardRateScale";
static const char sS504[] = "rReverseRateScale";
static const char sS524[] = "aObjectType";
static const char sS536[] = "rStartPercent";
extern char lbl_8035FB58[4];
extern char lbl_8035FC4C[4];
extern char lbl_8035FC54[4];
void *fn_8023F52C(P *, char *, char *, char *, int, int);
void fn_8023F214(P *);
void fn_80083908(P *p) {
    *(void **)((u8 *)p + 280) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS232, 1, 0);
    *(void **)((u8 *)p + 284) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS244, 1, 0);
    *(void **)((u8 *)p + 288) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS260, 1, 0);
    *(void **)((u8 *)p + 292) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS284, 1, 0);
    *(void **)((u8 *)p + 296) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, lbl_8035FC4C, 1, 0);
    *(void **)((u8 *)p + 300) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS296, 1, 0);
    *(void **)((u8 *)p + 304) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, lbl_8035FC54, 1, 0);
    *(void **)((u8 *)p + 308) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS308, 1, 0);
    *(void **)((u8 *)p + 312) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS320, 1, 0);
    *(void **)((u8 *)p + 316) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS340, 1, 0);
    *(void **)((u8 *)p + 320) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS364, 1, 0);
    *(void **)((u8 *)p + 324) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS380, 1, 0);
    *(void **)((u8 *)p + 328) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS396, 1, 0);
    *(void **)((u8 *)p + 332) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS416, 1, 0);
    *(void **)((u8 *)p + 336) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS432, 1, 0);
    *(void **)((u8 *)p + 340) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS456, 1, 0);
    *(void **)((u8 *)p + 344) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS484, 1, 0);
    *(void **)((u8 *)p + 348) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS504, 1, 0);
    *(void **)((u8 *)p + 352) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS524, 1, 0);
    *(void **)((u8 *)p + 356) = fn_8023F52C(p, lbl_8035FB58, lbl_8035FB58, (char *)sS536, 1, 0);
    fn_8023F214(p);
}

} /* extern "C" */
