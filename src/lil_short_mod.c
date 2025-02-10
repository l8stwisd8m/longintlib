#include <iso646.h>
#include <stdint.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

uint64_t lil_short_mod(lil_t *src_a, uint64_t val_b) {
    // return short remainder after division of long a by short b
    
    // exceptions
    if (lil_is_null(src_a)) return 0; // a = 0 => a mod b = 0
    assert(val_b);
    
    // casting b value to long_int
    lil_t *src_b;
    LIL_CALLOC(src_b, src_a->size);
    src_b->val[0] = val_b;
    
    int cmp_flag = lil_cmp_val(src_a, src_b);
    if (cmp_flag == -1) {
        free(src_b->val);
        free(src_b);
        return src_a->val[0]; // abs(a) < b => a mod b = a
    }
    if (cmp_flag == 0) {
        free(src_b->val);
        free(src_b);
        return 0; // abs(a) = b => a mod b = 0
    }
    
    uint64_t a_len = lil_len(src_a);
    uint64_t b_len = lil_len(src_b);
    uint64_t offset = a_len - b_len;
    
    // left shift b while b < a
    lil_shln(src_b, offset);
    if (lil_cmp_val(src_a, src_b) == -1) {
        lil_shr(src_b);
        offset -= 1;
    }
    
    // temporary structure
    long_int *src_t;
    LIL_CALLOC(src_t, src_a->size);
    
    // save initial value of a
    long_int *src_a_initial;
    LIL_MALLOC(src_a_initial, src_a->size);
    lil_cpy(src_a_initial, src_a);
    
    // mod calculation
    src_a->sign = LIL_PLUS;
    src_b->sign = LIL_MINUS;
    for (int i = 0; i <= offset; i++) {
        lil_sum(src_t, src_a, src_b); // t = a - b
        if ((src_t->sign == LIL_PLUS) or lil_is_null(src_t)) {
            lil_cpy(src_a, src_t); // a = t
        }
        lil_shr(src_b); // b /= 2
    }

    uint64_t result = src_a->val[0];

    // restore value of a
    lil_cpy(src_a, src_a_initial);
    LIL_FREE(src_a_initial);
    
    LIL_FREE(src_t);
    LIL_FREE(src_b);
    return result;
}
