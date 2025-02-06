#include <stdint.h>
#include "../include/longintlib.h"

void lil_rev(lil_t *src) {
    // reverse source values order
    uint64_t tmp;
    for (int i = 0; i < src->size / 2; i++) {
        tmp = src->val[src->size - 1 - i];
        src->val[src->size - 1 - i] = src->val[i];
        src->val[i] = tmp;
    }
}
