// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

}
struct C801883E0 { C801883E0(); u8 pad[204]; };
struct C8018E150 { C8018E150(); u8 pad[168]; };
struct E8 { u32 w[2]; };
struct Res { u8 pad[4]; u16 type; };
struct G { u8 pad[8]; u8 *db; };
struct Obj { u8 pad[692]; E8 *arr; u32 n; u32 f700; void *f704; };
extern "C" {
extern void *lbl_8035B320;
extern G *lbl_8035B460;
void fn_800604C4(s32, s32, s32, s32);
void fn_800F7EC0(void *);
void fn_800F7E98(void);
Res *fn_800F9398(void *, E8 *);
Res *fn_800F9788(void *, E8 *, E8 *);
void fn_800F6E88(E8 *, E8 *);
void fn_80188144(C801883E0 *, u8 *, Res *, int);
void fn_8018DFAC(C8018E150 *, u8 *, Res *);
void fn_80232DF8(Obj *o, E8 *a, E8 *b, u32 n, u32 x) {
    E8 *pb;
    E8 *pa;
    u32 off;
    u32 i;
    if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
    fn_800F7EC0(lbl_8035B320);
    o->arr = new E8[n];
    fn_800F7E98();
    if (o->arr == 0) fn_800604C4(-4, 0, 0, 0);
    o->n = n;
    pb = b; pa = a; i = 0; off = 0;
    for (; i < n; pb++, pa++, off += 8, i++) {
        Res *t;
        u8 *db = lbl_8035B460->db;
        E8 *nm = pb;
        if (nm == 0 || *(s8 *)nm == 0) t = fn_800F9398(db + 144, pa);
        else t = fn_800F9788(db + 168, nm, pa);
        if (t == 0) continue;
        if (t->type == 8) {
            fn_800F6E88((E8 *)((u8 *)o->arr + off), pa);
            o->f704 = 0;
        } else if (t->type == 3) {
            b = (E8 *)t;
            C801883E0 *c;
            if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B320);
            c = new C801883E0;
            fn_800F7E98();
            if (c == 0) fn_800604C4(-4, 0, 0, 0);
            fn_80188144(c, lbl_8035B460->db, (Res *)b, 0);
            o->f704 = c;
        } else if (t->type == 2) {
            b = (E8 *)t;
            C8018E150 *c;
            if (lbl_8035B320 == 0) fn_800604C4(-2, 0, 0, 0);
            fn_800F7EC0(lbl_8035B320);
            c = new C8018E150;
            fn_800F7E98();
            if (c == 0) fn_800604C4(-4, 0, 0, 0);
            fn_8018DFAC(c, lbl_8035B460->db, (Res *)b);
            o->f704 = c;
        }
    }
    o->f700 = x;
}

} /* extern "C" */
