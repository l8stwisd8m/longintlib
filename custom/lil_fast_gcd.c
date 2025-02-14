#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include <inttypes.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"
#define GCD_LEN_DIF 16 // value in range [0, 32), recommended option - between 8 and 16
#define GCD_SPLIT 32

static uint64_t short_gcd(uint64_t a, uint64_t b);
static void binary_reduction(lil_t *a, lil_t *b);
static void extended_reduction(lil_t *a, lil_t *b);

void lil_fast_gcd(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // greatest common divisor of sources a and b
    
    // default result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    dst->val[0] = 1; // set gcd = 1
    
    // exceptions
    assert((lil_is_null(src_a) == 0) or (lil_is_null(src_b) == 0));
    if (lil_is_null(src_b)) {
        LIL_CPY_VAL(dst, src_a);
        return; // gcd(a, 0) = a
    }
    if (lil_is_null(src_a)) {
        LIL_CPY_VAL(dst, src_b);
        return; // gcd(b, 0) = b
    }
    if (lil_cmp_val(src_a, src_b) == 0) {
        LIL_CPY_VAL(dst, src_a);
        return; // gcd(a, a) = a
    }
    
    uint64_t a_len = lil_len(src_a);
    uint64_t b_len = lil_len(src_b);
    
    // a and b values are short
    if ((a_len <= LIL_BASE) and (b_len <= LIL_BASE)) {
        dst->val[0] = short_gcd(src_a->val[0], src_b->val[0]);
        return;
    }
    
    // value of a or b is short 
    if (b_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, src_a, src_b->val[0]);
        dst->val[0] = short_gcd(tmp, src_b->val[0]);
        return;
    }
    if (a_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, src_b, src_a->val[0]);
        dst->val[0] = short_gcd(tmp, src_a->val[0]);
        return;
    }
    
    // both a and b are long integers 
    assert(src_a->size == src_b->size);
    long_int *tmp_a, *tmp_b;
    LIL_MALLOC(tmp_a, src_a->size);
    LIL_MALLOC(tmp_b, src_b->size);
    LIL_CPY_VAL(tmp_a, src_a);
    LIL_CPY_VAL(tmp_b, src_b);
    
    // primary length reducing 
    uint64_t shift_amount = 0;
    while (lil_is_even(tmp_a) and lil_is_even(tmp_b)) {
        lil_shr(tmp_a); // a /= 2
        lil_shr(tmp_b); // b /= 2
        shift_amount += 1;
    }
    
    // further length reducing operations, until it's possible to perform short gcd
    // assuming a and b are long integers at this point
    int cmp_flag = 0;
    int64_t len_dif = 0;
    while ((a_len > LIL_BASE) or (b_len > LIL_BASE)) {
        // edge cases
        if (lil_is_null(tmp_a)) {
            //LIL_CPY_VAL(dst, tmp_b);
            break; // a = 0 => gcd(a, b) = b
        }
        if (lil_is_null(tmp_b)) {
            //LIL_CPY_VAL(dst, tmp_a);
            break; // b = 0 => gcd(a, b) = a
        }
        if (lil_cmp_val(tmp_a, tmp_b) == 0) {
            //LIL_CPY_VAL(dst, tmp_a);
            break; // a = b => gcd(a, b) = a
        }
        
        // condition for extended reduction
        len_dif = a_len - b_len;
        len_dif = (len_dif < 0) ? -len_dif : len_dif; // abs(len_dif)
        
        // perform binary reduction when extended reduction is not possible
        if (len_dif > GCD_LEN_DIF) {
            binary_reduction(tmp_a, tmp_b);
        }
        
        // perform extended reduction if it's possible
        if ((len_dif <= GCD_LEN_DIF) and (tmp_a->val[tmp_a->size - 1] ==0) and (tmp_b->val[tmp_b->size - 1] == 0)) {
            extended_reduction(tmp_a, tmp_b);
        }
        
        a_len = lil_len(tmp_a);
        b_len = lil_len(tmp_b);
    }
    
    // cheack edge cases again
    if (lil_is_null(tmp_a)) {
        LIL_CPY_VAL(dst, tmp_b);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return; // a = 0 => gcd(a, b) = b
    }
    if (lil_is_null(tmp_b)) {
        LIL_CPY_VAL(dst, tmp_a);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return; // b = 0 => gcd(a, b) = a
    }
    if (lil_cmp_val(tmp_a, tmp_b) == 0) {
        LIL_CPY_VAL(dst, tmp_a);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return; // a = b => gcd(a, b) = a
    }

    a_len = lil_len(tmp_a);
    b_len = lil_len(tmp_b);
    
    // a and b values are short
    if ((a_len <= LIL_BASE) and (b_len <= LIL_BASE)) {
        dst->val[0] = short_gcd(tmp_a->val[0], tmp_b->val[0]);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return;
    }
     
    // value of a or b is short 
    if (b_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, tmp_a, tmp_b->val[0]);
        dst->val[0] = short_gcd(tmp, tmp_b->val[0]);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return;
    }
    if (a_len <= LIL_BASE) {
        uint64_t tmp = 0;
        lil_short_mod(&tmp, tmp_b, tmp_a->val[0]);
        dst->val[0] = short_gcd(tmp, tmp_a->val[0]);
        lil_shln(dst, shift_amount); // multiply gcd by power of 2, if necessary
        LIL_FREE(tmp_a);
        LIL_FREE(tmp_b);
        return;
    }
    
    LIL_FREE(tmp_a);
    LIL_FREE(tmp_b);
    assert((a_len > LIL_BASE) and (b_len > LIL_BASE)); // something went wrong
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
    while (lil_is_even(a)) {
        lil_shr(a); // a /= 2
    }
    while (lil_is_even(b)) {
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

static void extended_reduction(lil_t *a, lil_t *b) {
    // most significant digits (64 bits) of a and b 
    uint64_t numerator = 0;
    uint64_t denominator = 0;
    
    // actual numbers of most significat digits of a and b
    int msd_a = (int)a->size;
    int msd_b = (int)b->size;
    for (int i = msd_a - 1; i >= 0; i--) {
        msd_a -= 1;
        if (a->val[i]) break;
    }
    for (int i = msd_b - 1; i >= 0; i--) {
        msd_b -= 1;
        if (b->val[i]) break;
    }
    
    if ((msd_a == 0) and (msd_b == 0)) {
        return; // a and b are single digits or both are null
    }
    
    // numerator and denominator
    if (msd_a == msd_b) {
        // most significant digits have actually the same number in both a and b
        if (((a->val[msd_a] & LIL_LH) != 0) or ((b->val[msd_b] & LIL_LH) != 0)) {
            numerator = a->val[msd_a];
            denominator = b->val[msd_b];
        }
        else {
            numerator = ((a->val[msd_a] & LIL_RH) << GCD_SPLIT) | ((a->val[msd_a - 1] & LIL_LH) >> GCD_SPLIT);
            denominator = ((b->val[msd_a] & LIL_RH) << GCD_SPLIT) | ((b->val[msd_b - 1] & LIL_LH) >> GCD_SPLIT);
        }
    }
    if (msd_a > msd_b) {
        // most significant digits are located in the adjacent positions (a > b)
        numerator = ((a->val[msd_a] & LIL_RH) << GCD_SPLIT) | ((a->val[msd_a - 1] & LIL_LH) >> GCD_SPLIT);
        denominator = ((b->val[msd_a] & LIL_RH) << GCD_SPLIT) | ((b->val[msd_a - 1] & LIL_LH) >> GCD_SPLIT);
    }
    if (msd_a < msd_b) {
        // most significant digits are located in the adjacent positions (a < b)
        numerator = ((a->val[msd_b] & LIL_RH) << GCD_SPLIT) | ((a->val[msd_b - 1] & LIL_LH) >> GCD_SPLIT);
        denominator = ((b->val[msd_b] & LIL_RH) << GCD_SPLIT) | ((b->val[msd_b - 1] & LIL_LH) >> GCD_SPLIT);
    }
    
    // set Bezout coefficients
    uint64_t residue = 0;
    int64_t bezout_x_a = 0; int64_t bezout_y_a = 0; // Bezout's identity for a
    int64_t bezout_x_b = 0; int64_t bezout_y_b = 0; // Bezout's identity for b
    int swap_flag = 0;
    if (numerator < denominator) {
        bezout_x_a = 0; bezout_y_a = 1;
        bezout_x_b = 1; bezout_y_b = 0;
        swap_flag = 1;
    }
    else {
        bezout_x_a = 1; bezout_y_a = 0;
        bezout_x_b = 0; bezout_y_b = 1;
    }
    
    // swap numerator and denominator if necessary
    uint64_t tmp = (numerator > denominator) ? denominator : numerator;
    numerator = (numerator > denominator) ? numerator : denominator;
    denominator = tmp; // now, numerator > denominator
    
    // approximations 
    uint64_t lesser_num = numerator;
    uint64_t lesser_den = denominator + 1;
    uint64_t greater_num = numerator + 1;
    uint64_t greater_den = denominator;
    uint64_t lesser_q = lesser_num / lesser_den;
    uint64_t greater_q = greater_num / greater_den;
    
    if (lesser_q == greater_q) {
        residue = numerator - lesser_q * denominator;
    }
    
    while (residue != 0) {
        // update residue and Bezout coefficients
        tmp = bezout_x_a; bezout_x_a = bezout_x_b; bezout_x_b = tmp - lesser_q * (bezout_x_a);
        tmp = bezout_y_a; bezout_y_a = bezout_y_b; bezout_y_b = tmp - lesser_q * (bezout_y_a);
        residue = numerator % denominator; numerator = denominator; denominator = residue;
        
        // update lesser quotient
        tmp = lesser_num % lesser_den; lesser_num = lesser_den; lesser_den = tmp;
        lesser_q = lesser_num / lesser_den;
        
        // update greater quotient
        tmp = greater_num % greater_den; greater_num = greater_den; greater_den = tmp;
        greater_q = greater_num / greater_den;
        
        if (lesser_q != greater_q) {
            break; // quotients mismatch
        }
    }
    
    if (swap_flag) {
        tmp = -bezout_x_a; bezout_x_a = -bezout_y_a; bezout_y_a = tmp;
        tmp = -bezout_x_b; bezout_x_b = -bezout_y_b; bezout_y_b = tmp;
    }
    
    // further reduction of a and b (exceptions)
    if ((bezout_x_a == 0) and (bezout_y_a == 1) and (bezout_x_b == 1) and (bezout_y_b == 0)) {
        return;  // values are not reduced
    }
    if ((bezout_x_a == 1) and (bezout_y_a == 0) and (bezout_x_b == 0) and (bezout_y_b == 1)) {
        return;  // values are not reduced
    }
    int cmp_flag = lil_cmp_val(a, b);
    if (cmp_flag == 0) {
        return; // assertion (a = b)
    }
    
    long_int *new_a, *new_b, *tmp_a, *tmp_b;
    LIL_CALLOC(new_a, a->size);
    LIL_CALLOC(new_b, b->size);
    LIL_CALLOC(tmp_a, a->size);
    LIL_CALLOC(tmp_b, b->size);
    
    // reduce a 
    if ((bezout_x_a == 0) and (bezout_y_a == 1)) {
        LIL_CPY_VAL(new_a, b);
    }
    if ((bezout_x_a == 1) and (bezout_y_a == 0)) {
        LIL_CPY_VAL(new_a, b);
    }
    if ((cmp_flag == 1) and (bezout_x_a > 0) and (bezout_y_a < 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_a, tmp_b); // tmp_a = a - b
        lil_short_mul(tmp_a, (uint64_t)(bezout_x_a)); // tmp_a = (a - b) * x_a
        lil_short_mul(tmp_b, (uint64_t)(-(bezout_x_a + bezout_y_a))); // tmp_b = b * (y_a - x_a)
        LIL_CPY_VAL(new_a, tmp_a);
        lil_sub(new_a, tmp_b);
    }
    if ((cmp_flag == 1) and (bezout_x_a < 0) and (bezout_y_a > 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_a, tmp_b); // tmp_a = a - b
        lil_short_mul(tmp_a, (uint64_t)(-bezout_x_a)); // tmp_a = (a - b) * x_a
        lil_short_mul(tmp_b, (uint64_t)(bezout_x_a + bezout_y_a)); // tmp_b = b * (y_a - x_a)
        LIL_CPY_VAL(new_a, tmp_b);
        lil_sub(new_a, tmp_a);
    }
    if ((cmp_flag == -1) and (bezout_x_a > 0) and (bezout_y_a < 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_b, tmp_a); // tmp_b = b - a
        lil_short_mul(tmp_b, (uint64_t)(bezout_x_a)); // tmp_a = (a - b) * x_a
        lil_short_mul(tmp_a, (uint64_t)(-(bezout_x_a + bezout_y_a))); // tmp_a = b * (y_a - x_a)
        LIL_CPY_VAL(new_a, tmp_a);
        lil_sub(new_a, tmp_b);
    }
    if ((cmp_flag == -1) and (bezout_x_a < 0) and (bezout_y_a > 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_b, tmp_a); // tmp_b = b - a
        lil_short_mul(tmp_b, (uint64_t)(-bezout_x_a)); // tmp_a = (a - b) * x_a
        lil_short_mul(tmp_a, (uint64_t)(bezout_x_a + bezout_y_a)); // tmp_a = b * (y_a - x_a)
        LIL_CPY_VAL(new_a, tmp_b);
        lil_sub(new_a, tmp_a);
    }
    // reduce b
    if ((cmp_flag == 1) and (bezout_x_b > 0) and (bezout_y_b < 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_a, tmp_b); // tmp_a = a - b
        lil_short_mul(tmp_a, (uint64_t)(bezout_x_b)); // tmp_a = (a - b) * x_b
        lil_short_mul(tmp_b, (uint64_t)(-(bezout_x_b + bezout_y_b))); // tmp_b = b * (y_b - x_b)
        LIL_CPY_VAL(new_b, tmp_a);
        lil_sub(new_b, tmp_b);
    }
    if ((cmp_flag == 1) and (bezout_x_b < 0) and (bezout_y_b > 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_a, tmp_b); // tmp_a = a - b
        lil_short_mul(tmp_a, (uint64_t)(-bezout_x_b)); // tmp_a = (a - b) * x_b
        lil_short_mul(tmp_b, (uint64_t)(bezout_x_b + bezout_y_b)); // tmp_b = b * (y_b - x_b)
        LIL_CPY_VAL(new_b, tmp_b);
        lil_sub(new_b, tmp_a);
    }
    if ((cmp_flag == -1) and (bezout_x_b > 0) and (bezout_y_b < 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_b, tmp_a); // tmp_b = b - a
        lil_short_mul(tmp_b, (uint64_t)(bezout_x_b)); // tmp_a = (a - b) * x_b
        lil_short_mul(tmp_a, (uint64_t)(-(bezout_x_b + bezout_y_b))); // tmp_a = b * (y_b - x_b)
        LIL_CPY_VAL(new_b, tmp_a);
        lil_sub(new_b, tmp_b);
    }
    if ((cmp_flag == -1) and (bezout_x_b < 0) and (bezout_y_b > 0)) {
        LIL_CPY_VAL(tmp_a, a);
        LIL_CPY_VAL(tmp_b, b);
        lil_sub(tmp_b, tmp_a); // tmp_b = b - a
        lil_short_mul(tmp_b, (uint64_t)(-bezout_x_b)); // tmp_a = (a - b) * x_b
        lil_short_mul(tmp_a, (uint64_t)(bezout_x_b + bezout_y_b)); // tmp_a = b * (y_b - x_b)
        LIL_CPY_VAL(new_b, tmp_b);
        lil_sub(new_b, tmp_a);
    }
    
    // prevent endless loop if an overflow occured 
    if (lil_cmp_val(a, new_a) == 1) {
        LIL_CPY_VAL(a, new_a);
    }
    if (lil_cmp_val(b, new_b) == 1) {
        LIL_CPY_VAL(b, new_b);
    }
    LIL_FREE(tmp_a);
    LIL_FREE(tmp_b);
    LIL_FREE(new_a);
    LIL_FREE(new_b);
    return;
}
