#include <stddef.h>
#include "longintlib.h"
#include "longintmacro.h"
#include "longintprime.h"

#define LT_SIZE 30
#define LT_LIMIT 9
static const uint64_t lt_primes[LT_SIZE] = {3, 5, 7, 11, 13, 17, 19,
                                            23, 29, 31, 37, 41, 43, 
                                            47, 53, 59, 61, 67, 71, 
                                            73, 79, 83, 89, 97, 101, 
                                            103, 107, 109, 113, 127};
#define MAGIC_NUMBER 3234846615ULL // another magic constant yeah >.<
static uint64_t short_gcd(uint64_t a, uint64_t b);

int lil_primality(lil_t *src) {
    // fast test based on trial division & miller-rabin test
    
    // exceptions
    if (lil_is_one(src)) return LIL_TEST_FAIL;  // one can not be considered prime or composite
    if (lil_is_null(src)) return LIL_TEST_FAIL; // zero can not be considered prime or composite
    
    // case when length does not exceed eight bits
    if (lil_len(src) < 8) {
        if (LIL_LSD(src) == 2) return LIL_PRIME;
        for (size_t i = 0; i < LT_SIZE; i++) {
            if (LIL_LSD(src) == lt_primes[i]) return LIL_PRIME;
        }
        return LIL_COMPOSITE;
    }
    
    if (LIL_IS_EVEN(src)) return LIL_COMPOSITE; // even numbers are composite
    
    // trial division
    uint64_t redused_val = 0;
    lil_short_mod(&redused_val, src, MAGIC_NUMBER);
    redused_val = short_gcd(redused_val, MAGIC_NUMBER);
    for (size_t i = 0; i < LT_LIMIT; i++) {
        if (redused_val % lt_primes[i] == 0) return LIL_COMPOSITE;
    }
    
    // miller-rabin test
    size_t rounds = 4 * src->size;
    int flag = lil_miller_rabin(src, rounds);
    
    return flag;
}

static uint64_t short_gcd(uint64_t a, uint64_t b) {
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
