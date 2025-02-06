#include <stdint.h>
#include "../include/longintlib.h"

int lil_cmp_val(lil_t *src_a, lil_t *src_b) {
    // return 0 if abs(a) = abs(b), -1 if abs(a) < abs(b), 1 if abs(a) > abs(b)
    uint64_t a_len = lil_len(src_a);
    uint64_t b_len = lil_len(src_b);
    int cmp_flag = (a_len > b_len) ? 1 : -1;
    uint64_t cmp_size = (src_a->size > src_b->size) ? src_b->size : src_a->size; // min( size(a), size(b) )
    if (a_len == b_len) {
        cmp_flag = 0;
        for (int i = cmp_size - 1; i >= 0; i--) {
            if (src_a->val[i] > src_b->val[i]) {
                cmp_flag = 1;
                break;
            }
            if (src_a->val[i] < src_b->val[i]) {
                cmp_flag = -1;
                break;
            }
        }
    }
    return cmp_flag;
}
