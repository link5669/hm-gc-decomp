// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E80219888 {
    u8 *buf;
    u8 pad[16];
};
struct S80219888 {
    s32 inited;
    E80219888 *ents;
    u32 f8;
    u32 count;
    u32 size;
};
extern "C" {

void fn_802195E8(char *s, void *a);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
extern char lbl_80356DC8[];
extern void *lbl_8035B238;

static inline void Free80219888(S80219888 *p) {
    u32 i;
    if (p->inited != 0) {
        if (p->ents != 0) {
            for (i = 0; i < p->count; i++) delete[] p->ents[i].buf;
            delete[] p->ents;
        }
        p->inited = 0;
        p->ents = 0;
        p->count = 0;
        p->size = 0;
    }
}

void fn_80219888(S80219888 *p, void *a, u32 count, u32 size) {
    u32 i;
    Free80219888(p);
    fn_802195E8(lbl_80356DC8, a);
    p->count = count;
    p->size = size;
    if (lbl_8035B238 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B238);
    p->ents = new E80219888[p->count];
    fn_800F7E98();
    if (p->ents == 0) fn_800604C4(-4, 0, 0, 0);
    for (i = 0; i < p->count; i++) {
        if (lbl_8035B238 == 0) fn_800604C4(-2, 0, 0, 0);
        fn_800F7EC0(lbl_8035B238);
        p->ents[i].buf = new u8[p->size];
        fn_800F7E98();
        if (p->ents[i].buf == 0) fn_800604C4(-4, 0, 0, 0);
    }
    p->inited = 1;
}

} /* extern "C" */
