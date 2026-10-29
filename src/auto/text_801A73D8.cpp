// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct ValE { u8 pad[8]; s32 type; } ValE;
typedef struct TgtE {
    ValE *def;
    u8 pad[8];
    union { f32 f; s32 i; } v;
} TgtE;
typedef struct EntE {
    TgtE *tgt;
    s32 op;
    f32 val;
    struct EntE *next;
} EntE;
typedef struct SelfE {
    u8 pad[356];
    EntE *list;
} SelfE;
void fn_801A71DC(SelfE *, s32, TgtE *);

#pragma opt_propagation off
void fn_801A73D8(SelfE *self) {
    EntE *e;
    s32 icur;
    f32 fcur;
    TgtE *t;
    for (e = self->list; e; e = e->next) {
        t = e->tgt;
        if (t) {
            switch (e->op) {
            case 1:
                switch (t->def->type) {
                case 3:
                    t->v.f = e->val;
                    fn_801A71DC(self, 3, e->tgt);
                    break;
                case 2:
                    t->v.i = (s32)e->val;
                    fn_801A71DC(self, 2, e->tgt);
                    break;
                }
                break;
            case 2:
                switch (t->def->type) {
                case 3:
                    fcur = t->v.f; t->v.f = e->val + fcur;
                    fn_801A71DC(self, 3, e->tgt);
                    break;
                case 2:
                    icur = t->v.i; t->v.i = (s32)e->val + icur;
                    fn_801A71DC(self, 2, e->tgt);
                    break;
                }
                break;
            case 3:
                switch (t->def->type) {
                case 3:
                    fcur = t->v.f; t->v.f = fcur - e->val;
                    fn_801A71DC(self, 3, e->tgt);
                    break;
                case 2:
                    icur = t->v.i; t->v.i = icur - (s32)e->val;
                    fn_801A71DC(self, 2, e->tgt);
                    break;
                }
                break;
            }
        }
    }
}
#pragma opt_propagation reset

} /* extern "C" */
