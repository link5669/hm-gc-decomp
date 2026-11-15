#ifndef MP_H
#define MP_H
typedef signed char s8; typedef unsigned char u8; typedef short s16; typedef unsigned short u16;
typedef int s32; typedef unsigned int u32; typedef float f32; typedef int BOOL;
void *OSGetArenaLo(void);
void OSSetArenaLo(void *p);
void OSReport(const char *fmt, ...);
#endif
