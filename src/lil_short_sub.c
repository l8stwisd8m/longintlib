#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

int lil_short_sub(lil_t *src_a, uint64_t src_b) {
    // subtract short abs(b) from abs(values) of long a
    
    uint64_t tmp = src_a->val[0];
    src_a->val[0] -= src_b;
    
    // borrow
    if (tmp < src_a->val[0]) {
        for (size_t i = 1; i < src_a->size; i++) {
            if (src_a->val[i] == 0) src_a->val[i] = ~0;
            else {
                src_a->val[i] -= 1;
                return 0;
            }
        }
        return LIL_OVERFLOW;
    }
    else return 0;
}
