// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct R_89F24 {
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void v5(void *a, s32 b, void *c);
    virtual void v6(s32 a);
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void v12(void *a, void *b, s32 c, s32 d);
};
struct I_89F24 {
    u8 pad[48];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void *v19();
};
struct O_89F24 {
    I_89F24 *f0;
    u8 pad[6444];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void d21();
    virtual void d22();
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void d26();
    virtual void d27();
    virtual void d28();
    virtual void d29();
    virtual void d30();
    virtual void d31();
    virtual void d32();
    virtual void d33();
    virtual void d34();
    virtual void d35();
    virtual void d36();
    virtual void d37();
    virtual void d38();
    virtual void d39();
    virtual void d40();
    virtual void d41();
    virtual void d42();
    virtual void d43();
    virtual void d44();
    virtual void d45();
    virtual void d46();
    virtual void d47();
    virtual void d48();
    virtual void d49();
    virtual void d50();
    virtual void d51();
    virtual void d52();
    virtual void d53();
    virtual void d54();
    virtual void d55();
    virtual void d56();
    virtual void d57();
    virtual void d58();
    virtual void d59();
    virtual void d60();
    virtual void d61();
    virtual void d62();
    virtual void d63();
    virtual void d64();
    virtual void d65();
    virtual void *v66();
    virtual void *v67();
};
extern "C" {
typedef struct { u8 d[28]; } L_89F24;
typedef struct {
    u8 pad[112];
    R_89F24 *r;
    f32 v116[3];
    f32 v128[4];
    f32 v144;
    u8 pad2[36];
} C_89F24;
typedef struct { s32 f0; u8 pad[12]; } E_89F24;
typedef struct { u32 f0; void **f4; } B_89F24;
typedef struct {
    u8 pad[8];
    B_89F24 f8;
    u8 pad2[64];
    s32 f80;
    E_89F24 *f84;
} S_89F24;
extern u8 lbl_803286D0[];
extern u8 lbl_8032C110[];
void fn_8014CA08(L_89F24 *p);
void fn_8014C8C8(L_89F24 *p, s32 a, s32 b, s32 c);
void fn_80189BA4(S_89F24 *self, O_89F24 *obj, C_89F24 *ctx);
void fn_80189808(S_89F24 *self, C_89F24 *ctx, E_89F24 *e);

void fn_80189F24(S_89F24 *self, O_89F24 *obj, void *a, B_89F24 *b) {
    L_89F24 l8;
    C_89F24 ctx;
    E_89F24 *e;
    E_89F24 *end;

    fn_8014CA08(&l8);
    (*(void (**)(void *, void *, f32 *))(lbl_803286D0 + 392))(obj->v67(), a, ctx.v116);
    if ((*(u32 (**)(void *, f32 *, f32 *, f32 *))(lbl_8032C110 + 436))(obj->v66(), ctx.v116, ctx.v128, &ctx.v144) == 0) {
        ctx.v144 = -ctx.v144;
        if (b == 0) b = &self->f8;
        ctx.r = (R_89F24 *)obj->f0->v19();
        fn_80189BA4(self, obj, &ctx);
        fn_8014C8C8(&l8, 0xE100, 0, 1);
        end = self->f84 + self->f80;
        for (e = self->f84; e < end; e++) {
            ctx.r->v5(&l8, 6, &ctx);
            fn_80189808(self, &ctx, e);
            ctx.r->v6(6);
            ctx.r->v12(obj, b->f4[e->f0], 0, 0);
        }
    }
}

} /* extern "C" */
