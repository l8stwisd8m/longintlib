#include "../include/longintlib.h"

int lil_is_odd(lil_t *src) {
    // return 1 if source is odd, 0 otherwise
    
    if (src->val[0] & 1) return 1;
    else return 0;
}
