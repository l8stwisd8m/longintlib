#include "../include/longintlib.h"

void lil_dec(lil_t *src) {
    // decrement source value
    for (int i = 0; i < src->size; i++) {
        if (src->val[i] == 0) src->val[i] -= 1;
        else {
            src->val[i] -= 1;
            break;
        }
    }
}
