// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern u8 __vt__9C80129A9C[];
} /* extern "C" */

struct R8022F98C {
    virtual ~R8022F98C();
};

struct C80239B40 : R8022F98C {
    u8 pad[592];
    C80239B40();
    ~C80239B40();
};

struct C80105074 {
    u8 pad[36];
    C80105074();
    ~C80105074();
};

struct C80105818 : C80105074 {
    u8 *vt;
    C80105818() { vt = __vt__9C80129A9C; }
    ~C80105818();
};

struct C8023B4DC {
    u8 pad[164];
    C8023B4DC();
    ~C8023B4DC();
};

struct C8022F98C : C80239B40 {
    s32 f596, f600, f604, f608, f612, f616;
    C80105818 m620;
    C8023B4DC m660;
    s32 f824, f828;
    C8022F98C();
    ~C8022F98C();
};

C8022F98C::C8022F98C() {
    f604 = -1;
    f596 = 0;
    f608 = 0;
    f612 = 0;
    f616 = 0;
    f824 = 0;
    f828 = 0;
}

extern "C" {

} /* extern "C" */
