// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O5CC4C {
    u8 pad0[104];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void m11(f32 dt);
};
extern "C" {
typedef struct { f32 x, y, z; } Vec5CC4C;
typedef struct { u8 pad[12]; Vec5CC4C *f12; } B5CC4C;
typedef struct { O5CC4C o; u8 pad108[12]; void *f120; } Obj5CC4C;
typedef struct {
    u8 pad0[68];
    u8 f68[592];
    void *f660;
    u8 pad664[4];
    B5CC4C *f668;
    f32 *f672;
    f32 *f676;
    u8 pad680[48];
    Obj5CC4C *f728[10];
    s32 f768;
    u8 pad772[4];
    u8 *f776;
    f32 f780;
} P5CC4C;
extern u8 lbl_803286D0[];
extern u32 lbl_8035E468;
extern f32 lbl_8035E484;
void fn_80190C98(void *);
void fn_80107F3C(void *, Vec5CC4C *);
void fn_80230928(P5CC4C *, f32);
inline void sub5CC4C(u8 *q, void *arg) {
    u8 *r = *(u8 **)(q + 0x30);
    if (r != NULL) {
        (*(void (**)(void *, void *))(lbl_803286D0 + 0xC))(*(void **)(r + 0x10), arg);
        *(u32 *)(r + 0x20) |= lbl_8035E468;
        fn_80190C98(q);
    }
}
void fn_8005CC4C(P5CC4C *p, f32 dt) {
    u8 *q;
    u8 *r;
    s32 i;
    q = p->f776;
    if (q != NULL) {
        r = *(u8 **)(q + 0x30);
        if (r != NULL) {
            (*(void (**)(void *, void *))(lbl_803286D0 + 0xC))(*(void **)(r + 0x10), p->f68);
            *(u32 *)(r + 0x20) |= lbl_8035E468;
            fn_80190C98(q);
        }
    }
    for (i = 0; i < p->f768; i++) {
        if (p->f728[i] != 0) {
            if (p->f672 != 0 && p->f676 != 0 && p->f780 < *p->f676) {
                p->f780 = p->f780 + dt;
                if (p->f780 > *p->f676) p->f780 = *p->f676;
                {
                    Vec5CC4C out;
                    Vec5CC4C *v;
                    f32 x;
                    f32 z;
                    f32 y;
                    f32 a;
                    f32 t;
                    a = *p->f672;
                    t = a + p->f780 * ((lbl_8035E484 - a) / *p->f676);
                    v = p->f668->f12;
                    x = v->x;
                    z = v->z;
                    y = v->y;
                    out.x = t * x;
                    out.y = t * y;
                    out.z = t * z;
                    if (p->f728[i]->f120 != 0) fn_80107F3C(p->f728[i]->f120, &out);
                }
            }
            p->f728[i]->o.m11(dt);
        }
    }
    fn_80230928(p, dt);
}

} /* extern "C" */
