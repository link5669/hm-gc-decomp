// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct C800322B0 {
    s32 a;
    s32 b;
    s32 c;
    C800322B0() { a = 0; c = 0; b = 0; }
    ~C800322B0() {}
};
struct A801E24A8 {
    u8 pad[20];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void Upd(f32); virtual void v6(); virtual void v7();
    virtual void Fa();
};
struct B801E24A8 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void Upd(f32); virtual void v6();
    virtual void Fb();
};
struct NA801E24A8 { NA801E24A8 *next; u32 f4; A801E24A8 *obj; };
struct NB801E24A8 { NB801E24A8 *next; u32 f4; B801E24A8 *obj; };
struct St801E24A8 { u32 flags; u8 pad[44]; u32 f30; };
struct EntBase801E24A8 {
    u8 pad[104];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void Upd(f32);
};
struct Ent801E24A8 : EntBase801E24A8 { u8 pad108[68]; St801E24A8 *st; };
struct Obj801E24A8 {
    u8 pad0[12];
    f32 f12;
    u8 pad10[4];
    Ent801E24A8 *ent;
    u8 pad18[8];
    NA801E24A8 *listA;
    u8 pad24[32];
    void *f44;
    NB801E24A8 *listB;
    u8 pad4c[12];
    NB801E24A8 *listC;
    u8 pad5c[24];
    s32 f74;
};
extern f32 lbl_803652D0;
void fn_801089F0(void *, C800322B0 *);

static inline void Deact(Obj801E24A8 *o) {
    {
            C800322B0 m2;
            NA801E24A8 *na;
            NB801E24A8 *nb;
            na = o->listA;
            nb = o->listB;
            if (o->f74 != 0) {
                o->f74 = 0;
                for (; na != 0; na = na->next) {
                    na->obj->Fa();
                }
                for (; nb != 0; nb = nb->next) {
                    nb->obj->Fb();
                }
                if (o->ent != 0 && (o->ent->st->f30 & 1)) {
                    o->ent->st->flags &= ~2;
                }
            }
            if (o->ent != 0) {
                o->ent->st->f30 &= ~1;
            }
        }
}
static inline void Stop(Obj801E24A8 *o) {
    C800322B0 m;
    if (o->f74 != 0) {
        if (o->f44 != 0) {
            m.b = 1;
            m.a = (s32)o->f44;
            fn_801089F0(o->f44, &m);
        }
        Deact(o);
    }
}

void fn_801E24A8(Obj801E24A8 *o, f32 dt) {
    NA801E24A8 *na = o->listA;
    NB801E24A8 *nc = o->listC;
    if (o->f12 < dt) o->f12 = dt;
    if (o->f74 != 0) {
        if (o->ent != 0) o->ent->Upd(dt);
        for (; na != 0; na = na->next) na->obj->Upd(dt);
        for (; nc != 0; nc = nc->next) nc->obj->Upd(dt);
        o->f12 -= dt;
        if (o->f12 <= lbl_803652D0) Stop(o);
    }
}

} /* extern "C" */
