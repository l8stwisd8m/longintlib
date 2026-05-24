#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_ctz(uint64_t *dst, lil_t *src) {
    // number of trailing zeroes, starting at the least significant bit position
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[i]) {
            *dst = LIL_BASE * i + __builtin_ctzll(src->val[i]);
            return 0;
        }
    }
    *dst = LIL_BASE * src->size;
    
    return 0;
}
