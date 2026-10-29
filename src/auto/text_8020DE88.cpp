// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C80214C34 {
    u32 f0;
    u8 pad[64];
    char name[380];
    C80214C34();
    ~C80214C34();
};
struct C8020F398 {
    u8 pad[20];
    C8020F398();
};
struct M8020DE88 {
    u8 pad[96];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual s32 v9(C80214C34 *it);
    virtual s32 v10(C80214C34 *it);
    virtual void v11();
    virtual void *v12();
};
extern "C" {
extern char lbl_8036581C[2];
extern char lbl_80365820[2];
extern void *lbl_8035A9F4;
char *strcpy(char *d, const char *s);
char *strstr(const char *s, const char *t);
u32 strlen(const char *s);
void fn_800604C4(s32 a, s32 b, s32 c, s32 d);
void fn_800F7EC0(void *heap);
void fn_800F7E98(void);
void fn_8020EFE4(C8020F398 *l, void *x, s32 z);
void fn_800FA474(char *src, char *dst, s32 n);
s32 fn_80210D54(char *name, char *dir, char *pat);
void fn_8020EC24(C8020F398 *l, s32 i, char *name);
void fn_8020ED44(C8020F398 *l, s32 i, u32 v);
void fn_8020EDB8(C8020F398 *l, s32 i, s32 z);

C8020F398 *fn_8020DE88(u8 *self, char *path) {
    C80214C34 it;
    char buf[32];
    char name[32];
    C8020F398 *list;
    s32 n;
    char *s;
    if (path == 0) {
        strcpy(buf, lbl_8036581C);
        path = buf;
    } else {
        strcpy(buf, path);
        s = strstr(path, lbl_80365820);
        if (s == 0) {
            path = buf + strlen(buf);
        } else {
            *s = 0;
            path = s + 1;
        }
    }
    if (lbl_8035A9F4 == 0) {
        fn_800604C4(-2, 0, 0, 0);
    }
    fn_800F7EC0(lbl_8035A9F4);
    list = new C8020F398;
    fn_800F7E98();
    if (list == 0) {
        fn_800604C4(-4, 0, 0, 0);
    }
    fn_8020EFE4(list, (*(M8020DE88 **)(self + 1724))->v12(), 0);
    n = 0;
    if ((*(M8020DE88 **)(self + 1724))->v9(&it) != 0) {
        do {
            fn_800FA474(it.name, name, 31);
            if (fn_80210D54(name, buf, path) != 0) {
                fn_8020EC24(list, n, name);
                fn_8020ED44(list, n, it.f0);
                fn_8020EDB8(list, n, 0);
                n++;
            }
        } while ((*(M8020DE88 **)(self + 1724))->v10(&it) != 0);
    }
    return list;
}

} /* extern "C" */
