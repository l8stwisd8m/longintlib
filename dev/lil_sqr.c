#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_sqr(lil_t *dst, lil_t *src) {
    // raising source to the power of two
    
    // default result
    LIL_SET_NULL(dst);
    dst->sign = LIL_PLUS;
    
    if (lil_is_null(src)){
        dst->sign = LIL_PLUS;
        return 0;
    }
    
    if (dst->size < (2 * src->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid size of destination value; raising to the power of two can not be performed");
        exit(EXIT_FAILURE);
    }
    
    lil_chunk_t _chunk;
    long_int *tmp;
    LIL_CALLOC(tmp, 2 * src->size)
    
    // precalculation
    for (size_t i = 0; i < src->size; i++) {
        _chunk.entire = (uint128_t)src->val[i] * src->val[i];
        dst->val[2 * i] = _chunk.halves[0];
        dst->val[2 * i + 1] = _chunk.halves[1];
    }
    
    // remaining values
    for (size_t i = 0; i < src->size - 1; i++) {
        for (size_t j = i + 1; j < src->size; j++) {
            _chunk.entire = (uint128_t)src->val[i] * src->val[j];
            tmp->val[i + j] = _chunk.halves[0];
            tmp->val[i + j + 1] = _chunk.halves[1];
            lil_shl(tmp); // tmp *= 2
            lil_add(dst, tmp);
            LIL_SET_NULL(tmp);
        }
    }
    
    LIL_FREE(tmp);
    return 0;
}
