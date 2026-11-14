// fn_801A8C24: UI list key handler (jump to item by first letter). NonMatching: instructions identical, callee-saved register colouring differs (DIFF 114 SDIFF 0; p/a now r30/r29 vs target r26/r27, key/kl swapped).
#include "common.h"

extern "C" {

struct Sub { u8 pad[0x24]; void *f24; };
struct ChO { u8 pad[0xc]; virtual u16 ch(s32); };
struct Ent { ChO *f0; s32 f4; u32 f8; };
struct Arr { u8 pad[0xc]; s32 *fc; };
struct Own { u8 pad[0x68]; void *f68; u32 pad6c; void *f70; };
struct It {
    u8 pad0[0x6c]; s32 f6c; u8 pad70[0x80 - 0x70];
    virtual void w0();
    virtual void w1();
    virtual void w2();
    virtual void w3();
    virtual void w4();
    virtual void w5();
    virtual void w6();
    virtual void w7();
    virtual void w8();
    virtual void w9();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual void w18();
    virtual void w19();
    virtual void v58(s32);
    virtual void w21();
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w30();
    virtual void w31();
    virtual void w32();
    virtual void w33();
    virtual void w34();
    virtual void w35();
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void w40();
    virtual void w41();
    virtual void w42();
    virtual void w43();
    virtual void w44();
    virtual void w45();
    virtual void w46();
    virtual void w47();
    virtual void w48();
    virtual void w49();
    virtual void w50();
    virtual void w51();
    virtual void w52();
    virtual void w53();
    virtual void w54();
    virtual void w55();
    virtual void w56();
    virtual void w57();
    virtual void vf0(s32, s32);
    virtual void vf4(s32, s32);
    virtual void w60();
    virtual void w61();
    virtual void w62();
    virtual void w63();
    virtual void w64();
    virtual void w65();
    virtual void w66();
    virtual void w67();
    virtual void w68();
    virtual void w69();
    virtual void w70();
    virtual void w71();
    virtual void sel(s32);
    u8 pad84[0x144 - 0x84]; u32 f144; u8 pad148[0x188 - 0x148]; s32 f188; u8 pad18c[0x1b8 - 0x18c]; Own **f1b8; Ent *f1bc; u8 pad1c0[0x1d4 - 0x1c0]; Arr *f1d4;
};
struct Lo {
    virtual void w0();
    virtual void w1();
    virtual void w2();
    virtual void w3();
    virtual void w4();
    virtual void w5();
    virtual void w6();
    virtual void w7();
    virtual void w8();
    virtual void w9();
    virtual void w10();
    virtual void w11();
    virtual void w12();
    virtual void w13();
    virtual void w14();
    virtual void w15();
    virtual void w16();
    virtual void w17();
    virtual void w18();
    virtual void w19();
    virtual void w20();
    virtual void w21();
    virtual void w22();
    virtual void w23();
    virtual void w24();
    virtual void w25();
    virtual void w26();
    virtual void w27();
    virtual void w28();
    virtual void w29();
    virtual void w30();
    virtual void w31();
    virtual void w32();
    virtual void w33();
    virtual s32 hit(void *, s32, s32);
};
struct N { Lo *obj; s32 on; N *next; };
struct P { u8 pad[0x6c]; u32 f6c; u8 pad70[0x88 - 0x70]; N *f88; u8 pad8c[0x144 - 0x8c]; s32 f144; u8 pad148[0x164 - 0x148]; s32 f164; u8 pad168[0x170 - 0x168]; It *f170; It *f174; It *f178; };
void fn_801CCB84(void *, s32 *, Sub **, void *);
void fn_801B4B40(It *, s32);

inline s32 IsSel(It *o) {
    u8 b = 0;
    u16 t = o->f144;
    if (t == 8 || t == 4 || t == 0x20 || t == 0x80 || t == 0x200) b = 1;
    return b;
}
inline s32 Bit1(It *o) { int v = (o->f6c >> 1) & 1; return v; }
inline void Set1(It *q) { int v = Bit1(q); if (!v) q->f6c |= 2; }
inline s32 IsFoc(It *o) {
    u16 t = o->f144;
    if (t == 0x10 || t == 0x20 || t == 0x40 || t == 0x80) return 1;
    return 0;
}

#pragma push
#pragma opt_propagation off
s32 fn_801A8C24(void *pv, u32 av, u32 bv) {
P *p = (P *)pv;
s32 a = av;
s32 b = bv;
N *n;
s32 r = 0;
    for (n = p->f88; n != NULL; n = n->next) {
        if (n->on != 0 && n->obj->hit(p, a, b) == 0) r = 1;
    }
    if (r != 0) return 0;
    if (!(p->f6c & 2)) return 0;
    if (p->f164 != 0) {
        switch (p->f144) {
        case 8: case 0x20: case 0x40: case 0x80:
            if (!IsFoc(p->f174)) p->f174->vf4(b, 1);
            if (!IsSel(p->f174)) p->f174->sel(1);
            p->f174->vf0(a, b);
            break;
        }
    } else {
        It *o;
        s32 i;
        s32 cnt;
        s32 kl;
        u32 key;
        s32 start;
        key = (u16)a;
        kl = key | 0x20;
        o = p->f170;
        cnt = o->f188 - 1;
        start = o->f1d4->fc[0];
        for (i = start + 1; i != start; i++) {
            if (i > cnt) i = 0;
            It *q = p->f170;
            s32 c = 0;
            Sub *s;
            ChO *x;
            Ent *t = q->f1bc;
            if (t) {
                x = t[i].f0;
            } else {
                fn_801CCB84(q->f1b8[i]->f70, &c, &s, q->f1b8[i]->f68);
                if (!s) x = 0;
                else x = (ChO *)s->f24;
            }
            s32 ch = (u16)x->ch(0);
            if (key >= 'a' && key <= 'z') {
                if (kl == (ch | 0x20)) {
                    fn_801B4B40(p->f170, i);
                if (!(p->f170->f6c & 1)) p->f170->v58(1);
                Set1(p->f170);
                if (!IsFoc(p->f170)) p->f170->vf4(b, 1);
                if (!IsSel(p->f170)) p->f170->sel(1);
                    break;
                }
            } else if ((u16)a == (u16)ch) {
                fn_801B4B40(p->f170, i);
                if (!(p->f170->f6c & 1)) p->f170->v58(1);
                Set1(p->f170);
                if (!IsFoc(p->f170)) p->f170->vf4(b, 1);
                if (!IsSel(p->f170)) p->f170->sel(1);
                break;
            }
        }
    }
    return 0;
}
#pragma pop

}
