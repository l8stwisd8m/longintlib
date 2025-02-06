#include "../include/longintlib.h"

void lil_inc(lil_t *src) {
    // increment source value
    for (int i = 0; i < src->size; i++) {
        if (src->val[i] + 1 < src->val[i]) src->val[i] += 1;
        else {
            src->val[i] += 1;
            break;
        }
    }
}
