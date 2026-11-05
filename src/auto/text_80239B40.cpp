// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 lbl_802F189C[];
extern u8 lbl_802F069C[];
void fn_8010344C(void *);
void fn_80222BE8(void *);
void fn_8023994C(void *);
} /* extern "C" */

struct C8022DFC8 {
    C8022DFC8();
    ~C8022DFC8();
};

struct C80031B94 {
    u32 x0;
    C80031B94() { fn_8010344C(this); }
    ~C80031B94();
};

struct C80033BD0 : C80031B94 {
    void *vt;
    u8 pad8[212];
    C80033BD0() {
        vt = lbl_802F069C;
        fn_80222BE8(this);
    }
    ~C80033BD0();
};

struct V80239B40 {
    void *vt;
    V80239B40() { vt = lbl_802F189C; }
};

struct C80239B40 : C8022DFC8 {
    V80239B40 v;
    u8 pad4[372];
    C80033BD0 m;
    C80239B40();
    ~C80239B40();
};

C80239B40::C80239B40() { fn_8023994C(this); }

extern "C" {

} /* extern "C" */
