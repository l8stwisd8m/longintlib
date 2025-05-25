#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_short_pow_mod(lil_t *src_a, uint64_t n, lil_t *src_m) {
    // raising a to the power n modulo m
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; raising to the power can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if (src_a->size != src_m->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; raising to the power can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    // a = 0 => a ^ n mod m = 0
    if (lil_is_null(src_a)) {
        src_a->sign = LIL_PLUS;
        return 0; 
    }
    
    // n = 0 => a ^ n mod m = 1
    if (n == 0) {
        LIL_SET_NULL(src_a);
        LIL_LSD(src_a) = 1;
        src_a->sign = LIL_PLUS;
        return 0;
    }
    
    // a <- a mod m
    lil_val_mod(src_a, src_m);
    if (n == 1) return 0;
    
    lil_t *tmp, *res;
    LIL_MALLOC(tmp, src_a->size);
    LIL_MALLOC(res, src_a->size);
    LIL_CPY_VAL(res, src_a);
    
    size_t ctr = LIL_BASE - (1 +__builtin_clzll(n));
    while(ctr--) {
        LIL_CPY_VAL(tmp, res);
        lil_mul_mod(res, tmp, tmp, src_m);
        if ((n >> ctr) & 1) {
            LIL_CPY_VAL(tmp, res);
            lil_mul_mod(res, tmp, src_a, src_m);
        }
    }
    
    lil_cpy(src_a, res);
    
    LIL_FREE(tmp);
    LIL_FREE(res);
    return 0;
}
