/* Multiplayer mod: enemies target both players.
   The game's actor update loop (fn_80228A48) is reimplemented here unchanged, except that while an enemy
   updates, "the player" (o72 = *(mgr+0x48), which ~60 functions read) is set to that enemy's own target.
   Each enemy starts on a random player and switches to the other one after a random 8..20 s. */
#include "mp.h"
#include "mp_state.h"

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))
#define U32(p, o) (*(u32 *)((u8 *)(p) + (o)))
#define F32(p, o) (*(f32 *)((u8 *)(p) + (o)))

void fn_8023C528(void *it, char *x);
void *fn_8023A490(void *a, void *b);
void fn_8023C3F4(void *it);
void fn_80228A48(void *mgr, f32 dt);
u32 OSGetTick(void);
extern f32 lbl_80365CB0, lbl_80365CD8;
extern u8 *lbl_8035B488;
extern s32 mp_p2_lives;

/* ---- which actors are enemies (behaviour vtables, filled in from the class registry) ---- */
/* hostile behaviours (class registry, see hm-work/mp/enemies.md): ghosts, skeletons, reaper, spiders,
   phantom arms, bride's maid, worms, moths, bats, maggots, zombie arms, shrivels, knights... */
static const u32 s_enemy_vt[] = {
    0x802b0d98 /* BBlrdGst */, 0x802b3728 /* BDSkel */, 0x802b4ec0 /* BGhost */, 0x802b5894 /* BKSkel */,
    0x802b7a38 /* BReaper */, 0x802ba100 /* BShrivel */, 0x802baeb8 /* BSpider */, 0x802c5038 /* BSpdrLrd */,
    0x802c811c /* BPhArm */, 0x802c952c /* BBriMaid */, 0x802c9f94 /* BPhArmAx */, 0x802cb630 /* BMnGhst */,
    0x802cd4fc /* BWorm */, 0x802ce4f4 /* BSSpider */, 0x802cef94 /* BMusKnit */, 0x802d0398 /* BAuxGh */,
    0x802d10f0 /* BMoth */, 0x802d1634 /* BBat */, 0x802d3988 /* BMaggot */, 0x802d5ea8 /* BZombArm */,
};
/* allocation size of each behaviour above (the `new` in its factory): the retarget scan must stay inside it */
static const u16 s_enemy_size[] = {
    0x134, 0x160, 0x150, 0x138, 0x180, 0x27c, 0x1cc, 0x12c, 0x184, 0x178,
    0x128, 0x17c, 0x1e0, 0x134, 0x1a8, 0x184, 0x144, 0x184, 0x138, 0x140,
};
#define ENEMY_MIN_SIZE 0x128
/* behaviours that keep their own copy of the target (set once from o72): offset in the behaviour */
static int cached_target_ofs(u32 vt)
{
    if (vt == 0x802b4ec0)
        return 0x138; /* BGhost */
    if (vt == 0x802b3728)
        return 0x118; /* BDSkel */
    return 0;
}
static int is_enemy(u8 *o)
{
    u8 *beh = PTR(o, MP_BEHAVIOUR_OFS);
    u32 vt;
    int i;
    if (((u32)beh & 0xFE000000) != 0x80000000)
        return 0;
    vt = U32(beh, 0);
    for (i = 0; i < (int)(sizeof(s_enemy_vt) / sizeof(s_enemy_vt[0])); i++)
        if (s_enemy_vt[i] && vt == s_enemy_vt[i])
            return 1;
    return 0;
}

/* Enemies keep copies of their target inside their behaviour (e.g. BGhost +0x138, BDSkel +0x118, spiders...):
   point every reference to the other player at the assigned target. */
static void retarget(u8 *o, u8 *who, u8 *other)
{
    u8 *beh = PTR(o, MP_BEHAVIOUR_OFS);
    u32 i, vt, size = ENEMY_MIN_SIZE;
    if (((u32)beh & 0xFE000000) != 0x80000000)
        return;
    vt = U32(beh, 0);
    for (i = 0; i < sizeof(s_enemy_vt) / sizeof(s_enemy_vt[0]); i++)
        if (vt == s_enemy_vt[i])
            size = s_enemy_size[i];
    for (i = 4; i + 4 <= size; i += 4)
        if (PTR(beh, i) == other)
            PTR(beh, i) = who;
}

/* ---- per-enemy target assignment ---- */
typedef struct Tgt { u8 *actor; u8 who; u32 until; } Tgt;
static Tgt s_tgt[256];
static u32 s_rng = 12345, s_tick;
static u32 rnd(void)
{
    s_rng = s_rng * 1103515245u + 12345u;
    return s_rng >> 8;
}

