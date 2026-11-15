#ifndef MP_DRAW_H
#define MP_DRAW_H
#include <dolphin/types.h>
void mp_draw_begin(void);
void mp_draw_box(f32 x, f32 y, f32 w, f32 h, u32 rgba);
void mp_draw_text(f32 x, f32 y, const char *s, f32 scale, u32 rgba);
void mp_draw_text_centered(f32 cx, f32 y, const char *s, f32 scale, u32 rgba);
int mp_text_width(const char *s, f32 scale);
#endif
