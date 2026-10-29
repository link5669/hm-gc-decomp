// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void __ct__9C80233124Fv(void *);
extern u8 lbl_802BCC00[];
extern f32 lbl_8035E438;
} /* extern "C" */
struct C8005D3E0 {
    u8 *vt;
    u8 pad4[724];
    s32 f728[10];
    s32 f768;
    s32 f772;
    s32 f776;
    f32 f780;
    u8 pad784[32];
    s32 f816;
    s32 f820;
    s32 f824;
    s32 f828;
    s32 f832;
    C8005D3E0() {
        __ct__9C80233124Fv(this);
        vt = lbl_802BCC00;
        f772 = 0;
        f776 = 0;
        f780 = lbl_8035E438;
        f768 = 0;
        f728[0] = 0;
        f728[1] = 0;
        f728[2] = 0;
        f728[3] = 0;
        f728[4] = 0;
        f728[5] = 0;
        f728[6] = 0;
        f728[7] = 0;
        f728[8] = 0;
        f728[9] = 0;
        f820 = 0;
        f824 = 0;
        f828 = 0;
        f832 = 0;
        f816 = 0;
    }
    ~C8005D3E0();
};
extern "C" {
extern void *lbl_8035B320;
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
C8005D3E0 *fn_8005D470(s32 n) {
    C8005D3E0 *p;
    if (n <= 1) {
        if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B320);
        p = new C8005D3E0;
        fn_800F7E98();
        if (p == 0) fn_800604C4(-4, 0, 0, 0);
        return p;
    } else {
        C8005D3E0 *q;
        if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B320);
        q = new C8005D3E0[n];
        fn_800F7E98();
        if (q == 0) fn_800604C4(-4, 0, 0, 0);
        return q;
    }
}

} /* extern "C" */
