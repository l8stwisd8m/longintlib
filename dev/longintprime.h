#ifndef _LONG_INT_PRIME_
#define _LONG_INT_PRIME_

// longintlib v0.1
// https://github.com/l8stwisd8m/longintlib

#include <stddef.h>
#include <stdint.h>
#include "longintlib.h"

// FUNDAMENTAL THEOREM OF ARITHMETIC COMPOSITE TYPE
// lists of short & long prime factors of number

typedef struct {
    uint64_t *sf; // short factors
    size_t *exp;  // correspondigs exponents
    lil_t **lf;   // long integer factors
} lil_fta_t;

// PRIMALITY TESTS RESULTS AND ERROR HANDLING

enum lil_primality {
    LIL_COMPOSITE,  // authentic composite
    LIL_PRIME,      // strong probable prime
    LIL_TEST_FAIL   // invalid parameter was entered
};

// UTILITY FUNCTIONS
// FACTORIZATION

// something will be uploaded soon ^_^

// PRIMALITY TESTS

int lil_primality(lil_t *src); // fast test based on trial division & miller-rabin test
int lil_miller_rabin(lil_t *src, size_t rounds); // miller-rabin primality test
int lil_solovay_strassen(lil_t *src, size_t rounds); // solovay-strassen primality test

#endif
