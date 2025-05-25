#include <errno.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_mul(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // multiplication of a and b
    
    // default result
    LIL_SET_NULL(dst);
    if (lil_is_null(src_a) or lil_is_null(src_b)){
        dst->sign = LIL_PLUS;
        return 0;
    }
    dst->sign = src_a->sign ^ src_b->sign;
    
    #ifdef LIL_OPERAND_SIZES
    if (dst->size < (src_a->size + src_b->size)) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid size of destination value; multiplication can not be performed");
        exit(EXIT_FAILURE);
    }
    #endif /* LIL_OPERAND_SIZES */
    
    uint64_t tmp_val = 0;
    lil_chunk_t _chunk;
    long_int *tmp;
    LIL_CALLOC(tmp, src_a->size + src_b->size)
    
    // multiplication
    for (size_t i = 0; i < src_b->size; i++) {
        for (size_t j = 0; j < src_a->size; j++) {
            _chunk.entire = (uint128_t)src_a->val[j] * src_b->val[i];
            tmp_val = tmp->val[i+j];
            tmp->val[i+j] += _chunk.halves[0];
            tmp->val[i+j+1] += _chunk.halves[1];
            if (tmp_val > tmp->val[i+j]) tmp->val[i+j+1] += 1; // carry
        }
        lil_add(dst, tmp);
        LIL_SET_NULL(tmp);
    }
    
    LIL_FREE(tmp);
    return 0;
}
