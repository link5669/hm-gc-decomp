// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } T12_8015F808;
extern T12_8015F808 lbl_802E6FB0[10];
} /* extern "C" */
struct R8015F808 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void *Get(s32 id);
};
extern "C" {
void *memcpy(void *dst, const void *src, u32 n);
void fn_802178B8(void *p, u8 **pp, u32 *pcount);
void *fn_8015FE74(R8015F808 *r, s32 id);

typedef struct D8015F808 {
    s32 w0;
    s32 w4;
    u32 w8;
    u32 w12;
    u32 w16;
    u16 h20;
    u16 h22;
    u16 h24;
    u16 h26;
    u16 h28;
    u16 h30;
    u8 b32[4];
    u16 h36;
    u16 h38;
} D8015F808;

typedef struct O8015F808 {
    u8 pad[20];
    u32 w20;
} O8015F808;

typedef struct S8015F808 {
    O8015F808 *w0;
    u8 pad4[16];
    u32 w20;
    u32 w24;
    u32 w28;
    u16 h32;
    u16 h34;
    u16 h36;
    u16 h38;
    u16 h40;
    u16 h42;
    u32 w44;
    u8 pad48[4];
    void *w52;
    u8 pad56[4];
    u8 sub60[16];
    u16 h76;
    u8 pad78[10];
    T12_8015F808 c88;
} S8015F808;

typedef struct C8015F808 {
    u8 pad[24];
    R8015F808 *res;
} C8015F808;

void fn_8015F808(S8015F808 *self, void *unused, C8015F808 *ctx, u8 **pp, u32 *pcount) {
    T12_8015F808 *tab = lbl_802E6FB0;
    D8015F808 *desc = (D8015F808 *)*pp;
    self->h36 = desc->h24;
    self->w20 = desc->w8;
    self->h34 = desc->h22;
    self->w24 = desc->w12;
    self->w28 = desc->w16;
    self->h38 = desc->h26;
    self->h40 = desc->h28;
    self->h76 = desc->h36;
    self->h32 = desc->h20;
    self->h42 = desc->h30;
    if (self->h42 > 4) {
        self->w44 = *pcount;
        *pcount += self->h42;
    } else {
        memcpy(&self->w44, desc->b32, 4);
    }
    *pp += 40;
    if (desc->w0 >= 0) {
        self->w0 = (O8015F808 *)ctx->res->Get(desc->w0);
        fn_802178B8(self->sub60, pp, pcount);
    }
    if (desc->w4 >= 0) {
        self->w52 = fn_8015FE74(ctx->res, desc->w4);
    }
    if (self->h36 & 0x80) {
        self->c88 = tab[6];
    } else if (self->w0->w20 == 0) {
        self->c88 = tab[7];
    } else if (self->w0->w20 == 1) {
        self->c88 = tab[8];
    } else {
        self->c88 = tab[9];
    }
}

} /* extern "C" */
