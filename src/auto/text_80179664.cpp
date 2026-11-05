// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void *__ct__9C8015D9A4Fv(void *p);
void *__dt__9C8015D9A4Fv(void *p, s16 f);
void *__register_global_object(void *obj, void *dtor, void *chain);
extern f32 lbl_803596E0[];
extern f32 lbl_8035AD50;
u8 lbl_8032FF18[12];
u8 lbl_8032FF24[300];
u8 lbl_80330050[12];
u8 lbl_8033005C[300];
void fn_80179664(void) {
    lbl_8035AD50 = lbl_803596E0[0];
    __register_global_object(__ct__9C8015D9A4Fv(lbl_8032FF24), (void *)__dt__9C8015D9A4Fv, lbl_8032FF18);
    __register_global_object(__ct__9C8015D9A4Fv(lbl_8033005C), (void *)__dt__9C8015D9A4Fv, lbl_80330050);
}

__declspec(section ".ctors") static void (*const ctor_80179664)(void) = fn_80179664;

} /* extern "C" */
