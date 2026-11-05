// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800FB0F8(void *, void *);
f32 fn_800FB2E0(void *);
u32 fn_800FB33C(void *);
void fn_800FB064(void *, void *);
void fn_801DCA84(void *, s32, void *, void *);

void fn_801C4768(u8 *p, s32 a, void *b, void *c);
void fn_801C493C(void);
void fn_801C0A10(void);
void fn_801BDD3C(void);
void fn_801C48AC(void);
void fn_801DB744(void);
void fn_801C0834(void);
void fn_801DC730(void);
void fn_8009F150(void);
void fn_801DBE0C(void);
void fn_801DBACC(void);
void fn_801BDA5C(void);
void fn_801BDA0C(void);
void fn_801BDB4C(void);
void fn_801BDB18(void);
void fn_801C079C(void);
void fn_801C07E8(void);
void fn_801C0750(void);
void fn_801C0704(void);
void fn_801C420C(void);
void fn_8002A984(void);
void fn_801C4AB8(void);
void fn_801DB740(void);
void fn_801DB01C(void);
void fn_801DB00C(void);
void fn_801DBF24(void);
void fn_801DAEE4(void);
void fn_801C4658(void);
void fn_801DAC0C(void);
void fn_801DA954(void);
void fn_801C457C(void);
void fn_801DAAE4(void);
void fn_801DA5E8(void);
void fn_801DA4C0(void);
void fn_801DA398(void);
void fn_801DA1E4(void);
void fn_801D9F80(void);
void fn_801D9E80(void);
void fn_801D9D80(void);
void fn_801D99B4(void);
void fn_801D95E8(void);
void fn_801D921C(void);
void fn_801D8E50(void);
void fn_801D8CBC(void);
void fn_801D8B9C(void);
void fn_801C44C0(void);
void fn_801D895C(void);
void fn_801C4404(void);
void fn_801D871C(void);
void fn_801D85FC(void);
void fn_801D84DC(void);
void fn_801D83BC(void);
void fn_801D829C(void);
void fn_801D817C(void);
void fn_801D805C(void);
void fn_801D7F3C(void);
void fn_801D7E1C(void);
void fn_801D7CE0(void);
void fn_801D7BC8(void);
void fn_801D791C(void);
void fn_801D7680(void);
void fn_801C4084(void);
void fn_801C405C(void);
void fn_801D6C10(void);
void fn_801DAE5C(void);
void fn_801C42CC(void);
void fn_801C4214(void);
void fn_801D7248(void);
void fn_801D7148(void);
void fn_801C4134(void);
void fn_801D6F48(void);
void fn_801C49B0(void);
void fn_801DB220(void);
void fn_801DB4B0(void);
void fn_8009F130(void);
void fn_801DD9D4(void);
void fn_8009F134(void);
void fn_801B30F0(void);
void fn_801C488C(void);
void *lbl_802EBDD8[81] = { 0, 0, (void *)fn_801C4768, (void *)fn_801C493C, (void *)fn_801C0A10, (void *)fn_801BDD3C, (void *)fn_801C48AC, (void *)fn_801DB744, (void *)fn_801C0834, (void *)fn_801DC730, (void *)fn_8009F150, (void *)fn_801DBE0C, (void *)fn_801DBACC, (void *)fn_801BDA5C, (void *)fn_801BDA0C, (void *)fn_801BDB4C, (void *)fn_801BDB18, (void *)fn_801C079C, (void *)fn_801C07E8, (void *)fn_801C0750, (void *)fn_801C0704, (void *)fn_801C420C, (void *)fn_8002A984, (void *)fn_801C4AB8, (void *)fn_801DB740, (void *)fn_801DB01C, (void *)fn_801DB00C, (void *)fn_801DBF24, (void *)fn_801DAEE4, (void *)fn_801C4658, (void *)fn_801DAC0C, (void *)fn_801DA954, (void *)fn_801C457C, (void *)fn_801DAAE4, (void *)fn_801DA5E8, (void *)fn_801DA4C0, (void *)fn_801DA398, (void *)fn_801DA1E4, (void *)fn_801D9F80, (void *)fn_801D9E80, (void *)fn_801D9D80, (void *)fn_801D99B4, (void *)fn_801D95E8, (void *)fn_801D921C, (void *)fn_801D8E50, (void *)fn_801D8CBC, (void *)fn_801D8B9C, (void *)fn_801C44C0, (void *)fn_801D895C, (void *)fn_801C4404, (void *)fn_801D871C, (void *)fn_801D85FC, (void *)fn_801D84DC, (void *)fn_801D83BC, (void *)fn_801D829C, (void *)fn_801D817C, (void *)fn_801D805C, (void *)fn_801D7F3C, (void *)fn_801D7E1C, (void *)fn_801D7CE0, (void *)fn_801D7BC8, (void *)fn_801D791C, (void *)fn_801D7680, (void *)fn_801C4084, (void *)fn_801C405C, (void *)fn_801D6C10, (void *)fn_801DAE5C, (void *)fn_801C42CC, (void *)fn_801C4214, (void *)fn_801D7248, (void *)fn_801D7148, (void *)fn_801C4134, (void *)fn_801D6F48, (void *)fn_801C49B0, (void *)fn_801DB220, (void *)fn_801DB4B0, (void *)fn_8009F130, (void *)fn_801DD9D4, (void *)fn_8009F134, (void *)fn_801B30F0, (void *)fn_801C488C };

void fn_801C4768(u8 *p, s32 a, void *b, void *c) {
    switch (a) {
    case 157:
        fn_800FB0F8(c, p + 356);
        break;
    case 158:
        *(f32 *)(p + 360) = fn_800FB2E0(c);
        break;
    case 159:
        *(u32 *)(p + 364) = fn_800FB33C(c);
        break;
    case 160:
        *(u32 *)(p + 368) = fn_800FB33C(c);
        break;
    case 161:
        *(u32 *)(p + 372) = 1;
        break;
    case 162:
        *(u32 *)(p + 376) = 1;
        break;
    case 163:
        *(u32 *)(p + 380) = 1;
        break;
    case 164:
        *(u32 *)(p + 384) = 1;
        break;
    case 165:
        *(u32 *)(p + 388) = 1;
        break;
    case 166:
        *(u32 *)(p + 392) = 1;
        break;
    case 167:
        *(u32 *)(p + 396) = 1;
        break;
    case 168:
        *(u32 *)(p + 400) = 1;
        break;
    case 169:
        fn_800FB064(c, p + 404);
        break;
    case 170:
        fn_800FB064(c, p + 412);
        break;
    case 171:
        fn_800FB064(c, p + 420);
        break;
    default:
        fn_801DCA84(p, a, b, c);
        break;
    }
}

} /* extern "C" */
