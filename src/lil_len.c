#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

uint64_t lil_len(lil_t *src) {
    // return bit length of source
    if (lil_is_null(src)) return 0;
    uint64_t bit_len = 64 * src->size; // result
    for (int i = src->size - 1; i >= 0; i--) {
        if (src->val[i]) {
            for (int j = 0; j < 64; j++) {
                if (LIL_MSBIT & (src->val[i] << j)) {
                    bit_len -= j;
                    break;
                }
            }
            break;
        }
        else bit_len -= 64;
    }
    return bit_len;
}
