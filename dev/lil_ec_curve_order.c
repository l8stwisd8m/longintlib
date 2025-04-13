#include "../include/longintlib.h"
#include "../include/longintmacro.h"
#include "../include/longintcurve.h"

int lil_ec_curve_order(lil_ec_t *curve, lil_t *dst) {
    // order of a curve
    
    // TODO: check exceptions
    
    // count one special point
    LIL_SET_NULL(dst);
    LIL_LSD(dst) = 1;
    
    long_int *tmp, *ctr;
    LIL_CALLOC(ctr, curve->m->size);
    LIL_MALLOC(tmp, curve->m->size);
    
    // count other points
    while (lil_cmp_val(ctr, curve->m) != 0) {
        lil_ec_evaluate(curve, tmp, ctr);
        
        // (ctr | m) = 0 => there is one more point
        if (lil_is_null(tmp)) {
            lil_inc(dst);
            lil_inc(ctr);
            continue;
        }
        
        // (ctr | m) = 1 => there are two more points
        if (lil_jacobi(tmp, curve->m) == 1) {
            lil_inc(dst);
            lil_inc(dst);
        }
        
        lil_inc(ctr);
    }
    
    LIL_FREE(tmp);
    LIL_FREE(ctr);
    return 0;
}
