/* Multiplayer mod: debug warp progress (see hm-work/mp/progression.md).
   Areas in story order with the spirits their door requires and the lantern gem level a normal run has there. */
#include "mp.h"

#define PTR(p, o) (*(void **)((u8 *)(p) + (o)))

typedef struct Area { const char *key, *name; u16 spirits; u8 gems; } Area;
static const Area s_areas[] = {
    {"GRTHALL", "GREAT HALL", 0, 1},      {"FOYER", "FOYER", 15, 1},         {"CONSERV", "CONSERVATORY", 30, 1},
    {"GROOM", "GAME ROOM", 50, 1},        {"HALLAB", "LOWER HALLWAY", 170, 3}, {"KITCHEN", "KITCHEN", 170, 3},
    {"DINROOM", "DINING ROOM", 190, 3},   {"MAID", "MAID'S ROOM", 190, 3},   {"BALLROOM", "BALLROOM", 220, 3},
    {"GRAVEYD", "GRAVEYARD", 340, 7},     {"WINTER", "WINTER GARDEN", 340, 7}, {"MAUSOLM", "MAUSOLEUM", 365, 7},
    {"PANTRY", "PANTRY", 405, 7},         {"HALLCD", "UPPER HALLWAY", 525, 15}, {"GUEST", "GUEST ROOM", 525, 15},
    {"MASTRBED", "MASTER BEDROOM", 525, 15}, {"TOYROOM", "TOY ROOM", 525, 31}, {"SUNROOM", "SUN ROOM", 585, 15},
    {"MUSEUM", "LIBRARY", 700, 31},       {"CHILDREN", "CHILDREN'S ROOM", 700, 15}, {"SITTING", "SITTING ROOM", 700, 31},
    {"PARLOR", "PARLOR", 750, 31},        {"GALLERY", "GALLERY", 860, 63},   {"OBSERV", "OBSERVATORY", 860, 63},
    {"ATTIC", "ATTIC", 885, 63},          {"LAB", "LABORATORY", 885, 63},
};
#define NAREAS ((int)(sizeof(s_areas) / sizeof(s_areas[0])))

int mp_area_count(void) { return NAREAS; }
const char *mp_area_label(int i) { return s_areas[i].name; }

/* key as the 8-byte level key */
void mp_area_key(int i, char *key8)
{
    int k;
    for (k = 0; k < 8; k++)
        key8[k] = 0;
    for (k = 0; k < 8 && s_areas[i].key[k]; k++)
        key8[k] = s_areas[i].key[k];
}

/* Spirits total seen by the doors (fn_8003C930 sums every level's found spirits): after a warp it is at least
   what a normal run would have at that point. */
static u32 s_min_spirits;
u32 fn_8003C930(void *p);
u32 mp_total_spirits(void *p)
{
    u32 n = fn_8003C930(p);
    return n < s_min_spirits ? s_min_spirits : n;
}

static s32 *persist_int(const char *name)
{
    u8 *app = *(u8 **)0x8035B65C, *reg, *var, *vt;
    u8 *fn_80207198(u8 *, const char *, s32);
    if (!app || !(reg = PTR(app, 0x24)))
        return 0;
    var = fn_80207198(reg + 0x3e0, name, 0);
    if (!var || !(vt = PTR(var, 8)))
        return 0;
    return ((s32 * (*)(void *, s32)) PTR(vt, 0x1c))(var, 0);
}

void mp_apply_area_progress(int i)
{
    s32 *gems = persist_int("mGemFlag");
    s_min_spirits = s_areas[i].spirits;
    if (gems && *gems < s_areas[i].gems)
        *gems = s_areas[i].gems;  /* lantern upgrades (never take gems away) */
    OSReport("[mp] warp progress: %s spirits>=%d gems %d (var %p)\n", s_areas[i].name, s_areas[i].spirits,
             s_areas[i].gems, gems);
}

/* old interface (unused now) */
int mp_area_name(const char *key8, char *out, int n) { (void)key8; (void)out; (void)n; return 0; }
void mp_apply_progress(const char *key8) { (void)key8; }
