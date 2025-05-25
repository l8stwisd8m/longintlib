#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_pow_mod(lil_t *dst, lil_t *src_a, lil_t *src_n, lil_t *src_m) {
    // raising a to the power n modulo m
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; raising to the power can not be performed");
        exit(EXIT_FAILURE); // invalid m value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if ((dst->size != src_a->size) or (src_a->size != src_n->size) or (src_n->size != src_m->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; raising to the power can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    // default result
    LIL_SET_NULL(dst);
    dst->sign = LIL_PLUS;
    
    // a = 0 => a ^ n mod m = 0
    if (lil_is_null(src_a)) {
        return 0; 
    }
    
    // n = 0 => a ^ n mod m = 1
    if (lil_is_null(src_n)) {
        LIL_LSD(dst) = 1;
        return 0;
    }
    
    // a <- a mod m
    lil_val_mod(src_a, src_m);
    
    lil_t *tmp;
    LIL_MALLOC(tmp, src_a->size);
    LIL_CPY_VAL(dst, src_a);
    
    uint64_t shift = lil_len(src_n) - 1;
    int64_t bit_shift = 0;
    // iterate bits of source n one by one, from the MSB (not including MSB) to the LSB
    for (int64_t i = (int64_t)(shift / LIL_BASE); i >= 0; i--) {
        bit_shift = (i == (int64_t)(shift / LIL_BASE)) ? (int64_t)(shift % LIL_BASE) - 1 : LIL_BASE - 1;
        for (int64_t j = bit_shift; j >= 0; j--) {
            LIL_CPY_VAL(tmp, dst);
            lil_mul_mod(dst, tmp, tmp, src_m);
            if ((src_n->val[i] >> j) & 1) {
                LIL_CPY_VAL(tmp, dst);
                lil_mul_mod(dst, tmp, src_a, src_m);
            }
        }
    }
    
    LIL_FREE(tmp);
    return 0;
}
