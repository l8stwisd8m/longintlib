#include <stddef.h>
#include <stdint.h>
#include "../include/longintlib.h"

int lil_cmp_val(lil_t *src_a, lil_t *src_b) {
    // return 0 if abs(a) = abs(b), -1 if abs(a) < abs(b), 1 if abs(a) > abs(b)
    
    uint64_t a_len = lil_len(src_a);
    uint64_t b_len = lil_len(src_b);
    int cmp_flag = (a_len > b_len) ? 1 : -1;
    size_t i = 0; size_t j = 0;
    size_t cmp_size = (src_a->size > src_b->size) ? src_b->size : src_a->size; // min( size(a), size(b) )
    
    if (a_len == b_len) {
        cmp_flag = 0;
        for (i = 0; i < cmp_size; i++) {
            j = cmp_size - i - 1;
            if (src_a->val[j] > src_b->val[j]) {
                cmp_flag = 1;
                break;
            }
            if (src_a->val[j] < src_b->val[j]) {
                cmp_flag = -1;
                break;
            }
        }
    }
    
    return cmp_flag;
}
