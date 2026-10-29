// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct O16 { u8 pad[8]; u32 fl; u8 pad12[24]; struct { u8 pad[4]; u32 a4; } *o36; };
struct O456 { u8 pad[326]; u16 a326; };
struct P {
    virtual void v0(); virtual s32 s1();
    f32 t4;
    f32 t8;
    f32 t12;
    O16 *o16;
    u8 pad20[8];
    u8 fl;
    u8 pad29[7];
    u32 a36;
    u8 pad40[112];
    u8 s152[4];
    u32 a156;
    u8 pad160[56];
    u32 a216;
    u8 pad220[224];
    u32 a444;
    u16 a448;
    u8 pad450[6];
    O456 *o456;
};
extern f32 lbl_80365718, lbl_8036571C;
void fn_80206888(u8 *);
void fn_802037C4(u8 *);
void fn_80205330(u8 *);
void fn_802025B8(P *, int);
void fn_80204DB0(u8 *);
void fn_8020685C(u8 *);

void fn_80201F68(P *p, f32 dt) {
    u8 fl;
    p->t4 += dt;
    fl = p->fl;
    if (fl & 2) {
        if (p->t4 >= p->t12) {
            u32 t = p->o16->fl;
            if (t & 0x400) {
                if (t & 0x80) {
                    fn_80206888(p->s152);
                    p->a156 = p->a36;
                } else {
                    fn_802037C4(p->s152);
                    p->a156 = p->a36;
                }
            } else if (t & 0x800) {
                p->fl = fl | 8;
                p->a444 = p->a36;
                fn_80205330(p->s152);
                p->a216 = p->o16->o36->a4;
            }
            p->fl |= 1;
            p->fl &= ~2;
            p->fl &= ~2;
        }
    } else if (fl & 4) {
        u32 t = p->o16->fl;
        if (t & 0x400) {
            if (p->t4 >= p->t8) {
                fn_802025B8(p, 0);
                p->fl &= ~4;
            }
        } else if (t & 0x800) {
            if (p->o456->a326 == 0) {
                fn_802025B8(p, 0);
            } else {
                f32 f = p->t8;
                if (!(f >= lbl_80365718 && f <= lbl_8036571C) && p->t4 >= f) {
                    fn_802025B8(p, 0);
                    p->fl &= ~4;
                } else {
                    fn_80204DB0(p->s152);
                }
            }
        }
    } else if (fl) {
        if (!p->s1()) {
            fn_802025B8(p, 0);
        } else {
            u32 t = p->o16->fl;
            if (!(t & 0x400) && (t & 0x800)) {
                fn_80204DB0(p->s152);
                if ((p->a448 & 1) && (p->fl & 8)) p->fl &= ~8;
            }
            t = p->o16->fl;
            if ((t & 0x80) && (t & 0x400)) fn_8020685C(p->s152);
        }
    }
}

} /* extern "C" */
