#include <stdint.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintmacro.h"

void lil_mul(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // multiplication of a and b
    lil_chunk_t _chunk;
    assert(dst->size >= (src_a->size + src_b->size));
    dst->sign = src_a->sign ^ src_b->sign;
    for (int i = 0; i < dst->size; dst->val[i++] = 0);
    
    // temporary structure
    long_int *tmp;
    LIL_CALLOC(tmp, src_a->size + src_b->size)
    
    // multiplication
    uint64_t tmp_val = 0;
    for (int i = 0; i < src_b->size; i++) {
        for (int j = 0; j < src_a->size; j++) {
            _chunk.entire = (uint128_t)src_a->val[j] * src_b->val[i];
            tmp_val = tmp->val[i+j];
            tmp->val[i+j] += _chunk.halves[0];
            tmp->val[i+j+1] += _chunk.halves[1];
            if (tmp_val > tmp->val[i+j]) tmp->val[i+j+1] += 1; // carry
        }
        lil_add(dst, tmp);
        for (int i = 0; i < tmp->size; tmp->val[i++] = 0); // clean temporary values
    }
    
    LIL_FREE(tmp);
}
