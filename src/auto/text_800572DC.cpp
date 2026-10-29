// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct H800572DC { u8 pad[16]; u32 count; };
struct E800572DC { u32 a, b; };
struct A800572DC { H800572DC *hdr; u8 pad[8]; E800572DC *data; };
struct B800572DC { H800572DC *hdr; u8 pad[8]; s32 *data; };
struct P800572DC {
    u8 pad[472];
    A800572DC *f472;
    B800572DC *f476;
    B800572DC *f480;
    B800572DC *f484;
    u8 pad2[596 - 488];
    s32 f596;
};
extern "C" {

extern char lbl_8035E060[4];
extern f32 lbl_8035E1A4;
void fn_800F6E88(void *, void *);
s32 fn_800F6CD0(void *, void *);
void fn_80240DBC(P800572DC *, f32);
void fn_8024118C(P800572DC *, void *, s32);
void fn_80240B50(P800572DC *, void *, s32);
void fn_802410CC(P800572DC *, void *, s32);
static inline void else572(P800572DC *p, u32 idx, u32 *local) {
    s32 v = 0;
    B800572DC *b = p->f476;
    if (b->hdr->count > idx) v = b->data[idx];
    {
    s32 w = 0;
    B800572DC *d = p->f484;
    if (d->hdr->count > idx) w = d->data[idx];
    if (w == 0) {
        B800572DC *c = p->f480;
        if (c != 0 && c->hdr->count > idx && c->data[idx] == 1) {
            fn_8024118C(p, local, v);
        } else if (p->f596 != 0) {
            p->f596 = 0;
            fn_80240B50(p, local, v);
        } else {
            fn_8024118C(p, local, v);
        }
    } else {
        fn_802410CC(p, local, v);
    }
    }
    p->f596 = v;
}
void fn_800572DC(P800572DC *p, u32 idx) {
    u32 local[2];
    A800572DC *a = p->f472;
    if (a->hdr->count > idx) {
        fn_800F6E88(local, &a->data[idx]);
        if (fn_800F6CD0(local, lbl_8035E060) != 0) {
            B800572DC *c = p->f480;
            if (c == 0 || c->hdr->count > idx || c->data[idx] == 1) {
                if (p->f596 != 0) {
                    p->f596 = 0;
                    fn_80240DBC(p, lbl_8035E1A4);
                }
            }
        } else {
            else572(p, idx, local);
        }
    }
}

} /* extern "C" */
