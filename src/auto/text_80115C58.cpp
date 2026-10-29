// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"
extern "C" {

typedef struct Ent { char name[20]; void *fn; void *obj; } Ent;
typedef struct Reg { Ent ents[360]; u32 count; u8 pad[0x277c-0x2764]; u8 pool[0x28]; u32 ready; } Reg;
typedef struct TEnt { char name[20]; void *fn; u32 x; } TEnt;
extern TEnt lbl_802E2E30[];
extern TEnt lbl_802E2F68[];
extern char lbl_80363A40[8];
extern char lbl_80363A48[8];
extern char lbl_80363A50[8];
extern Reg *lbl_8035AB04;
char *strcpy(char *, const char *);
void fn_80115B64(void); void fn_80115B5C(void); void fn_80115AE0(void); void fn_80115930(void);
void fn_80115A54(void); void fn_801158A8(void); void fn_801159A0(void); void fn_80115800(void); void fn_801153CC(void);
void fn_800F8E38(void *, int);
static inline void Add(Reg *r, const char *name, void *fn) {
    if (r->count < 40) {
        r->ents[r->count].obj = r;
        r->ents[r->count].fn = fn;
        strcpy(r->ents[r->count].name, name);
        r->count++;
    }
}
void fn_80115C58(Reg *r) {
    int i;

    lbl_8035AB04 = r;

    for (i = 0; lbl_802E2E30[i].fn; i++) Add(r, lbl_802E2E30[i].name, lbl_802E2E30[i].fn);
    for (i = 0; lbl_802E2F68[i].fn; i++) Add(r, lbl_802E2F68[i].name, lbl_802E2F68[i].fn);
    Add(r, lbl_80363A40, (void *)fn_80115B64);
    Add(r, lbl_80363A48, (void *)fn_80115B5C);
    Add(r, "vSetRegInt", (void *)fn_80115AE0);
    Add(r, "nGetRegInt", (void *)fn_80115930);
    Add(r, "vSetRegFloat", (void *)fn_80115A54);
    Add(r, "fGetRegFloat", (void *)fn_801158A8);
    Add(r, "vSetRegString", (void *)fn_801159A0);
    Add(r, "vGetRegString", (void *)fn_80115800);
    Add(r, lbl_80363A50, (void *)fn_801153CC);
    fn_800F8E38(r->pool, 2000);
    r->ready = 1;
}

}
