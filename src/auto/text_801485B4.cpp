// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u32 lbl_8035ACA0;
extern char lbl_803643B4[0x3];
void __dla__FPv(int);
void fn_800604C4(int, int, int, int);
void fn_80060568(int, int, int, int);
void strcat(int, void *);
void strcpy(int, int);
void fn_800F7E98(void);
void fn_800F7EC0(int);
u32 __nwa__FUl(int);
u32 strlen(void *);
s8 *fn_80210E48(u32);

void fn_801485B4(u32 param_1, u32 param_x) {
    u32 iVar2;
    s8 *param_2;
    u32 sVar1;

    param_2 = fn_80210E48(param_x);
    if (lbl_8035ACA0 == 0) {
        fn_800604C4((int)(0xfffffffe), (int)(0), (int)(0), (int)(0));
    }
    fn_800F7EC0((int)(lbl_8035ACA0));
    sVar1 = strlen(param_2);
    iVar2 = __nwa__FUl((int)(sVar1 + 0x18));
    fn_800F7E98();
    if (iVar2 == 0) {
        fn_800604C4((int)(0xfffffffc), (int)(0), (int)(0), (int)(0));
    }
    if (iVar2 == 0) {
        fn_80060568((int)(param_2), (int)(0), (int)(0), (int)(0));
    }
    else {
        strcpy((int)(iVar2), (int)(param_1));
        strcat((int)(iVar2), lbl_803643B4);
        strcat((int)(iVar2), param_2);
        fn_80060568((int)(iVar2), (int)(0), (int)(0), (int)(0));
        __dla__FPv((int)(iVar2));
    }
}

} /* extern "C" */
