#include "common.h"

extern "C" {

/* NonMatching draft (wMF, wMO): DIFF 14 / SDIFF 4. Base ctors made trivial and all three vt stores put in the first member-init arg (removes the this copies). Left: target materializes lbl_802EFC40 into r4 first (before the 934 pair) and uses r31 (not the r5 arg copy) for this+4. To link it also needs __dt__9C80208C80Fv renamed to __dt__9C8020EA30Fv and the current __dt__9C8020EA30Fv (0x8020EA30, the FC40 base dtor) renamed (e.g. __dt__9C8020EA30Fv). */
extern u8 lbl_802EF934[], lbl_802EFC40[], lbl_802EF9A0[];
struct C8020EA30_0 { void *vt; ~C8020EA30_0(); };
struct C8020EA30 : C8020EA30_0 { ~C8020EA30(); };
struct C80208C80 { C80208C80(int, int, int); ~C80208C80(); u8 pad[0x44]; };
struct C80208924 { C80208924(); u8 pad[0x18]; };
struct C80209368 : C8020EA30 { C80208C80 m; C80208924 m2; C80209368(); };
static inline int U() { int x; return x; }
C80209368::C80209368() : m((vt = lbl_802EF934, vt = lbl_802EFC40, vt = lbl_802EF9A0, (int)lbl_802EFC40), (int)this, U()) {}

} /* extern "C" */
