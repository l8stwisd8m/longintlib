#include <stdint.h>
#include "../include/longintlib.h"

void lil_short_add(lil_t *src_a, uint64_t src_b) {
    // add short abs(b) to abs(values) of long a
    uint64_t tmp = src_a->val[0];
    src_a->val[0] += src_b;
    
    // carry
    if (src_a->val[0] < tmp) {
        for (int i = 1; i < src_a->size; i++) {
            if (src_a->val[i] + 1 < src_a->val[i]) src_a->val[i] += 1;
            else {
                src_a->val[i] += 1;
                break;
            }
        }
    }
}
