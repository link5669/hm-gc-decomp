// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Vec8026 { f32 x, y, z; } Vec8026;
} /* extern "C" */
struct V8026D368 {
    u8 pad[36];
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void m(Vec8026 *);
};
extern "C" {
extern V8026D368 *volatile lbl_8035B7C4;
void fn_80107244(void *, Vec8026 *);
void fn_80103CA0(void *, void *);

void fn_8026D368(void *self, void *obj) {
    Vec8026 a, b;
    volatile Vec8026 d;
    fn_80107244(obj, &a);
    fn_80107244(lbl_8035B7C4, &b);
    d.x = a.x - b.x;
    d.y = a.y - b.y;
    d.z = a.z - b.z;
    fn_80103CA0(lbl_8035B7C4, obj);
    lbl_8035B7C4->m((Vec8026 *)&d);
}

} /* extern "C" */
