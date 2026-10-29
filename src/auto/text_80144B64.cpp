// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct C80144B64;
typedef void (C80144B64::*PMF80144B64)();
struct C80144B64 {
    u8 pad0[140];
    u32 m140;
    u8 pad144[12];
    u32 m156;
    u32 m160;
    u32 m164;
    u32 m168;
    u32 m172;
    u8 pad176[1260];
    u32 m1436;
    PMF80144B64 m1440[26];
    u32 pad1752;
    PMF80144B64 m1756;
    PMF80144B64 m1768;
    PMF80144B64 m1780;
    PMF80144B64 m1792;
};
extern "C" {

void fn_80144B64(C80144B64 *p) {
    u8 *q;
    u32 i;
    u32 n;
    p->m160 = p->m140;
    while (p->m160 >= 32) {
        p->m156 = 32;
        p->m164 = p->m168;
        (p->*(p->m1756))();
        for (i = 0, q = (u8 *)p; i < p->m1436; q += 12, i++) (p->*(((C80144B64 *)q)->m1440[0]))();
        n = p->m168;
        while (n >= 32) {
            (p->*(p->m1768))();
            n -= 32;
        }
        if (n != 0) {
            p->m156 = n;
            (p->*(p->m1792))();
        }
        p->m160 -= 32;
    }
    if (p->m160 != 0) {
        p->m156 = p->m160;
        p->m164 = p->m172;
        (p->*(p->m1780))();
        for (i = 0, q = (u8 *)p; i < p->m1436; q += 12, i++) (p->*(((C80144B64 *)q)->m1440[0]))();
        p->m156 = 32;
        n = p->m172;
        while (n >= 32) {
            (p->*(p->m1768))();
            n -= 32;
        }
        if (n != 0) {
            p->m156 = n;
            (p->*(p->m1792))();
        }
    }
}

} /* extern "C" */
