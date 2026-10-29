// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C8014AC64o {
    u8 pad[292];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4(s32);
    virtual s32 v5();
};
extern "C" {
void fn_8014AC64(s32 *out, C8014AC64o *o) {
    switch (o->v5()) {
    case 87: *out = 1; break;
    case 88: *out = 2; break;
    case 89: *out = 3; break;
    case 90: *out = 4; break;
    case 91: *out = 5; break;
    case 92: *out = 6; break;
    case 93: *out = 7; break;
    case 94: *out = 8; break;
    case 95: *out = 9; break;
    case 96: *out = 10; break;
    default: o->v4(30); break;
    }
}

} /* extern "C" */
