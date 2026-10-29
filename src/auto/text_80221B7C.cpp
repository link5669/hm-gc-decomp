// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V_80221B7C { u8 pad[96]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); };
extern "C" {
struct Bink_80221B7C { u32 w; u32 h; };
struct P_80221B7C {
    u8 pad0[8];
    s32 f8;
    s32 f12;
    s32 f16;
    s32 f20;
    u8 pad24[8];
    f32 f32_;
    u32 f36;
    u8 pad40[4];
    void *f44;
    u8 pad48[16];
    u32 f64;
    u32 f68;
    u8 pad72[4];
    u32 f76;
    u8 pad80[20];
    Bink_80221B7C *bink;
};
struct I_80221B7C { u8 pad[32]; u32 track; u8 pad2[20]; void *f56; };
extern f32 lbl_80365A20;
void fn_80216844(P_80221B7C *p, I_80221B7C *info);
void *fn_80221538(u32);
void fn_80221510(void *);
void fn_8027B6C0(void *(*a)(u32), void (*f)(void *));
void fn_80276FD8(u32 n, u32 *tracks);
Bink_80221B7C *fn_80277218(void *src, u32 flags);
s32 fn_800BFF54(void);
char *fn_802769E4(void);
char *strcat(char *dst, const char *src);
void fn_8027A538(Bink_80221B7C *b, u32 track, u32 vol);

void fn_80221B7C(P_80221B7C *self, I_80221B7C *info) {
    u32 flags;
    u32 tmp;
    fn_80216844(self, info);
    fn_8027B6C0(fn_80221538, fn_80221510);
    flags = 0;
    s32 snd = (self->f76 & 8) ? 0 : 1;
    if (snd == 0) {
        fn_80276FD8(0, 0);
        flags = 0x4000;
    } else if (info->track != 0) {
        tmp = info->track;
        fn_80276FD8(1, &tmp);
        flags = 0x4000;
    }
    if (self->f76 & 4) {
        ((V_80221B7C *)self)->v0();
        self->bink = fn_80277218(self->f44, flags | 0x4000000);
    } else {
        if (fn_800BFF54() == 0) {
            ((V_80221B7C *)self)->v5();
            return;
        }
        self->bink = fn_80277218(info->f56, flags);
    }
    if (self->bink == 0) {
        char *err = fn_802769E4();
        char buf[128] = "AtVpBiPlayer: Bink Error - ";
        strcat(buf, err);
        ((V_80221B7C *)self)->v5();
        return;
    }
    self->f68 = self->bink->h;
    self->f64 = self->bink->w;
    if (self->f20 == 0) self->f20 = self->f8 + self->bink->h;
    if (self->f16 == 0) self->f16 = self->f12 + self->bink->w;
    fn_8027A538(self->bink, self->f36, (u32)(lbl_80365A20 * self->f32_));
    ((V_80221B7C *)self)->v2();
}

} /* extern "C" */
