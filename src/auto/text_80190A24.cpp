// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct Seg { V a, b; };
struct R { u32 f0; Seg s; V *pa; V *pb; Seg s2; V a60; V b72; int f84; int f88; f32 f92; V d96; };
struct O { u32 f0; u8 pad4[20]; u8 f24[32]; void *f56; u8 pad60[44]; virtual void a0(); virtual void a1(); virtual void upd(); virtual void a3(); virtual void *def(); };
extern u32 lbl_80364B38;
extern O *lbl_8035AE40;
int fn_80100B10(void *, R *);
void fn_8017C824(void *, O *, void *, R *);
f32 fn_80101590(V *, V *);
void fn_80101820(V *);
int fn_801009DC(void *, int, int, f32 *, V *, V *, f32 *, int);
int fn_800FC4A0(R *, f32);
void fn_8018B500(R *, int);
void fn_80190A24(O *o, R *r, void *x) {
    if (o->f0 & 4) o->upd();
    if (r->f0 & 8) {
        r->a60 = *r->pa;
        r->b72 = *r->pb;
        r->s2.a.x = r->s.a.x;
        r->s2.a.y = r->s.a.y;
        r->s2.a.z = r->s.a.z;
        r->s2.b.x = r->s.b.x;
        r->s2.b.y = r->s.b.y;
        r->s2.b.z = r->s.b.z;
        r->f0 &= ~8;
        r->f0 |= lbl_80364B38;
    }
    lbl_8035AE40 = o;
    if (o->f56) {
        if (!fn_80100B10(o->f24, r)) return;
        if (!x) x = o->def();
        fn_8017C824(o->f56, o, x, r);
        return;
    }
    V hit;
    f32 t;
    int a = r->f84;
    int b = r->f88;
    if (r->f0 & 4) {
        r->f92 = fn_80101590(&r->s.a, &r->s.b);
        r->f0 &= ~4;
    }
    f32 len = r->f92;
    if (r->f0 & 1) {
        r->d96.x = r->b72.x - r->a60.x;
        r->d96.y = r->b72.y - r->a60.y;
        r->d96.z = r->b72.z - r->a60.z;
        fn_80101820(&r->d96);
        r->f0 &= ~1;
    }
    if (fn_801009DC(o->f24, a, b, &len, &r->d96, &hit, &t, 0) && fn_800FC4A0(r, t)) fn_8018B500(r, 1);
}

} /* extern "C" */
