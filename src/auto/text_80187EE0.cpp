// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct B80187EE0 {
    f32 data[4];
} B80187EE0;
typedef struct V3_80187EE0 {
    f32 x, y, z;
} V3_80187EE0;
} /* extern "C" */
struct S80187EE0;
struct VT80187EE0 {
    u8 pad[104];
    virtual void v0();
    virtual void v1();
    virtual void Update();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void SetA(V3_80187EE0 *v);
    virtual void SetB(V3_80187EE0 *v);
    virtual void SetC(B80187EE0 *b);
};
extern "C" {

typedef struct S80187EE0 {
    u32 w0;
    u16 h4;
    u8 pad6[2];
    f32 a[4];
    f32 b[4];
    u8 pad40[12];
    void *f52;
    u8 pad56[28];
    struct S80187EE0 *next;
    struct S80187EE0 *child;
    u8 pad92[76];
    u32 f168;
} S80187EE0;

void fn_80100CF4(B80187EE0 *b);
void fn_8018D1F4(S80187EE0 *self, f32 dt);
u32 fn_8017A16C(u32 *p, B80187EE0 *b, V3_80187EE0 *v1, V3_80187EE0 *v2, f32 dt);
void fn_8017A028(u32 *p);
void fn_80190C98(S80187EE0 *p);

void fn_80187EE0(S80187EE0 *self, f32 dt) {
    B80187EE0 b;
    V3_80187EE0 v1;
    V3_80187EE0 v2;
    u32 flags;
    S80187EE0 *p;

    fn_80100CF4(&b);
    fn_8018D1F4(self, dt);
    flags = fn_8017A16C(&self->f168, &b, &v1, &v2, dt);
    if (flags & 1) {
        ((VT80187EE0 *)self)->SetC(&b);
        for (p = self->child; p != 0; p = p->next) {
            if (p->h4 == 3 && (p->w0 & 0x40000) && p->f168 == self->f168) {
                if (self->w0 & 4) {
                    ((VT80187EE0 *)self)->Update();
                }
                p->a[0] = self->b[0];
                p->a[1] = self->b[1];
                p->a[2] = self->b[2];
                p->a[3] = self->b[3];
                p->b[0] = self->b[0];
                p->b[1] = self->b[1];
                p->b[2] = self->b[2];
                p->b[3] = self->b[3];
                p->w0 &= ~4;
            }
        }
    }
    if (self->f52 != 0) {
        if (flags & 2) {
            ((VT80187EE0 *)self)->SetA(&v1);
        }
        if (flags & 4) {
            ((VT80187EE0 *)self)->SetB(&v2);
        }
    }
    if (!(self->w0 & 0x80000)) {
        fn_8017A028(&self->f168);
        for (p = self->child; p != 0; p = p->next) {
            fn_80190C98(p);
        }
    }
}

} /* extern "C" */
