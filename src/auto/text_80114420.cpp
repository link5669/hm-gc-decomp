// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_8035AAB8;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7E98(void);
void fn_800F7EC0(u32);
void *memcpy(void *, const void *, unsigned long);
typedef struct H80114420 { u8 pad[16]; u32 size; } H80114420;
typedef struct S80114420 { H80114420 *hdr; u8 pad[8]; u8 *data; } S80114420;

#pragma opt_propagation off
s32 fn_80114420(S80114420 *self, u32 size0) {
    u32 size = size0;
    u8 *p;
    if (lbl_8035AAB8 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035AAB8);
    p = new u8[size];
    fn_800F7E98();
    if (p == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    if (p == 0) {
        return -4;
    }
    if (self->data != 0) {
        if (size > self->hdr->size) {
            memcpy(p, self->data, self->hdr->size);
        } else {
            memcpy(p, self->data, size);
        }
        delete[] self->data;
    }
    self->data = p;
    self->hdr->size = size;
    return 0;
}
#pragma opt_propagation reset

} /* extern "C" */
