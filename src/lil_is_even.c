#include "../include/longintlib.h"

int lil_is_even(lil_t *src) {
    // return 1 if source is even, 0 otherwise
    if (src->val[0] & 1) return 0;
    else return 1;
}
