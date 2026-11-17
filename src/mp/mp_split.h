#ifndef MP_SPLIT_H
#define MP_SPLIT_H
#include <dolphin/types.h>
int mp_split_render(void *game, void *gx, const f32 *eye2, const f32 *at2);
int mp_cam2_basis(f32 *eye, f32 *fwd, f32 *side, f32 *up);
void mp_cam2_recenter(const f32 *dir);
void mp_cam_get_pos(void *cam, f32 *pos);
void mp_cam_get_basis(void *cam, f32 *right, f32 *up, f32 *fwd);
void *mp_split_cam2(void);
void mp_draw_tags(void *cam, f32 x0, f32 y0, f32 sw, f32 sh);
int mp_player_pos(void *player, f32 *pos);
#endif
