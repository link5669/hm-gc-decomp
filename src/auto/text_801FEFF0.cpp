// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct V_801FEFF0 { virtual void p0(); virtual s32 m(); };
extern f32 lbl_803656F4;
extern f32 lbl_803656F8;
void fn_801FBB60(void *, void *, f32);
f32 fn_801FC1F4(f32);
s32 fn_80202B68(void *);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);

#pragma opt_propagation off
void fn_801FEFF0(u8 *p, void *a, f32 f) {
    u8 *q;
    f32 v;
    s32 n;
    fn_801FBB60(p, a, f);
    if (a == 0) {
        for (q = *(u8 **)(p + 104); q != 0; q = *(u8 **)(q + 468)) {
            if (((V_801FEFF0 *)q)->m() != 0 || fn_80202B68(q) != 0) {
                f *= *(f32 *)(q + 44);
                v = fn_801FC1F4(f);
                if (v < lbl_803656F4) {
                    v = lbl_803656F4;
                }
                if (v > lbl_803656F8) {
                    v = lbl_803656F8;
                }
                n = (s32)v;
                n *= 10;
                n <<= 16;
                if (n != *(s32 *)(q + 136)) {
                    s32 lv = OSDisableInterrupts();
                    *(s32 *)(q + 136) = n;
                    OSRestoreInterrupts(lv);
                }
            }
        }
    }
}
#pragma opt_propagation reset

} /* extern "C" */
