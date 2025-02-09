#include <iso646.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

uint64_t lil_short_mod(lil_t *src_a, uint64_t val_b) {
    // return short remainder after division of long a by short b
    
    // exceptions
    if (lil_is_null(src_a)) return 0; // a = 0 => a mod b = 0
    assert(val_b);
    
    // casting b value to long_int
    lil_t *src_b = (lil_t *)malloc(sizeof(lil_t));
    assert(src_b);
    src_b->size = src_a->size;
    src_b->val = calloc(src_b->size, sizeof(uint64_t));
    assert(src_b->val);
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
    
    // memory allocation for temporary structure
    lil_t *src_t = (lil_t *)malloc(sizeof(lil_t));
    assert(src_t);
    src_t->size = src_a->size;
    src_t->val = calloc(src_t->size, sizeof(uint64_t));
    assert(src_t->val);
    
    // save initial value of a
    int src_a_sign = src_a->sign;
    uint64_t *src_a_initial = (uint64_t *)malloc(src_a->size * sizeof(uint64_t));
    assert(src_a_initial);
    for (int i = 0; i < src_a->size; i++) {
        src_a_initial[i] = src_a->val[i];
    }
    
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
    src_a->sign = src_a_sign;
    for (int i = 0; i < src_a->size; i++) {
        src_a->val[i] = src_a_initial[i];
    }
    free(src_a_initial);
    
    free(src_t->val);
    free(src_t);
    free(src_b->val);
    free(src_b);
    return result;
}
