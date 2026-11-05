// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern volatile u32 lbl_80365A28;
extern volatile u32 lbl_80365A2C;
typedef struct T80222160 { u32 a; u32 b; } T80222160;
void fn_80276930(void);
void fn_802769F0(void (*f)(void), T80222160 *d);
void fn_80221B7C(void *a, void *b);
#pragma scheduling 604
void fn_80222160(void *a, void *b) {
    T80222160 t;
    T80222160 u;
    fn_802769F0(fn_80276930, (t.a = lbl_80365A28, t.b = lbl_80365A2C, &t));
    fn_80221B7C(a, b);
}
#pragma scheduling reset

} /* extern "C" */
