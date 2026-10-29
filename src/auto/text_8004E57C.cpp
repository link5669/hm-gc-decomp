// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */

struct C802449C4 {
    u8 pad[56];
    C802449C4();
    ~C802449C4();
};

struct O8004E57C {
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
    virtual void GetPos(f32 *pos, s32 a, s32 b, s32 c, s32 d);
};

extern "C" {

void *fn_80242144(void *self, s32 n);
void fn_802448C8(C802449C4 *it, void *list);
void fn_80244750(C802449C4 *it, s32 n);
O8004E57C *fn_8024457C(C802449C4 *it);
s32 fn_80244584(C802449C4 *it);
void fn_80244594(C802449C4 *it);
f32 fn_80101590(f32 *a, f32 *b);
void fn_802494A4(void *self, s32 n);
void fn_800A1A44(void *self);
void fn_800A10D4(void *self, f32 dt);

void fn_8004E57C(u8 *self, f32 dt) {
    if (*(s32 *)(self + 440) != 0 && *(s32 *)(self + 452) != 0) {
        f32 b[3];
        f32 a[3];
        C802449C4 it;
        bool found;

        fn_802448C8(&it, fn_80242144(self, 2));
        fn_80244750(&it, 0);
        found = false;
        (*(O8004E57C **)(self + 224))->GetPos(b, 0, 0, 0, 0);
        for (; !fn_80244584(&it) && !found; fn_80244594(&it)) {
            if (*(u32 *)((u8 *)fn_8024457C(&it) + 180) & 2) {
                fn_8024457C(&it)->GetPos(a, 0, 0, 0, 0);
                if (**(s32 **)(self + 336) != 0) {
                    a[2] = b[2];
                }
                if (fn_80101590(b, a) <= **(f32 **)(self + 292)) {
                    if (**(s32 **)(self + 320) != 0) {
                        fn_802494A4(self, 3);
                    }
                    fn_800A1A44(self);
                    found = true;
                }
            }
        }
    }
    fn_800A10D4(self, dt);
}

} /* extern "C" */
