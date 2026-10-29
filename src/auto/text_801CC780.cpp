// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */

struct Parser {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual u32 v5();
};

struct SelfBase {
    void *f0;
    s32 f4;
    u8 pad8[8];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
};

struct Self : SelfBase {
    u8 f20[16];
    s32 f36;
    u8 pad40[16];
    s32 f56;
    u8 pad60[4];
    char *f64;
};

extern "C" {

extern void *lbl_8035A9F4;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void fn_800FB064(Parser *, void *);
void fn_800FAEF8(Parser *);
void fn_800F6E88(char *, void *);
void fn_80121CE8(void *, Parser *);
s32 fn_801AAA5C(void *, void *, void *);
void fn_800F87F0(void *, void *, Self *);

s32 fn_801CC780(Self *self, void *a, Parser *parser, void *d) {
    u8 buf16[16];
    u8 buf8[8];
    u32 tok;

    if (self->f4 != 0) {
        self->v6();
    }
    self->f0 = a;
    parser->v5();
    fn_800FB064(parser, buf16);
    fn_800FB064(parser, buf8);
    fn_800FAEF8(parser);
    if (lbl_8035A9F4 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035A9F4);
    self->f64 = new char[8];
    fn_800F7E98();
    if (self->f64 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    self->f64[0] = 0;
    fn_800F6E88(self->f64, buf8);
    while ((tok = parser->v5()) != 6) {
        switch (tok) {
        case 58:
            fn_80121CE8(self->f20, parser);
            break;
        case 103:
            self->f56 = 1;
            break;
        }
    }
    self->f36 = fn_801AAA5C(self->f0, buf16, buf8);
    fn_800F87F0(d, buf16, self);
    self->f4 = 1;
    return 0;
}

} /* extern "C" */
