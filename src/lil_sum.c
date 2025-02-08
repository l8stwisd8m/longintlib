#include <iso646.h>
#include <assert.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"

void lil_sum(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // arithmetic sum of a and b
    
    int a_is_null_flag = lil_is_null(src_a);
    int b_is_null_flag = lil_is_null(src_b);

    // a = b = 0 => a + b = 0
    if (a_is_null_flag and b_is_null_flag) {
        for (int i = 0; i < dst->size; dst->val[i++] = 0);
        dst->sign = LIL_PLUS;
        return; 
    }
    
    // a = 0 => a + b = b
    if (a_is_null_flag) {
        assert(dst->size >= src_b->size);
        for (int i = 0; i < src_b->size; i++) {
            dst->val[i] = src_b->val[i];
        }
        dst->sign = src_b->sign;
        return;
    }

    // b = 0 => a + b = a
    if (b_is_null_flag) {
        assert(dst->size >= src_a->size);
        for (int i = 0; i < src_a->size; i++) {
            dst->val[i] = src_a->val[i];
        }
        dst->sign = src_a->sign;
        return;
    }
    
    // assetion for arithmetic sum calculation in other cases
    if (src_a->size >= src_b->size) assert(dst->size >= src_a->size);
    else assert(dst->size >= src_b->size);
    
    // (-a) + (-b) = -(a + b)
    if (src_a->sign and src_b->sign) {
        for (int i = 0; i < src_a->size; i++) {
            dst->val[i] = src_a->val[i];
        }
        lil_add(dst, src_b);
        dst->sign = LIL_MINUS;
        return;
    }
    
    // a and b values comparison
    int cmp_flag = lil_cmp_val(src_a, src_b);
    
    // abs(a) = abs(b), a < 0 < b or b < 0 < a => a + b = 0
    if ((cmp_flag == 0) and (src_a->sign or src_b->sign)) {
        for (int i = 0; i < dst->size; dst->val[i++] = 0);
        dst->sign = LIL_PLUS;
        return;
    }
    
    // a < 0 < b, abs(a) < abs(b) => a + b = (b - a)
    if (src_a->sign and (cmp_flag == -1)) {
        for (int i = 0; i < src_b->size; i++) {
            dst->val[i] = src_b->val[i];
        }
        lil_sub(dst, src_a);
        dst->sign = LIL_PLUS;
        return;
    }
         
    // a < 0 < b, abs(a) > abs(b) => a + b = -(a - b)
    if (src_a->sign and (cmp_flag == 1)) {
        for (int i = 0; i < src_a->size; i++) {
            dst->val[i] = src_a->val[i];
        }
        lil_sub(dst, src_b);
        dst->sign = LIL_MINUS;
        return;
    }
    
    // b < 0 < a, abs(a) < abs(b) => a + b = -(b - a)
    if (src_b->sign and (cmp_flag == -1)) {
        for (int i = 0; i < src_b->size; i++) {
            dst->val[i] = src_b->val[i];
        }
        lil_sub(dst, src_a);
        dst->sign = LIL_MINUS;
        return;
    }
    
    // b < 0 < 0, abs(a) < abs(b) => a + b = (a - b)
    if (src_b->sign and (cmp_flag == 1)) {
        for (int i = 0; i < src_a->size; i++) {
            dst->val[i] = src_a->val[i];
        }
        lil_sub(dst, src_b);
        dst->sign = LIL_PLUS;
        return;
    }
    
    // a + b
    for (int i = 0; i < src_a->size; i++) {
        dst->val[i] = src_a->val[i];
    }
    lil_add(dst, src_b);
    dst->sign = LIL_PLUS;
}
