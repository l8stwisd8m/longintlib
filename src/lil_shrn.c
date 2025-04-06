#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_shrn(lil_t *src, uint64_t n) {
    // right shift by n bits
    
    int flag = 0;
    size_t w_shift = n / LIL_BASE;
    size_t b_shift = n % LIL_BASE;
    uint64_t tmp = 0;
    uint64_t carry_value = 0;
    uint64_t carry_mask = 0;
    
    // shift by word size
    if ((w_shift) and (src->val[0])) flag = LIL_OVERFLOW;
    for (size_t i = 0; i < w_shift; i++) {
        for (size_t j = 0; j < src->size - 1; j++) {
            src->val[j] = src->val[j + 1];
        }
        src->val[src->size - 1] = 0;
    }

    // shift by (n mod w) bits
    for (size_t i = 0; i < b_shift; i++) {
        // carry mask generation
        carry_mask = carry_mask | (LIL_LSBIT << i);
    }
    for (size_t i = 0; i < src->size; i++) {
        tmp = src->val[src->size - i - 1] & carry_mask;
        src->val[src->size - i - 1] = (src->val[src->size - i - 1] >> b_shift) ^ carry_value;
        carry_value = 0 ^ (tmp << (LIL_BASE - b_shift));
    }
    if ((b_shift) and (carry_value)) flag = LIL_OVERFLOW;
    
    return flag;
}
