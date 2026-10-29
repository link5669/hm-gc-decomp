// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 *lbl_8035B79C;
extern u8 *lbl_8035B7BC;
extern u8 *lbl_8035A0A4;
extern u8 *lbl_8035B65C;
extern u8 *lbl_8035A074;
extern u8 *lbl_8035A01C;
void fn_80099EEC(u8 *p, u32 a);
void fn_80268A8C(u8 *p, s32 a, f32 f);
void fn_8026DD40(u8 *p, s32 a, f32 f);
void fn_8003E77C(u8 *p, u32 a);
void fn_8003E66C(u8 *p);
void fn_8003B3E8(u8 *p, s32 a);

s32 fn_80099D18(u8 *p, u32 flags) {
    if (*(s32 *)(p + 700) != 0) return 6;
    if ((flags & 2) && *(s32 *)(p + 708) == 0) return 2;
    if (flags & 8) {
        if (*(s32 *)(p + 236) == 0) fn_80099EEC(p, *(u32 *)(p + 196));
    } else if (flags & 0x10) {
        if (*(s32 *)(p + 236) == 0) fn_80099EEC(p, *(u32 *)(p + 188));
    } else if (flags & 0x20) {
        if (*(s32 *)(p + 236) == 0) fn_80099EEC(p, *(u32 *)(p + 204));
    } else if (flags & 0x40) {
        if (*(s32 *)(p + 236) == 0) fn_80099EEC(p, *(u32 *)(p + 192));
    } else {
        if (*(s32 *)(p + 240) != 0) {
            if (*(u32 *)(p + 212) == *(u32 *)(p + 216)) {
                fn_80268A8C(lbl_8035B79C, 0, *(f32 *)(p + 740));
                fn_8026DD40(lbl_8035B7BC, 1, *(f32 *)(p + 736));
            }
            fn_8003E77C(lbl_8035A0A4, *(u32 *)(p + 212));
            *(u32 *)(p + 212) = 0;
            if (lbl_8035B65C == 0 || !(*(u32 *)(lbl_8035B65C + 140) & 0x80)) {
                fn_8003E66C(lbl_8035A0A4);
                fn_8003B3E8(lbl_8035A074, 0);
            }
            if (lbl_8035A01C != 0 && *(s32 *)(lbl_8035A01C + 28) == 0) {
                fn_80268A8C(lbl_8035B79C, 0, *(f32 *)(p + 740));
            }
            if (lbl_8035B65C != 0 && (*(u32 *)(lbl_8035B65C + 140) & 0x80)) {
                fn_80268A8C(lbl_8035B79C, 0, *(f32 *)(p + 740));
                fn_8026DD40(lbl_8035B7BC, 1, *(f32 *)(p + 736));
            }
        }
        *(s32 *)(p + 236) = 0;
        *(s32 *)(p + 240) = 0;
    }
    return 0;
}

} /* extern "C" */
