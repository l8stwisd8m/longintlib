#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_clz(uint64_t *dst, lil_t *src) {
    // number of leading zeroes, starting at the most significant bit position
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[src->size - i - 1]) {
            *dst = LIL_BASE * i + __builtin_clzll(src->val[src->size - i - 1]);
            return 0;
        }
    }
    *dst = LIL_BASE * src->size;
    
    return 0;
}
