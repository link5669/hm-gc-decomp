// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u16 loopFlag;
    u16 format;
    u16 loopAddressHi;
    u16 loopAddressLo;
    u16 endAddressHi;
    u16 endAddressLo;
    u16 currentAddressHi;
    u16 currentAddressLo;
} AXPBADDR204;
typedef struct {
    u16 c0, c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15;
    u16 gain;
    u16 pred_scale;
    u16 yn1;
    u16 yn2;
} AXPBADPCM204;
typedef struct {
    u16 ratioHi;
    u16 ratioLo;
    u16 currentAddressFrac;
    u16 last_samples[4];
} AXPBSRC204;
typedef struct {
    u8 pad0[8];
    u32 rate;
    u8 pad12[16];
    AXPBADPCM204 *adpcm;
} Info204;
typedef struct {
    u8 pad0[28];
    u32 start;
    u8 pad32[4];
    u32 len;
    u8 pad40[264];
    void *voice;
} Self204;
void fn_800C9A68(void *voice, u32 type);
void fn_800C9B74(void *voice, AXPBADDR204 *addr);
void fn_800C9948(void *voice, u32 x);
void fn_800C9C84(void *voice, AXPBADPCM204 *adpcm);
void fn_800C9D28(void *voice, AXPBSRC204 *src);

s32 fn_80204C1C(Self204 *self, Info204 *info) {
    AXPBADDR204 addr;
    AXPBSRC204 src;
    AXPBADPCM204 adpcm;
    u32 start;
    u32 end;
    start = self->start * 2 + 2;
    end = (self->start + self->len) * 2 - 1;
    addr.loopFlag = 1;
    addr.format = 0;
    addr.loopAddressHi = start >> 16;
    addr.loopAddressLo = start;
    addr.endAddressHi = end >> 16;
    addr.endAddressLo = end;
    addr.currentAddressHi = start >> 16;
    addr.currentAddressLo = start;
    adpcm = *info->adpcm;
    src.ratioHi = info->rate / 32000;
    src.ratioLo = info->rate % 32000;
    src.currentAddressFrac = 0;
    src.last_samples[0] = 0;
    src.last_samples[1] = 0;
    src.last_samples[2] = 0;
    src.last_samples[3] = 0;
    fn_800C9A68(self->voice, 1);
    fn_800C9B74(self->voice, &addr);
    fn_800C9948(self->voice, 0);
    fn_800C9C84(self->voice, &adpcm);
    fn_800C9D28(self->voice, &src);
    return 0;
}

} /* extern "C" */
