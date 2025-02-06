#include <iso646.h>
#include <stdint.h>
#include "../include/longintlib.h"

void lil_sum(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // arithmetic sum of a and b

    if (lil_is_null(src_a) and lil_is_null(src_b)) return; // a = b = 0

    //if (dst->size < src_a->size or dst->size < src_b->size) return; // error

    // a = 0, a + b = b
    if (lil_is_null(src_a)) {
        dst->sign = src_b->sign;
        for (int i = 0; i < src_b->size; i++) dst->val[i] = src_b->val[i];
        return;
    }

    // b = 0, a + b = a
    if (lil_is_null(src_b)) {
        dst->sign = src_a->sign;
        for (int i = 0; i < src_a->size; i++) dst->val[i] = src_a->val[i];
        return;
    }

    // (-a) + (-b) = -(a + b)
    if (src_a->sign and src_b->sign) {
        dst->sign = 1; // minus
        for (int i = 0; i < src_a->size; i++) dst->val[i] = src_a->val[i];
        lil_add(dst, src_b);
        return;
    }

    // a and b values comparison
    int cmp_flag = lil_cmp_val(src_a, src_b);

    // (-a) + b or (-b) + a
    if (src_a->sign or src_b->sign) {
        // abs(a) = abs(b)
        if (cmp_flag == 0) {
            dst->sign = 0;
            return; // (-a) + b = 0 or (-b) + a = 0
        }

        // (-a) + b = b - a
        if (src_a->sign) {
            dst->sign = (cmp_flag == 1) ? 1 : 0; // b - a < 0 if a > b
            for (int i = 0; i < src_b->size; i++) dst->val[i] = src_b->val[i];
            lil_sub(dst, src_a);
            return;
        }

        // a + (-b) = a - b
        if (src_b->sign) {
            dst->sign = (cmp_flag == 1) ? 0 : 1; // b - a < 0 if a < b
            for (int i = 0; i < src_a->size; i++) dst->val[i] = src_a->val[i];
            lil_sub(dst, src_b);
            return;
        }
    }

    // a + b
    dst->sign = 0; // plus
    for (int i = 0; i < src_a->size; i++) dst->val[i] = src_a->val[i];
    lil_add(dst, src_b);
}
