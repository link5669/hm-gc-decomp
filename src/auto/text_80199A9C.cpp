// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } Vec;
} /* extern "C" */
struct Body199 {
    u8 pad[88];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23(); virtual void v24();
    virtual void SetPos(Vec *p);
    virtual void SetVel(Vec *p);
};
struct Body199b : Body199 {
    f32 x, y, z;
};
extern "C" {
typedef struct {
    u32 flags;
    u8 pad4[44];
    void *f48;
    u8 pad52[56];
    Body199b *body;
} Self199;
void fn_80190DFC(Self199 *self, f32 dt);
void fn_80107244(void *p, Vec *out);
extern f32 lbl_80364C80;
extern f32 lbl_80364C84;
extern f32 lbl_80364C88;
extern f32 lbl_80364C8C;

void fn_80199A9C(Self199 *self, f32 dt) {
    Vec pos;
    Vec vel;
    f32 ox, oy, oz;
    f32 inv;
    if (self->body != 0) {
        fn_80190DFC(self, dt);
        ox = self->body->x;
        oy = self->body->y;
        oz = self->body->z;
        if (self->f48 != 0) {
            fn_80107244(self->f48, &pos);
        } else {
            pos.x = lbl_80364C80;
            pos.y = lbl_80364C80;
            pos.z = lbl_80364C80;
        }
        self->body->SetPos(&pos);
        if (self->flags & 0x800) {
            self->flags &= ~0x800;
        } else {
            if (!(dt >= lbl_80364C84 && dt <= lbl_80364C88)) {
                volatile Vec *vp = &vel;
                f32 dx, dy, dz;
                dx = pos.x - ox;
                dy = pos.y - oy;
                dz = pos.z - oz;
                vp->x = dx;
                vp->y = dy;
                vp->z = dz;
                inv = *(volatile f32 *)&lbl_80364C8C / dt;
                vp->x = dx * inv;
                vp->y = dy * inv;
                vp->z = dz * inv;
            } else {
                vel.x = lbl_80364C80;
                vel.y = lbl_80364C80;
                vel.z = lbl_80364C80;
            }
            self->body->SetVel(&vel);
        }
    }
}

} /* extern "C" */
