#include <stdlib.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void lil_mod(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // return remainder after division of a by b

    uint64_t a_len = 0;
    uint64_t b_len = 0;
    uint64_t offset = 0;

    // default result
    dst->sign = LIL_PLUS;
    for (int i = 0; i < dst->size; dst->val[i++] = 0);

    // exceptions
    if (lil_is_null(src_a)) return; // a = 0 => a mod b = 0
    assert(lil_is_null(src_b) == 0); // invalid b value
    assert((src_a->size == dst->size) and (src_b->size == dst->size)); // operand sizes mismatch error

    a_len = lil_len(src_a);
    b_len = lil_len(src_b);
    offset = a_len - b_len;
     
    int cmp_flag = lil_cmp_val(src_a, src_b);
    if (cmp_flag == -1) {
        for (int i = 0; i < dst->size; i++) {
            dst->val[i] = src_a->val[i];
        }
        return; // abs(a) < b => a mod b = a
    }
    if (cmp_flag == 0) {
        return; // abs(a) = b => a mod b = 0
    }
    
    // save initial values of a and b
    int src_a_sign = src_a->sign;
    int src_b_sign = src_b->sign;
    uint64_t *src_a_initial = (uint64_t *)malloc(src_a->size * sizeof(uint64_t));
    uint64_t *src_b_initial = (uint64_t *)malloc(src_b->size * sizeof(uint64_t));
    assert(src_a_initial and src_b_initial);
    for (int i = 0; i < src_a->size; i++) {
        src_a_initial[i] = src_a->val[i];
        src_b_initial[i] = src_b->val[i];
    }
    
    // left shift b while b < a
    lil_shln(src_b, offset);
    if (lil_cmp_val(src_a, src_b) == -1) {
        lil_shr(src_b);
        offset -= 1;
    }
    
    // mod calculation
    src_a->sign = LIL_PLUS;
    src_b->sign = LIL_MINUS;
    for (int i = 0; i <= offset; i++) {
        lil_sum(dst, src_a, src_b); // t = a - b
        if ((dst->sign == LIL_PLUS) or lil_is_null(dst)) {
            lil_cpy(src_a, dst); // a = t
        }
        lil_shr(src_b); // b /= 2
    }
    lil_cpy(dst, src_a); // result
    
    // restore values of a and b
    for (int i = 0; i < src_a->size; i++) {
        src_a->val[i] = src_a_initial[i];
        src_b->val[i] = src_b_initial[i];
    }
    src_a->sign = src_a_sign;
    src_b->sign = src_b_sign;
    
    free(src_a_initial);
    free(src_b_initial);
}
