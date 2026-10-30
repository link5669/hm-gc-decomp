// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct V { f32 x, y, z; };
struct B8 { u32 a, b; };
extern f32 lbl_80361B28, lbl_80361B2C;
extern char lbl_80361AF4[8], lbl_80361AFC[8];
extern char lbl_8029A818[];
struct L { u8 pad[52]; u8 *f52; };
struct T;
struct S224 { virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3(); virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7(); virtual void a8(); virtual void a9(); virtual void a10(); virtual void a11(); virtual void a12(); virtual void a13(); virtual void a14(); virtual void a15(); virtual void a16(); virtual void a17(); virtual void a18(); virtual void a19(); virtual void a20(); virtual void a21(); virtual void a22(); virtual void a23(); virtual void a24(); virtual void a25(); virtual void a26(); virtual void a27(); virtual void a28(); virtual void a29(); virtual void a30(); virtual void a31(); virtual void a32(); virtual void add(B8 *, S224 *, L *, u32 *, B8 *); };
struct T { u8 pad[224]; S224 *f224; u8 pad228[52]; u8 f280[12]; V f292; V f304; V f316; u8 f328[8]; L *f336; u8 pad340[20]; int f360; int f364; };
int fn_80244D40(L *, int, const char *);
void fn_80245E58(L *, int, void *);
void fn_80245D9C(L *, int, V *, V *, void *, int);
u32 fn_8024548C(L *, int, int, int, B8 *, u32 *, B8 *);
void fn_802494A4(T *, int);
void fn_8009FBC8(T *t, int start) {
    int old = t->f364;
    if (start < old) return;
    if (!t->f336) return;
    if (old >= 0) t->f336->f52[old] = 0;
    t->f364 = start;
    int inside = fn_80244D40(t->f336, t->f364, lbl_80361AF4);
    int done = 0;
    while (t->f364 < t->f360 - 1) {
        t->f364++;
        u8 *vis = t->f336->f52;
        if (vis[t->f364] & 1) {
            if (fn_80244D40(t->f336, t->f364, lbl_80361AF4)) inside = 1;
        } else if (!inside) {
            vis[t->f364] = 1;
            fn_80245E58(t->f336, t->f364, t->f280);
            t->f316.x = lbl_80361B28;
            t->f316.y = lbl_80361B28;
            t->f316.z = lbl_80361B2C;
            t->f292.x = lbl_80361B28;
            t->f292.y = lbl_80361B2C;
            t->f292.z = lbl_80361B28;
            fn_80245D9C(t->f336, t->f364, &t->f316, &t->f292, t->f328, 0);
            t->f304.x = t->f292.y * t->f316.z - t->f292.z * t->f316.y;
            t->f304.y = t->f292.z * t->f316.x - t->f292.x * t->f316.z;
            t->f304.z = t->f292.x * t->f316.y - t->f292.y * t->f316.x;
            B8 a[10];
            B8 c[10];
            u32 b[10];
            u32 n = fn_8024548C(t->f336, t->f364, -1, 10, a, b, c);
            for (u32 i = 0; i < n; i++) t->f224->add(&a[i], t->f224, t->f336, &b[i], &c[i]);
            done = 1;
            break;
        } else {
            if (fn_80244D40(t->f336, t->f364, lbl_8029A818)) inside = 0;
            else if (fn_80244D40(t->f336, t->f364, lbl_80361AFC)) inside = 0;
        }
    }
    if (done) fn_802494A4(t, 2);
    else t->f364 = old;
}

} /* extern "C" */
