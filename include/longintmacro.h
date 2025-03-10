#ifndef _LONG_INT_MACRO_
#define _LONG_INT_MACRO_ 

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "longintlib.h"

// check if source value is even
#define LIL_IS_EVEN(SRC) ((SRC->val[0] & 1) == 0)

// check if source value is odd
#define LIL_IS_ODD(SRC) ((SRC->val[0] & 1) == 1)

// most significant digit
#define LIL_MSD(SRC) (SRC->val[SRC->size - 1])

// least significant digit
#define LIL_LSD(SRC) (SRC->val[0])

// copy source value to destination value
#define LIL_CPY_VAL(DST, SRC) \
    assert(DST->size >= SRC->size); \
    for (size_t i = 0; i < SRC->size; i++) { \
        DST->val[i] = SRC->val[i]; \
    } 

// set source value null
#define LIL_SET_NULL(SRC) \
    for (size_t i = 0; i < SRC->size; SRC->val[i++] = 0);

// memory allocation for source
#define LIL_MALLOC(SRC, SIZE) \
    SRC = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC); \
    SRC->size = SIZE; \
    SRC->val = (uint64_t *)malloc((SIZE) * sizeof(uint64_t)); \
    assert(SRC->val);

// clean memory allocation for source
#define LIL_CALLOC(SRC, SIZE) \
    SRC = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC); \
    SRC->size = SIZE; \
    SRC->val = (uint64_t *)calloc(SIZE, sizeof(uint64_t)); \
    assert(SRC->val);

// free memory allocated for source
#define LIL_FREE(SRC) \
    free(SRC->val); \
    free(SRC);

// bitwise exclusive or
#define LIL_BIT_XOR(SRC_A, SRC_B) \
    assert(SRC_A->size >= SRC_B->size); \
    for (size_t i = 0; i < SRC_B->size; i++) { \
        SRC_A->val[i] = SRC_A->val[i] ^ SRC_B->val[i]; \
    }

// bitwise inversion
#define LIL_BIT_NOT(SRC) \
    for (size_t i = 0; i < SRC->size; i++) { \
        SRC->val[i] = ~SRC->val[i]; \
    }

// bitwise conjunction
#define LIL_BIT_AND(SRC_A, SRC_B) \
    assert(SRC_A->size >= SRC_B->size); \
    for (size_t i = 0; i < SRC_B->size; i++) { \
        SRC_A->val[i] = SRC_A->val[i] & SRC_B->val[i]; \
    }

// bitwise disjunction
#define LIL_BIT_OR(SRC_A, SRC_B) \
    assert(SRC_A->size >= SRC_B->size); \
    for (size_t i = 0; i < SRC_B->size; i++) { \
        SRC_A->val[i] = SRC_A->val[i] | SRC_B->val[i]; \
    }

#endif // _LONG_INT_MACRO_
