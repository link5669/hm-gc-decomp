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

#ifdef MP_DEBUG_AUTOJOIN
/* debug: list every actor (name, class vtable, behaviour vtable, position) */
void fn_8023C528(void *it, char *x);
void fn_8023C3F4(void *it);
void *fn_8023A490(void *a, void *b);
void mp_debug_list_actors(void)
{
    u8 *mgr = *(u8 **)0x8035B308, *it, *o, *beh;
    int n = 0;
    if (!mgr || !(it = *(u8 **)(mgr + 0x50)))
        return;
    for (fn_8023C528(it, 0); *(void **)(it + 8) && n < 400; fn_8023C3F4(it), n++) {
        o = fn_8023A490(*(void **)(it + 8), *(void **)(it + 12));
        if (!o)
            continue;
        beh = *(u8 **)(o + 0x20c);
        OSReport("[mp] ACT %p '%.8s' vt %08x beh %p bvt %08x pos %d %d %d\n", o, (char *)o + 0x8c, *(u32 *)o, beh,
                 ((u32)beh & 0xff000000) == 0x80000000 ? *(u32 *)beh : 0, (int)(*(f32 *)(o + 0x44) * 10),
                 (int)(*(f32 *)(o + 0x48) * 10), (int)(*(f32 *)(o + 0x4c) * 10));
    }
    OSReport("[mp] ACT end (%d)\n", n);
}
#endif

#ifdef MP_DEBUG_AUTOJOIN
/* debug: teleport player 2 to an actor by name (cycles through a list) */
extern void *mp_player[2];
void mp_debug_tp_actor(void)
{
    static const char *names[] = {"FOYEtrig", "ghost1", "ghost2", "ghost0"};
    static int idx;
    u8 *mgr = *(u8 **)0x8035B308, *it, *o, *p2 = mp_player[1];
    const char *want = names[idx];
    int n = 0, k;
    idx = (idx + 1) % 4;
    if (!mgr || !p2 || !(it = *(u8 **)(mgr + 0x50)))
        return;
    for (fn_8023C528(it, 0); *(void **)(it + 8) && n < 400; fn_8023C3F4(it), n++) {
        o = fn_8023A490(*(void **)(it + 8), *(void **)(it + 12));
        if (!o)
            continue;
        for (k = 0; k < 8 && want[k] && ((char *)o)[0x8c + k] == want[k]; k++)
            ;
        if (k < 8 && want[k])
            continue;
        *(f32 *)(p2 + 0x44) = *(f32 *)(o + 0x44) + (want[0] == 'g' ? 1.5f : 0.0f);
        *(f32 *)(p2 + 0x48) = *(f32 *)(o + 0x48);
        *(f32 *)(p2 + 0x4c) = want[0] == 'g' ? 0.0f : *(f32 *)(o + 0x4c);
        OSReport("[mp] debug: player 2 teleported to '%s' (%d %d %d)\n", want, (int)(*(f32 *)(o + 0x44) * 10),
                 (int)(*(f32 *)(o + 0x48) * 10), (int)(*(f32 *)(o + 0x4c) * 10));
        return;
    }
    OSReport("[mp] debug: actor '%s' not found\n", want);
}
#endif
