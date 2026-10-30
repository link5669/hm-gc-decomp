// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

typedef struct N { struct N *ch; u8 pad[8]; u16 n; u8 pad2[6]; } N;
void fn_80212DA4(N *n, void *a);
inline u16 fn_80212D9C(N *n) { return n->n; }
void fn_80212B10(N *n, void *a) {
    u32 i;
    fn_80212DA4(n, a);
    for (i = 0; i < fn_80212D9C(n); i++) fn_80212B10(&n->ch[i], a);
}

} /* extern "C" */
