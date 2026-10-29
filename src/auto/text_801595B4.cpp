// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct B_1595B4 {
    u8 pad[12];
    virtual void d0();
    virtual void d1();
    virtual void d2();
    virtual void d3();
    virtual void d4();
    virtual void d5();
    virtual void d6();
    virtual void d7();
    virtual void d8();
    virtual void d9();
    virtual void d10();
    virtual void d11();
    virtual void d12();
    virtual void d13();
    virtual void d14();
    virtual void d15();
    virtual void d16();
    virtual void d17();
    virtual void d18();
    virtual void d19();
    virtual void d20();
    virtual void v21(s32 a, s32 b, void *key);
    virtual void v22(void *data, s32 flag);
    virtual void d23();
    virtual void d24();
    virtual void d25();
    virtual void v26(void *data, u32 n);
};
struct C801768A4 : B_1595B4 {
    u8 f16[88];
    C801768A4();
    ~C801768A4();
};
struct N_1595B4 {
    C801768A4 arr[2];
    u32 f208;
    u32 f212;
    N_1595B4 *f216;
};
extern "C" {
typedef struct {
    u8 pad[8];
    N_1595B4 *f8;
    u32 f12;
    u32 f16;
    u8 pad2[4];
    N_1595B4 *f24;
} S_1595B4;
extern void *lbl_8035ACD0;
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *p);
void fn_800F7E98(void);
s32 fn_8014C6F4(void *p, void *key);

static inline N_1595B4 *get_1595B4(S_1595B4 *self, void *key) {
    N_1595B4 *n;
    for (n = self->f8; n != 0; n = n->f216) {
        if (fn_8014C6F4(n->arr[0].f16, key) != 0) return n;
    }
    if (lbl_8035ACD0 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035ACD0);
    n = new N_1595B4;
    fn_800F7E98();
    if (n == 0) fn_800604C4(-4, 0, 0, 0);
    n->f216 = self->f8;
    self->f8 = n;
    n->f208 = 0;
    n->f212 = 0;
    n->arr[0].v21(4096, 1, key);
    n->arr[1].v21(4096, 1, key);
    return n;
}
void fn_801595B4(S_1595B4 *self, void *key, u32 size, void *data) {
    s32 flag;

    self->f16 = size;
    self->f24 = get_1595B4(self, key);
    if (self->f24->f212 + size > 4096) {
        self->f24->f208 = (self->f24->f208 + 1) & 1;
        self->f24->f212 = 0;
        flag = 8;
    } else {
        flag = 4;
    }
    self->f12 = self->f24->f212;
    self->f24->arr[self->f24->f208].v22(data, flag);
    if (self->f12 != 0) self->f24->arr[self->f24->f208].v26(data, self->f12);
}

} /* extern "C" */
