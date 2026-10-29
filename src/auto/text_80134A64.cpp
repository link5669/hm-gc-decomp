// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct S80134A64_0 { u32 pad[1804 / 4]; } S80134A64_0;
typedef struct S80134A64_1 { u32 pad[1356 / 4]; } S80134A64_1;
typedef struct S80134A64_2 { u32 pad[1368 / 4]; } S80134A64_2;
typedef struct S80134A64_3 { u32 pad[1360 / 4]; } S80134A64_3;
typedef struct S80134A64_4 { u32 pad[1364 / 4]; } S80134A64_4;
typedef struct S80134A64_5 { u32 pad[1352 / 4]; } S80134A64_5;
void *fn_801474EC(void *p);
void *fn_80120FAC(void *p);
void *__ct__9C8014C450Fv(void *p);
void *__ct__9C8013DEE0Fv(void *p);
void *__ct__9C8014A570Fv(void *p);
void *fn_801269E4(void *p);
void *__dt__9C801203A8Fv(void *p, s16 f);
void *__dt__9C80134BD0Fv(void *p, s16 f);
void *__dt__9C80134B70Fv(void *p, s16 f);
void *__dt__9C80134B10Fv(void *p, s16 f);
void *__dt__9C80121E84Fv(void *p, s16 f);
void *__register_global_object(void *obj, void *dtor, void *chain);

static S80134A64_0 obj0_80134A64;
static u8 chain1_80134A64[12];
static S80134A64_1 obj1_80134A64;
static u8 chain2_80134A64[12];
static S80134A64_2 obj2_80134A64;
static u8 chain3_80134A64[12];
static S80134A64_3 obj3_80134A64;
static u8 chain4_80134A64[12];
static S80134A64_4 obj4_80134A64;
static u8 chain5_80134A64[12];
static S80134A64_5 obj5_80134A64;

void fn_80134A64(void) {
    fn_801474EC(&obj0_80134A64);
    __register_global_object(fn_80120FAC(&obj1_80134A64), (void *)__dt__9C801203A8Fv, chain1_80134A64);
    __register_global_object(__ct__9C8014C450Fv(&obj2_80134A64), (void *)__dt__9C80134BD0Fv, chain2_80134A64);
    __register_global_object(__ct__9C8013DEE0Fv(&obj3_80134A64), (void *)__dt__9C80134B70Fv, chain3_80134A64);
    __register_global_object(__ct__9C8014A570Fv(&obj4_80134A64), (void *)__dt__9C80134B10Fv, chain4_80134A64);
    __register_global_object(fn_801269E4(&obj5_80134A64), (void *)__dt__9C80121E84Fv, chain5_80134A64);
}

__declspec(section ".ctors") static void (*const ctor_80134A64)(void) = fn_80134A64;

} /* extern "C" */
