// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
} /* extern "C" */
struct Mgr3DD00 {
    u8 pad[192];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void m3(void *out, u8 v);
    virtual void v4();
    virtual void v5();
    virtual u32 m6();
};
extern "C" {
typedef struct { char d[8]; } Key3DD00;
typedef struct { u8 *f0; } Buf3DD00;
typedef struct { u8 pad[736]; s32 f736; } P3DD00;
extern Mgr3DD00 *lbl_8035B684;
extern char lbl_8035C224[4];
extern char lbl_80294E1C[];
void *memcpy(void *, const void *, unsigned long);
s32 fn_800F6CD0(void *, void *);
s32 fn_8003DD00(P3DD00 *p, Buf3DD00 *b) {
    s32 type;
    s32 pos;
    p->f736 = 0;
    pos = 1;
    do {
        type = b->f0[pos++];
        switch (type) {
        case 0: {
            Key3DD00 buf;
            u32 cnt;
            u32 i;
            lbl_8035B684->m3(&buf, b->f0[pos]);
            memcpy(&cnt, &b->f0[pos + 1], 4);
            pos += 5;
            for (i = 0; i < cnt; i++) {
                Key3DD00 key;
                u8 v = b->f0[pos];
                if (v >= lbl_8035B684->m6()) return 0;
                memcpy(&key, &b->f0[pos + 1], 8);
                if (fn_800F6CD0(&key, lbl_8035C224)) return 0;
                if (fn_800F6CD0(&key, lbl_80294E1C)) {
                    u32 val = 0;
                    memcpy(&val, &b->f0[pos + 9], 4);
                    p->f736 += val;
                }
                pos += 13;
            }
            continue;
        }
        case 3:
            pos += 4;
            continue;
        case 1:
            pos += 60;
            continue;
        case 2:
            break;
        }
        if (type != 2) return 0;
    } while (type != 2);
    return 1;
}

} /* extern "C" */
