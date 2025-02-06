#include <stdint.h>
#include <assert.h>
#include "../include/longintlib.h"

void lil_add(lil_t *src_a, lil_t *src_b) {
    // addition of a and b
    uint64_t carry_flag = 0;
    uint64_t tmp = 0;
    assert(src_a->size >= src_b->size);
    for (int i = 0; i < src_a->size; i++) {
        // check carry
        tmp = src_a->val[i];
        src_a->val[i] += carry_flag;
        carry_flag = (tmp > src_a->val[i]) ? 1 : 0;
        if (i < src_b->size) {
            // add b[i] to a[i]
            tmp = src_a->val[i];
            src_a->val[i] += src_b->val[i];
            if (tmp > src_a->val[i]) carry_flag += 1;
        }
    }
}
