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

    if (n == 0) return; // shift by 0 bits

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
        carry_mask = carry_mask ^ (LIL_LSBIT << i);
    }
    for (int i = src->size - 1; i >= 0; i--) {
        // shift by (n mow w) bits
        tmp = src->val[i] & carry_mask;
        src->val[i] = (src->val[i] >> b_shift) ^ carry_value;
        // reverse carry value bits order
        carry_value = 0;
        for (int j = 0; j < b_shift; j++) {
            carry_value = carry_value ^ ((LIL_MSBIT & (tmp << (LIL_BASE - 1 - j))) >> j);
        }
    }
}
