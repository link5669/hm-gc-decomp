// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct X { u8 pad[36]; f32 a; f32 b; f32 c; f32 d; };
struct Ev { u32 f0; s32 type; u32 src; u32 id; union { s32 i; f32 f; } v; u8 pad[16]; };
struct Ctl { u8 pad[4]; u32 n; u8 pad2[200];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5();
    virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual X *get(u32);
    u8 q[4]; u8 f216[40]; f32 a256[4]; f32 a272[4]; };
static const s32 sT0[9] = {0, 1, 3, 3, 4, 5, 5, 7, 4};
static const s32 sT36[9] = {0, 1, 1, 3, 4, 5, 7, 7, 0};
static const f32 sT72[8] = {0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, -1.0f, -1.0f};
static const f32 sT104[8] = {-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f};
extern "C" {
extern f32 lbl_80363A68;
extern f32 lbl_80363A6C;
extern f32 lbl_80363A70;
extern f32 lbl_80328870[8];
int fn_8011814C(u8 *, Ev *, int);
void fn_8011D8A4(Ctl *, u32, int);
void fn_8011D79C(Ctl *, u32, f32);
void fn_8011D770(Ctl *, u32, f32);
static inline f32 lookup(f32 v, u32 id) {
    s32 k;
    for (k = 0; k < 8; k++) {
        if (v == lbl_80328870[k]) {
            if (id & 0x10000) return sT104[k];
            return sT72[k];
        }
    }
    return lbl_80363A68;
}
int fn_80116E1C(Ctl *c) {
    Ev ev;
    u32 i;
    for (i = 0; i < c->n; i++) {
        X *x = c->get(i);
        x->b = x->a;
        x->d = x->c;
    }
    while (fn_8011814C(c->f216, &ev, 255)) {
        switch (ev.id & 0xF0000000) {
        case 0x30000000: {
            int on;
            if (ev.type == 0) on = ev.v.i != 0;
            else on = ev.v.f != lbl_80363A68 ? 1 : 0;
            fn_8011D8A4(c, (ev.id & 0xF000FFFF) - 0x30000000, on);
            break;
        }
        case 0x40000000: {
            f32 f;
            if (ev.type == 1) {
                if ((ev.src & 0xF0000000) - 0x40000000 == 0) f = ev.v.f;
                else {
                    f = lookup(ev.v.f, ev.id);
                }
            } else {
                f32 g = ev.v.i == 0 ? lbl_80363A68 : lbl_80363A70;
                f = g;
                if (ev.id & 0x10000) f = -g;
            }
            fn_8011D79C(c, (ev.id & 0xF000FFFF) - 0x40000000, f);
            break;
        }
        case 0x50000000: {
            u32 idx = (ev.id & 0xF000FFFF) - 0x50000000;
            f32 f;
            if (ev.type == 1) {
                if ((ev.src & 0xF0000000) - 0x50000000 == 0) f = ev.v.f;
                else {
                    u32 k;
                    Ctl *p;
                    if (ev.id & 0x10000) c->a272[idx] = ev.v.f;
                    else c->a256[idx] = ev.v.f;
                    k = 8;
                    p = (Ctl *)((u8 *)c + ((ev.id & 0xF000FFFF) - 0x50000000) * 4);
                    if (lbl_80363A68 < p->a256[0]) k = 2;
                    else if (p->a256[0] != lbl_80363A68) k = 6;
                    {
                        f32 z;
                        f32 y;
                        y = p->a272[0];
                        z = *(volatile f32 *)&lbl_80363A68;
                        if (y != z) {
                            if (y < z) k = sT36[k];
                            else if (y > z) k = sT0[k];
                        }
                    }
                    f = k < 8 ? lbl_80328870[k] : lbl_80363A6C;
                }
            } else {
                f = ev.v.i != 0 ? lbl_80328870[(ev.id >> 16) & 0xF] : lbl_80363A6C;
            }
            fn_8011D770(c, idx, f);
            break;
        }
        }
    }
    return 0;
}

} /* extern "C" */
