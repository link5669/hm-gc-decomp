// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct B8015E62C { u8 pad[162300]; f32 v[4]; };
struct E8015E62C;
typedef void (E8015E62C::*PM8015E62C)(B8015E62C *, void *);
struct E8015E62C {
    u32 f0;
    u8 pad4[32];
    u16 f36;
    u16 f38;
    u8 pad40[44];
    f32 *f84;
    PM8015E62C f88;
};
extern "C" {
typedef struct O8015E62C { u8 pad[44]; u32 f44; u8 pad48[248]; u32 f296; } O8015E62C;
typedef struct L8015E62C { u32 count; O8015E62C **arr; } L8015E62C;
typedef struct S8015E62C { u8 pad[28]; L8015E62C f28; u8 pad36[40]; E8015E62C *f76; } S8015E62C;
typedef struct C8015E62C { u8 pad[292]; O8015E62C *f292; u8 pad296[6156]; B8015E62C *f6452; void *f6456; } C8015E62C;
void fn_8015C998(O8015E62C *o, void *a, u32 b);
void fn_8015D624(O8015E62C *o, C8015E62C *c, u32 i);
void fn_8016BFF0(B8015E62C *b, E8015E62C *e, O8015E62C *o, C8015E62C *c);
void fn_8015FD3C(E8015E62C *e, B8015E62C *b);
void fn_8015C95C(O8015E62C *o, B8015E62C *b, u32 i);
void *fn_80164310(C8015E62C *c, E8015E62C *e);
void fn_8015F4A0(E8015E62C *e, C8015E62C *c, void *r);
void fn_8016BC04(B8015E62C *b, C8015E62C *c);

#pragma opt_propagation off
void fn_8015E62C(S8015E62C *self, C8015E62C *ctx0, u32 start, u32 count, L8015E62C *list) {
    B8015E62C *big;
    u32 grp;
    u32 i;
    C8015E62C *ctx = ctx0;
    E8015E62C *cur;
    E8015E62C *end;
    E8015E62C *first;
    O8015E62C *obj;
    s32 flag;
    void *res;
    f32 *v;

    flag = 0;
    big = ctx->f6452;
    if (list == 0) list = &self->f28;
    if (list->count < 1) return;
    cur = self->f76 + start;
    end = cur + count;
    while (cur < end) {
        if (!(cur->f36 & 1)) { cur++; continue; }
        grp = cur->f38;
        first = cur;
        obj = list->arr[grp];
        if (obj == 0) { cur++; continue; }
        if (ctx->f292 != 0) obj = ctx->f292;
        fn_8015C998(obj, ctx->f6456, cur->f0);
        i = 0;
        do {
            cur = first;
            fn_8015D624(obj, ctx, i);
            do {
                if (cur->f36 & 1) {
                    if ((obj->f44 & 0x300) && i == 0) {
                        fn_8016BFF0(ctx->f6452, cur, obj, ctx);
                        flag = 1;
                    }
                    fn_8015FD3C(cur, big);
                    fn_8015C95C(obj, big, i);
                    res = fn_80164310(ctx, cur);
                    if (res != 0) {
                        v = cur->f84;
                        if (v != 0) {
                            big->v[0] = v[0];
                            big->v[1] = v[1];
                            big->v[2] = v[2];
                            big->v[3] = v[3];
                        }
                        fn_8015F4A0(cur, ctx, res);
                    } else {
                        (cur->*(cur->f88))(ctx->f6452, res);
                    }
                }
                cur++;
            } while (cur < end && grp == cur->f38);
        } while (++i < obj->f296);
    }
    if (flag) fn_8016BC04(ctx->f6452, ctx);
}

} /* extern "C" */
