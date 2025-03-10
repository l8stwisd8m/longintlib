#ifndef _LONG_INT_LIB_
#define _LONG_INT_LIB_

#include <stdint.h>
#include <stddef.h>

#ifndef uint128_t
#define uint128_t __uint128_t
#endif // uint128_t

typedef struct {
    enum {PLUS, MINUS} sign;
    uint64_t *val;
    size_t size;
} lil_t;

typedef union {
    uint128_t entire;
    uint64_t halves[2];
} lil_chunk_t;

#undef PLUS
#undef MINUS

#define long_int lil_t

enum lil_perror {
    ERR_SIZE_MISMATCH = -1,
    ERR_ZERO_DIVISION = -2,
    ERR_INVALID_INPUT = -3
};

// BASIC FUNCTIONS
int lil_rev(lil_t *src); // reverse source values order
int lil_cpy(lil_t *dst, lil_t *src); // copy source structure to destination
uint64_t lil_len(lil_t *src); // return bit length of source
int lil_cmp(lil_t *src_a, lil_t *src_b); // return 0 if a = b, -1 if a < b, 1 if a > b
int lil_cmp_len(lil_t *src_a, lil_t *src_b); // return 0 if length(a) = length(b), -1 if length(a) < length(b), 1 if length(a) > length(b)
int lil_cmp_val(lil_t *src_a, lil_t *src_b); // return 0 if abs(a) = abs(b), -1 if abs(a) < abs(b), 1 if abs(a) > abs(b)
int lil_is_null(lil_t *src); // return 1 if source is empty, 0 otherwise
int lil_is_even(lil_t *src); // return 1 if source is even, 0 otherwise
int lil_is_odd(lil_t *src);  // return 1 if source is odd, 0 otherwise

// PRINT & SCAN FUNCTIONS
int lil_print_bin(lil_t *src); // print binary representation of source
int lil_print_dec(lil_t *src); // print decimal representation of source
int lil_print_hex(lil_t *src); // print hexadecimal representation of source
int lil_scan_bin(lil_t *src); // scan binary representation of source
int lil_scan_dec(lil_t *src); // scan decimal representation of source
int lil_scan_hex(lil_t *src); // scan hexadecimal representation of source

// BASIC MATH FUNCTIONS
int lil_add(lil_t *src_a, lil_t *src_b); // addition of a and b
int lil_sub(lil_t *src_a, lil_t *src_b); // subtracting b from a
int lil_sum(lil_t *dst, lil_t *src_a, lil_t *src_b); // arithmetic sum of a and b
int lil_mul(lil_t *dst, lil_t *src_a, lil_t *src_b); // multiplication of a and b
int lil_div(lil_t *dst, lil_t *src_a, lil_t *src_b); // floor from division of a by b
int lil_mod(lil_t *dst, lil_t *src_a, lil_t *src_b); // remainder after division of a by b
int lil_gcd(lil_t *dst, lil_t *src_a, lil_t *src_b); // greatest commond divisor of a and b

// UNARY MATH FUNCTIONS
int lil_inc(lil_t *src); // increment source value
int lil_dec(lil_t *src); // decrement source value

// SHIFTS
int lil_shl(lil_t *src); // left shift by one bit
int lil_shr(lil_t *src); // right shift by one bit
int lil_shlw(lil_t *src); // left shift by word size
int lil_shrw(lil_t *src); // right shift by word size
int lil_shln(lil_t *src, uint64_t n); // left shift by n bits
int lil_shrn(lil_t *src, uint64_t n); // right shift by n bits

// MODULAR ARITHMETIC FUNCTIONS
int lil_mul_mod(lil_t *dst, lil_t *src_a, lil_t *src_b, lil_t *src_m); // multiplication of a and b modulo m
int lil_pow_mod(lil_t *dst, lil_t *src_a, lil_t *src_n, lil_t *src_m); // raising a to the power n modulo m
int lil_inv(lil_t *dst, lil_t *src_a, lil_t *src_m); // inverse element a modulo m

// SHORT OPERATIONS
int lil_short_add(lil_t *src_a, uint64_t src_b); // add short abs(b) to abs(values) of long a
int lil_short_sub(lil_t *src_a, uint64_t src_b); // subtract short abs(b) from abs(values) of long a
int lil_short_mul(lil_t *src_a, uint64_t src_b); // multiply abs(values) of long a by short abs(b)
int lil_short_div(lil_t *dst, lil_t *src_a, uint64_t src_b); // return floor from division of long a by short b
int lil_short_mod(uint64_t *dst, lil_t *src_a, uint64_t val_b); // short remainder after division of long a by short b
int lil_short_pow_mod(lil_t *src_a, uint64_t n, lil_t *src_m); // raising a to the power n modulo m

// CUSTOM FUNCTIONS
int lil_fast_gcd(lil_t *dst, lil_t *src_a, lil_t *src_b); // greatest commond divisor of a and b

#endif // _LONG_INT_LIB_
