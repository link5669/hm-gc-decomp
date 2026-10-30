// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct P { u8 pad[1396]; s32 a1396; s32 a1400; s32 a1404; s32 a1408; s32 a1412; s32 a1416; s32 a1420; };
struct EV { u8 pad[12]; char name[20]; char *arg; };
static const char sPad[176] = {1};
static const char s176[] = "M_STOPSC";
static const char s188[] = "M_STOPSR";
static const char s200[] = "M_STOPS1";
static const char s212[] = "M_STOPS2";
static const char s224[] = "M_STOPS3";
static const char s236[] = "M_STOPS4";
static const char s248[] = "M_STOPS5";
static const char s260[] = "M_AMBSND";
extern char lbl_80366D54[8], lbl_80366D5C[8], lbl_80366D64[8], lbl_80366D6C[8], lbl_80366D74[8], lbl_80366D7C[8], lbl_80366D84[8], lbl_80366D8C[8], lbl_80366D94[8];
extern void *lbl_8035B7BC;
void fn_800F6E88(char *, char *);
int fn_800F6CD0(char *, const char *);
void fn_8026B7CC(void *, char *);

void fn_80268B08(P *p, EV *e) {
    char buf[8];
    fn_800F6E88(buf, e->name);
    if (fn_800F6CD0(buf, lbl_80366D54)) {
        p->a1404 = 2;
    } else if (fn_800F6CD0(buf, lbl_80366D5C)) {
        p->a1400 = 1;
        p->a1408 = 4;
    } else if (fn_800F6CD0(buf, lbl_80366D64)) {
        p->a1408 = 4;
    } else if (fn_800F6CD0(buf, lbl_80366D6C)) {
        p->a1420 = 7;
    } else if (fn_800F6CD0(buf, lbl_80366D74)) {
        p->a1416 = 8;
    } else if (fn_800F6CD0(buf, lbl_80366D7C)) {
        p->a1412 = 9;
    } else if (fn_800F6CD0(buf, lbl_80366D84)) {
        p->a1396 = 10;
    } else if (fn_800F6CD0(buf, lbl_80366D8C)) {
        p->a1396 = 11;
    } else if (fn_800F6CD0(buf, s176)) {
        if (p->a1400 == 1) p->a1400 = 15;
    } else if (fn_800F6CD0(buf, s188)) {
        if (p->a1408 == 4) p->a1408 = 15;
    } else if (fn_800F6CD0(buf, s200)) {
        if (p->a1420 == 7) p->a1420 = 15;
    } else if (fn_800F6CD0(buf, s212)) {
        if (p->a1416 == 8) p->a1416 = 15;
    } else if (fn_800F6CD0(buf, s224)) {
        if (p->a1412 == 9) p->a1412 = 15;
    } else if (fn_800F6CD0(buf, s236)) {
        if (p->a1396 == 10) p->a1396 = 15;
    } else if (fn_800F6CD0(buf, s248)) {
        if (p->a1396 == 11) p->a1396 = 15;
    } else if (fn_800F6CD0(buf, s260)) {
        if (e->arg) fn_8026B7CC(lbl_8035B7BC, e->arg);
        else fn_8026B7CC(lbl_8035B7BC, lbl_80366D94);
    }
}

} /* extern "C" */
