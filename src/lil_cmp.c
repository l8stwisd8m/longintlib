#include <iso646.h>
#include <stddef.h>
#include "longintlib.h"

int lil_cmp(lil_t *src_a, lil_t *src_b) {
    // return 0 if a = b, -1 if a < b, 1 if a > b
    
    if (lil_is_null(src_a) and lil_is_null(src_b)) return 0; // a = b = 0
    if (src_a->sign and not src_b->sign) return -1; // a < 0 < b
    if (not src_a->sign and src_b->sign) return 1;  // a > 0 > b

    size_t a_len = lil_len(src_a);
    size_t b_len = lil_len(src_b);
    
    if (a_len > b_len) {
        if (src_a->sign) return -1; // a < b < 0
        else return 1;              // 0 < b < a
    }
    if (a_len < b_len) {
        if (src_a->sign) return 1;  // b < a < 0
        else return -1;             // 0 < a < b
    }

    size_t i = 0; size_t j = 0;
    size_t cmp_size = (src_a->size > src_b->size) ? src_b->size : src_a->size; // min( size(a), size(b) )
    for (i = 0; i < cmp_size; i++) {
        j = cmp_size - i - 1;
        if (src_a->val[j] > src_b->val[j]) {
            if (src_a->sign) return -1; // a < b < 0
            else return 1;              // 0 < b < a
        }
        if (src_a->val[j] < src_b->val[j]) {
            if (src_a->sign) return 1;  // b < a < 0
            else return -1;             // 0 < a < b
        }
    }
    
    return 0; // a = b
}
