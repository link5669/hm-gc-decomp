// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } V3_86934;
typedef struct { f32 x, y, z, w; } Q4_86934;
typedef struct { u8 pad[16]; void *f16; u8 pad2[12]; u32 f32; } B86934;
typedef struct { u8 pad[48]; B86934 *f48; } A86934;
typedef struct { u8 pad[8]; Q4_86934 q; } R86934;
typedef struct {
    u8 pad[156]; R86934 *f156; u8 pad2[560]; s32 f720; s32 f724; u8 pad3[16]; A86934 *f744; u8 pad4[164]; f32 f912;
} P86934;
extern f32 lbl_8035FDF8;
extern volatile f32 lbl_8035FE40;
extern u32 lbl_8035FDF0;
extern void *lbl_803286D0[];
void fn_8005E77C(P86934 *, void *);
void fn_80190C98(A86934 *);
void fn_80100CF4(Q4_86934 *);
void fn_80233030(P86934 *, void *);
void fn_80086934(P86934 *p, void *a) {
    volatile V3_86934 v;
    Q4_86934 q;
    A86934 *o;
    B86934 *b;
    p->f720 = 3;
    p->f724 = 1;
    fn_8005E77C(p, a);
    { f32 k = lbl_8035FDF8; v.x = k; v.y = k; v.z = lbl_8035FE40; }
    o = p->f744;
    if (o != 0) {
        b = o->f48;
        if (b != 0) {
            ((void (*)(void *, V3_86934 *))lbl_803286D0[3])(b->f16, (V3_86934 *)&v);
            b->f32 |= lbl_8035FDF0;
            fn_80190C98(o);
        }
    }
    fn_80100CF4(&q);
    q = p->f156->q;
    p->f912 = q.w;
    fn_80233030(p, a);
}

} /* extern "C" */
