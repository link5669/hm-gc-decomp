// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void __dla__FPv(void *);
} /* extern "C" */
struct V8016CE20 { u8 pad[32]; virtual void v0(); virtual void v1(); };
extern "C" {
static inline void freeBufs(u8 *self) {
    u32 i;
    for (i = 0; i < *(u32 *)(self + 836); i++) {
        if (*(void **)(self + i * 4 + 7960) != 0) {
            __dla__FPv(*(void **)(self + i * 4 + 7960));
            *(void **)(self + i * 4 + 7960) = 0;
        }
    }
}
void fn_8016CE20(u8 *self) {
    ((V8016CE20 *)(self + 952))->v1();
    ((V8016CE20 *)(self + 840))->v1();
    freeBufs(self);
}

} /* extern "C" */
