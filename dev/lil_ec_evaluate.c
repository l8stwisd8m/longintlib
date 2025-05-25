#include "longintlib.h"
#include "longintmacro.h"
#include "longintcurve.h"

int lil_ec_evaluate(lil_ec_t *curve, lil_t *dst, lil_t *src) {
    // long integer source evaluation
    
    // TODO: check exceptions
    
    // correct input
    lil_val_mod(src, curve->m);
    
    // temporary values
    lil_t *tmp, *val;
    LIL_MALLOC(tmp, src->size);
    LIL_MALLOC(val, src->size);
    
    // evaluation
    LIL_CPY_VAL(tmp, src);
    lil_mul_mod(dst, tmp, src, curve->m);       // x ^ 2 mod m
    LIL_CPY_VAL(tmp, dst);
    lil_mul_mod(dst, tmp, src, curve->m);       // x ^ 3 mod m
    lil_mul_mod(val, src, curve->a, curve->m);  // a * x mod m
    LIL_CPY_VAL(tmp, dst);
    lil_sum_mod(dst, tmp, val, curve->m);       // x ^ 3 + a * x mod m
    LIL_CPY_VAL(tmp, dst);
    lil_sum_mod(dst, tmp, curve->b, curve->m);  // x ^ 3 + a * x + b mod m
    
    LIL_FREE(tmp);
    LIL_FREE(val);
    
    return 0;
}
