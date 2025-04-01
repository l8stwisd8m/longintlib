#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

static void mul_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m);

int lil_mul_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m) {
    // multiplication of a and b modulo m
    
    // exceptions
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; modulus calculation can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    if ((dst->size != src_a->size) or (src_a->size != src_b->size) or (src_b->size != src_m->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; modulus calculation can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    
    // default: result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    
    // a = 0 or b = 0 => a * b = 0 mod m
    if (lil_is_null(src_a) or lil_is_null(src_b)) {
        return 0; // a = 0 or b = 0 => a * b = 0
    }
    // a > m => a <- a mod m
    if(lil_cmp_val(src_a, src_m) != -1) {
        long_int *tmp_a;
        LIL_MALLOC(tmp_a, src_a->size);
        LIL_CPY_VAL(tmp_a, src_a);
        lil_mod(src_a, tmp_a, src_m);
        LIL_FREE(tmp_a);
    }
    // b > m => b <- b mod m
    if(lil_cmp_val(src_b, src_m) != -1) {
        long_int *tmp_b;
        LIL_MALLOC(tmp_b, src_b->size);
        LIL_CPY_VAL(tmp_b, src_b);
        lil_mod(src_b, tmp_b, src_m);
        LIL_FREE(tmp_b);
    }
    
    if (lil_cmp_len(src_a, src_b) == 1) mul_mod(dst, src_b, src_a, src_m);
    else mul_mod(dst, src_a, src_b, src_m);
    return 0;
}

static void mul_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m) {
    uint64_t shift = lil_len(src_a) - 1;
    int64_t bit_shift = 0;
    // iterate bits of source a one by one, from the MSB to the LSB
    for (int64_t i = (int64_t)(shift / LIL_BASE); i >= 0; i--) {
        bit_shift = (i == (int64_t)(shift / LIL_BASE)) ? (int64_t)(shift % LIL_BASE) : LIL_BASE - 1;
        for (int64_t j = bit_shift; j >= 0; j--) {
            lil_shl(dst); 
            if (lil_cmp_val(dst, src_m) != -1) {
                lil_sub(dst, src_m); // dst -= m
            }
            if ((src_a->val[i] >> j) & LIL_LSBIT) {
                lil_add(dst, src_b); // dst += b
            }
            if (lil_cmp_val(dst, src_m) != -1) {
                lil_sub(dst, src_m); // dst -= m
            }
        }
    }
}
