// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern "C" int memcmp(const void *, const void *, unsigned long);
extern char lbl_802A5C20[], lbl_802A5C34[], lbl_802A5C4C[];
extern char lbl_803654C0[5];
void fn_80060568(const char *, int, int, int);
struct K { u8 b[8]; };
void fn_801F12D4(K *);
void fn_801F10F8(K *, u8 *, u32);
u32 fn_801F12C4(K *);
struct St { u32 f0; u8 *cur; u8 *end; int f12; };
struct H { St *s; };
struct R {
    H *h;
    virtual void v0(); virtual void v1(); virtual void v2(); virtual u32 size(); virtual void read(u32, u8 **); virtual u32 crc();
    u8 id[4]; u8 *p; u32 len;
};
static inline void sync(R *r) {
    r->h->s->cur = r->p;
    r->h->s->end = r->p + r->len;
}
static inline int load(R *r) {
    r->len = r->size();
    if (!r->len) return 0;
    r->read(r->len + 4, &r->p);
    u32 c = r->crc();
    K k;
    fn_801F12D4(&k);
    fn_801F10F8(&k, r->p, r->len + 4);
    if (c != fn_801F12C4(&k)) fn_80060568(lbl_802A5C20, 0, 0, 0);
    r->id[0] = *r->p; r->p++;
    r->id[1] = *r->p; r->p++;
    r->id[2] = *r->p; r->p++;
    r->id[3] = *r->p; r->p++;
    sync(r);
    return 1;
}
void fn_801F6334(R *r) {
    H *h = r->h;
    St *s = h->s;
    if (s->f12 >= 0) s->cur++;
    h->s->f12 = -1;
    if (!load(r)) fn_80060568(lbl_802A5C34, 0, 0, 0);
    if (memcmp(r->id, lbl_803654C0, 4)) fn_80060568(lbl_802A5C4C, 0, 0, 0);
    sync(r);
    s = r->h->s;
    if (s->f12 < 0) s->f12 = 0;
}

} /* extern "C" */
