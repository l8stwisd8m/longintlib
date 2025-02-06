#include <assert.h>
#include "../include/longintlib.h"

void lil_xor(lil_t *src_a, lil_t *src_b) {
    // bitwise exclusive or
    assert(src_a->size >= src_b->size);
    for (int i = 0; i < src_b->size; i++) {
        src_a->val[i] = src_a->val[i] ^ src_b->val[i];
    }
}
