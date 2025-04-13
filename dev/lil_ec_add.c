#include "../include/longintlib.h"
#include "../include/longintmacro.h"
#include "../include/longintcurve.h"

int lil_ec_add(lil_ec_t *curve, lil_point_t *dst, lil_point_t *src_p, lil_point_t *src_q) {
    // sum of points p and q
    
    // TODO: check exceptions
    
    // p = 0 => p + q = q
    if (LIL_EC_SPECIAL_POINT(src_p)) {
        lil_ec_cpy(dst, src_q);
        return 0;
    }
    
    // q = 0 => p + q = p
    if (LIL_EC_SPECIAL_POINT(src_q)) {
        lil_ec_cpy(dst, src_p);
        return 0;
    }
    
    // numerator and denominator of tangent slope
    long_int *tgs_num, *tgs_den;
    LIL_MALLOC(tgs_num, curve->m->size);
    LIL_MALLOC(tgs_den, curve->m->size);
    // temporary variables (in advance)
    long_int *tmp, *val;
    LIL_MALLOC(tmp, curve->m->size);
    LIL_MALLOC(val, curve->m->size);
    
    lil_sum_mod(tgs_den, src_p->y, src_q->y, curve->m); // y_p + y_q
    
    if (lil_is_null(tgs_den)) {
        LIL_CPY_VAL(tmp, src_p->x);
        tmp->sign = !(src_p->x->sign);
        lil_sum_mod(tgs_num, tmp, src_q->x, curve->m);  // x_q - x_p
        
        // (x_q - x_p) = 0 => r = (0, 0)
        if (lil_is_null(tgs_num)) {
            LIL_EC_SET_NULL(dst);
            LIL_FREES(tmp, val, tgs_num, tgs_den);
            return 0;
        }
        
        // (x_q - x_p) != 0 
        
        // denominator recalculation
        LIL_CPY_VAL(tmp, src_p->y);
        tmp->sign = !(src_p->y->sign);
        lil_sum_mod(tgs_den, tmp, src_q->y, curve->m);  // y_q - y_p
        
        // swap numerator and denominator
        long_int *tmp_ptr = tgs_num;
        tgs_num = tgs_den;
        tgs_den = tmp_ptr;
    }
    else {
        lil_mul_mod(tmp, src_p->x, src_p->x, curve->m); // x_p * x_p
        lil_mul_mod(val, src_p->x, src_q->x, curve->m); // x_p * x_q
        lil_sum_mod(tgs_num, tmp, val, curve->m);       // x_p ^ 2 + x_p * x_q
        lil_mul_mod(val, src_q->x, src_q->x, curve->m); // x_q * x_q
        lil_sum_mod(tmp, val, tgs_num, curve->m);       // x_p ^ 2 + x_p * x_q + x_q ^ 2
        lil_sum_mod(tgs_num, tmp, curve->a, curve->m);  // x_p ^ 2 + x_p * x_q + x_q ^ 2 + a
    }
    
    // tangent slope 
    long_int *tgs = val;
    lil_div_mod(tgs, tgs_num, tgs_den, curve->m);
    
    // actual point calculation
    
    // abscissa
    lil_mul_mod(tgs_num, tgs, tgs, curve->m);           // tgs ^ 2
    lil_sum_mod(tgs_den, src_p->x, src_q->x, curve->m); // x_p + x_q
    tgs_den->sign = !(tgs_den->sign);
    lil_sum_mod(dst->x, tgs_num, tgs_den, curve->m);    // x_r <- tgs ^ 2 - (x_p + x_q)
    
    // ordinate
    LIL_CPY_VAL(tmp, dst->x);
    tmp->sign = !(dst->x->sign);
    lil_sum_mod(tgs_num, tmp, src_p->x, curve->m);      // x_p - x_r
    lil_mul_mod(tgs_den, tgs_num, tgs, curve->m);       // tgs * (x_p - x_r)
    LIL_CPY_VAL(tgs_num, src_p->y);
    tgs_num->sign = !(src_p->y->sign);
    lil_sum_mod(dst->y, tgs_num, tgs_den, curve->m);    // y_r <- tgs * (x_p - x_r) - y_p
    
    LIL_FREES(tmp, tgs, tgs_num, tgs_den);
    return 0;
}
