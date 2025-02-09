#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void lil_short_mul(long_int *src_a, uint64_t src_b) {
    // multiplication of long a and short b
    
    if (src_b == 0) {
        for (int i = 0; i < src_a->size; src_a->val[i++] = 0);
        src_a->sign = LIL_PLUS;
        return;
    }
    
    // multiplication
    uint64_t multiplier = src_a->val[0];
    lil_chunk_t _chunk;
    src_a->val[0] = 0; // replacing values of a
    for (int i = 1; i < src_a->size; i++) {
        _chunk.entire = (uint128_t)multiplier * src_b;
        multiplier = src_a->val[i];
        src_a->val[i] = _chunk.halves[1];
        if (src_a->val[i-1] + _chunk.halves[0] < src_a->val[i-1]) src_a->val[i] += 1; // overflow check
        src_a->val[i-1] += _chunk.halves[0];
    }
    src_a->val[src_a->size - 1] += multiplier * src_b; // multiply remaining value + cut overflow
}
