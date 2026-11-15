#ifndef MP_H
#define MP_H
#include <dolphin/types.h>
void *OSGetArenaLo(void);
void OSSetArenaLo(void *p);
void OSReport(const char *fmt, ...);
#endif
