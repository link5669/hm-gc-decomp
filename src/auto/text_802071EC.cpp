// Code of main that had no source file yet: decomp.wtf gave it this one.
// split_file divides it into the game's real files (file_status shows its range).
#include "common.h"

extern "C" {

/* QV=2.0p1 */
void fn_800F6E88(char *, const char *);
void fn_801123A4(void *, void *);
void fn_8011266C(void *, void *);

} /* extern "C" */
struct Str_802071EC {
    char s[16];
    Str_802071EC(const char *const &src) {
        s[0] = 0;
        if (src != 0) {
            if (*src == 0) s[0] = 0;
            else fn_800F6E88(s, src);
        }
    }
    const char *c_str() const { return s; }
};
extern "C" {

void fn_802071EC(u8 *self, u8 *obj) {
    Str_802071EC str(*(const char **)(obj + 476));
    const char *c = str.c_str();
    if (c == 0 || c[0] == 0) fn_801123A4(self + 64, obj);
    else fn_8011266C(self + 84, obj);
}

} /* extern "C" */
