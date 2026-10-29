// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
typedef struct { u8 d[28]; } L80170044;
typedef struct { u8 d[112]; } C80170044;
struct R80170044 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(L80170044 *, u32, C80170044 *);
    virtual void v6(u32);
    virtual void v7();
    virtual void v8();
    virtual void v9(u32, u16 **);
    virtual void v10(u32);
};
struct S80170044 {
    u32 f0;
    u8 pad[68];
    u8 *f72;
    u8 *f76;
    u32 f80;
};
extern "C" {

void fn_8014CA08(L80170044 *);
void fn_8014C8C8(L80170044 *, u32, u32, u32);
void fn_8016FDE4(S80170044 *, void *, void *);
void fn_8016FA80(S80170044 *, u8 *, C80170044 *);
void fn_80158C64(R80170044 *, u8 *, void *, void *);

#pragma opt_propagation off
void fn_80170044(S80170044 *s, u32 start, u32 count, void *a3, void *a4) {
    u16 *ptr;
    L80170044 desc;
    C80170044 ctx;
    R80170044 *r;
    u8 *vtx;
    u32 j;
    u32 rem;
    u32 n;
    u32 ni;

    fn_8014CA08(&desc);
    if (start < s->f0) {
        if (start + count > s->f0) count = s->f0 - start;
        r = (R80170044 *)(s->f72 + 10656);
        fn_8014C8C8(&desc, 0xA080, 0, 1);
        fn_8016FDE4(s, a3, a4);
        rem = count * 4;
        vtx = s->f76 + start * s->f80;
        do {
            n = rem < 4096 ? rem : 4096;
            ni = n + n / 2;
            j = 0;
            r->v5(&desc, n, &ctx);
            r->v9(ni, &ptr);
            do {
                fn_8016FA80(s, vtx, &ctx);
                vtx += s->f80;
                *ptr++ = j;
                *ptr++ = j + 1;
                *ptr++ = j + 2;
                *ptr++ = j + 1;
                *ptr++ = j + 3;
                *ptr++ = j + 2;
                j += 4;
            } while (j < n);
            rem -= n;
            r->v10(ni);
            r->v6(n);
            fn_80158C64(r, s->f72, a3, a4);
        } while (rem != 0);
    }
}
#pragma opt_propagation reset

} /* extern "C" */