static int target_of(u8 *o)
{
    u32 h = ((u32)o >> 4) & 255, i;
    for (i = 0; i < 256; i++) {
        Tgt *t = &s_tgt[(h + i) & 255];
        if (t->actor == o || t->actor == 0) {
            if (t->actor == 0) {  /* first time: random player */
                t->actor = o;
                t->who = rnd() & 1;
                t->until = s_tick + 480 + rnd() % 720;
                OSReport("[mp] enemy %p '%.8s' targets player %d\n", o, (char *)o + 0x8c, t->who + 1);
            } else if ((s32)(s_tick - t->until) >= 0) {  /* time to go after the other one */
                t->who ^= 1;
                t->until = s_tick + 480 + rnd() % 720;
                OSReport("[mp] enemy %p '%.8s' switches to player %d\n", o, (char *)o + 0x8c, t->who + 1);
            }
            return t->who;
        }
    }
    return 0;
}

void mp_enemies_reset(void)
{
    int i;
    for (i = 0; i < 256; i++)
        s_tgt[i].actor = 0;
    s_rng ^= OSGetTick();
}

static void tick(u8 *o, f32 dt, f32 k)
{
    f32 s = F32(o, 0x110);
    void (*upd)(void *, f32) = (void (*)(void *, f32))PTR(*(void **)o, 0x38);
    if (lbl_80365CD8 == s)
        upd(o, k);
    else if (lbl_80365CB0 != s)
        upd(o, dt * s);
}

/* The original loop, with the per-enemy "player" swap. */
static void actor_loop(u8 *p, f32 dt)
{
    u8 *it = PTR(p, 0x50), *p1 = PTR(p, 0x48), *p2 = mp_player[1], *o76 = PTR(p, 0x4c);
    f32 k = *(f32 *)(lbl_8035B488 + 20);
    /* (not in co-op = controller 2 unplugged: he stands still and enemies leave him alone) */
    int p2_ok = p2 && mp.mode == MP_COOP && mp_p2_lives >= 0 && F32(p2, 0x1ac) > 0.0f;
    if (!it)
        return;
    s_tick++;
    for (fn_8023C528(it, 0); PTR(it, 8); fn_8023C3F4(it)) {
        int upd = 1;
        u8 *o = fn_8023A490(PTR(it, 8), PTR(it, 12)), *q;
        if (!o)
            continue;
        q = PTR(o, 0x9c);
        if (q) {
            u16 t = *(u16 *)(q + 4);
            if (t >= 1 && t <= 13) {
                s32 a168 = PTR(o, 0xa8) ? *(s32 *)PTR(o, 0xa8) : 0;
                int b2;
                if (!((U32(q, 0) & 0x800) || (U32(o, 0xb4) & 4) || a168 != 0) || o == p1 || o == o76)
                    upd = 0;
                b2 = o76 && (U32(o76, 0x284) != 0 || F32(o76, 0x290) != lbl_80365CB0);
                if (b2 && U32(o, 0x94) == 2 && U32(o, 0x240) == 0)
                    upd = 0;
            }
        }
        if (o == p2)
            upd = 0;  /* player 2 is updated by mp_update_p2 */
        if (!upd)
            continue;
        if (p2_ok && is_enemy(o)) {
#ifdef MP_TEST_TARGET_P2
            u8 *who = p2, *beh = PTR(o, MP_BEHAVIOUR_OFS);
#else
            u8 *who = target_of(o) ? p2 : p1, *beh = PTR(o, MP_BEHAVIOUR_OFS);
#endif
            retarget(o, who, who == p2 ? p1 : p2);
            PTR(p, 0x48) = who;
            tick(o, dt, k);
            PTR(p, 0x48) = p1;
        } else {
            /* player 2 is down: enemies that were after him go back to player 1 */
            if (p2 && !p2_ok && is_enemy(o))
                retarget(o, p1, p2);
            tick(o, dt, k);
        }
    }
    tick(p1, dt, k);
    if (o76)
        tick(o76, dt, k);
}

void mp_actor_update_coop(void *mgr, f32 dt)
{
    if (mp_player[1])
        actor_loop((u8 *)mgr, dt);
    else
        fn_80228A48(mgr, dt);
}

/* Collision events (fn_80225FC0: sep/touch/gone virtual calls) are dispatched outside any actor update, so
   handlers that act on "the player" (o72) would hit player 1 even when player 2's body was involved. Each of
   those `bctrl`s is replaced by a call to this stub: if either side is player 2 (actor or its world node), o72 is
   player 2 for the duration of the call. All argument registers and CTR are passed through untouched. */
