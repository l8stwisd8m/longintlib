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

// something will be uploaded soon ^^

// PRIMALITY TESTS

int lil_primality(lil_t *src); // fast test based on trial division & miller-rabin test
int lil_miller_rabin(lil_t *src, size_t rounds); // miller-rabin primality test
int lil_solovay_strassen(lil_t *src, size_t rounds); // solovay-strassen primality test

// UTILITY CONSTANTS

#define LIL_MAGIC_NUMBER 4849845ULL

// FIELD SIZES

#define LIL_PRIME_FIELD_SIZE_192 3U
#define LIL_PRIME_FIELD_SIZE_224 4U
#define LIL_PRIME_FIELD_SIZE_256 4U
#define LIL_PRIME_FIELD_SIZE_384 6U
#define LIL_PRIME_FIELD_SIZE_521 9U
#define LIL_PRIME_FIELD_SIZE_255 4U
#define LIL_PRIME_FIELD_SIZE_448 7U

// NIST SP 800-168 
// https://doi.org/10.6028/NIST.SP.800-186

#define LIL_NIST_CURVE_P192 {0xffffffffffffffff, 0xfffffffffffffffe, 0xffffffffffffffff};
#define LIL_NIST_CURVE_P224 {0x1, 0xffffffff00000000, 0xffffffffffffffff, 0x00000000ffffffff};
#define LIL_NIST_CURVE_P256 {0xffffffffffffffff, 0x00000000ffffffff, 0x0, 0xffffffff00000001};
#define LIL_NIST_CURVE_P384 {0x00000000ffffffff, 0xffffffff00000000, 0xfffffffffffffffe, \
                             0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};
#define LIL_NIST_CURVE_P521 {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, \
                             0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, \
                             0xffffffffffffffff, 0xffffffffffffffff, 0x1ff};
#define LIL_NIST_CURVE_25519 {0xffffffffffffffed, 0xffffffffffffffff, 0xffffffffffffffff, 0x7fffffffffffffff};
#define LIL_NIST_CURVE_448 {0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff, 0xfffffffeffffffff, \
                            0xffffffffffffffff, 0xffffffffffffffff, 0xffffffffffffffff};

// MERSENNE PRIMES

#define LIL_MERSENNE_P107 {0xffffffffffffffff, 0x000007ffffffffff};
#define LIL_MERSENNE_P127 {0xffffffffffffffff, 0x7fffffffffffffff};

// OTHER PRIMES

#define LIL_RSA_PUBLIC_EXP 65537

#endif
