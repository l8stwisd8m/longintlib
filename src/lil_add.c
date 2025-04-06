#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_add(lil_t *src_a, lil_t *src_b) {
    // addition of a and b
    
    uint64_t carry_value = 0;
    unsigned long long tmp = 0;
    
    #ifdef LIL_OPERAND_SIZES
    if (src_a->size < src_b->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid sizes of subtraction terms");
        exit(EXIT_FAILURE); // invalid operand sizes
    }
    #endif /* LIL_OPERAND_SIZES_CHECK */
    
    for (size_t i = 0; i < src_a->size; i++) {
        // check carry
        carry_value = __builtin_uaddll_overflow(src_a->val[i], carry_value, &tmp);
        src_a->val[i] = (uint64_t)tmp;
        if (i < src_b->size) {
            // add b[i] to a[i]
            if(__builtin_uaddll_overflow(src_a->val[i], src_b->val[i], &tmp)) carry_value += 1;
            src_a->val[i] = (uint64_t)tmp;
        }
    }
    
    // check overflow
    if (carry_value) return LIL_OVERFLOW; 
    else return 0;
}
