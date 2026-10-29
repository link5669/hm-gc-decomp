// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#include <stdarg.h>
typedef struct { char *name; u32 x; u32 y; f32 w; f32 h; } E_802196E0;
typedef struct { u8 pad[4]; E_802196E0 *ents; s32 n; u8 pad2[4]; u32 size; } T_802196E0;
extern u32 lbl_8035A9F4;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7E98(void);
void fn_800F7EC0(u32);
void fn_800E904C(char *, const char *, va_list);
char *strcpy(char *, const char *);

#pragma peephole off
void fn_802196E0(T_802196E0 *p, const char *fmt, f32 a, f32 b, f32 c, f32 d, ...) {
    va_list va;
    char *buf;
    if (lbl_8035A9F4 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035A9F4);
    buf = new char[p->size];
    fn_800F7E98();
    if (buf == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    va_start(va, fmt);
    fn_800E904C(buf, fmt, va);
    p->ents[p->n].x = a;
    p->ents[p->n].y = b;
    p->ents[p->n].w = c;
    p->ents[p->n].h = d;
    strcpy(p->ents[p->n].name, buf);
    p->n++;
    delete[] buf;
}
#pragma peephole reset

} /* extern "C" */
