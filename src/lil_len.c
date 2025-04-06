#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

uint64_t lil_len(lil_t *src) {
    // return bit length of source
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[src->size - i - 1]) {
            return LIL_BASE * (src->size - i) - \
            __builtin_clzll(src->val[src->size - i - 1]);
        }
    }
    
    return 0;
}
