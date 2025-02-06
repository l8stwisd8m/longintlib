#include <stdint.h>
#include <assert.h>
#include "../include/longintlib.h"

void lil_sub(lil_t *src_a, lil_t *src_b) {
    // subtracting b from a
    uint64_t carry_flag = 1;
    uint64_t tmp = 0;
    assert(src_a->size >= src_b->size);
    
    // add -b[i] to a[i]
    for (int i = 0; i < src_b->size; i++) {
        tmp = src_a->val[i];
        src_a->val[i] += (carry_flag + ~src_b->val[i]);
        carry_flag = (src_a->val[i] > tmp) ? 0 : 1;
    }
    
    // check borrow
    for (int i = src_b->size; i < src_a->size; i++) {
        if (src_a->val[i]) {
            src_a->val[i] -= 1;
            break;
        }
        else src_a->val[i] = ~0;
    }
}
