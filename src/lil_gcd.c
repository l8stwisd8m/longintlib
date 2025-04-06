#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

static uint64_t short_gcd(uint64_t a, uint64_t b);
static void binary_reduction(lil_t *a, lil_t *b);

int lil_gcd(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // greatest common divisor of sources a and b
    
    // default result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    dst->val[0] = 1; // set gcd = 1
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_a) and lil_is_null(src_b)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; gcd calculation can not be performed");
        exit(EXIT_FAILURE); // invalid value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if ((src_a->size != dst->size) or (src_b->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; gcd calculation can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES_CHECK */
    
    if (lil_is_null(src_b)) {
        LIL_CPY_VAL(dst, src_a);
        return 0; // gcd(a, 0) = a
    }
    if (lil_is_null(src_a)) {
        LIL_CPY_VAL(dst, src_b);
        return 0; // gcd(b, 0) = b
    }
    if (lil_cmp_val(src_a, src_b) == 0) {
        LIL_CPY_VAL(dst, src_a);
        return 0; // gcd(a, a) = a
    }
    
    uint64_t a_len = lil_len(src_a);
    uint64_t b_len = lil_len(src_b);
    
    // a and b values are short
    if ((a_len <= LIL_BASE) and (b_len <= LIL_BASE)) {
        dst->val[0] = short_gcd(src_a->val[0], src_b->val[0]);
        return 0;
    }
    
    // value of a or b is short 
    if (b_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, src_a, src_b->val[0]);
        dst->val[0] = short_gcd(tmp, src_b->val[0]);
        return 0;
    }
    if (a_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, src_b, src_a->val[0]);
        dst->val[0] = short_gcd(tmp, src_a->val[0]);
        return 0;
    }
    
    // both a and b are long integers 
    long_int *tmp_a, *tmp_b;
    LIL_MALLOC(tmp_a, src_a->size);
    LIL_MALLOC(tmp_b, src_b->size);
    LIL_CPY_VAL(tmp_a, src_a);
    LIL_CPY_VAL(tmp_b, src_b);
    
    // primary length reducing 
    uint64_t shift_amount = 0;
    while (LIL_IS_EVEN(tmp_a) and (LIL_IS_EVEN(tmp_b))) {
        lil_shr(tmp_a); // a /= 2
        lil_shr(tmp_b); // b /= 2
        shift_amount += 1;
    }
    
    // further length reducing operations, until it's possible to perform short gcd
    // assuming a and b are long integers at this point
    while ((a_len > LIL_BASE) or (b_len > LIL_BASE)) {
        // edge cases
        if (lil_is_null(tmp_a)) {
            break; // a = 0 => gcd(a, b) = b
        }
        if (lil_is_null(tmp_b)) {
            break; // b = 0 => gcd(a, b) = a
        }
        if (lil_cmp_val(tmp_a, tmp_b) == 0) {
            break; // a = b => gcd(a, b) = a
        }
        
        binary_reduction(tmp_a, tmp_b);
        
        a_len = lil_len(tmp_a);
        b_len = lil_len(tmp_b);
    }
    
    // cheack edge cases again
    if (lil_is_null(tmp_a)) {
        LIL_CPY_VAL(dst, tmp_b);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return 0; // a = 0 => gcd(a, b) = b
    }
    if (lil_is_null(tmp_b)) {
        LIL_CPY_VAL(dst, tmp_a);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return 0; // b = 0 => gcd(a, b) = a
    }
    if (lil_cmp_val(tmp_a, tmp_b) == 0) {
        LIL_CPY_VAL(dst, tmp_a);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return 0; // a = b => gcd(a, b) = a
    }

    a_len = lil_len(tmp_a);
    b_len = lil_len(tmp_b);
    
    // a and b values are short
    if ((a_len <= LIL_BASE) and (b_len <= LIL_BASE)) {
        dst->val[0] = short_gcd(tmp_a->val[0], tmp_b->val[0]);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return 0;
    }
     
    // value of a or b is short 
    if (b_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, tmp_a, tmp_b->val[0]);
        dst->val[0] = short_gcd(tmp, tmp_b->val[0]);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return 0;
    }
    if (a_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, tmp_b, tmp_a->val[0]);
        dst->val[0] = short_gcd(tmp, tmp_a->val[0]);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return 0;
    }
    
    LIL_FREE(tmp_a);
    LIL_FREE(tmp_b);
    assert((a_len > LIL_BASE) and (b_len > LIL_BASE)); // something went wrong
    return 0;
}

static uint64_t short_gcd(uint64_t a, uint64_t b) {
    assert(a and b); // just in case 
    
    uint64_t tmp_a = (a > b) ? a : b;
    uint64_t tmp_b = (a > b) ? b : a;
    uint64_t residue = tmp_a % tmp_b;
    
    while (residue != 0) {
        residue = tmp_a % tmp_b;
        tmp_a = tmp_b;
        tmp_b = residue;
    }
    
    return tmp_a;
}

static void binary_reduction(lil_t *a, lil_t *b) {
    // assuming a and b are not equal to zero
    while (LIL_IS_EVEN(a)) {
        lil_shr(a); // a /= 2
    }
    while (LIL_IS_EVEN(b)) {
        lil_shr(b); // b /= 2
    }
    int cmp_flag = lil_cmp_val(a, b);
    if (cmp_flag == 1) {
        lil_sub(a, b); // a -= b if a > b
    }
    if (cmp_flag == -1) {
        lil_sub(b, a); // b -= a if a < b
    }
}
