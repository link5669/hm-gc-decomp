// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern void *lbl_8035AAD8;
extern char lbl_80363A14[4];
extern char lbl_80363A18[6];
u32 strlen(const char *);
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
char *__nwa__FUl(u32);
void strcpy(char *, const char *);
void fn_80060E30(...);
void fn_8010F3DC(u8 *, u32, u32, u32, u32);

} /* extern "C" */

struct R8010FD54 { u8 pad[12]; char *name; };
struct C80215F50 { C80215F50(); ~C80215F50(); u8 b[40]; R8010FD54 *rd; u32 f44; u8 c[8]; };

extern "C" {
void fn_80215BFC(C80215F50 *);
s32 fn_80215C84(C80215F50 *, char *, char *, int, int);

s32 fn_8010FD54(u8 *p, u32 a, char *path, u32 unused, u32 c, u32 d) {
    C80215F50 f;
    s32 e = fn_80215C84(&f, path, lbl_80363A14, 2, 0);
    if (e != 0) {
        fn_80060E30(e, lbl_80363A18, path, lbl_80363A14);
    }
    char *name = f.rd->name;
    if (lbl_8035AAD8 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035AAD8);
    *(char **)(p + 484) = __nwa__FUl(strlen(name) + 1);
    fn_800F7E98();
    if (*(char **)(p + 484) == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    strcpy(*(char **)(p + 484), name);
    fn_8010F3DC(p, a, f.f44, c, d);
    fn_80215BFC(&f);
    *(s32 *)(p + 488) = 1;
    return 0;
}

} /* extern "C" */
