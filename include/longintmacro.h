#ifndef _LONG_INT_MACRO_
#define _LONG_INT_MACRO_ 

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "longintlib.h"

// copy source value to destination value
#define LIL_CPY_VAL(DST, SRC) \
    size_t LIM = (DST->size < SRC->size) ? DST->size : SRC->size; \
    for (int i = 0; i < LIM; i++) { \
        DST->val[i] = SRC->val[i]; \
    }

// set source value null
#define LIL_SET_NULL(SRC) \
    for (int i = 0; i < SRC->size; SRC->val[i++] = 0);

// memory allocation for source
#define LIL_MALLOC(SRC_PTR, SIZE) \
    SRC_PTR = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC_PTR); \
    SRC_PTR->size = SIZE; \
    SRC_PTR->val = (uint64_t *)malloc((SIZE) * sizeof(uint64_t)); \
    assert(SRC_PTR->val);

// clean memory allocation for source
#define LIL_CALLOC(SRC_PTR, SIZE) \
    SRC_PTR = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC_PTR); \
    SRC_PTR->size = SIZE; \
    SRC_PTR->val = (uint64_t *)calloc(SIZE, sizeof(uint64_t)); \
    assert(SRC_PTR->val);

// free memory allocated for source
#define LIL_FREE(SRC_PTR) \
    free(SRC_PTR->val); \
    free(SRC_PTR);

// bitwise exclusive or
#define LIL_XOR(SRC_A, SRC_B) \
    size_t LIM = (SRC_A->size < SRC_B->size) ? SRC_A->size : SRC_B->size; \
    for (int i = 0; i < LIM; i++) { \
        SRC_A->val[i] = SRC_A->val[i] ^ SRC_B->val[i]; \
    }

// bitwise conjunction
#define LIL_AND(SRC_A, SRC_B) \
    size_t LIM = (SRC_A->size < SRC_B->size) ? SRC_A->size : SRC_B->size; \
    for (int i = 0; i < LIM; i++) { \
        SRC_A->val[i] = SRC_A->val[i] & SRC_B->val[i]; \
    }

// bitwise disjunction
#define LIL_OR(SRC_A, SRC_B) \
    size_t LIM = (SRC_A->size < SRC_B->size) ? SRC_A->size : SRC_B->size; \
    for (int i = 0; i < LIM; i++) { \
        SRC_A->val[i] = SRC_A->val[i] | SRC_B->val[i]; \
    }

#endif // _LONG_INT_MACRO_
