#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintmacro.h"

int lil_div_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m) {
    // multiplication of a and inverted b modulo m
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; modulo division can not be performed");
        exit(EXIT_FAILURE); // invalid m value
    }
    if (lil_is_null(src_b)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; modulo division can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if ((src_a->size != dst->size) or (src_m->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; modulo division can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES_CHECK */
    
    // correct input
    lil_val_mod(src_a, src_m); // a <- a mod m
    
    // b = 1 => a / b mod m = a mod m
    if (lil_is_one(src_b)) {
        LIL_SET_NULL(dst);
        LIL_CPY_VAL(dst, src_a);
        return 0;
    }
    
    long_int *tmp_b;
    LIL_MALLOC(tmp_b, src_b->size);
    lil_inv(tmp_b, src_b, src_m); // b <- inv(b)
    lil_mul_mod(dst, src_a, tmp_b, src_m); // a / b mod m
    
    LIL_FREE(tmp_b);
    return 0;
}
