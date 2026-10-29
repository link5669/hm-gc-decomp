// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct Heap80160F40 { u8 pad[24]; u32 f24; u32 f28; };
extern Heap80160F40 *lbl_8035AD10;
extern u8 lbl_8032E780[];
extern u8 lbl_8032E794[];
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
void *memset(void *, s32, u32);
void fn_80148288(void *, s32, s32, s32, s32, s32, s32);
void fn_800D8508(void *, u16 *, s32, s32);

struct S80160F40 {
    u16 f0;
    u16 f2;
    u8 pad4[4];
    u8 f8[12];
    void *f20;
    u16 *f24;
};
struct A80160F40 { u16 f0; u16 f2; };

void fn_80160F40(S80160F40 *self, A80160F40 *a, u32 flags) {
    s32 n;

    if (self->f24 != 0) {
        if (self->f24) delete[] self->f24;
        self->f0 = 0;
        self->f2 = 0;
        self->f20 = 0;
        memset(self->f8, 0, 12);
        self->f24 = 0;
    }
    self->f0 = 1 << a->f2;
    if (lbl_8035AD10->f24 >= 5) {
        lbl_8035AD10->f28 = lbl_8035AD10->f24;
    } else {
        lbl_8035AD10->f28 = 5;
    }
    if (lbl_8035AD10 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035AD10);
    self->f24 = new u16[self->f0];
    fn_800F7E98();
    if (self->f24 == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    lbl_8035AD10->f28 = lbl_8035AD10->f24;
    memset(self->f24, 0, self->f0 * 2);
    self->f2 = (flags & 0x38) | 1;
    if (flags & 0x10) {
        n = 2;
        fn_80148288(lbl_8032E780, 16, 0xF00, 0xF0, 0xF, 0x3000, 0);
        self->f20 = lbl_8032E780;
    } else {
        n = 1;
        fn_80148288(lbl_8032E794, 16, 0xF800, 0x7E0, 0x1F, 0, 0);
        self->f20 = lbl_8032E794;
    }
    if (!(flags & 0x20)) {
        fn_800D8508(self->f8, self->f24, n, self->f0);
    }
}

} /* extern "C" */
