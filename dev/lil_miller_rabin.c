#include <iso646.h>
#include <stddef.h>
#include "../include/longintlib.h"
#include "../include/longintmacro.h"
#include "../include/longintprime.h"

static void prng_witness(lil_t *src_a, lil_t *src_m, size_t seed);

int lil_miller_rabin(lil_t *src, size_t rounds) {
    // miller-rabin primality test
    
    // exceptions
    if (rounds == 0) return LIL_TEST_FAIL;      // amount of rounds should be non-zero
    if (lil_is_one(src)) return LIL_TEST_FAIL;  // one can not be considered prime or composite
    if (lil_is_null(src)) return LIL_TEST_FAIL; // zero can not be considered prime or composite
    if ((lil_len(src) < 4) and \
        (LIL_LSD(src) == 2 or LIL_LSD(src) == 3 or LIL_LSD(src) == 5)) return LIL_PRIME;
    if (LIL_IS_EVEN(src)) return LIL_COMPOSITE; // even numbers are composite
    
    size_t shift = 0;
    long_int *residue;
    LIL_MALLOC(residue, src->size);
    LIL_CPY_VAL(residue, src);
    lil_dec(residue);
    
    // factoring out factors of 2
    while (LIL_IS_EVEN(residue)) {
        lil_shr(residue);
        shift += 1;
    }
    
    long_int *witness, *tmp, *sqr;
    LIL_MALLOC(sqr, src->size);
    LIL_MALLOC(tmp, src->size);
    LIL_MALLOC(witness, src->size);
    
    size_t seed = 0;
    for (size_t i = 0; i < rounds; i++) {
        prng_witness(witness, src, seed++); // set pseudorandom in range (2, src - 1)
        while (lil_len(witness) < 2) prng_witness(witness, src, seed++); // make sure it's greater than 3
        
        lil_pow_mod(tmp, witness, residue, src);
        
        for (size_t j = 0; j < shift; j++) {
            lil_mul_mod(sqr, tmp, tmp, src);
            if (lil_is_one(sqr) and (not lil_is_one(tmp))) {
                lil_dec(src);
                if (lil_cmp_val(tmp, src) != 0) {
                    lil_inc(src);
                    LIL_FREES(sqr, tmp, residue, witness);
                    return LIL_COMPOSITE;
                }
                lil_inc(src);
            }
            LIL_CPY_VAL(tmp, sqr);
        }
        
        if (not lil_is_one(sqr)) {
            LIL_FREES(sqr, tmp, residue, witness);
            return LIL_COMPOSITE;
        }
    }
    
    LIL_FREES(sqr, tmp, residue, witness);
    return LIL_PRIME;
}

static void prng_witness(lil_t *src_a, lil_t *src_m, size_t seed) {
    // set pseudorandom value in range [0, m - 1)
    lil_prng(src_a, seed);
    lil_val_mod(src_a, src_m);
    lil_dec(src_a);
}
