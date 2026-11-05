#include "common.h"

/* The base C80257738 has an out-of-line ctor and dtor. Its vptr (__vt__9C80273730) sits at
 * 0x0 and is stored before the member at 0xC0 is built: it is modelled as a member whose inline ctor stores it. */

extern "C" {
extern u8 __vt__9C80273730[];
void fn_802575F0(void *p);
}

struct C80257738 { C80257738(); ~C80257738(); };
struct V80273730 { u8 *vt; V80273730() { vt = __vt__9C80273730; } };
struct C8025E920 { C8025E920(); ~C8025E920(); };

struct C80273730 : C80257738 {
    V80273730 m0;
    u8 pad4[0xc0 - 4];
    C8025E920 mC0;
    C80273730();
};

C80273730::C80273730() {
    fn_802575F0(this);
}
