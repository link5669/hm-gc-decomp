// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern f32 lbl_803656D0;
extern f64 lbl_803656D8;
extern f32 lbl_803656E0;
s32 OSDisableInterrupts(void);
void OSRestoreInterrupts(s32);
} /* extern "C" */
struct D801FEC54 { u8 pad[8]; u32 f8; };
struct O801FEC54 {
    virtual void v0();
    virtual s32 v1();
    u8 pad[12];
    D801FEC54 *f16;
    u8 pad2[148 - 20];
    u8 f148;
    u8 pad3[468 - 149];
    O801FEC54 *f468;
};
struct S801FEC54 {
    u8 pad[104];
    O801FEC54 *f104;
};
extern "C" {
void fn_801FBA24(S801FEC54 *, f32);
s32 fn_80202B68(O801FEC54 *);
#pragma opt_propagation off
void fn_801FEC54(S801FEC54 *self, f32 t) {
    O801FEC54 *o;
    s32 intr;
    s32 v;
    u32 flags;
    fn_801FBA24(self, t);
    { f32 s; f32 a; a = lbl_803656D0 + t; s = a * lbl_803656D8; v = (s32)(lbl_803656E0 * s); }
    intr = OSDisableInterrupts();
    for (o = self->f104; o != 0; o = o->f468) {
        if (o->v1() != 0 || fn_80202B68(o) != 0) {
            flags = o->f16->f8;
            if (flags & 0x80) {
                o->f148 = v;
            } else if (flags & 0x800) {
                o->f148 = v;
            } else if (flags & 0x400) {
                o->f148 = v;
            }
        }
    }
    OSRestoreInterrupts(intr);
}
#pragma opt_propagation reset

} /* extern "C" */
