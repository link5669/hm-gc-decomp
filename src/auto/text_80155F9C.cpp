// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S80155F9C {
    u32 flags;
    u32 count;
    u8 b8;
    u8 b9;
    u8 b10;
    u8 b11;
    u32 n;
    u8 arr[8];
} S80155F9C;

int fn_80101A7C(u8 fmt);

#pragma opt_propagation off
u32 fn_80155F9C(const S80155F9C *p0) {
    u32 size = 0;
    S80155F9C *p = (S80155F9C *)p0;
    if (p->flags & 0x40) size += fn_80101A7C(p->b8) * 2;
    else if (p->flags & 0x80) size += fn_80101A7C(p->b8) * 3;
    else if (p->flags & 0x100) size += fn_80101A7C(p->b8) * 4;
    size += p->count * fn_80101A7C(p->b8);
    if (p->flags & 0x400) size += (p->count + 1) * fn_80101A7C(p->b10);
    if (p->flags & 0x800) size += fn_80101A7C(p->b11) * 3;
    if (p->flags & 0x2000) size += 4;
    if (p->flags & 0x4000) size += 4;
    {
        u32 n;
        u32 m;
        u32 flags;
        u32 i;
        flags = *(u32 *)p;
        i = 0;
        n = p->n;
        m = 0x01010000;
    for (; i < n; i++) {
        if (!(flags & (m << i))) size += fn_80101A7C(p->arr[i]) * 2;
        else if (flags & (0x10000 << i)) size += fn_80101A7C(p->arr[i]) * 3;
        else size += fn_80101A7C(p->arr[i]) * 4;
    }
    }
    return size;
}
#pragma opt_propagation reset

} /* extern "C" */
