#ifndef _LONG_INT_CURVE_
#define _LONG_INT_CURVE_

// longintlib v0.1
// https://github.com/l8stwisd8m/longintlib

#include <stdio.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

// ELLIPTIC CURVE TYPE
// weierstrass short form
// y ^ 2 = x ^ 3 * a * x ^ 2 + b mod m (modulus supposed to be prime)

typedef struct {
    lil_t *a; // coefficient a
    lil_t *b; // coefficient b
    lil_t *m; // modulus
} lil_ec_t;

// ELLIPTIC CURVE POINT
// due to the form chosen, a representation of point is pair of coordinates

typedef struct {
    lil_t *x; // abscissa
    lil_t *y; // ordinate
} lil_point_t;

// ERROR HANDLING & VALIDATION

enum lil_ec_validation {
    LIL_EC_INVALID, // for curves and points
    LIL_EC_VALID,   // for curves and points
    LIL_EC_SPECIAL  // for points only to verify (0, 0) point
};

// UTILITY FUNCTIONS

int lil_ec_cpy(lil_point_t *dst, lil_point_t *src); // copy source point to destination
int lil_ec_cmp(lil_ec_t *curve, lil_point_t *src_p, lil_point_t *src_q); // return 1 if point p is equal to q, 0 otherwise

// VALIDATION

int lil_ec_valid_curve(lil_ec_t *curve); // check if curve is non-singular
int lil_ec_valid_point(lil_ec_t *curve, lil_point_t *src); // check if source point belongs to curve

// ARITHMETIC FUNCTIONS

int lil_ec_add(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, lil_point_t *src_q); // addition of points p and q
int lil_ec_sub(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, lil_point_t *src_q); // subtraction of points p and q
int lil_ec_mul(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, lil_t *src_n); // point p multiplied by long int n
int lil_ec_short_mul(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, uint64_t src_n); // point p multiplied by short int n

// FUNCTIONS FOR CRYPTOGRAPHIC APPLICATIONS & OTHER PURPOSES

int lil_ec_evaluate(lil_ec_t *curve, lil_t *dst, lil_t *src); // long integer source evaluation
int lil_ec_embed(lil_ec_t *curve, lil_point_t *dst, lil_t *src); // long integer source embedding into point
int lil_ec_point_order(lil_ec_t *curve, lil_t *dst, lil_point_t *src); // order of source point
int lil_ec_curve_order(lil_ec_t *curve, lil_t *dst); // order of a curve
int lil_ec_curve_trace(lil_ec_t *curve, lil_t *dst); // frobenius trace of a curve
int lil_ec_prng_point(lil_ec_t *curve, lil_point_t *dst, size_t seed); // pseudorandom point generation

// MACROS

// value stored in abscissa 
#define LIL_EC_X_VAl(SRC) \
    (SRC->x->val)

// value stored in ordinate
#define LIL_EC_Y_VAl(SRC) \
    (SRC->y->val)

// sign of abscissa 
#define LIL_EC_X_SIGN(SRC) \
    (SRC->x->sign)

// sign of ordinate
#define LIL_EC_Y_SIGN(SRC) \
    (SRC->y->sign)

// size of abscissa 
#define LIL_EC_X_SIZE(SRC) \
    (SRC->x->size)

// size of ordinate
#define LIL_EC_Y_SIZE(SRC) \
    (SRC->y->size)

// set both coordinates null
#define LIL_EC_SET_NULL(SRC) \
    LIL_SET_NULL(SRC->x); \
    LIL_SET_NULL(SRC->y); \
    LIL_EC_X_SIGN(SRC) = LIL_PLUS; \
    LIL_EC_Y_SIGN(SRC) = LIL_PLUS;

// check is both point coordinates are equal to zero
#define LIL_EC_SPECIAL_POINT(SRC) \
    (lil_is_null(SRC->x) and lil_is_null(SRC->y))

// print debug info (binary)
#define LIL_EC_DEBUG_BIN(SRC) \
    printf("%s->x:\t", #SRC); \
    lil_print_bin((SRC)->x);  \
    printf("%s->y:\t", #SRC); \
    lil_print_bin((SRC)->y);

// print debug info (decimal)
#define LIL_EC_DEBUG_DEC(SRC) \
    printf("%s->x:\t", #SRC); \
    lil_print_dec((SRC)->x);  \
    printf("%s->y:\t", #SRC); \
    lil_print_dec((SRC)->y);

// print debug info (hexadecimal)
#define LIL_EC_DEBUG_HEX(SRC) \
    printf("%s->x:\t", #SRC); \
    lil_print_hex((SRC)->x);  \
    printf("%s->y:\t", #SRC); \
    lil_print_hex((SRC)->y);

// memory allocation for point
#define LIL_EC_MALLOC(SRC, SIZE) \
    SRC = (lil_point_t *)malloc(sizeof(lil_point_t)); \
    assert(SRC); \
    SRC->x = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC->x); \
    SRC->x->size = SIZE; \
    SRC->x->sign = LIL_PLUS; \
    SRC->x->val = (uint64_t *)malloc((SIZE) * sizeof(uint64_t)); \
    assert(SRC->x->val); \
    SRC->y = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC->y); \
    SRC->y->size = SIZE; \
    SRC->y->sign = LIL_PLUS; \
    SRC->y->val = (uint64_t *)malloc((SIZE) * sizeof(uint64_t)); \
    assert(SRC->y->val);

// clean memory allocation for point
#define LIL_EC_CALLOC(SRC, SIZE) \
    SRC = (lil_point_t *)malloc(sizeof(lil_point_t)); \
    assert(SRC); \
    SRC->x = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC->x); \
    SRC->x->size = SIZE; \
    SRC->x->sign = LIL_PLUS; \
    SRC->x->val = (uint64_t *)calloc((SIZE), sizeof(uint64_t)); \
    assert(SRC->x->val); \
    SRC->y = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC->y); \
    SRC->y->size = SIZE; \
    SRC->y->sign = LIL_PLUS; \
    SRC->y->val = (uint64_t *)calloc((SIZE), sizeof(uint64_t)); \
    assert(SRC->y->val);

// free memory allocated for source
#define LIL_EC_FREE(SRC) \
    free(SRC->x->val); \
    free(SRC->y->val); \
    free(SRC->x); \
    free(SRC->y); \
    free(SRC);

// CONSTANTS

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

#endif // _LONG_INT_CURVE_
