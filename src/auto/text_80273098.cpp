// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern void *lbl_8035B738;
extern u8 __vt__9C80273730[];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);

} /* extern "C" */
struct C80257738 { C80257738(); ~C80257738(); };
extern "C" {
struct C8025E920 {
    u8 d[208 - 192];
    C8025E920();
    ~C8025E920();
};
struct V_80273098 {
    u8 *vt;
    V_80273098() { vt = __vt__9C80273730; }
};
struct N_80273098;
void fn_802575F0(N_80273098 *);
struct N_80273098 : C80257738 {
    V_80273098 v;
    u8 pad[192 - 4];
    C8025E920 m;
    N_80273098() { fn_802575F0(this); }
};
struct C80273730 {
    u8 d[208];
    C80273730();
    ~C80273730();
};

void *fn_80273098(s32 n) {
    if (n <= 1) {
        N_80273098 *p;
        if (!lbl_8035B738) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new N_80273098;
        fn_800F7E98();
        if (!p) fn_800604C4(-4, 0, 0, 0);
        return p;
    } else {
        C80273730 *p;
        if (!lbl_8035B738) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B738);
        p = new C80273730[n];
        fn_800F7E98();
        if (!p) fn_800604C4(-4, 0, 0, 0);
        return p;
    }
}

} /* extern "C" */
