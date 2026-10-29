// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Str80056B4C { u32 a; u32 b; } Str80056B4C;
typedef struct SL80056B4C { u8 pad[12]; Str80056B4C *f12; } SL80056B4C;
typedef struct IL80056B4C { u8 pad[12]; s32 *f12; } IL80056B4C;
typedef struct Cnt80056B4C { u8 pad[16]; u32 f16; } Cnt80056B4C;
typedef struct KL80056B4C { Cnt80056B4C *f0; u8 pad[8]; s32 *f12; } KL80056B4C;
typedef struct E80056B4C { u8 pad[20]; s32 f20; } E80056B4C;
typedef struct T80056B4C {
    u8 pad0[224];
    s32 f224;
    u8 pad1[440 - 228];
    SL80056B4C *f440;
    SL80056B4C *f444;
    SL80056B4C *f448;
    SL80056B4C *f452;
    IL80056B4C *f456;
    IL80056B4C *f460;
    KL80056B4C *f464;
    u8 pad2[536 - 468];
    u32 f536;
    u32 f540;
    u32 f544;
    u8 pad3[580 - 548];
    s32 *f580;
    u8 pad4[4];
    s32 f588;
} T80056B4C;
extern char lbl_8035E060[4];
extern void *lbl_8035B65C;
void fn_800F6E88(Str80056B4C *dst, Str80056B4C *src);
s32 fn_800F6CD0(Str80056B4C *s, char *t);
E80056B4C *fn_80242144(T80056B4C *self, u32 idx);
void fn_80242BC0(E80056B4C *e, Str80056B4C *a, s32 b, s32 c, Str80056B4C *d, s32 f);
void __ct__9C80253F24Fiiii(void *o, Str80056B4C *a, s32 b, s32 c, Str80056B4C *d);

void fn_80056B4C(T80056B4C *self, s32 id) {
    Str80056B4C a;
    Str80056B4C b;
    u32 i;
    for (i = 0; i < self->f536; i++) {
        KL80056B4C *kl = self->f464;
        u32 n = kl->f0->f16;
        if ((i >= n && id == 0) || (i < n && id == kl->f12[i])) {
            s32 found = 0;
            if ((*self->f580 & self->f588) == 0 && i < self->f540) {
                found = 1;
                fn_800F6E88(&a, &self->f440->f12[i]);
                fn_800F6E88(&b, &self->f444->f12[i]);
                fn_800F6CD0(&b, lbl_8035E060);
            } else if ((*self->f580 & self->f588) != 0 && i < self->f544) {
                found = 1;
                fn_800F6E88(&a, &self->f448->f12[i]);
                fn_800F6E88(&b, &self->f452->f12[i]);
                fn_800F6CD0(&b, lbl_8035E060);
            }
            if (found != 0 && fn_800F6CD0(&a, lbl_8035E060) == 0) {
                s32 m = *self->f580 & self->f588;
                if ((m == 0 && self->f456->f12[i] != 0) || (m != 0 && self->f460->f12[i] != 0)) {
                    __ct__9C80253F24Fiiii(lbl_8035B65C, &a, self->f224, 0, &b);
                } else {
                    u32 next = i + 1;
                    if (fn_80242144(self, next)->f20 > 0) {
                        fn_80242BC0(fn_80242144(self, next), &a, self->f224, 0, &b, 0);
                    }
                }
            }
        }
    }
}

} /* extern "C" */
