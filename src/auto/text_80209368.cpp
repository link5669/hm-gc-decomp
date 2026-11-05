// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

extern u8 lbl_802EF934[];
extern u8 lbl_802EFC40[];
extern u8 lbl_802EF9A0[];
void __ct__9C80208C80Fiii(void *p);
} /* extern "C" */
struct CV802EF934 { u8 *vt; CV802EF934() { vt = lbl_802EF934; } ~CV802EF934(); };
struct CV802EFC40 : CV802EF934 { CV802EFC40() { vt = lbl_802EFC40; } ~CV802EFC40(); };
struct C80208C80 : CV802EFC40 { C80208C80() { vt = lbl_802EF9A0; } ~C80208C80(); };
struct C80208924 : CV802EFC40 { u32 f4, f8, f12, f16, f20; C80208924(); ~C80208924(); };
struct C80208BF0 { u8 data[68]; C80208BF0() { __ct__9C80208C80Fiii(this); } ~C80208BF0(); };
struct C80209368 : C80208C80 { C80208BF0 m4; C80208924 m72; C80209368(); ~C80209368(); };
C80209368::C80209368() { }
extern "C" {

} /* extern "C" */
