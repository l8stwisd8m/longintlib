#ifndef _LONG_INT_MACRO_
#define _LONG_INT_MACRO_ 

#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <assert.h>
#include "longintlib.h"

#define LIL_CPY_VAL(DST, SRC) \
    size_t LIM = (DST->size < SRC->size) ? DST->size : SRC->size; \
    for (int i = 0; i < LIM; i++) { \
        DST->val[i] = SRC->val[i]; \
    }

#define LIL_SET_NULL(SRC) \
    for (int i = 0; i < SRC->size; SRC->val[i++] = 0);

#define LIL_MALLOC(SRC_PTR, SIZE) \
    SRC_PTR = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC_PTR); \
    SRC_PTR->size = SIZE; \
    SRC_PTR->val = (uint64_t *)malloc((SIZE) * sizeof(uint64_t)); \
    assert(SRC_PTR->val);

#define LIL_CALLOC(SRC_PTR, SIZE) \
    SRC_PTR = (long_int *)malloc(sizeof(long_int)); \
    assert(SRC_PTR); \
    SRC_PTR->size = SIZE; \
    SRC_PTR->val = (uint64_t *)calloc(SIZE, sizeof(uint64_t)); \
    assert(SRC_PTR->val);

#define LIL_FREE(SRC_PTR) \
    free(SRC_PTR->val); \
    free(SRC_PTR);

#endif // _LONG_INT_MACRO_
