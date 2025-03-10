#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

uint64_t lil_len(lil_t *src) {
    // return bit length of source
    
    if (lil_is_null(src)) return 0;
    uint64_t bit_len = LIL_BASE * src->size; // result
    
    for (size_t i = 0; i < src->size; i++) {
        if (src->val[src->size - i - 1]) {
            for (int j = 0; j < LIL_BASE; j++) {
                if (LIL_MSBIT & (src->val[src->size - i - 1] << j)) {
                    bit_len -= j;
                    break;
                }
            }
            break;
        }
        else bit_len -= LIL_BASE;
    }
    
    return bit_len;
}
