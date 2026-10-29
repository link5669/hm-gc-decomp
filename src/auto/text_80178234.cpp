// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct V4_80178234 { volatile f32 x, y, z, w; };
extern "C" {
extern volatile f32 lbl_80364788;
extern volatile f32 lbl_80364790;
extern volatile f32 lbl_803647A8;
extern volatile f32 lbl_8036478C;
extern volatile f32 lbl_803647AC;
void fn_80135CB0(void);
void __construct_array(void *, void *, void *, u32, u32);
static V4_80178234 s_a;
static V4_80178234 s_b;
static V4_80178234 s_c;
static V4_80178234 s_d;
static V4_80178234 s_e;
static u8 s_arr[128][16];
static inline void init4(V4_80178234 *p, f32 c) { p->x = c; p->y = c; p->z = c; p->w = c; }
void fn_80178234(void) {
    init4(&s_a, lbl_80364788);
    init4(&s_b, lbl_80364790);
    init4(&s_c, lbl_803647A8);
    init4(&s_d, lbl_8036478C);
    init4(&s_e, lbl_803647AC);
    __construct_array(s_arr, (void *)fn_80135CB0, 0, 16, 128);
}
__declspec(section ".ctors") static void (*const ctor_80178234)(void) = fn_80178234;

} /* extern "C" */
