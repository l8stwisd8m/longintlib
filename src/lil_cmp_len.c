#include "longintlib.h"

int lil_cmp_len(lil_t *src_a, lil_t *src_b) {
    // return 0 if len(a) = len(b), -1 if len(a) < len(b), 1 if len(a) > len(b)
    
    size_t a_len = lil_len(src_a);
    size_t b_len = lil_len(src_b);
    
    if (a_len > b_len) return 1;    // length(a) > length(b)
    if (a_len < b_len) return -1;   // length(a) < length(b)
    return 0;                       // length(a) = length(b)
}
