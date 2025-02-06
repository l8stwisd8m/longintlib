#include "assert.h"
#include "../include/longintlib.h"

void lil_cpy(lil_t *dst, lil_t *src) {
    // copy source structure to destination
    assert(dst->size >= src->size);
    dst->sign = src->sign;
    dst->size = src->size;
    for (int i = 0; i < src->size; i++) {
        dst->val[i] = src->val[i];
    }
}
