// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S801DD9D4 {
    u8 pad0[132];
    u32 f132, f136, f140, f144;
    u8 f148[8];
    u8 f156[8];
    u32 f164;
    u8 f168[8];
    u8 f176[8];
    u32 f184;
    u8 f188[8];
    u8 f196[8];
    u32 f204;
    u8 f208[8];
    u8 f216[8];
    u32 f224;
    u8 f228[8];
    u8 f236[8];
    u32 f244;
    u8 f248[8];
    u8 f256[8];
    u32 f264;
    u8 f268[8];
    u8 f276[8];
    u32 f284, f288;
    u8 f292[8];
    u8 f300[8];
    u32 f308, f312, f316, f320, f324, f328;
    f32 f332, f336, f340, f344;
    u32 f348, f352;
} S801DD9D4;
void fn_801C0834(S801DD9D4 *, S801DD9D4 *);
void fn_800F6E88(u8 *, u8 *);
void fn_801DD9D4(S801DD9D4 *d, S801DD9D4 *s) {
    fn_801C0834(d, s);
    d->f132 = s->f132;
    d->f136 = s->f136;
    d->f140 = s->f140;
    d->f144 = s->f144;
    fn_800F6E88(d->f148, s->f148);
    fn_800F6E88(d->f156, s->f156);
    d->f164 = s->f164;
    fn_800F6E88(d->f168, s->f168);
    fn_800F6E88(d->f176, s->f176);
    d->f184 = s->f184;
    fn_800F6E88(d->f188, s->f188);
    fn_800F6E88(d->f196, s->f196);
    d->f204 = s->f204;
    fn_800F6E88(d->f208, s->f208);
    fn_800F6E88(d->f216, s->f216);
    d->f224 = s->f224;
    fn_800F6E88(d->f228, s->f228);
    fn_800F6E88(d->f236, s->f236);
    d->f244 = s->f244;
    fn_800F6E88(d->f248, s->f248);
    fn_800F6E88(d->f256, s->f256);
    d->f264 = s->f264;
    fn_800F6E88(d->f268, s->f268);
    fn_800F6E88(d->f276, s->f276);
    d->f284 = s->f284;
    d->f288 = s->f288;
    fn_800F6E88(d->f292, s->f292);
    fn_800F6E88(d->f300, s->f300);
    d->f308 = s->f308;
    d->f312 = s->f312;
    d->f316 = s->f316;
    d->f320 = s->f320;
    d->f324 = (u16)s->f324;
    d->f328 = s->f328;
    d->f332 = s->f332;
    d->f336 = s->f336;
    d->f340 = s->f340;
    d->f344 = s->f344;
    d->f348 = s->f348;
    d->f352 = s->f352;
}

} /* extern "C" */
