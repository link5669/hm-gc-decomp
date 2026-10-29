// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800F9654(void *p, u8 *v);
void fn_800F994C(void *p, u32 n);
void fn_8012C4FC(void *self, u32 a, void *b, u32 c);

void fn_801361C0(u8 *self, u32 *a, const u8 *b) {
    u8 tmp;
    *(u32 **)(self + 52) = a;
    *(u32 *)(self + 56) = *(const u32 *)(b + 56);
    tmp = 0;
    fn_800F9654(self + 60, &tmp);
    fn_800F994C(self + 84, 64);
    fn_800F9654(self + 120, &tmp);
    fn_800F994C(self + 144, 64);
    fn_800F9654(self + 180, &tmp);
    fn_800F994C(self + 204, 64);
    fn_800F9654(self + 240, &tmp);
    fn_800F994C(self + 264, 64);
    fn_800F9654(self + 300, &tmp);
    fn_800F994C(self + 324, 64);
    fn_800F9654(self + 360, &tmp);
    fn_800F994C(self + 384, 64);
    fn_800F9654(self + 420, &tmp);
    fn_800F994C(self + 444, 64);
    fn_800F9654(self + 480, &tmp);
    fn_800F994C(self + 504, 64);
    fn_800F9654(self + 540, &tmp);
    fn_800F994C(self + 564, 16);
    fn_800F9654(self + 600, &tmp);
    fn_800F994C(self + 624, 16);
    fn_800F9654(self + 660, &tmp);
    fn_800F9654(self + 684, &tmp);
    fn_800F9654(self + 708, &tmp);
    fn_800F9654(self + 732, &tmp);
    fn_800F9654(self + 756, &tmp);
    fn_800F9654(self + 780, &tmp);
    fn_8012C4FC(self, *a, (void *)(b + 8), *(const u32 *)b);
}

} /* extern "C" */
