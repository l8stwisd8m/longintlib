#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

void lil_div(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // return floor from division of a by b

    uint64_t a_len = 0;
    uint64_t b_len = 0;
    uint64_t offset = 0;

    // default result
    dst->sign = LIL_PLUS;
    LIL_SET_NULL(dst);
    
    // exceptions
    if (lil_is_null(src_a)) return; // a = 0 => a mod b = 0
    assert(lil_is_null(src_b) == 0); // invalid b value
    assert((src_a->size == dst->size) and (src_b->size == dst->size)); // operand sizes mismatch error
     
    int cmp_flag = lil_cmp_val(src_a, src_b);
    if (cmp_flag == -1) {
        return; // abs(a) < b => floor(a/b) = 0
    }
    if (cmp_flag == 0) {
        dst->val[0] = 1;
        return; // abs(a) = b => floor(a/b) = 1
    }
    
    a_len = lil_len(src_a);
    b_len = lil_len(src_b);
    offset = a_len - b_len;
    
    dst->sign = src_a->sign;

    // save initial values of a and b
    long_int *src_a_initial, *src_b_initial;
    LIL_MALLOC(src_a_initial, src_a->size);
    LIL_MALLOC(src_b_initial, src_b->size);
    lil_cpy(src_a_initial, src_a);
    lil_cpy(src_b_initial, src_b);
    
    // left shift b while b < a
    lil_shln(src_b, offset);
    if (lil_cmp_val(src_a, src_b) == -1) {
        lil_shr(src_b);
        offset -= 1;
    }

    // temporary structure
    long_int *src_t;
    LIL_CALLOC(src_t, src_a->size);

    // div calculation
    src_a->sign = LIL_PLUS;
    src_b->sign = LIL_MINUS;
    for (int i = 0; i <= offset; i++) {
        lil_shl(dst); // dst *= 2
        lil_sum(src_t, src_a, src_b); // t = a - b
        if ((src_t->sign == LIL_PLUS) or lil_is_null(src_t)) {
            lil_inc(dst); // dst++
            lil_cpy(src_a, src_t); // a = t
        }
        lil_shr(src_b); // b /= 2
    }

    LIL_FREE(src_t);

    // restore values of a and b
    lil_cpy(src_a, src_a_initial);
    lil_cpy(src_b, src_b_initial);
    LIL_FREE(src_a_initial);
    LIL_FREE(src_b_initial);
}
