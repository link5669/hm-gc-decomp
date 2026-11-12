// main: schedule-equivalent (schedequiv.txt): the lis/li of the first call arguments are in a different order.
// GC/2.0p1 with optimization_level 1 + scheduling 603 (saved wave-31 draft).
#include "common.h"
extern "C" {
extern s32 lbl_8035A1D4;
extern char **lbl_8035A1D0;
extern char lbl_80302DDC[];
s32 fn_800629DC(char *a, s32 b, s32 c);
void fn_80061E80(char *a);
void fn_800619B8(char *a);
#pragma optimization_level 1
#pragma scheduling 603
int main(int argc, char **argv) {
    if (lbl_8035A1D0 = argv, lbl_8035A1D4 = argc, fn_800629DC(lbl_80302DDC, 0, 0) == 0) fn_80061E80(lbl_80302DDC);
    fn_800619B8(lbl_80302DDC);
    return 1;
}
}
