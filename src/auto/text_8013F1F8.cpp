// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Pkt13F {
    u8 pad[42];
    u16 count;
    u8 buf[4];
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual void Write(u32 a, s32 b, void *c, u32 d, u32 e, u32 f);
};
struct Src13F {
    u8 pad[20];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15();
    virtual Pkt13F *Get(u32 idx);
};
struct Out13F {
    u8 pad[12];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void v25();
    virtual void Send(void *buf, u32 len);
};
extern "C" {
typedef struct {
    u32 f0;
    u8 pad4[4];
    Src13F *f8;
    s32 f12;
    u8 f16[112];
    u32 f128;
    u8 pad132[4];
    Out13F *f136;
    u32 f140;
    u32 f144;
    u32 f148;
    u32 f152;
    u32 f156[4];
    u32 f172;
    u32 f176;
    u32 f180;
} Self13F;
void fn_8013F5E0(Self13F *self, u32 a, u32 b, u32 *c);

static inline void Copy13F(Pkt13F *o, Self13F *self) {
    u32 i;
    for (i = 0; i < self->f152; i++) {
        o->buf[o->count++] = self->f156[i];
    }
}

void fn_8013F1F8(Self13F *self, u32 n) {
    u32 len;
    Pkt13F *o;
    self->f180 = 0;
    if (self->f12 == 1) {
        len = n + 2;
        self->f140 += len;
        self->f176 += len;
        self->f128 &= ~1;
        if (self->f176 == 0) {
            self->f144--;
        } else {
            o = self->f8->Get(self->f144 - 1);
            if (self->f12 == 1) {
                o->Write(self->f0, 8, self->f136, self->f148, self->f172, self->f176);
            } else {
                o->Write(self->f0, 4, self->f136, self->f148, self->f172, self->f176);
            }
            Copy13F(o, self);
        }
        fn_8013F5E0(self, self->f148, self->f152, self->f156);
    } else {
        len = n + (n + n);
        self->f140 += len;
        self->f176 += len;
    }
    self->f136->Send(self->f16, len);
}

} /* extern "C" */
