#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"

int lil_sum_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m) {
    // arithmetic sum of a and b modulo m
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; arithmetic sum calculation can not be performed");
        exit(EXIT_FAILURE); // invalid m value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if ((src_a->size != dst->size) or (src_m->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; arithmetic sum calculation can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    // both a and b are positive or negative at the same time
    if (src_a->sign ^ src_b->sign) {
        lil_val_mod(src_a, src_m);
        lil_val_mod(src_b, src_m);
        lil_sum(dst, src_a, src_b);
        lil_val_mod(dst, src_m);
    }
    
    // either a or b is negative
    else {
        lil_sum(dst, src_a, src_b);
        lil_val_mod(dst, src_m);
    }
    
    return 0;
}
