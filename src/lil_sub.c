#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <iso646.h>
#include <stdint.h>
#include <stdlib.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_sub(lil_t *src_a, lil_t *src_b) {
    // subtracting b from a
    
    unsigned long long tmp = 0;
    uint64_t borrow_flag = 0;
    
    #ifdef LIL_OPERAND_SIZES
    if (src_a->size < src_b->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid sizes of subtraction terms");
        exit(EXIT_FAILURE); // invalid operand sizes
    }
    #endif /* LIL_OPERAND_SIZES */
    
    // subtract b[i] from a[i]
    for (size_t i = 0; i < src_b->size; i++) {
        borrow_flag = ((borrow_flag) and (src_a->val[i] == 0)) or \
        __builtin_usubll_overflow(src_a->val[i] - borrow_flag, src_b->val[i], &tmp);
        src_a->val[i] = (uint64_t)tmp;
    }
    
    // check borrow
    if (borrow_flag == 0) return 0; 
    for (size_t i = src_b->size; i < src_a->size; i++) {
        if (src_a->val[i]) {
            src_a->val[i] -= 1;
            return 0;
        }
        else src_a->val[i] = ~0ULL;
    }
    return LIL_OVERFLOW;
}
