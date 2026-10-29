// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802E8578[];
extern u32 lbl_8035AD68;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F6E88(char *, char *);
void fn_800F7E98(void);
void fn_800F7EC0(u32);
void fn_80131BB8(void *);

struct C80179E1Ca {
    u8 pad0[0x10];
    u8 *vt;
    u8 pad14[0x20];
    u32 f34;
    u32 f38;
    u32 f3c;
    C80179E1Ca() {
        fn_80131BB8(this);
        vt = lbl_802E8578;
        f38 = 0;
        f34 = 0;
        f3c = 0;
    }
};
} /* extern "C" */
struct V80179B20 {
    u8 pad[0x10];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6(u32, u32, u32, u32, char *);
};
extern "C" {

struct S80179B20 {
    u8 pad0[0xc];
    char *name;
    u8 pad10[4];
    u32 f14;
    u32 f18;
    u8 pad1c[8];
    u32 f24;
    u8 pad28[8];
    V80179B20 *obj;
    u32 f34;
};

void fn_80179B20(S80179B20 *p) {
    char buf[16];

    if (lbl_8035AD68 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035AD68);
    p->obj = (V80179B20 *)new C80179E1Ca;
    fn_800F7E98();
    if (p->obj == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    if (p->name == 0) {
        buf[0] = 0;
    }
    else {
        fn_800F6E88(buf, p->name);
    }
    p->obj->v6(p->f34, p->f18, p->f24, p->f14, buf);
}

} /* extern "C" */
