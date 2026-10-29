// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct P801DE24C {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void Error(s32 code);
    virtual u32 Next();
};
struct V801DE24C {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void Reset();
};
extern "C" {
void fn_800FAEF8(P801DE24C *parser);
void fn_800FB064(P801DE24C *parser, char *buf);
void fn_800F87F0(void *d, char *buf, void *self);
u32 fn_800F9398(void *p, char *buf);
u32 fn_800F9788(void *p, char *a, char *b);
f32 fn_800FB2E0(P801DE24C *parser);
void fn_80121CE8(void *p, P801DE24C *parser);

static inline BOOL IsEmpty801DE24C(const char *s) {
    return s == 0 || s[0] == 0;
}

s32 fn_801DE24C(u8 *self, u8 *a, P801DE24C *parser, void *d) {
    char name[8];
    char buf[16];
    u32 tok;
    u32 r;
    u8 *o;

    if (M2C_FIELD(self, s32 *, 4) != 0) {
        ((V801DE24C *)self)->Reset();
    }
    M2C_FIELD(self, u8 **, 0) = a;
    M2C_FIELD(self, u32 *, 8) = M2C_FIELD(a, u32 *, 16);
    fn_800FAEF8(parser);
    while ((tok = parser->Next()) != 6) {
        switch (tok) {
        case 57:
            fn_800FB064(parser, buf);
            fn_800F87F0(d, buf, self);
            break;
        case 86:
            fn_800FB064(parser, buf);
            fn_800FB064(parser, name);
            o = M2C_FIELD(self, u8 **, 8);
            if (name == 0 || name[0] == 0) {
                r = fn_800F9398(o + 540, buf);
            } else {
                r = fn_800F9788(o + 564, name, buf);
            }
            M2C_FIELD(self, u32 *, 36) = r;
            break;
        case 72:
            M2C_FIELD(self, f32 *, 40) = fn_800FB2E0(parser);
            break;
        case 73:
            M2C_FIELD(self, f32 *, 44) = fn_800FB2E0(parser);
            break;
        case 58:
            fn_80121CE8(self + 20, parser);
            break;
        case 74:
            M2C_FIELD(self, f32 *, 48) = fn_800FB2E0(parser);
            M2C_FIELD(self, f32 *, 52) = fn_800FB2E0(parser);
            break;
        default:
            parser->Error(30);
            break;
        }
    }
    M2C_FIELD(self, s32 *, 4) = 1;
    return 0;
}

} /* extern "C" */