asm void mp_coll_call(void)
{
    nofralloc
    stwu r1, -48(r1)
    mflr r0
    stw r0, 52(r1)
    stw r31, 44(r1)
    stw r30, 40(r1)
    stw r29, 36(r1)
    li r29, 0
    lis r31, mp_player@ha
    addi r31, r31, mp_player@l
    lwz r30, 4(r31)
    cmpwi r30, 0
    beq do_call
    cmplw r3, r30
    beq swap
    cmplw r4, r30
    beq swap
    lwz r0, 0x9c(r30)
    cmplw r4, r0
    bne do_call
swap:
    lis r31, 0x8036
    lwz r31, -0x4cf8(r31)
    lwz r29, 0x48(r31)
    stw r30, 0x48(r31)
do_call:
    bctrl
    cmpwi r29, 0
    beq done
    lis r31, 0x8036
    lwz r31, -0x4cf8(r31)
    stw r29, 0x48(r31)
done:
    lwz r29, 36(r1)
    lwz r30, 40(r1)
    lwz r31, 44(r1)
    lwz r0, 52(r1)
    mtlr r0
    addi r1, r1, 48
    blr
}

#ifdef MP_DEBUG_AUTOJOIN
void fn_8007225C(void *pl, f32 amount);
/* debug: who hurts whom */
void mp_dbg_damage(void *pl, f32 amount)
{
    if (amount < 0.0f)
        mp_backtrace(pl == mp_player[1] ? "HURT P2" : "HURT P1", (u32)pl, (u32)*(void **)((u8 *)*(void **)0x8035B308 + 0x48));
    fn_8007225C(pl, amount);
}
#endif

/* The target an enemy actor is assigned to (0 if not an enemy or co-op is off). */
void *mp_target_for(u8 *o)
{
    u8 *p1, *p2 = mp_player[1];
    if (mp.mode != MP_COOP || !p2 || !o || F32(p2, 0x1ac) <= 0.0f || !is_enemy(o))
        return 0;
    p1 = PTR(*(void **)0x8035B308, 0x48);
#ifdef MP_TEST_TARGET_P2
    retarget(o, p2, p1);
    return p2;
#else
    {
        u8 *who = target_of(o) ? p2 : p1;
        retarget(o, who, who == p2 ? p1 : p2);
        return who;
    }
#endif
}

/* Animation events (e.g. a spider's bite frame) reach the owning actor from the world animation update, not from
   the actor's own update: fn_80222840 `actor->event(...)` (bctrl at 0x80222b24, r3 = actor). The call goes through
   this stub so "the player" is the enemy's target during the event. */
int mp_in_anim_event;  /* an animation event is being delivered (never dropped by player 2's cutscene filter) */
asm void mp_actor_event_call(void)
{
    nofralloc
    stwu r1, -64(r1)
    mflr r0
    stw r0, 68(r1)
    stw r3, 8(r1)
    stw r4, 12(r1)
    stw r5, 16(r1)
    stw r6, 20(r1)
    stw r7, 24(r1)
    stw r8, 28(r1)
    mfctr r0
    stw r0, 32(r1)
    stw r31, 60(r1)
    stw r30, 56(r1)
    bl mp_target_for
    mr r30, r3
    li r31, 0
    cmpwi r30, 0
    beq call
    lis r12, 0x8036
    lwz r12, -0x4cf8(r12)
    lwz r31, 0x48(r12)
    stw r30, 0x48(r12)
call:
    lis r12, mp_in_anim_event@ha
    addi r12, r12, mp_in_anim_event@l
    lwz r0, 0(r12)
    addi r0, r0, 1
    stw r0, 0(r12)
    lwz r0, 32(r1)
    mtctr r0
    lwz r3, 8(r1)
    lwz r4, 12(r1)
    lwz r5, 16(r1)
    lwz r6, 20(r1)
    lwz r7, 24(r1)
    lwz r8, 28(r1)
    bctrl
    lis r12, mp_in_anim_event@ha
    addi r12, r12, mp_in_anim_event@l
    lwz r0, 0(r12)
    subi r0, r0, 1
    stw r0, 0(r12)
    cmpwi r30, 0
    beq done
    lis r12, 0x8036
    lwz r12, -0x4cf8(r12)
    stw r31, 0x48(r12)
done:
    lwz r30, 56(r1)
    lwz r31, 60(r1)
    lwz r0, 68(r1)
    mtlr r0
    addi r1, r1, 64
    blr
}

int mp_is_enemy_actor(u8 *o) { return is_enemy(o); }
