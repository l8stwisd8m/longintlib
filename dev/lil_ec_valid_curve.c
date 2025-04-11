#include <iso646.h>
#include "../include/longintlib.h"
#include "../include/longintmacro.h"
#include "../include/longintcurve.h"

int lil_ec_valid_curve(lil_ec_t *curve) {
    // check if curve is non-singular
    
    // TODO: check exceptions
    
    int flag = 0;
    long_int *val_a, *val_b, *val_d;
    LIL_MALLOC(val_a, curve->m->size);
    LIL_MALLOC(val_b, curve->m->size);
    LIL_MALLOC(val_d, curve->m->size);
    
    lil_mul_mod(val_a, curve->a, curve->a, curve->m); // a ^ 2 mod m
    LIL_CPY_VAL(val_d, val_a);
    LIL_SET_PLUS(val_d);
    lil_mul_mod(val_a, val_d, curve->a, curve->m);    // a ^ 3 mod m
    lil_shl(val_a);
    lil_shl(val_a);
    lil_val_mod(val_a, curve->m);                     // 4 * a ^ 3 mod m
    
    lil_mul_mod(val_b, curve->b, curve->b, curve->m); // b ^ 2 mod m
    lil_short_mul(val_b, 27);
    lil_val_mod(val_b, curve->m);                     // 27 * b ^ 2 mod m
    
    // check if discriminant is congruent to zero
    lil_sum_mod(val_d, val_a, val_b, curve->m);       // 4 * a ^ 3 + 27 * b ^ 2 mod m
    flag = not lil_is_null(val_d);
    
    LIL_FREE(val_a);
    LIL_FREE(val_b);
    LIL_FREE(val_d);
    
    return flag;
}
