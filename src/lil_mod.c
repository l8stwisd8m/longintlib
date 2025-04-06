#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

int lil_mod(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // return remainder after division of a by b
    
    uint64_t a_len = 0;
    uint64_t b_len = 0;
    uint64_t offset = 0;
    
    // default result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    
    // exceptions
    if (lil_is_null(src_a)) return 0; // a = 0 => a mod b = 0
    
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_b)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; modulus calculation can not be performed");
        exit(EXIT_FAILURE); // invalid b value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if ((src_a->size != dst->size) or (src_b->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; modulus calculation can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    a_len = lil_len(src_a);
    b_len = lil_len(src_b);
    offset = a_len - b_len;
    
    int cmp_flag = lil_cmp_val(src_a, src_b);
    if (cmp_flag == -1) {
        LIL_CPY_VAL(dst, src_a);
        return 0; // abs(a) < b => a mod b = a
    }
    if (cmp_flag == 0) {
        return 0; // abs(a) = b => a mod b = 0
    }
    
    // save initial values of a and b
    long_int *src_a_initial, *src_b_initial;
    LIL_MALLOC(src_a_initial, src_a->size);
    LIL_MALLOC(src_b_initial, src_b->size);
    lil_cpy(src_a_initial, src_a);
    lil_cpy(src_b_initial, src_b);
    
    // left shift b while b < a
    lil_shln(src_b, offset);
    if (lil_cmp_val(src_a, src_b) == -1) {
        lil_shr(src_b);
        offset -= 1;
    }
    
    // mod calculation
    src_a->sign = LIL_PLUS;
    src_b->sign = LIL_MINUS;
    for (size_t i = 0; i <= offset; i++) {
        lil_sum(dst, src_a, src_b); // t = a - b
        if ((dst->sign == LIL_PLUS) or lil_is_null(dst)) {
            lil_cpy(src_a, dst); // a = t
        }
        lil_shr(src_b); // b /= 2
    }
    lil_cpy(dst, src_a); // result
    
    // restore values of a and b
    lil_cpy(src_a, src_a_initial);
    lil_cpy(src_b, src_b_initial);
    LIL_FREE(src_a_initial);
    LIL_FREE(src_b_initial);
    
    dst->sign = LIL_PLUS;
    return 0;
}
