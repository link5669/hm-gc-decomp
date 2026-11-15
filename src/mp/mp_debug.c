/* Multiplayer mod: debugging helpers (stack backtraces to the Dolphin log). */
#include "mp.h"

asm u32 *mp_get_sp(void)
{
    nofralloc
    mr r3, r1
    blr
}

void mp_backtrace(const char *tag, u32 a, u32 b)
{
    u32 *sp = mp_get_sp();
    int i;
    OSReport("[mp] %s %08x %08x bt:", tag, a, b);
    for (i = 0; i < 10; i++) {
        sp = (u32 *)sp[0];
        if ((u32)sp < 0x80000000 || (u32)sp >= 0x81800000 || ((u32)sp & 7))
            break;
        OSReport(" %08x", sp[1]);
    }
    OSReport("\n");
}
