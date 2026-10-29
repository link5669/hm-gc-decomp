// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800E91D0(const char *fmt, ...);
void exit(int);

#pragma readonly_strings on
void fn_800604C4(s32 code, char *file, s32 line) {
    char *msg;
    switch (code) {
    case 0: msg = "Invalid error condition"; break;
    case -1: msg = "General error occurred"; break;
    case -2: msg = "Invalid parameter detected"; break;
    case -3: msg = "Invalid value detected"; break;
    case -4: msg = "Out of memory error occured"; break;
    case -5: msg = "Critical resource busy"; break;
    case -7: msg = "Assertion Failed"; break;
    default: msg = "Unknown error condition occured"; break;
    }
    fn_800E91D0("%s, file \"%s\" line %d\n", msg, file, line);
    exit(1);
}
#pragma readonly_strings reset

} /* extern "C" */
