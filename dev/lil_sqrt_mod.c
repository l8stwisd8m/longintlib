#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

static void prng_quadratic_nonresidue(lil_t *src_a, lil_t *src_m);
static void update_exp(uint64_t *exp, lil_t *tmp_e, lil_t *tmp_t, lil_t *src_a, lil_t *src_m);

int lil_sqrt_mod(lil_t *dst, lil_t *src_a, lil_t *src_m) {
    // modulo square root of a modulo m
    
    // exceptions
    #ifdef LIL_DIVISION_BY_ZERO
    if (lil_is_null(src_m)) {
        errno = ERR_ZERO_DIVISION;
        perror("Division by zero is not a valid operation; square root calculation can not be performed");
        exit(EXIT_FAILURE); // invalid m value
    }
    #endif /* LIL_DIVISION_BY_ZERO */
    
    #ifdef LIL_OPERAND_SIZES
    if ((src_a->size != dst->size) or (src_m->size != dst->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid terms sizes; square root calculation can not be performed");
        exit(EXIT_FAILURE); // operand sizes mismatch error
    }
    #endif /* LIL_OPERAND_SIZES */
    
    // correct input
    lil_val_mod(src_a, src_m);
    
    // default result
    LIL_SET_NULL(dst);
    dst->sign = LIL_PLUS;
    
    // a = 0 => sqrt(a) mod m = 0
    if (lil_is_null(src_a)) {
        return LIL_NO_ANSWER; 
    }
    
    long_int *tmp_m;
    LIL_MALLOC(tmp_m, src_m->size);
    
    // one more exception (make sure a and m are relatively prime)
    lil_gcd(tmp_m, src_a, src_m);
    if (not lil_is_one(tmp_m)) {
        errno = ERR_INVALID_INPUT;
        perror("Given number is not relatively prime to the modulus; square root calculation can not be performed");
        LIL_FREE(tmp_m);
        exit(EXIT_FAILURE); // invalid values
    }
    
    // (a | p) != 1 => solution doesn't exist
    if (lil_jacobi(src_a, src_m) != 1) {
        LIL_FREE(tmp_m);
        return LIL_NO_ANSWER;
    }
    
    LIL_CPY_VAL(tmp_m, src_m); tmp_m->sign = LIL_PLUS;
    
    // check "easy case"
    if ((LIL_LSD(tmp_m) & 3) == 3) {
        lil_inc(tmp_m); // m <- m + 1
        lil_shr(tmp_m); lil_shr(tmp_m); // m <- m >> 2
        lil_pow_mod(dst, src_a, tmp_m, src_m);
        LIL_FREE(tmp_m);
        return 0; // result = a ^ ((m + 1) / 4) mod m
    }
    
    // pseudorandom quadratic nonresidue
    long_int *tmp_n;
    LIL_MALLOC(tmp_n, src_m->size);
    prng_quadratic_nonresidue(tmp_n, src_m);
    
    // shift decremented m while it is even
    uint64_t trailing_zeroes = 0;
    LIL_LSD(tmp_m) -= 1;
    assert(LIL_IS_EVEN(tmp_m));
    while (LIL_IS_EVEN(tmp_m)) {
        lil_shr(tmp_m);
        trailing_zeroes += 1;
    }
    
    // set up new variables
    long_int *tmp_x, *tmp_y, *tmp_b;
    LIL_MALLOC(tmp_x, src_m->size);
    LIL_MALLOC(tmp_y, src_m->size);
    LIL_MALLOC(tmp_b, src_m->size);
    
    // y <- (n ^ shifted(m)) mod m
    lil_pow_mod(tmp_y, tmp_n, tmp_m, src_m); 
    
    // x <- (a ^ ((shifted(m) - 1) / 2)) mod m
    assert(LIL_IS_ODD(tmp_m));
    LIL_LSD(tmp_m) -= 1;  // shifted(m) <- shifted(m) - 1
    lil_shr(tmp_m);       // shifted(m) <- shifted(m) / 2
    lil_pow_mod(tmp_x, src_a, tmp_m, src_m); 
    
    // x is result (dst variable), but some transformation may be required
    
    // dst <- a * x mod m
    lil_mul_mod(dst, src_a, tmp_x, src_m);
    
    // b <- a * x * x mod m
    lil_mul_mod(tmp_b, dst, tmp_x, src_m);
    
    // b = 1 => result is already stored in dst
    if (lil_is_one(tmp_b)) {
        LIL_FREES(tmp_m, tmp_n, tmp_x, tmp_y, tmp_b);
        return 0;
    }
    
    // correct x
    lil_inc(tmp_m); // shifted(m) <- shifted(m) + 1
    lil_pow_mod(tmp_x, src_a, tmp_m, src_m); 
    
    // renaming temporary variables
    long_int *tmp_t = tmp_n; // for temporary values
    long_int *tmp_e = tmp_m; // for exponents
    // exponents
    uint64_t exp_r = trailing_zeroes; 
    uint64_t exp_m = 0;
    while(not lil_is_one(tmp_b)) {
        update_exp(&exp_m, tmp_e, tmp_t, tmp_b, src_m);
        assert(exp_m != 0);
        assert(exp_m < exp_r);
        LIL_SET_NULL(tmp_e);                // tmp_e = 0
        LIL_LSD(tmp_e) = 1;                 // tmp_e <- 1
        lil_shln(tmp_e, exp_r - exp_m - 1); // tmp_e <- 2 ^ (r - m - 1)
        lil_pow_mod(tmp_t, tmp_y, tmp_e, src_m);  // t <- y ^ e mod m
        lil_mul_mod(tmp_y, tmp_t, tmp_t, src_m);  // y <- t ^ 2 mod m
        exp_r = exp_m;                            // r <- m
        lil_mul_mod(dst, tmp_x, tmp_t, src_m);    // x <- x * t mod m
        lil_mul_mod(tmp_x, tmp_b, tmp_y, src_m);  // b <- b * y mod m
        LIL_CPY_VAL(tmp_b, tmp_x);
        LIL_CPY_VAL(tmp_x, dst);
    }
    
    LIL_FREES(tmp_x, tmp_y, tmp_b, tmp_t, tmp_e);
    return 0;
}

static void prng_quadratic_nonresidue(lil_t *src_a, lil_t *src_m) {
    // set a to a pseudorandom number such that (a | m) = -1
    
    size_t seed = 0;
    do {
        lil_prng(src_a, seed++);
        lil_val_mod(src_a, src_m);
    } while (lil_jacobi(src_a, src_m) != -1);
}

static void update_exp(uint64_t *exp, lil_t *tmp_e, lil_t *tmp_t, lil_t *src_a, lil_t *src_m) {
    // find such exponent that (a ^ (2 ^ exp)) = 1 mod m
    // tmp_t is used temporary for storing exponentiation result, tmp_e for exponent
    
    *exp = 0;
    LIL_SET_NULL(tmp_e);  // tmp_e <- 0
    LIL_LSD(tmp_e) = 1;   // tmp_e <- 1
    do {
        if (*exp) lil_shl(tmp_e); // tmp_e <- 2 ^ exp
        lil_pow_mod(tmp_t, src_a, tmp_e, src_m);
        if (lil_is_one(tmp_t)) {
            return; // (a ^ (2 ^ exp)) = 1 mod m
        }
        *exp += 1;  // update exponent
    } while (*exp != 0); // break the cycle if an overflow occured (exponent wasn't found)
}
