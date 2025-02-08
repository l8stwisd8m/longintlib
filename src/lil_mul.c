#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "../include/longintlib.h"

void lil_mul(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // multiplication of a and b
    lil_chunk_t _chunk;
    assert(dst->size >= (src_a->size + src_b->size));
    dst->sign = src_a->sign ^ src_b->sign;
    for (int i = 0; i < dst->size; dst->val[i++] = 0);

    // memory allocation for temporary structure
    lil_t *tmp_struct = (lil_t*)malloc(sizeof(lil_t));
    assert(tmp_struct);
    tmp_struct->size = src_a->size + src_b->size;
    tmp_struct->val = (uint64_t *)calloc(tmp_struct->size, sizeof(uint64_t));
    assert(tmp_struct->val);

    uint64_t tmp_val = 0;
    for (int i = 0; i < src_b->size; i++) {
        for (int j = 0; j < src_a->size; j++) {
            // multiplication
            _chunk.entire = (uint128_t)src_a->val[j] * src_b->val[i];
            tmp_val = tmp_struct->val[i+j];
            tmp_struct->val[i+j] += _chunk.halves[0];
            tmp_struct->val[i+j+1] += _chunk.halves[1];
            if (tmp_val > tmp_struct->val[i+j]) tmp_struct->val[i+j+1] += 1; // carry
        }
        lil_add(dst, tmp_struct);
        for (int i = 0; i < tmp_struct->size; tmp_struct->val[i++] = 0); // clean temporary values
    }
    
    free(tmp_struct->val);
    free(tmp_struct);
}
