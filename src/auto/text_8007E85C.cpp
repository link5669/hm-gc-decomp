// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
extern char lbl_80298768[];
extern char lbl_8035F940[4];
extern char lbl_8035F978[7];
void *fn_8023F52C(void *self, char *a, char *b, char *name, s32 c, s32 d);
void fn_8023F214(void *self);

#pragma opt_propagation off
void fn_8007E85C(u8 *self) {
    char *str = lbl_80298768;
    M2C_FIELD(self, void **, 280) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 204, 1, 0);
    M2C_FIELD(self, void **, 284) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 220, 1, 0);
    M2C_FIELD(self, void **, 288) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, lbl_8035F978, 1, 0);
    M2C_FIELD(self, void **, 292) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 232, 1, 0);
    M2C_FIELD(self, void **, 296) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 248, 1, 0);
    M2C_FIELD(self, void **, 300) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 268, 1, 0);
    M2C_FIELD(self, void **, 304) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 280, 1, 0);
    M2C_FIELD(self, void **, 308) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 292, 1, 0);
    M2C_FIELD(self, void **, 312) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 304, 1, 0);
    M2C_FIELD(self, void **, 316) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 316, 1, 0);
    M2C_FIELD(self, void **, 348) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 336, 1, 0);
    M2C_FIELD(self, void **, 352) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 356, 1, 0);
    M2C_FIELD(self, void **, 356) = fn_8023F52C(self, lbl_8035F940, lbl_8035F940, str + 372, 1, 0);
    fn_8023F214(self);
}
#pragma opt_propagation reset

} /* extern "C" */
