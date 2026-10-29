// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O801CDEC0 {
    u8 pad[16];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8(f32);
    virtual void v9();
    virtual void v10();
};
extern "C" {
typedef struct E801CDEC0 {
    O801CDEC0 *obj;
    u8 pad[24];
} E801CDEC0;
typedef struct S801CDEC0 {
    s32 f0;
    E801CDEC0 *f4;
    u32 f8;
    u8 padc[12];
    u32 *f24;
} S801CDEC0;

static inline void call8(O801CDEC0 *o, f32 f) {
    if (o != 0) o->v8(f);
}

void fn_801CDEC0(S801CDEC0 *p, u32 mask, f32 f) {
    u32 i;
    for (i = 0; i < p->f8; i++) {
        O801CDEC0 *o = p->f4[i].obj;
        if (o != 0) {
            u32 fl = p->f24[i];
            u32 fh = fl & 0xFFFF0000;
            if ((mask & 0xFFFF0000) == fh || fh == 0) {
                if (((mask & 0xFFFF) & fl) != 0 || (fl & 0x4000) != 0) {
                    call8(o, f);
                }
            }
        }
    }
    if (p->f0 != 0) {
        for (i = 0; i < p->f8; i++) {
            O801CDEC0 *o = p->f4[i].obj;
            if (o != 0) o->v10();
        }
    }
}

} /* extern "C" */
