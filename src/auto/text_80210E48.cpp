// Merged TU: text_80210E48, text_80210F20 and text_802110C8 share the string pool at 0x802A6ED0.
#include "common.h"

extern "C" {

/* QV=2.0p1 */
#pragma readonly_strings on
typedef struct __va_list_struct {
    char gpr;
    char fpr;
    char reserved[2];
    char *input_arg_area;
    char *reg_save_area;
} va_list[1];
#define va_start(ap, fmt) ((void)fmt, __builtin_va_info(&ap))
extern const char lbl_80365848[5];
s32 fn_800E8F6C(char *, const char *, ...);
s32 fn_800E904C(char *, const char *, void *);
void fn_80060568(char *, s32, s32, s32);
const char *fn_80210E48(u32 n) {
    switch (n) {
    case 0: return "no error";
    case 1: return "file or directory not found";
    case 2: return "error opening the specified file";
    case 3: return "general error";
    case 4: return "media not formatted";
    case 5: return "media format incorrect";
    case 6: return "buffer supplied was insufficient";
    case 7: return "asynchronous operation is pending";
    case 8: return "file pointer is out of bounds";
    case 9: return "access violation";
    case 10: return "write was only partially completed";
    case 11: return "memory card error (is the card attached?)";
    case 12: return "memory card is not attached";
    case 13: return "memory card file system has no save game specified";
    case 14: return "device is out of space";
    case 15: return "bad file descriptor";
    case 16: return "media not ready";
    case 17: return "media is corrupt";
    case 18: return "media is invalid";
    case 20: return "feature is unimplemented";
    case 21: return "feature is unsupported";
    case 19:
    default: return "<unspecified error>";
    }
}
#pragma opt_propagation off
void fn_80210F20(u32 code, const char *fmt0, ...) {
    va_list args;
    char buf[512];
    const char *fmt;
    char *p;
    s32 n;
    va_start(args, fmt0);
    fmt = fmt0;
    if (fmt == 0) fmt = "<No Message>";
    n = fn_800E8F6C(buf, lbl_80365848, fn_80210E48(code));
    p = buf + n;
    fn_800E904C(p, fmt, args);
    fn_80060568(buf, 0, 0, 0);
}
#pragma opt_propagation reset
void fn_802110C8(u32 code, const char *msg, void *args) {
    char buf[528];
    char *p;
    if (msg == 0) {
        msg = "<No Message>";
    }
    p = buf + fn_800E8F6C(buf, lbl_80365848, fn_80210E48(code));
    fn_800E904C(p, msg, args);
    fn_80060568(buf, 0, 0, 0);
}

} /* extern "C" */
