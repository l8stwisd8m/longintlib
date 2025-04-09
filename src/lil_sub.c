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
    
    uint64_t carry_flag = 1;
    uint64_t tmp = 0;
    
    // invalid operand sizes
    if (src_a->size < src_b->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid sizes of subtraction terms");
        exit(EXIT_FAILURE);
    }
    
    // add -b[i] to a[i]
    for (size_t i = 0; i < src_b->size; i++) {
        tmp = src_a->val[i];
        src_a->val[i] += (carry_flag + ~src_b->val[i]);
        carry_flag = (src_a->val[i] > tmp) ? 0 : 1;
        // check borrow in some edge cases
        if ((src_a->val[i] == tmp) and (src_b->val[i] == ~0ULL)) carry_flag = 0;
    }
    
    // check borrow
    if (carry_flag == 1) return 0; 
    for (size_t i = src_b->size; i < src_a->size; i++) {
        if (src_a->val[i]) {
            src_a->val[i] -= 1;
            return 0;
        }
        else src_a->val[i] = ~0ULL;
    }
    return LIL_OVERFLOW;
}
