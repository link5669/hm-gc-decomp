// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct V3 { f32 x, y, z; };
struct U { u8 pad[104]; virtual void u0(); virtual void u1(); virtual void u2(); virtual void u3(); virtual void u4(); virtual void u5(); virtual void u6(); virtual void u7(); virtual void u8_(); virtual void u9(); virtual void u10(); virtual void upd(f32 dt);
    u8 pad2[120 - 108]; void *f120; };
struct X { u8 pad[16]; void *f16; u8 pad2[12]; u32 f32_; };
struct E { u32 f0; u8 pad[44]; X *x; };
struct T { virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3(); virtual void t4(); virtual void t5(); virtual void t6(); virtual void t7(); virtual void t8(); virtual void t9(); virtual void t10(); virtual void t11(); virtual void t12();
    virtual void getDir(V3 *, s32, V3 *, s32, s32); virtual void setPos(V3 *, s32, s32, s32, s32);
    u8 pad[68 - 4]; u8 f68[280 - 68]; V3 vel; u8 pad1[620 - 292]; s32 f620; u8 pad2[728 - 624]; f32 s[3]; U *u0; U *u1; E *e; u8 pad3[840 - 752]; f32 f840; u8 pad4[852 - 844]; f32 f852; u8 pad5[860 - 856]; f32 f860;
    u8 pad6[912 - 864]; f32 *amp; f32 *freq; s32 f920; f32 f924; V3 pos; };
struct FT { void *a, *b, *c; void (*f)(void *, void *); };
extern "C" {
extern FT lbl_803286D0;
extern T *lbl_8035A1A8;
extern u32 lbl_8035FDC0;
extern const f32 lbl_8035FDC4, lbl_8035FDC8; extern volatile f32 lbl_8035FDCC, lbl_8035FDD0;
void fn_8005E354(T *t, f32 dt);
void fn_80230928(T *t, f32 dt);
void fn_80190C98(E *e);
void fn_80107F3C(void *p, f32 *s);
f64 fn_800F030C(f32);
void fn_8005E6BC(T *, f32);
void fn_8005E00C(T *, f32);

void fn_8008553C(T *t, f32 dt) {
    if (t->f620) {
        E *e;
        X *x;
        f32 r;
        V3 a, b;
        t->pos.x = dt * t->vel.x + t->pos.x;
        t->pos.y = dt * t->vel.y + t->pos.y;
        t->pos.z = dt * t->vel.z + t->pos.z;
        fn_8005E354(t, dt);
        fn_80230928(t, dt);
        if (t->u0) t->u0->upd(dt);
        if (t->u1) t->u1->upd(dt);
        if (t->f840 < t->f860) r = t->f840 / t->f860; else r = lbl_8035FDC4;
        if (r < lbl_8035FDC8) r = lbl_8035FDC8;
        t->s[0] = t->f852 * r;
        t->s[1] = t->f852 * r;
        t->s[2] = t->f852 * r;
        t->getDir(&a, 0, &b, 0, 0);
        {
            f32 ph = *t->freq * (lbl_8035FDCC * (t->f840 + t->f924));
            f32 k;
            while (ph > lbl_8035FDD0) ph -= lbl_8035FDCC;
            k = *t->amp * (f32)fn_800F030C(ph);
            a.x = k * b.x + t->pos.x;
            a.y = k * b.y + t->pos.y;
            a.z = k * b.z + t->pos.z;
        }
        t->setPos(&a, 0, 0, 0, 0);
        if (t->u0 && t->u0->f120) fn_80107F3C(t->u0->f120, t->s);
        if (t->u1 && t->u1->f120) fn_80107F3C(t->u1->f120, t->s);
        t->f840 = t->f840 + dt;
        if (!t->f920 && (e = t->e) && lbl_8035A1A8 == t && (x = e->x)) {
            lbl_803286D0.f(x->f16, t->f68);
            x->f32_ |= lbl_8035FDC0;
            fn_80190C98(e);
        }
    }
    fn_8005E6BC(t, dt);
    fn_8005E00C(t, dt);
}

} /* extern "C" */
