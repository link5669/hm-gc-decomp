#include "common.h"
extern "C" {
struct EV;
struct V { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11(); virtual void m(void *); };
struct H2 { V *v; }; struct H1 { u8 pad[4]; H2 *h; };
struct P { u8 pad[1340]; s32 f1340; u8 pad2[4]; s32 f1348; u8 pad3[4]; H1 *f1356; void *f1360; s32 f1364; H1 *f1368; void *f1372; void ev(EV *); };
typedef void (P::*PM)(EV *);

static const struct { char pad[176]; char s[8][12]; } S = {{77, 117, 115, 105, 99, 68, 97, 116, 97, 98, 97, 115, 101, 0, 0, 0, 77, 117, 115, 105, 99, 69, 118, 101, 110, 116, 0, 0, 83, 101, 97, 114, 99, 104, 105, 110, 103, 0, 0, 0, 82, 111, 111, 109, 67, 108, 101, 97, 114, 0, 0, 0, 82, 111, 111, 109, 67, 108, 101, 97, 114, 82, 101, 116, 117, 114, 110, 0, 83, 112, 101, 99, 105, 97, 108, 49, 0, 0, 0, 0, 83, 112, 101, 99, 105, 97, 108, 50, 0, 0, 0, 0, 83, 112, 101, 99, 105, 97, 108, 51, 0, 0, 0, 0, 83, 112, 101, 99, 105, 97, 108, 52, 0, 0, 0, 0, 83, 112, 101, 99, 105, 97, 108, 53, 0, 0, 0, 0, 71, 109, 83, 111, 77, 117, 115, 105, 99, 77, 97, 110, 97, 103, 101, 114, 0, 0, 0, 0, 65, 116, 69, 118, 83, 117, 98, 115, 99, 114, 105, 98, 101, 114, 0, 0, 71, 109, 66, 97, 79, 98, 106, 101, 99, 116, 0, 0}, {"M_STOPSC", "M_STOPSR", "M_STOPS1", "M_STOPS2", "M_STOPS3", "M_STOPS4", "M_STOPS5", "M_AMBSND"}};

extern void *lbl_8035B65C;
extern char lbl_80366D08[]; extern char lbl_80366D10[]; extern char lbl_80366D18[]; extern char lbl_80366D20[]; extern char lbl_80366D28[]; extern char lbl_80366D30[]; extern char lbl_80366D38[]; extern char lbl_80366D40[];
extern char lbl_80366D54[0x7];
extern char lbl_80366D5C[0x7];
extern char lbl_80366D64[0x7];
extern char lbl_80366D6C[0x8];
extern char lbl_80366D74[0x8];
extern char lbl_80366D7C[0x8];
extern char lbl_80366D84[0x8];
extern char lbl_80366D8C[0x8];
struct T12 { s32 a, b; void *f; };
void fn_80268B08(void);
static struct { void *pad[150]; T12 t[16]; } D = {{0, (void *)0x28u, 0, 0, (void *)0x28u, 0, 0, (void *)0x28u, 0, 0, (void *)0x3f800000u, 0, 0, 0, 0, 0, (void *)0x40000000u, 0, (void *)0x3f800000u, (void *)0x3f800000u, 0, (void *)0xbf800000u, (void *)0x3f800000u, 0, 0, (void *)0x3f800000u, (void *)0x3f800000u, 0, (void *)0x3f800000u, (void *)0xbf800000u, 0, (void *)0x6u, (void *)0x9u, (void *)0xcu, (void *)0xfu, (void *)0x12u, (void *)0x15u, (void *)0x18u, (void *)0x1bu, 0, (void *)0x6u, (void *)0x9u, (void *)0xcu, (void *)0xfu, (void *)0x12u, (void *)0x15u, (void *)0x18u, (void *)0x1bu, 0, (void *)0x6u, (void *)0x40u, (void *)0x43u, (void *)0x46u, (void *)0x49u, (void *)0x4cu, (void *)0x4fu, (void *)0x52u, (void *)0x55u, (void *)0x1eu, (void *)0x21u, (void *)0x24u, (void *)0x27u, (void *)0x2au, (void *)0x2du, (void *)0x30u, (void *)0x33u, (void *)0x3au, (char *)&S + 0, (void *)0x3bu, (char *)&S + 16, (void *)0x3cu, (void *)lbl_80366D08, (void *)0x3du, (void *)lbl_80366D10, (void *)0x3eu, (void *)lbl_80366D18, (void *)0x3fu, (void *)lbl_80366D20, (void *)0x40u, (char *)&S + 28, (void *)0x41u, (char *)&S + 40, (void *)0x42u, (char *)&S + 52, (void *)0x43u, (char *)&S + 68, (void *)0x44u, (char *)&S + 80, (void *)0x45u, (char *)&S + 92, (void *)0x46u, (char *)&S + 104, (void *)0x47u, (char *)&S + 116, (void *)0x49u, (void *)lbl_80366D28, (void *)0x4au, (void *)lbl_80366D30, (void *)0x4bu, (void *)lbl_80366D38, (void *)0x48u, (void *)lbl_80366D40, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u, 0, (void *)0xffffffffu, (void *)0x80268b08u}, {{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08},{0,-1,(void*)fn_80268B08}}};
void fn_80253AD8(void *, P *, T12 *, const char *);
static inline void Reg(P *p, volatile T12 *q, const char *n) {
    volatile T12 v;
    { u32 x, y, z; x = q->a; y = q->b; z = (u32)q->f; v.a = x; v.b = y; v.f = (void *)z; }
    fn_80253AD8(*(void *volatile *)&lbl_8035B65C, p, (T12 *)&v, n);
}
void fn_80268DCC(void *pp) {
    P *p = (P *)pp;
    const char *str = (const char *)&S;
    char *d = (char *)&D;
    Reg(p, (T12 *)(d + 600), lbl_80366D54);
    Reg(p, (T12 *)(d + 612), lbl_80366D5C);
    Reg(p, (T12 *)(d + 624), lbl_80366D64);
    Reg(p, (T12 *)(d + 636), lbl_80366D6C);
    Reg(p, (T12 *)(d + 648), lbl_80366D74);
    Reg(p, (T12 *)(d + 660), lbl_80366D7C);
    Reg(p, (T12 *)(d + 672), lbl_80366D84);
    Reg(p, (T12 *)(d + 684), lbl_80366D8C);
    Reg(p, (T12 *)(d + 696), str + 176);
    Reg(p, (T12 *)(d + 708), str + 188);
    Reg(p, (T12 *)(d + 720), str + 200);
    Reg(p, (T12 *)(d + 732), str + 212);
    Reg(p, (T12 *)(d + 744), str + 224);
    Reg(p, (T12 *)(d + 756), str + 236);
    Reg(p, (T12 *)(d + 768), str + 248);
    Reg(p, (T12 *)(d + 780), str + 260);
    if (p->f1360) {
        p->f1356->h->v->m(p->f1360);
        p->f1360 = 0;
    }
    if (p->f1372) {
        p->f1368->h->v->m(p->f1372);
        p->f1372 = 0;
    }
    p->f1348 = 0;
    p->f1340 = 1;
    p->f1356 = 0;
    p->f1360 = 0;
    p->f1364 = 0;
    p->f1368 = 0;
    p->f1372 = 0;
}
}
