// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct N801D25A0 {
    struct N801D25A0 *parent;
    struct N801D25A0 *child;
    struct N801D25A0 *next;
    u8 pad[8];
    char *volatile label;
    s32 open;
} N801D25A0;
extern volatile f32 lbl_803651A8;
extern volatile f32 lbl_8035B038;
extern volatile f32 lbl_8035B03C;
void fn_801CCC7C(void *res, u8 **b, u8 **a, u32 x, u32 y);
void fn_8012D0A4(void *font, f32 *out, char *text, f32 *pos, u8 *col, s32 flags, f32 s, f32 t, f32 u);

void fn_801D25A0(u8 *self, N801D25A0 *node, f32 x, f32 y) {
    f32 out[3];
    f32 pt[2];
    u8 *a;
    u8 *b;
    void *font;
    f32 w;
    N801D25A0 *prev;
    N801D25A0 *c;
    a = 0;
    b = 0;
    font = 0;
    while (node != 0) {
        (*(s32 *)(self + 836))++;
        w = *(f32 *)(self + 844);
        w += *(f32 *)(self + 824);
        if (*(void **)(self + 768) != 0) {
            if (a == 0) {
                fn_801CCC7C(*(void **)(self + 768), &b, &a, *(u32 *)(self + 324), *(u32 *)(self + 104));
            }
            if (font == 0) {
                font = *(void **)(a + 36);
            }
            pt[0] = x;
            pt[1] = y;
            fn_8012D0A4(font, out, node->label, pt, a + 48, 17, lbl_803651A8, lbl_8035B038, lbl_8035B03C);
            w += out[2] - *(f32 *)(self + 72);
        }
        if (w > *(f32 *)(self + 840)) {
            *(f32 *)(self + 840) = w;
        }
        if (node->open != 0 && node->child != 0) {
            x += *(f32 *)(self + 824);
            y += *(f32 *)(self + 820);
            node = node->child;
        } else if (node->next != 0) {
            y += *(f32 *)(self + 820);
            node = node->next;
        } else {
            prev = node;
            node = node->parent;
            while (node != 0) {
                x -= *(f32 *)(self + 824);
                y -= *(f32 *)(self + 820);
                c = node->child;
                while (c != prev) {
                    c = c->next;
                    y -= *(f32 *)(self + 820);
                }
                if (node->next != 0) {
                    y += *(f32 *)(self + 820);
                    node = node->next;
                    break;
                }
                prev = node;
                node = node->parent;
            }
        }
    }
}

} /* extern "C" */
