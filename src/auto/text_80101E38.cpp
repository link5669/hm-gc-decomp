// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Key_80101E38 { u8 pad[10]; u16 f10; } Key_80101E38;
typedef struct Elem_80101E38 { u8 pad[48]; u8 f48[32]; } Elem_80101E38;
typedef struct Obj_80101E38 { u8 pad[24]; void *a; Key_80101E38 *keys; Key_80101E38 *keys2; } Obj_80101E38;
typedef struct P_80101E38 { Obj_80101E38 *f0; u8 pad[28]; u16 f32; u16 f34; u16 f36; u16 f38; u8 pad40[14]; u16 f54; } P_80101E38;
typedef struct Q_80101E38 { u8 pad[40]; Elem_80101E38 *f40; } Q_80101E38;
void fn_8021BE0C(void *, Key_80101E38 *, u16, void *, f32);
void fn_8021BD48(void *, Key_80101E38 *, u16, f32 *, f32);
void fn_80106634(Q_80101E38 *);
void fn_80106474(Q_80101E38 *, f32 *);

static inline void *getA(P_80101E38 *p) { return p->f0->a; }
void fn_80101E38(P_80101E38 *p, Q_80101E38 *q, f32 t, f32 *scale) {
    void *a;
    u32 i;
    u32 end;
    f32 v[3];
    a = getA(p);
    end = p->f32 + p->f34;
    for (i = p->f32; i < end; i++) {
        fn_8021BE0C(a, &p->f0->keys[i], p->f54, q->f40[p->f0->keys[i].f10].f48, t);
    }
    fn_80106634(q);
    if (p->f38 != 0) {
        fn_8021BD48(a, &p->f0->keys2[p->f36], p->f54, v, t);
        if (scale != 0) {
            v[0] *= scale[0];
            v[1] *= scale[1];
            v[2] *= scale[2];
        }
        fn_80106474(q, v);
    }
}

} /* extern "C" */
