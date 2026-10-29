// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_80297148[];
extern f32 lbl_8035E4CC;
extern f32 lbl_8035E4F8;
extern char lbl_8035E4FC[1];
extern char lbl_8035E500[8];
extern u8 *lbl_8035A1DC;
extern u8 *lbl_8035B65C;
void fn_80233050(void *);
void fn_80232C90(void *);
void *fn_8023D13C(void *, char *, s32);
void *fn_8010FEDC(void *, void *, char *, s32);
void *fn_800F9398(void *, char *);
void *fn_800F9788(void *, char *, char *);
void fn_8019AE40(void *, void *);

static inline void *FindRes_8005F38C(u8 *mgr, char *grp, char *name) {
    if (grp == 0 || grp[0] == 0) {
        return fn_800F9398(mgr + 12496, name);
    }
    return fn_800F9788(mgr + 12520, grp, name);
}

#pragma opt_propagation off
void fn_8005F38C(u8 *self) {
    char *str = lbl_80297148;
    u32 *r;
    u8 *t;
    fn_80233050(self);
    fn_80232C90(self);
    *(void **)(self + 848) = fn_8023D13C(self, str + 48, 0);
    if (*(f32 **)(self + 848) != 0) {
        *(f32 *)(self + 852) = **(f32 **)(self + 848);
    } else {
        *(f32 *)(self + 852) = lbl_8035E4CC;
    }
    *(void **)(self + 856) = fn_8023D13C(self, str + 60, 0);
    if (*(f32 **)(self + 856) != 0) {
        *(f32 *)(self + 860) = **(f32 **)(self + 856);
    } else {
        *(f32 *)(self + 860) = lbl_8035E4F8;
    }
    *(void **)(self + 864) = fn_8023D13C(self, str + 72, 0);
    r = (u32 *)fn_8010FEDC(*(void **)(self + 12), *(void **)(self + 16), str + 92, 0);
    if (r != 0) {
        *(u32 *)(self + 868) = *r;
    }
    *(void **)(self + 876) = fn_8023D13C(self, str + 104, 0);
    *(void **)(self + 748) = FindRes_8005F38C(lbl_8035A1DC, lbl_8035E4FC, lbl_8035E500);
    *(void **)(self + 880) = fn_8023D13C(self, str + 120, 0);
    if (*(u8 **)(self + 748) != 0) {
        if (*(void **)(*(u8 **)(self + 748) + 64) == 0) {
            fn_8019AE40(*(void **)(lbl_8035B65C + 12), *(void **)(self + 748));
            fn_8019AE40(*(void **)(*(u8 **)(lbl_8035B65C + 116) + 484), *(void **)(self + 748));
        }
        **(u32 **)(self + 748) &= ~0x800;
        t = *(u8 **)(*(u8 **)(*(u8 **)(self + 748) + 108) + 16);
        *(f32 *)(self + 788) = *(f32 *)(t + 64);
        *(f32 *)(self + 792) = *(f32 *)(t + 68);
        *(f32 *)(self + 796) = *(f32 *)(t + 72);
        *(f32 *)(self + 800) = *(f32 *)(t + 60);
    }
}
#pragma opt_propagation reset

} /* extern "C" */
