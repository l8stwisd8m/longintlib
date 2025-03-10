#include <errno.h>
#include <stdio.h>
#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintconst.h"
#include "../include/longintmacro.h"

int lil_sum(lil_t *dst, lil_t *src_a, lil_t *src_b) {
    // arithmetic sum of a and b
    
    int flag = 0;
    int a_is_null_flag = lil_is_null(src_a);
    int b_is_null_flag = lil_is_null(src_b);

    // a = b = 0 => a + b = 0
    if (a_is_null_flag and b_is_null_flag) {
        LIL_SET_NULL(dst);
        dst->sign = LIL_PLUS;
        return flag; 
    }
    
    // a = 0 => a + b = b
    if (a_is_null_flag) {
        lil_cpy(dst, src_b);
        return flag;
    }

    // b = 0 => a + b = a
    if (b_is_null_flag) {
        lil_cpy(dst, src_a);
        return flag;
    }
    
    // assetion for arithmetic sum calculation in other cases
    if (((src_a->size >= src_b->size) and (dst->size < src_a->size)) or 
        ((src_b->size >= src_a->size) and (dst->size < src_b->size))) {
        errno = ERR_SIZE_MISMATCH;
        perror("Invalid size of destination value; sum calculation can not be performed");
        exit(EXIT_FAILURE);
    }
    
    // (-a) + (-b) = -(a + b)
    if (src_a->sign and src_b->sign) {
        LIL_CPY_VAL(dst, src_a);
        flag = lil_add(dst, src_b);
        dst->sign = LIL_MINUS;
        return flag;
    }
    
    // a and b values comparison
    int cmp_flag = lil_cmp_val(src_a, src_b);
    
    // abs(a) = abs(b), a < 0 < b or b < 0 < a => a + b = 0
    if ((cmp_flag == 0) and (src_a->sign or src_b->sign)) {
        LIL_SET_NULL(dst);
        dst->sign = LIL_PLUS;
        return flag;
    }
    
    // a < 0 < b, abs(a) < abs(b) => a + b = (b - a)
    if (src_a->sign and (cmp_flag == -1)) {
        LIL_CPY_VAL(dst, src_b);
        flag = lil_sub(dst, src_a);
        dst->sign = LIL_PLUS;
        return flag;
    }
    
    // a < 0 < b, abs(a) > abs(b) => a + b = -(a - b)
    if (src_a->sign and (cmp_flag == 1)) {
        LIL_CPY_VAL(dst, src_a);
        flag = lil_sub(dst, src_b);
        dst->sign = LIL_MINUS;
        return flag;
    }
    
    // b < 0 < a, abs(a) < abs(b) => a + b = -(b - a)
    if (src_b->sign and (cmp_flag == -1)) {
        LIL_CPY_VAL(dst, src_b);
        flag = lil_sub(dst, src_a);
        dst->sign = LIL_MINUS;
        return flag;
    }
    
    // b < 0 < 0, abs(a) < abs(b) => a + b = (a - b)
    if (src_b->sign and (cmp_flag == 1)) {
        LIL_CPY_VAL(dst, src_a);
        flag = lil_sub(dst, src_b);
        dst->sign = LIL_PLUS;
        return flag;
    }
    
    // a > 0, b > 0 => a + b = a + b
    LIL_CPY_VAL(dst, src_a);
    flag = lil_add(dst, src_b);
    dst->sign = LIL_PLUS;
    return flag;
}
