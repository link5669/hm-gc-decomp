// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 *lbl_8035AD48;
extern u32 lbl_80364780;
extern u32 lbl_80364784;
void fn_800604C4(s32 code, s32 a, s32 b, s32 c);
void fn_800F7EC0(void *heap);
void *fn_800F7FC4(u32 size);
void fn_800F7E98(void);

#define ALLOC(field, size) \
    if (lbl_8035AD48 == 0) { \
        fn_800604C4(-2, 0, 0, 0); \
    } \
    fn_800F7EC0(lbl_8035AD48); \
    p[field] = (u32)fn_800F7FC4(size); \
    fn_800F7E98(); \
    if (p[field] == 0) { \
        fn_800604C4(-4, 0, 0, 0); \
    }

// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"
extern "C" {


#define ALLOC(field, size) \
    if (lbl_8035AD48 == 0) { \
        fn_800604C4(-2, 0, 0, 0); \
    } \
    fn_800F7EC0(lbl_8035AD48); \
    p[field] = (u32)fn_800F7FC4(size); \
    fn_800F7E98(); \
    if (p[field] == 0) { \
        fn_800604C4(-4, 0, 0, 0); \
    }

static inline u32 wA_f4(u32 n) { return n * 4; }

void fn_80176314(u32 *p) {
    u32 i;
    s32 n;

    if (*(u32 *)(lbl_8035AD48 + 0x18) >= 5) {
        *(u32 *)(lbl_8035AD48 + 0x1C) = *(u32 *)(lbl_8035AD48 + 0x18);
    } else {
        *(u32 *)(lbl_8035AD48 + 0x1C) = 5;
    }
    p[0x18] = 0;
    p[0] |= lbl_80364780;
    if (p[4] & 0x40) {
        p[0x18]++;
        ALLOC(0x13, p[2] * 8)
    } else if (p[4] & 0x80) {
        p[0x18]++;
        ALLOC(0x13, p[2] * 0xC)
    } else if (p[4] & 0x100) {
        p[0x18]++;
        ALLOC(0x13, p[2] * 0x10)
    }
    if (p[4] & 0x200) {
        ALLOC(0x14, p[2] * (p[5] * 4))
    }
    if (p[4] & 0x400) {
        ALLOC(0x15, p[2] * (p[5] + 1))
    }
    if (p[4] & 0x800) {
        p[0x18]++;
        ALLOC(0x16, wA_f4(p[2] * 3))
    }
    if (p[4] & 0x2000) {
        p[0x18]++;
        ALLOC(0x11, p[2] * 4)
    }
    if (p[4] & 0x4000) {
        p[0x18]++;
        ALLOC(0x12, p[2] * 4)
    }
    if (p[4] & 0x8000) {
        n = 0;
        p[0x18] += p[7];
        p[0x19] = 0;
        for (i = 0; i < p[7]; i++) {
            if (p[4] & (0x1000000 << i)) {
                n += 4;
                p[0x19] += 0x10;
            } else if (p[4] & (0x10000 << i)) {
                n += 3;
                p[0x19] += 0xC;
            } else {
                n += 2;
                p[0x19] += 8;
            }
        }
        ALLOC(0x17, n * p[2] * 4)
    }
    p[1] |= lbl_80364784;
    *(u32 *)(lbl_8035AD48 + 0x1C) = *(u32 *)(lbl_8035AD48 + 0x18);
}

}

} /* extern "C" */
