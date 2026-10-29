// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct {
    u8 pad[144];
    u8 byName[24];
    u8 bySub[8];
} Mgr1E7;
typedef struct {
    u8 pad[212];
    Mgr1E7 *mgr;
} Ctx1E7;
typedef struct {
    u8 pad0[8];
    Ctx1E7 *ctx;
    s32 state;
    u8 pad16[24];
    char name[8];
    u32 f48;
    u32 f52;
    u8 f56[8];
} Self1E7;
void fn_800FB064(void *stream, char *buf);
u32 fn_800F9398(void *tbl, char *name);
u32 fn_800F9788(void *tbl, char *a, char *b);
void fn_80101124(void *obj, void *stream);
void fn_801EF720(Self1E7 *self, void *stream, s32 cmd);

static inline BOOL IsEmpty1E7(char *s) { return s == 0 || s[0] == 0; }

static inline void Lookup1E7(Self1E7 *self, char *name, char *sub) {
    Mgr1E7 *m = self->ctx->mgr;
    u32 r;
    if (sub == 0 || sub[0] == 0) {
        r = fn_800F9398(m->byName, name);
    } else {
        r = fn_800F9788(m->bySub, sub, name);
    }
    self->f52 = 0;
    self->f48 = 0;
    self->f48 = r;
}

void fn_801E7558(Self1E7 *self, void *stream, s32 cmd) {
    char name[8];
    char sub[8];
    switch (cmd) {
    case 102:
        fn_800FB064(stream, name);
        fn_800FB064(stream, sub);
        Lookup1E7(self, name, sub);
        break;
    case 96:
        fn_800FB064(stream, self->name);
        fn_800FB064(stream, name);
        fn_800FB064(stream, sub);
        Lookup1E7(self, name, sub);
        break;
    case 97:
    case 127:
        fn_80101124(self->f56, stream);
        break;
    case 171:
        self->state = 22;
        break;
    case 173:
        self->state = 23;
        break;
    case 172:
    default:
        fn_801EF720(self, stream, cmd);
        break;
    }
}

} /* extern "C" */
