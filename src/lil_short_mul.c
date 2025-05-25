#include <stddef.h>
#include <stdint.h>
#include <iso646.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"

int lil_short_mul(long_int *src_a, uint64_t src_b) {
    // multiplication of long a and short b
    
    int flag = 0;
    
    if ((src_b == 0) or (lil_is_null(src_a))) {
        LIL_SET_NULL(src_a);
        src_a->sign = LIL_PLUS;
        return flag; // a * 0 = 0
    }
    
    uint64_t multiplier = src_a->val[0];
    lil_chunk_t _chunk;
    
    // multiplication
    src_a->val[0] = 0; // replacing values of a
    for (size_t i = 1; i < src_a->size; i++) {
        _chunk.entire = (uint128_t)multiplier * src_b;
        multiplier = src_a->val[i];
        src_a->val[i] = _chunk.halves[1];
        if (src_a->val[i - 1] + _chunk.halves[0] < src_a->val[i - 1]) src_a->val[i] += 1; // overflow check
        src_a->val[i - 1] += _chunk.halves[0];
    }
    // remaining value multiplication + overflow cut
    _chunk.entire = (uint128_t)multiplier * src_b;
    flag = (_chunk.halves[1]) ? LIL_OVERFLOW : 0;
    if (src_a->val[src_a->size - 1] + _chunk.halves[0] < src_a->val[src_a->size - 1]) flag = LIL_OVERFLOW;
    src_a->val[src_a->size - 1] += _chunk.halves[0]; 
    
    return flag;
}
