// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { f32 x, y, z; } Vec3;
} /* extern "C" */
struct VObj {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(Vec3 *, Vec3 *, Vec3 *, Vec3 *, int);
};
extern "C" {
void fn_80107244(void *, Vec3 *);
void fn_801074D0(void *, Vec3 *, Vec3 *, Vec3 *);
void fn_80101414(Vec3 *, Vec3 *, f32);
void fn_8023FE08(void *, f32);

struct P { u8 pad[400]; s32 f400; u8 pad2[12]; void *f416; u8 pad3[12]; VObj *f432; VObj *f436; u8 pad4[4]; f32 f444; };

static inline void helper(P *p, VObj *o) {
    Vec3 a, c, b, d;
    fn_80107244(p->f416, &a);
    fn_801074D0(p->f416, &b, &c, &d);
    c.x = -c.x; c.y = -c.y; c.z = -c.z;
    b.x = -b.x; b.y = -b.y; b.z = -b.z;
    fn_80101414(&c, &b, p->f444);
    fn_80101414(&d, &b, p->f444);
    o->v14(&a, &c, &d, &b, 0);
}

void fn_8009829C(P *p, f32 x) {
    VObj *o;
    o = p->f436;
    if (o) helper(p, o);
    if (p->f400 != 0) {
        o = p->f432;
        if (o) helper(p, o);
    }
    fn_8023FE08(p, x);
}

} /* extern "C" */
