#include "common.h"
extern "C" {
typedef struct V3 { f32 x, y, z; } V3;
struct VO {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12();
    virtual void v13(V3 *a, V3 *b, V3 *c, V3 *d, s32 e);
    virtual void v14(V3 *a, s32 b, s32 c, s32 d, s32 e);
};
typedef struct G1 { u8 pad[188]; f32 f188; } G1;
typedef struct G { u8 pad[4]; G1 *f4; } G;
typedef struct M { u8 pad[72]; VO *f72; } M;
typedef struct T {
    u8 pad0[192]; G *f192; u8 p1[224 - 196]; VO *f224; u8 p2[284 - 228];
    f32 *f284; f32 *f288; u8 p3[296 - 292]; f32 *f296; u8 p4[340 - 300]; s32 *f340; f32 *f344;
    u8 p5[360 - 348]; s32 *f360; u8 p6[424 - 364]; f32 f424; u8 p7[432 - 428]; f32 f432; s32 f436;
    u8 p8[448 - 440]; s32 f448; u8 p9[456 - 452]; s32 f456; u8 p10[464 - 460]; u32 f464; u32 f468;
    u8 p11[508 - 472]; s32 *f508; s32 *f512; void *f516;
} T;
extern "C" {
extern M *lbl_8035B308;
extern f32 lbl_803596E0[];
extern f32 lbl_80361BD0;
extern f32 lbl_80361C08;
extern f64 lbl_80361C10;
extern f32 lbl_80361C18;
extern f32 lbl_80361C1C;
int rand(void);
void fn_80101820(V3 *);
f32 fn_80101590(V3 *, V3 *);
V3 *fn_80245F8C(void *, u32);
void fn_80245E58(void *, u32, V3 *);
f64 fn_800F045C(f64);
void fn_8023F5E8(T *, s32);
void fn_80257A4C(G1 *, V3 *);
void fn_80241628(T *, s32, s32);
}
static inline bool zle(T *self, V3 *e, V3 *pos) {
    f32 d = (f32)__fabs(pos->z - e->z);
    return d <= *self->f344;
}
static inline bool zok(T *self, V3 *e, V3 *pos) {
    return *self->f340 || (!*self->f340 && zle(self, e, pos));
}
static inline f32 Acos(f32 x) {
    if ((f32)__fabs(x) <= lbl_80361C10) return (f32)fn_800F045C(x);
    if (x > lbl_80361BD0) return lbl_80361BD0;
    return lbl_80361C18;
}
static inline u32 pickIdx(u32 n) { u32 p = 0; if (n) p = (u32)rand() % n; return p; }
#pragma push
#pragma opt_common_subs off
extern "C" void fn_800A1AA8(T *self) {
    V3 pos;
    V3 dir;
    V3 tmp;
    V3 p2;
    V3 d;
    u32 cnt;
    u32 i;
    f32 thr;
    s32 found;
    u32 n;
    self->f224->v13(&pos, &dir, 0, 0, 0);
    fn_80101820(&dir);
    cnt = 0;
    if (!self->f456 || !*self->f360) fn_80245F8C(self->f516, self->f468);
    for (i = 0; i < self->f464; i++) {
        V3 *e = fn_80245F8C(self->f516, i);
        u8 vis = 0;
        bool near = i != self->f468 && fn_80101590(e, &pos) <= self->f424;
        if (near) {
            if (zok(self, e, &pos)) vis = 1;
        }
        self->f508[i] = vis;
        self->f512[i] = vis;
        if (vis) cnt++;
    }
    self->f448 = self->f436;
    if (!self->f464) return;
    if (!((!self->f448 && self->f432 > lbl_80361BD0) || (self->f448 && *self->f296 > lbl_80361BD0))) return;
    {
        if (cnt == 0 || (self->f456 && *self->f360)) {
            u32 bi = 0;
            u32 bj = 0;
            f32 bd = lbl_803596E0[0];
            f32 bd2 = bd;
            for (i = 0; i < self->f464; i++) {
                f32 dd = fn_80101590(fn_80245F8C(self->f516, i), &pos);
                if (i != self->f468) {
                    if (dd < bd) { bi = i; bd = dd; }
                    if (dd < bd2) {
                        if ((f32)__fabs(pos.z - fn_80245F8C(self->f516, i)->z) <= *self->f344) { bj = i; bd2 = dd; }
                    }
                }
            }
            if (!*self->f340 && bd2 != lbl_803596E0[0]) {
                self->f508[bj] = 1;
                self->f512[bj] = 1;
            } else {
                self->f508[bi] = 1;
                self->f512[bi] = 1;
            }
            if (self->f456 && *self->f360) {
                if (!*self->f340 && bd2 != lbl_803596E0[0]) self->f468 = bj;
                else self->f468 = bi;
                fn_80245E58(self->f516, self->f468, &tmp);
                self->f224->v14(&tmp, 0, 0, 0, 0);
                self->f456 = 0;
                fn_800A1AA8(self);
                return;
            }
        }
        if (self->f436) {
            lbl_8035B308->f72->v13(&p2, 0, 0, 0, 0);
            dir.x = p2.x - pos.x;
            dir.y = p2.y - pos.y;
            dir.z = p2.z - pos.z;
            fn_80101820(&dir);
        }
        thr = self->f448 ? *self->f284 : lbl_80361C08;
        G1 *g0 = self->f192->f4;
        g0->f188 = self->f448 ? *self->f296 : self->f432;
        found = 0;
        n = 0;
        while (!found) {
            n = 0;
            for (i = 0; i < self->f464; i++) {
                if (self->f508[i]) {
                    V3 *e = fn_80245F8C(self->f516, i);
                    s32 ok;
                    d.x = pos.x - e->x;
                    d.y = pos.y - e->y;
                    d.z = pos.z - e->z;
                    fn_80101820(&d);
                    ok = lbl_80361C1C * Acos(dir.x * d.x + dir.y * d.y + dir.z * d.z) <= thr;
                    self->f512[i] = ok;
                    if (ok) { found = 1; n++; }
                }
            }
            if (!found) thr += *self->f288;
        }
        {
            u32 pick;
            u32 k;
            pick = pickIdx(n);
            for (i = 0, k = 0; i < self->f464; i++) {
                if (self->f512[i]) {
                    if (k == pick) {
                        V3 *e = fn_80245F8C(self->f516, i);
                        G1 *g = self->f192->f4;
                        fn_8023F5E8(self, 0);
                        fn_80257A4C(g, e);
                        self->f468 = i;
                        if (g->f188 > lbl_80361BD0) fn_80241628(self, 1, 0);
                        else { self->f224->v14(e, 0, 0, 0, 0); self->f448 = 0; }
                        return;
                    }
                    k++;
                }
            }
        }
    }
}
#pragma pop
}
