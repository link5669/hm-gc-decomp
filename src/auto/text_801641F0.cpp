// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct O4 {
    u8 pad[28];
    u16 f28;
    u16 f30;
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9(s32 *a, s32 *b, s32 c);
    virtual void v10();
};
struct O6452b {
    u8 pad[48];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual O4 *v11();
};
struct O6452 : O6452b {
    u8 pad2[784];
    u32 f836;
};
struct T0 {
    u8 pad0[4];
    O4 *f4;
    u8 pad8[4];
    u32 f12;
    u8 pad16[6432];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
};
struct T : T0 {
    O6452 *f6452;
    u8 pad6456[4];
    s32 f6460;
};
extern "C" {
void *fn_8015B06C(O4 *);
void fn_800D7480(void *, s32);
void fn_800D6EC4(s32, s32, u16, u16);
void *fn_801562D8(void);
void fn_800D6F74(u16, u16, void *, s32);
void fn_800D75E8(s32, s32);
void fn_800D6270(void);
void fn_800D8704(void);

void fn_801641F0(T *p) {
    u16 y;
    u16 x;
    s32 a;
    s32 b;
    p->v30();
    p->f6460 = 0;
    p->f12 &= ~2;
    if (p->f6452->v11() == p->f4) {
        if (p->f6452->f836 > 1) {
            fn_800D7480(fn_8015B06C(p->f4), 0);
        }
    } else {
        fn_800D6EC4(0, 0, p->f4->f28, p->f4->f30);
        y = p->f4->f30;
        x = p->f4->f28;
        fn_800D6F74(x, y, fn_801562D8(), 0);
        p->f4->v9(&a, &b, 2);
        fn_800D75E8(a, 0);
        fn_800D6270();
        fn_800D8704();
        p->f4->v10();
    }
}

} /* extern "C" */
