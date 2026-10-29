// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct V_80205AEC { virtual void p0(); virtual s32 m(); };
extern f32 lbl_80365774;
extern f32 lbl_80365778;
void fn_801FBB60(void *, void *, f32);
s32 fn_80202B68(void *);
f32 fn_801FC1F4(f32);
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);

#pragma opt_propagation off
void fn_80205AEC(u8 *p, void *a, f32 f) {
    u8 *q;
    fn_801FBB60(p, a, f);
    if (a == NULL) {
        for (q = *(u8 **)(p + 0xB0); q != NULL; q = *(u8 **)(q + 0x1D4)) {
            if (((V_80205AEC *)q)->m() != 0 || fn_80202B68(q) != 0) {
                f32 g;
                s32 v;
                f *= *(f32 *)(q + 0x2C);
                g = fn_801FC1F4(f);
                if (g < lbl_80365774) {
                    g = lbl_80365774;
                }
                if (g > lbl_80365778) {
                    g = lbl_80365778;
                }
                v = (s32)g;
                v = v * 10;
                v = v << 16;
                if (v != *(s32 *)(q + 0x88)) {
                    s32 lv = OSDisableInterrupts();
                    *(s32 *)(q + 0x88) = v;
                    OSRestoreInterrupts(lv);
                }
            }
        }
    }
}
#pragma opt_propagation reset

} /* extern "C" */
