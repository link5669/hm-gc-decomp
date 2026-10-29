// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Tbl801E8E64 {
    u8 a[24];
    u8 b[24];
};
struct R4_801E8E64 {
    u8 pad[480];
    Tbl801E8E64 t;
};
struct R212_801E8E64 {
    u8 pad0[4];
    R4_801E8E64 *f4;
    u8 pad8[136];
    Tbl801E8E64 t;
};
struct R8_801E8E64 {
    u8 pad[212];
    R212_801E8E64 *f212;
};
struct S801E8E64 {
    u8 pad0[8];
    R8_801E8E64 *f8;
    s32 f12;
    u8 pad16[24];
    void *f40;
    void *f44;
    s32 f48;
    void *f52;
    s32 f56;
};
extern "C" {

void fn_800FB064(void *s, char *buf);
s32 fn_800FB33C(void *s);
void *fn_800F9398(void *t, const char *name);
void *fn_800F9788(void *t, const char *grp, const char *name);
void *fn_8019565C(void *r);
void *fn_8019556C(void *r);
void fn_801EF720(S801E8E64 *p, void *s, s32 id);

static inline void *LookupA801E8E64(R212_801E8E64 *t, const char *grp, const char *name) {
    if (grp == 0 || grp[0] == 0) return fn_800F9398(t->t.a, name);
    return fn_800F9788(t->t.b, grp, name);
}
static inline void *LookupB801E8E64(R4_801E8E64 *t, const char *grp, const char *name) {
    if (grp == 0 || grp[0] == 0) return fn_800F9398(t->t.a, name);
    return fn_800F9788(t->t.b, grp, name);
}

void fn_801E8E64(S801E8E64 *p, void *s, s32 id) {
    char name[8];
    char grp[8];
    void *r;
    switch (id) {
    case 104:
        fn_800FB064(s, name);
        fn_800FB064(s, grp);
        r = LookupA801E8E64(p->f8->f212, grp, name);
        if (r != 0) r = fn_8019565C(r);
        r = fn_8019556C(r);
        p->f44 = 0;
        p->f40 = 0;
        p->f40 = r;
        break;
    case 117:
        p->f48 = fn_800FB33C(s);
        fn_800FB064(s, name);
        fn_800FB064(s, grp);
        if (name[0] != 0) {
            p->f52 = LookupB801E8E64(p->f8->f212->f4, grp, name);
        } else {
            p->f52 = 0;
        }
        break;
    case 167:
        p->f12 = 15;
        break;
    case 168:
        p->f12 = 16;
        break;
    case 169:
        p->f56 = 1;
        break;
    default:
        fn_801EF720(p, s, id);
        break;
    }
}

} /* extern "C" */
