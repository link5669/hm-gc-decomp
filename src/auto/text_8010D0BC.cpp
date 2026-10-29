// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct E16_8010D0BC { u8 b[16]; };
struct E20_8010D0BC { u8 b[20]; };
struct E60_8010D0BC { u8 b[60]; };
struct B36_8010D0BC { u8 pad[8]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual u8 *get(s32); };
struct E36_8010D0BC : B36_8010D0BC { u8 pad2[20]; s32 ready; };
extern "C" {
struct T_8010D0BC { s32 index; void *f4; u8 **tabs; };
u32 *fn_80112B18(void *p);
void fn_801094CC(E36_8010D0BC *e);

u8 *fn_8010D0BC(T_8010D0BC *p, s32 idx) {
    u8 *r = 0;
    switch (fn_80112B18(p->f4)[2]) {
    case 1: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 2: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 3: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 4: r = (u8 *)&((E20_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 5: r = (u8 *)&((E60_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 6: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 7: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 8: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 9: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 10: r = (u8 *)&((E16_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 11: r = (u8 *)&((E20_8010D0BC *)p->tabs[idx])[p->index]; break;
    case 12: {
        E36_8010D0BC *e = &((E36_8010D0BC *)p->tabs[idx])[p->index];
        if (e->ready == 0) fn_801094CC(e);
        r = e->get(0);
        break;
    }
    }
    return r;
}

} /* extern "C" */
