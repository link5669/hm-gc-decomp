#include "common.h"
namespace m80268178 {
/* Functions from 0x80268178 to 0x80268290, found by decomp-toolkit. */

extern "C" {

extern "C" {

}


extern "C" void fn_80268178(s32 *object, s32 value) {
    s32 index;
    switch (value) {
    case 13: index = 1; break;
    case 12: index = 2; break;
    case 10: case 11: case 14: index = 3; break;
    case 1: case 5: case 6: index = 4; break;
    case 2: case 3: index = 5; break;
    case 0: case 4: index = 6; break;
    case 9: index = 7; break;
    case 8: index = 8; break;
    case 7: index = 9; break;
    case 15: index = 20; break;
    default: index = 0; break;
    }
    {
        s32 current = object[index + 346];
        if (current != value) return;
        object[index + 346] = 15;
    }
}

extern "C" {

}


extern "C" void fn_8026820C(s32 *object, u32 value) {
    s32 index;
    switch (value) {
    case 13: index = 1; break;
    case 12: index = 2; break;
    case 10: case 11: case 14: index = 3; break;
    case 1: case 5: case 6: index = 4; break;
    case 2: case 3: index = 5; break;
    case 0: case 4: index = 6; break;
    case 9: index = 7; break;
    case 8: index = 8; break;
    case 7: index = 9; break;
    case 15: index = 20; break;
    default: index = 0; break;
    }
    object[index + 346] = value;
}

} /* extern "C" */

} /* namespace m80268178 */

namespace m80268290 {
// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).

extern "C" {

struct X { u8 pad_[88]; virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void stop(int); virtual void vol(int, f32); virtual void s23(); virtual void pitch(f32); };
struct E { u8 pad[24]; u32 n; void *a[10]; void *b[5]; };
struct S { E ent[15]; u8 pad[1340 - 15 * 88]; int on; u8 pad1344[4]; f32 *f1348; u8 pad1352[4]; X *x1356; u32 f1360; u8 pad1364[4]; X *x1368; u32 f1372; u8 pad1376[4]; u32 f1380; int arr[20]; f32 f1464; };
extern f32 lbl_80366D48;
extern f32 lbl_80366D4C;
extern f32 lbl_80366D50;
int rand(void);
void fn_801FEC18(X *, void *, u32, u32, int);
static inline int cat(u32 id) {
    int k;
    switch (id) {
    case 13: k = 1; break;
    case 12: k = 2; break;
    case 10: case 11: case 14: k = 3; break;
    case 1: case 5: case 6: k = 4; break;
    case 2: case 3: k = 5; break;
    case 0: case 4: k = 6; break;
    case 9: k = 7; break;
    case 8: k = 8; break;
    case 7: k = 9; break;
    case 15: k = 20; break;
    default: k = 0; break;
    }
    return k;
}
static inline u32 rnd(u32 n) { u32 r = 0; if (n) r = rand() % n; return r; }
void fn_80268290(S *s, u32 id) {
    if (!s->on) return;
    {
        u32 r;
        X *a;
        X *b;
        if (s->ent[id].n) {
            r = rnd(s->ent[id].n);
            s->x1356->stop(0);
            s->x1368->stop(0);
            s->x1356->vol(0, *s->f1348);
            s->x1368->vol(0, *s->f1348);
            a = s->x1356;
            b = s->x1368;
            if (s->ent[id].a[r]) fn_801FEC18(a, s->ent[id].a[r], s->f1360, s->f1372, 0);
            if (s->ent[id].b[r]) fn_801FEC18(b, s->ent[id].b[r], s->f1372, s->f1360, 0);
            s->x1356->pitch(lbl_80366D4C);
            s->x1368->pitch(lbl_80366D50);
            s->f1380 = id;
            s->f1464 = lbl_80366D48;
        } else {
            int k = cat(id);
            if (s->arr[k] == (int)id) s->arr[k] = 15;
        }
    }
}

} /* extern "C" */

} /* namespace m80268290 */
