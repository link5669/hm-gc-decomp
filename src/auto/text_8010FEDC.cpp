// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
typedef struct Node8010FEDC {
    u8 pad[8];
    struct Node8010FEDC *next;
} Node8010FEDC;
Node8010FEDC *fn_80110064(void *ctx, char *path, Node8010FEDC *node);
#pragma opt_propagation off
Node8010FEDC *fn_8010FEDC(void *ctx, Node8010FEDC *node0, char *path, s32 recurse) {
    Node8010FEDC *node = node0;
    char *p = path;
    Node8010FEDC *next;
    s32 retry;

    while (*p != 0) {
        if (recurse != 0) {
            do {
                retry = 0;
                next = node ? node->next : 0;
                node = fn_80110064(ctx, p, node);
                if (node == 0 && next != 0) {
                    retry = 1;
                    node = next;
                }
            } while (retry != 0);
        } else {
            node = fn_80110064(ctx, p, node);
            if (node == 0) {
                break;
            }
        }
        while (*p != 0 && *p != '\\') {
            p++;
        }
        if (*p == '\\') {
            p++;
        }
    }
    return node == 0 ? 0 : node;
}
#pragma opt_propagation reset

} /* extern "C" */
