#ifndef MP_SPLIT_H
#define MP_SPLIT_H
#include <dolphin/types.h>
int mp_split_render(void *game, void *gx, const f32 *eye2, const f32 *at2);
void mp_cam_get_pos(void *cam, f32 *pos);
void mp_cam_get_basis(void *cam, f32 *right, f32 *up, f32 *fwd);
#endif
