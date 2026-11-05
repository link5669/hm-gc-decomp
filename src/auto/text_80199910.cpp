/* Functions from 0x80199910 to 0x80199A98, found by decomp-toolkit. */
#include "common.h"

extern "C" {


typedef struct {
    f32 x, y, z, w;
} Plane;

typedef struct Pl80199910 { f32 x, y, z, w; } Pl80199910;
typedef struct Fr80199910 { Pl80199910 *p; s32 n; } Fr80199910;
s32 fn_80199910(const Fr80199910 *f, const Pl80199910 *s) {
    Pl80199910 *p = f->p;
    Pl80199910 *end = p + f->n;
    for (; p < end; p++) {
        if (p->w + (s->x * p->x + s->y * p->y + s->z * p->z) < -s->w) {
            return 0;
        }
    }
    return 1;
}

void fn_8019998C(void *arg0, s32 arg1, s32 arg2) {
    *(s32 *)((u8 *)arg0 + 0) = arg1;
    *(s32 *)((u8 *)arg0 + 4) = arg2;
}

void fn_80199998(void *arg0, const void *arg1, void *arg2) {
    extern f32 lbl_80330648[];
    extern Plane lbl_80330654;
    lbl_80330648[0] = M2C_FIELD(arg1, f32 *, 96);
    lbl_80330648[1] = M2C_FIELD(arg1, f32 *, 100);
    lbl_80330648[2] = M2C_FIELD(arg1, f32 *, 104);
    M2C_FIELD(arg0, void **, 0) = arg2;
    M2C_FIELD(arg0, s32 *, 4) = 4;
    {
        Plane *p = &lbl_80330654;
        p->x = M2C_FIELD(arg1, f32 *, 16);
        p->y = M2C_FIELD(arg1, f32 *, 20);
        p->z = M2C_FIELD(arg1, f32 *, 24);
        p->w = M2C_FIELD(arg1, f32 *, 28);
    }
    {
        Plane *p = (Plane *)((char *)M2C_FIELD(arg0, void **, 0) + 0);
        p->x = M2C_FIELD(arg1, f32 *, 32);
        p->y = M2C_FIELD(arg1, f32 *, 36);
        p->z = M2C_FIELD(arg1, f32 *, 40);
        p->w = M2C_FIELD(arg1, f32 *, 44);
    }
    {
        Plane *p = (Plane *)((char *)M2C_FIELD(arg0, void **, 0) + 16);
        p->x = M2C_FIELD(arg1, f32 *, 64);
        p->y = M2C_FIELD(arg1, f32 *, 68);
        p->z = M2C_FIELD(arg1, f32 *, 72);
        p->w = M2C_FIELD(arg1, f32 *, 76);
    }
    {
        Plane *p = (Plane *)((char *)M2C_FIELD(arg0, void **, 0) + 32);
        p->x = M2C_FIELD(arg1, f32 *, 48);
        p->y = M2C_FIELD(arg1, f32 *, 52);
        p->z = M2C_FIELD(arg1, f32 *, 56);
        p->w = M2C_FIELD(arg1, f32 *, 60);
    }
    {
        Plane *p = (Plane *)((char *)M2C_FIELD(arg0, void **, 0) + 48);
        p->x = M2C_FIELD(arg1, f32 *, 80);
        p->y = M2C_FIELD(arg1, f32 *, 84);
        p->z = M2C_FIELD(arg1, f32 *, 88);
        p->w = M2C_FIELD(arg1, f32 *, 92);
    }
    M2C_FIELD(arg0, s32 *, 8) = 0;
}

void __ct__9C80199A84Fv(void *arg0) {
    *(u32 *)((u8 *)arg0 + 0) = 0;
    *(u32 *)((u8 *)arg0 + 4) = 0;
    *(u32 *)((u8 *)arg0 + 8) = 0;
}


} /* extern "C" */
