// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802C4398[];
extern u8 lbl_80359308[8];
extern f32 lbl_8035FC48;

#define F(off) (*(u32 *)((u8 *)p + (off)))
#define FP(off) (*(void **)((u8 *)p + (off)))

#pragma opt_propagation off
void fn_80083784(u8 *p) {
    u8 *d = lbl_802C4398;
    s32 i;
    F(84) = 23;
    F(44) = 23;
    F(104) = 5;
    F(92) = 1;
    F(128) = 1;
    F(124) = 3;
    F(132) = 0;
    F(136) = 2;
    F(140) = 0;
    F(148) = 0;
    FP(88) = d + 640;
    FP(40) = d + 732;
    FP(48) = d + 1008;
    FP(108) = d + 620;
    FP(120) = d + 604;
    FP(196) = lbl_80359308;
    FP(200) = d + 540;
    F(204) = 0;
    FP(244) = d + 576;
    F(252) = 0;
    F(268) = 0;
    F(280) = 0;
    F(284) = 0;
    F(288) = 0;
    F(292) = 0;
    F(296) = 0;
    F(300) = 0;
    F(304) = 0;
    F(308) = 0;
    F(312) = 0;
    F(316) = 0;
    F(320) = 0;
    F(324) = 0;
    F(328) = 0;
    F(332) = 0;
    F(336) = 0;
    F(340) = 0;
    F(344) = 0;
    F(348) = 0;
    F(352) = 0;
    F(356) = 0;
    F(360) = 0;
    F(364) = 0;
    F(368) = 0;
    F(372) = 0;
    F(376) = 0;
    F(380) = 0;
    F(384) = 0;
    F(388) = 0;
    F(392) = 0;
    F(396) = 0;
    F(400) = 1;
    F(404) = 1;
    F(408) = 0;
    F(412) = 0;
    F(416) = 0;
    F(420) = 0;
    F(424) = 0;
    F(428) = 0;
    F(432) = 0;
    F(436) = 8;
    F(440) = 0;
    F(444) = 0x80000000;
    F(448) = 0x40000000;
    F(452) = 0x20000000;
    F(456) = 0x18000000;
    F(460) = 0x07FFFFFF;
    *(f32 *)(p + 464) = lbl_8035FC48;
}
#pragma opt_propagation reset

} /* extern "C" */
