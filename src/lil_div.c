#include <stdlib.h>
#include <stdint.h>
#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"

void lil_div(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // return floor from division of a by b

    uint64_t a_len = 0;
    uint64_t b_len = 0;
    uint64_t offset = 0;

    // default result
    dst->sign = 0;
    for (int i = 0; i < dst->size; dst->val[i++] = 0);

    // exceptions
    if (lil_is_null(src_b)) return; // invalid b value
    if (lil_is_null(src_a)) return; // a = 0 => a mod b = 0
    if (src_a->size != src_b->size or src_b->size != dst->size) return; // operand sizes mismatch error

    a_len = lil_len(src_a);
    b_len = lil_len(src_b);
    offset = a_len - b_len;

    if (b_len > a_len) return; // floor(a/b) = 0
    dst->sign = src_a->sign;

    // save initial values of a and b
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

    // memory allocation for temporary structure
    lil_t *src_t = (lil_t*)malloc(sizeof(lil_t));
    src_t->size = src_a->size;
    src_t->val = (uint64_t *)calloc(src_t->size, sizeof(uint64_t));
    assert(src_t and src_t->val);

    // mod calculation
    src_a->sign = 0;
    src_b->sign = 1;
    for (int i = 0; i <= offset; i++) {
        lil_shl(dst); // dst *= 2
        lil_sum(src_t, src_a, src_b); // t = a - b
        if (not src_t->sign or lil_is_null(src_t)) {
            lil_inc(dst); // dst++
            lil_cpy(src_a, src_t); // a = t
        }
        lil_shr(src_b); // b /= 2
    }

    free(src_t->val);
    free(src_t);

    // restore values of a and b
    for (int i = 0; i < src_a->size; i++) {
        src_a->val[i] = src_a_initial[i];
        src_b->val[i] = src_b_initial[i];
    }
    
    free(src_a_initial);
    free(src_b_initial);
}
