// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern "C" {
extern volatile u32 lbl_8035B680;
void fn_802557D8(u32);
void fn_80108860(void *, s32, s32);
} /* extern "C" */
struct V8025 { u8 pad[192]; virtual void v0(); virtual void v1(); virtual void v2(); };
extern "C" {
void fn_802558DC(u8 *p, u32 *s) {
    if (lbl_8035B680 != 0) {
        ((V8025 *)p)->v2();
    }
    *(u32 *)(p + 0) = s[0];
    lbl_8035B680 = s[7];
    fn_802557D8(lbl_8035B680);
    *(u32 *)(p + 172) = s[2];
    *(u32 *)(p + 176) = s[3];
    *(u32 *)(p + 180) = s[4];
    *(u32 *)(p + 184) = s[5];
    *(u32 *)(p + 188) = s[6] == 0;
    fn_80108860(p + 8, 16, 16);
}
}

} /* extern "C" */
