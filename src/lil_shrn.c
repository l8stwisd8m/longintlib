#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void lil_shrn(lil_t *src, uint64_t n) {
    // right shift by n bits
    int w_shift = n / LIL_BASE;
    int b_shift = n % LIL_BASE;
    uint64_t tmp = 0;
    uint64_t carry_value = 0;
    uint64_t carry_mask = 0;

    // shift by word size
    for (int i = 0; i < w_shift; i++) {
        for (int j = 0; j < src->size - 1; j++) {
            src->val[j] = src->val[j + 1];
        }
        src->val[src->size - 1] = 0;
    }

    // shift by (n mod w) bits
    for (int i = 0; i < b_shift; i++) {
        // carry mask generation
        carry_mask = carry_mask | (LIL_LSBIT << i);
    }
    for (int i = src->size - 1; i >= 0; i--) {
        tmp = src->val[i] & carry_mask;
        src->val[i] = (src->val[i] >> b_shift) ^ carry_value;
        carry_value = (carry_value ^ carry_value) ^ (tmp << (LIL_BASE - b_shift));
    }
}
