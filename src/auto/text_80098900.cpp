// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802CC2B8[];
extern volatile f32 lbl_803614B8;

#define F(off) (*(u32 *)((u8 *)p + (off)))
#define FP(off) (*(void **)((u8 *)p + (off)))
#define FF(off) (*(f32 *)((u8 *)p + (off)))

#pragma opt_propagation off
void fn_80098900(u8 *p) {
    u8 *d = lbl_802CC2B8;
    F(84) = 54;
    F(44) = 53;
    F(104) = 16;
    F(92) = 6;
    F(128) = 4;
    F(124) = 20;
    F(132) = 3;
    F(136) = 14;
    F(140) = 0;
    F(148) = 2;
    FP(88) = d + 1240;
    FP(40) = d + 1456;
    FP(48) = d + 2092;
    FP(108) = d + 1176;
    FP(120) = d + 1040;
    FP(196) = d + 540;
    FP(200) = d + 556;
    FP(204) = d + 796;
    FP(244) = d + 832;
    F(252) = 0;
    FP(268) = d + 1136;
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
    F(364) = 0;
    F(368) = 0;
    F(372) = 0;
    F(376) = 0;
    F(380) = 0;
    F(384) = 0;
    F(388) = 1;
    F(392) = 0;
    F(396) = 0;
    F(400) = 0;
    F(404) = 0;
    F(408) = 0;
    F(412) = 0;
    F(416) = 0;
    F(420) = 0;
    F(424) = 0;
    F(428) = 0;
    F(432) = 0;
    F(436) = 0;
    FF(440) = lbl_803614B8;
    FF(444) = lbl_803614B8;
    F(448) = 0;
    FF(452) = lbl_803614B8;
    FF(456) = lbl_803614B8;
    F(460) = 0;
    F(464) = 0;
    F(468) = 0;
    F(472) = 0;
    F(476) = 0;
}
#pragma opt_propagation reset

} /* extern "C" */
