// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

struct OV { u8 pad[8]; virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual u32 s5(int); };
static const char sPad[164] = {1};
static const char s164[] = "MaxNumActors";
static const char s180[] = "ActorsPerSpawn";
static const char s196[] = "TimeBetweenSpawns";
static const char s216[] = "SpawnNow";
static const char s228[] = "AlwaysDisplace";
static const char s244[] = "DisplacementRadius";
static const char s264[] = "SpawnsPerTrigger";
static const char s284[] = "AlwaysOn";
static const char s296[] = "ActorSceneName";
static const char s312[] = "GameActorName";
static const char s328[] = "MaxNumActorsEver";
static const char s348[] = "SpawnFacingPlayer";
OV **fn_8010FEDC(void *, void *, const char *, int);
void fn_800F6FBC(u32, u8 *);
void fn_80239024(u8 *);
#define F(o, t) (*(t *)(p + (o)))
static inline u32 get(u8 *p, const char *n) { return (*fn_8010FEDC(F(12, void *), F(16, void *), n, 1))->s5(0); }

void fn_802349DC(u8 *p) {
    F(996, u32) = get(p, s164);
    F(1000, u32) = get(p, s180);
    F(1004, u32) = get(p, s196);
    F(1008, u32) = get(p, s216);
    F(1024, u32) = get(p, s228);
    F(1028, u32) = get(p, s244);
    F(1012, u32) = get(p, s264);
    F(1016, u32) = get(p, s284);
    F(1068, u32) = *F(1016, u32 *);
    fn_800F6FBC(get(p, s296), p + 1036);
    fn_800F6FBC(get(p, s312), p + 1044);
    F(1020, u32) = get(p, s328);
    F(1032, u32) = get(p, s348);
    F(1060, f32) = *F(1004, f32 *);
    F(180, u32) |= 4;
    fn_80239024(p);
}

} /* extern "C" */
