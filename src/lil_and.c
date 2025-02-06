#include <assert.h>
#include "../include/longintlib.h"

void lil_and(lil_t *src_a, lil_t *src_b) {
    // bitwise conjunction
    assert(src_a->size >= src_b->size);
    for (int i = 0; i < src_b->size; i++) {
        src_a->val[i] = src_a->val[i] & src_b->val[i];
    }
}
