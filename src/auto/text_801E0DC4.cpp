// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 __vt__9C80129A9C[];
void __ct__9C80105074Fv(void *);
void __dt__9C8010500CFv(void *, s16);
void fn_80101124(void *, void *);
void fn_800FF9E8(void *, void *);
void fn_801EF720(void *, void *, s32);
} /* extern "C" */
struct C80105818 {
    u8 pad[36];
    u8 *vt;
    C80105818() { __ct__9C80105074Fv(this); vt = __vt__9C80129A9C; }
    ~C80105818() { vt = __vt__9C80129A9C; __dt__9C8010500CFv(this, 0); }
};
struct Vec3_801E0DC4 { f32 x, y, z; };
extern "C" {

void fn_801E0DC4(u8 *self, void *arg, s32 cmd) {
    Vec3_801E0DC4 v;
    C80105818 obj;
    switch (cmd) {
    case 125:
        fn_80101124(self + 84, arg);
        fn_80101124(self + 72, arg);
        *(s32 *)(self + 96) = 1;
        break;
    case 124:
        fn_800FF9E8(self + 44, arg);
        *(s32 *)(self + 96) = 0;
        break;
    case 128:
        fn_80101124(self + 60, arg);
        fn_80101124(&v, arg);
        *(f32 *)(self + 84) = v.x - *(f32 *)(self + 60);
        *(f32 *)(self + 88) = v.y - *(f32 *)(self + 64);
        *(f32 *)(self + 92) = v.z - *(f32 *)(self + 68);
        fn_80101124(self + 72, arg);
        *(s32 *)(self + 96) = 1;
        break;
    case 126:
        fn_80101124(self + 60, arg);
        break;
    case 176:
        *(s32 *)(self + 12) = 19;
        break;
    case 177:
        *(s32 *)(self + 12) = 20;
        break;
    case 178:
        *(s32 *)(self + 12) = 21;
        break;
    default:
        fn_801EF720(self, arg, cmd);
        break;
    }
}

} /* extern "C" */
