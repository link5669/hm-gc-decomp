// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_80220940(void *);
} /* extern "C" */

struct C80064530 {
    u8 d0[672];
    C80064530();
    virtual ~C80064530();
};

struct B80220940 {
    u8 d0[628];
    B80220940() { fn_80220940(this); }
    ~B80220940();
};

struct C800644D0 : B80220940 {
    C800644D0() {}
    virtual ~C800644D0();
};

struct C80064474 : C80064530 {
    u8 pad[12344 - 676];
    C800644D0 m;
    C80064474();
    virtual ~C80064474();
};

C80064474::C80064474() {}

extern "C" {

} /* extern "C" */
