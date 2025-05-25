#include <iso646.h>
#include <stddef.h>
#include "longintlib.h"
#include "longintmacro.h"
#include "longintprime.h"

static void prng_witness(lil_t *src_a, lil_t *src_m, size_t seed);

int lil_solovay_strassen(lil_t *src, size_t rounds) {
    // solovay-strassen primality test
    
    // exceptions
    if (rounds == 0) return LIL_TEST_FAIL;      // amount of rounds should be non-zero
    if (lil_is_one(src)) return LIL_TEST_FAIL;  // one can not be considered prime or composite
    if (lil_is_null(src)) return LIL_TEST_FAIL; // zero can not be considered prime or composite
    if ((lil_len(src) < 3) and LIL_IS_EVEN(src)) return LIL_PRIME; // two is prime
    if (LIL_IS_EVEN(src)) return LIL_COMPOSITE; // even numbers are composite
    
    int symbol = 0;
    long_int *witness, *tmp, *exp;
    LIL_MALLOC(exp, src->size);
    LIL_MALLOC(tmp, src->size);
    LIL_MALLOC(witness, src->size);
    
    // exp = (src - 1) / 2
    LIL_CPY_VAL(exp, src);
    lil_dec(exp);
    lil_shr(exp);
    
    size_t seed = 0;
    for (size_t i = 0; i < rounds; i++) {
        prng_witness(witness, src, seed++); // set pseudorandom in range [2, src - 1]
        while (lil_len(witness) < 1) prng_witness(witness, src, seed++); // make sure it's greater than 2
        
        symbol = lil_jacobi(witness, src);    // (witness | src)
        lil_pow_mod(tmp, witness, exp, src);  // witness ^ ((src - 1) / 2) mod src
        
        // (witness | src) = 0 => src is composite
        if (symbol == 0) {
            LIL_FREES(tmp, exp, witness);
            return LIL_COMPOSITE;
        }
        
        // (witness | src) is not congruent to witness ^ ((src - 1) / 2) mod src => src is composite
        
        if ((symbol == 1) and (not lil_is_one(tmp))) {
            LIL_FREES(tmp, exp, witness);
            return LIL_COMPOSITE;
        }
        
        lil_dec(src);
        if ((symbol == -1) and (lil_cmp_val(tmp, src) != 0)) {
            lil_inc(src);
            LIL_FREES(tmp, exp, witness);
            return LIL_COMPOSITE;
        }
        lil_inc(src);
    }
    
    LIL_FREES(tmp, exp, witness);
    return LIL_PRIME;
}

static void prng_witness(lil_t *src_a, lil_t *src_m, size_t seed) {
    // set pseudorandom value in range [0, m - 1]
    lil_prng(src_a, seed);
    lil_val_mod(src_a, src_m);
}
