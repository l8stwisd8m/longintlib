#include <assert.h>
#include "longintlib.h"
#include "longintconst.h"
#include "longintmacro.h"
#include "longintcurve.h"

int lil_ec_embed(lil_ec_t *curve, lil_point_t *dst, lil_t *src) {
    // long integer source embedding into point
    
    // TODO: check exceptions
    
    // correct input
    lil_val_mod(src, curve->m);
    
    // empty value
    if (lil_is_null(src)) {
        LIL_EC_SET_NULL(dst);
        return 0;
    }
    
    long_int *tmp, *eval;
    LIL_MALLOC(tmp, src->size);
    LIL_MALLOC(eval, src->size);
    LIL_CPY_VAL(tmp, src);
    lil_ec_evaluate(curve, eval, tmp);
    
    // while evaluation of source value is not a quadratic residue increment it
    while (lil_jacobi(eval, curve->m) != 1) {
        lil_inc(tmp);
        lil_ec_evaluate(curve, eval, tmp);
        
        // attempt to find point corresponding to source value failed
        if (lil_cmp_val(tmp, src) == 0) {
            LIL_FREE(tmp);
            LIL_FREE(eval);
            LIL_EC_SET_NULL(dst);
            return LIL_NO_ANSWER;
        }
    }
    
    // embedding source value to x and it's evaluation square root to y
    LIL_CPY_VAL(dst->x, tmp);
    lil_sqrt_mod(dst->y, eval, curve->m);
    
    assert(lil_ec_valid_point(curve, dst) == LIL_EC_VALID);
    
    LIL_FREE(tmp);
    LIL_FREE(eval);
    return 0;
}
