// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 pad[80];
    char *names[10];
} S_1ACEF8;
extern const char lbl_80364EB4[2];
char *strrchr(const char *s, int c);
unsigned long strlen(const char *s);
char *strcpy(char *d, const char *s);
char *strcat(char *d, const char *s);

void fn_801ACEF8(S_1ACEF8 *self, s32 idx, char **pp) {
    char buf[256];
    char *path;
    s32 err;
    char *name;
    char *slash;
    char *slash2;
    s32 i;

    i = idx - 57;
    if (self->names[i] == 0 || pp == 0 || idx > 66) return;
    path = *pp;
    err = 0;
    slash = strrchr(path, '\\');
    if (slash == 0) {
        name = path;
        if (strlen(self->names[i]) + 2 < 255)
            strcpy(buf, self->names[i]);
        else
            err = 1;
    } else {
        *slash = 0;
        slash2 = strrchr(path, '\\');
        if (slash2 != 0) {
            *slash2 = 0;
            strcpy(buf, path);
            strcat(buf, lbl_80364EB4);
            *slash2 = '\\';
            if (strlen(buf) + strlen(self->names[i]) + 2 < 255)
                strcat(buf, self->names[i]);
            else
                err = 1;
        } else {
            if (strlen(self->names[i]) + 2 < 255)
                strcpy(buf, self->names[i]);
            else
                err = 1;
        }
        name = slash + 1;
        *slash = '\\';
    }
    if (err == 0) {
        strcat(buf, lbl_80364EB4);
        if (strlen(buf) + strlen(name) + 2 < 255)
            strcat(buf, name);
        else
            err = 1;
    }
    if (err == 0) strcpy(path, buf);
}

} /* extern "C" */
