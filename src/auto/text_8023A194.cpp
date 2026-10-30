// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct El { virtual void e0(); virtual void e1(); virtual void e2(); virtual void kill(); };
struct Rec { u8 pad[28]; s32 stride; };
struct C8023A51C { u32 cnt; u32 f4; s32 f8; u32 f12; u32 f16; u8 *f20; C8023A51C *f24; void *f28; ~C8023A51C() {} };
typedef C8023A51C N;
extern "C" {
extern void __dt__9C8023D2ACFv(void *, s16);
Rec *fn_800F85F0(void *, s32);
void fn_800E1E88(void *, void *);
inline s32 fn_8023A14C(Rec *r) { return r->stride; }
inline s32 fn_8023A154(N *n) { return (u8)(n->f8 >= 0); }
inline void fn_8023A168(N *n) { n->f8 = -1; n->f28 = 0; n->f20 = 0; n->cnt = 0; n->f4 = 4; n->f16 = 0; n->f24 = 0; }
inline El *fn_8023A490(N *n, u32 i) { Rec *r = fn_800F85F0(n->f28, n->f8); u8 *b = n->f20; b += i * fn_8023A14C(r); return (El *)b; }

void fn_8023A194(N *n) {
    if (fn_8023A154(n)) {
        u32 i;
        for (i = 0; i < n->cnt; i++) fn_8023A490(n, i)->kill();
        if (n->f20) fn_800E1E88(n->f20, (void *)__dt__9C8023D2ACFv);
        if (n->f24) {
            fn_8023A194(n->f24);
            delete n->f24;
        }
        fn_8023A168(n);
    }
}

} /* extern "C" */
