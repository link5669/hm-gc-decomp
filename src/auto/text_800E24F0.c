/* Functions from 0x800E24F0 to 0x800E2C68, found by decomp-toolkit. */
#include "common.h"



extern const double lbl_8029BF20[];
unsigned __cvt_fp2unsigned(double d) {
unsigned result = 0;
if (!(d < 0.0)) {
result--;
if (d < 4294967296.0) {
double value = d;
if (!(d < 2147483648.0)) value -= 2147483648.0;
result = (int)value;
if (!(d < 2147483648.0)) result += 0x80000000;
}
}
return result;
}

int GetR2__Fv_800E2C60(int r2) {
    return r2;
}

asm s32 fn_800E24F0(void *p) {
    nofralloc
    lwz r5, 0(r3)
    lwz r6, 4(r3)
    lwz r7, 8(r3)
    li r3, 1
    cmpwi r5, 0
    cmpwi cr6, r6, 0
    cmpwi cr7, r7, 0
    bnelr
    bnelr cr6
    bnelr cr7
    li r3, 0
    blr
}

asm s32 fn_800E2520(void *a, void *b) {
    nofralloc
    lwz r5, 0(r3)
    lwz r6, 0(r4)
    lwz r7, 4(r3)
    lwz r8, 4(r4)
    lwz r9, 8(r3)
    lwz r10, 8(r4)
    li r3, 1
    cmpw r5, r6
    cmpw cr6, r7, r8
    cmpw cr7, r9, r10
    bnelr
    bnelr cr6
    bnelr cr7
    li r3, 0
    blr
}

asm void __ptmf_scall(void) {
    nofralloc
    lwz r0, 0(r12)
    lwz r11, 4(r12)
    lwz r12, 8(r12)
    add r3, r3, r0
    cmpwi r11, 0
    blt loc_0x20
    lwzx r12, r3, r12
    lwzx r12, r12, r11
loc_0x20:
    mtctr r12
    bctr
}
