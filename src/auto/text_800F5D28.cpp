// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800F9FE0(void *o, int c);
char *strncpy(char *d, const char *s, u32 n);
typedef struct S800F5D28 { void *f0; u8 pad[16]; char buf[256]; } S800F5D28;
void fn_800F5D28(S800F5D28 *self, const char *str) {
    char *p;
    fn_800F9FE0(self->f0, '/');
    fn_800F9FE0(self->f0, '/');
    fn_800F9FE0(self->f0, ' ');
    strncpy(self->buf, str, 255);
    self->buf[255] = 0;
    for (p = self->buf; *p != 0; p++) fn_800F9FE0(self->f0, *p);
}

} /* extern "C" */
