#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"
#define COPRIME_TERMS_INVERSION // definition can be removed for certain purposes,
                                // for example in some factorization algorithms, 
                                // however it's highly recommended not to do it

int lil_inv(lil_t *dst, lil_t *src_a, lil_t *src_m) {
    // inverse element a modulo m
    
    // default result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    // correct a
    lil_val_mod(src_a, src_m);
    // correct modulo sign
    src_m->sign = LIL_PLUS;
    
    // exceptions
    if (lil_is_null(src_a)) {
        errno = ERR_INVALID_INPUT;
        perror("Zero is not coprime with the modulus; modulo inversion can not be performed");
        exit(EXIT_FAILURE); // invalid a value
    }
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; modulo inversion can not be performed");
        exit(EXIT_FAILURE); // invalid modulus
    }
    if ((src_a->size != dst->size) or (src_m->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; modulo inversion can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    long_int *tmp;
    LIL_MALLOC(tmp, src_a->size);
    #ifdef COPRIME_TERMS_INVERSION
    lil_gcd(tmp, src_a, src_m);
    if (tmp->val[0] != 1) {
        errno = ERR_INVALID_INPUT;
        perror("Given number is not coprime with the modulus; modulo inversion can not be performed");
        LIL_FREE(tmp);
        exit(EXIT_FAILURE); // invalid a value
    }
    #endif /* ifdef COPRIME_TERMS_INVERSION */
    
    // assuming a is not equal to zero at this point due to the coprime check
    // when coprime check is disabled, it's neccessary to assert it 
    
    #ifndef COPRIME_TERMS_INVERSION // it can not be used in most applications so it can be removed
    while (LIL_IS_EVEN(src_a) and LIL_IS_EVEN(src_m)) {
        lil_shr(src_a);
        lil_shr(src_m);
    }
    #endif /* ifndef COPRIME_TERMS_INVERSION */
    
    // set up variables
    long_int *y, *h;
    LIL_CALLOC(y, src_a->size);
    LIL_MALLOC(h, src_a->size);
    long_int *t1, *t2, *t3;
    LIL_CALLOC(t1, src_a->size);
    LIL_CALLOC(t2, src_a->size);
    LIL_MALLOC(t3, src_a->size);
    y->val[0] = 1; LIL_CPY_VAL(h, src_m);   // (x, y, h) = (0, 1, m)
    t1->val[0] = 1; LIL_CPY_VAL(t3, src_a); // (t1, t2, t3) = (1, 0, a)
    
    int flag = 0;
    long_int *res;
    LIL_MALLOC(res, src_a->size);
    y->sign = LIL_PLUS; h->sign = LIL_PLUS;
    t1->sign = LIL_PLUS; t2->sign = LIL_PLUS; t3->sign = LIL_PLUS;  
    while ((flag = lil_cmp_val(h, t3)) != 0) {
        if (LIL_IS_ODD(h)) {
            if (flag == 1) {
                // h > t3 => (x, y, h) -= (t1, t2, t3)
                LIL_CPY_VAL(tmp, t1); tmp->sign = !(t1->sign); lil_sum(res, dst, tmp); lil_cpy(dst, res);
                LIL_CPY_VAL(tmp, t2); tmp->sign = !(t2->sign); lil_sum(res, y, tmp); lil_cpy(y, res);
                LIL_CPY_VAL(tmp, t3); tmp->sign = !(t3->sign); lil_sum(res, h, tmp); lil_cpy(h, res);
            }
            if (flag == -1) {
                // h < t3 => (t1, t2, t3) -= (x, y, h)
                LIL_CPY_VAL(tmp, dst); tmp->sign = !(dst->sign); lil_sum(res, t1, tmp); lil_cpy(t1, res);
                LIL_CPY_VAL(tmp, y); tmp->sign = !(y->sign); lil_sum(res, t2, tmp); lil_cpy(t2, res);
                LIL_CPY_VAL(tmp, h); tmp->sign = !(h->sign); lil_sum(res, t3, tmp); lil_cpy(t3, res);
            }
        }
        else {
            if (LIL_IS_EVEN(dst) and LIL_IS_EVEN(y)) {
                // (x, y, h) /= 2
                lil_shr(dst); lil_shr(y); lil_shr(h);
            }
            else {
                // (x, y, h) = ((x+m)/2, (y-a)/2, h/2)
                LIL_CPY_VAL(tmp, src_m); tmp->sign = LIL_PLUS; lil_sum(res, dst, tmp); lil_cpy(dst, res);
                LIL_CPY_VAL(tmp, src_a); tmp->sign = LIL_MINUS; lil_sum(res, y, tmp); lil_cpy(y, res);
                lil_shr(dst); lil_shr(y); lil_shr(h);
            }
        }
    }
    
    // correct result
    if (dst->sign == LIL_MINUS) {
        // x < 0 => x += m
        lil_sum(tmp, dst, src_m); lil_cpy(dst, tmp);
    }
    if (lil_cmp_val(src_m, dst) != 1) {
        // x > m => x <- x % m
        LIL_CPY_VAL(tmp, dst);
        lil_mod(dst, tmp, src_m);
    }
    
    LIL_FREE(y);
    LIL_FREE(h);
    LIL_FREE(t1);
    LIL_FREE(t2);
    LIL_FREE(t3);
    LIL_FREE(res);
    LIL_FREE(tmp);
    return 0;
}
