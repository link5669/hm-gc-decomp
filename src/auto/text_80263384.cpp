// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { char s[8]; } N8_80263384;
typedef struct { u32 v[2]; } V8_80263384;
extern char lbl_80366B64[8];
extern char lbl_80366B24[8];
extern char lbl_80366B2C[8];
typedef struct { u8 pad[768]; s32 f768; } P_80263384;
typedef struct { u8 pad[600]; P_80263384 *f600; } Q_80263384;
typedef struct { u8 pad[72]; Q_80263384 *f72; } G_80263384;
extern G_80263384 *lbl_8035B308;
} /* extern "C" */
struct O_80263384 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(void *, O_80263384 *, u32, f32 *, V8_80263384 *);
};
struct Self_80263384 {
    u8 pad[156];
    O_80263384 *f156;
    u8 pad160[72];
    f32 f232;
    u8 pad236[8];
    u32 f244;
    u32 f248;
    u8 pad252[4];
    u32 f256;
};
extern "C" {
u32 fn_8024548C(u32, u32, s32, s32, N8_80263384 *, f32 *, V8_80263384 *);
s32 fn_800F6CD0(N8_80263384 *, char *);

void fn_80263384(Self_80263384 *self, u32 start, u32 end) {
    f32 bufB[60];
    N8_80263384 bufA[60];
    V8_80263384 bufC[60];
    u32 i;
    u32 cnt;
    u32 j;

    if (lbl_8035B308->f72->f600 != 0 && lbl_8035B308->f72->f600->f768 == 0) {
        for (i = start; i < end; i++) {
            cnt = fn_8024548C(self->f244, i, -1, 60, bufA, bufB, bufC);
            self->f156->v33(lbl_80366B64, 0, 0, 0, 0);
            if (cnt != 0) {
                for (j = self->f248; j < cnt; j++) {
                    self->f248++;
                    if (fn_800F6CD0(&bufA[j], lbl_80366B24) != 0) {
                        self->f232 = bufB[j];
                        self->f156->v33(&bufA[j], self->f156, self->f244, &bufB[j], &bufC[j]);
                        break;
                    }
                    if (fn_800F6CD0(&bufA[j], lbl_80366B2C) != 0) {
                        self->f256 = 1;
                        break;
                    }
                    self->f156->v33(&bufA[j], self->f156, self->f244, &bufB[j], &bufC[j]);
                }
            }
        }
    }
}

} /* extern "C" */
