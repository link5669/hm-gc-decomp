// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct { u32 v[3]; } T12_80108A94;
struct Node_80108A94 { Node_80108A94 *next; u32 f4; T12_80108A94 f8; u32 f20; };
struct List_80108A94 { Node_80108A94 *head; };
s32 fn_800E24F0(void *p);
s32 fn_800E2520(void *a, void *b);
void __dl__FPv(void *p);

void fn_80108A94(List_80108A94 *list, u32 a, void *b, u32 c) {
    Node_80108A94 *cur;
    Node_80108A94 *prev;
    Node_80108A94 *h = list->head;
    cur = h;
    prev = h;
    while (cur != 0) {
        if (fn_800E24F0(b) != 0) {
            T12_80108A94 tmp = cur->f8;
            if (fn_800E2520(&tmp, b) != 0) {
                prev = cur;
                cur = cur->next;
                continue;
            }
        }
        if (c != 0 && c != cur->f20) {
            prev = cur;
            cur = cur->next;
            continue;
        }
        if (cur->f4 != a) {
            prev = cur;
            cur = cur->next;
            continue;
        }
        if (cur != 0) {
            Node_80108A94 *del = cur;
            prev->next = cur->next;
            if (cur == list->head) {
                list->head = cur->next;
                prev = cur->next;
            }
            cur = cur->next;
            __dl__FPv(del);
        }
    }
}

} /* extern "C" */
