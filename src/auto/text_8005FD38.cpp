// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct OV {
    u8 pad[104];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    virtual void v11(f32 dt);
};
struct O : OV {
    u8 pad2[12];
    void *f120;
};
extern "C" {
typedef struct Q {
    u8 pad[16];
    void *f16;
    u8 pad2[12];
    u32 f32_;
} Q;
typedef struct P {
    u8 pad[48];
    Q *f48;
} P;
typedef struct FT {
    u8 pad[12];
    void (*f12)(void *a, void *b);
} FT;
typedef struct Self {
    u8 pad[68];
    u8 f68[620 - 68];
    s32 f620;
    u8 pad2[728 - 624];
    f32 f728;
    f32 f732;
    f32 f736;
    O *f740;
    O *f744;
    P *f748;
    u8 pad3[840 - 752];
    f32 f840;
    u8 pad4[8];
    f32 f852;
    u8 pad5[4];
    f32 f860;
} Self;
extern FT lbl_803286D0;
extern Self *lbl_8035A1A8;
extern u32 lbl_8035E51C;
extern f32 lbl_8035E520;
extern f32 lbl_8035E524;
void fn_8005E354(Self *self);
void fn_80230928(Self *self, f32 dt);
void fn_80107F3C(void *a, f32 *v);
void fn_80190C98(P *p);
void fn_8005E6BC(Self *self, f32 dt);
void fn_8005E00C(Self *self, f32 dt);

void fn_8005FD38(Self *self, f32 dt) {
    if (self->f620 != 0) {
        f32 r;
        P *p;
        Q *q;
        fn_8005E354(self);
        fn_80230928(self, dt);
        if (self->f740 != 0) self->f740->v11(dt);
        if (self->f744 != 0) self->f744->v11(dt);
        if (self->f840 < self->f860) r = self->f840 / self->f860;
        else r = lbl_8035E520;
        if (r < lbl_8035E524) r = lbl_8035E524;
        self->f728 = self->f852 * r;
        self->f732 = self->f852 * r;
        self->f736 = self->f852 * r;
        if (self->f740 != 0 && self->f740->f120 != 0) fn_80107F3C(self->f740->f120, &self->f728);
        if (self->f744 != 0 && self->f744->f120 != 0) fn_80107F3C(self->f744->f120, &self->f728);
        self->f840 += dt;
        p = self->f748;
        if (p != 0 && lbl_8035A1A8 == self) {
            q = p->f48;
            if (q != 0) {
                lbl_803286D0.f12(q->f16, self->f68);
                q->f32_ |= lbl_8035E51C;
                fn_80190C98(p);
            }
        }
    }
    fn_8005E6BC(self, dt);
    fn_8005E00C(self, dt);
}

} /* extern "C" */
