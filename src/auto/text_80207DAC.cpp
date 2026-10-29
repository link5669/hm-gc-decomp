// Code of main that had no source file yet: decomp.wtf gave it this one.
#include "common.h"

extern "C" {

/* QV=2.0p1 */
struct T_80207DAC { char name[664]; char names[8][128]; s32 n; };
u32 strlen(const char *);
char *strcpy(char *, const char *);
char *strcat(char *, const char *);

BOOL fn_80207DAC(T_80207DAC *p, char *d, u32 max) {
    u32 n = strlen(p->name);
    if (p->n != -1) {
        n += strlen(p->names[p->n]);
    }
    if (n >= max) {
        return FALSE;
    }
    strcpy(d, p->name);
    if (p->n != -1) {
        strcat(d, p->names[p->n]);
    }
    return TRUE;
}

} /* extern "C" */
