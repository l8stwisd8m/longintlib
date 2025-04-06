#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

int lil_short_div(lil_t *dst, lil_t *src_a, uint64_t val_b) {
    // return floor from division of long a by short b
    
    // default result
    LIL_SET_NULL(dst);
    
    // exceptions
    if (lil_is_null(src_a)) return 0; // a = 0 => floor(a/b) = 0
    
    #ifdef LIL_DIVISION_BY_ZERO
    if (val_b == 0) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; division can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if (src_a->size != dst->size) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; division can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    dst->sign = src_a->sign; // save sign(a)

    // casting b value to long_int
    long_int *src_b;
    LIL_CALLOC(src_b, src_a->size);
    src_b->val[0] = val_b;
    
    int cmp_flag = lil_cmp_val(src_a, src_b);
    if (cmp_flag == -1) {
        dst->sign = LIL_PLUS;
        LIL_FREE(src_b);
        return 0; // abs(a) < b => floor(a/b) = 0
    }
    if (cmp_flag == 0) {
        dst->sign = src_a->sign;
        dst->val[0] = 1;
        LIL_FREE(src_b);
        return 0; // abs(a) = b => floor(a/b) = 1
    }
    
    uint64_t a_len = lil_len(src_a);
    uint64_t b_len = lil_len(src_b);
    uint64_t offset = a_len - b_len;
    
    // left shift b while b < a
    lil_shln(src_b, offset);
    if (lil_cmp_val(src_a, src_b) == -1) {
        lil_shr(src_b);
        offset -= 1;
    }
    
    // temporary structure
    long_int *src_t;
    LIL_CALLOC(src_t, src_a->size);
    
    // save initial value of a
    long_int *src_a_initial;
    LIL_MALLOC(src_a_initial, src_a->size);
    lil_cpy(src_a_initial, src_a);
    
    // div calculation
    src_a->sign = LIL_PLUS;
    src_b->sign = LIL_MINUS;
    for (size_t i = 0; i <= offset; i++) {
        lil_shl(dst); // dst *= 2
        lil_sum(src_t, src_a, src_b); // t = a - b
        if ((src_t->sign == LIL_PLUS) or lil_is_null(src_t)) {
            lil_inc(dst); // dst++
            lil_cpy(src_a, src_t); // a = t
        }
        lil_shr(src_b); // b /= 2
    }
    
    // restore value of a
    lil_cpy(src_a, src_a_initial);
    LIL_FREE(src_a_initial);
    
    LIL_FREE(src_t);
    LIL_FREE(src_b);
    return 0;
}
